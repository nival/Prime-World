#include "stdafx.h"
#include "LClientControlInterface.auto.h"

#pragma warning( push )
#pragma warning( disable : 4065 )

namespace clientCtl
{


	typedef void (clientCtl::IInterface::*TRegisterLoginSvc)( const Transport::TServiceId* _svcid, NI_LPTR Login::ISessionKeyRegister* _sessionKeyInterface);
	typedef void (clientCtl::IInterface::*TUpdateLoginSvc)( const Transport::TServiceId* _svcid, int _state, unsigned _load);
	typedef void (clientCtl::IInterface::*TUserEnters)( const Transport::TServiceId* _loginSvcId, Transport::TClientId _uid, Transport::TUserSid _usid, NI_LPTR IUserPresenceCallback* _callback);
	typedef void (clientCtl::IInterface::*TUserLeft)( const Transport::TServiceId* _loginSvcId, Transport::TClientId _uid, Transport::TUserSid _usid);


    bool LIInterface::vcall( byte method_id, rpc::MethodCall& call, rpc::MethodCallStack& stack )
    {
        bool popResult = true;
        switch ( method_id )
        {
			case 0: { NI_PROFILE_BLOCK("clientCtl::IInterface::RegisterLoginSvc/0");rpc::VCall( stack, localObject.Get(), TRegisterLoginSvc(&clientCtl::IInterface::RegisterLoginSvc), popResult); } break;
			case 1: { NI_PROFILE_BLOCK("clientCtl::IInterface::UpdateLoginSvc/1");rpc::VCall( stack, localObject.Get(), TUpdateLoginSvc(&clientCtl::IInterface::UpdateLoginSvc), popResult); } break;
			case 2: { NI_PROFILE_BLOCK("clientCtl::IInterface::AllocateLoginSvc/2");rpc::VCall( stack, localObject.Get(), &clientCtl::IInterface::AllocateLoginSvc, popResult); } break;
			case 3: { NI_PROFILE_BLOCK("clientCtl::IInterface::UserEnters/3");rpc::VCall( stack, localObject.Get(), TUserEnters(&clientCtl::IInterface::UserEnters), popResult); } break;
			case 4: { NI_PROFILE_BLOCK("clientCtl::IInterface::UserLeft/4");rpc::VCall( stack, localObject.Get(), TUserLeft(&clientCtl::IInterface::UserLeft), popResult); } break;
			case 5: { NI_PROFILE_BLOCK("clientCtl::IInterface::KickUser/5");rpc::VCall( stack, localObject.Get(), &clientCtl::IInterface::KickUser, popResult); } break;

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
rpc::ILocalEntity* CreateLocalEntity(clientCtl::IInterface* api, rpc::IEntityMap* entityMap)
{
  return new clientCtl::LIInterface(api, entityMap);
}

} // rpc

#pragma warning( pop )

NI_DEFINE_REFCOUNT( clientCtl::LIInterface )


