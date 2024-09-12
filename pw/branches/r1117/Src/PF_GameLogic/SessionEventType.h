#pragma once

//corresponding file in cs Tools\GMTools\StatisticService\RPC\SessionEventType.cs 
namespace SessionEventType
{
  enum EventType
  {
    EventBase = 0,
    FirstEvent = 0,

#define NAMED_ENUM(key, value) key = value
#include "SessionEventTypeDef.h"
#undef  NAMED_ENUM

    NumberOfEvents
  };

  char const * getEventName(int evtid);
}
