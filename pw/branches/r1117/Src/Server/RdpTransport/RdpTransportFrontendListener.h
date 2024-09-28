#ifndef RDPTRANSPORTFRONTENDLISTENER_H_INCLUDED
#define RDPTRANSPORTFRONTENDLISTENER_H_INCLUDED

#include "RdpTransportListener.h"
#include "RdpTransportFrontendChannel.h"


namespace rdp_transport
{

class FrontendListener : public Listener
{
  NI_DECLARE_REFCOUNT_CLASS_1( FrontendListener, Listener );

public:
  FrontendListener( const Transport::TServiceId & _svcid, const CommonCtx & _commonCtx, Transport::IFrontendTransportAuth * _auth );

protected:
  //Listener
  virtual StrongMT<Channel> NewIncomingChannel( const ni_udp::NetAddr & _remoteAddr, const Transport::Address & _ta );

private:
  StrongMT<Transport::IFrontendTransportAuth> auth;
};

} //namespace rdp_transport

#endif RDPTRANSPORTFRONTENDLISTENER_H_INCLUDED
