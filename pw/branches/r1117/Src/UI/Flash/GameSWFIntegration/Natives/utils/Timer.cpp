#include "TamarinPCH.h"

#include "../../FlashMovie.h"
#include "../events/TimerEvent.h"

#include "Timer.h"

namespace avmplus
{

TimerObject::TimerObject( VTable *ivtable, ScriptObject *delegate ) :
  EventDispatcherObject(ivtable, delegate),
  isRunnung (false),
  delay(0),
  timePassed(0),
  timerID(-1)
{

}


TimerObject::~TimerObject( void )
{

}

void TimerObject::_timerDispatch()
{
  TimerEventClass * timerEventClass = FlashCore()->GetClassCache().GetClass<TimerEventClass>(EFlashClassID::TimerEventClass);
  Atom args[] = {0, FlashCore()->GetEventTypes().TIMER->atom() };
  TimerEventObject * event = (TimerEventObject *) FlashCore()->atomToScriptObject(timerEventClass->construct(1,args));

  dispatchEventFunction(event);

  //also reset the timer
  timePassed = 0;

  return (void)0;
}

void TimerObject::_start( double delay, FunctionObject* closure )
{
  FlashCore()->GetMovie()->SubscribeForAdvance(this);
  
  callback = closure;
  this->delay = delay / 1000.0; // time in msec
  isRunnung = true;
}

void TimerObject::stop()
{
  FlashCore()->GetMovie()->UnsubscribeForAdvance(this);
  
  isRunnung = false;
  timePassed = 0;
}

bool TimerObject::get_running()
{
  return isRunnung;
}

void TimerObject::Advance( float deltaTime )
{
  timePassed += deltaTime;

  if ( timePassed >= delay )
  {
    int numTicks = int( timePassed / delay );
    timePassed = fmodf( timePassed, delay );

    for ( int i = 0; i < numTicks && isRunnung; ++i )
    {
      Atom args[] = {callback->atom()};
      callback->call(0, args);
    }
  }
}

TimerClass::TimerClass(VTable *vtable) : 
  EventDispatcherClass(vtable)
{
  flash::FlashMovieAvmCore * flashCore = (flash::FlashMovieAvmCore*) core();
  flashCore->GetClassCache().RegisterClass( EFlashClassID::TimerClass, this );
}

ScriptObject* TimerClass::createInstance( VTable* ivtable, ScriptObject* prototype )
{
  return new (core()->GetGC(), ivtable->getExtraSize()) TimerObject(ivtable, prototype);
}

avmplus::Atom TimerClass::construct( int argc, Atom* argv )
{
  VTable* ivtable = this->ivtable();
  ScriptObject* obj = newInstance();

  argv[0] = obj->atom(); 
  ivtable->init->coerceEnter(argc, argv);
  return obj->atom();
}
}