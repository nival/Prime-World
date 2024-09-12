#ifndef __L_LobbyAccounting_H__
#define __L_LobbyAccounting_H__

#include <RPC/RPC.h>
#include <RPC/CppWrapper.h>


#include "LobbyAccounting.h"

namespace Lobby
{


class LLobbyAccounting : public rpc::ILocalEntity, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(LLobbyAccounting, rpc::ILocalEntity, BaseObjectMT);
public:
  LLobbyAccounting():entityMap(0) {}
  LLobbyAccounting(Lobby::LobbyAccounting* _localObject, rpc::IEntityMap* _entityMap, rpc::ILocalEntityFactory* _factory=0)
  :   factory(_factory)
  ,   entityMap(_entityMap)
  ,   localObject(_localObject) 
  {
    localObject->SetOwner( this );
  }

  ~LLobbyAccounting() 
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
        { "Lobby::LobbyAccounting::BlockMoney", 2, false, rpc::GetMethodCode(&Lobby::LobbyAccounting::BlockMoney) },
        { "Lobby::LobbyAccounting::UnblockMoney", 2, false, rpc::GetMethodCode(&Lobby::LobbyAccounting::UnblockMoney) },
        { "Lobby::LobbyAccounting::GetServicePrice", 1, false, rpc::GetMethodCode(&Lobby::LobbyAccounting::GetServicePrice) },
        { "Lobby::LobbyAccounting::BuyBlockedService", 3, false, rpc::GetMethodCode(&Lobby::LobbyAccounting::BuyBlockedService) },
        { "Lobby::LobbyAccounting::BuyService", 2, false, rpc::GetMethodCode(&Lobby::LobbyAccounting::BuyService) },
        { "Lobby::LobbyAccounting::GetMoney", 1, false, rpc::GetMethodCode(&Lobby::LobbyAccounting::GetMoney) },
        { "Lobby::LobbyAccounting::GiveMoneyToUser", 3, false, rpc::GetMethodCode(&Lobby::LobbyAccounting::GiveMoneyToUser) },
        { "Lobby::LobbyAccounting::GetServices", 0, false, rpc::GetMethodCode(&Lobby::LobbyAccounting::GetServices) },
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
  virtual void* _Get( uint classId ) { return (classId == rpc::_GetId("Lobby::LobbyAccounting", rpc::GeneratedType) ) ? localObject : 0; }
  virtual uint GetClassCrc() const { return 0x925716e2; }
  static uint GetClassCrcStatic() { return 0x925716e2; }

  virtual int GetMemberIndex( const void* ) { return -1; }


private:
  StrongMT<Lobby::LobbyAccounting> localObject;
  rpc::ILocalEntityFactory* factory;
  WeakMT<rpc::IEntityMap> entityMap;
  rpc::EntityId entityId;
};

}



#endif // __L_LobbyAccounting_H__