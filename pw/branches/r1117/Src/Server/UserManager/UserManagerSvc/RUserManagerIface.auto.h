#ifndef __R_UserManagerIface_H__
#define __R_UserManagerIface_H__

#include <RPC/RPC.h>
#include "Network/LoginData.h"
#include "ClusterTypes/ClusterTypes.h"
#include "UserManagerIface.h"


#include "UserManagerIface.h"

namespace UserManager
{


class RIPrepareUserEnvCallback : public IPrepareUserEnvCallback, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(RIPrepareUserEnvCallback, IPrepareUserEnvCallback, BaseObjectMT);
public:
  RPC_INFO("UserManager::IPrepareUserEnvCallback", 0x25343c71);
  
  RIPrepareUserEnvCallback() : handler(0) {}
  RIPrepareUserEnvCallback( rpc::EntityHandler* _handler, rpc::IRemoteEntity* _parent )
  :  handler(_handler)
  ,  parent(_parent)

  {

  }

  ~RIPrepareUserEnvCallback()
  {
    if( handler )
    {
      handler->OnDestruct(*this);
      handler = 0;
    }
  }
  virtual rpc::RemoteEntityInfo GetInfo() const { rpc::RemoteEntityInfo info = { handler->GetId(), { RIPrepareUserEnvCallback::ID(), RIPrepareUserEnvCallback::CRC32}, handler->GetGUID() }; return info; }
  inline bool IsUpdated() const { return handler->IsUpdated(); }
  rpc::EntityHandler* GetHandler() { return handler; }

  void OnPrepareUserEnv(  int _result, Cluster::TUserId _userid, RelayInfo const & _relayInfo, PartialReconnectInfo const & _partialReconnectInfo )
  {
    handler->Go(handler->Call( 0, _result, _userid, _relayInfo, _partialReconnectInfo ));
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

  static uint GetClassCrcStatic() { return 0x25343c71; }
protected:
  friend class rpc::Gate;




private:
  StrongMT<rpc::EntityHandler> handler;
  WeakMT<rpc::IRemoteEntity> parent;


};

}



namespace UserManager
{


class RIUserManager : public rpc::IRemoteEntity, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(RIUserManager, rpc::IRemoteEntity, BaseObjectMT);
public:
  RPC_INFO("UserManager::IUserManager", 0x1fc1d3be);
  
  RIUserManager() : handler(0) {}
  RIUserManager( rpc::EntityHandler* _handler, rpc::IRemoteEntity* _parent )
  :  handler(_handler)
  ,  parent(_parent)

  {

  }

  ~RIUserManager()
  {
    if( handler )
    {
      handler->OnDestruct(*this);
      handler = 0;
    }
  }
  virtual rpc::RemoteEntityInfo GetInfo() const { rpc::RemoteEntityInfo info = { handler->GetId(), { RIUserManager::ID(), RIUserManager::CRC32}, handler->GetGUID() }; return info; }
  inline bool IsUpdated() const { return handler->IsUpdated(); }
  rpc::EntityHandler* GetHandler() { return handler; }


  template <typename T>
  rpc::ECallResult::Enum AddUser( Cluster::TUserId _userId, string const & _sessionKey, Transport::TServiceId const & _sessionPath, wstring const & _username, T* object, void (T::*func)(bool result) )
  {           
    rpc::Transaction* transaction = handler->Call( 0, _userId, _sessionKey, _sessionPath, _username );
    if (transaction)
    {
      transaction->RegisterAsyncCall( transaction->GetInfo(), new rpc::FunctorNoContext<T, bool>(object, func) );
      return handler->Go(transaction);
    }
    return rpc::ECallResult::NoTransaction;
  }
  

  template <typename T, typename C>
  rpc::ECallResult::Enum AddUser( Cluster::TUserId _userId, string const & _sessionKey, Transport::TServiceId const & _sessionPath, wstring const & _username, T* object, void (T::*func)(bool result, C context, rpc::CallStatus status), const C& context, float timeout=0.f)
  {           
    rpc::Transaction* transaction = handler->Call( 0, _userId, _sessionKey, _sessionPath, _username );
    if (transaction)
    {
      transaction->RegisterAsyncCall( transaction->GetInfo(), new rpc::FunctorContext<T, bool, C>(object, func, context), timeout );
      return handler->Go(transaction);
    }
    return rpc::ECallResult::NoTransaction;
  }
  

  template <typename T>
  rpc::ECallResult::Enum RemoveUser( Cluster::TUserId _userId, T* object, void (T::*func)(bool result) )
  {           
    rpc::Transaction* transaction = handler->Call( 1, _userId );
    if (transaction)
    {
      transaction->RegisterAsyncCall( transaction->GetInfo(), new rpc::FunctorNoContext<T, bool>(object, func) );
      return handler->Go(transaction);
    }
    return rpc::ECallResult::NoTransaction;
  }
  

  template <typename T, typename C>
  rpc::ECallResult::Enum RemoveUser( Cluster::TUserId _userId, T* object, void (T::*func)(bool result, C context, rpc::CallStatus status), const C& context, float timeout=0.f)
  {           
    rpc::Transaction* transaction = handler->Call( 1, _userId );
    if (transaction)
    {
      transaction->RegisterAsyncCall( transaction->GetInfo(), new rpc::FunctorContext<T, bool, C>(object, func, context), timeout );
      return handler->Go(transaction);
    }
    return rpc::ECallResult::NoTransaction;
  }
  

  template <typename T>
  rpc::ECallResult::Enum FindUserSession( string const & _sessionKey, bool _partialReconnect, T* object, void (T::*func)(UserSessionInfo result) )
  {           
    rpc::Transaction* transaction = handler->Call( 2, _sessionKey, _partialReconnect );
    if (transaction)
    {
      transaction->RegisterAsyncCall( transaction->GetInfo(), new rpc::FunctorNoContext<T, UserSessionInfo>(object, func) );
      return handler->Go(transaction);
    }
    return rpc::ECallResult::NoTransaction;
  }
  

  template <typename T, typename C>
  rpc::ECallResult::Enum FindUserSession( string const & _sessionKey, bool _partialReconnect, T* object, void (T::*func)(UserSessionInfo result, C context, rpc::CallStatus status), const C& context, float timeout=0.f)
  {           
    rpc::Transaction* transaction = handler->Call( 2, _sessionKey, _partialReconnect );
    if (transaction)
    {
      transaction->RegisterAsyncCall( transaction->GetInfo(), new rpc::FunctorContext<T, UserSessionInfo, C>(object, func, context), timeout );
      return handler->Go(transaction);
    }
    return rpc::ECallResult::NoTransaction;
  }
  

  template <typename T>
  rpc::ECallResult::Enum PrepareUserEnv( UserManager::UserEnvInfo const & uei, UserManager::IPrepareUserEnvCallback* cb, T* object, void (T::*func)(Result::Enum result) )
  {           
    rpc::Transaction* transaction = handler->Call( 3, uei, cb );
    if (transaction)
    {
      transaction->RegisterAsyncCall( transaction->GetInfo(), new rpc::FunctorNoContext<T, Result::Enum>(object, func) );
      return handler->Go(transaction);
    }
    return rpc::ECallResult::NoTransaction;
  }
  

  template <typename T, typename C>
  rpc::ECallResult::Enum PrepareUserEnv( UserManager::UserEnvInfo const & uei, UserManager::IPrepareUserEnvCallback* cb, T* object, void (T::*func)(Result::Enum result, C context, rpc::CallStatus status), const C& context, float timeout=0.f)
  {           
    rpc::Transaction* transaction = handler->Call( 3, uei, cb );
    if (transaction)
    {
      transaction->RegisterAsyncCall( transaction->GetInfo(), new rpc::FunctorContext<T, Result::Enum, C>(object, func, context), timeout );
      return handler->Go(transaction);
    }
    return rpc::ECallResult::NoTransaction;
  }
  

  template <typename T>
  rpc::ECallResult::Enum OnUserLeave( Cluster::TUserId _userId, Transport::TServiceId const & _svcid, Coordinator::TServiceRole const & _svcrole, T* object, void (T::*func)(bool result) )
  {           
    rpc::Transaction* transaction = handler->Call( 4, _userId, _svcid, _svcrole );
    if (transaction)
    {
      transaction->RegisterAsyncCall( transaction->GetInfo(), new rpc::FunctorNoContext<T, bool>(object, func) );
      return handler->Go(transaction);
    }
    return rpc::ECallResult::NoTransaction;
  }
  

  template <typename T, typename C>
  rpc::ECallResult::Enum OnUserLeave( Cluster::TUserId _userId, Transport::TServiceId const & _svcid, Coordinator::TServiceRole const & _svcrole, T* object, void (T::*func)(bool result, C context, rpc::CallStatus status), const C& context, float timeout=0.f)
  {           
    rpc::Transaction* transaction = handler->Call( 4, _userId, _svcid, _svcrole );
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

  static uint GetClassCrcStatic() { return 0x1fc1d3be; }
protected:
  friend class rpc::Gate;




private:
  StrongMT<rpc::EntityHandler> handler;
  WeakMT<rpc::IRemoteEntity> parent;


};

}



#endif // __R_UserManagerIface_H__
