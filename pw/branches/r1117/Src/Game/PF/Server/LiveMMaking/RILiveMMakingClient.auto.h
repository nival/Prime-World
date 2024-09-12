#ifndef __R_ILiveMMakingClient_H__
#define __R_ILiveMMakingClient_H__

#include <RPC/RPC.h>
#include "ILiveMMakingClient.h"


#include "ILiveMMakingClient.h"

namespace mmaking
{


class RILiveMMakingClient : public ILiveMMakingClient, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(RILiveMMakingClient, ILiveMMakingClient, BaseObjectMT);
public:
  RPC_INFO("mmaking::ILiveMMakingClient", 0xd0833daf);
  
  RILiveMMakingClient() : handler(0) {}
  RILiveMMakingClient( rpc::EntityHandler* _handler, rpc::IRemoteEntity* _parent )
  :  handler(_handler)
  ,  parent(_parent)

  {

  }

  ~RILiveMMakingClient()
  {
    if( handler )
    {
      handler->OnDestruct(*this);
      handler = 0;
    }
  }
  virtual rpc::RemoteEntityInfo GetInfo() const { rpc::RemoteEntityInfo info = { handler->GetId(), { RILiveMMakingClient::ID(), RILiveMMakingClient::CRC32}, handler->GetGUID() }; return info; }
  inline bool IsUpdated() const { return handler->IsUpdated(); }
  rpc::EntityHandler* GetHandler() { return handler; }

  void MmLogicSetupResult(  const Transport::TServiceId & _svcId, bool _result )
  {
    handler->Go(handler->Call( 0, _svcId, _result ));
  }
  void GameMatchmaked(  const SGame & _game )
  {
    handler->Go(handler->Call( 1, _game ));
  }
  void GameMatchmakedForReconnect(  const SReconnectSlot & _slot )
  {
    handler->Go(handler->Call( 2, _slot ));
  }
  void MmResultAddRequest(  TRequestUId _requestUId, bool _ok )
  {
    handler->Go(handler->Call( 3, _requestUId, _ok ));
  }
  void MmResultRemoveRequest(  TRequestUId _requestUId, bool _ok )
  {
    handler->Go(handler->Call( 4, _requestUId, _ok ));
  }
  void MmResultAddReconnectGame(  lobby::TGameId _gameId, bool _ok )
  {
    handler->Go(handler->Call( 5, _gameId, _ok ));
  }
  void MmResultRemoveReconnectGame(  lobby::TGameId _gameId, bool _ok )
  {
    handler->Go(handler->Call( 6, _gameId, _ok ));
  }
  void MmDebugStatus(  const char * _status )
  {
    handler->Go(handler->Call( 7, _status ));
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

  static uint GetClassCrcStatic() { return 0xd0833daf; }
protected:
  friend class rpc::Gate;




private:
  StrongMT<rpc::EntityHandler> handler;
  WeakMT<rpc::IRemoteEntity> parent;


};

}



#endif // __R_ILiveMMakingClient_H__
