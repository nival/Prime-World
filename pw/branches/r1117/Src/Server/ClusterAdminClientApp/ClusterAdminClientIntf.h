#pragma once

namespace ClusterAdmin
{
  struct ClientConfig
  {
    nstl::string svcNetAddr_;
  };

  class IClient : public IBaseInterfaceMT
  {
  public:
    virtual void Shutdown(unsigned int seconds) = 0;
  };
}
