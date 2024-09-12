#pragma once
#include "System/SystemLog.h"
#include "PlayerGlobalIncludes.h"
#include "TextJustifier.h"

namespace avmplus
{


class SpaceJustifierObject: public TextJustifierObject
{
public:
  SpaceJustifierObject(VTable *ivtable, ScriptObject *delegate):TextJustifierObject(ivtable, delegate) {}
  ~SpaceJustifierObject(void) {}

  void set_letterSpacing(bool value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "SpaceJustifierObject", "set_letterSpacing" );
    return (void)0;
  }

  bool get_letterSpacing()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "SpaceJustifierObject", "get_letterSpacing" );
    return (bool)0;
  }


private:
  DECLARE_SLOTS_SpaceJustifierObject;
};
  
class SpaceJustifierClass : public ClassClosure
{
public:
  SpaceJustifierClass(VTable *vtable): ClassClosure(vtable){}
  ~SpaceJustifierClass(){}
  
  virtual ScriptObject* createInstance(VTable* ivtable, ScriptObject* prototype)
  {
    return new (core()->GetGC(), ivtable->getExtraSize()) SpaceJustifierObject(ivtable, prototype);
  }  
  

private:
  DECLARE_SLOTS_SpaceJustifierClass;
};

}