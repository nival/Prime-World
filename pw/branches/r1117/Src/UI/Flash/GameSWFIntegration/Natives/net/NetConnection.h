#pragma once
#include "System/SystemLog.h"
#include "PlayerGlobalIncludes.h"
#include "../events/EventDispatcher.h"

namespace avmplus
{
class ArrayObject;


class NetConnectionObject: public EventDispatcherObject
{
public:
  NetConnectionObject(VTable *ivtable, ScriptObject *delegate):EventDispatcherObject(ivtable, delegate) {}
  ~NetConnectionObject(void) {}

  ArrayObject* get_unconnectedPeerStreams()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "NetConnectionObject", "get_unconnectedPeerStreams" );
    return (ArrayObject*)0;
  }

  AvmString get_nearID()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "NetConnectionObject", "get_nearID" );
    return (AvmString)0;
  }

  void set_objectEncoding(uint version)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "NetConnectionObject", "set_objectEncoding" );
    return (void)0;
  }

  void set_maxPeerConnections(uint maxPeers)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "NetConnectionObject", "set_maxPeerConnections" );
    return (void)0;
  }

  AvmString get_protocol()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "NetConnectionObject", "get_protocol" );
    return (AvmString)0;
  }

  AvmString get_proxyType()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "NetConnectionObject", "get_proxyType" );
    return (AvmString)0;
  }

  bool get_connected()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "NetConnectionObject", "get_connected" );
    return (bool)0;
  }

  void connect(AvmString command, AvmBox args)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "NetConnectionObject", "connect" );
    return (void)0;
  }

  AvmBox get_client()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "NetConnectionObject", "get_client" );
    return (AvmBox)0;
  }

  AvmString get_uri()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "NetConnectionObject", "get_uri" );
    return (AvmString)0;
  }

  AvmBox invokeWithArgsArray(uint index, ArrayObject* args)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "NetConnectionObject", "invokeWithArgsArray" );
    return (AvmBox)0;
  }

  uint get_maxPeerConnections()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "NetConnectionObject", "get_maxPeerConnections" );
    return (uint)0;
  }

  void set_proxyType(AvmString ptype)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "NetConnectionObject", "set_proxyType" );
    return (void)0;
  }

  AvmBox invoke(uint index, AvmBox args)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "NetConnectionObject", "invoke" );
    return (AvmBox)0;
  }

  uint get_objectEncoding()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "NetConnectionObject", "get_objectEncoding" );
    return (uint)0;
  }

  AvmString get_nearNonce()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "NetConnectionObject", "get_nearNonce" );
    return (AvmString)0;
  }

  void set_client(AvmBox object)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "NetConnectionObject", "set_client" );
    return (void)0;
  }

  bool get_usingTLS()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "NetConnectionObject", "get_usingTLS" );
    return (bool)0;
  }

  AvmString get_farID()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "NetConnectionObject", "get_farID" );
    return (AvmString)0;
  }

  AvmString get_farNonce()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "NetConnectionObject", "get_farNonce" );
    return (AvmString)0;
  }

  AvmString get_connectedProxyType()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "NetConnectionObject", "get_connectedProxyType" );
    return (AvmString)0;
  }


private:
  DECLARE_SLOTS_NetConnectionObject;
};
  
class NetConnectionClass : public ClassClosure
{
public:
  NetConnectionClass(VTable *vtable): ClassClosure(vtable){}
  ~NetConnectionClass(){}
  
  virtual ScriptObject* createInstance(VTable* ivtable, ScriptObject* prototype)
  {
    return new (core()->GetGC(), ivtable->getExtraSize()) NetConnectionObject(ivtable, prototype);
  }  
  
  void set_defaultObjectEncoding(uint version)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "NetConnectionClass", "set_defaultObjectEncoding" );
    return (void)0;
  }

  uint get_defaultObjectEncoding()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "NetConnectionClass", "get_defaultObjectEncoding" );
    return (uint)0;
  }


private:
  DECLARE_SLOTS_NetConnectionClass;
};

}