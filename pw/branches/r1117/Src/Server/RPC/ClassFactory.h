#pragma once

#include "Interfaces.h"
#include "Packets.h"
#include "Calls.h"
#include "Transaction.h"
#include <System/fixedvector.h>
#include <System/Thread.h>
#include <System/ThreadHelpers.h>
#include <System/IDGenerator.h>
#include "EntityMap.h"
#include "System/InlineProfiler.h"
#include "Packets.h"
#include "IMultiPipe.h"
#include "IFunctor.h"
#include "ILocalEntities.h"
#include "RpcEntityHandler.h"

namespace rpc
{

void RegisterFactory(uint classId, rpc::ILocalEntityFactory& factory);
void UnregisterFactory(uint classId);

class CreationEntry {
public:
  CreationEntry(uint classId, ILocalEntityFactory& factory)
  {
    rpc::RegisterFactory(classId, factory);
  }
};



template <typename T, class B>
class LocalObjectsFactory
{
public:

  ~LocalObjectsFactory()
  {
    for (int i=0;i<objects.size();++i)
    {
      delete ((B*)objects[i]);
    }
  }

  void deallocate(T& t) 
  {
    objects.push_back(&t);
  }

  template <typename N, typename P0, typename P1>
  N& allocate(P0 p0, P1 p1)
  {
    NI_ASSERT(sizeof(N) == sizeof(T), "Sizes should be equal");
    if (objects.size() > 0) 
    {
      T* result = objects.back();
      objects.pop_back();
      return *((N*)result);
    } 
    return *new N(p0, p1);
  }
private:
  nstl::vector<T*> objects;
};

template <typename T, typename P, typename C>
class FunctorContext : public IFunctor
{
  WeakMT<T> object;
  void (T::*func)(P result, C context, rpc::CallStatus status);
  C context;
public:
  FunctorContext():func(0) {}
  FunctorContext(T* _object, void (T::*_func)(P result, C context, rpc::CallStatus status), const C& _context):
  object(_object),
  func(_func),
  context(_context)
  {
  }

  virtual bool Call(VArgList v) 
  {
    StrongMT<T> lobject = object.Lock();
    if (lobject)
    {
      (lobject->*func)(_mng_va_arg(v,P), context, rpc::CallSuccessful);
      return true;
    }
    StrongMT<T> lobject2 = object.Lock();
    NI_ASSERT( lobject2 == 0, "inconsistent locking of weak ptr: probably StrongMT<> object created as raw *" );
    return false;
  }

  virtual void OnFailure(rpc::CallStatus status)
  {
    StrongMT<T> lobject = object.Lock();
    if (lobject)
    {
      P p = P();
      (lobject->*func)(p, context, status);
    }
  }
};

template <typename T, typename P>
class FunctorNoContext : public IFunctor
{
  WeakMT<T> object;
  void (T::*func)(P result);
public:
  FunctorNoContext():func(0) {}
  FunctorNoContext(T* _object, void (T::*func)(P result)):
  object(_object),
  func(func)
  {
  }

  virtual bool Call(VArgList v) 
  {
    StrongMT<T> lobject = object.Lock();
    if (lobject)
    {
      (lobject->*func)(_mng_va_arg(v,P));
      return true;
    }
    StrongMT<T> lobject2 = object.Lock();
    NI_ASSERT( lobject2 == 0, "inconsistent locking of weak ptr: probably StrongMT<> object created as raw *" );
    return false;
  }

  virtual void OnFailure(rpc::CallStatus status)
  {
    StrongMT<T> lobject = object.Lock();
    if (lobject)
    {
      P p = P();
      (lobject->*func)(p);
    }
  }
};

template <typename T, typename P, typename C>
class RefFunctorContext : public IFunctor
{
  WeakMT<T> object;
  void (T::*func)(P& result, C context, rpc::CallStatus status);
  C context;
public:
  RefFunctorContext():func(0) {}
  RefFunctorContext(T* _object, void (T::*func)(P& result, C context, rpc::CallStatus status), const C& _context):
  object(_object),
  func(func),
  context(_context)
  {
  }

  virtual bool Call(VArgList v) 
  {
    StrongMT<T> lobject = object.Lock();
    if (lobject)
    {
      (lobject->*func)(*_mng_va_arg(v, P*), context, rpc::CallSuccessful);
      return true;
    }
    StrongMT<T> lobject2 = object.Lock();
    NI_ASSERT( lobject2 == 0, "inconsistent locking of weak ptr: probably StrongMT<> object created as raw *" );
    return false;
  }

  virtual void OnFailure(rpc::CallStatus status)
  {
    StrongMT<T> lobject = object.Lock();
    if (lobject)
    {
      P p = P();
      (lobject->*func)(p, context, status);
    }
  }
};

template <typename T, typename P>
class RefFunctorNoContext : public IFunctor
{
  WeakMT<T> object;
  void (T::*func)(P& result);
public:
  RefFunctorNoContext():func(0) {}
  RefFunctorNoContext(T* _object, void (T::*func)(P& result)):
  object(_object),
  func(func)
  {
  }

  virtual bool Call(VArgList v) 
  {
    StrongMT<T> lobject = object.Lock();
    if (lobject)
    {
      (lobject->*func)(*_mng_va_arg(v, P*));
      return true;
    }
    StrongMT<T> lobject2 = object.Lock();
    NI_ASSERT( lobject2 == 0, "inconsistent locking of weak ptr: probably StrongMT<> object created as raw *" );
    return false;
  }

  virtual void OnFailure(rpc::CallStatus status)
  {
    StrongMT<T> lobject = object.Lock();
    if (lobject)
    {
      P p = P();
      (lobject->*func)(p);
    }
  }
};

template <typename T>
class VoidCallFunctor : public IFunctor
{
  T* object;
  void (T::*func)();
public:
  VoidCallFunctor():object(0), func(0) {}
  VoidCallFunctor(T* object, void (T::*func)()):
  object(object),
    func(func)
  {
  }

  virtual bool Call(VArgList) 
  {
    (object->*func)();
    return true;
  }

  virtual void OnFailure(rpc::CallStatus status)
  {
    (object->*func)();
  }
};


typedef VoidCallFunctor<LocalEntityInfo> DummyVoidCallFunctor;
typedef nstl::hash_map<EntityId, LocalEntityInfo*> LocalEntityContainer;

class LocalEntities : public ILocalEntities, NonCopyable
{
public:
  LocalEntities(EntityMap* _entityMap):
  entityMap(_entityMap)
  {
    logTrace = entityMap->GetLogTrace();
  }

  ~LocalEntities()
  {
    for (LocalEntityContainer::iterator it=_entities.begin();it != _entities.end();++it)
    {
      it->second->Clear();
      delete it->second;
    }
  }
  rpc::ILocalEntity* GetEntity(EntityId entityId)
  {
    rpc::LocalEntityInfo* info = GetEntityInfo(entityId);
    return info?info->Get():0;
  }

  rpc::LocalEntityInfo* GetEntityInfo(EntityId entityId)
  {
    NI_PROFILE_HEAVY_FUNCTION;

    LocalEntityContainer::iterator it = _entities.find(entityId);
    if (it != _entities.end())
    {
      return it->second;
    }
    return 0;
  }

  rpc::ILocalEntity* GetEntity(EntityId entityId, const RemoteEntityTypeInfo& info);

  void* get(EntityId entityId, uint id)
  {
    rpc::ILocalEntity* entity = GetEntity(entityId);
    if (entity)
    {
      return entity->_Get(id);    
    }
    return 0;
  }
  bool RemoveHandler(const void* value);
  bool AppendEntity(uint classId, EntityId id, ILocalEntity* e, const GUID& entityGUID);
  bool AppendEntity(EntityId id, const LocalEntityInfo& info, const GUID& entityGUID);
  LocalEntityInstanceInfo RemoveEntity(EntityId id, IPacketPipe * pipe, const NodeDescription& opponent, GUID& entityGUID );
  rpc::LocalEntityInfo* FindMember(const void* value, int& index);
  template <typename H>
  bool SetHandler(const void* value, H* object, void (H::*func)())
  {
    int index = 0;
    rpc::LocalEntityInfo* info = FindMember(value, index);
    if (info)
    {
      VoidCallFunctor<H>& callback = change_callbacks_factory.allocate<VoidCallFunctor<H> >(object, func);
      info->AddHandledMember(index, &callback);
      return true;
    }
    return false;
  }
private:
  TLogTrace logTrace;
  LocalEntityContainer _entities;
  LocalObjectsFactory<DummyVoidCallFunctor, rpc::IFunctor> change_callbacks_factory;
  EntityMap* entityMap;
};



class ClassFactory 
{
public:
  ClassFactory(
    threading::Mutex& _section, 
    IDGenerator& idGenerator, 
    EntityFactoriesContainer& factoriesContainer,
    IPipeProcessor* _processor,
    INodes& _nodes):
    handlers(_section, idGenerator, factoriesContainer, _nodes, _processor)
  {
  }
private:
  EntityMap handlers;
};

} // rpc