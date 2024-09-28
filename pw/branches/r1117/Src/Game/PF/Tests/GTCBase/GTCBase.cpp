#include "stdafx.h"

#include <Network/Initializer.h>
#include <Network/Transport.h>
#include <Network/TransportInitializer.h>
#include <Network/TransportMessages.h>
#include <Network/ClientTransportSystem3.h>
#include <Network/ClientTransportSystemIntf.h>
#include <Network/AddressTranslator.h>
#include <Network/FreePortsFinder.h>
#include <transport/TLTransportModule.h>
#include "Server/DebugVarUpdate/DebugVarReporter.h"
#include <Network/RdpClientTransport/RdpClientTransport.h>

#include "System/InlineProfiler.h"

#include "GTCBase.h"

unsigned loginTimeout = 60.0; // если за столько секунд не залогинились, ассертим

namespace GameTestClient2
{

  namespace BaseStage
  {
    char const * stageNames[] = 
    {
      "INITIAL",
      "LOGIN_STARTED",
      "LOGIN_FINISHED"
    };
  };

  ClientBase::ClientBase(int localid,
                Network::INetworkDriver * driver,
                TL::TransportModule * sptm, 
                unsigned int stepInMs,
                nstl::string const & loginaddr,
                nstl::string const & user, nstl::string const & pswd,
                nstl::string const & sessionKey,
                unsigned firstUdpPort, unsigned udpPortSearchRange )
    :localid_(localid),
    netdriver_(driver),
    sptm_(sptm),
    userId_(0),
    stage_(BaseStage::INITIAL),
    stageTimeout( 0 ),
    lastresult_(Result::INVALID),
    loginAddr_(loginaddr),
    user_(user),
    pswd_(pswd),
    factory_(0),
    bexit_(false),
    sessionKey_(sessionKey),
    stepStartTime_(0.0),
    stepInMs_(stepInMs),
    currentStep_(0)
  {
    Login::ClientVersion ver;

    ni_udp::NetAddr loginSvcAddr;
    unsigned loginSvcMux = 0;
    if ( rdp_transport::ParseAddress( loginSvcAddr, loginSvcMux, loginaddr.c_str() ) && loginSvcMux )
    {
      if ( !firstUdpPort )
        firstUdpPort = 38000;
      if ( !udpPortSearchRange )
        udpPortSearchRange = 10000;
      ni_udp::NetAddr rdpBindAddr( 0, firstUdpPort );
      StrongMT<rdp_transport::ClientTransport> clTr = new rdp_transport::ClientTransport( rdpBindAddr, udpPortSearchRange, Transport::GetGlobalMessageFactory() );
      transport_ = clTr;
    }
    else
      transport_ = new Transport::ClientTransportSystem3( netdriver_, Transport::GetGlobalMessageFactory(), ver, sptm_.Get());
  }

  ClientBase::~ClientBase()
  {
    if (factory_)
      delete factory_;
    factory_ = 0;
    gateKeeper_ = 0;
    transport_ = 0;
  }

  void ClientBase::OnNewNode( Transport::IChannel * channel, rpc::Node * node )
  {
  }

  void ClientBase::OnChannelClosed( Transport::IChannel * channel, rpc::Node * node )
  {
    MessageTrace( "OnChannelClosed: user id %d, node '%s'", userId_, node ? node->GetName() : "---" );
    bexit_ = true;
  }

  void ClientBase::OnCorruptData( Transport::IChannel * channel, rpc::Node * node )
  {
    MessageTrace( "OnCorruptData: user id %d, node '%s'", userId_, node ? node->GetName() : "---" );
    bexit_ = true;
  }

  int ClientBase::startLogin()
  {
    NI_PROFILE_FUNCTION;

    transport_->Login( loginAddr_, user_, pswd_, sessionKey_ );
    return Result::IN_PROGRESS;
  }

  int ClientBase::checkLogin()
  {
    NI_PROFILE_FUNCTION;
    if (stage_ != BaseStage::LOGIN_STARTED)
      return Result::FAIL;

    if ( !transport_ )
      return Result::IN_PROGRESS;

    int rc = Result::INVALID;
    Login::ELoginResult::Enum result = transport_->GetLoginResult();
    if (Login::ELoginResult::NoResult == result)
    {
      rc = Result::IN_PROGRESS;
    }
    else
    if (Login::ELoginResult::Success == result)
    {
      userId_ = transport_->GetUserId();
      rc = Result::SUCCESS;
    }
    else
    {
      rc = Result::FAIL;
    }

    return rc;
  }



  void ClientBase::setStage( int st, timer::Time _timeout )
  {
    stage_ = st;

    if ( _timeout )
      stageTimeout = timer::Now() + _timeout;
    else
      stageTimeout = 0;
  }



  void ClientBase::Poll()
  {
    NI_PROFILE_FUNCTION;

    if ( stageTimeout ) {
      timer::Time now = timer::Now();
      if ( now > stageTimeout ) {
        MessageTrace( "Stage %d timed out in client %d", stage_, localid_ );
        lastresult_ = Result::FAIL;
        stageTimeout = 0;
      }
    }

    if (gateKeeper_)
      gateKeeper_->Poll();
  }

  bool ClientBase::checkTransportStatus()
  {
    static int failedClientCount = 0;

    if( transport_ ) 
    {
      switch( transport_->GetStatus() )
      {
      case Transport::EStatus::CRITICAL_FAIL:
        // если транспорт признал окончательное поражение, можно и нам сдаваться
        WarningTrace( "TRANSPORT HAS FAILED, stopping test client (%d), total failed=%d", transport_->GetUserId(), ++failedClientCount );
        transport_ = 0;
        return false;
      
      case Transport::EStatus::FAIL:
        // если просто дисконнект, можно retry
        WarningTrace( "Transport failed, Logging out. userId=%d", transport_->GetUserId() );
        transport_ = 0;
        return false;
        break;

      default:
        break;
      }
    }

    return true;
  }

  int ClientBase::Step()
  {
    if (transport_)
      transport_->Step();

    if (!stepStartTime_)
      stepStartTime_ = GetTime();

    if (bexit_)
      return -1;

    if( !checkTransportStatus() )
      return -1;

    Poll();

    if (Result::INVALID == lastresult())  //  only on 1st step
      setLastResult(Result::IN_PROGRESS);

    //  calc step
    Timestamp currTime = GetTime();
    Timestamp timeDiff = currTime - stepStartTime_;
    Timestamp stepSize = double(stepInMs_)*0.001;

    unsigned int currStep = timeDiff/stepSize;
    NI_ASSERT(currStep >= currentStep_, "");
    if (currStep == currentStep_)
      return lastresult();

    currentStep_ = currStep;

    int rc = Result::INVALID;
    switch(stage_)
    {
    case BaseStage::INITIAL:
      if ( transport_ ) {
        rc = startLogin();
        stage_ = BaseStage::LOGIN_STARTED;
        lastresult_ = rc;
        timeLoginStarted_ = GetTime();
      }
      else
        WarningTrace( "Transport is not initialized! Cannot login!" );
      break;

    case BaseStage::LOGIN_STARTED:
      {
        rc = checkLogin();
        if (Result::IN_PROGRESS == rc)
        {
          if( NHPTimer::GetScalarTime() - timeLoginStarted_ > loginTimeout )
          {
            LOG_A(0) << "FAIL: login timeout for user " << user_;
            NI_ALWAYS_ASSERT( "login time exceeded" );
            stage_ = BaseStage::LOGIN_FINISHED;
            rc = Result::TIMEOUT;
            timeLoginFinished_ = NHPTimer::GetScalarTime();
          }
        }
        else
        {
          lastresult_ = rc;
          stage_ = BaseStage::LOGIN_FINISHED;
          rc = Result::SUCCESS;
          timeLoginFinished_ = GetTime();
          LOG_D(0).Trace("Login finished(rc=%d user=%s uid=%d duration=%f)", 
            lastresult_, user_.c_str(), userId_, double(timeLoginFinished_ - timeLoginStarted_));
        }
      }
      break;

    case BaseStage::LOGIN_FINISHED:
      rc = Result::FAIL;
      if ( transport_ )
      {
        gateKeeper_ = new rpc::GateKeeperClient(transport_, Transport::ENetInterface::Invalid, this );
        if (gateKeeper_)
        {
          factory_ = new rpc::LocalEntityFactory( gateKeeper_->GetGate() );
          if (factory_)
          {
            setStage( BaseStage::LOGIN_FINISHED_POST_STEP );
            rc = Result::SUCCESS;
          }
        }
      }
      break;

    default:
      rc = Result::NO_SUCH_STAGE;
      break;
    }

    setLastResult(rc);
    return rc;
  }

  char const * ClientBase::stageName(int st)
  {
    if (st < BaseStage::INITIAL || st >= BaseStage::LOGIN_FINISHED_POST_STEP)
      return 0;

    return BaseStage::stageNames[st];
  }

} // namespace GameTestClient2
