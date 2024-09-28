#pragma once
#include "System/SystemLog.h"
#include "PlayerGlobalIncludes.h"

namespace avmplus
{


class FontDescriptionObject: public ScriptObject
{
public:
  FontDescriptionObject(VTable *ivtable, ScriptObject *delegate):ScriptObject(ivtable, delegate) {}
  ~FontDescriptionObject(void) {}

  void set_fontLookup(AvmString value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "FontDescriptionObject", "set_fontLookup" );
    return (void)0;
  }

  AvmString get_fontWeight()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "FontDescriptionObject", "get_fontWeight" );
    return (AvmString)0;
  }

  AvmString get_fontLookup()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "FontDescriptionObject", "get_fontLookup" );
    return (AvmString)0;
  }

  bool get_locked()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "FontDescriptionObject", "get_locked" );
    return (bool)0;
  }

  void set_fontWeight(AvmString value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "FontDescriptionObject", "set_fontWeight" );
    return (void)0;
  }

  AvmString get_renderingMode()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "FontDescriptionObject", "get_renderingMode" );
    return (AvmString)0;
  }

  void set_cffHinting(AvmString value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "FontDescriptionObject", "set_cffHinting" );
    return (void)0;
  }

  void set_fontPosture(AvmString value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "FontDescriptionObject", "set_fontPosture" );
    return (void)0;
  }

  void set_fontName(AvmString value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "FontDescriptionObject", "set_fontName" );
    return (void)0;
  }

  AvmString get_cffHinting()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "FontDescriptionObject", "get_cffHinting" );
    return (AvmString)0;
  }

  AvmString get_fontPosture()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "FontDescriptionObject", "get_fontPosture" );
    return (AvmString)0;
  }

  AvmString get_fontName()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "FontDescriptionObject", "get_fontName" );
    return (AvmString)0;
  }

  void set_locked(bool value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "FontDescriptionObject", "set_locked" );
    return (void)0;
  }

  void set_renderingMode(AvmString value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "FontDescriptionObject", "set_renderingMode" );
    return (void)0;
  }


private:
  DECLARE_SLOTS_FontDescriptionObject;
};
  
class FontDescriptionClass : public ClassClosure
{
public:
  FontDescriptionClass(VTable *vtable): ClassClosure(vtable){}
  ~FontDescriptionClass(){}
  
  virtual ScriptObject* createInstance(VTable* ivtable, ScriptObject* prototype)
  {
    return new (core()->GetGC(), ivtable->getExtraSize()) FontDescriptionObject(ivtable, prototype);
  }  
  
  bool isFontCompatible(AvmString fontName, AvmString fontWeight, AvmString fontPosture)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "FontDescriptionClass", "isFontCompatible" );
    return (bool)0;
  }


private:
  DECLARE_SLOTS_FontDescriptionClass;
};

}