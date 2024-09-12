#include "stdafx.h"
#include "LRelayBalancerIface.auto.h"

#pragma warning( push )
#pragma warning( disable : 4065 )

namespace Relay
{


	typedef void (Relay::IBalancerCallback::*TOnRelayAllocated)( Transport::TClientId clienid, int userctx, Transport::TServiceId const * genericrelay, Network::NetAddress const * genericaddr, Transport::TServiceId const * gamerelay, Network::NetAddress const * gameaddr);


    bool LIBalancerCallback::vcall( byte method_id, rpc::MethodCall& call, rpc::MethodCallStack& stack )
    {
        bool popResult = true;
        switch ( method_id )
        {
			case 0: { NI_PROFILE_BLOCK("Relay::IBalancerCallback::OnRelayAllocated/0");rpc::VCall( stack, localObject.Get(), TOnRelayAllocated(&Relay::IBalancerCallback::OnRelayAllocated), popResult); } break;

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
rpc::ILocalEntity* CreateLocalEntity(Relay::IBalancerCallback* api, rpc::IEntityMap* entityMap)
{
  return new Relay::LIBalancerCallback(api, entityMap);
}

} // rpc

#pragma warning( pop )

NI_DEFINE_REFCOUNT( Relay::LIBalancerCallback )


#pragma warning( push )
#pragma warning( disable : 4065 )

namespace Relay
{


	typedef int (Relay::IBalancer::*TAllocateRelay)( Cluster::TGameId gameid, Transport::TClientId clienid, Transport::TServiceId const * svcpath, Coordinator::TServiceRole const * _svcrole, int userctx, Relay::IBalancerCallback* cb);


    bool LIBalancer::vcall( byte method_id, rpc::MethodCall& call, rpc::MethodCallStack& stack )
    {
        bool popResult = true;
        switch ( method_id )
        {
			case 0: { NI_PROFILE_BLOCK("Relay::IBalancer::AllocateRelay/0");
			{
				int result = rpc::VCall( stack, localObject.Get(), TAllocateRelay(&Relay::IBalancer::AllocateRelay), popResult); 
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
rpc::ILocalEntity* CreateLocalEntity(Relay::IBalancer* api, rpc::IEntityMap* entityMap)
{
  return new Relay::LIBalancer(api, entityMap);
}

} // rpc

#pragma warning( pop )

NI_DEFINE_REFCOUNT( Relay::LIBalancer )


