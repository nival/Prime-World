#pragma once
#include "System/SystemLog.h"
#include "PlayerGlobalIncludes.h"
#include "../events/EventDispatcher.h"

namespace avmplus
{
class MicrophoneObject;
class ArrayObject;
class SoundTransformObject;


class MicrophoneObject: public EventDispatcherObject
{
public:
  MicrophoneObject(VTable *ivtable, ScriptObject *delegate):EventDispatcherObject(ivtable, delegate) {}
  ~MicrophoneObject(void) {}

  void set_rate(int rate)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "MicrophoneObject", "set_rate" );
    return (void)0;
  }

  void set_soundTransform(SoundTransformObject* sndTransform)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "MicrophoneObject", "set_soundTransform" );
    return (void)0;
  }

  double get_silenceLevel()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "MicrophoneObject", "get_silenceLevel" );
    return (double)0;
  }

  void setSilenceLevel(double silenceLevel, int timeout)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "MicrophoneObject", "setSilenceLevel" );
    return (void)0;
  }

  double get_gain()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "MicrophoneObject", "get_gain" );
    return (double)0;
  }

  int get_rate()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "MicrophoneObject", "get_rate" );
    return (int)0;
  }

  void setUseEchoSuppression(bool useEchoSuppression)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "MicrophoneObject", "setUseEchoSuppression" );
    return (void)0;
  }

  bool get_muted()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "MicrophoneObject", "get_muted" );
    return (bool)0;
  }

  void set_codec(AvmString codec)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "MicrophoneObject", "set_codec" );
    return (void)0;
  }

  void set_gain(double gain)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "MicrophoneObject", "set_gain" );
    return (void)0;
  }

  bool get_useEchoSuppression()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "MicrophoneObject", "get_useEchoSuppression" );
    return (bool)0;
  }

  int get_silenceTimeout()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "MicrophoneObject", "get_silenceTimeout" );
    return (int)0;
  }

  int get_encodeQuality()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "MicrophoneObject", "get_encodeQuality" );
    return (int)0;
  }

  void set_encodeQuality(int quality)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "MicrophoneObject", "set_encodeQuality" );
    return (void)0;
  }

  void setLoopBack(bool state)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "MicrophoneObject", "setLoopBack" );
    return (void)0;
  }

  double get_activityLevel()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "MicrophoneObject", "get_activityLevel" );
    return (double)0;
  }

  AvmString get_codec()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "MicrophoneObject", "get_codec" );
    return (AvmString)0;
  }

  int get_index()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "MicrophoneObject", "get_index" );
    return (int)0;
  }

  AvmString get_name()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "MicrophoneObject", "get_name" );
    return (AvmString)0;
  }

  SoundTransformObject* get_soundTransform()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "MicrophoneObject", "get_soundTransform" );
    return (SoundTransformObject*)0;
  }

  void set_framesPerPacket(int frames)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "MicrophoneObject", "set_framesPerPacket" );
    return (void)0;
  }

  int get_framesPerPacket()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "MicrophoneObject", "get_framesPerPacket" );
    return (int)0;
  }


private:
  DECLARE_SLOTS_MicrophoneObject;
};
  
class MicrophoneClass : public ClassClosure
{
public:
  MicrophoneClass(VTable *vtable): ClassClosure(vtable){}
  ~MicrophoneClass(){}
  
  virtual ScriptObject* createInstance(VTable* ivtable, ScriptObject* prototype)
  {
    return new (core()->GetGC(), ivtable->getExtraSize()) MicrophoneObject(ivtable, prototype);
  }  
  
  MicrophoneObject* getMicrophone(int index)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "MicrophoneClass", "getMicrophone" );
    return (MicrophoneObject*)0;
  }

  ArrayObject* get_names()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "MicrophoneClass", "get_names" );
    return (ArrayObject*)0;
  }


private:
  DECLARE_SLOTS_MicrophoneClass;
};

}