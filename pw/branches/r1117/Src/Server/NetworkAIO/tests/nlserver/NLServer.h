#pragma once
#include <naio/Driver.h>
#include <naio/Cfg.h>

namespace NetworkLayer
{
  namespace NL = NetworkLayer;

  struct Server
  {
    naio::Cfg naiocfg_;
    int delay;
    nstl::string listenAddr;

    int messagesSent;
    int messagesReceived;

    int Run();
  };
}
