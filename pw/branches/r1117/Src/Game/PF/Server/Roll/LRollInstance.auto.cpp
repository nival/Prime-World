#include "stdafx.h"
#include "LRollInstance.auto.h"

#pragma warning( push )
#pragma warning( disable : 4065 )

namespace roll
{


	typedef void (roll::IInstance::*TRoll)( NI_LPTR IClient* client, const SPreGameData* preGame, const SPostGameData* postGame);
	typedef void (roll::IInstance::*TForgeRoll)( NI_LPTR IClient* client, const SForgeRollData * data);


    bool LIInstance::vcall( byte method_id, rpc::MethodCall& call, rpc::MethodCallStack& stack )
    {
        bool popResult = true;
        switch ( method_id )
        {
			case 0: { NI_PROFILE_BLOCK("roll::IInstance::Roll/0");rpc::VCall( stack, localObject.Get(), TRoll(&roll::IInstance::Roll), popResult); } break;
			case 1: { NI_PROFILE_BLOCK("roll::IInstance::ForgeRoll/1");rpc::VCall( stack, localObject.Get(), TForgeRoll(&roll::IInstance::ForgeRoll), popResult); } break;

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
rpc::ILocalEntity* CreateLocalEntity(roll::IInstance* api, rpc::IEntityMap* entityMap)
{
  return new roll::LIInstance(api, entityMap);
}

} // rpc

#pragma warning( pop )

NI_DEFINE_REFCOUNT( roll::LIInstance )


