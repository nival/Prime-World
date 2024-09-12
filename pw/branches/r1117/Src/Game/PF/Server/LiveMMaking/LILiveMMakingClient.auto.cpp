#include "stdafx.h"
#include "LILiveMMakingClient.auto.h"

#pragma warning( push )
#pragma warning( disable : 4065 )

namespace mmaking
{


	typedef void (mmaking::ILiveMMakingClient::*TMmLogicSetupResult)( const Transport::TServiceId * _svcId, bool _result);
	typedef void (mmaking::ILiveMMakingClient::*TGameMatchmaked)( const SGame * _game);
	typedef void (mmaking::ILiveMMakingClient::*TGameMatchmakedForReconnect)( const SReconnectSlot * _slot);


    bool LILiveMMakingClient::vcall( byte method_id, rpc::MethodCall& call, rpc::MethodCallStack& stack )
    {
        bool popResult = true;
        switch ( method_id )
        {
			case 0: { NI_PROFILE_BLOCK("mmaking::ILiveMMakingClient::MmLogicSetupResult/0");rpc::VCall( stack, localObject.Get(), TMmLogicSetupResult(&mmaking::ILiveMMakingClient::MmLogicSetupResult), popResult); } break;
			case 1: { NI_PROFILE_BLOCK("mmaking::ILiveMMakingClient::GameMatchmaked/1");rpc::VCall( stack, localObject.Get(), TGameMatchmaked(&mmaking::ILiveMMakingClient::GameMatchmaked), popResult); } break;
			case 2: { NI_PROFILE_BLOCK("mmaking::ILiveMMakingClient::GameMatchmakedForReconnect/2");rpc::VCall( stack, localObject.Get(), TGameMatchmakedForReconnect(&mmaking::ILiveMMakingClient::GameMatchmakedForReconnect), popResult); } break;
			case 3: { NI_PROFILE_BLOCK("mmaking::ILiveMMakingClient::MmResultAddRequest/3");rpc::VCall( stack, localObject.Get(), &mmaking::ILiveMMakingClient::MmResultAddRequest, popResult); } break;
			case 4: { NI_PROFILE_BLOCK("mmaking::ILiveMMakingClient::MmResultRemoveRequest/4");rpc::VCall( stack, localObject.Get(), &mmaking::ILiveMMakingClient::MmResultRemoveRequest, popResult); } break;
			case 5: { NI_PROFILE_BLOCK("mmaking::ILiveMMakingClient::MmResultAddReconnectGame/5");rpc::VCall( stack, localObject.Get(), &mmaking::ILiveMMakingClient::MmResultAddReconnectGame, popResult); } break;
			case 6: { NI_PROFILE_BLOCK("mmaking::ILiveMMakingClient::MmResultRemoveReconnectGame/6");rpc::VCall( stack, localObject.Get(), &mmaking::ILiveMMakingClient::MmResultRemoveReconnectGame, popResult); } break;
			case 7: { NI_PROFILE_BLOCK("mmaking::ILiveMMakingClient::MmDebugStatus/7");rpc::VCall( stack, localObject.Get(), &mmaking::ILiveMMakingClient::MmDebugStatus, popResult); } break;

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
rpc::ILocalEntity* CreateLocalEntity(mmaking::ILiveMMakingClient* api, rpc::IEntityMap* entityMap)
{
  return new mmaking::LILiveMMakingClient(api, entityMap);
}

} // rpc

#pragma warning( pop )

NI_DEFINE_REFCOUNT( mmaking::LILiveMMakingClient )


