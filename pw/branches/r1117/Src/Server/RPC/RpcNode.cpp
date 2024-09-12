#include "stdafx.h"
#include "RpcNode.h"
#include "System/Crc32Checksum.h"
/*
#include <Network/Transport.h>
#include "RPC.h"
#include "System/InlineProfiler.h"
#include "System/ported/types.h"
#include "System/ported/cwfn.h"
*/

NI_DEFINE_REFCOUNT(rpc::Node);

namespace rpc
{

Node::Node( threading::Mutex & section, EntityMap * _entityMap, rpc::IPacketPipe * _pipe, const GUID * id, EntityFactoriesContainer & factoriesContainer ) :
dataProcessing(&section),
entityMap(_entityMap),
pipe(_pipe)
{
  if (id)
  {
    opponent.SetId(*id);
  }
  const char* name = pipe->GetName();
  if (name)
  {
    opponent.name = name;
  }
  subNode = new PipeEntities(pipe, entityMap, factoriesContainer, opponent);
  logTrace = entityMap->GetLogTrace();
}



Node::~Node()
{
  Disconnect();
}


bool Node::Poll()
{
  return subNode->Poll( this );
}

void Node::Disconnect()
{
  NI_PROFILE_FUNCTION;

  if (subNode)
  {
    delete subNode;
    subNode = 0;
  }
  entityMap = 0;
}



IRemoteEntity* Node::_QueryWithFunctor(uint classId, uint classCrc, const char* path, IFunctor* functor, float timeout, const char* password, IRemoteEntityFactory* factory)
{
  if (entityMap)
  {
    MethodCallHeader header;
    IRemoteEntity* instance = _Query(classId, classCrc, factory, path, password, header);
    entityMap->RegisterAsyncCall(header, functor, timeout);  
    return instance;
  }
  return 0;
}



void Node::_QueryByGUID( uint classId, uint classCrc, const char* path, const char* password, rpc::MethodCall &call, const GUID& entityGUID)
{
  Crc32Checksum hashCode;
  if (password)
  {
    hashCode.AddString(password);
  }
  ArgWriter& args = call.Prepare(0);
  args.Push(classId);
  args.Push(classCrc);
  args.Push(path);
  args.Push(hashCode.Get());
  args.Push(entityGUID);
  call.info.header.id = rpc::QueryRequest;
  call.Go(GetPipe());
}



IRemoteEntity* Node::_Query( uint classId, uint classCrc, IRemoteEntityFactory* factory, const char* path, const char* password, MethodCallHeader& header )
{
  RemoteEntityInfo_ einfo = entityMap->CreateEntity(classId, classCrc, this, false, true, factory);
  einfo.handler->RegisterNode(this, GetName(), GetDesc().guid);
  rpc::MethodCall call(einfo.instance->GetInfo().entityId, classCrc);
  EntityCreationInfo info = { classId, classCrc, false, true };
  _QueryByGUID(info.classId, info.classCrc, path, password, call, einfo.handler->GetGUID());
  LogTrace2(GetDesc(), rpc::Out, "send query %s (eid=%d euid=%s node=%s path=%s)", einfo.instance->ClassName(), call.info.header.entityId, GUIDString(einfo.handler->GetGUID()).GetValue(), GetPipe()->GetName(), path );
  header = call.info.header;
  return einfo.instance;
}

int HandlerRegistrator::AppendEntity(rpc::EntityHandler* handler)
{
  threading::MutexLock locker(objectsRegistration);
  if (!isEnabled)
  {
    return -1;
  }

  if (freeIndices.size() > 0)
  {
    nstl::vector<int>::iterator iit = freeIndices.end()-1;
    int result = *iit;
    freeIndices.pop_back();
    RemoteEntityHandlerContainer::iterator it = handlers.begin()+result;
    *it = handler;
    return result;
  }
  int oldSize = handlers.size();
  handlers.resize(oldSize+oldSize/2+1);
  freeIndices.reserve(handlers.size());
  RemoteEntityHandlerContainer::iterator it = handlers.begin()+oldSize;
  *it++ = handler;
  for (int i=oldSize+1;i<handlers.size();++i)
  {
    freeIndices.push_back(i);
    *it++ = 0;
  } 
  return oldSize;
}

void HandlerRegistrator::_FreeEntity(rpc::EntityHandler* handler, int index )
{
  if (index >= 0)
  {
    RemoteEntityHandlerContainer::iterator it = handlers.begin()+index;
    if (*it == handler)
    {
      *it = 0;
      freeIndices.push_back(index);
    }
    else
    {
      NI_ALWAYS_ASSERT("Can't find entity by given index");
    }
  }
}


void HandlerRegistrator::RemoveEntity(rpc::EntityHandler* handler, int index)
{
  threading::MutexLock locker(objectsRegistration);
  _FreeEntity(handler, index);
}

void HandlerRegistrator::DereplicateAll(INode* node)
{
  _DisableRegistration();
  for (RemoteEntityHandlerContainer::iterator it = handlers.begin();it != handlers.end();++it)
  {
    threading::MutexLock locker(objectsRegistration);
    rpc::EntityHandler* handler = *it;
    if (handler)
    {
      int index = handler->Dereplicate(*node);
      _FreeEntity(handler, index);
    }
  }
}

} // rpc
