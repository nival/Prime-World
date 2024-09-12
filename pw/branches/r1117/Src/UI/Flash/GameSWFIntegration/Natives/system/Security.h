#pragma once
#include "System/SystemLog.h"
#include "PlayerGlobalIncludes.h"

namespace avmplus
{


class SecurityObject: public ScriptObject
{
public:
  SecurityObject(VTable *ivtable, ScriptObject *delegate):ScriptObject(ivtable, delegate) {}
  ~SecurityObject(void) {}


private:
  DECLARE_SLOTS_SecurityObject;
};
  
class SecurityClass : public ClassClosure
{
public:
  SecurityClass(VTable *vtable): ClassClosure(vtable){}
  ~SecurityClass(){}
  
  virtual ScriptObject* createInstance(VTable* ivtable, ScriptObject* prototype)
  {
    return new (core()->GetGC(), ivtable->getExtraSize()) SecurityObject(ivtable, prototype);
  }  
  
  void showSettings(AvmString panel)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "SecurityClass", "showSettings" );
    return (void)0;
  }

  AvmString get_sandboxType()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "SecurityClass", "get_sandboxType" );
    return (AvmString)0;
  }

  bool get_exactSettings()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "SecurityClass", "get_exactSettings" );
    return (bool)0;
  }

  void set_exactSettings(bool value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "SecurityClass", "set_exactSettings" );
    return (void)0;
  }

  void allowDomain(AvmBox args)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "SecurityClass", "allowDomain" );
    return (void)0;
  }

  void allowInsecureDomain(AvmBox args)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "SecurityClass", "allowInsecureDomain" );
    return (void)0;
  }

  void loadPolicyFile(AvmString url)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "SecurityClass", "loadPolicyFile" );
    return (void)0;
  }

  void set_disableAVM1Loading(bool value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "SecurityClass", "set_disableAVM1Loading" );
    return (void)0;
  }

  bool get_disableAVM1Loading()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "SecurityClass", "get_disableAVM1Loading" );
    return (bool)0;
  }


private:
  DECLARE_SLOTS_SecurityClass;
};

}