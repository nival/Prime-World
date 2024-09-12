#pragma once
#include "System/SystemLog.h"
#include "../PlayerGlobalIncludes.h"
#include "../../FlashBaseClasses.h"

namespace avmplus
{
class ApplicationDomainObject;
class ByteArrayObject;


class ApplicationDomainObject: public FlashScriptObject
{
public:
  ApplicationDomainObject(VTable *ivtable, ScriptObject *delegate):FlashScriptObject(ivtable, delegate) {}
  ~ApplicationDomainObject(void) {}

  AvmBox getDefinition(AvmString name);
  bool hasDefinition(AvmString name);


  ByteArrayObject* get_domainMemory()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ApplicationDomainObject", "get_domainMemory" );
    return (ByteArrayObject*)0;
  }
  
  AvmBox set_domainMemory(ByteArrayObject* mem)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ApplicationDomainObject", "set_domainMemory" );
    return (AvmBox)0;
  }
 

  ApplicationDomainObject* get_parentDomain()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ApplicationDomainObject", "get_parentDomain" );
    return (ApplicationDomainObject*)0;
  }

private:

  //TODO refactor this. outEnv looks ugly
  Traits * FindTraits( AvmString name,  ScriptEnv* & outEnv );

  DECLARE_SLOTS_ApplicationDomainObject;
};
  
class ApplicationDomainClass : public FlashClassClosure
{
  //its supposed that we have only a single application domain instance

  DRCWB(ApplicationDomainObject*) applicationDomain; 

public:
  ApplicationDomainClass(VTable *vtable): FlashClassClosure(vtable)
  {
    applicationDomain = new (core()->GetGC(), ivtable()->getExtraSize()) ApplicationDomainObject(ivtable(), prototype);
  }

  ~ApplicationDomainClass(){}
  
  virtual ScriptObject* createInstance(VTable* ivtable, ScriptObject* prototype)
  {
    NI_ALWAYS_ASSERT("no ctor here!");
    return 0;
    //return new (core()->GetGC(), ivtable->getExtraSize()) ApplicationDomainObject(ivtable, prototype);
  }  
  
  ApplicationDomainObject* get_currentDomain()
  {
    return applicationDomain;
  }

  uint get_MIN_DOMAIN_MEMORY_LENGTH()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ApplicationDomainClass", "get_MIN_DOMAIN_MEMORY_LENGTH" );
    return (uint)0;
  }


private:
  DECLARE_SLOTS_ApplicationDomainClass;
};

}