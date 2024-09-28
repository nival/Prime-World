#ifndef __R_ClientControlRemote_H__
#define __R_ClientControlRemote_H__

#include <RPC/RPC.h>
#include "ClientControlTypes.h"
#include "Network/RSessionKeyRegisterIface.auto.h"


#include "ClientControlRemote.h"

namespace clientCtl
{


class RIUserPresenceCallback : public IUserPresenceCallback, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(RIUserPresenceCallback, IUserPresenceCallback, BaseObjectMT);
public:
  RPC_INFO("clientCtl::IUserPresenceCallback", 0xe316fef5);
  
  RIUserPresenceCallback() : handler(0) {}
  RIUserPresenceCallback( rpc::EntityHandler* _handler, rpc::IRemoteEntity* _parent )
  :  handler(_handler)
  ,  parent(_parent)

  {

  }

  ~RIUserPresenceCallback()
  {
    if( handler )
    {
      handler->OnDestruct(*this);
      handler = 0;
    }
  }
  virtual rpc::RemoteEntityInfo GetInfo() const { rpc::RemoteEntityInfo info = { handler->GetId(), { RIUserPresenceCallback::ID(), RIUserPresenceCallback::CRC32}, handler->GetGUID() }; return info; }
  inline bool IsUpdated() const { return handler->IsUpdated(); }
  rpc::EntityHandler* GetHandler() { return handler; }

  void LetUserIn( )
  {
    handler->Go(handler->Call( 0 ));
  }
  void DenyUser( )
  {
    handler->Go(handler->Call( 1 ));
  }
  void KickUser( )
  {
    handler->Go(handler->Call( 2 ));
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

  static uint GetClassCrcStatic() { return 0xe316fef5; }
protected:
  friend class rpc::Gate;




private:
  StrongMT<rpc::EntityHandler> handler;
  WeakMT<rpc::IRemoteEntity> parent;


};

}

#include "ClientControlRemote.h"

namespace clientCtl
{


class RILoginSvcAllocationCallback : public ILoginSvcAllocationCallback, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(RILoginSvcAllocationCallback, ILoginSvcAllocationCallback, BaseObjectMT);
public:
  RPC_INFO("clientCtl::ILoginSvcAllocationCallback", 0x6ebffabd);
  
  RILoginSvcAllocationCallback() : handler(0) {}
  RILoginSvcAllocationCallback( rpc::EntityHandler* _handler, rpc::IRemoteEntity* _parent )
  :  handler(_handler)
  ,  parent(_parent)

  {

  }

  ~RILoginSvcAllocationCallback()
  {
    if( handler )
    {
      handler->OnDestruct(*this);
      handler = 0;
    }
  }
  virtual rpc::RemoteEntityInfo GetInfo() const { rpc::RemoteEntityInfo info = { handler->GetId(), { RILoginSvcAllocationCallback::ID(), RILoginSvcAllocationCallback::CRC32}, handler->GetGUID() }; return info; }
  inline bool IsUpdated() const { return handler->IsUpdated(); }
  rpc::EntityHandler* GetHandler() { return handler; }

  void LoginSvcAllocated(  int _alllocId, const Transport::TServiceId & _svcid, NI_LPTR Login::ISessionKeyRegister* _sessionKeyInterface )
  {
    handler->Go(handler->Call( 0, _alllocId, _svcid, RemotePtr<Login::RISessionKeyRegister>(_sessionKeyInterface) ));
  }
  void LoginSvcAllocationFailed(  int _alllocId )
  {
    handler->Go(handler->Call( 1, _alllocId ));
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

  static uint GetClassCrcStatic() { return 0x6ebffabd; }
protected:
  friend class rpc::Gate;




private:
  StrongMT<rpc::EntityHandler> handler;
  WeakMT<rpc::IRemoteEntity> parent;


};

}



#endif // __R_ClientControlRemote_H__
