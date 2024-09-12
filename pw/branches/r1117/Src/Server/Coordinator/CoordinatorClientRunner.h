#pragma once
#include "RPC/GateKeeper.h"
#include "System/JobThread.h"

namespace Network
{
  _interface INetworkDriver;
}

namespace Coordinator
{

class CoordinatorClient;

class CoordinatorClientRunnerTicker;

class CoordinatorClientRunner : public BaseObjectMT, public threading::IThreadJob
{
  NI_DECLARE_REFCOUNT_CLASS_1( CoordinatorClientRunner, BaseObjectMT );

public:
  CoordinatorClientRunner( const Transport::TServiceId & _svcpath, Network::INetworkDriver * _netDriver );

  CoordinatorClient * GetClient() { return client; }

  void Open( Transport::ITransportSystem * _backendTransport, Transport::ITransportSystem * _frontendTransport, const Network::NetAddress & _coordinatorAddress, const nstl::string & _source );

private:
  virtual void Work( volatile bool & _isRunning );

  StrongMT<CoordinatorClient> client;
  StrongMT<rpc::GateKeeper> gk;
  StrongMT<Network::INetworkDriver> netDriver;
};

} //namespace Coordinator
