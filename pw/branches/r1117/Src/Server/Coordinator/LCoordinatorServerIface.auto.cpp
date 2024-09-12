#include "stdafx.h"
#include "LCoordinatorServerIface.auto.h"

#pragma warning( push )
#pragma warning( disable : 4065 )

namespace Coordinator
{




    bool LIRegisterClientCallback::vcall( byte method_id, rpc::MethodCall& call, rpc::MethodCallStack& stack )
    {
        bool popResult = true;
        switch ( method_id )
        {
			case 0: { NI_PROFILE_BLOCK("Coordinator::IRegisterClientCallback::OnRegisterClient/0");rpc::VCall( stack, localObject.Get(), &Coordinator::IRegisterClientCallback::OnRegisterClient, popResult); } break;

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
rpc::ILocalEntity* CreateLocalEntity(Coordinator::IRegisterClientCallback* api, rpc::IEntityMap* entityMap)
{
  return new Coordinator::LIRegisterClientCallback(api, entityMap);
}

} // rpc

#pragma warning( pop )

NI_DEFINE_REFCOUNT( Coordinator::LIRegisterClientCallback )


#pragma warning( push )
#pragma warning( disable : 4065 )

namespace Coordinator
{


	typedef void (Coordinator::ICoordinatorServerRemote::*TRegisterClient)( Coordinator::ServerIdT _clientid, NI_LPTR ICoordinatorClientRemote* _rptr, ServerDef const * _serverdef, NI_LPTR IRegisterClientCallback* _cb);
	typedef void (Coordinator::ICoordinatorServerRemote::*TServicesStarted)( ServicesStartInfo const * _info);
	typedef void (Coordinator::ICoordinatorServerRemote::*TStopService)( Transport::TServiceId const * _svcid);
	typedef void (Coordinator::ICoordinatorServerRemote::*TServiceStopped)( Transport::TServiceId const * _svcid);
	typedef void (Coordinator::ICoordinatorServerRemote::*TSoftStopService)( Transport::TServiceId const * _svcid);
	typedef void (Coordinator::ICoordinatorServerRemote::*TReloadConfig)( Transport::TServiceId const * _svcid);


    bool LICoordinatorServerRemote::vcall( byte method_id, rpc::MethodCall& call, rpc::MethodCallStack& stack )
    {
        bool popResult = true;
        switch ( method_id )
        {
			case 0: { NI_PROFILE_BLOCK("Coordinator::ICoordinatorServerRemote::RegisterClient/0");rpc::VCall( stack, localObject.Get(), TRegisterClient(&Coordinator::ICoordinatorServerRemote::RegisterClient), popResult); } break;
			case 1: { NI_PROFILE_BLOCK("Coordinator::ICoordinatorServerRemote::ServicesStarted/1");rpc::VCall( stack, localObject.Get(), TServicesStarted(&Coordinator::ICoordinatorServerRemote::ServicesStarted), popResult); } break;
			case 2: { NI_PROFILE_BLOCK("Coordinator::ICoordinatorServerRemote::Shutdown/2");rpc::VCall( stack, localObject.Get(), &Coordinator::ICoordinatorServerRemote::Shutdown, popResult); } break;
			case 3: { NI_PROFILE_BLOCK("Coordinator::ICoordinatorServerRemote::StopService/3");rpc::VCall( stack, localObject.Get(), TStopService(&Coordinator::ICoordinatorServerRemote::StopService), popResult); } break;
			case 4: { NI_PROFILE_BLOCK("Coordinator::ICoordinatorServerRemote::ServiceStopped/4");rpc::VCall( stack, localObject.Get(), TServiceStopped(&Coordinator::ICoordinatorServerRemote::ServiceStopped), popResult); } break;
			case 5: { NI_PROFILE_BLOCK("Coordinator::ICoordinatorServerRemote::SoftStopService/5");rpc::VCall( stack, localObject.Get(), TSoftStopService(&Coordinator::ICoordinatorServerRemote::SoftStopService), popResult); } break;
			case 6: { NI_PROFILE_BLOCK("Coordinator::ICoordinatorServerRemote::ReloadConfig/6");rpc::VCall( stack, localObject.Get(), TReloadConfig(&Coordinator::ICoordinatorServerRemote::ReloadConfig), popResult); } break;

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
rpc::ILocalEntity* CreateLocalEntity(Coordinator::ICoordinatorServerRemote* api, rpc::IEntityMap* entityMap)
{
  return new Coordinator::LICoordinatorServerRemote(api, entityMap);
}

} // rpc

#pragma warning( pop )

NI_DEFINE_REFCOUNT( Coordinator::LICoordinatorServerRemote )


