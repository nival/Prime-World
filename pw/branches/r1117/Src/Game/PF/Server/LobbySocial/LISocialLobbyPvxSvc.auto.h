#ifndef __L_ISocialLobbyPvxSvc_H__
#define __L_ISocialLobbyPvxSvc_H__

#include <RPC/RPC.h>
#include <RPC/CppWrapper.h>
#include "SocialLobbyTypes.h"


#include "ISocialLobbyPvxSvc.h"

namespace socialLobby
{


class LIPvxSvc : public rpc::ILocalEntity, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(LIPvxSvc, rpc::ILocalEntity, BaseObjectMT);
public:
  LIPvxSvc():entityMap(0) {}
  LIPvxSvc(socialLobby::IPvxSvc* _localObject, rpc::IEntityMap* _entityMap, rpc::ILocalEntityFactory* _factory=0)
  :   factory(_factory)
  ,   entityMap(_entityMap)
  ,   localObject(_localObject) 
  {
    localObject->SetOwner( this );
  }

  ~LIPvxSvc() 
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
        { "socialLobby::IPvxSvc::NewGame", 4, false, rpc::GetMethodCode(&socialLobby::IPvxSvc::NewGame) },
        { "socialLobby::IPvxSvc::NewReconnectingUser", 3, false, rpc::GetMethodCode(&socialLobby::IPvxSvc::NewReconnectingUser) },
        { "socialLobby::IPvxSvc::NewSpectator", 5, false, rpc::GetMethodCode(&socialLobby::IPvxSvc::NewSpectator) },
        { "socialLobby::IPvxSvc::UserLeftTheGameInCastle", 3, false, rpc::GetMethodCode(&socialLobby::IPvxSvc::UserLeftTheGameInCastle) },
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
  virtual void* _Get( uint classId ) { return (classId == rpc::_GetId("socialLobby::IPvxSvc", rpc::GeneratedType) ) ? localObject : 0; }
  virtual uint GetClassCrc() const { return 0xc2406604; }
  static uint GetClassCrcStatic() { return 0xc2406604; }

  virtual int GetMemberIndex( const void* ) { return -1; }


private:
  StrongMT<socialLobby::IPvxSvc> localObject;
  rpc::ILocalEntityFactory* factory;
  WeakMT<rpc::IEntityMap> entityMap;
  rpc::EntityId entityId;
};

}



#endif // __L_ISocialLobbyPvxSvc_H__