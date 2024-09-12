#include "stdafx.h"
#include "LRollBalancer.auto.h"

#pragma warning( push )
#pragma warning( disable : 4065 )

namespace roll
{


	typedef void (roll::IBalancer::*TLoadNotify)( RIInstance* inst, const string * serviceId, int currentLoad);


    bool LIBalancer::vcall( byte method_id, rpc::MethodCall& call, rpc::MethodCallStack& stack )
    {
        bool popResult = true;
        switch ( method_id )
        {
			case 0: { NI_PROFILE_BLOCK("roll::IBalancer::LoadNotify/0");rpc::VCall( stack, localObject.Get(), TLoadNotify(&roll::IBalancer::LoadNotify), popResult); } break;
			case 1: { NI_PROFILE_BLOCK("roll::IBalancer::AllocateInstance/1");
			{
				RIInstance* result = rpc::VCall( stack, localObject.Get(), &roll::IBalancer::AllocateInstance, popResult); 
				call.Prepare(1).Push(result);
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
rpc::ILocalEntity* CreateLocalEntity(roll::IBalancer* api, rpc::IEntityMap* entityMap)
{
  return new roll::LIBalancer(api, entityMap);
}

} // rpc

#pragma warning( pop )

NI_DEFINE_REFCOUNT( roll::LIBalancer )


