#include "stdafx.h"
#include "LUserNotificationIface.auto.h"

#pragma warning( push )
#pragma warning( disable : 4065 )

namespace UserManager
{


	typedef void (UserManager::IUserNotificationSubscriber::*TOnUserLoggedIn)( UserInfo const * _uinfo);
	typedef void (UserManager::IUserNotificationSubscriber::*TOnUserLoggedOut)( UserInfo const * _uinfo);


    bool LIUserNotificationSubscriber::vcall( byte method_id, rpc::MethodCall& call, rpc::MethodCallStack& stack )
    {
        bool popResult = true;
        switch ( method_id )
        {
			case 0: { NI_PROFILE_BLOCK("UserManager::IUserNotificationSubscriber::OnUserLoggedIn/0");rpc::VCall( stack, localObject.Get(), TOnUserLoggedIn(&UserManager::IUserNotificationSubscriber::OnUserLoggedIn), popResult); } break;
			case 1: { NI_PROFILE_BLOCK("UserManager::IUserNotificationSubscriber::OnUserLoggedOut/1");rpc::VCall( stack, localObject.Get(), TOnUserLoggedOut(&UserManager::IUserNotificationSubscriber::OnUserLoggedOut), popResult); } break;

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
rpc::ILocalEntity* CreateLocalEntity(UserManager::IUserNotificationSubscriber* api, rpc::IEntityMap* entityMap)
{
  return new UserManager::LIUserNotificationSubscriber(api, entityMap);
}

} // rpc

#pragma warning( pop )

NI_DEFINE_REFCOUNT( UserManager::LIUserNotificationSubscriber )


#pragma warning( push )
#pragma warning( disable : 4065 )

namespace UserManager
{




    bool LIUserNotificationPublisher::vcall( byte method_id, rpc::MethodCall& call, rpc::MethodCallStack& stack )
    {
        bool popResult = true;
        switch ( method_id )
        {
			case 0: { NI_PROFILE_BLOCK("UserManager::IUserNotificationPublisher::RegisterSubscriber/0");
			{
				SubscriberIdT result = rpc::VCall( stack, localObject.Get(), &UserManager::IUserNotificationPublisher::RegisterSubscriber, popResult); 
				call.Prepare(0).PushByValue(result);
			}
			} break;
			case 1: { NI_PROFILE_BLOCK("UserManager::IUserNotificationPublisher::UnregisterSubscriber/1");rpc::VCall( stack, localObject.Get(), &UserManager::IUserNotificationPublisher::UnregisterSubscriber, popResult); } break;

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
rpc::ILocalEntity* CreateLocalEntity(UserManager::IUserNotificationPublisher* api, rpc::IEntityMap* entityMap)
{
  return new UserManager::LIUserNotificationPublisher(api, entityMap);
}

} // rpc

#pragma warning( pop )

NI_DEFINE_REFCOUNT( UserManager::LIUserNotificationPublisher )


