#pragma once
#include "System/SystemLog.h"
#include "PlayerGlobalIncludes.h"
#include "../../display/DisplayObjectContainer.h"

namespace avmplus
{
class ObjectVectorObject;
class DisplayObjectObject;
class TextLineObject;
class TextBlockObject;
class ScriptObject;


class TextLineObject: public DisplayObjectContainerObject
{
public:
  TextLineObject(VTable *ivtable, ScriptObject *delegate):DisplayObjectContainerObject(NULL) {}
  ~TextLineObject(void) {}

  ObjectVectorObject* get_mirrorRegions()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextLineObject", "get_mirrorRegions" );
    return (ObjectVectorObject*)0;
  }

  double get_descent()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextLineObject", "get_descent" );
    return (double)0;
  }

  DisplayObjectObject* getAtomGraphic(int atomIndex)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextLineObject", "getAtomGraphic" );
    return (DisplayObjectObject*)0;
  }

  double getBaselinePosition(AvmString baseline)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextLineObject", "getBaselinePosition" );
    return (double)0;
  }

  TextLineObject* get_nextLine()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextLineObject", "get_nextLine" );
    return (TextLineObject*)0;
  }

  TextLineObject* get_previousLine()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextLineObject", "get_previousLine" );
    return (TextLineObject*)0;
  }

  AvmString dump()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextLineObject", "dump" );
    return (AvmString)0;
  }

  int doGetAtomIndexAtPoint(double x, double y)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextLineObject", "doGetAtomIndexAtPoint" );
    return (int)0;
  }

  int getAtomBidiLevel(int atomIndex)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextLineObject", "getAtomBidiLevel" );
    return (int)0;
  }

  double get_unjustifiedTextWidth()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextLineObject", "get_unjustifiedTextWidth" );
    return (double)0;
  }

  double get_textWidth()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextLineObject", "get_textWidth" );
    return (double)0;
  }

  double get_ascent()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextLineObject", "get_ascent" );
    return (double)0;
  }

  TextBlockObject* get_textBlock()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextLineObject", "get_textBlock" );
    return (TextBlockObject*)0;
  }

  bool getAtomWordBoundaryOnLeft(int atomIndex)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextLineObject", "getAtomWordBoundaryOnLeft" );
    return (bool)0;
  }

  int getAtomTextBlockBeginIndex(int atomIndex)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextLineObject", "getAtomTextBlockBeginIndex" );
    return (int)0;
  }

  ScriptObject/*Rectangle*/ * getAtomBounds(int atomIndex)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextLineObject", "getAtomBounds" );
    return (ScriptObject/*Rectangle*/ *)0;
  }

  void set_validity(AvmString value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextLineObject", "set_validity" );
    return (void)0;
  }

  int get_textBlockBeginIndex()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextLineObject", "get_textBlockBeginIndex" );
    return (int)0;
  }

  bool get_hasGraphicElement()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextLineObject", "get_hasGraphicElement" );
    return (bool)0;
  }

  int getAtomTextBlockEndIndex(int atomIndex)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextLineObject", "getAtomTextBlockEndIndex" );
    return (int)0;
  }

  AvmString get_validity()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextLineObject", "get_validity" );
    return (AvmString)0;
  }

  double get_textHeight()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextLineObject", "get_textHeight" );
    return (double)0;
  }

  double get_specifiedWidth()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextLineObject", "get_specifiedWidth" );
    return (double)0;
  }

  AvmString getAtomTextRotation(int atomIndex)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextLineObject", "getAtomTextRotation" );
    return (AvmString)0;
  }

  int get_rawTextLength()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextLineObject", "get_rawTextLength" );
    return (int)0;
  }

  double getAtomCenter(int atomIndex)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextLineObject", "getAtomCenter" );
    return (double)0;
  }

  int get_atomCount()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextLineObject", "get_atomCount" );
    return (int)0;
  }

  void flushAtomData()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextLineObject", "flushAtomData" );
    return (void)0;
  }


private:
  DECLARE_SLOTS_TextLineObject;
};
  
class TextLineClass : public ClassClosure
{
public:
  TextLineClass(VTable *vtable): ClassClosure(vtable){}
  ~TextLineClass(){}
  
  virtual ScriptObject* createInstance(VTable* ivtable, ScriptObject* prototype)
  {
    return new (core()->GetGC(), ivtable->getExtraSize()) TextLineObject(ivtable, prototype);
  }  
  

private:
  DECLARE_SLOTS_TextLineClass;
};

}