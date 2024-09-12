#include "stdafx.h"
#include "LServiceAppearanceNotifierIface.auto.h"

#pragma warning( push )
#pragma warning( disable : 4065 )

namespace Coordinator
{


	typedef void (Coordinator::IServiceAppearanceSubscriber::*TOnRegisterSubscriber)( Coordinator::SubcriberIdT id, Coordinator::ClusterInfo const * cluster);
	typedef void (Coordinator::IServiceAppearanceSubscriber::*TOnRegisterService)( Transport::TServiceId const * svcid);
	typedef void (Coordinator::IServiceAppearanceSubscriber::*TOnUnregisterService)( Transport::TServiceId const * svcid);
	typedef void (Coordinator::IServiceAppearanceSubscriber::*TOnStartService)( SvcInfo const * ssi);
	typedef void (Coordinator::IServiceAppearanceSubscriber::*TOnStopService)( Transport::TServiceId const * svcid);
	typedef void (Coordinator::IServiceAppearanceSubscriber::*TOnChangeServiceStatus)( Transport::TServiceId const * _svcid, int _status);


    bool LIServiceAppearanceSubscriber::vcall( byte method_id, rpc::MethodCall& call, rpc::MethodCallStack& stack )
    {
        bool popResult = true;
        switch ( method_id )
        {
			case 0: { NI_PROFILE_BLOCK("Coordinator::IServiceAppearanceSubscriber::OnRegisterSubscriber/0");rpc::VCall( stack, localObject.Get(), TOnRegisterSubscriber(&Coordinator::IServiceAppearanceSubscriber::OnRegisterSubscriber), popResult); } break;
			case 1: { NI_PROFILE_BLOCK("Coordinator::IServiceAppearanceSubscriber::OnRegisterService/1");rpc::VCall( stack, localObject.Get(), TOnRegisterService(&Coordinator::IServiceAppearanceSubscriber::OnRegisterService), popResult); } break;
			case 2: { NI_PROFILE_BLOCK("Coordinator::IServiceAppearanceSubscriber::OnUnregisterService/2");rpc::VCall( stack, localObject.Get(), TOnUnregisterService(&Coordinator::IServiceAppearanceSubscriber::OnUnregisterService), popResult); } break;
			case 3: { NI_PROFILE_BLOCK("Coordinator::IServiceAppearanceSubscriber::OnStartService/3");rpc::VCall( stack, localObject.Get(), TOnStartService(&Coordinator::IServiceAppearanceSubscriber::OnStartService), popResult); } break;
			case 4: { NI_PROFILE_BLOCK("Coordinator::IServiceAppearanceSubscriber::OnStopService/4");rpc::VCall( stack, localObject.Get(), TOnStopService(&Coordinator::IServiceAppearanceSubscriber::OnStopService), popResult); } break;
			case 5: { NI_PROFILE_BLOCK("Coordinator::IServiceAppearanceSubscriber::OnChangeServiceStatus/5");rpc::VCall( stack, localObject.Get(), TOnChangeServiceStatus(&Coordinator::IServiceAppearanceSubscriber::OnChangeServiceStatus), popResult); } break;

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
rpc::ILocalEntity* CreateLocalEntity(Coordinator::IServiceAppearanceSubscriber* api, rpc::IEntityMap* entityMap)
{
  return new Coordinator::LIServiceAppearanceSubscriber(api, entityMap);
}

} // rpc

#pragma warning( pop )

NI_DEFINE_REFCOUNT( Coordinator::LIServiceAppearanceSubscriber )


#pragma warning( push )
#pragma warning( disable : 4065 )

namespace Coordinator
{


	typedef int (Coordinator::IServiceAppearancePublisher::*TSubscribe)( SubcriberIdT sid, Transport::TServiceId const * svcls);
	typedef void (Coordinator::IServiceAppearancePublisher::*TUnsubscribe)( SubcriberIdT sid, Transport::TServiceId const * svcls);


    bool LIServiceAppearancePublisher::vcall( byte method_id, rpc::MethodCall& call, rpc::MethodCallStack& stack )
    {
        bool popResult = true;
        switch ( method_id )
        {
			case 0: { NI_PROFILE_BLOCK("Coordinator::IServiceAppearancePublisher::RegisterSubscriber/0");rpc::VCall( stack, localObject.Get(), &Coordinator::IServiceAppearancePublisher::RegisterSubscriber, popResult); } break;
			case 1: { NI_PROFILE_BLOCK("Coordinator::IServiceAppearancePublisher::UnregisterSubscriber/1");rpc::VCall( stack, localObject.Get(), &Coordinator::IServiceAppearancePublisher::UnregisterSubscriber, popResult); } break;
			case 2: { NI_PROFILE_BLOCK("Coordinator::IServiceAppearancePublisher::Subscribe/2");
			{
				int result = rpc::VCall( stack, localObject.Get(), TSubscribe(&Coordinator::IServiceAppearancePublisher::Subscribe), popResult); 
				call.Prepare(2).Push(result);
			}
			} break;
			case 3: { NI_PROFILE_BLOCK("Coordinator::IServiceAppearancePublisher::Unsubscribe/3");rpc::VCall( stack, localObject.Get(), TUnsubscribe(&Coordinator::IServiceAppearancePublisher::Unsubscribe), popResult); } break;

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
rpc::ILocalEntity* CreateLocalEntity(Coordinator::IServiceAppearancePublisher* api, rpc::IEntityMap* entityMap)
{
  return new Coordinator::LIServiceAppearancePublisher(api, entityMap);
}

} // rpc

#pragma warning( pop )

NI_DEFINE_REFCOUNT( Coordinator::LIServiceAppearancePublisher )


