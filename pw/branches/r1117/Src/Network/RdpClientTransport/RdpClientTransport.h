#ifndef RDPCLIENTTRANSPORT_H_INCLUDED
#define RDPCLIENTTRANSPORT_H_INCLUDED

#include "Network/ClientTransportSystemIntf.h"
#include "Network/RUDP/UdpAddr.h"
#include "Server/RdpTransport/RdpTransportUtils.h"
#include "Server/NewLogin/NewLoginTypes.h"
#include "System/JobThread.h"


namespace ni_udp
{
  class ISocketServer;
  class IRdp;
}

namespace rdp_transport
{

class LoginClient;


class ClientTransport : public Transport::IClientTransportSystem, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( ClientTransport, Transport::IClientTransportSystem, BaseObjectMT );

public:
  ClientTransport( const ni_udp::NetAddr & _bindAddr, unsigned _portSearchRange, Transport::MessageFactory * _msgFactory );

  virtual int GetUserId() const;

  virtual StrongMT<Transport::IChannel> OpenChannel( Transport::TServiceId interfaceId, unsigned int pingperiod, unsigned int to );
  virtual void GetNewAcceptedChannels(vector<StrongMT<Transport::IChannel>> & _chnls);

  virtual void Login( const Network::NetAddress & _loginServerAddress, const nstl::string & _login, const nstl::string & _password, const nstl::string & _sessionKey, Login::LoginType::Enum _loginType );
  virtual void Logout();
  virtual Login::ELoginResult::Enum GetLoginResult() const;
  virtual Transport::EStatus::Enum GetStatus();
  virtual Transport::TServiceId GetSessionPath() const;
  virtual Network::NetAddress GetRelayAddress() const;
  virtual Network::NetAddress GetSecondaryRelayAddress() const;
  virtual void Step() {}

private:
  class Worker;
  friend Worker;

  ni_udp::NetAddr                   bindAddr;
  unsigned                          portSearchRange;
  threading::Mutex                  mutex;
  threading::Mutex                  initShutdownMutex;
  CommonCtx                         commonCtx;
  StrongMT<ni_udp::ISocketServer>   sockServer;
  StrongMT<ni_udp::IRdp>            rdp;
  StrongMT<LoginClient>             loginClient;
  StrongMT<threading::JobThread>    thread;

  void Cleanup();
  void ParallelPoll();
};

} //namesapce rdp_transport

#endif //RDPCLIENTTRANSPORT_H_INCLUDED
