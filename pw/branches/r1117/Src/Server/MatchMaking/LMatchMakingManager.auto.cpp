#include "stdafx.h"
#include "LMatchMakingManager.auto.h"

#pragma warning( push )
#pragma warning( disable : 4065 )

namespace MatchMaking
{


	typedef void (MatchMaking::Manager::*TCancelMatchMaking)( ClientId const * cid);


    bool LManager::vcall( byte method_id, rpc::MethodCall& call, rpc::MethodCallStack& stack )
    {
        bool popResult = true;
        switch ( method_id )
        {
			case 0: { NI_PROFILE_BLOCK("MatchMaking::Manager::RequestMatchMaking/0");
			{
				ClientId result = rpc::VCall( stack, localObject.Get(), &MatchMaking::Manager::RequestMatchMaking, popResult); 
				call.Prepare(0).PushByValue(result);
			}
			} break;
			case 1: { NI_PROFILE_BLOCK("MatchMaking::Manager::CancelMatchMaking/1");rpc::VCall( stack, localObject.Get(), TCancelMatchMaking(&MatchMaking::Manager::CancelMatchMaking), popResult); } break;

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
rpc::ILocalEntity* CreateLocalEntity(MatchMaking::Manager* api, rpc::IEntityMap* entityMap)
{
  return new MatchMaking::LManager(api, entityMap);
}

} // rpc

#pragma warning( pop )

NI_DEFINE_REFCOUNT( MatchMaking::LManager )


