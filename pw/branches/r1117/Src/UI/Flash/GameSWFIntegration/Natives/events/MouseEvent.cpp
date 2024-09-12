#include "TamarinPCH.h"

#include "../display/DisplayObject.h"
#include "../display/InteractiveObject.h"

#include "MouseEvent.h"

namespace avmplus
{

MouseEventObject::MouseEventObject(VTable *ivtable, ScriptObject *delegate) : 
  EventObject(ivtable, delegate) 
{

}

MouseEventObject::~MouseEventObject(void) 
{

}

void MouseEventObject::updateAfterEvent()
{
  NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "MouseEventObject", "updateAfterEvent" );
  return (void)0;
}

DisplayObjectObject* MouseEventObject::GetRelatedObject()
{ 
  return relatedObject;
}

void MouseEventObject::SetRelatedObject( DisplayObjectObject* _relatedObject )
{
  relatedObject = _relatedObject;

  if ( dynamic_cast<InteractiveObjectObject*>( _relatedObject ) )
  {
    avmplus::Stringp propName = core()->internConstantStringLatin1( "m_relatedObject" );

    if ( relatedObject )
      SetPropertyByName( propName, relatedObject->atom() );
  }
}

void MouseEventObject::SetCurrentTarget( ScriptObject * currentDispatcher )
{
  EventObject::SetCurrentTarget( currentDispatcher );

  DisplayObjectObject* displayObject = dynamic_cast<DisplayObjectObject*>( currentDispatcher );

  if ( displayObject )
  {
    // TODO convert to local coords
  }
}

MouseEventClass::MouseEventClass(VTable *vtable) : 
  EventClass(vtable)
{
  flash::FlashMovieAvmCore * flashCore = (flash::FlashMovieAvmCore*) core();
  flashCore->GetClassCache().RegisterClass( EFlashClassID::MouseEventClass, this );
}

ScriptObject* MouseEventClass::createInstance(VTable* ivtable, ScriptObject* prototype)
{
  return new (core()->GetGC(), ivtable->getExtraSize()) MouseEventObject(ivtable, prototype);
}

MouseEventObject* MouseEventClass::CreateMouseEvent(  const char * _type, 
                                                      float _stageX, float _stageY, 
                                                      float _localX, float _localY, 
                                                      bool primaryButton, DisplayObjectObject* _relatedObject, 
                                                      int mouseWheelDelta )
{
  Atom args[] = 
  { 0, 
    core()->internConstantStringLatin1(_type)->atom(),
    trueAtom,
    falseAtom, // cancelable
    core()->doubleToAtom( _localX ),
    core()->doubleToAtom( _localY ),
    (dynamic_cast<InteractiveObjectObject*>(_relatedObject) ? _relatedObject->atom() : nullObjectAtom),
    falseAtom, // ctrlKey 
    falseAtom, // altKey
    falseAtom, // shiftKey
    primaryButton ? trueAtom : falseAtom,
    core()->intToAtom(mouseWheelDelta)
  };

  int numParams = sizeof( args ) / sizeof( Atom ) - 1;

  MouseEventObject * event = (MouseEventObject *) core()->atomToScriptObject( construct( numParams, args ) );

  if ( event )
    event->SetStageXY( _stageX, _stageY );

  return event;
}

}
