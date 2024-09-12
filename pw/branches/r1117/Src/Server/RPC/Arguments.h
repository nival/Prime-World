#pragma once

#include <System/ChunklessSaver.h>
#include <System/MetaProg.h>
#include <System/fixedvector.h>

#include "Packets.h"
#include "ReplicationTypes.h"
#include "Types.h"
#include "System/InlineProfiler.h"
#include "ArgWriter.h"


namespace rpc
{
  class LocalEntities;

  inline int align(int size, int align) { return (((size) + ((align) - 1)) & ~((align) - 1)); }

  class xvector : public nstl::vector<byte>
  {
  public:
    void Set(byte* start, int elementsCount)
    {
      this->_M_set(start, start+elementsCount, start+elementsCount);
    }
  };

  class xstring : public nstl::string
  {
  public:
    xstring(const byte* value, int length, bool isWide):nstl::string( nstl::string::eNotAllocateOnConstruct )
    {
      Set(const_cast<byte*>(value), length, isWide);
    }
    ~xstring()
    {
      Set(0, 0, false);
    }
  private:
    uint getItemSize( bool isWide ) const
    {
#if defined( NV_WIN_PLATFORM )
      return isWide?sizeof(wchar_t):sizeof(char);
#elif defined( NV_LINUX_PLATFORM )
      return isWide?2:sizeof(char);
#endif
    }
    void Set(byte* value, int length, bool isWide)
    {
      this->_M_start = (char*)value;
      if (value)
      {
        uint itemSize = getItemSize( isWide );
        this->_M_finish = (char*)(value+length*itemSize);
        this->_M_end_of_storage = _M_finish+itemSize;
      }
    }
  };
  struct ParamInfo 
  {
    byte code;
  };

  uint GetVectorContentSize(uint elementsCount, uint elementSize);

  class ArgReader
  {
    const byte* rdata;
    uint length;
  public:
    ArgReader(ILocalEntities* _entities, rpc::IPacketPipe* _pipe, bool _isRemote=false):
    entities(_entities),
    entityMap(0),
    pipe(_pipe),
    isRemote(_isRemote)
    {
      Reset(0, 0, 0);
    }

    ~ArgReader()
    {
      Reset(0, 0, 0);
    }

    void SetEntityMap(rpc::IEntityMap* _entityMap) { entityMap = _entityMap; }

    const byte* GetCurrentPtr() const 
    {
      return rdata;
    }

    void Preallocate(int preAllocatedSize) 
    {
      for (int i=0;i<strings.size();++i)
      {
        strings[i]->~xstring();
      }
      strings.clear();
#if defined( NV_LINUX_PLATFORM )
      for (int i=0;i<heapStrings.size();++i)
      {
        delete heapStrings[i];
      }
      heapStrings.clear();
#endif
      for (int i=0;i<vectors.size();++i)
      {
        vectors[i]->Set(0, 0);
        vectors[i]->~xvector();
      }
      vectors.clear();

      for (int i=0;i<datas.size();++i)
      {
        datas[i]->~Data();
      }
      bytes.reserve(preAllocatedSize);
      bytes.resize(0);
      datas.clear();
    }

    void Reset(const byte* _rdata, uint _length, uint preAllocatedSize) 
    {
      NI_PROFILE_HEAVY_FUNCTION;

      Preallocate(preAllocatedSize);
      rdata = _rdata;
      length = _length;
      rparents.clear();
      lparents.clear();
      createdLocalEntities.clear();
      readEntities.clear();
    }

    ParamInfo PopTypeCode(bool& result);
 
    template <typename T>
    T PopRaw(bool& result) 
    {
      if (length >= sizeof(T))
      {
        T value = *(T*)rdata;
        _Advance(sizeof(T));
        return value;
      } else
      {
        result = false;
        return T();
      }
    }

    void Copy(byte* dst, uint size, bool& result);

    int GetRemainingSize() const 
    {
      return length;
    }

    template <typename T>
    T PopType(bool& result) 
    {
      ParamInfo param = PopTypeCode(result); 
      if (result)
      {
        if (rpc::GetTypeT<T>::type == param.code)
        {
          return PopRaw<T>(result);
        }
        result = false;
      }
      return T();
    }

    const byte* PopString(bool& result, bool isWide);
    const byte* _PopString(bool& result, bool isWide);

    const byte* PopData(uint size, bool& result);
    void PopData(void* dst, uint size, bool& result);

    const byte* PopSimpleStructRaw(bool& result, int size=-1, int* structSize=0);
    void Revert(bool& result);

    template <typename T>
    bool Assign(T& member) 
    {
      bool result = true;
      const T* data = PopSimpleStructT<const T>(result);
      if (result)
      {
        if (data)
        {
          member = *data;
        } else
        {
          result = false;
        }
      } 
      return result;
    }

    bool Assign(const void*& member, int size) 
    {
      bool result = true;
      const void* data = PopSimpleStruct(result, size);
      if (result)
      {
        if (data)
        {
          member = data;
        } else
        {
          result = false;
        }
      } 
      return result;
    }

    ILocalEntity* PopLocalEntity(bool& result);

    rpc::Data* _PopSerializedStruct(bool& result, uint size, DataFactory* factory=0);
    rpc::Data* _PopRawSerializedData(bool& result, int size, DataFactory* factory=0, int dataStructSize = sizeof(rpc::Data));
    void _PopSimpleStructToMemory(bool& result, void* memory, uint size);

    template <typename T>
    bool Assign(nstl::vector<T>& member) 
    {
      bool result = true;
      bool isSerializedStruct = SUPERSUBCLASS( rpc::Data, T );
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
            if (!isSerializedStruct)
            {
              T& value = member.push_back();
              _PopSimpleStructToMemory(result, &value, sizeof(T));
            } else
            {
              rpc::Data* data = _PopSerializedStruct(result, sizeof(T));
              member.push_back(*((T*)data));
            }
          }
          break;
        case rpc::voSet:
          {
            T& value = member[info->index];
            if (!isSerializedStruct)
            {
              _PopSimpleStructToMemory(result, &value, sizeof(T));
            } else
            {
              rpc::Data* data = _PopSerializedStruct(result, sizeof(T));
              value = *((T*)data);
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
        if (result && (rpc::VectorOfScalars == param.code || rpc::VectorOfStructs == param.code))
        {
          _PopVectorWithoutTypeCode(member, sizeof(T), (rpc::VectorOfStructs == param.code), result) ; 
        }
      }
      return result;
    }

    template <typename T>
    void _PopVectorWithoutTypeCode(nstl::vector<T>& member, int expectedElementSize, bool isSerializedStruct, bool& result)
    {
      uint elementSize = PopRaw<uint>(result); 
      if (result)
      {
        if (expectedElementSize == -1 ||  uint(expectedElementSize) == elementSize || isSerializedStruct)
        {
          uint elementsCount = PopRaw<uint>(result); 
          if (result)
          {
            if (elementsCount > 0) 
            { 
              if (GetVectorContentSize(elementsCount, sizeof(T)) > 0)
              {
                member.resize(elementsCount); 
                if (isSerializedStruct)
                {
                  xvector* _data = _PopVectorOfSerializedStructs(elementSize, elementsCount, result);
                  if (result)
                  {
                    nstl::vector<T>* data = (nstl::vector<T>*)_data;
                    for (int i=0;i<member.size();++i)
                    {
                      member[i] = data->operator[](i);
                    }
                  }
                } else
                {
                  _PopVectorOfSimpleStructs((byte*)&member[0], elementSize, elementsCount, result);
                }
              }
              else
              {
                result = false;
                return;
              }
            } else
            {
              if (isSerializedStruct)
              {
                PopRaw<uint>(result); 
              }
            }
          }
        }
      }
    }

    void _PopVectorOfSimpleStructs(byte* destData, uint elementSize, uint elementsCount, bool& result);

    template <typename T>
    bool Rollback(T& member) 
    {
      return Assign(member);
    }

    template <typename T>
    bool Rollback(StrongMT<T>& member)
    {
      bool result = true;
      bool isDelta = PopRaw<bool>(result);
      isDelta;
      ParamInfo type = PopTypeCode(result);
      if (result && type.code == rpc::SPtr)
      {
        byte* memory = const_cast<byte*>(PopSimpleStructRaw(result));
        if (result)
        {
          CObjHolder<T>* ptr = (CObjHolder<T>*)memory;
          member = ptr->value;
          ((IObjHolder*)memory)->~IObjHolder();
        } else
        {
          member = 0;
        }
      }
      return result;
    }

    template <typename T>
    bool Rollback(rpc::vector<T>& member) 
    {
      bool result = true;
      bool isSerializedStruct = SUPERSUBCLASS( rpc::Data, T );
      bool isDelta = PopRaw<bool>(result);
      isDelta;
      const ContainerOperationInfo* info = PopSimpleStructT<const ContainerOperationInfo>(result);
      if (!result)
      {
        return false;
      }

      switch (info->operationType) 
      {
      case rpc::voAppend:
        {
          member.pop_back();
        }
        break;
      case rpc::voSet:
        {
          T& value = member[info->index];
          if (!isSerializedStruct)
          {
            _PopSimpleStructToMemory(result, &value, sizeof(T));
          } else
          {
            rpc::Data* data = _PopSerializedStruct(result, sizeof(T));
            value = *((T*)data);
          }
        }
        break;
      case rpc::voEraseByIndex:
        {
          member.insert(info->index);
          T& value = member[info->index];
          if (!isSerializedStruct)
          {
            _PopSimpleStructToMemory(result, &value, sizeof(T));
          } else
          {
            rpc::Data* data = _PopSerializedStruct(result, sizeof(T));
            value = *((T*)data);
          }
        }
        break;
      default:
        result = false;
      }
      return result;
    }

    bool Assign(nstl::string& member) {  return AssignStr<nstl::string, char, false>(member); }
    bool Assign(nstl::wstring& member) {  return AssignStr<nstl::wstring, wchar_t, true>(member); }
    bool Rollback(rpc::rpcstring& member) {  return AssignStr<rpc::rpcstring, char, false>(member); }
    bool Rollback(rpc::rpcwstring& member) {  return AssignStr<rpc::rpcwstring, wchar_t, true>(member); }

    template <typename T0, typename T1, bool isWide>
    bool AssignStr(T0& member) 
    {
      bool result = true;
      bool isDelta = PopRaw<bool>(result);
      isDelta;
      const ContainerOperationInfo* info = PopSimpleStructT<const ContainerOperationInfo>(result);
      switch (info->operationType) 
      {
      case rpc::soAssign:
        {
          const T1* value = (const T1*)PopString(result, isWide);
          if (result)
          {
            if (value)
            {
              member.assign(value);
            } else
            {
              member.clear();
            }
          }
        }
        break;
      case rpc::soSetByIndex:
        {
          member[info->index] = PopType<T1>(result);
        }
        break;
      default:
        result = false;
        break;
      }
      return result;
    }

    template <typename T>
    bool Assign(StrongMT<T>& member) 
    {
      bool result = true;
      if (!isRemote)
      {
        ILocalEntity* entity = PopLocalEntity(result);
        if (result)
        {
          member = entity?entity->Get<T>():0;
        }
      } else
      {
        IRemoteEntity* entity = _PopRemoteEntity(result);
        if (result)
        {
          member = dynamic_cast<T*>(entity);
        }
      }
      return result;
    }

    bool Assign( IRemoteEntity*& member, IRemoteEntityFactory* factory=0 );

    template <typename T>
    bool Assign(nstl::vector<StrongMT<T> >& member) 
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
            StrongMT<T>& m = member.push_back();
            result = Assign(m);
          }
          break;
        case rpc::voSet:
          {
            result = Assign(member[info->index]);
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
          int size = PopRaw<int>(result);
          if (result)
          {
            member.resize(size);
            for (int i=0;result && i<size;++i)
            {
              rpc::IRemoteEntity* entity = _PopRemoteEntity(result);
              member[i] = (T*)entity;
            }
          }
        }
      }
      return result; 
    }
    bool Assign( nstl::vector<IRemoteEntity*>& member, IRemoteEntityFactory* factory=0 );
    template <typename T>
    bool Rollback(rpc::vector<StrongMT<T> >& member) { return false; } 

    rpc::IRemoteEntity* PopRawRemoteEntity(bool& result, IRemoteEntityFactory* factory=0);

    template <typename T> 
    T& PopStruct(bool& result, DataFactory* factory=0)
    {
      bool isSerializedStruct = SUPERSUBCLASS( rpc::Data, T );
      if (!isSerializedStruct)
      {
        return *((T*)PopSimpleStruct(result, sizeof(T)));
      } else
      {
        return *((T*)PopSerializedStruct(result, factory)); 
      }
    }

    const byte* PopRawStruct(bool& result)
    {
      return PopSimpleStruct(result, -1);
    }

    rpc::Data* PopRawSerializedData(bool& result, DataFactory* factory, int dataStructSize);
    rpc::Data* Deserialize(uint structId, byte* source, uint sourceSize, void* target, DataFactory* factory, bool& result);
    void* _AllocateBuffer(int size);
    rpc::IRemoteEntity* _PopRemoteEntity( bool& result, IRemoteEntityFactory* factory=0 );

    xvector* _PopVector(int expectedElementSize, bool& result, DataFactory* factory);
    xvector* _PopVectorOfSerializedStructs(uint elementSize, uint elementsCount, bool& result, DataFactory* factory=0);

    bool DeserializeVector( void* start, uint elementsCount, uint structId, DataFactory* factory, uint elementSize);
    xvector* _PopVectorOfSimpleStructs(uint elementSize, uint elementsCount, bool& result);
    xvector* _AllocateVector();
    xvector* _PopVectorWithoutTypeCode(int expectedElementSize, bool& result, DataFactory* factory);
    xvector* _PopVectorOfAnyStrings( bool& result );
    const nstl::string& PopEmptyString();
    const nstl::wstring& PopEmptyWideString();
    xstring* _PopStringContent(void* buffer, uint length, bool& result, bool isWide);
    xstring* _CreateString(void* buffer, const byte* value, uint length, bool isWide);
    xstring* _PopXString(void* buffer, bool& result);
    void* _PopFixedVector(bool& result, uint expectedCapacity=0, int expectedSize=-1);
    void* _PopFixedVectorWithoutTypeCode(bool& result, uint expectedCapacity=0, int expectedSize=-1);
    const nstl::vector<rpc::MemoryBlock>* PopVectorOfMemoryBlocksRaw(bool &result);

    template <typename T>
    T Pop(bool& result)
    {
      return PopType<T>(result);
    }

    bool UpdateRemoteEntity(rpc::IRemoteEntity* entity, uint classCrc, uint dataSize);
    bool UpdateLocalEntity(rpc::LocalEntityInfo& info, uint dataSize);
    const byte* PopSimpleStruct(bool& result, int size=-1);
    const rpc::MemoryBlock* PopMemoryBlockRaw(bool& result);
    void _PopMemoryBlockRaw( bool& result, rpc::MemoryBlock* block );

    IEntityMap* GetIEntityMap()
    {
      return entityMap;
    }
    rpc::IRemoteEntity* GetLastRemoteEntity() { return rparents.size()>0?*(rparents.end()-1):0; }
    rpc::ILocalEntity* GetLastLocalEntity() { return lparents.size()>0?*(lparents.end()-1):0; }

    const nstl::vector<rpc::LocalEntityInfo*>& GetCreatedLocalEntities() const { return createdLocalEntities; }

  private:
    template <typename T>
    bool _Assign(T& member) 
    {
      bool result = true;
      member = PopType<T>(result);
      return result;
    }

    rpc::Data* PopSerializedStruct(bool& result, DataFactory* factory);


    void _Advance(uint _step)
    {
      rdata += _step;
      length -= _step;
    }


    template <typename T>
    T* PopSimpleStructT(bool& result)
    {
      return (T*)PopSimpleStruct(result, sizeof(T));
    }
    ILocalEntities* entities;
    IEntityMap* entityMap;
    StrongMT<IPacketPipe> pipe;
    nstl::vector<rpc::Data*> datas;  
    nstl::vector<byte> bytes;
    nstl::vector<xstring*> strings;
#if defined( NV_LINUX_PLATFORM )
    nstl::vector<nstl::wstring*> heapStrings;
#endif
    nstl::vector<xvector*> vectors;  
    bool isRemote;
    nstl::vector<rpc::IRemoteEntity*> rparents;
    nstl::vector<rpc::ILocalEntity*> lparents;
    nstl::vector<rpc::LocalEntityInfo*> createdLocalEntities;
    nstl::vector<StrongMT<rpc::IRemoteEntity> > readEntities;
  };
  

  template <> inline bool ArgReader::Assign(int& member) { return _Assign<int>(member);}
  template <> inline bool ArgReader::Assign(uint& member) { return _Assign<uint>(member);}
  template <> inline bool ArgReader::Assign(double& member) { return _Assign<double>(member); }
  template <> inline bool ArgReader::Assign(float& member) { return _Assign<float>(member); }
  template <> inline bool ArgReader::Assign(bool& member) { return _Assign<bool>(member);}
  template <> inline bool ArgReader::Assign(short& member) { return _Assign<short>(member);}
  template <> inline bool ArgReader::Assign(unsigned short& member) { return _Assign<unsigned short>(member);}
  template <> inline bool ArgReader::Assign(byte& member) { return _Assign<byte>(member); }
  template <> inline bool ArgReader::Assign(char& member) { return _Assign<char>(member); }
  template <> inline bool ArgReader::Assign(long long& member) { return _Assign<long long>(member); }
  template <> inline bool ArgReader::Assign(unsigned long long& member) { return _Assign<unsigned long long>(member); }
  template <> inline bool ArgReader::Assign(unsigned long& member) { return _Assign<unsigned long>(member); }
  template <> inline bool ArgReader::Assign(long& member) { return _Assign<long>(member); }
  template <> inline bool ArgReader::Assign(wchar_t& member) { return _Assign<wchar_t>(member); }


  template <> const char* ArgReader::Pop<const char*>(bool& result);
  template <> const nstl::string& ArgReader::Pop<const nstl::string&>(bool& result);
  template <> const char* ArgReader::PopRaw<const char*>(bool& result);
  template <> const nstl::string& ArgReader::PopRaw<const nstl::string&>(bool& result);
  template <> const nstl::wstring& ArgReader::Pop<const nstl::wstring&>(bool& result);
  template <> const nstl::wstring& ArgReader::PopRaw<const nstl::wstring&>(bool& result);


  struct CodeInfo
  {
    uint code;
    uint size;
  };

  struct PtrInfo
  {
    char* ptr;
    int position;
  };

  struct SerializableStructInfo 
  {
    int structId;
    int instanceSize;
    int bufferSize;
    const byte* bufferStart;
    int stackOffset;
  };

  class Arguments
  {
  public:
    Arguments(IEntityMap* _entityMap, rpc::IPacketPipe * _pipe, ILocalEntities* entities):
    reader(entities, _pipe, true)
    {
      reader.SetEntityMap(_entityMap);
    }

    ~Arguments()
    {
      Reset(0, 0, 0);
    }

    void Reset(const byte* _data, uint preAllocatedSize, uint paramsSize);

    const byte* PopData(short length, bool& result) { return reader.PopData(length, result); }

    template <typename T> 
    T& PopStruct(bool& result, DataFactory* factory=0) { return reader.PopStruct<T>(result, factory); }
    rpc::Data* PopRawSerializedData(bool& result, DataFactory* factory, int dataStructSize = sizeof(rpc::Data) ) { return reader.PopRawSerializedData(result, factory, dataStructSize); }

    template <typename T>
    const nstl::vector<T>& PopVector(bool& result, DataFactory* factory=0)
    {
      if (SUPERSUBCLASS( rpc::Data, T ))
      {
        NI_ASSERT(factory, "Factory should be defined for serialized struct");
      }
      return *((nstl::vector<T>*)reader._PopVector(sizeof(T), result, factory));
    }

    template <typename T>
    const nstl::vector<T>& PopVectorWithoutTypeCode(bool& result, DataFactory* factory)
    {
      return *((nstl::vector<T>*)reader._PopVectorWithoutTypeCode(-1, result, factory));
    }

    template <typename T>
    const nstl::vector<T>& PopVectorOfStrings(bool& result) { return *((nstl::vector<T>*)reader._PopVectorOfAnyStrings(result)); }

    template <typename T, uint capacity>
    const FixedVector<T, capacity>& PopFixedVector(bool& result)
    {
      return *(FixedVector<T, capacity>*)reader._PopFixedVector(result, capacity, sizeof(T));
    }

    template <typename T>
    T Pop(bool& result)
    {
      return reader.Pop<T>(result);
    }

    ArgReader& GetReader() { return reader; }
    ParamInfo PopTypeCode(bool& result) 
    {
      return reader.PopTypeCode(result); 
    }
    template <typename T>
    T PopRaw(bool& result)
    {
      return reader.PopRaw<T>(result);
    }

    void* _PopFixedVectorWithoutTypeCode(bool& result, uint expectedCapacity=0, int expectedSize=-1) { return reader._PopFixedVectorWithoutTypeCode(result, expectedCapacity, expectedSize); }
    const byte* PopSimpleStruct(int size, bool& result)
    {
      return reader.PopSimpleStruct(result, size);
    }

    const MemoryBlock* PopMemoryBlockRaw(bool& result)
    {
      return reader.PopMemoryBlockRaw(result);
    }

    const nstl::vector<rpc::MemoryBlock>* PopVectorOfMemoryBlocksRaw(bool &result)
    {
      return reader.PopVectorOfMemoryBlocksRaw(result);
    }

    const byte* PopRawStruct(bool& result, int* structSize=0)
    {
      return reader.PopSimpleStructRaw(result, -1, structSize);
    }

    rpc::IRemoteEntity* PopRawEntity(bool& result, IRemoteEntityFactory* factory=0) { return reader.PopRawRemoteEntity(result, factory); }

    template <typename T>
    T* PopEntity(bool& result)
    {
      return (T*)reader._PopRemoteEntity(result);
    }

    IEntityMap* GetEntityMap()
    {
      return reader.GetIEntityMap();
    }
  private:
    ArgReader reader;
  };

  inline int GetStringSize(bool isWide) { return isWide?sizeof(nstl::wstring):sizeof(nstl::string); }

} // rpc
