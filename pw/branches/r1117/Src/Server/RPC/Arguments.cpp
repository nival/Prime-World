#include "stdafx.h"

#pragma warning( push ) 
#pragma warning( disable: 4512 ) //assignment operator could not be generated   

#include <RPC/RPC.h>
#include <RPC/EntityMap.h>
#include <System/Crc32Checksum.h>
#include <System/DebugVar.h>
#include "Transaction.h"
#include "ClassFactory.h"
#include "System/InlineProfiler.h"
#pragma warning( pop )

namespace rpc
{


#if defined( NV_WIN_PLATFORM )

typedef short                          Int16T;
typedef ushort                         UInt16T;
typedef int                            Int32T;
typedef uint                           UInt32T;
typedef long long                      Int64T;
typedef unsigned long long             UInt64T;

#elif defined( NV_LINUX_PLATFORM )

typedef nival::int16_t                 Int16T;
typedef nival::uint16_t                UInt16T;
typedef nival::int32_t                 Int32T;
typedef nival::uint32_t                UInt32T;
typedef nival::int64_t                 Int64T;
typedef nival::uint64_t                UInt64T;

#endif


  
static NDebug::DebugVar<int> rpcMethodCallsSent( "NET|RPC calls sent", "" );

const byte* ArgReader::PopSimpleStruct(bool& result, int size)
{
  ParamInfo type = PopTypeCode(result);
  if (result && type.code == rpc::RawStruct)
  {
    return PopSimpleStructRaw(result, size);
  }
  result = false;
  return 0;
}

const MemoryBlock* ArgReader::PopMemoryBlockRaw(bool& result)
{
  rpc::MemoryBlock* block = (rpc::MemoryBlock*)_AllocateBuffer(sizeof(rpc::MemoryBlock));
  if (block)
  {
    _PopMemoryBlockRaw(result, block);
    return block;
  }
  result = false;
  return 0;
}

void ArgReader::_PopMemoryBlockRaw( bool& result, rpc::MemoryBlock* block )
{
  uint blockSize = PopRaw<UInt16T>(result);
  if (result)
  {
    const byte* blockData = PopData(blockSize, result);
    if (result)
    {
      block->memory = (void*)(const_cast<byte*>(blockData));
      block->size = blockSize;
      return;
    }
  } 
  block->memory = 0;
  block->size = 0;
}

const byte* ArgReader::PopSimpleStructRaw(bool& result, int size, int* structSize)
{
  uint data_size = PopRaw<UInt16T>(result);
  if (result)
  {
    if (structSize)
    {
      *structSize = data_size;
    }
    if (size == -1 || data_size == uint(size))
    {
      return PopData(data_size, result);
    }
  }
  result = false;
  return 0;
}
struct DummyStruct
{
  byte data[24];
};

void ArgReader::_PopSimpleStructToMemory(bool& result, void* memory, uint size)
{
  ParamInfo type = PopTypeCode(result);
  type;
  if (result)
  {
    PopData(memory, size, result);
  }
}

rpc::Data* ArgReader::PopRawSerializedData(bool& result, DataFactory* factory, int dataStructSize)
{
  return _PopRawSerializedData(result, -1, factory, dataStructSize);
}

rpc::Data* ArgReader::_PopRawSerializedData(bool& result, int size, DataFactory* factory, int dataStructSize)
{
  SerializableStructInfo info;
  info.structId = PopRaw<Int32T>(result);
  if (result)
  {
    info.instanceSize = PopRaw<UInt16T>(result);
    if (result)
    {
      if (size < 0 || size == info.instanceSize)
      {
        info.bufferSize = PopRaw<UInt16T>(result);
        if (result)
        {
          info.bufferStart = PopData(info.bufferSize, result);
          int realDataStructSize = info.instanceSize;
          void* buffer;
          if ( info.instanceSize > info.bufferSize )
          {
            realDataStructSize = dataStructSize > (info.instanceSize-info.bufferSize) ? dataStructSize : info.instanceSize-info.bufferSize;
            buffer = _AllocateBuffer(info.bufferSize+realDataStructSize);
          }
          else
          {
            realDataStructSize = dataStructSize > info.instanceSize ? dataStructSize : info.instanceSize;
            buffer = _AllocateBuffer(realDataStructSize);
          }
          if (buffer)
          {
            return Deserialize(info.structId, const_cast<byte*>(info.bufferStart), info.bufferSize, buffer, factory, result);
          } 
        }
      } 
    }
  }
  result = false;
  return 0;
}

rpc::Data* ArgReader::_PopSerializedStruct(bool& result, uint size, DataFactory* factory)
{
  ParamInfo param = PopTypeCode(result); 
  if (result && rpc::Struct == param.code)
  {
    return _PopRawSerializedData(result, size, factory); 
  }
  result = false;
  return 0;
}

rpc::Data* ArgReader::PopSerializedStruct(bool& result, DataFactory* factory)
{
  ParamInfo param = PopTypeCode(result); 
  if (result && rpc::Struct == param.code)
  {
    return PopRawSerializedData(result, factory, sizeof(rpc::Data)); 
  }
  result = false;
  return 0;
}

template <>
const char* ArgReader::Pop<const char*>(bool& result)
{
  return (const char*)PopString(result, false);
}

static const nstl::string nullString;
static const nstl::wstring nullWString;

template <> 
const char* ArgReader::PopRaw<const char*>(bool& result)
{
  return (const char*)_PopString(result, false);
}

template <> 
const nstl::string& ArgReader::PopRaw<const nstl::string&>(bool& result)
{
  void* buffer = _AllocateBuffer(sizeof(xstring));
  if (buffer)
  {
    return *((const nstl::string*)_PopXString(buffer, result));
  }
  result = false;
  return nullString;
}

template <> const nstl::wstring& ArgReader::PopRaw<const nstl::wstring&>(bool& result)
{
  void* buffer = _AllocateBuffer(sizeof(xstring));
  if (buffer)
  {
    return *((const nstl::wstring*)_PopXString(buffer, result));
  }
  result = false;
  return nullWString;
}


static const byte emptyString[4] = {0, 0, 0, 0};

xstring* ArgReader::_CreateString(void* buffer, const byte* value, uint length, bool isWide)
{
  xstring* s = new (buffer) xstring(value, length, isWide);
  strings.push_back(s);
  return s;
}

const nstl::string& ArgReader::PopEmptyString()
{
  void* buffer = _AllocateBuffer(sizeof(xstring));
  if (buffer)
  {
    return *((const nstl::string*)_CreateString(buffer, emptyString, 0, false));
  }
  return nullString;
}

const nstl::wstring& ArgReader::PopEmptyWideString()
{
  void* buffer = _AllocateBuffer(sizeof(xstring));
  if (buffer)
  {
    return *((const nstl::wstring*)_CreateString(buffer, emptyString, 0, true));
  }
  return nullWString;
}

xstring* ArgReader::_PopXString(void* buffer, bool& result)
{
  bool isWide = PopRaw<bool>(result);
  ushort length = PopRaw<UInt16T>(result);
  if (result && length > 0)
  {
    return _PopStringContent(buffer, length, result, isWide);
  } 
  return _CreateString(buffer, emptyString, 0, isWide);
}

template <> 
const nstl::string& ArgReader::Pop<const nstl::string&>(bool& result)
{
  ParamInfo param = PopTypeCode(result); 
  if (result && rpc::StlString == param.code)
  {
    return PopRaw<const nstl::string&>(result);
  } 
  return PopEmptyString();
}

template <> 
const nstl::wstring& ArgReader::Pop<const nstl::wstring&>(bool& result)
{
  ParamInfo param = PopTypeCode(result); 
  if (result && rpc::StlString == param.code)
  {
    return PopRaw<const nstl::wstring&>(result);
  } 
  return PopEmptyWideString();
}

void Arguments::Reset(const byte* _data, uint preAllocatedSize, uint paramsSize)
{
  reader.Reset(_data, paramsSize, preAllocatedSize);
}

static xvector emptyVector;
const uint maxVectorContentSize = 64*1024;

uint GetVectorContentSize(uint elementsCount, uint elementSize)
{
  if (elementSize == 0 ) //видимо получили какой-то левый тип данных
    return 0;

  uint desiredElementsCount = maxVectorContentSize/elementSize;
  if (elementsCount < desiredElementsCount)
  {
    return elementsCount*elementSize;
  }
  return 0;
}


xvector* ArgReader::_PopVectorOfSerializedStructs(uint elementSize, uint elementsCount, bool& result, DataFactory* factory)
{
  NI_VERIFY(elementsCount > 0, "Vector size should be greater than 0", return &emptyVector);
  uint structId = PopRaw<UInt32T>(result); 
  if (result)
  {
    if (structId > 0)
    {
      DataFactory* _factory = factory?factory:GetGlobalDataFactory();
      elementSize = _factory->GetRealSize( structId );
      uint dataBytes = GetVectorContentSize(elementsCount, elementSize);
      if (dataBytes > 0)
      {
        xvector* s = _AllocateVector();
        if (s)
        {
          void* start = _AllocateBuffer(dataBytes);
          if (start)
          {
            result = DeserializeVector(start, elementsCount, structId, factory, elementSize);
            if (result)
            {
              s->Set((byte*)start, dataBytes);
            }
            return s;
          }
        }
      }
    }
  }
  result = false;
  return &emptyVector;
}

bool ArgReader::DeserializeVector( void* start, uint elementsCount, uint structId, DataFactory* factory, uint elementSize)
{
  bool result = true;
  byte* current = (byte*)start;
  for (uint i=0;result && i<elementsCount;++i)
  {
    ushort itemSize = PopRaw<UInt16T>(result);
    if (result)
    {
      const byte* itemData = PopData(itemSize, result);
      if (result)
      {
        Deserialize(structId, const_cast<byte*>(itemData), itemSize, current, factory, result);
        current += elementSize;
      } 
    } 
  }
  return result;
}


xvector* ArgReader::_AllocateVector()
{
  void* buffer = _AllocateBuffer(sizeof(xvector));
  if (buffer)
  {
    xvector* s = new (buffer) xvector;
    NI_ASSERT(s, "Placement new can't be null");
    vectors.push_back((xvector*)s);
    return s; 
  }
  return 0;
}

xvector* ArgReader::_PopVectorOfSimpleStructs(uint elementSize, uint elementsCount, bool& result)
{
  NI_VERIFY(elementsCount > 0, "Vector size should be greater than 0", return &emptyVector);
  uint dataBytes = GetVectorContentSize(elementsCount, elementSize);
  if (dataBytes > 0)
  {
    xvector* s = _AllocateVector();
    if (s)
    {
      const byte* start = PopData(dataBytes, result);
      if (result)
      {
        s->Set((byte*)start, dataBytes);
      }
      return s;
    }
  }
  result = false;
  return &emptyVector;
}

void* ArgReader::_PopFixedVector(bool& result, uint expectedCapacity, int expectedSize)
{
  ParamInfo param = PopTypeCode(result); 
  if (result && rpc::FixedVectorOfScalars == param.code)
  {
    return _PopFixedVectorWithoutTypeCode(result, expectedCapacity, expectedSize);
  }
  result = false;
  return 0;
}

bool ArgReader::UpdateLocalEntity(rpc::LocalEntityInfo& info, uint dataSize)
{
  bool result = true;
  uint limitLength = length-dataSize;
  while (result && length > limitLength) {
    ParamInfo type = PopTypeCode(result); 
    if (result && rpc::Byte1 == type.code) 
    {
      byte memberId = PopRaw<byte>(result);
      if (result) 
      {
        lparents.push_back(info.Get());
        result = info.Get()->vset(memberId, *this);
        lparents.pop_back();
        NI_ASSERT(result, NI_STRFMT( "Parameter parsing failed: memberId(%d)", memberId));
      }
      if (result)
      {
        IFunctor* f = info.isHandled(memberId);
        if (f)
        {
          f->Call(0);
        }
      } 
    } else
    {
      NI_ALWAYS_ASSERT(NI_STRFMT( "Parameters parsing failed while set fields for entity"));
      result = false;
    }
  }
  return result;
}

bool ArgReader::UpdateRemoteEntity(rpc::IRemoteEntity* entity, uint classCrc, uint dataSize)
{
  bool result = true;
  if (dataSize > 0)
  {
    uint localClassCrc = entity->GetInfo().typeInfo.classCrc;
    if (classCrc != localClassCrc)
    {
      return true; // we just recieved update data for already deleted and newly created object of different type
    }              

    uint limitLength = length-dataSize;
    while (result && length > limitLength) {
      ParamInfo type = PopTypeCode(result); 
      if (result && rpc::Byte1 == type.code) 
      {
        uint memberId = PopRaw<byte>(result);
        if (result) 
        {
          rparents.push_back(entity);
          result = entity->vset(memberId, *this);
          rparents.pop_back();
          NI_ASSERT(result, NI_STRFMT( "Parameter parsing failed: memberId(%d)", memberId));
        } 
      } else
      {
        NI_ALWAYS_ASSERT(NI_STRFMT( "Parameters parsing failed while updating entity fields"));
        result = false;
      }
    }
  }
  if (result)
  {
    entity->GetHandler()->MarkUpdated(entity, dataSize);
  }
  return result;
}

const nstl::vector<rpc::MemoryBlock>* ArgReader::PopVectorOfMemoryBlocksRaw(bool &result)
{
  int elementsCount = PopRaw<Int32T>(result); 
  if (elementsCount > 0) 
  {
    uint dataBytes = GetVectorContentSize(elementsCount, sizeof(rpc::MemoryBlock));
    if (dataBytes > 0)
    {
      xvector* s = _AllocateVector();
      if (s)
      {
        void* buffer = _AllocateBuffer(dataBytes);
        if (buffer)
        {
          rpc::MemoryBlock* blocks = (rpc::MemoryBlock*)buffer;
          for (int i=0;i<elementsCount && result;++i)
          {
            _PopMemoryBlockRaw(result, blocks++);
          }
          if (result)
          {
            s->Set((byte*)buffer, dataBytes);
          }
          return (const nstl::vector<rpc::MemoryBlock>*)s;
        }
      }
    }
  } else
  {
    return (const nstl::vector<rpc::MemoryBlock>*)&emptyVector;
  }
  result = false;
  return (const nstl::vector<rpc::MemoryBlock>*)&emptyVector;
}


void* ArgReader::_PopFixedVectorWithoutTypeCode(bool& result, uint expectedCapacity, int expectedSize)
{
  int elementSize = PopRaw<Int32T>(result); 
  if (result)
  {
    uint elementsCount = PopRaw<UInt32T>(result); 
    if (result) 
    { 
      uint capacity = PopRaw<UInt32T>(result); 
      if ( (expectedCapacity != 0 && capacity != expectedCapacity) || (expectedSize != -1 && expectedSize != elementSize))
      {
        result = false;
      } else
      {
        uint dataBytes = GetVectorContentSize(elementsCount, elementSize);
        if (dataBytes > 0)
        {
          const byte* start = PopData(dataBytes, result);
          if (result)
          {
            void* buffer = _AllocateBuffer(elementSize*capacity+sizeof(uint));
            if (buffer)
            {
              crt::memcpy(buffer, elementSize*capacity, start, dataBytes);
              uint* size = (uint*)((byte*)buffer+elementSize*capacity);
              *size = elementsCount;
              return buffer;
            }
          }
        }
      }
    }
  }
  result = false;
  return 0;
}

rpc::Data* ArgReader::Deserialize(uint structId, byte* source, uint sourceSize, void* target, DataFactory* _factory, bool& result)
{
  DataFactory* factory = _factory?_factory:GetGlobalDataFactory();
  FixedMemoryStream stream(source, sourceSize );
  CObj<IBinSaver> pSaver = CreateChunklessSaver( GetAddress(stream), 0, true );
  rpc::Data* data = factory->Create(structId, target);
  if (data)
  {
    data->operator &(*pSaver);
    datas.push_back(data);
  }
  if (pSaver->GetError() == IBinSaver::BINSAVER_ERR_OK)
  {
    return data;
  } 
  else
  {
    result = false;
    return 0;
  }
}

xvector* ArgReader::_PopVectorOfAnyStrings( bool& result )
{
  int elementsCount = PopRaw<UInt16T>(result); 
  if (elementsCount == 0) { return &emptyVector; }
  bool isWide = PopRaw<bool>(result);
  if (result)
  {
    uint dataBytes = GetVectorContentSize(elementsCount, GetStringSize(isWide));
    if (dataBytes > 0)
    {
      xvector* v  = _AllocateVector();
      if (v)
      {
        void* start = _AllocateBuffer(dataBytes);
        if (start)
        {
          v->Set((byte*)start, dataBytes);
          byte* data = (byte*)start;
          for (int i=0;result && i<elementsCount;++i)
          {
            ParamInfo param = PopTypeCode(result); 
            if (result && rpc::StlString == param.code)
            {
#if defined( NV_WIN_PLATFORM )
              _PopXString(data, result);
#elif defined( NV_LINUX_PLATFORM )
              *(xstring**)data = _PopXString(data, result);
#endif
            }
            data += GetStringSize(isWide);
          }
          return v;
        }
      }
    }
  }
  result = false;
  return &emptyVector;
}

xvector* ArgReader::_PopVectorWithoutTypeCode(int expectedElementSize, bool& result, DataFactory* factory)
{
  int elementSize = PopRaw<Int32T>(result); 
  if (result)
  {
    if (expectedElementSize == elementSize || expectedElementSize == -1)
    {
      uint elementsCount = PopRaw<UInt32T>(result);
      if (result) 
      { 
        if (elementsCount > 0)
        {
          if (factory)
          {
            return _PopVectorOfSerializedStructs(elementSize, elementsCount, result, factory);
          } else
          {
            return _PopVectorOfSimpleStructs(elementSize, elementsCount, result);
          }
        } else
        {
          if (factory)
          {
            uint value = PopRaw<UInt32T>(result);
            NI_ASSERT(0 == value, "Expected 0");
          }
        }
      }
    }
  }
  return &emptyVector;
}

xvector* ArgReader::_PopVector(int expectedElementSize, bool& result, DataFactory* factory)
{
  ParamInfo param = PopTypeCode(result); 
  if (result && (rpc::VectorOfScalars == param.code || rpc::VectorOfStructs == param.code))
  {
    return _PopVectorWithoutTypeCode(expectedElementSize, result, factory);
  }
  result = false;
  return &emptyVector;
}

void* ArgReader::_AllocateBuffer(int size)
{
  int old_size = bytes.size();
  NI_VERIFY(old_size+size <= bytes.capacity(), "Reallocations are prohibited because of possible heap corruption after memory reallocation", return 0);
  bytes.resize(old_size+size);
  return &bytes[old_size];
}

rpc::IRemoteEntity* ArgReader::_PopRemoteEntity( bool& result, IRemoteEntityFactory* factory )
{
  ParamInfo param = PopTypeCode(result); 
  if (result && rpc::RemoteEntity == param.code)
  {
    return PopRawRemoteEntity( result, factory );
  }
  result = false;
  return 0;
}

IRemoteEntity* ArgReader::PopRawRemoteEntity(bool& result, IRemoteEntityFactory* factory) 
{
  const RemoteEntityInfo& info = PopStruct<RemoteEntityInfo>(result, 0);
  if (result)
  {
    const char* sourceNodeName = pipe->GetName();

    const char* nodeName = Pop<const char*>(result);
    if (!result) { return 0; }

    int lnodeCount = PopRaw<Int16T>(result);
    if (!result) { return 0; }

    GUID lnodeId;
    memset(&lnodeId, 0, sizeof(GUID));
    if (lnodeCount > 0)
    {
      NI_ASSERT(lnodeCount == 1, "Pointers to replicated objects currently are not supported");
      lnodeId = PopStruct<GUID>(result, 0);
      if (!result) { return 0; }
    }
    const GUID& rnodeId = PopStruct<GUID>(result, 0);
    if (result)
    {
      if (!info.IsNull())
      {
        IRemoteEntity* entity = 0;
        if (nodeName)
        {
          NI_ASSERT( !IsGUIDEmpty( lnodeId ), "Node GUID should not be empty" );
          entity = entityMap->ConnectToEntity(info, sourceNodeName, nodeName, lnodeId, factory, rnodeId, GetLastRemoteEntity());
        } else
        {
          entity = entityMap->ConnectToEntity(info, 0, sourceNodeName, rnodeId, factory, rnodeId, GetLastRemoteEntity());
        }
        if (entity)
        {
          readEntities.push_back(entity);
        }
        int dataSize = PopRaw<Int32T>(result);
        if (entity && result)
        {
          result = UpdateRemoteEntity(entity, info.typeInfo.classCrc, dataSize);
        }
        return entity;
      }  else
      {
        /*int dataSize = */PopRaw<Int32T>(result);
        return 0;
      }
    }
  } 
  result = false;
  return 0;
}

void ArgWriter::Copy(const byte* _data, int _size)
{
  if (buffer)
  {
    byte* start = _Allocate(_size);
    if (start)
    {
      crt::memcpy(start, _size, _data, _size);
    }
  }
}

bool ArgWriter::Push(const rpc::MemoryBlock& value)
{
  _PushTypeCode(rpc::MemoryBlockType); 
  _PushBuffer(value.memory, value.size);
  IncrementParamsCount();
  Preallocate(sizeof(rpc::MemoryBlock));
  return true;
}

bool ArgWriter::Push(const nstl::vector<rpc::IRemoteEntity*>& value)
{
  _PushTypeCode(rpc::VectorOfStructs);
  _PushRaw<UInt32T>(value.size()); 
  for (int i=0;i<value.size();++i)
  {
    Push(value[i]);
  }
  IncrementParamsCount();
  Preallocate(sizeof(nstl::vector<rpc::IRemoteEntity*>)+sizeof(rpc::IRemoteEntity*)*value.size());
  return true;
}   

void ArgWriter::_PushSerializedStructByValue(const rpc::Data& value)
{
  _PushTypeCode(rpc::StructByValue); 
  rpc::TypeInfo info = value.GetTypeInfo();
  _PushRaw<UInt32T>(info.id); 
  NI_ASSERT(info.size <= USHRT_MAX, "Size of struct should be less than USHRT_MAX");
  _PushRaw<UInt16T>(ushort(info.size)); 
  _Serialize(value);
  IncrementParamsCount();
  Preallocate(info.size + 24);
}    

void ArgWriter::_PushSerializedStruct(const rpc::Data& value)
{
  _PushTypeCode(rpc::Struct); 
  rpc::TypeInfo info = value.GetTypeInfo();
  _PushRaw<UInt32T>(info.id); 
  NI_ASSERT(info.size <= USHRT_MAX, "Size of struct should be less than USHRT_MAX");
  _PushRaw<UInt16T>(UInt16T(info.size)); 
  _Serialize(value);
  IncrementParamsCount();
  Preallocate(info.size + 24);
}    

void ArgWriter::_Serialize(const rpc::Data& value)
{
  stream.Seek(0, SEEKORIGIN_BEGIN);
  const_cast<rpc::Data&>(value).operator &(*saver);
  const char* _buffer = stream.GetBuffer();
  uint size = stream.GetPosition();
  _PushBuffer(_buffer, size);
}

byte* ArgWriter::AllocateAndPush(uint size)
{
  _PushRaw<UInt16T>(size);
  return _Allocate(size);
}

void ArgWriter::_PushBuffer(const void* _buffer, uint size)
{
  byte* dest = AllocateAndPush(size);
  if (dest)
  {
    crt::memcpy(dest, size, _buffer, size);
  }
}

byte* ArgWriter::_Allocate(uint size)
{
  if (buffer)
  {
    int position = buffer->size();
    buffer->resize(buffer->size()+size);
    return buffer->begin()+position;
  }
  return 0;
}

bool ArgWriter::Push(int value)
{
  _PushTypeCode(rpc::ParamTypes(rpc::GetTypeT<int>::type)); 
  _PushRaw<Int32T>(value); 
  IncrementParamsCount();
  return true;
}    

struct EntityEnumerator : IEntityEnumerator
{
  virtual void OnProcess(rpc::IRemoteEntity* entity)
  {
    entities.push_back(entity);
  }
  void Share(IMultiPipe* pipe)
  {
    for (int i=0;i<entities.size();++i)
    {
      entities[i]->GetHandler()->MarkShared(pipe, entities[i]);
    }
  }
  nstl::vector<rpc::IRemoteEntity*> entities;
};

bool ArgWriter::PushRemoteEntity(rpc::IRemoteEntity* entity, bool pushContent)
{
  if (entity && enumerator)
  {
    enumerator->OnProcess(entity);
  }
  static GUID nullGUID = {0, 0, 0, 0};
  const GUID& gateID = entityMap->GetGateID();
  const rpc::LocalInstanceInfo* linfo = entity?entity->GetLocalInstanceInfo():0;
  if (linfo)
  {
    StrongMT<rpc::IRemoteEntity> obj = entity;
    RemoteEntityInfo info;
    if (entityMap)
    {
      ILocalEntity* localEntity = entityMap->CreateLocalEntity(linfo->instance, info, linfo->classId);
      if (localEntity)
      {
        PushRaw(byte(rpc::RemoteEntity));
        PushRawSimpleStruct(info);
        if (linfo->gateName.length() > 0)
        {
          PushRawString(linfo->gateName.c_str(), false);
        } else
        {
          PushRawString(0, false);
        }
        PushRaw(short(1));
        PushRawSimpleStruct(gateID);
        PushRawSimpleStruct(gateID);
        IncrementParamsCount();

        if (pipe)
        {
          for (int i=0;i<pipe->GetCount();++i)
          {
            if ( StrongMT<rpc::INode> node = pipe->GetNode(i) )
            {
              entityMap->ShareEntity(gateID, info.entityId, node->GetDesc().guid, info.entityGUID, false);
            }
          }
        }

        int currentIndex = buffer->size();
        PushRaw(int(0));

        if (pushContent)
        {
          int currentSize = buffer->size();
          ArgWriter w(pipe);
          w.SetEntityMap(entityMap);
          w.SetEnumerator(enumerator);
          w.Reset(buffer, false);
          localEntity->Update(&w);
          Preallocate(w.GetPreAllocatedSize());
          byte* dataSizePtr = buffer->begin()+currentIndex;
          *((int*)dataSizePtr) = buffer->size()-currentSize;
        }
        return true;
      } else
      {
        NI_ALWAYS_ASSERT("Can't create local entity");
        return false;
      }
    }
    else
    {
      return false;
    }
  } else
  {
    PushRaw(byte(rpc::RemoteEntity));
    RemoteEntityInfo info = entity?entity->GetInfo():NullInfo;
    PushRawSimpleStruct(info);

    bool found = false;
    if (entity)
    {
      nstl::vector<NodeBriefDesc> nodes;
      entity->GetHandler()->GetAllNodes(nodes);
      if (nodes.size() == 1)
      {
        PushRawString(nodes[0].nodeName.c_str(), false);
        PushRaw(short(1));
        NI_ASSERT( !IsGUIDEmpty(nodes[0].id), "Node GUID should not be empty" );
        PushRawSimpleStruct(nodes[0].id);
        found = true;
      }
      else
      {
        NI_ALWAYS_ASSERT("Pointers to replicated objects currently are not supported");
      }
    } 
    if (!found)
    {
      PushRawString(0, false);
      PushRaw(short(0));
    }
    PushRawSimpleStruct(gateID);
    IncrementParamsCount();
    PushRaw(int(0));
    if (entity)
    {
//      ArgWriter w(0, 0);
      //EntityEnumerator e;
      //w.SetEnumerator(&e);
      //entity->Synchronize(&w);
      entity->GetHandler()->MarkShared(pipe, entity);
      //e.Share(pipe);
    }
    return true;
  }
}

bool ArgWriter::Push(long long value)
{
  _PushTypeCode(rpc::Byte8); 
  _PushRaw<Int64T>(value); 
  IncrementParamsCount();
  return true;
}    

bool ArgWriter::Push(unsigned long long value)
{
  _PushTypeCode(rpc::Byte8); 
  _PushRaw<UInt64T>(value); 
  IncrementParamsCount();
  return true;
}    

bool ArgWriter::Push(uint value)
{
  _PushTypeCode(rpc::Byte4);
  _PushRaw<UInt32T>(value); 
  IncrementParamsCount();
  return true;
}    

bool ArgWriter::Push(bool value)
{
  _PushTypeCode(rpc::Byte1); 
  _PushRaw<bool>(value); 
  IncrementParamsCount();
  return true;
}    

bool ArgWriter::Push(float value)
{
  _PushTypeCode(rpc::Byte4); 
  _PushRaw<float>(value); 
  IncrementParamsCount();
  return true;
}    

bool ArgWriter::Push(byte value)
{
  _PushTypeCode(rpc::Byte1); 
  _PushRaw<byte>(value); 
  IncrementParamsCount();
  return true;
}    

bool ArgWriter::Push(wchar_t value)
{
  _PushTypeCode(rpc::Byte2); 
  _PushRaw<UInt16T>(UInt16T(value));
  IncrementParamsCount();
  return true;
}    

bool ArgWriter::Push(char value)
{
  _PushTypeCode(rpc::Byte1); 
  _PushRaw<char>(value); 
  IncrementParamsCount();
  return true;
}    

bool ArgWriter::Push(short value)
{
  _PushTypeCode(rpc::Byte2); 
  _PushRaw<Int16T>(value); 
  IncrementParamsCount();
  return true;
}    

bool ArgWriter::Push(ushort value)
{
  _PushTypeCode(rpc::Byte2); 
  _PushRaw<UInt16T>(value); 
  IncrementParamsCount();
  return true;
}    

bool ArgWriter::Push(double value)
{
  _PushTypeCode(rpc::Byte8); 
  _PushRaw<double>(value); 
  IncrementParamsCount();
  return true;
}    

void ArgWriter::_PushString( const byte* start, uint size, bool isWide)
{
  _PushTypeCode(rpc::StlString); 
  _PushRaw<bool>(isWide); 
  _PushStringContent(start, size, isWide);
  Preallocate(GetStringSize(isWide));
}

void ArgWriter::_PushStringContent( const void* start, uint size, bool isWide )
{
  _PushRaw<UInt16T>(size); 
  if (size > 0)
  {
    uint length = size+1;
    if (isWide)
    {
#if defined( NV_WIN_PLATFORM )
      length *= sizeof(wchar_t);
#elif defined( NV_LINUX_PLATFORM )
      length *= 2;
#endif
    }
    byte* dest = _Allocate(length);
    if (dest)
    {
#if defined( NV_WIN_PLATFORM )
      crt::memcpy(dest, length, start, length);
#elif defined( NV_LINUX_PLATFORM )
      if ( isWide )
      {
        nival::uint16_t * p = ( nival::uint16_t* ) dest;
        const wchar_t * s = static_cast< const wchar_t * >( start );
        std::copy( s, s + size + 1, p );
      }
      else
      {
        crt::memcpy(dest, length, start, length);
      }
#endif
    }
  }
}


void ArgWriter::PushRawString(const void* value, bool isWide)
{
  _PushTypeCode(rpc::String); 
  int size = value?(isWide?wcslen((const wchar_t*)value):crt::strlen((const char*)value)):0;
  _PushStringContent(value, size, isWide);
}

bool ArgWriter::Push(const wchar_t* value)
{
  PushRawString(value, true);
  IncrementParamsCount();
  return true;
}

bool ArgWriter::Push(const char* value)
{
  PushRawString(value, false);
  IncrementParamsCount();
  return true;
}    

bool ArgWriter::Push( const nstl::string& value )
{
  _PushString((const byte*)value.c_str(), value.size(), false);
  IncrementParamsCount();
  return true;
}    

bool ArgWriter::Push( const nstl::wstring& value )
{
  _PushString((const byte*)value.c_str(), value.size(), true);
  IncrementParamsCount();
  return true;
}    

void ArgWriter::Reset( nstl::vector<byte>* _data, bool resetData )
{
  buffer = _data;
  if (buffer && resetData)
  {
    buffer->resize(0);
  }
  paramsCount = 0;
  _preAllocatedSize = 0;
}

bool ArgWriter::Push(const nstl::vector<rpc::MemoryBlock>& value)
{
  _PushTypeCode(rpc::VectorOfMemoryBlocks); 
  _PushRaw<UInt32T>(value.size()); 
  for (int i=0;i<value.size();++i)
  {
    _PushBuffer(value[i].memory, value[i].size);
    Preallocate(sizeof(rpc::MemoryBlock));
  }
  IncrementParamsCount();
  Preallocate(sizeof(nstl::vector<rpc::MemoryBlock>));
  return true;
}

void ArgWriter::_PushVectorOfSimpleStruct(uint elementSize, uint elementsCount, const byte* data, uint dataBytes)
{
  _PushTypeCode(rpc::VectorOfScalars); 
  _PushRaw<UInt32T>(elementSize); 
  _PushRaw<UInt32T>(elementsCount); 

  if (dataBytes > 0)
  {
    byte* dest = _Allocate(dataBytes);
    crt::memcpy(dest, dataBytes, data, dataBytes);
  }
  IncrementParamsCount();
  Preallocate(sizeof(nstl::vector<int>));
}

void ArgWriter::_PushFixedVectorOfSimpleStruct(uint elementSize, uint elementsCount, const byte* data, uint dataBytes, uint capacity)
{
  _PushTypeCode(rpc::FixedVectorOfScalars); 
  _PushRaw<UInt32T>(elementSize); 
  _PushRaw<UInt32T>(elementsCount); 
  _PushRaw<UInt32T>(capacity); 

  if (dataBytes > 0)
  {
    byte* dest = _Allocate(dataBytes);
    crt::memcpy(dest, dataBytes, data, dataBytes);
  }
  IncrementParamsCount();
  Preallocate(elementSize*capacity+sizeof(uint));      // this value depends from internal mechanics of fixed vector
}

void ArgWriter::_PushVectorOfStrings(const nstl::vector<nstl::string>& value)
{
  _PushTypeCode(rpc::VectorOfStrings); 
  _PushRaw<UInt16T>(value.size()); 
  _PushRaw<bool>(false); 

  for (int i=0;i<value.size();++i)
  {
    _PushString((const byte*)value[i].c_str(), value[i].size(), false);
  }
  IncrementParamsCount();
  Preallocate(sizeof(nstl::vector<nstl::string>));
}

void ArgWriter::_PushVectorOfStrings(const nstl::vector<nstl::wstring>& value)
{
  _PushTypeCode(rpc::VectorOfStrings); 
  _PushRaw<UInt16T>(value.size()); 
  _PushRaw<bool>(true); 

  for (int i=0;i<value.size();++i)
  {
    _PushString((const byte*)value[i].c_str(), value[i].size(), true);
  }
  IncrementParamsCount();
  Preallocate(sizeof(nstl::vector<nstl::string>));
}

xstring* ArgReader::_PopStringContent(void* buffer, uint size, bool& result, bool isWide)
{
  uint length = size+1;
  if (isWide)
  {
#if defined( NV_WIN_PLATFORM )
    length *= sizeof(wchar_t);
#elif defined( NV_LINUX_PLATFORM )
    length *= 2;
#endif
  }
  const byte* value = PopData(length, result);
  if (result)
  {
#if defined( NV_WIN_PLATFORM )
    return _CreateString(buffer, value, size, isWide);
#elif defined( NV_LINUX_PLATFORM )
    nstl::wstring * wstr = new nstl::wstring;
    wstr -> resize( size );
    const UInt16T * p = ( const UInt16T * ) ( value );
    std::copy( p, p + size, wstr -> begin() );
    heapStrings.push_back( wstr );
    return (xstring*) wstr;
#endif
  }
  return _CreateString(buffer, emptyString, 0, isWide);
}

const byte* ArgReader::_PopString(bool& result, bool isWide) 
{
  ushort length = PopRaw<UInt16T>(result);
  if (result && length > 0)
  {
    return PopData((length+1)*(isWide?sizeof(wchar_t):sizeof(char)), result);
  }
  return 0;
}

const byte* ArgReader::PopString(bool& result, bool isWide) 
{
  ParamInfo param = PopTypeCode(result); 
  if (result && rpc::String == param.code)
  {
    return _PopString(result, isWide);
  }
  result = false;
  return 0;
}

void ArgReader::Revert(bool& result)
{
  bool isMember = Pop<bool>(result);
  if (result)
  {
    bool isDelta = PopRaw<bool>(result);
    isDelta;
    if (result)
    {
      ParamInfo param = PopTypeCode(result); 
      if (isMember)
      {
        if (rpc::RawStruct == param.code)
        {
          const ContainerOperationInfo* memory = (const ContainerOperationInfo*)PopSimpleStructRaw(result, sizeof(ContainerOperationInfo));
          memory;
          param = PopTypeCode(result);
        }
      }
      if (result && rpc::SPtr == param.code)
      {
        byte* memory = const_cast<byte*>(PopSimpleStructRaw(result));
        if (result)
        {
          IObjHolder* ptr = (IObjHolder*)memory;
          ptr->~IObjHolder();
        }
      }
    }
  }
}

void ArgReader::_PopVectorOfSimpleStructs(byte* destData, uint elementSize, uint elementsCount, bool& result)
{
  uint dataBytes = GetVectorContentSize(elementsCount, elementSize);
  if (dataBytes > 0)
  {
    const byte* start = PopData(dataBytes, result);
    if (result)
    {
      memcpy(destData, start, dataBytes);
      return;
    }
  } 
  result = false;
}

void ArgReader::Copy(byte* dst, uint size, bool& result)
{
  if (length >= size)
  {
    crt::memcpy(dst, size, rdata, size);
    _Advance(size);
  } else
  {
    result = false;
  }
}

ParamInfo ArgReader::PopTypeCode(bool& result) 
{
  ParamInfo value = { PopRaw<byte>(result)};
  if (result)
  {
    return value;
  }
  value.code = rpc::ParamsCount; // invalid type
  return value;
}

const byte* ArgReader::PopData(uint size, bool& result) 
{
  if (length >= size)
  {
    const byte* value = rdata;
    _Advance(size);
    return value;
  }
  else
  {
    result = false;
    return 0;
  }
}

void ArgReader::PopData(void* dst, uint size, bool& result) 
{
  if (length >= size)
  {
    crt::memcpy(dst, size, rdata, size);
    _Advance(size);
  } 
  else
  {
    result = false;
  }
}

bool ArgReader::Assign( IRemoteEntity*& member, IRemoteEntityFactory* factory ) 
{
  bool result = true;
  IRemoteEntity* entity = _PopRemoteEntity( result, factory );
  if (result)
  {
    member = entity;
  }
  return result;
}

bool ArgReader::Assign( nstl::vector<IRemoteEntity*>& member, IRemoteEntityFactory* factory  )
{
  bool result = true;
  bool isDelta = PopRaw<bool>(result);
  if (isDelta)
  {
    const ContainerOperationInfo* info = PopSimpleStructT<const ContainerOperationInfo>(result);
    if (!result)
    {
      return false;
    }
    switch (info->operationType) 
    {
    case rpc::voAppend:
      {
        IRemoteEntity*& m = member.push_back();
        result = Assign( m, factory );
      }
      break;
    case rpc::voSet:
      {
        byte* memory = const_cast<byte*>(PopSimpleStructRaw(result));
        memory;
        IRemoteEntity* entity = _PopRemoteEntity( result, factory );
        if (result)
        {
          member[info->index] = entity;
        }
      }
      break;
    case rpc::voEraseByIndex:
      {   
        member.eraseByIndex(info->index); 
      }
      break;
    default:
      result = false;
    }
  } else
  {
    ParamInfo param = PopTypeCode(result); 
    if (result && (rpc::VectorOfStructs == param.code))
    {
      int size = PopRaw<Int32T>(result);
      if (result)
      {
        member.resize(size);
        for (int i=0;result && i<size;++i)
        {
          member[i] = _PopRemoteEntity( result, factory );
        }
      }
    }
  }
  return result;
}
ArgWriter& MethodCall::Prepare( uint methodId )
{
  info.header.Prepare(methodId); 
  args.Reset(&info.data);
  return args;
}

void MethodCallInfo::SerializeCall(Stream& s, const nstl::vector<byte>* setData)
{
  header.Optimize();
  s.Seek(0, SEEKORIGIN_BEGIN);
  UInt32T crc = static_cast< UInt32T >( classCrc );
  s.Write( &crc, sizeof( crc ) );

  if (setData && setData->size() > 0)
  {
    header.isDataMembersIncluded = true;
  }
  s.Write(&header.data, sizeof(header.data));             // 2
  UInt16T tid = static_cast< UInt16T >( header.transactionId );
  s.Write( &tid, sizeof( tid ) );           // 2
  switch (header.dataSizeFlag)    //2-4 depends of value
  {
  case 0: { UInt16T value = static_cast< UInt16T >( header.dataSize & 0xFFFF ); s.Write( &value, sizeof( UInt16T ) ); } break;
  case 1: { UInt32T dsize = static_cast< UInt32T >( header.dataSize ); s.Write( &dsize, sizeof( UInt32T ) ); } break;
  }
  switch (header.entitySizeFlag)                     // 1-4 depends of value
  {
  case 0: { byte value = byte(header.entityId); s.Write(&value, sizeof(byte)); } break;
  case 1: { UInt16T value = UInt16T(header.entityId); s.Write(&value, sizeof(UInt16T)); } break;
  case 2: { s.Write((byte*)(&header.entityId), sizeof(UInt32T)-1); } break;  // TODO: support endianness 
  case 3: { UInt32T eid = static_cast< UInt32T >( header.entityId ); s.Write( &eid, sizeof( UInt32T ) ); } break;
  }
  switch (header.preAllocatedSizeFlag)
  {
  case 1: { byte value = byte(header.preAllocatedSize); s.Write(&value, sizeof(byte)); } break;
  case 2:
  {
    UInt16T psize = static_cast< UInt16T >( header.preAllocatedSize );
    s.Write( &psize, sizeof( UInt16T ) );
  } break;
  }
                                                          // total 8-14 bytes for header 
  if (header.isDataMembersIncluded)
  {
    UInt32T dataSize = setData?setData->size():0;
    s.Write(&dataSize, sizeof(UInt32T));
    byte dataFlags = header.dataFlags;
    s.Write(&dataFlags, sizeof(byte));
    if (setData)
    {
      s.Write(&setData->operator[](0), setData->size());
    }
  }
  if (header.dataSize > 0)
  {
    s.Write(&data[0], data.size());
  }
}

const char* MethodCall::GetReason(FailReason reason)
{
  switch(reason)
  {
  case rpc::MethodCall::OK : return "OK";
  case rpc::MethodCall::FailedEntitySize: return "EntitySize";
  case rpc::MethodCall::FailedEntityHeader: return "EntityHeader";
  case rpc::MethodCall::FailedTransactionId: return "TransactionId";
  case rpc::MethodCall::FailedRemainingDataSize: return "RemainingDataSize";
  case rpc::MethodCall::FailedDataSize: return "DataSize";
  case rpc::MethodCall::FailedPreallocatedSize: return "PreallocatedSize";
  }                                                         
  return "Unknown";
}

const byte* MethodCall::DeserializeCall(ArgReader& r, MethodCallHeader& header, FailReason& reason)
{
  NI_PROFILE_HEAVY_FUNCTION;

  header.Reset();
  reason = rpc::MethodCall::OK;
  bool result = true;
  UInt32T classCrc = r.PopRaw<UInt32T>(result);
  classCrc;
  if (!result)
  {
    reason = rpc::MethodCall::FailedEntityHeader;
    return 0;
  }

  r.PopData(header.data, sizeof(header.data), result);
  if (result)
  {
    header.transactionId = r.PopRaw</*TransactionId*/UInt16T>(result);
    if (result)
    {
      switch (header.dataSizeFlag)
      {
      case 0: header.dataSize = r.PopRaw<UInt16T>(result); break;
      case 1: header.dataSize = r.PopRaw<UInt32T>(result); break;
      }
      if (result)
      {
        switch (header.entitySizeFlag)
        {
        case 0: header.entityId = r.PopRaw<byte>(result); break;
        case 1: header.entityId = r.PopRaw<UInt16T>(result); break;
        case 2: header.entityId = 0; r.Copy((byte*)(&header.entityId), sizeof(UInt32T)-1, result); break;
        case 3: header.entityId = r.PopRaw</*EntityId*/UInt32T>(result); break;      
        }
        if (result)
        {
          switch (header.preAllocatedSizeFlag)
          {
          case 0: header.preAllocatedSize = 0; break;
          case 1: header.preAllocatedSize = r.PopRaw<byte>(result); break;
          case 2: header.preAllocatedSize = r.PopRaw<UInt16T>(result); break;
          }
          if (result)
          {
            if (header.isDataMembersIncluded)
            {
              header.membersSize = r.PopRaw<UInt32T>(result);
              header.dataFlags = r.PopRaw<byte>(result);
            } 
            else
            {
              header.membersSize = 0;
            }
            if (r.GetRemainingSize()-header.membersSize == header.dataSize)
            {
              return r.GetCurrentPtr();
            } 
            else
            {
              reason = rpc::MethodCall::FailedRemainingDataSize;
            }
          } 
          else
          {
            reason = rpc::MethodCall::FailedPreallocatedSize;
          }
        } 
        else
        {
          reason = rpc::MethodCall::FailedEntitySize;
        }
      }
      else
      {
        reason = rpc::MethodCall::FailedDataSize;
      }
    }
    else
    {
      reason = rpc::MethodCall::FailedTransactionId;
    }
  } else
  {
    reason = rpc::MethodCall::FailedEntityHeader;
  }
  return 0;
}

void MethodCallInfo::Apply()
{
  header.paramsCount = writer->GetParamsCount();
  header.preAllocatedSize = writer->GetPreAllocatedSize();
  header.dataSize = writer->size();
}

const int MaxPacketSize = 64000;

uint MethodCallInfo::Go(IPacketPipe * pipe, Stream& stream, const nstl::vector<byte>* setData, bool force)
{
  SerializeCall(stream, setData);
  const char* buffer = stream.GetBuffer();
  uint size = stream.GetPosition();
  NI_VERIFY(size <= MaxPacketSize, "Packet size too large", return 0);
  pipe->Send( (const byte*)buffer, size, force );
  rpcMethodCallsSent.AddValue( 1 );
  return size;
}      

ILocalEntity* ArgReader::PopLocalEntity(bool& result)
{
  ParamInfo param = PopTypeCode(result); 
  if (result && entities && rpc::RemoteEntity == param.code)
  {
    const RemoteEntityInfo& info = PopStruct<RemoteEntityInfo>(result, 0);
    if (result)
    {
      const char* nodeName = Pop<const char*>(result);
      nodeName;
      if (result)
      {
        int lnodeCount = PopRaw<Int16T>(result);
        if (lnodeCount > 0)
        {
          NI_ASSERT(lnodeCount <= 1, "Pointers to replicated objects currently are not supported");
          const GUID& lnodeId = PopStruct<GUID>(result, 0);
          lnodeId;
        }
        const GUID& rnodeId = PopStruct<GUID>(result, 0);
        rnodeId;
        if (result)
        {
          PopRaw<Int32T>(result);
        }
      }
      if (result && !info.IsNull())
      {
        rpc::LocalEntityInfo* linfo = entities->GetEntityInfo(info.entityId);
        if (linfo)
        {
          if (linfo->IsMatched(info.typeInfo.classId, info.typeInfo.classCrc))
          {
            linfo->SetParent(GetLastLocalEntity());
            createdLocalEntities.push_back(linfo);
            return linfo->Get();
          } else 
          {
            result = false;
          }
        } else
        {
          result = false;
        }
      }
    }
  }
  return 0;
}


} // rpc

