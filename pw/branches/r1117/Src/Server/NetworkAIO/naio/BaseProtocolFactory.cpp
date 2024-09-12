#include "naio/stdafx.h"
#include "naio/BaseProtocolFactory.h"
#include "naio/Ops.h"
#include "naio/ProtocolHandler.h"
#include "naio/ConnectionContext.h"

namespace naio
{
  BaseProtocolFactory::BaseProtocolFactory(const ACE_TCHAR *name,
                                            IProtocolHandlerFactory* phf,
                                            int              log_level,
                                            unsigned int     min_cache_size, 
                                            unsigned int     max_cache_size)
    :Parent(name, log_level, min_cache_size, max_cache_size),
    handlerFactory_(phf)
  {
  }

  BaseProtocolFactory::Parent::Protocol *
  BaseProtocolFactory::create_protocol(const void * act)
  {
    if (!handlerFactory_)
    {
      ACE_ERROR((LM_ERROR, ACE_TEXT("[naio] %s: handler factory is NULL"), __FUNCTION__));
      return 0;
    }

    //  here we come only when connection is established successfully
    naio::BaseProtocol* proto = static_cast<naio::BaseProtocol*>(Parent::create_protocol(act));
    proto->act(const_cast<void*>(act));

    //OpenConnectionOp* ocop = reinterpret_cast<OpenConnectionOp*>(const_cast<void*>(act));
    proto->ph_ = handlerFactory_->CreateProtocolHandler(0/*ocop->connctx()->userContext()*/);
    proto->set_message_block_factory(proto->ph_->getMessageBlockFactory());
    
    return proto;
  }

  int
  BaseProtocolFactory::validate_connection (
    bool             success,
    const ACE_Addr & /*remote*/,
    const ACE_Addr & /*local*/,
    const void *     act)
  {
    if (!handlerFactory_)
    {
      ACE_ERROR((LM_ERROR, ACE_TEXT("[naio] %s: handler factory is NULL"), __FUNCTION__));
      return -1;
    }

    //  connect, failed accept never come here
    if (!success)
    {
      //  connection failed
      Ptr<OpenConnectionOp> ocop(reinterpret_cast<OpenConnectionOp*>(const_cast<void*>(act)), false);
      IProtocolHandlerSP ph = handlerFactory_->CreateProtocolHandler(ocop->connctx()->userContext());
      ph->OnOpenConnection(false, true, ocop->connctx());
      handlerFactory_->DestroyProtocolHandler(ph);
    }

    return 0;
  }

  void BaseProtocolFactory::destroy_protocol(BaseProtocolFactory::Parent::Protocol * protocol)
  {
    handlerFactory_->DestroyProtocolHandler(static_cast<naio::BaseProtocol*>(protocol)->ph_);
    return Parent::destroy_protocol(protocol);
  }
}
