#include "stdafx.h"

#include "ReplayRunner.h"

#include "Core/CoreFSM.h"
#include "PF_GameLogic/PFAdvMap.h"
#include "PF_GameLogic/MapStartup.h"
#include "PF_Core/IUpdateable.h"
#include "Server/LobbyPvx/CommonTypes.h"
#include "Client/MainTimer.h"
#include "Client/ScreenCommands.h"
#include "System/LoadingProgress.h"
#include "LocalCmdScheduler.h"

#include "PF_GameLogic/StringExecutor.h"
#include "PF_GameLogic/AdventureScreen.h"
#include "PF_Minigames/MinigameSessionInterface.h"
#include "PF_GameLogic/PFWorld.h"
#include "Core/Replay.h"
#include "ReplayTransceiver.h"
#include "PF_GameLogic/MapDescriptionLoader.h"
#include "PF_GameLogic/DBTalent.h"
#include "PF_GameLogic/PFResourcesCollection.h"
#include "PF_GameLogic/ForceCalc.h"

#include "PF_GameLogic/AsyncMapStartup.h"

#include <functional>


bool g_useServerReplay = true;
REGISTER_DEV_VAR( "use_server_replay", g_useServerReplay, STORAGE_NONE );


namespace Game
{
  const float ReplayRunner::rForcedStepTime = 0.025f;

  ReplayRunner::ReplayRunner( const string& _replayFileName, 
                              NWorld::IMapCollection * _mapCollection)
    : LoadingScreen( "", "", true, false )
    , replayFileName( _replayFileName )
    , mapCollection( _mapCollection )
    , rSkipTime(0.0f)
  {
    NGlobal::RegisterContextCmd( "replay_skip_time", this, &ReplayRunner::SkipTime );
  }



  ReplayRunner::~ReplayRunner()
  {
  }

  ReplayRunnerLoader::ReplayRunnerLoader( NWorld::ReplayTransceiver* _transceiver, 
                                          LocalCmdScheduler* _scheduler, 
                                          NCore::MapStartInfo& _mapInfo,
                                          ReplayRunner* runner)
    : state( ReplayRunnerLoader::S_STARTING_SCREEN )
    , mapInfo(_mapInfo)
    , advScreen( 0 )
    , scheduler(_scheduler)
    , replayRunner(runner)
  {
    transceiver = _transceiver;
  }


  bool ReplayRunner::Init( UI::User * uiUser )
  {
    if ( StartReplay() )
    {
      loader->Stop();
    }

    LoadingScreen::Init(uiUser);
   
    return true;
  }



  bool ReplayRunner::StartReplay()
  {
    CObj<NCore::IReplayStorage> pReplay;
    if (g_useServerReplay)
      pReplay = new NWorld::ReplayStorage2( NCore::REPLAY_BUFFER_READ, replayFileName.c_str(), mapCollection, GetLoadingStatusHandler() );
    else
      pReplay = new NCore::ReplayStorage( NCore::REPLAY_BUFFER_READ, replayFileName.c_str() );

    if ( !pReplay->IsOk() )
    {
      // Assert and message to screen are shown inside ReplayStorage2
      return false;
    }

    // Get info from replay
    int stepLength;
    NCore::ClientSettings clientSettings;
    lobby::SGameParameters gameParams;
    int clientId;
    if (!pReplay->GetHeader( &mapInfo, &clientId, &stepLength, &clientSettings, &gameParams ))
      return false;

    mapDescription = new NWorld::MapDescriptionLoader(mapInfo.mapDescName);

    NI_VERIFY(mapDescription, "Invalid map description loader!", return false);
    NI_VERIFY(mapDescription->IsSuccessfullyLoaded, "Map description wasn't loaded!", return false);

    transceiver = new NWorld::ReplayTransceiver( pReplay, stepLength );
    transceiver->SetUseServerReplay(g_useServerReplay);

    mapInfo.replayName = replayFileName;

    int playerId = GetPlayer(clientId);

    loader = new ReplayRunnerLoader( transceiver, new LocalCmdScheduler(playerId), mapInfo, this);
   
    CreateAdvScreeen( playerId, stepLength, clientSettings );

    loader->SetAdventureScreen( advScreeen );

    ApplyClientSettings( clientSettings );

    // Create and initialize loading context
    Strong<Game::LoadingGameContext> loadingGameContext = new Game::LoadingGameContext( mapInfo );
    loadingGameContext->advMapDescription = mapDescription->Description;
    loadingGameContext->advMapSettings = mapDescription->Settings;
    loadingGameContext->userId = clientId;
    loadingGameContext->params = gameParams;

    for ( int i = 0; i < mapInfo.playersInfo.size(); ++i )
    {
      const NCore::PlayerStartInfo& slotInfo = mapInfo.playersInfo[i];
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

      float force = NWorld::Force::CalculateForce(slotInfo.playerInfo, slotInfo.usePlayerInfoTalentSet, resourceCollection, mapDescription->Description);

      info.exp = slotInfo.playerInfo.heroExp;
      info.force = force;
      info.raiting = (int)( slotInfo.playerInfo.heroRating );

      info.isNovice = ( slotInfo.playerInfo.basket == NCore::EBasket::Newbie );
      info.isPremium = slotInfo.playerInfo.hasPremium;
      info.partyId = slotInfo.playerInfo.partyId;

      loadingGameContext->lineup_info[slotInfo.playerID] = info;
    }

    Setup(loadingGameContext);

    return true;
  }



  void ReplayRunner::CreateAdvScreeen(int playerId, int _stepLength, const NCore::ClientSettings & clientSettings)
  {
    struct Local
    {
      static int GetUserIdByPlayerId(const NCore::MapStartInfo& msi, const int playerId)
      {
        NCore::TPlayersStartInfo::const_iterator it = msi.playersInfo.begin();
        NCore::TPlayersStartInfo::const_iterator it_end = msi.playersInfo.end();
        for (; it != it_end; ++it)
        {
          NCore::TPlayersStartInfo::const_reference psi = *it;

          if (psi.playerID == playerId)
            return psi.userID;
        }

        return -1;
      }
    };

    NI_ASSERT(IsValid(loader), "" );

    advScreeen = new NGameX::AdventureScreen;
    advScreeen->SetLobbyCallback( loader );
    advScreeen->Construct( 0, 0, 0, true, false );

    resourceCollection = new NWorld::PFResourcesCollection;
    resourceCollection->CollectTalents();
    resourceCollection->CollectConsumables();

    const NGameX::GSClientSettings gsClientSettings(clientSettings.minigameEnabled, clientSettings.logicParam1,
                                                      false, clientSettings.shareUrl, clientSettings.aiForLeaversEnabled,
                                                      clientSettings.aiForLeaversThreshold);
    advScreeen->ApplyGSClientSettings( gsClientSettings );

    if ( !advScreeen->InitAdventures( mapInfo, transceiver, 0, lobby::EGameType::None, playerId,  resourceCollection, 0, 0, _stepLength ) )
      return;

    NI_VERIFY(mapDescription, "Invalid map description loader!", return);
    NI_VERIFY(mapDescription->IsSuccessfullyLoaded, "Map description wasn't loaded!", return);

    advScreeen->InitPlayerNames(mapInfo, Local::GetUserIdByPlayerId(mapInfo, playerId), mapDescription->Description);

    transceiver->SetAdventureScreenInterface( advScreeen );

    NScreenCommands::PushCommand( NScreenCommands::CreatePushScreenCommand( advScreeen ) );
  }

  int ReplayRunner::GetPlayer(int userId)
  {
    if (userId > 0)
    {
      for (int i = 0; i < mapInfo.playersInfo.size(); ++i)
      {
        if (mapInfo.playersInfo[i].userID == userId)
        {
          return mapInfo.playersInfo[i].playerID;
        }
      }
    }

    return PickAnyPlayer();
  }

  int ReplayRunner::PickAnyPlayer()
  {
    for ( int i = 0; i < mapInfo.playersInfo.size(); i++ )
      if ( mapInfo.playersInfo[i].userID != -1 )
        return mapInfo.playersInfo[i].playerID;

    NI_ALWAYS_ASSERT( "Should be at least one player");
    return -1;
  }

  void ReplayRunner::ForcedStep( float rDt )
  {
    transceiver->Step( rDt * 1000.f );
  }

  void ReplayRunner::RunningState()
  {
    float rTimeFotUpdate = NMainLoop::GetTimeDelta();

    while( rSkipTime > rForcedStepTime )
    {
      ForcedStep( rForcedStepTime );
      rSkipTime -= rForcedStepTime;
    }

    if ( rSkipTime >= 0 )
    {
      transceiver->Step( ( rSkipTime + rTimeFotUpdate ) * 1000.f );
      rSkipTime = 0.0f;
    }
  }

  void ReplayRunner::Step( bool bAppActive )
  {
    if (loader)
    {
      switch( loader->GetState())
      {

      case ReplayRunnerLoader::S_STARTING_SCREEN:
        break;

      case ReplayRunnerLoader::S_RUNNING:
        {
          RunningState();
          break;
        }

      case ReplayRunnerLoader::S_FINISHED:
        break;

      case ReplayRunnerLoader::S_LOADING:
        LoadingScreen::Step(bAppActive);
        break;
      }
    }
    else
    {
      LoadingScreen::Step(bAppActive);
    }
  }

  bool ReplayRunner::SkipTime(const char *name, const vector<wstring> &args)
  {
    const string sSkip  = !args.empty() ? NStr::ToMBCS( args[0] ) : "0";
    rSkipTime += NStr::ToFloat(sSkip);
    return true;
  }

  void ReplayRunner::StopAsyncMapLoadingJob()
  {
    if (loader)
      loader->StopAsyncMapLoadingJob();
  }

  void ReplayRunnerLoader::OnCombatScreenStarted( NCore::IWorldBase * world, const NGameX::ReplayInfo & _replayInfo )
  {
    transceiver->SetWorld( world );

    Strong<NWorld::MapDescriptionLoader> mapDescription = new NWorld::MapDescriptionLoader(mapInfo.mapDescName);

    NI_VERIFY(mapDescription, "Invalid map description loader!", return);
    NI_VERIFY(mapDescription->IsSuccessfullyLoaded, "Map description wasn't loaded!", return);

    mapLoadingJob = new NWorld::MapLoadingJob( world, mapInfo, mapDescription->Description, mapDescription->Settings, mapDescription->Map, false );

    replayRunner->SetProgress( mapLoadingJob->GetProgress() );

    state = S_LOADING;

    using NWorld::MapLoader;

    if (MapLoader::IsThreaded())
    {
      loadingThread = MapLoader::CreateMapLoadingThread(mapLoadingJob);
    }
    else
    {
      mapLoadingJob->DoTheJob();

      LaunchReplay();
    }
  }


  int ReplayRunnerLoader::Poll(float dt)
  {
    switch(state)
    {
    case S_LOADING:
      NI_VERIFY( scheduler, "", break );
      scheduler->Step( dt );

      NI_VERIFY( mapLoadingJob, "", break );
      if ( loadingThread->Wait( 0 ) )
      {
        loadingThread = 0;
        LaunchReplay();
      }
      else
      {
        Sleep( 50 );

        // We don't have OurUserId set. Update non-bots here explicitly.
        float percent = mapLoadingJob->GetProgress()->GetTotalProgress();
        for ( int i = 0; i < mapInfo.playersInfo.size(); ++i )
        {
          const NCore::PlayerStartInfo& slotInfo = mapInfo.playersInfo[i];
          if(slotInfo.userID > 0)
          {
            replayRunner->SetPlayerProgress(slotInfo.userID, Clamp( percent, 0.f, 1.f ));
          }
        }
      }
      break;
    }

    const int stepScheduler = scheduler ? scheduler->GetNextStep( false ) : -1;
    const int stepTransceiver = transceiver ? transceiver->GetNextStep() : -1;
    if(scheduler && transceiver)
      return stepScheduler - stepTransceiver;
    return -1;
  }


  void ReplayRunnerLoader::LaunchReplay()
  {
    NI_ASSERT( IsValid( advScreen ), "" );
    advScreen->OnMapLoaded( mapLoadingJob->MapDescriptionResource(), mapLoadingJob->GetCameraSettings() );
    advScreen->ActivateSessionSoundScene();
    advScreen->OnSessionStart(0);
    advScreen->ShowUIBlock( "EscMenuRunToCastleButton", false );
    scheduler->StartGame();

    state = ReplayRunnerLoader::S_RUNNING;
  }


  void ReplayRunnerLoader::OnVictory( const StatisticService::RPC::SessionClientResults & _playersStatistics, const NGameX::ReplayInfo & _replayInfo )
  {
    state = ReplayRunnerLoader::S_FINISHED;
  }

  void ReplayRunnerLoader::SetTimeScale( float timescale )
  {
    transceiver->SetTimeScale(timescale);
  }

  void ReplayRunnerLoader::LeaveGame()
  {
    NScreenCommands::PushCommand( NScreenCommands::CreatePopScreenCommand( advScreen ) );
    state = ReplayRunnerLoader::S_FINISHED;
  }

  void ReplayRunnerLoader::StopAsyncMapLoadingJob()
  {
    if (loadingThread)
    {
      loadingThread->AsyncStop();
      loadingThread->Wait(30000);
    }
  }

} //namespace Game
