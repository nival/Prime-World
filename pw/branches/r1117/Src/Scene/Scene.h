#pragma once
#include "SceneTypes.h"
#include "CollisionMap.h"
#include "HeightsController.h"
//#include "../PF_GameLogic/DBAdvMap.h"
#include "Core/Scheduler.h" // For DEFAULT_GAME_STEP_LENGTH constant

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class IRenderableScene;
struct Matrix43;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NDb
{
	struct TerrainElementObject;
	struct TerrainElementInstance;
  struct TerrainGeometry;
	struct BaseVisualObject;
	struct Terrain;
	struct Effect;
	struct SoundEnvironment;
	struct DBSceneObject;
	struct DBSceneComponent;
	struct AttachedSceneComponent;
	struct DBAnimatedSceneComponent;
	struct DBStaticSceneComponent;
	struct DBParticleSceneComponent;
  struct DBSoundSceneComponent;
}
namespace Render
{
	class Color;
	class Texture2D;
	struct SHShaderConstants;
  struct SceneConstants;
}
namespace Terrain
{
	class TerrainGeometryManager;
	class TerrainLayerManager;
	class Terrain;
	struct GridConstants;
	typedef long TerrainElementId;
}

namespace NGameX
{
	class HeroSceneObject;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NScene
{
	_interface ICamera;
	class CameraControllersContainer;
	class SceneObjectBase;
	class EditorSceneObject;
	class CollisionMap;
	class CollisionGeometry;
  class SHGrid;
	class MeshVertexColorsManager;
  class BitMap;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	struct PickResult
	{
		Intersection intersections[32];
		int usedIntersections;
		CVec3 terrainIntersection;
		bool hasTerrainIntersection;
		int terrainIntersectionLayer; 
	};

  struct ISceneObjectFunctor
  {
    virtual void operator()(SceneObjectBase* so) = 0;
  };

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  enum UpdatePriority { UPDATEPRIORITY_HIGH, UPDATEPRIORITY_NORMAL, UPDATEPRIORITY_PRIESTESS, UPDATEPRIORITY_LOW, UPDATEPRIORITY_COUNT };
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_interface IScene: public IObjectBase
	{
    virtual void Init( const char* _name, int _floorsCount, const CVec3& _floorBase, float _floorSize, int _stepLength = DEFAULT_GAME_STEP_LENGTH ) = 0;
		virtual int GetActiveFloor() const = 0;
		virtual bool SetActiveFloor( int floor ) = 0;

		virtual Time GetRenderTime() = 0;

    virtual void CreateTerrain( nstl::string const& dbTerrainName ) = 0;
		virtual void LoadTerrain( const NDb::Terrain* ) = 0;
		virtual void LoadAdvMapLightEnvironment( const NDb::LightEnvironment* advMapLightEnvironment ) = 0;
    virtual void LoadAdvMapLightEnvironment( const NDb::LightEnvironment* advMapLightEnvironment, const NDb::ELightEnvironment selector ) = 0;
		virtual void LoadAdvMapSoundEnvironment( const NDb::SoundEnvironment* pAdvMapSoundEnvironment ) = 0;
		virtual const NDb::LightEnvironment *GetAdvMapLightEnvironment() const = 0;
    virtual const NDb::LightEnvironment *GetAdvMapLightEnvironment(const NDb::ELightEnvironment selector) const = 0;

    virtual void LoadWaterMap(nstl::string const& fileName) = 0;
    virtual void LoadWaterMap(BitMap* _waterMap) = 0;
    virtual bool IsPosInWater(CVec2 const &pos) const = 0;

		//virtual IAIMap* GetAIMap() const = 0;


		virtual CollisionMap* GetCollisionMap() const = 0;
		virtual const string & GetName() const = 0;

		virtual const IHeightsController& GetHeightsController() const = 0;
		virtual void UpdateHeightsController() = 0;

		virtual Terrain::Terrain* GetTerrain() const = 0;
		virtual Terrain::GridConstants const& GetGridConstants() const = 0;

		virtual void CreateMeshVertexColorsManager(bool bEditor = false) = 0;
		virtual MeshVertexColorsManager* GetMeshVertexColorsManager() const = 0;

    virtual void SaveObjectLayer( int layer, const nstl::string& filename ) = 0;
    virtual void LoadObjectLayer( int layer, const nstl::string& filename ) = 0;
    virtual void AddCollisionObjectToLayer( int layer, CollisionHull* hull ) = 0;
    virtual void ClearHeightMapLayer( int layer ) = 0;
		virtual SceneObjectBase* AddSceneObject( SceneObjectBase* pSceneObject, UpdatePriority priority = UPDATEPRIORITY_NORMAL ) = 0;
		virtual void RemoveObject( SceneObjectBase* pSceneObject ) = 0;

    virtual void SceneObjectRenderEnable( SceneObjectBase* pSceneObject, bool bEnable ) = 0;

    virtual Terrain::TerrainElementId AddTerrainElement( const NDb::TerrainElementInstance& descriptor, const string& fileName ) = 0;
    virtual bool DeleteTerrainElement( Terrain::TerrainElementId id ) = 0;

		virtual int Pick( PickResult *pIntersections, const CVec2& screenPos ) = 0;
		virtual int Pick( PickResult *pIntersections, const CVec3& origin, const CVec3& direction ) = 0;
		virtual int  PickObjects( PickResult *pIntersections, const CVec3& origin, const CVec3& direction ) = 0;
		virtual bool PickTerrain( CVec3 &pos, const CVec3& origin, const CVec3& direction ) = 0;
		virtual bool PickRect( CollisionHull* pHull, int w, int h, CTRect<float> *pRect ) = 0;

    virtual void ConstrainRender(const RECT &_rect) = 0;

		virtual ICamera *GetCamera() = 0;
		virtual const ICamera *GetCamera() const = 0;
		virtual CameraControllersContainer *GetCameraControllers() = 0;

    virtual void ForAllSceneObjects(ISceneObjectFunctor* func) = 0;

		virtual void Update( Time time, Time delta, bool bIsGamePaused, bool isForcedUpdate = false ) = 0;
		virtual void Draw() = 0;
		virtual void DrawToTexture( Render::Texture2D *pTexture ) = 0;

		virtual void CalculateSH( const CVec2 &pos, Render::SHShaderConstants &shConsts ) = 0;
    virtual SHGrid &GetSHGrid() = 0;
    virtual void InitSHGrid(NDb::BakedLighting const &initParams) = 0;
    virtual void SaveSceneSH() = 0;
    virtual const Render::SceneConstants& GetSceneConstants() = 0;

		virtual Render::SHShaderConstants const &GetEnvLighting() const = 0;

		virtual IRenderableScene* GetRenderScene() = 0;
		virtual const IRenderableScene* GetRenderScene() const = 0;

    virtual int GetStepLength() const = 0;
    virtual float GetStepLengthInSeconds() const = 0;

    virtual void SetNightFraction(const float value) = 0;
    virtual void SetNightSpecularReduction(const float value) = 0;
	};
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	IScene* CreateScene();
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void EnableDrawingEntitiesWithoutVisual(bool enable);
	bool Need2DrawEntitiesWithoutVisual();

	void ToggleShowLocators();
  IScene * GetSceneFromRenderableScene(IRenderableScene *pRS);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
