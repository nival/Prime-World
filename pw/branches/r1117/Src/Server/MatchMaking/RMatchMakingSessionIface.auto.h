#ifndef __R_MatchMakingSessionIface_H__
#define __R_MatchMakingSessionIface_H__

#include <RPC/RPC.h>
#include "MatchMakingTypes.h"
#include "Game/PF/HybridServer/GameServerDispenserIface.h"


#include "MatchMakingSessionIface.h"

namespace MatchMaking
{


class RISession : public ISession, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(RISession, ISession, BaseObjectMT);
public:
  RPC_INFO("MatchMaking::ISession", 0xf4cd8a87);
  
  RISession() : handler(0) {}
  RISession( rpc::EntityHandler* _handler, rpc::IRemoteEntity* _parent )
  :  handler(_handler)
  ,  parent(_parent)

  {

  }

  ~RISession()
  {
    if( handler )
    {
      handler->OnDestruct(*this);
      handler = 0;
    }
  }
  virtual rpc::RemoteEntityInfo GetInfo() const { rpc::RemoteEntityInfo info = { handler->GetId(), { RISession::ID(), RISession::CRC32}, handler->GetGUID() }; return info; }
  inline bool IsUpdated() const { return handler->IsUpdated(); }
  rpc::EntityHandler* GetHandler() { return handler; }

  void PlayerReady(  MatchMaking::ClientId cid )
  {
    handler->Go(handler->Call( 0, cid ));
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

  static uint GetClassCrcStatic() { return 0xf4cd8a87; }
protected:
  friend class rpc::Gate;




private:
  StrongMT<rpc::EntityHandler> handler;
  WeakMT<rpc::IRemoteEntity> parent;


};

}



#endif // __R_MatchMakingSessionIface_H__
