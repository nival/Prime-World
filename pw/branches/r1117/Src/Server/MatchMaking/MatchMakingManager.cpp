#include "stdafx.h"

#include <Server/RPC/RPC.h>
#include "RMatchMakingClient.auto.h"
#include "MatchMakingSession.h"
#include "MatchMakingClient.h"
#include "MatchMakingManager.h"
#include "MatchMakingNaming.h"
#include "MatchMakingSvcCfg.h"

NI_DEFINE_REFCOUNT( MatchMaking::Manager )

namespace MatchMaking
{
  Manager::Manager( StatisticService::GameStatClient * statIface )
    :statIface_(statIface)
  {
  }

  Manager::~Manager()
  {
  }

  ClientId Manager::RequestMatchMaking(MatchMaking::RIClient* pclient)
  {
    StrongMT<ClientCtx> pctx = RegisterClient_(pclient);
    if (pctx)
    {
      requests_.push_back(pctx);
      LOG_M(TMMLOG).Trace("New client registered(mmcid=%d)", pctx->clientid());
      return pctx->clientid();
    }
    else
    {
      LOG_E(TMMLOG).Trace("Matchmaking request is FAILED: can't register client");
      return INVALID_CLIENT_ID;
    }
  }

  void Manager::Step()
  {
    bool bcontinue = true;
    while (bcontinue && Cfg::GetSessionSize() <= requests_.size())
    {
      if (gameBalancer_ || Cfg::StatisticModeOn())
      {
        //  create session
        StrongMT<Session> s = CreateSession_(Cfg::GetSessionSize());
        if (s)
        {
          //  add clients to session
          for(unsigned int i = 0; i < (unsigned)Cfg::GetSessionSize(); ++i)
          {
            StrongMT<ClientCtx> ctx = requests_.front();
            s->AddPlayer(ctx);

            //  send session to clients
            ctx->remoteClient()->MatchMakingCompleted(0, s->sessionid(), RemotePtr<MatchMaking::RISession>(s));

            requests_.pop_front();
          }
        }
        else
        {
          systemLog(NLogg::LEVEL_ASSERT) << "Can't create session" << endl;
          bcontinue = false;
        }
      }
    }

    for (RequestQueueT::iterator it = requests_.begin();it != requests_.end();)
    {
      if ((*it)->remoteClient()->GetHandler()->GetStatus() == rpc::Disconnected)
      {
        it = requests_.erase(it);
      }
      else
      {
        ++it;
      }
    }

    for (SessionsT::iterator it = sessions_.begin();it != sessions_.end();)
    {
      if (it->second->checkGameFinished())
      {
        it->second->sendSessionFinish();
        it = sessions_.erase(it);
      }
      else
      {
        ++it;
      }
    }
  }

  void Manager::CancelMatchMaking(ClientId const & cid)
  {
    for(RequestQueueT::iterator it = requests_.begin();
      it != requests_.end();)
    {
      if ((*it)->clientid() == cid)
      {
        it = requests_.erase(it);
      }
      else
      {
        ++it;
      }
    }

    UnregistedClient_(cid);
  }

  StrongMT<Session> Manager::CreateSession_(unsigned int numberOfPlayers)
  {
    SessionId sid = GenerateSessionId_();
    if (INVALID_SESSION_ID == sid)
    {
      LOG_E(TMMLOG).Trace("Can't create session: no free session id");
      return StrongMT<Session>();
    }

    if (!Cfg::StatisticModeOn() && !gameBalancer_)
    {
      LOG_E(TMMLOG).Trace("Can't create session: no game balancer");
      return StrongMT<Session>();
    }

    if (Cfg::StatisticModeOn() && !statIface_->Ready())
    {
      LOG_E(TMMLOG).Trace("Statistic iface is not available");
      return StrongMT<Session>();
    }

    StrongMT<Session> s(new Session(sid, numberOfPlayers, gameBalancer_ /*static_cast<IGameSvcMngrGetter*>(this)*/,
      static_cast<IManagerNotifier*>(this), statIface_));

    nstl::pair<SessionsT::iterator, bool> res = sessions_.insert(nstl::make_pair(sid, s));
    if (!res.second)
    {
      LOG_E(TMMLOG).Trace("Can't create session: session with the same id already exist(sid=%016x)", sid);
      return StrongMT<Session>();
    }

    return s;
  }

  StrongMT<ClientCtx> Manager::RegisterClient_(MatchMaking::RIClient* pclient)
  {
    StrongMT<rpc::INode> node = pclient->GetHandler()->GetNode(0);
    if (!node)
      return StrongMT<ClientCtx>();

    ClientId cid = node->GetConnectedPipe()->GetInfo().pipeId;
    if (INVALID_CLIENT_ID == cid)
      return StrongMT<ClientCtx>();

    pair<ClientCtxMapT::iterator,bool> res = clients_.insert(make_pair(cid, new ClientCtx(cid, pclient)));
    if (!res.second)
      return StrongMT<ClientCtx>();

    return res.first->second;
  }

  void Manager::UnregistedClient_(ClientId const & cid)
  {
    clients_.erase(cid);
  }

  void Manager::OnGameSessionStarted(Session const * s)
  {
    SessionId sid = s->sessionid();

    if (!Cfg::StatisticModeOn())
    {
      s = 0;
      sessions_.erase(sid);
    }
  }

  void Manager::onChangeState(rpc::IfaceRequesterState::Enum st, 
    StrongMT<rpc::IfaceRequester<GameBalancer::RIBalancer>> const & ifacereq)
  {
    if (rpc::IfaceRequesterState::OPENED == st)
    {
      gameBalancer_ = ifacereq->iface();
    }
    else
    if (rpc::IfaceRequesterState::CLOSED == st)
    {
      gameBalancer_ = 0;
    }
  }
}
