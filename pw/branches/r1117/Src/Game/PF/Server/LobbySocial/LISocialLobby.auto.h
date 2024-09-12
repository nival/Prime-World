#ifndef __L_ISocialLobby_H__
#define __L_ISocialLobby_H__

#include <RPC/RPC.h>
#include <RPC/CppWrapper.h>
#include "SocialLobbyTypes.h"


#include "ISocialLobby.h"

namespace socialLobby
{


class LISocialInterface : public rpc::ILocalEntity, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(LISocialInterface, rpc::ILocalEntity, BaseObjectMT);
public:
  LISocialInterface():entityMap(0) {}
  LISocialInterface(socialLobby::ISocialInterface* _localObject, rpc::IEntityMap* _entityMap, rpc::ILocalEntityFactory* _factory=0)
  :   factory(_factory)
  ,   entityMap(_entityMap)
  ,   localObject(_localObject) 
  {
    localObject->SetOwner( this );
  }

  ~LISocialInterface() 
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
        { "socialLobby::ISocialInterface::RegisterMmLogic", 3, false, rpc::GetMethodCode(&socialLobby::ISocialInterface::RegisterMmLogic) },
        { "socialLobby::ISocialInterface::AddRequest", 2, false, rpc::GetMethodCode(&socialLobby::ISocialInterface::AddRequest) },
        { "socialLobby::ISocialInterface::Spectate", 3, false, rpc::GetMethodCode(&socialLobby::ISocialInterface::Spectate) },
        { "socialLobby::ISocialInterface::GetRequest", 2, false, rpc::GetMethodCode(&socialLobby::ISocialInterface::GetRequest) },
        { "socialLobby::ISocialInterface::GetServerStatus", 0, false, rpc::GetMethodCode(&socialLobby::ISocialInterface::GetServerStatus) },
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
  virtual void* _Get( uint classId ) { return (classId == rpc::_GetId("socialLobby::ISocialInterface", rpc::GeneratedType) ) ? localObject : 0; }
  virtual uint GetClassCrc() const { return 0x2bb2959; }
  static uint GetClassCrcStatic() { return 0x2bb2959; }

  virtual int GetMemberIndex( const void* ) { return -1; }


private:
  StrongMT<socialLobby::ISocialInterface> localObject;
  rpc::ILocalEntityFactory* factory;
  WeakMT<rpc::IEntityMap> entityMap;
  rpc::EntityId entityId;
};

}

namespace socialLobby
{


class LIPvxInterface : public rpc::ILocalEntity, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(LIPvxInterface, rpc::ILocalEntity, BaseObjectMT);
public:
  LIPvxInterface():entityMap(0) {}
  LIPvxInterface(socialLobby::IPvxInterface* _localObject, rpc::IEntityMap* _entityMap, rpc::ILocalEntityFactory* _factory=0)
  :   factory(_factory)
  ,   entityMap(_entityMap)
  ,   localObject(_localObject) 
  {
    localObject->SetOwner( this );
  }

  ~LIPvxInterface() 
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
        { "socialLobby::IPvxInterface::PvxInstance", 4, false, rpc::GetMethodCode(&socialLobby::IPvxInterface::PvxInstance) },
        { "socialLobby::IPvxInterface::UpdatePvxSettings", 3, false, rpc::GetMethodCode(&socialLobby::IPvxInterface::UpdatePvxSettings) },
        { "socialLobby::IPvxInterface::PvxInstanceLoadNotify", 3, false, rpc::GetMethodCode(&socialLobby::IPvxInterface::PvxInstanceLoadNotify) },
        { "socialLobby::IPvxInterface::PvXPreparedForUser", 2, false, rpc::GetMethodCode(&socialLobby::IPvxInterface::PvXPreparedForUser) },
        { "socialLobby::IPvxInterface::UserEnteredPvX", 1, false, rpc::GetMethodCode(&socialLobby::IPvxInterface::UserEnteredPvX) },
        { "socialLobby::IPvxInterface::UserDroppedFromPvX", 2, false, rpc::GetMethodCode(&socialLobby::IPvxInterface::UserDroppedFromPvX) },
        { "socialLobby::IPvxInterface::GameFinished", 2, false, rpc::GetMethodCode(&socialLobby::IPvxInterface::GameFinished) },
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
  virtual void* _Get( uint classId ) { return (classId == rpc::_GetId("socialLobby::IPvxInterface", rpc::GeneratedType) ) ? localObject : 0; }
  virtual uint GetClassCrc() const { return 0x8925118f; }
  static uint GetClassCrcStatic() { return 0x8925118f; }

  virtual int GetMemberIndex( const void* ) { return -1; }


private:
  StrongMT<socialLobby::IPvxInterface> localObject;
  rpc::ILocalEntityFactory* factory;
  WeakMT<rpc::IEntityMap> entityMap;
  rpc::EntityId entityId;
};

}

namespace socialLobby
{


class LIDevSocLobby : public rpc::ILocalEntity, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(LIDevSocLobby, rpc::ILocalEntity, BaseObjectMT);
public:
  LIDevSocLobby():entityMap(0) {}
  LIDevSocLobby(socialLobby::IDevSocLobby* _localObject, rpc::IEntityMap* _entityMap, rpc::ILocalEntityFactory* _factory=0)
  :   factory(_factory)
  ,   entityMap(_entityMap)
  ,   localObject(_localObject) 
  {
    localObject->SetOwner( this );
  }

  ~LIDevSocLobby() 
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
        { "socialLobby::IDevSocLobby::AcquireUIdRange", 1, false, rpc::GetMethodCode(&socialLobby::IDevSocLobby::AcquireUIdRange) },
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
  virtual void* _Get( uint classId ) { return (classId == rpc::_GetId("socialLobby::IDevSocLobby", rpc::GeneratedType) ) ? localObject : 0; }
  virtual uint GetClassCrc() const { return 0xf1183b41; }
  static uint GetClassCrcStatic() { return 0xf1183b41; }

  virtual int GetMemberIndex( const void* ) { return -1; }


private:
  StrongMT<socialLobby::IDevSocLobby> localObject;
  rpc::ILocalEntityFactory* factory;
  WeakMT<rpc::IEntityMap> entityMap;
  rpc::EntityId entityId;
};

}



#endif // __L_ISocialLobby_H__