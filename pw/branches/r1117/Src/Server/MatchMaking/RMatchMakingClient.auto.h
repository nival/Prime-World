#ifndef __R_MatchMakingClient_H__
#define __R_MatchMakingClient_H__

#include <RPC/RPC.h>
#include "RMatchMakingSessionIface.auto.h"
#include "HybridServer/RPeered.auto.h"




namespace MatchMaking
{


class RIClient : public rpc::IRemoteEntity, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(RIClient, rpc::IRemoteEntity, BaseObjectMT);
public:
  RPC_INFO("MatchMaking::IClient", 0x182b4caf);
  
  RIClient() : handler(0) {}
  RIClient( rpc::EntityHandler* _handler, rpc::IRemoteEntity* _parent )
  :  handler(_handler)
  ,  parent(_parent)

  {

  }

  ~RIClient()
  {
    if( handler )
    {
      handler->OnDestruct(*this);
      handler = 0;
    }
  }
  virtual rpc::RemoteEntityInfo GetInfo() const { rpc::RemoteEntityInfo info = { handler->GetId(), { RIClient::ID(), RIClient::CRC32}, handler->GetGUID() }; return info; }
  inline bool IsUpdated() const { return handler->IsUpdated(); }
  rpc::EntityHandler* GetHandler() { return handler; }

  void MatchMakingCompleted(  int res, SessionId sid, MatchMaking::ISession* session )
  {
    handler->Go(handler->Call( 0, res, sid, session ));
  }
  void OnSessionStarted(  Peered::IGameServer* gsrv )
  {
    handler->Go(handler->Call( 1, gsrv ));
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

  static uint GetClassCrcStatic() { return 0x182b4caf; }
protected:
  friend class rpc::Gate;




private:
  StrongMT<rpc::EntityHandler> handler;
  WeakMT<rpc::IRemoteEntity> parent;


};

}



#endif // __R_MatchMakingClient_H__
