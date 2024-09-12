#include "stdafx.h"
#include "RdpFrontendTransport.h"
#include "RdpTransportChannel.h"
#include "RdpTransportFrontendListener.h"
#include "System/SafeTextFormatStl.h"


static unsigned s_rdpLogEevents = ni_udp::RdpOptions::LogMajorEvents | ni_udp::RdpOptions::LogWarnings | ni_udp::RdpOptions::LogErrors;
REGISTER_VAR( "rdp_frontend_log_events", s_rdpLogEevents, STORAGE_NONE );


namespace rdp_transport
{

PrimaryFrontend::PrimaryFrontend( Transport::MessageFactory * _msgFact, Transport::IAddressTranslator * _at, const ni_udp::NetAddr & _defaultSocketAddr ) :
PrimaryBase( _msgFact, _at, _defaultSocketAddr, "frontend" )
{
}



void PrimaryFrontend::ImplSetupRdpOptions( ni_udp::RdpOptions & _opt )
{
  PrimaryBase::ImplSetupRdpOptions( _opt );
  _opt.logEvents = s_rdpLogEevents;
}



StrongMT<Listener> PrimaryFrontend::ImplCreateChannelListener( Transport::TServiceId const & _interfaceId )
{
  StrongMT<Transport::IFrontendTransportAuth> auth;

  {
    threading::MutexLock lock( mutex );
    AuthList::iterator it = authList.find( _interfaceId );
    if ( it == authList.end() )
    {
      ErrorTrace( "Frontend client auth not found. svcid=%s", _interfaceId.c_str() );
      return 0;
    }
    auth = it->second;
  }

  return new FrontendListener( _interfaceId, CmmnCtx(), auth );
}



StrongMT<Channel> PrimaryFrontend::ImplCreateOutgoingChannel( const ni_udp::NetAddr & _rdpRemoteAddr, const Transport::Address & _transpAddress, const Transport::TLoginData & _loginData )
{
  NI_ALWAYS_ASSERT( "Frontend transport cannot establish outgoing connections" );
  return 0;
}



void PrimaryFrontend::AddFrontendAuth( const Transport::TServiceId & interfaceId, Transport::IFrontendTransportAuth * _auth )
{
  threading::MutexLock lock( mutex );

  authList[interfaceId] = _auth;
}

} //namespace rdp_transport
