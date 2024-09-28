#pragma once
#include "System/SystemLog.h"
#include "PlayerGlobalIncludes.h"
#include "../events/EventDispatcher.h"

namespace avmplus
{
class ArrayObject;
class CameraObject;


class CameraObject: public EventDispatcherObject
{
public:
  CameraObject(VTable *ivtable, ScriptObject *delegate):EventDispatcherObject(ivtable, delegate) {}
  ~CameraObject(void) {}

  bool get_loopback()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "CameraObject", "get_loopback" );
    return (bool)0;
  }

  void setMode(int width, int height, double fps, bool favorArea)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "CameraObject", "setMode" );
    return (void)0;
  }

  int get_width()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "CameraObject", "get_width" );
    return (int)0;
  }

  int get_height()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "CameraObject", "get_height" );
    return (int)0;
  }

  double get_fps()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "CameraObject", "get_fps" );
    return (double)0;
  }

  AvmString get_name()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "CameraObject", "get_name" );
    return (AvmString)0;
  }

  void setMotionLevel(int motionLevel, int timeout)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "CameraObject", "setMotionLevel" );
    return (void)0;
  }

  bool get_muted()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "CameraObject", "get_muted" );
    return (bool)0;
  }

  int get_motionLevel()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "CameraObject", "get_motionLevel" );
    return (int)0;
  }

  double get_currentFPS()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "CameraObject", "get_currentFPS" );
    return (double)0;
  }

  int get_bandwidth()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "CameraObject", "get_bandwidth" );
    return (int)0;
  }

  int get_index()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "CameraObject", "get_index" );
    return (int)0;
  }

  int get_keyFrameInterval()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "CameraObject", "get_keyFrameInterval" );
    return (int)0;
  }

  void setLoopback(bool compress)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "CameraObject", "setLoopback" );
    return (void)0;
  }

  double get_activityLevel()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "CameraObject", "get_activityLevel" );
    return (double)0;
  }

  void setCursor(bool value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "CameraObject", "setCursor" );
    return (void)0;
  }

  int get_motionTimeout()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "CameraObject", "get_motionTimeout" );
    return (int)0;
  }

  void setKeyFrameInterval(int keyFrameInterval)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "CameraObject", "setKeyFrameInterval" );
    return (void)0;
  }

  void setQuality(int bandwidth, int quality)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "CameraObject", "setQuality" );
    return (void)0;
  }

  int get_quality()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "CameraObject", "get_quality" );
    return (int)0;
  }


private:
  DECLARE_SLOTS_CameraObject;
};
  
class CameraClass : public ClassClosure
{
public:
  CameraClass(VTable *vtable): ClassClosure(vtable){}
  ~CameraClass(){}
  
  virtual ScriptObject* createInstance(VTable* ivtable, ScriptObject* prototype)
  {
    return new (core()->GetGC(), ivtable->getExtraSize()) CameraObject(ivtable, prototype);
  }  
  
  ArrayObject* get_names()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "CameraClass", "get_names" );
    return (ArrayObject*)0;
  }

  CameraObject* getCamera(AvmString name)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "CameraClass", "getCamera" );
    return (CameraObject*)0;
  }


private:
  DECLARE_SLOTS_CameraClass;
};

}