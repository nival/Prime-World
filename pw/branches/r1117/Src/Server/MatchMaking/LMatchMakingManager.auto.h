#ifndef __L_MatchMakingManager_H__
#define __L_MatchMakingManager_H__

#include <RPC/RPC.h>
#include <RPC/CppWrapper.h>
#include "RMatchMakingClient.auto.h"


#include "MatchMakingManager.h"

namespace MatchMaking
{


class LManager : public rpc::ILocalEntity, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(LManager, rpc::ILocalEntity, BaseObjectMT);
public:
  LManager():entityMap(0) {}
  LManager(MatchMaking::Manager* _localObject, rpc::IEntityMap* _entityMap, rpc::ILocalEntityFactory* _factory=0)
  :   factory(_factory)
  ,   entityMap(_entityMap)
  ,   localObject(_localObject) 
  {
    localObject->SetOwner( this );
  }

  ~LManager() 
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
        { "MatchMaking::Manager::RequestMatchMaking", 1, false, rpc::GetMethodCode(&MatchMaking::Manager::RequestMatchMaking) },
        { "MatchMaking::Manager::CancelMatchMaking", 1, false, rpc::GetMethodCode(&MatchMaking::Manager::CancelMatchMaking) },
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
  virtual void* _Get( uint classId ) { return (classId == rpc::_GetId("MatchMaking::Manager", rpc::GeneratedType) ) ? localObject : 0; }
  virtual uint GetClassCrc() const { return 0x6d5faa85; }
  static uint GetClassCrcStatic() { return 0x6d5faa85; }

  virtual int GetMemberIndex( const void* ) { return -1; }


private:
  StrongMT<MatchMaking::Manager> localObject;
  rpc::ILocalEntityFactory* factory;
  WeakMT<rpc::IEntityMap> entityMap;
  rpc::EntityId entityId;
};

}



#endif // __L_MatchMakingManager_H__