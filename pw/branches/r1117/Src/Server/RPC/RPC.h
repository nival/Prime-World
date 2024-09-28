#pragma once
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <System/nmap.h>
#include <System/Thread.h> 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace Transport { class MessageFactory; }
namespace rpc
{
  void RegisterMessages( Transport::MessageFactory* pFactory );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define INTERFACE
#define NI_LPTR
#define NI_REMOTE 
#define REMOTE NI_REMOTE
#define LOCAL(p) p

#pragma warning( push ) 
#pragma warning( disable: 4512 ) //assignment operator could not be generated   

#include <RPC/Interfaces.h>
#include <RPC/Types.h>
#include <RPC/Packets.h>
#include <RPC/Arguments.h>
#include <RPC/ArgWriter.h>
#include <RPC/Calls.h>
#include <RPC/Base.h>
#include <RPC/ReplicationTypes.h>

namespace rpc
{
  IRemoteEntity* CreateLocalRemoteWrapper(void* instance, IBaseInterfaceMT* object, uint classId, const char* gateName=0);
  void* GetLocalPtr(const rpc::IRemoteEntity* value);
  void EnableLog(int logLevel);
  int GetReportFreq();
  int GetLogLevel();
}
template <typename P> rpc::IRemoteEntity* RemotePtr(const StrongMT<P>& value) { return rpc::CreateLocalRemoteWrapper(value.Get(), (BaseObjectMT*)value.Get(), rpc::GetId<P>()); }
template <typename T, typename P> T* RemotePtr(const StrongMT<P>& value) { return (T*)rpc::CreateLocalRemoteWrapper(value.Get(), (BaseObjectMT*)value.Get(), rpc::GetId<T>()); }
template <typename T, typename P> T* RemotePtrInOtherGate(const StrongMT<P>& value, const char* gateName) { return (T*)rpc::CreateLocalRemoteWrapper(value.Get(), (BaseObjectMT*)value.Get(), rpc::GetId<T>(), gateName); }
template <typename T, typename P, typename P0> T* RemotePtr(const StrongMT<P>& value, P0 p0) { return (T*)rpc::CreateLocalRemoteWrapper(value.Get(), (BaseObjectMT*)value.Get(), rpc::GetId<T>()); }
template <typename T, typename P, typename C> T* RemotePtr(const C* value) { StrongMT<P> temp((P*)value); return (T*)rpc::CreateLocalRemoteWrapper(temp.Get(), (BaseObjectMT*)temp.Get(), rpc::GetId<P>()); }
template <typename P, typename C> P* RemotePtr(C* value) { StrongMT<C> temp(value); return (P*)rpc::CreateLocalRemoteWrapper(temp.Get(), (BaseObjectMT*)temp.Get(), rpc::GetId<P>()); }

// LocalPtr conversion is used in Game Server tests to get back object pointer from RemotePtr
template <typename P> P* LocalPtr(const rpc::IRemoteEntity* value) { return (P*)rpc::GetLocalPtr(value); }

#pragma warning( pop )
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
