#pragma once

#include <stdarg.h>
#include <System/nvector.h>
#include <System/nstring.h>
#include <System/Basic.h>
#include "RpcDataProcessor.h"
#include "RpcThreadPool.h"
#include "RpcNode.h"


namespace rpc
{

_interface IPipeProcessor;
_interface IPacketPipe;
_interface ILocalEntityFactory;
class Node;

/// <summary>
/// Управляет передачей вызовов RPC и представляет сторону удалённого взаимодействия. 
/// Значительная часть интерфейса гейта касается управления механизмом репликации. 
/// Методы Replicate, IsReplicated, Dereplicate позволяют создавать реплики. 
/// Методы Block, Unblock, SetExclusive, ClearExclusive управляют хождением вызовов от R-объекта 
/// до его серверных реплик (О-объектов).
/// Также гейт предоставляет интерфейс для регистрации объектов на стороне сервера, 
/// а также в нём регистрируются фабрики классов, объекты которых затем могут быть созданы 
/// через ноды данного гейта. 
/// Метод RegisterObject регистрирует объект, методы RegisterFactory и UnregisterFactory управляют регистрацией фабрик классов.
/// <summary>
class Gate : public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_1( Gate, BaseObjectMT );
public:
  Gate(IPipeProcessor* _processor=0, int _threadCount=0);

  ~Gate();

  const GUID& GetID() const { return _server.GetID(); }

  /// Создаёт ноду по переданному каналу.
  StrongMT<Node> AddPipe(IPacketPipe * pipe, const GUID* id=0);

  /// Удаляет ноду.
  void RemovePipe(Node* node)
  {
    _server.RemoveNode(node);
  }

  /// Обрабатывает удалённые вызовы к нодам данного гейта.
  void Poll();

  /// Создаёт реплику данного объекта в заданной ноде.
  /// 
  /// <param name="entity">R-объект для репликации</param>
  /// <param name="node">Ноду, на которую реплицировать</param>
  /// <returns>Возвращает успешность репликации</returns>
  template <typename T>
  bool Replicate(T& entity, Node& node)
  {
    EntityHandler* handler = entity.GetHandler();
    threading::MutexLock lock(dataProcessing);
    return handler->Replicate(entity, node);
  }

  /// Определяет, отреплицирован ли данный объект в заданной ноде.
  ///
  /// Method:    IsReplicated
  /// FullName:  rpc::Gate<T>::IsReplicated
  /// Access:    public 
  /// Returns:   bool
  /// Qualifier:
  /// Parameter: T & entity - R-объект, для которого надо определить, отреплицирован ли он
  /// Parameter: rpc::Node & node - нода, для которой надо определить
  //************************************
  template <typename T>
  bool IsReplicated(T& entity, Node& node)
  {
    threading::MutexLock lock(dataProcessing);
    return entity.GetHandler()->IsReplicated(node);
  }

  /// Запрещает хождение вызовов от заданного R-объекта до заданной ноды.
  template <typename T>
  void Block(T& entity, Node& node)
  {
    threading::MutexLock lock(dataProcessing);
    entity.GetHandler()->Block(node);
  }

  /// Разрешает хождение вызовов от заданного R-объекта до заданной ноды.
  template <typename T>
  void Unblock(T& entity, Node& node)
  {
    threading::MutexLock lock(dataProcessing);
    EntityHandler* handler = entity.GetHandler();
    if (!handler->Unblock(node))
    {
      handler->Replicate(entity, node);
    }
  }

  template <typename T>
  bool UnblockWithoutReplicate(T& entity, Node& node)
  {
    threading::MutexLock lock(dataProcessing);
    return entity.GetHandler()->Unblock(node);
  }

  /// Устанавливает режим эксклюзивного хождения вызовов от заданного R-объекта только до заданной ноды.
  template <typename T>
  void SetExclusive(T& entity, Node& node)
  {
    threading::MutexLock lock(dataProcessing);
    entity.GetHandler()->SetExclusive(node);
  }

  /// Отменяет эксклюзивный режим для пары объект-нода.
  template <typename T>
  void ClearExclusive(T& entity)
  {
    threading::MutexLock lock(dataProcessing);
    entity.GetHandler()->ClearExclusive();
  }

  /// Удаляет реплику данного объекта в заданной ноде.
  template <typename T>
  void Dereplicate(T& entity, Node& node)
  {
    EntityHandler* handler = entity.GetHandler();
    threading::MutexLock lock(dataProcessing);
    int index = handler->Dereplicate(node);
    node.RemoveEntity(handler, index);
  }

  /// Регистрирует объект на сервере для последующего обращения к нему из клиентов.
  void DereplicateAll(Node& node)
  {
    threading::MutexLock lock(dataProcessing);
    node.DereplicateAll();
  }

  /// Регистрирует объект на сервере для последующего обращения к нему из клиентов.
  template <typename T>
  void RegisterObject(StrongMT<T> value, const char* path, const char* password=0)
  {
    threading::MutexLock lock(dataProcessing);
    _server.RegisterObject(value, path, password);
  }

  template <typename T>
  bool UnregisterObject(StrongMT<T> value)
  {
    threading::MutexLock lock(dataProcessing);
    T* object = value.Get();
    return _server.UnregisterObject(GetId<T>(), object);
  }

  bool RegisterObject(uint classId, void* instance, const char* path, const char* password=0)
  {
    threading::MutexLock lock(dataProcessing);
    return _server.RegisterObject(classId, instance, path, password);
  }

  /// Регистрирует фабрику класса на сервере
  template<class T>
  void RegisterFactory( ILocalEntityFactory& factory)
  {
    threading::MutexLock lock(dataProcessing);
    _server.RegisterFactory( GetId<T>(0, BaseRemoteType), factory);
  }

  /// Удаляет регистацию фабрики классов
  template<class T>
  void UnregisterFactory()
  {
    threading::MutexLock lock(dataProcessing);
    _server.UnregisterFactory( GetId<T>(0, BaseRemoteType) );
  }
private:
  threading::Mutex dataProcessing;
  ServerDataProcessor _server;
  ThreadPool pool;
};

} // rpc
