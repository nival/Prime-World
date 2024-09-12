#pragma once
#include "System/SystemLog.h"
#include "PlayerGlobalIncludes.h"
#include "BitmapFilter.h"

namespace avmplus
{


class BevelFilterObject: public BitmapFilterObject
{
public:
  BevelFilterObject(VTable *ivtable, ScriptObject *delegate):BitmapFilterObject(ivtable, delegate) {}
  ~BevelFilterObject(void) {}

  double get_strength()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "BevelFilterObject", "get_strength" );
    return (double)0;
  }

  void set_strength(double value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "BevelFilterObject", "set_strength" );
    return (void)0;
  }

  void set_shadowColor(uint value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "BevelFilterObject", "set_shadowColor" );
    return (void)0;
  }

  bool get_knockout()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "BevelFilterObject", "get_knockout" );
    return (bool)0;
  }

  double get_highlightAlpha()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "BevelFilterObject", "get_highlightAlpha" );
    return (double)0;
  }

  uint get_highlightColor()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "BevelFilterObject", "get_highlightColor" );
    return (uint)0;
  }

  double get_blurX()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "BevelFilterObject", "get_blurX" );
    return (double)0;
  }

  double get_blurY()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "BevelFilterObject", "get_blurY" );
    return (double)0;
  }

  double get_angle()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "BevelFilterObject", "get_angle" );
    return (double)0;
  }

  void set_highlightAlpha(double value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "BevelFilterObject", "set_highlightAlpha" );
    return (void)0;
  }

  void set_highlightColor(uint value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "BevelFilterObject", "set_highlightColor" );
    return (void)0;
  }

  void set_blurX(double value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "BevelFilterObject", "set_blurX" );
    return (void)0;
  }

  uint get_shadowColor()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "BevelFilterObject", "get_shadowColor" );
    return (uint)0;
  }

  void set_blurY(double value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "BevelFilterObject", "set_blurY" );
    return (void)0;
  }

  double get_shadowAlpha()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "BevelFilterObject", "get_shadowAlpha" );
    return (double)0;
  }

  void set_angle(double value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "BevelFilterObject", "set_angle" );
    return (void)0;
  }

  void set_distance(double value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "BevelFilterObject", "set_distance" );
    return (void)0;
  }

  void set_type(AvmString value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "BevelFilterObject", "set_type" );
    return (void)0;
  }

  double get_distance()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "BevelFilterObject", "get_distance" );
    return (double)0;
  }

  AvmString get_type()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "BevelFilterObject", "get_type" );
    return (AvmString)0;
  }

  void set_knockout(bool value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "BevelFilterObject", "set_knockout" );
    return (void)0;
  }

  void set_shadowAlpha(double value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "BevelFilterObject", "set_shadowAlpha" );
    return (void)0;
  }

  void set_quality(int value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "BevelFilterObject", "set_quality" );
    return (void)0;
  }

  int get_quality()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "BevelFilterObject", "get_quality" );
    return (int)0;
  }


private:
  DECLARE_SLOTS_BevelFilterObject;
};
  
class BevelFilterClass : public ClassClosure
{
public:
  BevelFilterClass(VTable *vtable): ClassClosure(vtable){}
  ~BevelFilterClass(){}
  
  virtual ScriptObject* createInstance(VTable* ivtable, ScriptObject* prototype)
  {
    return new (core()->GetGC(), ivtable->getExtraSize()) BevelFilterObject(ivtable, prototype);
  }  
  

private:
  DECLARE_SLOTS_BevelFilterClass;
};

}