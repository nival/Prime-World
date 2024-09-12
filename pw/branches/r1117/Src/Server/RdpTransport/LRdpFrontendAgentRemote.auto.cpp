#include "stdafx.h"
#include "LRdpFrontendAgentRemote.auto.h"

#pragma warning( push )
#pragma warning( disable : 4065 )

namespace rdp_transport
{




    bool LIFrontendAgentRemote::vcall( byte method_id, rpc::MethodCall& call, rpc::MethodCallStack& stack )
    {
        bool popResult = true;
        switch ( method_id )
        {
			case 0: { NI_PROFILE_BLOCK("rdp_transport::IFrontendAgentRemote::UserPrepared/0");rpc::VCall( stack, localObject.Get(), &rdp_transport::IFrontendAgentRemote::UserPrepared, popResult); } break;
			case 1: { NI_PROFILE_BLOCK("rdp_transport::IFrontendAgentRemote::UserConnected/1");rpc::VCall( stack, localObject.Get(), &rdp_transport::IFrontendAgentRemote::UserConnected, popResult); } break;
			case 2: { NI_PROFILE_BLOCK("rdp_transport::IFrontendAgentRemote::UserTimedOut/2");rpc::VCall( stack, localObject.Get(), &rdp_transport::IFrontendAgentRemote::UserTimedOut, popResult); } break;
			case 3: { NI_PROFILE_BLOCK("rdp_transport::IFrontendAgentRemote::UserKicked/3");rpc::VCall( stack, localObject.Get(), &rdp_transport::IFrontendAgentRemote::UserKicked, popResult); } break;
			case 4: { NI_PROFILE_BLOCK("rdp_transport::IFrontendAgentRemote::UserDropped/4");rpc::VCall( stack, localObject.Get(), &rdp_transport::IFrontendAgentRemote::UserDropped, popResult); } break;

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
rpc::ILocalEntity* CreateLocalEntity(rdp_transport::IFrontendAgentRemote* api, rpc::IEntityMap* entityMap)
{
  return new rdp_transport::LIFrontendAgentRemote(api, entityMap);
}

} // rpc

#pragma warning( pop )

NI_DEFINE_REFCOUNT( rdp_transport::LIFrontendAgentRemote )


