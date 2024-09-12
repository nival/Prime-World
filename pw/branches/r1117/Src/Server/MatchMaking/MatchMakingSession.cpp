#include "stdafx.h"

#include "RMatchMakingClient.auto.h"
#include "MatchMakingClientCtx.h"
#include "MatchMakingGameSvcMngrGetter.h"
#include "HybridServer/RGameServerDispenserIface.auto.h"
#include "MatchMakingClient.h"
#include "MatchMakingSession.h"
#include "HybridServer/RGameServerDispenserIface.auto.h"
#include "MatchMakingNaming.h"
#include "Server/ServerAppBase/ServerCfg.h"
#include "MatchMakingSvcCfg.h"


namespace MatchMaking
{

class SessionHybridLink : public lobby::ISessionHybridLink, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( SessionHybridLink, lobby::ISessionHybridLink, BaseObjectMT );
public:
  SessionHybridLink( Session * _session = 0 ) : session( _session ) {}

  virtual void OnGameFinish( Peered::TSessionId _sessionId, int gameResultType, const StatisticService::RPC::SessionClientResults & _finishInfo, const nstl::vector<Peered::SClientStatistics>& clientsStatistics ) {}
  virtual void OnGameCheated( Peered::TSessionId _sessionId, Transport::TClientId _clientId, /*ECheatType*/ int _cheatType, const char * _clientIp ) {}
  virtual void OnChangeClientStatus( Peered::TSessionId _sessionId, const nstl::vector<Peered::BriefClientInfo>& clientIds) {}

private:
  WeakMT<Session> session;
};



  Session::Session()
    :numberOfPlayers_(0),
    sid_(0),
    allPlayersReady_(false)
  {
  }

  Session::Session(SessionId const & sid, unsigned int numberOfPlayers, 
                   StrongMT<GameBalancer::RIBalancer> const & balancer, IManagerNotifier* mn,
                   StatisticService::GameStatClient * statistics )
    :sid_(sid),
    numberOfPlayers_(numberOfPlayers),
    balancer_(balancer),
    managerNotifier_(mn),
    allPlayersReady_(false),
    statwr_(statistics)
  {
    hybridLink = new SessionHybridLink( this );
    players_.reserve(numberOfPlayers_);
  }

  Session::~Session()
  {
    LOG_M(TMMLOG) << "Session(" << sid_ << ") destroyed" << endl;
  }

  bool Session::AddPlayer(StrongMT<MatchMaking::ClientCtx> const & pctx)
  {
    LOG_M(TMMLOG) << "Session(" << sid_ << "): add player(" << pctx->clientid() << ")" << endl;

    if (players_.size() < numberOfPlayers_)
    {
      players_.push_back(pctx);
      return true;
    }
    else
    {
      LOG_E(TMMLOG) << "Session(" << sid_ << "): can't add player(" << pctx->clientid() << ")." 
        << " Session is full" << endl;
      return false;
    }
  }

  void Session::PlayerReady(ClientId cid)
  {
    LOG_M(TMMLOG) << "Session(" << sid_ << "): player(" << cid << ") ready" << endl;

    bool allready = true;
    for(PlayersT::iterator it = players_.begin(); it != players_.end(); ++it)
    {
      StrongMT<ClientCtx> const & pctx = *it;
      if (cid == pctx->clientid())
        pctx->ready(true);

      if (allready)
        allready = pctx->ready();
    }

    if (allready)
    {
      NI_ASSERT(!allPlayersReady_, "This session already pass 'all players ready' stage");

      if (!allPlayersReady_)
      {
        allPlayersReady_ = true;

        LOG_M(TMMLOG) << "Session(" << sid_ << "): all players ready" << endl;

        if (Cfg::StatisticModeOn())
        {
          StatisticService::RPC::SessionStartEvent info;
          info.sessionid = sid_;
          info.map = NStr::ToUnicode( "mapX" );
          info.server = L"";
          info.sessionType = 4;

          info.players.reserve( players_.size() );

          for ( int i = 0; i < players_.size(); ++i )
          {
            StrongMT<ClientCtx> const & member = players_[i];

            info.players.push_back();
            StatisticService::RPC::SessionStartPlayer & dest = info.players.back();

            dest.userid = member->clientid();
            dest.faction = rand();
            dest.sex = rand();
            dest.heroid = 22648455; //  artist
            dest.nickname = L"flex";
          }

          statwr_->Message( info );
          OnStatisticsSessionNotify( true ); //hack
        }
        else
        {
          balancer_->AllocateGameSvc(HostServer::Cfg::GetSvcPath().c_str(), sid_, 
            RemotePtr<GameBalancer::RIBalancerCallback>(static_cast<GameBalancer::IBalancerCallback*>(this)), this, &Session::onAllocateGameSvc);
        }
      }
    }
  }

  void Session::OnStatisticsSessionNotify( bool result )
  {
    LOG_M(TMMLOG) << "Session(" << sid_ << "): game server received" << endl;

    //  send notification to clients
    for(PlayersT::iterator it = players_.begin(); it != players_.end(); ++it)
    {
      (*it)->remoteClient()->OnSessionStarted(0);
    }
    managerNotifier_->OnGameSessionStarted(this);
  }



  void Session::onAllocateGameSvc(int result)
  {
    if (result < 0)
    {
      LOG_E(TMMLOG).Trace("%s: allocation is failed(res=%d)", __FUNCTION__, result);
    }
    else
    {
      LOG_M(TMMLOG).Trace("%s: allocation is OK(allocid=%d)", __FUNCTION__, result);
    }
  }

  void Session::OnGameSvcAllocated(Peered::TSessionId userctx, uint allocid, HybridServer::IGameServerDispenser* gs)
  {
    NI_ASSERT(userctx == (Peered::TSessionId)sid_, "");

    if (!gs)
    {
      LOG_E(TMMLOG).Trace("%s: allocation is failed(sid=%016x allocid=%d)", __FUNCTION__, sid_, allocid);
      return;
    }

    LOG_M(TMMLOG).Trace("%s: game dispenser received successfully(sid=%016x allocid=%d)", __FUNCTION__, sid_, allocid);

    gsDispenser_ = (HybridServer::RIGameServerDispenser*)gs;

    vector<Peered::ClientInfo> clientIds;
    clientIds.reserve( players_.size() );
    for( PlayersT::iterator it = players_.begin(); it != players_.end(); ++it )
    {
      Peered::ClientInfo info;
      info.clientId = (*it)->clientid();
      clientIds.push_back( info );
    }

    // Game line up with one default client - just to avoid GS crash due to RPC bug (NUM_TASK)
    lobby::TGameLineUp gameLineUp(1);

    Peered::SAllocationParams params;
    params.allocid = allocid;
    params.sessionId = sessionid();
    params.clientsInfo = clientIds;
    params.auxData = Peered::SAuxData();
    params.gameParams = lobby::SGameParameters();
    params.gameLineUp = gameLineUp;

    gsDispenser_->AcquireNewServer( params, hybridLink, this );
  }

  void Session::GameServerAllocated( Peered::RIGameServer * _clientsInterface, Peered::RIGameServerInternal * _internalInterface, const Peered::SInstanceId& _instId )
  {
    LOG_M(TMMLOG) << "Session(" << sid_ << "): game server received" << endl;
    NI_VERIFY( _clientsInterface && _internalInterface, "", return );

    //  send notification to clients
    for(PlayersT::iterator it = players_.begin(); it != players_.end(); ++it)
    {
      (*it)->remoteClient()->OnSessionStarted( _clientsInterface );
    }
    gameServer = _clientsInterface;
    gameServerInternal = _internalInterface;

    managerNotifier_->OnGameSessionStarted( this );
  }

  bool Session::checkGameFinished()
  {
    unsigned int count = MatchMaking::Cfg::GetSessionSize();
    for (PlayersT::iterator it = players_.begin();it != players_.end(); ++it)
    {
      if ((*it)->remoteClient()->GetHandler()->GetStatus() == rpc::Disconnected)
      {
        --count;
      }
    }
    if (count <= 0)
      return true;

    return false;
  }

  void Session::sendSessionFinish()
  {
    StatisticService::RPC::SessionResultEvent info;
    for(PlayersT::iterator it = players_.begin(); it != players_.end(); ++it)
    {
      StrongMT<ClientCtx> cctx = *it;
      StatisticService::RPC::SessionClientResultsPlayer player;
      player.userid = cctx->clientid();
      //int finalLevel;
      //int score;
      //int kills;
      //int deaths;
      //int assists;
      //int enemyCreepsKilled;
      //int neutralCreepsKilled;
      info.clientData.players.push_back(player);

      StatisticService::RPC::SessionServerResultsPlayer svPlr;
      svPlr.userid = cctx->clientid();
      svPlr.finishStatus = Peered::EGameFinishClientState::FinishedGame;
      info.serverPlayersInfo.push_back( svPlr );
    }
    info.result = 1;
    info.sessionid = sessionid();
    info.clientData.sideWon = 0;

    statwr_->Message( info );
  }
}
