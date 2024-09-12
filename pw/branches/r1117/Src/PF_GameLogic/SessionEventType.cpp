#include "stdafx.h"
#include "SessionEventType.h"

namespace SessionEventType
{
  const char* EventTypesName[] =
  {
#define NAMED_ENUM_(name) #name
#define NAMED_ENUM(key, value) NAMED_ENUM_(key##_##value)
#include "SessionEventTypeDef.h"
#undef  NAMED_ENUM
#undef NAMED_ENUM_
  };

  char const * getEventName(int evtid)
  {
    if (evtid < EventBase && evtid >= NumberOfEvents)
      return "##INVALID_EVENT_ID##";

    return EventTypesName[evtid];
  }

}
