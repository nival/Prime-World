#pragma once

#include "../PlayerGlobalIncludes.h"


namespace Render
{
  _interface IFlashRenderer;
}


namespace avmplus
{


class BitmapFilterObject: public ScriptObject
{
public:
  BitmapFilterObject(VTable *ivtable, ScriptObject *delegate):ScriptObject(ivtable, delegate) {}
  ~BitmapFilterObject(void) {}

  // inner functions

  virtual void RealtimeBegin( Render::IFlashRenderer* _renderer ) {}
  virtual void RealtimeEnd( Render::IFlashRenderer* _renderer ) {}

private:
  DECLARE_SLOTS_BitmapFilterObject;
};
  
class BitmapFilterClass : public ClassClosure
{
public:
  BitmapFilterClass(VTable *vtable): ClassClosure(vtable){}
  ~BitmapFilterClass(){}
  
  virtual ScriptObject* createInstance(VTable* ivtable, ScriptObject* prototype)
  {
    return new (core()->GetGC(), ivtable->getExtraSize()) BitmapFilterObject(ivtable, prototype);
  }  
  

private:
  DECLARE_SLOTS_BitmapFilterClass;
};

}