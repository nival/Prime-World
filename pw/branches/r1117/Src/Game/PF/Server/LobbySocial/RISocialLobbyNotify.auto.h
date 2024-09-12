#ifndef __R_ISocialLobbyNotify_H__
#define __R_ISocialLobbyNotify_H__

#include <RPC/RPC.h>
#include "ISocialLobbyNotify.h"
#include "RISocialLobbyUserCtx.auto.h"


#include "ISocialLobbyNotify.h"

namespace socialLobby
{


class RINotify : public INotify, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(RINotify, INotify, BaseObjectMT);
public:
  RPC_INFO("socialLobby::INotify", 0xc1877f4c);
  
  RINotify() : handler(0) {}
  RINotify( rpc::EntityHandler* _handler, rpc::IRemoteEntity* _parent )
  :  handler(_handler)
  ,  parent(_parent)

  {

  }

  ~RINotify()
  {
    if( handler )
    {
      handler->OnDestruct(*this);
      handler = 0;
    }
  }
  virtual rpc::RemoteEntityInfo GetInfo() const { rpc::RemoteEntityInfo info = { handler->GetId(), { RINotify::ID(), RINotify::CRC32}, handler->GetGUID() }; return info; }
  inline bool IsUpdated() const { return handler->IsUpdated(); }
  rpc::EntityHandler* GetHandler() { return handler; }

  void Open(  NI_LPTR IUserContext* _ctx )
  {
    handler->Go(handler->Call( 0, RemotePtr<RIUserContext>(_ctx) ));
  }
  void Failure( )
  {
    handler->Go(handler->Call( 1 ));
  }
  void UpdateStatus(  const SMatchmakingStatus& _status )
  {
    handler->Go(handler->Call( 2, _status ));
  }
  void Close( )
  {
    handler->Go(handler->Call( 3 ));
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

  static uint GetClassCrcStatic() { return 0xc1877f4c; }
protected:
  friend class rpc::Gate;




private:
  StrongMT<rpc::EntityHandler> handler;
  WeakMT<rpc::IRemoteEntity> parent;


};

}



#endif // __R_ISocialLobbyNotify_H__
