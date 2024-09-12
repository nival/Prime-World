/**
  @TODO: внимательнее разобраться в деталях и спортировать аккуратнее.
  @TODO: добавить кроссплатформенные юниттесты.
 */

#include "stdafx.h"
#include "MultiReaderLock.h"
#include <pthread.h>


namespace threading
{

class MultiReaderLock::MultiReaderLockImpl
{ 
public: 
  MultiReaderLockImpl() /*: readers( 0 )*/
  {
    /*
    ::pthread_mutex_init( &writeSection, NULL );
    ::pthread_mutex_init( &readerCountSection, NULL );
    // noReaders = ::CreateEvent( NULL, TRUE, TRUE, NULL );
    ::pthread_cond_init( &noReaders, NULL );
    ::pthread_cond_signal( &noReaders );
    */
    ::pthread_rwlock_init( &rwlock_, NULL );
  }

  ~MultiReaderLockImpl() throw()
  {
    // ::CloseHandle( noReaders );
    /*
    ::pthread_cond_destroy( &noReaders );
    ::pthread_mutex_destroy( &writeSection );
    ::pthread_mutex_destroy( &readerCountSection );
    */
    ::pthread_rwlock_destroy( &rwlock_ );
  }

  void LockForRead() const
  {
    /*
    ::pthread_mutex_lock( &writeSection );
    ::pthread_mutex_lock( &readerCountSection );
    if ( ++readers == 1 )
    {
      // ::ResetEvent( noReaders );
      ::pthread_cond_signal( &noReaders );
    }
    ::pthread_mutex_unlock( &readerCountSection );
    ::pthread_mutex_unlock( &writeSection );
    */
    ::pthread_rwlock_rdlock( &rwlock_ );
  }

  void UnlockAfterRead() const
  {
    /*
    ::pthread_mutex_lock( &readerCountSection );
    assert( readers > 0 );
    if ( !( --readers ) )
    {
      // ::SetEvent( noReaders );
      ::pthread_cond_signal( &noReaders );
    }
    ::pthread_mutex_unlock( &readerCountSection );
    */
    ::pthread_rwlock_unlock( &rwlock_ );
  }

  void LockForWrite() const
  {
    /*
    ::pthread_mutex_lock( &writeSection );
    // ::WaitForSingleObject( noReaders, INFINITE );
    ::pthread_cond_wait( &noReaders, &writeSection );
    */
    ::pthread_rwlock_wrlock( &rwlock_ );
  }

  void UnlockAfterWrite() const
  {
    // ::pthread_mutex_unlock( &writeSection );
    ::pthread_rwlock_unlock( &rwlock_ );
  }

private:
  /*
  mutable pthread_mutex_t   writeSection;
  mutable pthread_mutex_t   readerCountSection;
  mutable long              readers;
  mutable pthread_cond_t    noReaders;
  */
  mutable pthread_rwlock_t  rwlock_;
};


MultiReaderLock::MultiReaderLock() : impl_( new MultiReaderLockImpl )
{
  ;;
}



MultiReaderLock::~MultiReaderLock()
{
  ;;
}



void MultiReaderLock::LockForRead() const
{
  impl_ -> LockForRead();
}



void MultiReaderLock::UnlockAfterRead() const
{
  impl_ -> UnlockAfterRead();
}



void MultiReaderLock::LockForWrite() const
{
  impl_ -> LockForWrite();
}



void MultiReaderLock::UnlockAfterWrite() const
{
  impl_ -> UnlockAfterWrite();
}

} //namespace threading
