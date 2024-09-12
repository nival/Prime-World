#ifndef __R_SessionKeyRegisterIface_H__
#define __R_SessionKeyRegisterIface_H__

#include <RPC/RPC.h>
#include "Network/TransportTypes.h"
#include "ClusterTypes/ClusterTypes.h"


#include "SessionKeyRegisterIface.h"

namespace Login
{


class RIAddSessionKeyCallback : public IAddSessionKeyCallback, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(RIAddSessionKeyCallback, IAddSessionKeyCallback, BaseObjectMT);
public:
  RPC_INFO("Login::IAddSessionKeyCallback", 0x5bb98ddb);
  
  RIAddSessionKeyCallback() : handler(0) {}
  RIAddSessionKeyCallback( rpc::EntityHandler* _handler, rpc::IRemoteEntity* _parent )
  :  handler(_handler)
  ,  parent(_parent)

  {

  }

  ~RIAddSessionKeyCallback()
  {
    if( handler )
    {
      handler->OnDestruct(*this);
      handler = 0;
    }
  }
  virtual rpc::RemoteEntityInfo GetInfo() const { rpc::RemoteEntityInfo info = { handler->GetId(), { RIAddSessionKeyCallback::ID(), RIAddSessionKeyCallback::CRC32}, handler->GetGUID() }; return info; }
  inline bool IsUpdated() const { return handler->IsUpdated(); }
  rpc::EntityHandler* GetHandler() { return handler; }

  void OnAddSessionKey(  int _rc, const nstl::string & _loginSvcAddr, Cluster::TUserId _userid )
  {
    handler->Go(handler->Call( 0, _rc, _loginSvcAddr, _userid ));
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

  static uint GetClassCrcStatic() { return 0x5bb98ddb; }
protected:
  friend class rpc::Gate;




private:
  StrongMT<rpc::EntityHandler> handler;
  WeakMT<rpc::IRemoteEntity> parent;


};

}

#include "SessionKeyRegisterIface.h"

namespace Login
{


class RISessionKeyRegister : public ISessionKeyRegister, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(RISessionKeyRegister, ISessionKeyRegister, BaseObjectMT);
public:
  RPC_INFO("Login::ISessionKeyRegister", 0xe76ae2f3);
  
  RISessionKeyRegister() : handler(0) {}
  RISessionKeyRegister( rpc::EntityHandler* _handler, rpc::IRemoteEntity* _parent )
  :  handler(_handler)
  ,  parent(_parent)

  {

  }

  ~RISessionKeyRegister()
  {
    if( handler )
    {
      handler->OnDestruct(*this);
      handler = 0;
    }
  }
  virtual rpc::RemoteEntityInfo GetInfo() const { rpc::RemoteEntityInfo info = { handler->GetId(), { RISessionKeyRegister::ID(), RISessionKeyRegister::CRC32}, handler->GetGUID() }; return info; }
  inline bool IsUpdated() const { return handler->IsUpdated(); }
  rpc::EntityHandler* GetHandler() { return handler; }

  void AddSessionKey(  const nstl::string& _sessionKey, const Transport::TServiceId& _sessionPath, const nstl::string& _login, Cluster::TUserId _userid, Cluster::TGameId _gameid, NI_LPTR IAddSessionKeyCallback* _pcb )
  {
    handler->Go(handler->Call( 0, _sessionKey, _sessionPath, _login, _userid, _gameid, RemotePtr<RIAddSessionKeyCallback>(_pcb) ));
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

  static uint GetClassCrcStatic() { return 0xe76ae2f3; }
protected:
  friend class rpc::Gate;




private:
  StrongMT<rpc::EntityHandler> handler;
  WeakMT<rpc::IRemoteEntity> parent;


};

}



#endif // __R_SessionKeyRegisterIface_H__
