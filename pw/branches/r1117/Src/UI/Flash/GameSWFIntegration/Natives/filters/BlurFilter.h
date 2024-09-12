#pragma once
#include "System/SystemLog.h"
#include "PlayerGlobalIncludes.h"
#include "BitmapFilter.h"

namespace avmplus
{


class BlurFilterObject: public BitmapFilterObject
{
public:
  BlurFilterObject(VTable *ivtable, ScriptObject *delegate):BitmapFilterObject(ivtable, delegate) {}
  ~BlurFilterObject(void) {}

  double get_blurX()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "BlurFilterObject", "get_blurX" );
    return (double)0;
  }

  void set_blurX(double value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "BlurFilterObject", "set_blurX" );
    return (void)0;
  }

  void set_blurY(double value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "BlurFilterObject", "set_blurY" );
    return (void)0;
  }

  double get_blurY()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "BlurFilterObject", "get_blurY" );
    return (double)0;
  }

  void set_quality(int value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "BlurFilterObject", "set_quality" );
    return (void)0;
  }

  int get_quality()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "BlurFilterObject", "get_quality" );
    return (int)0;
  }


private:
  DECLARE_SLOTS_BlurFilterObject;
};
  
class BlurFilterClass : public ClassClosure
{
public:
  BlurFilterClass(VTable *vtable): ClassClosure(vtable){}
  ~BlurFilterClass(){}
  
  virtual ScriptObject* createInstance(VTable* ivtable, ScriptObject* prototype)
  {
    return new (core()->GetGC(), ivtable->getExtraSize()) BlurFilterObject(ivtable, prototype);
  }  
  

private:
  DECLARE_SLOTS_BlurFilterClass;
};

}