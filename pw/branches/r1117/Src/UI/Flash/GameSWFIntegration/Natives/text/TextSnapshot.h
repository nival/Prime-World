#pragma once
#include "System/SystemLog.h"
#include "PlayerGlobalIncludes.h"

namespace avmplus
{
class ArrayObject;


class TextSnapshotObject: public ScriptObject
{
public:
  TextSnapshotObject(VTable *ivtable, ScriptObject *delegate):ScriptObject(ivtable, delegate) {}
  ~TextSnapshotObject(void) {}

  bool getSelected(int beginIndex, int endIndex)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextSnapshotObject", "getSelected" );
    return (bool)0;
  }

  AvmString getText(int beginIndex, int endIndex, bool includeLineEndings)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextSnapshotObject", "getText" );
    return (AvmString)0;
  }

  void setSelected(int beginIndex, int endIndex, bool select)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextSnapshotObject", "setSelected" );
    return (void)0;
  }

  void setSelectColor(uint hexColor)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextSnapshotObject", "setSelectColor" );
    return (void)0;
  }

  int findText(int beginIndex, AvmString textToFind, bool caseSensitive)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextSnapshotObject", "findText" );
    return (int)0;
  }

  int get_charCount()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextSnapshotObject", "get_charCount" );
    return (int)0;
  }

  double hitTestTextNearPos(double x, double y, double maxDistance)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextSnapshotObject", "hitTestTextNearPos" );
    return (double)0;
  }

  ArrayObject* getTextRunInfo(int beginIndex, int endIndex)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextSnapshotObject", "getTextRunInfo" );
    return (ArrayObject*)0;
  }

  AvmString getSelectedText(bool includeLineEndings)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TextSnapshotObject", "getSelectedText" );
    return (AvmString)0;
  }


private:
  DECLARE_SLOTS_TextSnapshotObject;
};
  
class TextSnapshotClass : public ClassClosure
{
public:
  TextSnapshotClass(VTable *vtable): ClassClosure(vtable){}
  ~TextSnapshotClass(){}
  
  virtual ScriptObject* createInstance(VTable* ivtable, ScriptObject* prototype)
  {
    return new (core()->GetGC(), ivtable->getExtraSize()) TextSnapshotObject(ivtable, prototype);
  }  
  

private:
  DECLARE_SLOTS_TextSnapshotClass;
};

}