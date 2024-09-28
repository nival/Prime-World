#pragma once
#include <naio/Cfg.h>
#include "transport/TLGlobalCfg.h"

namespace Transport
{
  class IAddressTranslator;
  class MessageFactory;
}

namespace TransportLayer
{

namespace TL = TransportLayer;

class Cfg : public naio::Cfg
{
public:
  Cfg() :
  firstServerPort( 35000 ),
  at_(0),
  mf_(0),
  mbHeapDumpFreq_(10000),
  mbHeapPerConnection_(0 != GlobalCfg::GetMessageBlockHeapPerConnection()),
  mbHeapName_("default"),
  mbNotypeUseThreshold_(GlobalCfg::GetMessageBlockNotypeUseThreshold()),
  mbWriteUseThreshold_(GlobalCfg::GetMessageBlockWriteUseThreshold()),
  mbReadUseThreshold_(GlobalCfg::GetMessageBlockReadUseThreshold()),
  sendPing_(false)
  {}

public:
  int firstServerPort;
  StrongMT<Transport::IAddressTranslator> at_;
  Transport::MessageFactory* mf_;
  unsigned int mbHeapDumpFreq_;
  bool mbHeapPerConnection_;
  nstl::string mbHeapName_;
  int mbNotypeUseThreshold_;
  int mbWriteUseThreshold_;
  int mbReadUseThreshold_;
  bool sendPing_;
};

}
