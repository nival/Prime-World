#pragma once

#include "../Render/SHCoeffs.h"
#include "../Scene/Scene.h"
#include "../Terrain/Terrain.h"
#include "../Scene/SHGrid.h"

namespace NScene
{
class CollisionHull;
}

namespace AuditScene
{

class Scene: public NScene::IScene, public CObjectBase
{
  OBJECT_METHODS(0xF640C40, Scene);
public:
  
  static IScene* Create();
  
  virtual void Init( const char* _name, int _floorsCount, const CVec3& _floorBase, float _floorSize );
  
  virtual int GetActiveFloor() const;
  virtual bool SetActiveFloor( int );

  virtual NScene::Time GetRenderTime();

  virtual void LoadTerrain( const NDb::Terrain* );
  virtual void CreateTerrain( nstl::string const& dbTerrainName );

  virtual void LoadAdvMapLightEnvironment( const NDb::LightEnvironment* );
  virtual void LoadAdvMapSoundEnvironment( const NDb::SoundEnvironment* );
  virtual const NDb::LightEnvironment *GetAdvMapLightEnvironment() const;

  virtual void LoadAuxLightEnvironment( const NDb::LightEnvironment* );

  virtual NScene::CollisionMap* GetCollisionMap() const;
  virtual const string & GetName() const;

  virtual const NScene::HeightsController& GetHeightsController() const;
  virtual void UpdateHeightsController();

  virtual Terrain::Terrain* GetTerrain() const;
  virtual Terrain::GridConstants const& GetGridConstants() const;

  virtual void CreateMeshVertexColorsManager(bool bEditor = false);
	virtual NScene::MeshVertexColorsManager* GetMeshVertexColorsManager() const;

	virtual void SaveObjectLayer( int layer, const nstl::string& filename );
	virtual void LoadObjectLayer( int layer, const nstl::string& filename );
	virtual void AddCollisionObjectToLayer( int layer, NScene::CollisionHull* hull );
  virtual NScene::SceneObjectBase* AddSceneObject( NScene::SceneObjectBase* );
  virtual void RemoveObject( NScene::SceneObjectBase* );

  virtual Terrain::TerrainElementId AddTerrainElement( const NDb::TerrainElementInstance& descriptor, const string& fileName );
  virtual bool DeleteTerrainElement( Terrain::TerrainElementId );

  virtual int Pick( NScene::PickResult *, const CVec2& );
  virtual int Pick( NScene::PickResult *, const CVec3&, const CVec3& );
  virtual int  PickObjects( NScene::PickResult *, const CVec3&, const CVec3& );
  virtual bool PickTerrain( CVec3&, const CVec3&, const CVec3& );
  virtual bool PickRect( NScene::CollisionHull*, int, int, CTRect<float>* );

  virtual NScene::ICamera *GetCamera();
  virtual const NScene::ICamera *GetCamera() const;
  virtual NScene::CameraControllersContainer *GetCameraControllers();

	virtual Render::SHShaderConstants const &GetEnvLighting() const { return shc; }

  virtual void Update( NScene::Time, NScene::Time, bool );
  virtual void Draw();
  virtual void DrawToTexture( Render::Texture2D* );

  virtual void CalculateSH( const CVec2 &pos, Render::SHShaderConstants &shConsts );
	virtual NScene::SHGrid &GetSHGrid();
  virtual void InitSHGrid(NDb::BakedLighting const &initParams);
  virtual void SaveSceneSH();
  virtual const Render::SceneConstants& GetSceneConstants();

  virtual IRenderableScene* GetRenderScene();
private:
  CObj<Terrain::Terrain> pTerrain;
	Render::SHShaderConstants shc;
  string name;
};

} //namespace AuditScene
