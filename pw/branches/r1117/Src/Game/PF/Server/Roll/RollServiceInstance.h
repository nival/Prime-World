#ifndef ROLL_SERVICE_INSTANCE_H_INCLUDED
#define ROLL_SERVICE_INSTANCE_H_INCLUDED

#include "RollInstance.h"
#include "rpc/IfaceRequester.h"
#include "System/JobThread.h"
#include "RollConfig.h"
#include <list>


namespace roll
{

class RIBalancer;
class BaseJob;
class DropNRoll;
class SeClientWorker;
class InstanceSvc;

class Instance : public IInstance, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( Instance, IInstance, BaseObjectMT );

public:
  RPC_ID();

  Instance( rpc::GateKeeper * gk, const Transport::TServiceId & _serviceId, InstanceSvc* _instancesvc );

  void Poll();
  void OnConfigReload();

  //IInstance
  virtual void Roll( IClient * client, const SPreGameData & preGame, const SPostGameData & postGame );
  virtual void ForgeRoll( NI_LPTR IClient* client, const SForgeRollData & data );
  
  InstanceSvc*  InstSvc() { return instanceSvc;};

private:
  class ConfigProvider;

  typedef std::list<StrongMT<BaseJob>> Jobs;

  StrongMT<IConfigProvider> config;

  Transport::TServiceId serviceId;

  StrongMT<rpc::GateKeeper> gateKeeper;
  StrongMT<rpc::IfaceRequester<RIBalancer>>  balancer;
  timer::Time lastLoadSent;
  timer::Time lastConnectedTime;

  Strong<DropNRoll>  logic;

  Jobs  jobs;

  StrongMT<SeClientWorker>  seClient;
  StrongMT<threading::JobThread> seClientThread;
  InstanceSvc* instanceSvc;
};

} //namespace roll

#endif //ROLL_SERVICE_INSTANCE_H_INCLUDED
