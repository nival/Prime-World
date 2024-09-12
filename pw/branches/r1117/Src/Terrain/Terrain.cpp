
#include "stdafx.h"
#include "Terrain.h"
#include "TerrainLayerManager.h"
#include "TEGetter.h"
#include "RoadPrimitive.h"

#include "../Render/renderresourcemanager.h"
#include "../System/Win32Random.h"

#include "../Render/debugrenderer.h"
#include "../Render/MaterialResourceInterface.h"
#include "../Render/GlobalMasks.h"
#include "../Render/ImmediateRenderer.h"
#include "../Render/WaterManager.h"
#include "../Render/NullRenderSignal.h"
#include "../Render/ConfigManager.h"
#include <System/InlineProfiler.h>


// smirnov [2009/1/9]: there's no way to access material properties yet, so we use globals here
namespace Render {
    CVec2& GetAOEScaleHACK();
    CVec2& GetAOEOffsetHACK();
}


DEFINE_DEV_VAR(g_bDrawRoads, true, "draw_roads", STORAGE_NONE);
DEFINE_DEV_VAR(g_bDrawTerrain, true, "draw_terrain", STORAGE_NONE);
DEFINE_DEV_VAR(s_useTextureCache, false, "useTextureCache", STORAGE_NONE);

DEV_VAR_STATIC float g_terrainTiling = 1.7f;
REGISTER_DEV_VAR( "terrain_tiling", g_terrainTiling, STORAGE_NONE );

static NDebug::StringDebugVar terrain_Stats0("Stats0", "Terrain");
static NDebug::StringDebugVar terrain_Stats1("Stats1", "Terrain");
static NDebug::PerformanceDebugVar terrain_Update( "Update", "Terrain", 10, 10, false );

DECLARE_NULL_RENDER_FLAG

using namespace Render;

namespace Terrain
{

#ifndef VISUAL_CUTTED
struct Terrain::InitNatureMapParamsHelper : public NonCopyable
{
public :
  typedef pair<TerrainElementId, NatureMapElementId> tenmmap_type;
  typedef vector< tenmmap_type >                     tenmmap_container;

public :
  InitNatureMapParamsHelper(Terrain *owner)
    : owner(owner)
  {}

public :
  void operator()(NatureMapElementId id, NatureMapElementInfo const& info);
  void operator()(TerrainElementInfo const& info);

public :
  static bool TeLess( tenmmap_type const& t1, tenmmap_type const& t2 ) { return t1.first < t2.first; }
  static bool NmLess( tenmmap_type const& t1, tenmmap_type const& t2 ) { return t1.second < t2.second; }

public :
  tenmmap_container& GetTeNmMap() { return tenmmap; }

private :
  Terrain *owner;
  tenmmap_container tenmmap;
  NatureMapElementId curNmId;
};
#endif

#ifndef VISUAL_CUTTED
void Terrain::InitNatureMapParamsHelper::operator()(NatureMapElementId id, NatureMapElementInfo const& info)
{
  curNmId = id;

  AABB aabb;
  owner->natureMap.GetElementVisualBounds(curNmId, aabb);
  owner->GetElementManager().ForAllElementInfosAABB(*this, aabb);
}

void Terrain::InitNatureMapParamsHelper::operator()(TerrainElementInfo const& info)
{
  tenmmap.push_back(tenmmap_type(info.id, curNmId));
}
#endif


} // namespace Terrain

namespace Terrain
{

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//// NON-VISUAL PART OF TERRAIN
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// dummy constructor for CObjectBase
Terrain::Terrain() // all members are listed explicitly in the order they declared!
: layerManager()
, heightManager()
, elemManager()
#ifndef VISUAL_CUTTED
, geometryManager()
, materialCache()
, grassRenderManager()
, grassManager( grassRenderManager )
, aoeMaterial(NULL)
#endif
, natureMap(false)
#ifndef VISUAL_CUTTED
, textureCacheSize(2048)
, nmTerrainElements()
, teNatureMapElements()
, nmToTe()
, teToNm()
, natureMapDirty(0)
#endif
, modifiedElems()
, gridConstants()
, editable(false)
, aoeEnabled(false)
, aoeCenter(0.0f, 0.0f, 0.0f)
, aoeRadius(1.0f)
, layerDisplayMode(0)
{
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Terrain::Terrain(bool editable_) // all members are listed explicitly in the order they declared!
: layerManager()
, heightManager()
, elemManager()
#ifndef VISUAL_CUTTED
, geometryManager()
, materialCache()
, grassRenderManager()
, grassManager( grassRenderManager )
, aoeMaterial(NULL)
#endif
, natureMap(editable_)
#ifndef VISUAL_CUTTED
, textureCacheSize(2048)
, nmTerrainElements()
, teNatureMapElements()
, nmToTe()
, teToNm()
, natureMapDirty(0)
#endif
, modifiedElems()
, gridConstants()
, editable(editable_)
, aoeEnabled(false)
, aoeCenter(0.0f, 0.0f, 0.0f)
, aoeRadius(1.0f)
, layerDisplayMode(0)
{
  layerManager.SetOwner(this);
  elemManager.SetOwner(this);
  heightManager.SetOwner(this);
  geometryManager.SetOwner(this);

#ifndef VISUAL_CUTTED
  if(!RENDER_DISABLED)
    grassManager.SetHeightsController( this ); // CRAP // smirnov [2009/4/3]: who's there?!
#endif
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Terrain::~Terrain()
{
}

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  void Terrain::Initialize( const NDb::Terrain* pDBTerrain )
  {
    // copy given constants
    gridConstants.valid = true;
    gridConstants.metersPerElement = Patch::SIZE_OF_PATCH;
    gridConstants.sizeInElements.x = pDBTerrain->elemXCount;
    gridConstants.sizeInElements.y = pDBTerrain->elemYCount;
    gridConstants.tilesPerElement  = pDBTerrain->tilesPerElement;
    gridConstants.texelsPerElement = 16;

    // fill derived constants
    gridConstants.worldSize.Set(
      (float)gridConstants.sizeInElements.x * gridConstants.metersPerElement,
      (float)gridConstants.sizeInElements.y * gridConstants.metersPerElement, 50.0f);
    gridConstants.metersPerTile = gridConstants.metersPerElement / (float)gridConstants.tilesPerElement;
    gridConstants.metersPerTexel = gridConstants.metersPerElement / (float)gridConstants.texelsPerElement;
    gridConstants.sizeInTiles.x = gridConstants.sizeInElements.x * gridConstants.tilesPerElement;
    gridConstants.sizeInTiles.y = gridConstants.sizeInElements.y * gridConstants.tilesPerElement;
    gridConstants.sizeInTexels.x = gridConstants.sizeInElements.x * gridConstants.texelsPerElement;
    gridConstants.sizeInTexels.y = gridConstants.sizeInElements.y * gridConstants.texelsPerElement;

    // initialize components
    elemManager.Initialize();
    layerManager.Initialize();
    heightManager.Initialize();
#ifndef VISUAL_CUTTED
    if(!RENDER_DISABLED)
      grassManager.Resize(gridConstants.sizeInTiles.x, gridConstants.sizeInTiles.y);
#endif

    NatureMapParams hip = {&pDBTerrain->natureMap, gridConstants.worldSize};
    bool ok = natureMap.Initialize(hip, &modifiedElems);
    NI_VERIFY(ok, "Couldn't initialize natureMap system for terrain.", return);
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  void Terrain::CreateTerrain( const NDb::Terrain* pDBTerrain )
  {
    ASSERT(IsEditable());
    NI_VERIFY( pDBTerrain, "Invalid pointer to NDb::Terrain resource!", return );

    Initialize(pDBTerrain);

    geometryManager.Initialize( pDBTerrain->geometry );
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  void Terrain::LoadTerrain( const NDb::Terrain* pDBTerrain )
  {
    PushDXPoolGuard dxPool("Terrain");

    NI_VERIFY( pDBTerrain, "Invalid pointer to NDb::Terrain resource!", return );

    Initialize(pDBTerrain);

    geometryManager.Load( pDBTerrain->geometry );
#ifndef VISUAL_CUTTED
    if(!RENDER_DISABLED) {
      grassManager.Load( pDBTerrain->grassLayers );
      RestoreRenderResources();
      if(pTEGetter) {
        struct RegisterInTEGetter : public NonCopyable
        {
          TEGetter &getter;

          RegisterInTEGetter(TEGetter &_getter) : getter(_getter) {}

          void operator () (const TerrainElementInfo &info)
          {
            getter.AddElement(info.pElement);
          }
        } func(*pTEGetter);

        GetElementManager().ForAllElementInfos(func);
        RoadPrimitive::SetTEGetter( Get(pTEGetter) );
      }
    }
#endif
    layerManager.Load( pDBTerrain->layers, pDBTerrain->layerMaskFile );
    heightManager.Load( pDBTerrain->geometry.heightmapFileName );

    InitNatureMapParams();
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef VISUAL_CUTTED
  void Terrain::UpdateTerrainElements()
  {
    if (modifiedElems.size() == 0 || nmTerrainElements.size() == 0)
      return;

    natureMapDirty.FillZero();

    for (int i = 0, endI = modifiedElems.size(); i != endI; ++i)
    {
      int startJ = nmToTe[modifiedElems[i]], endJ = nmTerrainElements.size();
      if (startJ < 0)
        continue;

      for (int k = modifiedElems[i] + 1, endK = nmToTe.size(); k != endK; ++k )
      {
        if (nmToTe[k] != -1)
        {
          endJ = nmToTe[k];
          break;
        }
      }

      for (int j = startJ; j != endJ; ++j)
        natureMapDirty.SetData(nmTerrainElements[j]);
    }

    TerrainElementManager &em = GetElementManager();
    TerrainLayerManager::NatureType types[] = { TerrainLayerManager::NATURE_0, TerrainLayerManager::NATURE_A, TerrainLayerManager::NATURE_B };
    for (TerrainElementId id = em.GetFirstElementId(), end = em.GetLastElementId(); id <= end; ++id)
    {
      if (natureMapDirty.GetData(id))
      {
        int startJ = teToNm[id], endJ = teNatureMapElements.size();
        if (startJ < 0)
          continue;

        for (int k = id + 1, endK = teToNm.size(); k != endK; ++k )
        {
          if (teToNm[k] != -1)
          {
            endJ = teToNm[k];
            break;
          }
        }

        unsigned natureBits = 0;
        for(int j = startJ; j != endJ; ++j)
        {
          NatureMapElementInfo &ni = natureMap.GetElementInfo(teNatureMapElements[j]);
          if (ni.natureCur == ni.natureOld)
          {
            natureBits |= (0xFF << (types[ ni.natureCur ] * 8));
          }
          else
          {
            // some nature-changing is in progress
            // for safety we will render all three terrain types (fix for nasty bug: NUM_TASK)
            natureBits = 0xFFFFFF;
          }
        }

        em.GetElement(id)->natureBits = natureBits;
      }
    }
    
    modifiedElems.clear();
  }
#endif

  void Terrain::Update()
  {
    NDebug::PerformanceDebugVarGuard guard( terrain_Update, true );
    layerManager.Update();
#ifndef VISUAL_CUTTED
    if(!RENDER_DISABLED) {
      heightManager.Update();
      geometryManager.Update();

      if( grassManager.GetVersion() != heightManager.GetHeightsVersion() )
        grassManager.MakeUpdateRequest();

      // update grass layers, regenerate grass geometry
      grassManager.Update();
    }
#endif
    layerManager.GetUpdateRegion().Clear();

    natureMap.Update();

    UpdateTerrainElements();
  }

#ifndef VISUAL_CUTTED
  void Terrain::RecalculateLighting()
  {
    struct RecalcLightFunc : public NonCopyable
    {
      TerrainGeometryManager &m_geoMan;

      RecalcLightFunc(TerrainGeometryManager &geoMan) : m_geoMan(geoMan) {}
      
      void operator () (const TerrainElementInfo &info)
      {
        m_geoMan.InvalidateElement(info.id, INVALID_LIGHTING);
      }
    } recalcLightFunc(GetGeometryManager());

    GetElementManager().ForAllElementInfos(recalcLightFunc);

    Update();
  }


  void Terrain::InvalidateRenderResources()
  {
    Reset(pTextureCache);
  }

  static int GetAvailableVidMem()
  {
    if( ConfigManager * const pCM = GetConfigManager() )
    {
      IDirect3DDevice9* const pDevice = GetDevice();
      IDirect3D9* pD3D;
      if( SUCCEEDED(pDevice->GetDirect3D(&pD3D)) ) {
        IntrusivePtr<IDirect3D9> pD3D_holder(pD3D, false);
        D3DDEVICE_CREATION_PARAMETERS devParams;

        if( SUCCEEDED(pDevice->GetCreationParameters(&devParams)) )
        {
          UINT memSize, memSizeTotal;
          pCM->GetVidMem(pD3D->GetAdapterMonitor(devParams.AdapterOrdinal), &memSize, &memSizeTotal);
          return memSize;
        }
      }
    }
    return -1;
  }

  void Terrain::RestoreRenderResources()
  {
    static const int vidMemRequired = 128; // in MB
    if(!IsEditable() && s_useTextureCache && GetAvailableVidMem() >= vidMemRequired)
    {
      const float tileSize = gridConstants.metersPerElement;
      Reset( pTextureCache, TerrainTextureCache::Create(textureCacheSize, tileSize) );
      if( pTextureCache->IsValid() )
        Reset( pTEGetter, new TEGetter(tileSize) );
      else
        Reset( pTextureCache );
    }
  }


  void Terrain::InitNatureMapParams()
  {
    InitNatureMapParamsHelper f(this);
    natureMap.ForAllElements(f);
    InitNatureMapParamsHelper::tenmmap_container& tenmmap = f.GetTeNmMap();
    TerrainElementManager const& em = GetElementManager();

    sort(tenmmap.begin(), tenmmap.end(), InitNatureMapParamsHelper::TeLess);
    TerrainElementId teId = em.GetFirstElementId();
    teToNm.resize(em.GetLastElementId() + em.GetFirstElementId(), -1);
    teToNm[teId] = 0;

    int tSize = teToNm.size();
    tSize += 0;
    for (int i = 0, endI = tenmmap.size(); i != endI; ++i)
    {
      teNatureMapElements.push_back(tenmmap[i].second);
      if (teId != tenmmap[i].first)
      {
        teId = tenmmap[i].first;
        teToNm[teId] = i;
      }
    }

    sort(tenmmap.begin(), tenmmap.end(), InitNatureMapParamsHelper::NmLess);
    int nmSize = natureMap.GetSizeX() * natureMap.GetSizeY();
    nmToTe.resize(nmSize, -1);
    NatureMapElementId nmeId = 0;
    nmToTe[nmeId] = 0;
    for (int i = 0, endI = tenmmap.size(); i != endI; ++i)
    {
      nmTerrainElements.push_back(tenmmap[i].first);
      if (nmeId != tenmmap[i].second)
      {
        nmeId = tenmmap[i].second;
        nmToTe[nmeId] = i;
      }
    }

    natureMapDirty.SetSize(GetElementManager().GetLastElementId() + 1);
  }

#endif

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //// VISUAL PART OF TERRAIN
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef VISUAL_CUTTED

    void Terrain::StartRendering()
    {
        ConstantProtectionBlock block(CCONTEXT_TERRAIN);

        // directly setup sampler states since no one defined in material
        const SamplerState ss_aniso = SamplerState( SamplerState::PRESET_WRAP_MIP_BILINEAR() ).SetMinFilter(NDb::MINFILTERTYPE_ANISOTROPIC4X);
        const SamplerState& ss = SamplerState::IsTriLinearDisabled() ? SamplerState::PRESET_WRAP_MIP_BILINEAR() :
                                   s_useTextureCache ? ss_aniso : SamplerState::PRESET_WRAP_TRILINEAR();

        RenderStatesManager& rsManager = *GetStatesManager();

        rsManager.SetSamplerState(0, ss);
        rsManager.SetSamplerState(1, ss);
        rsManager.SetSamplerState(2, ss);
        rsManager.SetSamplerState(3, ss);

        // hard-coded material colors
        HDRColor ambientColor(1.0f, 1.0f, 1.0f, 1.0f);
        HDRColor diffuse1Color(1.0f, 1.0f, 1.0f, 1.0f);
        HDRColor diffuse2Color(1.0f, 1.0f, 1.0f, 1.0f);

        // setup common shader params
        Renderer* renderer = GetRenderer();
        const SceneConstants &sceneConst = SceneConstants::Global();
        HDRColor color; 
        color.Mul(sceneConst.ambientColor, ambientColor);
        renderer->SetPixelShaderConstantsHDRColor(TERRAIN_AMBIENT, color);
        color.Mul(sceneConst.diffuse1Color, diffuse1Color);
        renderer->SetPixelShaderConstantsHDRColor(TERRAIN_DIFFUSE1, color);
        color.Mul(sceneConst.diffuse2Color, diffuse2Color);
        renderer->SetPixelShaderConstantsHDRColor(TERRAIN_DIFFUSE2, color);

        renderer->SetVertexShaderConstantsFloat(VSHADER_LOCALCONST0, 0.1f / g_terrainTiling);
        renderer->SetVertexShaderConstantsVector4(VSHADER_LOCALCONST1, CVec4(1.0f / gridConstants.worldSize.x, -1.0f / gridConstants.worldSize.y, 0.0f, 1.0f));
        renderer->SetPixelShaderConstantsFloat(PSHADER_LOCALCONST0, natureMap.GetOverburnScale());

        rsManager.SetSampler(4, SamplerState::PRESET_WRAP_BILINEAR(), natureMap.GetTerrainMask() );
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Terrain::StopRendering()
    {
      GetRenderer()->ResetConstantProtectionBlock(CCONTEXT_TERRAIN);
      SmartRenderer::BindTexture( 4, GetEmptyTexture2D() );

      if (WaterManager::Get()->IsReflectionRendering())
        return;

      //TerrainElementManager &em = GetElementManager();
      //for (TerrainElementId id = em.GetFirstElementId(), endId = em.GetLastElementId(); id != endId; ++id)
      //{
      //  if (em.GetElementInfo(id).pElement->natureBits == 0)
      //    DebugRenderer::DrawAABB(em.GetElementInfo(id).pElement->GetWorldAABB(), Color(0, 0, 0xff, 0xff), false);
      //}

      natureMap.RenderDebug();

      // gather statistics
      int statNatureCountSum = 0;
      int statNatureCountDipSum = 0;
      for (int i = 0; i <= TerrainLayerManager::_NATURE_TYPE_COUNT_; i++)
      {
        statNatureCountSum += TerrainElement::statNatureCount[i];
        statNatureCountDipSum += i * TerrainElement::statNatureCount[i];
      }
      terrain_Stats0.SetValue("TEL = %i/%i/%i, DIP = %i:%i = {%i:%i x0, %i:%i x1, %i:%i x2, %i:%i x3} + %i:OVR",
                              TerrainElement::statElementCount,   TerrainElement::statElementCreated,
                              gridConstants.sizeInElements.x * gridConstants.sizeInElements.y,
                              statNatureCountDipSum, statNatureCountSum,
                              0*TerrainElement::statNatureCount[0], TerrainElement::statNatureCount[0],
                              1*TerrainElement::statNatureCount[1], TerrainElement::statNatureCount[1],
                              2*TerrainElement::statNatureCount[2], TerrainElement::statNatureCount[2],
                              3*TerrainElement::statNatureCount[3], TerrainElement::statNatureCount[3],
                              TerrainElement::statOverrideCount
                              );
      terrain_Stats1.SetValue("TEX: {1:%i, 2:%i, 3:%i, 4:%i} + ERR:%i",
                              TerrainElement::statLayerCount[1], TerrainElement::statLayerCount[2],
                              TerrainElement::statLayerCount[3], TerrainElement::statLayerCount[4], 
                              TerrainElement::statLayerCount[0]
                              );

      // reset statistics
      TerrainElement::statElementCount = 0;
      for (int i = 0; i <= TerrainElement::MAX_LAYER_COUNT; i++)
        TerrainElement::statLayerCount[i] = 0;
      for (int i = 0; i <= TerrainLayerManager::_NATURE_TYPE_COUNT_; i++)
        TerrainElement::statNatureCount[i] = 0;
      TerrainElement::statOverrideCount = 0;
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void Terrain::FillCache(Render::BatchQueue &_queue, class IRenderableScene *_pScene)
    {
      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // Internal for this function
      struct ProcessBatchesFunc : public IObjectFunctor, private NonCopyable
      {
      public:
        ProcessBatchesFunc(BatchQueue &_batchQueue, const SceneConstants &_sceneConsts, int _groupFlagsFilter = GROUPFLAGS_ALL)
          : IObjectFunctor(NScene::VoxelGridObj::RG_ROADS), batchQueue(_batchQueue)
          , sceneConsts(_sceneConsts), groupFlagsFilter(_groupFlagsFilter)
        {}

        virtual void operator()(RenderableSceneObj &obj)
        {
          obj.Render( batchQueue, sceneConsts, groupFlagsFilter );
        }

      protected:
        BatchQueue           &batchQueue;
        const SceneConstants &sceneConsts;
        int                   groupFlagsFilter;
      };
      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

      if(!g_bDrawTerrain || !s_useTextureCache || !pTextureCache)
        return;

      NI_PROFILE_FUNCTION;

      pTextureCache->OnFillStart(&_queue);

      StartRendering();

      RenderStatesManager& statesManager = *GetStatesManager();

      // Render terrain layer 0
      RenderState renderState = RenderState::NoBlendNoTest().SetCulling(NDb::ONOFFSTATE_ON);
      if( _queue.GetBatches(NDb::MATERIALPRIORITY_TERRAINLAYER0) )
      {
        statesManager.SetState(renderState);
        statesManager.SetStateDirect(D3DRS_ZENABLE, FALSE);

        WireframeEnable(true, WIREGROUP_TERRAIN0);
        RenderSequenceMarker("TerrainCache:LAYER0");
        _queue.Render( NDb::MATERIALPRIORITY_TERRAINLAYER0 );
        WireframeEnable(false, WIREGROUP_TERRAIN0);
      }

      // Render terrain layer 1 (additive blending)
      renderState.SetBlendMode(NDb::BLENDMODE_ADDCOLOR);
      statesManager.SetState(renderState);
      if( _queue.GetBatches(NDb::MATERIALPRIORITY_TERRAINLAYER1) )
      {
        WireframeEnable(true, WIREGROUP_TERRAIN1);
        RenderSequenceMarker("TerrainCache:LAYER1");
        _queue.Render( NDb::MATERIALPRIORITY_TERRAINLAYER1 );
        WireframeEnable(false, WIREGROUP_TERRAIN1);
      }

      if(g_bDrawRoads) {
        BatchQueue roadsQueue(Render::BatchQueue::INDEX_SECONDARY, batchQueueSorter, 1024);
        roadsQueue.SetSorting(NDb::MATERIALPRIORITY_ROADS, _queue.GetSubQueue(NDb::MATERIALPRIORITY_ROADS).bSort);
        {
          NI_PROFILE_BLOCK( "Gather roads to fill texCache" );
          ProcessBatchesFunc processor( roadsQueue, _pScene->GetSceneConstants() );
          _pScene->ForAllObjectsInBBox( processor, pTextureCache->GetAABB() );
        }
        // RoadMaterial sets blending himself. We will modify alpha channel blending only
        statesManager.SetStateDirect(D3DRS_SEPARATEALPHABLENDENABLE, TRUE);
        // statesManager.SetStateDirect(D3DRS_BLENDOPALPHA, D3DBLENDOP_ADD); // Not required - D3DBLENDOP_ADD is default value
        statesManager.SetStateDirect(D3DRS_SRCBLENDALPHA,  D3DBLEND_ZERO);
        statesManager.SetStateDirect(D3DRS_DESTBLENDALPHA, D3DBLEND_INVSRCALPHA);

        WireframeEnable(true, WIREGROUP_ROADS);
        RenderSequenceMarker("TerrainCache:ROADS");
        roadsQueue.Render( NDb::MATERIALPRIORITY_ROADS );
        WireframeEnable(false, WIREGROUP_ROADS);
        statesManager.SetStateDirect(D3DRS_SEPARATEALPHABLENDENABLE, FALSE);
      }

      pTextureCache->OnFillEnd(&_queue);

      statesManager.SetStateDirect(D3DRS_ZENABLE, TRUE);
      StopRendering();
    }


    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void Terrain::OnRender( const BatchQueue &_queue, bool _doTerrainZPrepass )
    {
      if(!g_bDrawTerrain)
        return;

      RenderStatesManager& statesManager = *GetStatesManager();
      const bool renderingReflection = WaterManager::Get()->IsReflectionRendering();

      StartRendering();

      // Render terrain layer 0
      Render::RenderState renderState;
      renderState.SetBlendMode(NDb::BLENDMODE_OFF);
      renderState.SetAlphaTest(NDb::ONOFFSTATE_ON);
      renderState.SetAlphaTestRef(127);
      renderState.SetCulling(NDb::ONOFFSTATE_ON);
      statesManager.SetState(renderState);

      WireframeEnable(true, WIREGROUP_TERRAIN0);
      RenderSequenceMarker(NDb::MATERIALPRIORITY_TERRAINLAYER0);

      if(s_useTextureCache && pTextureCache)
        pTextureCache->OnRender( const_cast<BatchQueue&>(_queue) );

      _queue.Render( NDb::MATERIALPRIORITY_TERRAINLAYER0 );
      WireframeEnable(false, WIREGROUP_TERRAIN0);

      if(renderingReflection && _doTerrainZPrepass)
      {
        statesManager.UnlockStencil();
        statesManager.SetStencilState(STENCILSTATE_CHECKBITS, STENCILBIT_RENDERALLOW);
        statesManager.LockStencil();
      }

      // Render terrain layer 1 (additive blending)
      renderState.SetBlendMode(NDb::BLENDMODE_ADDCOLOR);
      statesManager.SetState(renderState);
      statesManager.SetStateDirect(D3DRS_COLORWRITEENABLE1, 0); // additive terrain won't write to depth texture
      statesManager.SetStateDirect(D3DRS_ZWRITEENABLE, FALSE);

      WireframeEnable(true, WIREGROUP_TERRAIN1);
      RenderSequenceMarker(NDb::MATERIALPRIORITY_TERRAINLAYER1);
      _queue.Render( NDb::MATERIALPRIORITY_TERRAINLAYER1 );
      WireframeEnable(false, WIREGROUP_TERRAIN1);

      if(g_bDrawRoads) {
        if(s_useTextureCache && pTextureCache)
          GetRuntimePins().CachingPinValue = NDb::CACHINGPIN_USE;

        WireframeEnable(true, WIREGROUP_ROADS);
        RenderSequenceMarker(NDb::MATERIALPRIORITY_ROADS);
        _queue.Render( NDb::MATERIALPRIORITY_ROADS );
        WireframeEnable(false, WIREGROUP_ROADS);
      }

      if(s_useTextureCache && pTextureCache)
        pTextureCache->RestoreQueue( const_cast<BatchQueue&>(_queue) );

      StopRendering();
      statesManager.SetStateDirect(D3DRS_ZWRITEENABLE, TRUE);
      statesManager.SetStateDirect(D3DRS_COLORWRITEENABLE1, 0x0F); // restore back
    }


    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Terrain::RenderWithMaterial( AABB const& bbox, BatchQueue& queue, BaseMaterial* pMaterial )
    {
        class RenderFunctor
        {
            BatchQueue& queue;
            BaseMaterial* pMaterial;
        public:
            RenderFunctor(BatchQueue& queue_, BaseMaterial* pMaterial_)
                : queue(queue_), pMaterial(pMaterial_) {}
            void operator()(TerrainElementInfo const& elem)
            {
                elem.pElement->RenderWithMaterial(queue, pMaterial);
            }
        private:
            RenderFunctor& operator=(RenderFunctor const&) { return *this; }
        } renderFunctor(queue, pMaterial);
        elemManager.ForAllElementInfosAABB(renderFunctor, bbox);
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Terrain::SetAOEMaterial_Deprecated(NDb::Material const *pMaterial)
    {
      if (pMaterial)
      {
        if ( Get(aoeMaterial) &&
             aoeMaterial->GetDBMaterial()->GetDBID().GetHashKey() == pMaterial->GetDBID().GetHashKey() )
        {
          return;
        }

        Reset(aoeMaterial, static_cast<BaseMaterial*>( CreateRenderMaterial( pMaterial ) ));
      }
      else
      {
        Reset(aoeMaterial, NULL);
      }
    }

    void Terrain::SetAOESelection_Deprecated(CVec3 const& center, float radius)
    {
        aoeEnabled = true;
        aoeCenter = center;
        aoeRadius = radius;

        GetAOEScaleHACK().Set(0.5f / aoeRadius, -0.5f / aoeRadius);
        GetAOEOffsetHACK().Set(-0.5f * (aoeCenter.x / aoeRadius - 1.0f), 0.5f * (aoeCenter.y / aoeRadius + 1.0f));
    }

    void Terrain::RenderAOESelection_Deprecated( BatchQueue& queue )
    {
        if (!aoeEnabled)
            return;

        BaseMaterial *pMaterial = Get(aoeMaterial);
        if (!pMaterial)
        {
          return;
        }

        AABB bbox(aoeCenter, CVec3(aoeRadius, aoeRadius, 100.0f));
        RenderWithMaterial(bbox, queue, pMaterial);
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Terrain::SaveTCV( const string& fileName )
    {
        CObj<Stream> pStream = RootFileSystem::OpenFile( fileName, FILEACCESS_WRITE, FILEOPEN_CREATE_NEW );
        NI_VERIFY( pStream && pStream->IsOk(), NStr::StrFmt( "Cannot open TCV file for writing %s", fileName ), return );
        geometryManager.SaveTCV( pStream );

        MessageTrace( "Terrain::SaveTCV done" );
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Terrain::LoadTCV( const string& fileName, bool applyInstuntly )
    {
        CObj<Stream> pStream = RootFileSystem::OpenFile( fileName, FILEACCESS_READ, FILEOPEN_OPEN_EXISTING );
        NI_VERIFY( pStream && pStream->IsOk(), NStr::StrFmt( "Cannot open TCV file for reading %s", fileName ), return );
        geometryManager.LoadTCV( pStream, applyInstuntly );
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    int Terrain::BakeTerrainGeometry( const vector<TerrainElementId>& elements, const string& backedFileName ) const
    {
      ASSERT(IsEditable());

      CObj<Stream> pBakedStream = RootFileSystem::OpenFile( backedFileName, FILEACCESS_WRITE, FILEOPEN_CREATE_NEW );
      NI_VERIFY( pBakedStream && pBakedStream->IsOk(), NStr::StrFmt( "Cannot open backed file for writing %s", backedFileName ), return 0; );

      {
        unsigned const sign = geometryManager.GetBakedTerrainFileSignature();

        pBakedStream->Write(&sign, sizeof(sign));
      }

      typedef vector<TerrainElementId> TerrainElementContatiner;
      TerrainElementContatiner::const_iterator it = elements.begin();
      const TerrainElementContatiner::const_iterator itEnd = elements.end();

      int numberOfBakedElements = 0;

      for (; it != itEnd; ++it )
      {
        const TerrainElementId& id = *it;
        if ( geometryManager.BakeTerrainElement( id, pBakedStream ) )
          ++numberOfBakedElements;
      }

      MessageTrace( "Terrain::BakeTerrainGeometry done" );
      return numberOfBakedElements;
    }

  void Terrain::ShowNatureAttackTexture()
  {
    CTRect<float> rect(-0.9f, -0.5f, -0.2f, 0.5f), rect2( -0.1f, -0.5f, 0.6f, 0.5f );
    GetImmRenderer()->RenderScreenQuad(rect, ImmRenderer::Params("DiffuseMap", natureMap.GetTerrainMask()));
    GetImmRenderer()->RenderScreenQuad(rect2, ImmRenderer::Params("DiffuseMapAlpha", natureMap.GetTerrainMask()));
  }

  void Terrain::GetBoundsInCamera( const AABB& _cameraAABB, AABB& _receiversAABB )
  {
    struct GatherAABB
    {
      AABB aabb;

      GatherAABB() { aabb.Init2Empty(); }

      void operator()(TerrainElementInfo const& elem)
      {
        aabb.Grow( elem.pElement->GetWorldAABB() );
      }
    } gatherAABB;

    elemManager.ForAllElementInfosAABB( gatherAABB, _cameraAABB );

    _receiversAABB = gatherAABB.aabb;
  }
#endif

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //// END OF VISUAL PART OF TERRAIN
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef VISUAL_CUTTED
  void Terrain::GetBoundsInCamera( const Render::AABB& _cameraAABB, Render::AABB& _receiversAABB )
  {
    NI_ALWAYS_ASSERT("This method is not supported for VISUAL_CUTTED build");
  }
#endif


  inline void TEGetter::AddElement(const TerrainElement* _element)
  {
    const CVec2 &center = _element->GetWorldAABB().center.AsVec2D();
    teMap[GetPatchID(center)] = _element;
  }

  const PatchCacheParams* TEGetter::GetCacheParams(uint _patchID) const
  {
    static PatchCacheParams dummy = {CVec4(), NDb::CACHINGPIN_ORDINARY, 0 };
    TEMap::const_iterator it = teMap.find(_patchID);
    //NI_ASSERT(it != teMap.end(), "Wrong _patchID in TEGetter");
    if( it != teMap.end() )
      return &(it->second->cacheParams);
    else
      return &dummy;
  }
}
