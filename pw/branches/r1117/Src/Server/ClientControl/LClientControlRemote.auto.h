#ifndef __L_ClientControlRemote_H__
#define __L_ClientControlRemote_H__

#include <RPC/RPC.h>
#include <RPC/CppWrapper.h>
#include "ClientControlTypes.h"


#include "ClientControlRemote.h"

namespace clientCtl
{


class LIUserPresenceCallback : public rpc::ILocalEntity, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(LIUserPresenceCallback, rpc::ILocalEntity, BaseObjectMT);
public:
  LIUserPresenceCallback():entityMap(0) {}
  LIUserPresenceCallback(clientCtl::IUserPresenceCallback* _localObject, rpc::IEntityMap* _entityMap, rpc::ILocalEntityFactory* _factory=0)
  :   factory(_factory)
  ,   entityMap(_entityMap)
  ,   localObject(_localObject) 
  {
    localObject->SetOwner( this );
  }

  ~LIUserPresenceCallback() 
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
        { "clientCtl::IUserPresenceCallback::LetUserIn", 0, false, rpc::GetMethodCode(&clientCtl::IUserPresenceCallback::LetUserIn) },
        { "clientCtl::IUserPresenceCallback::DenyUser", 0, false, rpc::GetMethodCode(&clientCtl::IUserPresenceCallback::DenyUser) },
        { "clientCtl::IUserPresenceCallback::KickUser", 0, false, rpc::GetMethodCode(&clientCtl::IUserPresenceCallback::KickUser) },
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
  virtual void* _Get( uint classId ) { return (classId == rpc::_GetId("clientCtl::IUserPresenceCallback", rpc::GeneratedType) ) ? localObject : 0; }
  virtual uint GetClassCrc() const { return 0xe316fef5; }
  static uint GetClassCrcStatic() { return 0xe316fef5; }

  virtual int GetMemberIndex( const void* ) { return -1; }


private:
  StrongMT<clientCtl::IUserPresenceCallback> localObject;
  rpc::ILocalEntityFactory* factory;
  WeakMT<rpc::IEntityMap> entityMap;
  rpc::EntityId entityId;
};

}

namespace clientCtl
{


class LILoginSvcAllocationCallback : public rpc::ILocalEntity, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(LILoginSvcAllocationCallback, rpc::ILocalEntity, BaseObjectMT);
public:
  LILoginSvcAllocationCallback():entityMap(0) {}
  LILoginSvcAllocationCallback(clientCtl::ILoginSvcAllocationCallback* _localObject, rpc::IEntityMap* _entityMap, rpc::ILocalEntityFactory* _factory=0)
  :   factory(_factory)
  ,   entityMap(_entityMap)
  ,   localObject(_localObject) 
  {
    localObject->SetOwner( this );
  }

  ~LILoginSvcAllocationCallback() 
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
        { "clientCtl::ILoginSvcAllocationCallback::LoginSvcAllocated", 3, false, rpc::GetMethodCode(&clientCtl::ILoginSvcAllocationCallback::LoginSvcAllocated) },
        { "clientCtl::ILoginSvcAllocationCallback::LoginSvcAllocationFailed", 1, false, rpc::GetMethodCode(&clientCtl::ILoginSvcAllocationCallback::LoginSvcAllocationFailed) },
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
  virtual void* _Get( uint classId ) { return (classId == rpc::_GetId("clientCtl::ILoginSvcAllocationCallback", rpc::GeneratedType) ) ? localObject : 0; }
  virtual uint GetClassCrc() const { return 0x6ebffabd; }
  static uint GetClassCrcStatic() { return 0x6ebffabd; }

  virtual int GetMemberIndex( const void* ) { return -1; }


private:
  StrongMT<clientCtl::ILoginSvcAllocationCallback> localObject;
  rpc::ILocalEntityFactory* factory;
  WeakMT<rpc::IEntityMap> entityMap;
  rpc::EntityId entityId;
};

}



#endif // __L_ClientControlRemote_H__