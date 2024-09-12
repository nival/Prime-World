#ifndef __R_RelayBalancerClientNotifyIface_H__
#define __R_RelayBalancerClientNotifyIface_H__

#include <RPC/RPC.h>


#include "RelayBalancerClientNotifyIface.h"

namespace Relay
{


class RIOutgoingClientNotifySink : public IOutgoingClientNotifySink, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(RIOutgoingClientNotifySink, IOutgoingClientNotifySink, BaseObjectMT);
public:
  RPC_INFO("Relay::IOutgoingClientNotifySink", 0x7533a34d);
  
  RIOutgoingClientNotifySink() : handler(0) {}
  RIOutgoingClientNotifySink( rpc::EntityHandler* _handler, rpc::IRemoteEntity* _parent )
  :  handler(_handler)
  ,  parent(_parent)

  {

  }

  ~RIOutgoingClientNotifySink()
  {
    if( handler )
    {
      handler->OnDestruct(*this);
      handler = 0;
    }
  }
  virtual rpc::RemoteEntityInfo GetInfo() const { rpc::RemoteEntityInfo info = { handler->GetId(), { RIOutgoingClientNotifySink::ID(), RIOutgoingClientNotifySink::CRC32}, handler->GetGUID() }; return info; }
  inline bool IsUpdated() const { return handler->IsUpdated(); }
  rpc::EntityHandler* GetHandler() { return handler; }

  void OutgoingClientNotify(  Transport::TClientId _clientid, int _reason )
  {
    handler->Go(handler->Call( 0, _clientid, _reason ));
  }
  void ClientConnectedNotify(  Transport::TClientId _clientid )
  {
    handler->Go(handler->Call( 1, _clientid ));
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

  static uint GetClassCrcStatic() { return 0x7533a34d; }
protected:
  friend class rpc::Gate;




private:
  StrongMT<rpc::EntityHandler> handler;
  WeakMT<rpc::IRemoteEntity> parent;


};

}



namespace Relay
{


class RIIncomingClientNotifySink : public rpc::IRemoteEntity, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(RIIncomingClientNotifySink, rpc::IRemoteEntity, BaseObjectMT);
public:
  RPC_INFO("Relay::IIncomingClientNotifySink", 0x28bcd0b4);
  
  RIIncomingClientNotifySink() : handler(0) {}
  RIIncomingClientNotifySink( rpc::EntityHandler* _handler, rpc::IRemoteEntity* _parent )
  :  handler(_handler)
  ,  parent(_parent)

  {

  }

  ~RIIncomingClientNotifySink()
  {
    if( handler )
    {
      handler->OnDestruct(*this);
      handler = 0;
    }
  }
  virtual rpc::RemoteEntityInfo GetInfo() const { rpc::RemoteEntityInfo info = { handler->GetId(), { RIIncomingClientNotifySink::ID(), RIIncomingClientNotifySink::CRC32}, handler->GetGUID() }; return info; }
  inline bool IsUpdated() const { return handler->IsUpdated(); }
  rpc::EntityHandler* GetHandler() { return handler; }


  template <typename T>
  rpc::ECallResult::Enum RegisterOutgoingClientNotifySink( IOutgoingClientNotifySink* _cb, T* object, void (T::*func)(int result) )
  {           
    rpc::Transaction* transaction = handler->Call( 0, _cb );
    if (transaction)
    {
      transaction->RegisterAsyncCall( transaction->GetInfo(), new rpc::FunctorNoContext<T, int>(object, func) );
      return handler->Go(transaction);
    }
    return rpc::ECallResult::NoTransaction;
  }
  

  template <typename T, typename C>
  rpc::ECallResult::Enum RegisterOutgoingClientNotifySink( IOutgoingClientNotifySink* _cb, T* object, void (T::*func)(int result, C context, rpc::CallStatus status), const C& context, float timeout=0.f)
  {           
    rpc::Transaction* transaction = handler->Call( 0, _cb );
    if (transaction)
    {
      transaction->RegisterAsyncCall( transaction->GetInfo(), new rpc::FunctorContext<T, int, C>(object, func, context), timeout );
      return handler->Go(transaction);
    }
    return rpc::ECallResult::NoTransaction;
  }
  

  template <typename T>
  rpc::ECallResult::Enum IncomingClientNotify( Transport::TClientId _clientid, string const & _sessionkey, T* object, void (T::*func)(bool result) )
  {           
    rpc::Transaction* transaction = handler->Call( 1, _clientid, _sessionkey );
    if (transaction)
    {
      transaction->RegisterAsyncCall( transaction->GetInfo(), new rpc::FunctorNoContext<T, bool>(object, func) );
      return handler->Go(transaction);
    }
    return rpc::ECallResult::NoTransaction;
  }
  

  template <typename T, typename C>
  rpc::ECallResult::Enum IncomingClientNotify( Transport::TClientId _clientid, string const & _sessionkey, T* object, void (T::*func)(bool result, C context, rpc::CallStatus status), const C& context, float timeout=0.f)
  {           
    rpc::Transaction* transaction = handler->Call( 1, _clientid, _sessionkey );
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

  static uint GetClassCrcStatic() { return 0x28bcd0b4; }
protected:
  friend class rpc::Gate;




private:
  StrongMT<rpc::EntityHandler> handler;
  WeakMT<rpc::IRemoteEntity> parent;


};

}



#endif // __R_RelayBalancerClientNotifyIface_H__
