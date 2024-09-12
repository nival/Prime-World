#ifndef __R_ClientControlInterface_H__
#define __R_ClientControlInterface_H__

#include <RPC/RPC.h>
#include "ClientControlTypes.h"
#include "ClientControlRemote.h"
#include "RClientControlRemote.auto.h"
#include "Network/RSessionKeyRegisterIface.auto.h"


#include "ClientControlInterface.h"

namespace clientCtl
{


class RIInterface : public IInterface, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(RIInterface, IInterface, BaseObjectMT);
public:
  RPC_INFO("clientCtl::IInterface", 0xa90470fc);
  
  RIInterface() : handler(0) {}
  RIInterface( rpc::EntityHandler* _handler, rpc::IRemoteEntity* _parent )
  :  handler(_handler)
  ,  parent(_parent)

  {

  }

  ~RIInterface()
  {
    if( handler )
    {
      handler->OnDestruct(*this);
      handler = 0;
    }
  }
  virtual rpc::RemoteEntityInfo GetInfo() const { rpc::RemoteEntityInfo info = { handler->GetId(), { RIInterface::ID(), RIInterface::CRC32}, handler->GetGUID() }; return info; }
  inline bool IsUpdated() const { return handler->IsUpdated(); }
  rpc::EntityHandler* GetHandler() { return handler; }

  void RegisterLoginSvc(  const Transport::TServiceId& _svcid, NI_LPTR Login::ISessionKeyRegister* _sessionKeyInterface )
  {
    handler->Go(handler->Call( 0, _svcid, RemotePtr<Login::RISessionKeyRegister>(_sessionKeyInterface) ));
  }
  void UpdateLoginSvc(  const Transport::TServiceId& _svcid, int _state, unsigned _load )
  {
    handler->Go(handler->Call( 1, _svcid, _state, _load ));
  }
  void AllocateLoginSvc(  int _alllocId, NI_LPTR ILoginSvcAllocationCallback* _callback )
  {
    handler->Go(handler->Call( 2, _alllocId, RemotePtr<RILoginSvcAllocationCallback>(_callback) ));
  }
  void UserEnters(  const Transport::TServiceId& _loginSvcId, Transport::TClientId _uid, Transport::TUserSid _usid, NI_LPTR IUserPresenceCallback* _callback )
  {
    handler->Go(handler->Call( 3, _loginSvcId, _uid, _usid, RemotePtr<RIUserPresenceCallback>(_callback) ));
  }
  void UserLeft(  const Transport::TServiceId& _loginSvcId, Transport::TClientId _uid, Transport::TUserSid _usid )
  {
    handler->Go(handler->Call( 4, _loginSvcId, _uid, _usid ));
  }
  void KickUser(  Transport::TClientId _uid )
  {
    handler->Go(handler->Call( 5, _uid ));
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

  static uint GetClassCrcStatic() { return 0xa90470fc; }
protected:
  friend class rpc::Gate;




private:
  StrongMT<rpc::EntityHandler> handler;
  WeakMT<rpc::IRemoteEntity> parent;


};

}



#endif // __R_ClientControlInterface_H__
