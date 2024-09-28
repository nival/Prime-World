#include "stdafx.h"
//#include <sys/socket.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/transport/THttpServer.h>
#include "ClusterAdmin/ClusterAdminSvc/ClusterAdminNaming.h"

#include "ThriftHandler.h"
#include "ThriftModule.h"

using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;
using namespace apache::thrift::server;

namespace ClusterAdmin
{
  ThriftModule::ThriftModule()
  {
  }

  ThriftModule::~ThriftModule()
  {
  }

  int ThriftModule::open(ThriftModuleCfg const & cfg)
  {
    LOG_M(CALOG).Trace("Initailizing thrift. port=%d", cfg.port );

    //nsocket::Initialize();
    boost::shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());
    boost::shared_ptr<ThriftHandler> handler(new ThriftHandler(cfg.impl));
    boost::shared_ptr<TProcessor> processor(new Thrift::ClusterManagementProcessor(handler));
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
    return 0;
  }

  unsigned ThriftModule::Work()
  {
    try
    {
      serverImpl->serve();
    }
    catch ( const apache::thrift::TException & te )
    {
      LOG_E(CALOG).Trace( "Thrift exception: %s", te.what() );
    }

    return 0;
  }
}
