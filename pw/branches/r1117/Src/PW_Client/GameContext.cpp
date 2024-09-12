#include "stdafx.h"

#include "GameContext.h"

#include "NewLobbyGameClientPW.h"
#include "ReplayRunner.h"

#include "Network/Initializer.h"
#include "Network/TransportInitializer.h"
#include "Network/ClientTransportConfig.h"
#pragma warning(push)
#pragma warning(disable:4996)
#include "Network/ClientTransportSystem2.h"
#include "Network/ClientTransportSystem3.h"
#pragma warning(pop)
#include "Network/FreePortsFinder.h"
#include "Network/StreamAllocator.h"


#include "Client/ScreenCommands.h"
#include "NetworkStatusScreen.h"
#include "Client/WasserzeichenScreen.h"

#include "Game/PF/Client/GameChatClient/GameChatClient.h"
#include "Network/RdpClientTransport/RdpClientTransport.h"

#include "PF_GameLogic/MapCollection.h"
#include "PF_GameLogic/DbSessionRoots.h"
#include "PF_GameLogic/MapDescriptionLoader.h"

#include "PF_GameLogic/StringExecutor.h"
#include "PF_GameLogic/DBAdvMap.h"

#include "DebugVarsSender.h"

#include "System/InlineProfiler.h"
#include "Version.h"
#include "GameStatistics.h"
#include "Server/Statistic/StatClientDiskDispatcher.h"
#include "System/PersistEvents.h"
#include "HybridServer/Peered.h"
#include "FastReconnectCtxPW.h"
#include "System/MainFrame.h"

#include "LoadingScreen.h"
#include "LoadingStatusHandler.h"

static string g_loginTestSessionPath;
REGISTER_VAR( "login_test_session_path", g_loginTestSessionPath, STORAGE_NONE );

static bool s_stat_enabled = true;
REGISTER_VAR( "stat_enabled", s_stat_enabled , STORAGE_NONE );

static float s_stat_timeout = 15.0f;
REGISTER_VAR( "stat_timeout", s_stat_timeout , STORAGE_NONE );

static bool s_stat_immidiate = false;
REGISTER_VAR( "stat_immidiate_http", s_stat_immidiate , STORAGE_NONE );

static int s_fast_reconnect_max_tries = 5;
static float s_fast_reconnect_delay = 2.0f;
static float s_fast_reconnect_retry_delay = 10.0f;

REGISTER_VAR( "fast_reconnect_max_tries", s_fast_reconnect_max_tries, STORAGE_NONE );
REGISTER_VAR( "fast_reconnect_delay", s_fast_reconnect_delay, STORAGE_NONE );
REGISTER_VAR( "fast_reconnect_retry_delay", s_fast_reconnect_retry_delay, STORAGE_NONE );


static int s_base_udp_port = 34990;
REGISTER_VAR( "rdp_base_port", s_base_udp_port , STORAGE_NONE );


NI_DEFINE_REFCOUNT( Game::IGameContextUiInterface )


namespace Game
{

GameContext::GameContext( const char * _sessionKey, const char * _devLogin, const char * _mapId, NGameX::ISocialConnection * _socialConnection, NGameX::GuildEmblem* _guildEmblem, const bool _isSpectator, const bool _isTutorial ) :
  socialMode( _sessionKey ? true : false ),
  status( EContextStatus::Ready ),
  clientWasInitialized( false ),
  socialConnection(_socialConnection),
  guildEmblem( _guildEmblem ),
  isSpectator( _isSpectator ),
  isTutorial( _isTutorial )
{
  if ( _sessionKey )
    if ( !ParseSessionKey( _sessionKey ) )
      NI_ALWAYS_ASSERT( NStr::StrFmt( "Wrong session key '%s'", _sessionKey ) );

  if (_devLogin)
    devLogin = _devLogin;

  if (_mapId)
    mapId = _mapId;

  NGlobal::RegisterContextCmd( "login", this, &GameContext::LoginOnServer );
  NGlobal::RegisterContextCmd( "replay", this, &GameContext::LoadReplay );
  NGlobal::RegisterContextCmd( "custom_game_create", this, &GameContext::CustomGameCreate );
  NGlobal::RegisterContextCmd( "custom_game_join", this, &GameContext::CustomGameJoin );
  NGlobal::RegisterContextCmd( "custom_game_reconnect", this, &GameContext::CustomGameReconnect );
  NGlobal::RegisterContextCmd( "custom_game_spectate", this, &GameContext::CustomGameSpectate );
  NGlobal::RegisterContextCmd( "custom_game_settings", this, &GameContext::CustomGameSettings );
  NGlobal::RegisterContextCmd( "custom_game_ready", this, &GameContext::CustomGameReady );
}



GameContext::~GameContext()
{
  NGlobal::UnregisterCmd( "login" );
  NGlobal::UnregisterCmd( "custom_game_create" );
  NGlobal::UnregisterCmd( "custom_game_join" );
  NGlobal::UnregisterCmd( "custom_game_reconnect" );
  NGlobal::UnregisterCmd( "custom_game_spectate" );
  NGlobal::UnregisterCmd( "custom_game_settings" );
  NGlobal::UnregisterCmd( "custom_game_ready" );
  NGlobal::UnregisterCmd( "replay" );

  fastReconnectCtx = 0;
  Cleanup();

  NDb::SessionRoot::InitRoot( 0 );
}



void GameContext::Init()
{
  networkDriver = Network::Initialize();
  networkDriver->SetStreamAllocator( new Network::StreamAllocator );

  Login::ClientVersion ver(VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH, VERSION_REVISION);

  ni_udp::NetAddr loginSvcAddr;
  unsigned loginSvcMux = 0;
  const char * loginAdr = socialMode ? socialLoginAddress.c_str() : Transport::ClientCfg::GetLoginAddress().c_str();

  if ( rdp_transport::ParseAddress( loginSvcAddr, loginSvcMux, loginAdr ) && loginSvcMux )
  {
    MessageTrace( "UDP transport login address: %s@%u", loginSvcAddr, loginSvcMux );

    ni_udp::NetAddr rdpBindAddr( 0, s_base_udp_port );
    StrongMT<rdp_transport::ClientTransport> clTr = new rdp_transport::ClientTransport( rdpBindAddr, 1000, Transport::GetGlobalMessageFactory() );
    clientTransportSystem = clTr;
  }
  else
  {
    MessageTrace( "TCP transport login address: %s", loginAdr );
    clientTransportSystem = new Transport::ClientTransportSystem3( networkDriver, Transport::GetGlobalMessageFactory(), ver );
  }
}



void GameContext::Cleanup()
{
  debugVarsSender = 0;
  if ( chatClient )
  {
    // Разрываем кольцо NUM_TASK
    chatClient->Shutdown();
  }
  chatClient = 0;
  gameClient = 0;
  lobbyClient = 0;
  gameStatLogic = 0;
  gameStat = 0;
  if (clientTransportSystem)
    clientTransportSystem->Logout();
  clientTransportSystem = 0;
  networkDriver = 0;
  gateKeeper = 0;

  status = EContextStatus::Ready;
}



bool GameContext::ParseSessionKey( const char * _sessKey )
{
  const char separator = '/';

  const char * addrEnd = strchr( _sessKey, separator );
  if ( !addrEnd )
    return false;
  NI_ASSERT( addrEnd[0], "" );

  const char * loginEnd = strchr( addrEnd + 1, separator );
  if ( !loginEnd )
    return false;
  NI_ASSERT( loginEnd[0], "" );

  socialLoginAddress = string( _sessKey, addrEnd - _sessKey );
  socialLogin = string( addrEnd + 1, loginEnd - ( addrEnd + 1 ) );
  socialPassword = string( loginEnd + 1 );
  return !socialLoginAddress.empty() && !socialLogin.empty() && !socialPassword.empty();
}



void GameContext::Start()
{
  NI_VERIFY( !loadingScreen, "", return );
  
  //Root initialization
  NDb::SessionRoot::InitRoot( NDb::Get<NDb::SessionRoot>( NDb::DBID("Session.ROOT") ) );

  string back;
  string logo;

  if (mapId.size())
  {
    Strong<NWorld::MapDescriptionLoader>  mapDescription = new NWorld::MapDescriptionLoader(mapId);

    if (mapDescription->IsSuccessfullyLoaded)
    {
      const NDb::AdvMapDescription * advMapDescription = mapDescription->Description;

      back =  advMapDescription->loadingBackgroundImages.back? advMapDescription->loadingBackgroundImages.back->textureFileName.c_str() : "";
      logo =  advMapDescription->loadingBackgroundImages.logo? advMapDescription->loadingBackgroundImages.logo->textureFileName.c_str() : "";
    }
  }

  loadingScreen = new LoadingScreen( back.c_str(), logo.c_str(), isSpectator, isTutorial );
  NScreenCommands::PushCommand( NScreenCommands::CreatePushScreenCommand( loadingScreen ) );

  loadingStatusHandler = loadingScreen->GetLoadingStatusHandler();

  if ( socialMode )
    ConnectToCluster( "", "" );
  else if (devLogin.size())
    ConnectToCluster(devLogin, "");
}


int GameContext::Poll( float dt )
{
  NI_PROFILE_FUNCTION;

  // Poll only replay events while loading a replay
  if(replayRunner)
  {
    if(replayRunner->IsLoading())
    {
      return replayRunner->Poll(dt);
    }
    else if(replayRunner->IsRunning())
    {
      // Return here while replay is running, since replay runner
      // is in screens list and calls Step() each frame.
      return -1;
    }
  }

  if (clientTransportSystem)
    clientTransportSystem->Step();

  if ( gateKeeper )
    gateKeeper->Poll();

  if ( lobbyClient )
    lobbyClient->Poll();
  
  if ( lobbyClient && networkStatusScreen )
    networkStatusScreen->SetLobbyErrorCode( lobbyClient->ErrorCode() );

  const int numCommands = gameClient ? gameClient->Poll(dt) : -1;

  gameStatSetupTimer.Poll();

  PollFastReconnect();

  switch ( status )
  {
    default:
      break;

    case EContextStatus::WaitingLogin:
    {
      Login::ELoginResult::Enum res = clientTransportSystem->GetLoginResult();
      if ( loadingStatusHandler)
        loadingStatusHandler->OnLoginStatus( res );
      if ( res == Login::ELoginResult::Success )
      {
        if ( isSpectator )
        {
          StartLobbyClient();
        }
        else
        {
          if (s_stat_enabled)
            AcquireGameStat();
          else
            StartLobbyClient();
        }
      }
      else if ( res != Login::ELoginResult::NoResult )
      {
        status = EContextStatus::Error;
        persistentEvents::GetSingleton()->WriteEvent( fastReconnectCtx ? persistentEvents::EEvent::LoginFailedInFR : persistentEvents::EEvent::LoginFailed, (int)res );
      }
      break;
    }

    case EContextStatus::WaitingStatistics:
      WaitForStatistics();
      break;

    case EContextStatus::WaitingLobbyClient:
      NI_ASSERT( lobbyClient, "" );
      if ( loadingStatusHandler )
        loadingStatusHandler->OnLobbyStatus( lobbyClient->Status() );
      if ( lobbyClient->Status() == lobby::EClientStatus::Connected )
      {
        status = EContextStatus::InGame;

        if ( persistentEvents::GetSingleton() )
          persistentEvents::GetSingleton()->Open();
      }
      else if ( lobbyClient->Status() == lobby::EClientStatus::Error )
      {
        status = EContextStatus::Error;
        if ( NGlobal::GetVar( "exit_on_finish", 0 ).GetFloat() != 0 )
        {
          ErrorTrace( "EContextStatus::Error" );
          NMainFrame::Exit();
        }
      }
      break;

    case EContextStatus::InGame:
      if ( lobbyClient && loadingStatusHandler)
        loadingStatusHandler->OnLobbyInGameStatus( lobbyClient->LastLobbyOperationResult() );
      if ( NGlobal::GetVar( "exit_on_finish", 0 ).GetFloat() != 0 && ( lobbyClient->LastLobbyOperationResult() == lobby::EOperationResult::AlreadyInGame || lobbyClient->LastLobbyOperationResult() == lobby::EOperationResult::InternalError ) )
      {
        ErrorTrace( "EContextStatus::InGame error %d", (int)lobbyClient->LastLobbyOperationResult() );
        NMainFrame::Exit();
      }

      // TEST: multicast channel logic
      if (!inputChannel)
      {
        Transport::TChannels channels;
        clientTransportSystem->GetNewAcceptedChannels(channels);
        if (channels.size())
        {
          inputChannel = *(channels.begin());
          DebugTrace("Multicast channel accepted");
        }
      }
      else if (inputChannel->GetStatus() == Network::ConnectionState::Connected)
      {
        vector<byte> data;
        if (inputChannel->ReceiveRaw(&data))
        {
          gameClient->OnMulticastData(data);
        }
      }
      else if(inputChannel->GetStatus() == Network::ConnectionState::Closed)
      {
        inputChannel = 0;
        DebugTrace("Multicast channel closed");
      }

      break;

    case EContextStatus::Cleanup:
      Cleanup();
      break;
  }

  return numCommands;
}



void GameContext::WaitForStatistics()
{
  if ( gameStat && gameStat->Ready() )
  {
    ContinueAfterStatistics( Game::EGameStatStatus::Ready );
    return;
  }

  if ( gameStatSetupTimer.Elapsed() )
  {
    MessageTrace( "Statistics connection timed out! Continuin without..." );
    gameStat = 0;
  }

  if ( !gameStat )
    ContinueAfterStatistics( Game::EGameStatStatus::Failed );
}



void GameContext::ContinueAfterStatistics( Game::EGameStatStatus::Enum gss )
{
  if ( loadingStatusHandler )
    loadingStatusHandler->OnGameStatStatus( gss ); // Output status according to the most important interface

  ReportPersistentEvents();
  StartLobbyClient();
}



void GameContext::Shutdown()
{
  StopAsyncMapLoadingJob();
  Cleanup();
  fastReconnectCtx = 0;

  NScreenCommands::PushCommand( NScreenCommands::CreateClearStackCommand() );
}



void GameContext::OnAltTab(bool isActive)
{
  if(gameClient)
    gameClient->OnAltTab(isActive);
}



void GameContext::StartFastReconnect()
{
  MessageTrace( "Initiating fast reconnect..." );
  fastReconnectCtx = new lobby::FastReconnectCtxPW( gameClient->ClientId(), s_fast_reconnect_max_tries, s_fast_reconnect_delay, s_fast_reconnect_retry_delay );
  gameClient->SetupFastReconnectCtx( fastReconnectCtx );
}



void GameContext::RestartFastReconnect()
{
  NI_VERIFY( fastReconnectCtx, "", return );

  Cleanup();

  if ( !fastReconnectCtx->BeginNextTry() )
  {
    if ( networkStatusScreen )
      networkStatusScreen->GsConnectionIsDead();
    fastReconnectCtx = 0;
  }
}



void GameContext::PollFastReconnect()
{
  if ( !fastReconnectCtx )
    return;

  switch ( fastReconnectCtx->Stage() )
  {
    case lobby::EFastReconnStage::Idle:
      if ( fastReconnectCtx->BeginNextTry() )
      {
        MessageTrace( "Starting fast reconnect (on pause), try #%d...", fastReconnectCtx->TryIndex() );

        Cleanup();
        if ( networkStatusScreen ) {
          networkStatusScreen->ResetErrors();
          networkStatusScreen->SetFastReconnectTryIndex( fastReconnectCtx->TryIndex() );
        }
      }
      else
      {
        MessageTrace( "Failed to fast reconnect after %d tries!", fastReconnectCtx->TryIndex() );
        FastReconnectFailed();
      }
      break;

    case lobby::EFastReconnStage::WarmUp:
      if ( fastReconnectCtx->CanTryNow() )
      {
        MessageTrace( "Reconnecting fast, try #%d...", fastReconnectCtx->TryIndex() );
        ConnectToCluster( lastLogin, "", Login::LoginType::FAST_RECONNECT );
      }
      break;

    case lobby::EFastReconnStage::InProgress:
      if ( status == EContextStatus::Error )
        fastReconnectCtx->TryFailed();
      else if ( lobbyClient && ( lobbyClient->Status() == lobby::EClientStatus::Error ) )
        fastReconnectCtx->TryFailed();
      else if ( gameClient && ( gameClient->GracefullDisconnectReason() != Peered::EDisconnectReason::None ) )
      {
        MessageTrace( "Game server actively refused connection (code %d), fast reconnect aborted at %d try!", (int)gameClient->GracefullDisconnectReason(), fastReconnectCtx->TryIndex() );
        FastReconnectFailed();
      }
      else if ( gameClient && ( gameClient->GameState() == lobby::EGameState::Running ) )
      {
        MessageTrace( "Fast reconnect complete!" );
        fastReconnectCtx = 0;
        if ( networkStatusScreen )
          networkStatusScreen->ResetErrors();
        return;
      }
      break;
  }
}



void GameContext::FastReconnectFailed()
{
  if ( networkStatusScreen )
  {
    networkStatusScreen->GsConnectionIsDead();
    networkStatusScreen->SetFastReconnectTryIndex( 0 );
  }

  fastReconnectCtx = 0;
  Cleanup();
}



bool GameContext::ShouldStartFastReconnect() const
{
  if ( ( s_fast_reconnect_max_tries <= 0 ) || !socialMode )
    return false;

  if (gameClient && !gameClient->IsFastReconnectEnabled())
    return false;

  if ( lobbyClient && ( lobbyClient->GameLineup().size() < 2 ) )
    return false;

  if ( gameClient && ( gameClient->GracefullDisconnectReason() != Peered::EDisconnectReason::None ) )
    return false;

  if ( gameClient && ( gameClient->GameState() != lobby::EGameState::Running ) )
    return false;

  return true;
}



void GameContext::OnChannelClosed( Transport::IChannel * channel, rpc::Node * node )
{
  LOG_M(0).Trace("%s(channel=%s)", __FUNCTION__, channel->GetAddress().target.c_str());

  if ( gameClient && gameClient->IsThisGameServerNode( node ) )
  {
    MessageTrace( "Lost channel to Game Server" );

    if ( persistentEvents::GetSingleton() ) {
      lobby::TGameId sessId = lobbyClient ? lobbyClient->GameSessionId() : 0;
      persistentEvents::GetSingleton()->WriteEvent( fastReconnectCtx ? persistentEvents::EEvent::DisconnectInFR : persistentEvents::EEvent::Disconnect, (int)sessId );
    }

    if ( networkStatusScreen )
      networkStatusScreen->GsConnectionIsDead();

    if ( fastReconnectCtx )
      fastReconnectCtx->TryFailed();
    else if ( ShouldStartFastReconnect() )
      StartFastReconnect();

    status = EContextStatus::Cleanup;
  }
  else
  {
    if (clientTransportSystem)
    {
      Transport::EStatus::Enum st = clientTransportSystem->GetStatus();
      if (Transport::EStatus::CRITICAL_FAIL == st)
      {
        clientTransportSystem->Logout();
        if ( NGlobal::GetVar( "exit_on_finish", 0 ).GetFloat() != 0 )
        {
          ErrorTrace( "GameContext::OnChannelClosed error" );
          NMainFrame::Exit();
        }
      }
    }
  }
}



void GameContext::OnCorruptData( Transport::IChannel * channel, rpc::Node * node )
{
  if ( gameClient && gameClient->IsThisGameServerNode( node ) )
  {
    if ( persistentEvents::GetSingleton() ) {
      lobby::TGameId sessId = lobbyClient ? lobbyClient->GameSessionId() : 0;
      persistentEvents::GetSingleton()->WriteEvent( persistentEvents::EEvent::DisconnectCorruptData, (int)sessId );
    }
  }
}



bool GameContext::LoginInProgress() const
{
  return ( status != Game::EContextStatus::Ready ) && ( status != Game::EContextStatus::Error );
}



void GameContext::SetDeveloperSex( lobby::ESex::Enum _sex )
{
  NI_VERIFY( lobbyClient, "", return );
  lobbyClient->SetDeveloperSex( _sex );
}



void GameContext::ConnectToCluster( const string & login, const string & password, Login::LoginType::Enum _loginType )
{
  Cleanup();
  Init();

  NI_VERIFY( status == EContextStatus::Ready, "", return );
  NI_VERIFY( clientTransportSystem, "Client transport system could not be initialized!", return );

  if ( socialMode )
  {
    clientTransportSystem->Login( socialLoginAddress, socialLogin, "", socialPassword, _loginType );
    lastLogin = socialLogin;
  }
  else
  {
#ifndef _SHIPPING
    clientTransportSystem->Login( Transport::ClientCfg::GetLoginAddress(), login, password, g_loginTestSessionPath, _loginType );
#endif
    lastLogin = login;
  }

  status = EContextStatus::WaitingLogin;
  if ( loadingStatusHandler) 
    loadingStatusHandler->OnLoginStatus( Login::ELoginResult::NoResult );
}



NWorld::IMapCollection * GameContext::Maps()
{
  NI_VERIFY( lobbyClient, "", return 0 );
  return lobbyClient->Maps();
}



void GameContext::RefreshGamesList()
{
  NI_VERIFY( lobbyClient, "", return );
  lobbyClient->RefreshGamesList();
}



void GameContext::PopGameList( lobby::TDevGamesList & buffer )
{
  if ( lobbyClient )
    lobbyClient->PopGameList( buffer );
}



lobby::EOperationResult::Enum GameContext::LastLobbyOperationResult() const
{
  if ( lobbyClient )
    return lobbyClient->LastLobbyOperationResult();
  else
    return lobby::EOperationResult::Ok;
}



void GameContext::CreateGame( const char * mapId, int maxPlayers )
{
  NI_VERIFY( lobbyClient, "", return );
  lobbyClient->CreateGame( mapId, maxPlayers );
}



void GameContext::JoinGame( int gameId )
{
  NI_VERIFY( lobbyClient, "", return );
  lobbyClient->JoinGame( gameId );
}



void GameContext::Reconnect( int gameId, int team, const string & heroId )
{
  NI_VERIFY( lobbyClient, "", return );
  lobbyClient->ReconnectGame( gameId, team, heroId );
}



void GameContext::Spectate( int gameId )
{
  NI_VERIFY( lobbyClient, "", return );
  lobbyClient->SpectateGame( gameId );
}



void GameContext::ChangeCustomGameSettings( lobby::ETeam::Enum team, lobby::ETeam::Enum faction, const string & heroId )
{
  NI_VERIFY( lobbyClient, "", return );
  lobbyClient->ChangeCustomGameSettings( team, faction, heroId );
}



void GameContext::SetReady( lobby::EGameMemberReadiness::Enum readiness )
{
  NI_VERIFY( lobbyClient, "", return );
  lobbyClient->SetReady( readiness );
}



void GameContext::SetDeveloperParty(int party)
{
  NI_VERIFY( lobbyClient, "", return );
  lobbyClient->SetDeveloperParty(party);
}



void GameContext::AcquireGameStat()
{
  gameStat = 0;

  //UGLY: Объект создается здесь, инициализируется и поллится из SessionRunnerPW
  debugVarsSender = new DebugVarsSender;

  StrongMT<StatisticService::IStatDataDispatcher> statDispatcher = s_stat_immidiate ? 
                                                                        new StatisticService::ClientHttpDispatcher :
                                                                        new StatisticService::ClientDiskDispatcher;
  gameStat = new StatisticService::GameStatClient( statDispatcher, 1 );

  status = EContextStatus::WaitingStatistics;

  gameStatSetupTimer.Restart( s_stat_timeout );

  if ( loadingStatusHandler )
    loadingStatusHandler->OnGameStatStatus( Game::EGameStatStatus::Waiting );
}



void GameContext::OnStatusChange( lobby::EClientStatus::Enum oldStatus, lobby::EClientStatus::Enum newStatus )
{
  if ( newStatus == lobby::EClientStatus::Connected )
  {
    if ( !networkStatusScreen ) {
      Strong<NetworkStatusScreen> netStatus = new NetworkStatusScreen;
      networkStatusScreen = netStatus;
      NScreenCommands::PushCommand( NScreenCommands::CreatePushScreenCommand( netStatus ) );
    }

    if ( !clientWasInitialized )
    {
      client::WasserzeichenScreen::CreateScreen( NStr::ToUnicode( lastLogin ).c_str() );
      clientWasInitialized = true;
    }
  }
  else if ( newStatus == lobby::EClientStatus::InGameSession )
  {
    StartGameClient();
  }
}




void GameContext::ReportPersistentEvents()
{
  if ( !persistentEvents::GetSingleton() )
    return;

  if ( !gameStat || !gameStat->Ready() ) {
    DebugTrace( "Persistent events were NOT reported! (Statistics offline)" );
    return;
  }

  NI_VERIFY( clientTransportSystem, "", return );

  vector<persistentEvents::Event> events;
  persistentEvents::GetSingleton()->CollectEvents( events );

  DebugTrace( "Collected %d persistent events", events.size() );

  for ( int i = 0; i < events.size(); ++i ) {
    persistentEvents::Event & evt = events[i];

    DebugTrace( "Persistent event: code=%d", (int)evt.code );

    if ( evt.code != persistentEvents::EEvent::None )
    {
      StatisticService::RPC::OfflineClientEvent data;
      data.playerId = clientTransportSystem->GetUserId();
      data.persistentId = ( (unsigned __int64)evt.id.timestamp << 32 ) | (unsigned __int64)evt.id.index;
      data.code = (int)evt.code;
      data.auxData = evt.aux;
      data.eventTimestamp = evt.eventTimestamp;
      data.clientTimestampForSync = persistentEvents::Events::GetTimestamp();
      gameStat->Message( data );

      DebugTrace( "Persistent event sent: code=%d, playerid=%d, persid=%x", data.code, data.playerId, data.persistentId );
    }
  }

  persistentEvents::GetSingleton()->EraseEvents( events );
}



void GameContext::StartLobbyClient()
{
  NI_ASSERT( clientTransportSystem, "" );

  if ( fastReconnectCtx )
    if ( fastReconnectCtx->ClientId() != clientTransportSystem->GetUserId() )
      ErrorTrace( "Got different user id on fast reconnect! userid=%d, old userid = %d", clientTransportSystem->GetUserId(), fastReconnectCtx->ClientId() );

  lobbyClient = new lobby::ClientPW( clientTransportSystem->GetUserId(), socialMode, this, fastReconnectCtx);
  gateKeeper = new rpc::GateKeeperClient( clientTransportSystem, Transport::ENetInterface::Invalid, 0 );
  gateKeeper->attachNotificationCallback( this );

  lobbyClient->SetNotify( this );
  lobbyClient->Start( gateKeeper, clientTransportSystem->GetSessionPath() );

  status = EContextStatus::WaitingLobbyClient;

  if ( loadingStatusHandler )
    loadingStatusHandler->OnLobbyStatus( lobby::EClientStatus::Initial );
}



void GameContext::StartGameClient()
{
  NI_ASSERT( lobbyClient, "" );

  gameStatLogic = 0;
  gameClient = new lobby::GameClientPW( lobbyClient, lobbyClient->Maps(), networkStatusScreen, fastReconnectCtx, socialConnection, loadingScreen, guildEmblem, isSpectator, isTutorial );

  if ( gameStat )
  {
    if ( fastReconnectCtx && fastReconnectCtx->Statistics() ) {
      gameStatLogic = fastReconnectCtx->Statistics();
      gameStatLogic->ResetRemotePtrs( gameStat, gameStat );
    }
    else
    {
      gameStatLogic = new StatisticService::GameStatistics( gameStat, gameStat );
      gameStatLogic->SetRelayAddress(clientTransportSystem->GetRelayAddress());
    }
    gameClient->SetGameStatistics( gameStatLogic );
  }

  gameClient->SetDebugVarSender( debugVarsSender );
  
  CreateChatClient(gameClient->GetNickname());
  gameClient->SetChatClient( chatClient );

  //If we tried, but could not get game statistics pointer, clean up resources
  if ( gameStat && !gameStat->Ready() )
    gameStat = 0;
}






void GameContext::CreateChatClient(const nstl::wstring& nickName)
{
  chatClient = new gamechat::Client(lobbyClient->GameSessionId(), clientTransportSystem->GetUserId(), nickName, gateKeeper);
}



bool GameContext::LoginOnServer( const char * name, const vector<wstring> & args )
{
  if ( args.empty() )
  {
    MessageTrace( "Usage: %s login_name login_password", name ); 
    return false;
  }

  if ( status == EContextStatus::Ready )
  {
    string login = NStr::ToMBCS( args[0] );
    string pass;
    if ( args.size() >= 2 )
      pass = NStr::ToMBCS( args[1] );

    ConnectToCluster( login, pass );
    return true;
  }

  return false;
}



bool GameContext::CustomGameCreate( const char * name, const vector<wstring> & args )
{
  if ( !lobbyClient )
    return false;
  if ( lobbyClient->Status() != lobby::EClientStatus::Connected )
    return false;

  if ( args.size() >= 2 && args.size() <= 3)
  {
    int playersNumber = NStr::ToInt( args[0] );
    string mapId = NStr::ToMBCS( args[1] );
    int autostartPlayersNumber = -1;
    if (args.size() == 3)
      autostartPlayersNumber = NStr::ToInt( args[2] );
    if ( !mapId.empty() && playersNumber > 0 )
    {
      lobbyClient->CreateGame( mapId.c_str(), playersNumber, autostartPlayersNumber );
      return true;
    }
  }
  MessageTrace( "Wrong '%s' syntax: %s <player number> <map id> [autostart player number]", name, name );
  return true;
}



bool GameContext::CustomGameJoin( const char * name, const vector<wstring> & args )
{
  if ( !lobbyClient )
    return false;
  if ( lobbyClient->Status() != lobby::EClientStatus::Connected )
    return false;

  if ( args.size() == 0 )
  {
    lobbyClient->JoinGame( 0 );
    return true;
  }
  else if ( args.size() == 1 )
  {
    int gameId = NStr::ToInt( args[0] );
    if ( gameId > 0 )
    {
      lobbyClient->JoinGame( gameId );
      return true;
    }
  }
  MessageTrace( "Wrong '%s' syntax: %s <game id>", name, name );
  return true;
}



bool GameContext::CustomGameReconnect( const char * name, const vector<wstring> & args )
{
  if ( !lobbyClient )
    return false;
  if ( lobbyClient->Status() != lobby::EClientStatus::Connected )
    return false;

  if ( args.size() == 3 )
  {
    int gameId = NStr::ToInt( args[0] );
    int team = NStr::ToInt( args[1] );
    string hero = NStr::ToMBCS( args[2] );
    if ( gameId > 0 && !hero.empty() )
    {
      lobbyClient->ReconnectGame( gameId, team, hero.c_str() );
      return true;
    }
  }

  MessageTrace( "Wrong '%s' syntax: %s <game id> <team> <hero>", name, name );
  return true;
}



bool GameContext::CustomGameSpectate( const char * name, const vector<wstring> & args )
{
  if ( !lobbyClient )
    return false;
  if ( lobbyClient->Status() != lobby::EClientStatus::Connected )
    return false;

  if ( args.size() == 1 )
  {
    int gameId = NStr::ToInt( args[0] );
    if ( gameId > 0 )
    {
      lobbyClient->SpectateGame( gameId );
      return true;
    }
  }

  MessageTrace( "Wrong '%s' syntax: %s <game id>", name, name );
  return true;
}



bool GameContext::CustomGameSettings( const char * name, const vector<wstring> & args )
{
  if ( !lobbyClient )
    return false;
  if ( lobbyClient->Status() != lobby::EClientStatus::InCustomLobby )
    return false;

  int team = -1;
  string hero;
  int faction = -1;


  if ( args.size() == 2 )
  {
    team = NStr::ToInt( args[0] );
    hero = NStr::ToMBCS( args[1] );
    faction = team;
  }
  else
  if ( args.size() == 3 )
  {
    team = NStr::ToInt( args[0] );
    hero = NStr::ToMBCS( args[1] );
    faction = NStr::ToInt( args[2] );
  }

  if ( !hero.empty() && ( ( team == lobby::ETeam::Team1 ) || ( team == lobby::ETeam::Team2 ) )
    && ( ( faction == lobby::ETeam::Team1 ) || ( faction == lobby::ETeam::Team2 ) ))
  {
    lobbyClient->ChangeCustomGameSettings( (lobby::ETeam::Enum)team, (lobby::ETeam::Enum)faction, hero );
    return true;
  }

  if(args.size() < 2 || args.size() > 3)
    MessageTrace( "Wrong '%s' syntax: %s <team -1|0|1> <hero id> <faction -1|0|1>", name, name );
  return true;
}



bool GameContext::CustomGameReady( const char * name, const vector<wstring> & args )
{
  if ( !lobbyClient )
    return false;
  if ( lobbyClient->Status() != lobby::EClientStatus::InCustomLobby )
    return false;

  if ( args.size() == 1 )
  {
    int rdy = NStr::ToInt( args[0] );
    if ( ( rdy == lobby::EGameMemberReadiness::NotReady ) || ( rdy == lobby::EGameMemberReadiness::Ready ) || ( rdy == lobby::EGameMemberReadiness::ReadyForAnything ) )
    {
      lobbyClient->SetReady( (lobby::EGameMemberReadiness::Enum)rdy );
      return true;
    }
  }
  MessageTrace( "Wrong '%s' syntax: %s <ready 0|1|2>", name, name );
  return true;
}



bool GameContext::LoadReplay( const char * name, const vector<wstring> & args )
{
  if ( !lobbyClient || ( lobbyClient->Status() != lobby::EClientStatus::Connected && lobbyClient->Status() != lobby::EClientStatus::InCustomLobby ) )
  {
    MessageTrace( "Replay can be started only in lobby!" );
    return false;
  }

  const string replayName = NStr::ToMBCS( args[0] );
  replayRunner = new ReplayRunner( replayName, Maps() );

  lobbyClient->CleanUIScreens(); 
  if (loadingScreen)
    NScreenCommands::PushCommand( NScreenCommands::CreatePopScreenCommand( loadingScreen ) );

  NScreenCommands::PushCommand( NScreenCommands::CreatePushScreenCommand(replayRunner) );  

  return true;
}

void GameContext::StopAsyncMapLoadingJob()
{
  if (replayRunner)
    replayRunner->StopAsyncMapLoadingJob();

  if (gameClient)
    gameClient->StopAsyncMapLoadingJob();
}

} //namespace Game
