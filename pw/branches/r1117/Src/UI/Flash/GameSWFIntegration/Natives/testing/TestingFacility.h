#pragma once
#include "System/SystemLog.h"
#include "../PlayerGlobalIncludes.h"

namespace avmplus
{


class TestingFacilityObject: public ScriptObject
{
public:
  TestingFacilityObject(VTable *ivtable, ScriptObject *delegate):ScriptObject(ivtable, delegate) {}
  ~TestingFacilityObject(void) {}


private:
  DECLARE_SLOTS_TestingFacilityObject;
};
  
class TestingFacilityClass : public ClassClosure
{
public:
  TestingFacilityClass(VTable *vtable): ClassClosure(vtable){}
  ~TestingFacilityClass(){}
  
  virtual ScriptObject* createInstance(VTable* ivtable, ScriptObject* prototype)
  {
    return new (core()->GetGC(), ivtable->getExtraSize()) TestingFacilityObject(ivtable, prototype);
  }  
  
  AvmBox AssertImpl(bool expression, AvmString msg);


private:
  DECLARE_SLOTS_TestingFacilityClass;
};

}