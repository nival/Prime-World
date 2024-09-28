#include "TamarinPCH.h"

#include "TimerEvent.h"

#include "../../FlashMovieAvmCore.h"

namespace avmplus
{
//                        TimerEventClass
//////////////////////////////////////////////////////////////////////////
TimerEventClass::TimerEventClass( VTable *vtable ) : EventClass(vtable)
{
  flash::FlashMovieAvmCore * flashCore = (flash::FlashMovieAvmCore*) core(); 
  flashCore->GetClassCache().RegisterClass( EFlashClassID::TimerEventClass, this );
}


ScriptObject* TimerEventClass::createInstance( VTable* ivtable, ScriptObject* prototype )
{
  return new (core()->GetGC(), ivtable->getExtraSize()) TimerEventObject(ivtable, prototype);
}


//                      TimerEventObject
//////////////////////////////////////////////////////////////////////////
TimerEventObject::TimerEventObject( VTable *ivtable, ScriptObject *delegate ) :EventObject(ivtable, delegate)
{

}

void TimerEventObject::updateAfterEvent()
{

}




}