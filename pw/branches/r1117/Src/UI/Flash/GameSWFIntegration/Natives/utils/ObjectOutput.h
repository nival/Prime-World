#pragma once
#include "System/SystemLog.h"
#include "../PlayerGlobalIncludes.h"

namespace avmplus
{
class ByteArrayObject;


class ObjectOutputObject: public ScriptObject
{
public:
  ObjectOutputObject(VTable *ivtable, ScriptObject *delegate):ScriptObject(ivtable, delegate) {}
  ~ObjectOutputObject(void) {}

  void writeMultiByte(AvmString value, AvmString charSet)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ObjectOutputObject", "writeMultiByte" );
    return (void)0;
  }

  void writeUTFBytes(AvmString value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ObjectOutputObject", "writeUTFBytes" );
    return (void)0;
  }

  void writeObject(AvmBox object)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ObjectOutputObject", "writeObject" );
    return (void)0;
  }

  void writeBoolean(bool value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ObjectOutputObject", "writeBoolean" );
    return (void)0;
  }

  void writeBytes(ByteArrayObject* bytes, uint offset, uint length)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ObjectOutputObject", "writeBytes" );
    return (void)0;
  }

  void writeByte(int value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ObjectOutputObject", "writeByte" );
    return (void)0;
  }

  void writeUTF(AvmString value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ObjectOutputObject", "writeUTF" );
    return (void)0;
  }

  void writeDouble(double value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ObjectOutputObject", "writeDouble" );
    return (void)0;
  }

  void writeUnsignedInt(uint value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ObjectOutputObject", "writeUnsignedInt" );
    return (void)0;
  }

  void writeShort(int value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ObjectOutputObject", "writeShort" );
    return (void)0;
  }

  void writeInt(int value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ObjectOutputObject", "writeInt" );
    return (void)0;
  }

  AvmString get_endian()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ObjectOutputObject", "get_endian" );
    return (AvmString)0;
  }

  void set_objectEncoding(uint version)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ObjectOutputObject", "set_objectEncoding" );
    return (void)0;
  }

  uint get_objectEncoding()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ObjectOutputObject", "get_objectEncoding" );
    return (uint)0;
  }

  void set_endian(AvmString type)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ObjectOutputObject", "set_endian" );
    return (void)0;
  }

  void writeFloat(double value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ObjectOutputObject", "writeFloat" );
    return (void)0;
  }


private:
  DECLARE_SLOTS_ObjectOutputObject;
};
  
class ObjectOutputClass : public ClassClosure
{
public:
  ObjectOutputClass(VTable *vtable): ClassClosure(vtable){}
  ~ObjectOutputClass(){}
  
  virtual ScriptObject* createInstance(VTable* ivtable, ScriptObject* prototype)
  {
    return new (core()->GetGC(), ivtable->getExtraSize()) ObjectOutputObject(ivtable, prototype);
  }  
  

private:
  DECLARE_SLOTS_ObjectOutputClass;
};

}