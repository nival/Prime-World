#pragma once
#include "System/SystemLog.h"
#include "PlayerGlobalIncludes.h"

namespace avmplus
{


class DynamicPropertyOutputObject: public ScriptObject
{
public:
  DynamicPropertyOutputObject(VTable *ivtable, ScriptObject *delegate):ScriptObject(ivtable, delegate) {}
  ~DynamicPropertyOutputObject(void) {}

  void writeDynamicProperty(AvmString name, AvmBox value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "DynamicPropertyOutputObject", "writeDynamicProperty" );
    return (void)0;
  }


private:
  DECLARE_SLOTS_DynamicPropertyOutputObject;
};
  
class DynamicPropertyOutputClass : public ClassClosure
{
public:
  DynamicPropertyOutputClass(VTable *vtable): ClassClosure(vtable){}
  ~DynamicPropertyOutputClass(){}
  
  virtual ScriptObject* createInstance(VTable* ivtable, ScriptObject* prototype)
  {
    return new (core()->GetGC(), ivtable->getExtraSize()) DynamicPropertyOutputObject(ivtable, prototype);
  }  
  

private:
  DECLARE_SLOTS_DynamicPropertyOutputClass;
};

}