#pragma once
#include "System/SystemLog.h"
#include "../PlayerGlobalIncludes.h"

namespace avmplus
{


class SoundTransformObject: public ScriptObject
{
public:
  SoundTransformObject(VTable *ivtable, ScriptObject *delegate):ScriptObject(ivtable, delegate) {}
  ~SoundTransformObject(void) {}

  double get_rightToRight()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "SoundTransformObject", "get_rightToRight" );
    return (double)0;
  }

  double get_volume()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "SoundTransformObject", "get_volume" );
    return (double)0;
  }

  double get_leftToLeft()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "SoundTransformObject", "get_leftToLeft" );
    return (double)0;
  }

  void set_rightToRight(double rightToRight)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "SoundTransformObject", "set_rightToRight" );
    return (void)0;
  }

  void set_leftToLeft(double leftToLeft)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "SoundTransformObject", "set_leftToLeft" );
    return (void)0;
  }

  void set_leftToRight(double leftToRight)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "SoundTransformObject", "set_leftToRight" );
    return (void)0;
  }

  double get_leftToRight()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "SoundTransformObject", "get_leftToRight" );
    return (double)0;
  }

  void set_volume(double volume)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "SoundTransformObject", "set_volume" );
    return (void)0;
  }

  void set_rightToLeft(double rightToLeft)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "SoundTransformObject", "set_rightToLeft" );
    return (void)0;
  }

  double get_rightToLeft()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "SoundTransformObject", "get_rightToLeft" );
    return (double)0;
  }


private:
  DECLARE_SLOTS_SoundTransformObject;
};
  
class SoundTransformClass : public ClassClosure
{
public:
  SoundTransformClass(VTable *vtable): ClassClosure(vtable){}
  ~SoundTransformClass(){}
  
  virtual ScriptObject* createInstance(VTable* ivtable, ScriptObject* prototype)
  {
    return new (core()->GetGC(), ivtable->getExtraSize()) SoundTransformObject(ivtable, prototype);
  }  
  

private:
  DECLARE_SLOTS_SoundTransformClass;
};

}