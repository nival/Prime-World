#pragma once
#include "System/SystemLog.h"
#include "PlayerGlobalIncludes.h"

namespace avmplus
{


class XMLNodeObject: public ScriptObject
{
public:
  XMLNodeObject(VTable *ivtable, ScriptObject *delegate):ScriptObject(ivtable, delegate) {}
  ~XMLNodeObject(void) {}

  AvmString escapeXML(AvmString value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "XMLNodeObject", "escapeXML" );
    return (AvmString)0;
  }


private:
  DECLARE_SLOTS_XMLNodeObject;
};
  
class XMLNodeClass : public ClassClosure
{
public:
  XMLNodeClass(VTable *vtable): ClassClosure(vtable){}
  ~XMLNodeClass(){}
  
  virtual ScriptObject* createInstance(VTable* ivtable, ScriptObject* prototype)
  {
    return new (core()->GetGC(), ivtable->getExtraSize()) XMLNodeObject(ivtable, prototype);
  }  
  

private:
  DECLARE_SLOTS_XMLNodeClass;
};

}