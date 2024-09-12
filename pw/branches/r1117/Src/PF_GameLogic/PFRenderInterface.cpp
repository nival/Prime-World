#include "stdafx.h"

#include "System/2Darray.h"
#include "System/meminfo.h"
#include "System/fixedstring.h"
#include "System/InlineProfiler.h"

#include "Scene/Scene.h"
#include "Terrain/Terrain.h"
#include <Terrain\TerrainTextureCache.h>

#include "Render/ImmediateRenderer.h"
#include "Render/renderresourcemanager.h"
#include "Render/debugrenderer.h"
#include "Render/WaterManager.h"
#include "Render/ConvexVolume.h"
#include "Render/ShadowManager.h"
#include "Render/uirenderer.h"

#include "Render/VendorFOURCC.h"

#include "Render/GlobalMasks.h"

#include "Render/texture.h"
#include "Render/RenderSurface.h"
#include "Render/InstancedMeshResource.h"
#include "Render/FrustumCuller.h"

#include "PF_Core/RecolorableTexture.h"
#include "PF_Core/AnimatedTexture.h"

#include "PFClientVisibilityMap.h"
#include "PFWorldNatureMap.h"
#include "PFClientNatureMap.h"
#include "Scene/AmbienceMap.h"

#include "AdventureScreen.h"

#include "PFBaseUnit.h"
#include "PFClientBaseUnit.h"

#include "PFRenderUtils.h"
#include <Render/Stretcher.h>
#include "PFRenderWater.h"
#include "PFRenderInterface.h"
#include "Minimap.h"

//#include "Reprojector.h"
#include "Render/IConfigManager.h"
#include "Render/renderflagsconverter.h"

#include "Render/AOERenderer.h"
#include "System/MainFrame.h"
#include "libdb/DbResourceCache.h"


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static NDebug::DebugVar<unsigned int> render_TotalTriangleCount( "TrisTotal", "PerfCnt" );
static NDebug::DebugVar<unsigned int> render_SceneTriangleCount( "TrisScene", "PerfCnt" );
static NDebug::DebugVar<unsigned int> render_3DTriangleCount( "Tris3D", "PerfCnt" );
static NDebug::DebugVar<unsigned int> render_TotalDIPCount( "DIPsTotal", "PerfCnt" );
static NDebug::DebugVar<unsigned int> render_SceneDIPCount( "DIPsScene", "PerfCnt" );
static NDebug::DebugVar<unsigned int> render_3DDIPCount( "DIPs3D", "PerfCnt" );

static NDebug::DebugVar<unsigned int> render_MatSwitchCount( "MatSwitch", "PerfCnt" );

static NDebug::DebugVar<unsigned int> render_Frame( "FrameId", "Render" );
static NDebug::PerformanceDebugVar render_Gather( "Gather", "Render", 10, 10, true, 80 );
static NDebug::PerformanceDebugVar render_Draw( "Draw", "Render", 10, 10, true, 80 );
static NDebug::PerformanceDebugVar render_DrawTerrain( "Draw > Terrain", "Render", 10, 10, true );
static NDebug::PerformanceDebugVar render_Water( "Water", "Render", 10, 10, true );
static NDebug::PerformanceDebugVar render_UI( "UI", "Render", 10, 10, true );
static NDebug::PerformanceDebugVar render_TheRest( "TheRest", "Render", 10, 10, true );

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static bool s_enableDXHints = false;
REGISTER_VAR( "DXHints", s_enableDXHints, STORAGE_NONE );

DEV_VAR_STATIC bool s_forceSky = true;
REGISTER_DEV_VAR( "sky_force", s_forceSky, STORAGE_NONE );

static float s_waterReflCoeff = 0.5f;
REGISTER_VAR( "waterReflCoeff", s_waterReflCoeff, STORAGE_USER );

static float s_resScale = 1.0f;
REGISTER_VAR( "gfx_scale3D", s_resScale, STORAGE_USER );

static bool s_scaleMode = true;
REGISTER_DEV_VAR( "gfx_scaleMode", s_scaleMode, STORAGE_NONE );

static bool s_forceAdditionalRTs = false;
REGISTER_DEV_VAR( "gfx_scaleART", s_forceAdditionalRTs, STORAGE_NONE );

static bool s_drawHeightfog = true;
REGISTER_DEV_VAR( "draw_heightfog", s_drawHeightfog, STORAGE_NONE );

DEV_VAR_STATIC bool s_fogAfterTransp = false;
REGISTER_DEV_VAR( "draw_fog_after_transp", s_fogAfterTransp, STORAGE_NONE );

static bool s_rnd_PFX_new = true;

static bool EnablePFXInstancing( const char *name, const vector<wstring>& params )
{
  if( !params.empty() ) {
    s_rnd_PFX_new = (params[0] != L"0") && !Compatibility::IsRunnedUnderWine();
    Render::ParticleFXMaterial::SetInstancingFlag(s_rnd_PFX_new);
    NGlobal::RunCommand(L"resetSortIDs");
  }

  DebugTrace("Particle Instancing %s (provide bool param to change)", s_rnd_PFX_new ? "enabled" : "disabled");
  return true;
}
REGISTER_CMD( rnd_PFX_new, EnablePFXInstancing );


//static Reprojector s_Reprojector;
//
//static bool s_EnableRC = false;
//REGISTER_VAR( "reprojection", s_EnableRC, STORAGE_NONE );

static bool s_readableDepth = false;
static bool s_stencilSupported = true;
static bool s_useRESZ = false;
//static const bool s_useRESZ = false;
static bool s_EnableRESZ = false;
REGISTER_VAR("enableRESZ", s_EnableRESZ, STORAGE_USER);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Developing variables
static bool		bSetFFTT = false;
static int		showWaterTexture = 0;
static bool   showVisibilityMapTexture = false;
static bool		showAABBs = false;
static int		showShadowTexture = 0;
static bool   showDepthTexture = 0;
static bool   showBackTexture = 0;
static bool		showShadows = 1;
static bool		freezeShadows = false;
static float	miplodbias = 0.f;
static bool		g_bDrawOpaque   = true;
static bool		g_bDrawTrasp    = true;
static bool		g_bDrawDistort  = true;
static bool   g_renderLogActive = false;

static bool		wireframe = false;

static bool usecullinghack = false;
DEV_VAR_STATIC int  showNatureAttackTexture = 0;
DEV_VAR_STATIC bool showNatureCoeff = false;
DEV_VAR_STATIC bool showAmbienceTexture = false;
DEV_VAR_STATIC bool showTerrainTexCache = false;

static bool g_PostFXEnabled = false;
static bool  g_SharpEnabled = true;
static bool g_PostFXForced = false;
static bool g_enableDecalUnion = true;

static struct SRegister_InterfaceFactorySetter
{
  static Render::Interface * CreateRenderInterface(HWND hwnd) { return new Render::DeviceLostWrapper<PF_Render::Interface>(hwnd); }
  SRegister_InterfaceFactorySetter() { Render::Interface::RegisterFactory( &CreateRenderInterface ); }
} interfaceFactorySetter;

using namespace Render;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace PF_Render
{

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
class StatisticsMeasurer
{
  unsigned int currentTrisCount;
  unsigned int currentDIPsCount;
public:
  StatisticsMeasurer(bool startMeasuring = false) 
  {
    if (startMeasuring)
      StartMeasuring();
  }
  void StartMeasuring()
  {
    SmartRenderer::GetTriangleAndDipCount(currentTrisCount, currentDIPsCount);
  }
  void GetDeltas(NDebug::DebugVar<unsigned int> &triCnt, NDebug::DebugVar<unsigned int> &dipCnt)
  {
    unsigned int nTri, nDIP;
    SmartRenderer::GetTriangleAndDipCount(nTri, nDIP);
    triCnt.SetValue(nTri - currentTrisCount);
    dipCnt.SetValue(nDIP - currentDIPsCount);
  }
  void AppendDeltas(NDebug::DebugVar<unsigned int> &triCnt, NDebug::DebugVar<unsigned int> &dipCnt)
  {
    unsigned int nTri, nDIP;
    SmartRenderer::GetTriangleAndDipCount(nTri, nDIP);
    triCnt.AddValue(nTri - currentTrisCount);
    dipCnt.AddValue(nDIP - currentDIPsCount);
  }
  static void GetValues(NDebug::DebugVar<unsigned int> &triCnt, NDebug::DebugVar<unsigned int> &dipCnt)
  {
    unsigned int nTri, nDIP;
    SmartRenderer::GetTriangleAndDipCount(nTri, nDIP);
    triCnt.SetValue(nTri);
    dipCnt.SetValue(nDIP);
  }
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Internal for this module
class BatchLogger : public Render::IBatchQueueLogger
{
  static const char *ConvertClassName(const char *name)
  {
    const char *pStr = NStr::FindLastChar(name, ':');
    if (!pStr)
    {
      pStr = NStr::FindLastChar(name, ' ');
      if (!pStr)
        pStr = name;
      else
        pStr++;
    }
    else
      pStr++;
    return pStr;
  }

  virtual void operator()(const Batch &batch)
  {
    const NDb::DBID *pDBID = batch.pOwner->GetDBID();
    FixedString<256> ownerID(pDBID ? GetFormattedDbId(*pDBID).c_str() : "(unknown)");
    
    // Class names
    const char *renderComponentName = /*ConvertClassName*/(typeid(*batch.pOwner).name());
    const char *materialName        = ConvertClassName(typeid(*batch.pMaterial).name());

    int numInstances = -1;
    const Render::InstancedPrimitive *pIP = dynamic_cast<const Render::InstancedPrimitive*>(batch.pPrimitive);
    if (pIP)
      numInstances = pIP->GetNumInstances();

    DebugTrace("%s; %s; %s; %d; %d; %d; %f", 
               renderComponentName, ownerID.c_str(), materialName, 
               batch.pMaterial->GetSortId(), numInstances, batch.elementNumber, batch.sortValue);
  }
} s_batchLogger;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using Render::RenderSequenceMarker;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Internal for this module
template <bool withDebug>
struct ProcessBatchesFunc : public IObjectFunctor, private NonCopyable
{
public:
  ProcessBatchesFunc(BatchQueue &_batchQueue, const SceneConstants &_sceneConsts, IDebugRender* _debugRender, int _groupFlagsFilter = GROUPFLAGS_ALL)
    : batchQueue(_batchQueue)
    , sceneConsts(_sceneConsts)
    , groupFlagsFilter(_groupFlagsFilter)
    , debugRender(_debugRender)
  {
    fullaabb.Init2Empty();
  }

  virtual void operator()(RenderableSceneObj &obj)
  {
    const AABB &aabb = obj.GetWorldAABB();

    if ( withDebug )
    {
      if ( showAABBs )
        debugRender->DrawAABB( aabb, Color(0xFF, 0x0, 0x0), true );
 
      obj.DebugDraw( debugRender );
    }

    fullaabb.Grow( aabb );

    obj.Render( batchQueue, sceneConsts, groupFlagsFilter );
  }

  const AABB& GetAABB() { return fullaabb; }

protected:
  BatchQueue           &batchQueue;
  const SceneConstants &sceneConsts;
  AABB                  fullaabb;
  int                   groupFlagsFilter;
  IDebugRender*         debugRender;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct ProcessBatchesFuncBound : public ProcessBatchesFunc<false>
{
public:
  ProcessBatchesFuncBound(BatchQueue &_batchQueue, const SceneConstants &_sceneConsts, AABB const& _viewBound, int _groupFlagsFilter = GROUPFLAGS_ALL)
    : ProcessBatchesFunc(_batchQueue, _sceneConsts, 0, _groupFlagsFilter), viewBound(_viewBound)
  {
    viewMatrix.Set(sceneConsts.view);
  }

  virtual void operator()(RenderableSceneObj &obj)
  {
    const AABB &objBoxWS = obj.GetWorldAABB();
    fullaabb.Grow(objBoxWS);

    AABB objBoxVS;
    objBoxVS.Transform(viewMatrix, objBoxWS);
    if (viewBound.IsIntersectedBy(objBoxVS))
      obj.Render(batchQueue, sceneConsts, groupFlagsFilter);
  }

protected:
  Matrix43 viewMatrix;
  AABB const& viewBound;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <bool withDebug>
struct ProcessBatchesFuncWithGather : public ProcessBatchesFunc<withDebug>
{
public:
  ProcessBatchesFuncWithGather(BatchQueue &_batchQueue, const SceneConstants &_sceneConsts, vector<RenderableSceneObj*> &_renderableObjects, IDebugRender* _debugRender)
    : ProcessBatchesFunc(_batchQueue, _sceneConsts, _debugRender), renderableObjects(_renderableObjects)
  {
    renderableObjects.clear();
  }

  virtual void operator()(RenderableSceneObj &obj)
  {
    ProcessBatchesFunc::operator()(obj);
    renderableObjects.push_back(&obj);
  }

protected:
  vector<RenderableSceneObj*> &renderableObjects;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void RenderSky( const BatchQueue &queue )
{
  RenderSequenceMarker(NDb::MATERIALPRIORITY_SKY);
  RenderStatesManager &rsManager = *GetStatesManager();
  rsManager.SetStateDirect(D3DRS_ZWRITEENABLE, FALSE);
  queue.Render(NDb::MATERIALPRIORITY_SKY);
  rsManager.SetStateDirect(D3DRS_ZWRITEENABLE, TRUE);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static StretcherTwoPass stretcher(&Lanczos2);


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Interface::Interface(HWND hwnd) : 
  Render::Interface(hwnd),
  DeviceLostHandler(HANDLERPRIORITY_LOW),
  mainBatchQueue(Render::BatchQueue::INDEX_MAIN, batchQueueSorter),
  tempBatchQueue(Render::BatchQueue::INDEX_SECONDARY, batchQueueSorter),
  shadowBatchQueue(Render::BatchQueue::INDEX_SECONDARY, batchQueueSorter),
  pWaterReflectedFrustum(new ConvexVolume),
  decalRTCreated(false),
  silhouetteThickness(0.0f),
  colorSaturation(1.0f),
  customSaturationColor(1.f,1.f,1.f,1.f),
  useSaturationColor(false),
  width3D(0), height3D(0)
{
  // mark renderArea as invalid
  renderArea.left = renderArea.top = 0;
  renderArea.bottom = renderArea.right = -1;
}

Interface::~Interface() {}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Interface::Init()
{
  // Setup sorting properties of queues
  mainBatchQueue.SetSorting( NDb::MATERIALPRIORITY_TRANSPARENT, true );
  mainBatchQueue.SetSorting( NDb::MATERIALPRIORITY_TRANSPARENTSPECIAL, true );
  mainBatchQueue.SetSorting( NDb::MATERIALPRIORITY_DISTORTION, true );
  mainBatchQueue.SetSorting( NDb::MATERIALPRIORITY_TERRAINDOMINATIONDECALS, true );
  mainBatchQueue.SetSorting( NDb::MATERIALPRIORITY_TERRAINDECALS, true );
  mainBatchQueue.SetSorting( NDb::MATERIALPRIORITY_ROADS, true );
  // Reserve reasonable amount of objects
  gatheredRenderableObjects.reserve(1024);

  Reset(pSilhouetteMaterialStatic, static_cast<Render::BaseMaterial*>(Render::CreateRenderMaterial( NDb::SilhouetteMaterial::typeId )));
  pSilhouetteMaterialStatic->SetSkeletalMeshPin(NDb::BOOLEANPIN_NONE);
  pSilhouetteMaterialStatic->SetMaterialFlags(NDb::MATERIALFLAGS_NONE);
  Reset(pSilhouetteMaterialSkeletal, static_cast<Render::BaseMaterial*>(Render::CreateRenderMaterial( NDb::SilhouetteMaterial::typeId )));
  pSilhouetteMaterialSkeletal->SetSkeletalMeshPin(NDb::BOOLEANPIN_PRESENT);
  pSilhouetteMaterialSkeletal->SetMaterialFlags(NDb::MATERIALFLAGS_NONE);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Interface::CreateDepthTextures(UINT _width, UINT _height, UINT _copy_width, UINT _copy_height)
{
  depthCopyShaderName = 0;
  s_stencilSupported = true;

  GetDevice()->EvictManagedResources();

  if( s_readableDepth )
  {
    const IConfigManager* const configManager = GetIConfigManager();
    s_useRESZ = s_EnableRESZ && !configManager->HasINTZ() &&
                configManager->CheckFeatureSupportExact(IConfigManager::hasRESZ|IConfigManager::hasDF24);
    ERenderFormat format = s_useRESZ ? FORMAT_D24S8 : configManager->GetDepthFormatPreffered();
    s_stencilSupported = configManager->StencilSupported(format);
    D3DSURFACE_DESC desc = { Render::ConvertRenderFormat(format), D3DRTYPE_SURFACE, D3DUSAGE_DEPTHSTENCIL,
                             D3DPOOL_DEFAULT, D3DMULTISAMPLE_NONE, 0, _width, _height };
    pMainDepth = ::Create<Texture2D>(desc, HANDLERPRIORITY_HIGH);

    depthCopyShaderName = (FORMAT_RAWZ == format) ? "DecodeRAWZ" : "DecodeZ";
  }
  
  pMainRT1 = Render::CreateRenderTexture2D(_copy_width, _copy_height, FORMAT_R32F);
  pMainRT1Copy = s_stencilSupported ? Texture2DRef() : Render::CreateRenderTexture2D(_copy_width, _copy_height, FORMAT_R32F);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline DXSurfaceRef Interface::GetDepthSurface()
{
  return s_readableDepth && !s_useRESZ ? pMainDepth->GetSurface(0) : Render::GetRenderer()->GetDepthStencilSurface();  
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static inline DWORD CorrectResolution(DWORD _resolution)
{
  static const DWORD RESOLUTION_STEP = 1 << 2;
  static const DWORD RESOLUTION_MASK = ~(RESOLUTION_STEP - 1);

  if(s_resScale < 0.25f)
    s_resScale = 0.25f;

  if(s_resScale > 1.0f)
    s_resScale = 1.0f;

  DWORD newRes = (DWORD(s_resScale * _resolution) + RESOLUTION_STEP / 2) & RESOLUTION_MASK;
  return min(newRes, _resolution);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Interface::Start( RenderMode& mode )
{
  PushDXPoolGuard dxPool("Renderer");

  mode.width3D  = width3D  = CorrectResolution(mode.width);
  mode.height3D = height3D = CorrectResolution(mode.height);

  if (!Render::Interface::Start(mode))
    return false;
	
  CreateRTs(mode);

  //s_Reprojector.Init(mode.width3D, mode.height3D, FORMAT_A8R8G8B8, FORMAT_R32F);

  s_waterReflCoeff = Clamp(s_waterReflCoeff, 0.125f, 1.0f);

  WaterManager::CreateParams params(s_waterReflCoeff, s_waterReflCoeff);
  WaterManager::Init(params);

  GetDefaultTextures().Init();

  Init();

  InstancedPrimManager::Init();

  Reset( pPostFX, new FullScreenFX() );
  Reset( pPostFXMan, ::Create<PostFXParamsManager>() );
  GetUIRenderer()->Initialize();
  DebugRenderer::Initialize();
  Clear( Color(0, 0, 0, 0) );

  PF_Core::RecolorableTextureManager::Init();

  return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Interface::Stop()
{
  PF_Core::RecolorableTextureManager::Term();
  PF_Core::IUpdateableTexture::ForcedClear();

  ShadowManager::Term();
  WaterManager::Term();
  GetUIRenderer()->Release();
  DebugRenderer::Release();

  GetDefaultTextures().Term();

  pRT0BigCopy = 0;
  pRT0Big = 0;
  pMainRT1Copy = 0;
  pMainRT0Copy = 0;
  pMainRT1 = 0;
  pMainRT0 = 0;
  pMainDepth = 0;
  Reset(pPostFX, 0);
  Reset(pPostFXMan, 0);

  InstancedPrimManager::Term();

  Render::Interface::Stop();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Interface::DropAllSamplerStates()
{
  const SamplerState &stateVS = SamplerState::PRESET_CLAMP_MIP_BILINEAR();
  const SamplerState &statePS = SamplerState::IsTriLinearDisabled() ? SamplerState::PRESET_CLAMP_MIP_BILINEAR()
                                                                    : SamplerState::PRESET_CLAMP_TRILINEAR();
  const Texture2DRef &emptyTexture = GetEmptyTexture2D();
  RenderStatesManager &rsManager = *GetStatesManager();

  for (unsigned int i = Sampler::MIN_PS_SAMPLER_INDEX; i <= 9/*Sampler::MAX_PS_SAMPLER_INDEX*/; ++i)
    rsManager.SetSampler(i, statePS, emptyTexture);

  for (unsigned int i = Sampler::MIN_VS_SAMPLER_INDEX; i <= 9/*Sampler::MAX_VS_SAMPLER_INDEX*/; ++i)
    rsManager.SetSampler(i, stateVS, emptyTexture);
}


extern bool g_doTerrainZPrepass;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Interface::SetScreenToTextureTransform()
{
  CVec4 screenScaleOffset;
  screenScaleOffset.x = 1.0f / pMainRT0->GetWidth();
  screenScaleOffset.y = 1.0f / pMainRT0->GetHeight();
  screenScaleOffset.z = 0.5f * screenScaleOffset.x;
  screenScaleOffset.w = 0.5f * screenScaleOffset.y;

  GetRenderer()->SetPixelShaderConstantsVector4(SCREEN_TO_TEXTURE, screenScaleOffset);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Interface::RenderDecalMask( const BatchQueue &queue, NDb::MaterialPriority priority, Texture2D *pDepthTex )
{
  if( !g_enableDecalUnion || ShadowManager::Get()->IsShadowRendering() || queue.IsEmpty(priority) )
    return false;
 
  if(!decalRT && !decalRTCreated)
  {
    // TODO: Need to create single channel RT for mask only.
    // Use mask in second pass to return proper alpha value of decal.
    decalRT = Render::CreateRenderTexture2D(width3D, height3D, FORMAT_A8R8G8B8, FALSE);
    decalRTCreated = true;
  }

  if(!decalRT && decalRTCreated)
  {
    return false;
  }

  IDirect3DSurface9* oldRT0 = SmartRenderer::GetRenderTarget(0);
  IDirect3DSurface9* oldRT1 = SmartRenderer::GetRenderTarget(1);
  
  DXSurfaceRef surf = decalRT->GetSurface(0);
  SmartRenderer::BindRenderTargetColor(0, surf);
  SmartRenderer::BindRenderTargetColor(1, 0);
  Render::GetDevice()->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0, 0, 0, 0), 0.0f, 0);

  if ( SmartRenderer::UseMainViewport() ) // smirnov [2009/7/15]: why set it here? decals doesn't set their own viewport.
    SmartRenderer::ResetMainViewport();   // Need to find proper place for this call.

  SetScreenToTextureTransform(); // smirnov [2009/7/15]: may (automatically) set this register when render target changes (it doesn't change right here!)

  RenderStatesManager &statesManager = *GetStatesManager();
  statesManager.SetStateDirect(D3DRS_ZWRITEENABLE, 0);
  statesManager.SetStateDirect(D3DRS_SEPARATEALPHABLENDENABLE, 0);
  statesManager.SetStencilState(STENCILSTATE_CHECKBITS, STENCILBIT_DECALRECEIVER);

  statesManager.SetSampler(2, SamplerState::PRESET_CLAMP_POINT(), pDepthTex ? pDepthTex : pMainRT1);

  NDb::DecalModePin &decalModeValue = GetRuntimePins().DecalModeValue;

  const bool dualDepthTex = !s_stencilSupported && NDb::MATERIALPRIORITY_WATERDECALS == priority;
  if(dualDepthTex) {
    statesManager.SetSampler(3, SamplerState::PRESET_CLAMP_POINT(), pMainRT1Copy);
    decalModeValue = NDb::DECALMODEPIN_DUALDEPTH;
  }
  else if(s_useRESZ && NDb::MATERIALPRIORITY_TERRAINDECALS == priority) {
    const SHMatrix &proj = pScene->GetSceneConstants().projection;
    GetRenderer()->SetPixelShaderConstantsVector4(PSHADER_LOCALCONST0, CVec4(-proj._34, proj._33, 0.0f, 0.0f));
    decalModeValue = NDb::DECALMODEPIN_ZDECODE;
  }
  else
    decalModeValue = NDb::DECALMODEPIN_STANDARD;
  
  // Setup states for both passes
  float decalMaskWeight = 1.0f;
  GetDevice()->SetPixelShaderConstantF(96, &decalMaskWeight, 1);
  GetDevice()->SetRenderState(D3DRS_SEPARATEALPHABLENDENABLE, TRUE);
  GetDevice()->SetRenderState(D3DRS_SRCBLENDALPHA, D3DBLEND_ONE);
  GetDevice()->SetRenderState(D3DRS_DESTBLENDALPHA, D3DBLEND_ONE);
  GetDevice()->SetSamplerState(0, D3DSAMP_BORDERCOLOR, 0);
  
  // Setup states for pass 1
  GetDevice()->SetRenderState(D3DRS_BLENDOPALPHA, D3DBLENDOP_MAX);
  
  queue.Render(priority);

  // Render second pass (don't touch decals RGB)
  decalMaskWeight = 0.0f;
  GetDevice()->SetPixelShaderConstantF(96, &decalMaskWeight, 1);
  GetDevice()->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
  GetDevice()->SetRenderState(D3DRS_ALPHAREF, 1);
  GetDevice()->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);
  GetDevice()->SetRenderState(D3DRS_COLORWRITEENABLE, D3DCOLORWRITEENABLE_ALPHA);
  GetDevice()->SetRenderState(D3DRS_BLENDOPALPHA, D3DBLENDOP_REVSUBTRACT);
  GetDevice()->SetSamplerState(0, D3DSAMP_BORDERCOLOR, 0);

  queue.Render(priority);

  SmartRenderer::BindRenderTargetColor(1, oldRT1);
  SmartRenderer::BindRenderTargetColor(0, oldRT0);

  // Blend decals on top of original RT
  GetDevice()->SetRenderState(D3DRS_COLORWRITEENABLE, 0xf);
  GetDevice()->SetRenderState(D3DRS_ZENABLE, FALSE);
  GetDevice()->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
  GetDevice()->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
  GetDevice()->SetRenderState(D3DRS_SEPARATEALPHABLENDENABLE, FALSE);
  GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
  GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
  GetImmRenderer()->RenderScreenQuad(ImmRenderer::Params("DiffuseMap", decalRT));

  SmartRenderer::BindTexture(2, 0);
  if(dualDepthTex)
    SmartRenderer::BindTexture(3, 0);

  if ( SmartRenderer::UseMainViewport() ) // smirnov [2009/7/15]: why set this twice?
    SmartRenderer::ResetMainViewport();

  // Reset states
  statesManager.SetStateDirect(D3DRS_ZWRITEENABLE, 1);
  GetDevice()->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
  GetDevice()->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
  GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
  GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

  return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Interface::RenderDecals( const BatchQueue &queue, NDb::MaterialPriority priority, Texture2D *pDepthTex )
{
  if( ShadowManager::Get()->IsShadowRendering() || queue.IsEmpty(priority) )
    return;

  RenderSequenceMarker(priority);

  IDirect3DSurface9 *oldRT1 = SmartRenderer::GetRenderTarget(1);
  SmartRenderer::BindRenderTargetColor(1, 0);

  if ( SmartRenderer::UseMainViewport() ) // smirnov [2009/7/15]: why set it here? decals doesn't set their own viewport.
    SmartRenderer::ResetMainViewport();   // Need to find proper place for this call.

  SetScreenToTextureTransform(); // smirnov [2009/7/15]: may (automatically) set this register when render target changes (it doesn't change right here!)

  RenderStatesManager &statesManager = *GetStatesManager();
  statesManager.SetStateDirect(D3DRS_ZWRITEENABLE, 0);
  statesManager.SetStateDirect(D3DRS_SEPARATEALPHABLENDENABLE, 0);
  statesManager.SetStencilState(STENCILSTATE_CHECKBITS, STENCILBIT_DECALRECEIVER);

  statesManager.SetSampler(2, SamplerState::PRESET_CLAMP_POINT(), pDepthTex ? pDepthTex : pMainRT1);

  NDb::DecalModePin &decalModeValue = GetRuntimePins().DecalModeValue;

  const bool dualDepthTex = !s_stencilSupported && NDb::MATERIALPRIORITY_WATERDECALS == priority;
  if(dualDepthTex) {
    statesManager.SetSampler(3, SamplerState::PRESET_CLAMP_POINT(), pMainRT1Copy);
    decalModeValue = NDb::DECALMODEPIN_DUALDEPTH;
  }
  else if(s_useRESZ && NDb::MATERIALPRIORITY_TERRAINDECALS == priority) {
    const SHMatrix &proj = pScene->GetSceneConstants().projection;
    GetRenderer()->SetPixelShaderConstantsVector4(PSHADER_LOCALCONST0, CVec4(-proj._34, proj._33, 0.0f, 0.0f));
    decalModeValue = NDb::DECALMODEPIN_ZDECODE;
  }
  else
    decalModeValue = NDb::DECALMODEPIN_STANDARD;

  queue.Render(priority);
  
  SmartRenderer::BindTexture(2, 0);
  if(dualDepthTex)
    SmartRenderer::BindTexture(3, 0);

  statesManager.SetStateDirect(D3DRS_ZWRITEENABLE, 1);
  SmartRenderer::BindRenderTargetColor(1, oldRT1);

  if ( SmartRenderer::UseMainViewport() ) // smirnov [2009/7/15]: why set this twice?
    SmartRenderer::ResetMainViewport();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Interface::RenderOpaque( const BatchQueue &queue, NDb::MaterialPriority priority )
{
  if (!g_bDrawOpaque)
    return;
/*
  {
    IDirect3DSurface9 *pDS = 0;
    HRESULT hr = GetDevice()->GetDepthStencilSurface(&pDS);
    if( SUCCEEDED(hr) && pDS ) {
      D3DSURFACE_DESC desc;
      hr = pDS->GetDesc(&desc);
      pDS->Release();
    }
  } */

  RenderSequenceMarker(priority);

  // by default clear stencil marks (shadow/decal), may be overridden in material
  GetStatesManager()->SetStencilState(STENCILSTATE_WRITEBITS, STENCILBIT_SHADOWRECEIVER | STENCILBIT_DECALRECEIVER, 0);

  WireframeEnable(true, WIREGROUP_OPAQUE);
  queue.Render( priority );
  WireframeEnable(false, WIREGROUP_OPAQUE);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Interface::RenderSilhouette( const BatchQueue &queue )
{
  if (!g_bDrawOpaque)
    return;

  if (!queue.IsEmpty(NDb::MATERIALPRIORITY_MESHESSILHOUETTE))
  {
    Primitive::UseHiddenIndices(true);

    RenderStatesManager &statesManager = *GetStatesManager();
    Render::RenderState renderState;
    renderState.SetBlendMode(NDb::BLENDMODE_OFF);
    renderState.SetAlphaTest(NDb::ONOFFSTATE_OFF);
    renderState.SetCulling(NDb::ONOFFSTATE_ON);
    statesManager.SetState(renderState);
    statesManager.SetStencilState(STENCILSTATE_WRITEBITS, STENCILBIT_SHADOWRECEIVER | STENCILBIT_DECALRECEIVER, 0);
    statesManager.SetStateDirect(D3DRS_ZFUNC, D3DCMP_ALWAYS);

    // render exploded objects with front z
    GetRenderer()->SetVertexShaderConstantsVector4(VSHADER_LOCALCONST0, CVec4(silhouetteThickness, 888.888f, 0.0f, 888.888f));
    queue.Render( NDb::MATERIALPRIORITY_MESHESSILHOUETTE );

    // render normal objects with back z (make a hole)
    GetRenderer()->SetVertexShaderConstantsVector4(VSHADER_LOCALCONST0, CVec4(0.0f, 888.888f, 1.0f, 888.888f));
    queue.Render( NDb::MATERIALPRIORITY_MESHESSILHOUETTE );

    // restore direct states
    statesManager.SetStateDirect(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

    Primitive::UseHiddenIndices(false);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Interface::RenderMainPassOpaque( const BatchQueue &queue )
{
  NI_PROFILE_FUNCTION

  SetDefaultStates();

  RenderStatesManager &statesManager = *GetStatesManager();

  const bool renderingReflection = WaterManager::Get()->IsReflectionRendering();
  if(!renderingReflection)
  {
    GetDevice()->SetScissorRect(&renderArea);
    statesManager.SetStateDirect(D3DRS_SCISSORTESTENABLE, TRUE);
    RenderSequenceMarker("SILHOUETTE");
    RenderSilhouette(queue);
  }
  statesManager.SetStencilState(STENCILSTATE_IGNORE);

  const bool terrainFirst = !s_stencilSupported || renderingReflection/*|| s_EnableRC*/;
  if(!terrainFirst )
    RenderOpaque(queue, NDb::MATERIALPRIORITY_MESHESOPAQUE);

  if(!renderingReflection) {
    statesManager.SetStencilState(STENCILSTATE_WRITEBITS, STENCILBIT_SHADOWRECEIVER | STENCILBIT_DECALRECEIVER);
    queue.Render( NDb::MATERIALPRIORITY_TERRAINOBJECTS );
  }

  if( Terrain::Terrain* const pTerrain = pScene->GetRenderableTerrain() )
    pTerrain->OnRender(queue, g_doTerrainZPrepass);
  
  const bool copyDepth = s_readableDepth && !renderingReflection;
  const bool dualDepthCopy = !s_stencilSupported && !queue.IsEmpty(NDb::MATERIALPRIORITY_WATERDECALS);
  NI_ASSERT(copyDepth || !dualDepthCopy, "dualDepthCopy couldn't be true while copyDepth is false");
  NI_ASSERT(!(s_useRESZ && dualDepthCopy), "dualDepthCopy and useRESZ couldn't be true at once");

  // Copy depth buffer for terrain decals (and water decals, if stencil support is absent) rendering.
  Render::Texture2D* const pDepthTex = s_useRESZ ? pMainDepth :
                                       dualDepthCopy ? pMainRT1Copy.GetPtr() : pMainRT1.GetPtr();
  if(copyDepth) {
    const bool hasTerrainDecals = !queue.IsEmpty(NDb::MATERIALPRIORITY_TERRAINDECALS) || !queue.IsEmpty(NDb::MATERIALPRIORITY_TERRAINDOMINATIONDECALS);
    if(hasTerrainDecals && s_useRESZ)
      CopyDepthRESZ();
    else
      if(hasTerrainDecals || dualDepthCopy)
        CopyDepth( pDepthTex->GetSurface(0) );
  }
  if(!renderingReflection)
  {
    // Render both types of decals (simple decals and union decals)
    RenderDecals(queue, NDb::MATERIALPRIORITY_TERRAINDECALS, pDepthTex);
    RenderDecalMask(queue, NDb::MATERIALPRIORITY_TERRAINDOMINATIONDECALS, pDepthTex);
  }

  if( terrainFirst )
    RenderOpaque(queue, NDb::MATERIALPRIORITY_MESHESOPAQUE);

  statesManager.SetStencilState(STENCILSTATE_IGNORE);

  if(renderingReflection)
    RenderSky(queue);

  // Copy depth buffer for water, distortion, shadows etc.
  if(copyDepth) {
    if(s_useRESZ)
      CopyDepthRESZ();
    else
    CopyDepth( pMainRT1->GetSurface(0) );
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Interface::RenderMainPassTransparent( const BatchQueue &queue )
{
  if (!g_bDrawTrasp)
    return;

  RenderStatesManager &statesManager = *GetStatesManager();
  statesManager.SetStateDirect(D3DRS_ZENABLE, 1);

  //// Render special multi-pass opacity objects
  if (!queue.IsEmpty( NDb::MATERIALPRIORITY_TRANSPARENTSPECIAL ))
  {
//#define SPECIALTRANSPARENCY_PER_MESH
#ifdef SPECIALTRANSPARENCY_PER_MESH
    queue.Render_SpecialTransparency( NDb::MATERIALPRIORITY_TRANSPARENTSPECIAL );
#else
    statesManager.SetStateDirect(D3DRS_ZWRITEENABLE, 1);
    statesManager.SetStateDirect(D3DRS_COLORWRITEENABLE, 0x00); // disable back buffer
    GetRuntimePins().RenderModeValue = NDb::RENDERMODEPIN_RENDERSHAPEONLY;
    queue.Render( NDb::MATERIALPRIORITY_TRANSPARENTSPECIAL );

    statesManager.SetStateDirect(D3DRS_ZWRITEENABLE, 0);
    statesManager.SetStateDirect(D3DRS_COLORWRITEENABLE, 0x07); // disable alpha corruption
    GetRuntimePins().RenderModeValue = NDb::RENDERMODEPIN_RENDERNORMAL;
    queue.Render( NDb::MATERIALPRIORITY_TRANSPARENTSPECIAL );
#endif
  }

  statesManager.SetStateDirect(D3DRS_ZWRITEENABLE, 0);
  statesManager.SetStateDirect(D3DRS_COLORWRITEENABLE, 0x07); // disable alpha corruption

  //// Render transparent meshes & particles
  WireframeEnable(true, WIREGROUP_TRANSP);
  queue.Render( NDb::MATERIALPRIORITY_TRANSPARENT );
  WireframeEnable(false, WIREGROUP_TRANSP);

  statesManager.SetStateDirect(D3DRS_COLORWRITEENABLE, 0x0F); // enable alpha
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Interface::RenderMainPassDistortion( const BatchQueue &queue )
{
  if (!g_bDrawDistort)
    return;

  RenderStatesManager &rsManager = *GetStatesManager();
  //rsManager.SetState( RenderState::NoBlendNoTest() );

  RenderSequenceMarker("DISTORTION MESHES");

  rsManager.SetStateDirect(D3DRS_ZENABLE, 1);
  rsManager.SetStateDirect(D3DRS_ZWRITEENABLE, 0);
  rsManager.SetStateDirect(D3DRS_COLORWRITEENABLE, 0x07); // disable alpha corruption

  // set textures
  rsManager.SetSampler(2, SamplerState::PRESET_CLAMP_POINT(), pMainRT1); // for decals with distortion
  rsManager.SetSampler(DISTORTIONBUFFERSAMPLERINDEX, SamplerState::PRESET_CLAMP_BILINEAR(), pMainRT0Copy);
  rsManager.SetSampler(DISTORTIONNOISESAMPLERINDEX, SamplerState::PRESET_WRAP_BILINEAR(), WaterManager::Get()->GetHDxDyTexture() );

  // set pixel to texture space conversion
  SetScreenToTextureTransform();  // smirnov [2009/7/15]: may (automatically) set this register when render target changes (it doesn't change right here!)

  WireframeEnable(true, WIREGROUP_TRANSP);
  queue.Render(NDb::MATERIALPRIORITY_DISTORTION);
  WireframeEnable(false, WIREGROUP_TRANSP);

  // reset textures
  SmartRenderer::BindTexture(2, GetWhiteTexture2D());
  SmartRenderer::BindTexture(DISTORTIONNOISESAMPLERINDEX, GetEmptyTexture2D());

  rsManager.SetStateDirect(D3DRS_COLORWRITEENABLE, 0x0F); // enable alpha
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Interface::RenderSunShadow(const SceneConstants& sceneConsts, IRenderableScene* pScene, float _minHeight, float _maxHeight)
{
  NI_PROFILE_FUNCTION

  ShadowManager* const pShadowManager = ShadowManager::Get();

  if ( showShadows )
  {
    pShadowManager->SetShadowReceiverVolume( pScene->GetRenderableTerrain() );
    pShadowManager->SetShadowRenderingFlag( true );

    //////////////////////////////////////////////////////////////////////////
    // Gather shadow casters
    
    render_Gather.Start();

    /*
    static SceneConstants sceneConsts;
    if (!freezeShadows)
      sceneConsts = sceneConsts_;
    */

    // get (un)projection parameters
    CVec3 frustumEdge(sceneConsts.camfrustum);
    frustumEdge.x /= frustumEdge.z;
    frustumEdge.y /= frustumEdge.z;
    frustumEdge.z = 1.0f;

    // update shadow matrices and get casters bounds
    SceneConstants lightConsts(sceneConsts);
    Render::AABB castersAABB;
    pShadowManager->BuildLightMatrices(&lightConsts, &castersAABB, sceneConsts, frustumEdge, _minHeight, _maxHeight);

    { // gather casters
      shadowBatchQueue.Clear();
      ProcessBatchesFuncBound processor( shadowBatchQueue, lightConsts, pShadowManager->GetCastersBoundsLS(), NScene::SceneComponent::GROUPFLAGS_CASTSHADOW );
      pScene->ForAllObjectsInBBox( processor, castersAABB );
    }

    FrustumCuller culler(lightConsts.viewProjection);
    culler.Clip(&shadowBatchQueue);

    render_Gather.Stop();

    pShadowManager->SubstituteMaterials(shadowBatchQueue);

    //////////////////////////////////////////////////////////////////////////
    // Render shadow casters

    render_Draw.Start();
    ApplySceneConstantsCameraOnly(lightConsts);
    pShadowManager->CreateShadowTexture( shadowBatchQueue, lightConsts );
    ApplySceneConstantsCameraOnly(sceneConsts);
    render_Draw.Stop();

    pShadowManager->RemoveMaterials(shadowBatchQueue);

    pShadowManager->SetShadowRenderingFlag( false );
  }
  else
    pShadowManager->NoShadows();
}


static inline void SetScreenToTextureTransformVP(Renderer* pRenderer)
{
  CVec4 screenScaleOffset;
  int x, y, width, height;
  SmartRenderer::GetMainViewport(x, y, width, height);
  screenScaleOffset.x = 1.0f / width;
  screenScaleOffset.y = 1.0f / height;
  screenScaleOffset.z = (0.5f + x) * screenScaleOffset.x;
  screenScaleOffset.w = (0.5f + y) * screenScaleOffset.y;

  pRenderer->SetPixelShaderConstantsVector4(SCREEN_TO_TEXTURE, screenScaleOffset);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Interface::RenderHeightfog()
{
  IDirect3DSurface9* oldRT1 = SmartRenderer::GetRenderTarget(1);
  SmartRenderer::BindRenderTargetColor(1, 0);

  RenderStatesManager& rsManager = *GetStatesManager();
  rsManager.SetStateDirect(D3DRS_ZWRITEENABLE, 0);
  rsManager.SetStateDirect(D3DRS_COLORWRITEENABLE, 0x07); // disable alpha corruption
  rsManager.SetSampler(1, SamplerState::PRESET_CLAMP_BILINEAR(), pMainRT1);

  Renderer* const pRenderer = GetRenderer();
  
  // Set inverse projection data
  const SceneConstants& sceneConsts = pScene->GetSceneConstants();
  pRenderer->SetPixelShaderConstantsVector4(PSHADER_LOCALCONST0, CVec4(1.0f / sceneConsts.projection.xx, 1.0f / sceneConsts.projection.yy, 888.888f, 888.888f));
  pRenderer->SetPixelShaderConstantsVector4(PSHADER_LOCALCONST1, sceneConsts.invView.GetZ());

  SetScreenToTextureTransform();

  mainBatchQueue.Render(NDb::MATERIALPRIORITY_HEIGHTFOG);
  
  SmartRenderer::BindTexture(1, GetWhiteTexture2D());
  rsManager.SetStateDirect(D3DRS_COLORWRITEENABLE, 0x0F); // enable alpha
  rsManager.SetStateDirect(D3DRS_ZWRITEENABLE, 1);

  SmartRenderer::BindRenderTargetColor(1, oldRT1);
  SmartRenderer::FixViewport();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Interface::Render2SHTexture(const SHMatrix &view, const SHMatrix &proj, const Render::BatchQueue &queue)
{
  GetRenderer()->BeginScene();

  // Make own scene constants
  SceneConstants sceneConsts = pScene->GetSceneConstants();
  sceneConsts.view = view;
  sceneConsts.projection = proj;
  sceneConsts.Update();
  // Apply 'em
  ApplySceneConstants( sceneConsts );
  // Draw main pass
  RenderMainPassOpaque(queue);
  GetRenderer()->EndScene();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Interface::AddObjectSilhouette(NScene::SceneObject* pObject, Render::HDRColor const& color, const SceneConstants & sceneConsts)
{
  // skip silhouette if disabled (entirely transparent)
  if (color.A == 0.0f)
    return;

  tempBatchQueue.Clear();
  pObject->RenderDirectly(tempBatchQueue, sceneConsts);

  if (!tempBatchQueue.IsEmpty(NDb::MATERIALPRIORITY_MESHESOPAQUE))
  {
    // prepare to pass color as elementNumber (no over-burned colors supported)
    Render::Color uintColor = (Render::Color)color;

    // remove selected batches from the main queue and add them to different priority
    Render::Batch* pMainBatch = mainBatchQueue.GetBatches(NDb::MATERIALPRIORITY_MESHESOPAQUE);
    Render::Batch* pBatch = tempBatchQueue.GetBatches(NDb::MATERIALPRIORITY_MESHESOPAQUE);
    while (pBatch)
    {
      // only BasicMaterial is supported
      Render::BasicMaterial* pBasicMaterial = dynamic_cast<Render::BasicMaterial*>(pBatch->pMaterial);
      if (pBasicMaterial)
      {
        // skip the main queue until the same batch
        while (pMainBatch && (pMainBatch->pPrimitive != pBatch->pPrimitive || pMainBatch->pMaterial != pBatch->pMaterial || 
               pMainBatch->elementNumber != pBatch->elementNumber || pMainBatch->pOwner != pBatch->pOwner))
          pMainBatch = pMainBatch->pNextBatch;

        if (pMainBatch)
        {
          // pass color as a sorting value
          NI_STATIC_ASSERT(sizeof(float) == sizeof(unsigned long), INCOMPATIBLE_FLOAT_AND_LONG);
          mainBatchQueue.SetCurrentSortingValue(*(float*)&uintColor.Dummy);

          // push with replaced material
          mainBatchQueue.Push(NDb::MATERIALPRIORITY_MESHESSILHOUETTE, pBatch->pOwner, pBatch->pPrimitive, pBatch->elementNumber, 
            pBasicMaterial->GetSkeletalMeshPin() ? ::Get(pSilhouetteMaterialSkeletal) : ::Get(pSilhouetteMaterialStatic));
        }
      }

      pBatch = pBatch->pNextBatch;
    }
  }

  tempBatchQueue.Clear();
}

void Interface::ProcessSilhouettes(const SceneConstants & sceneConsts)
{
  NI_PROFILE_FUNCTION

#if 1
  // Temporary? Process selection silhouette here as a test [8/26/2010 smirnov]
  if (NGameX::AdventureScreen *pAdvScr = NGameX::AdventureScreen::Instance())
  {
    silhouetteThickness = pAdvScr->GetSelectedOutlineThickness();
    if (silhouetteThickness <= 0.0f)
      return;

    // preselected object
    NScene::SceneObject* pPreselectedSceneObject = pAdvScr->GetCurrentPickedSceneObject();
    if (pPreselectedSceneObject && pPreselectedSceneObject->IsRendered())
      AddObjectSilhouette(pPreselectedSceneObject, pAdvScr->GetCurrentPickedOutlineColor(), sceneConsts);

    // selected object
    NScene::SceneObject* pSelectedSceneObject = pAdvScr->GetSelectedSceneObject();
    if (pSelectedSceneObject && pSelectedSceneObject->IsRendered() && pSelectedSceneObject != pPreselectedSceneObject)
      AddObjectSilhouette(pSelectedSceneObject, pAdvScr->GetSelectedOutlineColor(), sceneConsts);
  }
#endif
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Interface::CopyDepth(const DXSurfaceRef& _dest)
{
  RenderStatesManager& statesManager = *GetStatesManager();
  {
    Render::RenderState renderState( statesManager.GetCurrentState() );
    renderState.SetBlendMode(NDb::BLENDMODE_OFF);
    renderState.SetAlphaTest(NDb::ONOFFSTATE_OFF);
    statesManager.SetState(renderState);
  }
  statesManager.SetStencilState(STENCILSTATE_IGNORE);
  statesManager.SetStateDirect(D3DRS_ZENABLE, FALSE);

  IDirect3DSurface9* rt0 = SmartRenderer::GetRenderTarget(0);
  SmartRenderer::BindRenderTargetColor( 0, _dest );

  const SHMatrix &proj = pScene->GetSceneConstants().projection;
  GetRenderer()->SetPixelShaderConstantsVector4(PSHADER_LOCALCONST0, CVec4(-proj._34, proj._33, 0.0f, 0.0f));

  ImmRenderer::Params params( depthCopyShaderName, pMainDepth, &SamplerState::PRESET_CLAMP_POINT() );
  DWORD srcWidth  = pMainDepth->GetWidth();
  DWORD srcHeight = pMainDepth->GetHeight();
  DWORD destWidth  = SmartRenderer::GetRenderTargetWidth();
  DWORD destHeight = SmartRenderer::GetRenderTargetHeight();
  NI_ASSERT(srcWidth >= destWidth, "Bad depth buffer width");
  NI_ASSERT(srcHeight >= destHeight, "Bad depth buffer height");
  if(srcWidth > destWidth || srcHeight > destHeight )
    params.uvRect.Set(0, 0, float(destWidth) / srcWidth, float(destHeight) / srcHeight);

  GetImmRenderer()->RenderScreenQuad(params);
  SmartRenderer::BindTexture( 0, GetEmptyTexture2D() );

  SmartRenderer::BindRenderTargetColor( 0, rt0 );
  SmartRenderer::FixViewport();
  statesManager.SetStateDirect(D3DRS_ZENABLE, TRUE);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Interface::CopyDepthRESZ()
{
  static const D3DXVECTOR3 vDummyPoint(0.0f, 0.0f, 0.0f);
  static const DipDescriptor desc(RENDERPRIMITIVE_POINTLIST, 0, 0, 1, 0, 1);
  static const float pointSizeOne = 1.0f;

  // Bind destination depth-stencil texture to texture sampler 0
  SmartRenderer::BindTexture(0, pMainDepth);
  // Perform a dummy draw call to ensure texture sampler 0 is set before the resolve is triggered
  RenderStatesManager& statesManager = *GetStatesManager();
  statesManager.SetStateDirect(D3DRS_ZENABLE, FALSE);
  statesManager.SetStateDirect(D3DRS_COLORWRITEENABLE, 0);
  statesManager.SetStateDirect( D3DRS_POINTSIZE, (DWORD&)(pointSizeOne) );
  SmartRenderer::DrawPrimitiveUP( desc, vDummyPoint, sizeof(D3DXVECTOR3) );
  statesManager.SetStateDirect(D3DRS_COLORWRITEENABLE, 0x0F);
  statesManager.SetStateDirect(D3DRS_ZENABLE, TRUE);
  // Trigger the depth buffer resolve; after this call texture sampler 0
  // will contain the contents of the resolve operation
  statesManager.SetStateDirect(D3DRS_POINTSIZE, RESZ_CODE);

  statesManager.SetStateDirect( D3DRS_POINTSIZE, (DWORD&)(pointSizeOne) );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Interface::SetPostFXParams( const NDb::PostFXParams* params )
{
  pPostFXMan->SetDBParams( params );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Interface::DoPostFX(const SceneConstants & _sceneConsts)
{
  RenderStatesManager& statesManager = *GetStatesManager();
  statesManager.SetStateDirect(D3DRS_ZENABLE, 0);
  statesManager.SetStateDirect(D3DRS_ZWRITEENABLE, 0);
  statesManager.SetStateDirect(D3DRS_SEPARATEALPHABLENDENABLE, 0);

  pPostFXMan->Calculate(g_PostFXEnabled, g_SharpEnabled, g_PostFXForced);

  doRTSwap = pPostFX->PrepareBloom(firstRTInChain) || g_PostFXEnabled || g_SharpEnabled || !disableWarFog;
  if(doRTSwap) {
    int x, y, w, h;
    SmartRenderer::GetMainViewport(x, y, w, h);

    SwapRTInChain();

    RECT rc = { max(x, renderArea.left), max(y, renderArea.top),
                min(x + w, renderArea.right), min(y + h, renderArea.bottom) };
    statesManager.SetStateDirect(D3DRS_SCISSORTESTENABLE, TRUE);
    GetDevice()->SetScissorRect(&rc);

    pPostFX->Apply( _sceneConsts, secondRTInChain, pPostFXMan->GetCoeff(), g_PostFXEnabled, g_SharpEnabled,
                    colorSaturation, disableWarFog ? 0 : pMainRT1.GetPtr(), pPostFXMan->GetPivotParams(),
                    customSaturationColor, useSaturationColor );

    rc.left = rc.top = 0;
    rc.right  = firstRTInChain->GetWidth();
    rc.bottom = firstRTInChain->GetHeight();
    GetDevice()->SetScissorRect(&rc);

    SmartRenderer::ResetMainViewport();
  }
  SmartRenderer::BindRenderTargetDepth( GetDepthSurface() );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Interface::RenderMainScene(bool GIsEditor)
{
  NI_PROFILE_FUNCTION

  GetRuntimePins().NewParticlesValue = s_rnd_PFX_new ? NDb::BOOLPIN_TRUE : NDb::BOOLPIN_FALSE;

#ifdef SCENECOMPONENT_STATS
  NScene::SceneComponent::StatisticsRenderReset();
#endif // SCENECOMPONENT_STATS

  // In there are no mainscenes -- do nothing
  if (!pScene)
  {
    // Screen clearing is needed here to get a black blank screen in some rare error cases
    GetRenderer()->Clear(clearColor);
    return;
  }

  Terrain::Terrain* const pTerrain = pScene->GetRenderableTerrain();
  if( pTerrain )
    if( Terrain::NatureMapVisual* natureMap = static_cast<Terrain::NatureMapVisual*>(&pTerrain->GetNatureMap()) )
      if( natureMap->OnRender() )
        if( Terrain::TerrainTextureCache* pTextureCache = pTerrain->GetTextureCache() )
          pTextureCache->OnNatureAttack();

  if( NGameX::AdventureScreen * aScreen = NGameX::AdventureScreen::Instance() )
    if( NGameX::VisibilityMapClient *visMapClient = aScreen->GetClientVisibilityMap() )
      visMapClient->OnRender();

  Render::RenderStatesManager &rsManager = *Render::GetStatesManager();
  rsManager.SetStateDirect(D3DRS_ZENABLE, TRUE);
  rsManager.SetStateDirect(D3DRS_ZWRITEENABLE, TRUE);

  // pre-cache GetRenderTargetData() results
  if (pPostFXMan)
    pPostFXMan->SyncCoeffValue();

  StatisticsMeasurer stats;

  const SceneConstants & sceneConsts = pScene->GetSceneConstants();

  // Update animated textures (caustics etc.)
  PF_Core::IUpdateableTexture::ProceedUpdate(sceneConsts.renderTime);

  pScene->PrepareForRendering();

  // ===========================================================================================================================
  // Gathering main queue of batches

  render_Gather.Start();

  // Add scene objects
  mainBatchQueue.Clear();
  mainBatchQueue.EnableResourceManagment(s_enableDXHints);
  mainBatchQueue.OnNextFrame();

  if ( pScene->NeedDebugRender() || showAABBs )
  {
    NI_PROFILE_BLOCK( "Gather Batch" );

    ProcessBatchesFuncWithGather<true> processor(mainBatchQueue, sceneConsts, gatheredRenderableObjects, &debugRender);
    pScene->ForAllObjectsInCamera( processor );
  }
  else
  {
    NI_PROFILE_BLOCK( "Gather Batch" );

    ProcessBatchesFuncWithGather<false> processor(mainBatchQueue, sceneConsts, gatheredRenderableObjects, &debugRender);
    pScene->ForAllObjectsInCamera( processor );
  }

  float minHeight, maxHeight;
  {
    static const int RECIEVER_PRIORITIES[] = {
      NDb::MATERIALPRIORITY_MESHESOPAQUE,
      NDb::MATERIALPRIORITY_MESHESOPAQUELATE,
      NDb::MATERIALPRIORITY_TERRAINLAYER0,
      NDb::MATERIALPRIORITY_TERRAINOBJECTS
    };
    static const vector<int> priorities( RECIEVER_PRIORITIES, RECIEVER_PRIORITIES + ARRAY_SIZE(RECIEVER_PRIORITIES) );

    FrustumCuller culler(sceneConsts.viewProjection);
    culler.Clip(&mainBatchQueue, priorities); // WARNING: priorities should be sorted in ascending order!
    maxHeight = culler.GetWorldAABB().maxPt.z;
    minHeight = culler.GetWorldAABB().minPt.z - 0.05f;
  }
  const bool detailedRender = !GIsEditor || sceneConsts.campos.z < ShadowManager::Get()->GetShadowHeight() + maxHeight;

  // Add terrain area-of-effect selection
  if( pTerrain )
    pTerrain->RenderAOESelection_Deprecated(mainBatchQueue);

  ProcessSilhouettes(sceneConsts);

  mainBatchQueue.ManageResources();

  render_Gather.Stop();

  // ===========================================================================================================================
  // Precache terrain
  if( pTerrain )
    pTerrain->FillCache(mainBatchQueue, pScene);

  // ===========================================================================================================================
  // Prepare shadow texture

  if(detailedRender) {
    RenderSequenceMarker("RENDER 2 SHADOW");
    RenderSunShadow(sceneConsts, pScene, minHeight, maxHeight);
    RenderSequenceMarker("RENDER 2 SHADOW FINISHED");
  }

  // ===========================================================================================================================
  // Prepare render targets
  const DXSurfaceRef &pMainColorSurface = pMainRT0->GetSurface(0);
  
  // ===========================================================================================================================
  // Some magic to clear depth texture

  //if(!s_readableDepth) {
  //  SmartRenderer::BindRenderTarget(pMainRT1);
  //  GetRenderer()->ClearColorOnly( Color(0,0,0,0) );
  //}
  SmartRenderer::BindRenderTargetColor( 0, pMainColorSurface );
  SmartRenderer::BindRenderTargetDepth( GetDepthSurface() );
  GetRenderer()->Clear( clearColor );

  // ===========================================================================================================================
  // OPAQUE MESHES

  // Multiple render targets (color+depth)
  SmartRenderer::SetDefaultRenderTarget( pMainColorSurface,
                                         s_readableDepth ? DXSurfaceRef() : pMainRT1->GetSurface(0), GetDepthSurface() );
  SmartRenderer::BindRenderTargetDefault();

  render_Draw.Start();
  stats.StartMeasuring();
  ApplySceneConstants( sceneConsts );
  RenderMainPassOpaque(mainBatchQueue);

  if(GIsEditor || s_forceSky)
    RenderSky(mainBatchQueue);

  stats.GetDeltas(render_SceneTriangleCount, render_SceneDIPCount);
  render_Draw.Stop();

  // ===========================================================================================================================
  // WATER

 // Restore single render target (color only)
  SmartRenderer::SetDefaultRenderTarget( pMainColorSurface, GetDepthSurface() );
  SmartRenderer::BindRenderTargetDefault();

  render_Water.Start();
  SetScreenToTextureTransform();  // smirnov [2009/7/15]: may (automatically) set this register when render target changes (it doesn't change right here!)
  RenderSequenceMarker("WATER BEGIN ================");
  RenderWater(*this, sceneConsts, pScene, detailedRender);
  RenderSequenceMarker("WATER END ================");
  render_Water.Stop();

  // Water-dependant decals
  stats.StartMeasuring();
  SetDefaultStates();
  RenderDecals(mainBatchQueue, NDb::MATERIALPRIORITY_WATERDECALS);
  rsManager.SetStencilState(STENCILSTATE_IGNORE);
  stats.AppendDeltas(render_SceneTriangleCount, render_SceneDIPCount);

  // ===========================================================================================================================
  // FULL-SCREEN SHADOW PASS

  if ( showShadows ) 
  {
    RenderSequenceMarker("APPLY SHADOWS BEGIN ================");
    SetScreenToTextureTransform();  // smirnov [2009/7/15]: may (automatically) set this register when render target changes (it doesn't change right here!)
    ShadowManager::Get()->ApplyFullscreenShadows(sceneConsts, /*s_readableDepth ? pMainDepth :*/ pMainRT1);
    RenderSequenceMarker("APPLY SHADOWS END ================");
  }

  // ===========================================================================================================================
  // HEIGHT/VOLUMETRIC FOG
  if(s_drawHeightfog && !s_fogAfterTransp) {
    RenderSequenceMarker("HEIGHT FOG");
    RenderHeightfog();
  }

  // ===========================================================================================================================
  // TRANSPARENT MESHES
  stats.StartMeasuring();
  render_Draw.Start();
  RenderSequenceMarker("TRANSPARENT MESHES");
  RenderMainPassTransparent(mainBatchQueue);
  render_Draw.Stop();
  GetRuntimePins().NewParticlesValue = NDb::BOOLPIN_FALSE;
  
  // ===========================================================================================================================
  // DISTORTION

  render_Draw.Start();
  { // save a copy of back buffer
    bool const doRTCopy = g_bDrawDistort && mainBatchQueue.GetSubQueue(NDb::MATERIALPRIORITY_DISTORTION).numBatches
      || mainBatchQueue.GetSubQueue(NDb::MATERIALPRIORITY_HEIGHTFOG).numBatches;
    if(doRTCopy)
      GetRenderer()->StretchSurface( pMainRT0->GetSurface(0), pMainRT0Copy->GetSurface(0) );
  }
  RenderMainPassDistortion(mainBatchQueue);
  render_Draw.Stop();

  Render::SharedVB::ResetAll();

  // ===========================================================================================================================
  // HEIGHT/VOLUMETRIC FOG

  if(s_drawHeightfog && s_fogAfterTransp) {
    RenderSequenceMarker("HEIGHT FOG");
    RenderHeightfog();
  }
  stats.AppendDeltas(render_SceneTriangleCount, render_SceneDIPCount);

  // ===========================================================================================================================
  // FULL-SCREEN PASSES FOLLOW
  DoPostFX(sceneConsts);

  // ===========================================================================================================================
  // AOE (Area-of-Effect) OVERLAYS
  Render::GetAOERenderer()->Render();

  // release all scene constants
  GetRenderer()->ResetConstantProtectionBlock(CCONTEXT_RENDER_TIME);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Interface::SwapRTInChain()
{
  swap(firstRTInChain, secondRTInChain);
  SmartRenderer::UnBindTexture(firstRTInChain); // Not so efficient, however safe
  SmartRenderer::BindRenderTarget( firstRTInChain );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
RECT& AsRect(CTRect<int>& _arg)
{
  NI_STATIC_ASSERT(sizeof(LONG) == sizeof(int), Wrong_LONG);
  return (RECT&)_arg.left;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Interface::PrepareForUI(bool _isEditor)
{
  Renderer* const pRenderer = GetRenderer();
  SmartRenderer::BindRenderTargetDepth( pRenderer->GetDepthStencilSurface() );

  if(!_isEditor && s_resScale != 1.0f)
  {
    const DXSurfaceRef &pSrc = firstRTInChain->GetSurface(0);
    DWORD  width = pMainRT0->GetWidth();
    DWORD height = pMainRT0->GetHeight();
    if(pRT0Big) {
      width  = pRT0Big->GetWidth();
      height = pRT0Big->GetHeight();

      if(s_scaleMode)
        stretcher.Stretch(firstRTInChain, NULL, pRT0Big, pRT0BigCopy);
      else
        pRenderer->StretchSurface(pSrc, pRT0Big->GetSurface(0), true);

      firstRTInChain  = pRT0Big;
      secondRTInChain = pRT0BigCopy;
      SmartRenderer::BindRenderTarget(firstRTInChain);
    }
    else {
      int x, y, w, h;
      SmartRenderer::GetMainViewport(x, y, w, h);
      CTRect<int> rcSrc(x, y, x+w, y+h);
      if(s_scaleMode)
        stretcher.Stretch(firstRTInChain, &rcSrc, firstRTInChain, secondRTInChain);
      else
      {
        GetDevice()->StretchRect(::Get(pSrc), &AsRect(rcSrc), ::Get(secondRTInChain->GetSurface(0)), NULL, D3DTEXF_LINEAR);
        SwapRTInChain();
      }
    }
    SmartRenderer::SetMainViewport( 0, 0, width, height );
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Interface::Render( bool bEditorSpecific, int x, int y, int width, int height )
{
  SmartRenderer::SetMainViewport( x, y, width, height );
  Render( bEditorSpecific );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Interface::RenderUI( bool GIsEditor )
{
  NI_PROFILE_FUNCTION

  render_UI.Start();

  GetUIRenderer()->Render( ERenderWhat::_2D, firstRTInChain, secondRTInChain );

  render_UI.Stop();

  render_TheRest.Start();

  DebugRenderer::Draw2D();

  SmartRenderer::RenderDeferred2D();
  
  if (NGameX::AdventureScreen *pAdvScr =  NGameX::AdventureScreen::Instance())
  {
    if (NGameX::Minimap *pMinimap = pAdvScr->GetMinimap())
      pMinimap->Render();
  }

  render_TheRest.Stop();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Interface::FlushUI()
{  
   GetUIRenderer()->StartFrame();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Interface::Render( bool GIsEditor )
{
  NI_PROFILE_FUNCTION

  Renderer* const pRenderer = GetRenderer();
  if ( pRenderer->DeviceIsLost() )
    return;

  RenderStatesManager& statesManager = *GetStatesManager();
  ImmRenderer& immRenderer = *GetImmRenderer();

  if( skipFrame.Get() ) {
    if(pRenderer->GetSwapEffectParams() != D3DSWAPEFFECT_COPY)
      pRenderer->StretchSurface( firstRTInChain->GetSurface(0), pRenderer->GetColorSurface() );

    return;
  }

  if( GIsEditor && !SmartRenderer::UseMainViewport() )
    SmartRenderer::SetMainViewport( 0, 0, pMainRT0->GetWidth(), pMainRT0->GetHeight() );

  SmartRenderer::OnFrameStart();

  if( pScene && !PF_Core::RecolorableTexture::RecolorAllowed() )
  {
    PF_Core::RecolorableTexture::AllowRecolor(true);
    PF_Core::RecolorableTextureManager::Get()->ForceDXTexRebuild();
  }

  GetRuntimePins().DoDepthOutValue = s_readableDepth ? NDb::BOOLPIN_FALSE : NDb::BOOLPIN_TRUE;
  InstancedPrimManager::Get()->FreeAllPrimitives();

  if(!GIsEditor)
    SmartRenderer::SetMainViewport(0, 0, width3D, height3D);

  LogMarker("########################### FRAME BEGIN ###########################################");
  pRenderer->BeginScene();

  // Drop counter
  BatchQueue::DropMaterialSwitchCounter();

  // Reset to defaults
  DropAllSamplerStates();
  statesManager.UnlockStencil();
  SetDefaultStates();
  SmartRenderer::SetDefaultRenderTarget( pMainRT0->GetSurface(0), GetDepthSurface() );
  SmartRenderer::BindRenderTargetDefault();

  firstRTInChain = pMainRT0;   
  secondRTInChain = pMainRT0Copy;   

  // Main scene pass
  if( !skipFrame.Get() )
    RenderMainScene( GIsEditor );
  else if(doRTSwap)
    SwapRTInChain();

  // ================================================
  // Retrive stats
  
  // Total statistics
  StatisticsMeasurer::GetValues(render_3DTriangleCount, render_3DDIPCount);
  render_Frame.AddValue(1);

  // Sorry for profiling code [11/17/2009 smirnov]
//  SmartRenderer::_DebugSamplerBindDump();
//  SmartRenderer::_DebugSamplerBindReset();

  RenderSequenceMarker("DebugRenderer 3D");
  DebugRenderer::Draw3D();

  // spherical harmonics
  if (pScene)
    NScene::GetSceneFromRenderableScene(pScene)->GetSHGrid().DebugRender();

  GetUIRenderer()->Render( ERenderWhat::_3D, firstRTInChain, secondRTInChain );

  PrepareForUI(GIsEditor);

  DebugRenderTextures();

  render_TheRest.Stop();

  // ================================================
  // 2D UI section

  SmartRenderer::BindRenderTargetDepth( pRenderer->GetDepthStencilSurface() );
  pRenderer->ClearDepthStencil();
  RenderUI(GIsEditor);

  // ================================================
  // Write back to device
  SmartRenderer::BindRenderTargetColor( 0, pRenderer->GetColorSurface() );

  statesManager.SetState( RenderState::NoBlendNoTest() );
  statesManager.SetStateDirect(D3DRS_ZENABLE, 0);
  statesManager.SetStateDirect(D3DRS_ZWRITEENABLE, 0);

  immRenderer.RenderScreenQuad(ImmRenderer::Params("DiffuseMap", firstRTInChain));

  pRenderer->EndScene(); 

  // Total statistics
  StatisticsMeasurer::GetValues(render_TotalTriangleCount, render_TotalDIPCount);

  statesManager.UpdateStats();

  // ================================================
  // Reloading section
  RenderResourceManager::ReloadShaders();
  RenderResourceManager::ReloadTextures();
  //RenderResourceManager::ReloadGeometry();
  //RenderResourceManager::ReloadPFX();

  DebugRenderer::ClearBuffer(Render::DRBUFFER_DEFAULT);

  // Dump screenshots
  DumpScreenshots();

  // Drop logger
  LogMarker("########################### FRAME END ###########################################");
  BatchQueue::SetRenderLogger(0);
  render_MatSwitchCount.SetValue(BatchQueue::GetMaterialSwitchCounter());
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Interface::SetDefaultStates()
{
  RenderStatesManager &rsManager = *GetStatesManager();

  rsManager.SetState( RenderState::NoBlendNoTest().SetCulling(NDb::ONOFFSTATE_ON) );
  rsManager.SetStateDirect(D3DRS_ZENABLE, 1);
  rsManager.SetStateDirect(D3DRS_ZWRITEENABLE, 1);
  rsManager.SetStateDirect(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
  rsManager.SetStateDirect(D3DRS_FILLMODE, D3DFILL_SOLID);
  rsManager.SetStencilState(STENCILSTATE_IGNORE);

  IDirect3DDevice9* const pDevice = GetDevice();
  // GetStatesManagerOld()->SetMipMapBias( miplodbias );
  //CRAP{ Перенести в SamplerState
  for(size_t samplerIdx = 0; samplerIdx < 16; ++samplerIdx)
  {
    pDevice->SetSamplerState(samplerIdx, D3DSAMP_MIPMAPLODBIAS, (DWORD&)miplodbias);
  }
  //CRAP}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Interface::OnDeviceReset()
{
  SmartRenderer::SetDefaultRenderTarget( GetRenderer()->GetColorSurface(), GetDepthSurface() );
  SmartRenderer::BindRenderTargetDefault();

  SetDefaultStates();
}

bool Interface::SetShadows( bool val )
{
  bool res = showShadows;
  showShadows = val;
  return res;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Interface::CreateAdditionalRTs(UINT width, UINT height)
{
  pRT0Big = CreateRenderTexture2D(width,height, FORMAT_A8R8G8B8);
  pRT0BigCopy = CreateRenderTexture2D(width, height, FORMAT_A8R8G8B8);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Interface::CreateMainTextures( UINT width, UINT height )
{
  pMainRT0 = CreateRenderTexture2D(width,height, FORMAT_A8R8G8B8);
  pMainRT0Copy = CreateRenderTexture2D(width, height, FORMAT_A8R8G8B8);
  renderArea.right = width;
  renderArea.bottom = height;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Interface::InvalidateResources()
{
  if( pScene )
    if( Terrain::Terrain* pTerrain = pScene->GetRenderableTerrain() )
      pTerrain->InvalidateRenderResources();

  pMainRT0 = 0;
  pMainRT0Copy = 0;
  pMainRT1 = 0;
  pMainRT1Copy = 0;
  pRT0Big = 0;
  pRT0BigCopy = 0;
  
  GetDevice()->EvictManagedResources();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Interface::CorrectRendermode( Render::RenderMode &_renderMode )
{
  _renderMode.width3D  = CorrectResolution(_renderMode.width);
  _renderMode.height3D = CorrectResolution(_renderMode.height);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Interface::ApplyNewParams( const Render::RenderMode &_renderMode )
{
  width3D  = _renderMode.width;
  height3D = _renderMode.height;
   
  CreateRTs(_renderMode);

  if( pScene )
    if( Terrain::Terrain* pTerrain = pScene->GetRenderableTerrain() )
      pTerrain->RestoreRenderResources();

  if( NGameX::AdventureScreen *pAdvScr =  NGameX::AdventureScreen::Instance() )
    if( NGameX::Minimap *pMinimap = pAdvScr->GetMinimap() )
      pMinimap->OnRenderModeChange();
}

  // ================================================
  // Render debug textures, if desired
void Interface::DebugRenderTextures()
{
  RenderStatesManager& statesManager = *GetStatesManager();
  ImmRenderer& immRenderer = *GetImmRenderer();
  Renderer* const pRenderer = GetRenderer();

  bool wasViewport = SmartRenderer::UseMainViewport();
  SmartRenderer::SetUseMainViewport( false ); // smirnov [2009/7/15]: make it return previous value

  statesManager.SetState( RenderState::NoBlendNoTest() );
  statesManager.SetStateDirect(D3DRS_ZENABLE, 0);
  statesManager.SetStateDirect(D3DRS_ZWRITEENABLE, 0);

  if (showDepthTexture)
  {
    const SceneConstants & sceneConsts = pScene ? pScene->GetSceneConstants() : Render::SceneConstants::Global();
    float zNear = -sceneConsts.projection._34 / sceneConsts.projection._33;
    float zFar = 100.0f;//-sceneConsts.projection._34 / (sceneConsts.projection._33 - 1.0f); // note: zFar is too far in the game settings, so use constant

    pRenderer->SetPixelShaderConstantsVector4(PSHADER_LOCALCONST0, CVec4(1.0f / (zFar - zNear), -zNear / (zFar - zNear), 888.888f, 888.888f)); // scale and offset for R32f
    immRenderer.RenderScreenQuad(ImmRenderer::Params("DiffuseMapR32f", pMainRT1));
  }

  if ( wasViewport )
    SmartRenderer::ResetMainViewport(); // smirnov [2009/7/15]: don't we need to restore flag, i.e. SetUseMainViewport(wasViewport)?

  // ================================================
  // Debug section
  if (showBackTexture)
  {
    RenderState renderState;
    renderState.SetBlendMode(NDb::BLENDMODE_OFF);
    renderState.SetAlphaTest(NDb::ONOFFSTATE_OFF);
    statesManager.SetState(renderState);
    statesManager.SetStateDirect(D3DRS_ZENABLE, 0);
    immRenderer.RenderScreenQuad(CTRect<int>(128, 500, 128+256, 500+192), ImmRenderer::Params("DiffuseMap", pMainRT0Copy));
  }

  if(!pScene)
    return;

  const SceneConstants& sceneConsts = pScene->GetSceneConstants();
  DebugRenderer::SetMatrix( sceneConsts.view, sceneConsts.projection );

  render_TheRest.Start();
  if (showWaterTexture)
  {
    WaterManager::Get()->ShowWaterTexture(showWaterTexture);
  }
  if (showShadowTexture)
  {
    ShadowManager::Get()->ShowShadowTexture();
  }
  if (showVisibilityMapTexture)
  {
    // @BVS@TODO Ask Vlad to move this code to his system
    NGameX::AdventureScreen     *screen = NGameX::AdventureScreen::Instance();
    NGameX::VisibilityMapClient *visMapClient = screen->GetClientVisibilityMap();

    if (visMapClient) {
      // draw vis.map texture to screen area
      RenderState renderState;
      renderState.SetBlendMode(NDb::BLENDMODE_OFF);
      renderState.SetAlphaTest(NDb::ONOFFSTATE_OFF);
      statesManager.SetState(renderState);
      statesManager.SetStateDirect(D3DRS_ZENABLE, 0);
      CTRect<float> rect(-0.9f, -0.6f, -0.6f, -0.2f);
      pRenderer->SetPixelShaderConstantsVector4(PSHADER_LOCALCONST0, CVec4(1.0f, 0.0f, 0.0f, 0.0f)); // scale and offset for R32f
      SamplerState ss(SamplerState::PRESET_CLAMP_POINT());

      ImmRenderer::Params params("DiffuseMapAlpha", visMapClient->GetTextureSrc(), &ss);
      immRenderer.RenderScreenQuad(CTRect<int>(128, 500, 256, 628), params);

      params.SetTexture( visMapClient->GetTexture(0) );
      immRenderer.RenderScreenQuad(CTRect<int>(256, 500, 384, 628), params);

      params.SetTexture( visMapClient->GetTexture(1) );
      immRenderer.RenderScreenQuad(CTRect<int>(384, 500, 512, 628), params);

      params.SetTexture( visMapClient->GetTexture() );
      immRenderer.RenderScreenQuad(CTRect<int>(512, 500, 640, 628), params);
    }
  }

  if( showNatureAttackTexture )
  {
    if (Terrain::Terrain* pTerrain = pScene->GetRenderableTerrain())
      pTerrain->ShowNatureAttackTexture();
  }
  if( showNatureCoeff ) {
    if(pPostFXMan) {
      Texture2DRef pTex = pPostFXMan->GetCoeff();
      int x = pMainRT0->GetWidth() / 2;
      int y = pMainRT0->GetHeight() / 2;
      int w = pTex->GetWidth() * 4;
      int h = pTex->GetHeight() * 4;
      pRenderer->SetPixelShaderConstantsHDRColor( PSHADER_LOCALCONST0, HDRColor::BLACK() );
      immRenderer.RenderScreenQuad( CTRect<int>(x, y, x + w + 4, y + h + 4), ImmRenderer::Params("ConstantColor") );
      immRenderer.RenderScreenQuad( CTRect<int>(x + 2, y + 2, x + w + 2, y + h + 2),
                                    ImmRenderer::Params("DiffuseMap", pTex) );
    }
  }
  if ( showAmbienceTexture )
  {
    if (NGameX::AdventureScreen *pAdvScr = NGameX::AdventureScreen::Instance())
    {
      if (AmbienceMap* pAmbienceMap = pAdvScr->GetAmbienceMap())
        pAmbienceMap->RenderDebug();
    }
  }
  if ( showTerrainTexCache ) {
    if( const Terrain::Terrain *pTerrain = pScene->GetRenderableTerrain() )
      if( const Terrain::TerrainTextureCache* const pTerrainTextureCache = pTerrain->GetTextureCache() )
      {
        const Texture2D* pTex = pTerrainTextureCache->GetTexture(0);
        const int x = pMainRT0->GetWidth() / 2;
        const int y = pMainRT0->GetHeight() / 2;
        const int w = x * 0.6f,  h = y  * 0.75f;
        pRenderer->SetPixelShaderConstantsHDRColor( PSHADER_LOCALCONST0, HDRColor(1.f, 0.f, 1.f) );
        immRenderer.RenderScreenQuad( CTRect<int>(x, y, x + w + 4, y + h + 4), ImmRenderer::Params("ConstantColor") );
        immRenderer.RenderScreenQuad( CTRect<int>(x + 2, y + 2, x + w + 2, y + h + 2),
                                      ImmRenderer::Params("DiffuseMap", pTex) );
      }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Interface::CreateRTs( const RenderMode &mode )
{
  const bool useAdditionalRTs = s_forceAdditionalRTs || (mode.width * mode.height > 3 * width3D * height3D);

  DWORD  widthRT = useAdditionalRTs ?  width3D : mode.width;
  DWORD heightRT = useAdditionalRTs ? height3D : mode.height;
  s_readableDepth = GetIConfigManager()->ReadableDepthEnabled();

  s_rnd_PFX_new &= !Compatibility::IsRunnedUnderWine();
  Render::ParticleFXMaterial::SetInstancingFlag(s_rnd_PFX_new);

  CreateDepthTextures(widthRT, heightRT, s_readableDepth ? width3D : widthRT, s_readableDepth ? height3D : heightRT);
  CreateMainTextures(widthRT, heightRT); // Those textures can be used by UI too
  if(useAdditionalRTs)
    CreateAdditionalRTs(mode.width, mode.height); // Those textures will be used by UI
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static bool LoadSH(const char *name, const vector<wstring>& params)
{
  NGameX::AdventureScreen::Instance()->GetWorld()->GetScene()->GetSHGrid().Load();
  return true;
}
static bool SaveSH(const char *name, const vector<wstring>& params)
{
//   NGameX::AdventureScreen::Instance()->GetWorld()->GetScene()->GetSHGrid().Save("Z:/tst_tex/aaa.a");
  NGameX::AdventureScreen::Instance()->GetWorld()->GetScene()->GetSHGrid().Save();
  return true;
}

static bool LogRenderSequence(const char *name, const vector<wstring>& params)
{
  BatchQueue::SetRenderLogger(&s_batchLogger);
  return true;
}

static bool RestartRender()
{
  DebugTrace( "RestartRender" );
  
  Render::RenderMode renderMode;
  
  Render::GetRenderModeFromConfig(renderMode);
  Render::GetRenderer()->CorrectRenderMode(renderMode);
  Interface::CorrectRendermode( renderMode );
  
  UI::GetFontRenderer()->Release();
  Interface::Get()->InvalidateResources();  
  Render::GetRenderer()->InvalidateResources();
 
  NMainFrame::ApplyNewParams( renderMode.width, renderMode.height, renderMode.isFullScreen );
  Render::GetRenderer()->ApplyNewParams(renderMode);
       
  UI::ApplyNewParams( renderMode.width, renderMode.height, renderMode.isFullScreen );             
  Interface::Get()->ApplyNewParams(renderMode);
  UI::GetFontRenderer()->Initialize();

  NMainFrame::SetActualClipCursorRect();

  return true;
}

static bool ApplyPresentParams(const char *name, const vector<wstring>& params)
{
  return RestartRender();
}

static bool ReloadTexturesWithChangedParams( const char *name, const vector<wstring>& params )
{
  Render::ReloadTextures( true );
  return RestartRender();
}

static bool ReloadWaterParams( const char *name, const vector<wstring>& )
{
  WaterManager::Term();
  WaterManager::CreateParams params(s_waterReflCoeff, s_waterReflCoeff);
  WaterManager::Init(params);
  
  return true;
}

static bool ReloadShadowsParams( const char *name, const vector<wstring>& )
{
  Render::ShadowManager::Get()->Reload();
  return true;
}

} // namespace Render


REGISTER_VAR( "vismaptex", showVisibilityMapTexture, STORAGE_NONE );
REGISTER_VAR( "watertex", showWaterTexture, STORAGE_NONE );
REGISTER_DEV_VAR( "aabbs", showAABBs, STORAGE_NONE );
REGISTER_VAR( "shadowtex", showShadowTexture, STORAGE_NONE );
REGISTER_VAR( "depthtex", showDepthTexture, STORAGE_NONE );
REGISTER_VAR( "backtex", showBackTexture, STORAGE_NONE );

REGISTER_VAR( "shadows", showShadows, STORAGE_USER );
REGISTER_VAR_INTERFACE( "proxy_shadows", NGlobal::MakeVarProxy(&showShadows), STORAGE_NONE );

REGISTER_VAR( "shadow_freeze", freezeShadows, STORAGE_NONE );
REGISTER_VAR( "mipmaplodbias", miplodbias, STORAGE_NONE );

REGISTER_VAR( "usecullinghack", usecullinghack, STORAGE_NONE );

REGISTER_VAR( "draw_opaque", g_bDrawOpaque, STORAGE_NONE );
REGISTER_VAR( "draw_transp", g_bDrawTrasp, STORAGE_NONE );
REGISTER_VAR( "draw_distort", g_bDrawDistort, STORAGE_NONE );

REGISTER_DEV_VAR( "nattacktex", showNatureAttackTexture, STORAGE_NONE );
REGISTER_DEV_VAR( "showNatureCoeff", showNatureCoeff, STORAGE_NONE );
REGISTER_DEV_VAR( "ambiencetex", showAmbienceTexture, STORAGE_NONE );
REGISTER_DEV_VAR( "showTerrainTexCache", showTerrainTexCache, STORAGE_NONE );

REGISTER_VAR( "pfx_enable", g_PostFXEnabled, STORAGE_USER );
REGISTER_VAR_INTERFACE( "proxy_pfx_enable", NGlobal::MakeVarProxy(&g_PostFXEnabled), STORAGE_NONE );
REGISTER_VAR( "pfx_sharp_enable", g_SharpEnabled, STORAGE_USER );
REGISTER_VAR_INTERFACE( "proxy_pfx_sharp_enable", NGlobal::MakeVarProxy(&g_SharpEnabled), STORAGE_NONE );
REGISTER_VAR( "pfx_force", g_PostFXForced, STORAGE_NONE );

REGISTER_DEV_VAR( "enable_decal_union", g_enableDecalUnion, STORAGE_NONE );

REGISTER_DEV_CMD( sh_load, PF_Render::LoadSH);
REGISTER_DEV_CMD( sh_save, PF_Render::SaveSH);
REGISTER_DEV_CMD( render_log_seq, PF_Render::LogRenderSequence);
REGISTER_CMD( render_apply_present_params, PF_Render::ApplyPresentParams);
REGISTER_CMD( render_reload_textures, PF_Render::ReloadTexturesWithChangedParams);
REGISTER_CMD( render_reload_water_params, PF_Render::ReloadWaterParams);
REGISTER_CMD( render_reload_shadows_params, PF_Render::ReloadShadowsParams);

static bool WarfogDisable( const char *name, const vector<wstring> &args )
{
  if( args.empty() )
    return false;

  const bool disable( 0 != NStr::ToULong(NStr::ToMBCS(args[0])) );
  if( PF_Render::Interface::Get() )
  {
    PF_Render::Interface::Get()->DisableWarFog(disable);
    return true;
  }
  return false;
}

REGISTER_DEV_CMD( warfogDisable, WarfogDisable);

