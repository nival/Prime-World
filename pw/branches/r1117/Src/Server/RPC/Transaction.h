#pragma once

//#include "Arguments.h"
#include "ArgWriter.h"
#include "System/types.h"


namespace rpc
{

class ArgReader;
struct ICallRoutine;
struct IFunctor;
struct ILocalEntity;

struct MarshalledParam
{
  uint offset;
  uint size;
};

class Transaction 
{
public:
  Transaction();
  ~Transaction();

  void SetEntityInfo(EntityId entityId, uint classCrc)
  {
    info.SetEntityInfo(entityId, classCrc);
  }

  void Publish(bool publishAfterCommit)
  {
    info.header.isPublishOnCommit = publishAfterCommit;
    info.header.isDataMembersIncluded = true;
  }

  void Reset(EntityId entityId, TransactionId _transactionId, IEntityMap* _entityMap)
  {
    transactionId = _transactionId;
    Reset(entityId, info.data, _entityMap);
    entityMap = _entityMap;
  }

  void Clear()
  {
    Reset(INVALID_ENTITY, INVALID_TRANSACTION, 0);
  }

  void Prepare( uint methodId, nival::uint32_t classCrc, bool isConnected) 
  {
    info.header.Prepare(methodId); 
    info.header.transactionId = transactionId;
    info.classCrc = classCrc;
  }

  ArgWriter& GetArgs() { return args; }
  const nstl::vector<byte>& GetArgsData() { return info.data; }
  ArgWriter& GetRollbackArgs() { return rollbackArgs; }
  const nstl::vector<MarshalledParam>& GetParams() const { return params; }
  TransactionId GetId() const { return transactionId; }

  void AddParam(uint offset, uint size)
  {
    MarshalledParam p = {offset, size};
    params.push_back(p);
  }
  const byte* Get(uint offset=0) const { return &rollbackData[offset]; }
  uint Go(IPacketPipe * pipe, bool force=false)
  {
    info.Apply();
    return info.Go(pipe, stream, 0, force);
  }
  const MethodCallHeader& GetInfo() const { return info.header; }
  Stream& GetStream() { return stream; }
  rpc::ArgReader& StartRollback();
  ICallRoutine& RegisterSynchronousCall(const MethodCallHeader& header);
  void RegisterAsyncCall(const MethodCallHeader& header, IFunctor* functor, float timeout=0.f);
  void RegisterAsyncCall(const MethodCallHeader& header, IFunctor* functor, ICallRoutine* routine, float timeout=0.f);
  rpc::IEntityMap* GetEntityMap() { return entityMap; }
  TransactionId GetTransactionId() const { return transactionId; }

  void SetReady() { isReady = true; } 
  bool IsReady() const  { return isReady; } 
private:
  void Reset(EntityId entityId, nstl::vector<byte>& _data, IEntityMap* entityMap);
  
  ArgWriter args;
  MethodCallInfo info;
  ArgWriter rollbackArgs;
  nstl::vector<MarshalledParam> params;
  nstl::vector<byte> rollbackData;
  TransactionId transactionId;
  MemoryStream stream;
  rpc::ArgReader * reader;
  StrongMT<rpc::IEntityMap> entityMap;
  bool isReady;
};


} // rpc