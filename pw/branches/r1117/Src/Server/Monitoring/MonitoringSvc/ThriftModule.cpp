#include "stdafx.h"
#include <sys/socket.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/transport/THttpServer.h>

#include "MonitoringSvc/ThriftHandler.h"
#include "MonitoringSvc/ThriftModule.h"

using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;
using namespace apache::thrift::server;

namespace Monitoring
{
  ThriftModule::ThriftModule()
  {
  }

  ThriftModule::~ThriftModule()
  {
  }

  int ThriftModule::open(ThriftModuleCfg const & cfg)
  {
    nsocket::Initialize();
    boost::shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());
    boost::shared_ptr<ThriftHandler> handler(new ThriftHandler(cfg.mc));
    boost::shared_ptr<TProcessor> processor(new Thrift::MonitoringProcessor(handler));
    boost::shared_ptr<TServerTransport> serverTransport(new TServerSocket(cfg.port));
    boost::shared_ptr<TTransportFactory> transportFactory(new THttpServerTransportFactory());

    serverImpl.reset(new TSimpleServer(processor,
      serverTransport,
      transportFactory,
      protocolFactory));

    Resume();

    return 0;
  }

  int ThriftModule::close()
  {
    serverImpl->stop();
    bool exited = Wait( 5000 );
    NI_ASSERT( exited, "Thrift thread stop timed out" );
    return 0;
  }

  unsigned ThriftModule::Work()
  {
    if (serverImpl)
      serverImpl->serve();
    return 0;
  }
}
