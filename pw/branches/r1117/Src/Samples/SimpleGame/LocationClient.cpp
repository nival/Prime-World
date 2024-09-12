#include "stdafx.h"

#include "LocationClient.h"
#include <Network/ClientTransportSystem.h>

#include "Protocol.h"
#include "World.h"

#include "RLocationServer.auto.h"
#include "LGameObject.auto.h"

namespace Location
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LocationClient::LocationClient( Transport::ClientTransportSystem * transport ) :
  lastClientTime(0),
  lastServerTime(0),
  diffClientTime(0),
  clientState(EClientState::Connecting),
  rpcNode(0)
{
  gateKeeper = new rpc::GateKeeperClient( transport, Transport::ENetInterface::Invalid );

  rpcNode = gateKeeper->RequestNode( "location/0"/*Protocol::locationServerId*/ ); 
  // @SE@TODO доделать координатор, чтобы адреса single серверов не оканчивались на /0

  gateKeeper->GetGate().RegisterFactory<GameObject>( *this );
  gateKeeper->GetGate().RegisterFactory<LocationClient>( *this );

  gateKeeper->GetGate().RegisterObject<LocationClient>( this, Protocol::LOCATION_CLIENT_RPC_NAME );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LocationClient::~LocationClient()
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LocationClient::OnDestroyContents()
{
  gateKeeper->GetGate().UnregisterFactory<GameObject>();
  gateKeeper->GetGate().UnregisterFactory<LocationClient>();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool LocationClient::Init()
{
  world = new World();

  if ( !world->Init() )
    return false;

  return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LocationClient::Suspend()
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LocationClient::Resume()
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
rpc::ILocalEntity* LocationClient::Create( const rpc::LocalEntityCreationInfo& info, rpc::Arguments& args )
{
  if ( info.classId == rpc::GetId<LocationClient>() )
  {
    return 0;
  }
  else if ( info.classId == rpc::GetId<GameObject>() )
  {
    bool popResult = true;
    Protocol::ObjectID _objectID = args.Pop<Protocol::ObjectID>(popResult);
    const Placement& _placement = args.PopStruct<Placement>(popResult);
    const nstl::string& _clientResource = args.Pop<const nstl::string&>(popResult);

    CPtr<GameObject> gameObject = world->CreateObjectWithID<GameObject>( _objectID );

    CVec2 target2D( _placement.pos.x, _placement.pos.y );

    gameObject->SetPlacement( _placement );
    gameObject->MoveTo( target2D, 0 );
    gameObject->SetClientResource( _clientResource );
    gameObject->SetConnectionToServer( this );


    rpc::ILocalEntity* localGameObject = new LGameObject( gameObject.GetPtr() );
    return localGameObject;
  }

  return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LocationClient::SetBattleServer( Battle::RBattleServer* _battleServer )
{
  battleServer = _battleServer;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LocationClient::Destroy( rpc::ILocalEntity* entity )
{
  GameObject *gameObject = entity->Get<GameObject>();

  if ( gameObject )
    world->RemoveObject( gameObject->GetID() );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LocationClient::SetPlayer( /*Protocol::ObjectID*/ int _objectID )
{
  player = world->GetObjectById( _objectID );
  player->SetPlayer( true );

  rpcNode->Query<RLocationServer>( Protocol::LOCATION_SERVER_RPC_NAME, this, &LocationClient::OnSetTownServer );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LocationClient::SetServerTime( /*Protocol::AbsoluteTime*/ double _serverTime )
{
  diffClientTime = _serverTime - lastClientTime;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LocationClient::OnSetTownServer( RLocationServer* _result )
{
  server = _result;
  clientState = EClientState::Running;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LocationClient::MovePlayerTo( const CVec3& _target, Protocol::ObjectID _pursuitID )
{
  threading::MutexLock lock( messageMutex );

  float distance = (_target - player->GetPlacement().pos).Length();
  double timeAtFinish = lastServerTime + distance / player->GetLinearVelocity();

  CVec2 currentPos2D( player->GetPlacement().pos.x, player->GetPlacement().pos.y );
  CVec2 target2D( _target.x, _target.y );

  if ( server )
  {
    server->MovePlayer( player->GetID(), currentPos2D.x, currentPos2D.y, target2D.x, target2D.y, timeAtFinish );

//     systemLog( NLogg::LEVEL_MESSAGE ) << "Move Base: " << player->GetID() << " " << lastServerTime << endl;
//     systemLog( NLogg::LEVEL_MESSAGE ) << "Move Base (sec): " << player->GetID() << " " << NHPTimer::Time2Seconds(lastServerTime) << endl;
  }

  player->MoveTo( target2D, timeAtFinish );
  player->Pursuit( _pursuitID );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LocationClient::RegisterPlayer( byte cellX, byte cellY )
{
  if ( server )
    server->RegisterPlayer( player->GetID(), cellX, cellY );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const PoolElement& LocationClient::GetPlayerVoxel() const
{
  return player->GetVoxelElement();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LocationClient::MovePlayerToObject( Protocol::ObjectID _pursuitID )
{
  player->Pursuit( _pursuitID );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LocationClient::Step( Protocol::Time deltaTime, Protocol::AbsoluteTime currentHPTime )
{
  threading::MutexLock lock( messageMutex );

  lastClientTime = currentHPTime;
  lastServerTime = diffClientTime + lastClientTime;

  world->Step( deltaTime, lastServerTime );

  gateKeeper->Poll();

  if ( IsValid( battleServer ) )
    battleServer->TestFunction( player->GetID() );

  Draw();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LocationClient::Draw()
{
  if ( !IsValid( debugDraw ) )
    return;

  if ( !debugDraw->Clear() )
    return;

  World::Objects worldObjects = world->GetWorldObjects();

  World::Objects::iterator it = worldObjects.begin();
  World::Objects::iterator last = worldObjects.end();

  for (; it != last; ++it)
  {
    const Placement& placement = it->second->GetPlacement();

    Color color = /*it->second->isNPC ? Color( 0, 1, 0 ) :*/ Color( 0, 0, 0 );

    debugDraw->DrawLine( placement.pos.x - 3, placement.pos.y - 3, placement.pos.x + 3, placement.pos.y + 3, color );
    debugDraw->DrawLine( placement.pos.x + 3, placement.pos.y - 3, placement.pos.x - 3, placement.pos.y + 3, color );
  }

  world->GetVoxelGrid().Draw( debugDraw );

  debugDraw->Invalidate();
}

//static rpc::SimpleRemoteEntityFactory<Battle::RBattleServer> factory_RBattleServer;

} // Location
