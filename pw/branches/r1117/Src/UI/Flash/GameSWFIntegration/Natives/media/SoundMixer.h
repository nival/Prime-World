#pragma once
#include "System/SystemLog.h"
#include "PlayerGlobalIncludes.h"

namespace avmplus
{
class SoundTransformObject;
class ByteArrayObject;


class SoundMixerObject: public ScriptObject
{
public:
  SoundMixerObject(VTable *ivtable, ScriptObject *delegate):ScriptObject(ivtable, delegate) {}
  ~SoundMixerObject(void) {}


private:
  DECLARE_SLOTS_SoundMixerObject;
};
  
class SoundMixerClass : public ClassClosure
{
public:
  SoundMixerClass(VTable *vtable): ClassClosure(vtable){}
  ~SoundMixerClass(){}
  
  virtual ScriptObject* createInstance(VTable* ivtable, ScriptObject* prototype)
  {
    return new (core()->GetGC(), ivtable->getExtraSize()) SoundMixerObject(ivtable, prototype);
  }  
  
  void set_soundTransform(SoundTransformObject* sndTransform)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "SoundMixerClass", "set_soundTransform" );
    return (void)0;
  }

  bool areSoundsInaccessible()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "SoundMixerClass", "areSoundsInaccessible" );
    return (bool)0;
  }

  int get_bufferTime()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "SoundMixerClass", "get_bufferTime" );
    return (int)0;
  }

  void computeSpectrum(ByteArrayObject* outputArray, bool FFTMode, int stretchFactor)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "SoundMixerClass", "computeSpectrum" );
    return (void)0;
  }

  void set_bufferTime(int bufferTime)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "SoundMixerClass", "set_bufferTime" );
    return (void)0;
  }

  SoundTransformObject* get_soundTransform()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "SoundMixerClass", "get_soundTransform" );
    return (SoundTransformObject*)0;
  }

  void stopAll()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "SoundMixerClass", "stopAll" );
    return (void)0;
  }


private:
  DECLARE_SLOTS_SoundMixerClass;
};

}