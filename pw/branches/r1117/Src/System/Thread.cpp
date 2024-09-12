#include "stdafx.h"

#include "Thread.h"

namespace threading
{

#if defined( NV_WIN_PLATFORM )

thread_id_t CurrentThreadID()
{
  return ::GetCurrentThreadId();
}

#elif defined( NV_LINUX_PLATFORM )

thread_id_t CurrentThreadID()
{
  return ::pthread_self();
}

#endif

}

#if defined( NV_WIN_PLATFORM )

#include "CrashRptWrapper.h"
#include <process.h>


namespace threading
{


Thread::Thread( unsigned stackSize ) :
threadID( 0 ),
externalHandle( 0 ),
isRunning( true )
{
  externalHandle = (HANDLE)_beginthreadex( NULL, stackSize, WorkInternal, this, CREATE_SUSPENDED, (unsigned *)&threadID );
}


Thread::~Thread()
{
  if( externalHandle )
    CloseHandle( externalHandle );
  externalHandle = 0;
}


unsigned Thread::Resume()
{
  if( externalHandle )
    return ResumeThread( externalHandle );
  return (unsigned)(-1);
}


unsigned Thread::Suspend()
{
  if( externalHandle )
    return SuspendThread( externalHandle );
  return (unsigned)(-1);
}


bool Thread::Wait( unsigned timeout )
{
  if( externalHandle )
    return ( WaitForSingleObject( externalHandle, timeout ) == WAIT_OBJECT_0 );

  return true;
}


void Thread::Terminate( unsigned int exitCode )
{ 
  if( externalHandle )
    TerminateThread( externalHandle, exitCode );
  externalHandle = 0;
}


void Thread::SetPriority( int priority )
{
  if( externalHandle )
    SetThreadPriority( externalHandle, priority );
}


void Thread::Stop( bool waitForStop, int timeoutInMs )
{
  if( !externalHandle )
    return;
  
  DebugTrace( "Stopping thread. tid=%d, from_tid=%d, ptr=%08x", threadID, CurrentThreadID(), (void*)this );

  isRunning = false;
  if( waitForStop )
  {
    bool stopped = Wait( timeoutInMs );
    NI_ASSERT( stopped, "Thread termination timed out!" );
    if( !stopped )
      Terminate( 0 );
  }

  DebugTrace( "Thread stopped. tid=%d, ptr=%08x", threadID, (void*)this );

  //LOG_D(0) << "Thread (" << ::GetCurrentThreadId() << ") stopped";
}


void Thread::AsyncStop()
{
  DebugTrace( "Stopping thread (async). tid=%d, from_tid=%d, ptr=%08x", threadID, CurrentThreadID(), (void*)this );

  isRunning = false;
}


uint Thread::WorkInternal( void * param )
{
  CrashRptWrapper::InstallToCurrentThread();

  Thread * This = (Thread *)param;
  unsigned result = This->Work();

#ifdef LOG_THREAD_EXIT
  //Damn static starforce protection in client code, starforce.cpp:
  //static AsyncInvokerPriority g_invoker;
  //We cannot write logs here
  DevTrace( "Thread exit. tid=%d, ptr=%08x", CurrentThreadID(), (void*)This );
#endif

  CrashRptWrapper::UninstallFromCurrentThread();

  return result;
}



void Sleep( unsigned milliseconds )
{
  ::Sleep( milliseconds );
}



void ExitCurrentThread( unsigned exitCode )
{
  _endthreadex( exitCode );
}


} // namespace threading


#elif defined( NV_LINUX_PLATFORM )


#include "sleep.h"
#include "threading/thread.cpp"

namespace threading 
{

void Sleep( unsigned int milliseconds )
{
  nival::sleep( milliseconds );
}

void ExitCurrentThread( unsigned int exitCode )
{
  nival::thread_t * current_thread = nival::get_current_thread();

  if ( current_thread && current_thread->is_foreign_thread() == false ) {

    current_thread->set_execution_result( exitCode );
    current_thread->stop();

  }
}

/*
void SetDebugThreadName( const char * name )
{
  nival::get_current_thread()->set_thread_name( name );
}

const char * GetDebugThreadName( thread_id_t thread_id )
{
  return ( * reinterpret_cast< nival::thread_t ** >( &thread_id ) )->get_thread_name();
}
*/

} // namespace threading


#endif  // #elif defined( NV_LINUX_PLATFORM )
