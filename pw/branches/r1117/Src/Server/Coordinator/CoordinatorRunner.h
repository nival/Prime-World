#pragma once
#include "Network/Network.h"
#include "Network/Transport.h"
#include "Network/TransportInitializer.h"
 
#include "Coordinator/CoordinatorClient.h"
#include "Coordinator/CoordinatorServer.h"
#include "ServerAppBase/ServerRunner.h"
#include "System/JobThread.h"

namespace Coordinator
{

class CoordinatorServerJob : public threading::IThreadJob, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( CoordinatorServerJob, threading::IThreadJob, BaseObjectMT );

public:
  CoordinatorServerJob( Transport::ITransportSystem * _transport, const string & _coordinatorAddress );
  ~CoordinatorServerJob();

  Coordinator::CoordinatorServer * GetServer() const { return coordinatorServer; }

private:
  virtual void Work( volatile bool & isRunning );

private:
  StrongMT<rpc::GateKeeper>                 gateKeeper;
  StrongMT<Coordinator::CoordinatorServer>  coordinatorServer;
};
}
