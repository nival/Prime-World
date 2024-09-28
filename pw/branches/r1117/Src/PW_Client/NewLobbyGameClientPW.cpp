#include "stdafx.h"

#include "NewLobbyGameClientPW.h"
#include "NewLobbyClientPW.h"

#include "PF_GameLogic/StringExecutor.h"
#include "PF_GameLogic/AdventureScreen.h"
#include "PF_GameLogic/ChatController.h"
#include "PF_GameLogic/SmartChatController.h"

#include "PF_GameLogic/PFWorld.h"
#include "PF_GameLogic/PFAIWorld.h"
#include "PF_GameLogic/PFAIContainer.h"
#include "PF_GameLogic/MapStartup.h"
#include "PF_GameLogic/PFTalent.h"
#include "PF_GameLogic/PFMaleHero.h"
#include "PF_GameLogic/PFHero.h"

#include "System/LoadingProgress.h"
#include "System/FileSystem/FileActivitySimpleMonitor.h"
#include "Client/LobbyPvx/HybridServerNodeImpl.h"
#include "Client/ScreenCommands.h"
#include "HybridServer/RPeered.auto.h"
#include "HybridServer/PeeredTypes.h"

#include "LoadingScreen.h"
#include "NetworkStatusScreen.h"

#include "System/InlineProfiler.h"

#include "Sound/EventScene.h"
#include "PF_GameLogic/DBSound.h"
#include "PF_GameLogic/DBServer.h"
#include "DebugVarsSender.h"
#include "GameStatistics.h"
#include "FastReconnectCtxPW.h"
#include "PF_GameLogic/MapDescriptionLoader.h"

#include "PF_GameLogic/ForceCalc.h"
#include "PF_GameLogic/ChatController.h"
#include "PF_GameLogic/IgnoreListStorage.h"

#include "PF_GameLogic/AsyncMapStartup.h"

#include "Game/PF/Server/LobbyPvx/CommonTypes.h"

#include "UI/FrameTimeRender.h"
#include "PF_GameLogic/SocialConnection.h"
#include "PF_GameLogic/PlayerBehaviourTracking.h"

static bool s_threaded_loading = true;
REGISTER_VAR( "threaded_loading", s_threaded_loading, STORAGE_NONE );

static bool s_LogIngameActivity = false;
REGISTER_DEV_VAR( "fs_log_ingame_activity0", s_LogIngameActivity, STORAGE_NONE );

static int s_boostVal = 1;
REGISTER_DEV_VAR( "boost_thread_priority_val", s_boostVal, STORAGE_NONE);
// NOTE: hardcode. полагаемся на то, что оператор настроит список жалоб правильно. см. NUM_TASK
#ifndef BAD_BEHAVIOUR_REPORT_ITEM_ID
#define BAD_BEHAVIOUR_REPORT_ITEM_ID 1
#endif
#ifndef INSULT_REPORT_ITEM_ID
#define INSULT_REPORT_ITEM_ID 2
#endif

namespace lobby
{

GameClientPW::GameClientPW( ClientPW * _client, NWorld::IMapCollection * _mapCollection, Game::NetworkStatusScreen * _networkStatusScreen, 
                           FastReconnectCtxPW * _fastReconnectCtxPw, NGameX::ISocialConnection * _socialConnection, Game::LoadingScreen * _loadingScreen, 
                           NGameX::GuildEmblem* _guildEmblem, const bool _isSpectator, const bool _isTutorial ) :
GameClient( _client, _mapCollection, _fastReconnectCtxPw, _isSpectator, _isTutorial ),
mapLoadStatus( _fastReconnectCtxPw ? EMapLoading::Done : EMapLoading::None ),
networkStatusScreen( _networkStatusScreen ),
client(_client),
saveWorldStep(-1),
fastReconnectCtxPw( _fastReconnectCtxPw ),
socialConnection(_socialConnection),
guildEmblem( _guildEmblem ),
loadingScreeen (_loadingScreen)
{
  if (_fastReconnectCtxPw && _fastReconnectCtxPw->GetResourcesCollection())
  {
    resourceCollection = _fastReconnectCtxPw->GetResourcesCollection();
  }
  else
  {
    resourceCollection = new NWorld::PFResourcesCollection;
    resourceCollection->CollectTalents();
    resourceCollection->CollectConsumables();
    resourceCollection->CollectMarketingItems();
  }

  ignoreListStorage = new NGameX::IgnoreListStorage( ClientId() );
}

//наму нужен деструктор, чтобы в явном виде указать какие члены долны шотдауниться раньше
GameClientPW::~GameClientPW()
{
  loadingThread = 0;
  mapLoadingJob = 0;
  saveCompressThread = 0;
  saveCompressJob = 0;    

  fastReconnectCtxPw = 0;

  client = 0;
  debugVarsSender = 0;

  chatController = 0;
  smartChatController = 0;

  resourceCollection = 0;
}


int GameClientPW::Poll( float transceiverDeltaTime )
{
  int numCommands = GameClient::Poll( transceiverDeltaTime );

  if ( networkStatusScreen )
  {
    if ( ServerNode() )
      networkStatusScreen->SetGsGracefullDisconnectReason( ServerNode()->GracefullDisconnectReason() );

    if ( Transceiver() )
      if ( Transceiver()->IsAsynced() )
        networkStatusScreen->SetClientAsync();
  }

  //PollClientStatusChange();

  switch ( mapLoadStatus )
  {
    default:
    case EMapLoading::None:
      break;


    case EMapLoading::MainThreadLoading:
      NI_VERIFY( mapLoadingJob, "", break );
      mapLoadingJob->DoTheJob();
      mapLoadStatus = EMapLoading::MapLoaded;
      break;


    case EMapLoading::ParallelLoading:
      NI_VERIFY( mapLoadingJob, "", break );

      if ( loadingThread->Wait( 0 ) )
      {
        loadingThread = 0;
        mapLoadStatus = EMapLoading::MapLoaded;
      }
      else
      {
        Sleep( 50 ); //Let da loadin tred do da woak
        float pro = mapLoadingJob->GetProgress()->GetTotalProgress();
        SetMapLoadingProgress( Clamp( (int)( pro * 100.0f ), 0, 100 ) );

        UpdatePerPlayerProgress();
      }
      break;

    case EMapLoading::MapLoaded:
      if (ServerNode() && ServerNode()->IsStarted())
      {
        if (ServerNode()->IsReconnecting())
        {
          ServerNode()->RequestWorldDataFromServer();
          mapLoadStatus = EMapLoading::WaitForSnapshot;
        }
        else
        {
          mapLoadStatus = EMapLoading::FinishLoading;
        }
      }
      break;

    case EMapLoading::WaitForSnapshot:
      PollWorldData();
      break;

    case EMapLoading::FinishLoading:
      NI_VERIFY( mapLoadingJob, "", break );
      NI_VERIFY( advScreeen, "", break );
      advScreeen->OnMapLoaded( mapLoadingJob->MapDescriptionResource(), mapLoadingJob->GetCameraSettings() );

      if ( const NDb::AdvMapSettings * advMapSettings = mapLoadingJob->MapSettingsResource() )
      {
        bool enableBotsAI = mapLoadingJob->MapSettingsResource()->overrideBotsSettings ? mapLoadingJob->MapSettingsResource()->overrideBotsSettings->enableBotsAI 
                                                                                       : NDb::SessionRoot::GetRoot()->logicRoot->aiLogic->botsSettings->enableBotsAI;
        if ( enableBotsAI && Client()->GameParams().gameType == EGameType::SocialMMaking )
        {
          advScreeen->StartBots( NGameX::AdventureScreen::FilterHumans, true );
        }
      }

      OnMapLoaded();

      mapLoadingJob = 0;
      mapLoadStatus = EMapLoading::Done;
      break;


    case EMapLoading::Done:
      UpdatePerPlayerProgress();
      break;
  }

  switch(GameState())
  {
  case EGameState::Running:
    {
      if ( debugVarsSender && Transceiver() )
        debugVarsSender->PollSession( Transceiver()->GetWorldStep() );

      PollWorldRequest();

      ProcessSpectatorJoin();
      ProcessBadBehaviourComplaints();

      if (NCore::ServerNode * serverNode = ServerNode())
      {
        float scale = 0.f;
        if (advScreeen && serverNode->PopNewTimeScale(scale))
        {
          advScreeen->OnTimeScaleChanged(scale);
        }
      }      
    }
    break;

  case EGameState::Finished:
    if (NCore::ServerNode * serverNode = ServerNode())
    {
      if (advScreeen && serverNode->IsAwardsReceived())
      {
        advScreeen->AwardUser(serverNode->GetAwards());
        serverNode->SetAwardsReceived(false);
      }
    }
    {
      ProcessPlaySameTeamDecisions();
    }
    break;
  }

  return numCommands;
}



void GameClientPW::OnAltTab(bool isActive)
{
  s_boostVal;

  if ( loadingThread )
    loadingThread->SetPriority( isActive ? 0 : s_boostVal );
}



void GameClientPW::ProcessAsyncStatus( NCore::ClientStatus & status )
{
  if ( advScreeen)
    advScreeen->OnClientStatusChange( status.clientId, status.status, status.step );

  if ( loadingScreeen )
    loadingScreeen->OnClientStatusChange( status.clientId, status.status, status.step );
}



Peered::EDisconnectReason::Enum GameClientPW::GracefullDisconnectReason()
{
  if ( !ServerNode() )
    return Peered::EDisconnectReason::None;
   return ServerNode()->GracefullDisconnectReason();
}



void GameClientPW::SetupFastReconnectCtx( FastReconnectCtxPW * ctx )
{
  ctx->SetMaps( GetMapCollection(), GetMapLoader() );
  ctx->SetGameSvcStuff( Scheduler(), Transceiver(), ServerNode(), ReplayWriter() );
  ctx->SetAdvScreen( advScreeen );
  ctx->SetChatController( chatController );
  ctx->SetSmartChatController( smartChatController );
  ctx->SetStatistics( GameStatistics() );
  ctx->SetResourcesCollection( resourceCollection );
}


//void GameClientPW::PollClientStatusChange()
//{
//  while ( true )
//  {
//    wstring nickname;
//    Peered::BriefClientInfo info;
//    bool ret = PopClientStatusChange( nickname, info );
//
//    if ( !ret )
//      break;
//
//    if ( advScreeen && Transceiver())
//    {
//      if (NWorld::PFWorld * pWorld = advScreeen->GetWorld())
//      {
//        // Calculate world step relative to game server step
//        int step = info.step - (Transceiver()->GetNextStep() - pWorld->GetStepNumber());
//        advScreeen->OnClientStatusChange( info.clientId, info.status, step );
//      }
//    }
//
//    if ( loadingScreeen )
//      loadingScreeen->OnClientStatusChange( info.clientId, info.status, info.step );
//  }
//}



void GameClientPW::PollWorldRequest()
{
  if (!advScreeen || !ServerNode() || !Transceiver())
    return;

  if (ServerNode()->IsWorldDataInProgress())
  {
    ServerNode()->SendWorldDataParts();
  }
  else if ( saveCompressThread )
  {
    if ( saveCompressThread->Wait( 0 ) )
    {
      Stream & worldData = ServerNode()->GetWorldDataStream();
      worldData.Seek(0, SEEKORIGIN_BEGIN);

      int sentSize = saveCompressJob->GetDestStream()->GetPosition();
      saveCompressJob->GetDestStream()->Seek(0, SEEKORIGIN_BEGIN);
      worldData.CopyFrom( saveCompressJob->GetDestStream(), sentSize );

      ServerNode()->SendWorldData( saveWorldStep );
      SetLastWorldRequestStep( saveWorldStep );

      saveCompressThread = 0;
      saveCompressJob = 0;
    }
  }
  else if (NWorld::PFWorld * pWorld = advScreeen->GetWorld())
  {
    bool worldRequest = false;
    int  step = Transceiver()->GetNextStep();

    ServerNode()->PopWorldRequest( worldRequest, step );

    if ( worldRequest )
    {
      saveWorldStep = step;
      saveCompressJob = new NWorld::SaveCompressThreadJob( false );

      pWorld->GetWorldChecker()->SaveWithoutCompression( *saveCompressJob->GetSourceStream() );

      saveCompressThread = new threading::JobThread( saveCompressJob, "SaveCompressing" );
    }
  }
}



void GameClientPW::PollWorldData()
{
  if (!advScreeen || !ServerNode() || !Transceiver())
    return;

  if (NWorld::PFWorld * pWorld = advScreeen->GetWorld())
  {
    if (ServerNode()->IsWorldDataReady())
    {
      MemoryStream worldData; // Proper buffer size will be set in the PopWorldData()
      int segmentStep;

      ServerNode()->PopWorldData( worldData, segmentStep );

      DebugTrace("Reconnect: World data received (size=%d)", worldData.GetPosition());
      Transceiver()->SetNextStep(segmentStep);
      Transceiver()->SetPrecalcCrcOnce( true );

      DebugTrace("Reconnect: Applying world data...");
      pWorld->GetAIWorld()->ClearVoxelMap();
      pWorld->GetWorldChecker()->Load( worldData );
      pWorld->Reset();
      if (pWorld->GetAIContainer())
      {
        pWorld->GetAIContainer()->OnReconnect();
      }
      mapLoadStatus = EMapLoading::FinishLoading;
      DebugTrace("Reconnect: World data applied");
    }
  }  
}



void GameClientPW::SetChatClient( gamechat::IClient * chatClient )
{
  {
    if (IsValid(chatController) && IsValid(smartChatController))
      chatController->RemoveMessageHook(smartChatController.Get());
  }

  if (fastReconnectCtxPw)
  {
    chatController = fastReconnectCtxPw->ChatController();
    chatController->OnFastReconnect(chatClient, ignoreListStorage);

    smartChatController = fastReconnectCtxPw->SmartChatController();
    smartChatController->OnFastReconnect(chatClient);
  }
  else
  {
    chatController = new NGameX::ChatUiController(chatClient);
    smartChatController = new NGameX::SmartChatController(chatClient);
  }

  {
    if (IsValid(chatController) && IsValid(smartChatController))
      chatController->AddMessageHook(smartChatController.Get());
  }
}



void GameClientPW::ShowLoadingScreen()
{
  if ( fastReconnectCtxPw )
    return;

  NI_VERIFY( loadingScreeen, "", return );

  if (!MapDescription()->IsSuccessfullyLoaded)
    return;

  Strong<Game::LoadingGameContext> loadingGameContext = new Game::LoadingGameContext( GetMapStartInfo() );
  loadingGameContext->chatController = chatController;
  loadingGameContext->advMapDescription = MapDescription()->Description;
  loadingGameContext->advMapSettings = MapDescription()->Settings;
  loadingGameContext->ignoreListStorage = ignoreListStorage;
  loadingGameContext->userId = Client()->ClientId();
  loadingGameContext->params = Client()->GameParams();
  loadingGameContext->lineup_info = lineup_info;

  loadingScreeen->Setup(loadingGameContext );

  if (client)
  {
    NDebug::SetSrv2ClientTimeDelta(client->GetTimeDelta());
    NDebug::ShowSrvTime(true);
  }

  if (IsValid(chatController))
  {
    chatController->Reset();
  }

  if (IsValid(smartChatController))
  {
    smartChatController->Reset();
    smartChatController->OnStartLoading();
  }

  //NScreenCommands::PushCommand( NScreenCommands::CreatePushScreenCommand( loadingScreeen ) );
}



void GameClientPW::HideLoadingScreen()
{
  if ( !loadingScreeen )
    return;

  NScreenCommands::PushCommand( NScreenCommands::CreatePopScreenCommand( loadingScreeen ) );
  loadingScreeen = 0;

  //TODO: Move to AdventureScreen::OnSessionStarted
	DebugTrace( "HideLoadingScreen" );

  if ( advScreeen )
  {
    advScreeen->ActivateSessionSoundScene();
    advScreeen->OnSessionStart( Client()->GameSessionId(), ServerNode() ? ServerNode()->IsReconnecting() : false );
  }

  if ( s_LogIngameActivity )
    RootFileSystem::AddDebugMonitor( new FileActivitySimpleMonitor( "ingame_fs_activity" ) );

  if ( debugVarsSender && GameStatistics())
  {
    for ( int i = 0; i < GetMapStartInfo().playersInfo.size(); ++i )
      if ( GetMapStartInfo().playersInfo[i].userID == ClientId() )
      {
        debugVarsSender->OnSessionStart( GameStatistics()->GetGameStatisticsDebugWriter(), Client()->GameSessionId(), GetMapStartInfo().playersInfo[i].userID );
        break;
      }
  }

  NDebug::ShowSrvTime(false);

  if (IsValid(chatController))
  {
    chatController->Reset();
  }

  if (IsValid(smartChatController))
  {
    smartChatController->Reset();
    smartChatController->OnFinishLoading();
  }
}


//////////////////////////////////////////////////////////////////////////

void GameClientPW::OnPlayerInfoLoaded()
{
  if (!loadingScreeen)
    return;

  if (ServerNode())
  {
    // OnPlayerInfoLoaded() is called after start from Game Server, so client settings are available here
    loadingScreeen->ApplyClientSettings(ServerNode()->GetClientSettings());
  }


  bool hasBots = false;


  const NCore::MapStartInfo & startInfo = GetMapStartInfo();

  for( int i = 0; i < startInfo.playersInfo.size(); ++i )
  {
    if (startInfo.playersInfo[i].playerType == NCore::EPlayerType::Computer)
    {
      hasBots = true;
      break;
    }  
  }

  for( int i = 0; i < startInfo.playersInfo.size(); ++i )
  {
    const NCore::PlayerStartInfo & playerStartInfo = startInfo.playersInfo[i];
    
    if ( playerStartInfo.playerInfo.heroId == 0 || playerStartInfo.teamID == NCore::ETeam::None)
      continue;

    Game::HeroInfo info;

    if (playerStartInfo.playerType == NCore::EPlayerType::Human)
    {
      float force = NWorld::Force::CalculateForce(playerStartInfo.playerInfo, playerStartInfo.usePlayerInfoTalentSet, resourceCollection, MapDescription()->Description);

      info.exp = playerStartInfo.playerInfo.heroExp;
      info.force = force;
      info.raiting = (int)( playerStartInfo.playerInfo.heroRating );

      if (!hasBots && !Client()->GameParams().customGame) // с ботами или в договорных не дают рейт
      {
        info.winDeltaRaiting = playerStartInfo.playerInfo.ratingDeltaPrediction.onVictory;
        info.loseDeltaRaiting = playerStartInfo.playerInfo.ratingDeltaPrediction.onDefeat;
      }

      info.isNovice = ( playerStartInfo.playerInfo.basket == NCore::EBasket::Newbie );
      info.isPremium = playerStartInfo.playerInfo.hasPremium;
      info.partyId = playerStartInfo.playerInfo.partyId;
      info.basket = playerStartInfo.playerInfo.basket;

      DevTrace("SetHeroInfo user = %d, force = %f, raiting = %f, deltaWin = %f, deltaLose = %f, partyId = %d, leagueIndex = %d, ownLeaguePlace = %d",
        playerStartInfo.userID, force, playerStartInfo.playerInfo.heroRating,
        info.winDeltaRaiting, info.loseDeltaRaiting, playerStartInfo.playerInfo.partyId, playerStartInfo.playerInfo.leagueIndex, playerStartInfo.playerInfo.ownLeaguePlace  );
    } 
    else
    {
      info.isBot = true;
      float force = NWorld::Force::CalculateForce(playerStartInfo.playerInfo, playerStartInfo.usePlayerInfoTalentSet, resourceCollection, MapDescription()->Description);
      info.force = force;
      info.raiting = (int)( playerStartInfo.playerInfo.heroRating );
      info.basket = playerStartInfo.playerInfo.basket;
    }

    info.team = playerStartInfo.teamID ;
		info.originalTeam = playerStartInfo.originalTeamID;
    info.locale = playerStartInfo.playerInfo.locale;
    if (MapDescription()->Description->canUseSkins)
    {
      info.skinId = playerStartInfo.playerInfo.heroSkin;
      info.isAnimatedAvatar = playerStartInfo.playerInfo.isAnimatedAvatar;
    }
    info.heroId = playerStartInfo.playerInfo.heroId;
    info.leagueIndex = playerStartInfo.playerInfo.leagueIndex;
    info.ownLeaguePlace = playerStartInfo.playerInfo.ownLeaguePlace;
    info.leaguePlaces = playerStartInfo.playerInfo.leaguePlaces;

    lineup_info[playerStartInfo.playerID] = info;    
  }

  
  ShowLoadingScreen();
}



void GameClientPW::CreateAdventureScreen()
{
  NI_PROFILE_FUNCTION;

  if ( fastReconnectCtxPw && fastReconnectCtxPw->AdvScreen() )
  {
    advScreeen = fastReconnectCtxPw->AdvScreen();
    advScreeen->SetLobbyCallback( this );
    if ( client )
      client->SetAdvScreen( advScreeen );
    return;
  }

  Strong<NGameX::AdventureScreen> screen = new NGameX::AdventureScreen;
  screen->SetLobbyCallback( this );
  screen->Construct( chatController, smartChatController, ignoreListStorage, IsSpectator(), IsTutorial() );

  const NCore::ClientSettings & clientSettings = ServerNode()->GetClientSettings();
  NGameX::GSClientSettings gsClientSettings(clientSettings.minigameEnabled, clientSettings.logicParam1,
                                              clientSettings.showGuildEmblem, clientSettings.shareUrl,
                                              clientSettings.aiForLeaversEnabled, clientSettings.aiForLeaversThreshold);
  screen->ApplyGSClientSettings(gsClientSettings);

  if ( !screen->InitAdventures( GetMapStartInfo(), Transceiver(), GameStatistics(), Client()->GameParams().gameType, ClientId(), resourceCollection, socialConnection, guildEmblem, ServerNode()->GetSimulationStep() ) )
    return;

  // initialize names earlier to make them available at loading screen too
  screen->InitPlayerNames(GetMapStartInfo(), ClientId(), MapDescription()->Description);
  screen->SetCustomSessionType(Client()->GameParams().customGame);

  advScreeen = screen;

  NScreenCommands::PushCommand( NScreenCommands::CreatePushScreenCommand( screen ) );

  if (client)
    client->SetAdvScreen(advScreeen);
}


void GameClientPW::NotifyChatMuted()
{
  if (!IsValid(advScreeen))
    return;
  if (!IsValid(chatController))
    return;

  NWorld::PFWorld* const world = advScreeen->GetWorld();

  if (!world)
    return;

  for (int i = 0, playerCount = world->GetPlayersCount(); i < playerCount; ++i)
  {
    const NWorld::PFPlayer* const player = world->GetPlayer(i);

    if (!player)
      continue;
    if (!player->IsChatMuted())
      continue;

    chatController->NotifyChatMuted(player);
  }
}

void GameClientPW::SendTeam()
{
  NGameX::AdventureScreen * advScreen = NGameX::AdventureScreen::Instance();
  if (!advScreen )
    return;

  NWorld::PFWorld *world = advScreen->GetWorld();
  if ( !world )
    return;

  NWorld::PFPlayer* player = world->GetPlayer( advScreen->GetLocalPlayerID() );
  if ( !player )
    return;

  nstl::vector<__int64> auids;
  for(int i = 0; i< world->GetPlayersCount(); ++i)
  {
    NWorld::PFPlayer* p = world->GetPlayer( i );
    if (p && p->GetUserID() != -1 && player->GetUserID() != p->GetUserID() && player->GetTeamID()== p->GetTeamID()){

      NWorld::PFBaseHero* hero = p->GetHero();
      if ( hero )
      {
        NWorld::PFHeroStatistics* stat = hero->GetHeroStatistics();
        if ( stat && !Peered::IsConnectedStatus(stat->GetLeaveStatus()))
        {
          DevTrace("GameClientPW::SendTeam - player %s is leaver", p->GetPlayerName());
          continue;
        }
      
      }
      NGameX::IgnoreListStorage* ilist= advScreen->GetIgnoreListStorage();
      
      if (ilist && ilist->ContainsUser(p->GetUserID()))
      {
        DevTrace("GameClientPW::SendTeam - player %s in your ignorelist", p->GetPlayerName());
        continue;
      }
      
      if (advScreen->InComplList(p))
      {
        DevTrace("GameClientPW::SendTeam - player %s in your ComplList", p->GetPlayerName());
        continue;
      }

      auids.push_back(p->GetUserID());
    }
  }
  if (auids.empty())
  {
    DevTrace("GameClientPW::SendTeam - vector auids is empty");
    return; 
  }
  Strong<NGameX::ISocialConnection> socialServer  = advScreen->GetSocialConnection();
  socialConnection->SendTeam( player->GetUserID(), auids );

}


void GameClientPW::StartMapLoading( NCore::IWorldBase * world )
{
  NI_ASSERT( !mapLoadingJob, "" );
  NI_ASSERT( mapLoadStatus == EMapLoading::None, "" );

  if (!MapDescription()->IsSuccessfullyLoaded)
    return;

  mapLoadingJob = new NWorld::MapLoadingJob( world, GetMapStartInfo(), MapDescription()->Description, MapDescription()->Settings, MapDescription()->Map, ServerNode()->IsReconnecting() );

  NI_ASSERT( loadingScreeen, "" );
  loadingScreeen->SetProgress( mapLoadingJob->GetProgress() );

  if ( s_threaded_loading )
    NI_VERIFY( NGlobal::GetVar( "render_threadsafe", 1 ).GetInt64(), "Parallel map loading was requested, but render is not in thread-safe mode. Falling back to single-threaded loading.", s_threaded_loading = false );

  using NWorld::MapLoader;

  if (MapLoader::IsThreaded())
  {
    mapLoadStatus = EMapLoading::ParallelLoading;
    loadingThread = MapLoader::CreateMapLoadingThread(mapLoadingJob);
  }
  else
  {
    mapLoadStatus = EMapLoading::MainThreadLoading;
  }
}



void GameClientPW::OnCombatScreenStarted( NCore::IWorldBase * _world, const NGameX::ReplayInfo & _replayInfo  )
{
  GameClient::OnCombatScreenStarted( _world, _replayInfo );
}



void GameClientPW::OnVictory( const StatisticService::RPC::SessionClientResults & _sessionResults, const NGameX::ReplayInfo & _replayInfo )
{
  //Session finished, kill network status screen
  if ( networkStatusScreen )
    NScreenCommands::PushCommand( NScreenCommands::CreatePopScreenCommand( networkStatusScreen ) );
  networkStatusScreen = 0;

  GameClient::OnVictory( _sessionResults, _replayInfo );
}


void GameClientPW::SetTimeScale(float timescale)
{
  if (NCore::ServerNode* const serverNode = ServerNode())
  {
    if (Peered::IGameServer* const server = serverNode->GameServer())
    {
      server->SetTimeScale(serverNode->GetClientIndex(), timescale);
    }
  }
}

void GameClientPW::LeaveGame()
{
  client->LeaveGame(ServerNode()->GetClientIndex());
  ServerNode()->DumpLags();
}



bool GameClientPW::IsGameReady()
{
  return mapLoadStatus > EMapLoading::FinishLoading && ( GameState() == EGameState::Running || GameState() == EGameState::Finished );
}



bool GameClientPW::IsWaitingLeaveAck()
{
  return ( client->Status() == EClientStatus::LeavingServer );
}



void GameClientPW::DispatchPlaySameTeamDecision(const bool agreed)
{
  if (NCore::ServerNode* const serverNode = ServerNode())
  {
    if (Peered::IGameServer* const server = serverNode->GameServer())
    {
      server->DispatchPlaySameTeamDecision(serverNode->GetClientIndex(), agreed);
    }
  }
}



void GameClientPW::DispatchBadBehaviourComplaint(const int userId, const int reportItemId)
{
  if (NCore::ServerNode* const serverNode = ServerNode())
  {
    if (Peered::IGameServer* const server = serverNode->GameServer())
    {
      server->DispatchBadBehaviourComplaint(serverNode->GetClientIndex(), userId, reportItemId);
    }
  }
}



void GameClientPW::OnProtectionError()
{
  if (NCore::ServerNode* const serverNode = ServerNode())
  {
    if (Peered::IGameServer* const server = serverNode->GameServer())
    {
      server->OnProtectionError(serverNode->GetClientIndex());
    }
  }
}



void GameClientPW::UpdatePerPlayerProgress()
{
  if ( ServerNode()->IsReconnecting())
   for ( TUsersLoadingStatus::const_iterator it = UsersLoadingProgress().begin(); it != UsersLoadingProgress().end(); ++it )
   {
    if (it->first!=Client()->ClientId())
      it->second = 100;
   }


  if ( loadingScreeen )
    for ( TUsersLoadingStatus::const_iterator it = UsersLoadingProgress().begin(); it != UsersLoadingProgress().end(); ++it )
      loadingScreeen->SetPlayerProgress( it->first, it->second / 100.0f );
}

void GameClientPW::ProcessSpectatorJoin()
{
  if (!advScreeen)
    return;

  if (NCore::ServerNode* serverNode = ServerNode())
  {
    if (!serverNode->DidSpectatorJoin())
      return;

    const Peered::SpectatorInfo& spectatorInfo = serverNode->GetJoinedSpectatorInfo();

    advScreeen->OnSpectatorJoin(spectatorInfo.nickname);

    if (ClientId() == spectatorInfo.clientId)
      advScreeen->StartSpectate(SPECTATE_PLAYER1_IDX);

    serverNode->DropJoinedSpectatorRecord();
  }
}

void GameClientPW::ProcessPlaySameTeamDecisions()
{
  if (!advScreeen)
    return;

  if (NCore::ServerNode* const serverNode = ServerNode())
  {
    NCore::PlaySameTeamDecision decision;

    while (serverNode->PopPlaySameTeamDecision(decision))
    {
      advScreeen->HandlePlaySameTeamDecision(advScreeen->GetWorld()->GetPlayerByUID(decision.clientId), decision.agreed);
    }
  }
}

void GameClientPW::ProcessBadBehaviourComplaints()
{
  struct Local
  {
    static void ProcessComplaint(NWorld::PFWorld* const world, const NCore::BadBehaviourComplaint& complaint)
    {
      const NWorld::PFPlayer* const sender = world->GetPlayerByUID(complaint.senderClientId);
      const NWorld::PFPlayer* const receiver = world->GetPlayerByUID(complaint.reportedClientId);

      if (!sender)
      {
        DevTrace("ProcessBadBehaviourComplaints: player not found (sender uid=%d)", complaint.senderClientId);
        return;
      }

      if (!receiver)
      {
        DevTrace("ProcessBadBehaviourComplaints: player not found (reported uid=%d)", complaint.reportedClientId);
        return;
      }

      // NOTE: такое не может случиться при нормальных условиях
      if (sender == receiver)
      {
        ErrorTrace("ProcessBadBehaviourComplaints: reported self (uid=%d)", complaint.senderClientId);
        return;
      }

      if (sender->GetTeamID() != receiver->GetTeamID())
      {
        DevTrace("ProcessBadBehaviourComplaints: reported enemy (sender uid=%d, reported uid=%d)", complaint.senderClientId, complaint.reportedClientId);
        return;
      }
      if (complaint.reportItemId == BAD_BEHAVIOUR_REPORT_ITEM_ID)
        PlayerBehaviourTracking::DispatchEvent(receiver, EPlayerBehaviourEvent::GotBadBehaviourComplaint);
      else if(complaint.reportItemId == INSULT_REPORT_ITEM_ID) 
        PlayerBehaviourTracking::DispatchEvent(receiver, EPlayerBehaviourEvent::GotToxicPlayerComplaint);
    }
  };

  if (!advScreeen)
    return;

  NWorld::PFWorld* const world = advScreeen->GetWorld();

  if (!world)
    return;

  if (NCore::ServerNode* const serverNode = ServerNode())
  {
    NCore::BadBehaviourComplaint complaint;

    while (serverNode->PopBadBehaviourComplaint(complaint))
    {
      Local::ProcessComplaint(world, complaint);
    }
  }
}

void GameClientPW::StopAsyncMapLoadingJob()
{
  if (loadingThread)
  {
    loadingThread->AsyncStop();
    loadingThread->Wait(30000);
  }
}

} //namespace lobby

NI_DEFINE_REFCOUNT( lobby::GameClientPW );
NI_DEFINE_REFCOUNT( lobby::FastReconnectCtxPW );
