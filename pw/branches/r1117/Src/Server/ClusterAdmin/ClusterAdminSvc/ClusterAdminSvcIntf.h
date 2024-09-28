#pragma once
#include <RPC/RPC.h>
#include "ClusterAdminNaming.h"

namespace ClusterAdmin
{
  REMOTE struct IClusterAdmin : public IBaseInterfaceMT
  {
    RPC_ID();

    REMOTE virtual void Shutdown(unsigned int timeout) = 0;
  };
}
