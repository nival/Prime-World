#pragma once
#include "System/SystemLog.h"
#include "PlayerGlobalIncludes.h"

namespace avmplus
{
class TextLineObject;
class ContentElementObject;
class TextJustifierObject;
class FontDescriptionObject;
class ObjectVectorObject;


class TextBlockObject: public ScriptObject
{
public:
  TextBlockObject(VTable *ivtable, ScriptObject *delegate):ScriptObject(ivtable, delegate) {}
  ~TextBlockObject(void) {}

  TextLineObject* getTextLineAtCharIndex(int charIndex)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextBlockObject", "getTextLineAtCharIndex" );
    return (TextLineObject*)0;
  }

  TextLineObject* get_firstLine()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextBlockObject", "get_firstLine" );
    return (TextLineObject*)0;
  }

  ContentElementObject* get_content()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextBlockObject", "get_content" );
    return (ContentElementObject*)0;
  }

  TextJustifierObject* getTextJustifier()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextBlockObject", "getTextJustifier" );
    return (TextJustifierObject*)0;
  }

  int findPreviousAtomBoundary(int beforeCharIndex)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextBlockObject", "findPreviousAtomBoundary" );
    return (int)0;
  }

  AvmString get_baselineZero()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextBlockObject", "get_baselineZero" );
    return (AvmString)0;
  }

  int findNextAtomBoundary(int afterCharIndex)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextBlockObject", "findNextAtomBoundary" );
    return (int)0;
  }

  int findNextWordBoundary(int afterCharIndex)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextBlockObject", "findNextWordBoundary" );
    return (int)0;
  }

  void set_baselineFontDescription(FontDescriptionObject* value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextBlockObject", "set_baselineFontDescription" );
    return (void)0;
  }

  AvmString get_lineRotation()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextBlockObject", "get_lineRotation" );
    return (AvmString)0;
  }

  int findPreviousWordBoundary(int beforeCharIndex)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextBlockObject", "findPreviousWordBoundary" );
    return (int)0;
  }

  bool get_applyNonLinearFontScaling()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextBlockObject", "get_applyNonLinearFontScaling" );
    return (bool)0;
  }

  int get_bidiLevel()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextBlockObject", "get_bidiLevel" );
    return (int)0;
  }

  ObjectVectorObject* getTabStops()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextBlockObject", "getTabStops" );
    return (ObjectVectorObject*)0;
  }

  void set_baselineZero(AvmString value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextBlockObject", "set_baselineZero" );
    return (void)0;
  }

  double get_baselineFontSize()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextBlockObject", "get_baselineFontSize" );
    return (double)0;
  }

  void setTabStops(ObjectVectorObject* value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextBlockObject", "setTabStops" );
    return (void)0;
  }

  void set_lineRotation(AvmString value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextBlockObject", "set_lineRotation" );
    return (void)0;
  }

  void set_applyNonLinearFontScaling(bool value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextBlockObject", "set_applyNonLinearFontScaling" );
    return (void)0;
  }

  TextLineObject* get_lastLine()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextBlockObject", "get_lastLine" );
    return (TextLineObject*)0;
  }

  FontDescriptionObject* get_baselineFontDescription()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextBlockObject", "get_baselineFontDescription" );
    return (FontDescriptionObject*)0;
  }

  void set_bidiLevel(int value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextBlockObject", "set_bidiLevel" );
    return (void)0;
  }

  void set_baselineFontSize(double value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextBlockObject", "set_baselineFontSize" );
    return (void)0;
  }

  void set_content(ContentElementObject* value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextBlockObject", "set_content" );
    return (void)0;
  }

  AvmString dump()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextBlockObject", "dump" );
    return (AvmString)0;
  }

  TextLineObject* DoCreateTextLine(TextLineObject* previousLine, double width, double lineOffset, bool fitSomething)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextBlockObject", "DoCreateTextLine" );
    return (TextLineObject*)0;
  }

  TextLineObject* get_firstInvalidLine()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextBlockObject", "get_firstInvalidLine" );
    return (TextLineObject*)0;
  }

  AvmString get_textLineCreationResult()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextBlockObject", "get_textLineCreationResult" );
    return (AvmString)0;
  }

  void setTextJustifier(TextJustifierObject* value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextBlockObject", "setTextJustifier" );
    return (void)0;
  }

  void releaseLines(TextLineObject* firstLine, TextLineObject* lastLine)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextBlockObject", "releaseLines" );
    return (void)0;
  }


private:
  DECLARE_SLOTS_TextBlockObject;
};
  
class TextBlockClass : public ClassClosure
{
public:
  TextBlockClass(VTable *vtable): ClassClosure(vtable){}
  ~TextBlockClass(){}
  
  virtual ScriptObject* createInstance(VTable* ivtable, ScriptObject* prototype)
  {
    return new (core()->GetGC(), ivtable->getExtraSize()) TextBlockObject(ivtable, prototype);
  }  
  

private:
  DECLARE_SLOTS_TextBlockClass;
};

}