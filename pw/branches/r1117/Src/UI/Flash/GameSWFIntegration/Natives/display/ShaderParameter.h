#pragma once
#include "System/SystemLog.h"
#include "PlayerGlobalIncludes.h"

namespace avmplus
{
class ArrayObject;


class ShaderParameterObject: public ScriptObject
{
public:
  ShaderParameterObject(VTable *ivtable, ScriptObject *delegate):ScriptObject(ivtable, delegate) {}
  ~ShaderParameterObject(void) {}

  ArrayObject* get_value()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ShaderParameterObject", "get_value" );
    return (ArrayObject*)0;
  }

  void set_value(ArrayObject* v)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ShaderParameterObject", "set_value" );
    return (void)0;
  }

  AvmString get_type()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ShaderParameterObject", "get_type" );
    return (AvmString)0;
  }

  int get_index()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ShaderParameterObject", "get_index" );
    return (int)0;
  }


private:
  DECLARE_SLOTS_ShaderParameterObject;
};
  
class ShaderParameterClass : public ClassClosure
{
public:
  ShaderParameterClass(VTable *vtable): ClassClosure(vtable){}
  ~ShaderParameterClass(){}
  
  virtual ScriptObject* createInstance(VTable* ivtable, ScriptObject* prototype)
  {
    return new (core()->GetGC(), ivtable->getExtraSize()) ShaderParameterObject(ivtable, prototype);
  }  
  

private:
  DECLARE_SLOTS_ShaderParameterClass;
};

}