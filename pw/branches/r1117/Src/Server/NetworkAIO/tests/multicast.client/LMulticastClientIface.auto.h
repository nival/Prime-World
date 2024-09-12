#ifndef __L_MulticastClientIface_H__
#define __L_MulticastClientIface_H__

#include <RPC/RPC.h>
#include <RPC/CppWrapper.h>


#include "MulticastClientIface.h"

namespace MulticastTest
{


class LIMulticastClient : public rpc::ILocalEntity, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(LIMulticastClient, rpc::ILocalEntity, BaseObjectMT);
public:
  LIMulticastClient():entityMap(0) {}
  LIMulticastClient(MulticastTest::IMulticastClient* _localObject, rpc::IEntityMap* _entityMap, rpc::ILocalEntityFactory* _factory=0)
  :   factory(_factory)
  ,   entityMap(_entityMap)
  ,   localObject(_localObject) 
  {
    localObject->SetOwner( this );
  }

  ~LIMulticastClient() 
  {
    if (factory)
    {
      factory->Destroy(this);
    }
  }
  
  virtual bool Call(const rpc::MethodCallHeader& call, rpc::MethodCall& resultCall, rpc::Arguments& args, const byte* paramsData, int _paramsSize)
  {
    entityId = resultCall.info.header.entityId;
    rpc::MethodCallStack stack = rpc::FillStack(call, args, paramsData, _paramsSize);
    return stack.isValid?vcall(call.id, resultCall, stack):false;
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
  virtual void* _Get( uint classId ) { return (classId == rpc::_GetId("MulticastTest::IMulticastClient", rpc::GeneratedType) ) ? localObject : 0; }
  virtual uint GetClassCrc() const { return 0xe9e2bc81; }
  static uint GetClassCrcStatic() { return 0xe9e2bc81; }

  virtual int GetMemberIndex( const void* ) { return -1; }


private:
  StrongMT<MulticastTest::IMulticastClient> localObject;
  rpc::ILocalEntityFactory* factory;
  WeakMT<rpc::IEntityMap> entityMap;
  rpc::EntityId entityId;
};

}



#endif // __L_MulticastClientIface_H__