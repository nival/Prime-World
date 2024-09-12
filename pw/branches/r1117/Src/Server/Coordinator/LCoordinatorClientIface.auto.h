#ifndef __L_CoordinatorClientIface_H__
#define __L_CoordinatorClientIface_H__

#include <RPC/RPC.h>
#include <RPC/CppWrapper.h>


#include "CoordinatorClientIface.h"

namespace Coordinator
{


class LICoordinatorClientRemote : public rpc::ILocalEntity, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(LICoordinatorClientRemote, rpc::ILocalEntity, BaseObjectMT);
public:
  LICoordinatorClientRemote():entityMap(0) {}
  LICoordinatorClientRemote(Coordinator::ICoordinatorClientRemote* _localObject, rpc::IEntityMap* _entityMap, rpc::ILocalEntityFactory* _factory=0)
  :   factory(_factory)
  ,   entityMap(_entityMap)
  ,   localObject(_localObject) 
  {
    localObject->SetOwner( this );
  }

  ~LICoordinatorClientRemote() 
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
        { "Coordinator::ICoordinatorClientRemote::AddRoute", 2, false, rpc::GetMethodCode(&Coordinator::ICoordinatorClientRemote::AddRoute) },
        { "Coordinator::ICoordinatorClientRemote::RemoveRoute", 1, false, rpc::GetMethodCode(&Coordinator::ICoordinatorClientRemote::RemoveRoute) },
        { "Coordinator::ICoordinatorClientRemote::StartService", 1, false, rpc::GetMethodCode(&Coordinator::ICoordinatorClientRemote::StartService) },
        { "Coordinator::ICoordinatorClientRemote::StopService", 1, false, rpc::GetMethodCode(&Coordinator::ICoordinatorClientRemote::StopService) },
        { "Coordinator::ICoordinatorClientRemote::SoftStopService", 1, false, rpc::GetMethodCode(&Coordinator::ICoordinatorClientRemote::SoftStopService) },
        { "Coordinator::ICoordinatorClientRemote::ReloadConfig", 1, false, rpc::GetMethodCode(&Coordinator::ICoordinatorClientRemote::ReloadConfig) },
        { "Coordinator::ICoordinatorClientRemote::Ping", 1, false, rpc::GetMethodCode(&Coordinator::ICoordinatorClientRemote::Ping) },
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
  virtual void* _Get( uint classId ) { return (classId == rpc::_GetId("Coordinator::ICoordinatorClientRemote", rpc::GeneratedType) ) ? localObject : 0; }
  virtual uint GetClassCrc() const { return 0x665c29fd; }
  static uint GetClassCrcStatic() { return 0x665c29fd; }

  virtual int GetMemberIndex( const void* ) { return -1; }


private:
  StrongMT<Coordinator::ICoordinatorClientRemote> localObject;
  rpc::ILocalEntityFactory* factory;
  WeakMT<rpc::IEntityMap> entityMap;
  rpc::EntityId entityId;
};

}



#endif // __L_CoordinatorClientIface_H__