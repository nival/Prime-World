#pragma once
#include <naio/ProtocolHandler.h>

namespace NetworkLayer
{
  namespace NL = NetworkLayer;

  class ProtocolHandlerFactory : public naio::IProtocolHandlerFactory
  {
  public:
    ProtocolHandlerFactory();
    ~ProtocolHandlerFactory();

  public:
    naio::IProtocolHandlerSP CreateProtocolHandler(void const * usercontext);
    void DestroyProtocolHandler(naio::IProtocolHandlerSP& ph);
  };
}
