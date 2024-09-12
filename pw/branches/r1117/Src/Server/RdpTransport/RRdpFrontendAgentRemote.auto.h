#ifndef __R_RdpFrontendAgentRemote_H__
#define __R_RdpFrontendAgentRemote_H__

#include <RPC/RPC.h>
#include "Network/TransportTypes.h"


#include "RdpFrontendAgentRemote.h"

namespace rdp_transport
{


class RIFrontendAgentRemote : public IFrontendAgentRemote, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(RIFrontendAgentRemote, IFrontendAgentRemote, BaseObjectMT);
public:
  RPC_INFO("rdp_transport::IFrontendAgentRemote", 0x25a1c629);
  
  RIFrontendAgentRemote() : handler(0) {}
  RIFrontendAgentRemote( rpc::EntityHandler* _handler, rpc::IRemoteEntity* _parent )
  :  handler(_handler)
  ,  parent(_parent)

  {

  }

  ~RIFrontendAgentRemote()
  {
    if( handler )
    {
      handler->OnDestruct(*this);
      handler = 0;
    }
  }
  virtual rpc::RemoteEntityInfo GetInfo() const { rpc::RemoteEntityInfo info = { handler->GetId(), { RIFrontendAgentRemote::ID(), RIFrontendAgentRemote::CRC32}, handler->GetGUID() }; return info; }
  inline bool IsUpdated() const { return handler->IsUpdated(); }
  rpc::EntityHandler* GetHandler() { return handler; }

  void UserPrepared(  Transport::TClientId _uid )
  {
    handler->Go(handler->Call( 0, _uid ));
  }
  void UserConnected(  Transport::TClientId _uid )
  {
    handler->Go(handler->Call( 1, _uid ));
  }
  void UserTimedOut(  Transport::TClientId _uid )
  {
    handler->Go(handler->Call( 2, _uid ));
  }
  void UserKicked(  Transport::TClientId _uid )
  {
    handler->Go(handler->Call( 3, _uid ));
  }
  void UserDropped(  Transport::TClientId _uid )
  {
    handler->Go(handler->Call( 4, _uid ));
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

  static uint GetClassCrcStatic() { return 0x25a1c629; }
protected:
  friend class rpc::Gate;




private:
  StrongMT<rpc::EntityHandler> handler;
  WeakMT<rpc::IRemoteEntity> parent;


};

}



#endif // __R_RdpFrontendAgentRemote_H__
