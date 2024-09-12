#pragma once
#include "System/SystemLog.h"
#include "PlayerGlobalIncludes.h"

namespace avmplus
{
class FunctionObject;


class ResponderObject: public ScriptObject
{
public:
  ResponderObject(VTable *ivtable, ScriptObject *delegate):ScriptObject(ivtable, delegate) {}
  ~ResponderObject(void) {}

  AvmBox Responder(FunctionObject* result, FunctionObject* status)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ResponderObject", "Responder" );
    return (AvmBox)0;
  }


private:
  DECLARE_SLOTS_ResponderObject;
};
  
class ResponderClass : public ClassClosure
{
public:
  ResponderClass(VTable *vtable): ClassClosure(vtable){}
  ~ResponderClass(){}
  
  virtual ScriptObject* createInstance(VTable* ivtable, ScriptObject* prototype)
  {
    return new (core()->GetGC(), ivtable->getExtraSize()) ResponderObject(ivtable, prototype);
  }  
  

private:
  DECLARE_SLOTS_ResponderClass;
};

}