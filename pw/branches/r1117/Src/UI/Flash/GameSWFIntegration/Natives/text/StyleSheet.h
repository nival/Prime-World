#pragma once
#include "System/SystemLog.h"
#include "PlayerGlobalIncludes.h"
#include "../events/EventDispatcher.h"

namespace avmplus
{


class StyleSheetObject: public EventDispatcherObject
{
public:
  //TODO fix args
  StyleSheetObject(VTable *ivtable, ScriptObject *delegate):EventDispatcherObject(ivtable, delegate) {}
  ~StyleSheetObject(void) {}

  void _update()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "StyleSheetObject", "_update" );
    return (void)0;
  }

  AvmBox get__styles()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "StyleSheetObject", "get__styles" );
    return (AvmBox)0;
  }

  void set__styles(AvmBox styles)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "StyleSheetObject", "set__styles" );
    return (void)0;
  }

  AvmString _parseCSSFontFamily(AvmString fontFamily)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "StyleSheetObject", "_parseCSSFontFamily" );
    return (AvmString)0;
  }

  AvmBox _parseCSSInternal(AvmString cssText)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "StyleSheetObject", "_parseCSSInternal" );
    return (AvmBox)0;
  }

  uint _parseColor(AvmString color)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "StyleSheetObject", "_parseColor" );
    return (uint)0;
  }


private:
  DECLARE_SLOTS_StyleSheetObject;
};
  
class StyleSheetClass : public EventDispatcherClass
{
public:
  StyleSheetClass(VTable *vtable): EventDispatcherClass(vtable){}
  ~StyleSheetClass(){}
  
  /*virtual ScriptObject* createInstance(VTable* ivtable, ScriptObject* prototype)
  {
    return new (core()->GetGC(), ivtable->getExtraSize()) StyleSheetObject(ivtable, prototype);
  }*/  
  

private:
  DECLARE_SLOTS_StyleSheetClass;
};

}