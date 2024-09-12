#pragma once
#include <naio/ProtocolHandler.h>
#include <naio/ConnectionContext.h>
#include "transport/TLTransportProtocol.h"
#include "transport/TLTypes.h"

namespace Transport
{
  class MessageFactory;
}

namespace TransportLayer
{
  namespace TL = TransportLayer;

  class ChannelFactory;

  class ProtocolHandlerFactory : public naio::IProtocolHandlerFactory
  {
  public:
    ProtocolHandlerFactory();
    ~ProtocolHandlerFactory();

  public:
    bool Init(Transport::MessageFactory* msgFactory,
              TL::ChannelFactory* chnlFactory,
              TL::MessageBlockFactorySP const & spmbf = TL::MessageBlockFactorySP());

    naio::IProtocolHandlerSP CreateProtocolHandler(void const * usercontext);
    void DestroyProtocolHandler(naio::IProtocolHandlerSP & ph);

  private:
    Transport::MessageFactory* msgFactory_;
    TL::ChannelFactory* chnlFactory_;
    bool packAddress_;
    TL::MessageBlockFactorySP spmbf_;
  };
}
