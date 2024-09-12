#include "stdafx.h"
#include "System/InlineProfiler.h"
#include "RpcDataProcessor.h"
#include "RpcNode.h"
#include "RpcThreadPool.h"


namespace rpc
{

ServerDataProcessor::ServerDataProcessor(
                    threading::Mutex& _section, 
                    IPipeProcessor* _processor, 
                    ThreadPool& _pool):
section(_section),
processor(_processor),
pool(_pool)
{
  entityMap = new EntityMap(_section, idGenerator, factoriesContainer, nodes, _processor);
  logTrace = entityMap->GetLogTrace();
}



ServerDataProcessor::~ServerDataProcessor()
{
  nodes.DisconnectAll(entityMap);
  entityMap = 0;
}



StrongMT<Node> ServerDataProcessor::AddNode(rpc::IPacketPipe * pipe, const GUID* id)
{
  if (id)
  {
    if (nodes.IsNodeExist(*id))
    {
      return 0;
    }
  }

  StrongMT<Node> nodeAccessor = new Node(section, entityMap, pipe, id, factoriesContainer);
  nodes.AddNode(nodeAccessor, id);
  
  {
    LogTrace2(nodeAccessor->GetDesc(), rpc::Out, "send identify (node=%s protocol=%d)", GUIDString(entityMap->GetID()).GetValue(), rpc::GateInfo::PROTOCOL_VERSION);

    Transaction* transaction = entityMap->StartTransaction(0);
    transaction->Prepare(rpc::SetGateInfo, 0, true);
    ArgWriter& args = transaction->GetArgs();
    GateInfo gateInfo = {entityMap->GetID(), rpc::GateInfo::PROTOCOL_VERSION};
    args.Push(gateInfo);
    transaction->Go(pipe);
    entityMap->StopTransaction(transaction);
  }
  return nodeAccessor;
}



void ServerDataProcessor::_RemoveNode(Node* node)
{
  NI_PROFILE_HEAVY_FUNCTION;
  if (node->IsConnected())
  {
    entityMap->RemoveNode(node);
    nodes.RemoveNode(node);
  }
}

void ServerDataProcessor::RemoveNode(Node* node)
{
  threading::MutexLock lock(nodeRemoving);
  nodesToRemove.push_back(node);
}

bool ServerDataProcessor::Build()
{
  NI_PROFILE_FUNCTION;
  {
    threading::MutexLock lock(nodeRemoving);
    if (nodesToRemove.size() > 0)
    {
      for (int i=0;i<nodesToRemove.size();++i)
      {
        _RemoveNode(nodesToRemove[i]);
      }
      nodesToRemove.clear();
    }
  }
  if (nodes.Flush() > 0)
  {
    nodes.Poll(pool);
    entityMap->Poll();

    if (pool.corruptedNodes.size() > 0)
    {
      NI_PROFILE_BLOCK( "Corrupted nodes processing" );
      for (int i=0;i<pool.corruptedNodes.size();++i)
      {
        Node* node = pool.corruptedNodes[i];
        IPacketPipe * pipe = node->GetPipe();
        RemoveNode(node);

        StrongMT<IPipeProcessor> strongProcessor = processor.Lock();
        if ( strongProcessor )
        {
          strongProcessor->OnCorruptData( pipe );
        }
      }
      pool.corruptedNodes.clear();
    }
  } else
  {
    entityMap->Poll();
  }
  return true;
}

} // rpc
