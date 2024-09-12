#include "transport/stdafx.h"
#include "transport/TLProtocolHandlerFactory.h"
#include "transport/TLProtocolHandler.h"
#include <ace/Log_Msg.h>
#include <mballocator/MessageBlockFactory.h>

namespace TransportLayer
{
  ProtocolHandlerFactory::ProtocolHandlerFactory()
    :msgFactory_(0),
    chnlFactory_(0)
  {
  }

  ProtocolHandlerFactory::~ProtocolHandlerFactory()
  {
  }

  bool ProtocolHandlerFactory::Init(Transport::MessageFactory* msgFactory,
                                    TL::ChannelFactory* chnlFactory,
                                    TL::MessageBlockFactorySP const & spmbf)
  {
    NI_PROFILE_BLOCK(__FUNCTION__);

    if (!msgFactory || !chnlFactory)
      return false;

    if (msgFactory_ || chnlFactory_)
      return false;

    msgFactory_ = msgFactory;
    chnlFactory_ = chnlFactory;

    spmbf_ = spmbf;
    return true;
  }

  naio::IProtocolHandlerSP ProtocolHandlerFactory::CreateProtocolHandler(void const * usercontext)
  {
    NI_PROFILE_BLOCK(__FUNCTION__);

    if (!msgFactory_)
    {
      ACE_ERROR((LM_ERROR, ACE_TEXT("%s(): FAILED. No message factory"), __FUNCTION__));
      return naio::IProtocolHandlerSP(0);
    }

    TL::MessageBlockFactorySP spmbf = spmbf_;
    if (spmbf.null())
      spmbf = TL::MessageBlockFactorySP(new TL::MessageBlockFactory("default", 10000));

    return naio::IProtocolHandlerSP(new TL::ProtocolHandler(msgFactory_, chnlFactory_, spmbf, packAddress_));
  }

  void ProtocolHandlerFactory::DestroyProtocolHandler(naio::IProtocolHandlerSP & ph)
  {
    NI_PROFILE_BLOCK(__FUNCTION__);

    ph.reset(0);
  }
}
