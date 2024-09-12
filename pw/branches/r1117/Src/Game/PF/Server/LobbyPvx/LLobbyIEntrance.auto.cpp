#include "stdafx.h"
#include "LLobbyIEntrance.auto.h"

#pragma warning( push )
#pragma warning( disable : 4065 )

namespace lobby
{




    bool LIEntrance::vcall( byte method_id, rpc::MethodCall& call, rpc::MethodCallStack& stack )
    {
        bool popResult = true;
        switch ( method_id )
        {
			case 0: { NI_PROFILE_BLOCK("lobby::IEntrance::RequestServerInstance/0");
			{
				RIServerInstance* result = rpc::VCall( stack, localObject.Get(), &lobby::IEntrance::RequestServerInstance, popResult); 
				call.Prepare(0).Push(result);
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
rpc::ILocalEntity* CreateLocalEntity(lobby::IEntrance* api, rpc::IEntityMap* entityMap)
{
  return new lobby::LIEntrance(api, entityMap);
}

} // rpc

#pragma warning( pop )

NI_DEFINE_REFCOUNT( lobby::LIEntrance )


