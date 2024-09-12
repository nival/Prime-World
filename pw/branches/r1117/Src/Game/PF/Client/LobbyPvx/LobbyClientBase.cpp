#include "stdafx.h"
#include "LobbyClientBase.h"
#include "Server/RPC/LocalEntityFactory.h"
#include "Network/ClientTransportSystemIntf.h"
#include "Server/LobbyPvx/CommonTypes.h"
#include "Server/LobbyPvx/RLobbyIEntrance.auto.h"
#include "Server/LobbyPvx/RLobbyIServerInstance.auto.h"
#include "RLobbyClientInterface.auto.h"
#include "LLobbyClientInterface.auto.h"
#include "Version.h"
#include "UI/FrameTimeRender.h"

namespace lobby
{


static float s_servicesTimeout = 15.0f;
REGISTER_VAR( "lobby_cl_svc_timeout", s_servicesTimeout, STORAGE_NONE );

static float s_leaveTimeout = 5.0f;
REGISTER_VAR( "lobby_cl_leave_timeout", s_leaveTimeout, STORAGE_NONE );

static int s_overrideManoeuvresFaction = lobby::ETeam::None;
REGISTER_DEV_VAR( "override_manoeuvres_faction", s_overrideManoeuvresFaction, STORAGE_NONE );



class LobbyUserProxy : public ILobbyUser, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( LobbyUserProxy, ILobbyUser, BaseObjectMT );
public:
  explicit LobbyUserProxy( ClientBase * _owner ) : owner( _owner ) {}

  virtual void AddGameInfo( const SDevGameInfo & info ) { owner->AddGameInfo( info ); }
  virtual void JoinCustomSession( const SGameParameters & params ) { owner->JoinCustomSession( params ); }
  virtual void UpdateClientStatus( int status ) { owner->UpdateClientStatus( status ); }
  virtual void AddCustomGameMember( const SGameMember & member ) { owner->AddCustomGameMember( member ); }
  virtual void RemoveCustomGameMember( int userId ) { owner->RemoveCustomGameMember( userId ); }
  virtual void UpdateCustomGameMember( int userId, const SPlayerGameContext & params ) { owner->UpdateCustomGameMember( userId, params ); }
  virtual void UpdateCustomGameMemberReadiness( int userId, bool ready ) { owner->UpdateCustomGameMemberReadiness( userId, ready ); }
  virtual void StartSession( TGameId _sessionId, const SGameParameters & _params, const TGameLineUp & _gameLineUp, Peered::RIGameServer * _gameServerInstance, const Peered::SInstanceId & _gsInstId, unsigned timestamp32 )
    { owner->StartSession( _sessionId, _params, _gameLineUp, _gameServerInstance, _gsInstId, timestamp32 ); }
  virtual void Award( const vector<roll::SAwardInfo> & _awards ) { owner->Award( _awards ); }
public:
  ClientBase * owner;
};







ClientBase::ClientBase( Transport::TClientId _clientId, bool _inSocialMode ) :
inSocialMode( _inSocialMode ),
status( EClientStatus::Initial ),
errorCode( EClientError::NoError ),
lastLobbyOperationResult( EOperationResult::Ok ),
clientId( _clientId ),
now( 0 ),
statusTimeLimit( -1 ),
gameSessionId( 0 ),
serverTimestamp( 0 ),
timeDelta( 0 ),
leaveAckCounter( 0 )
{
  lobbyUserProxy = new LobbyUserProxy( this );
}



ClientBase::~ClientBase()
{
  //TEMP: remove after NUM_TASK check
  NGlobal::UnregisterCmd( "leave_game" );

  serverInst = 0;
  entrance = 0;

  Reset( rpcFactory, 0 );
}



void ClientBase::CleanUpRpcCyclicLinks()
{
  gateKeeper = 0;
  serverInst = 0;
  entrance = 0;
  gameServerRequester = 0;
}



void ClientBase::Start( rpc::GateKeeperClient * _kateKeeper, const Transport::TServiceId & _fullLobbySvcId )
{
  MessageTrace( "Connecting to lobby server..." );

  NI_VERIFY( status != EClientStatus::Error, "", return );

  gateKeeper = _kateKeeper;

  gateKeeper->attachNotificationCallback( this );

  if ( status != EClientStatus::Initial )
  {
    SetError( EClientError::ProtocolViolation );
    return;
  }

  now = timer::Now();

  Reset( rpcFactory, new rpc::LocalEntityFactory( gateKeeper->GetGate() ) );
  rpcFactory->RegisterAttach<lobby::ILobbyUser, lobby::LILobbyUser>();

  Transport::TServiceId lobbyNodeSvcId;
  if ( inSocialMode )
  {
    if ( _fullLobbySvcId.empty() )
      ErrorTrace( "Lobby service path is unknown!" );
    else
    {
      MessageTrace( "Lobby service path: '%s'", _fullLobbySvcId.c_str() );
      if ( !Transport::GetLocalServiceId( _fullLobbySvcId, lobbyNodeSvcId ) )
        ErrorTrace( "Cannot parse service path!" );
    }
  }

  if ( lobbyNodeSvcId.empty() )
  {
    //HACK for custom lobby
    string id = serviceIds::Service.c_str();
    id += "/1";
    lobbyNodeSvcId = id.c_str();
  }

  MessageTrace( "Lobby service node id: '%s'", lobbyNodeSvcId.c_str() );

  entrance = new rpc::IfaceRequester<RIEntrance>;
  entrance->init( gateKeeper, lobbyNodeSvcId, serviceIds::Entrance );

  ChangeStatus( EClientStatus::WaitingEntrance );
  EnableStatusTimeout();
}



void ClientBase::Poll()
{
  now = timer::Now();

  if ( ( statusTimeLimit > 0 ) && ( now > statusTimeLimit ) )
  {
    SetError( EClientError::ServiceTimeOut );
  }

  if ( entrance )
    entrance->step();

  if ( gameServerRequester )
    gameServerRequester->step();

  switch ( status )
  {
    default:
      break;

    case EClientStatus::WaitingEntrance:
    {
      NI_VERIFY( entrance, "", SetError( EClientError::PrematureDisconnect ); break; );
      
      rpc::IfaceRequesterState::Enum newSt = entrance->PopNewState();
      if ( newSt == rpc::IfaceRequesterState::CLOSED )
      {
        ErrorTrace( "Could not connect to lobby service." );
        SetError( EClientError::PrematureDisconnect );
        break;
      }
      else if ( newSt == rpc::IfaceRequesterState::OPENED )
        OnEntrance();
      break;
    }

    case EClientStatus::ConnectingToGameSvc:
    {
      NI_VERIFY( gameServerRequester, "", SetError( EClientError::PrematureDisconnect ); break; );

      rpc::IfaceRequesterState::Enum newSt = gameServerRequester->PopNewState();
      if ( newSt == rpc::IfaceRequesterState::CLOSED )
      {
        ErrorTrace( "Could not connect to game service." );
        SetError( EClientError::PrematureDisconnect );
        break;
      }
      else if ( newSt == rpc::IfaceRequesterState::OPENED )
      {
        MessageTrace( "Connected to game service" );
        gameServer = gameServerRequester->iface();
        NI_VERIFY( gameServer, "", return );
        ChangeStatus( EClientStatus::InGameSession );
      }
      break;
    }

    case EClientStatus::Connected:
      break;

    //TODO
  }
}



void ClientBase::OnEntrance()
{
  MessageTrace( "Entered lobby, requesting instance..." );

  NI_ASSERT( status == EClientStatus::WaitingEntrance, "" );

  NI_VERIFY( entrance, "", SetError( EClientError::PrematureDisconnect ); return );
  NI_VERIFY( entrance->iface(), "", SetError( EClientError::PrematureDisconnect ); return );

  entrance->iface()->RequestServerInstance( RemotePtr<RILobbyUser>( lobbyUserProxy ), VERSION_REVISION, this, &ClientBase::OnGetServerInstance );

  ChangeStatus( EClientStatus::RequestingServerInstance );
  EnableStatusTimeout();
}




void ClientBase::OnGetServerInstance( RIServerInstance * svInst )
{
  MessageTrace( "Got lobby instance" );

  if ( !svInst || ( status != EClientStatus::RequestingServerInstance ) )
  {
    SetError( EClientError::ProtocolViolation );
    return;
  }

  serverInst = svInst;
  entrance = 0; //No longer needed

  //ChangeStatus( EClientStatus::WaitingAccounting );
  //EnableStatusTimeout();

  ChangeStatus( EClientStatus::Connected );

  if ( inSocialMode )
  {
    MessageTrace( "Joining social game..." );
    serverInst->JoinSocialGame( this, &ClientBase::OnOperatioResult );
    lastLobbyOperationResult = EOperationResult::InProgress;
  }
}



void ClientBase::OnOperatioResult( EOperationResult::Enum result )
{
  MessageTrace( "Got lobby operation result: %s(%d)", EOperationResult::ToString( result ), (int)result );

  switch ( status )
  {
    default:
      break;

    case EClientStatus::Connected:
      lastLobbyOperationResult = result;

      if ( inSocialMode && ( result != EOperationResult::Ok ) )
        SetError( EClientError::ServiceDenial );
      break;
  } 
}



void ClientBase::OnGameLeaveAnswer( bool )
{
  //FIXME: close channel here?

  ++leaveAckCounter;

  if ( leaveAckCounter > 0 )
  {
    ChangeStatus( EClientStatus::Disconnected );
  }
}



void ClientBase::OnChannelClosed( Transport::IChannel * channel, rpc::Node * node )
{
  if ( channel )
    channel->Close();

  if ( ( status != EClientStatus::Disconnected ) && ( status != EClientStatus::GameFinished ) )
    SetError( EClientError::PrematureDisconnect );
}



void ClientBase::OnCorruptData( Transport::IChannel * channel, rpc::Node * node )
{
  if ( channel )
    channel->Close();

  SetError( EClientError::DataCorruption );
}


void ClientBase::AddGameInfo( const SDevGameInfo & info )
{
  gamesList.push_back( info );

  OnLobbyDataChange();
}



void ClientBase::JoinCustomSession( const SGameParameters & params )
{
  NI_VERIFY( status == EClientStatus::Connected, "", return );
  NI_VERIFY( serverInst, "", return );

  gameParams = params;
  ChangeStatus( EClientStatus::InCustomLobby );
}



void ClientBase::UpdateClientStatus( /*EOperationResult::Enum*/ int status )
{
  lastLobbyOperationResult = (EOperationResult::Enum)status;
}



void ClientBase::AddCustomGameMember( const SGameMember & member )
{
  const int userId = member.user.userId;

  for ( int i = 0; i < gameLineUp.size(); ++i )
    if ( gameLineUp[i].user.userId == userId )
    {
      NI_ALWAYS_ASSERT( NStr::StrFmt( "User %d ('%S') already in game", userId, member.user.nickname.c_str() ) );
      return;
    }

  gameLineUp.push_back( member );

  OnLobbyDataChange();
}



void ClientBase::RemoveCustomGameMember( int userId )
{
  for ( int i = 0; i < gameLineUp.size(); ++i )
    if ( gameLineUp[i].user.userId == userId )
    {
      gameLineUp.erase( gameLineUp.begin() + i );
      OnLobbyDataChange();
      return;
    }

  NI_ALWAYS_ASSERT( NStr::StrFmt(  "User %d not found in game" , userId ) );
}



void ClientBase::UpdateCustomGameMember( int userId, const SPlayerGameContext & params )
{
  for ( int i = 0; i < gameLineUp.size(); ++i )
    if ( gameLineUp[i].user.userId == userId )
    {
      gameLineUp[i].context = params;
      OnLobbyDataChange();
      return;
    }

  NI_ALWAYS_ASSERT( NStr::StrFmt( "User %d not found in game", userId ) );
}



void ClientBase::UpdateCustomGameMemberReadiness( int userId, bool ready )
{
  if ( ready )
    gameMembersReadiness.insert( userId );
  else
    gameMembersReadiness.erase( userId );

  OnLobbyDataChange();
}



void ClientBase::StartSession( TGameId _sessionId, const SGameParameters & _params, const TGameLineUp & _gameLineUp, Peered::RIGameServer * _gameServerInstance, const Peered::SInstanceId & _gsInstId, unsigned timestamp32 )
{
  MessageTrace( "Starting game session. map='%s', players=%d, gameid=%s, custom=%i, gs_svcid=%s, gs_instid=%s", _params.mapId, _gameLineUp.size(), FmtGameId( _sessionId ), _params.customGame, _gsInstId.serviceId, _gsInstId.instanceId );

  for ( int i = 0; i < _gameLineUp.size(); ++i )
    MessageTrace( "  Player info. uid=%d, sex=%d, nick=%d, type=%d, team=%d, hero=%s, bot_skin=%s", _gameLineUp[i].user.userId, (int)_gameLineUp[i].user.zzimaSex, _gameLineUp[i].user.nickname,
    (int)_gameLineUp[i].context.playerType, (int)_gameLineUp[i].context.team, _gameLineUp[i].context.hero, _gameLineUp[i].context.botSkin );

  bool statusIsRight = false;
  if ( status == EClientStatus::InCustomLobby )
    statusIsRight = true;
  else if ( status == EClientStatus::Connected )
    statusIsRight = true;

  NI_VERIFY( statusIsRight, NStr::StrFmt( "Wrong Lobby Client status (%d)", (int)status ), return );
  NI_VERIFY( serverInst, "", return );

  gameSessionId = _sessionId;
  gameParams = _params;
  gameLineUp = _gameLineUp; 
  gameServer = _gameServerInstance;
  gameSvcInstId = _gsInstId;

  if ( s_overrideManoeuvresFaction == lobby::ETeam::Team1 || s_overrideManoeuvresFaction == lobby::ETeam::Team2 )
  {
    gameParams.manoeuvresFaction = (lobby::ETeam::Enum)s_overrideManoeuvresFaction;
  }

  gameMembersReadiness.clear();

  serverTimestamp = (__time32_t)timestamp32;
  if (serverTimestamp > 0)
  {
    __time32_t localTimestamp;
    _time32( &localTimestamp );
    if (localTimestamp > 0)
      timeDelta = localTimestamp - serverTimestamp;
  }

  if ( gameSvcInstId.Valid() )
  {
    MessageTrace( "Connecting to game server. svcid=%s, instid=%s", gameSvcInstId.serviceId, gameSvcInstId.instanceId );
    gameServerRequester = new rpc::IfaceRequester<Peered::RIGameServer>;
    gameServerRequester->init( gateKeeper, gameSvcInstId.serviceId.c_str(), gameSvcInstId.instanceId.c_str() );
    ChangeStatus( EClientStatus::ConnectingToGameSvc );
    EnableStatusTimeout();
  }
  else
  {
    NI_VERIFY( gameServer, "", return );
    ChangeStatus( EClientStatus::InGameSession );
  }
}



void ClientBase::LeaveGame(int clientIndex)
{
  if ( status == EClientStatus::Disconnected )
    return;

  if ( status == EClientStatus::GameFinished ) {
    ChangeStatus( EClientStatus::Disconnected );
    return;
  }

  NI_VERIFY( status == EClientStatus::InGameSession, "", return );
  NI_VERIFY( serverInst, "", return );

  gameServer->OnGameLeave( clientIndex, this, &ClientBase::OnGameLeaveAnswer );

  ChangeStatus( EClientStatus::LeavingServer );
  EnableStatusTimeout( s_leaveTimeout );
}



void ClientBase::ChangeStatus( EClientStatus::Enum newStatus )
{
  if ( newStatus == status )
    return;

  if ( status == EClientStatus::Error )
    return;

  statusTimeLimit = -1;

  OnStatusChange( newStatus );

  status = newStatus;
}



void ClientBase::SetError( EClientError::Enum code )
{
  if ( errorCode != EClientError::NoError )
    return;

  errorCode = code;
  statusTimeLimit = -1;

  ChangeStatus( EClientStatus::Error );
}



void ClientBase::EnableStatusTimeout( float _to )
{
  NI_ASSERT( statusTimeLimit < 0, "" );

  if ( !_to )
    _to = s_servicesTimeout;

  if ( _to )
    statusTimeLimit = now + _to;
}



void ClientBase::OnStatusChange( EClientStatus::Enum newStatus )
{
  StrongMT<IClientNotify> locked = notify.Lock();
  if ( locked )
    locked->OnStatusChange( status, newStatus );
}



void ClientBase::OnLobbyDataChange()
{
  StrongMT<IClientNotify> locked = notify.Lock();
  if ( locked )
    locked->OnLobbyDataChange();
}



void ClientBase::SetDeveloperSex( ESex::Enum _sex )
{
  NI_VERIFY( status == EClientStatus::Connected, "", return );
  NI_VERIFY( serverInst, "", return );
  NI_VERIFY( !inSocialMode, "", return );

  NI_VERIFY( _sex != ESex::Undefined, "", return );
  serverInst->SetDeveloperSex( _sex );
}



void ClientBase::RefreshGamesList()
{
  NI_VERIFY( status == EClientStatus::Connected, "", return );
  NI_VERIFY( serverInst, "", return );

  gamesList.clear();
  serverInst->RequestGamesList();
}



void ClientBase::CreateGame( const char * mapId, int maxPlayers, int maxPlayersPerTeam, int autostartPlayers /*= -1*/ )
{
  NI_VERIFY( status == EClientStatus::Connected, "", return );
  NI_VERIFY( serverInst, "", return );
  serverInst->CreateCustomGame( maxPlayers, maxPlayersPerTeam, mapId, autostartPlayers, this, &ClientBase::OnOperatioResult );

  lastLobbyOperationResult = EOperationResult::InProgress;
}



void ClientBase::JoinGame( int gameId )
{
  NI_VERIFY( status == EClientStatus::Connected, "", return );
  NI_VERIFY( serverInst, "", return );
  
  serverInst->JoinGame( gameId, this, &ClientBase::OnOperatioResult );
  lastLobbyOperationResult = EOperationResult::InProgress;
}



void ClientBase::ReconnectGame( int gameId, int team, const string& heroId )
{
  NI_VERIFY( status == EClientStatus::Connected, "", return );
  NI_VERIFY( serverInst, "", return );
  
  serverInst->ReconnectToCustomGame(gameId, team, heroId, this, &ClientBase::OnOperatioResult);
  lastLobbyOperationResult = EOperationResult::InProgress;
}



void ClientBase::SpectateGame( int gameId )
{
  NI_VERIFY( status == EClientStatus::Connected, "", return );
  NI_VERIFY( serverInst, "", return );
  
  serverInst->SpectateCustomGame( gameId, this, &ClientBase::OnOperatioResult );
  lastLobbyOperationResult = EOperationResult::InProgress;
}



void ClientBase::ChangeCustomGameSettings( ETeam::Enum team, ETeam::Enum faction, const string & heroId )
{
  NI_VERIFY( status == EClientStatus::InCustomLobby, "", return );
  NI_VERIFY( serverInst, "", return );
  serverInst->ChangeCustomGameSettings( team, faction, heroId );
}



void ClientBase::SetReady( EGameMemberReadiness::Enum readiness )
{
  NI_VERIFY( status == EClientStatus::InCustomLobby, "", return );
  NI_VERIFY( serverInst, "", return );
  serverInst->SetReady( readiness );
}



void ClientBase::SetDeveloperParty(int party)
{
  NI_VERIFY( status == EClientStatus::InCustomLobby, "", return );
  NI_VERIFY( serverInst, "", return );
  serverInst->SetDeveloperParty( party );
}



} //namespace lobby
