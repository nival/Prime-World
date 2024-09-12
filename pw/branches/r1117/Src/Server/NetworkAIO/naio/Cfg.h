#pragma once

#include "naio/Types.h"

namespace naio
{
  class IProtocolHandlerFactory;

  class Cfg
  {
  public:
    Cfg()
      :threads_(0),
      loglvl_(2),
      phf_(0),
      terabit_loglvl_(2),  //  minimum logging, only errors
      read_block_size_(4096),
      so_rcvbuf_(-1), //  use default value
      so_sndbuf_(-1), //  use default value
      disableNagleAlgorithm_(-1),  //  leave default system setting
      so_keepalive_(-1), //  default system value
      checkActivityTimeout_(0),
      logWrittenBytes_(0)
    {
    }

    int threads_;
    int loglvl_;
    int terabit_loglvl_;
    unsigned int read_block_size_;
    int so_rcvbuf_;
    int so_sndbuf_;
    int disableNagleAlgorithm_;
    int so_keepalive_;
    LogMsgCallbackSP spLogMsgCb_;
    IProtocolHandlerFactory* phf_;
    unsigned int checkActivityTimeout_;
    unsigned int logWrittenBytes_;
  };
}
