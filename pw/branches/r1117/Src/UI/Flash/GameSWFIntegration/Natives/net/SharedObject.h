#pragma once
#include "System/SystemLog.h"
#include "PlayerGlobalIncludes.h"
#include "../events/EventDispatcher.h"

namespace avmplus
{
class SharedObjectObject;
class ArrayObject;


class SharedObjectObject: public EventDispatcherObject
{
public:
  SharedObjectObject(VTable *ivtable, ScriptObject *delegate):EventDispatcherObject(ivtable, delegate) {}
  ~SharedObjectObject(void) {}

  AvmBox get_data()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "SharedObjectObject", "get_data" );
    return (AvmBox)0;
  }

  AvmBox get_client()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "SharedObjectObject", "get_client" );
    return (AvmBox)0;
  }

  void setDirty(AvmString propertyName)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "SharedObjectObject", "setDirty" );
    return (void)0;
  }

  void set_objectEncoding(uint version)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "SharedObjectObject", "set_objectEncoding" );
    return (void)0;
  }

  void set_client(AvmBox object)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "SharedObjectObject", "set_client" );
    return (void)0;
  }

  uint get_objectEncoding()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "SharedObjectObject", "get_objectEncoding" );
    return (uint)0;
  }

  AvmBox invokeWithArgsArray(uint index, ArrayObject* args)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "SharedObjectObject", "invokeWithArgsArray" );
    return (AvmBox)0;
  }

  AvmBox invoke(uint index, AvmBox args)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "SharedObjectObject", "invoke" );
    return (AvmBox)0;
  }


private:
  DECLARE_SLOTS_SharedObjectObject;
};
  
class SharedObjectClass : public ClassClosure
{
public:
  SharedObjectClass(VTable *vtable): ClassClosure(vtable){}
  ~SharedObjectClass(){}
  
  virtual ScriptObject* createInstance(VTable* ivtable, ScriptObject* prototype)
  {
    return new (core()->GetGC(), ivtable->getExtraSize()) SharedObjectObject(ivtable, prototype);
  }  
  
  void set_defaultObjectEncoding(uint version)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "SharedObjectClass", "set_defaultObjectEncoding" );
    return (void)0;
  }

  int getDiskUsage(AvmString url)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "SharedObjectClass", "getDiskUsage" );
    return (int)0;
  }

  uint get_defaultObjectEncoding()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "SharedObjectClass", "get_defaultObjectEncoding" );
    return (uint)0;
  }

  SharedObjectObject* getLocal(AvmString name, AvmString localPath, bool secure)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "SharedObjectClass", "getLocal" );
    return (SharedObjectObject*)0;
  }

  int deleteAll(AvmString url)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "SharedObjectClass", "deleteAll" );
    return (int)0;
  }

  SharedObjectObject* getRemote(AvmString name, AvmString remotePath, AvmBox persistence, bool secure)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "SharedObjectClass", "getRemote" );
    return (SharedObjectObject*)0;
  }


private:
  DECLARE_SLOTS_SharedObjectClass;
};

}