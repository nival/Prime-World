#pragma once
#include "System/SystemLog.h"
#include "PlayerGlobalIncludes.h"

namespace avmplus
{


class ShaderInputObject: public ScriptObject
{
public:
  ShaderInputObject(VTable *ivtable, ScriptObject *delegate):ScriptObject(ivtable, delegate) {}
  ~ShaderInputObject(void) {}

  int get_channels()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ShaderInputObject", "get_channels" );
    return (int)0;
  }

  int get_index()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ShaderInputObject", "get_index" );
    return (int)0;
  }

  void set_input(AvmBox input)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ShaderInputObject", "set_input" );
    return (void)0;
  }

  int get_width()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ShaderInputObject", "get_width" );
    return (int)0;
  }

  int get_height()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ShaderInputObject", "get_height" );
    return (int)0;
  }

  AvmBox get_input()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ShaderInputObject", "get_input" );
    return (AvmBox)0;
  }

  void set_width(int value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ShaderInputObject", "set_width" );
    return (void)0;
  }

  void set_height(int value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ShaderInputObject", "set_height" );
    return (void)0;
  }


private:
  DECLARE_SLOTS_ShaderInputObject;
};
  
class ShaderInputClass : public ClassClosure
{
public:
  ShaderInputClass(VTable *vtable): ClassClosure(vtable){}
  ~ShaderInputClass(){}
  
  virtual ScriptObject* createInstance(VTable* ivtable, ScriptObject* prototype)
  {
    return new (core()->GetGC(), ivtable->getExtraSize()) ShaderInputObject(ivtable, prototype);
  }  
  

private:
  DECLARE_SLOTS_ShaderInputClass;
};

}