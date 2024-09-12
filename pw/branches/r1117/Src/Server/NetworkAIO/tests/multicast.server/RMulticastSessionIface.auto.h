#ifndef __R_MulticastSessionIface_H__
#define __R_MulticastSessionIface_H__

#include <RPC/RPC.h>
#include "MulticastSessionIface.h"
#include "NetworkAIO/tests/multicast.server/RMulticastSessionIface.auto.h"




namespace MulticastTest
{


class RIMulticastSession : public rpc::IRemoteEntity, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(RIMulticastSession, rpc::IRemoteEntity, BaseObjectMT);
public:
  RPC_INFO("MulticastTest::IMulticastSession", 0x737cd897);
  
  RIMulticastSession() : handler(0) {}
  RIMulticastSession( rpc::EntityHandler* _handler, rpc::IRemoteEntity* _parent )
  :  handler(_handler)
  ,  parent(_parent)

  {

  }

  ~RIMulticastSession()
  {
    if( handler )
    {
      handler->OnDestruct(*this);
      handler = 0;
    }
  }
  virtual rpc::RemoteEntityInfo GetInfo() const { rpc::RemoteEntityInfo info = { handler->GetId(), { RIMulticastSession::ID(), RIMulticastSession::CRC32}, handler->GetGUID() }; return info; }
  inline bool IsUpdated() const { return handler->IsUpdated(); }
  rpc::EntityHandler* GetHandler() { return handler; }

  void ConfirmStep(  Transport::TClientId _cid, unsigned int _step )
  {
    handler->Go(handler->Call( 0, _cid, _step ));
  }



  bool Update(rpc::IUpdateCallback* callback=0)
  {
    return handler->Update(this, callback);
  }

  bool SetUpdateCallback(rpc::IUpdateCallback* callback=0)
  {
    return handler->SetUpdateCallback(callback);
  }

  void ReadOnly( bool val )
  {
    handler->ReadOnly( val );
  }

  void Publish()
  {
    handler->Publish();
  }
 
  rpc::INode* GetNode(int index) { return GetHandler()->GetNode(index); }
  rpc::INode* GetNode(const char* name) { return GetHandler()->GetNode(name); }
  virtual rpc::IUpdateCallback* GetUpdateCallback() { StrongMT<rpc::IRemoteEntity> _parent = parent.Lock(); return handler->GetUpdateCallback(_parent); }
  virtual void SetParent(rpc::IRemoteEntity* _parent) { parent = _parent; }
  virtual rpc::Status GetStatus() { return handler->GetStatus(); }

  static uint GetClassCrcStatic() { return 0x737cd897; }
protected:
  friend class rpc::Gate;




private:
  rpc::EntityHandler* handler;
  WeakMT<rpc::IRemoteEntity> parent;


};

}



#endif // __R_MulticastSessionIface_H__
