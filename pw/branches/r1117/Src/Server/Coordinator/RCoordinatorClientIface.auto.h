#ifndef __R_CoordinatorClientIface_H__
#define __R_CoordinatorClientIface_H__

#include <RPC/RPC.h>
#include "Network/TransportTypes.h"
#include "Coordinator/CoordinatorClientIface.h"




namespace Coordinator
{


class RICoordinatorClientRemote : public rpc::IRemoteEntity, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(RICoordinatorClientRemote, rpc::IRemoteEntity, BaseObjectMT);
public:
  RPC_INFO("Coordinator::ICoordinatorClientRemote", 0x665c29fd);
  
  RICoordinatorClientRemote() : handler(0) {}
  RICoordinatorClientRemote( rpc::EntityHandler* _handler, rpc::IRemoteEntity* _parent )
  :  handler(_handler)
  ,  parent(_parent)

  {

  }

  ~RICoordinatorClientRemote()
  {
    if( handler )
    {
      handler->OnDestruct(*this);
      handler = 0;
    }
  }
  virtual rpc::RemoteEntityInfo GetInfo() const { rpc::RemoteEntityInfo info = { handler->GetId(), { RICoordinatorClientRemote::ID(), RICoordinatorClientRemote::CRC32}, handler->GetGUID() }; return info; }
  inline bool IsUpdated() const { return handler->IsUpdated(); }
  rpc::EntityHandler* GetHandler() { return handler; }

  void AddRoute(  const Transport::TServiceId& service, SvcNetAddresses const & addrs )
  {
    handler->Go(handler->Call( 0, service, addrs ));
  }
  void RemoveRoute(  const Transport::TServiceId& service )
  {
    handler->Go(handler->Call( 1, service ));
  }
  void StartService(  const Transport::TServiceId& service )
  {
    handler->Go(handler->Call( 2, service ));
  }
  void StopService(  const Transport::TServiceId& service )
  {
    handler->Go(handler->Call( 3, service ));
  }
  void SoftStopService(  const Transport::TServiceId& service )
  {
    handler->Go(handler->Call( 4, service ));
  }
  void ReloadConfig(  const Transport::TServiceId & service )
  {
    handler->Go(handler->Call( 5, service ));
  }

  template <typename T>
  rpc::ECallResult::Enum Ping( unsigned int _param, T* object, void (T::*func)(unsigned int result) )
  {           
    rpc::Transaction* transaction = handler->Call( 6, _param );
    if (transaction)
    {
      transaction->RegisterAsyncCall( transaction->GetInfo(), new rpc::FunctorNoContext<T, unsigned int>(object, func) );
      return handler->Go(transaction);
    }
    return rpc::ECallResult::NoTransaction;
  }
  

  template <typename T, typename C>
  rpc::ECallResult::Enum Ping( unsigned int _param, T* object, void (T::*func)(unsigned int result, C context, rpc::CallStatus status), const C& context, float timeout=0.f)
  {           
    rpc::Transaction* transaction = handler->Call( 6, _param );
    if (transaction)
    {
      transaction->RegisterAsyncCall( transaction->GetInfo(), new rpc::FunctorContext<T, unsigned int, C>(object, func, context), timeout );
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

  static uint GetClassCrcStatic() { return 0x665c29fd; }
protected:
  friend class rpc::Gate;




private:
  StrongMT<rpc::EntityHandler> handler;
  WeakMT<rpc::IRemoteEntity> parent;


};

}



#endif // __R_CoordinatorClientIface_H__
