#ifndef __L_ISessionHybridLink_H__
#define __L_ISessionHybridLink_H__

#include <RPC/RPC.h>
#include <RPC/CppWrapper.h>


#include "ISessionHybridLink.h"

namespace lobby
{


class LISessionHybridLink : public rpc::ILocalEntity, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(LISessionHybridLink, rpc::ILocalEntity, BaseObjectMT);
public:
  LISessionHybridLink():entityMap(0) {}
  LISessionHybridLink(lobby::ISessionHybridLink* _localObject, rpc::IEntityMap* _entityMap, rpc::ILocalEntityFactory* _factory=0)
  :   factory(_factory)
  ,   entityMap(_entityMap)
  ,   localObject(_localObject) 
  {
    localObject->SetOwner( this );
  }

  ~LISessionHybridLink() 
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
        { "lobby::ISessionHybridLink::OnGameFinish", 4, false, rpc::GetMethodCode(&lobby::ISessionHybridLink::OnGameFinish) },
        { "lobby::ISessionHybridLink::OnGameCheated", 4, false, rpc::GetMethodCode(&lobby::ISessionHybridLink::OnGameCheated) },
        { "lobby::ISessionHybridLink::OnChangeClientStatus", 2, false, rpc::GetMethodCode(&lobby::ISessionHybridLink::OnChangeClientStatus) },
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
  virtual void* _Get( uint classId ) { return (classId == rpc::_GetId("lobby::ISessionHybridLink", rpc::GeneratedType) ) ? localObject : 0; }
  virtual uint GetClassCrc() const { return 0x7baf461f; }
  static uint GetClassCrcStatic() { return 0x7baf461f; }

  virtual int GetMemberIndex( const void* ) { return -1; }


private:
  StrongMT<lobby::ISessionHybridLink> localObject;
  rpc::ILocalEntityFactory* factory;
  WeakMT<rpc::IEntityMap> entityMap;
  rpc::EntityId entityId;
};

}



#endif // __L_ISessionHybridLink_H__