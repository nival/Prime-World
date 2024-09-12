#ifndef __R_Peered_H__
#define __R_Peered_H__

#include <RPC/RPC.h>
#include "Peered.h"


#include "Peered.h"

namespace Peered
{


class RIGameClient : public IGameClient, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(RIGameClient, IGameClient, BaseObjectMT);
public:
  RPC_INFO("Peered::IGameClient", 0xcf716401);
  
  RIGameClient() : handler(0) {}
  RIGameClient( rpc::EntityHandler* _handler, rpc::IRemoteEntity* _parent )
  :  handler(_handler)
  ,  parent(_parent)

  {

  }

  ~RIGameClient()
  {
    if( handler )
    {
      handler->OnDestruct(*this);
      handler = 0;
    }
  }
  virtual rpc::RemoteEntityInfo GetInfo() const { rpc::RemoteEntityInfo info = { handler->GetId(), { RIGameClient::ID(), RIGameClient::CRC32}, handler->GetGUID() }; return info; }
  inline bool IsUpdated() const { return handler->IsUpdated(); }
  rpc::EntityHandler* GetHandler() { return handler; }

  void Start(  const ClientStartInfo& clientStartInfo, RIGameServerReconnect * gameServerReconnect )
  {
    handler->Go(handler->Call( 0, clientStartInfo, gameServerReconnect ));
  }
  void Step(  int step, int lastConfirmedStep, const nstl::vector<rpc::MemoryBlock>& commands, const nstl::vector<BriefClientInfo>& statuses, const nstl::vector<GapInfo>& clientGaps, const Transport::MessageMiscInfo& __miscInfo__ )
  {
    handler->Go(handler->Call( 1, step, lastConfirmedStep, commands, statuses, clientGaps ));
  }
  void StepLoading(  int step, int lastConfirmedStep, const nstl::vector<rpc::MemoryBlock>& commands, const nstl::vector<BriefClientInfo>& statuses, const nstl::vector<GapInfo>& clientGaps )
  {
    handler->Go(handler->Call( 2, step, lastConfirmedStep, commands, statuses, clientGaps ));
  }
  void StepBatch(  int lastConfirmedStep, const nstl::vector<ClientStepData>& stepData )
  {
    handler->Go(handler->Call( 3, lastConfirmedStep, stepData ));
  }
  void OnAsync(  int step, const nstl::vector<AsyncInfo>& async )
  {
    handler->Go(handler->Call( 4, step, async ));
  }
  void OnStart(  int step )
  {
    handler->Go(handler->Call( 5, step ));
  }
  void OnTimeScaleChanged(  float scale )
  {
    handler->Go(handler->Call( 6, scale ));
  }
  void OnChangeClientStatus(  const nstl::vector<BriefClientInfo>& clientStatuses )
  {
    handler->Go(handler->Call( 7, clientStatuses ));
  }
  void OnDisconnect(  int reason )
  {
    handler->Go(handler->Call( 8, reason ));
  }
  void OnRejoin(  uint clientId )
  {
    handler->Go(handler->Call( 9, clientId ));
  }
  void RequestWorldData(  RIGameServerReconnect * gameServerReconnect )
  {
    handler->Go(handler->Call( 10, gameServerReconnect ));
  }
  void RequestCrcData(  int step )
  {
    handler->Go(handler->Call( 11, step ));
  }
  void Award(  const vector<roll::SAwardInfo> & _awards )
  {
    handler->Go(handler->Call( 12, _awards ));
  }
  void OnSpectate(  const SpectatorInfo& info )
  {
    handler->Go(handler->Call( 13, info ));
  }
  void OnPlaySameTeamDecision(  const Transport::TClientId clientId, const bool agreed )
  {
    handler->Go(handler->Call( 14, clientId, agreed ));
  }
  void OnBadBehaviourComplaint(  const Transport::TClientId clientId, const Transport::TClientId reportedClientId, int reportItemId )
  {
    handler->Go(handler->Call( 15, clientId, reportedClientId, reportItemId ));
  }
  void OnProtectionAsync(  int step )
  {
    handler->Go(handler->Call( 16, step ));
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

  static uint GetClassCrcStatic() { return 0xcf716401; }
protected:
  friend class rpc::Gate;




private:
  StrongMT<rpc::EntityHandler> handler;
  WeakMT<rpc::IRemoteEntity> parent;


};

}

#include "Peered.h"

namespace Peered
{


class RIGameClientReconnect : public IGameClientReconnect, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(RIGameClientReconnect, IGameClientReconnect, BaseObjectMT);
public:
  RPC_INFO("Peered::IGameClientReconnect", 0xc334a3a4);
  
  RIGameClientReconnect() : handler(0) {}
  RIGameClientReconnect( rpc::EntityHandler* _handler, rpc::IRemoteEntity* _parent )
  :  handler(_handler)
  ,  parent(_parent)

  {

  }

  ~RIGameClientReconnect()
  {
    if( handler )
    {
      handler->OnDestruct(*this);
      handler = 0;
    }
  }
  virtual rpc::RemoteEntityInfo GetInfo() const { rpc::RemoteEntityInfo info = { handler->GetId(), { RIGameClientReconnect::ID(), RIGameClientReconnect::CRC32}, handler->GetGUID() }; return info; }
  inline bool IsUpdated() const { return handler->IsUpdated(); }
  rpc::EntityHandler* GetHandler() { return handler; }

  void ApplyWorldDataInfo(  const WorldDataInfo& worldDataInfo )
  {
    handler->Go(handler->Call( 0, worldDataInfo ));
  }
  void ApplyWorldDataPart(  const rpc::MemoryBlock& worldDataPart )
  {
    handler->Go(handler->Call( 1, worldDataPart ));
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

  static uint GetClassCrcStatic() { return 0xc334a3a4; }
protected:
  friend class rpc::Gate;




private:
  StrongMT<rpc::EntityHandler> handler;
  WeakMT<rpc::IRemoteEntity> parent;


};

}

#include "Peered.h"

namespace Peered
{


class RIGameServer : public IGameServer, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(RIGameServer, IGameServer, BaseObjectMT);
public:
  RPC_INFO("Peered::IGameServer", 0xeb8e44be);
  
  RIGameServer() : handler(0) {}
  RIGameServer( rpc::EntityHandler* _handler, rpc::IRemoteEntity* _parent )
  :  handler(_handler)
  ,  parent(_parent)

  {

  }

  ~RIGameServer()
  {
    if( handler )
    {
      handler->OnDestruct(*this);
      handler = 0;
    }
  }
  virtual rpc::RemoteEntityInfo GetInfo() const { rpc::RemoteEntityInfo info = { handler->GetId(), { RIGameServer::ID(), RIGameServer::CRC32}, handler->GetGUID() }; return info; }
  inline bool IsUpdated() const { return handler->IsUpdated(); }
  rpc::EntityHandler* GetHandler() { return handler; }

  void AddClient(  const char* name, uint clientId, const Login::ClientVersion& clientVersion, NI_LPTR IGameClient* _client )
  {
    handler->Go(handler->Call( 0, name, clientId, clientVersion, RemotePtr<RIGameClient>(_client) ));
  }
  void AddClientFast(  int clientId, int clientIndex, NI_LPTR IGameClient* _client, int fromStep )
  {
    handler->Go(handler->Call( 1, clientId, clientIndex, RemotePtr<RIGameClient>(_client), fromStep ));
  }
  void SendCommand(  int clientIndex, const rpc::MemoryBlock& command, bool isPlayerCommand )
  {
    handler->Go(handler->Call( 2, clientIndex, command, isPlayerCommand ));
  }
  void OnFinishStep(  int clientIndex, uint step, uint worldCrc )
  {
    handler->Go(handler->Call( 3, clientIndex, step, worldCrc ));
  }
  void OnClientReady(  int clientIndex )
  {
    handler->Go(handler->Call( 4, clientIndex ));
  }
  void SetTimeScale(  int clientIndex, float scale )
  {
    handler->Go(handler->Call( 5, clientIndex, scale ));
  }

  template <typename T>
  rpc::ECallResult::Enum Ping( SHybridPongResult& time_step, T* object, void (T::*func)(SHybridPongResult& result) )
  {           
    rpc::Transaction* transaction = handler->Call( 6, time_step );
    if (transaction)
    {
      transaction->RegisterAsyncCall( transaction->GetInfo(), new rpc::RefFunctorNoContext<T, SHybridPongResult>(object, func) );
      return handler->Go(transaction);
    }
    return rpc::ECallResult::NoTransaction;
  }
  

  template <typename T, typename C>
  rpc::ECallResult::Enum Ping( SHybridPongResult& time_step, T* object, void (T::*func)(SHybridPongResult& result, C context, rpc::CallStatus status), const C& context, float timeout=0.f)
  {           
    rpc::Transaction* transaction = handler->Call( 6, time_step );
    if (transaction)
    {
      transaction->RegisterAsyncCall( transaction->GetInfo(), new rpc::RefFunctorContext<T, SHybridPongResult, C>(object, func, context), timeout );
      return handler->Go(transaction);
    }
    return rpc::ECallResult::NoTransaction;
  }
  
  void OnGameFinish(  int clientIndex, int step, const StatisticService::RPC::SessionClientResults & finishInfo )
  {
    handler->Go(handler->Call( 7, clientIndex, step, finishInfo ));
  }
  void RequestWorldData(  int clientIndex )
  {
    handler->Go(handler->Call( 8, clientIndex ));
  }

  template <typename T>
  rpc::ECallResult::Enum OnGameLeave( int clientIndex, T* object, void (T::*func)(bool result) )
  {           
    rpc::Transaction* transaction = handler->Call( 9, clientIndex );
    if (transaction)
    {
      transaction->RegisterAsyncCall( transaction->GetInfo(), new rpc::FunctorNoContext<T, bool>(object, func) );
      return handler->Go(transaction);
    }
    return rpc::ECallResult::NoTransaction;
  }
  

  template <typename T, typename C>
  rpc::ECallResult::Enum OnGameLeave( int clientIndex, T* object, void (T::*func)(bool result, C context, rpc::CallStatus status), const C& context, float timeout=0.f)
  {           
    rpc::Transaction* transaction = handler->Call( 9, clientIndex );
    if (transaction)
    {
      transaction->RegisterAsyncCall( transaction->GetInfo(), new rpc::FunctorContext<T, bool, C>(object, func, context), timeout );
      return handler->Go(transaction);
    }
    return rpc::ECallResult::NoTransaction;
  }
  
  void SendCrcData(  int clientIndex, int step, const rpc::MemoryBlock& crcData )
  {
    handler->Go(handler->Call( 10, clientIndex, step, crcData ));
  }
  void OnDisconnectAck(  int clientIndex )
  {
    handler->Go(handler->Call( 11, clientIndex ));
  }
  void DispatchPlaySameTeamDecision(  int clientIndex, const bool agreed )
  {
    handler->Go(handler->Call( 12, clientIndex, agreed ));
  }
  void DispatchBadBehaviourComplaint(  int clientIndex, const Transport::TClientId reportedClientId, const int reportItemId )
  {
    handler->Go(handler->Call( 13, clientIndex, reportedClientId, reportItemId ));
  }
  void OnProtectionError(  int clientIndex )
  {
    handler->Go(handler->Call( 14, clientIndex ));
  }
  void SendProtectionMagic(  int clientIndex, int step, uint magic )
  {
    handler->Go(handler->Call( 15, clientIndex, step, magic ));
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

  static uint GetClassCrcStatic() { return 0xeb8e44be; }
protected:
  friend class rpc::Gate;




private:
  StrongMT<rpc::EntityHandler> handler;
  WeakMT<rpc::IRemoteEntity> parent;


};

}

#include "Peered.h"

namespace Peered
{


class RIGameServerInternal : public IGameServerInternal, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(RIGameServerInternal, IGameServerInternal, BaseObjectMT);
public:
  RPC_INFO("Peered::IGameServerInternal", 0xec13ccd2);
  
  RIGameServerInternal() : handler(0) {}
  RIGameServerInternal( rpc::EntityHandler* _handler, rpc::IRemoteEntity* _parent )
  :  handler(_handler)
  ,  parent(_parent)

  {

  }

  ~RIGameServerInternal()
  {
    if( handler )
    {
      handler->OnDestruct(*this);
      handler = 0;
    }
  }
  virtual rpc::RemoteEntityInfo GetInfo() const { rpc::RemoteEntityInfo info = { handler->GetId(), { RIGameServerInternal::ID(), RIGameServerInternal::CRC32}, handler->GetGUID() }; return info; }
  inline bool IsUpdated() const { return handler->IsUpdated(); }
  rpc::EntityHandler* GetHandler() { return handler; }


  template <typename T>
  rpc::ECallResult::Enum OnRejoinClient( uint clientId, T* object, void (T::*func)(bool result) )
  {           
    rpc::Transaction* transaction = handler->Call( 0, clientId );
    if (transaction)
    {
      transaction->RegisterAsyncCall( transaction->GetInfo(), new rpc::FunctorNoContext<T, bool>(object, func) );
      return handler->Go(transaction);
    }
    return rpc::ECallResult::NoTransaction;
  }
  

  template <typename T, typename C>
  rpc::ECallResult::Enum OnRejoinClient( uint clientId, T* object, void (T::*func)(bool result, C context, rpc::CallStatus status), const C& context, float timeout=0.f)
  {           
    rpc::Transaction* transaction = handler->Call( 0, clientId );
    if (transaction)
    {
      transaction->RegisterAsyncCall( transaction->GetInfo(), new rpc::FunctorContext<T, bool, C>(object, func, context), timeout );
      return handler->Go(transaction);
    }
    return rpc::ECallResult::NoTransaction;
  }
  
  void AddSpectator(  uint clientId, const wstring& nickname )
  {
    handler->Go(handler->Call( 1, clientId, nickname ));
  }
  void UserLeftTheGameInCastle(  uint clientId )
  {
    handler->Go(handler->Call( 2, clientId ));
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

  static uint GetClassCrcStatic() { return 0xec13ccd2; }
protected:
  friend class rpc::Gate;




private:
  StrongMT<rpc::EntityHandler> handler;
  WeakMT<rpc::IRemoteEntity> parent;


};

}

#include "Peered.h"

namespace Peered
{


class RIGameServerReconnect : public IGameServerReconnect, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(RIGameServerReconnect, IGameServerReconnect, BaseObjectMT);
public:
  RPC_INFO("Peered::IGameServerReconnect", 0x3bd049b8);
  
  RIGameServerReconnect() : handler(0) {}
  RIGameServerReconnect( rpc::EntityHandler* _handler, rpc::IRemoteEntity* _parent )
  :  handler(_handler)
  ,  parent(_parent)

  {

  }

  ~RIGameServerReconnect()
  {
    if( handler )
    {
      handler->OnDestruct(*this);
      handler = 0;
    }
  }
  virtual rpc::RemoteEntityInfo GetInfo() const { rpc::RemoteEntityInfo info = { handler->GetId(), { RIGameServerReconnect::ID(), RIGameServerReconnect::CRC32}, handler->GetGUID() }; return info; }
  inline bool IsUpdated() const { return handler->IsUpdated(); }
  rpc::EntityHandler* GetHandler() { return handler; }

  void SendWorldDataInfo(  int clientIndex, const WorldDataInfo& worldDataInfo )
  {
    handler->Go(handler->Call( 0, clientIndex, worldDataInfo ));
  }
  void SendWorldDataPart(  int clientIndex, const rpc::MemoryBlock& worldDataPart )
  {
    handler->Go(handler->Call( 1, clientIndex, worldDataPart ));
  }
  void SetGameClientReconnect(  int clientIndex, IGameClientReconnect * gameClientReconnect )
  {
    handler->Go(handler->Call( 2, clientIndex, gameClientReconnect ));
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

  static uint GetClassCrcStatic() { return 0x3bd049b8; }
protected:
  friend class rpc::Gate;




private:
  StrongMT<rpc::EntityHandler> handler;
  WeakMT<rpc::IRemoteEntity> parent;


};

}



#endif // __R_Peered_H__
