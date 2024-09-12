#pragma once

#include "Game/PF/Tests/GTCBase/GTCBase.h"
#include "Server/Statistic/GameStatClient.h"
#include "PF_GameLogic/SessionEventType.h"
#include "Server/Statistic/StatisticsServerTypes.h"
#include "Server/Statistic/StatisticsClientTypes.h"
#include "TMMakingClientWrapper.h"

namespace GameTestClient2
{
  typedef std::vector<int> EventFreqT;      //  index is event, value is how many times this event happened during a session
  typedef std::vector<int> EventsScheduleT; //  index event, value - each step
 
  namespace StatStage
  {
    enum
    {
      INVALID = -1,
      INITIAL = BaseStage::LOGIN_FINISHED_POST_STEP,
      REQ_MATCH_MAKING_MANAGER_STARTED,
      REQ_MATCH_MAKING_MANAGER_FINISHED,
      REQ_MATCH_MAKING_STARTED,
      REQ_MATCH_MAKING_FINISHED,
      MATCH_MAKING_COMPLETED,
      PLAYER_READY_TO_PLAY,
      REQUEST_STAT_RPC_NODE_START,
      REQUEST_STAT_RPC_NODE_WAIT,
      QUERY_STAT_WRITER_START,
      QUERY_STAT_WRITER_IN_PROGRESS,
      QUERY_STAT_WRITER_IN_FINISHED,
      LOG_GAME_SESSION_START,
      LOG_GAME_SESSION_EVENTS,
      LOG_GAME_SESSION_FINISH,
      STAT_SESSION_FINISHED,
      NUMBER_OF_STAGES
    };
  };


  class StatSvcTestClient : public ClientBase, public ITMMakingClientWrapperCb, public BaseObjectMT
  {
    NI_DECLARE_REFCOUNT_CLASS_3( StatSvcTestClient, ClientBase, ITMMakingClientWrapperCb, BaseObjectMT );

  public:

    enum EventType
    {
      DamageEvt = SessionEventType::NumberOfEvents,
      DebugVarEvt = SessionEventType::NumberOfEvents + 1,
    };

  public:
    StatSvcTestClient(unsigned int sessionDurationInSteps,
      EventsScheduleT const & schedule,
      int localid, 
      StrongMT<Network::INetworkDriver> const & driver, 
      StrongMT<TransportLayer::TransportModule> const & sptm = 0, 
      unsigned int stepInMs = 100,
      nstl::string const & loginaddr = "",
      nstl::string const & user = "", 
      nstl::string const & pswd = "",
      nstl::string const & sessionKey = "");
    ~StatSvcTestClient();

  public:

    int Step();

    static char const * stageName(int st);

  protected:
    //  init statistics callback
    void OnStatisticsSessionNotify( int _statisticsSessionId );

    //  
    int LogSessionEvent(unsigned int evtid);
    int LogDamageEvent(StatisticService::RPC::SessionDamageInfo & sdi);
    int LogDebugVarEvent(int step, const nstl::wstring& debugVarName, const nstl::wstring& debugVarValue);

    //  ITMMakingClientWrapperCb
    virtual void OnMatchMakingManagerReceived(Result::Enum rc);
    virtual void OnRegisterMatchMaking(Result::Enum rc);
    virtual void OnMatchMakingCompleted(Result::Enum rc, MatchMaking::SessionId sid);
    virtual void OnSessionStarted(Peered::IGameServer* gsrv);

  private:
    wstring const & unicodeUsername() const;
    void unicodeUsername(string const & username);

    void sessionId(int sid);
    int sessionId() const;

  private:
    // statistics
    Timestamp timeStatNodeReqStart_;

    Timestamp timeStaticticsStarted_;
    StrongMT<StatisticService::GameStatClient> gstatCl;
    int statSessionId_;

    unsigned int sessionDurationInSteps_;
    EventsScheduleT const & schedule_;
    EventsScheduleT lastExecutedSteps_;
    wstring unicodeUsername_;
    StrongMT<TMMakingClientWrapper> mmcwrapper_;
  };

  inline
  wstring const & StatSvcTestClient::unicodeUsername() const
  {
    return unicodeUsername_;
  }
  
  inline
  void StatSvcTestClient::unicodeUsername(string const & username)
  {
    unicodeUsername_ = NStr::ToUnicode(username);
  }

  inline
  void StatSvcTestClient::sessionId(int sid)
  {
    statSessionId_ = sid;
  }

  inline
  int StatSvcTestClient::sessionId() const
  {
    return statSessionId_;
  }

  void GenerateEventSchedule(EventFreqT const & eventFreq,
    unsigned int sessionDurationInMs, //  1 step is 100ms, so 30min session is 18000 steps
    unsigned int stepInMs,
    EventsScheduleT& schedule);

}
