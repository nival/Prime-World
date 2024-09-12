#pragma once

#include "Server/Statistic/GameStatClient.h"
#include "Server/Statistic/StatisticsServerTypes.h"
#include "RPC/IfaceRequester.h"
#include "PeeredTypes.h"


namespace Transport
{
  class IPerfCounters;
}


namespace Peered
{

namespace EReconnectType
{
  enum Enum
  {
    Fast,
    Normal,
    Full
  };
}

namespace EReconnectResult
{
  enum Enum
  {
    Success,
    Failure,
    Cheated,
    GameFinished,
    WorldRequestFailed,
    NoReconnectIface,
    Disabled,
    WrongSesionState,
    ClientNotFound,
    IdAndIndexMissmatch,
    WrongStep,
    Disconnected
  };
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class IPeeredStatistics : public IBaseInterfaceMT
{
  NI_DECLARE_CLASS_1( IPeeredStatistics, IBaseInterfaceMT );

public:
  virtual void LogGSLag( StatisticService::RPC::ExceedingStepTimeInfoServer & info ) = 0;
  virtual void LogReconnect( StatisticService::RPC::ReconnectAttemptInfo & info ) = 0;
  virtual void LogTraffic( StatisticService::RPC::SessionTrafficInfo & info ) = 0;
  virtual void LogClientStatus( StatisticService::RPC::UserStatusEvent & evt ) = 0;
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PeeredStatistics : public IPeeredStatistics, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( PeeredStatistics, IPeeredStatistics, BaseObjectMT );

public:
  PeeredStatistics( StatisticService::GameStatClient * _statistics, Transport::IPerfCounters * _perfCounters ) :
  statistics( _statistics ),
  perfCounters( _perfCounters )
  {}

  virtual void LogGSLag( StatisticService::RPC::ExceedingStepTimeInfoServer & info );
  virtual void LogReconnect( StatisticService::RPC::ReconnectAttemptInfo & info );
  virtual void LogTraffic( StatisticService::RPC::SessionTrafficInfo & info );
  virtual void LogClientStatus( StatisticService::RPC::UserStatusEvent & evt );

private:
  StrongMT<StatisticService::GameStatClient> statistics;
  WeakMT<Transport::IPerfCounters> perfCounters;
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class TrafficStatistics : public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_1( TrafficStatistics, BaseObjectMT );

  struct FramedTrafficCounter
  {
    int totalTraffic;
    int maxFrameTraffic;
    int curFrameTraffic;
    int framesCount;

    FramedTrafficCounter() : totalTraffic(0), maxFrameTraffic(0), curFrameTraffic(0), framesCount(0) {}

    float GetAvg() const
    {
      return (framesCount > 0) ? ((float)totalTraffic / framesCount) : (0.0f);
    }

    void Add(int newTraffic)
    {
      curFrameTraffic += newTraffic;
    }

    void Finish(int _framesCount = 1)
    {
      if (curFrameTraffic > maxFrameTraffic)
        maxFrameTraffic = curFrameTraffic;
      totalTraffic += curFrameTraffic;
      curFrameTraffic = 0;
      framesCount += _framesCount;
    }
  };

public:
  TrafficStatistics(TSessionId _sessionId, Peered::IPeeredStatistics * _statisticsWrapper, NLogg::CChannelLogger * _logStream)
    : sessionId(_sessionId)
    , statisticsWrapper(_statisticsWrapper)
    , logStream(_logStream)
    , totalInTraffic(0)
    , totalInReconnectTraffic(0)
    , cmdTrafficSecond(0)
  {}

  void AddInTrafficSize(int size) { totalInTraffic += size; }
  void AddOutTrafficSize(int size) { outTraffic.Add(size); }
  void FinishOutTrafficFrame() { if (outTraffic.curFrameTraffic > 0) outTraffic.Finish(); }
  void AddInReconnectTrafficSize(int size) { totalInReconnectTraffic += size; }
  void AddOutReconnectTrafficSize(int size) { outReconnectTraffic.Add(size); }
  void FinishOutReconnectTrafficFrame() { if (outReconnectTraffic.curFrameTraffic > 0) outReconnectTraffic.Finish(); }
  void AddCmdTraffic(int count);
  void LogTraffic();

private:
  TSessionId sessionId;
  StrongMT<Peered::IPeeredStatistics> statisticsWrapper;
  NLogg::CChannelLogger* logStream;

  int totalInTraffic;
  FramedTrafficCounter outTraffic;

  int totalInReconnectTraffic;
  FramedTrafficCounter outReconnectTraffic;

  time_t cmdTrafficSecond;
  FramedTrafficCounter cmdTraffic;
};

} // namespace Peered

