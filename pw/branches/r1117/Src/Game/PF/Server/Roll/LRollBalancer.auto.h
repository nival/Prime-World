#ifndef __L_RollBalancer_H__
#define __L_RollBalancer_H__

#include <RPC/RPC.h>
#include <RPC/CppWrapper.h>
#include "RRollInstance.auto.h"


#include "RollBalancer.h"

namespace roll
{


class LIBalancer : public rpc::ILocalEntity, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(LIBalancer, rpc::ILocalEntity, BaseObjectMT);
public:
  LIBalancer():entityMap(0) {}
  LIBalancer(roll::IBalancer* _localObject, rpc::IEntityMap* _entityMap, rpc::ILocalEntityFactory* _factory=0)
  :   factory(_factory)
  ,   entityMap(_entityMap)
  ,   localObject(_localObject) 
  {
    localObject->SetOwner( this );
  }

  ~LIBalancer() 
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
        { "roll::IBalancer::LoadNotify", 3, false, rpc::GetMethodCode(&roll::IBalancer::LoadNotify) },
        { "roll::IBalancer::AllocateInstance", 0, false, rpc::GetMethodCode(&roll::IBalancer::AllocateInstance) },
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
  virtual void* _Get( uint classId ) { return (classId == rpc::_GetId("roll::IBalancer", rpc::GeneratedType) ) ? localObject : 0; }
  virtual uint GetClassCrc() const { return 0x5b0ebe6; }
  static uint GetClassCrcStatic() { return 0x5b0ebe6; }

  virtual int GetMemberIndex( const void* ) { return -1; }


private:
  StrongMT<roll::IBalancer> localObject;
  rpc::ILocalEntityFactory* factory;
  WeakMT<rpc::IEntityMap> entityMap;
  rpc::EntityId entityId;
};

}



#endif // __L_RollBalancer_H__