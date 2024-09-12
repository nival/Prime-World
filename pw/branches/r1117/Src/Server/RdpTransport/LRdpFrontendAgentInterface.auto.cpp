#include "stdafx.h"
#include "LRdpFrontendAgentInterface.auto.h"

#pragma warning( push )
#pragma warning( disable : 4065 )

namespace rdp_transport
{


	typedef void (rdp_transport::IFrontendAgent::*TPrepareUser)( Transport::TClientId _uid, const string * _login, const string * _key, NI_LPTR IFrontendAgentRemote* _callback);


    bool LIFrontendAgent::vcall( byte method_id, rpc::MethodCall& call, rpc::MethodCallStack& stack )
    {
        bool popResult = true;
        switch ( method_id )
        {
			case 0: { NI_PROFILE_BLOCK("rdp_transport::IFrontendAgent::PrepareUser/0");rpc::VCall( stack, localObject.Get(), TPrepareUser(&rdp_transport::IFrontendAgent::PrepareUser), popResult); } break;
			case 1: { NI_PROFILE_BLOCK("rdp_transport::IFrontendAgent::KickUser/1");rpc::VCall( stack, localObject.Get(), &rdp_transport::IFrontendAgent::KickUser, popResult); } break;

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
rpc::ILocalEntity* CreateLocalEntity(rdp_transport::IFrontendAgent* api, rpc::IEntityMap* entityMap)
{
  return new rdp_transport::LIFrontendAgent(api, entityMap);
}

} // rpc

#pragma warning( pop )

NI_DEFINE_REFCOUNT( rdp_transport::LIFrontendAgent )


