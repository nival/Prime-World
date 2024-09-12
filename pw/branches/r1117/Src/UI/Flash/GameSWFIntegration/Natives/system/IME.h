#pragma once
#include "System/SystemLog.h"
#include "PlayerGlobalIncludes.h"
#include "../events/EventDispatcher.h"

namespace avmplus
{


class IMEObject: public EventDispatcherObject
{
public:
  //TODO fix args
  IMEObject(VTable *ivtable, ScriptObject *delegate):EventDispatcherObject(ivtable, delegate) {}
  ~IMEObject(void) {}


private:
  DECLARE_SLOTS_IMEObject;
};
  
class IMEClass : public EventDispatcherClass
{
public:
  IMEClass(VTable *vtable): EventDispatcherClass(vtable){}
  ~IMEClass(){}
  
  /*virtual ScriptObject* createInstance(VTable* ivtable, ScriptObject* prototype)
  {
    return new (core()->GetGC(), ivtable->getExtraSize()) IMEObject(ivtable, prototype);
  }*/  
  
  void setCompositionString(AvmString composition)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "IMEClass", "setCompositionString" );
    return (void)0;
  }

  bool get_enabled()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "IMEClass", "get_enabled" );
    return (bool)0;
  }

  void set_conversionMode(AvmString mode)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "IMEClass", "set_conversionMode" );
    return (void)0;
  }

  void set_constructOK(bool construct)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "IMEClass", "set_constructOK" );
    return (void)0;
  }

  void doConversion()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "IMEClass", "doConversion" );
    return (void)0;
  }

  AvmString get_conversionMode()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "IMEClass", "get_conversionMode" );
    return (AvmString)0;
  }

  void set_enabled(bool enabled)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "IMEClass", "set_enabled" );
    return (void)0;
  }


private:
  DECLARE_SLOTS_IMEClass;
};

}