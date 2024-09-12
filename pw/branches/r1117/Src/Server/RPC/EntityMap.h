#pragma once

#include "Types.h"
#include "Calls.h"
#include "IEntityMap.h"
#include "RpcUtils.h"

class IDGenerator;

namespace rpc
{

struct INode;
struct INodes;
class Arguments;
struct ILogTracer;
typedef ILogTracer* TLogTrace;
struct LocalEntityInfo;

template <typename T>
struct CachedContainer
{
  ~CachedContainer()
  {
    for (int i=0;i<cache.size();++i)
    {
      delete cache[i];
    }
  }
  T* Allocate() 
  {
    if (cache.size() > 0)
    {
      T* result = *(cache.end()-1);
      cache.pop_back();
      return result;
    }
    return new T;
  }
  void Deallocate(T* value)
  {
    value->Reset();
    cache.push_back(value);
  }
  nstl::vector<T*> cache;
};


struct EntityGateInfo
{
  GUID gateId;
  EntityId entityId;
};

class PtrSharing
{
  struct EntityInfo
  {
    EntityId id;
    int refCount;
  };
  typedef nstl::map<GUID, EntityInfo, GUIDIsLess > GateEntityMap;
  struct EntityEntry
  {
    StrongMT<rpc::ILocalEntity> entity;
    int totalRefCount;
    GateEntityMap gateEntities;

    void Set(rpc::ILocalEntity* _entity, int _initialRefCount) { entity =_entity; totalRefCount = _initialRefCount; }
    void Reset()
    {
      entity = 0;
      totalRefCount = 0;
      gateEntities.clear();
    }
  };
  typedef nstl::map<GUID, EntityEntry*, GUIDIsLess> EntityEntryMap;
  struct EntityEntryIt
  {
    EntityEntry* entry;
    bool isNew;
    EntityEntryMap::iterator it;
  };
  struct EntityInfoIt
  {
    EntityInfo* info;
    bool isNew;
    GateEntityMap::iterator it;
  };
public:
  PtrSharing(const NodeDescription& _self, TLogTrace _logTrace=0):self(_self), logTrace(_logTrace) {}
  ~PtrSharing();

  bool RegisterObject(rpc::ILocalEntity* entity, const GUID& source, rpc::EntityId id, const GUID& entityGUID, bool isLocal=false);


  void RemoveGate(const GUID& source);
  void UnregisterObject(const GUID& source, rpc::EntityId id, const GUID& entityGUID);

  bool ShareObject(const GUID& destination, const GUID& entityGUID, bool delayedPacket);
  ILocalEntity* LinkToObject(const GUID& destination, rpc::EntityId destId, const GUID& entityGUID);
  bool GetAllGUIDs( rpc::ILocalEntity* entity, nstl::vector<EntityGateInfo>& guids, GUID& entityGUID );
  EntityId GetEntityId(const GUID& entityGUID, const GUID& destination);
  bool GetEntityGUID(rpc::ILocalEntity* entity, GUID& entityGUID);
private:
  EntityEntryMap::iterator _RemoveEntityReference( EntityEntryMap::iterator it, GateEntityMap::iterator git );
  EntityInfoIt _GetEntityInfo( EntityEntry* entry, const GUID& source, bool createIfNotFound);
  EntityEntryIt _GetEntityEntry( const GUID& entityGUID, bool createIfNotFound);
  TLogTrace logTrace;
  EntityEntryMap entities;
  CachedContainer<EntityEntry> entries;
  threading::Mutex itemsLocker;
  const NodeDescription& self;
};
          
struct Original2LocalEntityInfo
{
  EntityId entityId;
  GUID entityGUID;
  WeakMT<ILocalEntity> entity;
};

typedef nstl::hash_map<EntityId, RemoteEntityInfo_> RemoteEntityContainer;

struct RoutineInfo
{
  ICallRoutine* routine;
  NHPTimer::STime startTime;
  int timeout;

  void Set(ICallRoutine* _routine, float _timeout)
  {
    routine = _routine;
    timeout = _timeout*1000;
    NHPTimer::GetTime(startTime);
  }

  int GetCallTime(const NHPTimer::STime& curTime) const 
  {
    return NHPTimer::Time2Milliseconds(curTime-startTime);
  }

  bool IsTimedOut(const NHPTimer::STime& curTime) const 
  {
    if (timeout > 0)
    {
      if (GetCallTime(curTime) > timeout)
      {
        return true;
      }
    }
    return false;
  }
};

typedef nstl::map<int, RoutineInfo> CallsMap;

struct CallsMapInfo
{
  enum Status
  {
    OK,
    EntityNotFound,
    MethodCallNotFound,
    TransactionNotFound,
  };
  static const char* GetReason(Status _status);
  CallsMap* container;
  CallsMap::iterator it;
  Status status;
};

typedef nstl::map<int, CallsMap> MethodsMap;
typedef nstl::map<EntityId, MethodsMap> EntitiesMap;

class CallsHandler 
{
public:
  CallsHandler(ILogTracer* _logTrace):logTrace(_logTrace) {}

  ~CallsHandler();
  void RegisterCall(const MethodCallHeader& header, ICallRoutine& r, float timeout=0.f);
  rpc::ICallRoutine* UnregisterCall(const MethodCallHeader& call, CallsMapInfo::Status& _status);
  int CheckTimeouts(const NHPTimer::STime& curTime);
  uint CancelAsyncCalls(EntityId id);
private:
  CallsMapInfo _GetRoutine(const MethodCallHeader& call);
  CallsMap::iterator _FindRoutine(EntityId entityId, uint methodId, TransactionId transactionId);
  EntitiesMap calls;
  threading::Mutex section; 
  ILogTracer* logTrace;
};

struct PublishRequest
{
  GUID gateId;
  EntityId entityId;
  WeakMT<ILocalEntity> entity;
  GUID entityGUID;
};




class EntityMap : public IEntityMap, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( EntityMap, IEntityMap, BaseObjectMT );
  typedef nstl::map<GUID, WeakMT<IRemoteEntity>, GUIDIsLess> EntityPtrContainer;
  typedef nstl::map<__int64, Original2LocalEntityInfo> LocalEntityInfoContainer;
  typedef nstl::map<nstl::string, LocalEntityInfo*> LocalEntityNamedContainer;

public:
  EntityMap(
    threading::Mutex& _section, 
    IDGenerator& _idGenerator, 
    EntityFactoriesContainer& _factoriesContainer,
    INodes& _nodes,
    IPipeProcessor* _processor);
  ~EntityMap();

  bool RegisterRemoteObject(rpc::ILocalEntity* entity, GUID source, rpc::EntityId id, const GUID& entityGUID, bool isLocal, uint classId);
  bool UnregisterRemoteObject(GUID source, rpc::EntityId id, const GUID& entityGUID, void* instance, uint classId);

  bool GetEntityGUID(rpc::ILocalEntity* entity, GUID& entityGUID) { return ptrs->GetEntityGUID(entity, entityGUID); }

  ILocalEntity* LinkToLocalEntity(GUID source, rpc::EntityId srcId, GUID destination, rpc::EntityId destId, const GUID& entityGUID)
  {
    return ptrs->LinkToObject(destination, destId, entityGUID);
  }
 
  // entity creation
  template <typename T>
  RemoteEntityInfo_ CreateEntity(bool isShared=false, bool isQueried=false)
  {
    EntityCreationInfo info = {T::ID(), T::CRC32, isShared, isQueried};
    return CreateEntity(info);
  }

  RemoteEntityInfo_ CreateEntity(unsigned int classId, unsigned int classCrc, rpc::INode* node, bool isShared=false, bool isQueried=false, IRemoteEntityFactory* factory=0)
  {
    EntityCreationInfo info = {classId, classCrc, isShared, isQueried};
    return CreateEntity(info, factory);
  }


  // calls
  virtual ICallRoutine& RegisterSynchronousCall(const MethodCallHeader& header);
  virtual void RegisterAsyncCall(const MethodCallHeader& header, IFunctor* functor, float timeout=0.f);
  virtual void RegisterAsyncCall(const MethodCallHeader& header, IFunctor* functor, ICallRoutine* routine, float timeout=0.f) { calls->RegisterCall(header, *routine, timeout); }
  virtual uint CancelAsyncCalls(EntityId id) { return calls->CancelAsyncCalls(id); }

  bool ProcessReturnValue( const MethodCallHeader& call, const byte* paramsData, uint paramsSize, rpc::Arguments& args);

  // transactions
  virtual Transaction* StartTransaction(EntityId entityId, bool isReady=true);
  virtual void StopTransaction(Transaction* t);
  virtual bool RollbackTransaction(Transaction* t, IRemoteEntity* entity);

  virtual void RemoveEntity(IRemoteEntity& entity);

  virtual IRemoteEntity* ConnectToEntity(const RemoteEntityInfo& info, const char* sourceNode, const char* targetNode, const GUID& lnodeId, IRemoteEntityFactory* factory, const GUID& sourceId, rpc::IRemoteEntity* _parent);
  virtual StrongMT<IPacketPipe> ConnectToPipe(const char* name, const GUID& id);
  virtual ILocalEntity* CreateLocalEntity(void* instance, RemoteEntityInfo& info, uint classId);

  bool UnregisterObject(uint classId, void* value);
  bool RegisterObject( rpc::ILocalEntity* e, const char* path, const char* password, uint classId );
  bool CreateOrRegisterObject(uint classId, void* instance, const char* path, const char* password, rpc::ILocalEntity* e=0)
  {
    if (!e)
    {
      e = _CreateLocalEntity(instance, classId);
    }
    return RegisterObject(e, path, password, classId);
  }

  LocalEntityInfo* GetRegisteredLocalEntity(const char* path);

  void _RemoveLocalEntity( void* instance, uint classId );

  RemoteEntityInfo_ CreateEntity(const EntityCreationInfo& info, IRemoteEntityFactory* _factory=0, const GUID* entityId=0, rpc::IRemoteEntity* _parent=0);
  void RemoveNode(INode* node);

  //debug
  virtual const char* GetName()
  {
    return self.name.c_str();
  }

  virtual TransactionHandler StartDataTransaction();
  virtual bool CommitDataTransaction(TransactionHandler h, bool publishAfterCommit);
  virtual TransactionHandler GetActiveDataTransaction() { return activeDataTransaction; }
  virtual bool ShareEntity(const GUID& srcId, EntityId id, const GUID& dstId, const GUID& entityGUID, bool delayedPacket) { return ptrs->ShareObject(dstId, entityGUID, delayedPacket); }
  virtual const GUID& GetGateID() const { return GetID(); }

  bool GetAllGUIDs( rpc::ILocalEntity* entity, nstl::vector<EntityGateInfo>& guids, GUID& entityGUID )
  {
    return ptrs->GetAllGUIDs( entity, guids, entityGUID );
  }

  const GUID& GetID() const { return self.guid; }
  TLogTrace GetLogTrace() { return logTrace; }
  const NodeDescription& GetDesc() const { return self; }

  void RegisterGate( const GUID& guid, rpc::IPacketPipe* pipe );
  StrongMT<rpc::IPacketPipe> GetPipeByGUID( const GUID& guid );

  virtual void Publish(EntityId entityId, rpc::ILocalEntity* entity) { PublishInternal(entityId, entity); }
  bool PublishInternal( EntityId entityId, ILocalEntity* entity, const byte* paramsData=0, int dataSize=0, const GUID* requestingGateId=0, const nstl::vector<rpc::LocalEntityInfo*>* createdEntities=0);

  virtual StrongMT<INode> GetNode(IPacketPipe* pipe);

  void Poll();
  void BroadcastForceLink(const GUID& entityGUID, const GUID& targetGateId, const GUID& sourceGateId, const GUID* lastSenderGateId);

  bool GetEntity( const GUID & key, StrongMT<rpc::IRemoteEntity> & entity );
  bool GetEntity( EntityId id, StrongMT<rpc::IRemoteEntity> & entity );

  bool PrepareEntityData( rpc::ArgWriter& args, ILocalEntity* entity );
private:
  Transaction* PrepareOrCopyEntityData(ILocalEntity* entity, const byte* paramsData, int dataSize, EntityId entityId, const GUID& entityGUID );

  RemoteEntityContainer ritems;
  uint AppendLocalEntity(void* instance, EntityId id, ILocalEntity* e, const GUID& entityGUID, uint classId);

  void _AppendLocalEntity( EntityId id, const GUID& entityGUID, ILocalEntity* e, void* value, uint classId );
  rpc::ILocalEntity* _CreateLocalEntity(void* instance, uint classId);

  ILocalEntity* _GetLocalEntity(void* value, RemoteEntityInfo& info);
  RemoteEntityContainer::iterator AppendEntity(const GUID& key, EntityHandler* handler, IRemoteEntity* instance);

  uint GenerateId()
  {
    return lastId++;
  }

  nstl::vector<Transaction*> transactions;
  int activeTransactionsCount;
  int totalTransactionsCount;
  int lastTransactionsCount;
  NHPTimer::STime lastReportTime;
  TransactionId transactionId;
  threading::Mutex transactionLocker;
  threading::Mutex objectsCreation;
  threading::Mutex lobjectsCreation;
  EntityId lastId;
  EntityFactoriesContainer& factoriesContainer;
  EntityPtrContainer entityPtrs;
  IDGenerator& idGenerator;
  LocalEntityInfoContainer instance2local;
  threading::Mutex& section; 
  INodes& nodes;
  IPipeProcessor* processor;
  CallsHandler* calls;
  LocalEntityNamedContainer namedLocalEntities;
  TransactionHandler activeDataTransaction;
  NodeDescription self;
  PtrSharing* ptrs;
  ILogTracer* logTrace;
  nstl::vector<PublishRequest> publishRequests;
};

} // rpc