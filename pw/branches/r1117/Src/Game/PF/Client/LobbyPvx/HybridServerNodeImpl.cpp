#include "stdafx.h"
#include "HybridServerNodeImpl.h"

#include <Core/Scheduler.h>
#include <Client/MainTimer.h>
#include "HybridServer/Peered.h"

#include "PW_Client/GameStatistics.h"
#include "Network/Transport.h"
#include "HybridServer/RPeered.auto.h"
#include "System/LogFileName.h"
#include "System/FileSystem/FileSystem.h"
#include "System/FileSystem/FileUtils.h"
#include "System/Lifehacks.h"
#include "System/SafeTextFormatHistogram.h"
#include "Render/smartrenderer.h"
#include "NewReplay.h"


NI_DEFINE_REFCOUNT( NCore::ServerNode );

static NDebug::StringDebugVar clientsLags( "ClientsLags", "" );

namespace NCore
{
bool bLogStepTime = false;
REGISTER_VAR( "gameclient_log_step_time", bLogStepTime, STORAGE_NONE );

int acceptableLagsCount = 20;
REGISTER_VAR( "acceptable_lags_count", acceptableLagsCount, STORAGE_NONE );

#ifndef _SHIPPING

  int g_lagStepTime = 5000; // 5000ms=5s time interval between lags
  REGISTER_DEV_VAR( "lag_step_time", g_lagStepTime, STORAGE_NONE );

  int g_lagTime = 1000;     // 1000ms=1s lag time
  REGISTER_DEV_VAR( "lag_time", g_lagTime, STORAGE_NONE );

  bool g_lagEnabled = 0;    // Just on/off
  REGISTER_DEV_VAR( "lag_enabled", g_lagEnabled, STORAGE_NONE );

  int g_lagRepeat = 0;      // 0 = off, >0 = times to repeat g_lagRepeatTime lag after g_lagTime lag/
                            // Intended for immitation of slow steps arrival after lag.
  REGISTER_DEV_VAR( "lag_repeat", g_lagRepeat, STORAGE_NONE );

  int g_lagRepeatTime = 100; // 100ms=0.1s=1step time for short repetitive lags after long lag
  REGISTER_DEV_VAR( "lag_repeat_time", g_lagRepeatTime, STORAGE_NONE );

  int StepLags()
  {
    // Configurable lag immitation code for debug purposes
    static NHPTimer::STime lastTime = 0;
    static NHPTimer::STime lagTime = 0;
    static int repeatCount = 0;

    if (g_lagEnabled)
    {
      NHPTimer::STime currentTime;
      NHPTimer::GetTime(currentTime);

      if (g_lagRepeat != 0 && repeatCount < g_lagRepeat && lastTime != 0)
      {
        ++repeatCount;
        lagTime = currentTime;
        lastTime = 0;
      }
      else
      {
        if (lagTime == 0)
        {
          if (NHPTimer::Time2Milliseconds(currentTime) - NHPTimer::Time2Milliseconds(lastTime) >= g_lagStepTime)
          {
            repeatCount = 0;
            lastTime = 0;
            lagTime = currentTime;
          }
        }
        else
        {
          if (NHPTimer::Time2Milliseconds(currentTime) - NHPTimer::Time2Milliseconds(lagTime) >= g_lagTime
            || repeatCount && NHPTimer::Time2Milliseconds(currentTime) - NHPTimer::Time2Milliseconds(lagTime) >= g_lagRepeatTime)
          {
            lastTime = currentTime;
            lagTime = 0;
          }
          else
          {
            return true;
          }
        }
      }
    }

    return false;
  }

#endif // #ifndef _SHIPPING


void StreamedBlocks::Copy(const nstl::vector<rpc::MemoryBlock>& blocks)
{
  if (blocks.size() > 0)
  {
    int totalSize = 0;
    for (int i=0;i<blocks.size();++i)
    {
      totalSize += blocks[i].size;
    }
    itemsData.resize(totalSize);
    int offset = 0;
    for (int i=0;i<blocks.size();++i)
    {
      int dataSize = blocks[i].size;
      byte* commandPtr = itemsData.begin()+offset;
      byte* dataPtr = (byte*)blocks[i].memory;
      memcpy_s(commandPtr, dataSize, dataPtr, dataSize);
      FixedMemoryStream* cmd = new FixedMemoryStream(commandPtr, dataSize);
      offset += dataSize;
      items.push_back(cmd);
    }
  }
}


GameClientReconnect::~GameClientReconnect()
{
  for (WorldDataParts::iterator it = worldDataParts.begin(); it != worldDataParts.end(); ++it)
  {
    delete [] it->memory;
  }
  worldDataParts.clear();
}



void GameClientReconnect::ApplyWorldDataInfo(const Peered::WorldDataInfo& _worldDataInfo)
{
  DebugTrace("Reconnect: World data info received (step=%d, parts=%d)", _worldDataInfo.step, _worldDataInfo.partsCount);
  worldDataInfo = _worldDataInfo;
}


void GameClientReconnect::ApplyWorldDataPart(const rpc::MemoryBlock& worldDataPart)
{
  NI_VERIFY( worldDataInfo.partsCount > worldDataParts.size() || worldDataInfo.partsCount == 0, 
    "Reconnect: Unexpected world data part received!", return );

  void * dataPartBuffer = new char[worldDataPart.size];
  memcpy_s(dataPartBuffer, worldDataPart.size, worldDataPart.memory, worldDataPart.size);
  rpc::MemoryBlock & newWorldDataPart = worldDataParts.push_back();
  newWorldDataPart.memory = dataPartBuffer;
  newWorldDataPart.size = worldDataPart.size;
  worldDataSize += worldDataPart.size;
}


bool GameClientReconnect::IsWorldDataReady() const
{
  return (worldDataInfo.partsCount > 0 && worldDataParts.size() == worldDataInfo.partsCount);
}


bool GameClientReconnect::GetWorldData(Stream & worldData, int & segmentStep)
{
  if (IsWorldDataReady())
  {
    worldData.SetSize( worldDataSize );

    for (WorldDataParts::iterator it = worldDataParts.begin(); it != worldDataParts.end(); ++it)
    {
      worldData.Write( it->memory, it->size );
      delete [] it->memory;
    }

    segmentStep = worldDataInfo.step;
    
    worldDataParts.clear(); 
    worldDataInfo.clear();
    worldDataSize = 0;

    return true;
  }

  return false;
}


ServerNode::ServerNode(Peered::IGameServer* _server) :
server(_server),
rpcPing(-1),
transportPing(-1),
clientIndex(-1),
lastStep(INVALID_STEP),
startedStep(INVALID_STEP),
asyncStep(INVALID_STEP),
protectionAsyncStep(INVALID_STEP),
confirmFrequency(1),
protectionMagicConfirmFrequency(2),
snapshotChunkSize(1024),
isReconnecting(false),
snapshotSendPerStep(64000),
crcDataRequestsEnabled(false),
fastReconnectEnabled(false),
simulationStep(DEFAULT_GAME_STEP_LENGTH),
serverId(-1),
gracefullDisconnectReason( Peered::EDisconnectReason::None ),
worldRequested(false),
worldDataSizeLeft(0),
lastConfirmedStep(INVALID_STEP),
crcRequestStep(INVALID_STEP),
awardsReceived(false),
isSpectatorJoin(false),
spectatorInfo(),
transportTimeHisto( lifehack::EasyVector<double>( 0.0, 2.0, 5.0, 10.0, 20.0, 50.0, 100.0, 200.0, 500.0 ) ),
queueTimeHisto( lifehack::EasyVector<double>( 0.0, 2.0, 5.0, 10.0, 20.0, 50.0, 100.0, 200.0, 500.0 ) ),
newTimeScale(-1.0f)
{
  NGlobal::RegisterContextCmd( "timescale", this, &ServerNode::SetTimeScale );

  NDebug::IDebugVar * pingVar = NDebug::FindDebugVar( L"hybrid_ping_value" );
  hybridRPCPingVar = static_cast<NDebug::DebugVar<int>*>(pingVar);

  steps.reserve(2);
  steps.push_back(&stepsUc);
  steps.push_back(&stepsMc);
}



void ServerNode::Reinit( Peered::IGameServer* _server, int _lastStep )
{
  MessageTrace( "Re-initializing ServerNode, svcptr=%08x", (void*)_server );

  server = _server;

  for (int i = 0; i < steps.size(); ++i)
  {
    TStepsContainer * stepsQueue = steps[i];
    cache.reserve(cache.size() + stepsQueue->size());
    cache.insert(cache.end(), stepsQueue->begin(), stepsQueue->end());
    stepsQueue->clear();
  }
  lastStep = _lastStep;

  gracefullDisconnectReason = Peered::EDisconnectReason::None;
}



ServerNode::~ServerNode()
{
  NGlobal::UnregisterCmd( "timescale" );
  for (int i = 0; i < steps.size(); ++i)
  {
    TStepsContainer * stepsQueue = steps[i];
    for (TStepsContainer::iterator it = stepsQueue->begin(); it != stepsQueue->end(); ++it)
    {
      delete *it;
    }
    stepsQueue->clear();
  }

  for (int i=0;i<cache.size();++i)
  {
    delete cache[i];
  }
  cache.clear();
}


void ServerNode::SendCRC( int step, DWORD crcValue )
{
  if (server && confirmFrequency > 0 && step % confirmFrequency == 0)
  {
    server->OnFinishStep(clientIndex, step, crcValue);
  }
}


void ServerNode::SendCrcData( int step, unsigned char * data, int size)
{
  if (server)
  {
    //TODO: do something with the magic number 64k
    NI_VERIFY_TRACE( size <= 64000, "Async data exceeds max packet size!", return; );
    rpc::MemoryBlock crcData(data, size);
    server->SendCrcData(clientIndex, step, crcData);
  }
}


void ServerNode::SendMessage(Stream* writeStream, bool isPlayerCommand) 
{
  if (server)
  {
    server->SendCommand(clientIndex, rpc::MemoryBlock((void*)writeStream->GetBuffer(), writeStream->GetPosition()), isPlayerCommand);
  }
}



void ServerNode::OnAsync(int step, const nstl::vector<Peered::AsyncInfo>& _asyncs)
{
  if (asyncStep == INVALID_STEP)
  {
    asyncStep = step;
    asyncs = _asyncs;
  }
}



bool ServerNode::PopClientStatusChange( Peered::BriefClientInfo & info )
{
  if ( clientsStatusChanges.empty() )
    return false;

  info = clientsStatusChanges.front();
  clientsStatusChanges.pop_front();
  return true;
}



void ServerNode::OnCombatScreenStarted( const NGameX::ReplayInfo & _replayInfo )
{
  if (replayWriter)
    replayWriter->WriteStartGameInfo(_replayInfo);
}

void ServerNode::GameFinished( const StatisticService::RPC::SessionClientResults & finishInfo, const NGameX::ReplayInfo & _replayInfo, int step )
{
  if ( server )
    server->OnGameFinish( clientIndex, step, finishInfo );

  if (replayWriter)
    replayWriter->WriteFinishGame(step+1, finishInfo, _replayInfo);
}



void ServerNode::ClientReady()
{
  if (server)
    server->OnClientReady(clientIndex);
}


int ServerNode::GetServerSegment( TMessageList &segment, TStatusList & statuses ) 
{
#ifndef _SHIPPING
  if (StepLags()) // Call lag generator logic
    return INVALID_STEP;
#endif // #ifndef _SHIPPING

  int foundStep = INVALID_STEP;

  for (int i = 0; i < steps.size() && foundStep == INVALID_STEP; ++i)
  {
    TStepsContainer * stepsQueue = steps[i];
    while (stepsQueue->size() > 0)
    {
      StepData * data = *stepsQueue->begin();
      if ((lastStep + 1 >= (int)data->step || lastStep == INVALID_STEP))
      {
        stepsQueue->erase(stepsQueue->begin());
        cache.push_back(data);

        if ((lastStep + 1 == (int)data->step || lastStep == INVALID_STEP))
        {
          segment = data->commands.items;

          statuses.resize(data->statuses.size());
          for (int i = 0; i < data->statuses.size(); ++i)
          {
            NCore::ClientStatus & dstStatus = statuses[i];
            Peered::BriefClientInfo & srcStatus = data->statuses[i];

            dstStatus.clientId = srcStatus.clientId;
            dstStatus.status = srcStatus.status;
            dstStatus.step = srcStatus.step - startedStep; // Translate server step to world step
          }

          lastStep = data->step;
          return data->step;
        }
      }
      else
      {
        break;
      }
    }
  }


  return foundStep;
}

const Peered::ClientInfo* ServerNode::GetClientInfo( Transport::TClientId clientId ) const
{
  for (nstl::vector<Peered::ClientInfo>::const_iterator it = clientsInfos.begin(); it != clientsInfos.end(); ++it)
    if ((*it).clientId == clientId)
      return it;
  return 0;
}



void ServerNode::Start(const Peered::ClientStartInfo& clientStartInfo, Peered::RIGameServerReconnect * gameServerReconnect)
{
  if (bLogStepTime)
    MessageTrace( "gameclient: Start (time=%.4f, index=%d, serverId=%s, tid=%d)", NHPTimer::GetScalarTime(), clientStartInfo.index, lobby::FmtGameId( clientStartInfo.serverId ), ::GetCurrentThreadId() );

  MessageTrace( "ServerNode: Starting game (sid=%016x)", clientStartInfo.serverId );

  clientIndex = clientStartInfo.index;
  serverId = clientStartInfo.serverId;
  clientsInfos = clientStartInfo.clientsInfos;
  confirmFrequency = clientStartInfo.confirmFrequency;
  protectionMagicConfirmFrequency = clientStartInfo.protectionMagicConfirmFrequency;
  snapshotChunkSize = clientStartInfo.snapshotChunkSize;
  isReconnecting = clientStartInfo.isReconnecting;
  snapshotSendPerStep = clientStartInfo.snapshotSendPerStep;
  crcDataRequestsEnabled = clientStartInfo.crcDataRequestsEnabled;
  fastReconnectEnabled = clientStartInfo.fastReconnectEnabled;
  simulationStep = clientStartInfo.simulationStep;

  stepsDelaySettings.stepsDelayMin = clientStartInfo.stepsDelayMin;
  stepsDelaySettings.stepsDelayMax = clientStartInfo.stepsDelayMax;
  stepsDelaySettings.stepsDelayFrame = clientStartInfo.stepsDelayFrame;

  clientSettings = clientStartInfo.clientSettings;

  stats.Init(NHPTimer::Milliseconds2Time(simulationStep + 2), true);
  queueTimeStats.Init(NHPTimer::Milliseconds2Time(simulationStep - 5), true);
  NHPTimer::STime longStepTime = NHPTimer::Milliseconds2Time(simulationStep + simulationStep*stepsDelaySettings.stepsDelayMin);
  stats.SetLongTime( longStepTime );
  stepTimeStatsFull.SetLongTime( longStepTime );

  if (isReconnecting)
  {
    NI_VERIFY(gameServerReconnect, "ServerNode: Reconnect interface not received!", return;);

    clientReconnect = new GameClientReconnect();
    gameServerReconnect->SetGameClientReconnect(clientIndex, RemotePtr<Peered::RIGameClientReconnect>(clientReconnect));
  }

  for ( int i = 0; i < clientsInfos.size(); ++i )
  {
    const NCore::PlayerInfo & info = clientsInfos[i].info;
    MessageTrace( "gameclient: Player info. uid=%d, castle_lvl=%d, hero_lvl=%d, prating=%.2f, hrating=%.2f, party_id=%d", 
      info.auid, info.avatarLevel, info.heroLevel, info.playerRating, info.heroRating, info.partyId );
  }

  // We don't write replay after reconnect because it will be unplayable
  if (isReconnecting)
    replayWriter = 0;

  if (replayWriter)
    replayWriter->WriteGSData(simulationStep, clientSettings, clientsInfos);
}


void ServerNode::OnStart(int step)
{
  if (bLogStepTime)
  {
    systemLog(NLogg::LEVEL_MESSAGE) << 
      "gameclient: OnStart (time = "<< NHPTimer::GetScalarTime() << 
      " step = " << step << 
      " tid = " << ::GetCurrentThreadId() << 
      ")" << endl;
  }

  startedStep = step;

  if (replayWriter)
    replayWriter->WriteStartGame(serverId, step);
}


void ServerNode::Step(
  int step,
  int lastConfirmedStep,
  const nstl::vector<rpc::MemoryBlock>& commands, 
  const nstl::vector<Peered::BriefClientInfo>& statuses,
  const nstl::vector<Peered::GapInfo>& gapInfo,
  const Transport::MessageMiscInfo& __miscInfo__)
{
  if (startedStep >= 0)
    UpdateQueueTimeStatistics(step, __miscInfo__);

  StepImpl(step, lastConfirmedStep, commands, statuses, gapInfo, &stepsUc);
}


void ServerNode::StepLoading(
  int step,
  int lastConfirmedStep,
  const nstl::vector<rpc::MemoryBlock>& commands, 
  const nstl::vector<Peered::BriefClientInfo>& statuses,
  const nstl::vector<Peered::GapInfo>& gapInfo)
{
  // Just forward this call to a regular Step. Currently we have separate StepLoading for rpc calls statistics only.
  StepImpl(step, lastConfirmedStep, commands, statuses, gapInfo, &stepsUc);
}


void ServerNode::StepBatch(
  int lastConfirmedStep,
  const nstl::vector<Peered::ClientStepData>& stepData)
{
  for (int i = 0; i < stepData.size(); ++i)
  {
    const Peered::ClientStepData & step = stepData[i];
    StepImpl(step.step, lastConfirmedStep, step.commands, step.statuses, step.clientGaps, &stepsUc);
  }
}


void ServerNode::StepMc(const rpc::MemoryBlock& stepData)
{
  // TODO: De-crap this code in NUM_TASK
  char * src = (char *)stepData.memory;

  int step;
  memcpy(&step, src, sizeof(int));
  src += sizeof(int);

  int lastConfirmedStep;
  memcpy(&lastConfirmedStep, src, sizeof(int));
  src += sizeof(int);

  int size;
  memcpy(&size, src, sizeof(int));
  src += sizeof(int);
  vector<rpc::MemoryBlock> commands(size);
  for (int i = 0; i < size; ++i)
  {
    int commandSize;
    memcpy(&commandSize, src, sizeof(int));
    src += sizeof(int);
    commands[i].size = commandSize;
    commands[i].memory = src;
    src += commandSize;
  }

  memcpy(&size, src, sizeof(int));
  src += sizeof(int);
  vector<Peered::BriefClientInfo> statuses(size);
  for (int i = 0; i < size; ++i)
  {
    statuses[i] = *(Peered::BriefClientInfo*)src;
    src += sizeof(Peered::BriefClientInfo);
  }

  memcpy(&size, src, sizeof(int));
  src += sizeof(int);
  vector<Peered::GapInfo> gapInfo(size);
  for (int i = 0; i < size; ++i)
  {
    gapInfo[i] = *(Peered::GapInfo*)src;
    src += sizeof(Peered::GapInfo);
  }

  StepImpl(step, lastConfirmedStep, commands, statuses, gapInfo, &stepsMc);
}


void ServerNode::StepImpl(
  int step,
  int _lastConfirmedStep,
  const nstl::vector<rpc::MemoryBlock>& commands, 
  const nstl::vector<Peered::BriefClientInfo>& statuses,
  const nstl::vector<Peered::GapInfo>& gapInfo,
  TStepsContainer * stepsQueue)
{
  if (startedStep >= 0)
  {
    UpdateStepStatistics(step);
  }

  if (bLogStepTime)
  {
    systemLog(NLogg::LEVEL_MESSAGE) << 
      "gameclient: Step (time = "<< NHPTimer::GetScalarTime() << 
      " step = " << step << 
      " tid = " << ::GetCurrentThreadId() << 
      ")" << endl;
  }

  // Ignore blocked steps
  if (step == NCore::INVALID_STEP)
    return;

  if (replayWriter && startedStep >= 0 && (commands.size() > 0 || statuses.size() > 0))
    replayWriter->WriteStepData(step, commands, statuses);

  StepData* data;
  if (cache.size() > 0)
  {
    data = *(cache.end()-1);
    data->Reset();
    cache.pop_back();
  } 
  else
  {
    data = new StepData;
  }
  data->step = step;
  data->commands.Copy(commands);
  data->statuses = statuses;
  stepsQueue->push_back(data);

  lastConfirmedStep = max<int>(lastConfirmedStep, (int)_lastConfirmedStep);

  nstl::string clientsLagsStr;
  for( nstl::vector<Peered::GapInfo>::const_iterator it = gapInfo.begin(); it != gapInfo.end(); ++it )
  {
    if ( it != gapInfo.begin() )
      clientsLagsStr += ", ";
    clientsLagsStr += NStr::StrFmt( "%d: %d", it->clientId, it->confirmedStepsGap );
  }
  clientsLags.SetValue( clientsLagsStr );
}


void ServerNode::UpdateStepStatistics(int step)
{
  static int openedFileCount = RootFileSystem::GetOpenedFileCount();
  static int screenshotCount = Render::SmartRenderer::GetScreenshotCount();

  if (stats.IsStarted())
  {
    NHPTimer::STime stepTime = stats.Stop();

    stepTimeStatsFull.AddStepTime(stepTime);

    if ( stepTime >  stats.GetLongTime() )
    {
      if (hybridRPCPingVar)
      {
        rpcPing = hybridRPCPingVar->GetValue();
      }

      transportPing = GetPingTime().value;
    }
  }

  if (stats.GetCount() == 50)
  {
    const AppFramework::InstanceStatistics::ValueAccumulator& info = stats.Finish();
    int avgValueTimeMs = NHPTimer::Time2Milliseconds(info.averageValue);

    int newOpenedFileCount = RootFileSystem::GetOpenedFileCount() - openedFileCount;
    openedFileCount += newOpenedFileCount;
    int newScreenshotCount = Render::SmartRenderer::GetScreenshotCount() - screenshotCount;
    screenshotCount += newScreenshotCount;

    if ((avgValueTimeMs - simulationStep) > 2 || stats.GetLongTimeCount() > 0)
    {
      time_t startTimeStamp = stats.GetFirstStartTimeStamp();
      time_t endTimeStamp = stats.GetFinishTimeStamp();

      struct tm startTime;
      struct tm endTime;
      localtime_s(&startTime, &startTimeStamp);
      localtime_s(&endTime, &endTimeStamp);

      int minValueTimeMs = NHPTimer::Time2Milliseconds(info.minValue);
      int maxValueTimeMs = NHPTimer::Time2Milliseconds(info.maxValue);

      DebugTrace( "ServerNode: Lags detected: min:%d average:%d max:%d count:%d", 
          minValueTimeMs, avgValueTimeMs, maxValueTimeMs, stats.GetLongTimeCount() );
      DebugTrace( "ServerNode: Lags detected: start:%02d:%02d:%02d end:%02d:%02d:%02d step:%d fopens:%d screenshots:%d", 
          startTime.tm_hour, startTime.tm_min, startTime.tm_sec, 
          endTime.tm_hour, endTime.tm_min, endTime.tm_sec, step, newOpenedFileCount, newScreenshotCount);
      DebugTrace( "ServerNode: Lags detected: RPC ping:%d transport ping:%d", rpcPing, transportPing );

      if (gameStatistics && gameStatistics->IsDebugStatisticsAvailable())
      {
        StatisticService::RPC::ExceedingStepTimeInfo info;

        info.typeId       = StatisticService::RPC::ServerStepTime
                              | ((newOpenedFileCount > 0)?(StatisticService::RPC::OpenedFileFlag):(0))
                              | ((newScreenshotCount > 0)?(StatisticService::RPC::ScreenshotFlag):(0));
        info.startStep    = step - 50;
        info.finishStep   = step;
        info.startTime    = startTimeStamp;
        info.finishTime   = endTimeStamp;
        info.stepCount    = stats.GetLongTimeCount();
        info.stepTimeMin  = minValueTimeMs;
        info.stepTimeAvg  = avgValueTimeMs;
        info.stepTimeMax  = maxValueTimeMs;
        info.rpcPing      = rpcPing;
        info.transportPing = transportPing;

        gameStatistics->LogExceedingStepTime(info);

        gameStatistics->SetLogNextPingTime(true);
      }
    }
    stats.Reset();
    rpcPing = -1;
    transportPing = -1;
  }

  stats.Start();
}


void ServerNode::UpdateQueueTimeStatistics(int step, const Transport::MessageMiscInfo & _miscInfo )
{
  static int openedFileCount = RootFileSystem::GetOpenedFileCount();
  static int screenshotCount = Render::SmartRenderer::GetScreenshotCount();

  timer::Time now = timer::Now(), queueTime = NHPTimer::Time2Seconds( _miscInfo.queueAbsTime );
  timer::Time transportLag = 1e3 * ( queueTime - _miscInfo.recvAbsTime );
  timer::Time queueLag = 1e3 * ( now - queueTime );
  transportTimeHisto.AddData( transportLag );
  queueTimeHisto.AddData( queueLag );

  queueTimeStats.Start( _miscInfo.queueAbsTime );
  queueTimeStats.Stop();

  if (queueTimeStats.GetCount() == 50)
  {
    int newOpenedFileCount = RootFileSystem::GetOpenedFileCount() - openedFileCount;
    openedFileCount += newOpenedFileCount;
    int newScreenshotCount = Render::SmartRenderer::GetScreenshotCount() - screenshotCount;
    screenshotCount += newScreenshotCount;

    if ( queueTimeHisto.GetTotal().maxValue > 50.0 )
      DebugTrace( "ServerNode: Queue lags details: %.1f", queueTimeHisto );
    if ( transportTimeHisto.GetTotal().maxValue > 10.0 )
      DebugTrace( "ServerNode: Transport lags details: %.1f", transportTimeHisto );

    queueTimeHisto.ResetData();

    if (queueTimeStats.GetLongTimeCount() > 0)
    {
      const AppFramework::InstanceStatistics::ValueAccumulator& info = queueTimeStats.Finish();

      time_t startTimeStamp = queueTimeStats.GetFirstStartTimeStamp();
      time_t endTimeStamp = queueTimeStats.GetFinishTimeStamp();

      struct tm startTime;
      struct tm endTime;
      localtime_s(&startTime, &startTimeStamp);
      localtime_s(&endTime, &endTimeStamp);

      int minValueTimeMs = NHPTimer::Time2Milliseconds(info.minValue);
      int maxValueTimeMs = NHPTimer::Time2Milliseconds(info.maxValue);
      int avgValueTimeMs = NHPTimer::Time2Milliseconds(info.averageValue);

      DebugTrace( "ServerNode: Queue lags detected: min:%d average:%d max:%d count:%d", 
          minValueTimeMs, avgValueTimeMs, maxValueTimeMs, queueTimeStats.GetLongTimeCount() );
      DebugTrace( "ServerNode: Queue lags detected: start:%02d:%02d:%02d end:%02d:%02d:%02d step:%d fopens:%d screenshots:%d", 
          startTime.tm_hour, startTime.tm_min, startTime.tm_sec, 
          endTime.tm_hour, endTime.tm_min, endTime.tm_sec, step, newOpenedFileCount, newScreenshotCount);

      if (gameStatistics && gameStatistics->IsDebugStatisticsAvailable())
      {
        StatisticService::RPC::ExceedingStepTimeInfo info;

        info.typeId       = StatisticService::RPC::RpcQueueTime
                              | ((newOpenedFileCount > 0)?(StatisticService::RPC::OpenedFileFlag):(0))
                              | ((newScreenshotCount > 0)?(StatisticService::RPC::ScreenshotFlag):(0));
        info.startStep    = step - 50;
        info.finishStep   = step;
        info.startTime    = startTimeStamp;
        info.finishTime   = endTimeStamp;
        info.stepCount    = queueTimeStats.GetLongTimeCount();
        info.stepTimeMin  = minValueTimeMs;
        info.stepTimeAvg  = avgValueTimeMs;
        info.stepTimeMax  = maxValueTimeMs;
        info.rpcPing      = -1;
        info.transportPing = -1;

        gameStatistics->LogExceedingStepTime(info);
      }
    }
    queueTimeStats.Reset();
  }
}



StrongMT<Transport::IChannel> ServerNode::ServerChannel()
{
  StrongMT<Transport::IChannel> locked = serverChannel.Lock();
  if ( locked )
    return locked;

  if ( rpc::EntityHandler * pHandler = GetHandler() )
  {
    if ( rpc::INode * pNode = pHandler->GetNode(0) )
    {
      locked = pNode->GetConnectedPipe()->GetPipeChannel();
      serverChannel = locked;
      return locked;
    }
  }

  return 0;
}



Transport::Ping ServerNode::GetPingTime()
{
  if ( StrongMT<Transport::IChannel> chan = ServerChannel() )
    return chan->GetPingTime();

  Transport::Ping ping = -1;
  return ping;
}



void ServerNode::DumpLags() const
{
  if (stepTimeStatsFull.GetLongTimeCount() > acceptableLagsCount)
  {
    string logFileName = NDebug::GenerateDebugFileName( "lags", "bin" );
    HANDLE hLog = (HANDLE)NFile::CreateFileWithDir( logFileName.c_str() );
    if ( hLog == INVALID_HANDLE_VALUE )
      return;
    SetFilePointer( hLog, 0, 0, FILE_END );
    DWORD writtenSize;
    WriteFile( hLog, &startedStep, sizeof(startedStep), &writtenSize, 0 );
    WriteFile( hLog, stepTimeStatsFull.GetBuffer(), stepTimeStatsFull.GetBufferSize(), &writtenSize, 0 );
    CloseHandle( hLog );
  }

}


int ServerNode::PopCrcRequestStep()
{
  int currentCrcRequestStep = crcRequestStep;
  crcRequestStep = INVALID_STEP;
  return currentCrcRequestStep;
}

bool ServerNode::PopNewTimeScale(float& scale)
{
  if (newTimeScale >= 0.0f)
  {
    scale = newTimeScale;
    newTimeScale = -1.0f;
    return true;
  }
  
  return false;
}

void ServerNode::OnTimeScaleChanged(float scale)
{
  newTimeScale = scale;
}


bool ServerNode::SetTimeScale( const char *name, const vector<wstring> &args )
{
  if ( args.size() != 1 )
  {
    systemLog( NLogg::LEVEL_MESSAGE ) << "usage: " << name << " scale" << endl;
    return true;
  }

  string arg = NStr::ToMBCS( args[0] );
  float scale = NStr::ReadFloat( arg.c_str(), arg.size() );
  if ( scale < 0.01f )
  {
    systemLog( NLogg::LEVEL_MESSAGE ) << "value " << arg << " is not value for timescale" << endl;
    return true;
  }

  server->SetTimeScale( clientIndex, scale );
  return true;
}


void ServerNode::OnChangeClientStatus( const nstl::vector<Peered::BriefClientInfo> & clientStatuses )
{
  for ( int i = 0; i < clientStatuses.size(); ++i )
    clientsStatusChanges.push_back( clientStatuses[i] );
}


void ServerNode::OnDisconnect( int reason ) //Peered::EDisconnectReason::Enum
{
  gracefullDisconnectReason = (Peered::EDisconnectReason::Enum)reason;

  MessageTrace( "Game server forcibly disconnects, code %d", reason );

  if (server)
    server->OnDisconnectAck( clientIndex );
}


void ServerNode::OnRejoin(uint clientId)
{
  DebugTrace("Reconnect: Client is reconnecting (clientId=%d)", clientId);
}


void ServerNode::RequestWorldData(Peered::RIGameServerReconnect * gameServerReconnect)
{
  NI_VERIFY(gameServerReconnect, "World data request without server reconnect interface", return;);

  worldRequested = true;
  serverReconnect = (Peered::IGameServerReconnect*)gameServerReconnect;
  DebugTrace("Reconnect: World data request received");
}


void ServerNode::RequestCrcData(int step)
{
  crcRequestStep = step;
}


void ServerNode::Award( const vector<roll::SAwardInfo> & _awards )
{
  awards = _awards;
  awardsReceived = true;
}


void ServerNode::OnSpectate(const Peered::SpectatorInfo& info)
{
  isSpectatorJoin = true;
  spectatorInfo = info;
}


void ServerNode::OnPlaySameTeamDecision(const Transport::TClientId clientId, const bool agreed)
{
  const PlaySameTeamDecision decision(clientId, agreed);

  playSameTeamDecisions.push_back(decision);
}


bool ServerNode::PopPlaySameTeamDecision(PlaySameTeamDecision& decision)
{
  if (playSameTeamDecisions.empty())
    return false;

  decision = playSameTeamDecisions.front();

  playSameTeamDecisions.pop_front();

  return true;
}


bool ServerNode::PopWorldRequest(bool & worldRequest, int currentStep)
{
  worldRequest = false;

  if (server && confirmFrequency > 0 && currentStep % confirmFrequency == 0)
  {
    if (worldRequested)
    {
      worldRequested = false;
      worldRequest = true;
      return true;
    }
  }

  return false;
}


bool ServerNode::PopWorldData(Stream & worldData, int & segmentStep)
{
  if (clientReconnect)
  {
    return clientReconnect->GetWorldData(worldData, segmentStep);
  }

  return false;
}


void ServerNode::SendWorldData(int step)
{
  worldDataSizeLeft = worldData.GetPosition();

  worldData.Seek(0, SEEKORIGIN_BEGIN);

  int partsCount = (int)ceil( (float)worldDataSizeLeft/(float)snapshotChunkSize );

  DebugTrace("Reconnect: Sending world data (size=%d, step=%d, partsCount=%d)", worldDataSizeLeft, step, partsCount);

  Peered::WorldDataInfo currentWorldDataInfo(step, partsCount);

  serverReconnect->SendWorldDataInfo(clientIndex, currentWorldDataInfo);

  // Send first portion of world data
  SendWorldDataParts();
}


void ServerNode::SendWorldDataParts()
{
  int sentInCurrentCall = 0;

  while (worldDataSizeLeft > 0 && (snapshotSendPerStep <= 0 || sentInCurrentCall < snapshotSendPerStep))
  {
    int dataSizeToSend = (snapshotChunkSize < worldDataSizeLeft)?(snapshotChunkSize):(worldDataSizeLeft);
    rpc::MemoryBlock worldDataPart( (void*)(worldData.GetBuffer() + worldData.GetPosition()), dataSizeToSend );

    serverReconnect->SendWorldDataPart(clientIndex, worldDataPart);

    worldData.Seek(dataSizeToSend, SEEKORIGIN_OFFSET);
    worldDataSizeLeft -= dataSizeToSend;
    sentInCurrentCall += dataSizeToSend;
  }

  DebugTrace("Reconnect: World data portion sent (size=%d)", sentInCurrentCall);
}


void ServerNode::RequestWorldDataFromServer()
{
  DebugTrace("Reconnect: Requesting world data from server");
  server->RequestWorldData(clientIndex);
}


void ServerNode::OnBadBehaviourComplaint(const Transport::TClientId clientId, const Transport::TClientId reportedClientId, int reportItemId)
{
  const BadBehaviourComplaint complaint(clientId, reportedClientId, reportItemId);

  badBehaviourComplaints.push_back(complaint);
}


bool ServerNode::PopBadBehaviourComplaint(BadBehaviourComplaint& complaint)
{
  if (badBehaviourComplaints.empty())
    return false;

  complaint = badBehaviourComplaints.front();

  badBehaviourComplaints.pop_front();

  return true;
}


void ServerNode::SendProtectionMagic(int step, uint magic)
{
  if (!server)
    return;

  if (protectionMagicConfirmFrequency <= 0)
    return;
  if (step % protectionMagicConfirmFrequency)
    return;

  server->SendProtectionMagic(clientIndex, step, magic);
}


void ServerNode::OnProtectionAsync(int step)
{
  if (protectionAsyncStep == INVALID_STEP)
  {
    protectionAsyncStep = step;
  }
}


} // NCore