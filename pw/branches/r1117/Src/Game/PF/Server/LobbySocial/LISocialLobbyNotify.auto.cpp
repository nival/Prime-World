#include "stdafx.h"
#include "LISocialLobbyNotify.auto.h"

#pragma warning( push )
#pragma warning( disable : 4065 )

namespace socialLobby
{


	typedef void (socialLobby::INotify::*TUpdateStatus)( const SMatchmakingStatus* _status);


    bool LINotify::vcall( byte method_id, rpc::MethodCall& call, rpc::MethodCallStack& stack )
    {
        bool popResult = true;
        switch ( method_id )
        {
			case 0: { NI_PROFILE_BLOCK("socialLobby::INotify::Open/0");rpc::VCall( stack, localObject.Get(), &socialLobby::INotify::Open, popResult); } break;
			case 1: { NI_PROFILE_BLOCK("socialLobby::INotify::Failure/1");rpc::VCall( stack, localObject.Get(), &socialLobby::INotify::Failure, popResult); } break;
			case 2: { NI_PROFILE_BLOCK("socialLobby::INotify::UpdateStatus/2");rpc::VCall( stack, localObject.Get(), TUpdateStatus(&socialLobby::INotify::UpdateStatus), popResult); } break;
			case 3: { NI_PROFILE_BLOCK("socialLobby::INotify::Close/3");rpc::VCall( stack, localObject.Get(), &socialLobby::INotify::Close, popResult); } break;

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
rpc::ILocalEntity* CreateLocalEntity(socialLobby::INotify* api, rpc::IEntityMap* entityMap)
{
  return new socialLobby::LINotify(api, entityMap);
}

} // rpc

#pragma warning( pop )

NI_DEFINE_REFCOUNT( socialLobby::LINotify )


