#pragma once
#include "System/SystemLog.h"
#include "PlayerGlobalIncludes.h"

namespace avmplus
{


class WeakMethodClosureObject: public ScriptObject
{
public:
  WeakMethodClosureObject(VTable *ivtable, ScriptObject *delegate):ScriptObject(ivtable, delegate) {}
  ~WeakMethodClosureObject(void) {}

  AvmBox get_savedThis()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "WeakMethodClosureObject", "get_savedThis" );
    return (AvmBox)0;
  }


private:
  DECLARE_SLOTS_WeakMethodClosureObject;
};
  
class WeakMethodClosureClass : public ClassClosure
{
public:
  WeakMethodClosureClass(VTable *vtable): ClassClosure(vtable){}
  ~WeakMethodClosureClass(){}
  
  virtual ScriptObject* createInstance(VTable* ivtable, ScriptObject* prototype)
  {
    return new (core()->GetGC(), ivtable->getExtraSize()) WeakMethodClosureObject(ivtable, prototype);
  }  
  

private:
  DECLARE_SLOTS_WeakMethodClosureClass;
};

}