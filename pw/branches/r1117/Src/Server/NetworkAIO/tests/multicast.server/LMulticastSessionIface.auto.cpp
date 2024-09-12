#include "stdafx.h"
#include "LMulticastSessionIface.auto.h"

#pragma warning( push )
#pragma warning( disable : 4065 )

namespace MulticastTest
{




    bool LIMulticastSession::vcall( byte method_id, rpc::MethodCall& call, rpc::MethodCallStack& stack )
    {
        bool popResult = true;
        switch ( method_id )
        {
			case 0: { NI_PROFILE_BLOCK("MulticastTest::IMulticastSession::ConfirmStep/0");rpc::VCall( stack, localObject.Get(), &MulticastTest::IMulticastSession::ConfirmStep, popResult); } break;

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
rpc::ILocalEntity* CreateLocalEntity(MulticastTest::IMulticastSession* api, rpc::IEntityMap* entityMap)
{
  return new MulticastTest::LIMulticastSession(api, entityMap);
}

} // rpc

#pragma warning( pop )

NI_DEFINE_REFCOUNT( MulticastTest::LIMulticastSession )


