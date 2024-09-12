#ifndef __L_ILiveMMaking_H__
#define __L_ILiveMMaking_H__

#include <RPC/RPC.h>
#include <RPC/CppWrapper.h>
#include "RILiveMMaking.auto.h"


#include "ILiveMMaking.h"

namespace mmaking
{


class LILiveMMaking : public rpc::ILocalEntity, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(LILiveMMaking, rpc::ILocalEntity, BaseObjectMT);
public:
  LILiveMMaking():entityMap(0) {}
  LILiveMMaking(mmaking::ILiveMMaking* _localObject, rpc::IEntityMap* _entityMap, rpc::ILocalEntityFactory* _factory=0)
  :   factory(_factory)
  ,   entityMap(_entityMap)
  ,   localObject(_localObject) 
  {
    localObject->SetOwner( this );
  }

  ~LILiveMMaking() 
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
        { "mmaking::ILiveMMaking::SetupLogic", 2, false, rpc::GetMethodCode(&mmaking::ILiveMMaking::SetupLogic) },
        { "mmaking::ILiveMMaking::AddMmRequest", 4, false, rpc::GetMethodCode(&mmaking::ILiveMMaking::AddMmRequest) },
        { "mmaking::ILiveMMaking::RemoveMmRequest", 1, false, rpc::GetMethodCode(&mmaking::ILiveMMaking::RemoveMmRequest) },
        { "mmaking::ILiveMMaking::AddGameForReconnect", 2, false, rpc::GetMethodCode(&mmaking::ILiveMMaking::AddGameForReconnect) },
        { "mmaking::ILiveMMaking::RemoveGame", 1, false, rpc::GetMethodCode(&mmaking::ILiveMMaking::RemoveGame) },
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
  virtual void* _Get( uint classId ) { return (classId == rpc::_GetId("mmaking::ILiveMMaking", rpc::GeneratedType) ) ? localObject : 0; }
  virtual uint GetClassCrc() const { return 0xc03f7727; }
  static uint GetClassCrcStatic() { return 0xc03f7727; }

  virtual int GetMemberIndex( const void* ) { return -1; }


private:
  StrongMT<mmaking::ILiveMMaking> localObject;
  rpc::ILocalEntityFactory* factory;
  WeakMT<rpc::IEntityMap> entityMap;
  rpc::EntityId entityId;
};

}



#endif // __L_ILiveMMaking_H__