#pragma once

#include "Interfaces.h"
#include <System/ThreadHelpers.h>
#include "System/InlineProfiler.h"
#include "System/LockFree/spsc.h"
#include "System/LockFree/mpmc_bounded.h"

namespace AppFramework
{
 
struct InstanceInfo : NonCopyable
{
  InstanceInfo();
  ~InstanceInfo();


  NHPTimer::STime GetSleepTime(NHPTimer::STime current)
  {
    return time-current;
  }

  const NHPTimer::STime& GetTime() const { return time; }

  void Clear()
  {
    instance = 0;
    classStatistics = 0;
  }

  void Reset(bool resetLate=false)
  {
    work.Reset();
    if (resetLate) 
    {
      late.Reset();
    }
  }

  void Record(const NHPTimer::STime& _workTime, const NHPTimer::STime& _lateTime)
  {
    work.Record(_workTime);
    late.Record(_lateTime);
  }

  bool Shift(const NHPTimer::STime& absoluteTime, int _index)
  {
    time = absoluteTime;
    index = _index;
    return true;
  }

  void Set(ITimedInstance* _instance)
  {
    instance = _instance;
    instancePtr = _instance;
    instanceId = _instance->GetId();
  }
  StrongMT<ITimedInstance>& Get() 
  {
    return instance;
  }

  InstanceStatistics::ValueAccumulator work;
  InstanceStatistics::ValueAccumulator late;
  InstanceStatistics* classStatistics;
  void* instancePtr;
  int instanceId;
  int index;
private:
  NHPTimer::STime time;
  StrongMT<ITimedInstance> instance;
};

typedef mpmc_bounded_queue<InstanceInfo*> InstancesPublicQueue;
typedef nstl::vector<InstancesPublicQueue*> PendingInstances;
typedef spsc_queue<InstanceInfo*> InstancesQueue;
typedef nstl::vector<InstanceInfo*> InstancesArray;
typedef nstl::hash_map<int, int> InstancesMap;
typedef nstl::map<nstl::string, InstanceStatistics*> InstanceStatisticsMap;


inline int GetMinimum(int value0, int value1, int value2);

struct InstanceUpdater : NonCopyable
{
  InstanceUpdater( 
    InstancesPublicQueue& _pendingInstances, 
    const NHPTimer::STime& _desiredTimerResolution, 
    NLogg::CChannelLogger* _logStream, 
    InstanceStatisticsMap& _statistics, 
    int _threadIndex, 
    int _scheduleBufferSize,
    int _logLagTime=0);
  ~InstanceUpdater();

  int Update(NHPTimer::STime& currentTime);

  void OutputStats(bool exitIfEmpty);
  int GetCount() const { return instances.size(); }
  void Clear();
  int GetThreadIndex() const { return threadIndex; }
  NLogg::CChannelLogger* GetLogStream() const { return logStream; }

  void SetLogLagTime(int _logLagTime) { logLagTime = _logLagTime; }

private:
  //void Debug(int value);
  int FindNearestActive();
  void ScheduleInstance(InstanceInfo* info, const NHPTimer::STime& time, bool initial);
  bool UpdateInstance(InstanceInfo* instance, const NHPTimer::STime& currentTime, const NHPTimer::STime& lateTime);
  bool ProcessPendingInstances(const NHPTimer::STime& currentTime);
  InstancesPublicQueue& pendingInstances;
  NHPTimer::STime desiredTimerResolution;
  NHPTimer::STime pendingTime;
  NLogg::CChannelLogger* logStream;
  InstanceStatisticsMap& statistics;
  nstl::vector<InstancesArray*> steps;
  int stepsIndex;
  NHPTimer::STime stepsTime;
  InstancesMap instances;
  int threadIndex;
  int logLagTime;
};

struct InstanceThread : NonCopyable
{
  InstanceThread(
    int threadIndex,
    NHPTimer::STime _statisticsInterval, 
    NLogg::CChannelLogger* _logStream,
    bool _exitIfEmpty,
    InstanceStatisticsMap& _statistics,
    InstancesPublicQueue& _pendingInstances,
    int _scheduleBufferSize,
    int _logLagTime,
    bool _isMainThread);
  ~InstanceThread();
  uint Process(const volatile bool& isRunning);
  bool IsStopped() const { return exitIfEmpty && isStopped; }
  bool IsMainThread() const { return isMainThread; }
  void SetLogLagTime(int _logLagTime) { updater.SetLogLagTime(_logLagTime); }
  InstanceUpdater updater;
private:
  void Clear();

  NHPTimer::STime startTotalTime;
  NHPTimer::STime stopPendingStartTime;

  NHPTimer::STime statisticsInterval;
  bool isStopped;
  bool isStopPending;
  bool exitIfEmpty;
  bool isMainThread;
};

class InstanceProcessingUnit : NonCopyable
{
public:
  InstanceProcessingUnit(
    int _threadIndex,
    NHPTimer::STime _statisticsInterval, 
    NLogg::CChannelLogger* _logStream,
    bool _exitIfEmpty,
    InstanceStatisticsMap& _statistics,
    InstancesPublicQueue& _pendingInstances,
    int _scheduleBufferSize,
    int _logLagTime,
    bool _isMainThread):
  worker(_threadIndex, _statisticsInterval, _logStream, _exitIfEmpty, _statistics, _pendingInstances, _scheduleBufferSize, _logLagTime, _isMainThread), 
  thread(worker, false) {}

  uint Process(const volatile bool& isRunning)
  {
    NI_PROFILE_THREAD;

    return worker.Process(isRunning);
  }

  void Start() { thread.Resume(); }
  bool IsStopped() const { return worker.IsStopped(); }
  void Stop( bool waitForStop, int timeoutInMs = 1000 ) { thread.Stop(waitForStop, timeoutInMs); }
  bool IsMainThread() const { return worker.IsMainThread(); }
  InstanceThread* GetProcessor() { return &worker; }
  void SetLogLagTime(int _logLagTime) { worker.SetLogLagTime(_logLagTime); }
private:
  InstanceThread worker;
  threading::ProcessingThread<InstanceThread> thread;
};

class TimeSlicer : NonCopyable
{
public:
  TimeSlicer(float _statisticsInterval=1.f, NLogg::CChannelLogger* _logStream=0, 
              int _threadsCount=1, int _queueSize=1024, int _scheduleBufferSize=300, int _logLagTime=0);
  ~TimeSlicer();

  bool AddInstance(ITimedInstance* instance, int threadIndex = 0);
  void Do(const volatile bool& isRunning);
  void SetLogLagTime(int _logLagTime);
private:
  void RemoveInstance(ITimedInstance* instance);
  void Stop();

  NHPTimer::STime statisticsInterval;

  typedef nstl::vector<InstanceProcessingUnit*> UnitsArray;
  UnitsArray units;
  InstanceStatisticsMap statistics;


  NLogg::CChannelLogger* logStream;
  int savedTimerResolution;
  InstanceThread* defaultProcessor;
  int threadsCount;
  threading::Mutex registerMutex;

  PendingInstances pendingInstances;
};

int SetTimerResolution(uint ms, bool beginFlag);


}
