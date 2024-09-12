#ifndef __L_ServiceAppearanceNotifierIface_H__
#define __L_ServiceAppearanceNotifierIface_H__

#include <RPC/RPC.h>
#include <RPC/CppWrapper.h>


#include "ServiceAppearanceNotifierIface.h"

namespace Coordinator
{


class LIServiceAppearanceSubscriber : public rpc::ILocalEntity, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(LIServiceAppearanceSubscriber, rpc::ILocalEntity, BaseObjectMT);
public:
  LIServiceAppearanceSubscriber():entityMap(0) {}
  LIServiceAppearanceSubscriber(Coordinator::IServiceAppearanceSubscriber* _localObject, rpc::IEntityMap* _entityMap, rpc::ILocalEntityFactory* _factory=0)
  :   factory(_factory)
  ,   entityMap(_entityMap)
  ,   localObject(_localObject) 
  {
    localObject->SetOwner( this );
  }

  ~LIServiceAppearanceSubscriber() 
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
        { "Coordinator::IServiceAppearanceSubscriber::OnRegisterSubscriber", 2, false, rpc::GetMethodCode(&Coordinator::IServiceAppearanceSubscriber::OnRegisterSubscriber) },
        { "Coordinator::IServiceAppearanceSubscriber::OnRegisterService", 1, false, rpc::GetMethodCode(&Coordinator::IServiceAppearanceSubscriber::OnRegisterService) },
        { "Coordinator::IServiceAppearanceSubscriber::OnUnregisterService", 1, false, rpc::GetMethodCode(&Coordinator::IServiceAppearanceSubscriber::OnUnregisterService) },
        { "Coordinator::IServiceAppearanceSubscriber::OnStartService", 1, false, rpc::GetMethodCode(&Coordinator::IServiceAppearanceSubscriber::OnStartService) },
        { "Coordinator::IServiceAppearanceSubscriber::OnStopService", 1, false, rpc::GetMethodCode(&Coordinator::IServiceAppearanceSubscriber::OnStopService) },
        { "Coordinator::IServiceAppearanceSubscriber::OnChangeServiceStatus", 2, false, rpc::GetMethodCode(&Coordinator::IServiceAppearanceSubscriber::OnChangeServiceStatus) },
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
  virtual void* _Get( uint classId ) { return (classId == rpc::_GetId("Coordinator::IServiceAppearanceSubscriber", rpc::GeneratedType) ) ? localObject : 0; }
  virtual uint GetClassCrc() const { return 0xe9090e2e; }
  static uint GetClassCrcStatic() { return 0xe9090e2e; }

  virtual int GetMemberIndex( const void* ) { return -1; }


private:
  StrongMT<Coordinator::IServiceAppearanceSubscriber> localObject;
  rpc::ILocalEntityFactory* factory;
  WeakMT<rpc::IEntityMap> entityMap;
  rpc::EntityId entityId;
};

}

namespace Coordinator
{


class LIServiceAppearancePublisher : public rpc::ILocalEntity, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(LIServiceAppearancePublisher, rpc::ILocalEntity, BaseObjectMT);
public:
  LIServiceAppearancePublisher():entityMap(0) {}
  LIServiceAppearancePublisher(Coordinator::IServiceAppearancePublisher* _localObject, rpc::IEntityMap* _entityMap, rpc::ILocalEntityFactory* _factory=0)
  :   factory(_factory)
  ,   entityMap(_entityMap)
  ,   localObject(_localObject) 
  {
    localObject->SetOwner( this );
  }

  ~LIServiceAppearancePublisher() 
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
        { "Coordinator::IServiceAppearancePublisher::RegisterSubscriber", 1, false, rpc::GetMethodCode(&Coordinator::IServiceAppearancePublisher::RegisterSubscriber) },
        { "Coordinator::IServiceAppearancePublisher::UnregisterSubscriber", 2, false, rpc::GetMethodCode(&Coordinator::IServiceAppearancePublisher::UnregisterSubscriber) },
        { "Coordinator::IServiceAppearancePublisher::Subscribe", 2, false, rpc::GetMethodCode(&Coordinator::IServiceAppearancePublisher::Subscribe) },
        { "Coordinator::IServiceAppearancePublisher::Unsubscribe", 2, false, rpc::GetMethodCode(&Coordinator::IServiceAppearancePublisher::Unsubscribe) },
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
  virtual void* _Get( uint classId ) { return (classId == rpc::_GetId("Coordinator::IServiceAppearancePublisher", rpc::GeneratedType) ) ? localObject : 0; }
  virtual uint GetClassCrc() const { return 0x2bcbbd5c; }
  static uint GetClassCrcStatic() { return 0x2bcbbd5c; }

  virtual int GetMemberIndex( const void* ) { return -1; }


private:
  StrongMT<Coordinator::IServiceAppearancePublisher> localObject;
  rpc::ILocalEntityFactory* factory;
  WeakMT<rpc::IEntityMap> entityMap;
  rpc::EntityId entityId;
};

}



#endif // __L_ServiceAppearanceNotifierIface_H__