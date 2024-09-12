#include "stdafx.h"

#include "GameObject.h"
#include "StaticGameObject.h"
#include "World.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace {
  float TOWN_SIZE_MINX = 0.f;
  float TOWN_SIZE_MAXX = 1000.f;
  float TOWN_SIZE_MINY = 0.f;
  float TOWN_SIZE_MAXY = 1000.f;

  int TOWN_CELL_X = 16;
  int TOWN_CELL_Y = 16;

  REGISTER_VAR( "town_size_minx", TOWN_SIZE_MINX, STORAGE_GLOBAL );
  REGISTER_VAR( "town_size_maxx", TOWN_SIZE_MAXX, STORAGE_GLOBAL );
  REGISTER_VAR( "town_size_miny", TOWN_SIZE_MINY, STORAGE_GLOBAL );
  REGISTER_VAR( "town_size_maxy", TOWN_SIZE_MAXY, STORAGE_GLOBAL );

  REGISTER_VAR( "town_cell_x", TOWN_CELL_X, STORAGE_GLOBAL );
  REGISTER_VAR( "town_cell_y", TOWN_CELL_Y, STORAGE_GLOBAL );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace Location {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
World::World() : 
	nextID(EIdSpace::FirstNonPlayerID),
  spawnPlacement(NULLPLACEMENT),
  worldPlacement(NULLPLACEMENT),
  idGenerator(0)
{
  worldPlacement.scale = CVec3(4.f, 4.f, 4.f);
  voxelGrid.Setup( TOWN_SIZE_MINX, TOWN_SIZE_MAXX, TOWN_SIZE_MINY, TOWN_SIZE_MAXY, TOWN_CELL_X, TOWN_CELL_Y );

//  gameObjects.set_bucket_count( 12000 );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
World::~World()
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void World::GetWorldBounds( CVec3& _base, float _size ) const
{
  _base.x = TOWN_SIZE_MINX;
  _base.y = TOWN_SIZE_MINY;
  _base.z = TOWN_SIZE_MINX;

  _size = fabs( TOWN_SIZE_MAXX - TOWN_SIZE_MINX );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void World::SetIDGenerator( WorldIDGenerator* _idGenerator )
{
  Reset( idGenerator, _idGenerator );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void World::RemoveObject( Protocol::ObjectID objectID )
{
  if ( objectID < EIdSpace::FirstNonPlayerID )
  {
    if ( idGenerator )
      idGenerator->ReleaseID( objectID ); 

    playerObjects[objectID] = 0;
  }

	gameObjects.erase( objectID );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void World::SetObjectPassive( Protocol::ObjectID objectID, bool passive )
{
  Objects::iterator it = gameObjects.find( objectID );

  if ( it == gameObjects.end() )
    return;

  CPtr<GameObject> gameObject = it->second;

  if ( !IsValid( gameObject ) )
    return;

  gameObject->SetPassive( passive );

  if ( passive )
  {
    activeGameObjects.erase( objectID );
  }
  else
  {
    if ( IsValid( gameObject ) )
      activeGameObjects[ objectID ] = gameObject;
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
GameObject* World::GetObjectById( Protocol::ObjectID id )
{
	NI_VERIFY( id != Protocol::invalidObjectId, "Invalid id", return 0 );

  if ( id < EIdSpace::FirstNonPlayerID )
    return playerObjects[id];

	Objects::const_iterator it = gameObjects.find( id );
	NI_VERIFY( it != gameObjects.end(), NStr::StrFmt( "Try to get unregistered object, id: %d", id ), return 0 );

	return it->second;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool World::Init()
{
  return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void World::Step( Protocol::Time deltaTime, Protocol::AbsoluteTime currentHPTime )
{
  Objects::iterator it = activeGameObjects.begin();
  Objects::iterator last = activeGameObjects.end();

  nstl::set<int> goPassive;

  for (; it != last; ++it)
  {
    it->second->Step( deltaTime, currentHPTime );

    if ( it->second->IsPassive() )
      goPassive.insert( it->second->GetID() );
  }

  nstl::set<int>::iterator itD = goPassive.begin();
  nstl::set<int>::iterator lastD = goPassive.end();

  for (; itD != lastD; ++itD )
  {
    SetObjectPassive( *itD, true );
  }
}

} //namespace Location

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BASIC_REGISTER_CLASS( Location::World )	
