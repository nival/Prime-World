#include "stdafx.h"
#include "StatisticsDebugTypes.h"


namespace StatisticService
{
  namespace RPC
  {
    SERIALIZE_FACTORY( DebugVarMessage );
    SERIALIZE_FACTORY( ExceedingStepTimeInfo );
    SERIALIZE_FACTORY( ExceedingPingTimeInfo );
    SERIALIZE_FACTORY( OfflineClientEvent );

    SERIALIZE_FACTORY( PvxLoginInfo );
    SERIALIZE_FACTORY( PvxScreenResolutionInfo );
  }
}
