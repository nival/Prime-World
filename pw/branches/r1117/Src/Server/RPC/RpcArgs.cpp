#include "stdafx.h"
#include "RpcArgs.h"
#include "RpcMultiPacketPipe.h"


namespace rpc 
{
Args::Args( IEntityMap * _entityMap, TLogTrace _logTrace ) :
entityId(INVALID_ENTITY),
entityMap(_entityMap),
datatransaction(0),
multiPipe( new MultiPacketPipe ),
isReadOnly( false ),
reserved(true),
isFailed(false),
isConstructed(false),
reserved0(true),
isUpdated(false),
isShared(false),
isConnected(false),
logTrace(_logTrace)
{
}



rpc::ECallResult::Enum Args::DoTransaction(IPacketPipe * pipe, rpc::Transaction* & transaction)
{
  if (transaction)
  {
    if (transaction->IsReady())
    {
      uint size = transaction->Go(pipe);
      LogTrace3(transaction->GetEntityMap()->GetDesc(), rpc::Out, "send (size=%d tid=%d)", size, transaction->GetTransactionId());
      StopTransaction(transaction);
      return size > 0?rpc::ECallResult::OK:rpc::ECallResult::TooLargeData;
    } else
    {
      NI_ALWAYS_ASSERT("Not ready transaction found, corrupted arguments");
      return rpc::ECallResult::CorruptedArgs;
    }
  }
  return rpc::ECallResult::NoTransaction;
}



void Args::StopTransaction(rpc::Transaction* & transaction)
{
  if (transaction)
  {
    rpc::IEntityMap* sentityMap = transaction->GetEntityMap();
    if (sentityMap)
    {
      sentityMap->StopTransaction(transaction);
    }
  }
  transaction = 0;
}



rpc::Transaction* Args::StartTransaction( uint methodId, bool isReady )
{
  StrongMT<rpc::IEntityMap> sentityMap = entityMap.Lock();
  if (sentityMap)
  {
    if (!isConnected)
    {
      ConnectToNodes(sentityMap);
    }
    rpc::Transaction* transaction = sentityMap->StartTransaction(entityId, isReady);
    transaction->Prepare(methodId, creationInfo.classCrc, isConnected);
    return transaction;
  } 
  return 0;
}

} //namespace rpc 
