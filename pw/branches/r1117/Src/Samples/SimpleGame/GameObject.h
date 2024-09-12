#ifndef GAMEOBJECT_H_B4F7B77A_EEC9_4BC6
#define GAMEOBJECT_H_B4F7B77A_EEC9_4BC6

#include <RPC/RPC.h>
#include "Protocol.h"
#include "System/Placement.h"
#include "VoxelGrid.h"

namespace Location
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
_interface ITownClientForObject : public IObjectBase
{
  virtual void MovePlayerTo( const CVec3& _target, Protocol::ObjectID _pursuitID ) = 0;
  virtual void RegisterPlayer( byte cellX, byte cellY ) = 0;
  virtual const PoolElement& GetPlayerVoxel() const = 0;

  virtual Protocol::AbsoluteTime GetServerTime() const = 0;

  virtual float GetMinimalDistance( Protocol::ObjectID _first, Protocol::ObjectID _second ) = 0;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class World;

REMOTE class GameObject : public CObjectBase RPC_REFCOUNTED_OBJECT
{
  OBJECT_METHODS( 0x9D628B82, GameObject );

public:
  RPC_ID();

  GameObject();
    virtual ~GameObject();

    void SetWorldAndID( World* _world, Protocol::ObjectID _objectID );
    Protocol::ObjectID GetID() const { return objectID; }

  void SetConnectionToServer( ITownClientForObject* connection ) { connectionToServer = connection; }
  void SetPlayer( bool _isPlayer ) { isPlayer = _isPlayer; }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    const Placement& GetPlacement() const { return placement; }
    void SetPlacement( const Placement& _placement );
  void SetPosition( const CVec2& _pos, bool _register );

  int GetNeighbourCount() const { return neighbourCount; }
  void AddNeighbourCount( int count );

  REMOTE virtual void InitPlacement( const CVec2& _startPos, const CVec2& _targetPos, Protocol::AbsoluteTime _finishTime );

  virtual bool IsPassive() const { return isPassive; }
  virtual void SetPassive( bool _passive ) { isPassive = _passive; }

  float GetLinearVelocity() const { return linearVelocity; }

  const PoolElement& GetVoxelElement() const { return voxelGridElement; }

  const nstl::string& GetClientResource() const { return clientResource; }
  void SetClientResource( const nstl::string& _clientResource ) { clientResource = _clientResource; }

  const CVec3& GetTargetPos() const { return targetPos; }
  NHPTimer::STime GetFinishTime() const { return movementFinishTime; }

  bool RegisterInVoxelGrid();
  bool RegisterInVoxelGrid( byte cellX, byte cellY );

    virtual void Step( Protocol::Time deltaTime, Protocol::AbsoluteTime currentHPTime );
  virtual void OnTouch( int _objectID );

  REMOTE  virtual void MoveTo( const CVec2& _targetPos, Protocol::AbsoluteTime _finishTime );
  void Pursuit( Protocol::ObjectID _pursuitID );

private:
  void  CheckRegistration();
  void  CheckPursuit();

  Protocol::ObjectID objectID;
  Placement placement;

  CPtr<World> world;

  float linearVelocity;

  CVec3 targetPos;
  Protocol::AbsoluteTime movementFinishTime;

  Protocol::ObjectID pursuitID;

  nstl::string  clientResource;

  CPtr<ITownClientForObject> connectionToServer;

  PoolElement voxelGridElement;

  bool isPassive;
  bool isPlayer;

  int neighbourCount;
};

} // namespace Location

#endif //#define GAMEOBJECT_H_B4F7B77A_EEC9_4BC6