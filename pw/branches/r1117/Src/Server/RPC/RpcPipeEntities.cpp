#include "stdafx.h"
#include <Network/Transport.h>
//#include "RPC.h"
#include "RpcUtils.h"
#include "RpcPipeEntities.h"
/*
#include "System/InlineProfiler.h"
#include "System/ported/types.h"
#include "System/ported/cwfn.h"
*/

namespace rpc
{

static NDebug::DebugVar<int> rpcMethodCallsRecv( "NET|RPC calls recv", "" );
static NDebug::DebugVar<int> rpcBytesRecv( "RPC bytes recv", "Net" );


void DelayedPackets::Add(const void* data, int size, const Transport::MessageMiscInfo & miscInfo)
{
  byte* pdata = new byte[size];
  crt::memcpy(pdata, size, data, size);
  MemoryBlock& block = linkPackets.push_back();
  block.memory = pdata;
  block.size = size;
  times.push_back() = miscInfo;
}



DelayedPackets::~DelayedPackets()
{
  for (int i=0;i<linkPackets.size();++i)
  {
    delete [] ( static_cast< byte * >( linkPackets[i].memory ) );
  }
}



void DelayedPackets::Clear()
{
  if (indices.size() > 0)
  {
    for (int i=indices.size()-1;i>=0;--i)
    {
      delete [] ( static_cast< byte * >( linkPackets[indices[i]].memory ) );
      linkPackets.eraseByIndex(indices[i]);
      times.eraseByIndex(indices[i]);
    }
  }
  indices.clear();
}





bool PipeEntities::ProcessPacket( const byte* data , uint size, bool delayedPacket, rpc::Node* originNode, const Transport::MessageMiscInfo & _miscInfo)
{
  NI_PROFILE_FUNCTION;

  deserializeReader.Reset(data, size, 0);
  MethodCall::FailReason reason;
  const byte* paramsData = MethodCall::DeserializeCall(deserializeReader, call, reason);
  LogTrace3(opponent, rpc::In, "recieve (size=%d tid=%d delayed=%d)", size, call.transactionId, int(delayedPacket));
  call.miscInfo = _miscInfo;
  if (paramsData)
  {
    rpcMethodCallsRecv.AddValue( 1 );
    rpcBytesRecv.AddValue( size );
    if (!call.isReturnValue)
    {
      switch (call.id)
      {
        case rpc::QueryRequest: 
          if (!QueryEntity(call, paramsData, call.dataSize))
          {
            return false;
          }
          break;
        case rpc::Constructor:case rpc::ReplicatedConstructor: 
          if (!ConstructEntity(call, paramsData, call.dataSize+(call.isDataMembersIncluded?call.membersSize:0), call.id == rpc::ReplicatedConstructor, originNode))
          {
            return false;
          }
          break;
        case rpc::Destructor:
          if (!DestructEntity(call.entityId))
          {
            return false;
          }
          break;  
        case rpc::LinkConstructor:
          if (!LinkEntity(call.entityId, call, paramsData, call.dataSize))
          {
            if (!delayedPacket)
            {
              delayedPackets.Add(data, size, _miscInfo);
              return true;
            }
            return false;
          }
          break;  
        case rpc::NoMethod:
          if (!UpdateLocalEntity(call, paramsData, call.dataSize))
          {
            return false;
          }
          break;
        case rpc::UpdateRequest:
          if (!UpdateEntity(call.entityId))
          {
            return false;
          }
          break;
        case rpc::Publish:
          if (!Publish(call.entityId))
          {
            return false;
          }
          break;
        case rpc::UpdateData:
          if (!UpdateRemoteEntity(call, paramsData, call.dataSize))
          {
            return false;
          }
          break;
        case rpc::SetGateInfo:
          if (!SetGateInfo(call, paramsData, call.dataSize))
          {
            return false;
          }
          return true;
        case rpc::SharePtr:
          if (!SharePtr(call, paramsData, call.dataSize, delayedPacket))
          {
            if (!delayedPacket)
            {
              delayedPackets.Add(data, size, _miscInfo);
              return true;
            }
            return false;
          }
          return true;
        case rpc::ForceLink:
          if (!ForceLink(call, paramsData, call.dataSize))
          {
            return false;
          }
          return true;
        case rpc::Ping:
          if (!PingEntity(call.entityId, call, paramsData, call.dataSize))
          {
            return false;
          }
          return true;
        default:
          {
            NI_PROFILE_BLOCK( "call entity" );
            CallResult::Enum result = CallEntity(call.entityId, call, paramsData, call.dataSize);
            if (result != CallResult::OK)
            {
              if (result == CallResult::LocalEntityNotFound && !delayedPacket)
              {
                delayedPackets.Add(data, size, _miscInfo);
                return true;
              } else
              {
                const char* pipeName = pipe->GetName();
                LOG_E(0).Trace("Call corrupted (name=\"%s\" pipeId=%d reason=%s)", pipeName?pipeName:"<unknown>", pipe->GetInfo().pipeId, GetCallFailReason(result));
                PrintData(data, size);
              }
              return false;
            }
          }
          break;
      }
      return true;
    }
    else
    {
      NI_PROFILE_BLOCK( "Return value" );

      rpc::ILocalEntity* entity = entities.GetEntity(call.entityId);
      if (entity)
      {
        LogTrace2(opponent, rpc::In, "process return %s::%d (eid=%d)", entity->ClassName(), call.id, call.entityId);
      }
      bool returnResult = entityMap->ProcessReturnValue(call, paramsData, call.dataSize, args);
      if (!returnResult)
      {
        const char* pipeName = pipe->GetName();
        LOG_E(0).Trace("Return call failed (name=%s pid=%d)", pipeName?pipeName:"<unknown>", pipe->GetInfo().pipeId);
        PrintData(data, size);
      }
      args.Reset(0, 0, 0);
      return returnResult;
    }
  }
  LOG_E(0).Trace("Call deserialization failed (pipeId=%d reason=%s)", pipe->GetInfo().pipeId, rpc::MethodCall::GetReason(reason));
  PrintData(data, size);
  return false;
}

PipeEntities::~PipeEntities()
{
  args.Reset(0, 0, 0);
}

bool PipeEntities::Poll(rpc::Node* originNode)
{ 
  NI_PROFILE_FUNCTION;

  bool result = true;
  int index = 0;
  do
  {
    NI_PROFILE_BLOCK( "Main cycle" );

    if (delayedPackets.size() > 0)
    {
      NI_PROFILE_BLOCK( "Delayed packets" );
      for (int i=0;i<delayedPackets.linkPackets.size();++i)
      {
        if (ProcessPacket((byte*)delayedPackets.linkPackets[i].memory, delayedPackets.linkPackets[i].size, true, originNode, delayedPackets.times[i]))
        {
          delayedPackets.indices.push_back(i);
        }
      }
      delayedPackets.Clear();
    } 
    byte* data;
    int size;
    Transport::MessageMiscInfo miscInfo;
    if ( pipe->Recieve( index, &data, &size, miscInfo ) )
    {
      index++;
      result = ProcessPacket(data, size, false, originNode, miscInfo);
    } else
    {
      break;
    }
  } while (result);
  if (index > 0)
  {
    pipe->Reset();
  }
  return result;
}

bool LocalEntities::AppendEntity(uint classId, EntityId id, ILocalEntity* e, const GUID& entityGUID)
{
  NI_ASSERT(!IsGUIDEmpty(entityGUID), "Entity GUID can't be empty");
  if (_entities.insertUnique(id, new LocalEntityInfo(e, entityGUID, classId)))
  {
    return true;
  } else
  {
    NI_ALWAYS_ASSERT(NI_STRFMT( "Local entity with such id already created (tid=%d eid=%d)", threading::CurrentThreadID(), id));
  }
  return false;
}

bool LocalEntities::AppendEntity(EntityId id, const LocalEntityInfo& _info, const GUID& entityGUID)
{
  NI_ASSERT(!IsGUIDEmpty(entityGUID), "Entity GUID can't be empty");
  LocalEntityContainer::iterator it = _entities.insert(id);
  it->second = new LocalEntityInfo();
  it->second->Set(_info, entityGUID);
  return true;
} 

bool LocalEntities::RemoveHandler(const void* value)
{
  for (LocalEntityContainer::iterator it=_entities.begin();it != _entities.end();++it)
  {
    int index = it->second->Get()->GetMemberIndex(value);
    if (index >= 0)
    {
      LocalHandlerInfo* info = it->second->getHandlerInfo(index);
      if (info)
      {
        change_callbacks_factory.deallocate(*((DummyVoidCallFunctor*)info->functor));
        it->second->RemoveHandler(*info);
        return true;
      }
    }
  }
  NI_ALWAYS_ASSERT(NI_STRFMT( "Handler not found"));
  return false;
}

bool PipeEntities::ConstructEntity(const MethodCallHeader& call, const byte* paramsData, uint paramsSize, bool isReplicated, rpc::Node* originNode)
{
  NI_PROFILE_FUNCTION;

  bool result = true;
  args.Reset(paramsData, call.preAllocatedSize, paramsSize);
  const byte* membersData = 0;
  if (call.isDataMembersIncluded && call.membersSize > 0)
  {
    membersData = args.PopData(call.membersSize, result);
    NI_VERIFY(result, "Can't pop membersData", return false);
  }
  uint classId = args.Pop<int>(result);
  NI_VERIFY(result, "Can't pop classId", return false);

  uint classCrc = args.Pop<int>(result);
  NI_VERIFY(result, "Can't pop classCrc", return false);

  const GUID& entityGUID = args.PopStruct<GUID>(result);
  NI_VERIFY(result, "Can't pop entityGUID", return false);
  const int constructorParametersCount = 3;

  rpc::ILocalEntityFactory* factory = factoriesContainer.GetFactory<rpc::ILocalEntityFactory>(classId);
  if (factory)
  {
    LocalEntityCreationInfo info = {classId, call.GetParamsCount()-constructorParametersCount, isReplicated, originNode};
    rpc::ILocalEntity* e = factory->Create(info, args, entityMap);
    result = RegisterLocalEntity(classCrc, classId, call.entityId, e, entityGUID);
    if (result)
    {
      if (entityMap->RegisterRemoteObject(e, opponent.guid, call.entityId, entityGUID, false, classId))
      {
        LogTrace2( opponent, rpc::In, "process create %s (eid=%d euid=%s crc=%8.8X replicated=%d localEntity=%p)", e->ClassName(), call.entityId, GUIDString(entityGUID).GetValue(), classCrc, isReplicated, e );

        if (isReplicated)
        {
          if (membersData)  // members set
          {
            LocalEntityInfo* linfo = new LocalEntityInfo(e, entityGUID, classId);
            result = _UpdateLocalEntity(call, *linfo, membersData, call.membersSize);
            delete linfo;
          }
        } else
        {
          result = _UpdateEntity(call.entityId, e, entityGUID);
        }
      }
    } 
  } else
  {
    NI_ALWAYS_ASSERT(NI_STRFMT( "Local entity factory not found: classId 0x%0x, classCrc 0x%0x", classId, classCrc ));
    result = false;
  }
  return result;
}

bool PipeEntities::LinkEntity(EntityId id, const MethodCallHeader& call, const byte* paramsData, uint paramsSize)
{
  NI_PROFILE_FUNCTION;

  args.Reset(paramsData, call.GetPreAllocatedSize(), paramsSize);
  bool result = true;
  uint classId = args.Pop<int>(result);
  NI_VERIFY(result, "Can't pop classId", return false);

  uint classCrc = args.Pop<int>(result);
  NI_VERIFY(result, "Can't pop classCrc", return false);

  const GUID& entityGUID = args.PopStruct<GUID>(result);
  NI_VERIFY(result, "Can't pop entityGUID", return false);

  const char* sourceNode = args.Pop<const char*>(result);
  NI_VERIFY(result, "Can't pop sourceNode", return false);

  EntityId localId = args.Pop<int>(result);
  NI_VERIFY(result, "Can't pop localId", return false);

  const GUID& gateId = args.PopStruct<GUID>(result);
  NI_VERIFY(result, "Can't pop gateId", return false);

  ILocalEntity* entity = entityMap->LinkToLocalEntity(gateId, localId, opponent.guid, id, entityGUID);
  result = entity?RegisterLocalEntity(classCrc, classId, id, entity, entityGUID):false;
  if( result )
  {
    if ( sourceNode ) 
      LogTrace2( opponent, rpc::In, "process link %s:%d to %s:%d localEntity=%p", entity->ClassName(), id, sourceNode, localId, entity );
    else
      LogTrace2( opponent, rpc::In, "process link %s:%d to local object id=%d localEntity=%p", entity->ClassName(), id, localId, entity );
  } else
  {
    if ( sourceNode ) 
      LogTrace2( opponent, rpc::In, "fail link LObject:%d to %s:%d", id, sourceNode, localId);
    else
      LogTrace2( opponent, rpc::In, "fail link LObject:%d to <local>:%d", id, localId);
  }
  return result;
}


bool PipeEntities::RegisterLocalEntity(uint classCrc, uint classId,  EntityId id, ILocalEntity* e, const GUID& entityGUID)
{
  if (e)
  {
    if (e->GetClassCrc() == classCrc)
    {
      return entities.AppendEntity(classId, call.entityId, e, entityGUID); 
    } else
    {
      NI_ALWAYS_ASSERT(NI_STRFMT( "Class crc doesn't match: remote crc(0x%0X), local crc(0x%0X)", classCrc, e->GetClassCrc()));
      delete e;
      return false;
    }
  } 
  return false;
}

LocalEntityInstanceInfo LocalEntities::RemoveEntity(EntityId entityId, IPacketPipe * pipe, const NodeDescription& opponent, GUID& entityGUID)
{
  NI_PROFILE_FUNCTION;
  LocalEntityInstanceInfo result;
  LocalEntityContainer::iterator it = _entities.find(entityId);
  if (it != _entities.end())
  {
    LocalEntityInfo* info = it->second;
    entityGUID = info->GetGUID();
    LogTrace2(opponent, rpc::In, "process delete %s (eid=%d euid=%s)", info->Get()->ClassName(), entityId, GUIDString(entityGUID).GetValue() );
    result.instance = info->GetInstance();
    result.classId = info->GetClassId();
    info->Clear();
    delete info;
    _entities.erase(it);
  } 
  NI_ASSERT(result.instance, NI_STRFMT( "Can't find local entity (eid=%d node=%s)", entityId, pipe->GetName() ));
  return result;
}



bool PipeEntities::DestructEntity(EntityId entityId)
{
  NI_PROFILE_FUNCTION;

  GUID entityGUID;
  LocalEntityInstanceInfo linfo = entities.RemoveEntity(entityId, pipe, opponent, entityGUID);
  if (linfo.instance)
  {
    return entityMap->UnregisterRemoteObject(opponent.guid, entityId, entityGUID, linfo.instance, linfo.classId);
  }
  return false;
}



CallResult::Enum PipeEntities::CallEntity(EntityId entityId, const MethodCallHeader& call, const byte* paramsData, uint _paramsSize)
{
  NI_PROFILE_FUNCTION;

  rpc::CallResult::Enum result = rpc::CallResult::OK; 
  rpc::ILocalEntity* entity = entities.GetEntity(entityId);
  if (entity)
  {
    resultCall.Reset(entityId, entity->GetClassCrc());
    resultCall.args.Reset(0);
    LogTrace3(opponent, rpc::In, "call method %s::%d (eid=%d localEntity=%p)", entity->ClassName(), call.id, entityId, entity);
    
    result = entity->Call(call, resultCall, args,  paramsData, _paramsSize);
    NI_ASSERT(result == rpc::CallResult::OK, NI_STRFMT( "Call failed (eid=%d)", entityId));
    if (result == rpc::CallResult::OK)
    {
      if (resultCall.GetParamsCount() > 0)
      {
        resultCall.ReturnValue(call.id, call.transactionId);
        resultCall.Go(pipe, false);
      }
    }
    args.Reset(0, 0, 0);
  } 
  return result; 
}



bool PipeEntities::PingEntity(EntityId entityId, const MethodCallHeader& call, const byte* paramsData, uint paramsSize)
{                            
  NI_PROFILE_FUNCTION;

  rpc::ILocalEntity* entity = entities.GetEntity(entityId);
  if (entity)
  {
    resultCall.Reset(entityId, entity->GetClassCrc());
    LogTrace2(opponent, rpc::In, "ping method %s::%d (eid=%d localEntity=%p)", entity->ClassName(), call.id, entityId, entity);
    resultCall.args.Copy(paramsData, paramsSize);
    resultCall.args.IncrementParamsCount();
    resultCall.args.Preallocate(sizeof(nstl::vector<int>));
    resultCall.ReturnValue(call.id, call.transactionId);
    resultCall.Go(pipe);
    args.Reset(0, 0, 0);
  } 
  return true; 
}



bool PipeEntities::QueryEntity(const MethodCallHeader& call, const byte* paramsData, uint paramsSize)
{
  NI_PROFILE_FUNCTION;

  bool result = true;
  args.Reset(paramsData, call.GetPreAllocatedSize(), paramsSize);
  uint classId = args.Pop<int>(result);
  NI_VERIFY(result, "Can't pop classId", return false);

  uint classCrc = args.Pop<int>(result);
  NI_VERIFY(result, "Can't pop classCrc", return false);

  const char* path = args.Pop<const char*>(result);
  NI_VERIFY(result, "Can't pop path", return false);

  //unsigned long password = args.Pop<unsigned long>(result);
  unsigned int password = args.Pop<unsigned int>(result);
  NI_VERIFY(result, "Can't pop password", return false);

  const GUID& entityGUID = args.PopStruct<GUID>(result);
  NI_VERIFY(result, "Can't pop entityGUID", return false);

  LocalEntityInfo* linfo = entityMap->GetRegisteredLocalEntity(path); // TODO: addRef
  if (linfo)
  {
    if (linfo->IsMatched(classId, classCrc, password))
    {
      LogTrace2(opponent, rpc::In, "process query %s (eid=%d path=\"%s\")", linfo->Get()->ClassName(), call.entityId, path );
      if (entityMap->RegisterRemoteObject(linfo->Get(), opponent.guid, call.entityId, entityGUID, false, classId))
      {
        entities.AppendEntity(call.entityId, *linfo, entityGUID);
      } else
      {
        result = false;
      }
    } else
    {
      linfo = 0;
      result = false;
    }
  }
  else
    WarningTrace( "Unknown entity requested. path=%s, classCrc=%08x", path, classCrc );

  if (result)
  {
    rpc::MethodCall qcall(call.entityId, classCrc, entityMap);
    qcall.Prepare(0).Push(linfo?true:false);
    qcall.ReturnValue(call.id, call.transactionId);
    qcall.Go(pipe);
  }
  return result;
}



bool PipeEntities::UpdateLocalEntity(const MethodCallHeader& call, const byte* paramsData, uint dataSize) 
{
  NI_PROFILE_FUNCTION;

  rpc::LocalEntityInfo* info = entities.GetEntityInfo(call.entityId);
  if (info)
  {
    return _UpdateLocalEntity(call, *info, paramsData, dataSize);
  }
  return false;
}



bool PipeEntities::UpdateRemoteEntity(const MethodCallHeader& call, const byte* paramsData, uint paramsSize) 
{
  NI_PROFILE_FUNCTION;

  bool result = true;
  updateReader.Reset(paramsData, paramsSize, call.preAllocatedSize);
  GUID entityGUID;
  StrongMT<rpc::IRemoteEntity> entity;
  if (call.entityId != INVALID_ENTITY)
  {
    entityMap->GetEntity(call.entityId, entity);
  } else
  {
    entityGUID = updateReader.PopStruct<GUID>(result);
    entityMap->GetEntity(entityGUID, entity);
  }
  if (entity)
  {
    uint classCrc = updateReader.PopType<uint>(result);
    uint dataSize = updateReader.PopRaw<uint>(result);
    result = updateReader.UpdateRemoteEntity(entity, classCrc, dataSize);
  } else
  {
    NI_ALWAYS_ASSERT(NI_STRFMT( "Can't find remote entity (eid=%d)", call.entityId));
  }
  return result;
}



bool PipeEntities::SetGateInfo(const MethodCallHeader& call, const byte* paramsData, uint paramsSize) 
{
  NI_PROFILE_FUNCTION;

  bool result = true;
  args.Reset(paramsData, call.GetPreAllocatedSize(), paramsSize);
  const GateInfo& gateInfo = args.PopStruct<GateInfo>(result);
  if (result)
  {
    return _SetGateInfo(gateInfo);
  }
  return result;
}



bool PipeEntities::_SetGateInfo( const GateInfo &gateInfo )
{
  LogTrace2(opponent, rpc::In, "process identify (node=%s protocol=%d cnode=%s)", GUIDString(gateInfo.id).GetValue(), gateInfo.protocolVersion, GUIDString(opponent.guid).GetValue());
  if (rpc::GateInfo::PROTOCOL_VERSION != gateInfo.protocolVersion)
  {
    return false;
  }
  if (opponent.IsIdentified())
  {
    NI_VERIFY(opponent.guid == gateInfo.id, NI_STRFMT( "Node id mismath (actual=%s)", GUIDString(opponent.guid).GetValue()), return false);
  } 
  opponent.SetId(gateInfo.id);
  entityMap->RegisterGate(opponent.guid, pipe);
  return true;
}



bool PipeEntities::ForceLink(const MethodCallHeader& call, const byte* paramsData, uint paramsSize) 
{
  NI_PROFILE_FUNCTION;

  bool result = true;
  args.Reset(paramsData, call.GetPreAllocatedSize(), paramsSize);
  const GateInfo& gateInfo = args.PopStruct<GateInfo>(result);
  if (result && _SetGateInfo(gateInfo))
  {
    const GUID& sourceGateId  = args.PopStruct<GUID>(result);
    const GUID& entityGUID  = args.PopStruct<GUID>(result);
    const GUID& targetGateId  = args.PopStruct<GUID>(result);
    if (entityMap->GetID() == targetGateId)
    {
      StrongMT<rpc::IRemoteEntity> entity;
      entityMap->GetEntity(entityGUID, entity);
      if (entity && entity->GetHandler())
      {
        entity->GetHandler()->ConnectToNodes(entityMap);
      }
    } else if (entityMap->GetID() != sourceGateId)
    {
      entityMap->BroadcastForceLink(entityGUID, targetGateId, sourceGateId, &opponent.guid);
    }
  }
  return result;
}



bool PipeEntities::SharePtr(const MethodCallHeader& call, const byte* paramsData, uint paramsSize, bool delayedPacket) 
{
  NI_PROFILE_FUNCTION;

  bool result = true;
  args.Reset(paramsData, call.GetPreAllocatedSize(), paramsSize);
  const GUID& entityGUID  = args.PopStruct<GUID>(result);
  int count = args.Pop<short>(result);
  if (result)
  {
    for (int i=0;i<count && result;++i)
    {
      const GUID& gateId  = args.PopStruct<GUID>(result);
      if (result)
      {
        result = entityMap->ShareEntity(opponent.guid, call.entityId, gateId, entityGUID, delayedPacket);
        if (result)
        {
          LogTrace2(opponent, rpc::In, "process share LObject:%d %s", call.entityId, GUIDString(gateId).GetValue());
        } else
        {
          LogTrace2(opponent, rpc::In, "fail share LObject:%d %s", call.entityId, GUIDString(gateId).GetValue());
        }
      }
    }
  }
  return result;
}



bool PipeEntities::_UpdateEntity(uint entityId, ILocalEntity* entity, const GUID& entityGUID)
{
  Args args(entityMap, logTrace);
  args.SetEntityId(entityId);
  rpc::Transaction* transaction = args.StartDataTransaction(rpc::UpdateData);
  if (transaction)
  {
    if (entityMap->PrepareEntityData(transaction->GetArgs(), entity))
    {
      args.DoDataTransaction(pipe);
    } else
    {
      args.StopDataTransaction();
    }
    return true;
  }
  return false;
}



bool PipeEntities::UpdateEntity(EntityId entityId) 
{
  NI_PROFILE_FUNCTION;

  LogTrace2(opponent, rpc::In, "update entity (eid=%d)", entityId);
  rpc::ILocalEntity* entity = entities.GetEntity(entityId);
  if (entity)
  {
    GUID entityGUID;
    if (entityMap->GetEntityGUID(entity, entityGUID))
    {
      return _UpdateEntity(entityId, entity, entityGUID );
    }
  } else
  {
    NI_ALWAYS_ASSERT(NI_STRFMT( "Can't find local entity (eid=%d)", entityId));
  }
  return false;
}



bool PipeEntities::Publish( EntityId entityId) 
{
  NI_PROFILE_FUNCTION;

  LogTrace2(opponent, rpc::In, "publish entity (eid=%d)", entityId);
  rpc::ILocalEntity* entity = entities.GetEntity(entityId);
  if (entity)
  {
    return entityMap->PublishInternal( entityId, entity, 0, 0, &opponent.guid );
  }
  NI_ALWAYS_ASSERT(NI_STRFMT( "Can't find local entity (eid=%d)", entityId));
  return false;
}



bool PipeEntities::_UpdateLocalEntity(const MethodCallHeader& call, rpc::LocalEntityInfo& info, const byte* paramsData, uint dataSize)
{
  deserializeReader.Reset(paramsData, dataSize, call.preAllocatedSize);
  bool result = deserializeReader.UpdateLocalEntity(info, dataSize);
  if (result)
  {
    if (call.isPublishOnCommit)
    {
      return entityMap->PublishInternal(call.entityId, info.Get(), paramsData, dataSize, &opponent.guid, &deserializeReader.GetCreatedLocalEntities());
    }
  }
  return result;
}

} // rpc
