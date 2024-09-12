#ifndef __R_RollInstance_H__
#define __R_RollInstance_H__

#include <RPC/RPC.h>
#include "RollInstance.h"
#include "RRollClient.auto.h"


#include "RollInstance.h"

namespace roll
{


class RIInstance : public IInstance, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(RIInstance, IInstance, BaseObjectMT);
public:
  RPC_INFO("roll::IInstance", 0xc13d7e63);
  
  RIInstance() : handler(0) {}
  RIInstance( rpc::EntityHandler* _handler, rpc::IRemoteEntity* _parent )
  :  handler(_handler)
  ,  parent(_parent)

  {

  }

  ~RIInstance()
  {
    if( handler )
    {
      handler->OnDestruct(*this);
      handler = 0;
    }
  }
  virtual rpc::RemoteEntityInfo GetInfo() const { rpc::RemoteEntityInfo info = { handler->GetId(), { RIInstance::ID(), RIInstance::CRC32}, handler->GetGUID() }; return info; }
  inline bool IsUpdated() const { return handler->IsUpdated(); }
  rpc::EntityHandler* GetHandler() { return handler; }

  void Roll(  NI_LPTR IClient* client, const SPreGameData& preGame, const SPostGameData& postGame )
  {
    handler->Go(handler->Call( 0, RemotePtr<RIClient>(client), preGame, postGame ));
  }
  void ForgeRoll(  NI_LPTR IClient* client, const SForgeRollData & data )
  {
    handler->Go(handler->Call( 1, RemotePtr<RIClient>(client), data ));
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

  static uint GetClassCrcStatic() { return 0xc13d7e63; }
protected:
  friend class rpc::Gate;




private:
  StrongMT<rpc::EntityHandler> handler;
  WeakMT<rpc::IRemoteEntity> parent;


};

}



#endif // __R_RollInstance_H__
