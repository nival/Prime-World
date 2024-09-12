#pragma once
#include <RPC/RPC.h>
#include <Network/TransportTypes.h>

namespace MulticastTest
{
  REMOTE struct IMulticastSession : public IBaseInterfaceMT
   {
    RPC_ID();
    REMOTE virtual void ConfirmStep(Transport::TClientId _cid, unsigned int _step)=0;
  };
}
