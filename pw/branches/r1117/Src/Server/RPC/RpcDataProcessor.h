#pragma once

#include <stdarg.h>
#include <System/nvector.h>
#include <System/nstring.h>
#include <System/Basic.h>
#include "RpcDataProcessor.h"
#include "System/IDGenerator.h"
#include "RpcUtils.h"
#include "RpcNodes.h"
#include "EntityMap.h"
//#include "Packets.h"


namespace rpc 
{

class Node;
class ThreadPool;
_interface ILocalEntity;
_interface IEntityMap;
_interface ILocalEntityFactory;
_interface IPacketPipe;
_interface IPipeProcessor;


template <typename T>
ILocalEntity* CreateLocalEntity(T* instance, IEntityMap* entityMap);



class ServerDataProcessor
{
public:
  ServerDataProcessor(
    threading::Mutex& _section, 
    IPipeProcessor* _processor, 
    ThreadPool& _pool);

  ~ServerDataProcessor();

  bool Build();

  const GUID& GetID() const { return entityMap->GetID(); }

  template <typename T>
  bool RegisterObject(StrongMT<T>& value, const char* path, const char* password)
  {
    T* object = value.Get();
    rpc::ILocalEntity* e = rpc::CreateLocalEntity(object, entityMap);
    return entityMap->CreateOrRegisterObject(rpc::GetId<T>(), object, path, password, e);
  }

  bool RegisterObject(uint classId, void* instance, const char* path, const char* password)
  {
    return entityMap->CreateOrRegisterObject(classId, instance, path, password);
  }

  bool UnregisterObject(uint classId, void* instance)
  {
    return entityMap->UnregisterObject(classId, instance);
  }

  StrongMT<Node> AddNode( IPacketPipe * pipe, const GUID* id );

  void RemoveNode(Node* node);

  void RegisterFactory(uint classId, ILocalEntityFactory& factory)
  {
    factoriesContainer.RegisterFactory(classId, factory);
  }

  void UnregisterFactory(uint classId)
  {
    factoriesContainer.UnregisterFactory(classId);
  }
private:
  void _RemoveNode(Node* node);

  threading::Mutex& section;
  ::IDGenerator idGenerator;
  EntityFactoriesContainer factoriesContainer;
  WeakMT<IPipeProcessor> processor;
  Nodes nodes;
  StrongMT<EntityMap> entityMap;
  ThreadPool& pool;
  TLogTrace logTrace;

  threading::Mutex nodeRemoving;
  nstl::vector<StrongMT<Node> > nodesToRemove;
};

} // rpc
