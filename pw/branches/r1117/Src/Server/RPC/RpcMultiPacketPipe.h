#pragma once

#include "Packets.h"
#include "Types.h"
#include "IMultiPipe.h"
#include "IRemoteEntity.h"

namespace nstl
{

inline bool operator < (GUID const & v0, GUID const & v1) 
{
  return !IsEqualGUID(v0, v1);
}

}

namespace rpc 
{

struct INode;
_interface ILocalEntityFactory;
class EntityHandler;

struct NodeBriefDesc 
{
  nstl::string nodeName;
  GUID id;
  int pipeLabel;
};

struct NodeInfo
{
  nstl::string nodeName;
  StrongMT<INode> node;
  int pipeLabel;

  void Connect(INode* _node) { node = _node; }
  bool IsConnected() { return node != 0; }

  NodeInfo(const char* _nodeName, const GUID& _id, INode* _node)
  {
    node = _node;
    nodeName = _nodeName;
    id = _id;
  }
  const GUID& GetNodeGUID() const;
  NodeInfo() {}
private:
  GUID id;
};


typedef nstl::map<int, NodeInfo> NodesMap;

struct RemoveNodeInfo
{
  RemoveNodeInfo():entityIndex(-1), nodesCount(0) {}

  int entityIndex;
  int nodesCount;
  StrongMT<INode> node;
};

class MultiPacketPipe : public IPacketPipe, public IMultiPipe, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_3( MultiPacketPipe, IPacketPipe, IMultiPipe, BaseObjectMT );

private:
  typedef nstl::hash_map<void*, int> NodeContainer;
public:
  MultiPacketPipe():
  exclusiveNode(0),
  pipeLabelCounter(0)
  {
  }

  int RegisterNode(const char* _nodeName, const GUID& _nodeId, INode* _node);

  void SetExclusive(INode& node)
  {
    threading::SpinLockGuard lock(locker);
    exclusiveNode = &node;
  }

  void ClearExclusive()
  {
    threading::SpinLockGuard lock(locker);
    _ClearExclusive();
  }

  bool AddNode(INode* node, int index, int pipeLabel);
  void BlockNode(INode& node);
  bool UnblockNode(INode& node);
  bool HaveNode(INode& node);
  void RemoveNode(INode* _node, RemoveNodeInfo& _info);
  void RemoveFromFirstNode(RemoveNodeInfo& _info);

  virtual void Send( const byte* data, int size, bool force );

  virtual void Reset()
  {
    NI_ALWAYS_ASSERT("This method should never be called");
  }

  virtual bool Recieve(int index, byte** data, int* size, Transport::MessageMiscInfo & _miscInfo)
  {
    NI_ALWAYS_ASSERT("This method should never be called");
    return 0;
  }

  virtual const char* GetName();
  virtual IPacketPipe::PipeInfo GetInfo() const { PipeInfo info = {PipeInfo::Closed, -1}; return info; }
  virtual int GetCount() { threading::SpinLockGuard lock(locker); return activeNodes.size()+blockedNodes.size(); }
  virtual StrongMT<INode> GetNode(int index);

  StrongMT<INode> GetNode(const char* name);

  uint GetRegisteredCount() const { threading::SpinLockGuard lock(locker); return allNodes.size(); }
  int GetDisconnectedNodes(nstl::vector<NodeBriefDesc>& nodes);
  int GetAllNodes(nstl::vector<NodeBriefDesc>& nodes);
  rpc::Status GetStatus();

private:
  int _UnregisterNode(INode* node);
  void _RemoveNode(INode* _node, RemoveNodeInfo& _info);


  inline void _ClearExclusive()
  {
    exclusiveNode = 0;
  }

  inline bool _IsBlocked(INode* node) 
  {
    NodeContainer::iterator it = blockedNodes.find(node);
    return (it != blockedNodes.end());
  }

  int _Send(NodeContainer& nodes, const byte* data, int size );

  NodeContainer activeNodes;
  NodeContainer blockedNodes;
  INode* exclusiveNode; 
  threading::SpinLock locker;
  NodesMap allNodes;
  int pipeLabelCounter;
};

} //namespace rpc 
