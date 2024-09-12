#pragma once

#include "System/fixedvector.h"
#include "System/ported/types.h"
#include "System/ported/cwfn.h"
#include "Packets.h"
#if defined( NV_WIN_PLATFORM )
#include <Rpc.h> //WAT?
#endif

namespace crt
{
  inline unsigned int strlen(const char* value) { return ::strlen(value); }
#if defined( NV_WIN_PLATFORM )
  inline bool memcpy(void *dest, int dest_size, const void *src, int src_size) { return ::memcpy_s(dest, dest_size, src, src_size) == 0; } 
#elif defined( NV_LINUX_PLATFORM )
  inline bool memcpy(void *dest, int dest_size, const void *src, int src_size) { return ::memcpy(dest, src, min<int>(dest_size, src_size)) == 0; } 
#endif
  inline void memset(void *dest, int c, size_t src_size) { ::memset(dest, c, src_size); } 
  inline int strcmp(const char* s0,  const char* s1) { return ::strcmp(s0, s1); } 
}

namespace rpc
{ 

struct MemoryBlock
{
  MemoryBlock():memory(0), size(0) {}
  MemoryBlock(void* _memory, uint _size):memory(_memory), size(_size) {}
  void* memory;
  nival::uint32_t size;
};

struct CachedMemoryBlock : MemoryBlock
{
  CachedMemoryBlock():MemoryBlock() {}

  CachedMemoryBlock(const CachedMemoryBlock& other):MemoryBlock()
  {
    Set(other.memory, other.size);
  }
  CachedMemoryBlock(const void* data, int size)
  {
    Set(data, size);
  }
  ~CachedMemoryBlock()
  {
    Set(0, 0);
  }
  void operator = (const MemoryBlock& other) 
  {
    Set(other.memory, other.size);
  }

  void operator = (const CachedMemoryBlock& other) 
  {
    Set(other.memory, other.size);
  }

  void Set(const void* _memory, uint _size)
  {
    if (memory)
    {
      delete [] (byte*)memory;
    }
    size = _size;
    if (size > 0)
    {
      memory = new byte[size];
      crt::memcpy(memory, size, _memory, size);
    } else
    {
      memory = 0;
    }
  }
};

typedef ushort TransactionId;
#define INVALID_TRANSACTION rpc::TransactionId(-1)

struct MethodInfo
{
  const char* name;
  uint paramsCount;
  bool hasRecieveTime;
  uint methodCode;
};

enum ParamTypes 
{
  Byte4 = 0,            // 0
  Byte8 = 1,            // 1
  Byte1 = 2,            // 2
  Byte2 = 3,            // 3
  String= 4,           // 4
  VectorOfScalars = 5,  // 5
  Struct = 6,           // 6
  RawStruct = 7,        // 7
  StlString = 8,        // 8
  VectorOfStructs = 9,  // 9
  RawStructByValue = 10, // 10
  RemoteEntity = 11,     // 11
  VectorOfStrings = 12,  // 12
  SPtr = 13,             // 13
  FixedVectorOfScalars = 14, // 14
  MemoryBlockType = 15, // 15
  VectorOfMemoryBlocks = 16,  // 16
  StructByValue = 17, // 17
  ParamsCount = 18,
}; // max count no more that 17

template <typename T> 
struct GetTypeT;

template<> struct GetTypeT<int> { enum { type = rpc::Byte4 }; };
template<> struct GetTypeT<uint> { enum { type = rpc::Byte4 }; };
template<> struct GetTypeT<double> { enum { type = rpc::Byte8 }; };
template<> struct GetTypeT<float> { enum { type = rpc::Byte4 }; };
template<> struct GetTypeT<bool> { enum { type = rpc::Byte1 }; };
template<> struct GetTypeT<short> { enum { type = rpc::Byte2 }; };
template<> struct GetTypeT<unsigned short> { enum { type = rpc::Byte2 }; };
template<> struct GetTypeT<byte> { enum { type = rpc::Byte1 }; };
template<> struct GetTypeT<char> { enum { type = rpc::Byte1 }; };
template<> struct GetTypeT<long long> { enum { type = rpc::Byte8}; };
template<> struct GetTypeT<unsigned long long> { enum { type = rpc::Byte8}; };
template<> struct GetTypeT<unsigned long> { enum { type = rpc::Byte4 }; };
template<> struct GetTypeT<long> { enum { type = rpc::Byte4 }; };
template<> struct GetTypeT<wchar_t> { enum { type = rpc::Byte2 }; };
template<> struct GetTypeT<const char *> { enum { type = rpc::String }; };

template<typename T> struct GetTypeT<nstl::vector<T>& > { enum { type = rpc::VectorOfScalars }; };
template<typename T> struct GetTypeT<const nstl::vector<T>& > { enum { type = rpc::VectorOfScalars }; };

template<> struct GetTypeT<const nstl::vector<rpc::MemoryBlock>& > { enum { type = rpc::VectorOfMemoryBlocks}; };
template<> struct GetTypeT<nstl::vector<rpc::MemoryBlock>& > { enum { type = rpc::VectorOfMemoryBlocks}; };

template<> struct GetTypeT<const rpc::MemoryBlock& > { enum { type = rpc::MemoryBlockType }; };
template<> struct GetTypeT<const nstl::string& > { enum { type = rpc::StlString }; };
template<> struct GetTypeT<const nstl::wstring& > { enum { type = rpc::StlString }; };

template<typename T, int C> struct GetTypeT<const FixedVector<T, C>& > { enum { type = rpc::FixedVectorOfScalars }; };


template<> struct GetTypeT<const nstl::vector<nstl::string>& > { enum { type = rpc::VectorOfStrings}; };
template<> struct GetTypeT<nstl::vector<nstl::string>& > { enum { type = rpc::VectorOfStrings}; };
template<> struct GetTypeT<const nstl::vector<nstl::wstring>& > { enum { type = rpc::VectorOfStrings}; };
template<> struct GetTypeT<nstl::vector<nstl::wstring>& > { enum { type = rpc::VectorOfStrings}; };


template <typename T, typename C=int>
struct RValue : public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_1(RValue, BaseObjectMT);
  T result;
  C context;
  mutable volatile rpc::CallStatus status;

  RValue() { Reset(); }

  void OnCall(const T _result){  result = _result; status = rpc::CallSuccessful; }
  void OnCall(const T& _result){  result = _result; status = rpc::CallSuccessful; }
  void OnCallDetailed(const T _result, C _context, rpc::CallStatus _status=rpc::CallSuccessful){  result = _result; context = _context; status = _status; }
  void OnCallDetailed(const T& _result, C _context, rpc::CallStatus _status=rpc::CallSuccessful){  result = _result; context = _context; status = _status; }
  bool IsSet() const { rpc::CallStatus value = status; return value != rpc::CallPending; }
  void Reset() { status = rpc::CallPending; result = T(); }
  const T& Get() const { return result; }
};

template <typename T, typename C=int>
struct RefValue : public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_1(RefValue, BaseObjectMT);
  T result;
  C context;
  mutable volatile rpc::CallStatus status;

  RefValue() { Reset(); }

  void OnCall(const T& _result){  result = _result; status = rpc::CallSuccessful; }
  void OnCallDetailed(const T& _result, C _context, rpc::CallStatus _status=rpc::CallSuccessful){  result = _result; context = _context; status = _status; }

  bool IsSet() const { rpc::CallStatus value = status; return value != rpc::CallPending; }
  void Reset() { status = rpc::CallPending; result = T(); }
  const T& Get() const { return result; }
};

typedef RValue<int, int> RInt;
typedef RValue<uint, int> RUInt;
typedef RValue<double, int> RDouble;
typedef RValue<float, int> RFloat;
typedef RValue<short, int> RShort;
typedef RValue<byte, int> RByte;
typedef RValue<bool, int> RBool;

template <typename T, typename C=int>
struct SPtrValue : public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_1(SPtrValue, BaseObjectMT);
  StrongMT<T> result;
  C context;
  mutable volatile rpc::CallStatus status;

  SPtrValue() { Reset(); }
  void OnCall(T* _result)
  {  
    result = _result; 
    status=rpc::CallSuccessful; 
  }
  void OnCallDetailed(T* _result, C _context, rpc::CallStatus _status=rpc::CallSuccessful)
  {  
    result = _result; 
    context = _context; 
    status = _status; 
  }

  bool IsSet() const { rpc::CallStatus value = status; return value != rpc::CallPending; }
  void Reset() { status = rpc::CallPending; result = 0; context=C();}
  T* Get() { return result.Get(); }
};

#define LogTrace if ( logTrace && logTrace->CheckLog(1)) logTrace->Trace
#define LogTrace2 if ( logTrace && logTrace->CheckLog(1)) logTrace->TraceDetailed
#define LogTrace3 if ( logTrace && logTrace->CheckLog(2)) logTrace->TraceDetailed


typedef uint EntityId;
#define INVALID_ENTITY rpc::EntityId(-1)


enum StringOperations
{
  soAssign = 0,
  soSetByIndex = 2,
};

enum VectorOperations
{
  voAppend = 0,
  voSet = 1,
  voEraseByIndex = 2,
};


struct ContainerOperationInfo
{
  int index;
  byte operationScope;
  byte operationType;
};

typedef char * VArgList;

inline bool IsGUIDEmpty(const GUID& id)
{
  return id.Data1 == 0 && id.Data2 == 0 && id.Data3 == 0 && (*(int*)((byte*)(id.Data4))) == 0 && (*(int*)((byte*)(id.Data4+4))) == 0;
}

struct NodeDescription
{
  NodeDescription()
  {
    name.clear();
    crt::memset(&guid, 0, sizeof(GUID));
  }

  bool IsIdentified() const { return !IsGUIDEmpty(guid); }
  void SetId(const GUID& _value) { guid = _value; }

  void Generate()
  {
    ::UuidCreate(&guid);
  }

  nstl::string name;
  GUID guid;
};

} // rpc
