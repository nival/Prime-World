#pragma once
#include "System/SystemLog.h"
#include "PlayerGlobalIncludes.h"

namespace avmplus
{


class XMLTagObject: public ScriptObject
{
public:
  XMLTagObject(VTable *ivtable, ScriptObject *delegate):ScriptObject(ivtable, delegate) {}
  ~XMLTagObject(void) {}

  AvmString get_value()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "XMLTagObject", "get_value" );
    return (AvmString)0;
  }

  void set_value(AvmString v)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "XMLTagObject", "set_value" );
    return (void)0;
  }

  void set_type(uint value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "XMLTagObject", "set_type" );
    return (void)0;
  }

  uint get_type()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "XMLTagObject", "get_type" );
    return (uint)0;
  }

  void set_empty(bool value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "XMLTagObject", "set_empty" );
    return (void)0;
  }

  void set_attrs(AvmBox value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "XMLTagObject", "set_attrs" );
    return (void)0;
  }

  bool get_empty()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "XMLTagObject", "get_empty" );
    return (bool)0;
  }

  AvmBox get_attrs()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "XMLTagObject", "get_attrs" );
    return (AvmBox)0;
  }


private:
  DECLARE_SLOTS_XMLTagObject;
};
  
class XMLTagClass : public ClassClosure
{
public:
  XMLTagClass(VTable *vtable): ClassClosure(vtable){}
  ~XMLTagClass(){}
  
  virtual ScriptObject* createInstance(VTable* ivtable, ScriptObject* prototype)
  {
    return new (core()->GetGC(), ivtable->getExtraSize()) XMLTagObject(ivtable, prototype);
  }  
  

private:
  DECLARE_SLOTS_XMLTagClass;
};

}