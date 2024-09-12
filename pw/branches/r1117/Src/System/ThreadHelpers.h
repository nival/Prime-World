#ifndef THREADHELPERS_H_INCLUDED
#define THREADHELPERS_H_INCLUDED

//Thread helper classes zoo

#include "Thread.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace threading
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Just like threading::Thread but tries to stop thread in destructor and terminates if fails
class AutostopThread : public Thread
{
  unsigned waitMs;

public:
  AutostopThread( unsigned _waitMs = 1000, unsigned stackSize = 0 ) : Thread( stackSize ), waitMs( _waitMs ) {}

  ~AutostopThread() { Stop( true, waitMs ); }
};


//
//
// Классы ниже - устаревший функционал!
// Используйте JobThread / IThreadJob / AutostopThread
//
//


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Template thread helper class. User class must provide function:
// unsigned Process( bool & isRunning );
template <typename ThreadClass>
class ProcessingThread : public Thread
{
  ThreadClass & threadClass;
  
  virtual unsigned Work()
  {
    return (unsigned)threadClass.Process( isRunning );
  }
public:
  ProcessingThread( ThreadClass & _threadClass, bool startImmediately = true, int stackSize = 0 ) :
  threadClass( _threadClass )
  {
    if( startImmediately )
      Resume();
  }
};



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Macro thread helper class, the 'ticker' pattern
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
_interface ITickable : public IObjectBase
{
	virtual void Tick() = 0;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
_interface ITickerThread : public IObjectBase
{
	static CObj<ITickerThread> Create( ITickable *, const char * _threadName );

  virtual void Terminate() = 0;
};

}; //namespace threading

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define IMPLEMENT_TICKER( className, funcName )                                   \
class  className##Ticker : public threading::ITickable, public CObjectBase {      \
  OBJECT_BASIC_METHODS( className##Ticker )                                       \
  className* pObj;                                                                \
className##Ticker() {}                                                            \
public:                                                                           \
  className##Ticker( className *_pObj ) : pObj( _pObj ) {}                        \
  virtual void Tick()                                                             \
  {  if( pObj ) pObj->funcName();  }                                              \
};

#endif //THREADHELPERS_H_INCLUDED
