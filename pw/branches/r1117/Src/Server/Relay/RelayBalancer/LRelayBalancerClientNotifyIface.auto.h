#ifndef __L_RelayBalancerClientNotifyIface_H__
#define __L_RelayBalancerClientNotifyIface_H__

#include <RPC/RPC.h>
#include <RPC/CppWrapper.h>


#include "RelayBalancerClientNotifyIface.h"

namespace Relay
{


class LIOutgoingClientNotifySink : public rpc::ILocalEntity, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(LIOutgoingClientNotifySink, rpc::ILocalEntity, BaseObjectMT);
public:
  LIOutgoingClientNotifySink():entityMap(0) {}
  LIOutgoingClientNotifySink(Relay::IOutgoingClientNotifySink* _localObject, rpc::IEntityMap* _entityMap, rpc::ILocalEntityFactory* _factory=0)
  :   factory(_factory)
  ,   entityMap(_entityMap)
  ,   localObject(_localObject) 
  {
    localObject->SetOwner( this );
  }

  ~LIOutgoingClientNotifySink() 
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
        { "Relay::IOutgoingClientNotifySink::OutgoingClientNotify", 2, false, rpc::GetMethodCode(&Relay::IOutgoingClientNotifySink::OutgoingClientNotify) },
        { "Relay::IOutgoingClientNotifySink::ClientConnectedNotify", 1, false, rpc::GetMethodCode(&Relay::IOutgoingClientNotifySink::ClientConnectedNotify) },
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
  virtual void* _Get( uint classId ) { return (classId == rpc::_GetId("Relay::IOutgoingClientNotifySink", rpc::GeneratedType) ) ? localObject : 0; }
  virtual uint GetClassCrc() const { return 0x7533a34d; }
  static uint GetClassCrcStatic() { return 0x7533a34d; }

  virtual int GetMemberIndex( const void* ) { return -1; }


private:
  StrongMT<Relay::IOutgoingClientNotifySink> localObject;
  rpc::ILocalEntityFactory* factory;
  WeakMT<rpc::IEntityMap> entityMap;
  rpc::EntityId entityId;
};

}

namespace Relay
{


class LIIncomingClientNotifySink : public rpc::ILocalEntity, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(LIIncomingClientNotifySink, rpc::ILocalEntity, BaseObjectMT);
public:
  LIIncomingClientNotifySink():entityMap(0) {}
  LIIncomingClientNotifySink(Relay::IIncomingClientNotifySink* _localObject, rpc::IEntityMap* _entityMap, rpc::ILocalEntityFactory* _factory=0)
  :   factory(_factory)
  ,   entityMap(_entityMap)
  ,   localObject(_localObject) 
  {
    localObject->SetOwner( this );
  }

  ~LIIncomingClientNotifySink() 
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
        { "Relay::IIncomingClientNotifySink::RegisterOutgoingClientNotifySink", 1, false, rpc::GetMethodCode(&Relay::IIncomingClientNotifySink::RegisterOutgoingClientNotifySink) },
        { "Relay::IIncomingClientNotifySink::IncomingClientNotify", 2, false, rpc::GetMethodCode(&Relay::IIncomingClientNotifySink::IncomingClientNotify) },
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
  virtual void* _Get( uint classId ) { return (classId == rpc::_GetId("Relay::IIncomingClientNotifySink", rpc::GeneratedType) ) ? localObject : 0; }
  virtual uint GetClassCrc() const { return 0x28bcd0b4; }
  static uint GetClassCrcStatic() { return 0x28bcd0b4; }

  virtual int GetMemberIndex( const void* ) { return -1; }


private:
  StrongMT<Relay::IIncomingClientNotifySink> localObject;
  rpc::ILocalEntityFactory* factory;
  WeakMT<rpc::IEntityMap> entityMap;
  rpc::EntityId entityId;
};

}



#endif // __L_RelayBalancerClientNotifyIface_H__