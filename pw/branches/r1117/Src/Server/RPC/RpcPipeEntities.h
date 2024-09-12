#pragma once

#include <stdarg.h>
#include <System/nvector.h>
#include <System/nstring.h>
#include <System/Basic.h>

#include "Arguments.h"
#include "ClassFactory.h"

namespace rpc 
{


struct GateInfo
{
  GUID id;
  int protocolVersion;
  static const int PROTOCOL_VERSION = 5;
};

class Node;

struct DelayedPackets
{
  void Add(const void* data, int size, const Transport::MessageMiscInfo & miscInfo);
  ~DelayedPackets();

  nstl::vector<MemoryBlock> linkPackets; 
  nstl::vector<int> indices;
  nstl::vector<Transport::MessageMiscInfo> times;
  int size() { return linkPackets.size(); }
  void Clear();
};

struct DummyNode : public INode, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(DummyNode, INode, BaseObjectMT);
public:
  DummyNode(const NodeDescription& _desc):desc(&_desc)
  {
  }
  DummyNode():desc(0) {}

  virtual IPacketPipe * GetConnectedPipe() { return 0; } 
  virtual void RemoveEntity(rpc::EntityHandler* handler, int index) {}
  virtual int AppendEntity(rpc::EntityHandler* handler) { return 0; }
  virtual bool Poll() { return false; }
  virtual bool IsReady() const { return desc->IsIdentified(); }
  virtual const char* GetName() { return desc->name.c_str(); }
  virtual const NodeDescription& GetDesc() const { return *desc; }
  virtual bool IsConnected() const { return true; }
  virtual void DereplicateAll() {}
private:
  DUMMY_ASSIGNMENT(DummyNode);
  const NodeDescription* desc;
};

struct DummyMultiPipe : public IMultiPipe, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( DummyMultiPipe, IMultiPipe, BaseObjectMT );

public:
  DummyMultiPipe() { node = new DummyNode; }
  DummyMultiPipe(const NodeDescription& _desc) { node = new DummyNode( _desc ); }

  virtual int GetCount() { return 1;}
  virtual StrongMT<INode> GetNode(int index) { return index==0 ? node.Get() : 0; }
private:
  StrongMT<DummyNode> node;
};


class PipeEntities
{
public:
  /// Короткое описание заканчивается на этой точке. 
  /// Дальше - развёрнутое описание конструктора.
  PipeEntities(
  rpc::IPacketPipe * pipe, 
  EntityMap* _entityMap,
  EntityFactoriesContainer& _factoriesContainer,
  NodeDescription& _opponent):
  pipe(pipe),
  opponent(_opponent),
  entityMap(_entityMap),
  factoriesContainer(_factoriesContainer),
  args(_entityMap, pipe, &entities),
  entities(_entityMap),
  deserializeReader(&entities, pipe, false),
  updateReader(&entities, pipe, true),
  dummyPipe( new DummyMultiPipe( _opponent ) ),
  resultCall(0, 0, entityMap)
  {
    deserializeReader.SetEntityMap(_entityMap);
    updateReader.SetEntityMap(_entityMap);
    resultCall.args.SetPipe(dummyPipe);
    logTrace = entityMap->GetLogTrace();
  }

  /// Деструктор
  ~PipeEntities();

  /// hack method only for internal use, could be eliminated by retrieving local pointers from factories
  void* get(EntityId entityId, uint id) 
  {
    NI_ASSERT(id != 0xFFFFFFFF, "Class id can't be 0xFFFFFFFF");
    return entities.get(entityId, id);
  }

  /// Принимает пакеты из канала, собирает их и исполняет
  bool Poll(rpc::Node* originNode);

  /// Обрабатывает пакет
  bool ProcessPacket( const byte* data, uint size, bool delayedPacket, rpc::Node* originNode, const Transport::MessageMiscInfo & _miscInfo );

  /// Бриф для SetHandler
  template <typename H>
  bool SetHandler(const void* value, H* object, void (H::*func)())
  {
    return entities.SetHandler<H>(value, object, func);
  }

  /// Бриф для RemoveHandler
  bool RemoveHandler(const void* value) { return entities.RemoveHandler(value); }

  /// hack method only for internal use
  inline rpc::IPacketPipe * getPipe() { return pipe; }
private:
  TLogTrace logTrace;

  bool QueryEntity(const MethodCallHeader& call, const byte* paramsData, uint paramsSize);
  bool ConstructEntity(const MethodCallHeader& call, const byte* paramsData, uint paramsSize, bool isReplicated, rpc::Node* originNode);
  bool DestructEntity(EntityId entityId);
  bool LinkEntity(EntityId id, const MethodCallHeader& call, const byte* paramsData, uint paramsSize);
  CallResult::Enum CallEntity(EntityId entityId, const MethodCallHeader& call, const byte* paramsData, uint paramsSize);
  bool PingEntity(EntityId entityId, const MethodCallHeader& call, const byte* paramsData, uint paramsSize);
  bool UpdateLocalEntity( const MethodCallHeader& call, const byte* paramsData, uint dataSize);
  bool _UpdateLocalEntity( const MethodCallHeader& call, rpc::LocalEntityInfo& info, const byte* paramsData, uint dataSize);
  bool RegisterLocalEntity(uint classCrc, uint classId,  EntityId id, ILocalEntity* e, const GUID& entityGUID);
  bool UpdateEntity(EntityId entityId);
  bool _UpdateEntity(EntityId entityId, ILocalEntity* localEntity, const GUID& entityGUID);
  bool UpdateRemoteEntity(const MethodCallHeader& call, const byte* paramsData, uint paramsSize);
  bool ReturnValue(ICallRoutine& r, const MethodCallHeader& methodCall, const byte* paramsData, uint paramsSize);
  bool SetGateInfo(const MethodCallHeader& call, const byte* paramsData, uint paramsSize);

  bool SharePtr(const MethodCallHeader& call, const byte* paramsData, uint paramsSize, bool delayedPacket);
  bool ForceLink(const MethodCallHeader& call, const byte* paramsData, uint paramsSize);
  bool Publish(EntityId entityId);

  bool _SetGateInfo( const GateInfo &gateInfo );

  LocalEntities entities;  
  StrongMT<rpc::IPacketPipe> pipe;
  EntityMap* entityMap;
  rpc::Arguments args;
  EntityFactoriesContainer& factoriesContainer;
  MethodCallHeader call;
  ArgReader deserializeReader;
  ArgReader updateReader;
  DelayedPackets delayedPackets;
  rpc::MethodCall resultCall;
  StrongMT<DummyMultiPipe> dummyPipe;
  NodeDescription& opponent;
};

} // rpc
