#pragma once
#include "System/SystemLog.h"
#include "PlayerGlobalIncludes.h"
#include "../events/EventDispatcher.h"

namespace avmplus
{
class SoundTransformObject;
class ArrayObject;
class NetConnectionObject;
class ScriptObject;


class NetStreamObject: public EventDispatcherObject
{
public:
  NetStreamObject(VTable *ivtable, ScriptObject *delegate):EventDispatcherObject(ivtable, delegate) {}
  ~NetStreamObject(void) {}

  void set_soundTransform(SoundTransformObject* sndTransform)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "NetStreamObject", "set_soundTransform" );
    return (void)0;
  }

  ArrayObject* get_peerStreams()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "NetStreamObject", "get_peerStreams" );
    return (ArrayObject*)0;
  }

  AvmBox get_client()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "NetStreamObject", "get_client" );
    return (AvmBox)0;
  }

  AvmBox invokeWithArgsArray(uint index, ArrayObject* p_arguments)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "NetStreamObject", "invokeWithArgsArray" );
    return (AvmBox)0;
  }

  void set_client(AvmBox object)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "NetStreamObject", "set_client" );
    return (void)0;
  }

  void construct(NetConnectionObject* connection, AvmString peerID)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "NetStreamObject", "construct" );
    return (void)0;
  }

  void onResult(int streamId)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "NetStreamObject", "onResult" );
    return (void)0;
  }

  SoundTransformObject* get_soundTransform()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "NetStreamObject", "get_soundTransform" );
    return (SoundTransformObject*)0;
  }

  AvmString get_farNonce()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "NetStreamObject", "get_farNonce" );
    return (AvmString)0;
  }

  AvmString get_nearNonce()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "NetStreamObject", "get_nearNonce" );
    return (AvmString)0;
  }

  void set_checkPolicyFile(bool state)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "NetStreamObject", "set_checkPolicyFile" );
    return (void)0;
  }

  ScriptObject/*NetStreamInfo*/ * get_info()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "NetStreamObject", "get_info" );
    return (ScriptObject/*NetStreamInfo*/ *)0;
  }

  uint get_objectEncoding()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "NetStreamObject", "get_objectEncoding" );
    return (uint)0;
  }

  AvmBox invoke(uint index, AvmBox args)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "NetStreamObject", "invoke" );
    return (AvmBox)0;
  }

  AvmString get_farID()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "NetStreamObject", "get_farID" );
    return (AvmString)0;
  }

  void play(AvmBox args)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "NetStreamObject", "play" );
    return (void)0;
  }

  bool get_checkPolicyFile()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "NetStreamObject", "get_checkPolicyFile" );
    return (bool)0;
  }

  void play2(ScriptObject/*NetStreamPlayOptions*/ * param)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "NetStreamObject", "play2" );
    return (void)0;
  }


private:
  DECLARE_SLOTS_NetStreamObject;
};
  
class NetStreamClass : public ClassClosure
{
public:
  NetStreamClass(VTable *vtable): ClassClosure(vtable){}
  ~NetStreamClass(){}
  
  virtual ScriptObject* createInstance(VTable* ivtable, ScriptObject* prototype)
  {
    return new (core()->GetGC(), ivtable->getExtraSize()) NetStreamObject(ivtable, prototype);
  }  
  

private:
  DECLARE_SLOTS_NetStreamClass;
};

}