#include "stdafx.h"
#include "SceneStub.h"

#include "../Scene/VertexColorManager.h"

namespace NScene
{
  void MeshVertexColorsManager::Load( const string& fileName )
  {
  }
}

namespace AuditScene
{

NScene::IScene* Scene::Create()
{
  return new Scene();
}

Terrain::GridConstants const& Scene::GetGridConstants() const
{
  return pTerrain->GetGridConstants();
}

void Scene::Init( const char* _name, int _floorsCount, const CVec3& _floorBase, float _floorSize )
{
  name = nstl::string(_name);
}

void Scene::LoadTerrain( const NDb::Terrain* pDBTerrain )
{
  pTerrain = new Terrain::Terrain(false);
  pTerrain->LoadTerrain( pDBTerrain );
}

void Scene::LoadAdvMapLightEnvironment( const NDb::LightEnvironment* ) {
}

Terrain::Terrain* Scene::GetTerrain() const {
  return pTerrain;
}

const string& Scene::GetName() const {
  NI_ALWAYS_ASSERT("Must not be called!");
  return name;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

void Scene::CreateTerrain( nstl::string const& dbTerrainName )
{
  NI_ALWAYS_ASSERT("Must not be called!");
}

int Scene::GetActiveFloor() const {
  NI_ALWAYS_ASSERT("Must not be called!");
  return 0;
}

bool Scene::SetActiveFloor( int floor ) {
  NI_ALWAYS_ASSERT("Must not be called!");
  return false;
}

NScene::Time Scene::GetRenderTime() {
  NI_ALWAYS_ASSERT("Must not be called!");
  return NScene::Time(0);
}

void Scene::LoadAdvMapSoundEnvironment( const NDb::SoundEnvironment* ) {
  NI_ALWAYS_ASSERT("Must not be called!");
}

const NDb::LightEnvironment* Scene::GetAdvMapLightEnvironment() const{
  NI_ALWAYS_ASSERT("Must not be called!");
  return NULL;
}

void Scene::LoadAuxLightEnvironment( const NDb::LightEnvironment* advMapLightEnvironment ) {
  NI_ALWAYS_ASSERT("Must not be called!");
}

NScene::CollisionMap* Scene::GetCollisionMap() const {
  NI_ALWAYS_ASSERT("Must not be called!");
  return NULL;
}

const NScene::HeightsController& Scene::GetHeightsController() const {
  NI_ALWAYS_ASSERT("Must not be called!");
  static NScene::HeightsController controller;
  return controller;
}

NScene::MeshVertexColorsManager* Scene::GetMeshVertexColorsManager() const {
	return 0;
}

void Scene::CreateMeshVertexColorsManager(bool)
{
}



void Scene::UpdateHeightsController() {
  NI_ALWAYS_ASSERT("Must not be called!");
}

void Scene::SaveObjectLayer( int /*layer*/, const nstl::string& /*filename*/ ){
	NI_ALWAYS_ASSERT("Must not be called!");
}

void Scene::LoadObjectLayer( int /*layer*/, const nstl::string& /*filename*/ ){
	NI_ALWAYS_ASSERT("Must not be called!");
}

void Scene::AddCollisionObjectToLayer( int /*layer*/, NScene::CollisionHull* /*hull*/ ){
	NI_ALWAYS_ASSERT("Must not be called!");
}

NScene::SceneObjectBase* Scene::AddSceneObject( NScene::SceneObjectBase* pSceneObject ) {
  NI_ALWAYS_ASSERT("Must not be called!");
  return NULL;
}

void Scene::RemoveObject( NScene::SceneObjectBase* pSceneObject ) {
  NI_ALWAYS_ASSERT("Must not be called!");
}

Terrain::TerrainElementId Scene::AddTerrainElement( const NDb::TerrainElementInstance& descriptor, const string& fileName ) {
  NI_ALWAYS_ASSERT("Must not be called!");
  return Terrain::TerrainElementId(0);
}

bool Scene::DeleteTerrainElement( Terrain::TerrainElementId ) {
  NI_ALWAYS_ASSERT("Must not be called!");
  return false;
}

int Scene::Pick( NScene::PickResult *, const CVec2& ) {
  NI_ALWAYS_ASSERT("Must not be called!");
  return 0;
}

int Scene::Pick( NScene::PickResult *, const CVec3&, const CVec3& ) {
  NI_ALWAYS_ASSERT("Must not be called!");
  return 0;
}

int Scene::PickObjects( NScene::PickResult *, const CVec3&, const CVec3& ) {
  NI_ALWAYS_ASSERT("Must not be called!");
  return 0;
}

bool Scene::PickTerrain( CVec3 &, const CVec3&, const CVec3& ) {
  NI_ALWAYS_ASSERT("Must not be called!");
  return false;
}

bool Scene::PickRect( NScene::CollisionHull*, int, int, CTRect<float>* ) {
  NI_ALWAYS_ASSERT("Must not be called!");
  return false;
}

NScene::ICamera* Scene::GetCamera() {
  NI_ALWAYS_ASSERT("Must not be called!");
  return NULL;
}
const NScene::ICamera* Scene::GetCamera() const {
  NI_ALWAYS_ASSERT("Must not be called!");
  return NULL;
}

NScene::CameraControllersContainer* Scene::GetCameraControllers() {
  NI_ALWAYS_ASSERT("Must not be called!");
  return NULL;
}

void Scene::Update( NScene::Time, NScene::Time, bool ) {
  NI_ALWAYS_ASSERT("Must not be called!");
}

void Scene::Draw() {
  NI_ALWAYS_ASSERT("Must not be called!");
}

void Scene::DrawToTexture( Render::Texture2D* ) {
  NI_ALWAYS_ASSERT("Must not be called!");
}

void Scene::CalculateSH( const CVec2&, Render::SHShaderConstants& ) {
  NI_ALWAYS_ASSERT("Must not be called!");
}

IRenderableScene* Scene::GetRenderScene() {
  NI_ALWAYS_ASSERT("Must not be called!");
  return NULL;
}

NScene::SHGrid &Scene::GetSHGrid()
{
  NI_ALWAYS_ASSERT("Basic method should not be called");
  NScene::SHGrid* pGrid = 0;
  return *pGrid;
}
void Scene::InitSHGrid(NDb::BakedLighting const &)
{
}

void Scene::SaveSceneSH()
{
  NI_ALWAYS_ASSERT("Basic method should not be called");
}
const Render::SceneConstants& Scene::GetSceneConstants()
{
	NI_ALWAYS_ASSERT("Basic method should not be called");
	return *((Render::SceneConstants*)0);
}

}


BASIC_REGISTER_CLASS( NScene::IScene )
