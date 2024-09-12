#pragma once

namespace TransportLayer
{
  namespace TL = TransportLayer;

  struct GlobalCfg
  {
  public:
    static int GetThreads();
    static int GetReadBlockSize();
    static int GetSoRcvbuf();
    static unsigned int GetMaxWriteBlockSize();
    static int GetSoSndbuf();
    static int GetDisableNagleAlgorithm();
    static int GetSoKeepalive();
    static int GetLogLevel();
    static int GetTerabitLogLevel(); //  errors only
    static int GetMessageBlockHeapDumpFreq();
    static int GetMessageBlockHeapPerConnection();
    static int GetMessageBlockNotypeUseThreshold();
    static int GetMessageBlockWriteUseThreshold();
    static int GetMessageBlockReadUseThreshold();
    static int GetLogWrittenBytes();
    static unsigned int GetCheckActivityTimeout();
  };
}
