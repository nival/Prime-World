#pragma once
#include "System/SystemLog.h"
#include "PlayerGlobalIncludes.h"

namespace avmplus
{
class DisplayObjectObject;


class AccessibilityObject: public ScriptObject
{
public:
  AccessibilityObject(VTable *ivtable, ScriptObject *delegate):ScriptObject(ivtable, delegate) {}
  ~AccessibilityObject(void) {}


private:
  DECLARE_SLOTS_AccessibilityObject;
};
  
class AccessibilityClass : public ClassClosure
{
public:
  AccessibilityClass(VTable *vtable): ClassClosure(vtable){}
  ~AccessibilityClass(){}
  
  virtual ScriptObject* createInstance(VTable* ivtable, ScriptObject* prototype)
  {
    return new (core()->GetGC(), ivtable->getExtraSize()) AccessibilityObject(ivtable, prototype);
  }  
  
  void sendEvent(DisplayObjectObject* source, uint childID, uint eventType, bool nonHTML)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "AccessibilityClass", "sendEvent" );
    return (void)0;
  }

  void updateProperties()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "AccessibilityClass", "updateProperties" );
    return (void)0;
  }

  bool get_active()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "AccessibilityClass", "get_active" );
    return (bool)0;
  }


private:
  DECLARE_SLOTS_AccessibilityClass;
};

}