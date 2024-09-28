#pragma once
#include <Server/RPC/RPC.h>
#include "MatchMakingTypes.h"

namespace MatchMaking
{
  REMOTE class ISession : public rpc::IRemoteEntity
  {
    RPC_ID();

    REMOTE virtual void PlayerReady(MatchMaking::ClientId cid) = 0;
  };
}
