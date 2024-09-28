#include "stdafx.h"
#include "LUserManagerIface.auto.h"

#pragma warning( push )
#pragma warning( disable : 4065 )

namespace UserManager
{


	typedef void (UserManager::IPrepareUserEnvCallback::*TOnPrepareUserEnv)( int _result, Cluster::TUserId _userid, RelayInfo const * _relayInfo, PartialReconnectInfo const * _partialReconnectInfo);


    bool LIPrepareUserEnvCallback::vcall( byte method_id, rpc::MethodCall& call, rpc::MethodCallStack& stack )
    {
        bool popResult = true;
        switch ( method_id )
        {
			case 0: { NI_PROFILE_BLOCK("UserManager::IPrepareUserEnvCallback::OnPrepareUserEnv/0");rpc::VCall( stack, localObject.Get(), TOnPrepareUserEnv(&UserManager::IPrepareUserEnvCallback::OnPrepareUserEnv), popResult); } break;

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
rpc::ILocalEntity* CreateLocalEntity(UserManager::IPrepareUserEnvCallback* api, rpc::IEntityMap* entityMap)
{
  return new UserManager::LIPrepareUserEnvCallback(api, entityMap);
}

} // rpc

#pragma warning( pop )

NI_DEFINE_REFCOUNT( UserManager::LIPrepareUserEnvCallback )


#pragma warning( push )
#pragma warning( disable : 4065 )

namespace UserManager
{


	typedef bool (UserManager::IUserManager::*TAddUser)( Cluster::TUserId _userId, string const * _sessionKey, Transport::TServiceId const * _sessionPath, wstring const * _username);
	typedef UserSessionInfo (UserManager::IUserManager::*TFindUserSession)( string const * _sessionKey, bool _partialReconnect);
	typedef Result::Enum (UserManager::IUserManager::*TPrepareUserEnv)( UserManager::UserEnvInfo const * uei, UserManager::IPrepareUserEnvCallback* cb);
	typedef bool (UserManager::IUserManager::*TOnUserLeave)( Cluster::TUserId _userId, Transport::TServiceId const * _svcid, Coordinator::TServiceRole const * _svcrole);


    bool LIUserManager::vcall( byte method_id, rpc::MethodCall& call, rpc::MethodCallStack& stack )
    {
        bool popResult = true;
        switch ( method_id )
        {
			case 0: { NI_PROFILE_BLOCK("UserManager::IUserManager::AddUser/0");
			{
				bool result = rpc::VCall( stack, localObject.Get(), TAddUser(&UserManager::IUserManager::AddUser), popResult); 
				call.Prepare(0).Push(result);
			}
			} break;
			case 1: { NI_PROFILE_BLOCK("UserManager::IUserManager::RemoveUser/1");
			{
				bool result = rpc::VCall( stack, localObject.Get(), &UserManager::IUserManager::RemoveUser, popResult); 
				call.Prepare(1).Push(result);
			}
			} break;
			case 2: { NI_PROFILE_BLOCK("UserManager::IUserManager::FindUserSession/2");
			{
				UserSessionInfo result = rpc::VCall( stack, localObject.Get(), TFindUserSession(&UserManager::IUserManager::FindUserSession), popResult); 
				call.Prepare(2).PushByValue(result);
			}
			} break;
			case 3: { NI_PROFILE_BLOCK("UserManager::IUserManager::PrepareUserEnv/3");
			{
				Result::Enum result = rpc::VCall( stack, localObject.Get(), TPrepareUserEnv(&UserManager::IUserManager::PrepareUserEnv), popResult); 
				call.Prepare(3).PushByValue(result);
			}
			} break;
			case 4: { NI_PROFILE_BLOCK("UserManager::IUserManager::OnUserLeave/4");
			{
				bool result = rpc::VCall( stack, localObject.Get(), TOnUserLeave(&UserManager::IUserManager::OnUserLeave), popResult); 
				call.Prepare(4).Push(result);
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
rpc::ILocalEntity* CreateLocalEntity(UserManager::IUserManager* api, rpc::IEntityMap* entityMap)
{
  return new UserManager::LIUserManager(api, entityMap);
}

} // rpc

#pragma warning( pop )

NI_DEFINE_REFCOUNT( UserManager::LIUserManager )


