#pragma once
#include <RPC/RPC.h>
#include "HybridServer/RGameServerDispenserIface.auto.h"

namespace GameBalancer
{
  REMOTE class IBalancerCallback : public rpc::IRemoteEntity
  {
    NI_DECLARE_CLASS_1( IBalancerCallback, IRemoteEntity );

    RPC_ID();

  public:
    REMOTE virtual void OnGameSvcAllocated(Peered::TSessionId userctx, uint allocid, HybridServer::IGameServerDispenser* gs) = 0;
  };

  class RIBalacerCallback;

  REMOTE class IBalancer : public IBaseInterfaceMT
  {
    NI_DECLARE_CLASS_1( IBalancer, IBaseInterfaceMT );

    RPC_ID();

  public:
    REMOTE virtual int AllocateGameSvc(Transport::TServiceId const & svcpath, Peered::TSessionId userctx, IBalancerCallback* cb) = 0;
  };
}
