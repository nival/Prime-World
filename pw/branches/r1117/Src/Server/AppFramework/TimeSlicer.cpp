#include "stdafx.h"             
#pragma warning(disable:4201)
#if defined( NV_WIN_PLATFORM )
#include <Mmsystem.h>
#endif
#include "TimeSlicer.h"
#include "System/ThreadNames.h"
#include "System/DarkSide.h"

NI_DEFINE_REFCOUNT( AppFramework::ITimedInstance );

namespace AppFramework
{
const int desiredTimerResolutionInMs = 1;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
InstanceInfo::InstanceInfo():classStatistics(0)
{
  NHPTimer::GetTime(time);
  index = 0;
  Reset();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
InstanceInfo::~InstanceInfo()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SetTimerResolution(uint ms, bool beginFlag)
{
#if defined( NV_WIN_PLATFORM )
  if (beginFlag)
  {
    TIMECAPS tc;
    if (timeGetDevCaps(&tc, sizeof(TIMECAPS)) != TIMERR_NOERROR) 
    {
  	   return -1; // Error; application can't continue.
    }

    int result = min(max(tc.wPeriodMin, ms), tc.wPeriodMax);
    timeBeginPeriod(result); 	  
	  return result;
  } 
  else
  {
    timeEndPeriod(ms);
    return 0;
  }
#elif defined( NV_LINUX_PLATFORM )
  return 0;
#endif
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TimeSlicer::TimeSlicer(float _statisticsInterval, NLogg::CChannelLogger* _logStream, 
                       int _threadsCount, int _queueSize, int _scheduleBufferSize, int _logLagTime):
logStream(_logStream),
threadsCount(_threadsCount)
{
  savedTimerResolution = SetTimerResolution(desiredTimerResolutionInMs, true);
  NI_ASSERT(savedTimerResolution >= 0, "Can't set timer resolution");
  statisticsInterval = NHPTimer::Seconds2Time(_statisticsInterval);
  pendingInstances.reserve(threadsCount);
  pendingInstances.push_back(new InstancesPublicQueue(Ceil2PowerOf2(Max(2, _queueSize ))));
  defaultProcessor = new InstanceThread(0, statisticsInterval, logStream, false, statistics, *pendingInstances[0], _scheduleBufferSize, _logLagTime, true);
  for (int i=0;i<threadsCount-1;++i)
  {
    pendingInstances.push_back(new InstancesPublicQueue(Ceil2PowerOf2(Max(2, _queueSize ))));
    InstanceProcessingUnit* unit = new InstanceProcessingUnit(units.size()+1, statisticsInterval, logStream, false, statistics, *pendingInstances[i+1], _scheduleBufferSize, _logLagTime, false);
    units.push_back(unit);
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TimeSlicer::~TimeSlicer()
{
  Stop();
  for (InstanceStatisticsMap::iterator it=statistics.begin();it!=statistics.end();++it)
  {
    delete it->second;
  }
  for (PendingInstances::iterator it = pendingInstances.begin(); it != pendingInstances.end(); ++it)
  {
    delete *it;
  }
  SetTimerResolution(savedTimerResolution, false);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TimeSlicer::SetLogLagTime(int _logLagTime)
{
  if (defaultProcessor)
    defaultProcessor->SetLogLagTime(_logLagTime);

  for (UnitsArray::iterator it=units.begin();it!=units.end();++it)
  {
    if ((*it))
      (*it)->SetLogLagTime(_logLagTime);
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
InstanceThread::InstanceThread(
  int _threadIndex,                                
  NHPTimer::STime _statisticsInterval, 
  NLogg::CChannelLogger* _logStream,
  bool _exitIfEmpty,
  InstanceStatisticsMap& _statistics,
  InstancesPublicQueue& _pendingInstances,
  int _scheduleBufferSize,
  int _logLagTime,
  bool _isMainThread):
statisticsInterval(_statisticsInterval),
exitIfEmpty(_exitIfEmpty),
isMainThread(_isMainThread),
updater(_pendingInstances, NHPTimer::Milliseconds2Time(desiredTimerResolutionInMs), _logStream, _statistics, _threadIndex, _scheduleBufferSize, _logLagTime)
{
  NHPTimer::GetTime(startTotalTime);
  statisticsInterval = _statisticsInterval;
  isStopped = false;
  isStopPending = false;
}

struct TimeAccumulator : NonCopyable
{
  TimeAccumulator(NHPTimer::STime& _currentTime):currentTime(_currentTime)
  {
    NHPTimer::GetTime(lastTime);
  }

  const NHPTimer::STime& Record()
  {
    NHPTimer::STime curTime;
    NHPTimer::GetTime(curTime);
    lastDelta = curTime-lastTime;
    currentTime += lastDelta;
    lastTime = curTime;
    return lastDelta;
  }

  NHPTimer::STime& currentTime;
  NHPTimer::STime lastDelta;
  NHPTimer::STime lastTime;
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
static int debug[16];

void InstanceUpdater::Debug(int value)
{
  debug[threadIndex] = value;
}
*/

int InstanceUpdater::Update(NHPTimer::STime& currentTime)
{
  NI_PROFILE_HEAVY_FUNCTION;
  if (stepsIndex == -1)
  {
    stepsTime = currentTime;
    stepsIndex = 0;
  }
  NHPTimer::STime lateTime = 0L;

  int stepsCount = (currentTime-stepsTime)/desiredTimerResolution;
  if (stepsCount > steps.size())
  {
    NHPTimer::STime restartTime = currentTime-(desiredTimerResolution*(steps.size()-1));
    localLog(logStream, NLogg::LEVEL_DEBUG).Trace("Slicer lag detected (this=%d time=%d)", DarkSide::ptr2int< int >(this), NHPTimer::Time2Milliseconds(restartTime-stepsTime));
    stepsTime = restartTime;
    stepsCount = steps.size()-1;
  }
  /*
  if (0)
  {
    char buffer[1024];
    char* buf = buffer;
    buf += sprintf(buf,"Slicer update (ss=%d sc=%d ic=%d): ", stepsIndex, stepsCount, instances.size());
    for (InstancesMap::iterator it=instances.begin();it!=instances.end();++it)
    {
      InstanceInfo* info = (InstanceInfo*)(it->first);
      buf += sprintf(buf, "%d ", info->index);
    }
    localLog(logStream, NLogg::LEVEL_DEBUG).Trace(buffer);
  }
  */

  TimeAccumulator acc(currentTime);
  for (int i=0;i<stepsCount;++i)
  {
    InstancesArray* a = steps[stepsIndex];
    for (InstancesArray::iterator it = a->begin();it!= a->end(); ++it)
    {
      InstanceInfo* info = (*it);
      lateTime = info->GetSleepTime(currentTime);
      if (!UpdateInstance(*it, currentTime, lateTime))
      {
        InstancesMap::iterator mit = instances.find(DarkSide::ptr2int< int >(*it));
        if (mit != instances.end())
        {
          instances.erase(mit);
        }
        delete info;
        info = 0;
      } 
      if (info)
      {
        info->Record(acc.Record(), lateTime);
      }
    }
    acc.Record();
    a->clear();
    stepsIndex += 1;
    stepsIndex %= steps.size();
    stepsTime += desiredTimerResolution;
  }
  bool newInstance = false;
  if (currentTime >= pendingTime)
  {
    newInstance = ProcessPendingInstances(currentTime);
    const int pendingPeriod = 10;
    pendingTime = currentTime + NHPTimer::Milliseconds2Time(pendingPeriod);
  }
  int desiredSleep = 0;
  if (!newInstance)
  {
    desiredSleep = FindNearestActive()+1; 
  }
  return desiredSleep;
}

int InstanceUpdater::FindNearestActive()
{
  const int maxSleep = 19;
  int i = stepsIndex;
  int desiredSleep = 0;
  while (desiredSleep < maxSleep)
  {
    i %= steps.size();
    if (steps[i]->size() > 0)
    {
      break;
    }
    i += 1;
    desiredSleep += 1;
  }
  return desiredSleep;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void InstanceUpdater::OutputStats(bool exitIfEmpty)
{
  for (InstancesMap::iterator it=instances.begin();it!=instances.end();++it)
  {
#ifdef DEBUG
     //localLog(logStream, NLogg::LEVEL_DEBUG).Trace("%p count:%d late:%d", it->second->instance.GetPtr(), it->second->statistics.count, NHPTimer::Time2Milliseconds(-it->second->lateTime));
#endif
    InstanceInfo* info = DarkSide::int2ptr< InstanceInfo* >(it->first);
    info->classStatistics->Add(info->work);
    info->Reset();
  }
  if (!exitIfEmpty) // main thread
  {
    for (InstanceStatisticsMap::iterator it=statistics.begin();it!=statistics.end();++it)
    {
      const InstanceStatistics::ValueAccumulator& info = it->second->Finish();
      if (info.count > 0)
      {
        localLog(logStream, NLogg::LEVEL_DEBUG).Trace("    %20s (this=%d instances=%d min=%d average=%d max=%d calls=%d thread=%d)", it->first.c_str(), DarkSide::ptr2int< int >(this), it->second->GetInstancesCount(), NHPTimer::Time2Milliseconds(info.minValue), NHPTimer::Time2Milliseconds(info.averageValue), NHPTimer::Time2Milliseconds(info.maxValue), info.count, threading::CurrentThreadID());
      }
      it->second->Reset();
    } 
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void InstanceUpdater::Clear()
{
  for (int i=0;i<steps.size();++i)
  {
    InstancesArray* a = steps[i];
    for (InstancesArray::iterator it=a->begin();it!=a->end();++it)
    {
      pendingInstances.enqueue((*it));
    }
    a->clear();
  }
  instances.clear();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
uint InstanceThread::Process(const volatile bool& isRunning)
{
  char buffer[16];
  sprintf(buffer, "TimeSlicer/%d", updater.GetThreadIndex());
  threading::SetDebugThreadName( buffer );

  while (isRunning)
  {
    NI_PROFILE_BLOCK( __FUNCTION__" iteration" );
    NHPTimer::STime currentTime;
    NHPTimer::GetTime(currentTime);
    int desiredSleep = updater.Update(currentTime);
    if (desiredSleep > 0)
    {
      threading::Sleep(desiredSleep);
    }
    if (statisticsInterval > 0)
    {
      NHPTimer::STime endTime;
      NHPTimer::GetTime(endTime);
      NHPTimer::STime elapsedTime = endTime-startTotalTime;
      if (elapsedTime >= statisticsInterval)
      {
        startTotalTime = endTime;
        updater.OutputStats(exitIfEmpty);
      }
    }
    if (exitIfEmpty && updater.GetCount() == 0)
    {
      if (isStopPending)
      {
        NHPTimer::STime currentTime;
        NHPTimer::GetTime(currentTime);
        if ( NHPTimer::Time2Seconds(currentTime-stopPendingStartTime) > 1.f)
        {
          break; // stopping thread
        }
       } else
      {
        NHPTimer::GetTime(stopPendingStartTime);
        isStopPending = true;
      }
    } else
    {
      isStopPending = false;
    }
  }
  Clear();
  isStopped = true;
  return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
InstanceThread::~InstanceThread()
{
  Clear();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void InstanceThread::Clear()
{
  updater.Clear();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TimeSlicer::RemoveInstance(ITimedInstance* instance)
{
  //threading::MutexLock lock(removeLocker);
  //removedInstances.push_back(instance);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool TimeSlicer::AddInstance(ITimedInstance* instance, int threadIndex /*= 0*/)
{
  if (threadIndex == 0 || threadIndex > 0 && threadIndex <= units.size())
  {
    InstanceInfo* info = new InstanceInfo;
    const char* typeName = instance->ClassName();
    info->Set(instance);
    {
      threading::MutexLock lock(registerMutex);
      InstanceStatisticsMap::iterator sit = statistics.find(typeName);
      if (sit == statistics.end())
      {
        sit = statistics.insert(typeName);
        sit->second = new InstanceStatistics;
      }
      info->classStatistics = sit->second;
    }
    if (pendingInstances[threadIndex]->enqueue(info))
    {
      localLog(logStream, NLogg::LEVEL_DEBUG).Trace(
        "TimeSlicer: Add instance (id=%d ptr=%p threadIndex=%d)",
          info->instanceId, info->instancePtr, threadIndex);
      return true;
    }
    else
    {
      localLog(logStream, NLogg::LEVEL_WARNING).Trace(
        "TimeSlicer: Can't add instance, input buffer is full (id=%d ptr=%p threadIndex=%d)",
          info->instanceId, info->instancePtr, threadIndex);
      return false;
    }
  }
  else
  {
    localLog(logStream, NLogg::LEVEL_WARNING).Trace(
      "TimeSlicer: Can't add instance, wrong thread index (id=%d ptr=%p threadIndex=%d)", 
        instance->GetId(), (void*)instance, threadIndex);
    return  false;
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TimeSlicer::Do(const volatile bool& isRunning)
{
  for (UnitsArray::iterator it=units.begin();it!=units.end();++it)
  {
    (*it)->Start();
  }
  defaultProcessor->Process(isRunning);
  Stop();
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TimeSlicer::Stop()
{
  // sending stop signal to threads
  for (UnitsArray::iterator it=units.begin();it!=units.end();++it)
  {
    if (!(*it)->IsMainThread())
    {
      (*it)->Stop(false);
    }
  }
  // waiting for unit stop and delete units
  for (UnitsArray::iterator it=units.begin();it!=units.end();++it)
  {
    if (!(*it)->IsMainThread())
    {
      (*it)->Stop(true, 10000);
    }
    delete (*it);
  }
  units.clear();
  delete defaultProcessor;
  defaultProcessor = 0;
  for (PendingInstances::iterator it = pendingInstances.begin(); it != pendingInstances.end(); ++it)
  {
    InstanceInfo* info;
    while ((*it)->dequeue(info))
    {
      delete info;
    }
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
InstanceUpdater::InstanceUpdater( 
  InstancesPublicQueue& _pendingInstances, 
  const NHPTimer::STime& _desiredTimerResolution, 
  NLogg::CChannelLogger* _logStream, 
  InstanceStatisticsMap& _statistics, 
  int _threadIndex, 
  int _scheduleBufferSize,
  int _logLagTime):
pendingInstances(_pendingInstances),
desiredTimerResolution(_desiredTimerResolution),
logStream(_logStream),
statistics(_statistics),
threadIndex(_threadIndex),
logLagTime(_logLagTime)
{
  pendingTime = 0L;
  steps.reserve(_scheduleBufferSize);
  for (int i=0;i<steps.capacity();++i)
  {
    steps.push_back(new InstancesArray);
  }
  stepsIndex = -1;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
InstanceUpdater::~InstanceUpdater()
{
  Clear();
  for (int i=0;i<steps.size();++i)
  {
    delete steps[i];
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool InstanceUpdater::ProcessPendingInstances(const NHPTimer::STime& currentTime)
{
  NI_PROFILE_FUNCTION;
  InstanceInfo* info;
  if (pendingInstances.dequeue(info))
  {
    StrongMT<ITimedInstance> & timedInstance = info->Get();
    if ( timedInstance )
    {
      instances.insertUnique(DarkSide::ptr2int< int >(info), 0);
      ScheduleInstance(info, currentTime, true);
      localLog(logStream, NLogg::LEVEL_DEBUG).Trace(
        "TimeSlicer: Start instance (id=%d ptr=%p threadIndex=%d)", info->instanceId, info->instancePtr, threadIndex);
    }
    return true;
  }
  return false;
}

inline int GetRealIndex(int index, int size)
{
  if (index < 0) 
    index = size-1;
  else
  if (index >= size)
  {
    index = index % size;
  }
  return index;
}

int GetMinimum(int value0, int value1, int value2)
{
  if (value0 <= value1)
  {
    if (value0 <= value2)
    {
      return 0;
    } 
    else
    {
      return 2;
    }
  }
  {
    if (value1 <= value2)
    {
      return 1;
    } else
    {
      return 2;
    }
  }
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void InstanceUpdater::ScheduleInstance(InstanceInfo* info, const NHPTimer::STime& time, bool initial)
{
  NI_PROFILE_HEAVY_FUNCTION;
  int index = ((time-stepsTime)/desiredTimerResolution)-1;
  if (index <= 0)
  {
    index = initial?0:1; // always push to the next execution block
  }
  int realIndex = stepsIndex + index;
  if (realIndex >= steps.size())
  {
    realIndex %= steps.size();
    if (realIndex >= stepsIndex)
    {
      realIndex = stepsIndex+steps.size()-1; 
      realIndex %= steps.size();
    }
  } 
  int prevIndex = GetRealIndex(realIndex-1, steps.size());
  int nextIndex = GetRealIndex(realIndex+1, steps.size());
  int target = GetMinimum(steps[realIndex]->size(), steps[prevIndex]->size(), steps[nextIndex]->size());
  if (target == 1 && prevIndex != stepsIndex) 
  {
    realIndex = prevIndex;
  }
  else 
  if (target == 2 && nextIndex != stepsIndex) 
  {
    realIndex = nextIndex;
  }
  steps[realIndex]->push_back(info);
  info->Shift(time, realIndex);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool InstanceUpdater::UpdateInstance(InstanceInfo* instance, const NHPTimer::STime& currentTime, const NHPTimer::STime& lateTime)
{
  NI_PROFILE_HEAVY_FUNCTION;
  bool result = false;
  StrongMT<ITimedInstance> & timedInstance = instance->Get();
  if ( timedInstance )
  {
    NHPTimer::STime startTime = 0;
    if (logLagTime > 0)
    {
      NHPTimer::GetTime(startTime);
    }

    int delta = timedInstance->Step(-NHPTimer::Time2Milliseconds(lateTime));

    if (logLagTime > 0)
    {
      NHPTimer::STime stopTime;
      NHPTimer::GetTime(stopTime);
      int stepTime = NHPTimer::Time2Milliseconds(stopTime - startTime);
      if (stepTime > logLagTime)
      {
        localLog(logStream, NLogg::LEVEL_WARNING).Trace(
          "TimeSlicer: Instance step lag detected (id=%d ptr=%p threadIndex=%d stepTime=%d logLagTime=%d)",
            instance->instanceId, instance->instancePtr, threadIndex, stepTime, logLagTime);
      }
    }

    if (delta >= 0)
    {
      ScheduleInstance(instance, currentTime+NHPTimer::Milliseconds2Time(delta), false);
      result = true;
    }
    else
    {
      localLog(logStream, NLogg::LEVEL_DEBUG).Trace(
        "TimeSlicer: Stop instance (id=%d ptr=%p threadIndex=%d)", instance->instanceId, instance->instancePtr, threadIndex);
    }
  }
  else
  {
    localLog(logStream, NLogg::LEVEL_DEBUG).Trace(
      "TimeSlicer: Forget instance (id=%d ptr=%p threadIndex=%d)", instance->instanceId, instance->instancePtr, threadIndex);
  }
  if (!result)
  {
    instance->Clear();
  }
  return result;
}

}