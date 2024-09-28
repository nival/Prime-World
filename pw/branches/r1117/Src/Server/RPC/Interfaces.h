#pragma once

#include "System/Asserts.h"
#include "System/nstring.h"

#pragma warning(disable:4100)

#define _mng_INTSIZEOF(n)   ( (sizeof(n) + sizeof(int) - 1) & ~(sizeof(int) - 1) )
#define _mng_va_arg(ap,t)    ( *(t *)((ap += _mng_INTSIZEOF(t)) - _mng_INTSIZEOF(t)) )

//#include <RPC.h>
#include "Server/RPC/Types.h"
#include "System/Basic.h"
#include "Packets.h"
#include "IFunctor.h"
#include "IRemoteEntity.h"
#include "System/nvector.h"


namespace rpc 
{
typedef uint EntityId;
#define INVALID_ENTITY rpc::EntityId(-1)
template <typename T> 
uint GetId();

struct LocalInstanceInfo
{
  void* instance;
  StrongMT<IBaseInterfaceMT> object;
  uint classId;
  nstl::string gateName;
};

struct MethodCallHeader;
class Arguments;
class MethodCall;
class ArgReader;
class ArgWriter;
class EntityHandler;
class Node;
struct IUpdateCallback;

_interface IEntityMap;

_interface IUpdateCallback
{
  virtual void OnUpdated(const IRemoteEntity* entity)=0;
};

_interface IRemoteEntityFactory
{
  virtual rpc::IRemoteEntity* Create(uint classId, uint crc, rpc::EntityHandler* handler, rpc::IEntityMap* xxx, rpc::IRemoteEntity* _parent)=0;
};

void RegisterRemoteFactory(uint classId, rpc::IRemoteEntityFactory& factory);
void UnregisterRemoteFactory(uint classId);

template <typename T>
struct SimpleRemoteEntityFactory : rpc::IRemoteEntityFactory
{
  SimpleRemoteEntityFactory()
  {
    rpc::RegisterRemoteFactory(T::ID(), *this);
  }
  virtual rpc::IRemoteEntity* Create(uint classId, uint crc, rpc::EntityHandler* handler, rpc::IEntityMap* xxx, rpc::IRemoteEntity* _parent)
  {
    return new T(handler, _parent);
  }
  int dummy() const { return 0; }
};

namespace CallResult
{
  enum Enum
  {
    OK = 0,
    DataCorruption = 1,
    WrongMethodId = 2,
    WrongMethodCode = 3,
    LocalEntityNotFound = 4,
    StackCorruption = 5,
  };
}

_interface ILocalEntity : IBaseInterfaceMT
{
  NI_DECLARE_CLASS_1(ILocalEntity, IBaseInterfaceMT);
  virtual ~ILocalEntity() {}
  virtual bool vset(byte memberId, ArgReader& s) { return true; }
  virtual int GetMemberIndex(const void*)=0;
  virtual void* _Get(uint classId)=0;
  virtual uint GetClassCrc() const = 0;
  virtual void Update(rpc::ArgWriter* args) {}
  virtual rpc::CallResult::Enum Call(const MethodCallHeader& call, rpc::MethodCall& resultCall, rpc::Arguments& args, const byte* paramsData, int _paramsSize)=0;
  virtual void Publish() = 0;

  template<typename T>
  T* Get() { return (T*)_Get( rpc::GetId<T>()) ; }
};

struct LocalEntityCreationInfo
{
    uint classId;
    uint paramsCount;
    bool isReplicated;
    Node* originNode;
};

_interface ILocalEntityFactory
{
  virtual rpc::ILocalEntity* Create(const LocalEntityCreationInfo& entityInfo, rpc::Arguments& args, rpc::IEntityMap*)=0;
  virtual rpc::ILocalEntity* Create(uint classId, void* value, rpc::IEntityMap*) { return 0; }
  virtual void Destroy( rpc::ILocalEntity* entity ) {}
};

_interface ICallRoutine
{
  virtual ~ICallRoutine() {}
  virtual bool ProcessReturnValue(const MethodCallHeader& methodCall, const byte* paramsData, int _paramsSize, rpc::Arguments& args)=0;
  virtual void OnFailure(rpc::CallStatus status)=0;
  virtual VArgList Wait() { return 0; }
};

_interface INode : IBaseInterfaceMT
{
  NI_DECLARE_CLASS_1(INode, IBaseInterfaceMT);
  virtual ~INode() {}
  virtual IPacketPipe * GetConnectedPipe()=0;
  virtual void RemoveEntity(rpc::EntityHandler* handler, int index)=0;
  virtual int AppendEntity(rpc::EntityHandler* handler)=0;
  virtual bool Poll()=0;
  virtual bool IsReady() const=0;
  virtual const char* GetName() =0;
  virtual const NodeDescription& GetDesc() const=0;
  virtual bool IsConnected() const=0;
  virtual void DereplicateAll()=0;
};

_interface INodes
{
  virtual ~INodes() {}
  virtual StrongMT<INode> FindNode(IPacketPipe * pipe)=0;
  virtual StrongMT<IPacketPipe> GetPipe(const GUID& id, const char* name)=0;
  virtual bool IsNodeExist(const GUID& id)=0;
  virtual StrongMT<INode> GetNode(int index)=0;
};

_interface IEntityMap;

class _TransactionHandler
{
public:
  _TransactionHandler(IEntityMap* _entityMap, uint _handle):
  entityMap(_entityMap),
  handle(_handle)
  {
  }

  void Register(IRemoteEntity* entity)
  {
    items.push_back(entity);
  }
        
  bool Commit(bool publishAfterCommit);
  nstl::vector<IRemoteEntity*> items;
private:
  IEntityMap* entityMap;
  uint handle;
};

enum TraceDirection
{
  In,
  Out,
  Local,
};

struct ILogTracer 
{
  virtual ~ILogTracer()=0;
  virtual bool CheckLog(int _logLevel)=0;
  virtual void Trace(const char* format, ...)=0;
  virtual void TraceDetailed(const NodeDescription& dst, TraceDirection direction, const char* format, ...)=0;
};

inline ILogTracer::~ILogTracer() {}

typedef _TransactionHandler* TransactionHandler;

TransactionHandler StartTransaction(IRemoteEntity* e0);
TransactionHandler StartTransaction(IRemoteEntity* e0, IRemoteEntity* e1);
bool Commit(TransactionHandler h, bool publishAfterCommit=false);

struct LocalHandlerInfo
{
  int memberId;
  IFunctor* functor;
};

struct LocalEntityInfo : NonCopyable
{
  LocalEntityInfo():
  entity(0),
  classId(0),
  classCrc(0),
  password(0)
  {
  }

  LocalEntityInfo(rpc::ILocalEntity* entity, const GUID& _entityGUID, uint classId, unsigned long _password=0);

  void Set(const LocalEntityInfo& info, const GUID& _entityGUID)
  {
    entity = info.entity;
    classId = info.classId;
    password = info.password;
    entityGUID = _entityGUID;
  }

  void Clear()
  {
    entity = 0;
  }

  bool IsMatched(uint _classId, uint _classCrc, uint _password=0)
  {
    return (classId == _classId && entity->GetClassCrc() == _classCrc && password == _password);
  }

  rpc::ILocalEntity* Get() { return entity; }
  uint GetClassId() const { return classId; }
  const GUID& GetGUID() const { return entityGUID; }
  void* GetInstance() { return entity?entity->_Get(classId):0; }

  LocalHandlerInfo* getHandlerInfo(int memberId)  
  {
    for (int i=0;i<handled_members.size();++i)
    {
      if (handled_members[i].memberId == memberId) 
      {
        return &handled_members[i];
      }
    }
    return 0;
  }

  IFunctor* isHandled(int memberId) 
  {
    LocalHandlerInfo* info = getHandlerInfo(memberId);
    return info?info->functor:0;
  }

  void RemoveHandler(const LocalHandlerInfo& info)
  {
    for (int i=0;i<handled_members.size();++i)
    {
      if (&handled_members[i] == &info) 
      {
        handled_members.eraseByIndex(i);
        return;
      }
    }
  }

  void AddHandledMember(int memberId, IFunctor* functor)
  {
    LocalHandlerInfo info = { memberId, functor};
    handled_members.push_back(info);
  }
  void SetParent(rpc::ILocalEntity* _entity) { parent = _entity; }
private:
  StrongMT<rpc::ILocalEntity> entity;
  WeakMT<rpc::ILocalEntity> parent;
  uint classId;
  nival::uint32_t classCrc;
  GUID entityGUID;
  unsigned long password;
  nstl::vector<LocalHandlerInfo> handled_members;
};

template <typename T>
void RegisterRemoteFactory(T* instance=0);

typedef ILogTracer* TLogTrace;
 
namespace ECallResult
{
  enum Enum { OK=0, TooLargeData=1, NoTransaction=2, CorruptedArgs=3, OtherFail=4};
}

}
