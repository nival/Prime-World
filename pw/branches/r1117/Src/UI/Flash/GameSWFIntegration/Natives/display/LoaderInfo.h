#pragma once
#include "System/SystemLog.h"
#include "../PlayerGlobalIncludes.h"
#include "../events/EventDispatcher.h"

namespace avmplus
{
class LoaderInfoObject;
class LoaderInfoClass;
class ByteArrayObject;
class ApplicationDomainObject;
class LoaderObject;
class DisplayObjectObject;
class EventDispatcherObject;

class LoaderInfoObject: public EventDispatcherObject
{
  int width;
  int height;

  double frameRate;

  void Initialize();

  DRCWB(AvmString) url;

public:
  LoaderInfoObject(VTable *ivtable, ScriptObject *delegate);
  LoaderInfoObject( LoaderInfoClass * classType );
  ~LoaderInfoObject(void) {}

  int get_width() { return width; }
  void SetWidth(int value) { width = value; }

  int get_height() { return height; }
  void SetHeight(int value) { height = value; }

  double get_frameRate() { return frameRate;}
  void SetFrameRate(double value) { frameRate = value; }

  DisplayObjectObject* get_content() { return content; }
  void SetContent(DisplayObjectObject* value) { content = value; }

  AvmString get_url() { return url; }
  //////////////////////////////////////////////////////////////////////////
  
  
  //Events
  DECLARE_EVENT(INIT)
  DECLARE_EVENT(COMPLETE)


  //NOT IMPLEMETED
  //////////////////////////////////////////////////////////////////////////
  bool get_childAllowsParent()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "LoaderInfoObject", "get_childAllowsParent" );
    return true;
  }

  bool get_parentAllowsChild()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "LoaderInfoObject", "get_parentAllowsChild" );
    return true;
  }

  AvmBox _getArgs()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "LoaderInfoObject", "_getArgs" );
    return (AvmBox)0;
  }

  ByteArrayObject* get_bytes()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "LoaderInfoObject", "get_bytes" );
    return (ByteArrayObject*)0;
  }

  uint get_bytesLoaded()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "LoaderInfoObject", "get_bytesLoaded" );
    return (uint)0;
  }

  bool get_sameDomain()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "LoaderInfoObject", "get_sameDomain" );
    return (bool)0;
  }

  AvmString get_contentType()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "LoaderInfoObject", "get_contentType" );
    return (AvmString)0;
  }

  ApplicationDomainObject* get_applicationDomain()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "LoaderInfoObject", "get_applicationDomain" );
    return (ApplicationDomainObject*)0;
  }

  uint get_swfVersion()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "LoaderInfoObject", "get_swfVersion" );
    return (uint)0;
  }

  uint get_actionScriptVersion()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "LoaderInfoObject", "get_actionScriptVersion" );
    return (uint)0;
  }

  uint get_bytesTotal()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "LoaderInfoObject", "get_bytesTotal" );
    return (uint)0;
  }

  LoaderObject* get_loader()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "LoaderInfoObject", "get_loader" );
    return (LoaderObject*)0;
  }

  AvmString get_loaderURL()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "LoaderInfoObject", "get_loaderURL" );
    return (AvmString)0;
  }

  EventDispatcherObject* get_sharedEvents()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "LoaderInfoObject", "get_sharedEvents" );
    return (EventDispatcherObject*)0;
  }

 
private:

  DRCWB( DisplayObjectObject*) content;

  DECLARE_SLOTS_LoaderInfoObject;
};
  
class LoaderInfoClass : public EventDispatcherClass
{
public:
  LoaderInfoClass(VTable *vtable);  
  ~LoaderInfoClass(){}
  
  DECLARE_CREATE_MEMBERS(LoaderInfoObject)

  LoaderInfoObject* getLoaderInfoByDefinition(AvmBox object)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "LoaderInfoClass", "getLoaderInfoByDefinition" );
    return (LoaderInfoObject*)0;
  }


private:
  DECLARE_SLOTS_LoaderInfoClass;
};

}