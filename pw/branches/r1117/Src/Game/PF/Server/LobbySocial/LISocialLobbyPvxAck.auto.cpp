#include "stdafx.h"
#include "LISocialLobbyPvxAck.auto.h"

#pragma warning( push )
#pragma warning( disable : 4065 )

namespace socialLobby
{




    bool LIPvxAcknowledge::vcall( byte method_id, rpc::MethodCall& call, rpc::MethodCallStack& stack )
    {
        bool popResult = true;
        switch ( method_id )
        {
			case 0: { NI_PROFILE_BLOCK("socialLobby::IPvxAcknowledge::NewGameAck/0");rpc::VCall( stack, localObject.Get(), &socialLobby::IPvxAcknowledge::NewGameAck, popResult); } break;
			case 1: { NI_PROFILE_BLOCK("socialLobby::IPvxAcknowledge::NewReconnectingUserAck/1");rpc::VCall( stack, localObject.Get(), &socialLobby::IPvxAcknowledge::NewReconnectingUserAck, popResult); } break;
			case 2: { NI_PROFILE_BLOCK("socialLobby::IPvxAcknowledge::NewSpectatorAck/2");rpc::VCall( stack, localObject.Get(), &socialLobby::IPvxAcknowledge::NewSpectatorAck, popResult); } break;
			case 3: { NI_PROFILE_BLOCK("socialLobby::IPvxAcknowledge::UserLeftTheGameInCastleAck/3");rpc::VCall( stack, localObject.Get(), &socialLobby::IPvxAcknowledge::UserLeftTheGameInCastleAck, popResult); } break;

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
rpc::ILocalEntity* CreateLocalEntity(socialLobby::IPvxAcknowledge* api, rpc::IEntityMap* entityMap)
{
  return new socialLobby::LIPvxAcknowledge(api, entityMap);
}

} // rpc

#pragma warning( pop )

NI_DEFINE_REFCOUNT( socialLobby::LIPvxAcknowledge )


