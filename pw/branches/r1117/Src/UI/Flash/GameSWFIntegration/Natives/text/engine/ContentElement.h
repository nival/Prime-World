#pragma once
#include "System/SystemLog.h"
#include "PlayerGlobalIncludes.h"

namespace avmplus
{
class TextBlockObject;
class ElementFormatObject;
class EventDispatcherObject;
class GroupElementObject;


class ContentElementObject: public ScriptObject
{
public:
  ContentElementObject(VTable *ivtable, ScriptObject *delegate):ScriptObject(ivtable, delegate) {}
  ~ContentElementObject(void) {}

  TextBlockObject* get_textBlock()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ContentElementObject", "get_textBlock" );
    return (TextBlockObject*)0;
  }

  void set_elementFormat(ElementFormatObject* value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ContentElementObject", "set_elementFormat" );
    return (void)0;
  }

  int get_textBlockBeginIndex()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ContentElementObject", "get_textBlockBeginIndex" );
    return (int)0;
  }

  AvmString get_textRotation()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ContentElementObject", "get_textRotation" );
    return (AvmString)0;
  }

  AvmString get_text()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ContentElementObject", "get_text" );
    return (AvmString)0;
  }

  void set_eventMirror(EventDispatcherObject* value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ContentElementObject", "set_eventMirror" );
    return (void)0;
  }

  ElementFormatObject* get_elementFormat()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ContentElementObject", "get_elementFormat" );
    return (ElementFormatObject*)0;
  }

  void set_textRotation(AvmString value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ContentElementObject", "set_textRotation" );
    return (void)0;
  }

  EventDispatcherObject* get_eventMirror()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ContentElementObject", "get_eventMirror" );
    return (EventDispatcherObject*)0;
  }

  AvmString get_rawText()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ContentElementObject", "get_rawText" );
    return (AvmString)0;
  }

  GroupElementObject* get_groupElement()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ContentElementObject", "get_groupElement" );
    return (GroupElementObject*)0;
  }


private:
  DECLARE_SLOTS_ContentElementObject;
};
  
class ContentElementClass : public ClassClosure
{
public:
  ContentElementClass(VTable *vtable): ClassClosure(vtable){}
  ~ContentElementClass(){}
  
  virtual ScriptObject* createInstance(VTable* ivtable, ScriptObject* prototype)
  {
    return new (core()->GetGC(), ivtable->getExtraSize()) ContentElementObject(ivtable, prototype);
  }  
  

private:
  DECLARE_SLOTS_ContentElementClass;
};

}