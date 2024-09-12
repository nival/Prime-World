#ifndef __L_RdpFrontendAgentRemote_H__
#define __L_RdpFrontendAgentRemote_H__

#include <RPC/RPC.h>
#include <RPC/CppWrapper.h>


#include "RdpFrontendAgentRemote.h"

namespace rdp_transport
{


class LIFrontendAgentRemote : public rpc::ILocalEntity, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(LIFrontendAgentRemote, rpc::ILocalEntity, BaseObjectMT);
public:
  LIFrontendAgentRemote():entityMap(0) {}
  LIFrontendAgentRemote(rdp_transport::IFrontendAgentRemote* _localObject, rpc::IEntityMap* _entityMap, rpc::ILocalEntityFactory* _factory=0)
  :   factory(_factory)
  ,   entityMap(_entityMap)
  ,   localObject(_localObject) 
  {
    localObject->SetOwner( this );
  }

  ~LIFrontendAgentRemote() 
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
        { "rdp_transport::IFrontendAgentRemote::UserPrepared", 1, false, rpc::GetMethodCode(&rdp_transport::IFrontendAgentRemote::UserPrepared) },
        { "rdp_transport::IFrontendAgentRemote::UserConnected", 1, false, rpc::GetMethodCode(&rdp_transport::IFrontendAgentRemote::UserConnected) },
        { "rdp_transport::IFrontendAgentRemote::UserTimedOut", 1, false, rpc::GetMethodCode(&rdp_transport::IFrontendAgentRemote::UserTimedOut) },
        { "rdp_transport::IFrontendAgentRemote::UserKicked", 1, false, rpc::GetMethodCode(&rdp_transport::IFrontendAgentRemote::UserKicked) },
        { "rdp_transport::IFrontendAgentRemote::UserDropped", 1, false, rpc::GetMethodCode(&rdp_transport::IFrontendAgentRemote::UserDropped) },
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
  virtual void* _Get( uint classId ) { return (classId == rpc::_GetId("rdp_transport::IFrontendAgentRemote", rpc::GeneratedType) ) ? localObject : 0; }
  virtual uint GetClassCrc() const { return 0x25a1c629; }
  static uint GetClassCrcStatic() { return 0x25a1c629; }

  virtual int GetMemberIndex( const void* ) { return -1; }


private:
  StrongMT<rdp_transport::IFrontendAgentRemote> localObject;
  rpc::ILocalEntityFactory* factory;
  WeakMT<rpc::IEntityMap> entityMap;
  rpc::EntityId entityId;
};

}



#endif // __L_RdpFrontendAgentRemote_H__