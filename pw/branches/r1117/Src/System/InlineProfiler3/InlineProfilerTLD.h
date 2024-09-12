#ifndef INLINEPROFILERTLD_H_INCLUDED
#define INLINEPROFILERTLD_H_INCLUDED

#include "InlineProfilerStorage.h"

namespace profiler3
{

class Storage;

class ThreadLocalData : NonCopyable
{
public:
  const static TEventId           MaxEventId              = 0x4000;
  const static ni_detail::UInt64  EventId_MASK            = 0x3fff000000000000;
  const static size_t             EventId_ROLL            = 48;

  const static ni_detail::UInt64  EventCode_Start         = 0x8000000000000000;
  const static ni_detail::UInt64  EventCode_Finish        = 0x0000000000000000;
  const static ni_detail::UInt64  EventCode_StartWithMem  = 0x4000000000000000;
  const static ni_detail::UInt64  EventCode_FinishWithMem = 0xC000000000000000;
  const static ni_detail::UInt64  EventCode_MASK          = 0xC000000000000000;
  const static ni_detail::UInt64  EventCode_TIME_MASK     = 0x0000ffffffffffff;


  ThreadLocalData( TThreadId _threadIndex, const SSamplingSettings & _settings );

  TThreadId ThreadId() const { return threadId; }

  void SetStorage( Storage * _storage ) { storage = _storage; }

  void FlushBeforeDestruction();

  __forceinline static TTime GetCpuTickCount();

  struct SNormalEventPolicyTag {};
  struct SMemoryEventPolicyTag {};

  template<typename TEventPolicyTag>
  __forceinline void StartEvent( int eventId );

  template<typename TEventPolicyTag>
  __forceinline void FinishEvent( int eventId );

  __forceinline void RegisterAlloc( int allocIndex, size_t size );
  __forceinline void RegisterFree( int allocIndex, size_t size );

  __forceinline bool LiteModeOn() const { return settings.liteMode; }

private:
  const TThreadId           threadId;
  Storage *                 storage;
  SDataChunk                data;
  size_t                    currentEventLevel;
  size_t                    eventBufferSize;
  int                       rootEventId;
  TTime                     rootEventStart;

  TTime                     lastDataFlush;

  //Memory statistics
  ni_detail::UInt32         allocs;
  ni_detail::SInt32         allocsDelta;
  ni_detail::SInt32         memoryDelta;

  SSamplingSettings         settings;

  __forceinline void WriteEventInternal( const int eventId, const ni_detail::UInt64 eventCode, const TTime t );
  __forceinline void StartRootEvent( int eventId, TTime t );
  __forceinline void FinishRootEvent( int eventId, TTime t );
  __forceinline void DisabledFinishRootEvent( int eventId );
  __forceinline void WriteMemStatus();
  void FlushData( TTime t );
  void SetupBuffers();


  template<typename TEventPolicyTag> __forceinline void StartEventPolicy( const int eventId, const  TTime t );
  template<typename TEventPolicyTag> __forceinline void FinishEventPolicy( const int eventId, const  TTime t );

};

template<>
__forceinline
void ThreadLocalData::StartEventPolicy< ThreadLocalData::SNormalEventPolicyTag >( const int eventId, const TTime t )
{
  WriteEventInternal( eventId, EventCode_Start, t );
}

template<>
__forceinline
void ThreadLocalData::FinishEventPolicy< ThreadLocalData::SNormalEventPolicyTag >( const int eventId, const TTime t )
{
  WriteEventInternal( eventId, EventCode_Finish, t );
}

template<>
__forceinline
void ThreadLocalData::StartEventPolicy< ThreadLocalData::SMemoryEventPolicyTag >( const int eventId, const TTime t )
{
  WriteEventInternal( eventId, EventCode_StartWithMem, t );
  WriteMemStatus();
}

template<>
__forceinline
void ThreadLocalData::FinishEventPolicy< ThreadLocalData::SMemoryEventPolicyTag >( const int eventId, const TTime t )
{
  WriteEventInternal( eventId, EventCode_FinishWithMem, t );
  WriteMemStatus();
}

} //namespace profiler3

#include "InlineProfilerTLD.inl"

#endif //INLINEPROFILERTLD_H_INCLUDED
