#pragma once
#include "System/SystemLog.h"
#include "PlayerGlobalIncludes.h"

namespace avmplus
{
class XMLTagObject;


class XMLParserObject: public ScriptObject
{
public:
  XMLParserObject(VTable *ivtable, ScriptObject *delegate):ScriptObject(ivtable, delegate) {}
  ~XMLParserObject(void) {}

  int getNext(XMLTagObject* tag)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "XMLParserObject", "getNext" );
    return (int)0;
  }

  void startParse(AvmString source, bool ignoreWhite)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "XMLParserObject", "startParse" );
    return (void)0;
  }


private:
  DECLARE_SLOTS_XMLParserObject;
};
  
class XMLParserClass : public ClassClosure
{
public:
  XMLParserClass(VTable *vtable): ClassClosure(vtable){}
  ~XMLParserClass(){}
  
  virtual ScriptObject* createInstance(VTable* ivtable, ScriptObject* prototype)
  {
    return new (core()->GetGC(), ivtable->getExtraSize()) XMLParserObject(ivtable, prototype);
  }  
  

private:
  DECLARE_SLOTS_XMLParserClass;
};

}