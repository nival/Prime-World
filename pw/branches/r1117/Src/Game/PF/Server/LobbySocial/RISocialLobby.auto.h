#ifndef __R_ISocialLobby_H__
#define __R_ISocialLobby_H__

#include <RPC/RPC.h>
#include "RISocialLobbyNotify.auto.h"
#include "RISocialLobbyPvxSvc.auto.h"
#include "Server/LiveMMaking/RILiveMMaking.auto.h"




namespace socialLobby
{


class RISocialInterface : public rpc::IRemoteEntity, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(RISocialInterface, rpc::IRemoteEntity, BaseObjectMT);
public:
  RPC_INFO("socialLobby::ISocialInterface", 0x2bb2959);
  
  RISocialInterface() : handler(0) {}
  RISocialInterface( rpc::EntityHandler* _handler, rpc::IRemoteEntity* _parent )
  :  handler(_handler)
  ,  parent(_parent)

  {

  }

  ~RISocialInterface()
  {
    if( handler )
    {
      handler->OnDestruct(*this);
      handler = 0;
    }
  }
  virtual rpc::RemoteEntityInfo GetInfo() const { rpc::RemoteEntityInfo info = { handler->GetId(), { RISocialInterface::ID(), RISocialInterface::CRC32}, handler->GetGUID() }; return info; }
  inline bool IsUpdated() const { return handler->IsUpdated(); }
  rpc::EntityHandler* GetHandler() { return handler; }

  void RegisterMmLogic(  const Transport::TServiceId& _svcId, NI_LPTR mmaking::ILiveMMaking* _logic, int _gameModes )
  {
    handler->Go(handler->Call( 0, _svcId, RemotePtr<mmaking::RILiveMMaking>(_logic), _gameModes ));
  }
  void AddRequest(  const SMatchmakingRequest& _reqData, NI_LPTR INotify* _callback )
  {
    handler->Go(handler->Call( 1, _reqData, RemotePtr<RINotify>(_callback) ));
  }
  void Spectate(  const SMatchmakingRequestCore& _reqData, TUId _targetUid, NI_LPTR INotify* _callback )
  {
    handler->Go(handler->Call( 2, _reqData, _targetUid, RemotePtr<RINotify>(_callback) ));
  }
  void GetRequest(  TUId _uid, NI_LPTR INotify* _callback )
  {
    handler->Go(handler->Call( 3, _uid, RemotePtr<RINotify>(_callback) ));
  }

  template <typename T>
  rpc::ECallResult::Enum GetServerStatus( T* object, void (T::*func)(SServerStatus result) )
  {           
    rpc::Transaction* transaction = handler->Call( 4 );
    if (transaction)
    {
      transaction->RegisterAsyncCall( transaction->GetInfo(), new rpc::FunctorNoContext<T, SServerStatus>(object, func) );
      return handler->Go(transaction);
    }
    return rpc::ECallResult::NoTransaction;
  }
  

  template <typename T, typename C>
  rpc::ECallResult::Enum GetServerStatus( T* object, void (T::*func)(SServerStatus result, C context, rpc::CallStatus status), const C& context, float timeout=0.f)
  {           
    rpc::Transaction* transaction = handler->Call( 4 );
    if (transaction)
    {
      transaction->RegisterAsyncCall( transaction->GetInfo(), new rpc::FunctorContext<T, SServerStatus, C>(object, func, context), timeout );
      return handler->Go(transaction);
    }
    return rpc::ECallResult::NoTransaction;
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

  static uint GetClassCrcStatic() { return 0x2bb2959; }
protected:
  friend class rpc::Gate;




private:
  StrongMT<rpc::EntityHandler> handler;
  WeakMT<rpc::IRemoteEntity> parent;


};

}



namespace socialLobby
{


class RIPvxInterface : public rpc::IRemoteEntity, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(RIPvxInterface, rpc::IRemoteEntity, BaseObjectMT);
public:
  RPC_INFO("socialLobby::IPvxInterface", 0x8925118f);
  
  RIPvxInterface() : handler(0) {}
  RIPvxInterface( rpc::EntityHandler* _handler, rpc::IRemoteEntity* _parent )
  :  handler(_handler)
  ,  parent(_parent)

  {

  }

  ~RIPvxInterface()
  {
    if( handler )
    {
      handler->OnDestruct(*this);
      handler = 0;
    }
  }
  virtual rpc::RemoteEntityInfo GetInfo() const { rpc::RemoteEntityInfo info = { handler->GetId(), { RIPvxInterface::ID(), RIPvxInterface::CRC32}, handler->GetGUID() }; return info; }
  inline bool IsUpdated() const { return handler->IsUpdated(); }
  rpc::EntityHandler* GetHandler() { return handler; }


  template <typename T>
  rpc::ECallResult::Enum PvxInstance( NI_LPTR IPvxSvc* _pvx, const string& _clusterId, const Transport::TServiceId& _svcId, const PvxClusterSettings& _settings, T* object, void (T::*func)(bool result) )
  {           
    rpc::Transaction* transaction = handler->Call( 0, RemotePtr<RIPvxSvc>(_pvx), _clusterId, _svcId, _settings );
    if (transaction)
    {
      transaction->RegisterAsyncCall( transaction->GetInfo(), new rpc::FunctorNoContext<T, bool>(object, func) );
      return handler->Go(transaction);
    }
    return rpc::ECallResult::NoTransaction;
  }
  

  template <typename T, typename C>
  rpc::ECallResult::Enum PvxInstance( NI_LPTR IPvxSvc* _pvx, const string& _clusterId, const Transport::TServiceId& _svcId, const PvxClusterSettings& _settings, T* object, void (T::*func)(bool result, C context, rpc::CallStatus status), const C& context, float timeout=0.f)
  {           
    rpc::Transaction* transaction = handler->Call( 0, RemotePtr<RIPvxSvc>(_pvx), _clusterId, _svcId, _settings );
    if (transaction)
    {
      transaction->RegisterAsyncCall( transaction->GetInfo(), new rpc::FunctorContext<T, bool, C>(object, func, context), timeout );
      return handler->Go(transaction);
    }
    return rpc::ECallResult::NoTransaction;
  }
  

  template <typename T>
  rpc::ECallResult::Enum UpdatePvxSettings( const string& _clusterId, const Transport::TServiceId& _svcId, const PvxClusterSettings& _settings, T* object, void (T::*func)(bool result) )
  {           
    rpc::Transaction* transaction = handler->Call( 1, _clusterId, _svcId, _settings );
    if (transaction)
    {
      transaction->RegisterAsyncCall( transaction->GetInfo(), new rpc::FunctorNoContext<T, bool>(object, func) );
      return handler->Go(transaction);
    }
    return rpc::ECallResult::NoTransaction;
  }
  

  template <typename T, typename C>
  rpc::ECallResult::Enum UpdatePvxSettings( const string& _clusterId, const Transport::TServiceId& _svcId, const PvxClusterSettings& _settings, T* object, void (T::*func)(bool result, C context, rpc::CallStatus status), const C& context, float timeout=0.f)
  {           
    rpc::Transaction* transaction = handler->Call( 1, _clusterId, _svcId, _settings );
    if (transaction)
    {
      transaction->RegisterAsyncCall( transaction->GetInfo(), new rpc::FunctorContext<T, bool, C>(object, func, context), timeout );
      return handler->Go(transaction);
    }
    return rpc::ECallResult::NoTransaction;
  }
  
  void PvxInstanceLoadNotify(  const string& _clusterId, const Transport::TServiceId& _svcId, unsigned _load )
  {
    handler->Go(handler->Call( 2, _clusterId, _svcId, _load ));
  }

  template <typename T>
  rpc::ECallResult::Enum PvXPreparedForUser( TUserIdPvX _userId, const string & _key, T* object, void (T::*func)(bool result) )
  {           
    rpc::Transaction* transaction = handler->Call( 3, _userId, _key );
    if (transaction)
    {
      transaction->RegisterAsyncCall( transaction->GetInfo(), new rpc::FunctorNoContext<T, bool>(object, func) );
      return handler->Go(transaction);
    }
    return rpc::ECallResult::NoTransaction;
  }
  

  template <typename T, typename C>
  rpc::ECallResult::Enum PvXPreparedForUser( TUserIdPvX _userId, const string & _key, T* object, void (T::*func)(bool result, C context, rpc::CallStatus status), const C& context, float timeout=0.f)
  {           
    rpc::Transaction* transaction = handler->Call( 3, _userId, _key );
    if (transaction)
    {
      transaction->RegisterAsyncCall( transaction->GetInfo(), new rpc::FunctorContext<T, bool, C>(object, func, context), timeout );
      return handler->Go(transaction);
    }
    return rpc::ECallResult::NoTransaction;
  }
  

  template <typename T>
  rpc::ECallResult::Enum UserEnteredPvX( TUserIdPvX _userId, T* object, void (T::*func)(bool result) )
  {           
    rpc::Transaction* transaction = handler->Call( 4, _userId );
    if (transaction)
    {
      transaction->RegisterAsyncCall( transaction->GetInfo(), new rpc::FunctorNoContext<T, bool>(object, func) );
      return handler->Go(transaction);
    }
    return rpc::ECallResult::NoTransaction;
  }
  

  template <typename T, typename C>
  rpc::ECallResult::Enum UserEnteredPvX( TUserIdPvX _userId, T* object, void (T::*func)(bool result, C context, rpc::CallStatus status), const C& context, float timeout=0.f)
  {           
    rpc::Transaction* transaction = handler->Call( 4, _userId );
    if (transaction)
    {
      transaction->RegisterAsyncCall( transaction->GetInfo(), new rpc::FunctorContext<T, bool, C>(object, func, context), timeout );
      return handler->Go(transaction);
    }
    return rpc::ECallResult::NoTransaction;
  }
  

  template <typename T>
  rpc::ECallResult::Enum UserDroppedFromPvX( TUserIdPvX _userId, bool _intentional, T* object, void (T::*func)(bool result) )
  {           
    rpc::Transaction* transaction = handler->Call( 5, _userId, _intentional );
    if (transaction)
    {
      transaction->RegisterAsyncCall( transaction->GetInfo(), new rpc::FunctorNoContext<T, bool>(object, func) );
      return handler->Go(transaction);
    }
    return rpc::ECallResult::NoTransaction;
  }
  

  template <typename T, typename C>
  rpc::ECallResult::Enum UserDroppedFromPvX( TUserIdPvX _userId, bool _intentional, T* object, void (T::*func)(bool result, C context, rpc::CallStatus status), const C& context, float timeout=0.f)
  {           
    rpc::Transaction* transaction = handler->Call( 5, _userId, _intentional );
    if (transaction)
    {
      transaction->RegisterAsyncCall( transaction->GetInfo(), new rpc::FunctorContext<T, bool, C>(object, func, context), timeout );
      return handler->Go(transaction);
    }
    return rpc::ECallResult::NoTransaction;
  }
  

  template <typename T>
  rpc::ECallResult::Enum GameFinished( lobby::TSocialGameId _gameId, int _winner, T* object, void (T::*func)(bool result) )
  {           
    rpc::Transaction* transaction = handler->Call( 6, _gameId, _winner );
    if (transaction)
    {
      transaction->RegisterAsyncCall( transaction->GetInfo(), new rpc::FunctorNoContext<T, bool>(object, func) );
      return handler->Go(transaction);
    }
    return rpc::ECallResult::NoTransaction;
  }
  

  template <typename T, typename C>
  rpc::ECallResult::Enum GameFinished( lobby::TSocialGameId _gameId, int _winner, T* object, void (T::*func)(bool result, C context, rpc::CallStatus status), const C& context, float timeout=0.f)
  {           
    rpc::Transaction* transaction = handler->Call( 6, _gameId, _winner );
    if (transaction)
    {
      transaction->RegisterAsyncCall( transaction->GetInfo(), new rpc::FunctorContext<T, bool, C>(object, func, context), timeout );
      return handler->Go(transaction);
    }
    return rpc::ECallResult::NoTransaction;
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

  static uint GetClassCrcStatic() { return 0x8925118f; }
protected:
  friend class rpc::Gate;




private:
  StrongMT<rpc::EntityHandler> handler;
  WeakMT<rpc::IRemoteEntity> parent;


};

}



namespace socialLobby
{


class RIDevSocLobby : public rpc::IRemoteEntity, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(RIDevSocLobby, rpc::IRemoteEntity, BaseObjectMT);
public:
  RPC_INFO("socialLobby::IDevSocLobby", 0xf1183b41);
  
  RIDevSocLobby() : handler(0) {}
  RIDevSocLobby( rpc::EntityHandler* _handler, rpc::IRemoteEntity* _parent )
  :  handler(_handler)
  ,  parent(_parent)

  {

  }

  ~RIDevSocLobby()
  {
    if( handler )
    {
      handler->OnDestruct(*this);
      handler = 0;
    }
  }
  virtual rpc::RemoteEntityInfo GetInfo() const { rpc::RemoteEntityInfo info = { handler->GetId(), { RIDevSocLobby::ID(), RIDevSocLobby::CRC32}, handler->GetGUID() }; return info; }
  inline bool IsUpdated() const { return handler->IsUpdated(); }
  rpc::EntityHandler* GetHandler() { return handler; }


  template <typename T>
  rpc::ECallResult::Enum AcquireUIdRange( int count, T* object, void (T::*func)(SDevUidRange result) )
  {           
    rpc::Transaction* transaction = handler->Call( 0, count );
    if (transaction)
    {
      transaction->RegisterAsyncCall( transaction->GetInfo(), new rpc::FunctorNoContext<T, SDevUidRange>(object, func) );
      return handler->Go(transaction);
    }
    return rpc::ECallResult::NoTransaction;
  }
  

  template <typename T, typename C>
  rpc::ECallResult::Enum AcquireUIdRange( int count, T* object, void (T::*func)(SDevUidRange result, C context, rpc::CallStatus status), const C& context, float timeout=0.f)
  {           
    rpc::Transaction* transaction = handler->Call( 0, count );
    if (transaction)
    {
      transaction->RegisterAsyncCall( transaction->GetInfo(), new rpc::FunctorContext<T, SDevUidRange, C>(object, func, context), timeout );
      return handler->Go(transaction);
    }
    return rpc::ECallResult::NoTransaction;
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

  static uint GetClassCrcStatic() { return 0xf1183b41; }
protected:
  friend class rpc::Gate;




private:
  StrongMT<rpc::EntityHandler> handler;
  WeakMT<rpc::IRemoteEntity> parent;


};

}



#endif // __R_ISocialLobby_H__
