#pragma once

namespace Transport
{
  struct ClientCfg
  {
    static int GetLogLevel();
    static int DisableNagleAlgorithm(); //  -1 - system value, 0 - turn off, 1 - turn on
    static int GetReadBlockSize();
    static int GetCheckConnectionActivityTimeout();
    static int GetKeepalivePeriod();
    static int GetNumberOfThreads();
    static string const & GetLoginAddress();
  };
}
