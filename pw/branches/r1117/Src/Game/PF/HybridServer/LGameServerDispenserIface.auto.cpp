#include "stdafx.h"
#include "LGameServerDispenserIface.auto.h"

#pragma warning( push )
#pragma warning( disable : 4065 )

namespace HybridServer
{


	typedef void (HybridServer::IGameServerDispenser::*TAcquireNewServer)( const Peered::SAllocationParams* _params, NI_LPTR lobby::ISessionHybridLink* _session, NI_LPTR IGameServerDispenserCallback* _cb);


    bool LIGameServerDispenser::vcall( byte method_id, rpc::MethodCall& call, rpc::MethodCallStack& stack )
    {
        bool popResult = true;
        switch ( method_id )
        {
			case 0: { NI_PROFILE_BLOCK("HybridServer::IGameServerDispenser::AcquireNewServer/0");rpc::VCall( stack, localObject.Get(), TAcquireNewServer(&HybridServer::IGameServerDispenser::AcquireNewServer), popResult); } break;

        default:
            popResult = false;
            break;
        }
        return popResult;
    }

}


namespace rpc
{
template<>
rpc::ILocalEntity* CreateLocalEntity(HybridServer::IGameServerDispenser* api, rpc::IEntityMap* entityMap)
{
  return new HybridServer::LIGameServerDispenser(api, entityMap);
}

} // rpc

#pragma warning( pop )

NI_DEFINE_REFCOUNT( HybridServer::LIGameServerDispenser )


#pragma warning( push )
#pragma warning( disable : 4065 )

namespace HybridServer
{


	typedef void (HybridServer::IGameServerDispenserCallback::*TGameServerAllocated)( Peered::RIGameServer* _clientsInterface, Peered::RIGameServerInternal* _internalInterface, const Peered::SInstanceId* _instId);


    bool LIGameServerDispenserCallback::vcall( byte method_id, rpc::MethodCall& call, rpc::MethodCallStack& stack )
    {
        bool popResult = true;
        switch ( method_id )
        {
			case 0: { NI_PROFILE_BLOCK("HybridServer::IGameServerDispenserCallback::GameServerAllocated/0");rpc::VCall( stack, localObject.Get(), TGameServerAllocated(&HybridServer::IGameServerDispenserCallback::GameServerAllocated), popResult); } break;

        default:
            popResult = false;
            break;
        }
        return popResult;
    }

}


namespace rpc
{
template<>
rpc::ILocalEntity* CreateLocalEntity(HybridServer::IGameServerDispenserCallback* api, rpc::IEntityMap* entityMap)
{
  return new HybridServer::LIGameServerDispenserCallback(api, entityMap);
}

} // rpc

#pragma warning( pop )

NI_DEFINE_REFCOUNT( HybridServer::LIGameServerDispenserCallback )


