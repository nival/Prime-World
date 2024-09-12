#ifndef SYSTEM_INLINEPROFILER3CONTROL_H_INCLUDED
#define SYSTEM_INLINEPROFILER3CONTROL_H_INCLUDED

#include <System/ported/thread_specific.h>

#include "InlineProfiler3.h"

namespace profiler3
{

struct SSettings
{
  FTime       timelineLength;
  unsigned    initialSamplingBuffer;
  unsigned    samplingBufferLimit;
  unsigned    initialRootEvents;
  unsigned    rootEventsLimit;
  unsigned    maxWorstRootEvents;
  FTime       dataFlushPeriod;

  SSettings() : 
  timelineLength( 10.0 ),
  initialSamplingBuffer( 64 * 1024 ),
  samplingBufferLimit( 1024 * 1024 ),
  initialRootEvents( 128 ),
  rootEventsLimit( 4096 ),
  maxWorstRootEvents( 3 ),
  dataFlushPeriod( 1.0 )
  {}
};



struct SEventInfo
{
  //FXIME: We could easily use 'const char *' for all strings in this structure is static in fact
  string    name;
  string    file;
  int       line;

  SEventInfo() : line( 0 ) {}

  SEventInfo( const char * _name, const char * _file, int _line ) :
  name( _name ), file( _file ), line( _line )
  {}
};



typedef int TThreadId; //Internal one
typedef threading::thread_id_t TOsThreadId; //Common windows thread id


struct SThreadInfo
{
  TThreadId     threadId;
  TOsThreadId   osThreadId;
  bool          samplingEnabled;
  bool          alive;
  SThreadInfo() : threadId( 0 ), osThreadId( 0 ), samplingEnabled( false ), alive( true ) {}
};


typedef vector<SThreadInfo> TThreadsInfo;



struct SRootEventDesc
{
  int       id;
  union {
    TTime   internalStartTime; //for internal use
    FTime   startTime;
  };
  union {
    TTime   internalDuration; //for internal use
    FTime   duration;
  };
};

typedef vector<SRootEventDesc>  TRootEventsDescription;



struct SSingleWorstEvent
{
  int                       id;
  union {
    TTime                   internalDuration; //for internal use
    FTime                   duration;
  };
  vector<ni_detail::Byte>   samplingData;
  SSingleWorstEvent() : duration( 0 ) {}
};



struct SWorstEventsSet
{
  vector<SSingleWorstEvent>   events;
  int                         shortestEventIndex;
  void Clear() { events.clear(); shortestEventIndex = 0; }
  SWorstEventsSet() : shortestEventIndex( 0 ) {}
};



const static int WorstRootEventsMax = 16;


class CallGraphNode;
typedef map<TEventId, Strong<CallGraphNode> > TCallGraphNodes;



struct SCallGraphNodeData
{
  TEventId  eventId;
  FTime     span;
  FTime     meTime;
  unsigned  calls;
  bool      hasAllocsInfo;
  unsigned  allocs;
  int       allocsDelta, memoryDelta;
};



class CallGraphNode : public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_1( CallGraphNode, BaseObjectST );

public:
  explicit CallGraphNode( TEventId _eventId )
  {
    memset( &data, 0, sizeof( data ) );
    data.eventId = _eventId;
  }

  const SCallGraphNodeData & Data() const { return data; }

  const TCallGraphNodes & Subnodes() const { return subnodes; }

protected:
  SCallGraphNodeData  data;
  TCallGraphNodes subnodes;
};



struct STotalEventInfo
{
  int       calls;
  double    time;
  double    ownTime;
  bool      hasAllocsInfo;
  unsigned  allocs;
  int       allocsDelta, memoryDelta;

  STotalEventInfo() : calls( 0 ), time( 0 ), ownTime( 0 ), hasAllocsInfo( false ), allocs( 0 ), allocsDelta( 0 ), memoryDelta( 0 ) {}
};

typedef map<TEventId, STotalEventInfo>  TTotalEventInfos;



_interface IDumpCallback
{
  virtual void DumpLine( const char * str ) = 0;
};


_interface IProfilerControl
{
  virtual void Setup( const SSettings & _settings ) = 0;
  virtual bool GetSettings( SSettings & _settings ) = 0;

  virtual bool  Initialized() const = 0;
  virtual FTime TimelineLength() = 0;

  virtual const SEventInfo & GetEventInfo( TEventId eventId ) = 0;

  virtual FTime ProfilerTime( FTime * _timeFactor = 0 ) = 0;
  virtual bool EnableSampling( TThreadId threadId, bool enable ) = 0;

  virtual void EnableLiteMode( bool enabled ) = 0;
  virtual bool IsLiteModeEnabled() = 0;

  virtual void Pause( bool pause ) = 0;
  virtual bool IsPaused() = 0;

  virtual void SetMaxWorstEvents( int count ) = 0;
  virtual int GetMaxWorstEvents() = 0;

  virtual void GetThreadList( TThreadsInfo & info ) = 0;
  virtual void CleanupDeadThreads() = 0;
  virtual bool GetRootEvents( TThreadId threadId, /*in-out*/ TRootEventsDescription & events, int minId, int maxId ) = 0;
  virtual bool AdjustRootEventsToTimeline( TThreadId threadId, /*in-out*/ TRootEventsDescription & events ) = 0;
  virtual bool GetRootEventBytes( TThreadId threadId, int eventId, vector<ni_detail::Byte> & buffer ) = 0;

  virtual int SearchRootEvents( const TRootEventsDescription & events, FTime time ) = 0;

  virtual bool SyncWorstEvents( TThreadId threadId, SWorstEventsSet & result ) = 0;

  virtual Strong<CallGraphNode> CollectCallGraph( const ni_detail::Byte * data, size_t dataSize, TTotalEventInfos & totals ) const = 0;
  virtual void DumpCallgraph( CallGraphNode * node, const TTotalEventInfos & totals, IDumpCallback * callback, bool dumpFilenames ) const = 0;
};


IProfilerControl * GetControl();

} //namespace profiler3

#endif //SYSTEM_INLINEPROFILER3CONTROL_H_INCLUDED
