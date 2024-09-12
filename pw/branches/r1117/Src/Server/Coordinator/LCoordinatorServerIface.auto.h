#ifndef __L_CoordinatorServerIface_H__
#define __L_CoordinatorServerIface_H__

#include <RPC/RPC.h>
#include <RPC/CppWrapper.h>


#include "CoordinatorServerIface.h"

namespace Coordinator
{


class LIRegisterClientCallback : public rpc::ILocalEntity, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(LIRegisterClientCallback, rpc::ILocalEntity, BaseObjectMT);
public:
  LIRegisterClientCallback():entityMap(0) {}
  LIRegisterClientCallback(Coordinator::IRegisterClientCallback* _localObject, rpc::IEntityMap* _entityMap, rpc::ILocalEntityFactory* _factory=0)
  :   factory(_factory)
  ,   entityMap(_entityMap)
  ,   localObject(_localObject) 
  {
    localObject->SetOwner( this );
  }

  ~LIRegisterClientCallback() 
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
        { "Coordinator::IRegisterClientCallback::OnRegisterClient", 2, false, rpc::GetMethodCode(&Coordinator::IRegisterClientCallback::OnRegisterClient) },
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
  virtual void* _Get( uint classId ) { return (classId == rpc::_GetId("Coordinator::IRegisterClientCallback", rpc::GeneratedType) ) ? localObject : 0; }
  virtual uint GetClassCrc() const { return 0x7bed6863; }
  static uint GetClassCrcStatic() { return 0x7bed6863; }

  virtual int GetMemberIndex( const void* ) { return -1; }


private:
  StrongMT<Coordinator::IRegisterClientCallback> localObject;
  rpc::ILocalEntityFactory* factory;
  WeakMT<rpc::IEntityMap> entityMap;
  rpc::EntityId entityId;
};

}

namespace Coordinator
{


class LICoordinatorServerRemote : public rpc::ILocalEntity, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(LICoordinatorServerRemote, rpc::ILocalEntity, BaseObjectMT);
public:
  LICoordinatorServerRemote():entityMap(0) {}
  LICoordinatorServerRemote(Coordinator::ICoordinatorServerRemote* _localObject, rpc::IEntityMap* _entityMap, rpc::ILocalEntityFactory* _factory=0)
  :   factory(_factory)
  ,   entityMap(_entityMap)
  ,   localObject(_localObject) 
  {
    localObject->SetOwner( this );
  }

  ~LICoordinatorServerRemote() 
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
        { "Coordinator::ICoordinatorServerRemote::RegisterClient", 4, false, rpc::GetMethodCode(&Coordinator::ICoordinatorServerRemote::RegisterClient) },
        { "Coordinator::ICoordinatorServerRemote::ServicesStarted", 1, false, rpc::GetMethodCode(&Coordinator::ICoordinatorServerRemote::ServicesStarted) },
        { "Coordinator::ICoordinatorServerRemote::Shutdown", 0, false, rpc::GetMethodCode(&Coordinator::ICoordinatorServerRemote::Shutdown) },
        { "Coordinator::ICoordinatorServerRemote::StopService", 1, false, rpc::GetMethodCode(&Coordinator::ICoordinatorServerRemote::StopService) },
        { "Coordinator::ICoordinatorServerRemote::ServiceStopped", 1, false, rpc::GetMethodCode(&Coordinator::ICoordinatorServerRemote::ServiceStopped) },
        { "Coordinator::ICoordinatorServerRemote::SoftStopService", 1, false, rpc::GetMethodCode(&Coordinator::ICoordinatorServerRemote::SoftStopService) },
        { "Coordinator::ICoordinatorServerRemote::ReloadConfig", 1, false, rpc::GetMethodCode(&Coordinator::ICoordinatorServerRemote::ReloadConfig) },
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
  virtual void* _Get( uint classId ) { return (classId == rpc::_GetId("Coordinator::ICoordinatorServerRemote", rpc::GeneratedType) ) ? localObject : 0; }
  virtual uint GetClassCrc() const { return 0x22f3542f; }
  static uint GetClassCrcStatic() { return 0x22f3542f; }

  virtual int GetMemberIndex( const void* ) { return -1; }


private:
  StrongMT<Coordinator::ICoordinatorServerRemote> localObject;
  rpc::ILocalEntityFactory* factory;
  WeakMT<rpc::IEntityMap> entityMap;
  rpc::EntityId entityId;
};

}



#endif // __L_CoordinatorServerIface_H__