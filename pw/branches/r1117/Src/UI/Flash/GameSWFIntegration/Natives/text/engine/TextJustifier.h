#pragma once
#include "System/SystemLog.h"
#include "PlayerGlobalIncludes.h"

namespace avmplus
{


class TextJustifierObject: public ScriptObject
{
public:
  TextJustifierObject(VTable *ivtable, ScriptObject *delegate):ScriptObject(ivtable, delegate) {}
  ~TextJustifierObject(void) {}

  void set_lineJustification(AvmString value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextJustifierObject", "set_lineJustification" );
    return (void)0;
  }

  AvmString get_locale()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextJustifierObject", "get_locale" );
    return (AvmString)0;
  }

  void setLocale(AvmString value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextJustifierObject", "setLocale" );
    return (void)0;
  }

  AvmString get_lineJustification()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextJustifierObject", "get_lineJustification" );
    return (AvmString)0;
  }


private:
  DECLARE_SLOTS_TextJustifierObject;
};
  
class TextJustifierClass : public ClassClosure
{
public:
  TextJustifierClass(VTable *vtable): ClassClosure(vtable){}
  ~TextJustifierClass(){}
  
  virtual ScriptObject* createInstance(VTable* ivtable, ScriptObject* prototype)
  {
    return new (core()->GetGC(), ivtable->getExtraSize()) TextJustifierObject(ivtable, prototype);
  }  
  

private:
  DECLARE_SLOTS_TextJustifierClass;
};

}