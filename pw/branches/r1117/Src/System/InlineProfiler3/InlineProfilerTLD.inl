namespace profiler3
{

__forceinline
ThreadLocalData::ThreadLocalData( TThreadId _threadId, const SSamplingSettings & _settings ) :
threadId( _threadId ),
storage( 0 ),
currentEventLevel( 0 ),
eventBufferSize( 0 ),
rootEventId( 1 ),
rootEventStart( 0 ),
lastDataFlush( 0 ),
allocs( 0 ), allocsDelta( 0 ), memoryDelta( 0 ),
settings( _settings )
{
  SetupBuffers();

  lastDataFlush = GetCpuTickCount();
}



inline
void ThreadLocalData::FlushBeforeDestruction()
{
  NI_ASSERT( !currentEventLevel, "Destroing thread in the middle of root event" );

  TTime t = GetCpuTickCount();
  FlushData( t );
}

__forceinline
TTime ThreadLocalData::GetCpuTickCount()
{
  TTime register result;
#if defined( NV_WIN_PLATFORM )
  __asm {
    rdtsc
    mov DWORD PTR result, eax
    mov DWORD PTR result[4], edx
  };
#elif defined( NV_LINUX_PLATFORM )  
  __asm__ __volatile__ ("rdtsc" : "=A" (result) );
#endif
  return result;
}

template<typename TEventPolicyTag>
__forceinline
void ThreadLocalData::StartEvent( int eventId )
{
  //Disabled case
  if ( !eventBufferSize )
  {
    ++currentEventLevel;
    return;
  }

  TTime t = GetCpuTickCount();

  if ( !currentEventLevel )
    StartRootEvent( eventId, t );
  ++currentEventLevel;

  StartEventPolicy<TEventPolicyTag>( eventId, t );
}



template<typename TEventPolicyTag>
__forceinline
void ThreadLocalData::FinishEvent( int eventId )
{
  //Disabled case
  if ( !eventBufferSize )
  {
    --currentEventLevel;
    if ( !currentEventLevel )
      DisabledFinishRootEvent( eventId );
    return;
  }

  TTime t = GetCpuTickCount();

  FinishEventPolicy<TEventPolicyTag>( eventId, t );

  --currentEventLevel;
  if ( !currentEventLevel )
    FinishRootEvent( eventId, t );
}



__forceinline
void ThreadLocalData::WriteEventInternal( const int eventId, const ni_detail::UInt64 eventCode, const  TTime t )
{
  const size_t size = 8;

  if ( data.eventDataSize + size > eventBufferSize )
  {
    eventBufferSize *= 2;
    data.eventBuffer.resize( eventBufferSize );
    NI_ASSERT( data.eventDataSize + size <= eventBufferSize, "" );
  }

  ni_detail::Byte * dest = &data.eventBuffer[0] + data.eventDataSize;

  TTime start = t - rootEventStart;

  //We assume that time is only occupies lower 6 bytes of 'start' (it is enough to store 3.2 GHz CPU ticks for 24h)
  //Also that eventId is only occupies bits 0...14
  ni_detail::UInt64 chunk = (ni_detail::UInt64)start | eventCode | ((ni_detail::UInt64)eventId << EventId_ROLL );
  *(ni_detail::UInt64 *)dest = chunk;

  data.eventDataSize += size;
}



__forceinline
void ThreadLocalData::StartRootEvent( int eventId, TTime t )
{
  data.rootEvents.push_back( SRootEvent() );
  SRootEvent & root = data.rootEvents.back();
  root.id = rootEventId++;
  root.startOffset = data.eventDataSize;
  root.startTime = t;

  NI_ASSERT( !rootEventStart, "" );
  rootEventStart = t;

  allocs = 0;
  allocsDelta = 0;
  memoryDelta = 0;
}



__forceinline
void ThreadLocalData::FinishRootEvent( int eventId, TTime t )
{
  NI_ASSERT( rootEventStart, "" );
  TTime duration = ( t >= rootEventStart ) ? ( t - rootEventStart ) : 0; //Condition to circumvent AMD multicore clock
  rootEventStart = 0;

  NI_ASSERT( !data.rootEvents.empty(), "" );
  SRootEvent & root = data.rootEvents.back();
  root.length = data.eventDataSize - root.startOffset;
  root.duration = duration;

  if ( t >= lastDataFlush + settings.dataFlushPeriodInTicks )
    FlushData( t );
  else if ( ( data.eventDataSize >= settings.eventDataLimit ) && ( (size_t)data.rootEvents.size() >= settings.rootEventsLimit ) )
    FlushData( t );
}



__forceinline
void ThreadLocalData::DisabledFinishRootEvent( int eventId )
{
  TTime t = GetCpuTickCount();
  if ( t >= lastDataFlush + settings.dataFlushPeriodInTicks )
  {
    lastDataFlush = t;

    //Flush empty buffer and get updated sampling settings
    storage->FlushData( threadId, data, settings );

    SetupBuffers();
  }
}



__forceinline
void ThreadLocalData::WriteMemStatus()
{
  const size_t size = 12;

  if ( data.eventDataSize + size > eventBufferSize )
  {
    eventBufferSize *= 2;
    data.eventBuffer.resize( eventBufferSize );
    NI_ASSERT( data.eventDataSize + size <= eventBufferSize, "" );
  }

  ni_detail::UInt32 * dest = (ni_detail::UInt32 *)( &data.eventBuffer[0] + data.eventDataSize );
  dest[0] = allocs;
  dest[1] = allocsDelta;
  dest[2] = memoryDelta;

  data.eventDataSize += size;
}



inline
void ThreadLocalData::FlushData( TTime t )
{
  data.duration = t - lastDataFlush;

  storage->FlushData( threadId, data, settings );

  lastDataFlush = t;

  SetupBuffers();
}



inline
void ThreadLocalData::SetupBuffers()
{
  eventBufferSize = settings.initialEventDataBuffer;

  //FIXME: We are not recyclyng buffers yet, so this code is unnecessary
  //if ( !eventBufferSize )
  //{
  //  
  //  //Force STL vectors to deallocate
  //  vector<ni_detail::Byte> emptyBuffer;
  //  vector<SRootEvent> emptyRootEvents;
  //  data.eventBuffer.swap( emptyBuffer );
  //  data.rootEvents.swap( emptyRootEvents );
  //}

  data.eventDataSize = 0;
  data.duration = 0;
  data.eventBuffer.clear();
  data.eventBuffer.resize( eventBufferSize );

  data.rootEvents.clear();
  data.rootEvents.reserve( settings.initialRootEvents );
}



__forceinline void ThreadLocalData::RegisterAlloc( int allocIndex, size_t size )
{
  ++allocs;
  ++allocsDelta;
  memoryDelta += (ni_detail::SInt32)size;
}



__forceinline void ThreadLocalData::RegisterFree( int allocIndex, size_t size )
{
  --allocsDelta;
  memoryDelta -= (ni_detail::SInt32)size;
}

} //namespace profiler3
