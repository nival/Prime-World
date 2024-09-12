#pragma once
#include "System/SystemLog.h"
#include "PlayerGlobalIncludes.h"
#include "../events/EventDispatcher.h"

namespace avmplus
{
class ByteArrayObject;


class SocketObject: public EventDispatcherObject
{
public:
  SocketObject(VTable *ivtable, ScriptObject *delegate):EventDispatcherObject(ivtable, delegate) {}
  ~SocketObject(void) {}

  void writeUTFBytes(AvmString value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "SocketObject", "writeUTFBytes" );
    return (void)0;
  }

  void flush()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "SocketObject", "flush" );
    return (void)0;
  }

  void writeObject(AvmBox object)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "SocketObject", "writeObject" );
    return (void)0;
  }

  void writeByte(int value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "SocketObject", "writeByte" );
    return (void)0;
  }

  bool get_connected()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "SocketObject", "get_connected" );
    return (bool)0;
  }

  int readShort()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "SocketObject", "readShort" );
    return (int)0;
  }

  uint readUnsignedShort()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "SocketObject", "readUnsignedShort" );
    return (uint)0;
  }

  double readDouble()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "SocketObject", "readDouble" );
    return (double)0;
  }

  void writeInt(int value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "SocketObject", "writeInt" );
    return (void)0;
  }

  AvmString get_endian()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "SocketObject", "get_endian" );
    return (AvmString)0;
  }

  void set_objectEncoding(uint version)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "SocketObject", "set_objectEncoding" );
    return (void)0;
  }

  uint get_bytesAvailable()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "SocketObject", "get_bytesAvailable" );
    return (uint)0;
  }

  bool didFailureOccur()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "SocketObject", "didFailureOccur" );
    return (bool)0;
  }

  void writeDouble(double value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "SocketObject", "writeDouble" );
    return (void)0;
  }

  AvmBox readObject()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "SocketObject", "readObject" );
    return (AvmBox)0;
  }

  AvmString readUTF()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "SocketObject", "readUTF" );
    return (AvmString)0;
  }

  void set_endian(AvmString type)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "SocketObject", "set_endian" );
    return (void)0;
  }

  AvmString internalGetSecurityErrorMessage(AvmString host, int port)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "SocketObject", "internalGetSecurityErrorMessage" );
    return (AvmString)0;
  }

  bool readBoolean()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "SocketObject", "readBoolean" );
    return (bool)0;
  }

  AvmString readUTFBytes(uint length)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "SocketObject", "readUTFBytes" );
    return (AvmString)0;
  }

  void internalClose()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "SocketObject", "internalClose" );
    return (void)0;
  }

  void writeFloat(double value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "SocketObject", "writeFloat" );
    return (void)0;
  }

  int readByte()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "SocketObject", "readByte" );
    return (int)0;
  }

  void writeUTF(AvmString value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "SocketObject", "writeUTF" );
    return (void)0;
  }

  void writeBoolean(bool value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "SocketObject", "writeBoolean" );
    return (void)0;
  }

  uint get_objectEncoding()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "SocketObject", "get_objectEncoding" );
    return (uint)0;
  }

  uint readUnsignedInt()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "SocketObject", "readUnsignedInt" );
    return (uint)0;
  }

  void writeBytes(ByteArrayObject* bytes, uint offset, uint length)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "SocketObject", "writeBytes" );
    return (void)0;
  }

  void writeMultiByte(AvmString value, AvmString charSet)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "SocketObject", "writeMultiByte" );
    return (void)0;
  }

  uint readUnsignedByte()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "SocketObject", "readUnsignedByte" );
    return (uint)0;
  }

  void writeUnsignedInt(uint value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "SocketObject", "writeUnsignedInt" );
    return (void)0;
  }

  void writeShort(int value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "SocketObject", "writeShort" );
    return (void)0;
  }

  double readFloat()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "SocketObject", "readFloat" );
    return (double)0;
  }

  AvmString readMultiByte(uint length, AvmString charSet)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "SocketObject", "readMultiByte" );
    return (AvmString)0;
  }

  void internalConnect(AvmString host, int port)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "SocketObject", "internalConnect" );
    return (void)0;
  }

  void readBytes(ByteArrayObject* bytes, uint offset, uint length)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "SocketObject", "readBytes" );
    return (void)0;
  }

  int readInt()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "SocketObject", "readInt" );
    return (int)0;
  }


private:
  DECLARE_SLOTS_SocketObject;
};
  
class SocketClass : public ClassClosure
{
public:
  SocketClass(VTable *vtable): ClassClosure(vtable){}
  ~SocketClass(){}
  
  virtual ScriptObject* createInstance(VTable* ivtable, ScriptObject* prototype)
  {
    return new (core()->GetGC(), ivtable->getExtraSize()) SocketObject(ivtable, prototype);
  }  
  

private:
  DECLARE_SLOTS_SocketClass;
};

}