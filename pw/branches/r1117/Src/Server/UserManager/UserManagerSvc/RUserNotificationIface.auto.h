#ifndef __R_UserNotificationIface_H__
#define __R_UserNotificationIface_H__

#include <RPC/RPC.h>
#include "ClusterTypes/ClusterTypes.h"
#include "UserNotificationIface.h"


#include "UserNotificationIface.h"

namespace UserManager
{


class RIUserNotificationSubscriber : public IUserNotificationSubscriber, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(RIUserNotificationSubscriber, IUserNotificationSubscriber, BaseObjectMT);
public:
  RPC_INFO("UserManager::IUserNotificationSubscriber", 0xcb42c19e);
  
  RIUserNotificationSubscriber() : handler(0) {}
  RIUserNotificationSubscriber( rpc::EntityHandler* _handler, rpc::IRemoteEntity* _parent )
  :  handler(_handler)
  ,  parent(_parent)

  {

  }

  ~RIUserNotificationSubscriber()
  {
    if( handler )
    {
      handler->OnDestruct(*this);
      handler = 0;
    }
  }
  virtual rpc::RemoteEntityInfo GetInfo() const { rpc::RemoteEntityInfo info = { handler->GetId(), { RIUserNotificationSubscriber::ID(), RIUserNotificationSubscriber::CRC32}, handler->GetGUID() }; return info; }
  inline bool IsUpdated() const { return handler->IsUpdated(); }
  rpc::EntityHandler* GetHandler() { return handler; }

  void OnUserLoggedIn(  UserInfo const & _uinfo )
  {
    handler->Go(handler->Call( 0, _uinfo ));
  }
  void OnUserLoggedOut(  UserInfo const & _uinfo )
  {
    handler->Go(handler->Call( 1, _uinfo ));
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

  static uint GetClassCrcStatic() { return 0xcb42c19e; }
protected:
  friend class rpc::Gate;




private:
  StrongMT<rpc::EntityHandler> handler;
  WeakMT<rpc::IRemoteEntity> parent;


};

}



namespace UserManager
{


class RIUserNotificationPublisher : public rpc::IRemoteEntity, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(RIUserNotificationPublisher, rpc::IRemoteEntity, BaseObjectMT);
public:
  RPC_INFO("UserManager::IUserNotificationPublisher", 0xf138219d);
  
  RIUserNotificationPublisher() : handler(0) {}
  RIUserNotificationPublisher( rpc::EntityHandler* _handler, rpc::IRemoteEntity* _parent )
  :  handler(_handler)
  ,  parent(_parent)

  {

  }

  ~RIUserNotificationPublisher()
  {
    if( handler )
    {
      handler->OnDestruct(*this);
      handler = 0;
    }
  }
  virtual rpc::RemoteEntityInfo GetInfo() const { rpc::RemoteEntityInfo info = { handler->GetId(), { RIUserNotificationPublisher::ID(), RIUserNotificationPublisher::CRC32}, handler->GetGUID() }; return info; }
  inline bool IsUpdated() const { return handler->IsUpdated(); }
  rpc::EntityHandler* GetHandler() { return handler; }


  template <typename T>
  rpc::ECallResult::Enum RegisterSubscriber( NI_LPTR IUserNotificationSubscriber* _s, T* object, void (T::*func)(SubscriberIdT result) )
  {           
    rpc::Transaction* transaction = handler->Call( 0, RemotePtr<RIUserNotificationSubscriber>(_s) );
    if (transaction)
    {
      transaction->RegisterAsyncCall( transaction->GetInfo(), new rpc::FunctorNoContext<T, SubscriberIdT>(object, func) );
      return handler->Go(transaction);
    }
    return rpc::ECallResult::NoTransaction;
  }
  

  template <typename T, typename C>
  rpc::ECallResult::Enum RegisterSubscriber( NI_LPTR IUserNotificationSubscriber* _s, T* object, void (T::*func)(SubscriberIdT result, C context, rpc::CallStatus status), const C& context, float timeout=0.f)
  {           
    rpc::Transaction* transaction = handler->Call( 0, RemotePtr<RIUserNotificationSubscriber>(_s) );
    if (transaction)
    {
      transaction->RegisterAsyncCall( transaction->GetInfo(), new rpc::FunctorContext<T, SubscriberIdT, C>(object, func, context), timeout );
      return handler->Go(transaction);
    }
    return rpc::ECallResult::NoTransaction;
  }
  
  void UnregisterSubscriber(  SubscriberIdT _id, NI_LPTR IUserNotificationSubscriber* _s )
  {
    handler->Go(handler->Call( 1, _id, RemotePtr<RIUserNotificationSubscriber>(_s) ));
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

  static uint GetClassCrcStatic() { return 0xf138219d; }
protected:
  friend class rpc::Gate;




private:
  StrongMT<rpc::EntityHandler> handler;
  WeakMT<rpc::IRemoteEntity> parent;


};

}



#endif // __R_UserNotificationIface_H__
