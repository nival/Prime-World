#pragma once
#include "System/SystemLog.h"
#include "PlayerGlobalIncludes.h"

namespace avmplus
{
class ArrayObject;
class ClassClosure;


class FontObject: public ScriptObject
{
public:
  FontObject(VTable *ivtable, ScriptObject *delegate):ScriptObject(ivtable, delegate) {}
  ~FontObject(void) {}

  AvmString get_fontType()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "FontObject", "get_fontType" );
    return (AvmString)0;
  }

  AvmString get_fontStyle()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "FontObject", "get_fontStyle" );
    return (AvmString)0;
  }

  AvmString get_fontName()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "FontObject", "get_fontName" );
    return (AvmString)0;
  }

  bool hasGlyphs(AvmString str)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "FontObject", "hasGlyphs" );
    return (bool)0;
  }


private:
  DECLARE_SLOTS_FontObject;
};
  
class FontClass : public ClassClosure
{
public:
  FontClass(VTable *vtable): ClassClosure(vtable){}
  ~FontClass(){}
  
  virtual ScriptObject* createInstance(VTable* ivtable, ScriptObject* prototype)
  {
    return new (core()->GetGC(), ivtable->getExtraSize()) FontObject(ivtable, prototype);
  }  
  
  ArrayObject* enumerateFonts(bool enumerateDeviceFonts)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "FontClass", "enumerateFonts" );
    return (ArrayObject*)0;
  }

  void registerFont(ClassClosure* font)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "FontClass", "registerFont" );
    return (void)0;
  }


private:
  DECLARE_SLOTS_FontClass;
};

}