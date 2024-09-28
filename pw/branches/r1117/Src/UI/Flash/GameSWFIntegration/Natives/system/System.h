#pragma once
#include "System/SystemLog.h"
#include "PlayerGlobalIncludes.h"

namespace avmplus
{


class SystemObject: public ScriptObject
{
public:
  SystemObject(VTable *ivtable, ScriptObject *delegate):ScriptObject(ivtable, delegate) {}
  ~SystemObject(void) {}


private:
  DECLARE_SLOTS_SystemObject;
};
  
class SystemClass : public ClassClosure
{
public:
  SystemClass(VTable *vtable): ClassClosure(vtable){}
  ~SystemClass(){}
  
  virtual ScriptObject* createInstance(VTable* ivtable, ScriptObject* prototype)
  {
    return new (core()->GetGC(), ivtable->getExtraSize()) SystemObject(ivtable, prototype);
  }  
  
  bool get_useCodePage()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "SystemClass", "get_useCodePage" );
    return (bool)0;
  }

  uint get_totalMemory()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "SystemClass", "get_totalMemory" );
    return (uint)0;
  }

  void set_useCodePage(bool value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "SystemClass", "set_useCodePage" );
    return (void)0;
  }

  AvmString get_vmVersion()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "SystemClass", "get_vmVersion" );
    return (AvmString)0;
  }

  void resume()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "SystemClass", "resume" );
    return (void)0;
  }

  void setClipboard(AvmString string)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "SystemClass", "setClipboard" );
    return (void)0;
  }

  void pause()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "SystemClass", "pause" );
    return (void)0;
  }

  void gc()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "SystemClass", "gc" );
    return (void)0;
  }

  void exit(uint code)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "SystemClass", "exit" );
    return (void)0;
  }


private:
  DECLARE_SLOTS_SystemClass;
};

}