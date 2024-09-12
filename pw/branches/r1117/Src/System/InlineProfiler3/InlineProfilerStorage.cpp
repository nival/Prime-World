#include "stdafx.h"
#include "InlineProfilerStorage.h"
#include "InlineProfilerTLD.h"
#include "InlineProfiler3CG.h"
#include "System/ThreadNames.h"


namespace profiler3
{

Storage::Storage() :
lastMeasureTime( 0 ), lastMeasuredTicks( 0 ),
startupTicks( 0 ),
initialized( false ),
timeFactor( 0 ),
nextEventId( 1 ),
nextThreadIndex( 1 ),
timelineLength( 0 ), dataFlushPeriod( 0 ),
pauseTime( 0 )
{
  lastMeasureTime = NHPTimer::GetScalarTime();
  lastMeasuredTicks = ThreadLocalData::GetCpuTickCount();

  startupTicks = lastMeasuredTicks;

  threading::Sleep( 100 );
  SetupTimeFactor( true );

  dataFlushPeriod = timeFactor;
}



Storage::~Storage()
{
}



ThreadLocalData * Storage::ProduceForCurrentThread()
{
  threading::MutexLock lock( mutex );

  ThreadLocalData * tld = new ThreadLocalData( nextThreadIndex, samplingSettings );
  ++nextThreadIndex;

  pair<TThreadsData::iterator, bool> result =
    threadsData.insert( TThreadsData::value_type( tld->ThreadId(), SThreadData() ) );

  assert( result.second ); //Trying to register TLD twice for single thread
  if ( !result.second )
    return tld;

  SThreadData & item = result.first->second;
  item.tld = tld;
  item.osThreadId = threading::CurrentThreadID();
  tld->SetStorage( this );

  return tld;
}



void Storage::Destruct( ThreadLocalData * tld )
{
  threading::MutexLock lock( mutex );

  tld->SetStorage( 0 );

  for ( TThreadsData::iterator it = threadsData.begin(); it != threadsData.end(); ++it )
    if ( it->second.tld == tld )
    {
      //It s a relatively harmless assert, but by design TLD have to be deleted by its own thread
      assert( it->second.osThreadId == threading::CurrentThreadID() ); //Destructing TLD not from their thread!

      //We are destroing only 'ThreadLocalData' object and leave 'threadsData' element
      //this is needed to provide UI with information about exited threads
      //They will be erased in CleanupDeadThreads()
      delete tld;
      it->second.tld = 0;
      return;
    }
  assert( !"Trying to deregister unknown TLD" );
}



void Storage::Setup( const SSettings & _settings )
{
  threading::MutexLock lock( mutex );
  timelineLength                            = _settings.timelineLength;
  dataFlushPeriod                           = _settings.dataFlushPeriod;
  samplingSettings.initialEventDataBuffer   = _settings.initialSamplingBuffer;
  samplingSettings.eventDataLimit           = _settings.samplingBufferLimit;
  samplingSettings.initialRootEvents        = _settings.initialRootEvents;
  samplingSettings.rootEventsLimit          = _settings.rootEventsLimit;
  samplingSettings.maxWorstRootEvents       = _settings.maxWorstRootEvents;
  initialized = true;
}



bool Storage::GetSettings( SSettings & _settings )
{
  threading::MutexLock lock( mutex );
  if ( !initialized )
    return false;
  _settings.timelineLength          = timelineLength;
  _settings.dataFlushPeriod         = dataFlushPeriod;
  _settings.initialSamplingBuffer   = samplingSettings.initialEventDataBuffer;
  _settings.samplingBufferLimit     = samplingSettings.eventDataLimit;
  _settings.initialRootEvents       = samplingSettings.initialRootEvents;
  _settings.rootEventsLimit         = samplingSettings.rootEventsLimit;
  _settings.maxWorstRootEvents      = samplingSettings.maxWorstRootEvents;
  return true;
}



bool Storage::Initialized() const
{
  threading::MutexLock lock( mutex );
  return initialized;
}



FTime Storage::TimelineLength()
{
  threading::MutexLock lock( mutex );
  return timelineLength;
}



void Storage::SetupTimeFactor( bool forced )
{
  const NHPTimer::FTime TimeMeasurePeriod = 1.0;

  NHPTimer::FTime now = NHPTimer::GetScalarTime();
  if ( forced || ( now >= lastMeasureTime + TimeMeasurePeriod ) )
  {
    TTime currentClock = ThreadLocalData::GetCpuTickCount();
    TTime ticksPassed = currentClock - lastMeasuredTicks;
    NHPTimer::FTime timePassed = now - lastMeasureTime;
    timeFactor = (FTime)ticksPassed / timePassed;

    lastMeasuredTicks = currentClock;
    lastMeasureTime = now;
  }
}



TEventId Storage::RegisterEvent( const char * name, const char * file, int line )
{
  threading::MutexLock lock( mutex );

  //Для успешной упаковки евентов в поток байт, id должен использовать только биты с 16 по 30 (исключая 31й и 0...15)
  assert( nextEventId < ThreadLocalData::MaxEventId ); //Too many events
  eventsTable[nextEventId] = SEventInfo( name, file, line );
  return nextEventId++;
}



const SEventInfo & Storage::GetEventInfo( TEventId eventId )
{
  threading::MutexLock lock( mutex );

  static SEventInfo zero( "<unknown>", "", 0 );
  TEvents::const_iterator it = eventsTable.find( eventId );
  assert( it != eventsTable.end() ); //Unknown profiler event id
  if ( it == eventsTable.end() )
    return zero;
  return it->second;
}



void Storage::FlushData( TThreadId threadId, SDataChunk & chunk, SSamplingSettings & updatedSettings )
{
  threading::MutexLock lock( mutex );

  TThreadsData::iterator it = threadsData.find( threadId );
  assert( it != threadsData.end() ); //Trying to flush data from unregistered thread
  if ( it == threadsData.end() )
    return;

  TThreadSamplingData & samplingData = it->second.samplingData;

  const bool enabled = it->second.enabled && !pauseTime;

  if ( !chunk.rootEvents.empty() && enabled )
  {
    SearchForWorstFrames( it->second.worstEvents, chunk );

    samplingData.push_back( SDataChunk() );
    samplingData.back().ExtractData( chunk );
  }

  //TODO: Recycle buffers here to reduce allocations
  CleanupSamplingData( samplingData );

  updatedSettings = samplingSettings;
  updatedSettings.dataFlushPeriodInTicks = dataFlushPeriod * timeFactor;
  if ( !enabled )
  {
    updatedSettings.initialEventDataBuffer = 0;
    updatedSettings.initialRootEvents = 0;
  }
}




FTime Storage::ProfilerTime( FTime * _timeFactor )
{
  threading::MutexLock lock( mutex );

  if ( pauseTime )
  {
    if ( _timeFactor )
      *_timeFactor = timeFactor;
    return pauseTime;
  }

  SetupTimeFactor( false );

  if ( _timeFactor )
    *_timeFactor = timeFactor;

  return ( ThreadLocalData::GetCpuTickCount() - startupTicks ) / timeFactor;
}



bool Storage::EnableSampling( TThreadId threadId, bool enable )
{
  threading::MutexLock lock( mutex );

  TThreadsData::iterator it = threadsData.find( threadId );
  if ( it == threadsData.end() )
    return false;

  SThreadData & threadData = it->second;
  threadData.enabled = enable;
  threadData.samplingData.clear();
  threadData.worstEvents.Clear();
  return true;
}



void Storage::EnableLiteMode( bool enabled )
{
  threading::MutexLock lock( mutex );
  samplingSettings.liteMode = enabled;
}



bool Storage::IsLiteModeEnabled()
{
  threading::MutexLock lock( mutex );
  return samplingSettings.liteMode;
}



void Storage::Pause( bool pause )
{
  threading::MutexLock lock( mutex );
  if ( pause )
    pauseTime = ProfilerTime( 0 ); //FIXME: setting 'pauseTime' itself changes the ProfilerTime() behavior
  else
    pauseTime = 0;
}



bool Storage::IsPaused()
{
  threading::MutexLock lock( mutex );
  return pauseTime ? true : false;
}



void Storage::SetMaxWorstEvents( int count )
{
  threading::MutexLock lock( mutex );
  samplingSettings.maxWorstRootEvents = Min( WorstRootEventsMax, count );
}



int Storage::GetMaxWorstEvents()
{
  threading::MutexLock lock( mutex );
  return samplingSettings.maxWorstRootEvents;
}



void Storage::CleanupSamplingData( TThreadSamplingData & data )
{
  TTime duration = 0;

  TTime timeline = timelineLength * timeFactor;

  TThreadSamplingData::iterator it = data.end();
  while ( it != data.begin() )
  {
    --it;

    if ( duration > timeline )
    {
      data.erase( data.begin(), it );
      return;
    }

    duration += it->duration;
  }
}



void Storage::SearchForWorstFrames( SWorstEventsSet & worstEvents, const SDataChunk & chunk )
{
  if ( samplingSettings.maxWorstRootEvents < (size_t)worstEvents.events.size() )
  {
    //We do not support decrease of worst events set, just clear all data
    worstEvents.Clear();
  }

  if ( !samplingSettings.maxWorstRootEvents )
      return;

  TTime bestWorstDuration = 0;
  if ( !worstEvents.events.empty() )
    bestWorstDuration = worstEvents.events[worstEvents.shortestEventIndex].internalDuration;

  for ( int i = 0; i < chunk.rootEvents.size(); ++i )
  {
    //Search the new events for worst events
    const SRootEvent & event = chunk.rootEvents[i];
    if ( bestWorstDuration )
      if ( event.duration <= bestWorstDuration )
        continue;

    AddEventToWorstSet( worstEvents, chunk, event );

    assert( !worstEvents.events.empty() );
    bestWorstDuration = worstEvents.events[worstEvents.shortestEventIndex].internalDuration;
  }
}



void Storage::AddEventToWorstSet( SWorstEventsSet & worstEvents, const SDataChunk & chunk, const SRootEvent & event )
{
  assert( samplingSettings.maxWorstRootEvents > 0 );
  assert( event.length );

  //Find not so bad event to replace
  size_t targetWorstEvent = 0;
  if ( (size_t)worstEvents.events.size() < samplingSettings.maxWorstRootEvents )
  {
    targetWorstEvent = worstEvents.events.size();
    worstEvents.events.push_back();
  }
  else
  {
    targetWorstEvent = worstEvents.shortestEventIndex;
    assert( event.duration > worstEvents.events[targetWorstEvent].internalDuration ); //Wrong shortest worst event
  }

  //Replace event and its data
  SSingleWorstEvent & target = worstEvents.events[targetWorstEvent];
  target.internalDuration = event.duration;
  target.id = event.id;
  target.samplingData.resize( event.length );
  assert( event.startOffset + event.length <= chunk.eventDataSize );
  memcpy( &target.samplingData[0], &chunk.eventBuffer[0] + event.startOffset, event.length );

  //Find out new 'shortestEventIndex'
  for ( int i = 0; i < worstEvents.events.size(); ++i )
    if ( i != worstEvents.shortestEventIndex )
      if ( worstEvents.events[i].internalDuration < worstEvents.events[worstEvents.shortestEventIndex].internalDuration )
        worstEvents.shortestEventIndex = i;

  //FIXME: extensive check
  for ( int i = 0; i < worstEvents.events.size(); ++i )
    if ( i != worstEvents.shortestEventIndex )
      assert( worstEvents.events[i].internalDuration > worstEvents.events[worstEvents.shortestEventIndex].internalDuration );
}



void Storage::GetThreadList( TThreadsInfo & info )
{
  threading::MutexLock lock( mutex );

  info.resize( threadsData.size() );

  int idx = 0;
  for ( TThreadsData::iterator it = threadsData.begin(); it != threadsData.end(); ++it, ++idx )
  {
    info[idx].threadId = it->first;
    info[idx].osThreadId = it->second.osThreadId;
    info[idx].samplingEnabled = it->second.enabled;
    info[idx].alive = it->second.tld ? true : false;
  }
}



void Storage::CleanupDeadThreads()
{
  threading::MutexLock lock( mutex );

  for ( TThreadsData::iterator it = threadsData.begin(); it != threadsData.end(); )
    if ( it->second.tld )
    {
      ++it;
      continue;
    }
    else
      it = threadsData.erase( it );
}



bool Storage::GetRootEvents( TThreadId threadId, TRootEventsDescription & events, int minId, int maxId )
{
  const int base = (int)events.size();

  {
    threading::MutexLock lock( mutex );

    TThreadsData::iterator data = threadsData.find( threadId );
    if ( data == threadsData.end() )
      return false;
    
    TThreadSamplingData & samplingData = data->second.samplingData;
    for ( TThreadSamplingData::iterator it = samplingData.begin(); it != samplingData.end(); ++it )
    {
      vector<SRootEvent> & rootEvents = it->rootEvents;
      if ( rootEvents.empty() )
        continue;

      //check rough conditions at first
      const int backId = rootEvents.back().id;
      if ( ( minId >= 0 ) && ( minId > backId ) )
        continue;

      const int frontId = rootEvents.front().id;
      if ( ( maxId >= 0 ) && ( maxId < frontId ) )
        continue;

      const int fromIdx = ( ( minId >= 0 ) && ( minId > frontId ) ) ? ( minId - frontId ) : 0;
      const int toIdx = ( ( maxId >= 0 ) && ( maxId < backId ) ) ? ( rootEvents.size() - ( backId - maxId ) ) : rootEvents.size();

      int len = toIdx - fromIdx;
      if ( !len )
        continue;

      events.resize( base + len );
      SRootEvent * src = &rootEvents[fromIdx];
      SRootEventDesc * dest = &events[base];
      for ( int i = len; i; --i, ++src, ++dest )
      {
        dest->id = src->id;
        dest->internalStartTime = src->startTime;
        dest->internalDuration = src->duration;
      }
    }
  }

  PostProcessNewRootEvents( events, base );
  return true;
}



void Storage::PostProcessNewRootEvents( TRootEventsDescription & events, int base )
{
  for ( int i = base; i < (int)events.size(); ++i )
  {
    SRootEventDesc & evt = events[i];
    evt.startTime = ( evt.internalStartTime - startupTicks ) / timeFactor;
    evt.duration = evt.internalDuration / timeFactor;
  }
}



bool Storage::AdjustRootEventsToTimeline( TThreadId threadId, TRootEventsDescription & events )
{
  int minId = events.empty() ? -1 : ( events.back().id + 1 );

  if ( !GetRootEvents( threadId, events, minId, -1 ) )
    return false;

  FTime timelineLength = TimelineLength(); //FIXME: two mutex locks in a row

  FTime now = ProfilerTime( 0 );
  FTime timelineBegin = now - timelineLength;

  if ( !events.empty() )
  {
    FTime dataBegin = events.front().startTime;
    if ( dataBegin > timelineBegin - timelineLength * 0.1 ) // 10% threshold to reduce vector<>::erase() calls
      return true;
  }

  int removeNumber = SearchRootEvents( events, timelineBegin );

  if ( removeNumber > 0 )
  {
    if ( removeNumber >= events.size() )
    {
      events.clear();
      return true;
    }
    events.erase( events.begin(), events.begin() + removeNumber );
  }

  return true;
}




bool Storage::GetRootEventBytes( TThreadId threadId, int eventId, vector<ni_detail::Byte> & buffer )
{
  if ( !threadId || eventId < 0 )
    return false;

  threading::MutexLock lock( mutex );

  TThreadsData::iterator data = threadsData.find( threadId );
  if ( data == threadsData.end() )
    return false;
  
  TThreadSamplingData & samplingData = data->second.samplingData;
  for ( TThreadSamplingData::iterator it = samplingData.begin(); it != samplingData.end(); ++it )
  {
    const SDataChunk & chunk = *it;

    if ( chunk.rootEvents.empty() )
      continue;

    if ( ( eventId < chunk.rootEvents.front().id ) || ( eventId > chunk.rootEvents.back().id ) )
      continue;

    const SRootEvent & event = chunk.rootEvents[eventId - chunk.rootEvents.front().id];

    assert( eventId == event.id ); //Wrong event

    buffer.resize( event.length, 0 );
    if ( event.length )
    {
      assert( event.startOffset + event.length <= chunk.eventDataSize );
      memcpy( &buffer[0], &chunk.eventBuffer[0] + event.startOffset, event.length );
    }
    return true;
  }

  return false;
}

namespace detail {

	struct SRE_Functor {

		bool operator() ( const SRootEventDesc & left, const SRootEventDesc & right ) const
		{
			return ( left.startTime + left.duration ) < ( right.startTime + right.duration );
		}

	};

}

int Storage::SearchRootEvents( const TRootEventsDescription & events, FTime time )
{
  //using binanry search to find root event with given time
  detail::SRE_Functor f;
  SRootEventDesc testee;
  memset( &testee, 0, sizeof( testee ) );
  testee.startTime = time;
  vector<SRootEventDesc>::const_iterator it = std::lower_bound( events.begin(), events.end(), testee, f );
  return it - events.begin();
}



bool Storage::SyncWorstEvents( TThreadId threadId, SWorstEventsSet & result )
{
  if ( !threadId )
    return false;

  threading::MutexLock lock( mutex );

  TThreadsData::iterator data = threadsData.find( threadId );
  if ( data == threadsData.end() )
    return false;
  
  const SWorstEventsSet & worstEvents = data->second.worstEvents;
  result.shortestEventIndex = worstEvents.shortestEventIndex;
  result.events.resize( worstEvents.events.size() );
  for ( int i = 0; i < result.events.size(); ++i )
  {
    const SSingleWorstEvent & src = worstEvents.events[i];
    SSingleWorstEvent & dest = result.events[i];
    if ( src.id == dest.id )
      continue;

    dest.id = src.id;
    dest.duration = src.internalDuration / timeFactor;
    dest.samplingData.resize( src.samplingData.size() );
    if ( !src.samplingData.empty() )
      memcpy( &dest.samplingData[0], &src.samplingData[0], src.samplingData.size() );
  }

  return true;
}



Strong<CallGraphNode> Storage::CollectCallGraph( const ni_detail::Byte * data, size_t dataSize, TTotalEventInfos & totals ) const
{
  return profiler3::CollectCallGraph( data, dataSize, totals, timeFactor );
}



void Storage::DumpCallgraph( CallGraphNode * node, const TTotalEventInfos & totals, IDumpCallback * callback, bool dumpFilenames ) const
{
  profiler3::DumpCallgraph( node, totals, callback, dumpFilenames );
}



void SDataChunk::ExtractData( SDataChunk & other )
{
  eventBuffer.swap( other.eventBuffer );
  rootEvents.swap( other.rootEvents );

  eventDataSize = other.eventDataSize;
  duration = other.duration;
}

} //namespace profiler3
