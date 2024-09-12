#pragma once

#include <stdarg.h>
#include <System/nvector.h>
#include <System/nstring.h>
#include <System/Basic.h>
//#include <System/Crc32Checksum.h>
//#include <System/IDGenerator.h>
#include "RpcUtils.h"
#include "Interfaces.h"

/*
#include "Arguments.h"
#include "Calls.h"
#include "ArgWriter.h"
#include "CppWrapper.h"
#include "System/ThreadNames.h"
*/

namespace rpc
{

class EntityMap;
class ThreadPool;

class Nodes : public INodes
{
  typedef nstl::map<GUID, Node*, GUIDIsLess> GUID2NodeContainer;
public:
  typedef nstl::vector<StrongMT<Node> > NodeContainer;
  typedef nstl::map<Node*, StrongMT<Node> > NodeContainer2;

  ~Nodes();

  int GetCount() const {     threading::MutexLock lock(pipesMutex); return pipeNodes.size()+newNodes.size(); }
  int Flush();

  //INodes
  virtual StrongMT<INode> FindNode(IPacketPipe * pipe);
  virtual StrongMT<IPacketPipe> GetPipe(const GUID& id, const char* pipeName);
  virtual bool IsNodeExist(const GUID& id);
  virtual StrongMT<INode> GetNode(int index);

  void AddNode(StrongMT<Node> const & node, const GUID* id);
  void RemoveNode(Node* node);

  void DisconnectAll(rpc::EntityMap* entityMap);
  void Poll(ThreadPool& pool);
private:
  void _ProcessAnonymousNodes();
  void _AddNode( const GUID& id, Node* node )
  {
    GUID2NodeContainer::iterator it=names2nodes.find(id);
    if (it == names2nodes.end())
    {
      names2nodes[id] = node;
    } else
    {
      NI_DATA_ALWAYS_ASSERT("Gate already registered");
    }
  }
  void _Remove(Node* node);
  threading::Mutex pipesMutex;
  GUID2NodeContainer names2nodes;
  NodeContainer anonymousNodes;
  NodeContainer2 newNodes;
  NodeContainer2 pipeNodes;
};

} // rpc
