#include "stdafx.h"

#include "../Render/WaterManager.h"

#include "../Render/debugrenderer.h"

#include "../System/InlineProfiler.h"

#include "PFRenderUtils.h"
#include "PFRenderInterface.h"
#include "PFRenderWater.h"

using namespace Render;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static bool render2Reflection       = true;
static bool	showConvexVolumes       = false;
static bool	useConvexesOptimization = true;

NDebug::PerformanceDebugVar s_reflGather("WaterReflGather", "Water", 0, 10, true);

namespace PF_Render
{

DEFINE_DEV_VAR( s_drawWater, true, "draw_water", STORAGE_NONE );

bool g_doTerrainZPrepass = false;
REGISTER_VAR( "waterZPrepass", g_doTerrainZPrepass, STORAGE_NONE );
bool g_useQueries = true;
REGISTER_VAR( "waterUseQueries", g_useQueries, STORAGE_NONE );

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
__declspec(align(16))
struct WaterLevelsProcessor : private NonCopyable
{
private:
	FixedVector<ConvexVolume, 32>  volumes;
	Interface                      &renderInterface;
	const SceneConstants           &sceneConsts;
	IRenderableScene               *pScene;
	CVec3                          camPos;

  void RenderSurfaceMask(WaterLevel &level)
  { // Create water surface mask
    RenderSequenceMarker("REFLECTION MASK BEGIN");
    RenderStatesManager& statesManager = *GetStatesManager();

    Render::RenderState renderState;
    // Configure Z-only rendering
    statesManager.SetState(renderState); // disable alpha test and blending

    GUARD_VALUE(GetRuntimePins().RenderModeValue, NDb::RENDERMODEPIN_RENDERSHAPEONLY);
    statesManager.SetStateDirect(D3DRS_CULLMODE, D3DCULL_CCW);
    statesManager.SetStateDirect(D3DRS_COLORWRITEENABLE, 0);

    statesManager.SetStencilState(STENCILSTATE_WRITEBITS, STENCILBIT_RENDERALLOW);
    statesManager.LockStencil();
    statesManager.SetStateDirect(D3DRS_ZENABLE, FALSE);

    { // render water surface
      static BatchQueueSorter sorter(16, true);
      static BatchQueue tempQueue(BatchQueue::INDEX_SECONDARY, sorter);

      level.PushWaterBatches(tempQueue);
      tempQueue.Render();
      GetRenderer()->ResetConstantProtectionBlock(CCONTEXT_WATER);
      tempQueue.Clear();
    }

    statesManager.UnlockStencil();
    statesManager.SetStencilState(STENCILSTATE_WRITEBITS, STENCILBIT_RENDERALLOW, 0);
    statesManager.LockStencil();
    statesManager.SetStateDirect(D3DRS_ZENABLE, TRUE);
    statesManager.SetStateDirect(D3DRS_ZWRITEENABLE, TRUE);
    renderInterface.tempBatchQueue.Render(NDb::MATERIALPRIORITY_TERRAINLAYER0);

    statesManager.SetStateDirect(D3DRS_COLORWRITEENABLE, 0x0F);
    statesManager.SetStateDirect(D3DRS_CULLMODE, D3DCULL_CW);
    statesManager.UnlockStencil();
    statesManager.SetStencilState(STENCILSTATE_WRITEBITS, STENCILBIT_RENDERALLOW);
    statesManager.LockStencil();

    RenderSequenceMarker("REFLECTION MASK END");
  }

  void IssueInvisibleQueries(WaterLevel &level)
  { // Issue occlusion queries
    BatchQueue &batchQueue = renderInterface.tempBatchQueue;

    RenderSequenceMarker("REFLECTION QUERY ISSUE");
    Batch::SetWaterLevel( true, level.GetLevel() );
    OcclusionQueries::SetUseMode(OcclusionQueries::QUM_ISSUE);

    batchQueue.Render(NDb::MATERIALPRIORITY_MESHESOPAQUE);
    batchQueue.Render(NDb::MATERIALPRIORITY_TERRAINOBJECTS);
    batchQueue.Render(NDb::MATERIALPRIORITY_TRANSPARENT);
    batchQueue.Render(NDb::MATERIALPRIORITY_TRANSPARENTSPECIAL);

    OcclusionQueries::SetUseMode(OcclusionQueries::QUM_NONE);
    OcclusionQueries::SetCurrentCameraID(OcclusionQueriesBank::CID_MAIN);
    Batch::SetWaterLevel(false);
  }

	static void DrawConvexPoly(int numPoints, const CVec3 *pPoints)
	{
		Color color(0x00, 0xFF, 0x00);
		for (int i = 0, j = numPoints-1; i < numPoints; j = i++)
		{
			DebugRenderer::DrawLine3D(pPoints[j], pPoints[i], color, color, false);
		}
	}

public:

	WaterLevelsProcessor(Interface &_renderInterface, const SceneConstants &_sceneConsts, IRenderableScene* _pScene)
		: renderInterface(_renderInterface)
		, sceneConsts(_sceneConsts)
		, pScene(_pScene)
	{
		camPos = sceneConsts.invView.GetTrans3();
	}

	void operator()(int numPoints, const CVec3 *pPoints)
	{
		if (volumes.size() == volumes.capacity())
			return;

		ConvexVolume &volume = volumes.push_back();
		if ( volume.BuildFrustumAndPolyExtrusionIntersection( *renderInterface.pWaterReflectedFrustum, numPoints, pPoints, camPos ) )
		{
			if (showConvexVolumes)
			{
				DrawConvexPoly(numPoints, pPoints);
			}
		}
		else
		{
			// Remove volume
			volumes.setsize(volumes.size() - 1);
		}
	}

	void operator()(WaterLevel &level)
	{
		// ----------------------------------------------------
		// Render reflection

#ifdef _DEBUG_VIEWPORT
    D3DVIEWPORT9 vp;
    GetDevice()->GetViewport(&vp);
#endif // _DEBUG_VIEWPORT

		// Select batch queue to use
		BatchQueue &batchQueue = renderInterface.tempBatchQueue;
		
		// Copy scene constants
		SceneConstants reflSceneConstants = sceneConsts;

		// Reflect camera matrices
    level.BuildMatricesForReflection(&reflSceneConstants, sceneConsts, g_doTerrainZPrepass ? 0.02f : 0.05f );
		reflSceneConstants.Update();

		if (render2Reflection)
		{
		  // Update water reflection frustum
		  ConvexVolume &waterReflectedFrustum = *renderInterface.pWaterReflectedFrustum;
		  waterReflectedFrustum.BuildFrustum( reflSceneConstants.viewProjection );
			// Gather batches
			batchQueue.Clear();
			WaterManager::Get()->SetReflectionRenderingFlag( true );
			{
        NDebug::PerformanceDebugVarGuard guard(s_reflGather, false);

				if (useConvexesOptimization)
				{
					// Gather volumes
					level.ForAllConvexes( *this );

					// For all objects - check all frustums
					const int num = renderInterface.gatheredRenderableObjects.size();
					const int numVolumes = volumes.size();
					for (int i = 0; i < num; i++)
					{
						RenderableSceneObj *pObj = renderInterface.gatheredRenderableObjects[i];
						Render::AABB const &aabb = pObj->GetWorldAABB();
						for (int j = 0; j < numVolumes; j++)
						{
							if (volumes[j].IntersectBox(aabb))
							{
                pObj->Render(batchQueue, reflSceneConstants, NScene::SceneComponent::GROUPFLAGS_REFLECTINWATER);
								break;
							}
						}
					}
				}
				else
				{
					const int num = renderInterface.gatheredRenderableObjects.size();
					for (int i = 0; i < num; i++)
					{
						RenderableSceneObj *pObj = renderInterface.gatheredRenderableObjects[i];
						if (waterReflectedFrustum.IntersectBox(pObj->GetWorldAABB()))
							pObj->Render(batchQueue, reflSceneConstants, NScene::SceneComponent::GROUPFLAGS_REFLECTINWATER);
					}
				}
			}

		  // Render
      WaterManager::Get()->StartRenderingToReflectionTexture(!batchQueue.GetSubQueue(NDb::MATERIALPRIORITY_SKY).pBatchList);

			ApplySceneConstantsCameraOnly(reflSceneConstants);

      if( g_doTerrainZPrepass )
      {
        RenderSurfaceMask(level);
        if( g_useQueries )
        {
          OcclusionQueries::SetCurrentCameraID(OcclusionQueriesBank::CID_WATER);
          OcclusionQueries::SetUseMode(OcclusionQueries::QUM_CHECK_AND_ISSUE);
        }
      }

      RenderSequenceMarker("REFLECTION RENDER");
      renderInterface.RenderMainPassOpaque(batchQueue);
			renderInterface.RenderMainPassTransparent(batchQueue);

      if( g_doTerrainZPrepass )
      {
        if( g_useQueries )
          IssueInvisibleQueries(level);

        RenderStatesManager& statesManager = *GetStatesManager();
        statesManager.UnlockStencil();
        statesManager.SetStencilState(STENCILSTATE_IGNORE);
      }
      SmartRenderer::BindRenderTargetDefault();
		}

		WaterManager::Get()->SetReflectionRenderingFlag( false );

#ifdef _DEBUG_VIEWPORT
    GetDevice()->GetViewport(&vp);
#endif // _DEBUG_VIEWPORT

		// ----------------------------------------------------
		// Render water surface

		// Gather batches
		batchQueue.Clear();
		level.PushWaterBatches(batchQueue);
		ApplySceneConstantsCameraOnly( sceneConsts ); 
		WaterManager::Get()->StartWaterSurfaceRendering( reflSceneConstants.viewProjection, sceneConsts.viewProjection, sceneConsts, renderInterface.pMainRT1 );
    GetStatesManager()->SetStencilState(STENCILSTATE_WRITEBITS, STENCILBIT_SHADOWRECEIVER | STENCILBIT_DECALRECEIVER);

#ifdef _DEBUG_VIEWPORT
    GetDevice()->GetViewport(&vp);
#endif // _DEBUG_VIEWPORT
    // Render batches
    batchQueue.Render();
    SmartRenderer::BindTexture(2, GetEmptyTexture2D());
    SmartRenderer::BindRenderTargetColor(0, renderInterface.pMainRT1->GetSurface(0));
    if(renderInterface.pMainRT1Copy)
      SmartRenderer::BindRenderTargetColor(1,renderInterface.pMainRT1Copy->GetSurface(0));
    SmartRenderer::FixViewport();

    GetRuntimePins().DualDepthPinValue = renderInterface.pMainRT1Copy ? NDb::BOOLPIN_TRUE : NDb::BOOLPIN_FALSE;
    batchQueue.ReplaceMaterial(WaterManager::Get()->GetDummyMaterial());
    batchQueue.Render();
    SmartRenderer::BindRenderTargetDefault();
    GetStatesManager()->SetStencilState(STENCILSTATE_IGNORE);
		WaterManager::Get()->StopWaterSurfaceRendering();
	}
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RenderWater(Interface &iface, const Render::SceneConstants &sceneConsts, IRenderableScene* pScene, bool detailedRender)
{
  NI_PROFILE_FUNCTION;

  const bool reflEnableOld = render2Reflection;
  render2Reflection &= detailedRender;
  Render::GetRuntimePins().ShaderQualityValue = render2Reflection ? NDb::SHADERQUALITYPIN_BEST : NDb::SHADERQUALITYPIN_FAST;

  if(s_drawWater) {
    // Update water
    WaterManager::Get()->Update(sceneConsts.renderTime);

    // Render water
    WaterLevelsProcessor levelsProcessor(iface, sceneConsts, pScene);
    WaterManager::Get()->ProcessGatherdWaterLevels(levelsProcessor);
  }

  render2Reflection = reflEnableOld;
}

}

REGISTER_VAR( "waterrefl", render2Reflection, STORAGE_USER );
REGISTER_VAR_INTERFACE( "proxy_waterrefl", NGlobal::MakeVarProxy(&render2Reflection), STORAGE_NONE );
REGISTER_VAR( "waterconv", useConvexesOptimization, STORAGE_NONE );
REGISTER_DEV_VAR( "waterconvshow", showConvexVolumes, STORAGE_NONE );
