#pragma once
#include "System/SystemLog.h"
#include "PlayerGlobalIncludes.h"

namespace avmplus
{
class ByteArrayObject;


class ShaderDataObject: public ScriptObject
{
public:
  ShaderDataObject(VTable *ivtable, ScriptObject *delegate):ScriptObject(ivtable, delegate) {}
  ~ShaderDataObject(void) {}

  void _setByteCode(ByteArrayObject* code)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ShaderDataObject", "_setByteCode" );
    return (void)0;
  }


private:
  DECLARE_SLOTS_ShaderDataObject;
};
  
class ShaderDataClass : public ClassClosure
{
public:
  ShaderDataClass(VTable *vtable): ClassClosure(vtable){}
  ~ShaderDataClass(){}
  
  virtual ScriptObject* createInstance(VTable* ivtable, ScriptObject* prototype)
  {
    return new (core()->GetGC(), ivtable->getExtraSize()) ShaderDataObject(ivtable, prototype);
  }  
  

private:
  DECLARE_SLOTS_ShaderDataClass;
};

}