#include "stdafx.h"

#include "ThreadNames.h"
#include "SyncPrimitives.h"

namespace threading
{

#ifndef _SHIPPING
struct SThreadNames
{
  typedef map<DWORD, string> TNames;
  Mutex     mutex;
  TNames    names;
};

// Fix NUM_TASK
static SThreadNames threadNames;
#endif

//Nice MSVS hack
#define MS_VC_EXCEPTION 0x406D1388

#pragma pack(push,8)
  typedef struct tagTHREADNAME_INFO
  {
    DWORD dwType; // Must be 0x1000.
    LPCSTR szName; // Pointer to name (in user addr space).
    DWORD dwThreadID; // Thread ID (-1=caller thread).
    DWORD dwFlags; // Reserved for future use, must be zero.
  } THREADNAME_INFO;
#pragma pack(pop)


static void ThrowVcException( const char* threadName )
{
#if defined( NV_WIN_PLATFORM )
  if ( !IsDebuggerPresent() )
    return;
  //moved to separete function for error workaround:
  //error C2712: Cannot use __try in functions that require object unwinding

#if !defined( _SHIPPING )
  THREADNAME_INFO info;
  info.dwType = 0x1000;
  info.szName = threadName;
  info.dwThreadID = ::GetCurrentThreadId();
  info.dwFlags = 0;

  __try
  {
    RaiseException( MS_VC_EXCEPTION, 0, sizeof(info)/sizeof(ULONG_PTR), (ULONG_PTR*)&info );
  }
  __except(EXCEPTION_EXECUTE_HANDLER)
  {
  }
#endif
#endif // defined( NV_WIN_PLATFORM )
}

void SetDebugThreadName( const char* threadName )
{
#ifndef _SHIPPING
  if ( !threadName )
    return;

  {
    SThreadNames & names = threadNames;
    MutexLock lock( names.mutex );
#if defined( NV_WIN_PLATFORM )
    names.names[ ::GetCurrentThreadId() ] = threadName;
#elif defined( NV_WIN_PLATFORM )
    names.names[ ::pthread_self() ] = threadName;
#endif
  }

  ThrowVcException( threadName );
#endif
}


const char * GetDebugThreadName( DWORD threadId )
{
#ifndef _SHIPPING
  SThreadNames & names = threadNames;

  MutexLock lock( names.mutex );

  SThreadNames::TNames::iterator it = names.names.find( threadId );
  if ( it != names.names.end() )
    return it->second.c_str();
#endif
  return "<Unknown>";
}

}; //namespace threading

