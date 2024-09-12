#include "stdafx.h"

#include "LocalGameContext.h"

#include "PF_GameLogic/MapCollection.h"
#include "PF_GameLogic/StringExecutor.h"
#include "PF_GameLogic/AdventureScreen.h"
#include "PF_GameLogic/DbSessionRoots.h"
#include "PF_GameLogic/DbHeroesList.h"
#include "PF_GameLogic/MapStartup.h"
#include "PF_GameLogic/AsyncMapStartup.h"
#include "PF_GameLogic/MapDescriptionLoader.h"
#include "PF_GameLogic/ChatController.h"
#include "Sound/EventScene.h"
#include "PF_GameLogic/DBSound.h"

#include "System/LoadingProgress.h"
#include "LocalCmdScheduler.h"
#include "Client/ScreenCommands.h"
#include "Client/MainTimer.h"
#include "Core/Transceiver.h"
#include "SelectGameModeScreen.h"
#include "SelectHeroScreen.h"
#include "LoadingScreen.h"
#include "System/RandomGenerator.h"
#include "UI/FrameTimeRender.h"
#include "ReplayRunner.h"
#include "PF_GameLogic/IgnoreListStorage.h"
#include "Game/PF/Client/LobbyPvx/NewReplay.h"
#include "Version.h"

static bool g_enableReplayLocalGame = false;
REGISTER_DEV_VAR( "enable_replay_local_game", g_enableReplayLocalGame, STORAGE_NONE);


namespace Game
{

static string s_localNickname( "Very Local Player" );
REGISTER_DEV_VAR( "local_nickname", s_localNickname, STORAGE_NONE );



LocalGameContext::LocalGameContext( bool _isSpectator ) :
state( ELocalGameState::Initial ),
clientId( 1984 ),
maxPlayers( 0 ),
developerSex( lobby::ESex::Male ),
isSpectator( _isSpectator )
{
  NGlobal::RegisterContextCmd( "replay", this, &LocalGameContext::LoadReplay );

  // Spectator here means replay. We don't need all these commands in replay.
  if (!isSpectator)
  {
    NGlobal::RegisterContextCmd( "timescale", this, &LocalGameContext::SetTimeScale );
    NGlobal::RegisterContextCmd( "login", this, &LocalGameContext::LoginOnServer );
    NGlobal::RegisterContextCmd( "custom_game_create", this, &LocalGameContext::CustomGameCreate );
    NGlobal::RegisterContextCmd( "custom_game_join", this, &LocalGameContext::CustomGameJoin );
    NGlobal::RegisterContextCmd( "custom_game_reconnect", this, &LocalGameContext::CustomGameReconnect );
    NGlobal::RegisterContextCmd( "custom_game_settings", this, &LocalGameContext::CustomGameSettings );
    NGlobal::RegisterContextCmd( "custom_game_ready", this, &LocalGameContext::CustomGameReady );
  }

  resourceCollection = new NWorld::PFResourcesCollection;
  resourceCollection->CollectTalents();
  resourceCollection->CollectConsumables();
  resourceCollection->CollectMarketingItems();
}



LocalGameContext::~LocalGameContext()
{
  NGlobal::UnregisterCmd( "replay" );

  if (!isSpectator)
  {
    NGlobal::UnregisterCmd( "timescale" );
    NGlobal::UnregisterCmd( "login" );
    NGlobal::UnregisterCmd( "custom_game_create" );
    NGlobal::UnregisterCmd( "custom_game_join" );
    NGlobal::UnregisterCmd( "custom_game_reconnect" );
    NGlobal::UnregisterCmd( "custom_game_settings" );
    NGlobal::UnregisterCmd( "custom_game_ready" );
  }
}



void LocalGameContext::Start()
{
  NI_VERIFY( state == ELocalGameState::Initial, "", return );

  NDb::SessionRoot::InitRoot( NDb::Get<NDb::SessionRoot>( NDb::DBID("Session.ROOT") ) );

  StrongMT<NWorld::PWMapCollection> maps = new NWorld::PWMapCollection;
  maps->ScanForMaps();
  mapCollection = maps;

  LoadHeroes();

  Strong<NGameX::SelectGameModeScreen> screen = new NGameX::SelectGameModeScreen( this );
  NScreenCommands::PushCommand( NScreenCommands::CreatePushScreenCommand( screen ) );
  lobbyScreen = screen;

  state = ELocalGameState::InLobby;

  chatController = new NGameX::ChatUiController(0);
  ignoreListStorage = new NGameX::IgnoreListStorage( clientId );
}



void LocalGameContext::LoadHeroes()
{
  NDb::Ptr<NDb::HeroesDB> pHeroes = NDb::SessionRoot::GetRoot()->logicRoot->heroes;
  heroes.reserve( pHeroes->heroes.size() );
  for ( int i = 0; i < pHeroes->heroes.size(); ++i )
    if ( pHeroes->heroes[i] && pHeroes->heroes[i]->legal )
      heroes.push_back( pair<string, bool>( pHeroes->heroes[i]->id, false ) );
}



void LocalGameContext::GenerateLineup( int playersNumber )
{
  NI_VERIFY( !heroes.empty(), "", return );

  NRandom::RandomGenerator die( GetTickCount() );

  int teams[2] = { 0, 0 };

  for ( int i = 0; i < gameLineup.size(); ++i )
    ++teams[ gameLineup[i].context.team == lobby::ETeam::Team1 ? 0 : 1 ];

  lobby::ETeam::Enum humanTeam = lobby::ETeam::None;
  bool fillOneTeam = this->mapDescription->Description->mapType == NDb::MAPTYPE_COOPERATIVE;

  if ( !gameLineup.empty() )
    humanTeam = gameLineup[0].context.team;

  while ( gameLineup.size() < playersNumber )
  {
    bool spawnHuman = gameLineup.empty();

    gameLineup.push_back( lobby::SGameMember() );

    lobby::SUserInfo & userInfo = gameLineup.back().user;
    lobby::SPlayerGameContext & plrCtx = gameLineup.back().context;

    if ( spawnHuman )
    {
      userInfo.userId = clientId;
      userInfo.zzimaSex = developerSex;
      userInfo.nickname = NStr::ToUnicode( s_localNickname );
      plrCtx.playerType = lobby::EPlayerType::Human;
      plrCtx.team = lobby::ETeam::Team2;
      plrCtx.original_team = lobby::ETeam::Team1;
      humanTeam = plrCtx.team;
    }
    else 
    {
      userInfo.userId = -1;
      userInfo.zzimaSex = lobby::ESex::Male;
     // userInfo.nickname = L"Bot";
      plrCtx.playerType = lobby::EPlayerType::Computer;
      if ( fillOneTeam )
        plrCtx.team = humanTeam;
      else
        plrCtx.team = ( teams[0] < teams[1] ) ? lobby::ETeam::Team1 : lobby::ETeam::Team2;
    }

    ++teams[ plrCtx.team == lobby::ETeam::Team1 ? 0 : 1 ];

    //Let's find random unused hero
    int randHero = die.Next() % heroes.size();
    for ( int i = 0; i < heroes.size(); ++i, ++randHero )
      if ( !heroes[randHero % heroes.size()].second )
        break;

    plrCtx.hero = heroes[randHero % heroes.size()].first;
    heroes[randHero % heroes.size()].second = true;
  }
}



int LocalGameContext::Poll( float dt )
{
  switch ( state )
  {
    default:
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
      break;

    case ELocalGameState::ShowingLoadingScreen:
      //Waiting while LoadingScreen is being started and initialized
      NI_VERIFY( loadingScreeen, "", break );
      if ( loadingScreeen->GetLogic() )
        StartGame();
      break;

    case ELocalGameState::LoadingMap:
      NI_VERIFY( scheduler, "", break );
      scheduler->Step( dt );

      NI_VERIFY( mapLoadingJob, "", break );
      if ( loadingThread->Wait( 0 ) )
      {
        loadingThread = 0;
        LaunchGame();
      }
      else
      {
        Sleep( 50 );
        float pro = mapLoadingJob->GetProgress()->GetTotalProgress();
        if ( loadingScreeen )
          loadingScreeen->SetPlayerProgress( clientId, Clamp( pro, 0.f, 1.f ) );
      }
      break;

    case ELocalGameState::Playing:
      NI_VERIFY( scheduler && transceiver, "", break );
      scheduler->Step( dt );
      transceiver->Step( dt * 1e3 );
      break;
  }

  const int stepScheduler = scheduler ? scheduler->GetNextStep( false ) : -1;
  const int stepTransceiver = transceiver ? transceiver->GetNextStep() : -1;
  if(scheduler && transceiver)
    return stepScheduler - stepTransceiver;
  return -1;
}



void LocalGameContext::Shutdown()
{
  StopAsyncMapLoadingJob();

  //NDb::SessionRoot::InitRoot( 0 );

  NScreenCommands::PushCommand( NScreenCommands::CreateClearStackCommand() );
}


void LocalGameContext::OnAltTab(bool isActive)
{
  if(loadingThread)
    loadingThread->SetPriority( isActive ? 0 : 1 );
}


void LocalGameContext::CreateGame( const char * _mapId, int _maxPlayers )
{
  NI_VERIFY( state == ELocalGameState::InLobby, "", return );

  NI_VERIFY( mapCollection, "No map loader given", return );
  mapLoader = mapCollection->CreateMapLoader( _mapId );
  if ( !mapLoader )
    return;

  mapId = _mapId;
  maxPlayers = Min( _maxPlayers, 2 * mapLoader->GetMaxPlayersPerTeam() );

  mapDescription = new NWorld::MapDescriptionLoader(mapLoader->GetMapDescName());

  GenerateLineup( 1 ); //Add Just Player

  if ( lobbyScreen )
    NScreenCommands::PushCommand( NScreenCommands::CreatePopScreenCommand( lobbyScreen ) );

  Weak<NGameX::SelectHeroScreen> screen = new NGameX::SelectHeroScreen( this );
  NScreenCommands::PushCommand( NScreenCommands::CreatePushScreenCommand( screen ) );
  heroScreen = screen;

  state = ELocalGameState::InCustomGame;
  OnLobbyDataChange();
}

void LocalGameContext::OnLobbyDataChange()
{
  if ( state == ELocalGameState::InCustomGame )
  {
    set<int> empty;
    UpdateCustomLobbyPlayers( empty );
  }
}


void LocalGameContext::UpdateCustomLobbyPlayers( const set<int> & hilitePlayers )
{
  if ( !heroScreen )
    return;

  vector<wstring> lines;
  vector<int> linesIds;

  for( int i = 0; i < 2; ++i )
  {
    lobby::ETeam::Enum team = i ? lobby::ETeam::Team2 : lobby::ETeam::Team1;

    lines.push_back( i ? L"Team two:" : L"Team one:" );
    linesIds.push_back( -1 );
    for ( int j = 0; j < gameLineup.size(); ++j )
    {
      const lobby::SGameMember & memb = gameLineup[j];
      if( memb.context.team != team )
        continue;

      const bool ready = true;

      wstring line = NStr::StrFmtW( L"<space:2>%s (%d) as %s (%s), %s",
        memb.user.nickname.c_str(),
        memb.user.userId,
        NStr::ToUnicode( memb.context.hero ).c_str(),
        memb.context.original_team == lobby::ETeam::Team2 ? L"Adornia" : L"Doct",
        ready ? L"<style:green>ready</style>" : L"<style:money>not ready</style>" );

      lines.push_back( line );
      linesIds.push_back( memb.user.userId );
    }
  }

  heroScreen->UpdatePlayers( lines, linesIds, hilitePlayers );
}

void LocalGameContext::ChangeCustomGameSettings( lobby::ETeam::Enum team, lobby::ETeam::Enum faction, const string & heroId )
{
  for ( int i = 0; i < gameLineup.size(); ++i )
    if ( gameLineup[i].context.playerType == lobby::EPlayerType::Human )
    {
      if ( team != lobby::ETeam::None )
      {
        gameLineup[i].context.team = team;
      }

      if ( faction != lobby::ETeam::None )
      {
        gameLineup[i].context.original_team = faction;
      }

      if ( !heroId.empty() )
      {
        gameLineup[i].context.hero = heroId;
      }

      OnLobbyDataChange();
      return;
    }

  NI_ALWAYS_ASSERT( "No humans detected in games" );
}



void LocalGameContext::SetReady( lobby::EGameMemberReadiness::Enum readiness )
{
  NI_VERIFY( state == ELocalGameState::InCustomGame, "", return );

  if ( ( readiness == lobby::EGameMemberReadiness::Ready ) || ( readiness == lobby::EGameMemberReadiness::ReadyForAnything ) )
  {
    NI_VERIFY( mapLoader, "", return );

    GenerateLineup( maxPlayers );

    lobby::SGameParameters params;

    lobby::ETeam::Enum manoeuvresFaction = lobby::ETeam::None;

    for (int i = 0; i < gameLineup.size(); ++i)
    {
      const lobby::SGameMember & lobbyPlayer = gameLineup[i];
      manoeuvresFaction = lobbyPlayer.context.original_team;
    }

    params.manoeuvresFaction = manoeuvresFaction;
    params.randomSeed = GetTickCount();
    params.mapId = mapLoader->GetMapDescName();

    vector<Peered::ClientInfo> empty;

    mapLoader->FillMapStartInfo( mapStartInfo, gameLineup, params );
    mapLoader->FillPlayersInfo( mapStartInfo, empty );

    PrepareReplayWriter();

    if (replayWriter)
    {
      NCore::ClientSettings clientSettings;

      clientSettings.minigameEnabled = true;

      replayWriter->WriteLobbyData(0, gameLineup, params);
      replayWriter->WriteGSData(100, clientSettings, empty);
    }

    if ( heroScreen )
      NScreenCommands::PushCommand( NScreenCommands::CreatePopScreenCommand( heroScreen ) );

    ShowLoadingScreen();

    state = ELocalGameState::ShowingLoadingScreen;
  }
}



void LocalGameContext::SetDeveloperParty(int)
{
  
}



void LocalGameContext::OnCombatScreenStarted( NCore::IWorldBase * _world, const NGameX::ReplayInfo & _replayInfo )
{
  NI_VERIFY( state == ELocalGameState::StartingAdvScreen, "", return );

  //_world->SetAccounting( client->GetAccounting() );

  scheduler->OnCombatScreenStarted(_replayInfo);

  transceiver->SetWorld( _world );
  transceiver->RecordMapStart( mapStartInfo );

  NI_ASSERT( !mapLoadingJob, "" );
  NI_ASSERT( mapDescription->IsSuccessfullyLoaded, "" );
  
  mapLoadingJob = new NWorld::MapLoadingJob( _world, mapStartInfo, mapDescription->Description, mapDescription->Settings, mapDescription->Map, false );

  NI_ASSERT( loadingScreeen, "" );
  loadingScreeen->SetProgress( mapLoadingJob->GetProgress() );

  state = ELocalGameState::LoadingMap;

  using NWorld::MapLoader;

  if (MapLoader::IsThreaded())
  {
    loadingThread = MapLoader::CreateMapLoadingThread(mapLoadingJob);
  }
  else
  {
    mapLoadingJob->DoTheJob();

    LaunchGame();
  }
}



void LocalGameContext::OnVictory( const StatisticService::RPC::SessionClientResults & _sessionResults, const NGameX::ReplayInfo & _replayInfo )
{
  NI_VERIFY( state == ELocalGameState::Playing, "", return );
  state = ELocalGameState::GameFinished;
  scheduler->OnVictory(_sessionResults, _replayInfo);
}

void LocalGameContext::SetTimeScale( float timescale )
{
  NMainLoop::SetTimeScale( timescale );
}

void LocalGameContext::LeaveGame()
{
  advScreeen = NULL;
  gameLineup.clear();
  scheduler = NULL;
  transceiver = NULL;
}

bool LocalGameContext::IsGameReady()
{
  return ( state == ELocalGameState::Playing ) || ( state == ELocalGameState::GameFinished );
}



void LocalGameContext::StartGame()
{
  NI_VERIFY( state == ELocalGameState::ShowingLoadingScreen, "", return );
  NI_VERIFY( !scheduler && !transceiver, "Game can be started only once", return );

  scheduler = new LocalCmdScheduler( clientId );
  transceiver = new NCore::Transceiver( scheduler, DEFAULT_GAME_STEP_LENGTH, true );

  if (replayWriter)
  {
    scheduler->SetReplayWriter(replayWriter);
    replayWriter->WriteStartGame(0, 0);
  }

  advScreeen = new NGameX::AdventureScreen;
  advScreeen->SetLobbyCallback( this );
  advScreeen->Construct( chatController, NULL, ignoreListStorage, isSpectator, false );
  
  if ( !advScreeen->InitAdventures( mapStartInfo, transceiver, 0, lobby::EGameType::Custom, clientId, resourceCollection, 0, 0 ) )
    return;

  advScreeen->InitPlayerNames(mapStartInfo, clientId, mapDescription->Description);

  NScreenCommands::PushCommand( NScreenCommands::CreatePushScreenCommand( advScreeen ) );

  state = ELocalGameState::StartingAdvScreen;
}



void LocalGameContext::ShowLoadingScreen()
{
  NI_VERIFY( !loadingScreeen, "", return );

  loadingScreeen = new Game::LoadingScreen( "", "", isSpectator, false );
  
  NScreenCommands::PushCommand( NScreenCommands::CreatePushScreenCommand( loadingScreeen ) );

  Strong<Game::LoadingGameContext> loadingGameContext = new Game::LoadingGameContext( mapStartInfo );
  loadingGameContext->chatController = chatController;
  loadingGameContext->advMapDescription = mapDescription->Description;
  loadingGameContext->advMapSettings = mapDescription->Settings;
  loadingGameContext->ignoreListStorage = ignoreListStorage;
 // loadingGameContext->lineup = gameLineup;
  loadingGameContext->userId = clientId;
   
  for ( int i = 0; i < mapStartInfo.playersInfo.size(); ++i )
  {
    const NCore::PlayerStartInfo& slotInfo = mapStartInfo.playersInfo[i];
    Game::HeroInfo info;

    if ( slotInfo.playerInfo.heroId == 0 || slotInfo.teamID == NCore::ETeam::None)
      continue;

    if (slotInfo.playerType != NCore::EPlayerType::Human)
      info.isBot = true;

    info.team = slotInfo.teamID ;
    info.originalTeam = slotInfo.originalTeamID;
    info.locale = slotInfo.playerInfo.locale;
    if (mapDescription->Description->canUseSkins)
    {
      info.skinId = slotInfo.playerInfo.heroSkin;
      info.isAnimatedAvatar = slotInfo.playerInfo.isAnimatedAvatar;
    }
    info.heroId = slotInfo.playerInfo.heroId;
    info.leagueIndex = slotInfo.playerInfo.leagueIndex;
    info.ownLeaguePlace = slotInfo.playerInfo.ownLeaguePlace;
    info.leaguePlaces = slotInfo.playerInfo.leaguePlaces;
    
    loadingGameContext->lineup_info[slotInfo.playerID] = info;
  }
  
  loadingScreeen->Setup(loadingGameContext);
}



void LocalGameContext::LaunchGame()
{
  NI_VERIFY( state == ELocalGameState::LoadingMap, "", return );

  NI_VERIFY( mapLoadingJob, "", return );
  NI_VERIFY( advScreeen, "", return );
  advScreeen->OnMapLoaded( mapLoadingJob->MapDescriptionResource(), mapLoadingJob->GetCameraSettings() );
  mapLoadingJob = 0;

  advScreeen->ActivateSessionSoundScene();
  advScreeen->OnSessionStart( 0);

  if ( loadingScreeen )
    NScreenCommands::PushCommand( NScreenCommands::CreatePopScreenCommand( loadingScreeen ) );

  scheduler->StartGame();

  state = ELocalGameState::Playing;
}



bool LocalGameContext::SetTimeScale( const char *name, const vector<wstring> &args )
{
  if ( args.size() == 1 )
  {
    double scale = NStr::ToDouble( args[0] );
    if ( scale >= 0.01 && scale < 100.0 )
    {
      NMainLoop::SetTimeScale( scale );
      return true;
    }
  }
  MessageTrace( "Usage: %s <scale in range 0.01...100.0>", name );
  return true;
}



bool LocalGameContext::CustomGameCreate( const char * name, const vector<wstring> & args )
{
  if ( state != ELocalGameState::InLobby )
    return false;

  if ( args.size() == 2 )
  {
    int playersNumber = NStr::ToInt( args[0] );
    string mapId = NStr::ToMBCS( args[1] );
    if ( !mapId.empty() && playersNumber > 0 )
    {
      CreateGame( mapId.c_str(), playersNumber );
      return true;
    }
  }
  MessageTrace( "Wrong '%s' syntax: %s <player number> <map id>", name, name );
  return true;
}



bool LocalGameContext::CustomGameSettings( const char * name,  const vector<wstring> & args )
{
  if ( state != ELocalGameState::InCustomGame )
    return false;

  int team = -1;
  int faction = -1;
  string hero ;

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
  else
  {
    MessageTrace( "Wrong '%s' syntax: %s <team -1|0|1> <hero id>", name, name );
    return true;
  }

  if ( !hero.empty() && ( ( team == lobby::ETeam::Team1 ) || ( team == lobby::ETeam::Team2 ) )
    && ( ( faction == lobby::ETeam::Team1 ) || ( faction == lobby::ETeam::Team2 ) ))
  {
    ChangeCustomGameSettings( (lobby::ETeam::Enum)team, (lobby::ETeam::Enum)faction, hero );
    return true;
  }

  return true;
}



bool LocalGameContext::CustomGameReady( const char * name, const vector<wstring> & args )
{
  if ( state != ELocalGameState::InCustomGame )
    return false;

  if ( args.size() == 1 )
  {
    int rdy = NStr::ToInt( args[0] );
    if ( ( rdy == lobby::EGameMemberReadiness::Ready ) || ( rdy == lobby::EGameMemberReadiness::ReadyForAnything ) )
    {
      SetReady( (lobby::EGameMemberReadiness::Enum)rdy );
      return true;
    }
  }
  MessageTrace( "Wrong '%s' syntax: %s <ready 1|2>", name, name );
  return true;
}


bool LocalGameContext::LoadReplay( const char * name, const vector<wstring> & args )
{
  if ( state != ELocalGameState::InLobby && state != ELocalGameState::InCustomGame )
  {
    MessageTrace( "Replay can be started only in lobby!" );
    return false;
  }

  const string replayName = NStr::ToMBCS( args[0] );
  replayRunner = new ReplayRunner( replayName, mapCollection );

  if ( lobbyScreen )
    NScreenCommands::PushCommand( NScreenCommands::CreatePopScreenCommand( lobbyScreen ) );

  NScreenCommands::PushCommand( NScreenCommands::CreatePushScreenCommand( replayRunner ) );

  return true;
}

void LocalGameContext::StopAsyncMapLoadingJob()
{
  if (replayRunner)
    replayRunner->StopAsyncMapLoadingJob();

  if (loadingThread)
  {
    loadingThread->AsyncStop();
    loadingThread->Wait(30000);
  }
}

void LocalGameContext::PrepareReplayWriter()
{
  if (!g_enableReplayLocalGame)
    return;

  const Login::ClientVersion ver(VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH, VERSION_REVISION);

  replayWriter = new NCore::ReplayWriter();
  replayWriter->WriteVersion(ver);
}

} //namespace Game
