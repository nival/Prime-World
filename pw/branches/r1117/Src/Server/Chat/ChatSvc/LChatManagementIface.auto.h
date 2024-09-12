#ifndef __L_ChatManagementIface_H__
#define __L_ChatManagementIface_H__

#include <RPC/RPC.h>
#include <RPC/CppWrapper.h>


#include "ChatManagementIface.h"

namespace chat
{


class LIOpenSessionCallback : public rpc::ILocalEntity, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(LIOpenSessionCallback, rpc::ILocalEntity, BaseObjectMT);
public:
  LIOpenSessionCallback():entityMap(0) {}
  LIOpenSessionCallback(chat::IOpenSessionCallback* _localObject, rpc::IEntityMap* _entityMap, rpc::ILocalEntityFactory* _factory=0)
  :   factory(_factory)
  ,   entityMap(_entityMap)
  ,   localObject(_localObject) 
  {
    localObject->SetOwner( this );
  }

  ~LIOpenSessionCallback() 
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
        { "chat::IOpenSessionCallback::OnOpenSession", 2, false, rpc::GetMethodCode(&chat::IOpenSessionCallback::OnOpenSession) },
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
  virtual void* _Get( uint classId ) { return (classId == rpc::_GetId("chat::IOpenSessionCallback", rpc::GeneratedType) ) ? localObject : 0; }
  virtual uint GetClassCrc() const { return 0xf9cb56ad; }
  static uint GetClassCrcStatic() { return 0xf9cb56ad; }

  virtual int GetMemberIndex( const void* ) { return -1; }


private:
  StrongMT<chat::IOpenSessionCallback> localObject;
  rpc::ILocalEntityFactory* factory;
  WeakMT<rpc::IEntityMap> entityMap;
  rpc::EntityId entityId;
};

}

namespace chat
{


class LIOpenChannelCallback : public rpc::ILocalEntity, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(LIOpenChannelCallback, rpc::ILocalEntity, BaseObjectMT);
public:
  LIOpenChannelCallback():entityMap(0) {}
  LIOpenChannelCallback(chat::IOpenChannelCallback* _localObject, rpc::IEntityMap* _entityMap, rpc::ILocalEntityFactory* _factory=0)
  :   factory(_factory)
  ,   entityMap(_entityMap)
  ,   localObject(_localObject) 
  {
    localObject->SetOwner( this );
  }

  ~LIOpenChannelCallback() 
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
        { "chat::IOpenChannelCallback::OnOpenChannel", 4, false, rpc::GetMethodCode(&chat::IOpenChannelCallback::OnOpenChannel) },
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
  virtual void* _Get( uint classId ) { return (classId == rpc::_GetId("chat::IOpenChannelCallback", rpc::GeneratedType) ) ? localObject : 0; }
  virtual uint GetClassCrc() const { return 0x2d10ce14; }
  static uint GetClassCrcStatic() { return 0x2d10ce14; }

  virtual int GetMemberIndex( const void* ) { return -1; }


private:
  StrongMT<chat::IOpenChannelCallback> localObject;
  rpc::ILocalEntityFactory* factory;
  WeakMT<rpc::IEntityMap> entityMap;
  rpc::EntityId entityId;
};

}

namespace chat
{


class LIChatManagement : public rpc::ILocalEntity, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(LIChatManagement, rpc::ILocalEntity, BaseObjectMT);
public:
  LIChatManagement():entityMap(0) {}
  LIChatManagement(chat::IChatManagement* _localObject, rpc::IEntityMap* _entityMap, rpc::ILocalEntityFactory* _factory=0)
  :   factory(_factory)
  ,   entityMap(_entityMap)
  ,   localObject(_localObject) 
  {
    localObject->SetOwner( this );
  }

  ~LIChatManagement() 
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
        { "chat::IChatManagement::OpenSession", 2, false, rpc::GetMethodCode(&chat::IChatManagement::OpenSession) },
        { "chat::IChatManagement::CloseSession", 1, false, rpc::GetMethodCode(&chat::IChatManagement::CloseSession) },
        { "chat::IChatManagement::OpenChannel", 4, false, rpc::GetMethodCode(&chat::IChatManagement::OpenChannel) },
        { "chat::IChatManagement::CloseChannel", 2, false, rpc::GetMethodCode(&chat::IChatManagement::CloseChannel) },
        { "chat::IChatManagement::AddUser2Channel", 4, false, rpc::GetMethodCode(&chat::IChatManagement::AddUser2Channel) },
        { "chat::IChatManagement::RemoveUser", 3, false, rpc::GetMethodCode(&chat::IChatManagement::RemoveUser) },
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
  virtual void* _Get( uint classId ) { return (classId == rpc::_GetId("chat::IChatManagement", rpc::GeneratedType) ) ? localObject : 0; }
  virtual uint GetClassCrc() const { return 0x76a6e04a; }
  static uint GetClassCrcStatic() { return 0x76a6e04a; }

  virtual int GetMemberIndex( const void* ) { return -1; }


private:
  StrongMT<chat::IChatManagement> localObject;
  rpc::ILocalEntityFactory* factory;
  WeakMT<rpc::IEntityMap> entityMap;
  rpc::EntityId entityId;
};

}



#endif // __L_ChatManagementIface_H__