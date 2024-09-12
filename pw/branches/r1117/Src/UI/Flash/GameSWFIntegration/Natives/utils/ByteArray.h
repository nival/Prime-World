#pragma once
#include "System/SystemLog.h"
#include "../PlayerGlobalIncludes.h"

namespace avmplus
{
class ByteArrayObject;


class ByteArrayObject: public ScriptObject
{
public:
  ByteArrayObject(VTable *ivtable, ScriptObject *delegate):ScriptObject(ivtable, delegate) {}
  ~ByteArrayObject(void) {}

  void writeUTFBytes(AvmString value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ByteArrayObject", "writeUTFBytes" );
    return (void)0;
  }

  int readShort()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ByteArrayObject", "readShort" );
    return (int)0;
  }

  void writeByte(int value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ByteArrayObject", "writeByte" );
    return (void)0;
  }

  void writeDouble(double value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ByteArrayObject", "writeDouble" );
    return (void)0;
  }

  uint readUnsignedShort()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ByteArrayObject", "readUnsignedShort" );
    return (uint)0;
  }

  double readDouble()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ByteArrayObject", "readDouble" );
    return (double)0;
  }

  void writeInt(int value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ByteArrayObject", "writeInt" );
    return (void)0;
  }

  void _uncompress(AvmString algorithm)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ByteArrayObject", "_uncompress" );
    return (void)0;
  }

  AvmString get_endian()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ByteArrayObject", "get_endian" );
    return (AvmString)0;
  }

  uint get_bytesAvailable()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ByteArrayObject", "get_bytesAvailable" );
    return (uint)0;
  }

  AvmBox readObject()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ByteArrayObject", "readObject" );
    return (AvmBox)0;
  }

  uint get_position()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ByteArrayObject", "get_position" );
    return (uint)0;
  }

  bool readBoolean()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ByteArrayObject", "readBoolean" );
    return (bool)0;
  }

  void set_endian(AvmString type)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ByteArrayObject", "set_endian" );
    return (void)0;
  }

  AvmString readUTF()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ByteArrayObject", "readUTF" );
    return (AvmString)0;
  }

  AvmString readUTFBytes(uint length)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ByteArrayObject", "readUTFBytes" );
    return (AvmString)0;
  }

  void writeFloat(double value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ByteArrayObject", "writeFloat" );
    return (void)0;
  }

  void writeMultiByte(AvmString value, AvmString charSet)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ByteArrayObject", "writeMultiByte" );
    return (void)0;
  }

  uint readUnsignedInt()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ByteArrayObject", "readUnsignedInt" );
    return (uint)0;
  }

  int readByte()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ByteArrayObject", "readByte" );
    return (int)0;
  }

  uint get_objectEncoding()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ByteArrayObject", "get_objectEncoding" );
    return (uint)0;
  }

  void writeBytes(ByteArrayObject* bytes, uint offset, uint length)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ByteArrayObject", "writeBytes" );
    return (void)0;
  }

  void clear()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ByteArrayObject", "clear" );
    return (void)0;
  }

  void writeUTF(AvmString value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ByteArrayObject", "writeUTF" );
    return (void)0;
  }

  void writeBoolean(bool value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ByteArrayObject", "writeBoolean" );
    return (void)0;
  }

  void set_position(uint offset)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ByteArrayObject", "set_position" );
    return (void)0;
  }

  void _compress(AvmString algorithm)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ByteArrayObject", "_compress" );
    return (void)0;
  }

  uint readUnsignedByte()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ByteArrayObject", "readUnsignedByte" );
    return (uint)0;
  }

  void writeUnsignedInt(uint value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ByteArrayObject", "writeUnsignedInt" );
    return (void)0;
  }

  void writeShort(int value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ByteArrayObject", "writeShort" );
    return (void)0;
  }

  uint get_length()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ByteArrayObject", "get_length" );
    return (uint)0;
  }

  Atom toString()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ByteArrayObject", "toString" );
    return (Atom)0;
  }

  void set_length(uint value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ByteArrayObject", "set_length" );
    return (void)0;
  }

  void set_objectEncoding(uint version)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ByteArrayObject", "set_objectEncoding" );
    return (void)0;
  }

  double readFloat()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ByteArrayObject", "readFloat" );
    return (double)0;
  }

  int readInt()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ByteArrayObject", "readInt" );
    return (int)0;
  }

  AvmString readMultiByte(uint length, AvmString charSet)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ByteArrayObject", "readMultiByte" );
    return (AvmString)0;
  }

  void readBytes(ByteArrayObject* bytes, uint offset, uint length)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ByteArrayObject", "readBytes" );
    return (void)0;
  }

  void writeObject(AvmBox object)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ByteArrayObject", "writeObject" );
    return (void)0;
  }


private:
  DECLARE_SLOTS_ByteArrayObject;
};
  
class ByteArrayClass : public ClassClosure
{
public:
  ByteArrayClass(VTable *vtable): ClassClosure(vtable){}
  ~ByteArrayClass(){}
  
  virtual ScriptObject* createInstance(VTable* ivtable, ScriptObject* prototype)
  {
    return new (core()->GetGC(), ivtable->getExtraSize()) ByteArrayObject(ivtable, prototype);
  }  
  
  uint get_defaultObjectEncoding()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ByteArrayClass", "get_defaultObjectEncoding" );
    return (uint)0;
  }

  void set_defaultObjectEncoding(uint version)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "ByteArrayClass", "set_defaultObjectEncoding" );
    return (void)0;
  }


private:
  DECLARE_SLOTS_ByteArrayClass;
};

}