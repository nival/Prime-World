#pragma once
#include "System/SystemLog.h"
#include "PlayerGlobalIncludes.h"
#include "BitmapFilter.h"

namespace avmplus
{


class GlowFilterObject: public BitmapFilterObject
{
public:
  GlowFilterObject(VTable *ivtable, ScriptObject *delegate):BitmapFilterObject(ivtable, delegate) {}
  ~GlowFilterObject(void) {}

  double get_strength()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "GlowFilterObject", "get_strength" );
    return (double)0;
  }

  void set_blurX(double value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "GlowFilterObject", "set_blurX" );
    return (void)0;
  }

  uint get_color()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "GlowFilterObject", "get_color" );
    return (uint)0;
  }

  void set_blurY(double value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "GlowFilterObject", "set_blurY" );
    return (void)0;
  }

  void set_quality(int value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "GlowFilterObject", "set_quality" );
    return (void)0;
  }

  void set_color(uint value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "GlowFilterObject", "set_color" );
    return (void)0;
  }

  void set_strength(double value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "GlowFilterObject", "set_strength" );
    return (void)0;
  }

  void set_inner(bool value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "GlowFilterObject", "set_inner" );
    return (void)0;
  }

  double get_blurX()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "GlowFilterObject", "get_blurX" );
    return (double)0;
  }

  double get_blurY()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "GlowFilterObject", "get_blurY" );
    return (double)0;
  }

  void set_knockout(bool value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "GlowFilterObject", "set_knockout" );
    return (void)0;
  }

  bool get_inner()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "GlowFilterObject", "get_inner" );
    return (bool)0;
  }

  bool get_knockout()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "GlowFilterObject", "get_knockout" );
    return (bool)0;
  }

  void set_alpha(double value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "GlowFilterObject", "set_alpha" );
    return (void)0;
  }

  double get_alpha()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "GlowFilterObject", "get_alpha" );
    return (double)0;
  }

  int get_quality()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "GlowFilterObject", "get_quality" );
    return (int)0;
  }


private:
  DECLARE_SLOTS_GlowFilterObject;
};
  
class GlowFilterClass : public ClassClosure
{
public:
  GlowFilterClass(VTable *vtable): ClassClosure(vtable){}
  ~GlowFilterClass(){}
  
  virtual ScriptObject* createInstance(VTable* ivtable, ScriptObject* prototype)
  {
    return new (core()->GetGC(), ivtable->getExtraSize()) GlowFilterObject(ivtable, prototype);
  }  
  

private:
  DECLARE_SLOTS_GlowFilterClass;
};

}