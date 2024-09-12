#ifndef NITIMER_H_INCLUDED
#define NITIMER_H_INCLUDED

#include "HPTimer.h"

namespace timer
{

class ITimer : public IBaseInterfaceMT
{
  NI_DECLARE_CLASS_1( ITimer, IBaseInterfaceMT );
public:
  virtual timer::Time   Now() const = 0;
  virtual timer::Ticks  GetTicks() const = 0;
};



class RealTimer : public ITimer, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( RealTimer, ITimer, BaseObjectMT );
public:
  RealTimer() {}
  virtual timer::Time   Now() const { return timer::Now(); }
  virtual timer::Ticks  GetTicks() const { return timer::GetTicks(); }
};



//excellent for unit-testing
class FixedTimer : public ITimer, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( FixedTimer, ITimer, BaseObjectMT );
public:
  FixedTimer() : now( 0 ), ticks( 0 ) {}
  FixedTimer( timer::Time _now, timer::Ticks _ticks ) : now( _now ), ticks( _ticks ) {}

  virtual timer::Time   Now() const { return now; }
  virtual timer::Ticks  GetTicks() const { return ticks; }

  void Set( timer::Time _now, timer::Ticks _ticks ) { now = _now; ticks = _ticks; }

private:
  timer::Time   now;
  timer::Ticks  ticks;
};



//Simple time measurement object
class Stopwatch
{
public:
  Stopwatch() :
  startTime( Now() )
  {}

  void Restart() { startTime = Now(); }
  Time StartTime() const { return startTime; }
  Time ElapsedTime() const { return Now() - startTime; }

private:
  Time startTime;
};



//Common poll model timer
class Timer : public Stopwatch
{
public:
  explicit Timer( Time _timeout ) :
  Stopwatch(),
  timeout( _timeout ),
  deadline( StartTime() + _timeout ),
  running( true )
  {
    NI_ASSERT( _timeout > 0, "" );
  }


  Timer() :
  Stopwatch(),
  timeout( 0 ),
  deadline( StartTime() ),
  running( false )
  {
  }


  Time TimeLeft() const
  {
    if ( !running )
      return 0;

    Time t = Now();
    if ( t >= deadline )
      return 0;

    return deadline - t;
  }


  bool Poll()
  {
    if ( !running )
      return true;

    Time t = Now();
    if ( t < deadline )
      return false;

    running = false;
    OnTimeout();
    return true;
  }


  bool Elapsed() const { return !running; }
  bool Running() const { return running; }


  void Restart()
  {
    Stopwatch::Restart();

    running = true;
    deadline = StartTime() + timeout;
  }


  void Restart( Time _newTimeout )
  {
    NI_ASSERT( _newTimeout > 0, "" );
    timeout = _newTimeout;
    Restart();
  }


  void Stop() { running = false; }

protected:
  virtual void OnTimeout() {}

private:
  Time timeout;
  Time deadline;
  bool running;
};




//Timer with callback (MT-version only implemented yet)
class ICallback : public IBaseInterfaceMT
{
  NI_DECLARE_CLASS_1( ICallback, IBaseInterfaceMT );

public:
  virtual void OnTimeout( Timer * _timer ) = 0;
};

class CallbackTimer : public Timer
{
public:
  CallbackTimer( Time _timeout, ICallback * _cb ) :
  Timer( _timeout ),
  callback( _cb )
  {}

protected:
  virtual void OnTimeout()
  {
    StrongMT<ICallback> locked = callback.Lock();
    NI_VERIFY( locked, "", return );
    locked->OnTimeout( this );
  }

private:
  WeakMT<ICallback> callback;
};




//Timer with pointer-to-member callback (Unsafe class pointer!!)
template <class T>
class MemberPtrTimer : public Timer
{
public:
  MemberPtrTimer( Time _timeout, T * _classPtr, void (T::*_memberPtr)() ) :
  Timer( _timeout ),
  classPtr( _classPtr ),
  memberPtr( _memberPtr )
  {}

protected:
  virtual void OnTimeout()
  {
    (classPtr->*memberPtr)();
  }

private:
  T * classPtr;
  void (T::*memberPtr)();
};

} //namespace timer

#endif //NITIMER_H_INCLUDED
