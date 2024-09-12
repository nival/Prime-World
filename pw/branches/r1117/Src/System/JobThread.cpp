#include "stdafx.h"
#include "JobThread.h"
#include "System/ThreadNames.h"

namespace threading
{


class JobThreadImplementation : public Thread
{
public:
  JobThreadImplementation( IThreadJob * _job, const char * _debugName, unsigned _waitMs, unsigned stackSize ) :
  Thread( stackSize ),
  job( _job ),
  waitMs( _waitMs ),
  debugName( _debugName )
  {
  }

  ~JobThreadImplementation()
  {
    Stop( true, waitMs );
    job = 0;
  }

  void SetPriorityImpl( int _delta )
  {
    int prio = Clamp<int>( THREAD_PRIORITY_NORMAL + _delta, THREAD_PRIORITY_LOWEST, THREAD_PRIORITY_HIGHEST );
    SetPriority( prio );
  }

private:
  StrongMT<IThreadJob> job;
  unsigned  waitMs;
  string    debugName;

  virtual unsigned Work()
  {
    SetDebugThreadName( debugName.c_str() );
    job->Work( isRunning );
    job = 0;
    return 0;
  }
};





JobThread::JobThread( IThreadJob * job, const char * debugName, unsigned waitMs, unsigned stackSize ) :
thread( 0 )
{
  thread = new JobThreadImplementation( job, debugName, waitMs, stackSize );
  thread->Resume();
}



void JobThread::StopImpl()
{
  if ( thread )
    delete thread;
  thread = 0;
}


unsigned int JobThread::Id() const
{
  return thread ? thread->Id() : 0;
}



bool JobThread::Wait( unsigned timeout )
{
  if ( thread )
    return thread->Wait( timeout );
  return true;
}


void JobThread::SetPriority( int _delta )
{
  if ( thread )
    thread->SetPriorityImpl( _delta );
}


void JobThread::AsyncStop()
{
  if ( thread )
    thread->AsyncStop();
}

}; //namespace threading

NI_DEFINE_REFCOUNT( threading::JobThread )
