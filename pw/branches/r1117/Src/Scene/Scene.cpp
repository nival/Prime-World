
#pragma once
#include "stdafx.h"
#include "Scene.hpp"
#include "AnimSequencer.h"
#include "Camera.h"
#include "CameraControllersContainer.h"
#include "GeometryBuilders.h"
#include "LightingScene.h"

#include "CollisionHull.h"

#include "System/GeomMisc.h"
#include "Render/StaticMesh.h"
#include "Render/WaterManager.h"
#include "Render/RenderInterface.h"
#include "Render/SHCoeffs.h"
#include "System/Stream.h"
#include "System/nalgoritm.h"
#include "System/ChunklessSaver.h"
#include "System/InlineProfiler.h"
#include "System/AxisBoxGeometry.h"

#include "Terrain/TerrainGeometryManager.h"
#include "Render/DBRender.h"
#include "Render/debugrenderer.h"
#include "Render/ShadowManager.h"
#include "Sound/SoundScene.h"
#include "Render/ParticleFX.h"
#include <Render/ConvertDirection.h>

#include "VertexColorManager.h"

static NDebug::PerformanceDebugVar pick_CollMap( "Pick::Map", "AdvScr", 0, 2.0, true );
static NDebug::PerformanceDebugVar pick_Terrain( "Pick::Terr", "AdvScr", 0, 2.0, true );
static NDebug::DebugVar<int> mainPerf_SOUpdated( "SOs updated", "PerfCnt" );
static NDebug::DebugVar<int> mainPerf_SOFullyUpdated( "SOs fully updated", "PerfCnt" );

static bool s_refineFrustumBB = false;
REGISTER_DEV_VAR("frustum_refineBB", s_refineFrustumBB, STORAGE_NONE)

#ifdef SCENECOMPONENT_STATS
static NDebug::StringDebugVar mainPerf_SCSummary( "SCs summary", "PerfCnt" );
#endif // SCENECOMPONENT_STATS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static Render::StaticMesh* pPickPointModel = 0;
static float culledscreensize = 0.1f;
static struct SRegister_SPickPointGuard
{
	~SRegister_SPickPointGuard() { delete pPickPointModel; }
} pickPointGuard;


static int g_DrawHeights = 0;
static int g_PrecacheResource = 1;

static bool g_drawEntitiesWithoutVisual = false;
static bool g_bDrawPickPoint = true;
static CVec3 g_lastPickPos = VNULL3;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// CRAP { use this id for terrain
namespace
{
DECLARE_NULL_RENDER_FLAG

const int userId = 0x20000000;

struct BuildAABBFunc : public IObjectFunctor, private NonCopyable
{
protected:
  Render::AABB fullaabb;

public:
	BuildAABBFunc()
	{
		fullaabb.center = CVec3(0,0,0);
		fullaabb.halfSize = CVec3(0,0,0);
	}

  virtual void operator()(RenderableSceneObj &obj)
	{
    fullaabb.Grow( obj.GetWorldAABB() );
	}

  const Render::AABB& GetAABB()
	{
		return fullaabb;
	}
};

struct AddToVoxelGridFunc : public IObjectFunctor, private NonCopyable
{
protected:
  NScene::CollectionVG<RenderableSceneObj> *voxelGrid;

public:
  AddToVoxelGridFunc(NScene::CollectionVG<RenderableSceneObj> *vg) : voxelGrid(vg) {}

  virtual void operator()(RenderableSceneObj &obj)
	{
		voxelGrid->add(&obj);
	}
};

struct RemoveToVoxelGridFunc : public IObjectFunctor, private NonCopyable
{
protected:
  NScene::CollectionVG<RenderableSceneObj> *voxelGrid;

public:
  RemoveToVoxelGridFunc(NScene::CollectionVG<RenderableSceneObj> *vg) : voxelGrid(vg) {}

  virtual void operator()(RenderableSceneObj &obj)
  {
    voxelGrid->remove(&obj);
  }
};

using Render::ConvertDirection;

void ConvertDirection(const NDb::Direction &dir, CVec4 &vec)
{
  ConvertDirection( dir, vec.AsVec3D() );
  vec.w = 0.0f;
}

void IntersectFrustumWithPlane(const SHMatrix &viewProjection, float farZ, FrustumIntersection &intersection)
{
	float w = 1.f, h = 1.f, d = 0.9f;

	// build 4 basic rays
	CVec3 rays[4] =
	{
		CVec3(-w, -h, d),
		CVec3(-w,  h, d),
		CVec3( w,  h, d),
		CVec3( w, -h, d)
	};

	__declspec(align(16)) SHMatrix vp = viewProjection;
	vp.HomogeneousInverse(viewProjection);
	CVec3 camPos = vp.GetTranslation();
	camPos.z = fabs(camPos.z);

	// for each ray
	for (int i = 0; i < 4; ++i)
	{
		CVec3 ray;
		vp.RotateVector(&ray, rays[i]);

		float dist = farZ; // overestimate distance from camera projection to intersection point
		if (ray.z < 0.0)
		{
			// calculate distance to intersection point
			dist = camPos.z / fabs(ray.z);
		}

		intersection.points[i].x = camPos.x + ray.x * dist;
		intersection.points[i].y = camPos.y + ray.y * dist;
	}
}

// This function builds AABB for the projection of frustum volume onto XY plane, moved to specified Z.
// Frustum cone should intersect XY plane. Only upper part of cone (before intersection)
// is considered to generate the projection.
//
// Note! Calculation is not precise. AABB is a little overestimated.
//
// Note! If upper plane of frustum cone doesn't intersect XY plane AABB is highly
// overestimated.
void CalculateFrustumAABB(const FrustumIntersection &intersection, CVec3 camPos, float z, Render::AABB &aabb)
{
  camPos.z = fabs(camPos.z);

  BoundCalcer calc;
  if (camPos.z < EPS_VALUE)
  {
    for (int i = 0; i < 4; i++)
    {
      CVec3 p(intersection.points[i], z);
      calc.Add(p);
    }
  }
  else
  {
    float scale = (camPos.z - z) / camPos.z;
    for (int i = 0; i < 4; i++)
    {
      CVec3 p(intersection.points[i], 0.0f);
      p -= camPos;
      p *= scale;
      p += camPos;

      calc.Add(p);
    }
  }
	calc.Add(camPos);
	aabb.Set(calc.GetMin(), calc.GetMax());

  // make bbox big vertically so that objects' height doesn't matter
  aabb.halfSize.z = Max(aabb.halfSize.z, 100.f);
}

const float voxelSizeX = 10.f;
const float voxelSizeY = 10.f;
}
// CRAP }

IMPLEMENT_SIMPLE_SIGNAL_ST2(bool, IRenderableScene)

namespace NScene
{

#pragma warning( disable: 4355 ) //'this' : used in base member initializer list

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Scene::Scene()
	: currentTime( ANIM_START_TIME )
	, floorsCount( 0 )
	, activeFloor( -1 )
	, nextUniqueID( 0 )
	, pTerrain( 0 )
  , lightEnvironmentD(this, &Scene::OnLightingEnvironmentChangedD)
  , lightEnvironmentN(this, &Scene::OnLightingEnvironmentChangedN)
  , accDelta(0.f)
	, isFade(false)
	, fadeAlpha(0.f)
	, updateCount(0)
	, pCameraFrustum(new Render::ConvexVolume())
	, shGrid(this)
  , stepLength(DEFAULT_GAME_STEP_LENGTH)
  , stepLengthInSeconds(DEFAULT_GAME_STEP_LENGTH/1000.0f)
{
	ResetVoxelGrid();
  // mark renderArea as invalid
  renderArea.left = renderArea.top = 0;
  renderArea.bottom = renderArea.right = -1;
  //Render::ShadowManager::Term();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Scene::~Scene()
{
  // TODO: more cleanup?
  lightEnvironmentD = NULL;
  lightEnvironmentN = NULL;

	// remove all objects from scene
  for (int priority = 0; priority < UPDATEPRIORITY_COUNT; ++priority)
  {
    SceneObjectBase::Ring& objectsRing = objectsRings[priority];
    while (objectsRing.first() != objectsRing.last())
      objectsRing.first()->RemoveFromScene();
    ring::Clear(objectsRing);
  }

	if ( Render::Interface::Get() )
	{
		Render::Interface::Get()->RegisterSceneForRendering( NULL );
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Scene::Init( const char* _name, int _floorsCount, const CVec3& _floorBase, float _floorSize, int _stepLength )
{
  NI_PROFILE_FUNCTION

	name = _name;
	floorsCount = _floorsCount;
	activeFloor = 0;
	pCamera = CreateCamera();
	pControllersContainer = new CameraControllersContainer( pCamera );

	pCollisionMap = new CollisionMap();
	pCollisionMap->Initialize( floorsCount, _floorBase, _floorSize );

	heightsController.Initialize( floorsCount * 2 );

	// Initialize to fully white lighting
	for (int c = 0; c < 3; c++)
	{
		sceneConstants.envLighting.linearAndConstant[c] = CVec4(0.0f, 0.0f, 0.0f, 1.0f);
		sceneConstants.envLighting.quadratic[c] = CVec4(0.0f, 0.0f, 0.0f, 0.0f);
	}
	sceneConstants.envLighting.quadraticRGB = CVec4(0.0f, 0.0f, 0.0f, 0.0f);
  sceneConstants.worldSize.x = sceneConstants.worldSize.y = _floorSize;

  stepLength = _stepLength;
  stepLengthInSeconds = _stepLength/1000.0f;
}

void Scene::RemoveObject( SceneObjectBase* pSceneObject )
{
  if (pSceneObject->getVoxelGrid() == Get(voxelGrid))
  {
    voxelGrid->remove(pSceneObject);
  }
  SceneObjectBase::Ring::safeRemove(pSceneObject);
}

Terrain::TerrainElementId Scene::AddTerrainElement( const NDb::TerrainElementInstance& descriptor, const string& fileName )
{
  Terrain::TerrainElementId id = GetTerrain()->AddTerrainElement(descriptor, fileName);
  
  // add new terrain element to voxel grid
  {
    Terrain::TerrainElement* pElement = GetTerrain()->GetElementManager().GetElement(id);
		ASSERT(pElement != NULL);
    voxelGrid->add(pElement);
  }

  return id;
}

bool Scene::DeleteTerrainElement( Terrain::TerrainElementId id )
{
  // remove terrain element from voxel grid
  {
    Terrain::TerrainElement* pElement = GetTerrain()->GetElementManager().GetElement(id);
    ASSERT(pElement != NULL);
      voxelGrid->remove(pElement);
  }
  
  return GetTerrain()->DeleteTerrainElement( id );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Vertex color manager
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Scene::CreateMeshVertexColorsManager(bool bEditor)
{
  NI_PROFILE_FUNCTION

	Reset(pMeshVertexColorsManager, new MeshVertexColorsManager(bEditor));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Scene::LoadWaterMap(nstl::string const& fileName)
{
  NI_PROFILE_FUNCTION

  CObj<Stream> pStream = RootFileSystem::OpenFile( fileName, FILEACCESS_READ, FILEOPEN_OPEN_EXISTING );

  if (!(pStream && pStream->IsOk()))
  {
    return;
  }

  Reset(waterMap, new BitMap);
  CObj<IBinSaver> pSaver = CreateChunklessSaver( pStream, 0, true );
  pSaver->Add(1, Get(waterMap));
}

void Scene::LoadWaterMap( BitMap* _waterMap )
{
  Reset(waterMap, _waterMap);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// picks
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Scene::PickObjects( PickResult *pIntersections, const CVec3& origin, const CVec3& direction )
{
	NI_VERIFY( IsValid( pCollisionMap ), "Invalid collision map!", return 0; );

	pick_CollMap.Start();
	CRay ray( origin, direction );
	const int result = pCollisionMap->Trace( pIntersections->intersections, ARRAY_SIZE( pIntersections->intersections ), ray, true, pCamera->GetNear() );
	pIntersections->usedIntersections = result;
	pick_CollMap.Stop();

	return result;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Scene::PickTerrain( CVec3 &pos, const CVec3& origin, const CVec3& direction )
{
	if( pTerrain )
  {
	  pick_Terrain.Start();
    CRay ray( origin, direction );
    bool hasIntersection = heightsController.Intersect( &pos, ray );
    pick_Terrain.Stop();
		return hasIntersection;
  }

	return false;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Scene::Pick( PickResult *pIntersections, const CVec3& origin, const CVec3& direction )
{
	pIntersections->terrainIntersectionLayer = 0;
	pIntersections->hasTerrainIntersection = PickTerrain(pIntersections->terrainIntersection, origin, direction);
	return PickObjects(pIntersections, origin, direction);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Scene::Pick( PickResult *pIntersections, const CVec2& screenPos )
{
	CRay ray;
	pCamera->GetProjectiveRay( &ray.ptOrigin, &ray.ptDir, screenPos );
	return Pick( pIntersections, ray.ptOrigin, ray.ptDir );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Scene::PickRect( CollisionHull* pHull, int w, int h, CTRect<float> *pRect )
{
	if ( !pCamera )
		return false;

	if ( !pCollisionMap->TraceRect( pHull, pCamera->GetProjectiveMatrix() * pCamera->GetViewMatrix(), pCamera->GetNear(), w,h, pRect ) )
		return false;
	
	return true;
}

static bool g_skipFrame = true;
REGISTER_DEV_VAR( "camera_skip_frame",  g_skipFrame, STORAGE_NONE );

//bool g_simpleShaders = false;
//REGISTER_VAR( "simpleShaders", g_simpleShaders, STORAGE_USER);


struct AABB_Accumulator
{
  CAxisBox bb;

  void operator()(RenderableSceneObj &obj)
  {
    const Render::AABB &aabb = obj.GetWorldAABB();
    bb.Expand( CAxisBox(aabb.center, aabb.halfSize, true) );
  }

  NScene::VoxelGridObj::RenderGroups getRenderGroup() const { return NScene::VoxelGridObj::NUM_GROUPS; }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Scene::UpdateCamera(Time time, Time delta)
{
  pControllersContainer->Step( delta );

  if(skipFrame)
    return;

  SCameraPosition pos;
  pCamera->GetPosition(&pos);
  sceneConstants.campos = pos.GetCameraPos();

  pCamera->GetProjectiveRayLocal(&sceneConstants.camfrustum, CVec2(pCamera->GetScreenWidth(), 0.0f));

  sceneConstants.projection = pCamera->GetProjectiveMatrix();
  sceneConstants.view = pCamera->GetViewMatrix();
  sceneConstants.renderTime = time;
  sceneConstants.Update();

  // Update intersection of frustum with zero plane
  IntersectFrustumWithPlane(sceneConstants.viewProjection, pCamera->GetFar(), frustumIntersection);

  CalculateFrustumAABB(frustumIntersection, sceneConstants.invView.GetTranslation(), pTerrain ? zMin : -10, frustumAABB);

  if(s_refineFrustumBB) {
    AABB_Accumulator acc;
    voxelGrid->process(acc, frustumAABB, true);
    CalculateFrustumAABB(frustumIntersection, sceneConstants.invView.GetTranslation(), acc.bb.GetMin().z, frustumAABB);
  }

  sceneConstants.cameraAABB = frustumAABB;
  sceneConstants.farplane = pCamera->GetFar();


  // Update frustum for the camera
  if(renderArea.left < renderArea.right && renderArea.top < renderArea.bottom)
    pCameraFrustum->BuildFrustum( sceneConstants, renderArea, pCamera->GetScreenWidth(), pCamera->GetScreenHeight() );
  else
    pCameraFrustum->BuildFrustum(sceneConstants.viewProjection);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Scene::Update( Time time, Time delta, bool bIsPaused, bool isForcedUpdate )
{
  NI_PROFILE_FUNCTION

	time += ANIM_START_TIME;
	if (delta > 0.2f)
		delta = 0.2f;

  accDelta += delta;
  const bool skipFrameRender = skipFrame.Get();
  //const bool skipFrameRender = false;

  if(!skipFrameRender)
    Render::SharedVB::ResetAll();
  //Render::GetRuntimePins().ShaderQualityValue = g_simpleShaders ? NDb::SHADERQUALITYPIN_FAST : NDb::SHADERQUALITYPIN_BEST;

  if(!g_skipFrame) {
    NI_PROFILE_BLOCK("!g_skipFrame");
    UpdateCamera(time, accDelta);
  }

  if(!bIsPaused && !skipFrameRender)
  {
    NI_PROFILE_BLOCK("!bIsPaused");
  
	  int objectsCount = 0;
	  objectsFullyUpdatedCount = 0;
    for (int priority = 0; priority < UPDATEPRIORITY_COUNT; ++priority)
    {
	    for (ring::Range<SceneObjectBase::Ring> it( objectsRings[priority] ); it; )
	    {
		    SceneObjectBase *pObj = &(*it);
		    ++it;
        pObj->Update( accDelta, isForcedUpdate );
		    objectsCount++;
	    }
    }
	  mainPerf_SOUpdated.SetValue(objectsCount);
	  mainPerf_SOFullyUpdated.SetValue(objectsFullyUpdatedCount);
  }
	currentTime = time;

  if(g_skipFrame) {
    NI_PROFILE_BLOCK("g_skipFrame");
    UpdateCamera(time, accDelta);
  }

  if(skipFrameRender)
    return;

  accDelta = 0.f;

	// Update number of updates
	++updateCount;

#ifdef SCENECOMPONENT_STATS
  {
    NI_PROFILE_BLOCK("SCENECOMPONENT_STATS");
    
    unsigned long numTotal = 0, numShadows = 0, numReflections = 0;
    unsigned long numRTotal = 0, numRShadows = 0, numRReflections = 0;
    SceneComponent::StatisticsGet(&numTotal, &numShadows, &numReflections);
    SceneComponent::StatisticsRenderGet(&numRTotal, &numRShadows, &numRReflections);
    mainPerf_SCSummary.SetValue("RENDERED: %lu ( S:%lu R:%lu ) CREATED: %lu ( S:%lu R:%lu )", 
      numRTotal, numRShadows, numRReflections, 
      numTotal, numShadows, numReflections );
  }
#endif // SCENECOMPONENT_STATS

  if (pTerrain)
    pTerrain->Update();

  // debug draw
  if (g_DrawHeights)
  {
    NI_PROFILE_BLOCK("g_DrawHeights");
    const float scale = 0.5f;
    const float tileSize = pTerrain->GetGridConstants().metersPerTile;

    if (g_DrawHeights > 1)
    {
      for (int y = 0, h = pTerrain->GetHeightManager().GetHeights().GetSizeY() * g_DrawHeights; y < h; y++)
      {
        for (int x = 0, w = pTerrain->GetHeightManager().GetHeights().GetSizeX() * g_DrawHeights; x < w; x++)
        {
          CVec3 pos((x + 0.5f) * tileSize / g_DrawHeights, (y + 0.5f) * tileSize / g_DrawHeights, 0.0f);
          CVec3 normal;
          heightsController.GetHeight(pos.x, pos.y, 1, &pos.z, &normal);
          Render::Color color(0, 255, 0, 255);
          Render::DebugRenderer::DrawPoint3D(pos, 0.1f, color, true);
          Render::DebugRenderer::DrawLine3D(pos, pos + normal * scale, color, color, true);
        }
      }
    }

    for (int y = 0, h = pTerrain->GetHeightManager().GetHeights().GetSizeY(); y < h; y+=2)
    {
      for (int x = 0, w = pTerrain->GetHeightManager().GetHeights().GetSizeX(); x < w; x+=2)
      {
        CVec3 pos( (x + 0.5f) * tileSize, (y + 0.5f) * tileSize, 0.0f );
        heightsController.GetHeight(pos.x, pos.y, 1, &pos.z, 0 );
        Render::Color color(255, 255, 255, 255);
        //Render::DebugRenderer::DrawLine3D(pos - V3_AXIS_X * scale, pos + V3_AXIS_X * scale, color, color, true);
        //Render::DebugRenderer::DrawLine3D(pos - V3_AXIS_Y * scale, pos + V3_AXIS_Y * scale, color, color, true);
        //Render::DebugRenderer::DrawLine3D(pos - V3_AXIS_Z * scale, pos + V3_AXIS_Z * scale, color, color, true);
        Render::DebugRenderer::DrawPoint3D(pos, 0.03f, color, true);
      }
    }

  }

}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Scene::Draw()
{
	DrawToTexture( 0 );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Scene::DrawToTexture( Render::Texture2D *pTexture )
{
  Render::DebugRender debugRender;
	pCollisionMap->DebugRender( &debugRender );

	NI_ASSERT( pTexture == 0, "RenderSceneToTexture is not supported for now!" ); 
	Render::Interface::Get()->RegisterSceneForRendering( GetRenderScene() );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Scene::CreateTerrain( nstl::string const& dbTerrainName )
{
  NDb::Ptr<NDb::Terrain> pDBTerrain = NDb::Get<NDb::Terrain>(NDb::DBID(dbTerrainName));

  if (pTerrain && Get(voxelGrid))
  {
    NI_PROFILE_BLOCK( "RemoveToVoxelGridFunc" );
    RemoveToVoxelGridFunc f(Get(voxelGrid));
    pTerrain->ForAllElements(f);
  }

  CObj<Terrain::Terrain> pOldTerrain = pTerrain;

  // creating in editor
	pTerrain = new Terrain::Terrain(true);
	pTerrain->CreateTerrain( pDBTerrain );
	heightsController.AddTerrainToLayer( 0, pTerrain );
  
  if (IsValid(pOldTerrain))
  {
    pTerrain->GetGeometryManager().CopySubscribers(pOldTerrain->GetGeometryManager());
  }

  Render::AABB aabb(0.5f * GetGridConstants().worldSize, 0.5f * GetGridConstants().worldSize);
  ResetVoxelGrid(aabb);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Scene::LoadTerrain( const NDb::Terrain* pDBTerrain )
{
	NI_PROFILE_FUNCTION

  if (pTerrain && Get(voxelGrid))
  {
    NI_PROFILE_BLOCK( "RemoveToVoxelGridFunc" );
    RemoveToVoxelGridFunc f(Get(voxelGrid));
    pTerrain->ForAllElements(f);
  }

  // creating in game
	pTerrain = new Terrain::Terrain( !name.empty() );
	pTerrain->LoadTerrain( pDBTerrain );
	heightsController.AddTerrainToLayer( 0, pTerrain );

  const Render::AABB& terrainAABB = pTerrain->GetElementManager().GetWorldAABB();
  zMin = terrainAABB.center.z - terrainAABB.halfSize.z;

  sceneConstants.worldSize = GetTerrain()->GetGridConstants().worldSize.AsVec2D();

  ResetVoxelGrid();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Scene::OnLightingEnvironmentChangedD( const NDb::DBID& dbid )
{
	using namespace Render;

  CalculateLightingConstants(lightEnvironmentD.GetPtr(), sceneConstantsD);

  sceneConstantsD.nightFraction = 0.f;

  UpdateLightEnvironment(true);
  UpdateSceneConstants();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Scene::OnLightingEnvironmentChangedN(const NDb::DBID& dbid)
{
  using namespace Render;

  CalculateLightingConstants(lightEnvironmentN.GetPtr(), sceneConstantsN);

  sceneConstantsN.nightFraction = 1.f;

  UpdateLightEnvironment(true);
  UpdateSceneConstants();
}

void Scene::CalculateLightingConstants(const NDb::LightEnvironment* const lightEnvironment, Render::SceneConstants& sc)
{
  using namespace Render;

  if ( lightEnvironment )
  {
    // Make shader constants for environment lighting
    if (lightEnvironment->lightingCubeMapSHCoeffs.size() < 3*9)
    {
      SHCoeffs c1, c2;
      SHShaderConstants envLighting2;
      CVec3 dir;

      ConvertDirection(lightEnvironment->Light1Direction, dir);
      EvaluateSHCoeffsForDirLight(lightEnvironment->Light1DiffuseColor, CVec3(-dir.x, -dir.y, -dir.z), c1);
      ConvertSHCoeffs2ShaderConstants(c1, sc.envLighting);

      ConvertDirection(lightEnvironment->Light2Direction, dir);
      EvaluateSHCoeffsForDirLight(lightEnvironment->Light2DiffuseColor, CVec3(-dir.x, -dir.y, -dir.z), c2);
      ConvertSHCoeffs2ShaderConstants(c2, envLighting2);

      sc.envLighting.Add( envLighting2 );
    }
    else
    {
      const SHCoeffs *pCoeffs = reinterpret_cast<SHCoeffs const*>(&(lightEnvironment->lightingCubeMapSHCoeffs[0]));
      ConvertSHCoeffs2ShaderConstants(*pCoeffs, sc.envLighting);
    }

    // Update scene constants
    ConvertDirection(lightEnvironment->Light1Direction, sc.light1Direction);
    ConvertDirection(lightEnvironment->Light2Direction, sc.light2Direction);
    ConvertDirection(lightEnvironment->shadowDirection, sc.shadowDirection);

    sc.ambientColor  = lightEnvironment->AmbientColor;
    sc.diffuse1Color = lightEnvironment->Light1DiffuseColor;
    sc.diffuse2Color = lightEnvironment->Light2DiffuseColor;
    sc.minBakedColor = lightEnvironment->minBakedColor;
    sc.maxBakedColor = lightEnvironment->maxBakedColor;

    sc.pEnvCubeMap = NULL;

    if( IsValid(lightEnvironment->environmentCubeMap))
    {
      if( lightEnvironment->environmentCubeMap->textureFileName.size() )
        sc.pEnvCubeMap = Render::LoadCubeTextureFromFileRef(lightEnvironment->environmentCubeMap->textureFileName);
    }
  }
  else if ( GetRenderer() )
  {
    sc.envLighting.InitAsConstant(1.0f, 1.0f, 1.0f);
    sc.light1Direction = CVec4(0.0f, 0.0f, -1.0f, 0.f);
    sc.light2Direction = CVec4(1.0f, 0.0f, 0.0f, 0.f);
    sc.shadowDirection = CVec4(0.0f, 0.0f, -1.0f, 0.f);

    sc.ambientColor  = Render::HDRColor(1.0f, 1.0f, 1.0f, 1.0f);
    sc.diffuse1Color = Render::HDRColor(0.0f, 0.0f, 0.0f, 1.0f);
    sc.diffuse2Color = Render::HDRColor(0.0f, 0.0f, 0.0f, 1.0f);

    sc.pEnvCubeMap = NULL;
  }
}

void Scene::UpdateLightEnvironment(const bool reset)
{
  if (RENDER_DISABLED)
    return;

  using namespace Render;

  const bool dayLightingPresent = IsValid(lightEnvironmentD);
  const bool nightLightingPresent = IsValid(lightEnvironmentN);

  if (dayLightingPresent && nightLightingPresent)
  {
    ShadowManager::Params smParamsD;
    ShadowManager::Params smParamsN;

    smParamsD.FromLightEnvironment(lightEnvironmentD);
    smParamsN.FromLightEnvironment(lightEnvironmentN);

    ShadowManager::Params smParams;

    smParams.FromBlend(smParamsD, smParamsN, sceneConstants.nightFraction);

    if (reset)
    {
      ShadowManager::Term();
      ShadowManager::Init(smParams);
    }
    else
    {
      if (!ShadowManager::Get())
      {
        ShadowManager::Init(smParams);
      }
      else
      {
        ShadowManager::Get()->SetRuntimeParams(smParams);
      }
    }

    const float waterOscillationSpeedFactor =
      Lerp(lightEnvironmentD->WaterOscillationSpeedFactor, lightEnvironmentN->WaterOscillationSpeedFactor, sceneConstants.nightFraction);

    Render::HDRColor waterReflColor0;
    Render::HDRColor waterReflColor1;

    waterReflColor0.Lerp(lightEnvironmentD->WaterReflColor0, lightEnvironmentN->WaterReflColor0, sceneConstants.nightFraction);
    waterReflColor1.Lerp(lightEnvironmentD->WaterReflColor1, lightEnvironmentN->WaterReflColor1, sceneConstants.nightFraction);

    WaterManager::SetAnimationSpeedFactor(waterOscillationSpeedFactor);
    WaterManager::SetReflectedColors(waterReflColor0, waterReflColor1);
  }
  else if (dayLightingPresent || nightLightingPresent)
  {
    const NDb::LightEnvironment* const lenv = dayLightingPresent
      ? lightEnvironmentD.GetPtr()
      : lightEnvironmentN.GetPtr();

    if (reset)
    {
      ShadowManager::Term();
      ShadowManager::Init(lenv);
    }
    else
    {
      if (!ShadowManager::Get())
      {
        ShadowManager::Init(lenv);
      }
      else
      {
        ShadowManager::Params smParams;

        smParams.FromLightEnvironment(lenv);

        ShadowManager::Get()->SetRuntimeParams(smParams);
      }
    }

    WaterManager::SetAnimationSpeedFactor(lenv->WaterOscillationSpeedFactor);
    WaterManager::SetReflectedColors(lenv->WaterReflColor0, lenv->WaterReflColor1);
  }
  else
  {
    if (reset)
    {
      ShadowManager::Term();
      ShadowManager::Init();
    }
    else
    {
      /* placeholder */
    }

    WaterManager::SetAnimationSpeedFactor(1.f);
  }
}

void Scene::UpdateSceneConstants()
{
  struct Local
  {
    static inline void LerpSHShaderConstants(Render::SHShaderConstants& target, const Render::SHShaderConstants& lhs, const Render::SHShaderConstants& rhs, const float t)
    {
      for (int i = 0; i < 3; ++i)
      {
        target.linearAndConstant[i].Lerp(t, lhs.linearAndConstant[i], rhs.linearAndConstant[i]);
      }

      for (int i = 0; i < 3; ++i)
      {
        target.quadratic[i].Lerp(t, lhs.quadratic[i], rhs.quadratic[i]);
      }

      {
        target.quadraticRGB.Lerp(t, lhs.quadraticRGB, rhs.quadraticRGB);
      }
    }

    static inline void ColorMin(Render::HDRColor& target, const Render::HDRColor& lhs, const Render::HDRColor& rhs)
    {
      target.R = Min(lhs.R, rhs.R);
      target.G = Min(lhs.G, rhs.G);
      target.B = Min(lhs.B, rhs.B);
      target.A = Min(lhs.A, rhs.A);
    }

    static inline void ColorMax(Render::HDRColor& target, const Render::HDRColor& lhs, const Render::HDRColor& rhs)
    {
      target.R = Max(lhs.R, rhs.R);
      target.G = Max(lhs.G, rhs.G);
      target.B = Max(lhs.B, rhs.B);
      target.A = Max(lhs.A, rhs.A);
    }
  };

  const bool dayLightingPresent = IsValid(lightEnvironmentD);
  const bool nightLightingPresent = IsValid(lightEnvironmentN);

  if (dayLightingPresent && nightLightingPresent)
  {
    Local::LerpSHShaderConstants(sceneConstants.envLighting, sceneConstantsD.envLighting, sceneConstantsN.envLighting, sceneConstants.nightFraction);

    sceneConstants.light1Direction.Lerp(sceneConstants.nightFraction, sceneConstantsD.light1Direction, sceneConstantsN.light1Direction);
    sceneConstants.light2Direction.Lerp(sceneConstants.nightFraction, sceneConstantsD.light2Direction, sceneConstantsN.light2Direction);
    sceneConstants.shadowDirection.Lerp(sceneConstants.nightFraction, sceneConstantsD.shadowDirection, sceneConstantsN.shadowDirection);

    sceneConstants.ambientColor.Lerp(sceneConstantsD.ambientColor, sceneConstantsN.ambientColor, sceneConstants.nightFraction);
    sceneConstants.diffuse1Color.Lerp(sceneConstantsD.diffuse1Color, sceneConstantsN.diffuse1Color, sceneConstants.nightFraction);
    sceneConstants.diffuse2Color.Lerp(sceneConstantsD.diffuse2Color, sceneConstantsN.diffuse2Color, sceneConstants.nightFraction);

    // TODO: lerp?
    Local::ColorMin(sceneConstants.minBakedColor, sceneConstantsD.minBakedColor, sceneConstantsN.minBakedColor);
    Local::ColorMax(sceneConstants.maxBakedColor, sceneConstantsD.maxBakedColor, sceneConstantsN.maxBakedColor);

    // TODO: ?
    sceneConstants.pEnvCubeMap = sceneConstantsD.pEnvCubeMap;
  }
  else if (dayLightingPresent || nightLightingPresent)
  {
    const Render::SceneConstants& sc = dayLightingPresent
      ? sceneConstantsD
      : sceneConstantsN;

    sceneConstants.envLighting = sc.envLighting;

    sceneConstants.light1Direction = sc.light1Direction;
    sceneConstants.light2Direction = sc.light2Direction;
    sceneConstants.shadowDirection = sc.shadowDirection;

    sceneConstants.ambientColor = sc.ambientColor;
    sceneConstants.diffuse1Color = sc.diffuse1Color;
    sceneConstants.diffuse2Color = sc.diffuse2Color;

    sceneConstants.minBakedColor = sc.minBakedColor;
    sceneConstants.maxBakedColor = sc.maxBakedColor;

    // TODO: ?
    sceneConstants.pEnvCubeMap = sceneConstantsD.pEnvCubeMap;
  }
  else
  {
    sceneConstants.envLighting.InitAsConstant(1.0f, 1.0f, 1.0f);

    sceneConstants.light1Direction = CVec4(0.0f, 0.0f, -1.0f, 0.f);
    sceneConstants.light2Direction = CVec4(1.0f, 0.0f, 0.0f, 0.f);
    sceneConstants.shadowDirection = CVec4(0.0f, 0.0f, -1.0f, 0.f);

    sceneConstants.ambientColor  = Render::HDRColor(1.0f, 1.0f, 1.0f, 1.0f);
    sceneConstants.diffuse1Color = Render::HDRColor(0.0f, 0.0f, 0.0f, 1.0f);
    sceneConstants.diffuse2Color = Render::HDRColor(0.0f, 0.0f, 0.0f, 1.0f);

    sceneConstants.pEnvCubeMap = NULL;
  }
}

void Scene::LoadAdvMapLightEnvironment(const NDb::LightEnvironment* advMapLightEnvironment, const NDb::ELightEnvironment selector)
{
  NI_PROFILE_FUNCTION

  // TODO: ensure changed?

  switch (selector)
  {
  case NDb::LIGHTENVIRONMENT_DAY:
    lightEnvironmentD = advMapLightEnvironment;
    break;
  case NDb::LIGHTENVIRONMENT_NIGHT:
    lightEnvironmentN = advMapLightEnvironment;
    break;
  default:
    NI_ALWAYS_ASSERT("Invalid light environment selector!");
    break;
  }

  if (RENDER_DISABLED)
    return;

  switch (selector)
  {
  case NDb::LIGHTENVIRONMENT_DAY:
    OnLightingEnvironmentChangedD(NDb::DBID());
    break;
  case NDb::LIGHTENVIRONMENT_NIGHT:
    OnLightingEnvironmentChangedN(NDb::DBID());
    break;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Scene::LoadAdvMapSoundEnvironment( const NDb::SoundEnvironment* pAdvMapSoundEnvironment )
{
  soundEnvironment = pAdvMapSoundEnvironment;
	if( IsValid(soundEnvironment) )
	{
//  			NSoundScene::SetMinMaxDistance( NSoundScene::SOUNDCATEGORY_AMBIENT, pAdvMapSoundEnvironment->minDistanceForBuilding, pAdvMapSoundEnvironment->maxDistanceForBuilding);
//  			NSoundScene::SetMinMaxDistance( NSoundScene::SOUNDCATEGORY_EFFECT, pAdvMapSoundEnvironment->minDistanceForEffect, pAdvMapSoundEnvironment->maxDistanceForEffect);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Scene::ForAllObjects(IObjectFunctor &func)
{
  voxelGrid->process(func);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Scene::ForAllObjectsInCamera(IObjectFunctor &func, bool bNewProcess)
{
  // wrap functor into another functor that implements per-object culling with frustum
	VoxelGridObj::ProcessByFrustumProc<IObjectFunctor> f(*pCameraFrustum, func);
	voxelGrid->process(f, frustumAABB, bNewProcess);
}

void Scene::ForAllObjectsInFrustum(IObjectFunctor &func, Render::ConvexVolume const &frustum, bool bNewProcess)
{
	// wrap functor into another functor that implements per-object culling with frustum
	VoxelGridObj::ProcessByFrustumProc<IObjectFunctor> f(frustum, func);
	voxelGrid->process(f, frustumAABB, bNewProcess);
}

void Scene::ForAllObjectsInBBox(IObjectFunctor &func, const Render::AABB& aabb, bool bNewProcess)
{
  voxelGrid->process(func, aabb, bNewProcess);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float Scene::GetCameraRod() const
{
	const ICamera* pCamera = GetCamera();
  NI_VERIFY( IsValid( pCamera ), "Invalid camera!", return 1.f; );

	SCameraPosition position;
	pCamera->GetPosition( &position );
	return position.fRod;
}

void Scene::SetNightFraction(const float value)
{
  sceneConstants.nightFraction = Clamp(value, 0.f, 1.f);

  const bool hasNightLightingSupport =
    IsValid(lightEnvironmentD) &&
    IsValid(lightEnvironmentN);

  if (!hasNightLightingSupport)
    return;

  UpdateLightEnvironment(false);
  UpdateSceneConstants();
}

void Scene::SetNightSpecularReduction(const float value)
{
  sceneConstants.nightSpecularReduction = Clamp(value, 0.f, 1.f);
}

void Scene::SetCulledScreenSize( float size )
{
	culledscreensize = size;
}

void Scene::ResetVoxelGrid()
{
  NI_PROFILE_FUNCTION

  Render::AABB worldBBox(CVec3(VNULL3), CVec3(320.0, 320.0, 10.0));
  
  if (pTerrain)
  {
    // build AABB for terrain
    BuildAABBFunc f;
    pTerrain->ForAllElements(f);
    worldBBox = f.GetAABB();
  }

  ResetVoxelGrid(worldBBox);
}

void Scene::ResetVoxelGrid(Render::AABB const &worldBBox)
{
  NI_PROFILE_FUNCTION

  Render::AABB aabb(worldBBox);

  int nVoxelsX = (int)Round(2.0 * aabb.halfSize.x / voxelSizeX);
  int nVoxelsY = (int)Round(2.0 * aabb.halfSize.y / voxelSizeY);

  NI_ASSERT(unsigned(nVoxelsX) < SHRT_MAX && unsigned(nVoxelsY) < SHRT_MAX, "Wrong worldBBox");

  if (nVoxelsX == 0)
  {
    nVoxelsX = 1;
    aabb.halfSize.x = 0.5 * voxelSizeX;
  }

  if (nVoxelsY == 0)
  {
    nVoxelsY = 1;
    aabb.halfSize.y = 0.5 * voxelSizeY;
  }

  Reset(voxelGrid, new CollectionVG<RenderableSceneObj>(aabb, nVoxelsX, nVoxelsY, nVoxelsX * nVoxelsY));

  // add all terrain elements to new voxel grid
  if (pTerrain)
  {
    AddToVoxelGridFunc f(Get(voxelGrid));
      pTerrain->ForAllElements(f);
  }

  // add all objects to new voxel grid
  for (int priority = 0; priority < UPDATEPRIORITY_COUNT; ++priority)
  {
    for (ring::Range<SceneObjectBase::Ring> it( objectsRings[priority] ); it; ++it)
    {
      voxelGrid->add(&(*it));
    }
  }
}
void Scene::InitSHGrid(NDb::BakedLighting const &initParams)
{
  NI_PROFILE_FUNCTION

  shGrid.Init(initParams);
}

void Scene::SaveSceneSH()
{
  shGrid.Save();
}

void Scene::DebugRenderSHProbes()
{
  shGrid.DebugRender();
}

void Scene::CalculateSH( const CVec2 &pos, Render::SHShaderConstants &shConsts )
{
  shGrid.CalculateSH(pos, shConsts);
}

SceneObjectBase* Scene::AddSceneObject( SceneObjectBase* pSceneObject, UpdatePriority priority /*= UPDATEPRIORITY_NORMAL*/ )
{
  if(!RENDER_DISABLED) NI_ASSERT(pSceneObject->GetWorldAABB().IsValid(), NStr::StrFmt("Scene object '%s' has invalid AABB while adding to scene", pSceneObject->FormatDescription() ) );
	NI_VERIFY(!pSceneObject->IsInScene(), NStr::StrFmt("Scene object '%s' is already in scene", pSceneObject->FormatDescription() ), return pSceneObject; );

	objectsRings[priority].addLast( pSceneObject );
  voxelGrid->add(pSceneObject);
  return pSceneObject;
}

void Scene::SceneObjectRenderEnable( SceneObjectBase* pSceneObject, bool bEnable )
{
  NI_ASSERT(pSceneObject->GetScene() == this, "Scene object doesn't belong to this scene");
  if (bEnable)
  {
    NI_ASSERT(pSceneObject->getVoxelGrid() == NULL, "Scene object is already enabled for rendering");
    voxelGrid->add(pSceneObject);
  }
  else
  {
    NI_ASSERT(pSceneObject->getVoxelGrid() == Get(voxelGrid), "Trying to disable rendering twice");
    voxelGrid->remove(pSceneObject);
  }
}

void Scene::AddCollisionObjectToLayer( int layer, CollisionHull* hull )
{
  heightsController.AddObjectToLayer( layer, hull );
}

void Scene::SaveObjectLayer( int layer, const nstl::string& filename )
{
  heightsController.SaveObjectLayer( layer, filename );
}

void Scene::ClearHeightMapLayer( int layer )
{
  heightsController.ClearHeightMapLayer( layer );
}

void Scene::LoadObjectLayer( int layer, const nstl::string& filename )
{
  NI_PROFILE_FUNCTION

  heightsController.LoadObjectLayer( layer, filename );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Scene::NeedDebugRender()
{
  return SceneObject::NeedDebugRender();
}

void Scene::ForAllSceneObjects( ISceneObjectFunctor* func )
{
  for (int priority = 0; priority < UPDATEPRIORITY_COUNT; ++priority)
  {
    for ( ring::Range<SceneObjectBase::Ring> it( objectsRings[priority] ); it; ++it )
    {
      SceneObjectBase *pObj = &(*it);
      (*func)( pObj );
    }
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
IScene* CreateScene()
{
	return new Scene();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EnableDrawingEntitiesWithoutVisual(bool enable)
{
	g_drawEntitiesWithoutVisual = enable;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Need2DrawEntitiesWithoutVisual()
{
	return g_drawEntitiesWithoutVisual;
}

IScene * GetSceneFromRenderableScene(IRenderableScene *pRS)
{
  return static_cast<Scene *>(pRS);
}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
REGISTER_DEV_VAR( "ui_draw_pick_point", g_bDrawPickPoint, STORAGE_NONE )
REGISTER_DEV_VAR( "draw_enitities_without_visual", g_drawEntitiesWithoutVisual, STORAGE_NONE )
REGISTER_DEV_VAR( "show_heights", g_DrawHeights, STORAGE_NONE);
REGISTER_DEV_VAR( "precache_resource", g_PrecacheResource, STORAGE_NONE);
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BASIC_REGISTER_CLASS( NScene::IScene )
REGISTER_SAVELOAD_CLASS_NM(Scene, NScene);
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
