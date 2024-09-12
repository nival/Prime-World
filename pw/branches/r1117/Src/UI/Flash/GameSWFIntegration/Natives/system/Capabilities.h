#pragma once
#include "System/SystemLog.h"
#include "PlayerGlobalIncludes.h"

namespace avmplus
{


class CapabilitiesObject: public ScriptObject
{
public:
  CapabilitiesObject(VTable *ivtable, ScriptObject *delegate):ScriptObject(ivtable, delegate) {}
  ~CapabilitiesObject(void) {}


private:
  DECLARE_SLOTS_CapabilitiesObject;
};
  
class CapabilitiesClass : public ClassClosure
{
public:
  CapabilitiesClass(VTable *vtable): ClassClosure(vtable){}
  ~CapabilitiesClass(){}
  
  virtual ScriptObject* createInstance(VTable* ivtable, ScriptObject* prototype)
  {
    return new (core()->GetGC(), ivtable->getExtraSize()) CapabilitiesObject(ivtable, prototype);
  }  
  
  bool get_hasTLS()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "CapabilitiesClass", "get_hasTLS" );
    return (bool)0;
  }

  bool get_hasScreenBroadcast()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "CapabilitiesClass", "get_hasScreenBroadcast" );
    return (bool)0;
  }

  bool get_hasIME()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "CapabilitiesClass", "get_hasIME" );
    return (bool)0;
  }

  AvmString get_maxLevelIDC()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "CapabilitiesClass", "get_maxLevelIDC" );
    return (AvmString)0;
  }

  bool get_hasStreamingAudio()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "CapabilitiesClass", "get_hasStreamingAudio" );
    return (bool)0;
  }

  bool get_hasPrinting()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "CapabilitiesClass", "get_hasPrinting" );
    return (bool)0;
  }

  double get_screenDPI()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "CapabilitiesClass", "get_screenDPI" );
    return (double)0;
  }

  bool get_hasAccessibility()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "CapabilitiesClass", "get_hasAccessibility" );
    return (bool)0;
  }

  bool get_hasMP3()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "CapabilitiesClass", "get_hasMP3" );
    return (bool)0;
  }

  bool get_hasEmbeddedVideo()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "CapabilitiesClass", "get_hasEmbeddedVideo" );
    return (bool)0;
  }

  AvmString get_manufacturer()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "CapabilitiesClass", "get_manufacturer" );
    return (AvmString)0;
  }

  bool get_hasVideoEncoder()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "CapabilitiesClass", "get_hasVideoEncoder" );
    return (bool)0;
  }

  bool get_hasAudio()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "CapabilitiesClass", "get_hasAudio" );
    return (bool)0;
  }

  AvmString get_screenColor()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "CapabilitiesClass", "get_screenColor" );
    return (AvmString)0;
  }

  AvmString get_language()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "CapabilitiesClass", "get_language" );
    return (AvmString)0;
  }

  bool get_hasAudioEncoder()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "CapabilitiesClass", "get_hasAudioEncoder" );
    return (bool)0;
  }

  bool get_hasScreenPlayback()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "CapabilitiesClass", "get_hasScreenPlayback" );
    return (bool)0;
  }

  uint get__internal()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "CapabilitiesClass", "get__internal" );
    return (uint)0;
  }

  AvmString get_os()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "CapabilitiesClass", "get_os" );
    return (AvmString)0;
  }

  AvmString get_version()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "CapabilitiesClass", "get_version" );
    return (AvmString)0;
  }

  double get_screenResolutionY()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "CapabilitiesClass", "get_screenResolutionY" );
    return (double)0;
  }

  bool get_avHardwareDisable()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "CapabilitiesClass", "get_avHardwareDisable" );
    return (bool)0;
  }

  double get_pixelAspectRatio()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "CapabilitiesClass", "get_pixelAspectRatio" );
    return (double)0;
  }

  double get_screenResolutionX()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "CapabilitiesClass", "get_screenResolutionX" );
    return (double)0;
  }

  bool get_isDebugger()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "CapabilitiesClass", "get_isDebugger" );
    return (bool)0;
  }

  bool get_hasStreamingVideo()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "CapabilitiesClass", "get_hasStreamingVideo" );
    return (bool)0;
  }

  AvmString get_serverString()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "CapabilitiesClass", "get_serverString" );
    return (AvmString)0;
  }

  bool get_localFileReadDisable()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "CapabilitiesClass", "get_localFileReadDisable" );
    return (bool)0;
  }

  AvmString get_playerType()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "CapabilitiesClass", "get_playerType" );
    return (AvmString)0;
  }

  bool get_isEmbeddedInAcrobat()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "CapabilitiesClass", "get_isEmbeddedInAcrobat" );
    return (bool)0;
  }


private:
  DECLARE_SLOTS_CapabilitiesClass;
};

}