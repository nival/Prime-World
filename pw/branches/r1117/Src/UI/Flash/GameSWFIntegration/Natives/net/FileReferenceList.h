#pragma once
#include "System/SystemLog.h"
#include "PlayerGlobalIncludes.h"
#include "../events/EventDispatcher.h"

namespace avmplus
{
class ArrayObject;


class FileReferenceListObject: public EventDispatcherObject
{
public:
  FileReferenceListObject(VTable *ivtable, ScriptObject *delegate):EventDispatcherObject(ivtable, delegate) {}
  ~FileReferenceListObject(void) {}

  bool browse(ArrayObject* typeFilter)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "FileReferenceListObject", "browse" );
    return (bool)0;
  }

  ArrayObject* get_fileList()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "FileReferenceListObject", "get_fileList" );
    return (ArrayObject*)0;
  }


private:
  DECLARE_SLOTS_FileReferenceListObject;
};
  
class FileReferenceListClass : public ClassClosure
{
public:
  FileReferenceListClass(VTable *vtable): ClassClosure(vtable){}
  ~FileReferenceListClass(){}
  
  virtual ScriptObject* createInstance(VTable* ivtable, ScriptObject* prototype)
  {
    return new (core()->GetGC(), ivtable->getExtraSize()) FileReferenceListObject(ivtable, prototype);
  }  
  

private:
  DECLARE_SLOTS_FileReferenceListClass;
};

}