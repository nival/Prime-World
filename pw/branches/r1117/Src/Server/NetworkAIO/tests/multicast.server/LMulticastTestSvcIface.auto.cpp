#include "stdafx.h"
#include "LMulticastTestSvcIface.auto.h"

#pragma warning( push )
#pragma warning( disable : 4065 )

namespace MulticastTest
{




    bool LIMulticastSvc::vcall( byte method_id, rpc::MethodCall& call, rpc::MethodCallStack& stack )
    {
        bool popResult = true;
        switch ( method_id )
        {
			case 0: { NI_PROFILE_BLOCK("MulticastTest::IMulticastSvc::RegisterClient/0");
			{
				int result = rpc::VCall( stack, localObject.Get(), &MulticastTest::IMulticastSvc::RegisterClient, popResult); 
				call.Prepare(0).Push(result);
			}
			} break;
			case 1: { NI_PROFILE_BLOCK("MulticastTest::IMulticastSvc::ConfirmStep/1");rpc::VCall( stack, localObject.Get(), &MulticastTest::IMulticastSvc::ConfirmStep, popResult); } break;

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
rpc::ILocalEntity* CreateLocalEntity(MulticastTest::IMulticastSvc* api, rpc::IEntityMap* entityMap)
{
  return new MulticastTest::LIMulticastSvc(api, entityMap);
}

} // rpc

#pragma warning( pop )

NI_DEFINE_REFCOUNT( MulticastTest::LIMulticastSvc )


