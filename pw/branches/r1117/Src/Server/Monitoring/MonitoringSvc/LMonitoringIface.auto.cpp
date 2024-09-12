#include "stdafx.h"
#include "LMonitoringIface.auto.h"

#pragma warning( push )
#pragma warning( disable : 4065 )

namespace Monitoring
{


	typedef int (Monitoring::IMonitor::*TRegisterPerfCounter)( Transport::TServiceId const * _svcid, nstl::string const * _pcname, int _type, int _defaultUpdatePeriod, bool _toCumulate);
	typedef int (Monitoring::IMonitor::*TUnregisterPerfCounter)( Transport::TServiceId const * _svcid, nstl::string const * _pcname);


    bool LIMonitor::vcall( byte method_id, rpc::MethodCall& call, rpc::MethodCallStack& stack )
    {
        bool popResult = true;
        switch ( method_id )
        {
			case 0: { NI_PROFILE_BLOCK("Monitoring::IMonitor::RegisterPerfCounter/0");
			{
				int result = rpc::VCall( stack, localObject.Get(), TRegisterPerfCounter(&Monitoring::IMonitor::RegisterPerfCounter), popResult); 
				call.Prepare(0).Push(result);
			}
			} break;
			case 1: { NI_PROFILE_BLOCK("Monitoring::IMonitor::UnregisterPerfCounter/1");
			{
				int result = rpc::VCall( stack, localObject.Get(), TUnregisterPerfCounter(&Monitoring::IMonitor::UnregisterPerfCounter), popResult); 
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
rpc::ILocalEntity* CreateLocalEntity(Monitoring::IMonitor* api, rpc::IEntityMap* entityMap)
{
  return new Monitoring::LIMonitor(api, entityMap);
}

} // rpc

#pragma warning( pop )

NI_DEFINE_REFCOUNT( Monitoring::LIMonitor )


