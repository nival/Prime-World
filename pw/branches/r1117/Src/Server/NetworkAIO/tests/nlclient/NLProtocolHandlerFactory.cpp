#include "stdafx.h"
#include "NLProtocolHandlerFactory.h"
#include "NLProtocolHandler.h"

namespace NetworkLayer
{
  ProtocolHandlerFactory::ProtocolHandlerFactory()
  {
  }

  ProtocolHandlerFactory::~ProtocolHandlerFactory()
  {
  }

  naio::IProtocolHandlerSP ProtocolHandlerFactory::CreateProtocolHandler(void const * usercontext)
  {
    return naio::IProtocolHandlerSP(new NL::ProtocolHandler());
  }

  void ProtocolHandlerFactory::DestroyProtocolHandler(naio::IProtocolHandlerSP& ph)
  {
    ph.reset(0);
  }
}
