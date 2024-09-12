#include "stdafx.h"
#include "LCoordinatorClientIface.auto.h"

#pragma warning( push )
#pragma warning( disable : 4065 )

namespace Coordinator
{


	typedef void (Coordinator::ICoordinatorClientRemote::*TAddRoute)( const Transport::TServiceId* service, SvcNetAddresses const * addrs);
	typedef void (Coordinator::ICoordinatorClientRemote::*TRemoveRoute)( const Transport::TServiceId* service);
	typedef void (Coordinator::ICoordinatorClientRemote::*TStartService)( const Transport::TServiceId* service);
	typedef void (Coordinator::ICoordinatorClientRemote::*TStopService)( const Transport::TServiceId* service);
	typedef void (Coordinator::ICoordinatorClientRemote::*TSoftStopService)( const Transport::TServiceId* service);
	typedef void (Coordinator::ICoordinatorClientRemote::*TReloadConfig)( const Transport::TServiceId * service);


    bool LICoordinatorClientRemote::vcall( byte method_id, rpc::MethodCall& call, rpc::MethodCallStack& stack )
    {
        bool popResult = true;
        switch ( method_id )
        {
			case 0: { NI_PROFILE_BLOCK("Coordinator::ICoordinatorClientRemote::AddRoute/0");rpc::VCall( stack, localObject.Get(), TAddRoute(&Coordinator::ICoordinatorClientRemote::AddRoute), popResult); } break;
			case 1: { NI_PROFILE_BLOCK("Coordinator::ICoordinatorClientRemote::RemoveRoute/1");rpc::VCall( stack, localObject.Get(), TRemoveRoute(&Coordinator::ICoordinatorClientRemote::RemoveRoute), popResult); } break;
			case 2: { NI_PROFILE_BLOCK("Coordinator::ICoordinatorClientRemote::StartService/2");rpc::VCall( stack, localObject.Get(), TStartService(&Coordinator::ICoordinatorClientRemote::StartService), popResult); } break;
			case 3: { NI_PROFILE_BLOCK("Coordinator::ICoordinatorClientRemote::StopService/3");rpc::VCall( stack, localObject.Get(), TStopService(&Coordinator::ICoordinatorClientRemote::StopService), popResult); } break;
			case 4: { NI_PROFILE_BLOCK("Coordinator::ICoordinatorClientRemote::SoftStopService/4");rpc::VCall( stack, localObject.Get(), TSoftStopService(&Coordinator::ICoordinatorClientRemote::SoftStopService), popResult); } break;
			case 5: { NI_PROFILE_BLOCK("Coordinator::ICoordinatorClientRemote::ReloadConfig/5");rpc::VCall( stack, localObject.Get(), TReloadConfig(&Coordinator::ICoordinatorClientRemote::ReloadConfig), popResult); } break;
			case 6: { NI_PROFILE_BLOCK("Coordinator::ICoordinatorClientRemote::Ping/6");
			{
				unsigned int result = rpc::VCall( stack, localObject.Get(), &Coordinator::ICoordinatorClientRemote::Ping, popResult); 
				call.Prepare(6).Push(result);
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
rpc::ILocalEntity* CreateLocalEntity(Coordinator::ICoordinatorClientRemote* api, rpc::IEntityMap* entityMap)
{
  return new Coordinator::LICoordinatorClientRemote(api, entityMap);
}

} // rpc

#pragma warning( pop )

NI_DEFINE_REFCOUNT( Coordinator::LICoordinatorClientRemote )


