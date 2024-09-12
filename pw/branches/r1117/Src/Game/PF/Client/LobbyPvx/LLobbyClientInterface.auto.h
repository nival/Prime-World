#ifndef __L_LobbyClientInterface_H__
#define __L_LobbyClientInterface_H__

#include <RPC/RPC.h>
#include <RPC/CppWrapper.h>
#include "Game/PF/Server/LobbyPvx/CommonTypes.h"


#include "LobbyClientInterface.h"

namespace lobby
{


class LILobbyUser : public rpc::ILocalEntity, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(LILobbyUser, rpc::ILocalEntity, BaseObjectMT);
public:
  LILobbyUser():entityMap(0) {}
  LILobbyUser(lobby::ILobbyUser* _localObject, rpc::IEntityMap* _entityMap, rpc::ILocalEntityFactory* _factory=0)
  :   factory(_factory)
  ,   entityMap(_entityMap)
  ,   localObject(_localObject) 
  {
    localObject->SetOwner( this );
  }

  ~LILobbyUser() 
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
        { "lobby::ILobbyUser::AddGameInfo", 1, false, rpc::GetMethodCode(&lobby::ILobbyUser::AddGameInfo) },
        { "lobby::ILobbyUser::JoinCustomSession", 1, false, rpc::GetMethodCode(&lobby::ILobbyUser::JoinCustomSession) },
        { "lobby::ILobbyUser::UpdateClientStatus", 1, false, rpc::GetMethodCode(&lobby::ILobbyUser::UpdateClientStatus) },
        { "lobby::ILobbyUser::AddCustomGameMember", 1, false, rpc::GetMethodCode(&lobby::ILobbyUser::AddCustomGameMember) },
        { "lobby::ILobbyUser::RemoveCustomGameMember", 1, false, rpc::GetMethodCode(&lobby::ILobbyUser::RemoveCustomGameMember) },
        { "lobby::ILobbyUser::UpdateCustomGameMember", 2, false, rpc::GetMethodCode(&lobby::ILobbyUser::UpdateCustomGameMember) },
        { "lobby::ILobbyUser::UpdateCustomGameMemberReadiness", 2, false, rpc::GetMethodCode(&lobby::ILobbyUser::UpdateCustomGameMemberReadiness) },
        { "lobby::ILobbyUser::StartSession", 6, false, rpc::GetMethodCode(&lobby::ILobbyUser::StartSession) },
        { "lobby::ILobbyUser::Award", 1, false, rpc::GetMethodCode(&lobby::ILobbyUser::Award) },
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
  virtual void* _Get( uint classId ) { return (classId == rpc::_GetId("lobby::ILobbyUser", rpc::GeneratedType) ) ? localObject : 0; }
  virtual uint GetClassCrc() const { return 0x62dac159; }
  static uint GetClassCrcStatic() { return 0x62dac159; }

  virtual int GetMemberIndex( const void* ) { return -1; }


private:
  StrongMT<lobby::ILobbyUser> localObject;
  rpc::ILocalEntityFactory* factory;
  WeakMT<rpc::IEntityMap> entityMap;
  rpc::EntityId entityId;
};

}



#endif // __L_LobbyClientInterface_H__