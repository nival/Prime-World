#pragma once
#include "System/SystemLog.h"
#include "../PlayerGlobalIncludes.h"
#include "../../FlashBaseClasses.h"

namespace avmplus
{

//As dummy as it seems
class CoreWrapperObject: public FlashScriptObject
{
public:
  CoreWrapperObject(VTable *ivtable, ScriptObject *delegate):FlashScriptObject(ivtable, delegate) {}
  ~CoreWrapperObject(void) {}
private:
  DECLARE_SLOTS_CoreWrapperObject;
};
  

//wrapper for FlashMovieAvmCore. 
//Its used to have an access to the core from as code in order to make more complex tests with a lifetime.
class CoreWrapperClass : public FlashClassClosure
{
public:
  CoreWrapperClass(VTable *vtable): FlashClassClosure(vtable){}
  ~CoreWrapperClass(){}
  
  virtual ScriptObject* createInstance(VTable* ivtable, ScriptObject* prototype)
  {
    NI_ALWAYS_ASSERT ("for now this is only a static class");
    return 0;
    //return new (core()->GetGC(), ivtable->getExtraSize()) CoreWrapperObject(ivtable, prototype);
  }  
  
  //just call FlashCore()->Advance
  void Advance(double deltaTime);


private:
  DECLARE_SLOTS_CoreWrapperClass;
};

}