#pragma once
#include "System/SystemLog.h"
#include "PlayerGlobalIncludes.h"
#include "../events/EventDispatcher.h"

namespace avmplus
{


class LocalConnectionObject: public EventDispatcherObject
{
public:
  LocalConnectionObject(VTable *ivtable, ScriptObject *delegate):EventDispatcherObject(ivtable, delegate) {}
  ~LocalConnectionObject(void) {}

  AvmString get_domain()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "LocalConnectionObject", "get_domain" );
    return (AvmString)0;
  }

  void set_client(AvmBox client)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "LocalConnectionObject", "set_client" );
    return (void)0;
  }

  void close()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "LocalConnectionObject", "close" );
    return (void)0;
  }

  void allowInsecureDomain(AvmBox args)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "LocalConnectionObject", "allowInsecureDomain" );
    return (void)0;
  }

  void connect(AvmString connectionName)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "LocalConnectionObject", "connect" );
    return (void)0;
  }

  AvmBox get_client()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "LocalConnectionObject", "get_client" );
    return (AvmBox)0;
  }

  void allowDomain(AvmBox args)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "LocalConnectionObject", "allowDomain" );
    return (void)0;
  }

  void send(AvmString connectionName, AvmString methodName, AvmBox args)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "LocalConnectionObject", "send" );
    return (void)0;
  }


private:
  DECLARE_SLOTS_LocalConnectionObject;
};
  
class LocalConnectionClass : public ClassClosure
{
public:
  LocalConnectionClass(VTable *vtable): ClassClosure(vtable){}
  ~LocalConnectionClass(){}
  
  virtual ScriptObject* createInstance(VTable* ivtable, ScriptObject* prototype)
  {
    return new (core()->GetGC(), ivtable->getExtraSize()) LocalConnectionObject(ivtable, prototype);
  }  
  

private:
  DECLARE_SLOTS_LocalConnectionClass;
};

}