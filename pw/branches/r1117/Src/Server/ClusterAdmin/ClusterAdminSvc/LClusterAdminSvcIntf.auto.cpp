#include "stdafx.h"
#include "LClusterAdminSvcIntf.auto.h"

#pragma warning( push )
#pragma warning( disable : 4065 )

namespace ClusterAdmin
{




    bool LIClusterAdmin::vcall( byte method_id, rpc::MethodCall& call, rpc::MethodCallStack& stack )
    {
        bool popResult = true;
        switch ( method_id )
        {
			case 0: { NI_PROFILE_BLOCK("ClusterAdmin::IClusterAdmin::Shutdown/0");rpc::VCall( stack, localObject.Get(), &ClusterAdmin::IClusterAdmin::Shutdown, popResult); } break;

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
rpc::ILocalEntity* CreateLocalEntity(ClusterAdmin::IClusterAdmin* api, rpc::IEntityMap* entityMap)
{
  return new ClusterAdmin::LIClusterAdmin(api, entityMap);
}

} // rpc

#pragma warning( pop )

NI_DEFINE_REFCOUNT( ClusterAdmin::LIClusterAdmin )


