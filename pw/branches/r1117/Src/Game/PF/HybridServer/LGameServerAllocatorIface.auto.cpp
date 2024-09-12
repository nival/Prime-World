#include "stdafx.h"
#include "LGameServerAllocatorIface.auto.h"

#pragma warning( push )
#pragma warning( disable : 4065 )

namespace HybridServer
{




    bool LIGameServerAllocatorNotify::vcall( byte method_id, rpc::MethodCall& call, rpc::MethodCallStack& stack )
    {
        bool popResult = true;
        switch ( method_id )
        {
			case 0: { NI_PROFILE_BLOCK("HybridServer::IGameServerAllocatorNotify::AllocNotify/0");rpc::VCall( stack, localObject.Get(), &HybridServer::IGameServerAllocatorNotify::AllocNotify, popResult); } break;
			case 1: { NI_PROFILE_BLOCK("HybridServer::IGameServerAllocatorNotify::FreeNotify/1");rpc::VCall( stack, localObject.Get(), &HybridServer::IGameServerAllocatorNotify::FreeNotify, popResult); } break;

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
rpc::ILocalEntity* CreateLocalEntity(HybridServer::IGameServerAllocatorNotify* api, rpc::IEntityMap* entityMap)
{
  return new HybridServer::LIGameServerAllocatorNotify(api, entityMap);
}

} // rpc

#pragma warning( pop )

NI_DEFINE_REFCOUNT( HybridServer::LIGameServerAllocatorNotify )


#pragma warning( push )
#pragma warning( disable : 4065 )

namespace HybridServer
{




    bool LIGameServerAllocator::vcall( byte method_id, rpc::MethodCall& call, rpc::MethodCallStack& stack )
    {
        bool popResult = true;
        switch ( method_id )
        {
			case 0: { NI_PROFILE_BLOCK("HybridServer::IGameServerAllocator::AllocateServer/0");
			{
				uint result = rpc::VCall( stack, localObject.Get(), &HybridServer::IGameServerAllocator::AllocateServer, popResult); 
				call.Prepare(0).PushByValue(result);
			}
			} break;

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
rpc::ILocalEntity* CreateLocalEntity(HybridServer::IGameServerAllocator* api, rpc::IEntityMap* entityMap)
{
  return new HybridServer::LIGameServerAllocator(api, entityMap);
}

} // rpc

#pragma warning( pop )

NI_DEFINE_REFCOUNT( HybridServer::LIGameServerAllocator )


