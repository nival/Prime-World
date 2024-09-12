#ifndef __R_GameBalancerIface_H__
#define __R_GameBalancerIface_H__

#include <RPC/RPC.h>


#include "GameBalancerIface.h"

namespace GameBalancer
{


class RIBalancerCallback : public IBalancerCallback, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(RIBalancerCallback, IBalancerCallback, BaseObjectMT);
public:
  RPC_INFO("GameBalancer::IBalancerCallback", 0x61419b4);
  
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

  void OnGameSvcAllocated(  Peered::TSessionId userctx, uint allocid, HybridServer::IGameServerDispenser* gs )
  {
    handler->Go(handler->Call( 0, userctx, allocid, gs ));
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

  static uint GetClassCrcStatic() { return 0x61419b4; }
protected:
  friend class rpc::Gate;




private:
  StrongMT<rpc::EntityHandler> handler;
  WeakMT<rpc::IRemoteEntity> parent;


};

}



namespace GameBalancer
{


class RIBalancer : public rpc::IRemoteEntity, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(RIBalancer, rpc::IRemoteEntity, BaseObjectMT);
public:
  RPC_INFO("GameBalancer::IBalancer", 0x8bc57902);
  
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
  rpc::ECallResult::Enum AllocateGameSvc( Transport::TServiceId const & svcpath, Peered::TSessionId userctx, IBalancerCallback* cb, T* object, void (T::*func)(int result) )
  {           
    rpc::Transaction* transaction = handler->Call( 0, svcpath, userctx, cb );
    if (transaction)
    {
      transaction->RegisterAsyncCall( transaction->GetInfo(), new rpc::FunctorNoContext<T, int>(object, func) );
      return handler->Go(transaction);
    }
    return rpc::ECallResult::NoTransaction;
  }
  

  template <typename T, typename C>
  rpc::ECallResult::Enum AllocateGameSvc( Transport::TServiceId const & svcpath, Peered::TSessionId userctx, IBalancerCallback* cb, T* object, void (T::*func)(int result, C context, rpc::CallStatus status), const C& context, float timeout=0.f)
  {           
    rpc::Transaction* transaction = handler->Call( 0, svcpath, userctx, cb );
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

  static uint GetClassCrcStatic() { return 0x8bc57902; }
protected:
  friend class rpc::Gate;




private:
  StrongMT<rpc::EntityHandler> handler;
  WeakMT<rpc::IRemoteEntity> parent;


};

}



#endif // __R_GameBalancerIface_H__
