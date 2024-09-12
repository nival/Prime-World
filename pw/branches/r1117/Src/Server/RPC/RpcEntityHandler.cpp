#include "stdafx.h"
#include "RpcEntityHandler.h"


namespace rpc 
{

EntityHandler::EntityHandler(
              IEntityMap* _entityMap,
              const GUID& _entityGUID, TLogTrace _logTrace):Args(_entityMap, _logTrace),
updateCallback(0),
entityTypeName(0),
entityGUID(_entityGUID)
{
}



EntityHandler::~EntityHandler()
{
  delete creationInfo.writer;
}



void EntityHandler::Construct()
{
  StrongMT<rpc::IEntityMap> sentityMap = entityMap.Lock();
  if (!sentityMap)
  {
    return;
  }
  rpc::Transaction* transaction = sentityMap->StartTransaction(entityId);
  if (transaction)
  {
    creationInfo.Apply();
    creationInfo.Go(multiPipe, transaction->GetStream(), 0);
    sentityMap->StopTransaction(transaction);
    MarkConstructed();
  }
}



void EntityHandler::SetEntityInfo(const EntityCreationInfo& info, EntityId entityId, const char* name ) { 
  SetEntityId(entityId);  
  entityTypeName = name; 
  ArgWriter* writer = new ArgWriter(multiPipe);
  StrongMT<rpc::IEntityMap> sentityMap = entityMap.Lock();
  writer->SetEntityMap(sentityMap);
  creationInfo.Reset(entityId, writer, info.classCrc);
  if (info.isShared)
  {
    LogTrace2(sentityMap->GetDesc(), rpc::Local, "sconstruct (eid=%d euid=%s)", entityId, GUIDString(entityGUID).GetValue());
  }
  creationInfo.header.Prepare(info.isShared?rpc::LinkConstructor:rpc::Constructor);
  writer->Push(info.classId);
  writer->Push(info.classCrc);
  writer->Push(entityGUID);
  if (info.isQueried && !info.isShared)  
  {
    creationInfo.Apply();
  }
}



bool EntityHandler::ConnectNode(INode* node, int pipeLabel)
{
  if (node)
  {
    int index = node->AppendEntity(this);
    if (index >= 0)
    {
      if (!multiPipe->AddNode(node, index, pipeLabel))
      {
        node->RemoveEntity(this, index);
        return false;
      }
    } 
    else
    {
      return false;
    }
  }
  return true;
}



bool EntityHandler::RegisterNode(INode* node, const char* nodeName, const GUID& nodeId)
{
  int pipeLabel = multiPipe->RegisterNode(nodeName, nodeId, node);
  if (!node)
  {
    isConnected = false;
  }
  if (node)
  {
    return ConnectNode(node, pipeLabel);
  }
  return true;
}



bool EntityHandler::Replicate(IRemoteEntity& entity, INode& node)
{
  if (RegisterNode(&node, node.GetName(), node.GetDesc().guid))
  {
    byte id = creationInfo.header.id;
    creationInfo.header.id = ReplicatedConstructor;

    StrongMT<rpc::IEntityMap> sentityMap = entityMap.Lock();
    if (!sentityMap)
    {
      return false;
    }
    Transaction* replicationTransaction = sentityMap->StartTransaction(entityId);
    if (replicationTransaction)
    {
      ArgWriter& largs = replicationTransaction->GetArgs();
      entity.Synchronize(&largs);
      creationInfo.Go(node.GetConnectedPipe(), replicationTransaction->GetStream(), (largs.size() > 0)?&replicationTransaction->GetArgsData():0);
      creationInfo.header.id = id;
      sentityMap->StopTransaction(replicationTransaction);
      LogTrace2(node.GetDesc(), rpc::Out, "replicate %s (eid=%d)", entity.ClassName(), creationInfo.header.entityId );
      return true;
    }
  }
  return false;
  // TODO: what if transaction already on the way !!!
}



void EntityHandler::Block(INode& node) 
{ 
  LogTrace2(node.GetDesc(), rpc::Out, "block %s (eid=%d)", entityTypeName, creationInfo.header.entityId );
  multiPipe->BlockNode(node); 
}



bool EntityHandler::Unblock(INode& node) 
{ 
  bool result = multiPipe->UnblockNode(node); 
  if ( result )
    LogTrace2(node.GetDesc(), rpc::Out,  "unblock %s (eid=%d)", entityTypeName, creationInfo.header.entityId );
  return result;
}



void EntityHandler::SetExclusive(INode& node) 
{ 
  LogTrace2(node.GetDesc(), rpc::Out, "SetExclusive %s (eid=%d)", entityTypeName, creationInfo.header.entityId );
  multiPipe->SetExclusive(node); 
}



void EntityHandler::ClearExclusive() 
{ 
  //LogTrace2(entityMap->GetDesc(), rpc::Local, "ClearExclusive %s (eid=%d)\n", creationInfo.header.entityId );
  multiPipe->ClearExclusive(); 
}

void EntityHandler::Commit(bool publishAfterCommit) { 
  if (!IsReadOnly())
  {
    if (datatransaction)
    {
      datatransaction->Publish(publishAfterCommit);
      GoData(); 
      StopDataTransaction();
    }
  }
}



bool EntityHandler::Rollback(IRemoteEntity* entity) 
{ 
  bool result = false;
  if (datatransaction)
  {
    StrongMT<rpc::IEntityMap> sentityMap = entityMap.Lock();
    if (sentityMap)
    {
      result = sentityMap->RollbackTransaction(datatransaction, entity);
    }
    StopDataTransaction();
  }
  return result;
}



void EntityHandler::MarkUpdated(IRemoteEntity* entity, int dataSize)
{
  if (dataSize > 0)
  {
    isUpdated = true;
    if (updateCallback)
    {
      updateCallback->OnUpdated(entity);
    } else
    {
      rpc::IUpdateCallback* callback = entity->GetUpdateCallback();
      if (callback)
      {
        callback->OnUpdated(entity);
      }
    }
  }
}



bool EntityHandler::Update(IRemoteEntity* entity, IUpdateCallback* callback) 
{ 
  if (callback)
  {
    updateCallback = callback;
  }
  isUpdated = false;
  if (multiPipe->GetRegisteredCount() == 1)
  {
    Rollback(entity);
    if (StartDataTransaction(rpc::UpdateRequest))
    {
      GoData();
      return true;
    }
  }
  return false;
}



void EntityHandler::MarkShared(IMultiPipe* pipe, IRemoteEntity* entity) 
{ 
  StrongMT<rpc::IEntityMap> sentityMap = entityMap.Lock();
  if (!sentityMap)
  {
    return;
  }
  isShared = true; 
  if (pipe && pipe->GetCount() > 0 && isConstructed)
  {
    rpc::Transaction* localTransaction = sentityMap->StartTransaction(entityId);
    if (localTransaction)
    {
      ArgWriter& localArgs = localTransaction->GetArgs();
      localTransaction->Prepare(rpc::SharePtr, creationInfo.classCrc, isConnected);
      localArgs.Push(entity->GetInfo().entityGUID);
      NI_ASSERT( !IsGUIDEmpty( entity->GetInfo().entityGUID ), "entityGUID is NULL" );
      int count = pipe->GetCount();
      localArgs.Push(short(count));
      for (int i=0;i<count;++i)
      {
        StrongMT<INode> node = pipe->GetNode(i);
        if (node)
        {
          const GUID& nodeId = node->GetDesc().guid;
          LogTrace2(node->GetDesc(), rpc::Out, "send share %s (eid=%d node=%s)", entity->ClassName(), entity->GetInfo().entityId, GUIDString(nodeId).GetValue());
          localArgs.Push(nodeId);
        }
      }
      localTransaction->Go(multiPipe);
      sentityMap->StopTransaction(localTransaction);
    }
  }
}

void EntityHandler::OnDestruct(IRemoteEntity& entity)
{
  StopDataTransaction();
  if (isConstructed)
  {
    DestroyEntity(multiPipe);
  }
  RemoveNodeInfo info;
  do {
    multiPipe->RemoveFromFirstNode(info);
    if (info.entityIndex >= 0 && info.node)
    {
      info.node->RemoveEntity(this, info.entityIndex);
    }
  } while (info.nodesCount > 0);

  StrongMT<rpc::IEntityMap> sentityMap = entityMap.Lock();
  if (sentityMap)
  {
    sentityMap->RemoveEntity(entity);
  }
}


int EntityHandler::Dereplicate(INode& node)
{
  StopDataTransaction();
  RemoveNodeInfo info;
  multiPipe->RemoveNode(&node, info);
  if (info.entityIndex >= 0)
  {
    LogTrace2(node.GetDesc(), rpc::Out, "dereplicate %s (eid=%d pipe=%s)", entityTypeName, creationInfo.header.entityId, multiPipe->GetName() );
    DestroyEntity(node.GetConnectedPipe());
  }
  if (info.nodesCount == 0)
  {
    isConnected = false;
  }
  if (!isConnected)
  {
    StrongMT<rpc::IEntityMap> sentityMap = entityMap.Lock();
    if (sentityMap)
    {
      sentityMap->CancelAsyncCalls(GetId());
    }
  }
  return info.entityIndex;
}

int EntityHandler::ConnectToNodes(rpc::IEntityMap* sentityMap)
{
  int notConnected = 0;
  nstl::vector<NodeBriefDesc> nodes;
  int nodesCount = multiPipe->GetDisconnectedNodes(nodes);
  for (int i=0;i<nodes.size();++i)
  {
    StrongMT<IPacketPipe> pipe = sentityMap->ConnectToPipe(nodes[i].nodeName.c_str(), nodes[i].id);
    if (pipe)
    {
      StrongMT<INode> node = sentityMap->GetNode(pipe);  
      ConnectNode(node, nodes[i].pipeLabel);
      Construct();
    } else
    {
      notConnected++;
    }
  }
  if (notConnected == 0 && nodesCount > 0)
  {
    isConnected = true;
  }
  return notConnected;
}



bool EntityHandler::DestroyEntity(IPacketPipe * pipe)
{
  rpc::Transaction* transaction = StartTransaction();
  if (transaction)
  {
    transaction->Prepare(rpc::Destructor, creationInfo.classCrc, isConnected);
    transaction->Go(pipe, true);
    StopTransaction(transaction);
    return true;
  }
  return false;
}



void EntityHandler::Publish()
{
  if (StartDataTransaction(rpc::Publish))
  {
    GoData();
  }
}

} //namespace rpc 
