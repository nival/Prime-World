#ifndef __R_ISocialLobbyPvxSvc_H__
#define __R_ISocialLobbyPvxSvc_H__

#include <RPC/RPC.h>
#include "ISocialLobbyPvxSvc.h"
#include "RISocialLobbyPvxAck.auto.h"


#include "ISocialLobbyPvxSvc.h"

namespace socialLobby
{


class RIPvxSvc : public IPvxSvc, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(RIPvxSvc, IPvxSvc, BaseObjectMT);
public:
  RPC_INFO("socialLobby::IPvxSvc", 0xc2406604);
  
  RIPvxSvc() : handler(0) {}
  RIPvxSvc( rpc::EntityHandler* _handler, rpc::IRemoteEntity* _parent )
  :  handler(_handler)
  ,  parent(_parent)

  {

  }

  ~RIPvxSvc()
  {
    if( handler )
    {
      handler->OnDestruct(*this);
      handler = 0;
    }
  }
  virtual rpc::RemoteEntityInfo GetInfo() const { rpc::RemoteEntityInfo info = { handler->GetId(), { RIPvxSvc::ID(), RIPvxSvc::CRC32}, handler->GetGUID() }; return info; }
  inline bool IsUpdated() const { return handler->IsUpdated(); }
  rpc::EntityHandler* GetHandler() { return handler; }

  void NewGame(  lobby::TSocialGameId _gameId, const mmaking::SGame & _game, const PvxGameDetails & _gameDetails, NI_LPTR IPvxAcknowledge* _ack )
  {
    handler->Go(handler->Call( 0, _gameId, _game, _gameDetails, RemotePtr<RIPvxAcknowledge>(_ack) ));
  }
  void NewReconnectingUser(  lobby::TSocialGameId _gameId, TUserIdPvX _userId, NI_LPTR IPvxAcknowledge* _ack )
  {
    handler->Go(handler->Call( 1, _gameId, _userId, RemotePtr<RIPvxAcknowledge>(_ack) ));
  }
  void NewSpectator(  lobby::TSocialGameId _gameId, TUserIdPvX _userId, const string& _login, NI_LPTR IPvxAcknowledge* _ack, const wstring& nickname )
  {
    handler->Go(handler->Call( 2, _gameId, _userId, _login, RemotePtr<RIPvxAcknowledge>(_ack), nickname ));
  }
  void UserLeftTheGameInCastle(  lobby::TSocialGameId _gameId, TUserIdPvX _userId, NI_LPTR IPvxAcknowledge* _ack )
  {
    handler->Go(handler->Call( 3, _gameId, _userId, RemotePtr<RIPvxAcknowledge>(_ack) ));
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

  static uint GetClassCrcStatic() { return 0xc2406604; }
protected:
  friend class rpc::Gate;




private:
  StrongMT<rpc::EntityHandler> handler;
  WeakMT<rpc::IRemoteEntity> parent;


};

}



#endif // __R_ISocialLobbyPvxSvc_H__
