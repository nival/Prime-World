#pragma once

#include <RPC/RPC.h>
#include "RPeered.auto.h"
#include "Server/Roll/RollTypes.h"
#include "PeeredTypes.h"

namespace Peered
{
  class CommandsScheduler;
  struct ClientInfo;
}

namespace lobby
{
  class ISessionHybridLink;
  class RISessionHybridLink;
}

namespace HybridServer
{
  REMOTE class IGameServerDispenserCallback : public rpc::IRemoteEntity
  {
    RPC_ID();
    NI_DECLARE_CLASS_1( IGameServerDispenserCallback, rpc::IRemoteEntity );
  public:

    REMOTE virtual void GameServerAllocated( Peered::RIGameServer* _clientsInterface, Peered::RIGameServerInternal* _internalInterface, const Peered::SInstanceId& _instId ) = 0;
  };


  class RIGameServerDispenserCallback;


  REMOTE struct IGameServerDispenser : public rpc::IRemoteEntity
  {
    NI_DECLARE_CLASS_1( IGameServerDispenser, rpc::IRemoteEntity );

    RPC_ID();

    REMOTE virtual void AcquireNewServer( const Peered::SAllocationParams& _params, NI_LPTR lobby::ISessionHybridLink* _session, NI_LPTR IGameServerDispenserCallback* _cb ) = 0;
  };
}
