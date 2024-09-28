#ifndef __R_GameServerDispenserIface_H__
#define __R_GameServerDispenserIface_H__

#include <RPC/RPC.h>
#include "RPeered.auto.h"
#include "HybridServerNaming.h"
#include "Server/LobbyPvx/RISessionHybridLink.auto.h"


#include "GameServerDispenserIface.h"

namespace HybridServer
{


class RIGameServerDispenser : public IGameServerDispenser, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(RIGameServerDispenser, IGameServerDispenser, BaseObjectMT);
public:
  RPC_INFO("HybridServer::IGameServerDispenser", 0x2a20f981);
  
  RIGameServerDispenser() : handler(0) {}
  RIGameServerDispenser( rpc::EntityHandler* _handler, rpc::IRemoteEntity* _parent )
  :  handler(_handler)
  ,  parent(_parent)

  {

  }

  ~RIGameServerDispenser()
  {
    if( handler )
    {
      handler->OnDestruct(*this);
      handler = 0;
    }
  }
  virtual rpc::RemoteEntityInfo GetInfo() const { rpc::RemoteEntityInfo info = { handler->GetId(), { RIGameServerDispenser::ID(), RIGameServerDispenser::CRC32}, handler->GetGUID() }; return info; }
  inline bool IsUpdated() const { return handler->IsUpdated(); }
  rpc::EntityHandler* GetHandler() { return handler; }

  void AcquireNewServer(  const Peered::SAllocationParams& _params, NI_LPTR lobby::ISessionHybridLink* _session, NI_LPTR IGameServerDispenserCallback* _cb )
  {
    handler->Go(handler->Call( 0, _params, RemotePtr<lobby::RISessionHybridLink>(_session), RemotePtr<RIGameServerDispenserCallback>(_cb) ));
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

  static uint GetClassCrcStatic() { return 0x2a20f981; }
protected:
  friend class rpc::Gate;




private:
  StrongMT<rpc::EntityHandler> handler;
  WeakMT<rpc::IRemoteEntity> parent;


};

}

#include "GameServerDispenserIface.h"

namespace HybridServer
{


class RIGameServerDispenserCallback : public IGameServerDispenserCallback, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(RIGameServerDispenserCallback, IGameServerDispenserCallback, BaseObjectMT);
public:
  RPC_INFO("HybridServer::IGameServerDispenserCallback", 0xcc400da8);
  
  RIGameServerDispenserCallback() : handler(0) {}
  RIGameServerDispenserCallback( rpc::EntityHandler* _handler, rpc::IRemoteEntity* _parent )
  :  handler(_handler)
  ,  parent(_parent)

  {

  }

  ~RIGameServerDispenserCallback()
  {
    if( handler )
    {
      handler->OnDestruct(*this);
      handler = 0;
    }
  }
  virtual rpc::RemoteEntityInfo GetInfo() const { rpc::RemoteEntityInfo info = { handler->GetId(), { RIGameServerDispenserCallback::ID(), RIGameServerDispenserCallback::CRC32}, handler->GetGUID() }; return info; }
  inline bool IsUpdated() const { return handler->IsUpdated(); }
  rpc::EntityHandler* GetHandler() { return handler; }

  void GameServerAllocated(  Peered::RIGameServer* _clientsInterface, Peered::RIGameServerInternal* _internalInterface, const Peered::SInstanceId& _instId )
  {
    handler->Go(handler->Call( 0, _clientsInterface, _internalInterface, _instId ));
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

  static uint GetClassCrcStatic() { return 0xcc400da8; }
protected:
  friend class rpc::Gate;




private:
  StrongMT<rpc::EntityHandler> handler;
  WeakMT<rpc::IRemoteEntity> parent;


};

}



#endif // __R_GameServerDispenserIface_H__
