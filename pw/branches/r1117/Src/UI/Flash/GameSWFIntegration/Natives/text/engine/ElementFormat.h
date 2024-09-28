#pragma once
#include "System/SystemLog.h"
#include "PlayerGlobalIncludes.h"

namespace avmplus
{
class FontDescriptionObject;
class ScriptObject;


class ElementFormatObject: public ScriptObject
{
public:
  ElementFormatObject(VTable *ivtable, ScriptObject *delegate):ScriptObject(ivtable, delegate) {}
  ~ElementFormatObject(void) {}

  void set_baselineShift(double value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ElementFormatObject", "set_baselineShift" );
    return (void)0;
  }

  void set_trackingLeft(double value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ElementFormatObject", "set_trackingLeft" );
    return (void)0;
  }

  double get_baselineShift()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ElementFormatObject", "get_baselineShift" );
    return (double)0;
  }

  AvmString get_dominantBaseline()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ElementFormatObject", "get_dominantBaseline" );
    return (AvmString)0;
  }

  void set_color(uint value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ElementFormatObject", "set_color" );
    return (void)0;
  }

  AvmString get_alignmentBaseline()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ElementFormatObject", "get_alignmentBaseline" );
    return (AvmString)0;
  }

  void set_dominantBaseline(AvmString dominantBaseline)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ElementFormatObject", "set_dominantBaseline" );
    return (void)0;
  }

  AvmString get_textRotation()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ElementFormatObject", "get_textRotation" );
    return (AvmString)0;
  }

  AvmString get_kerning()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ElementFormatObject", "get_kerning" );
    return (AvmString)0;
  }

  void set_alignmentBaseline(AvmString alignmentBaseline)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ElementFormatObject", "set_alignmentBaseline" );
    return (void)0;
  }

  void set_trackingRight(double value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ElementFormatObject", "set_trackingRight" );
    return (void)0;
  }

  AvmString get_breakOpportunity()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ElementFormatObject", "get_breakOpportunity" );
    return (AvmString)0;
  }

  void set_textRotation(AvmString value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ElementFormatObject", "set_textRotation" );
    return (void)0;
  }

  void set_kerning(AvmString value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ElementFormatObject", "set_kerning" );
    return (void)0;
  }

  AvmString get_digitWidth()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ElementFormatObject", "get_digitWidth" );
    return (AvmString)0;
  }

  void set_fontDescription(FontDescriptionObject* value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ElementFormatObject", "set_fontDescription" );
    return (void)0;
  }

  void set_locked(bool value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ElementFormatObject", "set_locked" );
    return (void)0;
  }

  double get_alpha()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ElementFormatObject", "get_alpha" );
    return (double)0;
  }

  void set_ligatureLevel(AvmString ligatureLevelType)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ElementFormatObject", "set_ligatureLevel" );
    return (void)0;
  }

  void set_fontSize(double value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ElementFormatObject", "set_fontSize" );
    return (void)0;
  }

  AvmString get_locale()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ElementFormatObject", "get_locale" );
    return (AvmString)0;
  }

  bool get_locked()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ElementFormatObject", "get_locked" );
    return (bool)0;
  }

  uint get_color()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ElementFormatObject", "get_color" );
    return (uint)0;
  }

  double get_trackingRight()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ElementFormatObject", "get_trackingRight" );
    return (double)0;
  }

  void set_breakOpportunity(AvmString opportunityType)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ElementFormatObject", "set_breakOpportunity" );
    return (void)0;
  }

  FontDescriptionObject* get_fontDescription()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ElementFormatObject", "get_fontDescription" );
    return (FontDescriptionObject*)0;
  }

  void set_typographicCase(AvmString typographicCaseType)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ElementFormatObject", "set_typographicCase" );
    return (void)0;
  }

  double get_fontSize()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ElementFormatObject", "get_fontSize" );
    return (double)0;
  }

  void set_digitWidth(AvmString digitWidthType)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ElementFormatObject", "set_digitWidth" );
    return (void)0;
  }

  void set_locale(AvmString value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ElementFormatObject", "set_locale" );
    return (void)0;
  }

  double get_trackingLeft()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ElementFormatObject", "get_trackingLeft" );
    return (double)0;
  }

  AvmString get_ligatureLevel()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ElementFormatObject", "get_ligatureLevel" );
    return (AvmString)0;
  }

  void set_digitCase(AvmString digitCaseType)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ElementFormatObject", "set_digitCase" );
    return (void)0;
  }

  AvmString get_typographicCase()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ElementFormatObject", "get_typographicCase" );
    return (AvmString)0;
  }

  void set_alpha(double value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ElementFormatObject", "set_alpha" );
    return (void)0;
  }

  AvmString get_digitCase()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ElementFormatObject", "get_digitCase" );
    return (AvmString)0;
  }

  ScriptObject/*FontMetrics*/ * getFontMetrics()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ElementFormatObject", "getFontMetrics" );
    return (ScriptObject/*FontMetrics*/ *)0;
  }


private:
  DECLARE_SLOTS_ElementFormatObject;
};
  
class ElementFormatClass : public ClassClosure
{
public:
  ElementFormatClass(VTable *vtable): ClassClosure(vtable){}
  ~ElementFormatClass(){}
  
  virtual ScriptObject* createInstance(VTable* ivtable, ScriptObject* prototype)
  {
    return new (core()->GetGC(), ivtable->getExtraSize()) ElementFormatObject(ivtable, prototype);
  }  
  

private:
  DECLARE_SLOTS_ElementFormatClass;
};

}