#pragma once
#include "System/SystemLog.h"
#include "PlayerGlobalIncludes.h"

namespace avmplus
{


class TabStopObject: public ScriptObject
{
public:
  TabStopObject(VTable *ivtable, ScriptObject *delegate):ScriptObject(ivtable, delegate) {}
  ~TabStopObject(void) {}

  void set_position(double value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TabStopObject", "set_position" );
    return (void)0;
  }

  AvmString get_alignment()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TabStopObject", "get_alignment" );
    return (AvmString)0;
  }

  void set_alignment(AvmString value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TabStopObject", "set_alignment" );
    return (void)0;
  }

  AvmString get_decimalAlignmentToken()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TabStopObject", "get_decimalAlignmentToken" );
    return (AvmString)0;
  }

  double get_position()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TabStopObject", "get_position" );
    return (double)0;
  }

  void set_decimalAlignmentToken(AvmString value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "TabStopObject", "set_decimalAlignmentToken" );
    return (void)0;
  }


private:
  DECLARE_SLOTS_TabStopObject;
};
  
class TabStopClass : public ClassClosure
{
public:
  TabStopClass(VTable *vtable): ClassClosure(vtable){}
  ~TabStopClass(){}
  
  virtual ScriptObject* createInstance(VTable* ivtable, ScriptObject* prototype)
  {
    return new (core()->GetGC(), ivtable->getExtraSize()) TabStopObject(ivtable, prototype);
  }  
  

private:
  DECLARE_SLOTS_TabStopClass;
};

}