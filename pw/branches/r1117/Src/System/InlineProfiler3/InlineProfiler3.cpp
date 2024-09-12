#include "stdafx.h"
#include "InlineProfiler3.h"

#include "InlineProfilerTLD.h"
#include "InlineProfilerStorage.h"
#include "System/ThreadNames.h"
#include "System/TSS.h"


namespace profiler3
{

static nival::TSS_key_type s_tlsIndex = 0;

static void ProfilerAllocCallback( int allocIndex, size_t size );
static void ProfilerFreeCallback( int allocIndex, size_t size );

struct SAutoInitilizer
{
  SAutoInitilizer()
  {
    ( void ) nival::TSS_create( s_tlsIndex );
#if !defined( NV_LINUX_PLATFORM )
    ni_detail::AddMemoryCallback( &ProfilerAllocCallback, true );
    ni_detail::AddMemoryCallback( &ProfilerFreeCallback, false );
#endif
  }

  ~SAutoInitilizer()
  {
    if ( s_tlsIndex )
    {
#if !defined( NV_LINUX_PLATFORM )
      ni_detail::RemoveMemoryCallback( &ProfilerAllocCallback, true );
      ni_detail::RemoveMemoryCallback( &ProfilerFreeCallback, false );
#endif
      ( void ) nival::TSS_free( s_tlsIndex );
    }
  }
} s_auto;


static Storage s_storage;

static __forceinline Storage & AccessStorage()
{
  return s_storage;
}



IProfilerControl * GetControl()
{
  return &( AccessStorage() );
}



void SetupThisThread( const char * debugThreadName )
{
#if defined( NV_WIN_PLATFORM )
  assert( s_tlsIndex ); //TLS is not ready yet!
#endif // defined( NV_WIN_PLATFORM )

  LPVOID prevValue = nival::TSS_get( s_tlsIndex );
  assert( !prevValue ); //TLS for this thread is already set
  if ( prevValue )
    return;

  ThreadLocalData * tld = AccessStorage().ProduceForCurrentThread();
  bool result = nival::TSS_set( s_tlsIndex, tld );
  result;
  assert( result ); //Failed to set thread local data

#if !defined( NV_LINUX_PLATFORM )
  if ( debugThreadName )
    threading::SetDebugThreadName( debugThreadName );
#endif
}



void CleanupThisThread()
{
#if defined( NV_WIN_PLATFORM )
  assert( s_tlsIndex ); //TLS is not ready yet!
#endif // defined( NV_WIN_PLATFORM )

  LPVOID ptr = nival::TSS_get( s_tlsIndex );
  assert( ptr ); //TLS for this thread is not set
  if ( !ptr )
    return;

  ThreadLocalData * tld = static_cast<ThreadLocalData *>( ptr );

  tld->FlushBeforeDestruction();

  bool result = nival::TSS_set( s_tlsIndex, 0 );
  result;
  assert( result ); //Failed to clear thread local data

  AccessStorage().Destruct( tld );
}



TEventId RegisterEvent( const char * name, const char * file, int line )
{
  return AccessStorage().RegisterEvent( name, file, line );
}



void StartEvent( TEventId eventId )
{
#if defined( NV_WIN_PLATFORM )
  assert( s_tlsIndex ); //TLS is not ready yet!
#endif // defined( NV_WIN_PLATFORM )

  void * ptr = nival::TSS_get( s_tlsIndex );
  if ( !ptr )
    return;

  ThreadLocalData * tld = static_cast<ThreadLocalData *>( ptr );
  tld->StartEvent<ThreadLocalData::SNormalEventPolicyTag>( eventId );
}



void FinishEvent( TEventId eventId )
{
#if defined( NV_WIN_PLATFORM )
  assert( s_tlsIndex ); //TLS is not ready yet!
#endif // defined( NV_WIN_PLATFORM )

  void * ptr = nival::TSS_get( s_tlsIndex );
  if ( !ptr )
    return;

  ThreadLocalData * tld = static_cast<ThreadLocalData *>( ptr );
  tld->FinishEvent<ThreadLocalData::SNormalEventPolicyTag>( eventId );
}



void StartMemoryEvent( TEventId eventId )
{
#if defined( NV_WIN_PLATFORM )
  assert( s_tlsIndex ); //TLS is not ready yet!
#endif // defined( NV_WIN_PLATFORM )

  void * ptr = nival::TSS_get( s_tlsIndex );
  if ( !ptr )
    return;

  ThreadLocalData * tld = static_cast<ThreadLocalData *>( ptr );
  tld->StartEvent<ThreadLocalData::SMemoryEventPolicyTag>( eventId );
}



void FinishMemoryEvent( TEventId eventId )
{
#if defined( NV_WIN_PLATFORM )
  assert( s_tlsIndex ); //TLS is not ready yet!
#endif // defined( NV_WIN_PLATFORM )

  void * ptr = nival::TSS_get( s_tlsIndex );
  if ( !ptr )
    return;

  ThreadLocalData * tld = static_cast<ThreadLocalData *>( ptr );
  tld->FinishEvent<ThreadLocalData::SMemoryEventPolicyTag>( eventId );
}



void StartEavyEvent( TEventId eventId )
{
#if defined( NV_WIN_PLATFORM )
  assert( s_tlsIndex ); //TLS is not ready yet!
#endif // defined( NV_WIN_PLATFORM )

  void * ptr = nival::TSS_get( s_tlsIndex );
  if ( !ptr )
    return;

  ThreadLocalData * tld = static_cast<ThreadLocalData *>( ptr );

  if ( tld->LiteModeOn() )
    return;

  tld->StartEvent<ThreadLocalData::SNormalEventPolicyTag>( eventId );
}



void FinishEavyEvent( TEventId eventId )
{
#if defined( NV_WIN_PLATFORM )
  assert( s_tlsIndex ); //TLS is not ready yet!
#endif // defined( NV_WIN_PLATFORM )

  void * ptr = nival::TSS_get( s_tlsIndex );
  if ( !ptr )
    return;

  ThreadLocalData * tld = static_cast<ThreadLocalData *>( ptr );

  if ( tld->LiteModeOn() )
    return;

  tld->FinishEvent<ThreadLocalData::SNormalEventPolicyTag>( eventId );
}



static void ProfilerAllocCallback( int allocIndex, size_t size )
{
#if defined( NV_WIN_PLATFORM )
  assert( s_tlsIndex ); //TLS is not ready yet!
#endif // defined( NV_WIN_PLATFORM )

  void * ptr = nival::TSS_get( s_tlsIndex );
  if ( !ptr )
    return;

  ThreadLocalData * tld = static_cast<ThreadLocalData *>( ptr );

  tld->RegisterAlloc( allocIndex, size );
}



static void ProfilerFreeCallback( int allocIndex, size_t size )
{
#if defined( NV_WIN_PLATFORM )
  assert( s_tlsIndex ); //TLS is not ready yet!
#endif // defined( NV_WIN_PLATFORM )

  void * ptr = nival::TSS_get( s_tlsIndex );
  if ( !ptr )
    return;

  ThreadLocalData * tld = static_cast<ThreadLocalData *>( ptr );

  tld->RegisterFree( allocIndex, size );
}

} //namespace profiler3
