#include "TamarinPCH.h"
#include "Event.h"
#include "../../FlashMovieAvmCore.h"

namespace avmplus
{


EventClass::EventClass( VTable *vtable ) : FlashClassClosure(vtable)
{
  flash::FlashMovieAvmCore * flashCore = (flash::FlashMovieAvmCore*) core();
  flashCore->GetClassCache().RegisterClass( EFlashClassID::EventClass, this );
}


ScriptObject* EventClass::createInstance( VTable* ivtable, ScriptObject* prototype )
{
  return new (core()->GetGC(), ivtable->getExtraSize()) EventObject(ivtable, prototype);
}

EventObject::EventObject( VTable* ivtable, ScriptObject* prototype ): FlashScriptObject (ivtable, prototype),
defaultPrevented(false),
target(0),
curTarget(0),
immediatePropagationStopped(false),
propagationStopped(false)
{}

void EventObject::Init( AvmString type, bool bubbles, bool cancelable )
{
  eventType = type;
  this->bubbles = bubbles;
  this->cancelable = cancelable;
}

}