#ifndef RDPLOGINCLIENT_H_INCLUDED
#define RDPLOGINCLIENT_H_INCLUDED

#include "Network/Address.h"
#include "Network/RUDP/IRdp.h"
#include "Server/NewLogin/NewLoginTypes.h"
#include "System/NiTimer.h"
#include <map>


namespace ni_udp
{
  class IRdp;
  class IRdpConnection;
}


namespace Network
{
  class PacketDispatcher;
}


namespace rdp_transport
{

namespace ELoginClientState
{
  enum Enum { Connecting, WaitingReply, Ready, Failed };
}


class PacketWriter;
class ClientChannel;
struct CommonCtx;

class LoginClient : public BaseObjectMT, public ni_udp::IRdpConnectionCallback
{
  NI_DECLARE_REFCOUNT_CLASS_2( LoginClient, BaseObjectMT, ni_udp::IRdpConnectionCallback );

public:
  LoginClient( ni_udp::IRdp * _rdp, const ni_udp::NetAddr & _loginSvcAddr, unsigned _loginSvcMux, const nstl::string & _login, const nstl::string & _password, const nstl::string & _sessionKey );

  void ParallelPoll( timer::Time _now );
  ELoginClientState::Enum State();
  newLogin::LoginReply LoginSvcReply() const;
  StrongMT<Transport::IChannel> NewSvcChannel( const CommonCtx & _ctx, const Transport::TServiceId & _svcId );
  const ni_udp::NetAddr & LoginSvcAddr() const { return loginSvcAddr; }

protected:
  virtual void OnConnectionEstablished( ni_udp::IRdpConnection * _conn );
  virtual void OnConnectionClosed( ni_udp::IRdpConnection * _conn );
  virtual void OnConnectionFailed( ni_udp::IRdpConnection * _conn );
  virtual void OnDatagram( ni_udp::IRdpConnection * _conn, const void * _data, size_t _size, timer::Time _absRecvTime );

private:
  typedef std::map<int, StrongMT<ClientChannel> > TChannelsByReqId;

  const string                login, password, sessionKey;
  const ni_udp::NetAddr       loginSvcAddr;

  ELoginClientState::Enum     state;
  newLogin::LoginReply        loginSvcReply;

  threading::Mutex            mutex;
  StrongMT<ni_udp::IRdp>      rdp;
  StrongMT<ni_udp::IRdpConnection> connection;
  StrongMT<Network::PacketDispatcher> dispatcher;
  StrongMT<PacketWriter>      writer;
  timer::MemberPtrTimer<LoginClient> timeout;
  int                         nextChanReqId;
  TChannelsByReqId            channelsByReqId;

  void Switch( ELoginClientState::Enum _st );
  void Fail( Login::ELoginResult::Enum _result );
  void OnHelloReply( const newLogin::LoginReply & _reply );
  void OnSvcReqReply( const newLogin::ServiceReqReply  & _reply );
  void OnTimeout();
};

} //namesapce rdp_transport

#endif //RDPLOGINCLIENT_H_INCLUDED
