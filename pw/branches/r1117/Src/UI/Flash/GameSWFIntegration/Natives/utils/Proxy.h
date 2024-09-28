#pragma once
#include "System/SystemLog.h"
#include "PlayerGlobalIncludes.h"

namespace avmplus
{


class ProxyObject: public ScriptObject
{
public:
  ProxyObject(VTable *ivtable, ScriptObject *delegate):ScriptObject(ivtable, delegate) {}
  ~ProxyObject(void) {}

  bool isAttribute(AvmBox name)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ProxyObject", "isAttribute" );
    return (bool)0;
  }


private:
  DECLARE_SLOTS_ProxyObject;
};
  
class ProxyClass : public ClassClosure
{
public:
  ProxyClass(VTable *vtable): ClassClosure(vtable){}
  ~ProxyClass(){}
  
  virtual ScriptObject* createInstance(VTable* ivtable, ScriptObject* prototype)
  {
    return new (core()->GetGC(), ivtable->getExtraSize()) ProxyObject(ivtable, prototype);
  }  
  

private:
  DECLARE_SLOTS_ProxyClass;
};

}