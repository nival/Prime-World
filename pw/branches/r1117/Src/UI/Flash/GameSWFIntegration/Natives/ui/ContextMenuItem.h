#pragma once
#include "System/SystemLog.h"
#include "PlayerGlobalIncludes.h"
#include "../events/EventDispatcher.h"

namespace avmplus
{


class ContextMenuItemObject: public EventDispatcherObject
{
public:
  //TODO fix args
  ContextMenuItemObject(VTable *ivtable, ScriptObject *delegate):EventDispatcherObject(ivtable, delegate) {}
  ~ContextMenuItemObject(void) {}

  bool get_enabled()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ContextMenuItemObject", "get_enabled" );
    return (bool)0;
  }

  void set_enabled(bool value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ContextMenuItemObject", "set_enabled" );
    return (void)0;
  }

  bool get_separatorBefore()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ContextMenuItemObject", "get_separatorBefore" );
    return (bool)0;
  }

  AvmString get_caption()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ContextMenuItemObject", "get_caption" );
    return (AvmString)0;
  }

  void set_separatorBefore(bool value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ContextMenuItemObject", "set_separatorBefore" );
    return (void)0;
  }

  bool get_visible()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ContextMenuItemObject", "get_visible" );
    return (bool)0;
  }

  void set_visible(bool value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ContextMenuItemObject", "set_visible" );
    return (void)0;
  }

  void set_caption(AvmString value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ContextMenuItemObject", "set_caption" );
    return (void)0;
  }


private:
  DECLARE_SLOTS_ContextMenuItemObject;
};
  
class ContextMenuItemClass : public EventDispatcherClass
{
public:
  ContextMenuItemClass(VTable *vtable): EventDispatcherClass(vtable){}
  ~ContextMenuItemClass(){}
  
  /*virtual ScriptObject* createInstance(VTable* ivtable, ScriptObject* prototype)
  {
    return new (core()->GetGC(), ivtable->getExtraSize()) ContextMenuItemObject(ivtable, prototype);
  } */ 
  

private:
  DECLARE_SLOTS_ContextMenuItemClass;
};

}