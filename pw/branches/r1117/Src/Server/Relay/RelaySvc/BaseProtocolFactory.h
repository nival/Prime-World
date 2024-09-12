#pragma once
#include <IOTerabit/ProtocolFactory_T.h>
#include <mballocator/MessageBlockFactory.h>
#include "BaseProtocol.h"
#include "RelayServer2Cfg.h"

namespace Relay
{

template <class PROTOCOL>
class BaseProtocolFactory : public Terabit::ProtocolFactory_T<PROTOCOL>
{
  typedef Terabit::ProtocolFactory_T<PROTOCOL> Parent;

public:
  BaseProtocolFactory(const ACE_TCHAR *name,
    TL::MessageBlockFactorySP const & spmbf = TL::MessageBlockFactorySP(),
    int              log_level = 2,
    unsigned int     min_cache_size = 0, 
    unsigned int     max_cache_size = (unsigned int)-1);

public:
  typename Parent::Protocol* create_protocol(void const * act)
  {
    //  here we come only when connection is established successfully
    PROTOCOL* proto = static_cast<PROTOCOL*>(Parent::create_protocol(act));
    proto->act(act);

    TL::MessageBlockFactorySP mbf = mbf_;
    if (mbf.null())
    {
      mbf = TL::MessageBlockFactorySP(new TL::MessageBlockFactory("one_backend", RelayServer2Cfg::GetBackendMessageBlockHeapDumpFreq()));
      mbf->threshold(TL::MBType::NOTYPE_BLOCK, RelayServer2Cfg::GetBackendWriteBlockUseThreshold());
      mbf->threshold(TL::MBType::WRITE_BLOCK, RelayServer2Cfg::GetBackendWriteBlockUseThreshold());
      mbf->threshold(TL::MBType::READ_BLOCK, RelayServer2Cfg::GetBackendWriteBlockUseThreshold());
    }
    proto->set_message_block_factory(mbf);

    return proto;
  }

private:
  TL::MessageBlockFactorySP mbf_;
};

template <class PROTOCOL>
BaseProtocolFactory<PROTOCOL>::BaseProtocolFactory(const ACE_TCHAR *name,
  TL::MessageBlockFactorySP const & mbf,
  int              log_level,
  unsigned int     min_cache_size,
  unsigned int     max_cache_size)
  :Parent(name, log_level, min_cache_size, max_cache_size),
  mbf_(mbf)
{
}

}
