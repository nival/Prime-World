#ifndef RDPTRANSPORTFRONTENDCHANNEL_H_INCLUDED
#define RDPTRANSPORTFRONTENDCHANNEL_H_INCLUDED

#include "RdpTransportChannel.h"
#include "Server/NewLogin/NewLoginTypes.h"


namespace Network
{
  class PacketDispatcher;
}


namespace rdp_transport
{

class PacketWriter;


class FrontendChannel : public Channel, public Transport::IFrontendTransportKickCallback
{
  NI_DECLARE_REFCOUNT_CLASS_2( FrontendChannel, Transport::IFrontendTransportKickCallback, Channel );

public:
  FrontendChannel( const ni_udp::NetAddr & _remoteAddr, Transport::IFrontendTransportAuth * _auth, const Transport::Address & _transpAddress, const Transport::TLoginData & _loginData, const CommonCtx & _ctx );

protected:
  //IRdpConnectionCallback
  virtual void OnDatagram( ni_udp::IRdpConnection * _conn, const void * _data, size_t _size, timer::Time _absRecvTime );

  //Transport::IFrontendTransportKickCallback
  virtual void KickUser( Transport::TClientId _uid );

  virtual void OnRdpConnectionChange();

private:
  threading::Mutex                            authMutex;
  StrongMT<Transport::IFrontendTransportAuth> auth;

  StrongMT<Network::PacketDispatcher>         dispatcher;
  StrongMT<rdp_transport::PacketWriter>       writer;

  void OnHello( const newLogin::FrontendHello & _hello );
};

} //namesapce rdp_transport

#endif //RDPTRANSPORTFRONTENDCHANNEL_H_INCLUDED
