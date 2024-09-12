#ifndef GAMESTATISTICS_H_INCLUDED
#define GAMESTATISTICS_H_INCLUDED

#include "PF_GameLogic/IGameStatistics.h"
#include "Server/Statistic/GameStatClient.h"
#include "Server/Statistic/StatisticsCommonTypes.h"
#include "Server/Statistic/StatisticsClientTypes.h"
#include "Server/Statistic/StatisticsDebugTypes.h"


namespace StatisticService
{


class GameStatistics : public IGameStatistics, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( GameStatistics, IGameStatistics, BaseObjectMT );

public:
  GameStatistics( GameStatClient * _gameStatistics, GameStatClient * _gameStatisticsDebug ) :
  gameStatistics(_gameStatistics),
  gameStatisticsDebug(_gameStatisticsDebug),
  sessionId(0),
  userId(0),
  lastWorldRequestStep(0),
  timeDelta(0),
  logNextPingTime(false),
  stepTimeFlags(0)
  {
    stepTimeFlagsRemovalTime.assign(sizeof(int)*8, 0);
  }



  void ResetRemotePtrs( GameStatClient * _gameStatistics, GameStatClient * _gameStatisticsDebug )
  {
    gameStatistics = _gameStatistics;
    gameStatisticsDebug = _gameStatisticsDebug;
  }


  //IGameStatistics
  virtual void LogSessionEvent( int step, float x, float y, int eventType, const RPC::SessionEventInfo & info )
  {
    if (gameStatistics && sessionId)
    {
      if ( !gameStatistics->IsSessionEventEnabled( eventType ) )
        return;
      RPC::ClientCommonSessionEvent evt;
      evt.common = RPC::CommonSessionEventInfo( sessionId, userId, step );
      evt.x = x;
      evt.y = y;
      evt.eventType = eventType;
      evt.info = info;
      gameStatistics->Message( evt );
    }
  }


  //IGameStatistics
  virtual void LogSessionDamage( const RPC::SessionDamageInfo & info, int step )
  {
    if (gameStatistics && sessionId)
    {
      RPC::ClientSessionDamageMessage msg;
      msg.common = RPC::CommonSessionEventInfo( sessionId, userId, step );
      msg.info = info;
      gameStatistics->Message( msg );
    }
  }


  //IGameStatistics
  virtual void LogPvxLogin()
  {
    DebugTrace( NStr::StrFmt("LogPvxLogin: relayAddress = %s", NStr::ToMBCS(relayAddress)) );
    RPC::PvxLoginInfo info(sessionId, userId, relayAddress);
    gameStatisticsDebug->Message(info);
  }


  //IGameStatistics
  void LogScreenResolution( int w, int h )
  {
    RPC::PvxScreenResolutionInfo info( sessionId, userId, w, h );
    gameStatisticsDebug->Message( info );
  }


  void LogExceedingStepTime( RPC::ExceedingStepTimeInfo& info )
  {
    if (IsDebugStatisticsAvailable() && sessionId)
    {
      ApplyStepTimeFlags(info);

      info.sessionId = sessionId;
      info.playerId  = userId;
      info.lastWorldRequestStep = lastWorldRequestStep;
      if (info.startTime > 0)
        info.startTime  -= timeDelta;
      if (info.finishTime > 0)
        info.finishTime -= timeDelta;

      gameStatisticsDebug->Message( info );
    }
  }



  void LogExceedingPingTime( RPC::ExceedingPingTimeInfo& info )
  {
    logNextPingTime = false;

    if (IsDebugStatisticsAvailable() && sessionId)
    {
      info.sessionId = sessionId;
      info.playerId  = userId;
      if (info.startTime > 0)
        info.startTime  -= timeDelta;
      if (info.finishTime > 0)
        info.finishTime -= timeDelta;

      gameStatisticsDebug->Message( info );
    }
  }


  GameStatClient * GetGameStatisticsWriter() { return gameStatistics; }
  GameStatClient * GetGameStatisticsDebugWriter() { return gameStatisticsDebug; }



  void SetSessionId(__int64 _sessionId) { sessionId = _sessionId; }
  void SetUserId(int _userId) { userId = _userId; }
  void SetLastWorldRequestStep(int _lastWorldRequestStep) { lastWorldRequestStep = _lastWorldRequestStep; }
  void SetTimeDelta(int _timeDelta) { timeDelta = _timeDelta; }

  void SetLogNextPingTime(bool _logNextPingTime) { logNextPingTime = _logNextPingTime; }
  bool GetLogNextPingTime() const { return logNextPingTime; }

  bool IsDebugStatisticsAvailable() const;

  void AddStepTimeFlags(int _stepTimeFlags) { stepTimeFlags |= _stepTimeFlags; }
  void RemoveStepTimeFlags(int _stepTimeFlags);

  void SetRelayAddress(const nstl::string & _relayAddress) { relayAddress = NStr::ToUnicode(_relayAddress); }

private:
  void ApplyStepTimeFlags(RPC::ExceedingStepTimeInfo& info);

  StrongMT<GameStatClient>  gameStatistics;
  StrongMT<GameStatClient>  gameStatisticsDebug;

  __int64 sessionId;
  int userId;
  int lastWorldRequestStep;
  int timeDelta;

  bool logNextPingTime;

  int stepTimeFlags;
  nstl::vector<time_t> stepTimeFlagsRemovalTime;

  nstl::wstring relayAddress;
};




struct PingStatisticsContainer : NonCopyable
{
  struct PingStatistics
  {
    int pingMin;
    int pingMax;
    int pingCnt;
    __int64 pingAvg;

    PingStatistics()
    {
      Reset();
    }

    void Reset()
    {
      pingMin = _I32_MAX;
      pingMax = _I32_MIN;
      pingCnt = 0;
      pingAvg = 0;
    }

    void AddValue(int value)
    {
      if (value < pingMin) 
      {
        pingMin = value;
      }
      if (value > pingMax) 
      {
        pingMax = value;
      }
      pingAvg += value;
      ++pingCnt;
    }

    int GetMin()
    {
      if (pingMin != _I32_MAX)
      {
        return pingMin;
      }
      else
      {
        return 0;
      }
    }

    int GetMax()
    {
      if (pingMax != _I32_MIN)
      {
        return pingMax;
      }
      else
      {
        return 0;
      }
    }

    int GetAvg()
    {
      if (pingCnt > 0)
      {
        return double(pingAvg)/pingCnt;
      }
      else
      {
        return 0;
      }
    }
  };

  struct PingStatisticsPair
  {
    PingStatistics low;
    PingStatistics high;
    int lastNumber;

    int waterline;

    PingStatisticsPair() : waterline(400), lastNumber(-1)
    {
      Reset();
    }

    void Reset()
    {
      low.Reset();
      high.Reset();
    }

    void AddValue(int value, int number)
    {
      if (number != lastNumber)
      {
        lastNumber = number;

        if (value < waterline)
        {
          low.AddValue(value);
        }
        else
        {
          high.AddValue(value);
        }
      }
    }
  };

  typedef nstl::map<StatisticService::RPC::ExceedingPingTimeType, PingStatisticsPair> PingValues;

  time_t      firstPingTime;
  time_t      lastPingTime;
  int         count;
  PingValues  pingValues;

  PingStatisticsContainer()
  {
    Reset();
  }

  void Start(NHPTimer::FTime currentTime)
  {
    firstPingTime = currentTime;
  }

  void Step(NHPTimer::FTime currentTime)
  {
    lastPingTime = currentTime;
    ++count;
  }

  bool IsStarted() const
  {
    return (firstPingTime != 0.0);
  }

  void Reset()
  {
    for (PingValues::iterator it = pingValues.begin(); it != pingValues.end(); ++it)
    {
      it->second.Reset();
    }
    firstPingTime = 0.0;
    lastPingTime  = 0.0;
    count         = 0;
  }

  bool HasHighPing()
  {
    for (PingValues::iterator it = pingValues.begin(); it != pingValues.end(); ++it)
    {
      if (it->second.high.pingCnt > 0)
      {
        return true;
      }
    }
    return false;
  }

  PingStatisticsPair* GetPingStatistics(StatisticService::RPC::ExceedingPingTimeType type)
  {
    PingValues::iterator it = pingValues.find(type);
    if (it != pingValues.end())
    {
      return &it->second;
    }
    return 0;
  }

  bool GetPingStatistics(StatisticService::RPC::ExceedingPingTimeType type, StatisticService::RPC::ExceedingPingTimeInfo & dest)
  {
    PingValues::iterator it = pingValues.find(type);
    if (it != pingValues.end())
    {
      dest.typeId       = type;
      dest.startTime    = firstPingTime;
      dest.finishTime   = lastPingTime;
      dest.pingLCount   = it->second.low.pingCnt;
      dest.pingLTimeMin = it->second.low.GetMin();
      dest.pingLTimeMax = it->second.low.GetMax();
      dest.pingLTimeAvg = it->second.low.GetAvg();
      dest.pingHCount   = it->second.high.pingCnt;
      dest.pingHTimeMin = it->second.high.GetMin();
      dest.pingHTimeMax = it->second.high.GetMax();
      dest.pingHTimeAvg = it->second.high.GetAvg();
      return true;
    }
    return false;
  }

  void SetWaterline(StatisticService::RPC::ExceedingPingTimeType type, int waterline)
  {
    NI_VERIFY( waterline > 0, "Wrong ping waterline!", return; );

    pingValues[type].waterline = waterline;
  }

  void AddPingValue(StatisticService::RPC::ExceedingPingTimeType type, int value, int number)
  {
    if (value >= 0)
    {
      pingValues[type].AddValue(value, number);
    }
  }
};


} // namespace StatisticService

#endif // #ifndef GAMESTATISTICS_H_INCLUDED
