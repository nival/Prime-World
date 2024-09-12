#include "stdafx.h"
#include "LSessionKeyRegisterIface.auto.h"

#pragma warning( push )
#pragma warning( disable : 4065 )

namespace Login
{


	typedef void (Login::IAddSessionKeyCallback::*TOnAddSessionKey)( int _rc, const nstl::string * _loginSvcAddr, Cluster::TUserId _userid);


    bool LIAddSessionKeyCallback::vcall( byte method_id, rpc::MethodCall& call, rpc::MethodCallStack& stack )
    {
        bool popResult = true;
        switch ( method_id )
        {
			case 0: { NI_PROFILE_BLOCK("Login::IAddSessionKeyCallback::OnAddSessionKey/0");rpc::VCall( stack, localObject.Get(), TOnAddSessionKey(&Login::IAddSessionKeyCallback::OnAddSessionKey), popResult); } break;

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
rpc::ILocalEntity* CreateLocalEntity(Login::IAddSessionKeyCallback* api, rpc::IEntityMap* entityMap)
{
  return new Login::LIAddSessionKeyCallback(api, entityMap);
}

} // rpc

#pragma warning( pop )

NI_DEFINE_REFCOUNT( Login::LIAddSessionKeyCallback )


#pragma warning( push )
#pragma warning( disable : 4065 )

namespace Login
{


	typedef void (Login::ISessionKeyRegister::*TAddSessionKey)( const nstl::string* _sessionKey, const Transport::TServiceId* _sessionPath, const nstl::string* _login, Cluster::TUserId _userid, Cluster::TGameId _gameid, NI_LPTR IAddSessionKeyCallback* _pcb);


    bool LISessionKeyRegister::vcall( byte method_id, rpc::MethodCall& call, rpc::MethodCallStack& stack )
    {
        bool popResult = true;
        switch ( method_id )
        {
			case 0: { NI_PROFILE_BLOCK("Login::ISessionKeyRegister::AddSessionKey/0");rpc::VCall( stack, localObject.Get(), TAddSessionKey(&Login::ISessionKeyRegister::AddSessionKey), popResult); } break;

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
rpc::ILocalEntity* CreateLocalEntity(Login::ISessionKeyRegister* api, rpc::IEntityMap* entityMap)
{
  return new Login::LISessionKeyRegister(api, entityMap);
}

} // rpc

#pragma warning( pop )

NI_DEFINE_REFCOUNT( Login::LISessionKeyRegister )


