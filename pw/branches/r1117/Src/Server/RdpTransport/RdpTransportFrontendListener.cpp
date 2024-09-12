#include "stdafx.h"
#include "RdpTransportFrontendListener.h"
#include "RdpTransportChannel.h"


namespace rdp_transport
{

static float userTimeout = 10.0f;
REGISTER_VAR( "rdp_frontend_user_auth_timeout", userTimeout, STORAGE_NONE );

FrontendListener::FrontendListener( const Transport::TServiceId & _svcid, const CommonCtx & _commonCtx, Transport::IFrontendTransportAuth * _auth ) :
Listener( _svcid, _commonCtx, userTimeout ),
auth( _auth )
{
}



StrongMT<Channel> FrontendListener::NewIncomingChannel( const ni_udp::NetAddr & _remoteAddr, const Transport::Address & _ta )
{
  return new FrontendChannel( _remoteAddr, auth, _ta, Transport::TLoginData(), CmnCtx() );
}

} //namespace rdp_transport
