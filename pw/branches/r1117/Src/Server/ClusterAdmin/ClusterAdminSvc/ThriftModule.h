#pragma once

#include "gen-cpp/ClusterManagement.h"
#include "system/Thread.h"

namespace apache { namespace thrift { namespace server {
  class TSimpleServer;
}}}

namespace ClusterAdmin
{
  class ClusterAdminImpl;

  struct ThriftModuleCfg
  {
    //nstl::string addr;
    int port;
    StrongMT<ClusterAdminImpl> impl;
  };

  class ThriftModule : public threading::Thread, public BaseObjectMT
  {
    NI_DECLARE_REFCOUNT_CLASS_1( ThriftModule, BaseObjectMT );

  public:
    ThriftModule();
    ~ThriftModule();

  public:
    int open(ThriftModuleCfg const & cfg);
    int close();

  protected:
    virtual unsigned Work();

  private:
    boost::shared_ptr<apache::thrift::server::TSimpleServer> serverImpl;
  };
}
