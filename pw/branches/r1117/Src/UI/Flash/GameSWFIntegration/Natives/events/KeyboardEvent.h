#pragma once
#include "System/SystemLog.h"
#include "../PlayerGlobalIncludes.h"
#include "Event.h"

namespace avmplus
{


class KeyboardEventClass : public EventClass
{
public:
  KeyboardEventClass( VTable * vtable );
  ~KeyboardEventClass(){}

  virtual ScriptObject * createInstance( VTable * ivtable, ScriptObject * prototype );

  KeyboardEventObject * CreateKeyboardEvent(
    const char * _type,
    bool _bubbles, bool _cancelable,
    unsigned _charCodeValue, unsigned _keyCodeValue, unsigned _keyLocationValue,
    bool _ctrlKeyValue, bool _altKeyValue, bool _shiftKeyValue );

private:
  DECLARE_SLOTS_KeyboardEventClass;
};



class KeyboardEventObject: public EventObject
{
public:
  KeyboardEventObject( VTable * ivtable, ScriptObject * delegate ): EventObject( ivtable, delegate ) {}
  ~KeyboardEventObject() {}

  void updateAfterEvent()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "KeyboardEventObject", "updateAfterEvent" );
    return (void)0;
  }

private:
  DECLARE_SLOTS_KeyboardEventObject;
};


} //namespace avmplus
