#pragma once
#include <IOTerabit/ProtocolFactory_T.h>
#include "naio/BaseProtocol.h"

namespace naio
{
  class IProtocolHandlerFactory;

  class BaseProtocolFactory : public Terabit::ProtocolFactory_T<naio::BaseProtocol>
  {
    typedef Terabit::ProtocolFactory_T<naio::BaseProtocol> Parent;

  public:
    BaseProtocolFactory(const ACE_TCHAR *name,
      IProtocolHandlerFactory* phf,
      int              log_level = 2,
      unsigned int     min_cache_size = 0, 
      unsigned int     max_cache_size = static_cast< unsigned int >(-1) );

  public:

    IProtocolHandlerFactory*  setProtocolHandlerFactory(IProtocolHandlerFactory* phf);

    Parent::Protocol* create_protocol(void const * act);
    virtual void destroy_protocol (Parent::Protocol * protocol);
    virtual int  validate_connection (bool  success,
      const ACE_Addr &remote, 
      const ACE_Addr &local,
      const void *act);

  private:
    IProtocolHandlerFactory* handlerFactory_;
  };

  inline
  IProtocolHandlerFactory* BaseProtocolFactory::setProtocolHandlerFactory(IProtocolHandlerFactory* phf)
  {
    IProtocolHandlerFactory* phfprev = handlerFactory_;
    handlerFactory_ = phf;
    return phfprev;
  }
}
