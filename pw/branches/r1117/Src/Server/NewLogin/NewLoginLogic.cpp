#include "stdafx.h"
#include "NewLoginLogic.h"
#include "Network/RUDP/SockSrvWinsockBlocking.h"
#include "RdpTransport/RdpSocketFactory.h"
#include "RdpTransport/RdpTransportUtils.h"
#include "NewLoginUserCtx.h"
#include "NewLoginSvcLink.h"
#include "System/RandomInterfaceImpl.h"
#include "System/NiTimer.h"
#include "System/InlineProfiler.h"
#include "NewLoginLog.h"


namespace newLogin
{

Logic::Logic( const ni_udp::NetAddr & _listenAddr, IConfigProvider * _config, IClientAuth * _auth, clientCtl::IInterfaceAccessor * _clientCtl, ISvcLinkDict * _svcLinks, timer::Time _now, const Transport::TServiceId & _svcId ) :
serviceId( _svcId ),
ok( true ),
config( _config ),
auth( _auth ),
now( _now ),
clientControl( _clientCtl ),
svcLinkDict( _svcLinks ),
nextUserSid( 1 )
{
  sockSrv = new ni_udp::BlockingUdpSocketServer( config->Cfg()->threadPriority, config->Cfg()->udpSockBufferSize );

  StrongMT<rdp_transport::SocketFactory> sockFact = new rdp_transport::SocketFactory( sockSrv, _listenAddr, 128, 0 );

  ni_udp::RdpOptions opts;
  opts.logEvents = config->Cfg()->rdpLogEvents;
  opts.logicThreadPriority = config->Cfg()->threadPriority;

  Strong<ni_rnd::Factory> rndFact = new ni_rnd::Factory;

  rdp = ni_udp::NewRdpInstance();
  if ( !rdp->Init( sockFact, opts, rndFact->Produce( (unsigned)timer::GetTicks() ), new timer::RealTimer ) )
  {
    ok = false;
    return;
  }

  listener = rdp->Listen( rdp_transport::DefaultMux, this );

  if ( !listener )
    ok = false;

  listenAddress = rdp_transport::FormatAddr( sockFact->Addr(), rdp_transport::DefaultMux );

  NEWLOGIN_LOG_MSG( "Ready and listening. addr=%s", listenAddress );
}



ni_udp::IRdpConnectionCallback * Logic::OnConnectionEstablished( ni_udp::IRdpConnection * _conn, const ni_udp::NetAddr & _remoteAddr )
{
  NI_PROFILE_FUNCTION;

  NEWLOGIN_LOG_MSG( "New login context. ip=%s", _remoteAddr );

  StrongMT<ISvcLinkDict> svcLinks = svcLinkDict.Lock();
  NI_VERIFY( svcLinks, "", return 0 );

  threading::MutexLock lock( mutex );

  StrongMT<UserCtx> ctx = new UserCtx( config, auth, _conn, clientControl, svcLinks, now, _remoteAddr, serviceId, nextUserSid++ );
  newUsers.push_back( ctx );

  return (ni_udp::IRdpConnectionCallback *)ctx;
}



void Logic::Poll( timer::Time _now, size_t & _usersNumber )
{
  NI_PROFILE_FUNCTION;

  threading::MutexLock lock( mutex );

  now = _now;

  for ( TUsers::iterator it = activeUsers.begin(); it != activeUsers.end(); )
  {
    UserCtx * ctx = *it;

    UserCtx::EState::Enum state = ctx->Poll( now );
    if ( state == UserCtx::EState::Closed )
      it = activeUsers.erase( it );
    else
      ++it;
  }

  for ( TUsers::iterator it = newUsers.begin(); it != newUsers.end(); )
  {
    UserCtx * ctx = *it;

    UserCtx::EState::Enum state = ctx->Poll( now );
    if ( state == UserCtx::EState::Closed )
      it = newUsers.erase( it );
    else if ( state == UserCtx::EState::Active )
    {
      activeUsers.push_back( *it );
      it = newUsers.erase( it );
    }
    else
      ++it;
  }

  _usersNumber = newUsers.size() + activeUsers.size();
}

} //namespace newLogin
