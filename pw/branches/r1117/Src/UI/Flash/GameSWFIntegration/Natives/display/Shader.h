#pragma once
#include "System/SystemLog.h"
#include "PlayerGlobalIncludes.h"

namespace avmplus
{
class ShaderDataObject;


class ShaderObject: public ScriptObject
{
public:
  ShaderObject(VTable *ivtable, ScriptObject *delegate):ScriptObject(ivtable, delegate) {}
  ~ShaderObject(void) {}

  void set_data(ShaderDataObject* p)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ShaderObject", "set_data" );
    return (void)0;
  }

  AvmString get_precisionHint()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ShaderObject", "get_precisionHint" );
    return (AvmString)0;
  }

  ShaderDataObject* get_data()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ShaderObject", "get_data" );
    return (ShaderDataObject*)0;
  }

  void set_precisionHint(AvmString p)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ShaderObject", "set_precisionHint" );
    return (void)0;
  }


private:
  DECLARE_SLOTS_ShaderObject;
};
  
class ShaderClass : public ClassClosure
{
public:
  ShaderClass(VTable *vtable): ClassClosure(vtable){}
  ~ShaderClass(){}
  
  virtual ScriptObject* createInstance(VTable* ivtable, ScriptObject* prototype)
  {
    return new (core()->GetGC(), ivtable->getExtraSize()) ShaderObject(ivtable, prototype);
  }  
  

private:
  DECLARE_SLOTS_ShaderClass;
};

}