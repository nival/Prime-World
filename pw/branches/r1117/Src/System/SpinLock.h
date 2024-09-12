#ifndef SYSTEM_SPINLOCK_H_INCLUDED
#define SYSTEM_SPINLOCK_H_INCLUDED

#include "stdafx.h"
#include "noncopyable.h"
#include <assert.h>

namespace threading
{

class SpinLock : public NonCopyable
{
public:
  SpinLock() : gate( LockValueFree ) {}
  
  ~SpinLock()
  {
    assert( gate == LockValueFree );
  }

  void Lock() const
  {
    InternalLock( -1 );
  }

  bool TryLock() const
  {
    return InternalLock( 0 );
  }

  bool TryLock( int spinCount ) const
  {
    return InternalLock( spinCount );
  }

  void Unlock() const
  {
    //NOTE: We use non-locking operation here
    //It works on most (Intel and AMD) current x86 hardware and much more fasta

    assert( gate == LockValueBusy );
    gate = LockValueFree;

    //LONG check = InterlockedExchange( &gate, LockValueFree );
    //check;
    //assert( check == LockValueBusy );
  }

private:
  static const LONG LockValueFree = 0;
  static const LONG LockValueBusy = 1;

  volatile mutable LONG   gate;

  bool InternalLock( int spinCount ) const;
};



class SpinLockGuard : public NonCopyable
{
  const SpinLock & lock;
public:
  SpinLockGuard( const SpinLock & _lock ) : lock( _lock ) { lock.Lock(); }
  ~SpinLockGuard() { lock.Unlock(); }
};



class SpinLockUnlockGuard : public NonCopyable
{
  const SpinLock & lock;
public:
  SpinLockUnlockGuard( const SpinLock & _lock ) : lock( _lock ) {}
  ~SpinLockUnlockGuard() { lock.Unlock(); }
};

}; //namespace threading

#endif //SYSTEM_SPINLOCK_H_INCLUDED
