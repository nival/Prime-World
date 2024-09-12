#include "stdafx.h"
#include "LClientControlRemote.auto.h"

#pragma warning( push )
#pragma warning( disable : 4065 )

namespace clientCtl
{




    bool LIUserPresenceCallback::vcall( byte method_id, rpc::MethodCall& call, rpc::MethodCallStack& stack )
    {
        bool popResult = true;
        switch ( method_id )
        {
			case 0: { NI_PROFILE_BLOCK("clientCtl::IUserPresenceCallback::LetUserIn/0");rpc::VCall( stack, localObject.Get(), &clientCtl::IUserPresenceCallback::LetUserIn, popResult); } break;
			case 1: { NI_PROFILE_BLOCK("clientCtl::IUserPresenceCallback::DenyUser/1");rpc::VCall( stack, localObject.Get(), &clientCtl::IUserPresenceCallback::DenyUser, popResult); } break;
			case 2: { NI_PROFILE_BLOCK("clientCtl::IUserPresenceCallback::KickUser/2");rpc::VCall( stack, localObject.Get(), &clientCtl::IUserPresenceCallback::KickUser, popResult); } break;

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
rpc::ILocalEntity* CreateLocalEntity(clientCtl::IUserPresenceCallback* api, rpc::IEntityMap* entityMap)
{
  return new clientCtl::LIUserPresenceCallback(api, entityMap);
}

} // rpc

#pragma warning( pop )

NI_DEFINE_REFCOUNT( clientCtl::LIUserPresenceCallback )


#pragma warning( push )
#pragma warning( disable : 4065 )

namespace clientCtl
{


	typedef void (clientCtl::ILoginSvcAllocationCallback::*TLoginSvcAllocated)( int _alllocId, const Transport::TServiceId * _svcid, NI_LPTR Login::ISessionKeyRegister* _sessionKeyInterface);


    bool LILoginSvcAllocationCallback::vcall( byte method_id, rpc::MethodCall& call, rpc::MethodCallStack& stack )
    {
        bool popResult = true;
        switch ( method_id )
        {
			case 0: { NI_PROFILE_BLOCK("clientCtl::ILoginSvcAllocationCallback::LoginSvcAllocated/0");rpc::VCall( stack, localObject.Get(), TLoginSvcAllocated(&clientCtl::ILoginSvcAllocationCallback::LoginSvcAllocated), popResult); } break;
			case 1: { NI_PROFILE_BLOCK("clientCtl::ILoginSvcAllocationCallback::LoginSvcAllocationFailed/1");rpc::VCall( stack, localObject.Get(), &clientCtl::ILoginSvcAllocationCallback::LoginSvcAllocationFailed, popResult); } break;

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
rpc::ILocalEntity* CreateLocalEntity(clientCtl::ILoginSvcAllocationCallback* api, rpc::IEntityMap* entityMap)
{
  return new clientCtl::LILoginSvcAllocationCallback(api, entityMap);
}

} // rpc

#pragma warning( pop )

NI_DEFINE_REFCOUNT( clientCtl::LILoginSvcAllocationCallback )


