#ifndef __R_CoordinatorServerIface_H__
#define __R_CoordinatorServerIface_H__

#include <RPC/RPC.h>
#include "Coordinator/RCoordinatorClientIface.auto.h"


#include "CoordinatorServerIface.h"

namespace Coordinator
{


class RIRegisterClientCallback : public IRegisterClientCallback, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(RIRegisterClientCallback, IRegisterClientCallback, BaseObjectMT);
public:
  RPC_INFO("Coordinator::IRegisterClientCallback", 0x7bed6863);
  
  RIRegisterClientCallback() : handler(0) {}
  RIRegisterClientCallback( rpc::EntityHandler* _handler, rpc::IRemoteEntity* _parent )
  :  handler(_handler)
  ,  parent(_parent)

  {

  }

  ~RIRegisterClientCallback()
  {
    if( handler )
    {
      handler->OnDestruct(*this);
      handler = 0;
    }
  }
  virtual rpc::RemoteEntityInfo GetInfo() const { rpc::RemoteEntityInfo info = { handler->GetId(), { RIRegisterClientCallback::ID(), RIRegisterClientCallback::CRC32}, handler->GetGUID() }; return info; }
  inline bool IsUpdated() const { return handler->IsUpdated(); }
  rpc::EntityHandler* GetHandler() { return handler; }

  void OnRegisterClient(  int _result, Coordinator::ServerIdT _clientid )
  {
    handler->Go(handler->Call( 0, _result, _clientid ));
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

  static uint GetClassCrcStatic() { return 0x7bed6863; }
protected:
  friend class rpc::Gate;




private:
  StrongMT<rpc::EntityHandler> handler;
  WeakMT<rpc::IRemoteEntity> parent;


};

}



namespace Coordinator
{


class RICoordinatorServerRemote : public rpc::IRemoteEntity, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(RICoordinatorServerRemote, rpc::IRemoteEntity, BaseObjectMT);
public:
  RPC_INFO("Coordinator::ICoordinatorServerRemote", 0x22f3542f);
  
  RICoordinatorServerRemote() : handler(0) {}
  RICoordinatorServerRemote( rpc::EntityHandler* _handler, rpc::IRemoteEntity* _parent )
  :  handler(_handler)
  ,  parent(_parent)

  {

  }

  ~RICoordinatorServerRemote()
  {
    if( handler )
    {
      handler->OnDestruct(*this);
      handler = 0;
    }
  }
  virtual rpc::RemoteEntityInfo GetInfo() const { rpc::RemoteEntityInfo info = { handler->GetId(), { RICoordinatorServerRemote::ID(), RICoordinatorServerRemote::CRC32}, handler->GetGUID() }; return info; }
  inline bool IsUpdated() const { return handler->IsUpdated(); }
  rpc::EntityHandler* GetHandler() { return handler; }

  void RegisterClient(  Coordinator::ServerIdT _clientid, NI_LPTR ICoordinatorClientRemote* _rptr, ServerDef const & _serverdef, NI_LPTR IRegisterClientCallback* _cb )
  {
    handler->Go(handler->Call( 0, _clientid, RemotePtr<RICoordinatorClientRemote>(_rptr), _serverdef, RemotePtr<RIRegisterClientCallback>(_cb) ));
  }
  void ServicesStarted(  ServicesStartInfo const & _info )
  {
    handler->Go(handler->Call( 1, _info ));
  }
  void Shutdown( )
  {
    handler->Go(handler->Call( 2 ));
  }
  void StopService(  Transport::TServiceId const & _svcid )
  {
    handler->Go(handler->Call( 3, _svcid ));
  }
  void ServiceStopped(  Transport::TServiceId const & _svcid )
  {
    handler->Go(handler->Call( 4, _svcid ));
  }
  void SoftStopService(  Transport::TServiceId const & _svcid )
  {
    handler->Go(handler->Call( 5, _svcid ));
  }
  void ReloadConfig(  Transport::TServiceId const & _svcid )
  {
    handler->Go(handler->Call( 6, _svcid ));
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

  static uint GetClassCrcStatic() { return 0x22f3542f; }
protected:
  friend class rpc::Gate;




private:
  StrongMT<rpc::EntityHandler> handler;
  WeakMT<rpc::IRemoteEntity> parent;


};

}



#endif // __R_CoordinatorServerIface_H__
