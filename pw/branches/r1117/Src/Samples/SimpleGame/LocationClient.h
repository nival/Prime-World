#ifndef TOWNCLIENTBASE_H_F0EABDA3_6977_4
#define TOWNCLIENTBASE_H_F0EABDA3_6977_4

#include <RPC/RPC.h>
#include <RPC/GateKeeper.h>
#include <RPC/P2PNode.h>

#include "Protocol.h"
#include "GameObject.h"
#include "DebugDraw.h"
#include "RLocationServer.auto.h"
#include "RBattleServer.auto.h"
#include "LocationTypes.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace Transport
{
  _interface IChannel;
  class ClientTransportSystem;
}

namespace Game
{
  class LobbyClientRunner;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace Location
{

class GameObject;
class World;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
REMOTE class LocationClient : 
  rpc::ILocalEntityFactory, 
  public ITownClientForObject,
  public CObjectBase
{
  OBJECT_BASIC_METHODS( LocationClient );

public:
  RPC_ID();

  LocationClient( Transport::ClientTransportSystem * transport );
  virtual ~LocationClient();

  // from CObjectBase
  virtual void OnDestroyContents();

  virtual void Step( Protocol::Time deltaTime, Protocol::AbsoluteTime currentHPTime );
  virtual bool Init();
  virtual void Suspend(); //Game launched in Town
  virtual void Resume(); //TODO: Return from game
  void MovePlayerToObject( Protocol::ObjectID _pursuitID );

  EClientState::Enum GetState() const { return clientState; }

  // from ITownClientForObject
  virtual void MovePlayerTo( const CVec3& _target, Protocol::ObjectID _pursuitID );
  virtual void RegisterPlayer( byte cellX, byte cellY );
  virtual const PoolElement& GetPlayerVoxel() const;
  virtual Protocol::AbsoluteTime GetServerTime() const { return lastServerTime; }
  virtual float GetMinimalDistance( Protocol::ObjectID _first, Protocol::ObjectID _second ) { return 0.f; }

  REMOTE virtual const ClientConnectionInfo& GetConnectionInfo() { return connectionInfo; }
  REMOTE virtual void SetPlayer( /*Protocol::ObjectID*/ int _objectID );
  REMOTE virtual void SetServerTime( /*Protocol::AbsoluteTime */ double _serverTime ); 
  REMOTE virtual void SetBattleServer( Battle::RBattleServer* _battleServer );

  // from rpc::ILocalEntityFactory
  virtual rpc::ILocalEntity* Create(const rpc::LocalEntityCreationInfo& info, rpc::Arguments& args);
  virtual void Destroy( rpc::ILocalEntity* entity );

  World* GetWorld() const { return world; }
  GameObject* GetPlayer() const { return player; }

  void SetDebugDraw( IDebugDraw* _debugDraw ) { debugDraw = _debugDraw; } 

protected:
  LocationClient() : rpcNode( 0 ) {}

  void OnSetTownServer( RLocationServer* _result );
  void Draw();

  ClientConnectionInfo connectionInfo;

  EClientState::Enum clientState;

  StrongMT<rpc::GateKeeperClient> gateKeeper;
  rpc::Node* rpcNode;

  CObj<World> world;
  CPtr<GameObject> player;
  CPtr<RLocationServer> server;
  CPtr<Battle::RBattleServer> battleServer;

  Protocol::AbsoluteTime lastClientTime;
  Protocol::AbsoluteTime lastServerTime;
  Protocol::AbsoluteTime diffClientTime;

  CPtr<IDebugDraw> debugDraw;

  threading::Mutex messageMutex;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace Location


#endif //#define TOWNCLIENTBASE_H_F0EABDA3_6977_4
