#ifndef __L_SessionConnector_H__
#define __L_SessionConnector_H__

#include <RPC/RPC.h>
#include <RPC/CppWrapper.h>
#include "HybridServer/RPeered.auto.h"


#include "SessionConnector.h"

namespace Peered
{


class LSessionConnector : public rpc::ILocalEntity, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(LSessionConnector, rpc::ILocalEntity, BaseObjectMT);
public:
  LSessionConnector() {}
  LSessionConnector(Peered::SessionConnector* _localObject, rpc::ILocalEntityFactory* _factory=0 ):   
  localObject(_localObject),
  factory(_factory) 
  {
    localObject->SetOwner( this );
  }

  ~LSessionConnector()
  {
    if (factory)
    {
      factory->Destroy(this);
    }
  }
  
  virtual bool Call(const rpc::MethodCallHeader& call, rpc::MethodCall& resultCall, rpc::Arguments& args, const byte* paramsData, int _paramsSize)
  { 
    entityMap = args.GetEntityMap();
    entityId = resultCall.info.header.entityId;
    rpc::MethodCallStack stack = rpc::FillStack(call, args, paramsData, _paramsSize);
    return stack.isValid?vcall(call.id, resultCall, stack):false;
  }

  virtual void Publish()
  {
    entityMap->Publish( entityId, this );
  }

  bool vcall( byte method_id, rpc::MethodCall& call, rpc::MethodCallStack& stack );
  virtual void* _Get( uint classId ) { return (classId == rpc::_GetId("Peered::SessionConnector", rpc::GeneratedType) ) ? localObject : 0; }
  virtual uint GetClassCrc() const { return 0x4bb56ce; }

  virtual int GetMemberIndex( const void* ) { return -1; }


private:
  StrongMT<Peered::SessionConnector> localObject;
  rpc::ILocalEntityFactory* factory;
  rpc::EntityMap* entityMap;
  rpc::EntityId entityId;
};

}



#endif // __L_SessionConnector_H__