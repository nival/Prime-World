#pragma once
#include "System/SystemLog.h"
#include "PlayerGlobalIncludes.h"
#include "ContentElement.h"

namespace avmplus
{


class TextElementObject: public ContentElementObject
{
public:
  TextElementObject(VTable *ivtable, ScriptObject *delegate):ContentElementObject(ivtable, delegate) {}
  ~TextElementObject(void) {}

  void replaceText(int beginIndex, int endIndex, AvmString newText)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextElementObject", "replaceText" );
    return (void)0;
  }

  void set_text(AvmString value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextElementObject", "set_text" );
    return (void)0;
  }


private:
  DECLARE_SLOTS_TextElementObject;
};
  
class TextElementClass : public ClassClosure
{
public:
  TextElementClass(VTable *vtable): ClassClosure(vtable){}
  ~TextElementClass(){}
  
  virtual ScriptObject* createInstance(VTable* ivtable, ScriptObject* prototype)
  {
    return new (core()->GetGC(), ivtable->getExtraSize()) TextElementObject(ivtable, prototype);
  }  
  

private:
  DECLARE_SLOTS_TextElementClass;
};

}