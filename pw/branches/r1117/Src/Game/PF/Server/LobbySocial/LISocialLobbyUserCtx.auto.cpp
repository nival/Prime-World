#include "stdafx.h"
#include "LISocialLobbyUserCtx.auto.h"

#pragma warning( push )
#pragma warning( disable : 4065 )

namespace socialLobby
{


	typedef void (socialLobby::IUserContext::*TAcceptGameSession)( const SPlayerData* _playerData);
	typedef void (socialLobby::IUserContext::*TChangeGuardHero)( const SPlayerData* _playerData);


    bool LIUserContext::vcall( byte method_id, rpc::MethodCall& call, rpc::MethodCallStack& stack )
    {
        bool popResult = true;
        switch ( method_id )
        {
			case 0: { NI_PROFILE_BLOCK("socialLobby::IUserContext::AcceptGameSession/0");rpc::VCall( stack, localObject.Get(), TAcceptGameSession(&socialLobby::IUserContext::AcceptGameSession), popResult); } break;
			case 1: { NI_PROFILE_BLOCK("socialLobby::IUserContext::ChangeGuardHero/1");rpc::VCall( stack, localObject.Get(), TChangeGuardHero(&socialLobby::IUserContext::ChangeGuardHero), popResult); } break;
			case 2: { NI_PROFILE_BLOCK("socialLobby::IUserContext::GuardReady/2");rpc::VCall( stack, localObject.Get(), &socialLobby::IUserContext::GuardReady, popResult); } break;
			case 3: { NI_PROFILE_BLOCK("socialLobby::IUserContext::ReconnectToGame/3");rpc::VCall( stack, localObject.Get(), &socialLobby::IUserContext::ReconnectToGame, popResult); } break;
			case 4: { NI_PROFILE_BLOCK("socialLobby::IUserContext::LeaveGame/4");rpc::VCall( stack, localObject.Get(), &socialLobby::IUserContext::LeaveGame, popResult); } break;
			case 5: { NI_PROFILE_BLOCK("socialLobby::IUserContext::CancelRequest/5");rpc::VCall( stack, localObject.Get(), &socialLobby::IUserContext::CancelRequest, popResult); } break;
			case 6: { NI_PROFILE_BLOCK("socialLobby::IUserContext::CancelPartyRequest/6");rpc::VCall( stack, localObject.Get(), &socialLobby::IUserContext::CancelPartyRequest, popResult); } break;
			case 7: { NI_PROFILE_BLOCK("socialLobby::IUserContext::EmergencyCancel/7");rpc::VCall( stack, localObject.Get(), &socialLobby::IUserContext::EmergencyCancel, popResult); } break;

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
rpc::ILocalEntity* CreateLocalEntity(socialLobby::IUserContext* api, rpc::IEntityMap* entityMap)
{
  return new socialLobby::LIUserContext(api, entityMap);
}

} // rpc

#pragma warning( pop )

NI_DEFINE_REFCOUNT( socialLobby::LIUserContext )


