#ifndef __R_MulticastClientIface_H__
#define __R_MulticastClientIface_H__

#include <RPC/RPC.h>
#include "MulticastClientIface.h"


#include "MulticastClientIface.h"

namespace MulticastTest
{


class RIMulticastClient : public IMulticastClient, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(RIMulticastClient, IMulticastClient, BaseObjectMT);
public:
  RPC_INFO("MulticastTest::IMulticastClient", 0xe9e2bc81);
  
  RIMulticastClient() : handler(0) {}
  RIMulticastClient( rpc::EntityHandler* _handler, rpc::IRemoteEntity* _parent )
  :  handler(_handler)
  ,  parent(_parent)

  {

  }

  ~RIMulticastClient()
  {
    if( handler )
    {
      handler->OnDestruct(*this);
      handler = 0;
    }
  }
  virtual rpc::RemoteEntityInfo GetInfo() const { rpc::RemoteEntityInfo info = { handler->GetId(), { RIMulticastClient::ID(), RIMulticastClient::CRC32}, handler->GetGUID() }; return info; }
  inline bool IsUpdated() const { return handler->IsUpdated(); }
  rpc::EntityHandler* GetHandler() { return handler; }

  void Step(  int step )
  {
    handler->Go(handler->Call( 0, step ));
  }
  void OnRegisterClient(  RIMulticastSession* _session )
  {
    handler->Go(handler->Call( 1, _session ));
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

  static uint GetClassCrcStatic() { return 0xe9e2bc81; }
protected:
  friend class rpc::Gate;




private:
  rpc::EntityHandler* handler;
  WeakMT<rpc::IRemoteEntity> parent;


};

}



#endif // __R_MulticastClientIface_H__
