#include "stdafx.h"

#include "LobbyGameClient.h"

#include "Core/WorldBase.h"
#include "Core/Transceiver.h"
#include "Core/RemoteCommandScheduler.h"
#include "Core/CoreFSM.h"

#include "Server/RPC/LocalEntityFactory.h"
#include "System/CrashRptWrapper.h"
#include "System/MainFrame.h"

#include "Server/LobbyPvx/RLobbyIServerInstance.auto.h"
#include "Client/LobbyPvx/HybridServerNodeImpl.h"
#include "Client/LobbyPvx/RLobbyClientInterface.auto.h"
#include "HybridServer/RPeered.auto.h"
#include "HybridServer/LPeered.auto.h"
#include "Network/LoginClientVersion.h"
#include "Version.h"
#include "PF_GameLogic/GameMaps.h"
#include "PF_GameLogic/StringExecutor.h"
#include "PF_GameLogic/DBStats.h"
#include "PF_GameLogic/DBAdvMap.h"
#include "PF_GameLogic/MapDescriptionLoader.h"
#include "UI/FrameTimeRender.h"
#include "System/Lifehacks.h"
#include "System/SafeTextFormatHistogram.h"
#include "FastReconnectCtx.h"
#include "NewReplay.h"


static const float PROGRESS_SEND_INTERVAL = 0.33f;

static float g_fHybridPingPeriod = 5.0; // по умолчанию - будем запрашивать пинг раз в столько секунд
REGISTER_VAR( "hybrid_ping_period", g_fHybridPingPeriod, STORAGE_NONE);

static float g_fHybridPingThreshold = 0.4f; // если пинг (в секундах) больше этого значения, будем ругацца (т.е. ставить флаг warning в DebugVar "hybrid_ping_value")
REGISTER_VAR( "hybrid_ping_threshold", g_fHybridPingThreshold, STORAGE_NONE);

static float g_fHybridPingRequestTimeout = 20.0; // !=0: запрашивать пинг только после завершения предыдущего запроса, или по истечению указ. таймаута после пред. запроса
REGISTER_VAR( "hybrid_ping_timeout", g_fHybridPingRequestTimeout, STORAGE_NONE);

static float g_fUpdatePingStatisticsPeriod = 5.0; // Update ping statistics once in 5 seconds by default
REGISTER_VAR( "update_ping_statistics_period", g_fUpdatePingStatisticsPeriod, STORAGE_NONE);

static float g_fLogPingStatisticsPeriod = 60.0; // Log ping statistics once in 60 seconds by default
REGISTER_VAR( "log_ping_statistics_period", g_fLogPingStatisticsPeriod, STORAGE_NONE);

static bool g_enableReplay = true;
REGISTER_VAR( "enable_replay", g_enableReplay, STORAGE_USER);

#pragma warning( disable : 4996 ) // This function or variable may be unsafe.
class WorldStepIntDebugVar : public NDebug::DebugVar<int>
{
public:
  WorldStepIntDebugVar( const char * _name ) :
  NDebug::DebugVar<int>( _name, "" )
  {}

  void SetValue( int _value, int _worldStep, bool _warning )
  {
    worldStep = _worldStep;
    NDebug::DebugVar<int>::SetValue( _value, _warning );
  }

  virtual int FormatValue( wchar_t *pBuffer, const int bufferLen ) const {
    const wchar_t * str = NStr::StrFmtW( L"%d: %d", GetValue(), worldStep );
    if ( wcslen( str ) < (size_t)bufferLen )
      wcscpy( pBuffer, str );
    else
      pBuffer[0] = 0;
    return wcslen( pBuffer );
  }

  int GetWorldStep() const { return worldStep; }

private:
  int  worldStep;
};


static WorldStepIntDebugVar g_fHybridPingValue( "hybrid_ping_value" ); // сюда складываем последнее полученное значение ping


namespace lobby
{

class LoadingStatusMessage : public CObjectBase
{
  OBJECT_METHODS( 0xC5844381, LoadingStatusMessage );
public:
  ZDATA
  int userId;
  int loadingStatus;
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&userId); f.Add(3,&loadingStatus); return 0; }

  LoadingStatusMessage() {}
  LoadingStatusMessage( int uid, int status ) : userId( uid ), loadingStatus( status ) {}
};

} //namespace lobby

REGISTER_SAVELOAD_CLASS_NM( LoadingStatusMessage, lobby );
NI_DEFINE_REFCOUNT( lobby::GameClient );
NI_DEFINE_REFCOUNT( lobby::FastReconnectCtx );

namespace lobby
{

GameClient::GameClient( ClientBase * _client, NWorld::IMapCollection * _mapCollection, FastReconnectCtx * _fastReconnectCtx, const bool _isSpectator, const bool _isTutorial ) :
gameState( EGameState::Startup ),
client( _client ),
clientId( _client->ClientId() ),
hybridStarted( false ),
mapCollection( _mapCollection ),
currentMapLoadProgress( 0 ), nextMapLoadProgressTime( 0 ),
framesSkipped( 0 ),
timeToSkip( 0 ),
timeLastPingRequest( 0 ),
timeLastUnansweredPing( 0 ),
lastStep(0),
openedFileCount(-1),
noDataStats(0, true),
noDataStep(-1),
lastDebugStep( 0 ),
nextChannelDbgInfo( 0 ),
lastPollTime( timer::Now() ),
nextFrameTimeDump( timer::Now() + 10.0 ),
frameTimeHistogram( lifehack::EasyVector<double>( 0.0, 2.0, 10.0, 20.0, 30.0, 40.0, 50.0 ) ),
fastReconnectCtx( _fastReconnectCtx ),
isSpectator( _isSpectator ),
isTutorial( _isTutorial )
{
  CrashRptWrapper::AddTagToReport( "UserId", NStr::StrFmt( "%d", clientId ) );

  EnterGameServer();

  g_fHybridPingValue.SetValue( -1, 0, false );

  int pingWaterline = int(g_fHybridPingThreshold * 1e3);
  pingStatistics.SetWaterline( StatisticService::RPC::GameServerRPCPingTime, pingWaterline );
  pingStatistics.SetWaterline( StatisticService::RPC::GameServerTransportPingTime, pingWaterline );
  pingStatistics.SetWaterline( StatisticService::RPC::LobbyServerTransportPingTime, pingWaterline );
}



void GameClient::EnterGameServer()
{
  const TGameLineUp & players = client->GameLineup();

  for ( int i = 0; i < players.size(); ++i )
  {
    const lobby::SGameMember & memb = players[i];
    if( memb.context.playerType == lobby::EPlayerType::Computer )
      continue;

    if ( memb.user.userId == clientId )
    {
      nickname = memb.user.nickname;

      CrashRptWrapper::AddTagToReport( "Nickname", NStr::ToMBCS( memb.user.nickname ).c_str() );
      CrashRptWrapper::AddTagToReport( "HeroId", memb.context.hero.c_str() );
      CrashRptWrapper::AddTagToReport( "TeamId", NStr::StrFmt( "%d", memb.context.team ) );
    }
    
  }


  for ( int i = 0; i < players.size(); ++i )
    loadingProgress[players[i].user.userId] = ( players[i].context.playerType == lobby::EPlayerType::Human ) ? 0 : 100;

  if ( IsSpectator() )
  {
    nickname = L"spec";
    for ( int i = 0; i < players.size(); ++i )
    {
      const lobby::SGameMember & memb = players[i];
      if( memb.context.playerType == lobby::EPlayerType::Computer )
        continue;
      nickname = memb.user.nickname;
      break;
    }
  }

  if ( !IsTutorial() )
  {
    NI_ASSERT( !nickname.empty(), "" );
  }

  client->RpcFactory()->RegisterAttach<Peered::IGameClient, Peered::LIGameClient>();
  client->RpcFactory()->RegisterAttach<Peered::IGameClientReconnect, Peered::LIGameClientReconnect>();

  if ( fastReconnectCtx && fastReconnectCtx->ServerNode() && fastReconnectCtx->Transceiver() )
  {
    MessageTrace( "Adding client fast to game server..." );
    hybridServerNode = fastReconnectCtx->ServerNode();
    int fromStep = max( fastReconnectCtx->Transceiver()->GetNextStep() + 1, hybridServerNode->GetStartedStep() );
    hybridServerNode->Reinit( client->GameServer(), fromStep - 1 );
    client->GameServer()->AddClientFast( clientId, hybridServerNode->GetClientIndex(), hybridServerNode, fromStep );
  }
  else
  {
    MessageTrace( "Adding client to game server..." );
    hybridServerNode = new NCore::ServerNode( client->GameServer() );
    //FIXME: send nickname as wide string
    Login::ClientVersion clientVersion(VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH, VERSION_REVISION);
    client->GameServer()->AddClient( NStr::ToMBCS( nickname ).c_str(), clientId, clientVersion, hybridServerNode );
  }

  DebugTrace( "Client %d : GameClient created", clientId );
}



void GameClient::ProcessAsyncMessage( IObjectBase *pMsg )
{
  CDynamicCast<LoadingStatusMessage> pStatusMsg( pMsg );
  if ( !pStatusMsg )
    return;

  loadingProgress[pStatusMsg->userId] = pStatusMsg->loadingStatus;
}



void GameClient::OnCombatScreenStarted( NCore::IWorldBase * world, const NGameX::ReplayInfo & _replayInfo )
{
  NI_ASSERT( gameState == EGameState::StartingGame, "" );

  transceiver->SetWorld( world );
  transceiver->RecordMapStart( mapStartInfo );

  StartMapLoading( world );

  hybridServerNode->OnCombatScreenStarted( _replayInfo );

  gameState = EGameState::LoadingMap;
  DebugTrace( "GameClient.LoadingMap" );
}



void GameClient::SetMapLoadingProgress( int progress )
{
  NI_ASSERT( gameState == EGameState::LoadingMap, "" );
  currentMapLoadProgress = progress;
}



void GameClient::OnMapLoaded()
{
  NI_ASSERT( gameState == EGameState::LoadingMap, "" );

  gameState = EGameState::MapLoadCooldown;
  timeToSkip = 3.0;
  MessageTrace( "GameClient.MapLoadCooldown, clientId is %d", clientId );

  MessageTrace( "SENDING our (%d) progress: 100", clientId );

  scheduler->SendMessage( new LoadingStatusMessage( clientId, 100 ), false );
}
 


void GameClient::OnVictory( const StatisticService::RPC::SessionClientResults & _sessionResults, const NGameX::ReplayInfo & _replayInfo )
{
  gameState = EGameState::Finished;

  SendTeam();
  
  hybridServerNode->GameFinished( _sessionResults, _replayInfo, transceiver->GetNextStep() );

  if ( NGlobal::GetVar( "exit_on_finish", 0 ).GetFloat() != 0 )
    NMainFrame::Exit();
}

void GameClient::SetTimeScale( float timescale )
{
    if ( hybridServerNode )
      hybridServerNode->OnTimeScaleChanged( timescale );
}

bool GameClient::IsThisGameServerNode( rpc::INode * node )
{
  if ( hybridServerNode )
    if ( hybridServerNode->GameServer() )
    {
      rpc::INode * gsNode = hybridServerNode->GameServer()->GetHandler()->GetNode( 0 );
      if ( gsNode == node )
        return true;
    }
  return false;
}



void GameClient::PrepareMap()
{
  NI_VERIFY( mapCollection, "No map loader given", return );

  if ( fastReconnectCtx && fastReconnectCtx->Map() )
    mapLoader = fastReconnectCtx->Map();
  else
  {
    mapLoader = mapCollection->CreateMapLoader( client->GameParams().mapId.c_str() );
    NI_VERIFY( mapLoader, NStr::StrFmt( "Could not find map '%s'", client->GameParams().mapId.c_str() ), return );
  }

  mapLoader->FillMapStartInfo( mapStartInfo, client->GameLineup(), client->GameParams() );

  mapDescription = new NWorld::MapDescriptionLoader(mapStartInfo.mapDescName);
}




void GameClient::PrepareReplayWriter()
{
  if (!g_enableReplay)
    return;

  switch (MapDescription()->Description->mapType)
  {
  case NDb::MAPTYPE_TUTORIAL:
    return;
  }

  if (!fastReconnectCtx)
  {
    const Login::ClientVersion ver(VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH, VERSION_REVISION);

    replayWriter = new NCore::ReplayWriter();
    replayWriter->WriteVersion(ver);
  }
  else
  {
    replayWriter = fastReconnectCtx->ReplayWriter();
  }

  if (!fastReconnectCtx || !fastReconnectCtx->ServerNode() || !fastReconnectCtx->Transceiver())
  {
    hybridServerNode->SetReplayWriter(replayWriter);
  }
}



void GameClient::StartingGame()
{
  NI_VERIFY(mapDescription && mapDescription->IsSuccessfullyLoaded, "Map description isn't loaded", return; );

  if (!mapDescription->IsStatisticsEnabled())
  {
    MessageTrace( "Statistics disabled by map settings" );
    gameStatistics = 0;
  }

  if (replayWriter)
  {
    if (!fastReconnectCtx)
      replayWriter->WriteLobbyData(clientId, client->GameLineup(), client->GameParams());
  }
}



int GameClient::Poll( float transceiverDeltaTime )
{
  switch( gameState )
  {
    case EGameState::Startup:
      if ( client->Status() == EClientStatus::InGameSession )
      {
        gameState = EGameState::Connecting;
        PrepareMap();
        PrepareReplayWriter();
        StartingGame();
      }
      break;

    case EGameState::Connecting:
      if ( hybridServerNode && hybridServerNode->IsStarted())
      {
        StartGame();
      }
      break;

    case EGameState::StartingGame:
      break;

    case EGameState::LoadingMap:
    {
      scheduler->Step( transceiverDeltaTime );
      SendMyProgressIfNeeded();
      break;
    }

    case EGameState::MapLoadCooldown:
      scheduler->Step( transceiverDeltaTime );
      timeToSkip -= transceiverDeltaTime;
      if ( timeToSkip <= 0 )
        gameState = EGameState::WaitingOtherClients;
      break;

    case EGameState::WaitingOtherClients:
    {
      scheduler->Step( transceiverDeltaTime );

      SendMyProgressIfNeeded();

      //FIXME: здесь мы делаем предположение, что время загрузки карты является достаточным
      //для установки соединения с гибридным сервером. Впрочем, при ложном срабатывании
      //игра продолжит функционировать, просто появится окно об отвалившемся сервере

      if ( !hybridStarted && hybridServerNode->IsStarted() )
      {
        hybridStarted = true;
        hybridServerNode->ClientReady();
        DebugTrace( "GameClient.ClientReady" );
      }

      if ( hybridServerNode->GetStartedStep() >= 0 )
        RunSession();
      break;
    }

    case EGameState::Running:
      // Hide screen at the first step
      HideLoadingScreen();

      scheduler->Step( transceiverDeltaTime );

      StartStepStatistics(transceiver->GetNextStep());
      transceiver->Step( transceiverDeltaTime * 1e3f );
      StopStepStatistics(transceiver->GetNextStep());
      UpdateNoDataStatistics(transceiver->GetNextStep(), transceiver->GetNoData());
      UpdatePingStatistics();
  
      // раз в указанное кол-во секунд запрашиваем пинг (transit_time rpc-запроса до гибрид-сервера и обратно)
      RequestHybridPing();

      if ( hybridServerNode->GracefullDisconnectReason() != Peered::EDisconnectReason::None )
      {
        DebugTrace( "Switch to EGameState::Finished by %d", (int)hybridServerNode->GracefullDisconnectReason() );
        gameState = EGameState::Finished;
      }

      break;
    case EGameState::Finished:
      break;
  }

  DisplayDebugInfo();

  if ( scheduler && transceiver )
  {
    const int stepScheduler = scheduler->GetNextStep(false), stepTransceiver = transceiver->GetNextStep();
    NDebug::SetSteps(stepScheduler, stepTransceiver, transceiverDeltaTime, transceiver->GetBufferLimit());
    return stepTransceiver - stepScheduler;
  }

  return -1;
}



void GameClient::RunSession()
{
  NI_ASSERT( hybridStarted, "" );

  gameState = EGameState::Running;
  DebugTrace( "GameClient.Running" );
}



void GameClient::StartGame()
{
  DebugTrace( "Starting game for %d players on map '%s' (client)...", client->GameLineup().size(), client->GameParams().mapId.c_str() );

  NI_ASSERT( hybridServerNode, "Scheduling server not present" );

  if ( fastReconnectCtx )
  {
    scheduler = fastReconnectCtx->Scheduler();
    scheduler->Reinit( hybridServerNode, this );

    transceiver = fastReconnectCtx->Transceiver();
    transceiver->Reinit( scheduler );
  }
  else
  {
    scheduler = new NCore::RemoteCommandScheduler( hybridServerNode, this, clientId, isSpectator );
    transceiver = new NCore::Transceiver( scheduler, hybridServerNode->GetSimulationStep(), false );
    stats.Init(NHPTimer::Milliseconds2Time(hybridServerNode->GetSimulationStep()), true);
  }

  //Let's fill talent infos if any
  bool assertIfNoInfo = (client->GameParams().gameType == EGameType::SocialMMaking);
  mapLoader->FillPlayersInfo( mapStartInfo, hybridServerNode->GetClientInfos(), assertIfNoInfo );

  OnPlayerInfoLoaded();

  if (gameStatistics)
  {
    gameStatistics->SetSessionId( client->GameSessionId() );
    gameStatistics->SetUserId( clientId );
    gameStatistics->SetTimeDelta( client->GetTimeDelta() );

    if (hybridServerNode)
      hybridServerNode->SetGameStatistics(gameStatistics);
  }

  CreateAdventureScreen();

  if ( fastReconnectCtx )
  {
    hybridStarted = true;
    RunSession();
  }
  else
  {
    gameState = EGameState::StartingGame;
    DebugTrace( "GameClient.StartingGame" );

    NotifyChatMuted();
  }
}


bool GameClient::PopClientStatusChange( wstring & nickname, Peered::BriefClientInfo & info )
{
  if ( !hybridServerNode )
    return false;

  Peered::BriefClientInfo infoFromHS;
  if ( !hybridServerNode->PopClientStatusChange( infoFromHS ) )
    return false;

  const TGameLineUp & players = client->GameLineup();
  for ( int i = 0; i < players.size(); ++i )
    if ( players[i].user.userId == (int)infoFromHS.clientId )
    {
      nickname = players[i].user.nickname;
      info = infoFromHS;
      return true;
    }

  return false;
}


Transport::Ping GameClient::GetHybridServerTransportPing()
{
  Transport::Ping ping = -1;

  if ( hybridServerNode )
  {
    ping = hybridServerNode->GetPingTime();
  }

  return ping;
}


Transport::Ping GameClient::GetLobbyServerTransportPing()
{
  Transport::Ping ping = -1;

  StrongMT<Transport::IChannel> locked = lobbyServerChannel.Lock();
  if ( !locked )
  {
    if ( client && client->LobbyServer() )
    {
      if ( rpc::EntityHandler * pHandler = client->LobbyServer()->GetHandler() )
      {
        if ( rpc::INode * pNode = pHandler->GetNode(0) )
        {
          lobbyServerChannel = pNode->GetConnectedPipe()->GetPipeChannel();
          locked = lobbyServerChannel.Lock();
        }
      }
    }
  }

  if ( locked )
  {
    ping = locked->GetPingTime();
  }

  return ping;
}

bool GameClient::IsFastReconnectEnabled() const 
{
  if (hybridServerNode)
  {
    return hybridServerNode->IsFastReconnectEnabled();
  }

  return false;
}


void GameClient::OnMulticastData(const vector<byte> & data)
{
  rpc::MemoryBlock mcData((void*)&data[0], data.size());
  hybridServerNode->StepMc(mcData);
}


void GameClient::UpdateNoDataStatistics(int step, bool noData)
{
  if (noData)
  {
    if (!noDataStats.IsStarted())
    {
      noDataStats.Start();
      if (noDataStep == -1)
        noDataStep = step;
    }
  }
  else
  {
    if (noDataStats.IsStarted())
    {
      /*NHPTimer::STime noDataTime =*/ noDataStats.Stop();
      //DebugTrace("NODATA: %d", NHPTimer::Time2Milliseconds(noDataTime));
    }

    if (noDataStats.GetCount() > 0 && noDataStats.GetTimeStamp() - noDataStats.GetFirstStartTimeStamp() >= 60)
    {
      const AppFramework::InstanceStatistics::ValueAccumulator& info = noDataStats.Finish();

      time_t startTimeStamp = noDataStats.GetFirstStartTimeStamp();
      time_t endTimeStamp = noDataStats.GetFinishTimeStamp();

      struct tm startTime;
      struct tm endTime;
      localtime_s(&startTime, &startTimeStamp);
      localtime_s(&endTime, &endTimeStamp);

      int avgValueTimeMs = NHPTimer::Time2Milliseconds(info.averageValue);
      int minValueTimeMs = NHPTimer::Time2Milliseconds(info.minValue);
      int maxValueTimeMs = NHPTimer::Time2Milliseconds(info.maxValue);

      int rpcPing = g_fHybridPingValue.GetValue();
      int transportPing = GetHybridServerTransportPing().value;

      DebugTrace( "GameClient: No data detected: min:%d average:%d max:%d count:%d", 
          minValueTimeMs, avgValueTimeMs, maxValueTimeMs, noDataStats.GetCount() );
      DebugTrace( "GameClient: No data detected: start:%02d:%02d:%02d end:%02d:%02d:%02d step:%d", 
          startTime.tm_hour, startTime.tm_min, startTime.tm_sec, 
          endTime.tm_hour, endTime.tm_min, endTime.tm_sec, step);
      DebugTrace( "GameClient: No data detected: RPC ping:%d transport ping:%d", rpcPing, transportPing );


      if (gameStatistics && gameStatistics->IsDebugStatisticsAvailable())
      {
        StatisticService::RPC::ExceedingStepTimeInfo info;

        info.typeId       = StatisticService::RPC::NoDataTime;
        info.startStep    = noDataStep;
        info.finishStep   = step;
        info.startTime    = startTimeStamp;
        info.finishTime   = endTimeStamp;
        info.stepCount    = noDataStats.GetCount();
        info.stepTimeMin  = minValueTimeMs;
        info.stepTimeAvg  = avgValueTimeMs;
        info.stepTimeMax  = maxValueTimeMs;
        info.rpcPing      = rpcPing;
        info.transportPing = transportPing;

        gameStatistics->LogExceedingStepTime(info);

        gameStatistics->SetLogNextPingTime(true);
      }

      noDataStats.Reset();
      noDataStep = -1;
    }
  }
}

void GameClient::UpdatePingStatistics()
{
  if( g_fUpdatePingStatisticsPeriod > 0 )
  {
    time_t currentTime = time(0);
    
    if (currentTime - pingStatistics.lastPingTime >= g_fUpdatePingStatisticsPeriod)
    {
      if (!pingStatistics.IsStarted())
        pingStatistics.Start(currentTime);

      Transport::Ping hybridServerTransportPing = GetHybridServerTransportPing();
      Transport::Ping lobbyServerTransportPing = GetLobbyServerTransportPing();
      pingStatistics.AddPingValue( StatisticService::RPC::GameServerRPCPingTime, g_fHybridPingValue.GetValue(), g_fHybridPingValue.GetWorldStep() );
      pingStatistics.AddPingValue( StatisticService::RPC::GameServerTransportPingTime, hybridServerTransportPing.value, hybridServerTransportPing.count );
      pingStatistics.AddPingValue( StatisticService::RPC::LobbyServerTransportPingTime, lobbyServerTransportPing.value, lobbyServerTransportPing.count );

      pingStatistics.Step(currentTime);

      if (currentTime - pingStatistics.firstPingTime >= g_fLogPingStatisticsPeriod)
      {
        if (pingStatistics.HasHighPing() || gameStatistics && gameStatistics->GetLogNextPingTime())
        {
          StatisticService::RPC::ExceedingPingTimeInfo rpcPing;
          pingStatistics.GetPingStatistics(StatisticService::RPC::GameServerRPCPingTime, rpcPing);

          struct tm startTime;
          struct tm endTime;
          localtime_s(&startTime, &rpcPing.startTime);
          localtime_s(&endTime, &rpcPing.finishTime);
          DebugTrace( "GameClient: Ping statistics: start:%02d:%02d:%02d, end:%02d:%02d:%02d",
            startTime.tm_hour, startTime.tm_min, startTime.tm_sec, endTime.tm_hour, endTime.tm_min, endTime.tm_sec );

          DebugTrace( "GameClient: Long ping (RPC): samples:%d, min:%d, max:%d, avg:%d",
            rpcPing.pingHCount, rpcPing.pingHTimeMin, rpcPing.pingHTimeMax, rpcPing.pingHTimeAvg );
          DebugTrace( "GameClient: Norm ping (RPC): samples:%d, min:%d, max:%d, avg:%d",
            rpcPing.pingLCount, rpcPing.pingLTimeMin, rpcPing.pingLTimeMax, rpcPing.pingLTimeAvg );

          StatisticService::RPC::ExceedingPingTimeInfo transportPing;
          pingStatistics.GetPingStatistics(StatisticService::RPC::GameServerTransportPingTime, transportPing);

          DebugTrace( "GameClient: Long ping (TGS): samples:%d, min:%d, max:%d, avg:%d",
            transportPing.pingHCount, transportPing.pingHTimeMin, transportPing.pingHTimeMax, transportPing.pingHTimeAvg );
          DebugTrace( "GameClient: Norm ping (TGS): samples:%d, min:%d, max:%d, avg:%d",
            transportPing.pingLCount, transportPing.pingLTimeMin, transportPing.pingLTimeMax, transportPing.pingLTimeAvg );

          StatisticService::RPC::ExceedingPingTimeInfo transportPingLobby;
          pingStatistics.GetPingStatistics(StatisticService::RPC::LobbyServerTransportPingTime, transportPingLobby);

          DebugTrace( "GameClient: Long ping (TLS): samples:%d, min:%d, max:%d, avg:%d",
            transportPingLobby.pingHCount, transportPingLobby.pingHTimeMin, transportPingLobby.pingHTimeMax, transportPingLobby.pingHTimeAvg );
          DebugTrace( "GameClient: Norm ping (TLS): samples:%d, min:%d, max:%d, avg:%d",
            transportPingLobby.pingLCount, transportPingLobby.pingLTimeMin, transportPingLobby.pingLTimeMax, transportPingLobby.pingLTimeAvg );

          if (gameStatistics) 
          {
            gameStatistics->LogExceedingPingTime(rpcPing);
            gameStatistics->LogExceedingPingTime(transportPing);
            gameStatistics->LogExceedingPingTime(transportPingLobby);
          }
        }
        pingStatistics.Reset();
      }
    }
  }
}


void GameClient::OnHybridPing( Peered::SHybridPongResult& time_step, int context, rpc::CallStatus status )
{
  if (rpc::CallSuccessful == status)
  {
    NHPTimer::FTime now = NHPTimer::GetScalarTime();
    float ping = now - time_step.pingTime;

    int iping = (int)( 1e3 * ping );
    bool warn = ( ping > g_fHybridPingThreshold );
    g_fHybridPingValue.SetValue( iping, time_step.worldStep, warn );
    debugDisplay::AddGraph( "gping", debugDisplay::Align( -1, -1 ), iping, debugDisplay::GraphInfo( 32, 100, debugDisplay::Color::Green, warn ? debugDisplay::Color::Red : debugDisplay::Color::Green, true ) );

    if ( NGlobal::GetVar( "show_info_graph" ).GetInt64() )
      debugDisplay::SetNewGraphInfo( "gping", debugDisplay::GraphInfo( 32, 100, debugDisplay::Color::Green, warn ? debugDisplay::Color::Red : debugDisplay::Color::Green, true ) );
    else
      debugDisplay::SetNewGraphInfo( "gping", debugDisplay::GraphInfo( 32, 100, debugDisplay::Color::Green, warn ? debugDisplay::Color::Red : debugDisplay::Color::Green, false ) );

    timeLastUnansweredPing = 0; // на пред.запрос ответили, можно начинать следующий запрос
    //DebugTrace("OnHybridPing: prev %0.4f, now %0.4f, ping=%0.4f, step=%d, isWarning=%d", time_step.pingTime, now, ping, time_step.worldStep, (ping > g_fHybridPingThreshold) );
  }
}



void GameClient::RequestHybridPing()
{
  if( g_fHybridPingPeriod > 0 )
  {// раз в указанное кол-во секунд запрашиваем пинг (transit_time rpc-запроса до гибрид-сервера и обратно)
    NHPTimer::FTime tm = NHPTimer::GetScalarTime();
    if ( ( tm - timeLastPingRequest > g_fHybridPingPeriod )
         && (timeLastUnansweredPing == 0 || tm - timeLastUnansweredPing > g_fHybridPingRequestTimeout) ) // UnansweredPing сбрасывается в 0, когда получаем ответ
    {
      if ( client->GameServer() )
      {
        timeLastUnansweredPing = tm;
        int worldStep = transceiver ? transceiver->GetWorldStep() : 0;
        Peered::SHybridPongResult time_step;
        time_step.pingTime = tm;
        time_step.worldStep = worldStep ;

        client->GameServer()->Ping( time_step, this, &GameClient::OnHybridPing, 0 );
      }
      timeLastPingRequest = tm;
    }
  }
}

void GameClient::SendMyProgressIfNeeded()
{
  if ( client->Now() > nextMapLoadProgressTime )
  {
    scheduler->SendMessage( new LoadingStatusMessage( clientId, currentMapLoadProgress ), false );
    nextMapLoadProgressTime = client->Now() + PROGRESS_SEND_INTERVAL;
  }
}

void GameClient::StartStepStatistics(int step)
{
  lastStep = step;
  stats.Start();

  if (openedFileCount == -1)
  {
    openedFileCount = RootFileSystem::GetOpenedFileCount();
  }
}

void GameClient::StopStepStatistics(int step)
{
  if (!stats.IsStarted())
    return;

  if (step == lastStep)
  {
    stats.Discard();  // Discard, if not stepped
    return;
  }

  stats.Stop();

  if (stats.GetCount() == 50)
  {
    const AppFramework::InstanceStatistics::ValueAccumulator& info = stats.Finish();
    int maxValueTimeMs = NHPTimer::Time2Milliseconds(info.maxValue);

    int newOpenedFileCount = RootFileSystem::GetOpenedFileCount() - openedFileCount;
    openedFileCount += newOpenedFileCount;

    if (maxValueTimeMs > hybridServerNode->GetSimulationStep())
    {
      time_t startTimeStamp = stats.GetFirstStartTimeStamp();
      time_t endTimeStamp = stats.GetFinishTimeStamp();

      struct tm startTime;
      struct tm endTime;
      localtime_s(&startTime, &startTimeStamp);
      localtime_s(&endTime, &endTimeStamp);

      int minValueTimeMs = NHPTimer::Time2Milliseconds(info.minValue);
      int avgValueTimeMs = NHPTimer::Time2Milliseconds(info.averageValue);

      DebugTrace( "GameClient: Lags detected: min:%d average:%d max:%d count:%d", 
          minValueTimeMs, avgValueTimeMs, maxValueTimeMs, stats.GetLongTimeCount() );
      DebugTrace( "GameClient: Lags detected: start:%02d:%02d:%02d end:%02d:%02d:%02d step:%d fopens:%d", 
          startTime.tm_hour, startTime.tm_min, startTime.tm_sec, 
          endTime.tm_hour, endTime.tm_min, endTime.tm_sec, step, newOpenedFileCount);

      if (gameStatistics && gameStatistics->IsDebugStatisticsAvailable())
      {
        StatisticService::RPC::ExceedingStepTimeInfo info;

        info.typeId       = StatisticService::RPC::LogicStepTime | ((newOpenedFileCount > 0)?(StatisticService::RPC::OpenedFileFlag):(0));
        info.startStep    = step - 50;
        info.finishStep   = step;
        info.startTime    = startTimeStamp;
        info.finishTime   = endTimeStamp;
        info.stepCount    = stats.GetLongTimeCount();
        info.stepTimeMin  = minValueTimeMs;
        info.stepTimeAvg  = avgValueTimeMs;
        info.stepTimeMax  = maxValueTimeMs;
        info.rpcPing      = 0;  // Pings aren't interesting in logics lag
        info.transportPing = 0;

        gameStatistics->LogExceedingStepTime(info);
      }
    }

    stats.Reset();
  }
}

void GameClient::SetLastWorldRequestStep(int _lastWorldRequestStep)
{
  if (gameStatistics)
  {
    gameStatistics->SetLastWorldRequestStep(_lastWorldRequestStep);
  }
}


void GameClient::DisplayDebugInfo()
{
  if ( !transceiver )
    return;

  bool needDrawInfo = NGlobal::GetVar( "show_info_graph" ).GetInt64() != 0;

  timer::Time now = timer::Now();

  {
    const timer::Time dt = now - lastPollTime;
    lastPollTime = now;

    const double instantFrameRate = ( dt > 1e-3 ) ? ( 1.0 / dt ) : 1000.0;
    frameTimeHistogram.AddData( instantFrameRate );
  }

  if ( now > nextFrameTimeDump )
  {
    nextFrameTimeDump = now + 10.0;
    if ( frameTimeHistogram.GetTotal().minValue < 20.0 )
      MessageTrace( "Frame time histo: %.1f", frameTimeHistogram );
    frameTimeHistogram.ResetData();
  }

  if ( now > nextChannelDbgInfo )
  {
    nextChannelDbgInfo = now + 1.0;
    if ( StrongMT<Transport::IChannel> chan = hybridServerNode->ServerChannel() )
    {
      string str;
      chan->FillDebugString( str );
      if ( str.c_str() )
      {
        int i = 0;
        for ( const char * s = str.c_str(); ; )
        {
          char buf[256] = "";
          int l = 0;
          if ( sscanf( s, "%256[^\n\r]%n", buf, &l ) != 1 )
            break;
          s += l;
          if ( needDrawInfo )
            debugDisplay::AddText( NI_STRFMT( "gs_chan_info%d", i++ ) , debugDisplay::Align( -1, -1 ), buf );
          else
            debugDisplay::Remove( NI_STRFMT( "gs_chan_info%d", i++ ) );

          if ( sscanf( s, "%256[\n\r]%n", buf, &l ) == 1 )
            s += l;
        }
      }
    }
  }
  
  if ( lastDebugStep != transceiver->GetNextStep() )
  {
    lastDebugStep = transceiver->GetNextStep();

    if ( hybridServerNode )
    {
      Transport::Ping ping = hybridServerNode->GetPingTime();
      debugDisplay::AddGraph( "tping", debugDisplay::Align( -1, -1 ), ping.value );
      if ( NGlobal::GetVar( "show_info_graph" ).GetInt64() )
        debugDisplay::SetNewGraphInfo( "tping", debugDisplay::GraphInfo( 32, 100, true ) );
      else
        debugDisplay::SetNewGraphInfo( "tping", debugDisplay::GraphInfo( 32, 100, false ) );
    }
  }
}

} //namespace lobby
