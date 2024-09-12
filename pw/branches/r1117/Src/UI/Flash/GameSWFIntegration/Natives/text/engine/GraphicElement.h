#pragma once
#include "System/SystemLog.h"
#include "PlayerGlobalIncludes.h"
#include "ContentElement.h"

namespace avmplus
{
class DisplayObjectObject;


class GraphicElementObject: public ContentElementObject
{
public:
  GraphicElementObject(VTable *ivtable, ScriptObject *delegate):ContentElementObject(ivtable, delegate) {}
  ~GraphicElementObject(void) {}

  void set_graphic(DisplayObjectObject* value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "GraphicElementObject", "set_graphic" );
    return (void)0;
  }

  double get_elementHeight()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "GraphicElementObject", "get_elementHeight" );
    return (double)0;
  }

  void set_elementWidth(double value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "GraphicElementObject", "set_elementWidth" );
    return (void)0;
  }

  void set_elementHeight(double value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "GraphicElementObject", "set_elementHeight" );
    return (void)0;
  }

  DisplayObjectObject* get_graphic()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "GraphicElementObject", "get_graphic" );
    return (DisplayObjectObject*)0;
  }

  double get_elementWidth()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "GraphicElementObject", "get_elementWidth" );
    return (double)0;
  }


private:
  DECLARE_SLOTS_GraphicElementObject;
};
  
class GraphicElementClass : public ClassClosure
{
public:
  GraphicElementClass(VTable *vtable): ClassClosure(vtable){}
  ~GraphicElementClass(){}
  
  virtual ScriptObject* createInstance(VTable* ivtable, ScriptObject* prototype)
  {
    return new (core()->GetGC(), ivtable->getExtraSize()) GraphicElementObject(ivtable, prototype);
  }  
  

private:
  DECLARE_SLOTS_GraphicElementClass;
};

}