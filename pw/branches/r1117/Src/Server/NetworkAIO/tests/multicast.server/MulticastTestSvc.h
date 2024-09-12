#pragma once

#include "Network/GateKeeperSvc.h"
#include "MulticastTestImpl.h"


namespace MulticastTest
{
  class Service : public Network::GateKeeperService
  {
    NI_DECLARE_REFCOUNT_CLASS_1( Service, Network::GateKeeperService );

  public:
    Service( Transport::ITransportSystem * transport, const Transport::TServiceId& serviceId);
    ~Service();

  protected:
    virtual void OnNewNode( StrongMT<Transport::IChannel> const & channel,  StrongMT<rpc::Node> const & node ) {}
    virtual void OnChannelClosed( StrongMT<Transport::IChannel> const & channel,  StrongMT<rpc::Node> const & node ) {}
    virtual void OnCorruptData( StrongMT<Transport::IChannel> const & channel, StrongMT<rpc::Node> const & node ) {}

  private:

    void Step();

  private:
    StrongMT<MulticastTestImpl>  impl;
  };
}
