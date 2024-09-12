#ifndef PROFILER3UIDATA_H_INCLUDED
#define PROFILER3UIDATA_H_INCLUDED

#include "InlineProfiler3Control.h"

namespace profiler3ui
{

class SamplingData : public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_1( SamplingData, BaseObjectST );

public:
  struct SThreadInformation
  {
    profiler3::TOsThreadId osThreadId;
    bool    alive;
    bool    samplingEnabled;
    int     kernelTimePerc;
    int     userTimePerc;
    SThreadInformation() : osThreadId( 0 ), samplingEnabled( false ), alive( true ), kernelTimePerc( 0 ), userTimePerc( 0 ) {}
  };

  SamplingData();

  void Update();

  void EnableSampling( profiler3::TThreadId threadId, bool enable );
  bool GetThreadInfo( profiler3::TThreadId threadId, SThreadInformation & info ) const;
  void PopNewThreads( vector<profiler3::TThreadId> & result );

  const profiler3::SRootEventDesc * GetRootEvent( profiler3::TThreadId threadId, int eventId, profiler3::TOsThreadId & osThreadId ) const;
  const profiler3::TRootEventsDescription * GetNextEnabledThreadRootEvents( profiler3::TThreadId & threadId, profiler3::TOsThreadId & osThreadId ) const;
  unsigned GetEnabledThreadsCount() const;
  unsigned GetDeadThreadsCount() const;

  const profiler3::SWorstEventsSet * GetWorstEventsSet( profiler3::TThreadId threadId ) const;

  unsigned GetProcessMemoryUsage() const { return memoryUsage; }

private:
  struct SThread
  {
    bool              samplingEnabled;
    bool              alive;

    profiler3::TOsThreadId osThreadId;

    //timings
    NHPTimer::FTime   lastMeasureTime;
    NHPTimer::FTime   kernelTime;
    NHPTimer::FTime   userTime;
    int               kernelPerc, userPerc;

    //service flags
    bool              valid;
    bool              newThread;

    profiler3::TRootEventsDescription  rootEvents; //Внимание! Здесь id евентов идут уже НЕ подряд, могут быть пропуски

    profiler3::SWorstEventsSet worstEvents;

    SThread() : 
    samplingEnabled( false ),
    alive( true ),
    osThreadId( 0 ),
    lastMeasureTime( 0 ), kernelTime( 0 ), userTime( 0 ), kernelPerc( 0 ), userPerc( 0 ),
    valid( true ),
    newThread( true )
    {}
  };

  typedef map<profiler3::TThreadId, SThread> TThreads;

  profiler3::TThreadsInfo   threadsInfoBuffer;
  TThreads                  threads;

  NHPTimer::FTime           lastSyncOperation;

  unsigned                  memoryUsage;

  void SyncThreads();
  void UpdateThreadTimings();
  void UpdateMemoryUsage();
  void RetrieveRootEvents();
  void SyncWorstEvents();
};

} //namespace profiler3ui

#endif //PROFILER3UIDATA_H_INCLUDED
