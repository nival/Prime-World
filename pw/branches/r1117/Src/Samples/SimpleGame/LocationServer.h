#ifndef LOCATIONSERVER_H_99919C07_C641_4
#define LOCATIONSERVER_H_99919C07_C641_4

#include <Network/TransportAddress.h>

#include <RPC/GateKeeper.h>
#include <RPC/RPC.h>
#include <RPC/P2PNode.h>

#include "Protocol.h"
#include "RLocationClient.auto.h"
#include "RGameObject.auto.h"
#include "RBattleServer.auto.h"
#include "GameObject.h"
#include "System/RefCntObject.h"

#define REMOTE 

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace Transport
{
  _interface IChannelListener;
  _interface IChannel;
}

namespace NScene
{
  class CollisionMap;
}

namespace AI
{
  class RAIServer;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace Location
{

class World;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
REMOTE class LocationServer : public rpc::IGateKeeperCallback, public CObjectBase
{
  OBJECT_METHODS( 0x9D629AC0, LocationServer );

public:
  RPC_ID();

  LocationServer( Transport::ITransportSystem* _transport, const Transport::TServiceId& serviceId );
  ~LocationServer();

  void Step( float delta, NHPTimer::STime serverTime );
  bool Init();

  void OnBattleServerReceived( Battle::RBattleServer* _battleServer );
  void OnAIServerReceived( AI::RAIServer* _aiServer );

  REMOTE const nstl::vector<int>& GetNPC();

  // registration in voxel grid
  REMOTE void RegisterPlayer( ushort _objectID, byte cellX, byte cellY );
  REMOTE void MovePlayer( ushort _objectID, float startPosx, float startPosy, float targetPosx, float targetPosy, Protocol::AbsoluteTime _finishTime );
  REMOTE void TouchObject( ushort _objectID );

  // from IGateKeeperCallback
  virtual void OnNewNode( Transport::IChannel* channel,  rpc::Node* node );
  virtual void OnChannelClosed( Transport::IChannel* channel,  rpc::Node* node );
  virtual void OnCorruptData( Transport::IChannel* channel, rpc::Node* node );

private:

  struct ClientConnection : public CObjectBase
  {
    OBJECT_BASIC_METHODS(ClientConnection)
  public:
    ClientConnection(){}

    CObj<RLocationClient> client;
    CPtr<LocationServer> server;
    rpc::Node* node;
    Protocol::ObjectID controlledObject;

    ClientConnection( rpc::Node* _node, LocationServer* _server ) 
      : node( _node ), client( 0 ), server( _server ), controlledObject( Protocol::invalidObjectId ) 
    {}

    void OnClientReceived( RLocationClient* _result )
    {
      client = _result;
      server->OnClientReceived( this );
    }

    void GetConnectionInfo( const ClientConnectionInfo& result )
    {
      server->OnGetConnectionInfo( this, result );
    }
  };
 
  struct ClientPlayer   
  {
    CObj<RGameObject> player;
    CObj<ClientConnection> connection;

    ClientPlayer( RGameObject* _player, ClientConnection* _connection ) : player(_player), connection(_connection) {}
  };

  typedef hash_map<uint, CObj<ClientConnection>> Connections;
  typedef hash_map<Protocol::ObjectID, ClientPlayer> ClientPlayers; 


  template < bool block >
  struct BlockUnblockHelper : public NonCopyable
  {
    rpc::Gate& gate;
    rpc::Node* receiverNode;
    CPtr<RGameObject> receiverPlayer;
    CPtr<World> world;
    CPtr<GameObject> playerObject;
    ClientPlayers& clientPlayers;
    int receiverID;
    int counter;

    BlockUnblockHelper( int _receiverID, ClientPlayers& _clientPlayers, World* _world, rpc::Gate& _gate );

//    bool IsReady() const { return receiverGate != 0; }

    void operator()( int objectID );
  };

  LocationServer() {} // $TODO remove default constructor

  void OnClientReceived( ClientConnection* _connection );
  void OnGetConnectionInfo( ClientConnection* _connection, const ClientConnectionInfo& _connectionInfo );

  void CountStatistics( float delta );

  static void ExlusiveMoveTo( RGameObject* _object, GameObject* gameObject, rpc::Gate& _gate, rpc::Node* _node );

  Connections connections;
  StrongMT<rpc::GateKeeper> gateKeeper;

  CObj<Battle::RBattleServer> battleServer;
  CObj<AI::RAIServer> aiServer;
  rpc::Node* aiNode;

  ClientPlayers clientPlayers;
  CObj<World> world;

  float nextPingSendTime;
  float nextQuickInfoRequest;

  Protocol::AbsoluteTime lastServerTime;
  Protocol::AbsoluteTime nextStatisticTime;
  int numberOfPlayers;
  int numberOfClosed;
  float avgNeighbours;
  int maxNeighbours;
};

} // namespace Location

//Inlines
#include "LocationServerImpl.h"

#endif //#define LOCATIONSERVER_H_99919C07_C641_4