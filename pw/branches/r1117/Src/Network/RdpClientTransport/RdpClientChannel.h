#ifndef RDPCLIENTCHANNEL_H_INCLUDED
#define RDPCLIENTCHANNEL_H_INCLUDED

#include "Server/RdpTransport/RdpTransportChannel.h"
#include "Server/NewLogin/NewLoginTypes.h"
#include "System/NiTimer.h"


namespace Network
{
  class PacketDispatcher;
}


namespace rdp_transport
{

namespace EClientChanState
{
  enum Enum
  {
    WaitingSvcAddr,
    ConnectingToSvc,
    WaitingSvcAck,
    Active,
    Closed
  };
}


class PacketWriter;

class ClientChannel : public Channel
{
  NI_DECLARE_REFCOUNT_CLASS_1( ClientChannel, Channel );

public:
  ClientChannel( ni_udp::IRdp * _rdp, const CommonCtx & _ctx, const Transport::Address & _ta, int _requestId );

  int RequestId() const { return requestId; }

  void OnSvcRequestReply( const newLogin::ServiceReqReply & _reply );
  bool Poll( timer::Time _now );

public:
  //IChannel
  virtual Network::ConnectionState::Enum GetStatus() const;
  virtual void SendRaw( const byte * _data, int _size );

protected:
  //IRdpConnectionCallback
  virtual void OnConnectionEstablished( ni_udp::IRdpConnection * _conn );
  virtual void OnConnectionClosed( ni_udp::IRdpConnection * _conn );
  virtual void OnConnectionFailed( ni_udp::IRdpConnection * _conn );
  virtual void OnDatagram( ni_udp::IRdpConnection * _conn, const void * _data, size_t _size, timer::Time _absRecvTime );

private:
  const int                                   requestId;
  StrongMT<ni_udp::IRdp>                      rdp;
  threading::Mutex                            mutex;
  EClientChanState::Enum                      state;
  timer::MemberPtrTimer<ClientChannel>        timeout;
  StrongMT<Network::PacketDispatcher>         dispatcher;
  StrongMT<rdp_transport::PacketWriter>       writer;
  newLogin::ServiceReqReply                   svcReqReply;

  void Switch( EClientChanState::Enum _st );
  void OnTimeout();
  void OnHelloReply( const newLogin::FrontendHelloReply & _reply );
  void CloseClientChannel();
};

} //namesapce rdp_transport

#endif //RDPCLIENTCHANNEL_H_INCLUDED
