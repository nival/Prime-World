#include "stdafx.h"
#include <System/IDGenerator.h>
#include "RPC.h"
#include "RPC/Types.h"
#include "System/LogFileName.h"
#include "System/FileSystem/FileUtils.h"
#include "System/InlineProfiler.h"
#include "System/ThreadLocal.h"
#include "System/ported/types.h"
#include "System/ported/cwfn.h"
#include "System/get_tick_count.h"
#include "System/Crc32Checksum.h"


namespace rpc
{

EntityFactoriesContainer& GetGlobalRemoteFactoryContainer();

class FileDumper 
{
#if defined( NV_WIN_PLATFORM )
  HANDLE hFile;
#elif defined( NV_LINUX_PLATFORM )
  int hFile;
#endif
  threading::Mutex locker;
  nstl::string name;

  bool StartLog()
  {
    threading::MutexLock lock( locker );

    string szOutFileName;
    string finalName = NDebug::GenerateDebugFileName( name.c_str(), "txt" );

#if defined( NV_WIN_PLATFORM )
    hFile = (HANDLE)NFile::OpenFileWithDir( finalName.c_str() );
    if ( hFile == INVALID_HANDLE_VALUE )
      return false;
    SetFilePointer( hFile, 0, 0, FILE_END );
#elif defined( NV_LINUX_PLATFORM )
    hFile = NFile::OpenFileWithDir( finalName.c_str() );
    if ( hFile == -1 )
      return false;
    lseek( hFile, 0, SEEK_END );
#endif
    return true;
  }

  bool StopLog()
  {
    threading::MutexLock lock( locker );
#if defined( NV_WIN_PLATFORM )
    if ( hFile != INVALID_HANDLE_VALUE )
      CloseHandle( hFile );
    hFile = INVALID_HANDLE_VALUE;
#elif defined( NV_LINUX_PLATFORM )
    if ( hFile != -1 )
      ::close( hFile );
    hFile = -1;
#endif
    return true;
  }
public:
#if defined( NV_WIN_PLATFORM )
  FileDumper(const char* _name) : hFile( INVALID_HANDLE_VALUE ) 
#elif defined( NV_LINUX_PLATFORM )
  FileDumper(const char* _name) : hFile( -1 ) 
#endif
  {
    name = nstl::string("rpc-")+nstl::string(_name);
  }
  ~FileDumper() { StopLog(); }
  bool Enable( bool isEnabled )
  {
#if defined( NV_WIN_PLATFORM )
    if ( isEnabled && hFile == INVALID_HANDLE_VALUE )
      return StartLog();
    if ( !isEnabled && hFile != INVALID_HANDLE_VALUE )
      return StopLog();
#elif defined( NV_LINUX_PLATFORM )
    if ( isEnabled && hFile == -1 )
      return StartLog();
    if ( !isEnabled && hFile != -1 )
      return StopLog();
#endif
    return false;
  }

  bool IsLogging() const 
  {
#if defined( NV_WIN_PLATFORM )
    return ( hFile != INVALID_HANDLE_VALUE );
#elif defined( NV_LINUX_PLATFORM )
    return ( hFile != -1 );
#endif
  }

  void AddLogString( const char* str, int len )
  {
#if defined( NV_WIN_PLATFORM )
    if ( hFile == INVALID_HANDLE_VALUE )
      return;
#elif defined( NV_LINUX_PLATFORM )
    if ( hFile == -1 )
      return;
#endif
    threading::MutexLock lock( locker );

    int dummy = 0;
#if defined( NV_WIN_PLATFORM )
    WriteFile( hFile, str, len, (DWORD*)&dummy, 0 );
#elif defined( NV_LINUX_PLATFORM )
    dummy = ::write( hFile, str, len );
#endif
    OutputDebugString( str );
  }
};

static const int BUFFER_LENGTH = 512;
struct LogBuffer
{
  char buffer[BUFFER_LENGTH];
};

static ThreadLocal<LogBuffer> logBuffer;

struct LogTracer : public ILogTracer
{
  LogTracer(const NodeDescription& desc):rpcFileDumper(GUIDString(desc.guid).GetValue()), desc(desc)
  {
    logLevel = 0;
  }

  virtual void Trace(const char* format, ...)
  {
    va_list va;
    va_start( va, format);
    _Trace(0, 0, rpc::Local, format, va);
    va_end(va);
  }

  virtual void TraceDetailed(const NodeDescription& dst, TraceDirection direction, const char* format, ...)
  {
    va_list va;
    va_start( va, format);
    _Trace(&desc, &dst, direction, format, va);
    va_end(va);
  }

  virtual bool CheckLog(int _logLevel)
  {
    if (rpc::GetLogLevel() != logLevel)
    {
      if (rpcFileDumper.Enable(rpc::GetLogLevel() != 0))
      {
        logLevel = rpc::GetLogLevel();
      }
    }
    return logLevel >= _logLevel && rpcFileDumper.IsLogging();
  }
private:
  void _Trace(const NodeDescription* src, const NodeDescription* dst, TraceDirection direction, const char* format, va_list va)
  {
    char* buf = logBuffer.GetValue().buffer;
    int offset = 0;
    offset += NStr::Printf(buf+offset, BUFFER_LENGTH-1-offset, "(%d) %d: ", threading::CurrentThreadID(), nival::get_tick_count());
    if (direction == rpc::Local)
    {
      offset += OutputDesc(*src, buf, offset);
    }
    else
    {
      if (src && dst)
      {
        offset += OutputDesc(*src, buf, offset);
        offset += NStr::Printf(buf+offset, BUFFER_LENGTH-1-offset, " %s ", direction==rpc::Out?"->":"<-");
        offset += OutputDesc(*dst, buf, offset);
      }
      else
      {
        offset += NStr::Printf(buf+offset, BUFFER_LENGTH-1-offset, "<local>");
      }
    }
    offset += NStr::Printf(buf+offset, BUFFER_LENGTH-1-offset, ": ");
    {
#if defined( NV_WIN_PLATFORM )
      offset += vsnprintf_s( buf+offset, BUFFER_LENGTH - 1-offset, BUFFER_LENGTH - 1, format, va );
#elif defined( NV_LINUX_PLATFORM )
      offset += vsnprintf( buf+offset, BUFFER_LENGTH - 1-offset, BUFFER_LENGTH - 1, format, va );
#endif
    }
    offset += NStr::Printf(buf+offset, BUFFER_LENGTH-1-offset, "\n");
    rpcFileDumper.AddLogString( buf, offset );
  }

  int OutputDesc( const NodeDescription &src, char* buf, int offset)
  {
    if (src.name.size() > 0)
    {
      return NStr::Printf(buf+offset, BUFFER_LENGTH-1-offset, "%s", src.name.c_str());
    } else
      if (src.IsIdentified())
      {
        return NStr::Printf(buf+offset, BUFFER_LENGTH-1-offset, "%s", GUIDString(src.guid).GetValue());
      } else
      {
        return NStr::Printf(buf+offset, BUFFER_LENGTH-1-offset, "<unknown>");
      }
  }
  FileDumper rpcFileDumper;
  int logLevel;
  const NodeDescription& desc;
};

EntityMap::EntityMap(
          threading::Mutex& _section, 
          IDGenerator& _idGenerator, 
          EntityFactoriesContainer& _factoriesContainer,
          INodes& _nodes,
          IPipeProcessor* _processor):
section(_section),
idGenerator(_idGenerator),
lastId(0), 
factoriesContainer(_factoriesContainer),
activeDataTransaction(0),
activeTransactionsCount(0),
totalTransactionsCount(0),
lastTransactionsCount(0),
transactionId(0),
nodes(_nodes),
processor(_processor)
{
  NHPTimer::GetTime(lastReportTime);
  self.Generate();
  if (processor)
  {
    const char* name = processor->GetName();
    if (name)
    {
      self.name = name;
    }
  }
  logTrace = new LogTracer(GetDesc());
  ptrs = new PtrSharing(self, logTrace);
  calls = new CallsHandler(logTrace);
}


rpc::ILocalEntity* EntityMap::_CreateLocalEntity(void* instance, uint classId)
{
  rpc::ILocalEntityFactory* factory = factoriesContainer.GetFactory<rpc::ILocalEntityFactory>( classId );
  if (factory)
  {
    return factory->Create(classId, instance, this);
  }
  return 0;
}

ILocalEntity* EntityMap::CreateLocalEntity(void* instance, RemoteEntityInfo& info, uint classId)
{
  info.typeInfo.classId = classId;
  rpc::ILocalEntity* e = _GetLocalEntity(instance, info);
  if (e)
  {
    ptrs->RegisterObject(e, GetID(), info.entityId, info.entityGUID, true);
    return e;
  }
  rpc::ILocalEntityFactory* factory = factoriesContainer.GetFactory<rpc::ILocalEntityFactory>( classId );
  if (factory)
  {
    e = factory->Create(classId, instance, this);
    if (e)
    {
      {
        threading::MutexLock locker(objectsCreation);
        info.entityId = GenerateId();
      }
      ::UuidCreate(&info.entityGUID);
      info.typeInfo.classCrc = AppendLocalEntity(instance, info.entityId, e, info.entityGUID, classId);
      return e;
    } else
    {
      NI_ALWAYS_ASSERT(NI_STRFMT( "Can't create local entity: classId(0x%0X)", classId));
      return 0;
    }
  } 
  NI_ALWAYS_ASSERT(NI_STRFMT( "Local entity factory not found: classId=0x%0x, classCrc=0x%08x", info.typeInfo.classId, info.typeInfo.classCrc));
  return 0;
}

ILocalEntity* EntityMap::_GetLocalEntity(void* value, RemoteEntityInfo& info)
{
  threading::MutexLock locker(lobjectsCreation);
  LocalEntityInstanceInfo linfo(value, info.typeInfo.classId);
  LocalEntityInfoContainer::iterator it = instance2local.find(linfo.key);
  if (it != instance2local.end())
  {
    Original2LocalEntityInfo& linfo = it->second;
    StrongMT<ILocalEntity> entity = linfo.entity.Lock();
    if (!entity)
    {
      instance2local.erase(it);
      return 0;
    }
    info.entityId = linfo.entityId;
    info.typeInfo.classCrc = entity->GetClassCrc();
    info.entityGUID = linfo.entityGUID;
    return entity;
  }
  return 0;
}

void EntityMap::_AppendLocalEntity( EntityId id, const GUID& entityGUID, ILocalEntity* e, void* value, uint classId )
{
  threading::MutexLock locker(lobjectsCreation);
  LocalEntityInstanceInfo linfo(value, classId);
  Original2LocalEntityInfo ol = { id, entityGUID, e };
  instance2local.insert(linfo.key)->second = ol;
}

uint EntityMap::AppendLocalEntity(void* value, EntityId id, ILocalEntity* e, const GUID& entityGUID, uint classId)
{
  _AppendLocalEntity(id, entityGUID, e, value, classId);
  ptrs->RegisterObject(e, GetID(), id, entityGUID, true);
  return e->GetClassCrc();
}

void EntityMap::_RemoveLocalEntity( void* instance, uint classId )
{
  NI_VERIFY(instance, "Original instance query failed", return);
  threading::MutexLock locker(lobjectsCreation);
  LocalEntityInstanceInfo linfo(instance, classId);
  LocalEntityInfoContainer::iterator it = instance2local.find(linfo.key);
  if (it != instance2local.end())
  {
    instance2local.erase(it);
  }
}

bool EntityMap::RegisterRemoteObject(rpc::ILocalEntity* entity, GUID source, rpc::EntityId id, const GUID& entityGUID, bool isLocal, uint classId)
{
  _AppendLocalEntity(id, entityGUID, entity, entity->_Get(classId), classId);
  return ptrs->RegisterObject(entity, source, id, entityGUID, isLocal);
}

bool EntityMap::UnregisterRemoteObject(GUID source, rpc::EntityId id, const GUID& entityGUID, void* instance, uint classId)
{
  NI_PROFILE_FUNCTION;
  _RemoveLocalEntity(instance, classId);
  ptrs->UnregisterObject(source, id, entityGUID);
  return true;
}

bool EntityMap::ProcessReturnValue( const MethodCallHeader& call, const byte* paramsData, uint paramsSize, rpc::Arguments& args )
{
  NI_PROFILE_FUNCTION;

  bool result = false;
  CallsMapInfo::Status status;
  rpc::ICallRoutine* r = calls->UnregisterCall(call, status);
  if (r)
  {
    result = r->ProcessReturnValue(call, paramsData, paramsSize, args);
    delete r;
  }
  else
  if (CallsMapInfo::TransactionNotFound == status)
  {
    WarningTrace("Can't find transaction for return value(datasize=%d)", call.dataSize);
    result = true;
  }
  else
  {
    NI_ALWAYS_ASSERT( NI_STRFMT("Can't find call routine, reason = \"%s\"", CallsMapInfo::GetReason(status)) );
  }

  return result;
}

RemoteEntityContainer::iterator EntityMap::AppendEntity(const GUID& key, EntityHandler* handler, IRemoteEntity* instance)
{
  threading::MutexLock locker(objectsCreation);
  EntityId entityId = idGenerator.Generate();
  LogTrace2(self, rpc::Local, "append entity (eid=%d euid=%s)", entityId, GUIDString(key).GetValue());
  ritems[entityId] = RemoteEntityInfo_(handler, instance);
  entityPtrs[key] = instance;
  return ritems.find(entityId);
}

Transaction* EntityMap::StartTransaction(EntityId entityId, bool isReady)
{
  Transaction* result = 0;
  {
    threading::MutexLock lock(transactionLocker);
    transactionId++;
    activeTransactionsCount ++;
    totalTransactionsCount++;
    if (transactions.size() > 0)
    {
      result = *(transactions.end()-1);
      transactions.pop_back();
    } else
    {
      result = new Transaction();
    }
  }
  result->Reset(entityId, transactionId, this);
  if (isReady)
  {
    result->SetReady();
  }
  return result;
}

void EntityMap::StopTransaction(Transaction* t)
{
  NI_ASSERT(activeTransactionsCount > 0, "No active tranactions");
  bool result = true;
  rpc::ArgReader& s = t->StartRollback();
  for (int i=t->GetParams().size()-1;i>=0;i--)
  {
    const MarshalledParam& param = t->GetParams()[i];
    s.Reset(t->Get(param.offset), param.size, 0);
    ParamInfo type = s.PopTypeCode(result); 
    if (result && rpc::Byte1 == type.code) 
    {
      s.PopRaw<byte>(result); // memberId
      if (result) 
      {
        s.Revert(result);
      }
    } else
    {
      NI_ALWAYS_ASSERT(NI_STRFMT( "Parameter parsing failed (index=%d)", i));
    }
  }
  {
    threading::MutexLock lock(transactionLocker);
    transactions.push_back(t);
    activeTransactionsCount--;
    t->Clear();
  }
}

bool EntityMap::RollbackTransaction(Transaction* t, IRemoteEntity* entity)
{
  bool result = true;
  rpc::ArgReader& s = t->StartRollback();
  for (int i=t->GetParams().size()-1;i>=0;i--)
  {
    const MarshalledParam& param = t->GetParams()[i];
    s.Reset(t->Get(param.offset), param.size, 0);
    ParamInfo type = s.PopTypeCode(result); 
    if (result && rpc::Byte1 == type.code) 
    {
      uint memberId = s.PopRaw<byte>(result);
      if (result) 
      {
        bool isMember = s.Pop<bool>(result);
        isMember;
        if (result)
        {
          result = entity->RollbackMember(memberId, s);
        }
      }
    } else
    {
      NI_ALWAYS_ASSERT(NI_STRFMT( "Parameter parsing failed (index=%d)", i));
      result = false;
    }
  }
  return result;
}

bool EntityMap::UnregisterObject(uint classId, void* value)
{
  for (LocalEntityNamedContainer::iterator it=namedLocalEntities.begin();it != namedLocalEntities.end();++it)
  {
    LocalEntityInfo* info = it->second;
    const nstl::string& name = it->first; 
    name;
    if (info->Get()->_Get(classId) == value)
    {
      info->Clear();
      delete info;
      namedLocalEntities.erase(it);
      return true;
    } 
  }
  return false;
}


bool EntityMap::RegisterObject( rpc::ILocalEntity* e, const char* path, const char* password, uint classId )
{
  NI_VERIFY(classId != 0xFFFFFFFF, NI_STRFMT( "Can't register instance with invalid classId"), return false);
  NI_VERIFY(e, NI_STRFMT( "Can't register null instance"), return false);
  Crc32Checksum hashCode;
  if (password)
  {
    hashCode.AddString(password);
  }
  GUID nullGUID = { 0, 0, 0, 0 };
  namedLocalEntities[path] = new LocalEntityInfo(e, nullGUID, classId, hashCode.Get()); 
  return true;
}

LocalEntityInfo* EntityMap::GetRegisteredLocalEntity(const char* path)
{
  LocalEntityNamedContainer::iterator it = namedLocalEntities.find(path); // TODO: addRef
  return (it != namedLocalEntities.end())?(it->second):0;
}

StrongMT<IPacketPipe> EntityMap::ConnectToPipe(const char* name, const GUID& id)
{
  StrongMT<IPacketPipe> result = nodes.GetPipe(id, name);
  if (!result && processor)
  {
    result = processor->ConnectToPipe(name, id);
  }
  NI_ASSERT(result, NI_STRFMT("Connection to pipe failed (name=%s)", name?name:"<empty>"));
  return result;
}

void EntityMap::RemoveNode(INode* node)
{
  NI_PROFILE_HEAVY_FUNCTION;

  const GUID& nodeId = node->GetDesc().guid;
  for (nstl::vector<PublishRequest>::iterator it=publishRequests.begin();it!=publishRequests.end();)
  {
    if (it->gateId == nodeId)
    {
      publishRequests.erase(it);
    } else
    {
      ++it;
    }
  }
  ptrs->RemoveGate(nodeId);
  node->DereplicateAll();
}

EntityMap::~EntityMap()
{
  for (LocalEntityNamedContainer::iterator it=namedLocalEntities.begin();it != namedLocalEntities.end(); ++it)
  {
    it->second->Clear();
    delete it->second;
  }
/*
  int index = 0;
  while (index < entityPtrs.size())
  {
    int oldSize = entityPtrs.size();
    EntityPtrContainer::iterator it = entityPtrs.begin();
    for (int i=0;i<index;i++,it++) ;
    StrongMT<rpc::IRemoteEntity> entity = it->second.Lock(); 
    it->second = 0; 
    int newSize = entityPtrs.size();
    if (newSize == oldSize)
    {
      index += 1;
    } 
  }
*/
  for (int i=0;i<transactions.size();++i)
  {
    delete transactions[i];
  }

  NI_VERIFY(activeTransactionsCount == 0, "Active transactions count should be 0", ;);
  if (activeDataTransaction)
  {
    delete activeDataTransaction;
    activeDataTransaction = 0;
  }
  ptrs->RemoveGate(self.guid);
  delete calls;
  delete ptrs;
  delete logTrace;
  logTrace = 0;
}

bool EntityMap::GetEntity(const GUID& key, StrongMT<rpc::IRemoteEntity>& entity)
{
  threading::MutexLock locker(objectsCreation);
  EntityPtrContainer::iterator it = entityPtrs.find(key);
  if (it != entityPtrs.end())
  {
    entity = it->second.Lock();   
    return true;
  } 
  return false;
} 

bool EntityMap::GetEntity(EntityId entityId, StrongMT<rpc::IRemoteEntity>& entity)
{
  threading::MutexLock locker(objectsCreation);
  RemoteEntityContainer::iterator it = ritems.find(entityId);
  if (it != ritems.end())
  {
    entity = it->second.instance;
    return true;
  }
  return false;
}

void EntityMap::RemoveEntity(IRemoteEntity& entity)
{
  threading::MutexLock tlocker(section);
  EntityHandler* handler = entity.GetHandler();
  EntityId id = handler->GetId();

  threading::MutexLock locker(objectsCreation);

  if (!handler->IsShared())
  {
    idGenerator.Release(id);
  }
  {
    RemoteEntityContainer::iterator it = ritems.find(id);
    if (it != ritems.end())
    {
      if (it->second.handler == handler)
      {
        ritems.erase(it);
      } else
      {
        NI_ALWAYS_ASSERT("Could't find entity");
      }
    } else
    {
      NI_ALWAYS_ASSERT("Could't find entity");
    }
  }
  LogTrace2(self, rpc::Local, "remove entity (euid=%s)", GUIDString(handler->GetGUID()).GetValue());
  EntityPtrContainer::iterator it = entityPtrs.find(handler->GetGUID());
  if (it != entityPtrs.end()) 
  {
    entityPtrs.erase(it);
  }
}

StrongMT<INode> EntityMap::GetNode( IPacketPipe * pipe )
{
  return pipe?nodes.FindNode( pipe ) : 0;
}

IRemoteEntity* EntityMap::ConnectToEntity(
  const RemoteEntityInfo& info, 
  const char* sourceNode, 
  const char* targetNode, 
  const GUID& lnodeId, 
  IRemoteEntityFactory* factory, 
  const GUID& sourceId, 
  rpc::IRemoteEntity* _parent)
{
  StrongMT<rpc::IRemoteEntity> entity;
  LogTrace3(self, rpc::Local, "connect to entity (euid=%s)", GUIDString(info.entityGUID).GetValue());
  if (GetEntity(info.entityGUID, entity))
  {
    if (entity && entity->GetHandler())
    {
      return entity;
    }
  }

  EntityCreationInfo cinfo = {info.typeInfo.classId, info.typeInfo.classCrc, true, true };
  RemoteEntityInfo_ einfo = CreateEntity(cinfo, factory, &info.entityGUID, _parent);
  if ( !einfo.handler ) { return 0; }
  einfo.handler->RegisterNode(0, targetNode, lnodeId);
  einfo.handler->Construct(sourceNode, info.entityId, sourceId, info.entityGUID);
  if (!sourceNode)
  {
    einfo.handler->ConnectToNodes(this);
  }
  /*
  if (pipe)
  {
    const char* typeName = einfo.instance->ClassName();
    if ( sourceNode )
      LogTrace( "%s->%s: send link %s:%d to %s:%s:%d", GetGateName(), pipe->GetName(), typeName, einfo.handler->GetId(), sourceNode, typeName, info.entityId );
    else
      LogTrace( "%s->%s: send link %s:%d to %s:%d (local)", GetGateName(), pipe->GetName(), typeName, einfo.handler->GetId(), targetNode, info.entityId );
  } */
  return einfo.instance;
}

RemoteEntityInfo_ EntityMap::CreateEntity(const EntityCreationInfo& info, IRemoteEntityFactory* _factory, const GUID* _entityGUID, rpc::IRemoteEntity* _parent)
{
  GUID entityGUID;
  if (_entityGUID)
  {
    entityGUID = *_entityGUID;
  } else
  {
    ::UuidCreate(&entityGUID);
  }
  IRemoteEntity* instance = 0;
  IRemoteEntityFactory* factory = _factory?_factory:GetGlobalRemoteFactoryContainer().GetFactory<IRemoteEntityFactory>(info.classId);
  if (!factory)
  {
    NI_ALWAYS_ASSERT( NI_STRFMT( "Could't find factory for %d", info.classId ) );
    return RemoteEntityInfo_();
  }

  EntityHandler* handler = new EntityHandler(this, entityGUID, GetLogTrace());
  
  instance = factory->Create(info.classId, info.classCrc, handler, this, _parent);
  if (!instance)
  {
    NI_ALWAYS_ASSERT( NI_STRFMT( "Could't create remote entity" ) );
    return RemoteEntityInfo_();
  }
  RemoteEntityContainer::iterator it = AppendEntity(entityGUID, handler, instance);
  handler->SetEntityInfo( info, it->first, instance->ClassName() );

  /*if ( !info.isQueried )
    LogTrace( "%s->%s: send create %s:%d (crc=%8.8X replicated=%d)", GetGateName(), node->GetName(), einfo.instance->ClassName(), entityId, info.classCrc, info.isShared );*/
   return it->second;
}

const char* CallsMapInfo::GetReason(Status _status)
{
  switch (_status)
  {
  case OK: return "OK";
  case EntityNotFound : return "EntityNotFound";
  case MethodCallNotFound : return "MethodCallNotFound";
  case TransactionNotFound : return "TransactionNotFound";
  }
  return "<UnknownError>";
}

CallsHandler::~CallsHandler()
{
  threading::MutexLock lock(section);
  for ( EntitiesMap::iterator emIt = calls.begin(); emIt != calls.end(); emIt++ )
  {
    for ( MethodsMap::iterator mmIt = emIt->second.begin(); mmIt != emIt->second.end(); mmIt++ )
    {
      for ( CallsMap::iterator cmIt = mmIt->second.begin(); cmIt != mmIt->second.end(); cmIt++ )
      {
        RoutineInfo& info = cmIt->second;
        info.routine->OnFailure(rpc::PipeDisconnected); 
        delete info.routine;
      }
    }
  }
}

void CallsHandler::RegisterCall(const MethodCallHeader& header, ICallRoutine& r, float timeout)
{
  if ( rpc::GetLogLevel() == 2)
  {
    LOG_M(0).Trace( "register call: %d %d %d", header.entityId, header.id, header.transactionId);
  }
  threading::MutexLock lock(section);
  CallsMap::iterator c = _FindRoutine(header.entityId, header.id, header.transactionId); 
  c->second.Set(&r, timeout);
}

rpc::ICallRoutine* CallsHandler::UnregisterCall(const MethodCallHeader& call, CallsMapInfo::Status& _status)
{
  if ( rpc::GetLogLevel() == 2) 
  {
    LOG_M(0).Trace( "unregister call: %d %d %d", call.entityId, call.id, call.transactionId);
  }

  threading::MutexLock lock(section);
  CallsMapInfo c = _GetRoutine(call);
  _status = c.status;
  if (c.container != 0)
  {
    rpc::ICallRoutine* r = c.it->second.routine;
    c.container->erase(c.it);
    return r;
  }
  return 0;
}

uint CallsHandler::CancelAsyncCalls(EntityId id)
{
  threading::MutexLock lock(section);
  uint totalCallsCanceled = 0;
  EntitiesMap::iterator emIt = calls.find(id);
  if (emIt != calls.end())
  {
    for ( MethodsMap::iterator mmIt = emIt->second.begin(); mmIt != emIt->second.end(); mmIt++ )
    {
      for ( CallsMap::iterator cmIt = mmIt->second.begin(); cmIt != mmIt->second.end(); )
      {
        RoutineInfo& info = cmIt->second;
        info.routine->OnFailure(rpc::PipeDisconnected); 
        delete info.routine;
        cmIt = mmIt->second.erase(cmIt);
        totalCallsCanceled++;
      }
    }
  }
  return totalCallsCanceled;
}

int CallsHandler::CheckTimeouts(const NHPTimer::STime& curTime)
{
  NI_PROFILE_FUNCTION;
  int callsCount = 0;
  threading::MutexLock lock(section);
  for ( EntitiesMap::iterator emIt = calls.begin(); emIt != calls.end(); emIt++ )
  {
    for ( MethodsMap::iterator mmIt = emIt->second.begin(); mmIt != emIt->second.end(); mmIt++ )
    {
      for ( CallsMap::iterator cmIt = mmIt->second.begin(); cmIt != mmIt->second.end(); )
      {
        RoutineInfo& info = cmIt->second;
        if (info.IsTimedOut(curTime))
        {
          info.routine->OnFailure(rpc::CallTimedOut);
          delete info.routine;
          cmIt = mmIt->second.erase(cmIt);
        } else
        {
          cmIt++;
        }
        callsCount++;
      }
    }
  }
  return callsCount;
}

CallsMapInfo CallsHandler::_GetRoutine(const MethodCallHeader& call)
{
  CallsMapInfo result = {0, CallsMap::iterator(), CallsMapInfo::OK};
  EntitiesMap::iterator e = calls.find(call.entityId);
  if (e != calls.end())
  {
    MethodsMap::iterator m = e->second.find(call.id);
    if (m != e->second.end())
    {
      CallsMap::iterator c = m->second.find(call.transactionId);
      if (c != m->second.end())
      {
        result.container = &m->second;
        result.it = c;
      } else
      {
        result.status = CallsMapInfo::TransactionNotFound;
      }
    } else
    {
      result.status = CallsMapInfo::MethodCallNotFound;
    }
  } else
  {
    result.status = CallsMapInfo::EntityNotFound;
  }
  return result;
}

CallsMap::iterator CallsHandler::_FindRoutine(EntityId entityId, uint methodId, TransactionId transactionId)
{
  EntitiesMap::iterator e = calls.find(entityId);
  if (e == calls.end())
  {
    e = calls.insert(entityId);
  } 
  MethodsMap::iterator m = e->second.find(methodId);
  if (m == e->second.end())
  {
    m = e->second.insert(methodId);
  }
  CallsMap::iterator c = m->second.find(transactionId);
  if (c == m->second.end())
  {
    c = m->second.insert(transactionId);
  }
  return c;
}

TransactionHandler StartTransaction(IRemoteEntity* e0)
{
  WeakMT<rpc::IEntityMap>& entityMap = e0->GetHandler()->GetEntityMap();
  StrongMT<rpc::IEntityMap> sentityMap = entityMap.Lock();
  if (sentityMap)
  {
    TransactionHandler h = sentityMap->StartDataTransaction();
    h->Register(e0);
    return h;
  }
  return 0;
}

TransactionHandler StartTransaction(IRemoteEntity* e0, IRemoteEntity* e1)
{
  WeakMT<rpc::IEntityMap>& entityMap = e0->GetHandler()->GetEntityMap();
  StrongMT<rpc::IEntityMap> sentityMap = entityMap.Lock();
  if (sentityMap)
  {
    TransactionHandler h = sentityMap->StartDataTransaction();
    h->Register(e0);
    h->Register(e1);
    return h;
  }
  return 0;
}


bool _TransactionHandler::Commit(bool publishAfterCommit)
{
  return entityMap->CommitDataTransaction(this, publishAfterCommit);
}

bool Commit(TransactionHandler h, bool publishAfterCommit)
{
  return h->Commit(publishAfterCommit);
}

TransactionHandler EntityMap::StartDataTransaction()
{
  NI_VERIFY(activeDataTransaction == 0, "Data transaction already on the way, aborted", return 0);
  activeDataTransaction = new _TransactionHandler(this, 0);
  return activeDataTransaction;
}

bool EntityMap::CommitDataTransaction(TransactionHandler h, bool publishAfterCommit)
{
  if (activeDataTransaction && activeDataTransaction == h)
  {
    for (int i=0;i<h->items.size();++i)
    {
      h->items[i]->Commit(publishAfterCommit);
    }
    delete h;
    activeDataTransaction = 0;
    return true;
  }
  return false;
}

void EntityMap::Poll()
{
  NI_PROFILE_FUNCTION;

  for (nstl::vector<PublishRequest>::iterator it=publishRequests.begin();it!=publishRequests.end();)
  {
    bool deleteEntry = false;

    StrongMT<rpc::ILocalEntity> entity = it->entity.Lock();
    if (entity)
    {
      NI_PROFILE_BLOCK( "publishRequests item" );

      StrongMT<rpc::IPacketPipe> pipe = GetPipeByGUID( it->gateId );
      if (pipe)
      {
        if (it->entityId == INVALID_ENTITY)
        {
          it->entityId = ptrs->GetEntityId(it->entityGUID, it->gateId);
        }
        Transaction* transaction = PrepareOrCopyEntityData(entity, 0, 0, it->entityId, it->entityGUID);
        if (transaction && it->entityId != INVALID_ENTITY)
        {
          transaction->SetEntityInfo(it->entityId, entity->GetClassCrc()); 
          transaction->Go( pipe );
          deleteEntry = true;
        }
        StopTransaction(transaction);
      }
    } else
    {
      deleteEntry = true;
    }
    if (deleteEntry)
    {
      publishRequests.erase(it);
    } else
    {
      ++it;
    }
  }
  NHPTimer::STime curTime;
  NHPTimer::GetTime(curTime);
  int callsCount = calls->CheckTimeouts(curTime);
  if (rpc::GetReportFreq() != 0 && NHPTimer::Time2Seconds(curTime-lastReportTime) > rpc::GetReportFreq())
  {
     lastReportTime = curTime;
     int tempTransactionsCount;
     {
       threading::MutexLock lock(transactionLocker);
       tempTransactionsCount = totalTransactionsCount;
     }
     int rentitiesCount;
     {
       threading::MutexLock lock(objectsCreation);
       rentitiesCount = entityPtrs.size();
     }
     int lentitiesCount;
     {
       threading::MutexLock locker(lobjectsCreation);
       lentitiesCount = instance2local.size();
     }
     LOG_M(0).Trace("RO: calls(total=%d diff=%d wait=%d) objs(rcount=%d lcount=%d)", tempTransactionsCount, tempTransactionsCount-lastTransactionsCount, callsCount, rentitiesCount, lentitiesCount);
     lastTransactionsCount = tempTransactionsCount;
  }
}

bool EntityMap::PrepareEntityData( rpc::ArgWriter& args, ILocalEntity* entity )
{
  args.Push(entity->GetClassCrc());
  int currentIndex = args.size();
  args.PushRaw(int(0));
  uint currentSize = args.size();
  entity->Update(&args);
  if (args.size() > currentSize)
  {
    byte* dataSizePtr = args.GetBuffer(currentIndex);
    *((int*)dataSizePtr) = args.size()-currentSize;
    return true;
  } 
  return false;
}

Transaction* EntityMap::PrepareOrCopyEntityData(ILocalEntity* entity, const byte* paramsData, int dataSize, EntityId entityId, const GUID& entityGUID )
{
  Transaction* transaction = StartTransaction(INVALID_ENTITY);
  if (transaction)
  {
    transaction->Prepare(rpc::UpdateData, entity->GetClassCrc(), true);
    rpc::ArgWriter& args = transaction->GetArgs();
    if (entityId == INVALID_ENTITY)
    {
      args.Push(entityGUID);
    }
    if (paramsData)
    {
      args.Push(entity->GetClassCrc());
      args.PushRaw(dataSize);
      args.Copy(paramsData, dataSize);
    } else
    {
      PrepareEntityData(args, entity);
    }
  }	
  return transaction;
}

void EntityMap::BroadcastForceLink(const GUID& entityGUID, const GUID& targetGateId, const GUID& sourceGateId, const GUID* lastSenderGateId)
{
  Transaction* transaction = StartTransaction(INVALID_ENTITY);
  if (transaction)
  {
    transaction->Prepare(rpc::ForceLink, 0, true);
    rpc::ArgWriter& args = transaction->GetArgs();
    rpc::GateInfo gateInfo = { self.guid, rpc::GateInfo::PROTOCOL_VERSION };
    args.Push(gateInfo);   
    args.Push(sourceGateId);
    args.Push(entityGUID); 
    args.Push(targetGateId);  

    StrongMT<rpc::IPacketPipe> pipe = nodes.GetPipe( targetGateId, 0 );
    if (pipe)
    {
      transaction->Go( pipe );
    } else
    {
      int index = 0;
      while ( StrongMT<INode> node = nodes.GetNode(index++))
      {
        if (!lastSenderGateId || *lastSenderGateId == node->GetDesc().guid)
        {
          transaction->Go(node->GetConnectedPipe());
        }
      }
    }
    StopTransaction(transaction);
  }
}

bool EntityMap::PublishInternal( EntityId entityId, ILocalEntity* entity, const byte* paramsData, int dataSize, const GUID* requestingGateId, const nstl::vector<rpc::LocalEntityInfo*>* createdEntities)
{
  nstl::vector<EntityGateInfo> guids;

  GUID entityGUID;
  if (GetAllGUIDs(entity, guids, entityGUID))
  {
    Transaction* transaction = 0;

    for ( int i = 0; i < guids.size(); i++ )
    {
      if (!requestingGateId || (*requestingGateId != guids[i].gateId && guids[i].gateId != self.guid))
      {
        if (createdEntities)
        {
          for (int j=0;j<createdEntities->size();++j)
          {
            rpc::LocalEntityInfo* info = (*createdEntities)[j];
            ptrs->ShareObject(guids[i].gateId, info->GetGUID(), false );
          }
        }
        StrongMT<rpc::IPacketPipe> pipe = GetPipeByGUID( guids[i].gateId );
        if (pipe)
        {
          if (!transaction)
          {
            transaction = PrepareOrCopyEntityData(entity, paramsData, dataSize, guids[i].entityId, entityGUID);
          }
          if (transaction)
          {
            transaction->SetEntityInfo(guids[i].entityId, entity->GetClassCrc()); 
            transaction->Go(pipe);
          }
          if (createdEntities)
          {
            for (int j=0;j<createdEntities->size();++j)
            {
              rpc::LocalEntityInfo* info = (*createdEntities)[j];
              Transaction* entityTransaction = PrepareOrCopyEntityData(info->Get(), 0, 0, INVALID_ENTITY, info->GetGUID());
              if (entityTransaction)
              {
                entityTransaction->SetEntityInfo(INVALID_ENTITY, 0); 
                entityTransaction->Go(pipe);
                StopTransaction(entityTransaction);
              }
            }
          }
        }
        else
        {
          PublishRequest& request = publishRequests.push_back();
          request.gateId = guids[i].gateId;
          request.entityId = guids[i].entityId;
          request.entity = entity;
          request.entityGUID = entityGUID;
          BroadcastForceLink(entityGUID, guids[i].gateId, self.guid, 0);
        }
      }
    }
    if (transaction)
    {
      StopTransaction(transaction);
    }
  }
  return true;
}

void EntityMap::RegisterGate( const GUID& guid, rpc::IPacketPipe* pipe )
{
  nodes.IsNodeExist(guid);
}

StrongMT<rpc::IPacketPipe> EntityMap::GetPipeByGUID( const GUID& guid )
{
  return nodes.GetPipe(guid, 0);
}

PtrSharing::~PtrSharing()
{
  for (EntityEntryMap::iterator it=entities.begin();it!=entities.end();++it)
  {
    delete it->second;
  }
}

PtrSharing::EntityEntryIt PtrSharing::_GetEntityEntry( const GUID& entityGUID, bool createIfNotFound)
{
  EntityEntryIt result;
  result.it = entities.find(entityGUID);
  if (result.it != entities.end())
  {
    result.entry = result.it->second;
    result.isNew = false;
  } else if (createIfNotFound)
  {
    result.it = entities.insert(entityGUID);
    result.isNew = true;
    result.entry = entries.Allocate();
    result.it->second = result.entry;
  } else
  {
    result.entry = 0;
    result.isNew = false;
  }
  return result;
}

PtrSharing::EntityInfoIt PtrSharing::_GetEntityInfo( EntityEntry* entry, const GUID& source, bool createIfNotFound)
{
  EntityInfoIt result;
  result.it = entry->gateEntities.find(source);
  if (result.it != entry->gateEntities.end())
  {
    result.info = &result.it->second;
    result.isNew = false;
  } else if (createIfNotFound)
  {
    result.it = entry->gateEntities.insert(source);
    result.info = &result.it->second;
    result.isNew = true;
  } else
  {
    result.info = 0;
    result.isNew = false;
  }
  return result;
}

EntityId PtrSharing::GetEntityId(const GUID& entityGUID, const GUID& destination)
{
  NI_ASSERT(!IsGUIDEmpty(destination), "Gate GUID can't be empty");
  NI_ASSERT(!IsGUIDEmpty(entityGUID), "Entity GUID can't be empty");
  threading::MutexLock lock(itemsLocker);
  EntityEntryIt entry = _GetEntityEntry(entityGUID, false);
  if (entry.entry)
  {
    EntityInfoIt info = _GetEntityInfo(entry.entry, destination, false);
    if (info.info)
    {
      return info.info->id;
    }
  }
  return INVALID_ENTITY;
}

bool PtrSharing::GetEntityGUID(rpc::ILocalEntity* entity, GUID& entityGUID)
{
  threading::MutexLock lock(itemsLocker);
  for (EntityEntryMap::iterator it=entities.begin();it!=entities.end();++it)
  {
    if (it->second->entity.Get() == entity)
    {
      entityGUID = it->first;
      return true;
    }
  }
  return false;
}


bool PtrSharing::RegisterObject(rpc::ILocalEntity* entity, const GUID& source, rpc::EntityId id, const GUID& entityGUID, bool isLocal)
{
  NI_VERIFY(!IsGUIDEmpty(source), "GUID can't be empty", return false);
  NI_VERIFY(!IsGUIDEmpty(entityGUID), "Entity GUID can't be empty", return false);
  LogTrace2(self, rpc::Local, "register entity (eid=%d euid=%s node=%s type=%s)", id, GUIDString(entityGUID).GetValue(), GUIDString(source).GetValue(), isLocal?"local":"remote");
  threading::MutexLock lock(itemsLocker);
  EntityEntryIt entry = _GetEntityEntry(entityGUID, true);
  if (entry.entry)
  {
    if (entry.isNew)
    {
      entry.entry->Set(entity, isLocal?0:1);
    }
    EntityInfoIt info = _GetEntityInfo(entry.entry, source, true);
    if (info.info)
    {
      if (info.isNew)
      {
        info.info->refCount = 1;
        info.info->id = id;
      } 
    }
  } else
  {
    NI_ALWAYS_ASSERT("Can't find entity for register !!!");
  }
  return true;
}


bool PtrSharing::GetAllGUIDs( rpc::ILocalEntity* entity, nstl::vector<EntityGateInfo>& guids, GUID& entityGUID )
{
  guids.resize(0);
  threading::MutexLock lock(itemsLocker);
  for (EntityEntryMap::iterator it=entities.begin();it!=entities.end();++it)
  {
    if (it->second->entity.Get() == entity)
    {
      guids.reserve(guids.size()+it->second->gateEntities.size());
      entityGUID = it->first;
      for (GateEntityMap::iterator git=it->second->gateEntities.begin();git!=it->second->gateEntities.end();++git)
      {
        EntityGateInfo& info = guids.push_back();
        info.gateId = git->first;
        info.entityId = git->second.id;
      }
    }
  }
  return guids.size() > 0;
}

void PtrSharing::RemoveGate(const GUID& source)
{
  LogTrace2(self, rpc::Local, "remove gate (node=%s)", GUIDString(source).GetValue());
  threading::MutexLock lock(itemsLocker);
  if (!IsGUIDEmpty(source))
  {
    for (EntityEntryMap::iterator it=entities.begin();it!=entities.end();)
    {
      EntityInfoIt info = _GetEntityInfo(it->second, source, false);
      if (info.info)
      {
        it = _RemoveEntityReference(it, info.it);
      } else
      {
        ++it;
      }
    }
    /*
    // debug print
    for (EntityEntryMap::iterator it=entities.begin();it!=entities.end();++it)
    {
      LogTrace("%p %s", it->second->entity.Get(),it->second->entity->ClassName());
      for (GateEntityMap::iterator git=it->second->gateEntities.begin();git!=it->second->gateEntities.end();++git)
      {
        LogTrace("  %s %d %d", GUIDString(git->first).value, git->second.id, git->second.refCount);
      }
    }
    */
  }
}

PtrSharing::EntityEntryMap::iterator PtrSharing::_RemoveEntityReference( EntityEntryMap::iterator it, GateEntityMap::iterator git )
{
  git->second.refCount--;
  if (git->second.refCount <= 0)
  {
    it->second->gateEntities.erase(git);
  }
  it->second->totalRefCount--;
  if (it->second->totalRefCount <= 0)
  {
    LogTrace2(self, rpc::Local, "deleting entity: %s", GUIDString(it->first).GetValue());
    it->second->entity = 0;
    entries.Deallocate(it->second);
    return entities.erase(it);
  } else
  {
    LogTrace2(self, rpc::Local, "entity alive: %s %d", GUIDString(it->first).GetValue(), it->second->totalRefCount);
  }
  it++;
  return it;
}

void PtrSharing::UnregisterObject(const GUID& source, rpc::EntityId id, const GUID& entityGUID)
{
  NI_ASSERT(!IsGUIDEmpty(source), "Gate GUID can't be empty");
  NI_ASSERT(!IsGUIDEmpty(entityGUID), "Entity GUID can't be empty");
  LogTrace2(self, rpc::Local, "unregister entity (eid=%d euid=%s node=%s)", id, GUIDString(entityGUID).GetValue(), GUIDString(source).GetValue());
  threading::MutexLock lock(itemsLocker);
  EntityEntryIt entry = _GetEntityEntry(entityGUID, false);
  if (entry.entry)
  {
    EntityInfoIt info = _GetEntityInfo(entry.entry, source, false);
    if (info.info)
    {
      if (info.info->id == id)
      {
        _RemoveEntityReference(entry.it, info.it);
      } else
      {
        ErrorTrace("Entity id not correlated (tid=%d expected=%d actual=%d)", threading::CurrentThreadID(), info.info->id, id);
      }
    } else
    {
      NI_ALWAYS_ASSERT(NStr::StrFmt("Can't find entity for unregister (euid=%s node=%s)", GUIDString(entityGUID).GetValue(), GUIDString(source).GetValue()));
    }
  } else
  {
    NI_ALWAYS_ASSERT(NStr::StrFmt("Can't find entity for unregister (euid=%s)", GUIDString(entityGUID).GetValue()));
  }
}

bool PtrSharing::ShareObject(const GUID& destination, const GUID& entityGUID, bool delayedPacket)
{
  NI_ASSERT(!IsGUIDEmpty(destination), "GUID can't be empty");
  LogTrace2(self, rpc::Local, "share entity (euid=%s node=%s)", GUIDString(entityGUID).GetValue(), GUIDString(destination).GetValue());
  threading::MutexLock lock(itemsLocker);
  EntityEntryIt entry = _GetEntityEntry(entityGUID, false);
  if (entry.entry)
  {
    EntityInfoIt info = _GetEntityInfo(entry.entry, destination, true);
    if (info.info)
    {
      if (info.isNew)
      {
        info.info->refCount = 1;
        info.info->id = INVALID_ENTITY;
      } else
      {
        info.info->refCount ++;
      }
      entry.entry->totalRefCount++;
      return true;
    } else
    {
      if (!delayedPacket)
      {
        NI_ALWAYS_ASSERT("Can't add entity info!!!");
      }
    }
  } else
  {
    if (!delayedPacket)
    {
      NI_ALWAYS_ASSERT(NStr::StrFmt("Can't find entity for share (euid=%s)", GUIDString(entityGUID).GetValue()));
    }
  }
  return false;
}

ILocalEntity* PtrSharing::LinkToObject(const GUID& destination, rpc::EntityId destId, const GUID& entityGUID)
{
  LogTrace2(self, rpc::Local, "set link to entity (eid=%d euid=%s node=%s)", destId, GUIDString(entityGUID).GetValue(), GUIDString(destination).GetValue());
  threading::MutexLock lock(itemsLocker);
  EntityEntryIt entry = _GetEntityEntry(entityGUID, false);
  if (entry.entry)
  {
    EntityInfoIt info = _GetEntityInfo(entry.entry, destination, true);
    if (info.info)
    {
      if (!info.isNew)
      {
        if (info.info->id == INVALID_ENTITY)
        {
          info.info->id = destId;
        } else
        {
          info.info->refCount ++;
          entry.entry->totalRefCount++;
        }
      } else // entity share info not found, but we return 
      {
        info.info->id = destId;
        info.info->refCount = 1;
        entry.entry->totalRefCount++;
      }
    }
    return entry.entry->entity;
  }
  return 0;
}

} // rpc
