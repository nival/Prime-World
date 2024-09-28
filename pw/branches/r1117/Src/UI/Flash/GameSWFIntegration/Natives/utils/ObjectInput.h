#pragma once
#include "System/SystemLog.h"
#include "../PlayerGlobalIncludes.h"

namespace avmplus
{
class ByteArrayObject;


class ObjectInputObject: public ScriptObject
{
public:
  ObjectInputObject(VTable *ivtable, ScriptObject *delegate):ScriptObject(ivtable, delegate) {}
  ~ObjectInputObject(void) {}

  uint readUnsignedInt()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ObjectInputObject", "readUnsignedInt" );
    return (uint)0;
  }

  int readByte()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ObjectInputObject", "readByte" );
    return (int)0;
  }

  int readShort()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ObjectInputObject", "readShort" );
    return (int)0;
  }

  double readDouble()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ObjectInputObject", "readDouble" );
    return (double)0;
  }

  bool readBoolean()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ObjectInputObject", "readBoolean" );
    return (bool)0;
  }

  uint readUnsignedByte()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ObjectInputObject", "readUnsignedByte" );
    return (uint)0;
  }

  uint get_objectEncoding()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ObjectInputObject", "get_objectEncoding" );
    return (uint)0;
  }

  AvmBox readObject()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ObjectInputObject", "readObject" );
    return (AvmBox)0;
  }

  uint readUnsignedShort()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ObjectInputObject", "readUnsignedShort" );
    return (uint)0;
  }

  AvmString get_endian()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ObjectInputObject", "get_endian" );
    return (AvmString)0;
  }

  uint get_bytesAvailable()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ObjectInputObject", "get_bytesAvailable" );
    return (uint)0;
  }

  void set_objectEncoding(uint version)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ObjectInputObject", "set_objectEncoding" );
    return (void)0;
  }

  AvmString readMultiByte(uint length, AvmString charSet)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ObjectInputObject", "readMultiByte" );
    return (AvmString)0;
  }

  double readFloat()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ObjectInputObject", "readFloat" );
    return (double)0;
  }

  AvmString readUTF()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ObjectInputObject", "readUTF" );
    return (AvmString)0;
  }

  void set_endian(AvmString type)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ObjectInputObject", "set_endian" );
    return (void)0;
  }

  int readInt()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ObjectInputObject", "readInt" );
    return (int)0;
  }

  AvmString readUTFBytes(uint length)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ObjectInputObject", "readUTFBytes" );
    return (AvmString)0;
  }

  void readBytes(ByteArrayObject* bytes, uint offset, uint length)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ObjectInputObject", "readBytes" );
    return (void)0;
  }


private:
  DECLARE_SLOTS_ObjectInputObject;
};
  
class ObjectInputClass : public ClassClosure
{
public:
  ObjectInputClass(VTable *vtable): ClassClosure(vtable){}
  ~ObjectInputClass(){}
  
  virtual ScriptObject* createInstance(VTable* ivtable, ScriptObject* prototype)
  {
    return new (core()->GetGC(), ivtable->getExtraSize()) ObjectInputObject(ivtable, prototype);
  }  
  

private:
  DECLARE_SLOTS_ObjectInputClass;
};

}