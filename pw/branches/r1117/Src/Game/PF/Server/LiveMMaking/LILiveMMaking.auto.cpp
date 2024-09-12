#include "stdafx.h"
#include "LILiveMMaking.auto.h"

#pragma warning( push )
#pragma warning( disable : 4065 )

namespace mmaking
{


	typedef void (mmaking::ILiveMMaking::*TSetupLogic)( const string * _mapId, NI_LPTR ILiveMMakingClient* _client);
	typedef void (mmaking::ILiveMMaking::*TAddMmRequest)( TRequestUId _requestUId, const SRequestCommonData * _commonData, const vector<SRequestMember> * _members, timer::Time _waitTime);
	typedef void (mmaking::ILiveMMaking::*TAddGameForReconnect)( lobby::TGameId _gameId, const SGame * _gameData);


    bool LILiveMMaking::vcall( byte method_id, rpc::MethodCall& call, rpc::MethodCallStack& stack )
    {
        bool popResult = true;
        switch ( method_id )
        {
			case 0: { NI_PROFILE_BLOCK("mmaking::ILiveMMaking::SetupLogic/0");rpc::VCall( stack, localObject.Get(), TSetupLogic(&mmaking::ILiveMMaking::SetupLogic), popResult); } break;
			case 1: { NI_PROFILE_BLOCK("mmaking::ILiveMMaking::AddMmRequest/1");rpc::VCall( stack, localObject.Get(), TAddMmRequest(&mmaking::ILiveMMaking::AddMmRequest), popResult); } break;
			case 2: { NI_PROFILE_BLOCK("mmaking::ILiveMMaking::RemoveMmRequest/2");rpc::VCall( stack, localObject.Get(), &mmaking::ILiveMMaking::RemoveMmRequest, popResult); } break;
			case 3: { NI_PROFILE_BLOCK("mmaking::ILiveMMaking::AddGameForReconnect/3");rpc::VCall( stack, localObject.Get(), TAddGameForReconnect(&mmaking::ILiveMMaking::AddGameForReconnect), popResult); } break;
			case 4: { NI_PROFILE_BLOCK("mmaking::ILiveMMaking::RemoveGame/4");rpc::VCall( stack, localObject.Get(), &mmaking::ILiveMMaking::RemoveGame, popResult); } break;

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
rpc::ILocalEntity* CreateLocalEntity(mmaking::ILiveMMaking* api, rpc::IEntityMap* entityMap)
{
  return new mmaking::LILiveMMaking(api, entityMap);
}

} // rpc

#pragma warning( pop )

NI_DEFINE_REFCOUNT( mmaking::LILiveMMaking )


