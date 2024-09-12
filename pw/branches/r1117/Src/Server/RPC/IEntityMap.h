#ifndef RPC_I_ENTITY_MAP_H__
#define RPC_I_ENTITY_MAP_H__

#include "Interfaces.h"

namespace rpc
{

class Transaction;
struct RemoteEntityInfo;
struct IRemoteEntityFactory;
struct ILogTracer;
struct INode;
struct MethodCallHeader;

class _TransactionHandler;
typedef _TransactionHandler* TransactionHandler;

struct IEntityMap : IBaseInterfaceMT
{
  NI_DECLARE_CLASS_1(IEntityMap, IBaseInterfaceMT);
  virtual ICallRoutine& RegisterSynchronousCall(const MethodCallHeader& header)=0;
  virtual void RegisterAsyncCall(const MethodCallHeader& header, IFunctor* functor, float timeout=0.f)=0;
  virtual void RegisterAsyncCall(const MethodCallHeader& header, IFunctor* functor, ICallRoutine* r, float timeout=0.f)=0;
  virtual uint CancelAsyncCalls(EntityId id)=0;

  virtual Transaction* StartTransaction(EntityId entityId, bool isReady=true)=0;
  virtual void StopTransaction(Transaction* t)=0;
  virtual bool RollbackTransaction(Transaction* t, IRemoteEntity* entity)=0;
  virtual void RemoveEntity(IRemoteEntity& entity)=0;
  virtual void Publish(EntityId entityId, rpc::ILocalEntity* entity)=0;
  virtual const GUID& GetGateID() const =0;
  virtual IRemoteEntity* ConnectToEntity(const RemoteEntityInfo& info, const char* sourceNode, const char* targetNode, const GUID& lnodeId, IRemoteEntityFactory* factory, const GUID& sourceId, rpc::IRemoteEntity* _parent)=0;
  virtual ILocalEntity* CreateLocalEntity(void* instance, RemoteEntityInfo& info, uint classId)=0;

  virtual const char* GetName() = 0;
  virtual TransactionHandler StartDataTransaction()=0;
  virtual bool CommitDataTransaction(TransactionHandler h, bool publishAfterCommit)=0;
  virtual TransactionHandler GetActiveDataTransaction()=0;
  virtual bool ShareEntity(const GUID& srcId, EntityId id, const GUID& dstId, const GUID& entityGUID, bool delayedPacket)=0;
  virtual ILogTracer* GetLogTrace()=0;
  virtual StrongMT<IPacketPipe> ConnectToPipe(const char* name, const GUID& id)=0;
  virtual StrongMT<INode> GetNode(IPacketPipe* pipe)=0;
  virtual const NodeDescription& GetDesc() const=0;
};

}

#endif // RPC_I_ENTITY_MAP_H__
