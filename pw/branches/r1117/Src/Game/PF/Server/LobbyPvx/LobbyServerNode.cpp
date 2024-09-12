#include "stdafx.h"
#include "LobbyServerNode.h"

#include "Client/LobbyPvx/RLobbyClientInterface.auto.h"
#include "LLobbyIServerInstance.auto.h"
#include "LLobbyIEntrance.auto.h"
#include "HybridServer/HybridServerDispencer.h"
#include "HybridServer/LPeered.auto.h"
#include "HybridServer/RGameServerDispenserIface.auto.h"
#include "HybridServer/LGameServerDispenserIface.auto.h"
#include "Server/GameSession/GameBalancer/GameBalancerTypes.h"
#include "Server/GameSession/GameBalancer/RGameBalancerIface.auto.h"
#include "Server/GameSession/GameBalancer/LGameBalancerIface.auto.h"
#include "Network/LSessionKeyRegisterIface.auto.h"
#include "LISessionHybridLink.auto.h"
#include "LobbyEntrance.h"
#include "LobbyServerConnection.h"
#include "LobbyGameSession.h"
#include "LobbyCustomGame.h"
#include "SessionHybridLink.h"
#include "LobbySocialProxy.h"
#include "LobbyServerLoginWrapper.h"
#include "UserManagerSvc/LUserNotificationIface.auto.h"
#include "Server/GameChatController/GameChatController.h"
#include "Server/LobbySocial/ISocialLobbyPvxAck.h"
#include "Server/LobbySocial/LISocialLobbyPvxSvc.auto.h"
#include "Server/LiveMMaking/HeroesTable.h"
#include "Server/Statistic/GameStatClient.h"
#include "Server/Statistic/StatClientHttpDispatcher.h"
#include "Coordinator/CoordinatorClient.h"
#include "RdpTransport/RdpTransportUtils.h"
#include "ClientControl/LClientControlRemote.auto.h"
#include "Db/DBServer.auto.h"
#include <PF_GameLogic/PFResourcesCollection.h>

#include "Network/RUDP/UdpAddr.h"
#include "transport/TLTransportModule.h"
#include "transport/TLCfg.h"
#include "Network/ClusterConfiguration.h"
#include "Coordinator/CoordinatorClientInternals.h"

#include "System/InlineProfiler.h"
#include "LobbyLog.h"




NI_DEFINE_REFCOUNT( lobby::ServerNode );

namespace lobby
{



static string s_externalSocialLobbyAddr = string();

REGISTER_VAR( "lobby_ext_social_addr", s_externalSocialLobbyAddr, STORAGE_NONE );



class SocialPvxInterface : public socialLobby::IPvxSvc, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( SocialPvxInterface, socialLobby::IPvxSvc, BaseObjectMT );

public:
  SocialPvxInterface( ServerNode * _owner ) :
  owner( _owner )
  {}

  //socialLobby::IPvxSvc
  virtual void NewGame( TSocialGameId _gameId, const mmaking::SGame & _game, const socialLobby::PvxGameDetails & _gameDetails, socialLobby::IPvxAcknowledge * _ack )
  {
    LOBBY_LOG_MSG( "Creating social MM game %s", FmtSocGameId( _gameId ) );

    if ( StrongMT<ServerNode> ptr = owner.Lock() )
      ptr->NewGame( _gameId, _game, _gameDetails );

    NI_VERIFY( _ack, "", return );
    _ack->NewGameAck( _gameId );
  }

  virtual void NewReconnectingUser( TSocialGameId _gameId, socialLobby::TUserIdPvX _userId, socialLobby::IPvxAcknowledge * _ack )
  {
    LOBBY_LOG_MSG( "User reconnects to game. user=%d, game=%s", _userId, FmtSocGameId( _gameId ) );

    if ( StrongMT<ServerNode> ptr = owner.Lock() )
      ptr->NewReconnectingUser( _gameId, _userId );

    NI_VERIFY( _ack, "", return );
    _ack->NewReconnectingUserAck( _gameId, _userId );
  }

  virtual void NewSpectator( lobby::TSocialGameId _gameId, socialLobby::TUserIdPvX _userId, const string& _login, socialLobby::IPvxAcknowledge* _ack, const wstring& nickname )
  {
    LOBBY_LOG_MSG( "Spectator reconnects to game. user=%d, game=%s, login=%s", _userId, FmtSocGameId( _gameId ), _login );

    if ( StrongMT<ServerNode> ptr = owner.Lock() )
      ptr->NewSpectator( _gameId, _userId, _login, nickname );

    NI_VERIFY( _ack, "", return );
    _ack->NewSpectatorAck( _gameId, _userId );
  }

  virtual void UserLeftTheGameInCastle( lobby::TSocialGameId _gameId, socialLobby::TUserIdPvX _userId, NI_LPTR socialLobby::IPvxAcknowledge* _ack )
  {
    LOBBY_LOG_MSG( "User left the game in castle. user=%d, game=%s", _userId, FmtSocGameId( _gameId ) );

    if ( StrongMT<ServerNode> ptr = owner.Lock() )
      ptr->UserLeftTheGameInCastle( _gameId, _userId );

    NI_VERIFY( _ack, "", return );
    _ack->UserLeftTheGameInCastleAck( _gameId, _userId );
  }

private:
  WeakMT<ServerNode> owner;
};




ServerNode::ServerNode( const Transport::ServiceParams & _svcParams, const Transport::CustomServiceParams & _customParams ) :
Transport::BaseService( _svcParams, _customParams ),
nextCustomGameId( 1 ),
now( timer::Now() ),
startTicks( timer::GetTicks() ),
nextSocCleanup( 0 ),
nextStatusDump( 0 ), nextFatStatusDump( 0 ),
clientsCounter("lobby_clients", "")
{
  config = CreateConfigFromStatics();

  if ( !s_externalSocialLobbyAddr.empty() )
  {
    LOBBY_LOG_MSG( "Connecting to external social lobby service. ext_addr=%s", s_externalSocialLobbyAddr );

    CreateExtClusterTransport();

    if ( extClusterAddrTranslator )
      extClusterAddrTranslator->DefineRoute( socialLobby::serviceIds::Service, Network::NetAddress( s_externalSocialLobbyAddr ) );
    else
      CoordClient()->AddExplicitRoute( socialLobby::serviceIds::Service, Coordinator::SvcNetAddresses( Network::NetAddress( s_externalSocialLobbyAddr ), Network::NetAddress() ) );

    extClusterGateKeeper = new rpc::GateKeeper( extClusterTransport, SvcId(), Transport::autoAssignClientId, this );
    Reset( extClusterRpcFactory, new rpc::LocalEntityFactory( extClusterGateKeeper->GetGate() ) );
  }

  RegisterFrontendAttach<IServerInstance, LIServerInstance>();
  RegisterBackendAttach<GameBalancer::IBalancerCallback, GameBalancer::LIBalancerCallback>();
  RegisterBackendAttach<ISessionHybridLink, LISessionHybridLink>();
  RegisterBackendAttach<HybridServer::IGameServerDispenserCallback, HybridServer::LIGameServerDispenserCallback>();
  RegisterBackendAttach<Login::IAddSessionKeyCallback, Login::LIAddSessionKeyCallback>();
  RegisterBackendAttach<Peered::IGameServer, Peered::LIGameServer>();
  RegisterBackendAttach<clientCtl::ILoginSvcAllocationCallback, clientCtl::LILoginSvcAllocationCallback>();

  if ( extClusterRpcFactory )
    extClusterRpcFactory->RegisterAttach<socialLobby::IPvxSvc, socialLobby::LIPvxSvc>();
  else
    RegisterBackendAttach<socialLobby::IPvxSvc, socialLobby::LIPvxSvc>();

  entrance = new Entrance( this );

  RegisterFrontendObject<IEntrance>( entrance.Get(), serviceIds::Entrance );

  gameSrvBalancer = new rpc::IfaceRequester<GameBalancer::RIBalancer>;
  gameSrvBalancer->init( BackendGk(), GameBalancer::ServiceClass, GameBalancer::ServiceRpcIface );

  chatControl = new gamechat::GameChatController( BackendGk() );

  socialPvxInterface = new SocialPvxInterface( this );

  socialLobbyProxy = new SocialLobbyProxy( config, extClusterGateKeeper ? extClusterGateKeeper : BackendGk(), socialPvxInterface, SvcId() );

  LoadHeroes();

  StrongMT<StatisticService::ClientHttpDispatcher> statClDispatcher = new StatisticService::ClientHttpDispatcher;
  statistics = new StatisticService::GameStatClient( statClDispatcher, 0 );

  //Game server interface
  gameServerLink = new SessionHybridLink( this );

  if ( rdp_transport::RdpTransportEnabled() )
    loginSvcAgent = new RdpLoginWrapper( BackendGk() );
  else
    loginSvcAgent = new TcpLoginWrapper( BackendGk() );
}



ServerNode::~ServerNode()
{
  Reset( extClusterRpcFactory, 0 );

  if ( entrance )
    UnregisterFrontendObject<IEntrance>( entrance );
}



void ServerNode::OnConfigReload()
{
  config->ReloadConfig();

  socialLobbyProxy->OnConfigReload();
}



RIServerInstance * ServerNode::AddClient( RILobbyUser * user, int clientRevision )
{
  NI_PROFILE_FUNCTION_MEM;

  rpc::INode * node = user->GetNode(0);
  NI_VERIFY( node, "", return 0 );
  rpc::IPacketPipe::PipeInfo info = node->GetConnectedPipe()->GetInfo();

  TConnections::iterator it = connections.find( info.pipeId );
  NI_VERIFY( it != connections.end(), "", return 0 );

  StrongMT<ServerConnection> connection = it->second;
  NI_VERIFY( connection, "", return 0 );

  connection->Established( user, clientRevision );

  LOBBY_LOG_MSG( "Entered user %d, rev %d", connection->ClientId(), clientRevision );

  AutoPerfCounterRate( "users_inc_lobby", 1 );

  return RemotePtr<RIServerInstance>( connection );
}



void ServerNode::OnNewNode( Transport::IChannel * channel, rpc::Node * node )
{
  NI_PROFILE_FUNCTION;

  Transport::BaseService::OnNewNode( channel, node );

  TConnections::iterator it = GetConnectionForChannel( channel, true );
  if ( it != connections.end() )
    it->second->JustConnected( node );
}



void ServerNode::OnChannelClosed( Transport::IChannel * channel, rpc::Node * node )
{
  NI_PROFILE_FUNCTION;

  Transport::BaseService::OnChannelClosed( channel, node );

  TConnections::iterator it = GetConnectionForChannel( channel, false );
  if ( it != connections.end() )
    CloseConnection( it );
}



void ServerNode::OnCorruptData( Transport::IChannel * channel, rpc::Node * node )
{
  NI_PROFILE_FUNCTION;

  Transport::BaseService::OnCorruptData( channel, node );

  TConnections::iterator it = GetConnectionForChannel( channel, false );
  if ( it != connections.end() )
    CloseConnection( it );
}



void ServerNode::StartPreparingPvx( const SSocialUserPrepare & data )
{
  StrongMT<SocUserPrepareItem> item = new SocUserPrepareItem( SvcId(), data, startTicks );
  socialUsersToPrepare.push_back( item );
}



void ServerNode::SocialGameAborted( TGameId _gameId )
{
  socialLobbyProxy->GameFinished( _gameId, ETeam::None );
}



Network::NetAddress ServerNode::GetSvcAddress( const Transport::TServiceId & _serviceId )
{
  if ( CoordClient() )
    if ( StrongMT<Transport::IAddressTranslator> at = CoordClient()->GetFrontendAddressTranslator() )
      return at->GetSvcAddress( _serviceId );

  NI_ALWAYS_ASSERT( "Cannot access frontend Address Translator" );
  return Network::NetAddress();
}



void ServerNode::OnGameFinish( Peered::TSessionId _sessionId, EGameResult::Enum _gameResult, const StatisticService::RPC::SessionClientResults & _info, const nstl::vector<Peered::SClientStatistics> & _clientsStatistics )
{
  NI_PROFILE_FUNCTION;

  socialLobbyProxy->GameFinished( _sessionId, (ETeam::Enum)_info.sideWon );

  LogGameFinish( _sessionId, _gameResult, _info, _clientsStatistics );

  GameSession * game = FindGame( _sessionId );
  if ( game )
    game->OnGameFinish( _gameResult, _info, _clientsStatistics );
  else {
    LOBBY_LOG_ERR( "Game sessionId=%d not found on finish", FmtGameId( _sessionId ) );
    return;
  }
}



void ServerNode::OnGameCheated( Peered::TSessionId _sessionId, Transport::TClientId _clientId, ECheatType::Enum _cheatType, const char * _clientIp )
{
  LOBBY_LOG_MSG( "GameCheated: sessionId=%d, userId=%d, cheat=%d, ip=%s", FmtGameId( _sessionId ), _clientId, (int)_cheatType, _clientIp );
  if ( GameSession * game = FindGame( _sessionId ) )
    game->OnGameCheated( _clientId, _cheatType, _clientIp );

  //if ( ServerConnection * conn = FindConnection( _clientId ) )
  //  conn->OnCheat( _sessionId, _cheatType, _clientIp );

  StatisticService::RPC::UserCheatEvent statEvent;
  statEvent.ctx = StatisticService::RPC::SessionUserContext( _sessionId, _clientId );
  statEvent.cheatType = _cheatType;
  statEvent.clientIp = NStr::ToUnicode( _clientIp ? _clientIp : "" );
  statistics->Message( statEvent );
}



void ServerNode::OnChangeClientStatus( Peered::TSessionId _sessionId, const nstl::vector<Peered::BriefClientInfo> & _clientInfos )
{
  for ( int i = 0; i < _clientInfos.size(); ++i )
  {
    const Transport::TClientId clientId = _clientInfos[i].clientId;
    const Peered::Status st = _clientInfos[i].status;

    LOBBY_LOG_MSG( "OnChangeClientStatus: sessionId=%d, userId=%d, status=%d", FmtGameId( _sessionId ), clientId, (int)st );

    if ( st == Peered::Connecting )
    {
      socialLobbyProxy->UserEnteredPvX( clientId );
    }
    else if ( Peered::IsDisconnectedStatus( st ) )
    {
      const bool leaver = ( st == Peered::DisconnectedByCheatAttempt );

      socialLobbyProxy->UserDroppedFromPvX( clientId, leaver );

      // NUM_TASK не отправляем в статистику события о дисконнектах после окончания игры
      {
        const GameSession* const game = FindGame(_sessionId);
        // NOTE: hacky
        const bool gameFinished = (!game || game->CanBeRemoved(timer::Now()));

        if (gameFinished)
          continue;
      }

      StatisticService::RPC::UserDisconnectEvent statEvent;
      statEvent.ctx = StatisticService::RPC::SessionUserContext( _sessionId, clientId );
      statEvent.reason = st;
      statistics->Message( statEvent );
    }
  }
}



void ServerNode::LoadHeroes()
{
  StrongMT<mmaking::HeroesTable> customHeroes = new mmaking::HeroesTable;

  NDb::Ptr<NDb::HeroesDB> dbHeroes = NDb::SessionRoot::GetRoot()->logicRoot->heroes;

  for ( int i = 0; i < dbHeroes->heroes.size(); ++i )
  {
    NDb::Ptr<NDb::Hero> dbHero = dbHeroes->heroes[i];
    NI_VERIFY( dbHero, "Null hero in data", continue );

    mmaking::SHeroDescription descr;
    descr.id = dbHero->id;
    descr.sex = ( dbHero->gender == NDb::GENDER_FEMALE ) ? ESex::Female : ESex::Male;
    customHeroes->Add( descr );


    uint intHeroId = Crc32Checksum().AddString( dbHero->id.c_str() ).Get();
    heroIdMap[intHeroId] = dbHero->id.c_str();
  }
  customGameHeroes = customHeroes;
}


void ServerNode::GetClientUsername( Transport::TClientId userId, wstring & username )
{
  NI_PROFILE_FUNCTION;

  StrongMT<UserManager::IUserManagerAgent> uma = CoordClient()->GetUserManagerAgent();
  if ( uma && uma->FindUserName( userId, username ) )
    return;
  
  string asciiLogin;
  if ( GetLoginForActiveFrontendUser( userId, asciiLogin ) )
  {
    NStr::ToUnicode( &username, asciiLogin );
    return;
  }

  username = L"UnknownUser";
}



StrongMT<ServerConnection> ServerNode::NewConnection( Transport::TClientId clientId )
{
  StrongMT<ServerConnection> conn = new ServerConnection( config, this, clientId );

  SUserInfo info;
  info.userId = clientId;
  GetClientUsername( clientId, info.nickname );
  info.zzimaSex = ESex::Male;

  conn->SetUserInfo( info );

  return conn;
}



ServerNode::TConnections::iterator ServerNode::GetConnectionForChannel( Transport::IChannel * channel, bool createIfNeeded )
{
  NI_PROFILE_FUNCTION;

  NI_VERIFY( channel, "", return connections.end() );
  
  if ( !channel->GetAddress().IsClientConnection() )
    return connections.end();

  Transport::TClientId clientId = channel->GetInternalClientId();

  TConnections::iterator it = connections.find( clientId );
  if ( it == connections.end() )
  {
    if ( createIfNeeded )
    {
      std::pair<TConnections::iterator, bool> insertResult =
          connections.insert( TConnections::value_type( clientId, NewConnection( clientId ) ) );
      clientsCounter.AddValue(1);

      NI_ASSERT( insertResult.second, "Server instance insert failed" );

      return insertResult.first;
    }
    return it;
  }

  NI_ASSERT( clientId == it->second->ClientId(), "" );
  return it;
}



ServerConnection * ServerNode::FindConnection( Transport::TClientId clientId )
{
  TConnections::iterator it = connections.find( clientId );
  if ( it == connections.end() )
    return 0;
  return it->second;
}



void ServerNode::CloseConnection( ServerNode::TConnections::iterator it )
{
  NI_PROFILE_FUNCTION;

  NI_VERIFY( it != connections.end(), "", return );
  StrongMT<ServerConnection> conn = it->second;
  NI_VERIFY( conn, "", return );

  LOBBY_LOG_MSG( "User %d leaves", conn->ClientId() );

  conn->Disconnected( now );
  connections.erase( it );
  clientsCounter.DecValue(1);

  StrongMT<CustomGame> game = conn->GetCustomGame();
  if ( game )
    game->RemovePlayer( conn );
}



EOperationResult::Enum ServerNode::JoinSocialGame( ServerConnection * connection )
{
  LOBBY_LOG_MSG( "User %d wants to join social game", connection->ClientId() );

  TSocialPlayerGames::iterator socGameIt = socialPlayers.find( connection->ClientId() );
  if ( socGameIt == socialPlayers.end() )
  {
    LOBBY_LOG_MSG( "No social game found for userId %d", connection->ClientId() );
    return EOperationResult::GameNotFound;
  }

  WeakMT<GameSession> gameWp = socGameIt->second;
  StrongMT<GameSession> lockedGame = gameWp.Lock();

  if ( !lockedGame )
  {
    LOBBY_LOG_MSG( "Social game for userId %d is rotten", connection->ClientId() );
    return EOperationResult::GameNotFound;
  }

  EOperationResult::Enum result = lockedGame->AddPlayerToSocialGame( connection );

  LOBBY_LOG_MSG( "User %d joined social game, code %d (%s)", connection->ClientId(), (int)result, EOperationResult::ToString(result) );
  return result;
}



StrongMT<CustomGame> ServerNode::CreateCustomGame( const SGameParameters & _params, int autostartPlayers )
{
  const TGameId gameId = nextCustomGameId++;

  return new CustomGame( config, gameId, _params, customGameHeroes, autostartPlayers );
}



void ServerNode::InsertGame( GameSession * _game )
{
  std::pair<TGames::iterator, bool> result = games.insert( TGames::value_type( _game->Id(), _game ) );
  if ( !result.second )
    LOBBY_LOG_ERR( "Failed to insert game with id %016x", _game->Id() );
}



void ServerNode::InsertCustomGame( CustomGame * _game )
{
  std::pair<TCustomGames::iterator, bool> result = customGames.insert( TCustomGames::value_type( _game->Id(), _game ) );
  if ( !result.second )
    LOBBY_LOG_ERR( "Failed to insert custom game with id %d", _game->Id() );
}



void ServerNode::Poll( timer::Time _now )
{
  NI_PROFILE_FUNCTION_MEM;

  now = NHPTimer::GetScalarTime();

  if ( extClusterGateKeeper )
    extClusterGateKeeper->Poll();

  socialLobbyProxy->Poll( now, (unsigned)connections.size() );
  gameSrvBalancer->step();

  if ( loginSvcAgent )
    loginSvcAgent->Poll();

  PollGames();
  PollCustomGames();
  PollChatChannels();
  PollSocPreparation();
  CleanupSocialLists();
  StatusDump();
}



void ServerNode::PollGames()
{
  NI_PROFILE_FUNCTION;

  for( TGames::iterator it = games.begin(); it != games.end(); )
  {
    StrongMT<GameSession> & game = it->second;
    game->Poll( now );

    const TGameId gameId = it->first;

    if ( game->CanBeRemoved( now ) )
    {
      LOBBY_LOG_MSG( "Removing empty game %s", FmtGameId( gameId ) );
      it = games.erase( it ); //'game' is no longer valid
    }
    else
      ++it;
  }
}



void ServerNode::PollCustomGames()
{
  NI_PROFILE_FUNCTION;

  for( TCustomGames::iterator it = customGames.begin(); it != customGames.end(); )
  {
    StrongMT<CustomGame> & game = it->second;
    game->Poll( now );

    const TGameId gameId = it->first;

    if ( game->State() == ECustomGameState::Starting )
    {
      LOBBY_LOG_MSG( "Starting custom game %s", FmtGameId( gameId ) );

      StartCustomGame( game );
      it = customGames.erase( it );
    }
    else if ( game->State() == ECustomGameState::Empty )
    {
      LOBBY_LOG_MSG( "Removing empty custom game %s", FmtGameId( gameId ) );
      it = customGames.erase( it );
    }
    else
      ++it;
  }
}



void ServerNode::PollSocPreparation()
{
  NI_PROFILE_FUNCTION_MEM;

  for ( TSocUserPrepareLine::iterator it = socialUsersToPrepare.begin(); it != socialUsersToPrepare.end(); )
  {
    SocUserPrepareItem * item = it->Get();

    ESocUserPreparation::Enum st = item->Poll( loginSvcAgent, now );

    if ( st == ESocUserPreparation::Done )
    {
      socialLobbyProxy->PvXPreparedForUser( item->Data().pvxUid, item->Key() );
      it = socialUsersToPrepare.erase( it );
    }
    else if ( st == ESocUserPreparation::Failed )
      it = socialUsersToPrepare.erase( it );
    else
      ++it;
  }
}



void ServerNode::NewGame( TSocialGameId _gameId, const mmaking::SGame & _game, const socialLobby::PvxGameDetails & _gameDetails )
{
  NI_PROFILE_FUNCTION;

  NI_VERIFY( gameSrvBalancer && gameSrvBalancer->isopen(), "No game server balancer!", return );

  SGameParameters params;
  params.gameType = EGameType::SocialMMaking;
  params.name = L"Social MM";
  params.mapId = _game.mapId;
  params.slotsCount = _game.humans.size();
  params.maxPlayersPerTeam = _game.humans.size() / 2;
  params.randomSeed = GetGameRandom();
  params.manoeuvresFaction = _game.manoeuvresFaction;
  params.hadPreGameLobby = _gameDetails.preGameLobby;
  params.customGame = _gameDetails.customGame;
  params.guildData = _gameDetails.guildData;
  params.sessiontype = _gameDetails.sessiontype;

  StrongMT<GameSession> gameSess = NewGameSession( _gameId, params );
  if ( !gameSess )
    return;
  gameSess->SetupSocialMMaking( _game, _gameDetails, config->Cfg()->myExternalLocation, heroIdMap );

  LOBBY_LOG_MSG( "Social MM game %s created", gameSess->StrId() );

  InsertGame( gameSess );

  for ( int pi = 0; pi < _game.humans.size(); ++pi )
    for ( int mi = 0; mi < _game.humans[pi].members.size(); ++mi )
    {
      const mmaking::SRequestMember & member = _game.humans[pi].members[mi];
      WeakMT<GameSession> & gameSlot = socialPlayers[member.mmId];
      if ( StrongMT<GameSession> prevGame = gameSlot.Lock() )
        LOBBY_LOG_WRN( "User %d is already waiting for social game %s. Re-assigned.", member.mmId, prevGame->StrId() );
      gameSlot = gameSess;
    }
}



void ServerNode::NewReconnectingUser( TSocialGameId _gameId, socialLobby::TUserIdPvX _userId )
{
  TGames::iterator it = games.find( _gameId );
  if ( it == games.end() )
  {
    LOBBY_LOG_ERR( "Unknown social game to reconnect to. gameid=%s", FmtSocGameId( _gameId ) );
    return;
  }

  StrongMT<GameSession> game = it->second;

  WeakMT<GameSession> & slot = socialPlayers[_userId];

  game->PlayerReconnects( _userId );
  slot = game;
}



void ServerNode::NewSpectator( TSocialGameId _gameId, socialLobby::TUserIdPvX _userId, const string & _login, const wstring& nickname )
{
  TGames::iterator it = games.find( _gameId );
  if ( it == games.end() )
  {
    LOBBY_LOG_ERR( "Unknown social game to spectate. gameid=%s", FmtSocGameId( _gameId ) );
    return;
  }

  StrongMT<GameSession> game = it->second;

  WeakMT<GameSession> & slot = socialPlayers[_userId];

  game->SpectatorReconnects( _userId, _login, nickname );
  slot = game;
}



void ServerNode::UserLeftTheGameInCastle( lobby::TSocialGameId _gameId, socialLobby::TUserIdPvX _userId )
{
  TGames::iterator it = games.find( _gameId );
  if ( it == games.end() )
  {
    LOBBY_LOG_ERR( "Unknown social game to leave. gameid=%s", FmtSocGameId( _gameId ) );
    return;
  }

  StrongMT<GameSession> game = it->second;

  game->UserLeftFromCastle( _userId );
}



void ServerNode::PollChatChannels()
{
  NI_PROFILE_FUNCTION_MEM;
  chatControl->step();
}



GameSession * ServerNode::NewGameSession( TGameId id, const SGameParameters & params )
{
  NI_VERIFY( gameSrvBalancer && gameSrvBalancer->isopen(), "No game server balancer!", return 0 );

  return new GameSession( config, id, params, now, this, gameSrvBalancer->iface(), chatControl, statistics );
}



void ServerNode::StartCustomGame( CustomGame * game )
{
  StrongMT<GameSession> gameSess = NewGameSession( game->Id(), game->Params() );
  if ( !gameSess )
    return;
  gameSess->SetupFromCustomGame( game );

  LOBBY_LOG_MSG( "Created game session from custom game %d", game->Id() );

  InsertGame( gameSess );
}



void ServerNode::CleanupSocialLists()
{
  NI_PROFILE_FUNCTION;

  if ( now < nextSocCleanup )
    return;
  nextSocCleanup = now + 60.0;

  for ( TSocialPlayerGames::iterator it = socialPlayers.begin(); it != socialPlayers.end(); )
  {
    if ( !it->second.Lock() )
    {
      it = socialPlayers.erase( it );
      continue;
    }
    ++it;
  }
}



GameSession * ServerNode::FindGame( TGameId _gameId )
{
  NI_PROFILE_HEAVY_FUNCTION;

  TGames::iterator it = games.find( _gameId );
  if ( it == games.end() )
    return 0;
  return it->second;
}



void ServerNode::LogGameFinish( Peered::TSessionId _sessionId, EGameResult::Enum _gameResult, const StatisticService::RPC::SessionClientResults & _info, const nstl::vector<Peered::SClientStatistics> & _clientsStatistics )
{
  StatisticService::RPC::SessionResultEvent statResult;
  statResult.result = _gameResult;
  statResult.sessionid = _sessionId;
  statResult.clientData = _info;

  statResult.serverPlayersInfo.resize( _clientsStatistics.size() );
  for ( int i = 0; i < _clientsStatistics.size(); ++i ) {
    statResult.serverPlayersInfo[i].userid = _clientsStatistics[i].clientId;
    statResult.serverPlayersInfo[i].finishStatus = _clientsStatistics[i].clientState;
  }

  statistics->Message( statResult );
  LOBBY_LOG_MSG( "Game %s LogSessionResults called", FmtGameId( _sessionId ) );
}



int ServerNode::CountActiveConnections()
{
  NI_PROFILE_HEAVY_FUNCTION;

  int activeConn = 0;
  for ( TConnections::iterator it = connections.begin(); it != connections.end(); ++it )
    if ( it->second->Status() == EConnectionStatus::Established )
      ++activeConn;
  return activeConn;
}



void ServerNode::StatusDump()
{
  NI_PROFILE_FUNCTION;

  if ( !config->Cfg()->statusDumpInterval )
    return;

  if ( now < nextStatusDump )
    return;

  nextStatusDump = now + config->Cfg()->statusDumpInterval;

  LOBBY_LOG_MSG( "Status: %d connections (%d active), %d games", connections.size(), CountActiveConnections(), games.size() );

  if ( !config->Cfg()->fatStatusDumpInterval )
    return;
  if ( now < nextFatStatusDump )
    return;
  nextFatStatusDump = now + config->Cfg()->fatStatusDumpInterval;

  if ( !connections.empty() )
  {
    LOBBY_LOG_MSG( "Dumping all connections:" );
    for ( TConnections::iterator it = connections.begin(); it != connections.end(); ++it )
    {
      ServerConnection * conn = it->second;
      NI_VERIFY( conn, "", continue );
      LOBBY_LOG_MSG( "  Connection %d, st %d, %s",
        it->first,
        (int)conn->Status(),
        conn->RemoteUser() ? "has client" : "no client" );
    }
  }

  if ( !games.empty() )
  {
    LOBBY_LOG_MSG( "Dumping all sessions:" );
    for( TGames::iterator it = games.begin(); it != games.end(); ++it )
      it->second->Dump();
  }
}



int ServerNode::GetGameRandom()
{
  return config->Cfg()->gameFixedRandom ? config->Cfg()->gameFixedRandom : random.Next();
}



void ServerNode::CreateExtClusterTransport()
{
  //TCP to TCP connection
  if ( !rdp_transport::RdpTransportEnabled() )
  {
    extClusterTransport = BackendTransport();
    return;
  }

  //RDP to RDP connection
  ni_udp::NetAddr udpSvcAddr;
  unsigned udpSvcMux = 0;
  if ( rdp_transport::ParseAddress( udpSvcAddr, udpSvcMux, s_externalSocialLobbyAddr.c_str() ) && udpSvcMux )
  {
    extClusterTransport = BackendTransport();
    return;
  }

  StrongMT<Coordinator::ClassRoutes> classRoutes = new Coordinator::ClassRoutes;
  extClusterAddrTranslator = new Coordinator::AddressTranslator( "ext_cluster", classRoutes );

  TL::Cfg cfg;
  cfg.firstServerPort = Network::GetFirstServerPort();
  cfg.mf_ = Transport::GetGlobalMessageFactory();
  cfg.at_ = extClusterAddrTranslator;
  cfg.threads_ = TL::GlobalCfg::GetThreads();
  cfg.loglvl_ = TL::GlobalCfg::GetLogLevel();
  cfg.terabit_loglvl_ = TL::GlobalCfg::GetTerabitLogLevel();
  cfg.read_block_size_ = TL::GlobalCfg::GetReadBlockSize();
  cfg.so_rcvbuf_ = TL::GlobalCfg::GetSoRcvbuf();
  cfg.so_sndbuf_ = TL::GlobalCfg::GetSoSndbuf();
  cfg.disableNagleAlgorithm_ = TL::GlobalCfg::GetDisableNagleAlgorithm();
  cfg.so_keepalive_ = TL::GlobalCfg::GetSoKeepalive();
  cfg.mbHeapDumpFreq_ = TL::GlobalCfg::GetMessageBlockHeapDumpFreq();
  cfg.mbHeapPerConnection_ = TL::GlobalCfg::GetMessageBlockHeapPerConnection();
  cfg.mbNotypeUseThreshold_ = TL::GlobalCfg::GetMessageBlockNotypeUseThreshold();
  cfg.mbWriteUseThreshold_ = TL::GlobalCfg::GetMessageBlockWriteUseThreshold();
  cfg.mbReadUseThreshold_ = TL::GlobalCfg::GetMessageBlockReadUseThreshold();
  cfg.logWrittenBytes_ = TL::GlobalCfg::GetLogWrittenBytes();
  cfg.checkActivityTimeout_ = TL::GlobalCfg::GetCheckActivityTimeout();

  extClusterTransport = TransportLayer::CreateTransportSystem(cfg);
}

} //namespace lobby
