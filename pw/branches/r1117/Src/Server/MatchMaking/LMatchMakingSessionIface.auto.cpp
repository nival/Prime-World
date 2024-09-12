#include "stdafx.h"
#include "LMatchMakingSessionIface.auto.h"

#pragma warning( push )
#pragma warning( disable : 4065 )

namespace MatchMaking
{




    bool LISession::vcall( byte method_id, rpc::MethodCall& call, rpc::MethodCallStack& stack )
    {
        bool popResult = true;
        switch ( method_id )
        {
			case 0: { NI_PROFILE_BLOCK("MatchMaking::ISession::PlayerReady/0");rpc::VCall( stack, localObject.Get(), &MatchMaking::ISession::PlayerReady, popResult); } break;

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
rpc::ILocalEntity* CreateLocalEntity(MatchMaking::ISession* api, rpc::IEntityMap* entityMap)
{
  return new MatchMaking::LISession(api, entityMap);
}

} // rpc

#pragma warning( pop )

NI_DEFINE_REFCOUNT( MatchMaking::LISession )


