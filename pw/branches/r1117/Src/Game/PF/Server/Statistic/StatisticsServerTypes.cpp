#include "stdafx.h"
#include "StatisticsServerTypes.h"


namespace StatisticService
{

namespace RPC
{
  SERIALIZE_FACTORY(SessionStartEvent);
  SERIALIZE_FACTORY(SessionStartPlayer);
  SERIALIZE_FACTORY(SessionServerResultsPlayer);
  SERIALIZE_FACTORY(SessionResultEvent);
  SERIALIZE_FACTORY(MMakingMember);
  SERIALIZE_FACTORY(MMakingGame);
  SERIALIZE_FACTORY(MMakingCanceled);
  SERIALIZE_FACTORY(ExceedingStepTimeInfoServer);
  SERIALIZE_FACTORY(ReconnectAttemptInfo);
  SERIALIZE_FACTORY(SessionTrafficInfo);
  SERIALIZE_FACTORY(SessionUserContext);
  SERIALIZE_FACTORY(UserCheatEvent);
  SERIALIZE_FACTORY(UserDisconnectEvent);
  SERIALIZE_FACTORY(UserStatusEvent);
}

}
