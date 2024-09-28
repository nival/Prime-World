#ifndef RDPTRANSPORT_H_INCLUDED
#define RDPTRANSPORT_H_INCLUDED

#include "RdpTransportBase.h"
#include "RdpTransportChannel.h"
#include "RdpTransportListener.h"


namespace rdp_transport
{

class SocketFactory;

class BackendTransport : public PrimaryBase
{
  NI_DECLARE_REFCOUNT_CLASS_1( BackendTransport, PrimaryBase );

public:
  BackendTransport( Transport::MessageFactory * _msgFact, Transport::IAddressTranslator * _at, const ni_udp::NetAddr & _defaultSocketAddr, const char * _dbgRole );

protected:
  //PrimaryBase
  virtual void ImplSetupRdpOptions( ni_udp::RdpOptions & _opt );
  virtual StrongMT<Listener> ImplCreateChannelListener( Transport::TServiceId const & _interfaceId );
  virtual StrongMT<Channel> ImplCreateOutgoingChannel( const ni_udp::NetAddr & _rdpRemoteAddr, const Transport::Address & _transpAddress, const Transport::TLoginData & _loginData );
};



class BackendListener : public Listener
{
  NI_DECLARE_REFCOUNT_CLASS_1( BackendListener, Listener );

public:
  BackendListener( const Transport::TServiceId & _svcid, const CommonCtx & _commonCtx );

protected:
  //Listener
  virtual StrongMT<Channel> NewIncomingChannel( const ni_udp::NetAddr & _remoteAddr, const Transport::Address & _ta );
};



class IncomingBackendChannel : public Channel
{
  NI_DECLARE_REFCOUNT_CLASS_1( IncomingBackendChannel, Channel );

public:
  IncomingBackendChannel( const ni_udp::NetAddr & _remoteAddr, const Transport::Address & _transpAddress, const Transport::TLoginData & _loginData, const CommonCtx & _ctx );

protected:
  //IRdpConnectionCallback
  virtual void OnDatagram( ni_udp::IRdpConnection * _conn, const void * _data, size_t _size, timer::Time _absRecvTime );
};



class OutgoingBackendChannel : public Channel
{
  NI_DECLARE_REFCOUNT_CLASS_1( OutgoingBackendChannel, Channel );

public:
  OutgoingBackendChannel( const ni_udp::NetAddr & _remoteAddr, const Transport::Address & _transpAddress, const Transport::TLoginData & _loginData, const CommonCtx & _ctx );

protected:
  //IRdpConnectionCallback
  virtual void OnConnectionEstablished( ni_udp::IRdpConnection * _conn );
};

} //namespace rdp_transport

#endif RDPTRANSPORT_H_INCLUDED
