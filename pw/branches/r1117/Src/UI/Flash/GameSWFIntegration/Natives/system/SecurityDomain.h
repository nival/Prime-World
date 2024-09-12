#pragma once
#include "System/SystemLog.h"
#include "PlayerGlobalIncludes.h"

namespace avmplus
{
class SecurityDomainObject;


class SecurityDomainObject: public ScriptObject
{
public:
  SecurityDomainObject(VTable *ivtable, ScriptObject *delegate):ScriptObject(ivtable, delegate) {}
  ~SecurityDomainObject(void) {}


private:
  DECLARE_SLOTS_SecurityDomainObject;
};
  
class SecurityDomainClass : public ClassClosure
{
public:
  SecurityDomainClass(VTable *vtable): ClassClosure(vtable){}
  ~SecurityDomainClass(){}
  
  virtual ScriptObject* createInstance(VTable* ivtable, ScriptObject* prototype)
  {
    return new (core()->GetGC(), ivtable->getExtraSize()) SecurityDomainObject(ivtable, prototype);
  }  
  
  SecurityDomainObject* get_currentDomain()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "SecurityDomainClass", "get_currentDomain" );
    return (SecurityDomainObject*)0;
  }


private:
  DECLARE_SLOTS_SecurityDomainClass;
};

}