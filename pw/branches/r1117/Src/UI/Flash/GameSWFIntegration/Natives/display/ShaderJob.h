#pragma once
#include "System/SystemLog.h"
#include "PlayerGlobalIncludes.h"
#include "../events/EventDispatcher.h"

namespace avmplus
{
class ShaderObject;


class ShaderJobObject: public EventDispatcherObject
{
public:
  //TODO fix args
  ShaderJobObject(VTable *ivtable, ScriptObject *delegate):EventDispatcherObject(ivtable, delegate) {}
  ~ShaderJobObject(void) {}

  void start(bool waitForCompletion)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ShaderJobObject", "start" );
    return (void)0;
  }

  ShaderObject* get_shader()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ShaderJobObject", "get_shader" );
    return (ShaderObject*)0;
  }

  int get_width()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ShaderJobObject", "get_width" );
    return (int)0;
  }

  int get_height()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ShaderJobObject", "get_height" );
    return (int)0;
  }

  void set_target(AvmBox s)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ShaderJobObject", "set_target" );
    return (void)0;
  }

  void set_shader(ShaderObject* s)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ShaderJobObject", "set_shader" );
    return (void)0;
  }

  void set_width(int v)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ShaderJobObject", "set_width" );
    return (void)0;
  }

  double get_progress()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ShaderJobObject", "get_progress" );
    return (double)0;
  }

  void set_height(int v)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ShaderJobObject", "set_height" );
    return (void)0;
  }

  AvmBox get_target()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ShaderJobObject", "get_target" );
    return (AvmBox)0;
  }

  void cancel()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ShaderJobObject", "cancel" );
    return (void)0;
  }


private:
  DECLARE_SLOTS_ShaderJobObject;
};
  
class ShaderJobClass : public EventDispatcherClass
{
public:
  ShaderJobClass(VTable *vtable): EventDispatcherClass(vtable){}
  ~ShaderJobClass(){}
  
  /*virtual ScriptObject* createInstance(VTable* ivtable, ScriptObject* prototype)
  {
    return new (core()->GetGC(), ivtable->getExtraSize()) ShaderJobObject(ivtable, prototype);
  }*/  
  

private:
  DECLARE_SLOTS_ShaderJobClass;
};

}