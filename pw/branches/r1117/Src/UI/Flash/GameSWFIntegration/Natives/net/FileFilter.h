#pragma once
#include "System/SystemLog.h"
#include "PlayerGlobalIncludes.h"

namespace avmplus
{


class FileFilterObject: public ScriptObject
{
public:
  FileFilterObject(VTable *ivtable, ScriptObject *delegate):ScriptObject(ivtable, delegate) {}
  ~FileFilterObject(void) {}

  void set_macType(AvmString value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "FileFilterObject", "set_macType" );
    return (void)0;
  }

  void set_description(AvmString value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "FileFilterObject", "set_description" );
    return (void)0;
  }

  AvmString get_macType()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "FileFilterObject", "get_macType" );
    return (AvmString)0;
  }

  AvmString get_description()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "FileFilterObject", "get_description" );
    return (AvmString)0;
  }

  void set_extension(AvmString value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "FileFilterObject", "set_extension" );
    return (void)0;
  }

  AvmString get_extension()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "FileFilterObject", "get_extension" );
    return (AvmString)0;
  }


private:
  DECLARE_SLOTS_FileFilterObject;
};
  
class FileFilterClass : public ClassClosure
{
public:
  FileFilterClass(VTable *vtable): ClassClosure(vtable){}
  ~FileFilterClass(){}
  
  virtual ScriptObject* createInstance(VTable* ivtable, ScriptObject* prototype)
  {
    return new (core()->GetGC(), ivtable->getExtraSize()) FileFilterObject(ivtable, prototype);
  }  
  

private:
  DECLARE_SLOTS_FileFilterClass;
};

}