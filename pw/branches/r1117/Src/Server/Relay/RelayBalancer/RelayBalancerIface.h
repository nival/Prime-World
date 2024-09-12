#pragma once
#include <RPC/RPC.h>
#include <Network/Address.h>
#include <Network/TransportTypes.h>
#include <ClusterTypes/ClusterTypes.h>

namespace Relay
{
  REMOTE class IBalancerCallback : public rpc::IRemoteEntity
  {
    NI_DECLARE_CLASS_1( IBalancerCallback, IRemoteEntity );
    RPC_ID();

  public:
    REMOTE virtual void OnRelayAllocated(Transport::TClientId clienid, int userctx, 
      Transport::TServiceId const & genericrelay, Network::NetAddress const & genericaddr,
      Transport::TServiceId const & gamerelay, Network::NetAddress const & gameaddr) = 0;
  };

  class RIBalacerCallback;

  namespace Role
  {
    enum Enum
    {
      PRIMARY,
      SECONDARY,
      BOTH
    };
  }

  REMOTE class IBalancer : public IBaseInterfaceMT
  {
    NI_DECLARE_CLASS_1( IBalancer, IBaseInterfaceMT );
    RPC_ID();

  public:
    REMOTE virtual int AllocateRelay(Cluster::TGameId gameid, Transport::TClientId clienid, Transport::TServiceId const & svcpath, Coordinator::TServiceRole const & _svcrole, int userctx, Relay::IBalancerCallback* cb) = 0;
  };
}
