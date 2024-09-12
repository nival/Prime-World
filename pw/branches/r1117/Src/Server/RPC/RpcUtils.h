#pragma once

#include "Interfaces.h"


namespace rpc 
{

class EntityHandler;
_interface IRemoteEntity;

struct RemoteEntityInfo_
{
  EntityHandler* handler;
  IRemoteEntity* instance;

  RemoteEntityInfo_():handler(0), instance(0) {}
  RemoteEntityInfo_(EntityHandler* _handler, IRemoteEntity* _instance):handler(_handler), instance(_instance) {}

  void Clear();

  template <typename T> T* InvokeConstructor() { 
    return (T*)InvokeSharedConstructor();
  }

  IRemoteEntity* InvokeSharedConstructor();

  template <typename T> T* Get() { 
    return (T*)instance; 
  }
};



struct EntityCreationInfo
{
  uint classId;
  uint classCrc;
  bool isShared;
  bool isQueried;
};



struct GUIDString
{
  string value;

  GUIDString(const GUID& id)
  {
    NStr::GUID2String(&value, id);
  }

  const char* GetValue() const { return value.c_str(); }
};



struct GUIDIsLess
{
  inline bool operator () ( const GUID& a, const GUID& b ) const 
  { 
    return memcmp(&a, &b, sizeof(GUID)) < 0;
  }
};



class EntityFactoriesContainer
{
public:
  typedef nstl::map<uint, void*> EntityFactoryMap;
  EntityFactoryMap& getFactoryMap() { return entityTypes; }

  template <typename T>
  T* GetFactory(uint classId) { return (T*)_GetFactory(classId); }

  template <typename T>
  void RegisterFactory(uint classId, T& factory) { _RegisterFactory(classId, &factory); }

  void UnregisterFactory(uint classId);
private:
  void _RegisterFactory(uint classId, void* factory);
  void _UnregisterFactory(uint classId);
  void* _GetFactory(uint classId);
  EntityFactoryMap entityTypes;
};


const char * GetCallFailReason( rpc::CallResult::Enum result );
void PrintData(const byte* data , int size);

} // rpc
