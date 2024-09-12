#pragma once
#include "System/SystemLog.h"
#include "PlayerGlobalIncludes.h"
#include "BitmapFilter.h"

namespace avmplus
{
class ArrayObject;


class ConvolutionFilterObject: public BitmapFilterObject
{
public:
  ConvolutionFilterObject(VTable *ivtable, ScriptObject *delegate):BitmapFilterObject(ivtable, delegate) {}
  ~ConvolutionFilterObject(void) {}

  ArrayObject* get_matrix()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ConvolutionFilterObject", "get_matrix" );
    return (ArrayObject*)0;
  }

  void set_matrix(ArrayObject* value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ConvolutionFilterObject", "set_matrix" );
    return (void)0;
  }

  uint get_color()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ConvolutionFilterObject", "get_color" );
    return (uint)0;
  }

  void set_preserveAlpha(bool value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ConvolutionFilterObject", "set_preserveAlpha" );
    return (void)0;
  }

  double get_alpha()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ConvolutionFilterObject", "get_alpha" );
    return (double)0;
  }

  void set_color(uint value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ConvolutionFilterObject", "set_color" );
    return (void)0;
  }

  void set_bias(double value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ConvolutionFilterObject", "set_bias" );
    return (void)0;
  }

  void set_alpha(double value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ConvolutionFilterObject", "set_alpha" );
    return (void)0;
  }

  void set_matrixX(double value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ConvolutionFilterObject", "set_matrixX" );
    return (void)0;
  }

  void set_matrixY(double value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ConvolutionFilterObject", "set_matrixY" );
    return (void)0;
  }

  bool get_preserveAlpha()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ConvolutionFilterObject", "get_preserveAlpha" );
    return (bool)0;
  }

  void set_clamp(bool value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ConvolutionFilterObject", "set_clamp" );
    return (void)0;
  }

  double get_matrixX()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ConvolutionFilterObject", "get_matrixX" );
    return (double)0;
  }

  double get_matrixY()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ConvolutionFilterObject", "get_matrixY" );
    return (double)0;
  }

  double get_bias()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ConvolutionFilterObject", "get_bias" );
    return (double)0;
  }

  bool get_clamp()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ConvolutionFilterObject", "get_clamp" );
    return (bool)0;
  }

  void set_divisor(double value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ConvolutionFilterObject", "set_divisor" );
    return (void)0;
  }

  double get_divisor()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ConvolutionFilterObject", "get_divisor" );
    return (double)0;
  }


private:
  DECLARE_SLOTS_ConvolutionFilterObject;
};
  
class ConvolutionFilterClass : public ClassClosure
{
public:
  ConvolutionFilterClass(VTable *vtable): ClassClosure(vtable){}
  ~ConvolutionFilterClass(){}
  
  virtual ScriptObject* createInstance(VTable* ivtable, ScriptObject* prototype)
  {
    return new (core()->GetGC(), ivtable->getExtraSize()) ConvolutionFilterObject(ivtable, prototype);
  }  
  

private:
  DECLARE_SLOTS_ConvolutionFilterClass;
};

}