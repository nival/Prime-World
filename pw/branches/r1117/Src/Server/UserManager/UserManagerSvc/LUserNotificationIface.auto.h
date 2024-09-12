#ifndef __L_UserNotificationIface_H__
#define __L_UserNotificationIface_H__

#include <RPC/RPC.h>
#include <RPC/CppWrapper.h>


#include "UserNotificationIface.h"

namespace UserManager
{


class LIUserNotificationSubscriber : public rpc::ILocalEntity, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(LIUserNotificationSubscriber, rpc::ILocalEntity, BaseObjectMT);
public:
  LIUserNotificationSubscriber():entityMap(0) {}
  LIUserNotificationSubscriber(UserManager::IUserNotificationSubscriber* _localObject, rpc::IEntityMap* _entityMap, rpc::ILocalEntityFactory* _factory=0)
  :   factory(_factory)
  ,   entityMap(_entityMap)
  ,   localObject(_localObject) 
  {
    localObject->SetOwner( this );
  }

  ~LIUserNotificationSubscriber() 
  {
    if (factory)
    {
      factory->Destroy(this);
    }
  }
  
  virtual rpc::CallResult::Enum Call(const rpc::MethodCallHeader& call, rpc::MethodCall& resultCall, rpc::Arguments& args, const byte* paramsData, int _paramsSize)
  {
    entityId = resultCall.info.header.entityId;
    
    static const rpc::MethodInfo methods[] = 
    {
        { "UserManager::IUserNotificationSubscriber::OnUserLoggedIn", 1, false, rpc::GetMethodCode(&UserManager::IUserNotificationSubscriber::OnUserLoggedIn) },
        { "UserManager::IUserNotificationSubscriber::OnUserLoggedOut", 1, false, rpc::GetMethodCode(&UserManager::IUserNotificationSubscriber::OnUserLoggedOut) },
    };
    if (call.id >= sizeof(methods)/sizeof(rpc::MethodInfo) || call.id < 0)
    {
      return rpc::CallResult::WrongMethodId;
    }
    rpc::MethodCallStack stack = rpc::FillStack(call, args, paramsData, _paramsSize, methods[call.id]);
    if (true || stack.methodCode == methods[call.id].methodCode)
    {
      if ( !stack.isValid ) return rpc::CallResult::DataCorruption;
      return vcall(call.id, resultCall, stack) ? rpc::CallResult::OK : rpc::CallResult::StackCorruption;
    }
    else
    {
      return rpc::CallResult::WrongMethodCode;
    }
  }

  virtual void Publish()
  {
    StrongMT<rpc::IEntityMap> sentityMap = entityMap.Lock();
    if (sentityMap)
    {
      sentityMap->Publish( entityId, this );
    }
  }

  bool vcall( byte method_id, rpc::MethodCall& call, rpc::MethodCallStack& stack );
  virtual void* _Get( uint classId ) { return (classId == rpc::_GetId("UserManager::IUserNotificationSubscriber", rpc::GeneratedType) ) ? localObject : 0; }
  virtual uint GetClassCrc() const { return 0xcb42c19e; }
  static uint GetClassCrcStatic() { return 0xcb42c19e; }

  virtual int GetMemberIndex( const void* ) { return -1; }


private:
  StrongMT<UserManager::IUserNotificationSubscriber> localObject;
  rpc::ILocalEntityFactory* factory;
  WeakMT<rpc::IEntityMap> entityMap;
  rpc::EntityId entityId;
};

}

namespace UserManager
{


class LIUserNotificationPublisher : public rpc::ILocalEntity, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(LIUserNotificationPublisher, rpc::ILocalEntity, BaseObjectMT);
public:
  LIUserNotificationPublisher():entityMap(0) {}
  LIUserNotificationPublisher(UserManager::IUserNotificationPublisher* _localObject, rpc::IEntityMap* _entityMap, rpc::ILocalEntityFactory* _factory=0)
  :   factory(_factory)
  ,   entityMap(_entityMap)
  ,   localObject(_localObject) 
  {
    localObject->SetOwner( this );
  }

  ~LIUserNotificationPublisher() 
  {
    if (factory)
    {
      factory->Destroy(this);
    }
  }
  
  virtual rpc::CallResult::Enum Call(const rpc::MethodCallHeader& call, rpc::MethodCall& resultCall, rpc::Arguments& args, const byte* paramsData, int _paramsSize)
  {
    entityId = resultCall.info.header.entityId;
    
    static const rpc::MethodInfo methods[] = 
    {
        { "UserManager::IUserNotificationPublisher::RegisterSubscriber", 1, false, rpc::GetMethodCode(&UserManager::IUserNotificationPublisher::RegisterSubscriber) },
        { "UserManager::IUserNotificationPublisher::UnregisterSubscriber", 2, false, rpc::GetMethodCode(&UserManager::IUserNotificationPublisher::UnregisterSubscriber) },
    };
    if (call.id >= sizeof(methods)/sizeof(rpc::MethodInfo) || call.id < 0)
    {
      return rpc::CallResult::WrongMethodId;
    }
    rpc::MethodCallStack stack = rpc::FillStack(call, args, paramsData, _paramsSize, methods[call.id]);
    if (true || stack.methodCode == methods[call.id].methodCode)
    {
      if ( !stack.isValid ) return rpc::CallResult::DataCorruption;
      return vcall(call.id, resultCall, stack) ? rpc::CallResult::OK : rpc::CallResult::StackCorruption;
    }
    else
    {
      return rpc::CallResult::WrongMethodCode;
    }
  }

  virtual void Publish()
  {
    StrongMT<rpc::IEntityMap> sentityMap = entityMap.Lock();
    if (sentityMap)
    {
      sentityMap->Publish( entityId, this );
    }
  }

  bool vcall( byte method_id, rpc::MethodCall& call, rpc::MethodCallStack& stack );
  virtual void* _Get( uint classId ) { return (classId == rpc::_GetId("UserManager::IUserNotificationPublisher", rpc::GeneratedType) ) ? localObject : 0; }
  virtual uint GetClassCrc() const { return 0xf138219d; }
  static uint GetClassCrcStatic() { return 0xf138219d; }

  virtual int GetMemberIndex( const void* ) { return -1; }


private:
  StrongMT<UserManager::IUserNotificationPublisher> localObject;
  rpc::ILocalEntityFactory* factory;
  WeakMT<rpc::IEntityMap> entityMap;
  rpc::EntityId entityId;
};

}



#endif // __L_UserNotificationIface_H__