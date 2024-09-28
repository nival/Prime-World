#pragma once

namespace NWorld
{
  class PFPlayer;
  class PFBaseHero;
}
namespace NGameX
{
 class AdventureScreen;
 class PFWorld;
 class PFPlayer;

}
namespace StatisticService
{
  namespace RPC
  {
    struct SessionClientResultsPlayer;
  }
}

namespace EPlayerBehaviourEvent
{
  enum Enum
  {
    Gone,
    Died,
    GotNaftaForKill,
    ServedTeamNaftaForKill,
    ServedTeamNaftaForPresence,
    EnteredZuma,
    LeftZuma,
    TookScroll,
    GaveScroll,
    GotBadBehaviourComplaint,
    GotToxicPlayerComplaint,
    AutoMuteMessage,
    MessageInFilter,
    CapsMeessage,
    AutoMuteMessageLength, 
    SpamDetected,
  };
}

namespace PlayerBehaviourTracking
{
  void DispatchEvent(const NWorld::PFPlayer* const player, const EPlayerBehaviourEvent::Enum event);
  void DispatchEvent(const NWorld::PFBaseHero* const hero, const EPlayerBehaviourEvent::Enum event);
  void DispatchEvent(int userId, const EPlayerBehaviourEvent::Enum event);

  bool ShouldTrackBehaviour(const NWorld::PFPlayer* const player);
  bool ShouldTrackBehaviour(const NWorld::PFBaseHero* const hero);

  void UpdatePlayerStatistics(const NWorld::PFPlayer* const player, StatisticService::RPC::SessionClientResultsPlayer& stats);
  int UpdateFastCRC(const NWorld::PFPlayer* const player, IBinSaver& f, const int indexBase);
}
