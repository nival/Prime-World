#include "stdafx.h"

#include <Network/Initializer.h>
#include <Network/Transport.h>
#include <Network/TransportInitializer.h>
#include <Network/TransportMessages.h>
#include <Network/ClientTransportSystem2.h>
#include <Network/ClientTransportSystemIntf.h>
#include <Network/AddressTranslator.h>
#include <Network/FreePortsFinder.h>
#include <transport/TLTransportModule.h>
#include "Server/DebugVarUpdate/DebugVarReporter.h"
#include "Server/Statistic/StatClientHttpDispatcher.h"

#include "System/InlineProfiler.h"

#include "StatSvcTestClient.h"

namespace GameTestClient2
{
  namespace StatStage
  {
    char const * stageNames[] = 
    {
      "REQ_MATCH_MAKING_MANAGER_STARTED",
      "REQ_MATCH_MAKING_MANAGER_FINISHED",
      "REQ_MATCH_MAKING_STARTED",
      "REQ_MATCH_MAKING_FINISHED",
      "MATCH_MAKING_COMPLETED",
      "PLAYER_READY_TO_PLAY",
      "REQUEST_STAT_RPC_NODE_START",
      "REQUEST_STAT_RPC_NODE_WAIT",
      "CREATE_STAT_WRITER",
      "LOG_GAME_SESSION_START",
      "LOG_GAME_SESSION_EVENTS",
      "LOG_GAME_SESSION_FINISH",
      "STAT_SESSION_FINISHED",
    };
  };

  StatSvcTestClient::StatSvcTestClient(unsigned int sessionDurationInSteps,
                EventsScheduleT const & schedule,
                int localid, 
                StrongMT<Network::INetworkDriver> const & driver,
                StrongMT<TL::TransportModule> const & sptm, 
                unsigned int stepInMs,
                nstl::string const & loginaddr,
                nstl::string const & user, nstl::string const & pswd,
                nstl::string const & sessionKey)
    :ClientBase(localid, driver, sptm, stepInMs, loginaddr, user, pswd, sessionKey),
    sessionDurationInSteps_(sessionDurationInSteps),
    schedule_(schedule)
  {
    lastExecutedSteps_.resize(schedule_.size());
  }

  StatSvcTestClient::~StatSvcTestClient()
  {
  }

  int StatSvcTestClient::Step()
  {
    int rc = ClientBase::Step();
    if (Result::NO_SUCH_STAGE != rc)
      return rc;

    switch(stage())
    {
    case StatStage::INITIAL:
      mmcwrapper_ = new TMMakingClientWrapper(this->getGateKeeper(), this);
      rc = mmcwrapper_->startReqMatchMakingManager();
      setStage(StatStage::REQ_MATCH_MAKING_MANAGER_STARTED);
      break;

    case StatStage::REQ_MATCH_MAKING_MANAGER_FINISHED:
      rc = mmcwrapper_->startReqMatchMaking();
      setStage(StatStage::REQ_MATCH_MAKING_STARTED);
      break;

    case StatStage::MATCH_MAKING_COMPLETED:
      rc = mmcwrapper_->PlayerReadyToPlay();
      setStage(StatStage::PLAYER_READY_TO_PLAY);
      break;

    case StatStage::REQUEST_STAT_RPC_NODE_START:
      {
        unicodeUsername_ = NStr::ToUnicode(getUserName());

        gstatCl = new StatisticService::GameStatClient( new StatisticService::ClientHttpDispatcher, 1 );
        NDebug::DebugVarReporter::AttachTo( getLocalEntityFactory() ); // регистрируемся, чтобы динамически создавать DebugVarReporter по запросу с той стороны
        rc = Result::SUCCESS;
  
        timeStatNodeReqStart_ = NHPTimer::GetScalarTime();
        setStage(StatStage::REQUEST_STAT_RPC_NODE_WAIT);
      }
      break;

    case StatStage::REQUEST_STAT_RPC_NODE_WAIT:
      if ( gstatCl->Ready() )
      {
        setStage(StatStage::QUERY_STAT_WRITER_IN_FINISHED);
        rc = Result::SUCCESS;
      }
      else
      {
        rc = Result::IN_PROGRESS;
      }
      break;

    case StatStage::QUERY_STAT_WRITER_IN_FINISHED:
      {
        if (!gstatCl)
        {
          LOG_C(0) << "NULL StatWriter remote ptr received";
          rc = Result::FAIL;
        }
        else
        {
          setStage(StatStage::LOG_GAME_SESSION_START);
          rc = Result::SUCCESS;
        }
      }
      break;

    case StatStage::LOG_GAME_SESSION_START:
      {
        // отправка информации о старте сессии
        /*
        StatisticService::RPC::SessionStartInfo ssinfo;
        ssinfo.sessionId = sessionId();
        ssinfo.login = unicodeUsername();
        ssinfo.faction = 1;
        ssinfo.preferFaction = 1;
        ssinfo.sessionType = 3;
        ssinfo.map = L"test_client_dummy_map_name";
        ssinfo.server = L"test_client_dummy_server_name";
        ssinfo.characterId = userid();
        */
        //gstatCl->LogSessionStart(ssinfo);

        setStage(StatStage::LOG_GAME_SESSION_EVENTS);
        rc = Result::SUCCESS;
      }
      break;

    case StatStage::LOG_GAME_SESSION_EVENTS:
      {
        for (unsigned int i=0; i < schedule_.size(); ++i)
        {
          unsigned int evtStepFreq = schedule_[i];

          if (!evtStepFreq)
            continue;

          while ((lastExecutedSteps_[i] + evtStepFreq) <= currentStep())
          {
            if (StatSvcTestClient::DamageEvt == i)
            {
              StatisticService::RPC::SessionDamageInfo sdi;
              sdi.physicalDamage = 20.0;
              rc = LogDamageEvent(sdi);
            }
            else
            if (StatSvcTestClient::DebugVarEvt == i)
            {
              rc = LogDebugVarEvent(currentStep(), wstring(L"FPS"), wstring(L"10.0"));
            }
            else
            {
              rc = LogSessionEvent(i);
              if (rc < 0)
              { //  todo log here
                break;
              }
            }

            lastExecutedSteps_[i] += evtStepFreq;
          }
        }

        if (sessionDurationInSteps_ && currentStep() > sessionDurationInSteps_)
        {
          setStage(StatStage::LOG_GAME_SESSION_FINISH);
          rc = Result::SUCCESS;
        }
      }
      break;

    case StatStage::LOG_GAME_SESSION_FINISH:
      {
        /*
        StatisticService::RPC::SessionResultInfo sri;
        sri.sessionId = sessionId();
        sri.login = unicodeUsername();
        sri.characterId = userid();
        */
        //gstatCl->LogSessionResults(sri);

        setStage(StatStage::STAT_SESSION_FINISHED);
        rc = Result::SUCCESS;
      }
      break;

    case StatStage::STAT_SESSION_FINISHED:
      {
        rc = Result::SCENARIO_FINISHED;
        mmcwrapper_ = 0;
      }
      break;

    default:
      break;
    }

    setLastResult(rc);
    return rc;
  }

  void StatSvcTestClient::OnStatisticsSessionNotify( int _statisticsSessionId )
  {
    statSessionId_ = _statisticsSessionId;
  }

  int StatSvcTestClient::LogSessionEvent(unsigned int evtid)
  {
    // для начала будем отсылать событие TalentUsed (EventType = 0)
    StatisticService::RPC::ClientCommonSessionEvent evt;
    evt.common = StatisticService::RPC::CommonSessionEventInfo( sessionId(), userid(), currentStep() );
    evt.info = StatisticService::RPC::SessionEventInfo();
    evt.info.intParam1 = 1778607205;
    gstatCl->Message( evt );
    //LOG_M(0).Trace("Log event (evt=%s c=%d u=%s)", SessionEventType::getEventName(evtid), userid(), getUserName());
    return Result::SUCCESS;
  }

  int StatSvcTestClient::LogDamageEvent(StatisticService::RPC::SessionDamageInfo & sdi)
  {
    StatisticService::RPC::ClientSessionDamageMessage msg;
    msg.common = StatisticService::RPC::CommonSessionEventInfo( sessionId(), userid(), 0 );
    msg.info = sdi;
    msg.info.dealt = true;

    gstatCl->Message( msg );
    //LOG_M(0).Trace("Log damage(c=%d u=%s)", userid(), getUserName());

    return Result::SUCCESS;
  }

  int StatSvcTestClient::LogDebugVarEvent(int step, const nstl::wstring& debugVarName, const nstl::wstring& debugVarValue)
  {
    //We have no DebugWriter here yet
    //StatisticService::RPC::CommonSessionEventInfo
    //gstatCl->LogDebugVar(sessionId(), step, userid(), debugVarName, debugVarValue);
    //LOG_M(0) << "Log debug var(var=" << debugVarName << " c=" << userid() << " u=" << getUserName() << ")";
    return Result::SUCCESS;    
  }

  char const * StatSvcTestClient::stageName(int st)
  {
    if (st >= StatStage::NUMBER_OF_STAGES)
      return 0;

    if (st <= StatStage::INITIAL)
      return ClientBase::stageName(st);

    return StatStage::stageNames[st - StatStage::INITIAL - 1];
  }


  void GenerateEventSchedule(EventFreqT const & eventFreq,
                             unsigned int sesstionDurationInMs,
                             unsigned int stepInMs,
                             EventsScheduleT& schedule)
  {
    schedule.resize(eventFreq.size());
    for(unsigned int i = 0; i < eventFreq.size(); ++i)
    {
      int evt = i;
      int freq = eventFreq[i];
      if (freq)
      {
        int howoften = ((sesstionDurationInMs/freq)/stepInMs - 0.5);
        if (!howoften)
          howoften = 1;

        schedule[evt] = howoften;
      }
    }
  }

  void StatSvcTestClient::OnMatchMakingManagerReceived(Result::Enum rc)
  {
    if (rc >= 0)
      setStage(StatStage::REQ_MATCH_MAKING_MANAGER_FINISHED);
    else
      setStage(StatStage::STAT_SESSION_FINISHED);
  }

  void StatSvcTestClient::OnRegisterMatchMaking(Result::Enum rc)
  {
    if (rc >= 0)
      setStage(StatStage::REQ_MATCH_MAKING_FINISHED);
    else
      setStage(StatStage::STAT_SESSION_FINISHED);
  }

  void StatSvcTestClient::OnMatchMakingCompleted(Result::Enum rc, MatchMaking::SessionId sid)
  {
    if (rc >= 0)
    {
      setStage(StatStage::MATCH_MAKING_COMPLETED);
      sessionId(sid);
    }
    else
      setStage(StatStage::STAT_SESSION_FINISHED);
  }

  void StatSvcTestClient::OnSessionStarted(Peered::IGameServer* gsrv)
  {
    setStage(StatStage::REQUEST_STAT_RPC_NODE_START);
  }

} // namespace GameTestClient2
