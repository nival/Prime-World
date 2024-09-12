#ifndef __R_ServiceAppearanceNotifierIface_H__
#define __R_ServiceAppearanceNotifierIface_H__

#include <RPC/RPC.h>


#include "ServiceAppearanceNotifierIface.h"

namespace Coordinator
{


class RIServiceAppearanceSubscriber : public IServiceAppearanceSubscriber, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(RIServiceAppearanceSubscriber, IServiceAppearanceSubscriber, BaseObjectMT);
public:
  RPC_INFO("Coordinator::IServiceAppearanceSubscriber", 0xe9090e2e);
  
  RIServiceAppearanceSubscriber() : handler(0) {}
  RIServiceAppearanceSubscriber( rpc::EntityHandler* _handler, rpc::IRemoteEntity* _parent )
  :  handler(_handler)
  ,  parent(_parent)

  {

  }

  ~RIServiceAppearanceSubscriber()
  {
    if( handler )
    {
      handler->OnDestruct(*this);
      handler = 0;
    }
  }
  virtual rpc::RemoteEntityInfo GetInfo() const { rpc::RemoteEntityInfo info = { handler->GetId(), { RIServiceAppearanceSubscriber::ID(), RIServiceAppearanceSubscriber::CRC32}, handler->GetGUID() }; return info; }
  inline bool IsUpdated() const { return handler->IsUpdated(); }
  rpc::EntityHandler* GetHandler() { return handler; }

  void OnRegisterSubscriber(  Coordinator::SubcriberIdT id, Coordinator::ClusterInfo const & cluster )
  {
    handler->Go(handler->Call( 0, id, cluster ));
  }
  void OnRegisterService(  Transport::TServiceId const & svcid )
  {
    handler->Go(handler->Call( 1, svcid ));
  }
  void OnUnregisterService(  Transport::TServiceId const & svcid )
  {
    handler->Go(handler->Call( 2, svcid ));
  }
  void OnStartService(  SvcInfo const & ssi )
  {
    handler->Go(handler->Call( 3, ssi ));
  }
  void OnStopService(  Transport::TServiceId const & svcid )
  {
    handler->Go(handler->Call( 4, svcid ));
  }
  void OnChangeServiceStatus(  Transport::TServiceId const & _svcid, int _status )
  {
    handler->Go(handler->Call( 5, _svcid, _status ));
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

  static uint GetClassCrcStatic() { return 0xe9090e2e; }
protected:
  friend class rpc::Gate;




private:
  StrongMT<rpc::EntityHandler> handler;
  WeakMT<rpc::IRemoteEntity> parent;


};

}



namespace Coordinator
{


class RIServiceAppearancePublisher : public rpc::IRemoteEntity, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(RIServiceAppearancePublisher, rpc::IRemoteEntity, BaseObjectMT);
public:
  RPC_INFO("Coordinator::IServiceAppearancePublisher", 0x2bcbbd5c);
  
  RIServiceAppearancePublisher() : handler(0) {}
  RIServiceAppearancePublisher( rpc::EntityHandler* _handler, rpc::IRemoteEntity* _parent )
  :  handler(_handler)
  ,  parent(_parent)

  {

  }

  ~RIServiceAppearancePublisher()
  {
    if( handler )
    {
      handler->OnDestruct(*this);
      handler = 0;
    }
  }
  virtual rpc::RemoteEntityInfo GetInfo() const { rpc::RemoteEntityInfo info = { handler->GetId(), { RIServiceAppearancePublisher::ID(), RIServiceAppearancePublisher::CRC32}, handler->GetGUID() }; return info; }
  inline bool IsUpdated() const { return handler->IsUpdated(); }
  rpc::EntityHandler* GetHandler() { return handler; }

  void RegisterSubscriber(  NI_LPTR IServiceAppearanceSubscriber* subscriber )
  {
    handler->Go(handler->Call( 0, RemotePtr<RIServiceAppearanceSubscriber>(subscriber) ));
  }
  void UnregisterSubscriber(  SubcriberIdT sid, NI_LPTR IServiceAppearanceSubscriber* subscriber )
  {
    handler->Go(handler->Call( 1, sid, RemotePtr<RIServiceAppearanceSubscriber>(subscriber) ));
  }

  template <typename T>
  rpc::ECallResult::Enum Subscribe( SubcriberIdT sid, Transport::TServiceId const & svcls, T* object, void (T::*func)(int result) )
  {           
    rpc::Transaction* transaction = handler->Call( 2, sid, svcls );
    if (transaction)
    {
      transaction->RegisterAsyncCall( transaction->GetInfo(), new rpc::FunctorNoContext<T, int>(object, func) );
      return handler->Go(transaction);
    }
    return rpc::ECallResult::NoTransaction;
  }
  

  template <typename T, typename C>
  rpc::ECallResult::Enum Subscribe( SubcriberIdT sid, Transport::TServiceId const & svcls, T* object, void (T::*func)(int result, C context, rpc::CallStatus status), const C& context, float timeout=0.f)
  {           
    rpc::Transaction* transaction = handler->Call( 2, sid, svcls );
    if (transaction)
    {
      transaction->RegisterAsyncCall( transaction->GetInfo(), new rpc::FunctorContext<T, int, C>(object, func, context), timeout );
      return handler->Go(transaction);
    }
    return rpc::ECallResult::NoTransaction;
  }
  
  void Unsubscribe(  SubcriberIdT sid, Transport::TServiceId const & svcls )
  {
    handler->Go(handler->Call( 3, sid, svcls ));
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

  static uint GetClassCrcStatic() { return 0x2bcbbd5c; }
protected:
  friend class rpc::Gate;




private:
  StrongMT<rpc::EntityHandler> handler;
  WeakMT<rpc::IRemoteEntity> parent;


};

}



#endif // __R_ServiceAppearanceNotifierIface_H__
