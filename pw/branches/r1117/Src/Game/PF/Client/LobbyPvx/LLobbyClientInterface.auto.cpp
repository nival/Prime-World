#include "stdafx.h"
#include "LLobbyClientInterface.auto.h"

#pragma warning( push )
#pragma warning( disable : 4065 )

namespace lobby
{


	typedef void (lobby::ILobbyUser::*TAddGameInfo)( const SDevGameInfo * info);
	typedef void (lobby::ILobbyUser::*TJoinCustomSession)( const SGameParameters * params);
	typedef void (lobby::ILobbyUser::*TAddCustomGameMember)( const SGameMember * member);
	typedef void (lobby::ILobbyUser::*TUpdateCustomGameMember)( int userId, const SPlayerGameContext * params);
	typedef void (lobby::ILobbyUser::*TStartSession)( TGameId sessionId, const SGameParameters * params, const TGameLineUp * gameLineUp, Peered::RIGameServer * gameServerInstance, const Peered::SInstanceId * _gsInstId, unsigned timestamp32);
	typedef void (lobby::ILobbyUser::*TAward)( const vector<roll::SAwardInfo> * _awards);


    bool LILobbyUser::vcall( byte method_id, rpc::MethodCall& call, rpc::MethodCallStack& stack )
    {
        bool popResult = true;
        switch ( method_id )
        {
			case 0: { NI_PROFILE_BLOCK("lobby::ILobbyUser::AddGameInfo/0");rpc::VCall( stack, localObject.Get(), TAddGameInfo(&lobby::ILobbyUser::AddGameInfo), popResult); } break;
			case 1: { NI_PROFILE_BLOCK("lobby::ILobbyUser::JoinCustomSession/1");rpc::VCall( stack, localObject.Get(), TJoinCustomSession(&lobby::ILobbyUser::JoinCustomSession), popResult); } break;
			case 2: { NI_PROFILE_BLOCK("lobby::ILobbyUser::UpdateClientStatus/2");rpc::VCall( stack, localObject.Get(), &lobby::ILobbyUser::UpdateClientStatus, popResult); } break;
			case 3: { NI_PROFILE_BLOCK("lobby::ILobbyUser::AddCustomGameMember/3");rpc::VCall( stack, localObject.Get(), TAddCustomGameMember(&lobby::ILobbyUser::AddCustomGameMember), popResult); } break;
			case 4: { NI_PROFILE_BLOCK("lobby::ILobbyUser::RemoveCustomGameMember/4");rpc::VCall( stack, localObject.Get(), &lobby::ILobbyUser::RemoveCustomGameMember, popResult); } break;
			case 5: { NI_PROFILE_BLOCK("lobby::ILobbyUser::UpdateCustomGameMember/5");rpc::VCall( stack, localObject.Get(), TUpdateCustomGameMember(&lobby::ILobbyUser::UpdateCustomGameMember), popResult); } break;
			case 6: { NI_PROFILE_BLOCK("lobby::ILobbyUser::UpdateCustomGameMemberReadiness/6");rpc::VCall( stack, localObject.Get(), &lobby::ILobbyUser::UpdateCustomGameMemberReadiness, popResult); } break;
			case 7: { NI_PROFILE_BLOCK("lobby::ILobbyUser::StartSession/7");rpc::VCall( stack, localObject.Get(), TStartSession(&lobby::ILobbyUser::StartSession), popResult); } break;
			case 8: { NI_PROFILE_BLOCK("lobby::ILobbyUser::Award/8");rpc::VCall( stack, localObject.Get(), TAward(&lobby::ILobbyUser::Award), popResult); } break;

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
rpc::ILocalEntity* CreateLocalEntity(lobby::ILobbyUser* api, rpc::IEntityMap* entityMap)
{
  return new lobby::LILobbyUser(api, entityMap);
}

} // rpc

#pragma warning( pop )

NI_DEFINE_REFCOUNT( lobby::LILobbyUser )


