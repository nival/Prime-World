#pragma once
#include "System/SystemLog.h"
#include "PlayerGlobalIncludes.h"
#include "../events/EventDispatcher.h"

namespace avmplus
{
class URLRequestObject;
class ByteArrayObject;


class URLStreamObject: public EventDispatcherObject
{
public:
  URLStreamObject(VTable *ivtable, ScriptObject *delegate):EventDispatcherObject(ivtable, delegate) {}
  ~URLStreamObject(void) {}

  uint readUnsignedInt()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "URLStreamObject", "readUnsignedInt" );
    return (uint)0;
  }

  double readDouble()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "URLStreamObject", "readDouble" );
    return (double)0;
  }

  double readFloat()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "URLStreamObject", "readFloat" );
    return (double)0;
  }

  bool readBoolean()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "URLStreamObject", "readBoolean" );
    return (bool)0;
  }

  int readShort()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "URLStreamObject", "readShort" );
    return (int)0;
  }

  bool get_connected()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "URLStreamObject", "get_connected" );
    return (bool)0;
  }

  uint readUnsignedShort()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "URLStreamObject", "readUnsignedShort" );
    return (uint)0;
  }

  uint readUnsignedByte()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "URLStreamObject", "readUnsignedByte" );
    return (uint)0;
  }

  uint get_objectEncoding()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "URLStreamObject", "get_objectEncoding" );
    return (uint)0;
  }

  AvmBox readObject()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "URLStreamObject", "readObject" );
    return (AvmBox)0;
  }

  AvmString get_endian()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "URLStreamObject", "get_endian" );
    return (AvmString)0;
  }

  uint get_bytesAvailable()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "URLStreamObject", "get_bytesAvailable" );
    return (uint)0;
  }

  void set_objectEncoding(uint version)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "URLStreamObject", "set_objectEncoding" );
    return (void)0;
  }

  void load(URLRequestObject* request)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "URLStreamObject", "load" );
    return (void)0;
  }

  AvmString readMultiByte(uint length, AvmString charSet)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "URLStreamObject", "readMultiByte" );
    return (AvmString)0;
  }

  AvmString readUTF()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "URLStreamObject", "readUTF" );
    return (AvmString)0;
  }

  void set_endian(AvmString type)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "URLStreamObject", "set_endian" );
    return (void)0;
  }

  int readInt()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "URLStreamObject", "readInt" );
    return (int)0;
  }

  AvmString readUTFBytes(uint length)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "URLStreamObject", "readUTFBytes" );
    return (AvmString)0;
  }

  void readBytes(ByteArrayObject* bytes, uint offset, uint length)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "URLStreamObject", "readBytes" );
    return (void)0;
  }

  int readByte()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "URLStreamObject", "readByte" );
    return (int)0;
  }

  void close()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "URLStreamObject", "close" );
    return (void)0;
  }


private:
  DECLARE_SLOTS_URLStreamObject;
};
  
class URLStreamClass : public ClassClosure
{
public:
  URLStreamClass(VTable *vtable): ClassClosure(vtable){}
  ~URLStreamClass(){}
  
  virtual ScriptObject* createInstance(VTable* ivtable, ScriptObject* prototype)
  {
    return new (core()->GetGC(), ivtable->getExtraSize()) URLStreamObject(ivtable, prototype);
  }  
  

private:
  DECLARE_SLOTS_URLStreamClass;
};

}