#ifndef __R_SessionConnector_H__
#define __R_SessionConnector_H__

#include <RPC/RPC.h>
#include "SessionConnector.h"




namespace Peered
{


class RSessionConnector : public rpc::IRemoteEntity, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(RSessionConnector, rpc::IRemoteEntity, BaseObjectMT);
public:
  RPC_INFO("Peered::SessionConnector", 0x4bb56ce);
  
  RSessionConnector() : handler(0), callWait(0) {}
  RSessionConnector( rpc::EntityHandler* _handler, rpc::IEntityMap* _callWait, rpc::IRemoteEntity* _parent )
  :  handler(_handler)
  ,  callWait(_callWait)
  ,  parent(_parent)

  {

  }

  ~RSessionConnector()
  {
    if( handler )
    {
      handler->OnDestruct(*this);
      handler = 0;
    }
  }
  virtual rpc::RemoteEntityInfo GetInfo() const { rpc::RemoteEntityInfo info = { handler->GetId(), { RSessionConnector::ID(), RSessionConnector::CRC32}, handler->GetGUID() }; return info; }
  inline bool IsUpdated() const { return handler->IsUpdated(); }
  rpc::EntityHandler* GetHandler() { return handler; }
  rpc::IEntityMap* GetCallWait() { return callWait; }


  template <typename T>
  void Connect( T* object, void (T::*func)(RIGameServer* result) )
  {           
    rpc::Transaction* transaction = handler->Call( 0 );
    callWait->RegisterAsyncCall( transaction->GetInfo(), new rpc::FunctorNoContext<T, RIGameServer*>(object, func) );
    handler->Go(transaction);
  }
  

  template <typename T, typename C>
  void Connect( T* object, void (T::*func)(RIGameServer* result, C context, rpc::CallStatus status), const C& context, float timeout=0.f)
  {           
    rpc::Transaction* transaction = handler->Call( 0 );
    callWait->RegisterAsyncCall( transaction->GetInfo(), new rpc::FunctorContext<T, RIGameServer*, C>(object, func, context), timeout );
    handler->Go(transaction);
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
protected:
  friend class rpc::Gate;




private:
  rpc::EntityHandler* handler;
  rpc::IEntityMap* callWait;
  WeakMT<rpc::IRemoteEntity> parent;


};

}



#endif // __R_SessionConnector_H__
