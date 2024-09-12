#pragma once
#include "System/SystemLog.h"
#include "PlayerGlobalIncludes.h"
#include "BitmapFilter.h"

namespace avmplus
{


class DropShadowFilterObject: public BitmapFilterObject
{
public:
  DropShadowFilterObject(VTable *ivtable, ScriptObject *delegate):BitmapFilterObject(ivtable, delegate) {}
  ~DropShadowFilterObject(void) {}

  bool get_hideObject()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "DropShadowFilterObject", "get_hideObject" );
    return (bool)0;
  }

  void set_blurX(double value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "DropShadowFilterObject", "set_blurX" );
    return (void)0;
  }

  uint get_color()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "DropShadowFilterObject", "get_color" );
    return (uint)0;
  }

  void set_blurY(double value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "DropShadowFilterObject", "set_blurY" );
    return (void)0;
  }

  void set_quality(int value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "DropShadowFilterObject", "set_quality" );
    return (void)0;
  }

  void set_angle(double value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "DropShadowFilterObject", "set_angle" );
    return (void)0;
  }

  double get_strength()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "DropShadowFilterObject", "get_strength" );
    return (double)0;
  }

  void set_hideObject(bool value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "DropShadowFilterObject", "set_hideObject" );
    return (void)0;
  }

  void set_distance(double value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "DropShadowFilterObject", "set_distance" );
    return (void)0;
  }

  void set_inner(bool value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "DropShadowFilterObject", "set_inner" );
    return (void)0;
  }

  void set_color(uint value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "DropShadowFilterObject", "set_color" );
    return (void)0;
  }

  void set_strength(double value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "DropShadowFilterObject", "set_strength" );
    return (void)0;
  }

  double get_blurX()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "DropShadowFilterObject", "get_blurX" );
    return (double)0;
  }

  double get_blurY()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "DropShadowFilterObject", "get_blurY" );
    return (double)0;
  }

  double get_angle()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "DropShadowFilterObject", "get_angle" );
    return (double)0;
  }

  void set_knockout(bool value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "DropShadowFilterObject", "set_knockout" );
    return (void)0;
  }

  double get_distance()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "DropShadowFilterObject", "get_distance" );
    return (double)0;
  }

  bool get_inner()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "DropShadowFilterObject", "get_inner" );
    return (bool)0;
  }

  bool get_knockout()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "DropShadowFilterObject", "get_knockout" );
    return (bool)0;
  }

  void set_alpha(double value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "DropShadowFilterObject", "set_alpha" );
    return (void)0;
  }

  double get_alpha()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "DropShadowFilterObject", "get_alpha" );
    return (double)0;
  }

  int get_quality()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "DropShadowFilterObject", "get_quality" );
    return (int)0;
  }


private:
  DECLARE_SLOTS_DropShadowFilterObject;
};
  
class DropShadowFilterClass : public ClassClosure
{
public:
  DropShadowFilterClass(VTable *vtable): ClassClosure(vtable){}
  ~DropShadowFilterClass(){}
  
  virtual ScriptObject* createInstance(VTable* ivtable, ScriptObject* prototype)
  {
    return new (core()->GetGC(), ivtable->getExtraSize()) DropShadowFilterObject(ivtable, prototype);
  }  
  

private:
  DECLARE_SLOTS_DropShadowFilterClass;
};

}