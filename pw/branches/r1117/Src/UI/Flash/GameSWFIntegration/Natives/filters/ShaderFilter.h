#pragma once
#include "System/SystemLog.h"
#include "PlayerGlobalIncludes.h"
#include "BitmapFilter.h"

namespace avmplus
{
class ScriptObject;
class ShaderObject;


class ShaderFilterObject: public BitmapFilterObject
{
public:
  ShaderFilterObject(VTable *ivtable, ScriptObject *delegate):BitmapFilterObject(ivtable, delegate) {}
  ~ShaderFilterObject(void) {}

  void set__extendBy(ScriptObject/*Rectangle*/ * extend)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ShaderFilterObject", "set__extendBy" );
    return (void)0;
  }

  ShaderObject* get_shader()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ShaderFilterObject", "get_shader" );
    return (ShaderObject*)0;
  }

  void set_shader(ShaderObject* shader)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ShaderFilterObject", "set_shader" );
    return (void)0;
  }

  ScriptObject/*Rectangle*/ * get__extendBy()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ShaderFilterObject", "get__extendBy" );
    return (ScriptObject/*Rectangle*/ *)0;
  }


private:
  DECLARE_SLOTS_ShaderFilterObject;
};
  
class ShaderFilterClass : public ClassClosure
{
public:
  ShaderFilterClass(VTable *vtable): ClassClosure(vtable){}
  ~ShaderFilterClass(){}
  
  virtual ScriptObject* createInstance(VTable* ivtable, ScriptObject* prototype)
  {
    return new (core()->GetGC(), ivtable->getExtraSize()) ShaderFilterObject(ivtable, prototype);
  }  
  

private:
  DECLARE_SLOTS_ShaderFilterClass;
};

}