/////////////////////////////////////////////////////////////////////////////////
// Includes
/////////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "Render/Filter.h"
#include "Render/IConfigManager.h"
#include "System/FileSystem/FileSystemChangesProcessor.h"

#include "PFClientVisibilityMap.h"

#include "Scene/Scene.h"
#include "Terrain/Terrain.h"

#include "AdventureScreen.h"
#include "System/InlineProfiler.h"
#include "PFClientBaseUnit.h"

#include "PFWorld.h"
#include "PFAIWorld.h"

#include "ClientVisibilityHelper.h"

BASIC_REGISTER_CLASS(NGameX::VisibilityMapClient)

/////////////////////////////////////////////////////////////////////////////////
// Defines
/////////////////////////////////////////////////////////////////////////////////

namespace
{
  DEV_VAR_STATIC int g_visMapMode = NGameX::EVisMapMode::Undefined;
  DEV_VAR_STATIC int g_visMapModeLast = NGameX::EVisMapMode::Undefined;

  DECLARE_NULL_RENDER_FLAG
}

REGISTER_DEV_VAR( "vismapmode", g_visMapMode, STORAGE_NONE );

namespace NGameX
{

struct WarFogParams 
{
  NDb::WarFogType  warFogType;
  Render::Color colors[2];
  float warFogMiniMapAlphaScale;
};
 

/////////////////////////////////////////////////////////////////////////////////
// Methods
/////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool VisibilityMapClient::SetVisMapMode(int visMapMode)
{
#ifndef _SHIPPING
  if (visMapMode < EVisMapMode::Last)
  {
    g_visMapMode = visMapMode;
    return true;
  }
#else
  (void)visMapMode;
#endif

  return false;
}

int VisibilityMapClient::GetVisMapMode()
{
#ifndef _SHIPPING
  return g_visMapMode;
#else
  return EVisMapMode::Undefined;
#endif
}

int VisibilityMapClient::GetVisMapAllMode()
{
  return EVisMapMode::Everything;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
VisibilityMapClient::VisibilityMapClient(NWorld::PFWorld * _world)
  : DeviceLostHandler(HANDLERPRIORITY_LOW)
  , m_texSource(NULL)
  , m_texBlended(NULL)
  , m_ratio(0)
  , m_texIndex(0)
  , m_stepNumber(0)
  , m_warfogMapping(0.0f,0.0f,0.0f,0.0f)
  , m_warfogParams(new WarFogParams)
  , world(_world)
  , currentworldStep(0)
  , m_created( false )
  , m_disabled( true )
  , m_initialized(false)
  , m_doBlur(false)
{
  NI_PROFILE_FUNCTION

  m_texStep[0] = NULL;
  m_texStep[1] = NULL;

  numUpdatesBetweenSteps  = 0;
  indexUpdateCur          = 0;

  m_stepNumber            = 0;

  // initial
  SetSpectatorMode(false);

  NI_VERIFY(IsValid(world), "Invalid world", delete m_warfogParams; return);
  NI_VERIFY(IsValid(fogOfWar), "Invalid warfog", delete m_warfogParams; return);

  OnCreate (fogOfWar->GetWidth(), fogOfWar->GetHeight(), world->GetScene());
}

VisibilityMapClient::~VisibilityMapClient()
{
  if (m_warfogParams)
    delete m_warfogParams;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool  VisibilityMapClient::OnCreate(int texSideX, int texSideY, NScene::IScene * scene)
{
  NI_PROFILE_FUNCTION

  const CVec3 & worldSize =  scene->GetTerrain()->GetGridConstants().worldSize;
  NDb::LightEnvironment const *lightEnv = scene->GetAdvMapLightEnvironment();

  m_warfogMapping.Set(1.0f / worldSize.x, -1.0f / worldSize.y, 0.0f, 1.0f);

  m_texSource  = Render::CreateTexture2D(texSideX, texSideY, 1, Render::RENDER_POOL_MANAGED, Render::FORMAT_A8R8G8B8);
  m_texStep[0] = Render::CreateRenderTexture2D(texSideX, texSideY, Render::FORMAT_A8R8G8B8);
  m_texStep[1] = Render::CreateRenderTexture2D(texSideX, texSideY, Render::FORMAT_A8R8G8B8);
  m_texBlended = Render::CreateRenderTexture2D(texSideX, texSideY, Render::FORMAT_A8R8G8B8);

  // prepare blur effect
  blurEffect.Init(texSideX, texSideY);

  NI_ASSERT(lightEnv, "Invalid light environment");

  lightEnvironment = lightEnv;
  OnLightingEnvironmentChanged("");
  // hook on lighting environment change
  RootFileSystem::GetChangesProcessor().RegisterFileWatchByName( lightEnv->GetDBID().GetFileName(),
    new FileWatchMethodFunctor<VisibilityMapClient>( this, &VisibilityMapClient::OnLightingEnvironmentChanged ) );

  m_created = true;

  FillTexture(m_texSource, FS_INIT);

  return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void VisibilityMapClient::OnLightingEnvironmentChanged( const string& )
{ // TODO - change color initialization
  m_warfogParams->colors[0] = lightEnvironment->warFogColor;
  m_warfogParams->colors[1] = lightEnvironment->warFogColor2;
  m_warfogParams->warFogType = lightEnvironment->warFogType;
  m_warfogParams->warFogMiniMapAlphaScale = lightEnvironment->warFogMiniMapAlphaScale;

  NI_VERIFY(IsValid(world), "Invalid world", return);
  NI_VERIFY(IsValid(fogOfWar), "Invalid warfog", return);

  fogOfWar->SetWarFogType(m_warfogParams->warFogType);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void VisibilityMapClient::InitRenderResources()
{
  if (!m_created)
    return;

  m_disabled = RENDER_DISABLED || Render::GetIConfigManager()->GetSysInfo().IsNullRef;
  if ( Render::GetRenderer()->DeviceIsLost() || m_disabled )
    return;

  ClearTextures();

  // Set sampler
  Render::GetStatesManager()->SetSamplerState( WARFOGSAMPLERINDEX, Render::SamplerState::PRESET_CLAMP_BILINEAR() );
  Render::SmartRenderer::BindTexture( WARFOGSAMPLERINDEX, m_texBlended, true );

  // Set constants for future
  Render::ConstantProtectionBlock block(Render::CCONTEXT_GLOBALCONSTANT);
  Render::GetRenderer()->SetVertexShaderConstantsVector4( WARFOGMAPPING, m_warfogMapping);
  //Render::GetRenderer()->SetPixelShaderConstantsHDRColor( WARFOGCOLOR, m_warfogParams->color);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void VisibilityMapClient::Update(float timeDelta)
{
  NI_PROFILE_FUNCTION;

  //m_doBlur = false;

  { //Update blend ratio and counter
    const float ratio = (numUpdatesBetweenSteps > 0) ? indexUpdateCur / (float)numUpdatesBetweenSteps : 1.0f;
    m_ratio = ClampFast(ratio, 0.0f, 1.0f);
    ++indexUpdateCur;
  }

  NI_VERIFY(IsValid(world), "invalid world", return );
  
  const int step = world->GetStepNumber();

  if (currentworldStep != step)
  {
    OnStep();

    currentworldStep = step;
  }
  else if (world->GetAIWorld()->WasGameFinished())
  {
    FillTexture(m_texSource, FS_END);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float VisibilityMapClient::GetMiniMapAlphaScale()
{
  return m_warfogParams->warFogMiniMapAlphaScale;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void VisibilityMapClient::OnStep()
{
  struct Local
  {
    struct F: NonCopyable
    {
      void operator()(PF_Core::WorldObjectBase& baseUnit) const
      {
        // Apply if unit
        CDynamicCast<NWorld::PFBaseUnit> pUnit = &baseUnit;
        if (!IsValid(pUnit))
          return;

        if(PFClientBaseUnit* const pClient = pUnit->ClientObject())
        {
          pClient->UpdateVisibility();
        }
      }
    };

    static void ForceUpdateVisibility(NWorld::PFWorld* const world)
    {
      F updater;

      world->ForAllObjectsBeingStepped(updater);
    }
  };

  NI_PROFILE_FUNCTION;


#ifndef _SHIPPING
  if (g_visMapModeLast != g_visMapMode)
  {
    g_visMapModeLast = g_visMapMode;

    Local::ForceUpdateVisibility(world);
  }
#endif

  // проскипаем первый степ, чтобы не обнулилась исходная текстура по не заполненному варфогу (т.к. она нужна для миникарты)
  if (world->GetStepNumber() < 2) 
    return;

  if (m_disabled)
    return;

  NI_VERIFY(!!controller, "Invalid controller", return);

#ifndef _SHIPPING
  switch (g_visMapMode)
  {
  case EVisMapMode::Undefined:
    controller->SetMode(EVisMapMode::FromFaction(ClientVisibilityHelper::GetPlayerFaction()));
    break;
  case EVisMapMode::FactionN:
  case EVisMapMode::FactionA:
  case EVisMapMode::FactionB:
  case EVisMapMode::Everything:
  case EVisMapMode::Combined:
    controller->SetMode(static_cast<EVisMapMode::Type>(g_visMapMode));
    break;
  default:
    NI_ALWAYS_ASSERT("Invalid visibility map mode!");
  }
#else
  const EVisMapMode::Type mode = controller->GetMode();

  switch (mode)
  {
  case EVisMapMode::Undefined:
    controller->SetMode(EVisMapMode::FromFaction(ClientVisibilityHelper::GetPlayerFaction()));
    break;
  case EVisMapMode::FactionA:
  case EVisMapMode::FactionB:
    {
      const EVisMapMode::Type actual_mode = EVisMapMode::FromFaction(ClientVisibilityHelper::GetPlayerFaction());

      if (mode != actual_mode)
      {
        controller->SetMode(actual_mode);
      }
    }
    break;
  default:
    break;
  }
#endif

  controller->Update();

  FillTexture(m_texSource);

  m_doBlur = true;
  m_stepNumber++;

  // Number of updates between 2 steps
  numUpdatesBetweenSteps = indexUpdateCur;
  indexUpdateCur = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void VisibilityMapClient::ClearTextures()
{
  if ( Render::GetRenderer()->DeviceIsLost() || m_disabled )
    return;

  IDirect3DDevice9* const pDevice = Render::GetDevice();
  DXSurfaceRef pSurf = m_texBlended->GetSurface(0);
  pDevice->ColorFill(Get(pSurf), NULL, 0);
  pSurf = m_texStep[0]->GetSurface(0);
  pDevice->ColorFill(Get(pSurf), NULL, 0);
  pSurf = m_texStep[1]->GetSurface(0);
  pDevice->ColorFill(Get(pSurf), NULL, 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void VisibilityMapClient::FillTexture(Render::Texture2DRef const& pTexture, FillStage stage /*= FS_STEP*/)
{
  if ( (Render::GetRenderer()->DeviceIsLost() || m_disabled) && stage != FS_INIT )
    return;

  if ( RENDER_DISABLED )
    return;

  using NWorld::FogOfWar;

  NI_VERIFY(IsValidPtr(pTexture), "invalid source", return);
  NI_VERIFY(IsValid(world), "invalid world", return);
  NI_VERIFY(IsValid(fogOfWar), "invalid warfog", return);
  NI_VERIFY(!!controller, "Invalid controller!", return);

  const int width = fogOfWar->GetWidth();
  const int height = fogOfWar->GetHeight();

  ASSERT(static_cast<unsigned>(width) <= pTexture->GetWidth());
  ASSERT(static_cast<unsigned>(height) <= pTexture->GetHeight());

  Render::LockedRect rect = pTexture->LockRect(0, 0, width, 0, height, Render::LOCK_DEFAULT);
  NI_VERIFY(rect.data != NULL,"", return);

  const bool everything =
    (stage == FS_END) ||
    (controller->GetMode() == EVisMapMode::Everything);

  // заливаем все варфогом сразу после создания текстур, т.к. реальный варфог еще не готов (объекты не сразу открывают собой его)
  // заливка нужна, чтобы интерфейсу было что отображать уже на самом первом апдейте.
  if (stage == FS_INIT) 
  {
    const bool isDualLayer = (m_warfogParams->warFogType == NDb::WARFOGTYPE_DUALLAYER);

    for (int i = 0, start = (height - 1) * rect.pitch; i < height; ++i, start -= rect.pitch)
    {
      PDWORD const pData = PDWORD(rect.data + start);
      for (int j = 0; j < width; ++j)
        pData[j] = m_warfogParams->colors[isDualLayer].Dummy;
    }
  }
  else if (everything)
  {
    // TODO: представление меняет данные!
    if(stage == FS_END)
      fogOfWar->MakeAllVisible();

    for (BYTE *start = rect.data, *bound = rect.data + height * rect.pitch; start != bound; start += rect.pitch)
      memset(start, 0, width * sizeof(Render::Color));
  }
  else
  {
    const bool isDualLayer = (m_warfogParams->warFogType == NDb::WARFOGTYPE_DUALLAYER);

    const FogOfWar::VisMap& visMap = controller->GetVisMap();
    const FogOfWar::VisMapMask& visMapMask = controller->GetVisMapMask();

    // TODO: !
    const DWORD colors[4] = { 0, m_warfogParams->colors[isDualLayer].Dummy,
                              0, m_warfogParams->colors[!isDualLayer].Dummy };

    NI_STATIC_ASSERT(int(true)  == 1, wrong_bool_representation);
    NI_STATIC_ASSERT(int(false) == 0, wrong_bool_representation);

    for (int i = 0, start = (height - 1) * rect.pitch; i < height; ++i, start -= rect.pitch)
    {
      PDWORD const pData = PDWORD(rect.data + start);

      FogOfWar::VisMap::SubArrayConst visMapRow = visMap[i];
      FogOfWar::VisMapMask::SubArrayConst visMapMaskRow = visMapMask[i];

      for (int j = 0; j < width; ++j)
        pData[j] = colors[ (int(visMapMaskRow[j]) << 1) | int(visMapRow[j] == 0) ];
    }
  }

  pTexture->UnlockRect(0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void VisibilityMapClient::BlendTextures()
{
  using namespace Render;

  Renderer &renderer = *GetRenderer();

  // set default image processing states // smirnov [2009/3/3]: refactor
  RenderStatesManager &rsManager = *GetStatesManager();
  rsManager.SetState( RenderState::NoBlendNoTest() );
  rsManager.SetStateDirect(D3DRS_ZENABLE, 0);
  rsManager.SetStateDirect(D3DRS_SEPARATEALPHABLENDENABLE, 0);

  // smirnov [2009/1/28]: FIX: Direct3D9: (WARN) :Can not render to a render target that is also used as a texture. 
  // A render target was detected as bound, but couldn't detect if texture was actually used in rendering.
  GetDevice()->SetTexture(WARFOGSAMPLERINDEX, NULL);

  // set shader parameters
  rsManager.SetSampler(1, SamplerState::PRESET_CLAMP_POINT(), m_texStep[m_texIndex]);
  renderer.SetPixelShaderConstantsFloat(PSHADER_LOCALCONST0, m_ratio);

  // execute shader
  SmartRenderer::BindRenderTarget(m_texBlended);
  GetImmRenderer()->RenderScreenQuad( ImmRenderer::Params("WarfogBlend", m_texStep[!m_texIndex], &SamplerState::PRESET_CLAMP_POINT()) );
  SmartRenderer::BindRenderTargetDefault();

  // smirnov [2009/1/28]: Restore texture binding
  GetDevice()->SetTexture(WARFOGSAMPLERINDEX, m_texBlended->GetDXTexture());
}

void VisibilityMapClient::OnRender()
{
  if(!m_initialized) {
    InitRenderResources();
    m_initialized = true;
  }
  BlendTextures();

  if(m_doBlur) {
    m_texIndex = !m_texIndex;
    blurEffect.Apply(m_texSource, m_texStep[m_texIndex]);
    m_doBlur = false;
  }

  //// Update warfog color
  //Render::ConstantProtectionBlock block(Render::CCONTEXT_GLOBALCONSTANT);
  //Render::GetRenderer()->SetPixelShaderConstantsHDRColor( WARFOGCOLOR, m_warfogParams->color );
}

//////////////////////////////////////////////////////////////////////////
void VisibilityMapClient::SetSpectatorMode(const bool value)
{
  if (value)
  {
    ::Reset(controller, new Detail::SpectatorVisMapClientController());

    controller->SetCombine(NDb::FACTION_FREEZE, true);
    controller->SetCombine(NDb::FACTION_BURN, true);
  }
  else
  {
#ifndef _SHIPPING
    ::Reset(controller, new Detail::DeveloperVisMapClientController());
#else
    ::Reset(controller, new Detail::RegularVisMapClientController());
#endif
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace Detail
{

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  namespace
  {
    static const NWorld::FogOfWar::VisMap l_dummyVisMap;
    static const NWorld::FogOfWar::VisMapMask l_dummyVisMapMask;

    static inline const NWorld::FogOfWar::VisMap& GetVisMapRef(const NWorld::FogOfWar::VisMap* const p)
    {
      if (p)
        return *p;
      return l_dummyVisMap;
    }

    static inline const NWorld::FogOfWar::VisMap& GetVisMapRef(const NWorld::FogOfWar::VisMap& r)
    {
      return r;
    }

    static inline const NWorld::FogOfWar::VisMapMask& GetVisMapMaskRef(const NWorld::FogOfWar::VisMapMask* const p)
    {
      if (p)
        return *p;
      return l_dummyVisMapMask;
    }

    static inline const NWorld::FogOfWar::VisMapMask& GetVisMapMaskRef(const NWorld::FogOfWar::VisMapMask& r)
    {
      return r;
    }
  }

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  bool VisMapClientController::IsPointVisible(const CVec2& pos) const
  {
    // TODO: return true ?
    if (!EVisMapMode::IsValid(mode))
      return false;

    if (!IsValid(fogOfWar))
      return false;
    if (!IsValid(tileMap))
      return false;

    const SVector tile(tileMap->GetTile(pos));

    if (tile.x < 0)
      return false;
    if (tile.y < 0)
      return false;

    return fogOfWar->IsTileVisible(tile, EVisMapMode::GetFogOfWarTeam(mode));
  }

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  RegularVisMapClientController::RegularVisMapClientController()
  {

  }

  RegularVisMapClientController::~RegularVisMapClientController()
  {

  }

  const NWorld::FogOfWar::VisMap& RegularVisMapClientController::GetVisMap() const
  {
    if (!IsValid(fogOfWar))
      return GetVisMapRef(NULL);

    switch (mode)
    {
    case EVisMapMode::FactionA:
    case EVisMapMode::FactionB:
      return GetVisMapRef(fogOfWar->GetVisMap(EVisMapMode::GetFogOfWarTeam(mode)));
    default:
      return GetVisMapRef(NULL);
    }
  }

  const NWorld::FogOfWar::VisMapMask& RegularVisMapClientController::GetVisMapMask() const
  {
    if (!IsValid(fogOfWar))
      return GetVisMapMaskRef(NULL);

    switch (mode)
    {
    case EVisMapMode::FactionA:
    case EVisMapMode::FactionB:
      return GetVisMapMaskRef(fogOfWar->GetVisMapMask(EVisMapMode::GetFogOfWarTeam(mode)));
    default:
      return GetVisMapMaskRef(NULL);
    }
  }

  void RegularVisMapClientController::SetMode(const EVisMapMode::Type value)
  {
    switch (value)
    {
    case EVisMapMode::FactionA:
    case EVisMapMode::FactionB:
      VisMapClientController::SetMode(value);
      break;
    default:
      break;
    }
  }

  bool RegularVisMapClientController::IsPointVisible(const CVec2& pos) const
  {
    switch (mode)
    {
    case EVisMapMode::FactionA:
    case EVisMapMode::FactionB:
      return VisMapClientController::IsPointVisible(pos);
    default:
      return false;
    }
  }

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  DeveloperVisMapClientController::DeveloperVisMapClientController()
  {

  }

  DeveloperVisMapClientController::~DeveloperVisMapClientController()
  {

  }

  const NWorld::FogOfWar::VisMap& DeveloperVisMapClientController::GetVisMap() const
  {
    if (!IsValid(fogOfWar))
      return GetVisMapRef(NULL);

    return GetVisMapRef(fogOfWar->GetVisMap(EVisMapMode::GetFogOfWarTeam(mode)));
  }

  const NWorld::FogOfWar::VisMapMask& DeveloperVisMapClientController::GetVisMapMask() const
  {
    if (!IsValid(fogOfWar))
      return GetVisMapMaskRef(NULL);

    return GetVisMapMaskRef(fogOfWar->GetVisMapMask(EVisMapMode::GetFogOfWarTeam(mode)));
  }

  void DeveloperVisMapClientController::SetMode(const EVisMapMode::Type value)
  {
    switch (value)
    {
    case EVisMapMode::FactionN:
    case EVisMapMode::FactionA:
    case EVisMapMode::FactionB:
    case EVisMapMode::Everything:
      VisMapClientController::SetMode(value);
      break;
    default:
      break;
    }
  }

  bool DeveloperVisMapClientController::IsPointVisible(const CVec2& pos) const
  {
    if (mode == EVisMapMode::Everything)
      return true;

    return VisMapClientController::IsPointVisible(pos);
  }

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  const NDb::EFaction l_factionsToCombine[] =
  {
    NDb::FACTION_FREEZE,
    NDb::FACTION_BURN,
  };

  template <typename T, unsigned N>
  static inline unsigned GetArrayLength(T (&arr)[N])
  {
    return N;
  }

  static inline bool CanCombineFaction(const NDb::EFaction faction)
  {
    for (unsigned i = 0U, count = GetArrayLength(l_factionsToCombine); i < count; ++i)
    {
      if (faction == l_factionsToCombine[i])
        return true;
    }

    return false;
  }

  template <unsigned N>
  struct Combiner
  {
    template <typename T>
    struct ValueCombiner;

    template <typename T, unsigned N>
    struct Impl;

    template <>
    struct Impl<byte, 2U>
    {
      static inline void Combine(const int x, const int y, const vector< const CArray2D<byte>* >& src, CArray2D<byte>& dst)
      {
        dst.Set(x, y,
          src[0]->GetUnsafe(x, y) |
          src[1]->GetUnsafe(x, y));
      }
    };

    template <>
    struct Impl<byte, 3U>
    {
      static inline void Combine(const int x, const int y, const vector< const CArray2D<byte>* >& src, CArray2D<byte>& dst)
      {
        dst.Set(x, y,
          src[0]->GetUnsafe(x, y) |
          src[1]->GetUnsafe(x, y) |
          src[2]->GetUnsafe(x, y));
      }
    };

    template <>
    struct Impl<bool, 2U>
    {
      static inline void Combine(const int x, const int y, const vector< const CArray2D<bool>* >& src, CArray2D<bool>& dst)
      {
        dst.Set(x, y,
          src[0]->GetUnsafe(x, y) ||
          src[1]->GetUnsafe(x, y));
      }
    };

    template <>
    struct Impl<bool, 3U>
    {
      static inline void Combine(const int x, const int y, const vector< const CArray2D<bool>* >& src, CArray2D<bool>& dst)
      {
        dst.Set(x, y,
          src[0]->GetUnsafe(x, y) ||
          src[1]->GetUnsafe(x, y) ||
          src[2]->GetUnsafe(x, y));
      }
    };

    template <typename T>
    inline void operator()(const vector< const CArray2D<T>* >& src, CArray2D<T>& dst) const
    {
      // TODO: verify sources?

      for (int y = 0, h = dst.GetSizeY(); y < h; ++y)
      {
        for (int x = 0, w = dst.GetSizeX(); x < w; ++x)
        {
          Impl<T, N>::Combine(x, y, src, dst);
        }
      }
    }

    template <typename T, typename U>
    inline void operator()(const vector< const CArray2D<T>* >& src0, CArray2D<T>& dst0, const vector< const CArray2D<U>* >& src1, CArray2D<U>& dst1) const
    {
      // TODO: verify sources?

      NI_VERIFY(dst0.GetSizeX() == dst1.GetSizeX(), "Trying to combine arrays of different size!", return);
      NI_VERIFY(dst0.GetSizeY() == dst1.GetSizeY(), "Trying to combine arrays of different size!", return);

      for (int y = 0, h = dst0.GetSizeY(); y < h; ++y)
      {
        for (int x = 0, w = dst0.GetSizeX(); x < w; ++x)
        {
          Impl<T, N>::Combine(x, y, src0, dst0);
          Impl<U, N>::Combine(x, y, src1, dst1);
        }
      }
    }
  };

  struct ScopedModeSwitch : public NonCopyable
  {
    explicit ScopedModeSwitch(SpectatorVisMapClientController& _owner, const EVisMapMode::Type _mode)
      : owner(_owner)
      , restoreMode(_owner.GetMode())
    {
      owner.SetMode(_mode);
    }
    ~ScopedModeSwitch()
    {
      owner.SetMode(restoreMode);
    }
  private:
    ScopedModeSwitch();

    SpectatorVisMapClientController& owner;

    const EVisMapMode::Type restoreMode;
  };

  SpectatorVisMapClientController::SpectatorVisMapClientController()
    : combinedVisMap()
    , combinedVisMapMask()
    , combineFactionsMask(0U)
    , combineRevision(0U)
    , combineFallbackMode(EVisMapMode::Undefined)
  {

  }

  SpectatorVisMapClientController::~SpectatorVisMapClientController()
  {

  }

  const NWorld::FogOfWar::VisMap& SpectatorVisMapClientController::GetVisMap() const
  {
    if (!IsValid(fogOfWar))
      return GetVisMapRef(NULL);

    switch (mode)
    {
    case EVisMapMode::FactionA:
    case EVisMapMode::FactionB:
      return GetVisMapRef(fogOfWar->GetVisMap(EVisMapMode::GetFogOfWarTeam(mode)));
    case EVisMapMode::Combined:
      if (combineFallbackMode == EVisMapMode::Undefined)
        return GetVisMapRef(combinedVisMap);
      else
        return GetVisMapRef(fogOfWar->GetVisMap(EVisMapMode::GetFogOfWarTeam(combineFallbackMode)));
    default:
      return GetVisMapRef(NULL);
    }
  }

  const NWorld::FogOfWar::VisMapMask& SpectatorVisMapClientController::GetVisMapMask() const
  {
    if (!IsValid(fogOfWar))
      return GetVisMapMaskRef(NULL);

    switch (mode)
    {
    case EVisMapMode::FactionA:
    case EVisMapMode::FactionB:
      return GetVisMapMaskRef(fogOfWar->GetVisMapMask(EVisMapMode::GetFogOfWarTeam(mode)));
    case EVisMapMode::Combined:
      if (combineFallbackMode == EVisMapMode::Undefined)
        return GetVisMapMaskRef(combinedVisMapMask);
      else
        return GetVisMapMaskRef(fogOfWar->GetVisMapMask(EVisMapMode::GetFogOfWarTeam(combineFallbackMode)));
    default:
      return GetVisMapMaskRef(NULL);
    }
  }

  bool SpectatorVisMapClientController::GetCombine(const NDb::EFaction faction) const
  {
#if 0
    if (!CanCombineFaction(faction))
      return false;
#endif

    const unsigned factionMask = (1 << static_cast<unsigned>(faction));

    if (combineFactionsMask & factionMask)
      return true;

    return false;
  }

  void SpectatorVisMapClientController::SetMode(const EVisMapMode::Type value)
  {
    switch (value)
    {
    case EVisMapMode::FactionA:
    case EVisMapMode::FactionB:
    case EVisMapMode::Combined:
      VisMapClientController::SetMode(value);
      break;
    default:
      break;
    }
  }

  void SpectatorVisMapClientController::SetCombine(const NDb::EFaction faction, const bool combine)
  {
    if (!CanCombineFaction(faction))
      return;

    const unsigned factionMask = (1 << static_cast<unsigned>(faction));

    const unsigned newCombineFactionsMask = combine
      ? (combineFactionsMask |  factionMask)
      : (combineFactionsMask & ~factionMask);

    if (newCombineFactionsMask == combineFactionsMask)
      return;

    combineFactionsMask = newCombineFactionsMask;
    combineRevision = 0U;
  }

  void SpectatorVisMapClientController::Update()
  {
    if (mode == EVisMapMode::Combined)
    {
      Combine();
    }
  }

  bool SpectatorVisMapClientController::IsPointVisible(const CVec2& pos) const
  {
    switch (mode)
    {
    case EVisMapMode::FactionA:
    case EVisMapMode::FactionB:
      return VisMapClientController::IsPointVisible(pos);
    case EVisMapMode::Combined:
      if (combineFallbackMode == EVisMapMode::Undefined)
      {
        return IsPointVisibleOnCombinedMapImpl(pos);
      }
      else
      {
        const ScopedModeSwitch guard(*const_cast<SpectatorVisMapClientController*>(this), combineFallbackMode);

        return VisMapClientController::IsPointVisible(pos);
      }
    default:
      return false;
    }
  }

  void SpectatorVisMapClientController::Combine()
  {
    NI_PROFILE_FUNCTION;

    if (!IsValid(fogOfWar))
      return;

    const int width = fogOfWar->GetWidth();
    const int height = fogOfWar->GetHeight();

    const int myWidth = combinedVisMap.GetSizeX();
    const int myHeight = combinedVisMap.GetSizeY();

    if (
      myWidth != width ||
      myHeight != height)
    {
      combinedVisMap.SetSizes(width, height);
      combinedVisMapMask.SetSizes(width, height);

      combinedVisMap.FillZero();
      combinedVisMapMask.FillZero();

      combineRevision = 0U;
    }

    {
      const unsigned revision = fogOfWar->GetRevision();

      if (combineRevision == revision)
        return;

      combineRevision = revision;
    }

    unsigned factionsToCombine = 0U;

    {
      for (unsigned i = 0U, count = GetArrayLength(l_factionsToCombine); i < count; ++i)
      {
        const NDb::EFaction faction = l_factionsToCombine[i];
        const unsigned factionMask = (1 << static_cast<unsigned>(faction));

        if (combineFactionsMask & factionMask)
        {
          ++factionsToCombine;
        }
      }
    }

    if (factionsToCombine < 2U)
    {
      for (unsigned i = 0U, count = GetArrayLength(l_factionsToCombine); i < count; ++i)
      {
        const NDb::EFaction faction = l_factionsToCombine[i];
        const unsigned factionMask = (1 << static_cast<unsigned>(faction));

        if (combineFactionsMask & factionMask)
        {
          combineFallbackMode = EVisMapMode::FromFaction(faction);
          return;
        }
      }

      NI_ALWAYS_ASSERT("Invalid state!")
    }
    else
    {
      combineFallbackMode = EVisMapMode::Undefined;
    }

    typedef vector<const NWorld::FogOfWar::VisMap*> TVisMaps;
    typedef vector<const NWorld::FogOfWar::VisMapMask*> TVisMapMasks;

    TVisMaps visMaps;
    TVisMapMasks visMapMasks;

    visMaps.reserve(factionsToCombine);
    visMapMasks.reserve(factionsToCombine);

    {
      for (unsigned i = 0U, count = GetArrayLength(l_factionsToCombine); i < count; ++i)
      {
        const NDb::EFaction faction = l_factionsToCombine[i];
        const unsigned factionMask = (1 << static_cast<unsigned>(faction));

        if (combineFactionsMask & factionMask)
        {
          const uint fogOfWarTeam = static_cast<uint>(faction);

          visMaps.push_back(fogOfWar->GetVisMap(fogOfWarTeam));
          visMapMasks.push_back(fogOfWar->GetVisMapMask(fogOfWarTeam));
        }
      }
    }

    switch (factionsToCombine)
    {
    case 2U:
      Combiner<2U>()(visMaps, combinedVisMap, visMapMasks, combinedVisMapMask);
      break;
    case 3U:
      Combiner<3U>()(visMaps, combinedVisMap, visMapMasks, combinedVisMapMask);
      break;
    default:
      NI_ALWAYS_ASSERT("Cannot combine!");
    }
  }

  bool SpectatorVisMapClientController::IsPointVisibleOnCombinedMapImpl(const CVec2& pos) const
  {
    if (!IsValid(fogOfWar))
      return false;
    if (!IsValid(tileMap))
      return false;

    SVector tile(tileMap->GetTile(pos));

    if (tile.x < 0)
      return false;
    if (tile.y < 0)
      return false;

    const int visTileSize = fogOfWar->GetVisTileSize();

    tile.x /= visTileSize;
    tile.y /= visTileSize;

    if (tile.x >= combinedVisMap.GetSizeX())
      return false;
    if (tile.y >= combinedVisMap.GetSizeY())
      return false;

    return combinedVisMap[tile.x][tile.y];
  }

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

} // namespace NGameX
