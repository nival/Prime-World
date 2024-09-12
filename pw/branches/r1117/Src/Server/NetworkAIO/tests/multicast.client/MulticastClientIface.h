#pragma once
#include <Server/RPC/RPC.h>
#include <NetworkAIO/tests/multicast.server/RMulticastSessionIface.auto.h>

namespace MulticastTest
{
  REMOTE struct IMulticastClient : rpc::IRemoteEntity
  {
    RPC_ID();
    NI_DECLARE_CLASS_1(IMulticastClient, rpc::IRemoteEntity);

    REMOTE virtual void Step(int step) = 0;
    REMOTE virtual void OnRegisterClient(RIMulticastSession* _session) = 0;
  };
}
