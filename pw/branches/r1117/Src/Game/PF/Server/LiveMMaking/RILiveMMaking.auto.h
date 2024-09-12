#ifndef __R_ILiveMMaking_H__
#define __R_ILiveMMaking_H__

#include <RPC/RPC.h>
#include "ILiveMMaking.h"
#include "LiveMMakingTypes.h"
#include "RILiveMMakingClient.auto.h"


#include "ILiveMMaking.h"

namespace mmaking
{


class RILiveMMaking : public ILiveMMaking, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(RILiveMMaking, ILiveMMaking, BaseObjectMT);
public:
  RPC_INFO("mmaking::ILiveMMaking", 0xc03f7727);
  
  RILiveMMaking() : handler(0) {}
  RILiveMMaking( rpc::EntityHandler* _handler, rpc::IRemoteEntity* _parent )
  :  handler(_handler)
  ,  parent(_parent)

  {

  }

  ~RILiveMMaking()
  {
    if( handler )
    {
      handler->OnDestruct(*this);
      handler = 0;
    }
  }
  virtual rpc::RemoteEntityInfo GetInfo() const { rpc::RemoteEntityInfo info = { handler->GetId(), { RILiveMMaking::ID(), RILiveMMaking::CRC32}, handler->GetGUID() }; return info; }
  inline bool IsUpdated() const { return handler->IsUpdated(); }
  rpc::EntityHandler* GetHandler() { return handler; }

  void SetupLogic(  const string & _mapId, NI_LPTR ILiveMMakingClient* _client )
  {
    handler->Go(handler->Call( 0, _mapId, RemotePtr<RILiveMMakingClient>(_client) ));
  }
  void AddMmRequest(  TRequestUId _requestUId, const SRequestCommonData & _commonData, const vector<SRequestMember> & _members, timer::Time _waitTime )
  {
    handler->Go(handler->Call( 1, _requestUId, _commonData, _members, _waitTime ));
  }
  void RemoveMmRequest(  TRequestUId _requestUId )
  {
    handler->Go(handler->Call( 2, _requestUId ));
  }
  void AddGameForReconnect(  lobby::TGameId _gameId, const SGame & _gameData )
  {
    handler->Go(handler->Call( 3, _gameId, _gameData ));
  }
  void RemoveGame(  lobby::TGameId _gameId )
  {
    handler->Go(handler->Call( 4, _gameId ));
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

  static uint GetClassCrcStatic() { return 0xc03f7727; }
protected:
  friend class rpc::Gate;




private:
  StrongMT<rpc::EntityHandler> handler;
  WeakMT<rpc::IRemoteEntity> parent;


};

}



#endif // __R_ILiveMMaking_H__
