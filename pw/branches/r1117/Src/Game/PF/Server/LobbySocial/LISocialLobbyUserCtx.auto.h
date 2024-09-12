#ifndef __L_ISocialLobbyUserCtx_H__
#define __L_ISocialLobbyUserCtx_H__

#include <RPC/RPC.h>
#include <RPC/CppWrapper.h>
#include "SocialLobbyTypes.h"


#include "ISocialLobbyUserCtx.h"

namespace socialLobby
{


class LIUserContext : public rpc::ILocalEntity, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(LIUserContext, rpc::ILocalEntity, BaseObjectMT);
public:
  LIUserContext():entityMap(0) {}
  LIUserContext(socialLobby::IUserContext* _localObject, rpc::IEntityMap* _entityMap, rpc::ILocalEntityFactory* _factory=0)
  :   factory(_factory)
  ,   entityMap(_entityMap)
  ,   localObject(_localObject) 
  {
    localObject->SetOwner( this );
  }

  ~LIUserContext() 
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
        { "socialLobby::IUserContext::AcceptGameSession", 1, false, rpc::GetMethodCode(&socialLobby::IUserContext::AcceptGameSession) },
        { "socialLobby::IUserContext::ChangeGuardHero", 1, false, rpc::GetMethodCode(&socialLobby::IUserContext::ChangeGuardHero) },
        { "socialLobby::IUserContext::GuardReady", 0, false, rpc::GetMethodCode(&socialLobby::IUserContext::GuardReady) },
        { "socialLobby::IUserContext::ReconnectToGame", 0, false, rpc::GetMethodCode(&socialLobby::IUserContext::ReconnectToGame) },
        { "socialLobby::IUserContext::LeaveGame", 0, false, rpc::GetMethodCode(&socialLobby::IUserContext::LeaveGame) },
        { "socialLobby::IUserContext::CancelRequest", 0, false, rpc::GetMethodCode(&socialLobby::IUserContext::CancelRequest) },
        { "socialLobby::IUserContext::CancelPartyRequest", 0, false, rpc::GetMethodCode(&socialLobby::IUserContext::CancelPartyRequest) },
        { "socialLobby::IUserContext::EmergencyCancel", 0, false, rpc::GetMethodCode(&socialLobby::IUserContext::EmergencyCancel) },
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
  virtual void* _Get( uint classId ) { return (classId == rpc::_GetId("socialLobby::IUserContext", rpc::GeneratedType) ) ? localObject : 0; }
  virtual uint GetClassCrc() const { return 0x2797918c; }
  static uint GetClassCrcStatic() { return 0x2797918c; }

  virtual int GetMemberIndex( const void* ) { return -1; }


private:
  StrongMT<socialLobby::IUserContext> localObject;
  rpc::ILocalEntityFactory* factory;
  WeakMT<rpc::IEntityMap> entityMap;
  rpc::EntityId entityId;
};

}



#endif // __L_ISocialLobbyUserCtx_H__