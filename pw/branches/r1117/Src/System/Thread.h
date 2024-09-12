#ifndef THREAD_H_INCLUDED
#define THREAD_H_INCLUDED

#include "types.h"
#include "noncopyable.h"
#include "SyncPrimitives.h"

namespace threading
{

#if defined( NV_WIN_PLATFORM )

typedef DWORD thread_id_t;

#elif defined( NV_LINUX_PLATFORM )

#define INFINITE 0xFFFFFFFF 
typedef pthread_t thread_id_t;

#endif

thread_id_t CurrentThreadID();


#if defined( NV_WIN_PLATFORM )


//Thread is ALWAYS created sleeping to prevent it from launching before parent class constructor finishes
class Thread : public NonCopyable
{
public:
  Thread( unsigned stackSize = 0 );
  virtual ~Thread();

  unsigned int Resume(); //Returns resume/suspend counter value..
  unsigned int Suspend(); //Use of this function is NOT recommended!
  bool Wait( unsigned int timeout = INFINITE ); // wait thread to finish timeout milliseconds,  returns true if thread is finished
  bool Finished() { return Wait( 0 ); } // returns true if thread is finished
  void      Terminate( unsigned int exitCode ); //Насильственное завершение
  void      SetPriority( int priority );
  HANDLE    Handle() const { return externalHandle; }
  unsigned int Id() const { return threadID; }
  void      Stop( bool waitForStop = false, int timeoutInMs = 1000 );
  void      AsyncStop();

  virtual unsigned int Work() = 0;

protected:
  volatile bool isRunning;

private:
  static unsigned __stdcall WorkInternal( void * param );

  unsigned int threadID;
  HANDLE  externalHandle;
};


#elif defined( NV_LINUX_PLATFORM )

//Thread is ALWAYS created sleeping to prevent it from launching before parent class constructor finishes
class Thread : public NonCopyable
{
private:
  static void * InternalHandler( void * param )
  {
    Thread * handler = static_cast< Thread * >( param );
    handler -> id_ = ::pthread_self();
    handler -> Work();

    NI_VERIFY_NO_RET( ::pthread_mutex_lock( &(handler -> finish_) ) == 0, "Cannot lock mutex" );
    NI_VERIFY_NO_RET( ::pthread_cond_broadcast( &(handler -> wait_) ) == 0, "Cannot signal condition" );
    NI_VERIFY_NO_RET( ::pthread_mutex_unlock( &(handler -> finish_) ) == 0, "Cannot unlock mutex" );

    return 0;
  }

public:

  // FIX: INFINITE is a predefined constant
  enum { NV_INFINITE = -1U };

public:

  Thread( unsigned stack_size = 0 ): isRunning( true ), id_( -1 )
  {
    //m_thread = new nival::ts_object_t< thread_wrapper_t >( this );
    NI_VERIFY_NO_RET( ::pthread_mutex_init( &finish_, 0 ) == 0, "Cannot init mutex" );
    NI_VERIFY_NO_RET( ::pthread_cond_init( &wait_, 0 ) == 0, "Cannot init cond" );
  }

  virtual ~Thread()
  {
    NI_VERIFY_NO_RET( ::pthread_mutex_destroy( &finish_ ) == 0, "Cannot destroy mutex" );
    NI_VERIFY_NO_RET( ::pthread_cond_destroy( &wait_ ) == 0, "Cannot destroy cond" );
  }

  // Starts the thread after construction
  unsigned int Resume()
  {
    return ( ::pthread_create( &th_, 0, InternalHandler, this ) == 0 ) ? 1 : 0;
  }

  // Doesn't work in linux
  unsigned int Suspend()
  {
    // TODO: Needs to log the call of Suspend()
    return 0;
  }

  // Waits thread to finish timeout milliseconds, returns true if thread is finished
  bool Wait( unsigned int timeout = NV_INFINITE )
  {
    if ( timeout == NV_INFINITE )
    {
      return ( ::pthread_join( th_, 0 ) == 0 );
    }

    struct timespec ts = { 0 };
    NI_VERIFY_NO_RET( ::clock_gettime( CLOCK_REALTIME, &ts ) == 0, "Cannot get real time" );
    ts.tv_sec += timeout / 1000;
    ts.tv_nsec += ( timeout % 1000 ) * 1000;
    NI_VERIFY_NO_RET( ::pthread_mutex_lock( &finish_ ) == 0, "Cannot lock mutex" );
    const int r = ::pthread_cond_timedwait( &wait_, &finish_, &ts );
    NI_VERIFY_NO_RET( ::pthread_mutex_unlock( &finish_ ) == 0, "Cannot unlock mutex" );
    return ( r == 0 );
  }

  // Returns true if thread is finished
  bool Finished() const
  {
    //return !m_thread.get() || m_thread->is_finished();
    return !isRunning;
  }

  // Doesn't work in linux
  void Terminate( unsigned int )
  {
    NI_VERIFY_NO_RET( ::pthread_cancel( th_ ) == 0, "Cannot cancel thread" );
  }
  
  unsigned int Id() const { return id_; }

  // Doesn't work in linux
  void SetPriority( int priority )
  {
    // TODO: Needs to log the call of SetPriority()
  }

  /*
  thread_id_t Id() const
  {
    //return static_cast< nival::thread_t * >( m_thread.get() );
    return 0;
  }
  */

  void Stop( bool waitForStop = false, int timeoutInMs = 1000 )
  {
    isRunning = false;

    if( waitForStop )
    {
      bool stopped = Wait( timeoutInMs );
      NI_ASSERT( stopped, "Thread termination timed out!" );
      if( !stopped )
        Terminate( 0 ); 
    }
  }

  // FIX: DIRTY HACK
  void AsyncStop() { Stop(); }

protected:

  virtual unsigned int Work() = 0;

  volatile bool isRunning;

private:

  //nival::ptr_t< thread_wrapper_t > m_thread;
  pthread_t th_;
  pthread_mutex_t finish_;
  pthread_cond_t wait_;
  thread_id_t id_;

};


#endif  // #elif defined( NV_LINUX_PLATFORM )


void Sleep( unsigned int milliseconds );
void ExitCurrentThread( unsigned int exitCode );

}; //namespace threading

#endif //THREAD_H_INCLUDED
