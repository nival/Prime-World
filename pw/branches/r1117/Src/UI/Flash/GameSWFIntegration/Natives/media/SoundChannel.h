#pragma once
#include "System/SystemLog.h"
#include "../PlayerGlobalIncludes.h"
#include "../events/EventDispatcher.h"

namespace avmplus
{
class SoundTransformObject;


class SoundChannelObject: public EventDispatcherObject
{
public:
  SoundChannelObject(VTable *ivtable, ScriptObject *delegate):EventDispatcherObject(ivtable, delegate) {}
  ~SoundChannelObject(void) {}

  void stop()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "SoundChannelObject", "stop" );
    return (void)0;
  }

  double get_leftPeak()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "SoundChannelObject", "get_leftPeak" );
    return (double)0;
  }

  double get_position()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "SoundChannelObject", "get_position" );
    return (double)0;
  }

  void set_soundTransform(SoundTransformObject* sndTransform)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "SoundChannelObject", "set_soundTransform" );
    return (void)0;
  }

  double get_rightPeak()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "SoundChannelObject", "get_rightPeak" );
    return (double)0;
  }

  SoundTransformObject* get_soundTransform()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "SoundChannelObject", "get_soundTransform" );
    return (SoundTransformObject*)0;
  }


private:
  DECLARE_SLOTS_SoundChannelObject;
};
  
class SoundChannelClass : public ClassClosure
{
public:
  SoundChannelClass(VTable *vtable): ClassClosure(vtable){}
  ~SoundChannelClass(){}
  
  virtual ScriptObject* createInstance(VTable* ivtable, ScriptObject* prototype)
  {
    return new (core()->GetGC(), ivtable->getExtraSize()) SoundChannelObject(ivtable, prototype);
  }  
  

private:
  DECLARE_SLOTS_SoundChannelClass;
};

}