#pragma once
#include "System/SystemLog.h"
#include "PlayerGlobalIncludes.h"

namespace avmplus
{


class MouseObject: public ScriptObject
{
public:
  MouseObject(VTable *ivtable, ScriptObject *delegate):ScriptObject(ivtable, delegate) {}
  ~MouseObject(void) {}


private:
  DECLARE_SLOTS_MouseObject;
};
  
class MouseClass : public ClassClosure
{
public:
  MouseClass(VTable *vtable): ClassClosure(vtable){}
  ~MouseClass(){}
  
  virtual ScriptObject* createInstance(VTable* ivtable, ScriptObject* prototype)
  {
    return new (core()->GetGC(), ivtable->getExtraSize()) MouseObject(ivtable, prototype);
  }  
  
  void hide()
  {
    return (void)0;
  }

  void set_cursor(AvmString value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "MouseClass", "set_cursor" );
    return (void)0;
  }

  void show()
  {
    return (void)0;
  }

  AvmString get_cursor()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "MouseClass", "get_cursor" );
    return (AvmString)0;
  }


private:
  DECLARE_SLOTS_MouseClass;
};

}