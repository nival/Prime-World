#pragma once
#include "System/SystemLog.h"
#include "PlayerGlobalIncludes.h"

namespace avmplus
{
class TextLineObject;
class ScriptObject;
class TextLineMirrorRegionObject;
class ContentElementObject;
class EventDispatcherObject;


class TextLineMirrorRegionObject: public ScriptObject
{
public:
  TextLineMirrorRegionObject(VTable *ivtable, ScriptObject *delegate):ScriptObject(ivtable, delegate) {}
  ~TextLineMirrorRegionObject(void) {}

  TextLineObject* get_textLine()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextLineMirrorRegionObject", "get_textLine" );
    return (TextLineObject*)0;
  }

  ScriptObject/*Rectangle*/ * get_bounds()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextLineMirrorRegionObject", "get_bounds" );
    return (ScriptObject/*Rectangle*/ *)0;
  }

  TextLineMirrorRegionObject* get_nextRegion()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextLineMirrorRegionObject", "get_nextRegion" );
    return (TextLineMirrorRegionObject*)0;
  }

  TextLineMirrorRegionObject* get_previousRegion()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextLineMirrorRegionObject", "get_previousRegion" );
    return (TextLineMirrorRegionObject*)0;
  }

  ContentElementObject* get_element()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextLineMirrorRegionObject", "get_element" );
    return (ContentElementObject*)0;
  }

  EventDispatcherObject* get_mirror()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextLineMirrorRegionObject", "get_mirror" );
    return (EventDispatcherObject*)0;
  }


private:
  DECLARE_SLOTS_TextLineMirrorRegionObject;
};
  
class TextLineMirrorRegionClass : public ClassClosure
{
public:
  TextLineMirrorRegionClass(VTable *vtable): ClassClosure(vtable){}
  ~TextLineMirrorRegionClass(){}
  
  virtual ScriptObject* createInstance(VTable* ivtable, ScriptObject* prototype)
  {
    return new (core()->GetGC(), ivtable->getExtraSize()) TextLineMirrorRegionObject(ivtable, prototype);
  }  
  

private:
  DECLARE_SLOTS_TextLineMirrorRegionClass;
};

}