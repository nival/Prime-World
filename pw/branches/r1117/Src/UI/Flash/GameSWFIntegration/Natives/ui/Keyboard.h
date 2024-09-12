#pragma once
#include "System/SystemLog.h"
#include "PlayerGlobalIncludes.h"

namespace avmplus
{


class KeyboardObject: public ScriptObject
{
public:
  KeyboardObject(VTable *ivtable, ScriptObject *delegate):ScriptObject(ivtable, delegate) {}
  ~KeyboardObject(void) {}


private:
  DECLARE_SLOTS_KeyboardObject;
};
  
class KeyboardClass : public ClassClosure
{
public:
  KeyboardClass(VTable *vtable): ClassClosure(vtable){}
  ~KeyboardClass(){}
  
  virtual ScriptObject* createInstance(VTable* ivtable, ScriptObject* prototype)
  {
    return new (core()->GetGC(), ivtable->getExtraSize()) KeyboardObject(ivtable, prototype);
  }  
  
  bool get_capsLock()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "KeyboardClass", "get_capsLock" );
    return (bool)0;
  }

  bool isAccessible()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "KeyboardClass", "isAccessible" );
    return (bool)0;
  }

  bool get_numLock()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "KeyboardClass", "get_numLock" );
    return (bool)0;
  }


private:
  DECLARE_SLOTS_KeyboardClass;
};

}