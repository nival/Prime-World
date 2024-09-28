#pragma once
#include "System/SystemLog.h"
#include "PlayerGlobalIncludes.h"

namespace avmplus
{
class ScriptObject;


class ObjectEncodingObject: public ScriptObject
{
public:
  ObjectEncodingObject(VTable *ivtable, ScriptObject *delegate):ScriptObject(ivtable, delegate) {}
  ~ObjectEncodingObject(void) {}


private:
  DECLARE_SLOTS_ObjectEncodingObject;
};
  
class ObjectEncodingClass : public ClassClosure
{
public:
  ObjectEncodingClass(VTable *vtable): ClassClosure(vtable){}
  ~ObjectEncodingClass(){}
  
  virtual ScriptObject* createInstance(VTable* ivtable, ScriptObject* prototype)
  {
    return new (core()->GetGC(), ivtable->getExtraSize()) ObjectEncodingObject(ivtable, prototype);
  }  
  
  ScriptObject/*IDynamicPropertyWriter*/ * get_dynamicPropertyWriter()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ObjectEncodingClass", "get_dynamicPropertyWriter" );
    return (ScriptObject/*IDynamicPropertyWriter*/ *)0;
  }

  void set_dynamicPropertyWriter(ScriptObject/*IDynamicPropertyWriter*/ * object)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ObjectEncodingClass", "set_dynamicPropertyWriter" );
    return (void)0;
  }


private:
  DECLARE_SLOTS_ObjectEncodingClass;
};

}