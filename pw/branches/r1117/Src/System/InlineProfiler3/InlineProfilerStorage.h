#ifndef INLINEPROFILERSTORAGE_H_INCLUDED
#define INLINEPROFILERSTORAGE_H_INCLUDED

#include "InlineProfiler3Control.h"
#include "System/HPTimer.h"
#include "System/SyncPrimitives.h"

namespace profiler3
{

struct SSamplingSettings
{
  bool        liteMode;
  unsigned    initialEventDataBuffer;
  unsigned    eventDataLimit;
  unsigned    initialRootEvents;
  unsigned    rootEventsLimit;

  TTime       dataFlushPeriodInTicks;

  unsigned    maxWorstRootEvents;

  SSamplingSettings() :
  liteMode( true ),
  initialEventDataBuffer( 0 ), eventDataLimit( 0 ),
  initialRootEvents( 0 ), rootEventsLimit( 0 ),
  dataFlushPeriodInTicks( 0 ),
  maxWorstRootEvents( 0 )
  {}
};



struct SRootEvent
{
  int         id;
  unsigned    startOffset;
  unsigned    length;
  TTime       startTime;
  TTime       duration;

  SRootEvent()
  {
    memset( this, 0, sizeof( SRootEvent ) ); //NOTE: NO virtual functions!
  }
};



struct SDataChunk
{
  vector<ni_detail::Byte>   eventBuffer;
  vector<SRootEvent>        rootEvents;
  unsigned                  eventDataSize;
  TTime                     duration;

  SDataChunk() : eventDataSize( 0 ), duration( 0 ) {}
  void ExtractData( SDataChunk & other );
};





class ThreadLocalData;

class Storage : public IProfilerControl, NonCopyable
{
public:
  Storage();
  ~Storage();

  //Sampling interface

  ThreadLocalData * ProduceForCurrentThread();
  void Destruct( ThreadLocalData * tld );

  TEventId RegisterEvent( const char * name, const char * file, int line );
  void FlushData( TThreadId threadId, SDataChunk & chunk, SSamplingSettings & updatedSettings );

  //IProfilerControl
  virtual void Setup( const SSettings & _settings );
  virtual bool GetSettings( SSettings & _settings );
  virtual bool  Initialized() const;
  virtual FTime TimelineLength();
  virtual const SEventInfo & GetEventInfo( TEventId eventId );
  virtual FTime ProfilerTime( FTime * _timeFactor );
  virtual bool EnableSampling( TThreadId threadId, bool enable );
  virtual void EnableLiteMode( bool enabled );
  virtual bool IsLiteModeEnabled();
  virtual void Pause( bool pause );
  virtual bool IsPaused();
  virtual void SetMaxWorstEvents( int count );
  virtual int GetMaxWorstEvents();
  virtual void GetThreadList( TThreadsInfo & info );
  virtual void CleanupDeadThreads();
  virtual bool GetRootEvents( TThreadId threadId, /*in-out*/ TRootEventsDescription & events, int minId, int maxId );
  virtual bool AdjustRootEventsToTimeline( TThreadId threadId, /*in-out*/ TRootEventsDescription & events );
  virtual bool GetRootEventBytes( TThreadId threadId, int eventId, vector<ni_detail::Byte> & buffer );
  virtual int SearchRootEvents( const TRootEventsDescription & events, FTime time );
  virtual bool SyncWorstEvents( TThreadId threadId, SWorstEventsSet & result );
  virtual Strong<CallGraphNode> CollectCallGraph( const ni_detail::Byte * data, size_t dataSize, TTotalEventInfos & totals ) const;
  virtual void DumpCallgraph( CallGraphNode * node, const TTotalEventInfos & totals, IDumpCallback * callback, bool dumpFilenames ) const;

private:
  typedef map<TEventId, SEventInfo> TEvents;

  typedef list<SDataChunk> TThreadSamplingData;

  struct SThreadData
  {
    ThreadLocalData *   tld;
    TOsThreadId         osThreadId;
    TThreadSamplingData samplingData;
    bool                enabled;
    SWorstEventsSet     worstEvents;

    SThreadData() : tld( 0 ), osThreadId( 0 ), enabled( false ) {}
  };

  typedef map<TThreadId, SThreadData> TThreadsData;

  NHPTimer::FTime       lastMeasureTime;
  TTime                 lastMeasuredTicks;
  TTime                 startupTicks;
  threading::Mutex      mutex;
  bool                  initialized;
  FTime                 timeFactor;
  TEvents               eventsTable;
  TEventId              nextEventId;
  TThreadId             nextThreadIndex;
  TThreadsData          threadsData;

  SSamplingSettings     samplingSettings;
  FTime                 timelineLength;
  FTime                 dataFlushPeriod;

  FTime                 pauseTime;

  void SetupTimeFactor( bool forced );
  void CleanupSamplingData( TThreadSamplingData & data );
  void SearchForWorstFrames( SWorstEventsSet & worstEvents, const SDataChunk & chunk );
  void AddEventToWorstSet( SWorstEventsSet & worstEvents, const SDataChunk & chunk, const SRootEvent & event );
  void PostProcessNewRootEvents( TRootEventsDescription & events, int base );
};

} //namespace profiler3

#endif //INLINEPROFILERSTORAGE_H_INCLUDED
