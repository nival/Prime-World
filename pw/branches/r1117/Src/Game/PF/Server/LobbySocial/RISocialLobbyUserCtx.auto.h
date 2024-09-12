#ifndef __R_ISocialLobbyUserCtx_H__
#define __R_ISocialLobbyUserCtx_H__

#include <RPC/RPC.h>


#include "ISocialLobbyUserCtx.h"

namespace socialLobby
{


class RIUserContext : public IUserContext, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(RIUserContext, IUserContext, BaseObjectMT);
public:
  RPC_INFO("socialLobby::IUserContext", 0x2797918c);
  
  RIUserContext() : handler(0) {}
  RIUserContext( rpc::EntityHandler* _handler, rpc::IRemoteEntity* _parent )
  :  handler(_handler)
  ,  parent(_parent)

  {

  }

  ~RIUserContext()
  {
    if( handler )
    {
      handler->OnDestruct(*this);
      handler = 0;
    }
  }
  virtual rpc::RemoteEntityInfo GetInfo() const { rpc::RemoteEntityInfo info = { handler->GetId(), { RIUserContext::ID(), RIUserContext::CRC32}, handler->GetGUID() }; return info; }
  inline bool IsUpdated() const { return handler->IsUpdated(); }
  rpc::EntityHandler* GetHandler() { return handler; }

  void AcceptGameSession(  const SPlayerData& _playerData )
  {
    handler->Go(handler->Call( 0, _playerData ));
  }
  void ChangeGuardHero(  const SPlayerData& _playerData )
  {
    handler->Go(handler->Call( 1, _playerData ));
  }
  void GuardReady( )
  {
    handler->Go(handler->Call( 2 ));
  }
  void ReconnectToGame( )
  {
    handler->Go(handler->Call( 3 ));
  }
  void LeaveGame( )
  {
    handler->Go(handler->Call( 4 ));
  }
  void CancelRequest( )
  {
    handler->Go(handler->Call( 5 ));
  }
  void CancelPartyRequest( )
  {
    handler->Go(handler->Call( 6 ));
  }
  void EmergencyCancel( )
  {
    handler->Go(handler->Call( 7 ));
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

  static uint GetClassCrcStatic() { return 0x2797918c; }
protected:
  friend class rpc::Gate;




private:
  StrongMT<rpc::EntityHandler> handler;
  WeakMT<rpc::IRemoteEntity> parent;


};

}



#endif // __R_ISocialLobbyUserCtx_H__
