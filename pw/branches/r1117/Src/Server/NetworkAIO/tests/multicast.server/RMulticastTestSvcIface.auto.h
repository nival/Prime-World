#ifndef __R_MulticastTestSvcIface_H__
#define __R_MulticastTestSvcIface_H__

#include <RPC/RPC.h>
#include "MulticastTestSvcIface.h"
#include "NetworkAIO/tests/multicast.client/RMulticastClientIface.auto.h"




namespace MulticastTest
{


class RIMulticastSvc : public rpc::IRemoteEntity, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(RIMulticastSvc, rpc::IRemoteEntity, BaseObjectMT);
public:
  RPC_INFO("MulticastTest::IMulticastSvc", 0xca86028a);
  
  RIMulticastSvc() : handler(0) {}
  RIMulticastSvc( rpc::EntityHandler* _handler, rpc::IRemoteEntity* _parent )
  :  handler(_handler)
  ,  parent(_parent)

  {

  }

  ~RIMulticastSvc()
  {
    if( handler )
    {
      handler->OnDestruct(*this);
      handler = 0;
    }
  }
  virtual rpc::RemoteEntityInfo GetInfo() const { rpc::RemoteEntityInfo info = { handler->GetId(), { RIMulticastSvc::ID(), RIMulticastSvc::CRC32}, handler->GetGUID() }; return info; }
  inline bool IsUpdated() const { return handler->IsUpdated(); }
  rpc::EntityHandler* GetHandler() { return handler; }


  template <typename T>
  rpc::ECallResult::Enum RegisterClient( const char* name, uint clientId, NI_LPTR IMulticastClient* _client, T* object, void (T::*func)(int result) )
  {           
    rpc::Transaction* transaction = handler->Call( 0, name, clientId, RemotePtr<RIMulticastClient>(_client) );
    if (transaction)
    {
      transaction->RegisterAsyncCall( transaction->GetInfo(), new rpc::FunctorNoContext<T, int>(object, func) );
      return handler->Go(transaction);
    }
    return rpc::ECallResult::NoTransaction;
  }
  

  template <typename T, typename C>
  rpc::ECallResult::Enum RegisterClient( const char* name, uint clientId, NI_LPTR IMulticastClient* _client, T* object, void (T::*func)(int result, C context, rpc::CallStatus status), const C& context, float timeout=0.f)
  {           
    rpc::Transaction* transaction = handler->Call( 0, name, clientId, RemotePtr<RIMulticastClient>(_client) );
    if (transaction)
    {
      transaction->RegisterAsyncCall( transaction->GetInfo(), new rpc::FunctorContext<T, int, C>(object, func, context), timeout );
      return handler->Go(transaction);
    }
    return rpc::ECallResult::NoTransaction;
  }
  
  void ConfirmStep(  unsigned int _sessionid, unsigned int _step )
  {
    handler->Go(handler->Call( 1, _sessionid, _step ));
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
 
  rpc::INode* GetNode(int index) { return GetHandler()->GetNode(index); }
  rpc::INode* GetNode(const char* name) { return GetHandler()->GetNode(name); }
  virtual rpc::IUpdateCallback* GetUpdateCallback() { StrongMT<rpc::IRemoteEntity> _parent = parent.Lock(); return handler->GetUpdateCallback(_parent); }
  virtual void SetParent(rpc::IRemoteEntity* _parent) { parent = _parent; }
  virtual rpc::Status GetStatus() { return handler->GetStatus(); }

  static uint GetClassCrcStatic() { return 0xca86028a; }
protected:
  friend class rpc::Gate;




private:
  rpc::EntityHandler* handler;
  WeakMT<rpc::IRemoteEntity> parent;


};

}



#endif // __R_MulticastTestSvcIface_H__
