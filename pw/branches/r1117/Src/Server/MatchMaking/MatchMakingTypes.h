#pragma once

namespace HybridServer
{
  class RIGameServerDispenser;
}

namespace MatchMaking
{
  typedef unsigned int ClientId;
  const ClientId INVALID_CLIENT_ID = (ClientId)(-1);

  typedef long long SessionId;
  const SessionId INVALID_SESSION_ID = (SessionId)(-1);

  const unsigned int DEFAULT_SESSION_SIZE = 10;

  typedef StrongMT<HybridServer::RIGameServerDispenser> GameSvcMngrStrongPtr;
  typedef WeakMT<HybridServer::RIGameServerDispenser> GameSvcMngrWeakPtr;
}


