#include "stdafx.h"
#include <Network/Transport.h>
//#include "RPC.h"
#include "RpcNodes.h"
#include "RpcNode.h"
#include "RpcThreadPool.h"


namespace rpc
{

Nodes::~Nodes()
{
}



StrongMT<INode> Nodes::GetNode(int index)
{
  threading::MutexLock lock(pipesMutex);
  if (index > pipeNodes.size())
  {
    return 0;
  }
  int n = 0;
  for (NodeContainer2::iterator it=pipeNodes.begin();it!=pipeNodes.end();++it)
  {
    if (n == index)
    {
      return it->first;
    }
    n++;
  }
  return 0;
}



StrongMT<IPacketPipe> Nodes::GetPipe(const GUID& id, const char* pipeName)
{
  threading::MutexLock lock(pipesMutex);
  _ProcessAnonymousNodes();
  GUID2NodeContainer::iterator it = names2nodes.find(id); 
  if (it != names2nodes.end())
  {
    StrongMT<IPacketPipe> pipe = it->second->GetConnectedPipe();
    if (pipe && pipeName)
    {
      const char* pipeActualName = pipe->GetName();
      if (pipeActualName && strcmp(pipeName, pipeActualName) != 0)
      {
        return 0;
      }
    }
    return pipe;
  }
  return 0;
}



bool Nodes::IsNodeExist(const GUID& id)
{
  NI_PROFILE_FUNCTION;
  threading::MutexLock lock(pipesMutex);
  _ProcessAnonymousNodes();
  return (names2nodes.find(id) != names2nodes.end());
}



void Nodes::AddNode(StrongMT<Node> const & node, const GUID* id)
{
  threading::MutexLock lock(pipesMutex);
  newNodes[node.Get()] = node;
  if (id)
  {
    _AddNode(*id, node);
  }
  else
  {
    anonymousNodes.push_back(node);
    _ProcessAnonymousNodes();
  }
}



void Nodes::RemoveNode(Node* node)
{
  NI_PROFILE_HEAVY_FUNCTION;
  threading::MutexLock lock(pipesMutex);
  _ProcessAnonymousNodes();
  if (node->IsReady())
  {
    GUID2NodeContainer::iterator it = names2nodes.find(node->GetDesc().guid);
    if (it != names2nodes.end())
    {
      names2nodes.erase(it);
    }
  }
  else
  {
    anonymousNodes.remove(node);
  }
  _Remove(node);
}



void Nodes::DisconnectAll(rpc::EntityMap* entityMap)
{
  while (pipeNodes.size() > 0)
  {
    NodeContainer2::iterator it = pipeNodes.begin();
    entityMap->RemoveNode(it->first);
    RemoveNode(it->first);
  }
}



void Nodes::_Remove(Node* node)
{
  NI_PROFILE_HEAVY_FUNCTION;

  if (node) 
  {
    node->Disconnect();
  }
  NodeContainer2::iterator it = pipeNodes.find(node);
  if (it != pipeNodes.end())
  {
    pipeNodes.erase(it);
  }
  else
  {
    it = newNodes.find(node);
    if (it != newNodes.end())
    {
      newNodes.erase(it);
    }
  }
}



void Nodes::_ProcessAnonymousNodes()
{
  NI_PROFILE_HEAVY_FUNCTION;

  if (anonymousNodes.size() > 0)
  {
    for (Nodes::NodeContainer::iterator it=anonymousNodes.begin();it!=anonymousNodes.end();)
    {
      if (!IsGUIDEmpty((*it)->GetDesc().guid))
      {
        names2nodes[(*it)->GetDesc().guid] = *it;
        anonymousNodes.erase(it);
      } else
      {
        ++it;
      }
    }
  }
}



StrongMT<INode> Nodes::FindNode(IPacketPipe * pipe)
{
  threading::MutexLock lock(pipesMutex);
  for (NodeContainer2::iterator it=pipeNodes.begin();it != pipeNodes.end(); ++it)
  {
    if ( it->first->GetConnectedPipe() == pipe )
    {
      return it->first;
    }
  }
  for (NodeContainer2::iterator it=newNodes.begin();it != newNodes.end(); ++it)
  {
    if ( it->first->GetConnectedPipe() == pipe )
    {
      return it->first;
    }
  }
  return 0;
}



int Nodes::Flush()
{
  NI_PROFILE_FUNCTION;

  threading::MutexLock lock(pipesMutex);
  if (newNodes.size() > 0)
  {
    for (NodeContainer2::iterator it=newNodes.begin();it!=newNodes.end();++it)
    {
      pipeNodes[it->first] = it->second;
    }
    newNodes.clear();
  }
  return pipeNodes.size();
}



void Nodes::Poll(ThreadPool& pool)
{
  NI_PROFILE_FUNCTION;

  if (pool.threads.size() > 0)
  {
    int usedThreadsCount = 0;
    for (Nodes::NodeContainer2::iterator it=pipeNodes.begin();it != pipeNodes.end(); ++it)
    {
      pool.queue.enqueue(it->first);
      usedThreadsCount++;
      pool.dataRecieved.Signal();
    }
    while (usedThreadsCount > 0)
    {
      pool.processingFinished.Wait();
      usedThreadsCount--;
    }
  } else
  {
    for (Nodes::NodeContainer2::iterator it=pipeNodes.begin();it != pipeNodes.end(); ++it)
    {
      bool result = it->first->Poll();
      if (!result)
      {
        pool.corruptedNodes.push_back(it->first);
      }
    }
  }
}

} // rpc
