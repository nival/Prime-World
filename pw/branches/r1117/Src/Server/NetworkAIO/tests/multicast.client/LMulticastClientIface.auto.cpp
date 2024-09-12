#include "stdafx.h"
#include "LMulticastClientIface.auto.h"

#pragma warning( push )
#pragma warning( disable : 4065 )

namespace MulticastTest
{




    bool LIMulticastClient::vcall( byte method_id, rpc::MethodCall& call, rpc::MethodCallStack& stack )
    {
        bool popResult = true;
        switch ( method_id )
        {
			case 0: { NI_PROFILE_BLOCK("MulticastTest::IMulticastClient::Step/0");rpc::VCall( stack, localObject.Get(), &MulticastTest::IMulticastClient::Step, popResult); } break;
			case 1: { NI_PROFILE_BLOCK("MulticastTest::IMulticastClient::OnRegisterClient/1");rpc::VCall( stack, localObject.Get(), &MulticastTest::IMulticastClient::OnRegisterClient, popResult); } break;

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
rpc::ILocalEntity* CreateLocalEntity(MulticastTest::IMulticastClient* api, rpc::IEntityMap* entityMap)
{
  return new MulticastTest::LIMulticastClient(api, entityMap);
}

} // rpc

#pragma warning( pop )

NI_DEFINE_REFCOUNT( MulticastTest::LIMulticastClient )


