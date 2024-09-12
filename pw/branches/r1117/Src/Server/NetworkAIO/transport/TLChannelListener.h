#pragma once
#include <Network/Transport.h>
#include <naio/AcceptorHandle.h>
#include "transport/TLChannelListenerInt.h"

namespace TransportLayer
{
  namespace TL = TransportLayer;

  class ChannelListener : public BaseObjectMT, public Transport::IChannelListener, public TL::ChannelListenerInternal
  {
    NI_DECLARE_REFCOUNT_CLASS_3( ChannelListener, BaseObjectMT, Transport::IChannelListener, ChannelListenerInternal )

  public:

    ChannelListener(Transport::TServiceId const & serviceId, ACE_INET_Addr const & listenAddr);
    ~ChannelListener();

  public:

    void acceptorHandle(naio::AcceptorHandle const & ah);
    naio::AcceptorHandle const & acceptorHandle() const;
    void close();

  public:
    //  ChannelListenerInternal
    void onOpenChannel(TL::IChannelInternalSP const & spchnl);

  public:
    //  IChannelListener implementation
    Transport::TServiceId const & GetServiceId() const;
    void GetNewConnections(vector<StrongMT<Transport::IChannel> >* pConnections);

  private:
    Transport::TServiceId serviceId_;
    ACE_INET_Addr listenAddr_;
    naio::AcceptorHandle acceptorHandle_;

    typedef vector<StrongMT<Transport::IChannel> > TChannels;
    TChannels newConnections;
    threading::Mutex newConnectionsMutex;
  };

  inline
  void ChannelListener::acceptorHandle(naio::AcceptorHandle const & ah)
  {
    acceptorHandle_ = ah;
  }

  inline
  naio::AcceptorHandle const & ChannelListener::acceptorHandle() const
  {
    return acceptorHandle_;
  }
}
