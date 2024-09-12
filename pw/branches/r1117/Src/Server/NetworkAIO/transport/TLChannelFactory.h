#pragma once
#include "transport/TLTypes.h"
#include <Network/TransportLoginData.h>
#include <Network/TransportChannelType.h>

namespace Transport
{
  struct Address;
  class MessageFactory;
}

namespace TransportLayer
{
  namespace TL = TransportLayer;

  class ChannelFactory
  {
  public:
    ChannelFactory();
    ~ChannelFactory();

  public:
    IChannelInternalSP CreateChannel(Transport::EChannelType::Enum _channeltype, bool isactive, TL::ConnectionSP const & spconn, Transport::Address const & addr, 
      Transport::TLoginData const & logindata, Transport::MessageFactory* mf, unsigned int openChannelTimeout, unsigned int pingPeriod);
    void DestroyChannel(IChannelInternalSP const & spch);
  };
}
