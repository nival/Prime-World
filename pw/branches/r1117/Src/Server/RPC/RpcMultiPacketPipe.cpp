#include "stdafx.h"
#include "RpcMultiPacketPipe.h"
#include "Interfaces.h"
#include "RpcNode.h"


namespace rpc 
{

int MultiPacketPipe::RegisterNode(const char* _nodeName, const GUID& _nodeId, INode* _node)
{
  threading::SpinLockGuard lock(locker);
  int pipeLabel = pipeLabelCounter++;
  allNodes[pipeLabel] = NodeInfo(_nodeName, _nodeId, _node);
  return pipeLabel;
}

int MultiPacketPipe::_UnregisterNode(INode* node)
{
  for (NodesMap::iterator it = allNodes.begin();it!=allNodes.end();++it) 
  {
    if (it->second.node == node)
    {
      allNodes.erase(it);
      break;
    }
  }
  return activeNodes.size()+blockedNodes.size();
}

int MultiPacketPipe::GetDisconnectedNodes(nstl::vector<NodeBriefDesc>& _nodes)
{
  _nodes.clear();
  threading::SpinLockGuard lock(locker);
  for (NodesMap::iterator it = allNodes.begin();it!=allNodes.end();++it)
  {
    if (!it->second.IsConnected())
    {
      NodeBriefDesc& desc = _nodes.push_back();
      desc.nodeName = it->second.nodeName;
      desc.id = it->second.GetNodeGUID();
      desc.pipeLabel = it->first;
    }
  }
  return allNodes.size();
}

int MultiPacketPipe::GetAllNodes(nstl::vector<NodeBriefDesc>& _nodes)
{
  _nodes.clear();
  threading::SpinLockGuard lock(locker);
  for (NodesMap::iterator it = allNodes.begin();it!=allNodes.end();++it)
  {
    NodeBriefDesc& desc = _nodes.push_back();
    desc.nodeName = it->second.nodeName;
    desc.id = it->second.GetNodeGUID();
    desc.pipeLabel = it->first;
  }
  return allNodes.size();
}

rpc::Status MultiPacketPipe::GetStatus() 
{
  int connectedCount = 0;
  int connectingCount = 0;
  int totalCount=0;

  {
    threading::SpinLockGuard lock(locker);
    totalCount = allNodes.size();
    for (NodesMap::iterator it = allNodes.begin();it!=allNodes.end();++it)
    {
      if (it->second.IsConnected())
      {
        IPacketPipe::PipeInfo::Status status = it->second.node->GetConnectedPipe()->GetInfo().status;
        if (status == IPacketPipe::PipeInfo::Connected)
        {
          connectedCount++;
        } 
        else
        if (status == IPacketPipe::PipeInfo::Connecting)
        {
          connectingCount++; 
        }
      }
    }
  }
  if (connectedCount > 0)
  {
    if (totalCount == connectedCount)
    {
      return rpc::Connected;
    } else
    {
      return rpc::PartiallyConnected;
    }
  } 
  else
  if (connectingCount  > 0)
  {
    return rpc::Connecting;
  }
  return rpc::Disconnected;
}


const GUID& NodeInfo::GetNodeGUID() const
{
  return node?node->GetDesc().guid:id; 
}

void MultiPacketPipe::RemoveFromFirstNode(RemoveNodeInfo& _info)
{
  threading::SpinLockGuard lock(locker);
  _info.entityIndex = -1;
  _info.nodesCount = 0;
  _info.node = 0;
  if (activeNodes.size() > 0)
  {
    _RemoveNode((INode*)(activeNodes.begin()->first), _info);
  }
  else
  if (blockedNodes.size() > 0)
  {
    _RemoveNode((INode*)(blockedNodes.begin()->first), _info);
  }
}

StrongMT<INode> MultiPacketPipe::GetNode(int index)
{
  threading::SpinLockGuard lock(locker);
  int i=0;
  NodeContainer::iterator it = activeNodes.begin();
  for (;it != activeNodes.end() && i<index;++i, ++it) ;
  if (it != activeNodes.end())
  {
    return ((INode*)(it->first));
  }
  it = blockedNodes.begin();
  for (;it != blockedNodes.end() && i<index;++i, ++it) ;
  if (it != blockedNodes.end())
  {
    return ((INode*)(it->first));
  }
  return 0;
}



StrongMT<INode> MultiPacketPipe::GetNode(const char* name)
{
  threading::SpinLockGuard lock(locker);
  for (NodeContainer::iterator it = activeNodes.begin(); it != activeNodes.end();++it)
  {
    const char* pipeName = ((INode*)(it->first))->GetName();
    if (crt::strcmp(pipeName, name) == 0)
    {
      return ((INode*)(it->first));
    }
  }
  for (NodeContainer::iterator it = blockedNodes.begin(); it != blockedNodes.end();++it)
  {
    const char* pipeName = ((INode*)(it->first))->GetName();
    if (crt::strcmp(pipeName, name) == 0)
    {
      return ((INode*)(it->first));
    }
  }
  return 0;
}



const char* MultiPacketPipe::GetName()
{ 
  threading::SpinLockGuard lock(locker);
  if (activeNodes.size() > 0)
  {
    return ((INode*)(activeNodes.begin()->first))->GetName();
  }
  if (blockedNodes.size() > 0)
  {
    return ((INode*)(blockedNodes.begin()->first))->GetName();
  }
  return 0; 
}



bool MultiPacketPipe::AddNode(INode* node, int index, int pipeLabel)
{
  threading::SpinLockGuard lock(locker);
  bool result = activeNodes.insertUnique(node, index);
  if (result)
  {
    NodesMap::iterator it = allNodes.find(pipeLabel);
    NI_VERIFY(it!=allNodes.end(), "Node not found", return false);
    it->second.Connect(node);
  } else
  {
    NI_ALWAYS_ASSERT("This node already present in multi pipe");
  }

  return result;
}

void MultiPacketPipe::BlockNode(INode& node)
{
  threading::SpinLockGuard lock(locker);
  NodeContainer::iterator it = activeNodes.find(&node);
  if (it != activeNodes.end())
  {
    blockedNodes.insertUnique(&node, it->second); // already replicated
    activeNodes.erase(it);
  } else
  {
    blockedNodes.insertUnique(&node, -1); // not replicated
  }
}



bool MultiPacketPipe::UnblockNode(INode& node)
{
  threading::SpinLockGuard lock(locker);
  NodeContainer::iterator it = blockedNodes.find(&node);
  if (it != blockedNodes.end())
  {
    int index = it->second;
    bool isReplicated = (index >= 0);
    blockedNodes.erase(it);
    if (isReplicated)
    {
      activeNodes.insertUnique(&node, index);
    }
    return isReplicated;
  } else
  {
    it = activeNodes.find(&node);
    if (it != activeNodes.end())
    {
      return true;
    }
  }
  return false;
}



bool MultiPacketPipe::HaveNode(INode& node)
{
  threading::SpinLockGuard lock(locker);
  NodeContainer::iterator it = activeNodes.find(&node);
  if (it == activeNodes.end())
  {
    it = blockedNodes.find(&node);
    if (it != blockedNodes.end())
    {
      return true;
    }
    return false;
  }
  return true;
}

void MultiPacketPipe::RemoveNode(INode* _node, RemoveNodeInfo& _info)
{
  threading::SpinLockGuard lock(locker);
  _RemoveNode(_node, _info);
}



void MultiPacketPipe::_RemoveNode(INode* _node, RemoveNodeInfo& _info)
{
  _info.entityIndex = -1;
  _info.nodesCount = 0;
  _info.node = _node;

  if (_node == exclusiveNode)
  {
    _ClearExclusive();
  }
  NodeContainer::iterator it = activeNodes.find(_node);
  if (it != activeNodes.end())
  {
    _info.entityIndex = it->second;
    activeNodes.erase(it);
  } 
  else
  {
    it = blockedNodes.find(_node);
    if (it != blockedNodes.end())
    {
      _info.entityIndex = it->second;
      blockedNodes.erase(it);
    }
  }
  _info.nodesCount = _UnregisterNode(_node);
}



int MultiPacketPipe::_Send(NodeContainer& nodes, const byte* data, int size )
{
  int sent = 0;
  for (NodeContainer::iterator it=nodes.begin();it != nodes.end(); ++it)
  {
    Node* node = ((Node*)(it->first));
    NI_VERIFY(node, "Node can't be null", continue);
    rpc::IPacketPipe* pipe = node->GetPipe();
    if (pipe)
    {
      pipe->Send(data, size, false);
      sent ++;
    }
  }
  return sent;
}



void MultiPacketPipe::Send( const byte* data, int size, bool force)
{
  threading::SpinLockGuard lock(locker);
  if (!exclusiveNode || force)
  {
    //Paranoid assert
    //NI_ASSERT( activeNodes.size() != 0 || blockedNodes.size() != 0, "Send error: no nodes" );
    _Send(activeNodes, data, size);
    if (force)
    {
      _Send(blockedNodes, data, size);
    }
  } else
  {
    if (!_IsBlocked(exclusiveNode))
    {
      exclusiveNode->GetConnectedPipe()->Send(data, size, false);
    }
  }
}

} //namespace rpc 
