#ifndef NEWLOGINLOGIC_H_INCLUDED
#define NEWLOGINLOGIC_H_INCLUDED

#include "NewLoginTypes.h"
#include "Network/RUDP/IRdp.h"
#include "NewLoginConfig.h"
#include <list>


namespace ni_udp
{
  class IRdp;
  class ISocketServer;
  class IRdpListenContext;
  struct NetAddr;
}


namespace clientCtl
{
  class IInterfaceAccessor;
}


namespace newLogin
{

class UserCtx;
class SvcLinkDict;
class IClientAuth;
class ISvcLinkDict;


class Logic : public ni_udp::IRdpListenContextCallback,  public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( Logic, ni_udp::IRdpListenContextCallback, BaseObjectMT );

public:
  Logic( const ni_udp::NetAddr & _listenAddr, IConfigProvider * _config, IClientAuth * _auth, clientCtl::IInterfaceAccessor * _clientCtl, ISvcLinkDict * _svcLinks, timer::Time _now, const Transport::TServiceId & _svcId );

  const string & ListenAddress() const { return listenAddress; }

  void Poll( timer::Time _now, size_t & _usersNumber );

  bool Ok() const { return ok; }

protected:
  virtual ni_udp::IRdpConnectionCallback * OnConnectionEstablished( ni_udp::IRdpConnection * _conn, const ni_udp::NetAddr & _remoteAddr );

private:
  typedef std::list<StrongMT<UserCtx> >  TUsers;

  const Transport::TServiceId       serviceId;

  bool                              ok;
  StrongMT<IConfigProvider>         config;
  StrongMT<IClientAuth>             auth;
  string                            listenAddress;
  timer::Time                       now;

  StrongMT<ni_udp::ISocketServer>   sockSrv;
  StrongMT<ni_udp::IRdp>            rdp;
  StrongMT<ni_udp::IRdpListenContext> listener;
  StrongMT<clientCtl::IInterfaceAccessor> clientControl;
  WeakMT<ISvcLinkDict>              svcLinkDict;

  Transport::TUserSid               nextUserSid;
  TUsers                            newUsers;
  TUsers                            activeUsers;

  threading::Mutex                  mutex;
};

} //namespace newLogin

#endif //NEWLOGINLOGIC_H_INCLUDED
