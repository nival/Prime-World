#pragma once

#include "Types.h"
#include <System/fixedvector.h>
#include "RpcDataFactory.h"
#include "System/ChunklessSaver.h"

namespace rpc 
{
#pragma warning( disable: 4201 ) // warning C4201: nonstandard extension used : nameless struct/union
_interface IMultiPipe;
_interface IRemoteEntity;
_interface IEntityMap;
_interface Data;

struct IObjHolder
{
  virtual ~IObjHolder() {}
};

template <typename T>
struct CObjHolder : IObjHolder
{
  CObjHolder(T* _value):value(_value)
  {
  }
  StrongMT<T> value;
};

struct IEntityEnumerator
{
  virtual ~IEntityEnumerator()=0;
  virtual void OnProcess(rpc::IRemoteEntity* entity)=0;
};

inline IEntityEnumerator::~IEntityEnumerator() {}

struct MethodCodeCalculator
{
  MethodCodeCalculator():methodCode(0), index(0) {}

  uint GetCode() const { return methodCode; }

  template <typename T> void Push() 
  { 
    Add(rpc::ParamTypes(typename rpc::GetTypeT<T>::type)); 
  }

  MethodCodeCalculator& Add(rpc::ParamTypes code)
  {
    methodCode += (int(code)+1)*(index+1);
    index++;
    return *this;
  }
private:
  uint methodCode;
  int index;
};

template <typename R, typename C>
uint GetMethodCodeTemp(R (C::*func)())
{
  return 0;
}

template <typename R, typename C, typename P0>
uint GetMethodCodeTemp(R (C::*func)(P0 p0))
{
  MethodCodeCalculator calc;
  calc.Push<P0>();
  return calc.GetCode();
}

template <typename R, typename C, typename P0, typename P1>
uint GetMethodCodeTemp(R (C::*func)(P0 p0, P1 p1))
{
  MethodCodeCalculator calc;
  calc.Push<P0>();
  calc.Push<P1>();
  return calc.GetCode();
}

template <typename R, typename C, typename P0, typename P1, typename P2>
uint GetMethodCodeTemp(R (C::*func)(P0 p0, P1 p1, P2 p2))
{
  MethodCodeCalculator calc;
  calc.Push<P0>();
  calc.Push<P1>();
  calc.Push<P2>();
  return calc.GetCode();
}

template <typename R, typename C, typename P0, typename P1, typename P2, typename P3>
uint GetMethodCodeTemp(R (C::*func)(P0 p0, P1 p1, P2 p2, P3 p3))
{
  MethodCodeCalculator calc;
  calc.Push<P0>();
  calc.Push<P1>();
  calc.Push<P2>();
  calc.Push<P3>();
  return calc.GetCode();
}

template <typename R, typename C, typename P0, typename P1, typename P2, typename P3, typename P4>
uint GetMethodCodeTemp(R (C::*func)(P0 p0, P1 p1, P2 p2, P3 p3, P4 p4))
{
  MethodCodeCalculator calc;
  calc.Push<P0>();
  calc.Push<P1>();
  calc.Push<P2>();
  calc.Push<P3>();
  calc.Push<P4>();
  return calc.GetCode();
}

template <typename R, typename C, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5>
uint GetMethodCodeTemp(R (C::*func)(P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5))
{
  MethodCodeCalculator calc;
  calc.Push<P0>();
  calc.Push<P1>();
  calc.Push<P2>();
  calc.Push<P3>();
  calc.Push<P4>();
  calc.Push<P5>();
  return calc.GetCode();
}

template <typename R, typename C, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>
uint GetMethodCodeTemp(R (C::*func)(P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6))
{
  MethodCodeCalculator calc;
  calc.Push<P0>();
  calc.Push<P1>();
  calc.Push<P2>();
  calc.Push<P3>();
  calc.Push<P4>();
  calc.Push<P5>();
  calc.Push<P6>();
  return calc.GetCode();
}

template <typename R, typename C>
uint GetMethodCode(R (C::*func)())
{
  return 0;
}

template <typename R, typename C, typename P0>
uint GetMethodCode(R (C::*func)(P0 p0))
{
  return 0;
}

template <typename R, typename C, typename P0, typename P1>
uint GetMethodCode(R (C::*func)(P0 p0, P1 p1))
{
  return 0;
}

template <typename R, typename C, typename P0, typename P1, typename P2>
uint GetMethodCode(R (C::*func)(P0 p0, P1 p1, P2 p2))
{
  return 0;
}

template <typename R, typename C, typename P0, typename P1, typename P2, typename P3>
uint GetMethodCode(R (C::*func)(P0 p0, P1 p1, P2 p2, P3 p3))
{
  return 0;
}

template <typename R, typename C, typename P0, typename P1, typename P2, typename P3, typename P4>
uint GetMethodCode(R (C::*func)(P0 p0, P1 p1, P2 p2, P3 p3, P4 p4))
{
  return 0;
}

template <typename R, typename C, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5>
uint GetMethodCode(R (C::*func)(P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5))
{
  return 0;
}

template <typename R, typename C, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>
uint GetMethodCode(R (C::*func)(P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6))
{
  return 0;
}


class ArgWriter
{
public:
  ArgWriter(IMultiPipe* _pipe):
  entityMap(0),
  pipe(_pipe),
  enumerator(0),
  saver( CreateChunklessSaver( &stream, 0, false ) ),
  paramsCount( 0 ),
  _preAllocatedSize( 0 ),
  buffer( 0 ) 
  {
    Reset(0);
  }
  ~ArgWriter()
  {
    Reset(0);
  }
  void Copy(const byte* _data, int _size);
  void SetPipe(IMultiPipe* _pipe) { pipe = _pipe; }
  void SetEntityMap(IEntityMap* _entityMap) { entityMap = _entityMap; }
  void SetEnumerator(IEntityEnumerator* _enumerator) { enumerator = _enumerator; }

  byte* GetBuffer(int size) { return buffer?buffer->begin()+size:0; }
  void Reset(nstl::vector<byte>* _data, bool resetData=true);
  uint size() const { return buffer?buffer->size():0; }
  uint GetParamsCount() const { return paramsCount; }
  uint GetPreAllocatedSize() const { return _preAllocatedSize; }

  bool Push(long value) { return Push(uint(value)); }
  bool Push(unsigned long value) { return Push(uint(value)); } 
  bool Push(long long value);
  bool Push(unsigned long long value);
  bool Push(int value);
  bool Push(uint value);
  bool Push(bool value);
  bool Push(float value);
  bool Push(byte value);
  bool Push(char value);
  bool Push(wchar_t value);
  bool Push(short value);
  bool Push(ushort value);
  bool Push(double value);
  bool Push(const char* value);
  bool Push(const wchar_t* value);
  bool Push(const nstl::string& value);
  bool Push(const nstl::wstring& value);
  bool PushRemoteEntity(rpc::IRemoteEntity* entity, bool pushContent);

  inline void IncrementParamsCount() { paramsCount++; }
  inline void Preallocate(int bytes) { _preAllocatedSize += bytes; }

  template <typename T>
  bool Push(const nstl::vector<T>& value)
  {
    bool isSerializedStruct = SUPERSUBCLASS( rpc::Data, T );
    if (!isSerializedStruct)
      _PushVectorOfSimpleStruct(value);
    else
      _PushVectorOfSerializableStructs(value);
    return true;
  }    

  bool Push(const nstl::vector<rpc::MemoryBlock>& value);

  template <typename T>
  bool Push(const nstl::vector<StrongMT<T> >& value)
  {
    _PushTypeCode(rpc::VectorOfStructs); 
    _PushRaw<uint>(value.size()); 
    for (int i=0;i<value.size();++i)
    {
      Push(value[i]);
    }
    IncrementParamsCount();
    Preallocate(sizeof(nstl::vector<StrongMT<T> >)+sizeof(StrongMT<T>)*value.size());
    return true;
  }    

  bool Push(const nstl::vector<rpc::IRemoteEntity*>& value);

  template <typename T, unsigned int capacity> bool Push(const FixedVector<T, capacity>& value) 
  { 
    const T * ptr = (value.size() > 0)?value.begin():0;
    _PushFixedVectorOfSimpleStruct( sizeof( T ), value.size(), (const byte *)ptr, sizeof( T ) * value.size(), capacity );
    return true;
  }

  bool Push(const nstl::vector<nstl::string>& value)
  {
    _PushVectorOfStrings(value);
    return true;
  } 


  bool Push(const nstl::vector<nstl::wstring>& value)
  {
    _PushVectorOfStrings(value);
    return true;
  }   

  template <typename T>
  bool PushRaw(const T& value)
  {
    _PushRaw<T>(value); 
    return true;
  }

  bool Push(const rpc::MemoryBlock& value);

  template <typename T>
  bool Push(const T& value)
  {
    if ( SUPERSUBCLASS( rpc::Data, T ) ) 
      _PushSerializedStruct( (rpc::Data&)value ); 
    else 
      _PushSimpleStruct(value);
    return true;
  }

  template <typename T>
  bool Push(const StrongMT<T>& value)
  {
    return Push(*const_cast<StrongMT<T>*>(&value));
  }

  template <typename T>
  void PushRef(const T& value)
  {
    Push(value);
  }

  void PushRef(IRemoteEntity* value)
  {
    _PushTypeCode(rpc::SPtr); 
    byte* holderMemory = AllocateAndPush(sizeof(CObjHolder<CObjectBase>));
    new (holderMemory) CObjHolder<IRemoteEntity>(value);
  }

  template <typename T>
  void PushRef(const StrongMT<T>& value)
  {
    if ( SUPERSUBCLASS( rpc::IRemoteEntity, T ) ) 
    {
      PushRef((rpc::IRemoteEntity*)value.Get());
    }
  }

  template <typename T>
  bool Push(StrongMT<T>& value)
  {
    rpc::IRemoteEntity* entity = 0;
    if ( SUPERSUBCLASS( rpc::IRemoteEntity, T ) ) 
    {
      entity = (rpc::IRemoteEntity*)value.Get();
    } else
    {
      T* ptr = value.Get();
      entity = ptr?RemotePtr(value):0;
    }
    return PushRemoteEntity(entity, true);
  }

  byte* PushRemoteEntityBase(rpc::IRemoteEntity* value)
  {
    byte* ptr = AllocateAndPush(sizeof(CObjHolder<CObjectBase>));
    PushRemoteEntity(value, true);
    return ptr;
  }

  bool Push( void* value, uint size )
  {
    _PushTypeCode(rpc::RawStruct); 
    _PushBuffer(value, size); 
    IncrementParamsCount();
    return true;
  }

  template <typename T> 
  bool Push(T* value) 
  { 
    if (SUPERSUBCLASS( rpc::IRemoteEntity, T ))
    {
      return PushRemoteEntity( (rpc::IRemoteEntity*)value, true ); 
    } else
    {
      return false;
    }
  }

  byte* AllocateAndPush(uint size);

  template <typename T>
  void PushByValue(T value)
  {
    if ( SUPERSUBCLASS( rpc::Data, T ) ) 
      _PushSerializedStructByValue( *((rpc::Data*)&value) ); 
    else 
      _PushSimpleStructByValue(value);
  }

  void PushRawString( const void* start, bool isWide );
  template <typename T>
  void PushRawSimpleStruct(const T& value)
  {
    _PushTypeCode(rpc::RawStruct); 
    _PushBuffer(&value, sizeof(T)); 
  }

  // sync
  template <typename T0> bool Sync(byte memberId, const T0& value) 
  { 
    Push(memberId);
    Push(value);
    return true;
  }

  template <typename T0> bool Sync(byte memberId, const nstl::vector<T0>& value) 
  { 
    Push(memberId);
    PushRaw<bool>(false);
    Push(value);
    return true;
  }

  bool Sync(byte memberId, void* value, int size) 
  { 
    Push(memberId);
    Push(value, size);
    return true;
  }

  bool SyncSimpleStruct(byte memberId, void* value, int size)
  {
    Push(memberId);
    _PushTypeCode(rpc::RawStruct); 
    _PushBuffer(value, size); 
    return true;
  }

  bool Sync(byte memberId, IRemoteEntity* value) 
  { 
    Push(memberId);
    PushRemoteEntity(value, true);
    return true;
  }

  void _PushTypeCode(rpc::ParamTypes code)
  {
    _PushRaw<byte>(code); 
  }

  template <typename T>
  bool PushSimpleStructWithoutSize(const T& value)
  {
    _PushTypeCode(rpc::RawStruct); 
    byte* dest = _Allocate(sizeof(T));
    crt::memcpy(dest, sizeof(T), &value, sizeof(T));
    IncrementParamsCount();
    return true;
  }

  void _PushVectorOfSimpleStruct(uint elementSize, uint elementsCount, const byte* data, uint dataBytes);

private:
  void _PushString( const byte* start, uint size, bool isWide);
  void _PushStringContent( const void* start, uint size, bool isWide );

  template <typename T>
  void _PushVectorOfSerializableStructs(const nstl::vector<T>& value)
  {
    _PushTypeCode(rpc::VectorOfStructs); 
    _PushRaw<uint>(sizeof(T)); 
    _PushRaw<uint>(value.size()); 
    if (value.size() > 0) 
    {
      rpc::TypeInfo info = ( (rpc::Data &)value[0] ).GetTypeInfo();
      _PushRaw<uint>(info.id); 
    } else
    {
      _PushRaw<int>(0);  // for empty vectors
    }
    for (int i=0;i<value.size();++i)
    {
      _Serialize((const rpc::Data&)value[i]);
    }
    IncrementParamsCount();
    Preallocate(sizeof(nstl::vector<int>)+2*sizeof(T)*value.size());
  }    

  template <typename T>
  bool _PushVectorOfSimpleStruct(const nstl::vector<T>& value)
  {
    const T * ptr = value.empty() ? 0 : &value[0];
    _PushVectorOfSimpleStruct( sizeof( T ), value.size(), (const byte *)ptr, sizeof( T ) * value.size() );
    return true;
  }
  void _PushVectorOfStrings(const nstl::vector<nstl::string>& value);
  void _PushVectorOfStrings(const nstl::vector<nstl::wstring>& value);
  void _PushFixedVectorOfSimpleStruct(uint elementSize, uint elementsCount, const byte* data, uint dataBytes, uint capacity);

  template <typename T>
  void _PushSimpleStruct(const T& value)
  {
    PushRawSimpleStruct(value);
    IncrementParamsCount();
  }

  template <typename T>
  void _PushSimpleStructByValue(const T& value)
  {
    _PushTypeCode(rpc::RawStructByValue); 
    _PushBuffer(&value, sizeof(T)); 
    IncrementParamsCount();
  }

  byte* _Allocate(uint size);

  template <typename T>
  void _PushRaw(const T& t)
  {
    T* dest = (T*)_Allocate(sizeof(T));
    if (dest)
    {
      *dest = t;
    }
  }

  void _PushBuffer(const void* buffer, uint size);
  void _PushSerializedStruct(const rpc::Data& value);
  void _PushSerializedStructByValue(const rpc::Data& value);
  void _Serialize(const rpc::Data& value);

  nstl::vector<byte>* buffer;
  uint paramsCount;
  uint _preAllocatedSize;
  MemoryStream stream;
  CObj<IBinSaver> saver;
  IEntityMap* entityMap;
  StrongMT<IMultiPipe> pipe;
  IEntityEnumerator* enumerator;
};

template <>
inline bool ArgWriter::Sync(byte memberId, const nstl::string& value)
{ 
  ContainerOperationInfo info = { 0, rpc::String, rpc::soAssign };
  Push(memberId);
  PushRaw<bool>(false);
  Push(info);
  Push(value.c_str());
  return true;
}

template <>
inline bool ArgWriter::Sync(byte memberId, const nstl::wstring& value)
{ 
  ContainerOperationInfo info = { 0, rpc::String, rpc::soAssign };
  Push(memberId);
  PushRaw<bool>(false);
  Push(info);
  Push(value.c_str());
  return true;
}

} // rpc
