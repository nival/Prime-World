#pragma once
#include "Scene.h"
#include "CollisionMap.h"
#include "SHGrid.h"
#include "BitMap.h"

#include "../Render/DBRender.h"
#include "../Render/renderstates.h"
#include "../Render/renderer.h"
#include "../Render/sceneconstants.h"
#include "../Render/omnilight.h"
#include "../Terrain/TerrainGeometryManager.h"
#include "RenderableScene.h"

#include "../Terrain/Terrain.h"

#include "SceneObject.h"

namespace NWorld { struct Node; }
namespace Terrain { class TerrainElement; }

namespace NScene
{

class Scene: public IScene, public CObjectBase, public IRenderableScene
{
  OBJECT_METHODS(0xE5BDB40, Scene)

private:
	int nextUniqueID;
	Time currentTime;

	// Frustum & camera stuff
	CObj<ICamera>                    pCamera;
	CObj<CameraControllersContainer> pControllersContainer;
	FrustumIntersection              frustumIntersection;
	Render::AABB                     frustumAABB;
	ScopedPtr<Render::ConvexVolume>  pCameraFrustum;


	//CObj<IAIMap> pAIMap;
	CObj<CollisionMap> pCollisionMap;
	CObj<Terrain::Terrain> pTerrain;
	int floorsCount;
	int activeFloor;
  float zMin;

	ScopedPtr<MeshVertexColorsManager> pMeshVertexColorsManager;

	Render::SceneConstants  sceneConstants;

  Render::SceneConstants  sceneConstantsD; // for day lighting
  Render::SceneConstants  sceneConstantsN; // for night lighting

	SceneObjectBase::Ring objectsRings[UPDATEPRIORITY_COUNT];

  NDb::ChangeablePtr<NDb::LightEnvironment> lightEnvironmentD; // day
  NDb::ChangeablePtr<NDb::LightEnvironment> lightEnvironmentN; // night

  NDb::Ptr<NDb::SoundEnvironment> soundEnvironment;

	HeightsController heightsController;

  float accDelta;

	bool isFade;
	float fadeAlpha;
	string name;

	int updateCount;
	int objectsFullyUpdatedCount;

  AutoPtr<CollectionVG<RenderableSceneObj>>  voxelGrid;
  SHGrid shGrid;
  RECT  renderArea;
  
  ScopedPtr<BitMap> waterMap;

  SkipFrameSignal skipFrame;

  int stepLength;
  float stepLengthInSeconds;

  void OnLightingEnvironmentChangedD( const NDb::DBID& dbid );
  void OnLightingEnvironmentChangedN( const NDb::DBID& dbid );

  static void CalculateLightingConstants(const NDb::LightEnvironment* const lightEnvironment, Render::SceneConstants& sc);

  void UpdateLightEnvironment(const bool reset);
  void UpdateSceneConstants();

public:
	Scene();

	~Scene();
	void Init( const char* _name, int _floorsCount, const CVec3& _floorBase, float _floorSize, int _stepLength = DEFAULT_GAME_STEP_LENGTH );
  void ResetVoxelGrid(Render::AABB const &worldBBox);
  void ResetVoxelGrid();
	int GetActiveFloor() const
	{
		return activeFloor;
	}
	bool SetActiveFloor( int floor )
	{
		NI_VERIFY( floor > 0 && floor < floorsCount, "Floor index out of bounds", return false );
		activeFloor = floor;
		pCollisionMap->SetActiveFloor( GetActiveFloor() );

		//TODO update camera
		return true;
	}

	int GetUpdateCount() const { return updateCount; }

	Time GetRenderTime() 
	{ 
		return currentTime; 
	}
	const string & GetName() const {return name;}

	void CreateTerrain( nstl::string const& dbTerrainName );
	void LoadTerrain( const NDb::Terrain* );
	void CreateMeshVertexColorsManager(bool bEditor = false);

	void LoadAdvMapLightEnvironment( const NDb::LightEnvironment* advMapLightEnvironment )
  {
    LoadAdvMapLightEnvironment(advMapLightEnvironment, NDb::LIGHTENVIRONMENT_DAY);
  }
  void LoadAdvMapLightEnvironment( const NDb::LightEnvironment* advMapLightEnvironment, const NDb::ELightEnvironment selector );
	void LoadAdvMapSoundEnvironment( const NDb::SoundEnvironment* advMapSoundEnvironment );

	virtual CollisionMap* GetCollisionMap() const { return pCollisionMap; }
	virtual const IHeightsController& GetHeightsController() const { return heightsController; }
	virtual void UpdateHeightsController() { heightsController.Update(); }

	virtual Terrain::Terrain* GetTerrain() const { return pTerrain; }
	virtual Terrain::Terrain* GetRenderableTerrain() const { return pTerrain; }
	virtual Terrain::GridConstants const& GetGridConstants() const { return pTerrain->GetGridConstants(); }

	virtual MeshVertexColorsManager* GetMeshVertexColorsManager() const { return Get(pMeshVertexColorsManager); }

  virtual void SaveObjectLayer( int layer, const nstl::string& filename );
  virtual void LoadObjectLayer( int layer, const nstl::string& filename );
  void ClearHeightMapLayer( int layer );
  void AddCollisionObjectToLayer( int layer, CollisionHull* hull );
	SceneObjectBase* AddSceneObject( SceneObjectBase* pSceneObject, UpdatePriority priority = UPDATEPRIORITY_NORMAL);
	void RemoveObject( SceneObjectBase* pSceneObject );

  void SceneObjectRenderEnable( SceneObjectBase* pSceneObject, bool bEnable );

  const NDb::LightEnvironment* GetAdvMapLightEnvironment() const
  {
    return GetAdvMapLightEnvironment(NDb::LIGHTENVIRONMENT_DAY);
  }

  const NDb::LightEnvironment* GetAdvMapLightEnvironment(const NDb::ELightEnvironment selector) const
  {
    switch (selector)
    {
    case NDb::LIGHTENVIRONMENT_DAY:
      return lightEnvironmentD.GetPtr();
    case NDb::LIGHTENVIRONMENT_NIGHT:
      return lightEnvironmentN.GetPtr();
    }

    NI_ALWAYS_ASSERT("Invalid light environment selector!");
    return NULL;
  }

  Terrain::TerrainElementId AddTerrainElement( const NDb::TerrainElementInstance& descriptor, const string& fileName );
  bool DeleteTerrainElement( Terrain::TerrainElementId id );

  virtual void LoadWaterMap(nstl::string const& fileName);
  virtual void LoadWaterMap(BitMap* _waterMap);
  virtual bool IsPosInWater(CVec2 const &pos) const { if (Get(waterMap)) return waterMap->CheckPos(pos); return false; }

	// picks
	int Pick( PickResult *pIntersections, const CVec2& screenPos );
	int Pick( PickResult *pIntersections, const CVec3& origin, const CVec3& direction );
  int  PickObjects( PickResult *pIntersections, const CVec3& origin, const CVec3& direction );
  bool PickTerrain( CVec3 &pos, const CVec3& origin, const CVec3& direction );
	bool PickRect( CollisionHull* pHull, int w, int h, CTRect<float> *pRect );

  virtual void ConstrainRender(const RECT &_rect) { renderArea = _rect; }

	ICamera *GetCamera()  { return pCamera; }
	const ICamera *GetCamera() const { return pCamera; }
	CameraControllersContainer *GetCameraControllers() { return pControllersContainer; }

	virtual void Update( float /*deltaTime*/ ) {}

  void UpdateCamera(Time time, Time delta);
	void Update(Time time, Time delta, bool bIsPaused, bool isForcedUpdate = false );
	void Draw();
	void DrawToTexture( Render::Texture2D *pTexture );

  void InitSHGrid(NDb::BakedLighting const &initParams);
  SHGrid &GetSHGrid() { return shGrid; }
  void SaveSceneSH();
  void DebugRenderSHProbes();	
  virtual void CalculateSH( const CVec2 &pos, Render::SHShaderConstants &shConsts );

	virtual Render::SHShaderConstants const &GetEnvLighting() const { return sceneConstants.envLighting; }

	IRenderableScene* GetRenderScene() { return this; }
	const IRenderableScene* GetRenderScene() const { return this; }
	virtual float GetCameraRod() const;

  virtual int GetStepLength() const { return stepLength; }
  virtual float GetStepLengthInSeconds() const { return stepLengthInSeconds; }

  virtual void SetNightFraction(const float value);
  virtual void SetNightSpecularReduction(const float value);

	void AccountFullyUpdatedObject() { objectsFullyUpdatedCount++; }

	// ================================================================================
	// From IRenderableScene

	virtual void PrepareForRendering() {}

	virtual const Render::ConvexVolume& GetCameraFrustum() const { return *pCameraFrustum; }

	virtual const FrustumIntersection& GetCameraFrustumIntersection() const { return frustumIntersection; }

	virtual const Render::AABB& GetFrustumAABB() const { return frustumAABB; }

	virtual void ForAllObjects(IObjectFunctor &func);
	virtual void ForAllObjectsInCamera(IObjectFunctor &func, bool bNewProcess = true);
	virtual void ForAllObjectsInFrustum(IObjectFunctor &func, Render::ConvexVolume const &frustum, bool bNewProcess = true);
	virtual void ForAllObjectsInBBox(IObjectFunctor &func, const Render::AABB& aabb, bool bNewProcess = true);
  
  virtual void ForAllSceneObjects(ISceneObjectFunctor* func);

	virtual const Render::SceneConstants& GetSceneConstants()
	{
		return sceneConstants;
	}

  virtual const Render::SceneConstants& GetSceneConstants(const NDb::ELightEnvironment selector) const
  {
    switch (selector)
    {
    case NDb::LIGHTENVIRONMENT_DAY:
      return sceneConstantsD;
    case NDb::LIGHTENVIRONMENT_NIGHT:
      return sceneConstantsN;
    }

    NI_ALWAYS_ASSERT("Invalid light environment selector!");

    return sceneConstants;
  }

	void SetCulledScreenSize(float size);

  virtual bool NeedDebugRender();

  //virtual float GetExposure();
	//virtual float GetThresholdAdd();
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
