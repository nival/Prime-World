#ifndef NEWLOGINUSERCTX_H_INCLUDED
#define NEWLOGINUSERCTX_H_INCLUDED

#include "Network/RUDP/IRdp.h"
#include "Network/PacketDispatcher.h"
#include "NewLoginTypes.h"
#include "NewLoginConfig.h"
#include "System/NiTimer.h"
#include "ClientControl/ClientControlRemote.h"

#include <list>

namespace Network
{
  class PacketDispatcher;
  class IControlSizePacketHandler;
}


namespace rdp_transport
{
  class PacketWriter;
  class IFrontendAgent;
}


namespace clientCtl
{
  class IInterfaceAccessor;
}


namespace newLogin
{

class IClientAuth;
class ISvcLinkDict;
class UserSvcLink;

class UserCtx : public Network::IControlSizePacketHandler, ni_udp::IRdpConnectionCallback, public clientCtl::IUserPresenceCallback, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_3( UserCtx,  ni_udp::IRdpConnectionCallback, clientCtl::IUserPresenceCallback, BaseObjectMT );

public:
  struct EState {
    enum Enum {
      WaitingHello,
      WaitingClientCtrl,
      Active,
      Closed,
      KickingUser
    };
  };

  UserCtx( IConfigProvider * _config, IClientAuth * _auth, ni_udp::IRdpConnection * _conn, clientCtl::IInterfaceAccessor * _clientCtl, ISvcLinkDict * _svcLinkDict, timer::Time _now, const ni_udp::NetAddr & _remoteAddr, const Transport::TServiceId & _svcId, Transport::TUserSid _userSid );

  EState::Enum Poll( timer::Time _now );

protected:
  //ni_udp::IRdpConnectionCallback
  virtual void OnConnectionEstablished( ni_udp::IRdpConnection * _conn );
  virtual void OnConnectionClosed( ni_udp::IRdpConnection * _conn );
  virtual void OnConnectionFailed( ni_udp::IRdpConnection * _conn );
  virtual void OnDatagram( ni_udp::IRdpConnection * _conn, const void * _data, size_t _size, timer::Time _absRecvTime );

  //clientCtl::IUserPresenceCallback
  virtual void LetUserIn();
  virtual void DenyUser();
  virtual void KickUser();

private:
  typedef std::list<StrongMT<UserSvcLink> > SvcLinks;

  const ni_udp::NetAddr                   remoteAddr;
  const Transport::TServiceId             serviceId;
  const Transport::TUserSid               userSid;
  StrongMT<IConfigProvider>               config;
  StrongMT<IClientAuth>                   auth;
  WeakMT<ISvcLinkDict>                    svcLinkDict;
  StrongMT<clientCtl::IInterfaceAccessor> clientControl;
  StrongMT<ni_udp::IRdpConnection>        conn;
  StrongMT<Network::PacketDispatcher>     dispatcher;
  StrongMT<rdp_transport::PacketWriter>   writer;

  threading::Mutex                        mutex;

  EState::Enum                            state;

  timer::MemberPtrTimer<UserCtx>          timeout;

  LoginHello                              loginHello;
  LoginReply                              loginReply;
  Transport::TUserSid                     usid;

  SvcLinks                                svcLinks;
  timer::MemberPtrTimer<UserCtx>          emptyLinksTimeout;

  Transport::TClientId Uid() const { return loginReply.uid; }
  void Switch( EState::Enum _st );
  void PollSvcLinks( timer::Time _now );
  void OnHello( const LoginHello & _hello );
  void OnServiceRequest( const ServiceRequest & _req );
  void OnTimeout();
  void OnEmptyLinksTimeout();
  void SendFailReply( Login::ELoginResult::Enum _code );
  void Close();
};

} //namespace newLogin

#endif //NEWLOGINUSERCTX_H_INCLUDED
