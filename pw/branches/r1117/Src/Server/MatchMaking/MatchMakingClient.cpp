#include "stdafx.h"

#include "MatchMakingSessionIface.h"
#include "MatchMakingClient.h"

namespace MatchMaking
{
  Client::Client()
    :userid_(0),
    cn_(0)
  {
  }

  Client::Client(IClientNotifier* cn, int userid)
    :cn_(cn),
    userid_(userid)
  {
  }

  Client::~Client()
  {
  }

  void Client::MatchMakingCompleted(int res, SessionId sid, MatchMaking::ISession* session)
  {
    cn_->MatchMakingCompleted(res, sid, session);
  }

  void Client::OnSessionStarted(Peered::IGameServer * gsrv)
  {
    cn_->OnSessionStarted(gsrv);
  }
}
