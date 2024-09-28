#pragma once

#include "Interfaces.h"
#include "RpcArgs.h"
#include "RpcUtils.h"
#include "RpcMultiPacketPipe.h"


namespace rpc 
{

struct LocalEntityInstanceInfo
{
  union
  {
    __int64 key;
    struct  
    {
      void* instance;
      uint classId; 
    };
  };
  LocalEntityInstanceInfo():instance(0), classId(0) {}
  LocalEntityInstanceInfo(void* _instance, uint _classId):instance(_instance), classId(_classId) {}
};

class EntityHandler : public BaseObjectMT, public Args
{
  NI_DECLARE_REFCOUNT_CLASS_1(EntityHandler, BaseObjectMT);
  friend struct RemoteEntityInfo_;
  friend class EntityMap;
  friend class ArgWriter;
public:
  EntityHandler() {}
  EntityHandler(
    IEntityMap* _entityMap,
    const GUID& entityGUID,
    TLogTrace _logTrace);

  ~EntityHandler();

  void SetEntityInfo(const EntityCreationInfo& info, EntityId entityId, const char* name );
  bool RegisterNode(INode* node, const char* nodeName, const GUID& nodeId);
  void OnDestruct(IRemoteEntity& entity);
  rpc::ECallResult::Enum Go(rpc::Transaction* transaction) { return DoTransaction(multiPipe, transaction); }
  rpc::ECallResult::Enum GoData() 
  { 
    return DoDataTransaction(multiPipe); 
  }

  // data related 
  void Commit(bool publishAfterCommit);
  bool Rollback(IRemoteEntity* entity);
  bool Update(IRemoteEntity* entity, IUpdateCallback* callback=0);
  bool SetUpdateCallback( IUpdateCallback* callback=0 ) {  updateCallback = callback; return true; }
  IUpdateCallback* GetUpdateCallback(rpc::IRemoteEntity* parent) { return updateCallback?updateCallback:(parent?parent->GetUpdateCallback():0); }
  void Publish();

  // call
  inline rpc::Transaction* Call(uint methodId) 
  { 
    rpc::Transaction* transaction = StartTransaction(methodId, false); 
    if (transaction)
    {
      transaction->SetReady();
    }
    return transaction;
  }
  template <typename T0> rpc::Transaction* Call(uint methodId, const T0& value0) 
  { 
    rpc::Transaction* transaction = StartTransaction(methodId, false); 
    if (
      transaction &&
      Push(transaction, value0)
      )
    {
      transaction->SetReady();
    }
    return transaction; 
  }
  template <typename T0, typename T1> rpc::Transaction* Call(uint methodId, const T0& value0, const T1& value1) 
  { 
    rpc::Transaction* transaction = StartTransaction(methodId, false); 
    if (
      transaction &&
      Push(transaction, value0) && 
      Push(transaction, value1)
      )
    {
      transaction->SetReady();
    }
    return transaction; 
  }
  template <typename T0, typename T1, typename T2> rpc::Transaction* Call(uint methodId, const T0& value0, const T1& value1, const T2& value2) 
  { 
    rpc::Transaction* transaction = StartTransaction(methodId, false);
    if (
      transaction &&
      Push(transaction, value0) && 
      Push(transaction, value1) && 
      Push(transaction, value2)
      ) 
    {
      transaction->SetReady();
    }
    return transaction; 
  }
  template <typename T0, typename T1, typename T2, typename T3> rpc::Transaction* Call(uint methodId, const T0& value0, const T1& value1, const T2& value2, const T3& value3) 
  { 
    rpc::Transaction* transaction = StartTransaction(methodId, false);
    if (
      transaction &&
      Push(transaction, value0) && 
      Push(transaction, value1) && 
      Push(transaction, value2) &&
      Push(transaction, value3)
      ) 
    {
      transaction->SetReady();
    }
    return transaction; 
  }
  template <typename T0, typename T1, typename T2, typename T3, typename T4> 
  rpc::Transaction* Call(uint methodId, const T0& value0, const T1& value1, const T2& value2, const T3& value3, const T4& value4) 
  { 
    rpc::Transaction* transaction = StartTransaction(methodId, false);
    if (
      transaction &&
      Push(transaction, value0) && 
      Push(transaction, value1) && 
      Push(transaction, value2) &&
      Push(transaction, value3) &&
      Push(transaction, value4)
      ) 
    {
      transaction->SetReady();
    }
    return transaction; 
  }
  template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
  rpc::Transaction* Call(uint methodId, const T0& value0, const T1& value1, const T2& value2, const T3& value3, const T4& value4, const T5& value5) 
  { 
    rpc::Transaction* transaction = StartTransaction(methodId, false);
    if (
      transaction &&
      Push(transaction, value0) && 
      Push(transaction, value1) && 
      Push(transaction, value2) &&
      Push(transaction, value3) &&
      Push(transaction, value4) &&
      Push(transaction, value5) 
      ) 
    {
      transaction->SetReady();
    }
    return transaction; 
  }
  template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6> 
  rpc::Transaction* Call(uint methodId,const T0& value0,const T1& value1,const T2& value2,const T3& value3,const T4& value4,const T5& value5,const T6& value6) 
  { 
    rpc::Transaction* transaction = StartTransaction(methodId, false);
    if (
      transaction &&
      Push(transaction, value0) && 
      Push(transaction, value1) && 
      Push(transaction, value2) &&
      Push(transaction, value3) &&
      Push(transaction, value4) &&
      Push(transaction, value5) &&
      Push(transaction, value6)
      ) 
    {
      transaction->SetReady();
    }
    return transaction; 
  }

  rpc::Transaction* Ping(const nstl::vector<byte>& value) 
  { 
    rpc::Transaction* transaction = StartTransaction(rpc::Ping, false); 
    if (
      transaction && 
      Push(transaction, value))
    {
      transaction->SetReady();
    }
    return transaction; 
  }

  template <typename T0> void Construct(const T0& value0) { isFailed = !(creationInfo.writer->Push(value0)); creationInfo.writer->SetEntityMap(0); }
  template <typename T0, typename T1> void Construct(const T0& value0, const T1& value1) { isFailed = !(creationInfo.writer->Push(value0) && creationInfo.writer->Push(value1)); creationInfo.writer->SetEntityMap(0); }
  template <typename T0, typename T1, typename T2> void Construct(const T0& value0, const T1& value1, const T2& value2) { isFailed = !(creationInfo.writer->Push(value0) && creationInfo.writer->Push(value1) && creationInfo.writer->Push(value2)); creationInfo.writer->SetEntityMap(0); }
  template <typename T0, typename T1, typename T2, typename T3> void Construct(const T0& value0, const T1& value1, const T2& value2, const T3& value3) { isFailed = !(creationInfo.writer->Push(value0) && creationInfo.writer->Push(value1) && creationInfo.writer->Push(value2) && creationInfo.writer->Push(value3)); creationInfo.writer->SetEntityMap(0); }

  EntityId GetId() const { return entityId; }
  bool IsUpdated() const { return isUpdated; }
  bool IsShared() const { return isShared; }
  bool IsFailed() const { return isFailed; }
  void MarkShared(IMultiPipe* pipe, IRemoteEntity* entity);
  void MarkConstructed() { isConstructed = true; }

  int Dereplicate(INode& pipe);

  bool Replicate(IRemoteEntity& entity, INode& pipe);
  bool IsReplicated(INode& node) { return multiPipe->HaveNode(node); }
  bool IsConnected() { return isConnected; }
  void Block(INode& node);
  bool Unblock(INode& node);
  void SetExclusive(INode& node);
  void ClearExclusive();
  void MarkUpdated(IRemoteEntity* entity, int dataSize);
  StrongMT<INode> GetNode(int index) { return multiPipe->GetNode(index); }
  StrongMT<INode> GetNode(const char* name) { return multiPipe->GetNode(name); }
  int GetAllNodes(nstl::vector<NodeBriefDesc>& nodes) { return multiPipe->GetAllNodes(nodes); }
  const GUID& GetGUID() const { return entityGUID; }
  ArgWriter* GetCreationArgWriter() { return creationInfo.writer; }
  virtual int ConnectToNodes(rpc::IEntityMap* _entityMap);
  rpc::Status GetStatus() { return multiPipe->GetStatus(); }
private:
  bool ConnectNode(INode* node, int pipeLabel);
  void Construct();

  bool DestroyEntity(IPacketPipe * pipe);

  IUpdateCallback* updateCallback;
  const char* entityTypeName;
  GUID entityGUID;
}; //class EntityHandler

} // rpc
