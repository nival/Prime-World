#ifndef __R_LobbyAccounting_H__
#define __R_LobbyAccounting_H__

#include <RPC/RPC.h>
#include "LobbyAccountingStructs.h"




namespace Lobby
{


class RLobbyAccounting : public rpc::IRemoteEntity, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(RLobbyAccounting, rpc::IRemoteEntity, BaseObjectMT);
public:
  RPC_INFO("Lobby::LobbyAccounting", 0x925716e2);
  
  RLobbyAccounting() : handler(0) {}
  RLobbyAccounting( rpc::EntityHandler* _handler, rpc::IRemoteEntity* _parent )
  :  handler(_handler)
  ,  parent(_parent)

  {

  }

  ~RLobbyAccounting()
  {
    if( handler )
    {
      handler->OnDestruct(*this);
      handler = 0;
    }
  }
  virtual rpc::RemoteEntityInfo GetInfo() const { rpc::RemoteEntityInfo info = { handler->GetId(), { RLobbyAccounting::ID(), RLobbyAccounting::CRC32}, handler->GetGUID() }; return info; }
  inline bool IsUpdated() const { return handler->IsUpdated(); }
  rpc::EntityHandler* GetHandler() { return handler; }


  template <typename T>
  rpc::ECallResult::Enum BlockMoney( int userId, int serviceId, T* object, void (T::*func)(int result) )
  {           
    rpc::Transaction* transaction = handler->Call( 0, userId, serviceId );
    if (transaction)
    {
      transaction->RegisterAsyncCall( transaction->GetInfo(), new rpc::FunctorNoContext<T, int>(object, func) );
      return handler->Go(transaction);
    }
    return rpc::ECallResult::NoTransaction;
  }
  

  template <typename T, typename C>
  rpc::ECallResult::Enum BlockMoney( int userId, int serviceId, T* object, void (T::*func)(int result, C context, rpc::CallStatus status), const C& context, float timeout=0.f)
  {           
    rpc::Transaction* transaction = handler->Call( 0, userId, serviceId );
    if (transaction)
    {
      transaction->RegisterAsyncCall( transaction->GetInfo(), new rpc::FunctorContext<T, int, C>(object, func, context), timeout );
      return handler->Go(transaction);
    }
    return rpc::ECallResult::NoTransaction;
  }
  
  void UnblockMoney(  int userId, int blockId )
  {
    handler->Go(handler->Call( 1, userId, blockId ));
  }

  template <typename T>
  rpc::ECallResult::Enum GetServicePrice( int serviceId, T* object, void (T::*func)(int result) )
  {           
    rpc::Transaction* transaction = handler->Call( 2, serviceId );
    if (transaction)
    {
      transaction->RegisterAsyncCall( transaction->GetInfo(), new rpc::FunctorNoContext<T, int>(object, func) );
      return handler->Go(transaction);
    }
    return rpc::ECallResult::NoTransaction;
  }
  

  template <typename T, typename C>
  rpc::ECallResult::Enum GetServicePrice( int serviceId, T* object, void (T::*func)(int result, C context, rpc::CallStatus status), const C& context, float timeout=0.f)
  {           
    rpc::Transaction* transaction = handler->Call( 2, serviceId );
    if (transaction)
    {
      transaction->RegisterAsyncCall( transaction->GetInfo(), new rpc::FunctorContext<T, int, C>(object, func, context), timeout );
      return handler->Go(transaction);
    }
    return rpc::ECallResult::NoTransaction;
  }
  

  template <typename T>
  rpc::ECallResult::Enum BuyBlockedService( int userId, int blockId, int serviceId, T* object, void (T::*func)(bool result) )
  {           
    rpc::Transaction* transaction = handler->Call( 3, userId, blockId, serviceId );
    if (transaction)
    {
      transaction->RegisterAsyncCall( transaction->GetInfo(), new rpc::FunctorNoContext<T, bool>(object, func) );
      return handler->Go(transaction);
    }
    return rpc::ECallResult::NoTransaction;
  }
  

  template <typename T, typename C>
  rpc::ECallResult::Enum BuyBlockedService( int userId, int blockId, int serviceId, T* object, void (T::*func)(bool result, C context, rpc::CallStatus status), const C& context, float timeout=0.f)
  {           
    rpc::Transaction* transaction = handler->Call( 3, userId, blockId, serviceId );
    if (transaction)
    {
      transaction->RegisterAsyncCall( transaction->GetInfo(), new rpc::FunctorContext<T, bool, C>(object, func, context), timeout );
      return handler->Go(transaction);
    }
    return rpc::ECallResult::NoTransaction;
  }
  

  template <typename T>
  rpc::ECallResult::Enum BuyService( int userId, int serviceId, T* object, void (T::*func)(Lobby::BuyResult result) )
  {           
    rpc::Transaction* transaction = handler->Call( 4, userId, serviceId );
    if (transaction)
    {
      transaction->RegisterAsyncCall( transaction->GetInfo(), new rpc::FunctorNoContext<T, Lobby::BuyResult>(object, func) );
      return handler->Go(transaction);
    }
    return rpc::ECallResult::NoTransaction;
  }
  

  template <typename T, typename C>
  rpc::ECallResult::Enum BuyService( int userId, int serviceId, T* object, void (T::*func)(Lobby::BuyResult result, C context, rpc::CallStatus status), const C& context, float timeout=0.f)
  {           
    rpc::Transaction* transaction = handler->Call( 4, userId, serviceId );
    if (transaction)
    {
      transaction->RegisterAsyncCall( transaction->GetInfo(), new rpc::FunctorContext<T, Lobby::BuyResult, C>(object, func, context), timeout );
      return handler->Go(transaction);
    }
    return rpc::ECallResult::NoTransaction;
  }
  

  template <typename T>
  rpc::ECallResult::Enum GetMoney( int userId, T* object, void (T::*func)(int result) )
  {           
    rpc::Transaction* transaction = handler->Call( 5, userId );
    if (transaction)
    {
      transaction->RegisterAsyncCall( transaction->GetInfo(), new rpc::FunctorNoContext<T, int>(object, func) );
      return handler->Go(transaction);
    }
    return rpc::ECallResult::NoTransaction;
  }
  

  template <typename T, typename C>
  rpc::ECallResult::Enum GetMoney( int userId, T* object, void (T::*func)(int result, C context, rpc::CallStatus status), const C& context, float timeout=0.f)
  {           
    rpc::Transaction* transaction = handler->Call( 5, userId );
    if (transaction)
    {
      transaction->RegisterAsyncCall( transaction->GetInfo(), new rpc::FunctorContext<T, int, C>(object, func, context), timeout );
      return handler->Go(transaction);
    }
    return rpc::ECallResult::NoTransaction;
  }
  

  template <typename T>
  rpc::ECallResult::Enum GiveMoneyToUser( int userId, int userDstId, int serviceId, T* object, void (T::*func)(bool result) )
  {           
    rpc::Transaction* transaction = handler->Call( 6, userId, userDstId, serviceId );
    if (transaction)
    {
      transaction->RegisterAsyncCall( transaction->GetInfo(), new rpc::FunctorNoContext<T, bool>(object, func) );
      return handler->Go(transaction);
    }
    return rpc::ECallResult::NoTransaction;
  }
  

  template <typename T, typename C>
  rpc::ECallResult::Enum GiveMoneyToUser( int userId, int userDstId, int serviceId, T* object, void (T::*func)(bool result, C context, rpc::CallStatus status), const C& context, float timeout=0.f)
  {           
    rpc::Transaction* transaction = handler->Call( 6, userId, userDstId, serviceId );
    if (transaction)
    {
      transaction->RegisterAsyncCall( transaction->GetInfo(), new rpc::FunctorContext<T, bool, C>(object, func, context), timeout );
      return handler->Go(transaction);
    }
    return rpc::ECallResult::NoTransaction;
  }
  

  template <typename T>
  rpc::ECallResult::Enum GetServices( T* object, void (T::*func)(const nstl::vector<Lobby::ServiceInfo>& result) )
  {           
    rpc::Transaction* transaction = handler->Call( 7 );
    if (transaction)
    {
      transaction->RegisterAsyncCall( transaction->GetInfo(), new rpc::RefFunctorNoContext<T, const nstl::vector<Lobby::ServiceInfo>>(object, func) );
      return handler->Go(transaction);
    }
    return rpc::ECallResult::NoTransaction;
  }
  

  template <typename T, typename C>
  rpc::ECallResult::Enum GetServices( T* object, void (T::*func)(const nstl::vector<Lobby::ServiceInfo>& result, C context, rpc::CallStatus status), const C& context, float timeout=0.f)
  {           
    rpc::Transaction* transaction = handler->Call( 7 );
    if (transaction)
    {
      transaction->RegisterAsyncCall( transaction->GetInfo(), new rpc::RefFunctorContext<T, const nstl::vector<Lobby::ServiceInfo>, C>(object, func, context), timeout );
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

  static uint GetClassCrcStatic() { return 0x925716e2; }
protected:
  friend class rpc::Gate;




private:
  StrongMT<rpc::EntityHandler> handler;
  WeakMT<rpc::IRemoteEntity> parent;


};

}



#endif // __R_LobbyAccounting_H__
