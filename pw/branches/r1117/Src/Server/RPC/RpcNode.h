#pragma once

#include "IFunctor.h"
#include "IRemoteEntity.h"
#include <System/nvector.h>
#include <System/Basic.h>

#include "CppWrapper.h"
#include "RpcEntityHandler.h"
#include "EntityMap.h"
#include "RpcPipeEntities.h"
#include "RpcUtils.h"


namespace rpc 
{

class EntityMap;
class EntityFactoriesContainer;

template <typename T, typename P, typename C>
class QueryFunctor : public IFunctor
{
  WeakMT<T> object;
  void (T::*func)(P result, C context, rpc::CallStatus status);
  C context;
  StrongMT<IRemoteEntity> entity;
  Stack stack;
public:
  QueryFunctor(T* _object, void (T::*_func)(P result, C context, rpc::CallStatus status), const C& _context):
  object(_object),
  func(_func),
  context(_context)
  {
  }

  void SetEntity(IRemoteEntity* _entity) { entity = _entity; } 

  virtual bool Call(VArgList args)
  {
    bool result = _mng_va_arg(args, bool);
    StrongMT<T> lobject = object.Lock();
    if (lobject)
    {
      if (result && entity)
      {
        entity->GetHandler()->MarkConstructed();
      }
      stack.Push<void*>(result?entity:0);
      stack.Stop();
      (lobject->*func)(stack.Pop<P>(), context, rpc::CallSuccessful);
      return true;
    }
    StrongMT<T> lobject2 = object.Lock();
    NI_ASSERT( lobject2 != 0, "inconsistent locking of weak ptr: probably StrongMT<> object created as raw *" );
    return result;
  }

  virtual void OnFailure(rpc::CallStatus status)
  {
    StrongMT<T> lobject = object.Lock();
    if (lobject)
    {
      stack.Push<P>();
      (lobject->*func)(stack.Pop<P>(), context, status);
    }
  }
};

template <typename T, typename P>
class QueryFunctorNoContext : public IFunctor
{
  WeakMT<T> object;
  void (T::*func)(P result);
  StrongMT<IRemoteEntity> entity;
  Stack stack;
public:
  QueryFunctorNoContext(T* _object, void (T::*_func)(P result)):
  object(_object),
  func(_func)
  {
  }
  void SetEntity(IRemoteEntity* _entity) { entity = _entity; } 

  virtual bool Call(VArgList args)
  {
    bool result = _mng_va_arg(args, bool);
    StrongMT<T> lobject = object.Lock();
    if (lobject)
    {
      if (result && entity)
      {
        entity->GetHandler()->MarkConstructed();
      }
      stack.Push<void*>(result?entity:0);
      stack.Stop();
      (lobject->*func)(stack.Pop<P>());
      return true;
    }
    StrongMT<T> lobject2 = object.Lock();
    NI_ASSERT( lobject2 != 0, "inconsistent locking of weak ptr: probably StrongMT<> object created as raw *" );
    return result;
  }

  virtual void OnFailure(rpc::CallStatus status)
  {
    // No notification here - use no status queries for your own sake
  }
};

struct HandlerRegistrator
{
  typedef nstl::vector<StrongMT<rpc::EntityHandler> > RemoteEntityHandlerContainer;
  
  HandlerRegistrator():isEnabled(true) {}

  int AppendEntity(rpc::EntityHandler* handler);
  void RemoveEntity(rpc::EntityHandler* handler, int index);
  void DereplicateAll(INode* node);
private:
  void _DisableRegistration() { threading::MutexLock locker(objectsRegistration); isEnabled = false; }
  void _FreeEntity(rpc::EntityHandler* handler, int index );
  RemoteEntityHandlerContainer handlers;
  nstl::vector<int> freeIndices;
  threading::Mutex objectsRegistration;
  bool isEnabled;
};

/// Управляет созданием удалённых объектов и представляет функционал RPC между двумя гейтами.
class Node : public INode, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(Node, INode, BaseObjectMT);
  friend class Gate;
  friend class MultiPacketPipe;
public:
  Node( threading::Mutex & section, EntityMap * _entityMap, rpc::IPacketPipe * pipe, const GUID * id, EntityFactoriesContainer & factoriesContainer );
  ~Node();

  /// Для внутреннего использования
  bool Poll();

  RemoteEntityInfo_ PreCreate( unsigned int classId, unsigned int classCrc, IRemoteEntityFactory* factory=0)
  {
    EntityCreationInfo info = {classId, classCrc, false, false};
    RemoteEntityInfo_ entity = entityMap->CreateEntity(info, factory);
    entity.handler->RegisterNode(this, GetName(), GetDesc().guid);
    return entity;
  }

  void InvokeConstructor( RemoteEntityInfo_ entity )
  {
    entity.InvokeConstructor<IRemoteEntity>();
  }

  /// Создание R-объекта.
  /// На сервер передаётся вызов на создание оригинального объекта.
  template <typename T>
  T* Create()
  {
    if (entityMap)
    {
      rpc::RegisterRemoteFactory<T>(0);
      RemoteEntityInfo_ entity = entityMap->CreateEntity<T>();
      entity.handler->RegisterNode(this, GetName(), GetDesc().guid);
      if (!entity.handler->IsFailed())
      {
        return entity.InvokeConstructor<T>();
      } else 
      {
        entity.Clear();
      }
    }
    return 0;
  }

  /// Создание R-объекта с одним параметром.
  template <typename T, typename P0>
  T* Create(const P0& p0)
  {
    if (entityMap)
    {
      rpc::RegisterRemoteFactory<T>(0);
      RemoteEntityInfo_ entity = entityMap->CreateEntity<T>();
      entity.handler->RegisterNode(this, GetName(), GetDesc().guid);
      entity.handler->Construct(p0);
      if (!entity.handler->IsFailed())
      {
        return entity.InvokeConstructor<T>();
      } else 
      {
        entity.Clear();
      }
    } 
    return 0;
  }

  /// Создание R-объекта с двумя параметрами.
  template <typename T, typename P0, typename P1>
  T* Create(const P0& p0, const P1& p1)
  {
    if (entityMap)
    {
      rpc::RegisterRemoteFactory<T>(0);
      RemoteEntityInfo_ entity = entityMap->CreateEntity<T>();
      entity.handler->RegisterNode(this, GetName(), GetDesc().guid);
      entity.handler->Construct(p0, p1);
      if (!entity.handler->IsFailed())
      {
        return entity.InvokeConstructor<T>();
      } else 
      {
        entity.Clear();
      }
    }
    return 0;
  }

  /// Создание R-объекта с тремя параметрами.
  template <typename T, typename P0, typename P1, typename P2>
  T* Create(const P0& p0, const P1& p1, const P2& p2)
  {
    if (entityMap)
    {
      rpc::RegisterRemoteFactory<T>(0);
      RemoteEntityInfo_ entity = entityMap->CreateEntity<T>();
      entity.handler->RegisterNode(this, GetName(), GetDesc().guid);
      entity.handler->Construct(p0, p1, p2);
      if (!entity.handler->IsFailed())
      {
        return entity.InvokeConstructor<T>();
      } else 
      {
        entity.Clear();
      }
    }
    return 0;
  }

  /// Создание R-объекта с четырьмя параметрами.
  template <typename T, typename P0, typename P1, typename P2, typename P3>
  T* Create(const P0& p0, const P1& p1, const P2& p2, const P3& p3)
  {
    if (entityMap)
    {
      rpc::RegisterRemoteFactory<T>(0);
      RemoteEntityInfo_ entity = entityMap->CreateEntity<T>();
      entity.handler->RegisterNode(this, GetName(), GetDesc().guid);
      entity.handler->Construct(p0, p1, p2, p3);
      if (!entity.handler->IsFailed())
      {
        return entity.InvokeConstructor<T>();
      } else 
      {
        entity.Clear();
      }
    }
    return 0;
  }

  IRemoteEntity* CreateWithFactory( uint classId, uint classCrc, IRemoteEntityFactory* factory )
  {
    if (entityMap)
    {
      EntityCreationInfo info = {classId, classCrc, false, false};
      RemoteEntityInfo_ entity = entityMap->CreateEntity(info, factory);
      entity.handler->RegisterNode(this, GetName(), GetDesc().guid);
      if (!entity.handler->IsFailed())
      {
        return entity.InvokeSharedConstructor();
      } else 
      {
        entity.Clear();
      }
    }
    return 0;
  }

  template <typename P0>
  IRemoteEntity* CreateWithFactory( uint classId, uint classCrc, IRemoteEntityFactory* factory, const P0& p0 )
  {
    if (entityMap)
    {
      EntityCreationInfo info = {classId, classCrc, false, false};
      RemoteEntityInfo_ entity = entityMap->CreateEntity(info, factory);
      entity.handler->RegisterNode(this, GetName(), GetDesc().guid);
      entity.handler->Construct(p0);
      if (!entity.handler->IsFailed())
      {
        return entity.InvokeSharedConstructor();
      } else 
      {
        entity.Clear();
      }
    }
    return 0;
  }

  template <typename P0, typename P1>
  IRemoteEntity* CreateWithFactory( uint classId, uint classCrc, IRemoteEntityFactory* factory, const P0& p0, const P1& p1 )
  {
    if (entityMap)
    {
      EntityCreationInfo info = {classId, classCrc, false, false};
      RemoteEntityInfo_ entity = entityMap->CreateEntity(info, factory);
      entity.handler->RegisterNode(this, GetName(), GetDesc().guid);
      entity.handler->Construct(p0,p1);
      if (!entity.handler->IsFailed())
      {
        return entity.InvokeSharedConstructor();
      } else 
      {
        entity.Clear();
      }
    }
    return 0;
  }

  /// Запрашивает объект, зарегистрированный через гейт.
  /// R-объект возвращается через указанную callback-функцию
  template <typename T, typename H, typename P>
  bool Query(const char* path, H* object, void (H::*func)(P result), const char* password=0)
  {
    rpc::RegisterRemoteFactory<T>(0);
    return Query<H, P>(T::ID(), T::CRC32, path, object, func, password);
  }


  template <typename T, typename H, typename P, typename C>
  bool Query(const char* path, H* object, void (H::*func)(P result, C context, rpc::CallStatus status), C context, float timeout=0.f, const char* password=0)
  {
    rpc::RegisterRemoteFactory<T>(0);
    if (entityMap)
    {
      QueryFunctor<H, P, C>* qfunctor =  new rpc::QueryFunctor<H, P, C>(object, func, context);
      IRemoteEntity* instance = _QueryWithFunctor(T::ID(), T::CRC32, path, qfunctor, timeout, password);
      if (instance)
      {
        qfunctor->SetEntity(instance);
        return true;
      }
    }
    return false;
  }

  template <typename H, typename P>
  bool Query(uint classId, uint classCrc, const char* path, H* object, void (H::*func)(P result), const char* password=0, IRemoteEntityFactory* factory=0)
  {
    if (entityMap)
    {
      QueryFunctorNoContext<H, P>* qfunctor =  new rpc::QueryFunctorNoContext<H, P>(object, func);
      IRemoteEntity* instance = _QueryWithFunctor(classId, classCrc, path, qfunctor, 0.f, password, factory);
      if (instance)
      {
        qfunctor->SetEntity(instance);
        return true;
      }
    }
    return false;
  } 

  // only for testing 
  template <typename T>
  T* get(uint entityId)
  {
    threading::MutexLock lock(*dataProcessing);
    return (T*)subNode->get(entityId, rpc::GetId<T>());
  }
 
  template <typename T, typename H>
  bool SetHandler(T& value, H* object, void (H::*func)())
  {
    threading::MutexLock lock(*dataProcessing);
    return subNode->SetHandler(&value, object, func);
  }

  template <typename T>
  bool RemoveHandler(T& value)
  {
    threading::MutexLock lock(*dataProcessing);
    return subNode->RemoveHandler(&value);
  }

  // not thread-safe, should be called only internally
  inline IPacketPipe* GetPipe()
  {
    return pipe;
  }

  virtual IPacketPipe * GetConnectedPipe() { return GetPipe(); }
  virtual bool IsReady() const { return IsConnected() && opponent.IsIdentified(); }
  virtual const char* GetName() { return opponent.name.c_str(); }
  virtual const NodeDescription& GetDesc() const { return opponent; }
  virtual bool IsConnected() const { return entityMap != 0; }
  virtual void DereplicateAll() { registrator.DereplicateAll(this); }

  void Disconnect();
protected:
  void _QueryByGUID( uint classId, uint classCrc, const char* path, const char* password, rpc::MethodCall &call, const GUID& entityGUID);
  virtual int AppendEntity(rpc::EntityHandler* handler) { return registrator.AppendEntity(handler); }
  virtual void RemoveEntity(rpc::EntityHandler* handler, int index) { registrator.RemoveEntity(handler, index); }
private:
  IRemoteEntity* _QueryWithFunctor(uint classId, uint classCrc, const char* path, IFunctor* functor, float timeout=0.f, const char* password=0, IRemoteEntityFactory* factory=0);
  IRemoteEntity* _Query( uint classId, uint classCrc, IRemoteEntityFactory* factory, const char* path, const char* password, MethodCallHeader& header );

  TLogTrace logTrace;
  StrongMT<EntityMap> entityMap;
  PipeEntities* subNode;
  HandlerRegistrator registrator;
  threading::Mutex* dataProcessing;
  NodeDescription opponent;
  StrongMT<rpc::IPacketPipe> pipe;
};

} // rpc
