#include "TamarinPCH.h"

#include "KeyboardEvent.h"

namespace avmplus
{

KeyboardEventClass::KeyboardEventClass( VTable * vtable ) :
EventClass( vtable )
{
  flash::FlashMovieAvmCore * flashCore = (flash::FlashMovieAvmCore*) core();
  flashCore->GetClassCache().RegisterClass( EFlashClassID::KeyboardEventClass, this );
}


ScriptObject * KeyboardEventClass::createInstance(VTable* ivtable, ScriptObject* prototype)
{
  return new (core()->GetGC(), ivtable->getExtraSize()) KeyboardEventObject(ivtable, prototype);
}



KeyboardEventObject * KeyboardEventClass::CreateKeyboardEvent(
    const char * _type,
    bool _bubbles, bool _cancelable,
    unsigned _charCodeValue, unsigned _keyCodeValue, unsigned _keyLocationValue,
    bool _ctrlKeyValue, bool _altKeyValue, bool _shiftKeyValue )
{
  Atom args[] = 
  { 0, 
    core()->internConstantStringLatin1(_type)->atom(),
    _bubbles ? trueAtom : falseAtom,
    _cancelable ? trueAtom : falseAtom,
    core()->uintToAtom( _charCodeValue ), core()->uintToAtom( _keyCodeValue ), core()->uintToAtom( _keyLocationValue ),
    _ctrlKeyValue ? trueAtom : falseAtom,
    _altKeyValue ? trueAtom : falseAtom,
    _shiftKeyValue ? trueAtom : falseAtom
  };

  int numParams = sizeof( args ) / sizeof( Atom ) - 1;

  KeyboardEventObject * event = (KeyboardEventObject *) core()->atomToScriptObject( construct( numParams, args ) );
  return event;
}

} //namespace avmplus
