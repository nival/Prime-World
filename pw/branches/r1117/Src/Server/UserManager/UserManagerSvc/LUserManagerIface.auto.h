#ifndef __L_UserManagerIface_H__
#define __L_UserManagerIface_H__

#include <RPC/RPC.h>
#include <RPC/CppWrapper.h>


#include "UserManagerIface.h"

namespace UserManager
{


class LIPrepareUserEnvCallback : public rpc::ILocalEntity, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(LIPrepareUserEnvCallback, rpc::ILocalEntity, BaseObjectMT);
public:
  LIPrepareUserEnvCallback():entityMap(0) {}
  LIPrepareUserEnvCallback(UserManager::IPrepareUserEnvCallback* _localObject, rpc::IEntityMap* _entityMap, rpc::ILocalEntityFactory* _factory=0)
  :   factory(_factory)
  ,   entityMap(_entityMap)
  ,   localObject(_localObject) 
  {
    localObject->SetOwner( this );
  }

  ~LIPrepareUserEnvCallback() 
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
        { "UserManager::IPrepareUserEnvCallback::OnPrepareUserEnv", 4, false, rpc::GetMethodCode(&UserManager::IPrepareUserEnvCallback::OnPrepareUserEnv) },
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
  virtual void* _Get( uint classId ) { return (classId == rpc::_GetId("UserManager::IPrepareUserEnvCallback", rpc::GeneratedType) ) ? localObject : 0; }
  virtual uint GetClassCrc() const { return 0x25343c71; }
  static uint GetClassCrcStatic() { return 0x25343c71; }

  virtual int GetMemberIndex( const void* ) { return -1; }


private:
  StrongMT<UserManager::IPrepareUserEnvCallback> localObject;
  rpc::ILocalEntityFactory* factory;
  WeakMT<rpc::IEntityMap> entityMap;
  rpc::EntityId entityId;
};

}

namespace UserManager
{


class LIUserManager : public rpc::ILocalEntity, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(LIUserManager, rpc::ILocalEntity, BaseObjectMT);
public:
  LIUserManager():entityMap(0) {}
  LIUserManager(UserManager::IUserManager* _localObject, rpc::IEntityMap* _entityMap, rpc::ILocalEntityFactory* _factory=0)
  :   factory(_factory)
  ,   entityMap(_entityMap)
  ,   localObject(_localObject) 
  {
    localObject->SetOwner( this );
  }

  ~LIUserManager() 
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
        { "UserManager::IUserManager::AddUser", 4, false, rpc::GetMethodCode(&UserManager::IUserManager::AddUser) },
        { "UserManager::IUserManager::RemoveUser", 1, false, rpc::GetMethodCode(&UserManager::IUserManager::RemoveUser) },
        { "UserManager::IUserManager::FindUserSession", 2, false, rpc::GetMethodCode(&UserManager::IUserManager::FindUserSession) },
        { "UserManager::IUserManager::PrepareUserEnv", 2, false, rpc::GetMethodCode(&UserManager::IUserManager::PrepareUserEnv) },
        { "UserManager::IUserManager::OnUserLeave", 3, false, rpc::GetMethodCode(&UserManager::IUserManager::OnUserLeave) },
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
  virtual void* _Get( uint classId ) { return (classId == rpc::_GetId("UserManager::IUserManager", rpc::GeneratedType) ) ? localObject : 0; }
  virtual uint GetClassCrc() const { return 0x1fc1d3be; }
  static uint GetClassCrcStatic() { return 0x1fc1d3be; }

  virtual int GetMemberIndex( const void* ) { return -1; }


private:
  StrongMT<UserManager::IUserManager> localObject;
  rpc::ILocalEntityFactory* factory;
  WeakMT<rpc::IEntityMap> entityMap;
  rpc::EntityId entityId;
};

}



#endif // __L_UserManagerIface_H__