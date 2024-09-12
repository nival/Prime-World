#pragma once

namespace AppFramework
{
static const int REMOVE_FROM_QUEUE = -1;
struct ITimedInstance : IBaseInterfaceMT
{
  NI_DECLARE_CLASS_1(ITimedInstance, IBaseInterfaceMT);
  virtual int Step(int delta=0)=0;
  virtual int GetId() const =0;
};

struct InstanceStatistics : NonCopyable
{
  struct ValueAccumulator : NonCopyable
  {
    NHPTimer::STime minValue;
    NHPTimer::STime maxValue;
    NHPTimer::STime averageValue;
    int count;

    ValueAccumulator() { Reset(); }

    void Finish()
    {
      if (count > 0)
      {
        averageValue = double(averageValue)/count;
      }
    }

    void Reset()
    {
      count = 0;
      minValue = _I64_MAX;
      maxValue = _I64_MIN;
      averageValue = 0;
    }

    void Record(const NHPTimer::STime& ms)
    {
      if (count == 0 || ms < minValue) 
      {
        minValue = ms;
      }
      if (count == 0 || ms > maxValue) 
      {
        maxValue = ms;
      }
      averageValue += ms;
      count++;
    }

    void Add(const ValueAccumulator& other) 
    { 
      if (other.minValue < minValue)
      {
        minValue = other.minValue;
      }
      if (other.maxValue > maxValue)
      {
        maxValue = other.maxValue;
      }
      averageValue += other.averageValue;
      count += other.count;
    }
  };

  InstanceStatistics()
  {
    Init(_I64_MAX, false);
  }

  InstanceStatistics(NHPTimer::STime _longTime, bool _saveTimeStamp)
  {
    Init(_longTime, _saveTimeStamp);
  }

  void Init(NHPTimer::STime _longTime, bool _saveTimeStamp)
  {
    longTime = _longTime;
    saveTimeStamp = _saveTimeStamp;
    Reset();
  }

  void Record(const NHPTimer::STime& ms)
  {
    info.Record(ms);
  }

  int GetCount() const { return info.count; }

  const ValueAccumulator& Finish()
  {
    if (saveTimeStamp)
    {
      finishTimeStamp = GetTimeStamp();
    }
    info.Finish();
    return info;
  }

  void Reset()
  {
    info.Reset();
    savedTime = 0;
    instancesCount = 0;
    firstStartTimeStamp = 0;
    longTimeCount = 0;
  }

  void Start()
  {
    NHPTimer::GetTime(savedTime);
    if (saveTimeStamp && !firstStartTimeStamp)
    {
      firstStartTimeStamp = GetTimeStamp();
    }
  }

  void Start(NHPTimer::STime startTime)
  {
    savedTime = startTime;
    if (saveTimeStamp && !firstStartTimeStamp)
    {
      firstStartTimeStamp = GetTimeStamp();
    }
  }

  bool IsStarted() const { return savedTime!= 0; }

  NHPTimer::STime Stop()
  {
    NHPTimer::STime currentTime;
    NHPTimer::GetTime(currentTime);
    currentTime-=savedTime;
    Record(currentTime);
    if (currentTime > longTime)
    {
      ++longTimeCount;
    }
    savedTime = 0;
    return currentTime;
  }

  void Discard()
  {
    savedTime = 0;
  }

  void Add(const ValueAccumulator& other) 
  { 
    threading::MutexLock lock(locker);
    instancesCount++;
    info.Add(other); 
  } 

  time_t GetTimeStamp() const { return time(0); }
  time_t GetFirstStartTimeStamp() const { return firstStartTimeStamp; }
  time_t GetFinishTimeStamp() const { return finishTimeStamp; }

  void SetLongTime(NHPTimer::STime _longTime) { longTime = _longTime; }
  NHPTimer::STime GetLongTime() const { return longTime; }
  int GetLongTimeCount() const { return longTimeCount; }

  int GetInstancesCount() const { return instancesCount; }

private:
  ValueAccumulator info;
  NHPTimer::STime savedTime;
  time_t firstStartTimeStamp;
  time_t finishTimeStamp;
  NHPTimer::STime longTime;
  int longTimeCount;
  bool saveTimeStamp;
  threading::Mutex locker;
  int instancesCount;
};

}