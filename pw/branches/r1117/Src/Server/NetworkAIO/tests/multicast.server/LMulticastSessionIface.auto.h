#ifndef __L_MulticastSessionIface_H__
#define __L_MulticastSessionIface_H__

#include <RPC/RPC.h>
#include <RPC/CppWrapper.h>


#include "MulticastSessionIface.h"

namespace MulticastTest
{


class LIMulticastSession : public rpc::ILocalEntity, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(LIMulticastSession, rpc::ILocalEntity, BaseObjectMT);
public:
  LIMulticastSession():entityMap(0) {}
  LIMulticastSession(MulticastTest::IMulticastSession* _localObject, rpc::IEntityMap* _entityMap, rpc::ILocalEntityFactory* _factory=0)
  :   factory(_factory)
  ,   entityMap(_entityMap)
  ,   localObject(_localObject) 
  {
    localObject->SetOwner( this );
  }

  ~LIMulticastSession() 
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
  virtual void* _Get( uint classId ) { return (classId == rpc::_GetId("MulticastTest::IMulticastSession", rpc::GeneratedType) ) ? localObject : 0; }
  virtual uint GetClassCrc() const { return 0x737cd897; }
  static uint GetClassCrcStatic() { return 0x737cd897; }

  virtual int GetMemberIndex( const void* ) { return -1; }


private:
  StrongMT<MulticastTest::IMulticastSession> localObject;
  rpc::ILocalEntityFactory* factory;
  WeakMT<rpc::IEntityMap> entityMap;
  rpc::EntityId entityId;
};

}



#endif // __L_MulticastSessionIface_H__