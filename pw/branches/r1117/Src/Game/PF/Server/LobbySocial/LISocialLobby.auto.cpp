#include "stdafx.h"
#include "LISocialLobby.auto.h"

#pragma warning( push )
#pragma warning( disable : 4065 )

namespace socialLobby
{


	typedef void (socialLobby::ISocialInterface::*TRegisterMmLogic)( const Transport::TServiceId* _svcId, NI_LPTR mmaking::ILiveMMaking* _logic, int _gameModes);
	typedef void (socialLobby::ISocialInterface::*TAddRequest)( const SMatchmakingRequest* _reqData, NI_LPTR INotify* _callback);
	typedef void (socialLobby::ISocialInterface::*TSpectate)( const SMatchmakingRequestCore* _reqData, TUId _targetUid, NI_LPTR INotify* _callback);


    bool LISocialInterface::vcall( byte method_id, rpc::MethodCall& call, rpc::MethodCallStack& stack )
    {
        bool popResult = true;
        switch ( method_id )
        {
			case 0: { NI_PROFILE_BLOCK("socialLobby::ISocialInterface::RegisterMmLogic/0");rpc::VCall( stack, localObject.Get(), TRegisterMmLogic(&socialLobby::ISocialInterface::RegisterMmLogic), popResult); } break;
			case 1: { NI_PROFILE_BLOCK("socialLobby::ISocialInterface::AddRequest/1");rpc::VCall( stack, localObject.Get(), TAddRequest(&socialLobby::ISocialInterface::AddRequest), popResult); } break;
			case 2: { NI_PROFILE_BLOCK("socialLobby::ISocialInterface::Spectate/2");rpc::VCall( stack, localObject.Get(), TSpectate(&socialLobby::ISocialInterface::Spectate), popResult); } break;
			case 3: { NI_PROFILE_BLOCK("socialLobby::ISocialInterface::GetRequest/3");rpc::VCall( stack, localObject.Get(), &socialLobby::ISocialInterface::GetRequest, popResult); } break;
			case 4: { NI_PROFILE_BLOCK("socialLobby::ISocialInterface::GetServerStatus/4");
			{
				SServerStatus result = rpc::VCall( stack, localObject.Get(), &socialLobby::ISocialInterface::GetServerStatus, popResult); 
				call.Prepare(4).PushByValue(result);
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
rpc::ILocalEntity* CreateLocalEntity(socialLobby::ISocialInterface* api, rpc::IEntityMap* entityMap)
{
  return new socialLobby::LISocialInterface(api, entityMap);
}

} // rpc

#pragma warning( pop )

NI_DEFINE_REFCOUNT( socialLobby::LISocialInterface )


#pragma warning( push )
#pragma warning( disable : 4065 )

namespace socialLobby
{


	typedef bool (socialLobby::IPvxInterface::*TPvxInstance)( NI_LPTR IPvxSvc* _pvx, const string* _clusterId, const Transport::TServiceId* _svcId, const PvxClusterSettings* _settings);
	typedef bool (socialLobby::IPvxInterface::*TUpdatePvxSettings)( const string* _clusterId, const Transport::TServiceId* _svcId, const PvxClusterSettings* _settings);
	typedef void (socialLobby::IPvxInterface::*TPvxInstanceLoadNotify)( const string* _clusterId, const Transport::TServiceId* _svcId, unsigned _load);
	typedef bool (socialLobby::IPvxInterface::*TPvXPreparedForUser)( TUserIdPvX _userId, const string * _key);


    bool LIPvxInterface::vcall( byte method_id, rpc::MethodCall& call, rpc::MethodCallStack& stack )
    {
        bool popResult = true;
        switch ( method_id )
        {
			case 0: { NI_PROFILE_BLOCK("socialLobby::IPvxInterface::PvxInstance/0");
			{
				bool result = rpc::VCall( stack, localObject.Get(), TPvxInstance(&socialLobby::IPvxInterface::PvxInstance), popResult); 
				call.Prepare(0).Push(result);
			}
			} break;
			case 1: { NI_PROFILE_BLOCK("socialLobby::IPvxInterface::UpdatePvxSettings/1");
			{
				bool result = rpc::VCall( stack, localObject.Get(), TUpdatePvxSettings(&socialLobby::IPvxInterface::UpdatePvxSettings), popResult); 
				call.Prepare(1).Push(result);
			}
			} break;
			case 2: { NI_PROFILE_BLOCK("socialLobby::IPvxInterface::PvxInstanceLoadNotify/2");rpc::VCall( stack, localObject.Get(), TPvxInstanceLoadNotify(&socialLobby::IPvxInterface::PvxInstanceLoadNotify), popResult); } break;
			case 3: { NI_PROFILE_BLOCK("socialLobby::IPvxInterface::PvXPreparedForUser/3");
			{
				bool result = rpc::VCall( stack, localObject.Get(), TPvXPreparedForUser(&socialLobby::IPvxInterface::PvXPreparedForUser), popResult); 
				call.Prepare(3).Push(result);
			}
			} break;
			case 4: { NI_PROFILE_BLOCK("socialLobby::IPvxInterface::UserEnteredPvX/4");
			{
				bool result = rpc::VCall( stack, localObject.Get(), &socialLobby::IPvxInterface::UserEnteredPvX, popResult); 
				call.Prepare(4).Push(result);
			}
			} break;
			case 5: { NI_PROFILE_BLOCK("socialLobby::IPvxInterface::UserDroppedFromPvX/5");
			{
				bool result = rpc::VCall( stack, localObject.Get(), &socialLobby::IPvxInterface::UserDroppedFromPvX, popResult); 
				call.Prepare(5).Push(result);
			}
			} break;
			case 6: { NI_PROFILE_BLOCK("socialLobby::IPvxInterface::GameFinished/6");
			{
				bool result = rpc::VCall( stack, localObject.Get(), &socialLobby::IPvxInterface::GameFinished, popResult); 
				call.Prepare(6).Push(result);
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
rpc::ILocalEntity* CreateLocalEntity(socialLobby::IPvxInterface* api, rpc::IEntityMap* entityMap)
{
  return new socialLobby::LIPvxInterface(api, entityMap);
}

} // rpc

#pragma warning( pop )

NI_DEFINE_REFCOUNT( socialLobby::LIPvxInterface )


#pragma warning( push )
#pragma warning( disable : 4065 )

namespace socialLobby
{




    bool LIDevSocLobby::vcall( byte method_id, rpc::MethodCall& call, rpc::MethodCallStack& stack )
    {
        bool popResult = true;
        switch ( method_id )
        {
			case 0: { NI_PROFILE_BLOCK("socialLobby::IDevSocLobby::AcquireUIdRange/0");
			{
				SDevUidRange result = rpc::VCall( stack, localObject.Get(), &socialLobby::IDevSocLobby::AcquireUIdRange, popResult); 
				call.Prepare(0).PushByValue(result);
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
rpc::ILocalEntity* CreateLocalEntity(socialLobby::IDevSocLobby* api, rpc::IEntityMap* entityMap)
{
  return new socialLobby::LIDevSocLobby(api, entityMap);
}

} // rpc

#pragma warning( pop )

NI_DEFINE_REFCOUNT( socialLobby::LIDevSocLobby )


