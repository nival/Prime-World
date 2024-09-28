#include "stdafx.h"
#include "LLobbyIServerInstance.auto.h"

#pragma warning( push )
#pragma warning( disable : 4065 )

namespace lobby
{


	typedef EOperationResult::Enum (lobby::IServerInstance::*TReconnectToCustomGame)( int gameId, int team, const string * heroId);
	typedef EOperationResult::Enum (lobby::IServerInstance::*TCreateCustomGame)( int maxPlayers, int maxPlayersPerTeam, const string * mapId, int autostartPlayers);
	typedef void (lobby::IServerInstance::*TChangeCustomGameSettings)( int team, int faction, const string * heroId);


    bool LIServerInstance::vcall( byte method_id, rpc::MethodCall& call, rpc::MethodCallStack& stack )
    {
        bool popResult = true;
        switch ( method_id )
        {
			case 0: { NI_PROFILE_BLOCK("lobby::IServerInstance::SetDeveloperSex/0");rpc::VCall( stack, localObject.Get(), &lobby::IServerInstance::SetDeveloperSex, popResult); } break;
			case 1: { NI_PROFILE_BLOCK("lobby::IServerInstance::RequestGamesList/1");rpc::VCall( stack, localObject.Get(), &lobby::IServerInstance::RequestGamesList, popResult); } break;
			case 2: { NI_PROFILE_BLOCK("lobby::IServerInstance::JoinGame/2");
			{
				EOperationResult::Enum result = rpc::VCall( stack, localObject.Get(), &lobby::IServerInstance::JoinGame, popResult); 
				call.Prepare(2).PushByValue(result);
			}
			} break;
			case 3: { NI_PROFILE_BLOCK("lobby::IServerInstance::ReconnectToCustomGame/3");
			{
				EOperationResult::Enum result = rpc::VCall( stack, localObject.Get(), TReconnectToCustomGame(&lobby::IServerInstance::ReconnectToCustomGame), popResult); 
				call.Prepare(3).PushByValue(result);
			}
			} break;
			case 4: { NI_PROFILE_BLOCK("lobby::IServerInstance::CreateCustomGame/4");
			{
				EOperationResult::Enum result = rpc::VCall( stack, localObject.Get(), TCreateCustomGame(&lobby::IServerInstance::CreateCustomGame), popResult); 
				call.Prepare(4).PushByValue(result);
			}
			} break;
			case 5: { NI_PROFILE_BLOCK("lobby::IServerInstance::SpectateCustomGame/5");
			{
				EOperationResult::Enum result = rpc::VCall( stack, localObject.Get(), &lobby::IServerInstance::SpectateCustomGame, popResult); 
				call.Prepare(5).PushByValue(result);
			}
			} break;
			case 6: { NI_PROFILE_BLOCK("lobby::IServerInstance::ChangeCustomGameSettings/6");rpc::VCall( stack, localObject.Get(), TChangeCustomGameSettings(&lobby::IServerInstance::ChangeCustomGameSettings), popResult); } break;
			case 7: { NI_PROFILE_BLOCK("lobby::IServerInstance::SetReady/7");rpc::VCall( stack, localObject.Get(), &lobby::IServerInstance::SetReady, popResult); } break;
			case 8: { NI_PROFILE_BLOCK("lobby::IServerInstance::SetDeveloperParty/8");rpc::VCall( stack, localObject.Get(), &lobby::IServerInstance::SetDeveloperParty, popResult); } break;
			case 9: { NI_PROFILE_BLOCK("lobby::IServerInstance::JoinSocialGame/9");
			{
				EOperationResult::Enum result = rpc::VCall( stack, localObject.Get(), &lobby::IServerInstance::JoinSocialGame, popResult); 
				call.Prepare(9).PushByValue(result);
			}
			} break;

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
rpc::ILocalEntity* CreateLocalEntity(lobby::IServerInstance* api, rpc::IEntityMap* entityMap)
{
  return new lobby::LIServerInstance(api, entityMap);
}

} // rpc

#pragma warning( pop )

NI_DEFINE_REFCOUNT( lobby::LIServerInstance )


