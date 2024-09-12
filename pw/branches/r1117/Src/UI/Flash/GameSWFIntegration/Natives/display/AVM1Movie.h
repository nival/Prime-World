#pragma once
#include "System/SystemLog.h"
#include "PlayerGlobalIncludes.h"
#include "DisplayObject.h"

namespace avmplus
{
class FunctionObject;
class ByteArrayObject;


class AVM1MovieObject: public DisplayObjectObject
{
public:
  //TODO fix args
  AVM1MovieObject(VTable *ivtable, ScriptObject *delegate):DisplayObjectObject(NULL) {}
  ~AVM1MovieObject(void) {}

  void _setCallAS3(FunctionObject* closure)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "AVM1MovieObject", "_setCallAS3" );
    return (void)0;
  }

  ByteArrayObject* _callAS2(AvmString functionName, ByteArrayObject* arguments)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "AVM1MovieObject", "_callAS2" );
    return (ByteArrayObject*)0;
  }

  bool get__interopAvailable()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "AVM1MovieObject", "get__interopAvailable" );
    return (bool)0;
  }


private:
  DECLARE_SLOTS_AVM1MovieObject;
};
  
class AVM1MovieClass : public ClassClosure
{
public:
  AVM1MovieClass(VTable *vtable): ClassClosure(vtable){}
  ~AVM1MovieClass(){}
  
  virtual ScriptObject* createInstance(VTable* ivtable, ScriptObject* prototype)
  {
    return new (core()->GetGC(), ivtable->getExtraSize()) AVM1MovieObject(ivtable, prototype);
  }  
  

private:
  DECLARE_SLOTS_AVM1MovieClass;
};

}