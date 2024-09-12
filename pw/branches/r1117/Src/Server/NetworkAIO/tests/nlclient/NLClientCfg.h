#pragma once
#include <naio/Driver.h>
#include <naio/Cfg.h>

namespace NetworkLayer
{
  namespace NL = NetworkLayer;

  struct ClientCfg
  {
    naio::Cfg naiocfg_;
    nstl::string serverAddr_;
  };
}
