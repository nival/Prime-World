#ifndef WORLD_H_92783BDF_32B9_4304_82F4
#define WORLD_H_92783BDF_32B9_4304_82F4

#include "System/Placement.h"

#include "Protocol.h"
#include "VoxelGrid.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace TownDebug
{
  const float TOWN_GROUND_Z = 18.2f; // [AZ] for debug only 
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace Location 
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace EIdSpace
{
  enum Enum
  {
    Player, // player object id 0 .. 65535
    Other,  // 65536 .. max int
  };

  const int FirstNonPlayerID = USHRT_MAX + 1;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class WorldIDGenerator
{
public:
  WorldIDGenerator() : 
    nextPlayerID(USHRT_MAX) 
  {
    for ( int i = 0; i <= USHRT_MAX; ++i )
    {
      freePlayerID[USHRT_MAX - i] = i;
    }
  }

  Protocol::ObjectID  GetNextPlayerID() 
  {
    if ( nextPlayerID == -1 )
      return -1;

    int _nextID = freePlayerID[nextPlayerID];
    nextPlayerID--;
    return _nextID;
  }

  void ReleaseID( Protocol::ObjectID _objectID ) 
  { 
    nextPlayerID++;

    NI_VERIFY( nextPlayerID < EIdSpace::FirstNonPlayerID, "Player removement is inconsistent", return );

    freePlayerID[nextPlayerID] = _objectID;    
  }

private:
  Protocol::ObjectID  nextPlayerID;
  int freePlayerID[EIdSpace::FirstNonPlayerID];
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class GameObject;

class World : public CObjectBase
{
	OBJECT_METHODS( 0x9D628B81, World );

public:

  World();
	virtual ~World();

  typedef nstl::map<Protocol::ObjectID, CObj<GameObject>> Objects;

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class _GameObject> _GameObject* CreateObjectInSpace( EIdSpace::Enum _spaceID );
	template <class _GameObject> _GameObject* CreateObjectWithID( Protocol::ObjectID objectID );

  void SetIDGenerator( WorldIDGenerator* _idGenerator );

	void RemoveObject( Protocol::ObjectID objectID );
	GameObject* GetObjectById( Protocol::ObjectID id );
  const Objects& GetWorldObjects() { return gameObjects; }

  void SetObjectPassive( Protocol::ObjectID objectID, bool passive );

  const Placement& GetSpawnPlacement() const { return spawnPlacement; }
  const Placement& GetWorldPlacement() const { return worldPlacement; }

  void GetWorldBounds( CVec3& _base, float _size ) const;

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	bool Init();
  void Step( Protocol::Time deltaTime, Protocol::AbsoluteTime currentHPTime );

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  VoxelGrid& GetVoxelGrid() { return voxelGrid; }

private:

  Protocol::ObjectID nextID;
  Objects gameObjects; 
  Objects activeGameObjects; 

  AutoPtr<WorldIDGenerator> idGenerator;
  CPtr<GameObject> playerObjects[EIdSpace::FirstNonPlayerID]; 

  VoxelGrid voxelGrid;

  Placement spawnPlacement;
  Placement worldPlacement; // $TMP [AZ]
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <class _GameObject>  
inline _GameObject* World::CreateObjectInSpace( EIdSpace::Enum _spaceID )
{
	_GameObject* pNewObject = new _GameObject();

  int _nextID = Protocol::invalidObjectId;

  if ( idGenerator )
  {
    if ( _spaceID == EIdSpace::Player )
    {
      _nextID = idGenerator->GetNextPlayerID();

      if ( _nextID == -1 )
        return 0;

      playerObjects[_nextID] = pNewObject;
    }
    else
    {
      _nextID = nextID;
      nextID++;
    }
  }
  else
  {
    _nextID = nextID;
    nextID++;
  }

  pNewObject->SetWorldAndID( this, _nextID );

  gameObjects.insert( make_pair( _nextID , pNewObject ) );

	return pNewObject;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <class _GameObject>
inline _GameObject* World::CreateObjectWithID(Protocol::ObjectID objectID)
{
	_GameObject* pNewObject = new _GameObject();

	NI_ASSERT( gameObjects.find(objectID) == gameObjects.end(), "Try to insert Object with existing ID." );

  if ( objectID < EIdSpace::FirstNonPlayerID )
    playerObjects[objectID] = pNewObject;

  gameObjects.insert( make_pair( objectID, pNewObject) );

	pNewObject->SetWorldAndID( this, objectID );

	return pNewObject;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

} //namespace Location

#endif //#define WORLD_H_92783BDF_32B9_4304_82F4