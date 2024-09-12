#pragma once

#include "RpcGate.h"

///////////////////////////////////////////////////////////////////////////////
// BOOST_CURRENT_FUNCTION Используется для получения максимально близкой по 
// формату сигнатуры функции на как MSVC так и на GCC
/////////////////////////////////////////////////////////////////////////////// 
#include <System/current_function.hpp>

namespace rpc
{

enum IdType
{
  OriginalType,
  RemoteType,
  GeneratedType,
  BaseRemoteType,
};

uint _GetId(const char* className, IdType idType);


template<class T>
inline const char *GetTypeIdName( Meta::Type2Type<T> )
{
  return T::GetRawRpcId();
}

template <typename T> 
uint GetId(T* value, IdType _idType=OriginalType) 
{
  IdType idType;
  if (_idType != BaseRemoteType)
  {
    idType = (SUPERSUBCLASS( rpc::IRemoteEntity, T ))?RemoteType:_idType;
  } else
  {
    idType = OriginalType;    
  }
  
  //GetTypeIdName используется вместо typeid(T).name() в связи с тем, что в реализации msvcr90.dll
  //от Wine метод type_info::name не реализован
  return _GetId( GetTypeIdName(Meta::Type2Type<typename Meta::UnConst<T>::Result>() ), idType);
}

// Split to two calls just to resolve some dependency problems on linux
template <typename T> 
uint GetId() 
{
  return GetId<T>(0);
}

} //namespace rpc

#define NI_RPC_INFO(className, crc)  \
  static const char *GetRawRpcId() { return className; } \
  static uint ID() { return rpc::_GetId(className, rpc::GeneratedType); } \
  static const uint CRC32=crc;


#define NI_RPC_REDEFINE_ID() static const char *GetRawRpcId() { return BOOST_CURRENT_FUNCTION; }

#define NI_RPC_ID() \
  private: \
    rpc::ILocalEntity* owner; \
  public: \
    virtual uint GetClassId() const { return rpc::GetId(this); } \
    void SetOwner( rpc::ILocalEntity* _owner ) { owner = _owner; } \
    NI_RPC_REDEFINE_ID()

#define RPC_ID NI_RPC_ID
#define RPC_REDEFINE_ID NI_RPC_REDEFINE_ID
#define RPC_INFO NI_RPC_INFO
