#ifndef __R_RelayBalancerIface_H__
#define __R_RelayBalancerIface_H__

#include <RPC/RPC.h>


#include "RelayBalancerIface.h"

namespace Relay
{


class RIBalancerCallback : public IBalancerCallback, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(RIBalancerCallback, IBalancerCallback, BaseObjectMT);
public:
  RPC_INFO("Relay::IBalancerCallback", 0x2c0abded);
  
  RIBalancerCallback() : handler(0) {}
  RIBalancerCallback( rpc::EntityHandler* _handler, rpc::IRemoteEntity* _parent )
  :  handler(_handler)
  ,  parent(_parent)

  {

  }

  ~RIBalancerCallback()
  {
    if( handler )
    {
      handler->OnDestruct(*this);
      handler = 0;
    }
  }
  virtual rpc::RemoteEntityInfo GetInfo() const { rpc::RemoteEntityInfo info = { handler->GetId(), { RIBalancerCallback::ID(), RIBalancerCallback::CRC32}, handler->GetGUID() }; return info; }
  inline bool IsUpdated() const { return handler->IsUpdated(); }
  rpc::EntityHandler* GetHandler() { return handler; }

  void OnRelayAllocated(  Transport::TClientId clienid, int userctx, Transport::TServiceId const & genericrelay, Network::NetAddress const & genericaddr, Transport::TServiceId const & gamerelay, Network::NetAddress const & gameaddr )
  {
    handler->Go(handler->Call( 0, clienid, userctx, genericrelay, genericaddr, gamerelay, gameaddr ));
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

  static uint GetClassCrcStatic() { return 0x2c0abded; }
protected:
  friend class rpc::Gate;




private:
  StrongMT<rpc::EntityHandler> handler;
  WeakMT<rpc::IRemoteEntity> parent;


};

}



namespace Relay
{


class RIBalancer : public rpc::IRemoteEntity, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(RIBalancer, rpc::IRemoteEntity, BaseObjectMT);
public:
  RPC_INFO("Relay::IBalancer", 0x4989e935);
  
  RIBalancer() : handler(0) {}
  RIBalancer( rpc::EntityHandler* _handler, rpc::IRemoteEntity* _parent )
  :  handler(_handler)
  ,  parent(_parent)

  {

  }

  ~RIBalancer()
  {
    if( handler )
    {
      handler->OnDestruct(*this);
      handler = 0;
    }
  }
  virtual rpc::RemoteEntityInfo GetInfo() const { rpc::RemoteEntityInfo info = { handler->GetId(), { RIBalancer::ID(), RIBalancer::CRC32}, handler->GetGUID() }; return info; }
  inline bool IsUpdated() const { return handler->IsUpdated(); }
  rpc::EntityHandler* GetHandler() { return handler; }


  template <typename T>
  rpc::ECallResult::Enum AllocateRelay( Cluster::TGameId gameid, Transport::TClientId clienid, Transport::TServiceId const & svcpath, Coordinator::TServiceRole const & _svcrole, int userctx, Relay::IBalancerCallback* cb, T* object, void (T::*func)(int result) )
  {           
    rpc::Transaction* transaction = handler->Call( 0, gameid, clienid, svcpath, _svcrole, userctx, cb );
    if (transaction)
    {
      transaction->RegisterAsyncCall( transaction->GetInfo(), new rpc::FunctorNoContext<T, int>(object, func) );
      return handler->Go(transaction);
    }
    return rpc::ECallResult::NoTransaction;
  }
  

  template <typename T, typename C>
  rpc::ECallResult::Enum AllocateRelay( Cluster::TGameId gameid, Transport::TClientId clienid, Transport::TServiceId const & svcpath, Coordinator::TServiceRole const & _svcrole, int userctx, Relay::IBalancerCallback* cb, T* object, void (T::*func)(int result, C context, rpc::CallStatus status), const C& context, float timeout=0.f)
  {           
    rpc::Transaction* transaction = handler->Call( 0, gameid, clienid, svcpath, _svcrole, userctx, cb );
    if (transaction)
    {
      transaction->RegisterAsyncCall( transaction->GetInfo(), new rpc::FunctorContext<T, int, C>(object, func, context), timeout );
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

  static uint GetClassCrcStatic() { return 0x4989e935; }
protected:
  friend class rpc::Gate;




private:
  StrongMT<rpc::EntityHandler> handler;
  WeakMT<rpc::IRemoteEntity> parent;


};

}



#endif // __R_RelayBalancerIface_H__
