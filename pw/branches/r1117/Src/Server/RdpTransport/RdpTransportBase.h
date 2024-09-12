#ifndef RDPTRANSPORTSYSTEM_H_INCLUDED
#define RDPTRANSPORTSYSTEM_H_INCLUDED

#include "Network/TransportBase.h"
#include "System/Schedule.h"
#include "RdpTransportUtils.h"
#include "Network/RUDP/UdpAddr.h"
#include <string>
#include <map>


namespace ni_udp
{
  class IRdp;
  class ISocketServer;
  struct RdpOptions;
  struct NetAddr;
}

namespace rdp_transport
{

class SocketFactory;
class Listener;
class Channel;

class PrimaryBase : public Transport::TransportSystemBase
{
  NI_DECLARE_REFCOUNT_CLASS_1( PrimaryBase, Transport::TransportSystemBase );

public:
  PrimaryBase( Transport::MessageFactory * _msgFact, Transport::IAddressTranslator * _at, const ni_udp::NetAddr & _defaultSocketAddr, const char * _dbgRole );
  ~PrimaryBase();

  //ITransportSystem
  virtual Network::NetAddress AllocateServerAddress( const Network::NetAddress & _ip );

  virtual StrongMT<Transport::IChannel> OpenChannelDirect( const Transport::Address & address, const Transport::TLoginData & loginData, const Network::NetAddress & netAddress, unsigned int pingperiod, unsigned int to );
  virtual StrongMT<Transport::IChannelListener> CreateChannelListenerDirect( Transport::TServiceId const & interfaceId, const string & listenAddress );

  virtual StrongMT<Transport::IMulticastChannel> OpenMulticastChannel( Transport::Address const & _taddr, unsigned int _pingperiod, unsigned int _opentimeout );
  virtual StrongMT<Transport::IMulticastChannel> OpenMulticastChannelDirect( Transport::Address const & _taddr, Network::NetAddress const & _netaddr, unsigned int _pingperiod, unsigned int _opentimeout );
  virtual StrongMT<Transport::IChannelListener> GetDefaultChannelListener() const;

protected:
  //overridable
  virtual void ImplSetupRdpOptions( ni_udp::RdpOptions & _opt );
  virtual StrongMT<Listener> ImplCreateChannelListener( Transport::TServiceId const & _interfaceId );
  virtual StrongMT<Channel> ImplCreateOutgoingChannel( const ni_udp::NetAddr & _rdpRemoteAddr, const Transport::Address & _transpAddress, const Transport::TLoginData & _loginData );

protected:
  struct Slot : public BaseObjectMT
  {
    NI_DECLARE_REFCOUNT_CLASS_1(Slot, BaseObjectMT);
  public:
    ni_udp::NetAddr                 addr;
    StrongMT<ni_udp::ISocketServer> sockSrv;
    StrongMT<ni_udp::IRdp>          rdp;
    unsigned                        nextSrviceMux;

    Slot( unsigned _nextSrviceMux ) :
    nextSrviceMux( _nextSrviceMux )
    {}
  };

  const CommonCtx & CmmnCtx() const { return commonCtx; }

private:
  typedef std::map<ni_udp::NetAddr, StrongMT<Slot>> Slots;

  Transport::MessageFactory *   msgFactory;
  const ni_udp::NetAddr         defaultSocketAddr;
  const std::string             dbgRole;
  CommonCtx                     commonCtx;
  Slots                         slots;
  StrongMT<Slot>                defaultSlot;
  threading::Mutex              mutex;

  StrongMT<Slot> NewSlot( const ni_udp::NetAddr & _sockAddr, bool _searchPort );
};

} //namespace rdp_transport

#endif RDPTRANSPORTSYSTEM_H_INCLUDED
