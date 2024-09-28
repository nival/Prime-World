#pragma once
#include "System/SystemLog.h"
#include "PlayerGlobalIncludes.h"
#include "../events/EventDispatcher.h"

namespace avmplus
{
class ScriptObject;
class ContextMenuObject;
class ArrayObject;
class URLRequestObject;


class ContextMenuObject: public EventDispatcherObject
{
public:
  //TODO fix args
  ContextMenuObject(VTable *ivtable, ScriptObject *delegate):EventDispatcherObject(ivtable, delegate) {}
  ~ContextMenuObject(void) {}

  void set_builtInItems(ScriptObject/*ContextMenuBuiltInItems*/ * value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ContextMenuObject", "set_builtInItems" );
    return (void)0;
  }

  ScriptObject/*ContextMenuBuiltInItems*/ * get_builtInItems()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ContextMenuObject", "get_builtInItems" );
    return (ScriptObject/*ContextMenuBuiltInItems*/ *)0;
  }

  void cloneLinkAndClipboardProperties(ContextMenuObject* c)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ContextMenuObject", "cloneLinkAndClipboardProperties" );
    return (void)0;
  }

  ScriptObject/*ContextMenuClipboardItems*/ * get_clipboardItems()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ContextMenuObject", "get_clipboardItems" );
    return (ScriptObject/*ContextMenuClipboardItems*/ *)0;
  }

  ArrayObject* get_customItems()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ContextMenuObject", "get_customItems" );
    return (ArrayObject*)0;
  }

  void set_clipboardMenu(bool value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ContextMenuObject", "set_clipboardMenu" );
    return (void)0;
  }

  void set_link(URLRequestObject* value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ContextMenuObject", "set_link" );
    return (void)0;
  }

  bool get_clipboardMenu()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ContextMenuObject", "get_clipboardMenu" );
    return (bool)0;
  }

  URLRequestObject* get_link()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ContextMenuObject", "get_link" );
    return (URLRequestObject*)0;
  }

  void set_clipboardItems(ScriptObject/*ContextMenuClipboardItems*/ * value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ContextMenuObject", "set_clipboardItems" );
    return (void)0;
  }

  void initLinkAndClipboardProperties()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ContextMenuObject", "initLinkAndClipboardProperties" );
    return (void)0;
  }

  void set_customItems(ArrayObject* value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ContextMenuObject", "set_customItems" );
    return (void)0;
  }


private:
  DECLARE_SLOTS_ContextMenuObject;
};
  
class ContextMenuClass : public EventDispatcherClass
{
public:
  ContextMenuClass(VTable *vtable): EventDispatcherClass(vtable){}
  ~ContextMenuClass(){}
  
  /*virtual ScriptObject* createInstance(VTable* ivtable, ScriptObject* prototype)
  {
    return new (core()->GetGC(), ivtable->getExtraSize()) ContextMenuObject(ivtable, prototype);
  }  */
  

private:
  DECLARE_SLOTS_ContextMenuClass;
};

}