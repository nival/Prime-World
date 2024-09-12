#include "stdafx.h"

#include <System/Win32Random.h>
#include "../SimpleGameAI_CPP/AIServer.h"
//#include "../SimpleGameAI_CPP/RAIServer.auto.h"

#include "LocationServer.h"
#include "Protocol.h"

#include "World.h"

namespace Location
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace {
  float TOWN_SPAWN_MINX = 300.f;
  float TOWN_SPAWN_MAXX = 500.f;
  float TOWN_SPAWN_MINY = 200.f;
  float TOWN_SPAWN_MAXY = 400.f;

  float QUICKINFO_UPD_RATE = 4.0f;

  REGISTER_VAR( "town_spawn_zone_minx", TOWN_SPAWN_MINX, STORAGE_GLOBAL );
  REGISTER_VAR( "town_spawn_zone_maxx", TOWN_SPAWN_MAXX, STORAGE_GLOBAL );
  REGISTER_VAR( "town_spawn_zone_miny", TOWN_SPAWN_MINY, STORAGE_GLOBAL );
  REGISTER_VAR( "town_spawn_zone_maxy", TOWN_SPAWN_MAXY, STORAGE_GLOBAL );

  REGISTER_VAR( "town_quick_info_rate", QUICKINFO_UPD_RATE, STORAGE_GLOBAL );
}

static float PING_SEND_TIME = 8.0f;
const static float COUNT_STATISTIC_TIME = 2.0f;

REGISTER_VAR( "town_ping_send_time", PING_SEND_TIME, STORAGE_NONE );

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LocationServer::LocationServer( Transport::ITransportSystem* _transport, const Transport::TServiceId& serviceId ) :
  lastServerTime( 0 ),
  nextPingSendTime( 0 ),
  numberOfPlayers( 0 ),
  numberOfClosed( 0 ),
  avgNeighbours( 0.f ),
  maxNeighbours( 0 ),
  nextQuickInfoRequest( 0 ),
  nextStatisticTime( 0.0 ),
  aiNode( 0 )
{
  gateKeeper = new rpc::GateKeeper( _transport, serviceId, Transport::autoAssignClientId, this );
  gateKeeper->GetGate().RegisterObject<LocationServer>( this, Protocol::LOCATION_SERVER_RPC_NAME );

  rpc::Node* battleNode = gateKeeper->RequestNode( Protocol::battleServerId );
  battleNode->Query<Battle::RBattleServer>( Protocol::BATTLE_SERVER_RPC_NAME, this, &LocationServer::OnBattleServerReceived );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LocationServer::~LocationServer()
{
  clientPlayers.clear();
  connections.clear();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LocationServer::OnBattleServerReceived( Battle::RBattleServer* _battleServer )
{
  battleServer = _battleServer;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const nstl::vector<int>& LocationServer::GetNPC()
{
  static nstl::vector<int> npcVector;
  npcVector.clear();

  const int npcCount = 100; // Take this from World (Location itself)

  for ( int i = 0; i < npcCount; i++ )
  {
    CPtr<GameObject> gameObject = world->CreateObjectInSpace<GameObject>( EIdSpace::Player );
    Protocol::ObjectID objectID = gameObject->GetID();

    npcVector.push_back( objectID );

    numberOfPlayers++;

    Placement spawnPalcement = world->GetSpawnPlacement();
    spawnPalcement.pos.x = NWin32Random::Random( TOWN_SPAWN_MINX, TOWN_SPAWN_MAXX );
    spawnPalcement.pos.y = NWin32Random::Random( TOWN_SPAWN_MINY, TOWN_SPAWN_MAXY );
    const CVec3& defaultTarget = spawnPalcement.pos;

    clientPlayers.insert( make_pair( objectID, ClientPlayer( 0, 0 ) ) );

    gameObject->SetPlacement( spawnPalcement );
    CVec2 defaultTarget2D( defaultTarget.x, defaultTarget.y );
    gameObject->MoveTo( defaultTarget2D, lastServerTime );

    const PoolElement& voxelElement = gameObject->GetVoxelElement();

    BlockUnblockHelper<false> unblock( objectID, clientPlayers, world, gateKeeper->GetGate() );
    VoxelGrid& voxelGrid = world->GetVoxelGrid();
    voxelGrid.ForAllNeighbours( voxelElement.cellX, voxelElement.cellY, 1, unblock );
    gameObject->AddNeighbourCount( unblock.counter );
  }

  return npcVector;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LocationServer::OnNewNode( Transport::IChannel* channel,  rpc::Node* node )
{
  Transport::TServiceId rawId = channel->GetAddress().target;
  Transport::TServiceId serviceId;
  Transport::GetServiceClass( rawId, &serviceId );

  if ( serviceId == AI::aiServerId )
  {
    
  }
  else
  {
    CObj<ClientConnection> clientConnection = new ClientConnection( node, this );
    connections.insert( make_pair( reinterpret_cast<uint>(node), clientConnection ) );
    clientConnection->node->Query<RLocationClient>( Protocol::LOCATION_CLIENT_RPC_NAME, clientConnection.GetPtr(), &ClientConnection::OnClientReceived );
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LocationServer::OnChannelClosed( Transport::IChannel* channel,  rpc::Node* node )
{
  Connections::iterator itConn = connections.find( reinterpret_cast<uint>(node) );
  NI_VERIFY( itConn != connections.end(), "Error removing client", return );

  Protocol::ObjectID objectId = itConn->second->controlledObject;

  if ( objectId == -1 ) // соединение было, но не пришло ConnectionInfo от игрока
    return;

  ClientPlayers::iterator itPlayer = clientPlayers.find( objectId );
  NI_ASSERT( itPlayer != clientPlayers.end(), "Error removing client" );

  connections.erase( itConn );
  RGameObject* rpcGameObject = itPlayer->second.player;

  {
    Connections::iterator it = connections.begin();
    Connections::iterator last = connections.end();

    for (; it != last; ++it)
    {
      if ( it->second->client == 0 )
        continue;

      gateKeeper->GetGate().Dereplicate( *rpcGameObject, *it->second->node );
    }
  }

  struct CountHelper
  {
    int myId;
    CPtr<World> world;

    void operator()( int objectID ) 
    {
      if ( objectID == myId )
        return;

      CPtr<GameObject> otherPlayer = world->GetObjectById( objectID );

      if ( IsValid( otherPlayer ) )
        otherPlayer->AddNeighbourCount( -1 );
    }
  };

  CountHelper helper;
  helper.myId = objectId;
  helper.world = world;

  CPtr<GameObject> gameObject = world->GetObjectById( objectId );

  if ( IsValid( gameObject ) )
  {
    const PoolElement& voxel = gameObject->GetVoxelElement();

    world->GetVoxelGrid().ForAllNeighbours( voxel.cellX, voxel.cellY, 1, helper );
    world->RemoveObject( objectId );
  }

  clientPlayers.erase( itPlayer );

  numberOfPlayers--;
  numberOfClosed++;

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LocationServer::OnCorruptData( Transport::IChannel* channel, rpc::Node* node )
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool LocationServer::Init()
{
  world = new World();
  world->SetIDGenerator( new WorldIDGenerator() );

  CVec3 worldBase;
  float worldSize = 0;
  world->GetWorldBounds( worldBase, worldSize );

  if ( !world->Init() )
    return false;

  return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LocationServer::OnClientReceived( ClientConnection* _connection )
{
  _connection->client->GetConnectionInfo( _connection, &ClientConnection::GetConnectionInfo );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LocationServer::OnGetConnectionInfo( ClientConnection* _connection, const ClientConnectionInfo& _connectionInfo )
{
  if ( IsValid( _connection->client ) )
    _connection->client->SetServerTime( lastServerTime );

  CPtr<GameObject> gameObject = world->CreateObjectInSpace<GameObject>( EIdSpace::Player );

  numberOfPlayers++;

  Protocol::ObjectID objectID = gameObject->GetID();
  _connection->controlledObject = objectID;

  Placement spawnPalcement = world->GetSpawnPlacement();
  spawnPalcement.pos.x = NWin32Random::Random( TOWN_SPAWN_MINX, TOWN_SPAWN_MAXX );
  spawnPalcement.pos.y = NWin32Random::Random( TOWN_SPAWN_MINY, TOWN_SPAWN_MAXY );
  const CVec3& defaultTarget = spawnPalcement.pos;

  RGameObject* rpcGameObject = _connection->node->Create<RGameObject>( objectID, spawnPalcement, gameObject->GetClientResource() );
  gateKeeper->GetGate().Block( *rpcGameObject, *_connection->node );

  clientPlayers.insert( make_pair( objectID, ClientPlayer( rpcGameObject, _connection ) ) );

  gameObject->SetPlacement( spawnPalcement );
  CVec2 defaultTarget2D( defaultTarget.x, defaultTarget.y );
  gameObject->MoveTo( defaultTarget2D, lastServerTime );

  const PoolElement& voxelElement = gameObject->GetVoxelElement();

  BlockUnblockHelper<false> unblock( objectID, clientPlayers, world, gateKeeper->GetGate() );
  VoxelGrid& voxelGrid = world->GetVoxelGrid();
  voxelGrid.ForAllNeighbours( voxelElement.cellX, voxelElement.cellY, 1, unblock );
  gameObject->AddNeighbourCount( unblock.counter );

  if ( IsValid( _connection->client ) )
  {
    _connection->client->SetPlayer( gameObject->GetID() );
    _connection->client->SetBattleServer( battleServer.GetPtr() );
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LocationServer::ExlusiveMoveTo( RGameObject* _object, GameObject* _gameObject, rpc::Gate& _gate, rpc::Node* _node )
{
  if ( IsValid( _gameObject ) )
  {
    _gate.SetExclusive( *_object, *_node );

    CVec2 currentPos2D( _gameObject->GetPlacement().pos.x, _gameObject->GetPlacement().pos.y );
    CVec2 targetPos2D( _gameObject->GetTargetPos().x, _gameObject->GetTargetPos().y );
    _object->InitPlacement( currentPos2D, targetPos2D, _gameObject->GetFinishTime() );

    _gate.ClearExclusive( *_object );
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LocationServer::RegisterPlayer( ushort _objectIDShort, byte cellX, byte cellY )
{
  int _objectID = static_cast<int>(_objectIDShort);

  GameObject* gameObject = world->GetObjectById( _objectID );

  if ( gameObject )
  {
    const PoolElement& poolElement =  gameObject->GetVoxelElement();

    int oldX = poolElement.cellX;
    int oldY = poolElement.cellY;
    int sx = cellX - poolElement.cellX;
    int sy = cellY - poolElement.cellY;

    NI_ASSERT( abs( sx ) <= 1 && abs( sy ) <= 1, "VOXEL JUMP!" );

    if ( gameObject->RegisterInVoxelGrid( cellX, cellY ) )
    {
      BlockUnblockHelper<true> block( _objectID, clientPlayers, world, gateKeeper->GetGate() );
      BlockUnblockHelper<false> unblock( _objectID, clientPlayers, world, gateKeeper->GetGate() );

      VoxelGrid& voxelGrid = world->GetVoxelGrid();

      voxelGrid.ForAllNeighboursDelta( oldX, oldY, sx, sy, 1, unblock );
      voxelGrid.ForAllNeighboursDelta( poolElement.cellX, poolElement.cellY, -sx, -sy, 1, block );

      gameObject->AddNeighbourCount( unblock.counter );
      gameObject->AddNeighbourCount( -block.counter );
    }
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LocationServer::MovePlayer( ushort _objectIDShort, float startPosx, float startPosy, float targetPosx, float targetPosy, Protocol::AbsoluteTime _finishTime )
{
  int _objectID = static_cast<int>(_objectIDShort);

  CPtr<GameObject> gameObject = world->GetObjectById( _objectID ); 

  CVec2 startPos( startPosx, startPosy );
  CVec2 targetPos( targetPosx, targetPosy );

  if ( IsValid( gameObject ) )
  {
    gameObject->SetPosition( startPos, false );
    gameObject->MoveTo( targetPos, _finishTime );
  }

  ClientPlayers::iterator it = clientPlayers.find( _objectID );

  if ( it != clientPlayers.end() )
  {
    if ( IsValid( it->second.player ) )
      it->second.player->MoveTo( targetPos, _finishTime );
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LocationServer::TouchObject( ushort _objectIDShort )
{
  int _objectID = static_cast<int>(_objectIDShort);

  CPtr<GameObject> gameObject = world->GetObjectById( _objectID ); 

  if ( IsValid( gameObject ) )
    gameObject->OnTouch( _objectID );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LocationServer::Step( float dt, NHPTimer::STime serverTime )
{
  lastServerTime = NHPTimer::Time2Seconds( serverTime );

//   Transport::TChannels newConnections;
//   listener->GetNewConnections( &newConnections );
// 
//   for ( Transport::TChannels::iterator it = newConnections.begin(); it != newConnections.end(); ++it)
//   {
//     Transport::TClientId id = (*it)->GetAddress().client;
//     systemLog( NLogg::LEVEL_MESSAGE ) << "Client connected: " << id << endl;
// 
//     AddClient( id, *it );
//   }
// 
//   list<int> idsToErase;
// 
//   for ( Connections::iterator it = connections.begin(); it != connections.end(); ++it )
//   {
//     if ( it->second->endpoint.channel->GetStatus() == Network::ConnectionState::Closed )
//     {
//       idsToErase.push_back( it->first );
//       continue;
//     }
//   }
// 
//   for( list<int>::iterator it = idsToErase.begin(); it != idsToErase.end(); ++it )
//   {
//     RemoveClient( *it );
//   }

  gateKeeper->Poll();

  CountStatistics( dt );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LocationServer::CountStatistics( float delta )
{
  nextStatisticTime += delta;
  
  if ( nextStatisticTime > COUNT_STATISTIC_TIME )
  {
    const World::Objects& objects = world->GetWorldObjects();

    World::Objects::const_iterator it = objects.begin();
    World::Objects::const_iterator last = objects.end();

    int countNeighbourgs = 0;
    int number = 0;

    maxNeighbours = 0;

    for ( ; it != last; ++it )
    {
      int count = it->second->GetNeighbourCount();
      maxNeighbours = max( maxNeighbours, count );

      countNeighbourgs += count;
      number++;
    }

    avgNeighbours = float( countNeighbourgs ) / float( number );
    nextStatisticTime = 0;
  }

  char szBuf[1024] = "";

  int nWritten = sprintf_s( szBuf, "PLAYERS: %d( +%d closed )  AVG.NH: %.2f MAX.NH: %d", numberOfPlayers, numberOfClosed, avgNeighbours, maxNeighbours );
  NI_ASSERT( nWritten < 1024, "SetConsoleTitle overflow" );

  ::SetConsoleTitle( szBuf );
}


} // namespace Location
