#pragma once
#include <RPC/RPC.h>
#include <NetworkAIO/tests/multicast.client/RMulticastClientIface.auto.h>

namespace MulticastTest
{
  REMOTE struct IMulticastSvc : public IBaseInterfaceMT
  {
    RPC_ID();
    REMOTE virtual int RegisterClient(const char* name, uint clientId, NI_LPTR IMulticastClient* _client)=0;
    REMOTE virtual void ConfirmStep(unsigned int _sessionid, unsigned int _step)=0;
  };
}
