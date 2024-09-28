#ifndef SERVERRUNNNER_H_3C4F3557_F6CD_48
#define SERVERRUNNNER_H_3C4F3557_F6CD_48

#include "Coordinator/Interface.h"


namespace Transport
{

class IAddressTranslator;

typedef map<string, string> TServerCmdLine;
typedef set<string> TServiceOptions;



struct ServiceOptions
{
  TServiceOptions   options;
  TServerCmdLine    commandLine;
};



struct ServiceParams : public ServiceOptions
{
  TServiceId                                  serviceId;
  StrongMT<Network::INetworkDriver>           driver;
  StrongMT<ITransportSystem>                  backendTransport, frontendTransport;
  StrongMT<Coordinator::ICoordinatorClient>   coordClient;

  ServiceParams()
  {}

  ServiceParams( const ServiceOptions & _options ) :
  ServiceOptions( _options )
  {}
};



class IServerRunner : public IBaseInterfaceMT
{
  NI_DECLARE_CLASS_1( IServerRunner, IBaseInterfaceMT );

public:
  virtual const Coordinator::TServiceRole & GetRole() const  { return Coordinator::defaultServiceRole; } //ATTENTION: This is called BEFORE 'StartInstance()'

  // В этой функции надо создать ChannelListener'ы для всех интерфейсов сервиса (CreateChannelListener() ДОЛЖЕН отработать до 
  // выхода из функции) и запустить тред сервера. serviceId содержит имя конкретного инстанса сервиса, не класса сервисов 
  // (напр. "location/1", а не "location"). В CreateChannelListener надо использовать именно это имя. В _coordClient можно 
  // вызывать функцию GetCoordinatorInterface() - она вернёт интерфейс сервера
  virtual void StartInstance( const ServiceParams & _params ) = 0;

  virtual void StopInstance( const TServiceId & serviceId ) = 0;
  virtual void SoftStopInstance( const TServiceId & serviceId ) = 0;

  virtual void OnConfigReload() { NI_ALWAYS_ASSERT( "Not implemented" ); }
};




class IServiceSpawner : public IBaseInterfaceMT
{
  NI_DECLARE_CLASS_1( IServiceSpawner, IBaseInterfaceMT );

public:
  IServiceSpawner() {}
  virtual ~IServiceSpawner() {}

  virtual const TServiceId & ServiceClass() const = 0;
  virtual unsigned DefaultInstancesNumber() const = 0;
  virtual const Coordinator::SInterfacePolicy & Policy() const = 0;
  virtual bool ServiceIsExternal() const = 0 ;
  virtual IServerRunner * SpawnService() const = 0;
};


} // namespace Transport

#endif //#define SERVERRUNNNER_H_3C4F3557_F6CD_48
