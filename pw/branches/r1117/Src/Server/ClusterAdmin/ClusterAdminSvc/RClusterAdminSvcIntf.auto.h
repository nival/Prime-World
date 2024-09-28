#ifndef __R_ClusterAdminSvcIntf_H__
#define __R_ClusterAdminSvcIntf_H__

#include <RPC/RPC.h>




namespace ClusterAdmin
{


class RIClusterAdmin : public rpc::IRemoteEntity, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(RIClusterAdmin, rpc::IRemoteEntity, BaseObjectMT);
public:
  RPC_INFO("ClusterAdmin::IClusterAdmin", 0xd38a81cd);
  
  RIClusterAdmin() : handler(0) {}
  RIClusterAdmin( rpc::EntityHandler* _handler, rpc::IRemoteEntity* _parent )
  :  handler(_handler)
  ,  parent(_parent)

  {

  }

  ~RIClusterAdmin()
  {
    if( handler )
    {
      handler->OnDestruct(*this);
      handler = 0;
    }
  }
  virtual rpc::RemoteEntityInfo GetInfo() const { rpc::RemoteEntityInfo info = { handler->GetId(), { RIClusterAdmin::ID(), RIClusterAdmin::CRC32}, handler->GetGUID() }; return info; }
  inline bool IsUpdated() const { return handler->IsUpdated(); }
  rpc::EntityHandler* GetHandler() { return handler; }

  void Shutdown(  unsigned int timeout )
  {
    handler->Go(handler->Call( 0, timeout ));
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

  static uint GetClassCrcStatic() { return 0xd38a81cd; }
protected:
  friend class rpc::Gate;




private:
  rpc::EntityHandler* handler;
  WeakMT<rpc::IRemoteEntity> parent;


};

}



#endif // __R_ClusterAdminSvcIntf_H__
