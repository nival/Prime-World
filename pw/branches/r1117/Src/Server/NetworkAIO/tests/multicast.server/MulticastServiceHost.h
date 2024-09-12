#pragma once

#include <ServerAppBase/ServerAppBase.h>

namespace TransportTest
{
  class MulticastServiceHost : public Transport::ServerAppBase
  {
  public:
    MulticastServiceHost(); 

    virtual bool OnInitServerFactory( Transport::NivalServer * _serverFactory );

    virtual bool  OnInit(int argc, char* argv[]);
    virtual int   OnExit();
  };
}
