#include "stdafx.h"
#include "LRelayBalancerClientNotifyIface.auto.h"

#pragma warning( push )
#pragma warning( disable : 4065 )

namespace Relay
{




    bool LIOutgoingClientNotifySink::vcall( byte method_id, rpc::MethodCall& call, rpc::MethodCallStack& stack )
    {
        bool popResult = true;
        switch ( method_id )
        {
			case 0: { NI_PROFILE_BLOCK("Relay::IOutgoingClientNotifySink::OutgoingClientNotify/0");rpc::VCall( stack, localObject.Get(), &Relay::IOutgoingClientNotifySink::OutgoingClientNotify, popResult); } break;
			case 1: { NI_PROFILE_BLOCK("Relay::IOutgoingClientNotifySink::ClientConnectedNotify/1");rpc::VCall( stack, localObject.Get(), &Relay::IOutgoingClientNotifySink::ClientConnectedNotify, popResult); } break;

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
rpc::ILocalEntity* CreateLocalEntity(Relay::IOutgoingClientNotifySink* api, rpc::IEntityMap* entityMap)
{
  return new Relay::LIOutgoingClientNotifySink(api, entityMap);
}

} // rpc

#pragma warning( pop )

NI_DEFINE_REFCOUNT( Relay::LIOutgoingClientNotifySink )


#pragma warning( push )
#pragma warning( disable : 4065 )

namespace Relay
{


	typedef bool (Relay::IIncomingClientNotifySink::*TIncomingClientNotify)( Transport::TClientId _clientid, string const * _sessionkey);


    bool LIIncomingClientNotifySink::vcall( byte method_id, rpc::MethodCall& call, rpc::MethodCallStack& stack )
    {
        bool popResult = true;
        switch ( method_id )
        {
			case 0: { NI_PROFILE_BLOCK("Relay::IIncomingClientNotifySink::RegisterOutgoingClientNotifySink/0");
			{
				int result = rpc::VCall( stack, localObject.Get(), &Relay::IIncomingClientNotifySink::RegisterOutgoingClientNotifySink, popResult); 
				call.Prepare(0).Push(result);
			}
			} break;
			case 1: { NI_PROFILE_BLOCK("Relay::IIncomingClientNotifySink::IncomingClientNotify/1");
			{
				bool result = rpc::VCall( stack, localObject.Get(), TIncomingClientNotify(&Relay::IIncomingClientNotifySink::IncomingClientNotify), popResult); 
				call.Prepare(1).Push(result);
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
rpc::ILocalEntity* CreateLocalEntity(Relay::IIncomingClientNotifySink* api, rpc::IEntityMap* entityMap)
{
  return new Relay::LIIncomingClientNotifySink(api, entityMap);
}

} // rpc

#pragma warning( pop )

NI_DEFINE_REFCOUNT( Relay::LIIncomingClientNotifySink )


