#pragma once
#include "System/SystemLog.h"
#include "PlayerGlobalIncludes.h"
#include "TextJustifier.h"

namespace avmplus
{


class EastAsianJustifierObject: public TextJustifierObject
{
public:
  EastAsianJustifierObject(VTable *ivtable, ScriptObject *delegate):TextJustifierObject(ivtable, delegate) {}
  ~EastAsianJustifierObject(void) {}

  void set_justificationStyle(AvmString value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "EastAsianJustifierObject", "set_justificationStyle" );
    return (void)0;
  }

  AvmString get_justificationStyle()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "EastAsianJustifierObject", "get_justificationStyle" );
    return (AvmString)0;
  }


private:
  DECLARE_SLOTS_EastAsianJustifierObject;
};
  
class EastAsianJustifierClass : public ClassClosure
{
public:
  EastAsianJustifierClass(VTable *vtable): ClassClosure(vtable){}
  ~EastAsianJustifierClass(){}
  
  virtual ScriptObject* createInstance(VTable* ivtable, ScriptObject* prototype)
  {
    return new (core()->GetGC(), ivtable->getExtraSize()) EastAsianJustifierObject(ivtable, prototype);
  }  
  

private:
  DECLARE_SLOTS_EastAsianJustifierClass;
};

}