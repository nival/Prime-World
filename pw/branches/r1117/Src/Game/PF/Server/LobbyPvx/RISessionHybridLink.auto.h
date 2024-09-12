#ifndef __R_ISessionHybridLink_H__
#define __R_ISessionHybridLink_H__

#include <RPC/RPC.h>
#include "ISessionHybridLink.h"


#include "ISessionHybridLink.h"

namespace lobby
{


class RISessionHybridLink : public ISessionHybridLink, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(RISessionHybridLink, ISessionHybridLink, BaseObjectMT);
public:
  RPC_INFO("lobby::ISessionHybridLink", 0x7baf461f);
  
  RISessionHybridLink() : handler(0) {}
  RISessionHybridLink( rpc::EntityHandler* _handler, rpc::IRemoteEntity* _parent )
  :  handler(_handler)
  ,  parent(_parent)

  {

  }

  ~RISessionHybridLink()
  {
    if( handler )
    {
      handler->OnDestruct(*this);
      handler = 0;
    }
  }
  virtual rpc::RemoteEntityInfo GetInfo() const { rpc::RemoteEntityInfo info = { handler->GetId(), { RISessionHybridLink::ID(), RISessionHybridLink::CRC32}, handler->GetGUID() }; return info; }
  inline bool IsUpdated() const { return handler->IsUpdated(); }
  rpc::EntityHandler* GetHandler() { return handler; }

  void OnGameFinish(  Peered::TSessionId _sessionId, int _gameResultType, const StatisticService::RPC::SessionClientResults & _finishInfo, const nstl::vector<Peered::SClientStatistics> & _clientsStatistics )
  {
    handler->Go(handler->Call( 0, _sessionId, _gameResultType, _finishInfo, _clientsStatistics ));
  }
  void OnGameCheated(  Peered::TSessionId _sessionId, Transport::TClientId _clientId, int _cheatType, const char * _clientIp )
  {
    handler->Go(handler->Call( 1, _sessionId, _clientId, _cheatType, _clientIp ));
  }
  void OnChangeClientStatus(  Peered::TSessionId _sessionId, const nstl::vector<Peered::BriefClientInfo> & _clientInfos )
  {
    handler->Go(handler->Call( 2, _sessionId, _clientInfos ));
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

  static uint GetClassCrcStatic() { return 0x7baf461f; }
protected:
  friend class rpc::Gate;




private:
  StrongMT<rpc::EntityHandler> handler;
  WeakMT<rpc::IRemoteEntity> parent;


};

}



#endif // __R_ISessionHybridLink_H__
