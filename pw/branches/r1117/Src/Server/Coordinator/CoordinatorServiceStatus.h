#pragma once

namespace Coordinator
{
  namespace ServiceStatus
  {
    enum Enum
    {
      S_INIT,
      S_STARTING,
      S_STARTED,
      S_STOPPING,
      S_STOPPED,
      S_SOFT_STOPPING,
      S_SOFT_STOPPED,
      S_RESUMING,
      S_RESUMED,
    };

    inline
    char const * ToString(Enum svcst)
    {
      switch(svcst)
      {
      case S_INIT:
        return "INIT";
      case S_STARTING:
        return "STARTING";
      case S_STARTED:
        return "STARTED";
      case S_STOPPING:
        return "STOPPING";
      case S_STOPPED:
        return "STOPPED";
      case S_SOFT_STOPPING:
        return "SOFT_STOPPING";
      case S_SOFT_STOPPED:
        return "SOFT_STOPPED";
      case S_RESUMING:
        return "RESUMING";
      case S_RESUMED:
        return "RESUMED";
      default:
        return "";
      }
    }
  }
}
