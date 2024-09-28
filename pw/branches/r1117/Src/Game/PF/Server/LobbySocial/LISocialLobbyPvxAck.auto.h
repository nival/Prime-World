#ifndef __L_ISocialLobbyPvxAck_H__
#define __L_ISocialLobbyPvxAck_H__

#include <RPC/RPC.h>
#include <RPC/CppWrapper.h>
#include "SocialLobbyTypes.h"


#include "ISocialLobbyPvxAck.h"

namespace socialLobby
{


class LIPvxAcknowledge : public rpc::ILocalEntity, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(LIPvxAcknowledge, rpc::ILocalEntity, BaseObjectMT);
public:
  LIPvxAcknowledge():entityMap(0) {}
  LIPvxAcknowledge(socialLobby::IPvxAcknowledge* _localObject, rpc::IEntityMap* _entityMap, rpc::ILocalEntityFactory* _factory=0)
  :   factory(_factory)
  ,   entityMap(_entityMap)
  ,   localObject(_localObject) 
  {
    localObject->SetOwner( this );
  }

  ~LIPvxAcknowledge() 
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
        { "socialLobby::IPvxAcknowledge::NewGameAck", 1, false, rpc::GetMethodCode(&socialLobby::IPvxAcknowledge::NewGameAck) },
        { "socialLobby::IPvxAcknowledge::NewReconnectingUserAck", 2, false, rpc::GetMethodCode(&socialLobby::IPvxAcknowledge::NewReconnectingUserAck) },
        { "socialLobby::IPvxAcknowledge::NewSpectatorAck", 2, false, rpc::GetMethodCode(&socialLobby::IPvxAcknowledge::NewSpectatorAck) },
        { "socialLobby::IPvxAcknowledge::UserLeftTheGameInCastleAck", 2, false, rpc::GetMethodCode(&socialLobby::IPvxAcknowledge::UserLeftTheGameInCastleAck) },
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
  virtual void* _Get( uint classId ) { return (classId == rpc::_GetId("socialLobby::IPvxAcknowledge", rpc::GeneratedType) ) ? localObject : 0; }
  virtual uint GetClassCrc() const { return 0x9f0475a; }
  static uint GetClassCrcStatic() { return 0x9f0475a; }

  virtual int GetMemberIndex( const void* ) { return -1; }


private:
  StrongMT<socialLobby::IPvxAcknowledge> localObject;
  rpc::ILocalEntityFactory* factory;
  WeakMT<rpc::IEntityMap> entityMap;
  rpc::EntityId entityId;
};

}



#endif // __L_ISocialLobbyPvxAck_H__