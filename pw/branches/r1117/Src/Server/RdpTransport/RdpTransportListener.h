#ifndef RDPTRANSPORTLISTENER_H_INCLUDED
#define RDPTRANSPORTLISTENER_H_INCLUDED

#include "Network/Transport.h"
#include "Network/RUDP/IRdp.h"
#include "RdpTransportUtils.h"
#include "RdpTransportChannel.h"
#include <set>


namespace rdp_transport
{

class Listener : public Transport::IChannelListener, public ni_udp::IRdpListenContextCallback, public IDelayedAcceptCallback, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_4( Listener, Transport::IChannelListener, ni_udp::IRdpListenContextCallback, IDelayedAcceptCallback, BaseObjectMT );

public:
  Listener( const Transport::TServiceId & _svcid, const CommonCtx & _commonCtx, timer::Time _delayedAcceptTimeout = -1.0 );
  ~Listener();

  bool Init( ni_udp::IRdpListenContext * _listenCtx );

protected:
  //IChannelListener
  virtual const Transport::TServiceId & GetServiceId() const { return serviceId; }
  virtual void GetNewConnections( Transport::TChannels * pConnections );

  //IRdpListenContextCallback
  virtual ni_udp::IRdpConnectionCallback * OnConnectionEstablished( ni_udp::IRdpConnection * _conn, const ni_udp::NetAddr & _remoteAddr );

  //IDelayedAcceptCallback
  virtual void DelayedChannelAcceptFailed( Channel * _chan );
  virtual void AcceptDelayedChannel( Channel * _chan );

  //overridable
  virtual StrongMT<Channel> NewIncomingChannel( const ni_udp::NetAddr & _remoteAddr, const Transport::Address & _ta );

  void PushNewChannel( Transport::IChannel * _chan );

  const CommonCtx & CmnCtx() const { return commonCtx; }

private:
  typedef std::set<StrongMT<Channel> > DelayedAcceptChannels;

  const timer::Time                   delayedAcceptTimeout;
  Transport::TServiceId               serviceId;
  CommonCtx                           commonCtx;
  StrongMT<ni_udp::IRdpListenContext> listenCtx;

  threading::Mutex                    mutex;
  Transport::TChannels                newChannels;
  DelayedAcceptChannels               delayedAcceptChannels;
};

} //namespace rdp_transport

#endif RDPTRANSPORTLISTENER_H_INCLUDED
