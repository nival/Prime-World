#include "stdafx.h"

#include "GameTestClientBase.h"
#include <Network/Initializer.h>
#include <Network/Transport.h>
#include <Network/TransportInitializer.h>
#include <Network/TransportMessages.h>
#include <Network/ClientTransportSystem3.h>
#include <Network/ClientTransportSystemIntf.h>
#include <Network/AddressTranslator.h>
#include <transport/TLTransportModule.h>
#include "Server/DebugVarUpdate/DebugVarReporter.h"
#include "Network/RdpClientTransport/RdpClientTransport.h"

#include <Core/Scheduler.h>
#include "System/InlineProfiler.h"

static unsigned g_maxAllowedLoginTime = 60.0; // если за столько секунд не залогинились, ассертим


namespace gtc
{
int TestClientBase::instancesCount = 0;

TestClientBase::TestClientBase( const TestClientBaseParams & _params ) :
params( _params ),
userId_(0),
stage_(Stage::NONE),
lastresult_(Result::NONE),
factory_(0),
bexit_(false),
operationStart( -1 ), operationTimeout( -1 )
{
  Login::ClientVersion ver;

  ni_udp::NetAddr loginSvcAddr;
  unsigned loginSvcMux = 0;

  if ( rdp_transport::ParseAddress( loginSvcAddr, loginSvcMux, params.loginaddr.c_str() ) && loginSvcMux )
  {
    ni_udp::NetAddr rdpBindAddr( 0, params.firstUdpPort );
    StrongMT<rdp_transport::ClientTransport> clTr = new rdp_transport::ClientTransport( rdpBindAddr, params.udpPortSearchRange, Transport::GetGlobalMessageFactory() );
    transport_ = clTr;
  }
  else
    transport_ = new Transport::ClientTransportSystem3( params.driver, Transport::GetGlobalMessageFactory(), ver, params.sptm.Get());

  ++instancesCount;
}



TestClientBase::~TestClientBase()
{
  DebugTrace( "Destructing test client %d...", userId_ );

  if ( transport_ )
    transport_->Logout();

  if (factory_)
    delete factory_;
  factory_ = 0;
  gateKeeper_ = 0;

  transport_ = 0;
  params.sptm = 0;

  --instancesCount;
}



void TestClientBase::OnNewNode( Transport::IChannel * channel, rpc::Node * node )
{
}



void TestClientBase::OnChannelClosed( Transport::IChannel * channel, rpc::Node * node )
{
  MessageTrace( "OnChannelClosed: user id %d, node '%s'", userId_, node ? node->GetName() : "---" );
  bexit_ = true;
}



void TestClientBase::OnCorruptData( Transport::IChannel * channel, rpc::Node * node )
{
  MessageTrace( "OnCorruptData: user id %d, node '%s'", userId_, node ? node->GetName() : "---" );
  bexit_ = true;
}



void TestClientBase::StartOperationTimer( timer::Time _to, bool restart )
{
  if ( !restart )
    NI_ASSERT( ( operationTimeout < 0 ) && ( operationStart < 0 ), "" );

  operationStart = timer::Now();
  operationTimeout = operationStart + _to;
}



void TestClientBase::StopOperationTimer()
{
  NI_ASSERT( ( operationStart >= 0 ) && ( operationTimeout >= 0 ), "" );
  operationStart = -1.0;
  operationTimeout = -1.0;
}



timer::Time TestClientBase::OperationDuration()
{
  return timer::Now() - operationStart;
}



StepResult TestClientBase::MainStep()
{
  if (transport_)
    transport_->Step();

  if ( gateKeeper_ )
    gateKeeper_->Poll();

  if ( !checkTransportStatus() )
    return StepResult( false, false );

  if ( bexit_ )
    return StepResult( false, false );

  if ( operationTimeout >= 0 )
  {
    timer::Time now = timer::Now();
    if ( now > operationTimeout )
    {
      WarningTrace( "Operation timed out. uid=%d, stage=%d, timeout=%d", userId_, stage_, now - operationStart );
      operationTimeout = -1.0;
      return StepResult( false, false );
    }
  }

  switch ( stage_ )
  {
    default:
      return StepResult( false, true );

    case Stage::NONE:
      return StepResult( true, startLogin() != Result::FAIL );

    case Stage::LOGIN_STARTED:
      return StepResult( true, Result::FAIL != checkLogin() );

    case Stage::LOGIN_FINISHED:
      return StepResult( false, true );
  }
}



int TestClientBase::startLogin()
{
  NI_PROFILE_FUNCTION;

  timeLoginStarted_ = timer::Now();

  transport_->Login( params.loginaddr, params.user, params.pswd, params.sessionKey );

  stage_ = Stage::LOGIN_STARTED;
  lastresult_ = Result::IN_PROGRESS;
  return lastresult_;
}



int TestClientBase::checkLogin()
{
  NI_PROFILE_FUNCTION;

  if (stage_ != Stage::LOGIN_STARTED)
    return Result::FAIL;

  if ( timer::Now() - timeLoginStarted_ > g_maxAllowedLoginTime ) {
    ErrorTrace( "FAIL: login timeout for user %s", params.user );
    NI_ALWAYS_ASSERT( "login time exceeded" );
    return Result::FAIL;
  }

  Login::ELoginResult::Enum result = transport_->GetLoginResult();
  if (Login::ELoginResult::NoResult == result)
    return Result::IN_PROGRESS;

  if (Login::ELoginResult::Success == result)
  {
    userId_ = transport_->GetUserId();
    stage_ = Stage::LOGIN_FINISHED;
    lastresult_ = Result::SUCCESS;

    gateKeeper_ = new rpc::GateKeeperClient(transport_, Transport::ENetInterface::Invalid, this );
    factory_ = new rpc::LocalEntityFactory( gateKeeper_->GetGate() );
  }
  else
  {
    lastresult_ = Result::FAIL;
  }

  return lastresult_;
}



bool TestClientBase::checkTransportStatus()
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
      transport_->Logout();
      stage_ = Stage::NONE;
      break;

    default:
      break;
    }
  }

  return true;
}

} // namespace gtc

NI_DEFINE_REFCOUNT( gtc::TestClientBase );
