#pragma once
#include "System/SystemLog.h"
#include "PlayerGlobalIncludes.h"
#include "BitmapFilter.h"

namespace avmplus
{
class ArrayObject;


class GradientBevelFilterObject: public BitmapFilterObject
{
public:
  GradientBevelFilterObject(VTable *ivtable, ScriptObject *delegate):BitmapFilterObject(ivtable, delegate) {}
  ~GradientBevelFilterObject(void) {}

  void set_colors(ArrayObject* value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "GradientBevelFilterObject", "set_colors" );
    return (void)0;
  }

  double get_strength()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "GradientBevelFilterObject", "get_strength" );
    return (double)0;
  }

  void set_blurX(double value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "GradientBevelFilterObject", "set_blurX" );
    return (void)0;
  }

  void set_blurY(double value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "GradientBevelFilterObject", "set_blurY" );
    return (void)0;
  }

  void set_angle(double value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "GradientBevelFilterObject", "set_angle" );
    return (void)0;
  }

  AvmString get_type()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "GradientBevelFilterObject", "get_type" );
    return (AvmString)0;
  }

  ArrayObject* get_ratios()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "GradientBevelFilterObject", "get_ratios" );
    return (ArrayObject*)0;
  }

  void set_strength(double value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "GradientBevelFilterObject", "set_strength" );
    return (void)0;
  }

  void set_alphas(ArrayObject* value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "GradientBevelFilterObject", "set_alphas" );
    return (void)0;
  }

  ArrayObject* get_colors()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "GradientBevelFilterObject", "get_colors" );
    return (ArrayObject*)0;
  }

  double get_blurX()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "GradientBevelFilterObject", "get_blurX" );
    return (double)0;
  }

  double get_blurY()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "GradientBevelFilterObject", "get_blurY" );
    return (double)0;
  }

  double get_angle()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "GradientBevelFilterObject", "get_angle" );
    return (double)0;
  }

  void set_knockout(bool value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "GradientBevelFilterObject", "set_knockout" );
    return (void)0;
  }

  double get_distance()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "GradientBevelFilterObject", "get_distance" );
    return (double)0;
  }

  void set_ratios(ArrayObject* value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "GradientBevelFilterObject", "set_ratios" );
    return (void)0;
  }

  void set_distance(double value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "GradientBevelFilterObject", "set_distance" );
    return (void)0;
  }

  bool get_knockout()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "GradientBevelFilterObject", "get_knockout" );
    return (bool)0;
  }

  void set_type(AvmString value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "GradientBevelFilterObject", "set_type" );
    return (void)0;
  }

  ArrayObject* get_alphas()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "GradientBevelFilterObject", "get_alphas" );
    return (ArrayObject*)0;
  }

  void set_quality(int value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "GradientBevelFilterObject", "set_quality" );
    return (void)0;
  }

  int get_quality()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "GradientBevelFilterObject", "get_quality" );
    return (int)0;
  }


private:
  DECLARE_SLOTS_GradientBevelFilterObject;
};
  
class GradientBevelFilterClass : public ClassClosure
{
public:
  GradientBevelFilterClass(VTable *vtable): ClassClosure(vtable){}
  ~GradientBevelFilterClass(){}
  
  virtual ScriptObject* createInstance(VTable* ivtable, ScriptObject* prototype)
  {
    return new (core()->GetGC(), ivtable->getExtraSize()) GradientBevelFilterObject(ivtable, prototype);
  }  
  

private:
  DECLARE_SLOTS_GradientBevelFilterClass;
};

}