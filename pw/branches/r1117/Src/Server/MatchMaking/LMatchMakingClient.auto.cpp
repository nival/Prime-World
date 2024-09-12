#include "stdafx.h"
#include "LMatchMakingClient.auto.h"

#pragma warning( push )
#pragma warning( disable : 4065 )

namespace MatchMaking
{




    bool LIClient::vcall( byte method_id, rpc::MethodCall& call, rpc::MethodCallStack& stack )
    {
        bool popResult = true;
        switch ( method_id )
        {
			case 0: { NI_PROFILE_BLOCK("MatchMaking::IClient::MatchMakingCompleted/0");rpc::VCall( stack, localObject.Get(), &MatchMaking::IClient::MatchMakingCompleted, popResult); } break;
			case 1: { NI_PROFILE_BLOCK("MatchMaking::IClient::OnSessionStarted/1");rpc::VCall( stack, localObject.Get(), &MatchMaking::IClient::OnSessionStarted, popResult); } break;

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
rpc::ILocalEntity* CreateLocalEntity(MatchMaking::IClient* api, rpc::IEntityMap* entityMap)
{
  return new MatchMaking::LIClient(api, entityMap);
}

} // rpc

#pragma warning( pop )

NI_DEFINE_REFCOUNT( MatchMaking::LIClient )


