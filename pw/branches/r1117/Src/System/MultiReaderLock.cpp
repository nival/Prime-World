#include "stdafx.h"
#include "MultiReaderLock.h"


namespace threading
{

class MultiReaderLock::MultiReaderLockImpl
{ 
public: 
  MultiReaderLockImpl() : readers( 0 ),
                          noReaders( NULL )
  {
    ::InitializeCriticalSection( &writeSection );
    ::InitializeCriticalSection( &readerCountSection );
    noReaders = ::CreateEvent( NULL, TRUE, TRUE, NULL );
  }

  ~MultiReaderLockImpl() throw()
  {
    ::CloseHandle( noReaders );
    ::DeleteCriticalSection( &writeSection );
    ::DeleteCriticalSection( &readerCountSection );
  }

  void LockForRead() const
  {
    ::EnterCriticalSection( &writeSection );
    ::EnterCriticalSection( &readerCountSection );
    if ( ++readers == 1 )
    {
      ::ResetEvent( noReaders );
    }
    ::LeaveCriticalSection( &readerCountSection );
    ::LeaveCriticalSection( &writeSection );
  }

  void UnlockAfterRead() const
  {
    ::EnterCriticalSection( &readerCountSection );
    assert( readers > 0 );
    if ( !( --readers ) )
    {
      ::SetEvent( noReaders );
    }
    ::LeaveCriticalSection( &readerCountSection );
  }

  void LockForWrite() const
  {
    ::EnterCriticalSection( &writeSection );
    ::WaitForSingleObject( noReaders, INFINITE );
  }

  void UnlockAfterWrite() const
  {
    ::LeaveCriticalSection( &writeSection );
  }

private:
  mutable CRITICAL_SECTION  writeSection;
  mutable CRITICAL_SECTION  readerCountSection;
  mutable long              readers;
  mutable HANDLE            noReaders;
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
