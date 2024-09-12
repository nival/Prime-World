#pragma once
#include "System/SystemLog.h"
#include "PlayerGlobalIncludes.h"

namespace avmplus
{
class ArrayObject;


class TextRendererObject: public ScriptObject
{
public:
  TextRendererObject(VTable *ivtable, ScriptObject *delegate):ScriptObject(ivtable, delegate) {}
  ~TextRendererObject(void) {}


private:
  DECLARE_SLOTS_TextRendererObject;
};
  
class TextRendererClass : public ClassClosure
{
public:
  TextRendererClass(VTable *vtable): ClassClosure(vtable){}
  ~TextRendererClass(){}
  
  virtual ScriptObject* createInstance(VTable* ivtable, ScriptObject* prototype)
  {
    return new (core()->GetGC(), ivtable->getExtraSize()) TextRendererObject(ivtable, prototype);
  }  
  
  void set_maxLevel(int value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextRendererClass", "set_maxLevel" );
    return (void)0;
  }

  AvmString get_displayMode()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextRendererClass", "get_displayMode" );
    return (AvmString)0;
  }

  void setAdvancedAntiAliasingTable(AvmString fontName, AvmString fontStyle, AvmString colorType, ArrayObject* advancedAntiAliasingTable)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextRendererClass", "setAdvancedAntiAliasingTable" );
    return (void)0;
  }

  int get_maxLevel()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextRendererClass", "get_maxLevel" );
    return (int)0;
  }

  AvmString get_antiAliasType()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextRendererClass", "get_antiAliasType" );
    return (AvmString)0;
  }

  void set_displayMode(AvmString value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextRendererClass", "set_displayMode" );
    return (void)0;
  }

  void set_antiAliasType(AvmString value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextRendererClass", "set_antiAliasType" );
    return (void)0;
  }


private:
  DECLARE_SLOTS_TextRendererClass;
};

}