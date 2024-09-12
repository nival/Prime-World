#include "stdafx.h"
#include "LISocialLobbyPvxSvc.auto.h"

#pragma warning( push )
#pragma warning( disable : 4065 )

namespace socialLobby
{


	typedef void (socialLobby::IPvxSvc::*TNewGame)( lobby::TSocialGameId _gameId, const mmaking::SGame * _game, const PvxGameDetails * _gameDetails, NI_LPTR IPvxAcknowledge* _ack);
	typedef void (socialLobby::IPvxSvc::*TNewSpectator)( lobby::TSocialGameId _gameId, TUserIdPvX _userId, const string* _login, NI_LPTR IPvxAcknowledge* _ack, const wstring* nickname);


    bool LIPvxSvc::vcall( byte method_id, rpc::MethodCall& call, rpc::MethodCallStack& stack )
    {
        bool popResult = true;
        switch ( method_id )
        {
			case 0: { NI_PROFILE_BLOCK("socialLobby::IPvxSvc::NewGame/0");rpc::VCall( stack, localObject.Get(), TNewGame(&socialLobby::IPvxSvc::NewGame), popResult); } break;
			case 1: { NI_PROFILE_BLOCK("socialLobby::IPvxSvc::NewReconnectingUser/1");rpc::VCall( stack, localObject.Get(), &socialLobby::IPvxSvc::NewReconnectingUser, popResult); } break;
			case 2: { NI_PROFILE_BLOCK("socialLobby::IPvxSvc::NewSpectator/2");rpc::VCall( stack, localObject.Get(), TNewSpectator(&socialLobby::IPvxSvc::NewSpectator), popResult); } break;
			case 3: { NI_PROFILE_BLOCK("socialLobby::IPvxSvc::UserLeftTheGameInCastle/3");rpc::VCall( stack, localObject.Get(), &socialLobby::IPvxSvc::UserLeftTheGameInCastle, popResult); } break;

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
rpc::ILocalEntity* CreateLocalEntity(socialLobby::IPvxSvc* api, rpc::IEntityMap* entityMap)
{
  return new socialLobby::LIPvxSvc(api, entityMap);
}

} // rpc

#pragma warning( pop )

NI_DEFINE_REFCOUNT( socialLobby::LIPvxSvc )


