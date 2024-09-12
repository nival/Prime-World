#pragma once
#include <naio/Driver.h>
#include <naio/Cfg.h>
#include "NLClientCfg.h"

namespace NetworkLayer
{
  namespace NL = NetworkLayer;

  struct Client
  {
    ClientCfg cfg_;

    int Run();
  };
}
