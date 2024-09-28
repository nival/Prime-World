#ifndef __R_RdpFrontendAgentInterface_H__
#define __R_RdpFrontendAgentInterface_H__

#include <RPC/RPC.h>
#include "RdpFrontendAgentRemote.h"
#include "RRdpFrontendAgentRemote.auto.h"
#include "Network/TransportTypes.h"


#include "RdpFrontendAgentInterface.h"

namespace rdp_transport
{


class RIFrontendAgent : public IFrontendAgent, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(RIFrontendAgent, IFrontendAgent, BaseObjectMT);
public:
  RPC_INFO("rdp_transport::IFrontendAgent", 0x1ab6ab6a);
  
  RIFrontendAgent() : handler(0) {}
  RIFrontendAgent( rpc::EntityHandler* _handler, rpc::IRemoteEntity* _parent )
  :  handler(_handler)
  ,  parent(_parent)

  {

  }

  ~RIFrontendAgent()
  {
    if( handler )
    {
      handler->OnDestruct(*this);
      handler = 0;
    }
  }
  virtual rpc::RemoteEntityInfo GetInfo() const { rpc::RemoteEntityInfo info = { handler->GetId(), { RIFrontendAgent::ID(), RIFrontendAgent::CRC32}, handler->GetGUID() }; return info; }
  inline bool IsUpdated() const { return handler->IsUpdated(); }
  rpc::EntityHandler* GetHandler() { return handler; }

  void PrepareUser(  Transport::TClientId _uid, const string & _login, const string & _key, NI_LPTR IFrontendAgentRemote* _callback )
  {
    handler->Go(handler->Call( 0, _uid, _login, _key, RemotePtr<RIFrontendAgentRemote>(_callback) ));
  }
  void KickUser(  Transport::TClientId _uid )
  {
    handler->Go(handler->Call( 1, _uid ));
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
 
  StrongMT<rpc::INode> GetNode(int index) { return GetHandler()->GetNode(index); }
  StrongMT<rpc::INode> GetNode(const char* name) { return GetHandler()->GetNode(name); }
  virtual rpc::IUpdateCallback* GetUpdateCallback() { StrongMT<rpc::IRemoteEntity> _parent = parent.Lock(); return handler->GetUpdateCallback(_parent); }
  virtual void SetParent(rpc::IRemoteEntity* _parent) { parent = _parent; }
  virtual rpc::Status GetStatus() { return handler->GetStatus(); }

  static uint GetClassCrcStatic() { return 0x1ab6ab6a; }
protected:
  friend class rpc::Gate;




private:
  StrongMT<rpc::EntityHandler> handler;
  WeakMT<rpc::IRemoteEntity> parent;


};

}



#endif // __R_RdpFrontendAgentInterface_H__
