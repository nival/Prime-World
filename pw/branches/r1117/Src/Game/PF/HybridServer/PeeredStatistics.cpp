#include "stdafx.h"
#include "PeeredStatistics.h"
#include "ServerAppBase/PerfCounters.h"

namespace Peered
{


void PeeredStatistics::LogGSLag( StatisticService::RPC::ExceedingStepTimeInfoServer & info )
{
  if ( statistics )
    statistics->Message( info );

  if ( StrongMT<Transport::IPerfCounters> locked = perfCounters.Lock() )
    locked->AutoPerfCounterRate( "gamesvc_lags", max<int>(1, info.stepCount) );
}


void PeeredStatistics::LogReconnect( StatisticService::RPC::ReconnectAttemptInfo & info )
{
  if ( statistics )
    statistics->Message( info );

  if ( StrongMT<Transport::IPerfCounters> locked = perfCounters.Lock() )
      locked->AutoPerfCounterRate( "users_reconn", 1 );
}


void PeeredStatistics::LogTraffic( StatisticService::RPC::SessionTrafficInfo & info )
{
  if ( statistics )
    statistics->Message( info );
}


void PeeredStatistics::LogClientStatus( StatisticService::RPC::UserStatusEvent & evt )
{
  // NUM_TASK выяснилось, что это событие статистикой никак не учитывается; нет смысла его отправлять
#if 0
  if ( statistics )
    statistics->Message( evt );
#endif

  if ( evt.status == Connecting )
  {
    if ( StrongMT<Transport::IPerfCounters> locked = perfCounters.Lock() )
      locked->AutoPerfCounterRate( "users_inc_gamesvc", 1 );
  }
  else if ( IsDisconnectedStatus( evt.status ) )
  {
    if ( StrongMT<Transport::IPerfCounters> locked = perfCounters.Lock() )
      locked->AutoPerfCounterRate( "users_out_gamesvc", 1 );
  }
}



void TrafficStatistics::AddCmdTraffic(int count)
{
  time_t currentSecond = time(0);
  if (currentSecond != -1)
  {
    if (cmdTrafficSecond == 0)
    {
      cmdTrafficSecond = currentSecond;
    }
    else
    {
      time_t deltaSeconds = currentSecond - cmdTrafficSecond;
      if (deltaSeconds > 0)
      {
        cmdTraffic.Finish(deltaSeconds);
        cmdTrafficSecond = currentSecond;
      }
    }
    cmdTraffic.Add(count);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TrafficStatistics::LogTraffic()
{
  if (totalInTraffic || totalInReconnectTraffic)
  {
    if (cmdTrafficSecond > 0)
      cmdTraffic.Finish(time(0) - cmdTrafficSecond);

    StatisticService::RPC::SessionTrafficInfo info;

    info.sessionId = sessionId;
    info.totalIn = totalInTraffic;
    info.totalOut = outTraffic.totalTraffic;
    info.avgOutPerStep = outTraffic.GetAvg();
    info.maxOutPerStep = outTraffic.maxFrameTraffic;
    info.totalInReconnect = totalInReconnectTraffic;
    info.totalOutReconnect = outReconnectTraffic.totalTraffic;
    info.avgOutReconnect = outReconnectTraffic.GetAvg();
    info.maxOutReconnect = outReconnectTraffic.maxFrameTraffic;
    info.avgCmdPerSecond = cmdTraffic.GetAvg();
    info.maxCmdPerSecond = cmdTraffic.maxFrameTraffic;

    localLog(logStream, NLogg::LEVEL_DEBUG).Trace(
      "GameServer: LogTraffic: (sid=%016x totalIn=%d totalOut=%d avgOutPerStep=%f maxOutPerStep=%d)", 
        sessionId, info.totalIn, info.totalOut, info.avgOutPerStep, info.maxOutPerStep);
    localLog(logStream, NLogg::LEVEL_DEBUG).Trace(
      "GameServer: LogTraffic: (sid=%016x totalInReconnect=%d totalOutReconnect=%d avgOutReconnect=%f maxOutReconnect=%d)", 
        sessionId, info.totalInReconnect, info.totalOutReconnect, info.avgOutReconnect, info.maxOutReconnect);
    localLog(logStream, NLogg::LEVEL_DEBUG).Trace(
      "GameServer: LogTraffic: (sid=%016x totalCmd=%d avgCmdPerSecond=%f maxCmdPerSecond=%d totalSeconds=%d)", 
        sessionId, cmdTraffic.totalTraffic, info.avgCmdPerSecond, info.maxCmdPerSecond, cmdTraffic.framesCount);

    if (statisticsWrapper)
      statisticsWrapper->LogTraffic(info);
  }
  else
  {
    localLog(logStream, NLogg::LEVEL_DEBUG).Trace(
      "GameServer: LogTraffic: No traffic recorded (sid=%016x", sessionId);
  }
}

} // namespace Peered
