#include "stdafx.h"
#include "LRollClient.auto.h"

#pragma warning( push )
#pragma warning( disable : 4065 )

namespace roll
{


	typedef void (roll::IClient::*TRollResults)( const vector<SUserAward>* _award);


    bool LIClient::vcall( byte method_id, rpc::MethodCall& call, rpc::MethodCallStack& stack )
    {
        bool popResult = true;
        switch ( method_id )
        {
			case 0: { NI_PROFILE_BLOCK("roll::IClient::RollResults/0");rpc::VCall( stack, localObject.Get(), TRollResults(&roll::IClient::RollResults), popResult); } break;
			case 1: { NI_PROFILE_BLOCK("roll::IClient::ForgeRollAck/1");rpc::VCall( stack, localObject.Get(), &roll::IClient::ForgeRollAck, popResult); } break;
			case 2: { NI_PROFILE_BLOCK("roll::IClient::RollFailed/2");rpc::VCall( stack, localObject.Get(), &roll::IClient::RollFailed, popResult); } break;

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
rpc::ILocalEntity* CreateLocalEntity(roll::IClient* api, rpc::IEntityMap* entityMap)
{
  return new roll::LIClient(api, entityMap);
}

} // rpc

#pragma warning( pop )

NI_DEFINE_REFCOUNT( roll::LIClient )


