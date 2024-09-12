#include "stdafx.h"
#include "LPerfCounterProviderIface.auto.h"

#pragma warning( push )
#pragma warning( disable : 4065 )

namespace Monitoring
{




    bool LIPerfCounterProvider::vcall( byte method_id, rpc::MethodCall& call, rpc::MethodCallStack& stack )
    {
        bool popResult = true;
        switch ( method_id )
        {
			case 0: { NI_PROFILE_BLOCK("Monitoring::IPerfCounterProvider::GetPerfCountersList/0");
			{
				nstl::vector<nstl::string> result = rpc::VCall( stack, localObject.Get(), &Monitoring::IPerfCounterProvider::GetPerfCountersList, popResult); 
				call.Prepare(0).PushByValue(result);
			}
			} break;
			case 1: { NI_PROFILE_BLOCK("Monitoring::IPerfCounterProvider::GetPerfCounterSample/1");
			{
				PerfCounterSample result = rpc::VCall( stack, localObject.Get(), &Monitoring::IPerfCounterProvider::GetPerfCounterSample, popResult); 
				call.Prepare(1).PushByValue(result);
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
rpc::ILocalEntity* CreateLocalEntity(Monitoring::IPerfCounterProvider* api, rpc::IEntityMap* entityMap)
{
  return new Monitoring::LIPerfCounterProvider(api, entityMap);
}

} // rpc

#pragma warning( pop )

NI_DEFINE_REFCOUNT( Monitoring::LIPerfCounterProvider )


