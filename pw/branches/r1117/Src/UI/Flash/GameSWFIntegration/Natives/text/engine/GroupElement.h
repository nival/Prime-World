#pragma once
#include "System/SystemLog.h"
#include "PlayerGlobalIncludes.h"
#include "ContentElement.h"

namespace avmplus
{
class ContentElementObject;
class TextElementObject;
class GroupElementObject;
class ObjectVectorObject;


class GroupElementObject: public ContentElementObject
{
public:
  GroupElementObject(VTable *ivtable, ScriptObject *delegate):ContentElementObject(ivtable, delegate) {}
  ~GroupElementObject(void) {}

  ContentElementObject* getElementAt(int index)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "GroupElementObject", "getElementAt" );
    return (ContentElementObject*)0;
  }

  ContentElementObject* getElementAtCharIndex(int charIndex)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "GroupElementObject", "getElementAtCharIndex" );
    return (ContentElementObject*)0;
  }

  int get_elementCount()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "GroupElementObject", "get_elementCount" );
    return (int)0;
  }

  TextElementObject* splitTextElement(int elementIndex, int splitIndex)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "GroupElementObject", "splitTextElement" );
    return (TextElementObject*)0;
  }

  GroupElementObject* groupElements(int beginIndex, int endIndex)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "GroupElementObject", "groupElements" );
    return (GroupElementObject*)0;
  }

  void setElements(ObjectVectorObject* value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "GroupElementObject", "setElements" );
    return (void)0;
  }

  ObjectVectorObject* replaceElements(int beginIndex, int endIndex, ObjectVectorObject* newElements)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "GroupElementObject", "replaceElements" );
    return (ObjectVectorObject*)0;
  }

  TextElementObject* mergeTextElements(int beginIndex, int endIndex)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "GroupElementObject", "mergeTextElements" );
    return (TextElementObject*)0;
  }

  void ungroupElements(int groupIndex)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "GroupElementObject", "ungroupElements" );
    return (void)0;
  }


private:
  DECLARE_SLOTS_GroupElementObject;
};
  
class GroupElementClass : public ClassClosure
{
public:
  GroupElementClass(VTable *vtable): ClassClosure(vtable){}
  ~GroupElementClass(){}
  
  virtual ScriptObject* createInstance(VTable* ivtable, ScriptObject* prototype)
  {
    return new (core()->GetGC(), ivtable->getExtraSize()) GroupElementObject(ivtable, prototype);
  }  
  

private:
  DECLARE_SLOTS_GroupElementClass;
};

}