#pragma once
#include <Network/Transport.h>
#include <naio/Driver.h>
#include <Network/Message.h>
#include <ace/Atomic_Op.h>
#include "transport/TLProtocolHandlerFactory.h"
#include "transport/TLConnectionManager.h"
#include "transport/TLChannelFactory.h"
#include "Network/TransportBase.h"
#include "Network/FreePortsFinder.h"


namespace TransportLayer
{
  namespace TL = TransportLayer;

  class Cfg;

  class TransportModule : public Transport::TransportSystemBase
  {
    NI_DECLARE_REFCOUNT_CLASS_1( TransportModule, Transport::TransportSystemBase )

  public:
    TransportModule();
    ~TransportModule();

  public:
    bool Init( const TL::Cfg & cfg, const naio::DriverSP & spdrv = naio::DriverSP(0) );
    void Fini();

    virtual Network::NetAddress AllocateServerAddress( const Network::NetAddress & _ip );

    virtual StrongMT<Transport::IChannel> OpenChannelDirect( const Transport::Address& address, const Transport::TLoginData& loginData, 
      const Network::NetAddress& netAddress,
      unsigned int pingperiod = Transport::Defaults::GetPingPeriod(),
      unsigned int to = Transport::Defaults::GetOpenChannelTimeout() );

    virtual StrongMT<Transport::IChannelListener> CreateChannelListenerDirect( Transport::TServiceId const & interfaceId, const nstl::string & listenAddress );

    virtual StrongMT<Transport::IMulticastChannel> OpenMulticastChannel(Transport::Address const & _taddr,
      unsigned int _pingperiod = Transport::Defaults::GetPingPeriod(),
      unsigned int _opentimeout = Transport::Defaults::GetOpenChannelTimeout());

    virtual StrongMT<Transport::IMulticastChannel> OpenMulticastChannelDirect(Transport::Address const & _taddr, Network::NetAddress const & _netaddr,
      unsigned int _pingperiod = Transport::Defaults::GetPingPeriod(),
      unsigned int _opentimeout = Transport::Defaults::GetOpenChannelTimeout());

    virtual StrongMT<Transport::IChannelListener> GetDefaultChannelListener() const;

  protected:
    bool ResolveAddress(Transport::TServiceId const & serviceid, ACE_INET_Addr & netaddr);

  private:
    StrongMT<Network::IFreePortsFinder> freePortsFinder;
    Transport::MessageFactory msgFactory_;
    TL::ProtocolHandlerFactory phFactory_;
    naio::DriverSP spdrv_;
    bool bFiniNaio_;
    TL::ConnectionManagerSP spConnMngr_;
    TL::ChannelFactory channelFactory_;
    ACE_Atomic_Op<ACE_Thread_Mutex, long> initialized_;
  };

  StrongMT<TL::TransportModule> CreateTransportSystem(TL::Cfg const & cfg);
}

namespace TL = TransportLayer;
