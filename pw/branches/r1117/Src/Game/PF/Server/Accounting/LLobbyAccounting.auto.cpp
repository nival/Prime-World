#include "stdafx.h"
#include "LLobbyAccounting.auto.h"

#pragma warning( push )
#pragma warning( disable : 4065 )

namespace Lobby
{




    bool LLobbyAccounting::vcall( byte method_id, rpc::MethodCall& call, rpc::MethodCallStack& stack )
    {
        bool popResult = true;
        switch ( method_id )
        {
			case 0: { NI_PROFILE_BLOCK("Lobby::LobbyAccounting::BlockMoney/0");
			{
				int result = rpc::VCall( stack, localObject.Get(), &Lobby::LobbyAccounting::BlockMoney, popResult); 
				call.Prepare(0).Push(result);
			}
			} break;
			case 1: { NI_PROFILE_BLOCK("Lobby::LobbyAccounting::UnblockMoney/1");rpc::VCall( stack, localObject.Get(), &Lobby::LobbyAccounting::UnblockMoney, popResult); } break;
			case 2: { NI_PROFILE_BLOCK("Lobby::LobbyAccounting::GetServicePrice/2");
			{
				int result = rpc::VCall( stack, localObject.Get(), &Lobby::LobbyAccounting::GetServicePrice, popResult); 
				call.Prepare(2).Push(result);
			}
			} break;
			case 3: { NI_PROFILE_BLOCK("Lobby::LobbyAccounting::BuyBlockedService/3");
			{
				bool result = rpc::VCall( stack, localObject.Get(), &Lobby::LobbyAccounting::BuyBlockedService, popResult); 
				call.Prepare(3).Push(result);
			}
			} break;
			case 4: { NI_PROFILE_BLOCK("Lobby::LobbyAccounting::BuyService/4");
			{
				Lobby::BuyResult result = rpc::VCall( stack, localObject.Get(), &Lobby::LobbyAccounting::BuyService, popResult); 
				call.Prepare(4).PushByValue(result);
			}
			} break;
			case 5: { NI_PROFILE_BLOCK("Lobby::LobbyAccounting::GetMoney/5");
			{
				int result = rpc::VCall( stack, localObject.Get(), &Lobby::LobbyAccounting::GetMoney, popResult); 
				call.Prepare(5).Push(result);
			}
			} break;
			case 6: { NI_PROFILE_BLOCK("Lobby::LobbyAccounting::GiveMoneyToUser/6");
			{
				bool result = rpc::VCall( stack, localObject.Get(), &Lobby::LobbyAccounting::GiveMoneyToUser, popResult); 
				call.Prepare(6).Push(result);
			}
			} break;
			case 7: { NI_PROFILE_BLOCK("Lobby::LobbyAccounting::GetServices/7");
			{
				const nstl::vector<Lobby::ServiceInfo>& result = rpc::VCall( stack, localObject.Get(), &Lobby::LobbyAccounting::GetServices, popResult); 
				call.Prepare(7).Push(result);
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
rpc::ILocalEntity* CreateLocalEntity(Lobby::LobbyAccounting* api, rpc::IEntityMap* entityMap)
{
  return new Lobby::LLobbyAccounting(api, entityMap);
}

} // rpc

#pragma warning( pop )

NI_DEFINE_REFCOUNT( Lobby::LLobbyAccounting )


