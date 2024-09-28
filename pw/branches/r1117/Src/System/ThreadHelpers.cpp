#include "stdafx.h"
#include "ThreadHelpers.h"
#include "System/ThreadNames.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace threading
{

class TickerThreadImpl : public ITickerThread, public CObjectBase, public Thread
{
  OBJECT_BASIC_METHODS( TickerThreadImpl );
  CObj<ITickable> tickable;

#ifndef _SHIPPING
  string threadName;
#endif //_SHIPPING

  TickerThreadImpl() {}

public:
  TickerThreadImpl( ITickable * _tickable, const char * _threadName )
  : tickable( _tickable )
#ifndef _SHIPPING
  , threadName( _threadName )
#endif //_SHIPPING
  {
  }

  ~TickerThreadImpl()
  {
    Terminate();
  }

  //ITickerThread:
  virtual void Terminate()
  {
    Stop( true, 3000 );
  }

  //Thread:
  virtual unsigned Work()
  {
#if !defined( _SHIPPING )
    if ( !threadName.empty() )
      threading::SetDebugThreadName( threadName.c_str() );
#endif
    while( isRunning )
      tickable->Tick();

    return 0;
  }
};

CObj<ITickerThread> ITickerThread::Create( ITickable * _tickable, const char * _threadName )
{
  CObj<TickerThreadImpl> p = new TickerThreadImpl( _tickable, _threadName ) ;
  p->Resume();
  return (ITickerThread *)p;
}

}; //namespace threading

BASIC_REGISTER_CLASS( threading::ITickerThread )
BASIC_REGISTER_CLASS( threading::ITickable )
BASIC_REGISTER_CLASS( threading::TickerThreadImpl )
