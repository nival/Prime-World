#pragma once
#include <Server/RPC/RPC.h>
#include "MatchMakingTypes.h"
#include "HybridServer/RPeered.auto.h"
#include "MatchMakingSessionIface.h"

namespace MatchMaking
{
  class RSession;

  REMOTE struct IClient : public IBaseInterfaceMT
  {
    RPC_ID();

    REMOTE virtual void MatchMakingCompleted(int res, SessionId sid, MatchMaking::ISession* session) = 0;
    REMOTE virtual void OnSessionStarted(Peered::IGameServer* gsrv) = 0;
  };

  class IClientNotifier
  {
  public:
    virtual void MatchMakingCompleted(int res, SessionId sid, MatchMaking::ISession* session) = 0;
    virtual void OnSessionStarted(Peered::IGameServer* gsrv) = 0;
  };

  class Client : public IClient, public BaseObjectMT
  {
    NI_DECLARE_REFCOUNT_CLASS_2( Client, IClient, BaseObjectMT );

  public:
    Client();
    Client(IClientNotifier* cn, int userid);
    ~Client();

    REMOTE void MatchMakingCompleted(int res, SessionId sid, MatchMaking::ISession* session);
    REMOTE void OnSessionStarted(Peered::IGameServer* gsrv);

  private:
    IClientNotifier* cn_;
    int userid_;
  };
}
