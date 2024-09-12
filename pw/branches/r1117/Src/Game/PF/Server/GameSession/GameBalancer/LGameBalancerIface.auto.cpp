#include "stdafx.h"
#include "LGameBalancerIface.auto.h"

#pragma warning( push )
#pragma warning( disable : 4065 )

namespace GameBalancer
{




    bool LIBalancerCallback::vcall( byte method_id, rpc::MethodCall& call, rpc::MethodCallStack& stack )
    {
        bool popResult = true;
        switch ( method_id )
        {
			case 0: { NI_PROFILE_BLOCK("GameBalancer::IBalancerCallback::OnGameSvcAllocated/0");rpc::VCall( stack, localObject.Get(), &GameBalancer::IBalancerCallback::OnGameSvcAllocated, popResult); } break;

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
rpc::ILocalEntity* CreateLocalEntity(GameBalancer::IBalancerCallback* api, rpc::IEntityMap* entityMap)
{
  return new GameBalancer::LIBalancerCallback(api, entityMap);
}

} // rpc

#pragma warning( pop )

NI_DEFINE_REFCOUNT( GameBalancer::LIBalancerCallback )


#pragma warning( push )
#pragma warning( disable : 4065 )

namespace GameBalancer
{


	typedef int (GameBalancer::IBalancer::*TAllocateGameSvc)( Transport::TServiceId const * svcpath, Peered::TSessionId userctx, IBalancerCallback* cb);


    bool LIBalancer::vcall( byte method_id, rpc::MethodCall& call, rpc::MethodCallStack& stack )
    {
        bool popResult = true;
        switch ( method_id )
        {
			case 0: { NI_PROFILE_BLOCK("GameBalancer::IBalancer::AllocateGameSvc/0");
			{
				int result = rpc::VCall( stack, localObject.Get(), TAllocateGameSvc(&GameBalancer::IBalancer::AllocateGameSvc), popResult); 
				call.Prepare(0).Push(result);
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
rpc::ILocalEntity* CreateLocalEntity(GameBalancer::IBalancer* api, rpc::IEntityMap* entityMap)
{
  return new GameBalancer::LIBalancer(api, entityMap);
}

} // rpc

#pragma warning( pop )

NI_DEFINE_REFCOUNT( GameBalancer::LIBalancer )


