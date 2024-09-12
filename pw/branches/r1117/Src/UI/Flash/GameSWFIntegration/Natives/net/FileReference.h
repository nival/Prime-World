#pragma once
#include "System/SystemLog.h"
#include "PlayerGlobalIncludes.h"
#include "../events/EventDispatcher.h"

namespace avmplus
{
class URLRequestObject;
class ByteArrayObject;
class ArrayObject;
class DateObject;


class FileReferenceObject: public EventDispatcherObject
{
public:
  FileReferenceObject(VTable *ivtable, ScriptObject *delegate):EventDispatcherObject(ivtable, delegate) {}
  ~FileReferenceObject(void) {}

  void upload(URLRequestObject* request, AvmString uploadDataFieldName, bool testUpload)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "FileReferenceObject", "upload" );
    return (void)0;
  }

  void _load(ByteArrayObject* dest)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "FileReferenceObject", "_load" );
    return (void)0;
  }

  uint get_size()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "FileReferenceObject", "get_size" );
    return (uint)0;
  }

  AvmString get_type()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "FileReferenceObject", "get_type" );
    return (AvmString)0;
  }

  bool browse(ArrayObject* typeFilter)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "FileReferenceObject", "browse" );
    return (bool)0;
  }

  AvmString get_name()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "FileReferenceObject", "get_name" );
    return (AvmString)0;
  }

  AvmString get_creator()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "FileReferenceObject", "get_creator" );
    return (AvmString)0;
  }

  DateObject* get_creationDate()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "FileReferenceObject", "get_creationDate" );
    return (DateObject*)0;
  }

  void download(URLRequestObject* request, AvmString defaultFileName)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "FileReferenceObject", "download" );
    return (void)0;
  }

  DateObject* get_modificationDate()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "FileReferenceObject", "get_modificationDate" );
    return (DateObject*)0;
  }

  ByteArrayObject* get_data()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "FileReferenceObject", "get_data" );
    return (ByteArrayObject*)0;
  }

  void cancel()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "FileReferenceObject", "cancel" );
    return (void)0;
  }

  void _save(ByteArrayObject* data, AvmString defaultFileName)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "FileReferenceObject", "_save" );
    return (void)0;
  }


private:
  DECLARE_SLOTS_FileReferenceObject;
};
  
class FileReferenceClass : public ClassClosure
{
public:
  FileReferenceClass(VTable *vtable): ClassClosure(vtable){}
  ~FileReferenceClass(){}
  
  virtual ScriptObject* createInstance(VTable* ivtable, ScriptObject* prototype)
  {
    return new (core()->GetGC(), ivtable->getExtraSize()) FileReferenceObject(ivtable, prototype);
  }  
  

private:
  DECLARE_SLOTS_FileReferenceClass;
};

}