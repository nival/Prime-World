#ifndef GATEKEEPER_H_7868FF9E_2769_4E24
#define GATEKEEPER_H_7868FF9E_2769_4E24

#include "TransportPipe.h"
#include "Base.h"
#include "Network/TransportUtils.h"
#include "System/ThreadPool.h"
#include "PollJob.h"
#include "TransportPipeTrackerFactory.h"
#include "ClassFactory.h"

namespace Transport
{
  _interface IClientTransportSystem;
}

namespace rpc
{
  class TransportPipe;

  /// Предоставляет вызовы по внутренним событиям GateKeeper
  _interface IGateKeeperCallback : public IBaseInterfaceMT
  {
    NI_DECLARE_CLASS_1( IGateKeeperCallback, IBaseInterfaceMT );

    /// Вызывается из Poll() при появлении нового канала. Передаёт в параметрах канал и ноду
    virtual void OnNewNode( Transport::IChannel * channel,  rpc::Node * node ) = 0;

    /// Вызывается из Poll() при закрытии канала. Передаёт в параметрах канал и ноду
    virtual void OnChannelClosed( Transport::IChannel * channel, rpc::Node * node ) = 0;

    /// Вызывается при наступлении одноимённого события в канале
    virtual void OnCorruptData( Transport::IChannel * channel, rpc::Node * node ) = 0;
  };




  /// Базовый класс для GateKeeper и GateKeeperClient
  class GateKeeperBase : public BaseObjectMT, public rpc::IPipeProcessor
  {
    NI_DECLARE_REFCOUNT_CLASS_2( GateKeeperBase, BaseObjectMT, rpc::IPipeProcessor )

  public:
    GateKeeperBase( const Transport::TServiceId& _serviceId, Transport::TClientId _clientId, IGateKeeperCallback* callback,
       unsigned int nthreads = 1);

    ~GateKeeperBase(){}

    /// Прокачивает поступившие вызовы у всех нод
    void Poll();

    /// Возвращает гейт 
    //TODO: return pointer, NOT ref
    rpc::Gate * GetGate() const
    { 
      return gate;
    }

    void setGateKeeperCallback( IGateKeeperCallback* _callback );
    void attachNotificationCallback( IGateKeeperCallback * _callback );
    void detachNotificationCallback( IGateKeeperCallback * _callback );

    /// Возвращает ноду по serviceId. Если не находит, создаёт новую ноду.
    StrongMT<rpc::Node> RequestNode( const Transport::TServiceId& destination );

    void setTransportPipeTrackerFactory( TransportPipeTrafficTrackerFactory * tpttf );

    /// Возвращает ноду по serviceId. Если не находит, возвращает 0.
    StrongMT<rpc::Node> GetNode( const Transport::TServiceId& destination ) const;

    /// Удаляет ноду по serviceId
    void RemoveNode( const Transport::TServiceId& destination );

  protected:
    Transport::TServiceId serviceId;

    GateKeeperBase() : gate(0) {}

    void Init();
    void Destroy();
    void AddReceivedPipe( Transport::IChannel * channel );
    StrongMT<TransportPipe> CreatePipe( Transport::IChannel * chan, const GUID * id =0 );
    void GenerateServiceId( Transport::IChannel* channel, Transport::TServiceId *serviceId );

    virtual StrongMT<Transport::IChannel> OpenChannel( const Transport::Address& address ) = 0;
    virtual void OnPrePoll() {}
    virtual void OnPostPoll() {};

  private:
    typedef hash_map<Transport::TServiceId, StrongMT<TransportPipe>, Transport::ServiceIdHash> TPipes;
    typedef list<StrongMT<TransportPipe> > TPipeList;
    typedef nstl::list<WeakMT<IGateKeeperCallback> > CallbacksT;

    CallbacksT callbacks;

    Transport::TClientId clientId;
    unsigned int pipeCount;

    StrongMT<rpc::Gate> gate;
    TPipes pipes;
    TPipeList closingPipes;

    threading::ThreadPool tp_;
    CloseChannelJobFactory ccjobFactory_;

    //rpc::IPipeProcessor
    virtual void OnCorruptData( rpc::IPacketPipe * _pipe );
    virtual StrongMT<rpc::IPacketPipe> ConnectToPipe( const char* name, const GUID& id);
    virtual const char* GetName() const  { return serviceId.c_str(); }

    void attachNotificationCallback_(IGateKeeperCallback* _callback);

    StrongMT<TransportPipeTrafficTrackerFactory> tpttf;
    typedef map<Transport::TServiceId, StrongMT<TransportPipeTrafficTrackerFactory> > TPipeTrackers;
    TPipeTrackers trackers;
  };

 /// Доступ к гейту и нодам из прикладного уровня.
 /// Класс GateKeeper предназначен для доступа к гейту и нодам из прикладного уровня. 
 /// Он держит в себе гейт, коллекцию нод, а также ссылку на callback-объект.
 /// 
 /// См. также классы Gate и Node
 class GateKeeper : public GateKeeperBase 
 {
   NI_DECLARE_REFCOUNT_CLASS_1( GateKeeper, GateKeeperBase )

 public:
   /// Конструктор
   /// <param name="_transport">передаваемая ссылка на объект сетевого транспорта</param>
   /// <param name="_serviceId">код сервиса прикладного уровня</param>
   /// <param name="_clientId">дополнительный код (используется при создании канала), по умолчанию Transport::autoAssignClientId</param>
   /// <param name="callback">ссылка на callback-объект, по умолчанию 0</param>
   GateKeeper( Transport::ITransportSystem* _transport, const Transport::TServiceId& _serviceId, 
     Transport::TClientId _clientId = Transport::autoAssignClientId, IGateKeeperCallback* callback = 0,
     Network::NetAddress const & listenAddress = nstl::string());

   /// Деструктор
   ~GateKeeper()
   {
     Destroy();
   }

 private:
   StrongMT<Transport::ITransportSystem> transport;
   StrongMT<Transport::IChannelListener> listener;

   virtual StrongMT<Transport::IChannel> OpenChannel( const Transport::Address& address );
   virtual void OnPostPoll();

 };

 /// Доступ к гейту и нодам из прикладного уровня клиента.
 /// Класс GateKeeperClient аналогичен классу GateKeeper, 
 /// но использует при создании сетевой транспорт Transport::IClientTransportSystem, 
 /// и не содержит в конструкторе параметра _clientId.
 class GateKeeperClient : public GateKeeperBase 
 {
   NI_DECLARE_REFCOUNT_CLASS_1( GateKeeperClient, GateKeeperBase )

 public:
   /// Конструктор
   /// <param name="_transport">передаваемая ссылка на объект сетевого транспорта</param>
   /// <param name="_serviceId">код сервиса прикладного уровня</param>
   /// <param name="callback">ссылка на callback-объект, по умолчанию 0</param>
   GateKeeperClient( Transport::IClientTransportSystem* _transport, const Transport::TServiceId& _serviceId, IGateKeeperCallback* callback = 0 );

   /// Деструктор
   ~GateKeeperClient()
   {
     Destroy();
   }

   Transport::TClientId GetClientId() const;

 private:
   GateKeeperClient() {}

   StrongMT<Transport::IClientTransportSystem> transport;

   virtual StrongMT<Transport::IChannel> OpenChannel( const Transport::Address& address );
 };


 
class TransportPipe : public IPacketPipe, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( TransportPipe, IPacketPipe, BaseObjectMT );
public:
 TransportPipe( Transport::IChannel * channel, Transport::TServiceId _serviceId, TransportPipeTrafficTracker * _tptt );
 ~TransportPipe();

 bool IsClosed() const;
 StrongMT<rpc::Node> LockNode() { return node.Lock(); }
 void SetNode( rpc::Node * _node ) { node = _node; }

 virtual const char* GetName() const { return serviceId.c_str(); }
 virtual Transport::IChannel * GetPipeChannel() const { return channel; } 
 virtual IPacketPipe::PipeInfo GetInfo() const;
 virtual void Send( const byte* data, int size, bool force );
 virtual bool Recieve(int index, byte** data, int* size, Transport::MessageMiscInfo & _miscInfo );
 virtual bool Recieve(int index, byte** data, int* size );
 virtual void Reset();

private:
  WeakMT<rpc::Node> node; 
  Transport::TServiceId serviceId;
  nstl::vector<byte> dataCache;
  StrongMT<Transport::IChannel> channel;
  StrongMT<TransportPipeTrafficTracker> tptt;
};

}

#endif //#define GATEKEEPER_H_7868FF9E_2769_4E24
