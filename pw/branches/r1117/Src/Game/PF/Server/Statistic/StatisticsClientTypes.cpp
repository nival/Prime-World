#include "stdafx.h"
#include "StatisticsClientTypes.h"


namespace StatisticService
{
  namespace RPC
  {
    SERIALIZE_FACTORY(CommonSessionEventInfo);
    SERIALIZE_FACTORY(ClientCommonSessionEvent);
    SERIALIZE_FACTORY(ClientSessionDamageMessage);
  }
}
