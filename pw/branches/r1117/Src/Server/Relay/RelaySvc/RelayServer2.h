#pragma once
#include "Network/Network.h"
#include "Network/Message.h"
#include "ServerAppBase/NivalService.h"
#include "Network/TransportUtils.h"
#include "System/IDGenerator.h"
#include "Network/TransportClientsVerifier.h"
#include "System/ThreadNames.h"
#include "System/TextFileDumper.h"
#include "LogCallback.h"
#include "Coordinator/Interface.h"
#pragma warning(push)
#pragma warning(disable:4996)
#include <ace/Event.h>
#pragma warning(pop)

namespace NLogg
{
  class CChannelLogger;
}

namespace Relay
{

class ClientsVerifier;

class RelayServer2 : public Transport::BaseService
{
  NI_DECLARE_REFCOUNT_CLASS_1( RelayServer2, Transport::BaseService );

public:
  RelayServer2( const Transport::ServiceParams & _svcParams, const Transport::CustomServiceParams & _customParams,
    Transport::TServiceId const & _frontendSvcid, Transport::TServiceId const & _backendSvcid );
  ~RelayServer2();

  void SetVerifier( Transport::IClientsVerifier* verifier );

private:
  Transport::MessageFactory factory;

  Transport::TServiceId frontendSvcid, backendSvcid;
  Network::NetAddress frontendListenAddr, backendListenAddr;

  StrongMT<ClientsVerifier>     verifier;
  ACE_Event                     justAnEventToWait;
  NLogg::CChannelLogger*        logStream;
  NLogg::BasicTextFileDumper*   logDumper;
  LogCallback*                  logcb;

protected:
  void ThreadMain( volatile bool & _isRunning );
};

}
