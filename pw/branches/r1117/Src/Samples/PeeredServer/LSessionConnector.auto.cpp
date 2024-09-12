#include "stdafx.h"
#include "LSessionConnector.auto.h"

#pragma warning( push )
#pragma warning( disable : 4065 )

namespace Peered
{




    bool LSessionConnector::vcall( byte method_id, rpc::MethodCall& call, rpc::MethodCallStack& stack )
    {
        bool popResult = true;
        switch ( method_id )
        {
			case 0: 
			{
				RIGameServer* result = rpc::VCall( stack, localObject.Get(), &Peered::SessionConnector::Connect, popResult); 
				call.Prepare(0).Push(result);
			}
			break;

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
rpc::ILocalEntity* CreateLocalEntity(Peered::SessionConnector* api)
{
  return new Peered::LSessionConnector(api);
}

} // rpc

#pragma warning( pop )

NI_DEFINE_REFCOUNT( Peered::LSessionConnector )


