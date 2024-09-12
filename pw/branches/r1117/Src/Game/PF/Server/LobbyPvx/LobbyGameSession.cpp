#include "stdafx.h"
#include "LobbyGameSession.h"
#include "LobbyServerConnection.h"
#include "LobbyCustomGame.h"
#include "LobbyConfig.h"
#include "Server/GameSession/GameBalancer/RGameBalancerIface.auto.h"
#include "Server/Statistic/GameStatClient.h"
#include "Server/Statistic/StatisticsServerTypes.h"
#include "Db/DBServer.auto.h"
#include "HybridServer/RGameServerDispenserIface.auto.h"
#include "HybridServer/RPeered.auto.h"
#include "RISessionHybridLink.auto.h"
#include "Client/LobbyPvx/RLobbyClientInterface.auto.h"
#include "Server/ServerAppBase/ServerCfg.h"
#include "System/Crc32Checksum.h"
#include "LobbyLog.h"

namespace lobby
{

NI_ENUM_BEGIN_STD( EGameState )
  NI_ENUM_ITEM( Empty )
  NI_ENUM_ITEM( WaitingGameServer )
  NI_ENUM_ITEM( WaitingLogSessionStartAck )
  NI_ENUM_ITEM( InGame )
NI_ENUM_END_STD

}

namespace lobby
{

GameSession::GameSession( IConfigProvider * _cfg, TGameId _gameId, const SGameParameters & _params, timer::Time _now,
      IGameSessionOwner * _owner,
      GameBalancer::RIBalancer * _gameBalancer,
      gamechat::IGameChatController * _chatControl,
      StatisticService::GameStatClient * _statistics ) :
owner( _owner ),
config( _cfg ),
state( EGameState::Empty ),
gameId( _gameId ),
params( _params ),
gameSrvBalancer( _gameBalancer ),
asyncOpStartedTime( 0.0 ),
lastDisconnectTime( _now ),
chatControl( _chatControl ),
statistics( _statistics ),
gameServerLostTime( 0 )
{
  strGameId = FmtGameId( gameId );

  LOBBY_LOG_MSG( "Creating game id=%s, name='%s', seed=0x%08x", strGameId, NStr::ToMBCS( params.name ).c_str(), params.randomSeed );
}



GameSession::~GameSession()
{
}



void GameSession::Poll( NHPTimer::FTime now )
{
  NI_PROFILE_FUNCTION;

  if ( state == EGameState::WaitingGameServer )
  {
    if ( now > asyncOpStartedTime + config->Cfg()->hybridRequestTimeout )
    {
      LOBBY_LOG_ERR( "Game server request timed out (%.1f), killing game %s", config->Cfg()->hybridRequestTimeout, strGameId );
      AbortSocialGame();
    }
  }
  else if ( state == EGameState::WaitingLogSessionStartAck )
  {
    if ( now > asyncOpStartedTime + config->Cfg()->statisticsAckTimeout )
    {
      LOBBY_LOG_ERR( "Statistics acknowledge timed out (%.1f), game %s", config->Cfg()->statisticsAckTimeout, strGameId );
      statistics = 0;
      Start();
    }
  }
  else if ( state == EGameState::InGame )
  {
    PollGSConnection( now );
  }
}



void GameSession::PollGSConnection( NHPTimer::FTime now )
{
  if ( !config->Cfg()->lostGameServerTimeout )
    return;

  NI_VERIFY( gameServerInternal, "No game server", return );

  if ( gameServerInternal->GetStatus() == rpc::Connected ) {
    gameServerLostTime = 0;
    return;
  }

  if ( !gameServerLostTime ) {
    gameServerLostTime = now;
    LOBBY_LOG_ERR( "Lost connection to game server, game %s", strGameId );
    return;
  }

  if ( now < gameServerLostTime + config->Cfg()->lostGameServerTimeout )
    return;


  LOBBY_LOG_ERR( "Lost connection to game server, removing game %s", strGameId );
  AbortSocialGame();
}



void GameSession::SetupSocialMMaking( const mmaking::SGame & _game, const socialLobby::PvxGameDetails & _gameDetails, const string & _svcPath, const THeroIdMap & _heroIdMap )
{
  NI_PROFILE_FUNCTION;

  LOBBY_LOG_MSG( "Preparing to start social game %s", strGameId );

  NI_VERIFY( state == EGameState::Empty, "", return );
  NI_VERIFY( params.gameType == EGameType::SocialMMaking, "", return );
  NI_ASSERT( !_game.humans.empty(), "Asocial social game" );
  NI_ASSERT( !_gameDetails.playerDetails.empty(), "No players details" );

  StrongMT<IGameSessionOwner> lowner = owner.Lock();
  NI_VERIFY( lowner, "", return );

  socialGameData = _game;
  socialGameDetails = _gameDetails;

  int playersCnt = 0;
  for ( int pi = 0; pi < socialGameData.humans.size(); ++pi )
    playersCnt += socialGameData.humans[pi].members.size();

  params.slotsCount = playersCnt;

  lineup.reserve( params.slotsCount + socialGameData.bots.size() );

  gameServerData.clear();
  gameServerData.reserve( 10 );

  for ( int pi = 0; pi < socialGameData.humans.size(); ++pi )
    for ( int mi = 0; mi < socialGameData.humans[pi].members.size(); ++mi )
    {
      const mmaking::SRequestMember & member = socialGameData.humans[pi].members[mi];
      mmaking::TUserId clId = member.mmId;

      const socialLobby::PlayerDetails * details = socialGameDetails.FindPlayer( clId );
      if ( !details ) {
        LOBBY_LOG_ERR( "Creating pvx game. User got no player details. pvxuid=%d, gameid=%d", clId, strGameId );
        continue;
      }

      LOBBY_LOG_MSG( "User %d from game %s got %d talents", clId, strGameId, details->gameData.talents.size() );

      {
        SUserInfo uinfo( clId, member.sex, details->nick.c_str() );
        SPlayerGameContext uctx( EPlayerType::Human, socialGameData.humans[pi].common.team, member.original_team, member.heroId.c_str() );

        //In Guard game, hero can be changed after matchmaking
        //Override hero from lineup with hero from playerData
        THeroIdMap::const_iterator heroIdIt = _heroIdMap.find( details->gameData.heroId );
        if ( heroIdIt != _heroIdMap.end() )
          uctx.hero = heroIdIt->second.c_str();
        else
          LOBBY_LOG_ERR( "Unknown hero id %d, user=%d", details->gameData.heroId, clId );

        lineup.push_back( SGameMember( uinfo, uctx ) );
      }

      gameServerData.push_back();
      Peered::ClientInfo & info = gameServerData.back();
      info.clientId = clId;
      info.info = details->gameData;
    }

  for ( int i = 0; i < socialGameData.bots.size(); ++i )
  {
    lineup.push_back();
    SGameMember & memb = lineup.back();
    memb.context.playerType = EPlayerType::Computer;
    memb.context.team = socialGameData.bots[i].team;
    memb.context.hero = socialGameData.bots[i].heroId;
    memb.context.botSkin = socialGameData.bots[i].heroSkin;
  }

  ServeGameServer( _svcPath.c_str() ); 
}



void GameSession::SetupFromCustomGame( CustomGame * _customGame )
{
  customGame = _customGame;

  customGame->SetupGameStartInfo( gameServerData, lineup );

  ServeGameServer( HostServer::Cfg::GetSvcPath().c_str() ); 
}



EOperationResult::Enum GameSession::ReconnectToCustomGame( ServerConnection * player )
{
  LOBBY_LOG_MSG( "Trying to rejoin player %d to custom game %s...", player->ClientId(), strGameId );

  if ( state != EGameState::InGame )
  {
    LOBBY_LOG_WRN( "Social game %s is in wrong state %s (%d)", strGameId, EGameState::ToString( state ), (int)state );
    return EOperationResult::InternalError;
  }

  NI_VERIFY( ( gameServer || gameSvcInstId.Valid() ) && gameServerInternal, "", return EOperationResult::InternalError );
  NI_VERIFY( player->RemoteUser(), "", return EOperationResult::InternalError );

  gameServerInternal->OnRejoinClient( player->ClientId(), this, &GameSession::OnRejoinClientAnswer );

  player->RemoteUser()->StartSession( gameId, params, lineup, gameServer, gameSvcInstId, (unsigned)Timestamp() );
  return EOperationResult::Ok;
}



EOperationResult::Enum GameSession::SpectateCustomGame( ServerConnection * player )
{
  LOBBY_LOG_MSG( "Player %d trying to spectate custom game %s...", player->ClientId(), strGameId );

  if ( state != EGameState::InGame )
  {
    LOBBY_LOG_WRN( "Social game %s is in wrong state %s (%d)", strGameId, EGameState::ToString( state ), (int)state );
    return EOperationResult::InternalError;
  }

  NI_VERIFY( gameServer || gameSvcInstId.Valid(), "", return EOperationResult::InternalError );
  NI_VERIFY( player->RemoteUser(), "", return EOperationResult::InternalError );

  gameServerInternal->AddSpectator( player->ClientId(), player->UserInfo().nickname );

  player->RemoteUser()->StartSession( gameId, params, lineup, gameServer, gameSvcInstId, (unsigned)Timestamp() );

  AddToChatControl(player->ClientId(), lobby::ETeam::None);

  return EOperationResult::Ok;
}



inline bool CheckPlayerPresence( const mmaking::SGame & game, Transport::TClientId userId )
{
  for ( int pi = 0; pi < game.humans.size(); ++pi )
    for ( int mi = 0; mi < game.humans[pi].members.size(); ++mi )
      if ( userId == game.humans[pi].members[mi].mmId )
        return true;
  return false;
}



EOperationResult::Enum GameSession::AddPlayerToSocialGame( ServerConnection * player )
{
  NI_PROFILE_FUNCTION;

  LOBBY_LOG_MSG( "Trying to add player to social game. userid=%d, game_id=%s, map=%s", player->ClientId(), strGameId, params.mapId );

  if ( state != EGameState::InGame )
  {
    LOBBY_LOG_WRN( "Social game %s is in wrong state %s (%d)", strGameId, EGameState::ToString( state ), (int)state );
    return EOperationResult::InternalError;
  }

  NI_VERIFY( gameServer || gameSvcInstId.Valid(), "", return EOperationResult::InternalError );

  if ( !CheckPlayerPresence( socialGameData, player->ClientId() ) && ( spectators.find( player->ClientId() ) == spectators.end() ) )
  {
    LOBBY_LOG_WRN( "Player %d not found in social game %s", player->ClientId(), strGameId );
    return EOperationResult::InternalError;
  }

  if ( player->RemoteUser() )
    player->RemoteUser()->StartSession( gameId, params, lineup, gameServer, gameSvcInstId, (unsigned)Timestamp() );

  return EOperationResult::Ok;
}



void GameSession::PlayerReconnects( socialLobby::TUserIdPvX clientid )
{
  NI_VERIFY( gameServerInternal, "", return );
  gameServerInternal->OnRejoinClient( clientid, this, &GameSession::OnRejoinClientAnswer );

  StartPreparingPvx( clientid, 0 );
}



void GameSession::SpectatorReconnects( socialLobby::TUserIdPvX clientid, const string & login, const wstring& nickname )
{
  NI_VERIFY( gameServerInternal, "", return );
  gameServerInternal->AddSpectator( clientid, nickname );

  spectators.insert( clientid );

  //FIXME: Assuming chat control is ready
  AddToChatControl( clientid, lobby::ETeam::None );

  StartPreparingPvx( clientid, login.c_str() );
}



void GameSession::OnRejoinClientAnswer( bool result )
{
  //TODO: implement
}



void GameSession::UserLeftFromCastle( socialLobby::TUserIdPvX _userId )
{
  NI_VERIFY( gameServerInternal, "", return );
  gameServerInternal->UserLeftTheGameInCastle( _userId );
}



void GameSession::ServeGameServer( const char * _balancerSvcPath )
{
  LOBBY_LOG_MSG( "Starting game server allocation process with svc path '%s', game %s...", _balancerSvcPath, strGameId );

  NI_VERIFY( gameSrvBalancer, "", return );

  state = EGameState::WaitingGameServer;
  asyncOpStartedTime = NHPTimer::GetScalarTime();
  gameSrvBalancer->AllocateGameSvc( _balancerSvcPath, gameId, RemotePtr<GameBalancer::RIBalancerCallback>( this ), this, &GameSession::OnAllocateGameSvcResult, 0 );
}



void GameSession::SetupAuxGameServerData( Peered::SAuxData & gsAuxData )
{
  gsAuxData.lobbyGameType = params.gameType;
  gsAuxData.mapType = socialGameData.mapType;
  gsAuxData.mmBasket = socialGameData.basket;
  gsAuxData.socialLobbyGameId = gameId;
  gsAuxData.hadPreGameLobby = socialGameDetails.preGameLobby;
  gsAuxData.customGame = socialGameDetails.customGame;
  gsAuxData.guildData = params.guildData;
  gsAuxData.sessiontype = params.sessiontype;

  if ( socialGameData.mapType != NDb::MAPTYPE_NONE )
  {
    gsAuxData.mapDesc = socialGameData.mapId;
  }

  gsAuxData.users.reserve( socialGameDetails.playerDetails.size() );
  for ( int pi = 0; pi < socialGameData.humans.size(); ++pi )
  {
    const mmaking::SGameParty & pty = socialGameData.humans[pi];
    for ( int mi = 0; mi < socialGameData.humans[pi].members.size(); ++mi )
    {
      const mmaking::SRequestMember & memb = pty.members[mi];

      if ( const socialLobby::PlayerDetails * details = socialGameDetails.FindPlayer( memb.mmId ) )
        LOBBY_LOG_MSG( "User %d from game %s got %d talents", memb.mmId, strGameId, details->gameData.talents.size() );
      else {
        LOBBY_LOG_ERR( "User %d from game %s got no player details", memb.mmId, strGameId );
        continue;
      }

      gsAuxData.users.push_back();
      Peered::SAuxUserData & gsUser = gsAuxData.users.back();
      gsUser.clientId = memb.mmId;
      gsUser.faction = pty.common.team;
    }
  }
}



void GameSession::OnAllocateGameSvcResult( int _result, int, rpc::CallStatus _st )
{
  LOBBY_LOG_MSG( "Game server allocation result arrived. code=%d, gameid=%s, rpc_st=%d", _result, strGameId, (int)_st );
  NI_VERIFY( _result >= 0, "", return );

  if ( ( _st != rpc::CallSuccessful ) || ( _result < 0 ) )
  {
    LOBBY_LOG_ERR( "Game server allocation failed. gameid=%s", strGameId );
    AbortSocialGame();
  }
  //TODO: Prematurely close game session on error
}



void GameSession::OnGameSvcAllocated( Peered::TSessionId userctx, uint allocid, HybridServer::IGameServerDispenser * gsd )
{
  LOBBY_LOG_MSG( "Game server dispencer recieved. gameid=%s, ptr=0x%08x", strGameId, (void*)gsd );
  StrongMT<HybridServer::RIGameServerDispenser> remoteDisp = dynamic_cast<HybridServer::RIGameServerDispenser *>( gsd );

  if ( !remoteDisp ) {
    LOBBY_LOG_ERR( "Null game server dispencer for game %s", strGameId );
    return;
  }

  StrongMT<IGameSessionOwner> lowner = owner.Lock();
  NI_VERIFY( lowner, "", return );

  Peered::SAllocationParams allocPrms;
  allocPrms.allocid = allocid;
  allocPrms.sessionId = gameId;
  allocPrms.clientsInfo = gameServerData;
  SetupAuxGameServerData( allocPrms.auxData );
  allocPrms.gameParams = params;
  allocPrms.gameLineUp = lineup;

  remoteDisp->AcquireNewServer( allocPrms, lowner->GameServerLink(), this );
}



void GameSession::GameServerAllocated( Peered::RIGameServer * _clientsInterface, Peered::RIGameServerInternal * _internalInterface, const Peered::SInstanceId& _instId )
{
  NI_PROFILE_FUNCTION;

  LOBBY_LOG_DBG( "Game server allocated. front=%08x, back=%08x, svcid=%s, instid=%s", (void*)_clientsInterface, (void*)_internalInterface, _instId.serviceId, _instId.instanceId );

  NI_ASSERT( !gameServerInternal, "" );
  NI_ASSERT( !gameServer, "" );
  NI_ASSERT( !gameSvcInstId.Valid(), "" );
  NI_VERIFY( state == EGameState::WaitingGameServer, "", return );
  NI_VERIFY( ( _clientsInterface || _instId.Valid() ) && _internalInterface, "", return );

  asyncOpStartedTime = 0.0;
  gameServer = _clientsInterface;
  gameServerInternal = _internalInterface;
  gameSvcInstId = _instId;

  if ( statistics )
    BeginNotifyStatistics();
  else {
    LOBBY_LOG_MSG( "Game %s LogSessionStart call skipped", strGameId );
    Start();
  }
}



void GameSession::BeginNotifyStatistics()
{
  NI_PROFILE_FUNCTION;

  LOBBY_LOG_MSG( "Game %s LogSessionStart called, waiting ack...", strGameId );

  NI_ASSERT( statistics, "" );
  state = EGameState::WaitingLogSessionStartAck;
  asyncOpStartedTime = NHPTimer::GetScalarTime();

  StatisticService::EGameType::Enum gameType = StatisticService::EGameType::None;
  if ( params.gameType == EGameType::Custom )
    gameType = StatisticService::EGameType::Dev_Custom;
  else if ( params.gameType == EGameType::SocialMMaking )
  {
    if ( socialGameDetails.customGame )
    {
      if ( socialGameData.mapType == NDb::MAPTYPE_TRAINING )
        gameType = StatisticService::EGameType::Soc_CustomGameBots;
      else
        gameType = StatisticService::EGameType::Soc_CustomGame;
    }
    else if ( socialGameData.mapType == NDb::MAPTYPE_TRAINING )
    {
      ErrorTrace( "Training and NOT a custom-game! game_id=%s", strGameId );
      gameType = StatisticService::EGameType::Soc_Training;
    }
    else if ( ( socialGameData.mapType == NDb::MAPTYPE_PVP ) || ( socialGameData.mapType == NDb::MAPTYPE_CTE ) )
      gameType = StatisticService::EGameType::Soc_Matchmaking;
    else if ( socialGameData.mapType == NDb::MAPTYPE_TUTORIAL )
      gameType = StatisticService::EGameType::Soc_Tutorial;
    else if ( socialGameData.mapType == NDb::MAPTYPE_SERIES )
      gameType = StatisticService::EGameType::Soc_Singleplayer;
    else if ( socialGameData.mapType == NDb::MAPTYPE_COOPERATIVE )
      gameType = StatisticService::EGameType::Soc_Coop;
  }
  
  StatisticService::RPC::SessionStartEvent info;
  info.sessionid = gameId;
  info.persistentId = gameId;
  info.map = NStr::ToUnicode( params.mapId );
  info.cluster = NStr::ToUnicode( config->Cfg()->myExternalLocation );
  info.sessionType = (int)gameType;

  if ( gameServer )
  {
    if ( rpc::INode * gameServerNode = gameServer->GetHandler()->GetNode( 0 ) )
      info.server = NStr::ToUnicode( gameServerNode->GetName() );
  }
  else if ( gameSvcInstId.Valid() )
  {
    info.server = NStr::ToUnicode( gameSvcInstId.serviceId );

    StrongMT<IGameSessionOwner> lowner = owner.Lock();
    NI_VERIFY( lowner, "", return );

    if ( lowner )
      info.serverAddr = NStr::ToUnicode( lowner->GetSvcAddress( gameSvcInstId.serviceId.c_str() ) );
  }

  info.players.reserve( 10 );

  for ( int i = 0; i < lineup.size(); ++i )
  {
    const lobby::SGameMember & member = lineup[i];

    if ( member.context.playerType == EPlayerType::Human ) {
      info.players.push_back();
      StatisticService::RPC::SessionStartPlayer & dest = info.players.back();

      dest.userid = member.user.userId;
      dest.faction = member.context.team;
      dest.sex = member.user.zzimaSex;
      dest.heroid = Crc32Checksum().AddString( member.context.hero.c_str() ).Get();
      dest.nickname = member.user.nickname;
    }
  }

  statistics->Message( info );
  OnStatisticsSessionNotify( true ); //hack
}



void GameSession::OnStatisticsSessionNotify( bool _result )
{
  LOBBY_LOG_MSG( "Game %s got LogSessionStart ack(%d)", strGameId, _result );

  NI_VERIFY( state == EGameState::WaitingLogSessionStartAck, "", return );

  asyncOpStartedTime = 0.0;

  Start();
}



void GameSession::Start()
{
  NI_PROFILE_FUNCTION;

  LOBBY_LOG_MSG( "Game %s started", strGameId );

  NI_ASSERT( gameServer || gameSvcInstId.Valid(), "" );

  if ( chatControl )
  {
    vector<chat::ChannelName> chatChannelNames;
    chatChannelNames.push_back( gamechat::channels::Session);
    chatChannelNames.push_back( gamechat::channels::Team1 );
    chatChannelNames.push_back( gamechat::channels::Team2 );
    chatChannelNames.push_back( gamechat::channels::Team1_SmartChat );
    chatChannelNames.push_back( gamechat::channels::Team2_SmartChat );

    int rc = chatControl->OpenGameChat(gameId, chatChannelNames, this);
    if (rc < 0)
    {
      LOBBY_LOG_ERR( "ChatControl: can't create chat session (gameid=%s)", strGameId.c_str() );
    }
  }

  if ( customGame )
    for( int i = 0; i < customGame->Players().size(); ++i )
    {
      StrongMT<ServerConnection> plr = customGame->Players()[i].player;
      if ( plr->RemoteUser() )
        plr->RemoteUser()->StartSession( gameId, params, lineup, gameServer, gameSvcInstId, (unsigned)Timestamp() );
    }

  if ( StrongMT<IGameSessionOwner> lowner = LockOwnerForSocialFeedback() )
    for ( int i = 0; i < lineup.size(); ++i )
      if ( lineup[i].context.playerType == EPlayerType::Human )
        StartPreparingPvx( lineup[i].user.userId, 0 );

  customGame = 0;

  state = EGameState::InGame;
}



StrongMT<IGameSessionOwner> GameSession::LockOwnerForSocialFeedback()
{
  if ( params.gameType != EGameType::SocialMMaking )
    return 0;

  return owner.Lock();
}



void GameSession::Cleanup()
{
  LOBBY_LOG_MSG( "Game %s cleared", strGameId );

  chatControl->CloseGameChat(gameId);

  chatControl = 0;
  gameServer = 0;
  gameServerInternal = 0;
  gameSvcInstId.Clear();

  state = EGameState::Empty;
}



void GameSession::AbortSocialGame()
{
  if ( StrongMT<IGameSessionOwner> lowner = LockOwnerForSocialFeedback() )
    lowner->SocialGameAborted( gameId );

  Cleanup();
}



bool GameSession::CanBeRemoved( timer::Time _now ) const
{
  if ( state == EGameState::Empty )
    return true;

  return false;
}

void GameSession::OnOpenSessionChat(gamechat::GameSessionId const & _gameid, int _rc)
{
  NI_ASSERT(gameId == _gameid, "");

  if (_rc < 0)
  {
    LOBBY_LOG_ERR( "Open session chat FAILED (gameid=%s rc=%d)", strGameId, _rc );
  }
  else
  {
    LOBBY_LOG_MSG( "Open session chat completed (gameid=%s rc=%d)", strGameId, _rc );

    for( int i = 0; i < lineup.size(); ++i )
      if ( lineup[i].context.playerType == EPlayerType::Human )
        AddToChatControl( lineup[i].user.userId, lineup[i].context.team );
  }
}



namespace
{
  typedef vector<Peered::ClientInfo> TClientInfoVector;

  const int FindClientIndex(const TClientInfoVector& clients, const Transport::TClientId clientId)
  {
    for (int i = 0, count = clients.size(); i < count; ++i)
    {
      if (clients[i].clientId == clientId)
        return i;
    }

    return -1;
  }
}

inline bool IsClientMuted(const TClientInfoVector& clients, Transport::TClientId clientId, const string & strGameId)
{
  const int client_index = FindClientIndex(clients, clientId);

  if (client_index == -1)
  {
    LOBBY_LOG_ERR("User not found (gameid=%s user=%d)", strGameId, clientId);
    return false;
  }

  return clients[client_index].info.chatMuted;
}

inline bool IsClientLeaverOrLeaverPartyMember(const TClientInfoVector& clients, Transport::TClientId clientId, const string & strGameId)
{
  const int client_index = FindClientIndex(clients, clientId);

  if (client_index == -1)
  {
    LOBBY_LOG_ERR("User not found (gameid=%s user=%d)", strGameId, clientId);
    return false;
  }

  if (clients[client_index].info.basket == mmaking::EBasket::Leaver)
    return true;

  const uint partyId = clients[client_index].info.partyId;

  if (partyId == 0U)
    return false;

  for (int i = 0, count = clients.size(); i < count; ++i)
  {
    TClientInfoVector::const_reference ci = clients[i];

    if (ci.info.partyId != partyId)
      continue;

    if (ci.info.basket == mmaking::EBasket::Leaver)
      return true;
  }

  return false;
}


void GameSession::AddToChatControl( Transport::TClientId clientId, ETeam::Enum team )
{
  LOBBY_LOG_MSG( "ChatControl: user %d added to game %s", clientId, strGameId );

  const bool isMuted = IsClientMuted(gameServerData, clientId, strGameId);
  const bool isLeaverOrLeaverPartyMember = IsClientLeaverOrLeaverPartyMember(gameServerData, clientId, strGameId);

  {
    chatControl->AddToChannel( gameId, gamechat::channels::Session, clientId, isMuted || isLeaverOrLeaverPartyMember );
  }

  if ( team != ETeam::Team2 )
  {
    chatControl->AddToChannel( gameId, gamechat::channels::Team1, clientId, isMuted );
    chatControl->AddToChannel( gameId, gamechat::channels::Team1_SmartChat, clientId, false );
  }

  if ( team != ETeam::Team1 )
  {
    chatControl->AddToChannel( gameId, gamechat::channels::Team2, clientId, isMuted );
    chatControl->AddToChannel( gameId, gamechat::channels::Team2_SmartChat, clientId, false );
  }
}



void GameSession::StartPreparingPvx( socialLobby::TUserIdPvX pvxUserId, const char * spectatorLogin )
{
  StrongMT<IGameSessionOwner> lowner = owner.Lock();
  NI_VERIFY( lowner, "", return );

  SSocialUserPrepare pvxPrepData;
  pvxPrepData.pvxUid = pvxUserId;
  pvxPrepData.gameId = gameId;

  if ( spectatorLogin )
    pvxPrepData.login = spectatorLogin;
  else
  {
    const socialLobby::PlayerDetails * details = socialGameDetails.FindPlayer( pvxUserId );
    if ( !details ) {
      LOBBY_LOG_ERR( "Preparing user for pvx. User got no player details. pvxuid=%d, gameid=%s", pvxUserId, strGameId );
      return;
    }

    pvxPrepData.login = details->login;
  }

  lowner->StartPreparingPvx( pvxPrepData );
}



void GameSession::OnGameFinish( EGameResult::Enum _gameResult, const StatisticService::RPC::SessionClientResults & _info, const nstl::vector<Peered::SClientStatistics> & _clientsStatistics )
{
  Cleanup();
}



__time32_t GameSession::Timestamp()
{
  __time32_t t;
  _time32( &t );
  return t;
}



void GameSession::Dump()
{
  LOBBY_LOG_MSG( "Dumping game %s in state %s (%d):", strGameId, EGameState::ToString( state ), (int)state );
}

} //namespace lobby

NI_DEFINE_REFCOUNT( lobby::IGameSessionOwner );
NI_DEFINE_REFCOUNT( lobby::GameSession );
