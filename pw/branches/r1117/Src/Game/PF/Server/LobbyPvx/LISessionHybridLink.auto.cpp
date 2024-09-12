#include "stdafx.h"
#include "LISessionHybridLink.auto.h"

#pragma warning( push )
#pragma warning( disable : 4065 )

namespace lobby
{


	typedef void (lobby::ISessionHybridLink::*TOnGameFinish)( Peered::TSessionId _sessionId, int _gameResultType, const StatisticService::RPC::SessionClientResults * _finishInfo, const nstl::vector<Peered::SClientStatistics> * _clientsStatistics);
	typedef void (lobby::ISessionHybridLink::*TOnChangeClientStatus)( Peered::TSessionId _sessionId, const nstl::vector<Peered::BriefClientInfo> * _clientInfos);


    bool LISessionHybridLink::vcall( byte method_id, rpc::MethodCall& call, rpc::MethodCallStack& stack )
    {
        bool popResult = true;
        switch ( method_id )
        {
			case 0: { NI_PROFILE_BLOCK("lobby::ISessionHybridLink::OnGameFinish/0");rpc::VCall( stack, localObject.Get(), TOnGameFinish(&lobby::ISessionHybridLink::OnGameFinish), popResult); } break;
			case 1: { NI_PROFILE_BLOCK("lobby::ISessionHybridLink::OnGameCheated/1");rpc::VCall( stack, localObject.Get(), &lobby::ISessionHybridLink::OnGameCheated, popResult); } break;
			case 2: { NI_PROFILE_BLOCK("lobby::ISessionHybridLink::OnChangeClientStatus/2");rpc::VCall( stack, localObject.Get(), TOnChangeClientStatus(&lobby::ISessionHybridLink::OnChangeClientStatus), popResult); } break;

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
rpc::ILocalEntity* CreateLocalEntity(lobby::ISessionHybridLink* api, rpc::IEntityMap* entityMap)
{
  return new lobby::LISessionHybridLink(api, entityMap);
}

} // rpc

#pragma warning( pop )

NI_DEFINE_REFCOUNT( lobby::LISessionHybridLink )


