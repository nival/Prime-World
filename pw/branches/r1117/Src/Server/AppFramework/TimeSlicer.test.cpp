//!Component('Server/AppFramework/TimeSlicer')
#include <System/stdafx.h>
#include <cxxtest/TestSuite.h>
#include <System/ThreadHelpers.h>

// T класс наследован от IObjectBase
// убрать лишнии аллокации через rvector
#include "TimeSlicer.h"

namespace test
{
struct MockInstance : AppFramework::ITimedInstance, BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( MockInstance, AppFramework::ITimedInstance, BaseObjectMT );
public:
  enum InstanceStatus
  {
    Running,
    Stopping,
    Stopped,
  };
  MockInstance(int _step, int _delay=0):step(_step), delay(_delay), status(Running) {}

  virtual int GetId() const { return 0; }

  virtual int Step(int delta)
  {
    threading::MutexLock lock(locker);
    NI_ASSERT(status != Stopped, "Updating stopped instance");
    deltas.push_back(delta);
    NHPTimer::STime time;
    NHPTimer::GetTime(time);
    times.push_back(time);
    if (delay > 0)
    {
      threading::Sleep(delay);
    }
    if (status == Stopping)
    {
      status = Stopped;
    }
    return step;
  }

  void Clear()
  {
    threading::MutexLock lock(locker);
    deltas.clear();
    times.clear();
  }

  void Stop()
  {
    threading::MutexLock lock(locker);
    delay = 0;
    step = -1;
    deltas.clear();
    times.clear();
    status = Stopping;
  }
  MockInstance() {}
  int step;
  int delay;
  nstl::vector<int> deltas;
  nstl::vector<NHPTimer::STime> times;
  threading::Mutex locker;
  InstanceStatus status;
};

struct CallInfo
{
  NHPTimer::STime time;
  int id;
};

int CompareCallInfo(const void* p0, const void* p1)
{
  const CallInfo* c0 = (CallInfo*)p0;
  const CallInfo* c1 = (CallInfo*)p1;
  if (c0->time < c1->time)
  {
    return -1;
  }
  if (c0->time > c1->time)
  {
    return 1;
  }
  return 0;
}

}

struct Test_Runner : public CxxTest::TestSuite
{
  void FillCalls(nstl::vector<test::CallInfo>& calls, test::MockInstance& instance, int id)
  {
    for (int i=0;i<instance.times.size();++i)
    {
      test::CallInfo info = { instance.times[i], id };
      calls.push_back(info);
    }
    qsort(calls.begin(), calls.size(), sizeof(test::CallInfo), test::CompareCallInfo);
  }

  void OutputCalls(const nstl::vector<test::CallInfo>& calls)
  {
    for (int i=0;i<calls.size();++i)
    {
      printf("%f %d\n", NHPTimer::Time2Seconds(calls[i].time), calls[i].id);
    }
  }

  void setUp()
  {
    NHPTimer::Init();
    savedTimerResolution = AppFramework::SetTimerResolution(1, true);
  }

  void tearDown()
  {
    AppFramework::SetTimerResolution(savedTimerResolution, false);
  }

  int savedTimerResolution;

  void test_SimpleSmall()
  {
    AppFramework::InstancesPublicQueue queue(128);
    {
      NHPTimer::STime currentTime;
      NHPTimer::GetTime(currentTime);
      AppFramework::InstanceStatisticsMap stats;
      AppFramework::InstanceUpdater u(queue, NHPTimer::Milliseconds2Time(1), 0, stats, 0, 300);

      StrongMT<test::MockInstance> instance = new test::MockInstance(5);
      AppFramework::InstanceInfo* info = new AppFramework::InstanceInfo;
      info->Set(instance);
      queue.enqueue(info);

      int sleepInMs;

      TS_ASSERT_EQUALS(0, u.Update(currentTime));
      TS_ASSERT_EQUALS(0, instance->deltas.size());
      TS_ASSERT_EQUALS(1, u.GetCount());

      sleepInMs = u.Update(currentTime);
      TS_ASSERT_EQUALS(1, sleepInMs);
      TS_ASSERT_EQUALS(0, instance->deltas.size());

      currentTime += NHPTimer::Milliseconds2Time(sleepInMs);
      sleepInMs = u.Update(currentTime);
      TS_ASSERT_EQUALS(5, sleepInMs);
      TS_ASSERT_EQUALS(1, instance->deltas.size());
    }
    ClearQueue(queue);
  }

  void test_Simple()
  {
    AppFramework::InstancesPublicQueue queue(128);
    {
      NHPTimer::STime currentTime;
      NHPTimer::GetTime(currentTime);
      AppFramework::InstanceStatisticsMap stats;
      AppFramework::InstanceUpdater u(queue, NHPTimer::Milliseconds2Time(1), 0, stats, 0, 300);

      StrongMT<test::MockInstance> instance = new test::MockInstance(100);
      AppFramework::InstanceInfo* info = new AppFramework::InstanceInfo;
      info->Set(instance);
      queue.enqueue(info);

      int sleepInMs;

      TS_ASSERT_EQUALS(0, u.Update(currentTime));
      TS_ASSERT_EQUALS(0, instance->deltas.size());
      TS_ASSERT_EQUALS(1, u.GetCount());

      currentTime += NHPTimer::Milliseconds2Time(1); // just for case
      sleepInMs = u.Update(currentTime);
      TS_ASSERT_EQUALS(20, sleepInMs);
      TS_ASSERT_EQUALS(1, instance->deltas.size());

      sleepInMs = u.Update(currentTime);
      TS_ASSERT_EQUALS(20, sleepInMs);
      TS_ASSERT_EQUALS(1, instance->deltas.size());

      currentTime += NHPTimer::Milliseconds2Time(sleepInMs);
      sleepInMs = u.Update(currentTime);
      TS_ASSERT_DELTA(20, sleepInMs, 1);
      TS_ASSERT_EQUALS(1, instance->deltas.size());

      currentTime += NHPTimer::Milliseconds2Time(sleepInMs);
      sleepInMs = u.Update(currentTime);
      TS_ASSERT_EQUALS(20, sleepInMs);
      TS_ASSERT_EQUALS(1, instance->deltas.size());
      TS_ASSERT_EQUALS(1, u.GetCount());

      currentTime += NHPTimer::Milliseconds2Time(sleepInMs);
      sleepInMs = u.Update(currentTime);
      TS_ASSERT_DELTA(20, sleepInMs, 1);
      TS_ASSERT_EQUALS(1, instance->deltas.size());

      instance->Stop();
      currentTime += NHPTimer::Milliseconds2Time(sleepInMs);
      sleepInMs = u.Update(currentTime);
      TS_ASSERT_DELTA(20, sleepInMs, 2);
      TS_ASSERT_EQUALS(0, instance->deltas.size());
      TS_ASSERT_EQUALS(1, u.GetCount());

      currentTime += NHPTimer::Milliseconds2Time(sleepInMs);
      sleepInMs = u.Update(currentTime);
      TS_ASSERT_EQUALS(20, sleepInMs);
      TS_ASSERT_EQUALS(1, instance->deltas.size());
      TS_ASSERT_EQUALS(0, u.GetCount());
    }
    ClearQueue(queue);
  }

  int ClearQueue(AppFramework::InstancesPublicQueue& queue)
  {
    int total = 0;
    while (true)
    {
      AppFramework::InstanceInfo* info;  
      if (queue.dequeue(info))
      {
        delete info;
        total ++;
      } 
      else
      {
        break;
      }
    }
    return total;
  }

  void test_TwoInstances()
  {
    AppFramework::InstancesPublicQueue queue(128);
    {
      NHPTimer::STime currentTime;
      NHPTimer::GetTime(currentTime);
      AppFramework::InstanceStatisticsMap stats;
      AppFramework::InstanceUpdater u(queue, NHPTimer::Milliseconds2Time(1), 0, stats, 0, 300);

      StrongMT<test::MockInstance> instance0 = new test::MockInstance(100);
      AppFramework::InstanceInfo* info0 = new AppFramework::InstanceInfo;
      info0->Set(instance0);
      queue.enqueue(info0);

      StrongMT<test::MockInstance> instance1 = new test::MockInstance(100);
      AppFramework::InstanceInfo* info1 = new AppFramework::InstanceInfo;
      info1->Set(instance1);
      queue.enqueue(info1);

      int sleepInMs;

      sleepInMs = u.Update(currentTime);
      TS_ASSERT_EQUALS(0, sleepInMs);
      TS_ASSERT_EQUALS(0, instance0->deltas.size());
      TS_ASSERT_EQUALS(0, instance1->deltas.size());
      TS_ASSERT_EQUALS(1, u.GetCount());

      currentTime += NHPTimer::Milliseconds2Time(sleepInMs);
      sleepInMs = u.Update(currentTime);
      TS_ASSERT_EQUALS(1, sleepInMs);
      TS_ASSERT_EQUALS(0, instance0->deltas.size());
      TS_ASSERT_EQUALS(0, instance1->deltas.size());
      TS_ASSERT_EQUALS(1, u.GetCount());

      currentTime += NHPTimer::Milliseconds2Time(sleepInMs);
      sleepInMs = u.Update(currentTime); // call
      TS_ASSERT_EQUALS(20, sleepInMs);
      TS_ASSERT_EQUALS(1, instance0->deltas.size());
      TS_ASSERT_EQUALS(0, instance1->deltas.size());
      TS_ASSERT_EQUALS(1, u.GetCount());

      currentTime += NHPTimer::Milliseconds2Time(sleepInMs); // +20
      sleepInMs = u.Update(currentTime);
      TS_ASSERT_EQUALS(0, sleepInMs);
      TS_ASSERT_EQUALS(1, instance0->deltas.size());
      TS_ASSERT_EQUALS(0, instance1->deltas.size()); 
      TS_ASSERT_EQUALS(2, u.GetCount());

      currentTime += NHPTimer::Milliseconds2Time(sleepInMs); // +0
      sleepInMs = u.Update(currentTime);
      TS_ASSERT_EQUALS(1, sleepInMs);
      TS_ASSERT_EQUALS(1, instance0->deltas.size());
      TS_ASSERT_EQUALS(0, instance1->deltas.size()); 
      TS_ASSERT_EQUALS(2, u.GetCount());

      currentTime += NHPTimer::Milliseconds2Time(sleepInMs); // +1
      sleepInMs = u.Update(currentTime);
      TS_ASSERT_EQUALS(20, sleepInMs);
      TS_ASSERT_EQUALS(1, instance0->deltas.size());
      TS_ASSERT_EQUALS(1, instance1->deltas.size()); 
      TS_ASSERT_EQUALS(2, u.GetCount());

      currentTime += NHPTimer::Milliseconds2Time(sleepInMs); // +20
      sleepInMs = u.Update(currentTime);
      TS_ASSERT_DELTA(20, sleepInMs, 1);
      TS_ASSERT_EQUALS(1, instance0->deltas.size());
      TS_ASSERT_EQUALS(1, instance1->deltas.size()); 
      TS_ASSERT_EQUALS(2, u.GetCount());

      currentTime += NHPTimer::Milliseconds2Time(sleepInMs); // +20
      sleepInMs = u.Update(currentTime);
      TS_ASSERT_DELTA(20, sleepInMs, 1);
      TS_ASSERT_EQUALS(1, instance0->deltas.size());
      TS_ASSERT_EQUALS(1, instance1->deltas.size()); 
      TS_ASSERT_EQUALS(2, u.GetCount());

      currentTime += NHPTimer::Milliseconds2Time(sleepInMs); // +20
      sleepInMs = u.Update(currentTime);
      TS_ASSERT_DELTA(20, sleepInMs, 1);
      TS_ASSERT_EQUALS(1, instance0->deltas.size());
      TS_ASSERT_EQUALS(1, instance1->deltas.size()); 
      TS_ASSERT_EQUALS(2, u.GetCount());

      currentTime += NHPTimer::Milliseconds2Time(sleepInMs); // +20
      sleepInMs = u.Update(currentTime);
      TS_ASSERT_DELTA(20, sleepInMs, 1);
      TS_ASSERT_EQUALS(2, instance0->deltas.size());
      TS_ASSERT_EQUALS(1, instance1->deltas.size()); 
      TS_ASSERT_EQUALS(2, u.GetCount());

      currentTime += NHPTimer::Milliseconds2Time(sleepInMs); // +20
      sleepInMs = u.Update(currentTime);
      TS_ASSERT_DELTA(1, sleepInMs, 1);
      TS_ASSERT_EQUALS(2, instance0->deltas.size());
      TS_ASSERT_EQUALS(1, instance1->deltas.size()); 
      TS_ASSERT_EQUALS(2, u.GetCount());

      currentTime += NHPTimer::Milliseconds2Time(sleepInMs); 
      sleepInMs = u.Update(currentTime);
      TS_ASSERT_DELTA(20, sleepInMs, 1);
      TS_ASSERT_EQUALS(2, instance0->deltas.size());
      TS_ASSERT_EQUALS(2, instance1->deltas.size()); 
      TS_ASSERT_EQUALS(2, u.GetCount());

      instance0->Stop();
      for (int i=0;i<3;++i)
      {
        currentTime += NHPTimer::Milliseconds2Time(sleepInMs);
        sleepInMs = u.Update(currentTime);
        TS_ASSERT_DELTA(20, sleepInMs, 1);
        TS_ASSERT_EQUALS(0, instance0->deltas.size());
        TS_ASSERT_EQUALS(2, instance1->deltas.size()); // should be 1
        TS_ASSERT_EQUALS(2, u.GetCount());
      }
      currentTime += NHPTimer::Milliseconds2Time(sleepInMs);
      sleepInMs = u.Update(currentTime);
      TS_ASSERT_DELTA(20, sleepInMs, 1);
      TS_ASSERT_EQUALS(1, instance0->deltas.size());
      TS_ASSERT_EQUALS(2, instance1->deltas.size()); // should be 1
      TS_ASSERT_EQUALS(1, u.GetCount());
    }
    ClearQueue(queue);
  }

  void test_Empty()
  {
    AppFramework::InstancesPublicQueue queue(128);
    NHPTimer::STime currentTime;
    NHPTimer::GetTime(currentTime);
    AppFramework::InstanceStatisticsMap stats;
    AppFramework::InstanceUpdater u(queue, NHPTimer::Milliseconds2Time(1), 0, stats, 0, 300);

    for (int i=0;i<10;++i)
    {
      int sleepInMs = u.Update(currentTime);
      TS_ASSERT_EQUALS(20, sleepInMs);

      currentTime += NHPTimer::Milliseconds2Time(sleepInMs);
    }
  }

  void test_Minimum()
  {
    TS_ASSERT_EQUALS(0, AppFramework::GetMinimum(0, 1, 2));
    TS_ASSERT_EQUALS(1, AppFramework::GetMinimum(55, 1, 2));
    TS_ASSERT_EQUALS(2, AppFramework::GetMinimum(55, 77, 2));
    TS_ASSERT_EQUALS(0, AppFramework::GetMinimum(0, 0, 2));
    TS_ASSERT_EQUALS(1, AppFramework::GetMinimum(55, 2, 2));
  }

  void test_Lag()
  {
    AppFramework::InstancesPublicQueue queue(128);
    {
      NHPTimer::STime currentTime;
      NHPTimer::GetTime(currentTime);
      AppFramework::InstanceStatisticsMap stats;
      AppFramework::InstanceUpdater u(queue, NHPTimer::Milliseconds2Time(1), 0, stats, 0, 300);

      StrongMT<test::MockInstance> instance = new test::MockInstance(100);
      AppFramework::InstanceInfo* info = new AppFramework::InstanceInfo;
      info->Set(instance);
      queue.enqueue(info);

      int sleepInMs = 0;

      while (0 == instance->deltas.size())
      {
        currentTime += NHPTimer::Milliseconds2Time(sleepInMs); 
        sleepInMs = u.Update(currentTime);
      }

      TS_ASSERT_EQUALS(1, instance->deltas.size());
      TS_ASSERT_EQUALS(1, u.GetCount());

      currentTime += NHPTimer::Milliseconds2Time(150);  // more than instance period
      sleepInMs = u.Update(currentTime);
      TS_ASSERT_EQUALS(20, sleepInMs);
      TS_ASSERT_EQUALS(2, instance->deltas.size());
      TS_ASSERT_DELTA(50, instance->deltas[1], 1);
    }
    ClearQueue(queue);
  }

  void test_LargeLag()
  {
    AppFramework::InstancesPublicQueue queue(128);
    {
      NHPTimer::STime currentTime;
      NHPTimer::GetTime(currentTime);
      AppFramework::InstanceStatisticsMap stats;
      AppFramework::InstanceUpdater u(queue, NHPTimer::Milliseconds2Time(1), 0, stats, 0, 300);

      StrongMT<test::MockInstance> instance = new test::MockInstance(100); 
      AppFramework::InstanceInfo* info = new AppFramework::InstanceInfo;
      info->Set(instance);
      queue.enqueue(info);

      int sleepInMs = 0;

      while (0 == instance->deltas.size())
      {
        currentTime += NHPTimer::Milliseconds2Time(sleepInMs); 
        sleepInMs = u.Update(currentTime);
      }

      TS_ASSERT_EQUALS(1, instance->deltas.size());
      TS_ASSERT_EQUALS(1, u.GetCount());

      currentTime += NHPTimer::Milliseconds2Time(1500);  // more than instance period
      sleepInMs = u.Update(currentTime);
      TS_ASSERT_EQUALS(20, sleepInMs);
      TS_ASSERT_EQUALS(2, instance->deltas.size());
      TS_ASSERT_DELTA(1400, instance->deltas[1], 1);

      for (int i=0;i<4;i++)
      {
        currentTime += NHPTimer::Milliseconds2Time(sleepInMs);  
        sleepInMs = u.Update(currentTime);
        TS_ASSERT_EQUALS(20, sleepInMs);
        TS_ASSERT_EQUALS(2, instance->deltas.size());
      }
      currentTime += NHPTimer::Milliseconds2Time(sleepInMs);  
      sleepInMs = u.Update(currentTime);
      TS_ASSERT_EQUALS(20, sleepInMs);
      TS_ASSERT_EQUALS(3, instance->deltas.size());
    }
    ClearQueue(queue);
  }

  void test_SameSchedulingIndex()
  {
    AppFramework::InstancesPublicQueue queue(128);
    {
      NHPTimer::STime currentTime;
      NHPTimer::GetTime(currentTime);
      AppFramework::InstanceStatisticsMap stats;
      AppFramework::InstanceUpdater u(queue, NHPTimer::Milliseconds2Time(1), 0, stats, 0, 300);

      StrongMT<test::MockInstance> instance = new test::MockInstance(0); //zero wait
      AppFramework::InstanceInfo* info = new AppFramework::InstanceInfo;
      info->Set(instance);
      queue.enqueue(info);

      int sleepInMs = 0;

      TS_ASSERT_EQUALS(0, u.Update(currentTime));
      TS_ASSERT_EQUALS(0, instance->deltas.size());
      TS_ASSERT_EQUALS(1, u.GetCount());

      currentTime += NHPTimer::Milliseconds2Time(sleepInMs);
      sleepInMs = u.Update(currentTime);
      TS_ASSERT_EQUALS(1, sleepInMs);
      TS_ASSERT_EQUALS(0, instance->deltas.size());

      currentTime += NHPTimer::Milliseconds2Time(sleepInMs);
      sleepInMs = u.Update(currentTime);
      TS_ASSERT_EQUALS(1, sleepInMs);
      TS_ASSERT_EQUALS(1, instance->deltas.size());
    }
    ClearQueue(queue);
  }

  void test_LaggingStatistics()
  {
    static const int instancesCount = 11;
    AppFramework::InstancesPublicQueue queue(2048);
    {
      NHPTimer::STime currentTime = 0;
      AppFramework::InstanceStatisticsMap stats;
      AppFramework::InstanceUpdater u(queue, NHPTimer::Milliseconds2Time(1), 0, stats, 0, 300);

      nstl::vector<StrongMT<test::MockInstance> > instances;
      nstl::vector<AppFramework::InstanceInfo*> infos;
      instances.reserve(instancesCount);
      infos.reserve(instancesCount);

      for (int i=0;i<instancesCount;++i)
      {
        StrongMT<test::MockInstance> instance = new test::MockInstance(100); 
        instances.push_back(instance);
        AppFramework::InstanceInfo* info = new AppFramework::InstanceInfo;
        info->Set(instance);
        queue.enqueue(info);
        infos.push_back(info);
      }
      while (u.GetCount() != instancesCount)
      {
        int sleepInMs = u.Update(currentTime);
        currentTime += NHPTimer::Milliseconds2Time(sleepInMs);
      }

      for (nstl::vector<AppFramework::InstanceInfo*>::iterator it=infos.begin();it!=infos.end();++it)
      {
        (*it)->Reset();
      }

      static const int cyclesCount = 32;
      for (int i=0;i<cyclesCount;++i)
      {
        int sleepInMs = u.Update(currentTime);
        currentTime += NHPTimer::Milliseconds2Time(sleepInMs);
      }
      for (nstl::vector<AppFramework::InstanceInfo*>::iterator it=infos.begin();it!=infos.end();++it)
      {
        AppFramework::InstanceInfo* info = (*it);
        info->work.Finish();
        int totalLateMs = NHPTimer::Time2Milliseconds(info->late.averageValue);
        info->late.Finish();
        char buffer[256];
//        sprintf(buffer, "work: count=%d min=%d avg=%d max=%d\n", info->work.count, NHPTimer::Time2Milliseconds(info->work.minValue), NHPTimer::Time2Milliseconds(info->work.averageValue), NHPTimer::Time2Milliseconds(info->work.maxValue));
        sprintf(buffer, "late: total=%d count=%d min=%d avg=%d max=%d\n", totalLateMs, info->late.count, NHPTimer::Time2Milliseconds(info->late.minValue), NHPTimer::Time2Milliseconds(info->late.averageValue), NHPTimer::Time2Milliseconds(info->late.maxValue));
        //OutputDebugString(buffer);
      }
    }
    ClearQueue(queue);
  }

};

