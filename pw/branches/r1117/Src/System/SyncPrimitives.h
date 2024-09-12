#ifndef SYNCPRIMITIVES_H_INCLUDED
#define SYNCPRIMITIVES_H_INCLUDED

#include "System/config.h"
#include "noncopyable.h"

#if defined( NV_LINUX_PLATFORM )
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#endif // #if defined( NV_LINUX_PLATFORM )

#include "Asserts.h"

// do not use this in DLL - it is not compatible with LoadLibrary() under XP.
#define THREAD_LS __declspec(thread)

namespace threading
{


#if defined( NV_WIN_PLATFORM )


class Mutex : public NonCopyable
{
  mutable CRITICAL_SECTION section;
public:

  Mutex()               { InitializeCriticalSection( &section ); }
  explicit Mutex( int spinCount ) { InitializeCriticalSectionAndSpinCount( &section, (DWORD)spinCount ); }

  void Lock() const     { EnterCriticalSection(&section); }

  bool TryLock() const  { return (0 != TryEnterCriticalSection( &section ) ); }

  void Unlock() const   { LeaveCriticalSection(&section); }

  ~Mutex()              { DeleteCriticalSection(&section); }
};




class Semaphore : public NonCopyable
{
  mutable HANDLE sema;
public:

  Semaphore(unsigned int nMaxCount = 1)           { sema = CreateSemaphore( NULL, 0, nMaxCount, NULL); }

  void Signal(unsigned int nCount = 1) const      { ReleaseSemaphore(sema, nCount, NULL); }

  bool Wait(unsigned int nTime = INFINITE) const  { return WAIT_OBJECT_0 == WaitForSingleObject(sema, nTime); }
  void Reset()                             const  { while(WAIT_OBJECT_0 == WaitForSingleObject(sema, 0)) {;} }

  ~Semaphore()                                    { CloseHandle(sema); }
};





class Event : public NonCopyable
{
  HANDLE handle;
public:
  Event( bool manualReset = false, bool initialState = false, const char * name = 0 ) : handle( 0 )
  {
    handle = CreateEventA( 0, manualReset ? TRUE : FALSE, initialState ? TRUE : FALSE, name );
  }

  ~Event()
  {
    if ( handle )
      CloseHandle( handle );
  }

  void Reset() { ResetEvent( handle ); }

  void Set() { SetEvent( handle ); }

  bool Wait( unsigned time = INFINITE ) const
  {
    return ( WaitForSingleObject( handle, (DWORD)time ) == WAIT_OBJECT_0 );
  }

  HANDLE GetHandle() const { return handle; }
};


#elif defined( NV_LINUX_PLATFORM )


class Event : public NonCopyable
{
private:

  //HANDLE handle;

public:

  Event( bool manualReset = false, bool initialState = false, const char * name = NULL ) // : handle( 0 )
  {
    //handle = CreateEventA( 0, manualReset ? TRUE : FALSE, initialState ? TRUE : FALSE, name );
  }

  ~Event()
  {
    /*if ( handle )
      CloseHandle( handle );*/
  }

  void Reset() { /*ResetEvent( handle );*/ }

  void Set() { /*SetEvent( handle );*/ }

  enum { NV_INFINITE = -1U };

  bool Wait( unsigned time = NV_INFINITE ) const
  {
    return 1; //( WaitForSingleObject( handle, (DWORD)time ) == WAIT_OBJECT_0 );
  }

  //HANDLE GetHandle() const { return handle; }

};

class Mutex : public NonCopyable
{

  mutable pthread_mutex_t m_mutex;
  pthread_mutexattr_t m_attr;

public:

  Mutex()
  {
    NI_VERIFY_NO_RET( ::pthread_mutexattr_init( &m_attr ) == 0, "Cannot init mutex attr" );
    NI_VERIFY_NO_RET( ::pthread_mutexattr_settype( &m_attr, PTHREAD_MUTEX_RECURSIVE_NP ) == 0, "Cannot set mutex type" );
    NI_VERIFY_NO_RET( ::pthread_mutex_init( &m_mutex, &m_attr ) == 0, "Cannot init mutex" );
  }

  // Mutex spin count is not implemented in Linux
  explicit Mutex( int /*spinCount*/ )
  {
    NI_VERIFY_NO_RET( ::pthread_mutexattr_init( &m_attr ) == 0, "Cannot init mutex attr" );
    NI_VERIFY_NO_RET( ::pthread_mutexattr_settype( &m_attr, PTHREAD_MUTEX_RECURSIVE_NP ) == 0, "Cannot set mutex type" );
    NI_VERIFY_NO_RET( ::pthread_mutex_init( &m_mutex, &m_attr ) == 0, "Cannot init mutex" );
  }

  void Lock() const
  {
    NI_VERIFY_NO_RET( ::pthread_mutex_lock( &m_mutex ) == 0, "Cannot lock mutex" );
  }

  bool TryLock() const
  {
    return ( 0 == ::pthread_mutex_trylock( &m_mutex ) );
  }

  void Unlock() const
  {
    NI_VERIFY_NO_RET( pthread_mutex_unlock( &m_mutex ) == 0, "Cannot unlock mutex" );
  }

  ~Mutex()
  {
    NI_VERIFY_NO_RET( pthread_mutex_destroy( &m_mutex ) == 0, "Cannot destroy mutex" );
    NI_VERIFY_NO_RET( pthread_mutexattr_destroy( &m_attr ) == 0, "Cannot destroy mutex attr" );
  }

};

class Semaphore : public NonCopyable
{
private:

  mutable sem_t m_semaphore;

public:

  enum {

    INFINITE = -1U

  };

  Semaphore( unsigned int nMaxCount = 1 )
  {
    NI_VERIFY(
      sem_init( &m_semaphore, 0, 0 ) == 0,
      "Cannot initialize semaphore by sem_init()",
      return
    );
  }

  void Signal( unsigned int nCount = 1 ) const
  {
    while ( nCount-- )
      NI_VERIFY(
        sem_post( &m_semaphore ) == 0,
        "Cannot signal semaphore by sem_post()",
        return
      );
  }

  bool Wait( unsigned int nTime = INFINITE ) const
  {
    if (INFINITE == nTime) {

      NI_VERIFY(
        sem_wait( &m_semaphore ) == 0,
        "Something wrong in sem_wait()",
        return false
      );

      return true;

    }

    timespec current_time;

    NI_VERIFY(
      clock_gettime( CLOCK_REALTIME, &current_time ) != -1,
      "Cannot get current time by clock_gettime()",
      return false
    );

    current_time.tv_nsec += ( nTime % 1000 ) * 1000000;
    if (current_time.tv_nsec >= 1000000000) {

      ++current_time.tv_sec;
      current_time.tv_nsec -= 1000000000;

    }

    current_time.tv_sec += nTime / 1000;

    return sem_timedwait( &m_semaphore, &current_time ) == 0;
  }

  void Reset() const
  {
    while ( Wait( 0 ) ) {}
  }

  ~Semaphore()
  {
    sem_destroy( &m_semaphore );
    //m_semaphore = NULL;
  }

};

#endif  // #elif defined( NV_LINUX_PLATFORM )


class MutexLock : public NonCopyable
{
  const Mutex * mutex;

public:
  MutexLock( const Mutex & _mutex ) : mutex( &_mutex ) { mutex->Lock(); }

  ~MutexLock() { mutex->Unlock(); }
};




class MutexUnlock : public NonCopyable
{
  const Mutex * mutex;

public:
  MutexUnlock( const Mutex & _mutex ) : mutex( &_mutex ) {}

  ~MutexUnlock() { mutex->Unlock(); }
};



}; //namespace threading

#endif //SYNCPRIMITIVES_H_INCLUDED
