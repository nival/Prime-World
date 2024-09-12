#include "stdafx.h"
#include "PlayerBehaviourTracking.h"

#include "PFHero.h"
#include "AdventureScreen.h"

namespace PlayerBehaviourTracking
{
  using NWorld::PlayerBehaviourTracker;

  namespace Private
  {
    // NOTE: implemented elsewhere
    void DispatchEventImpl(const CObj<PlayerBehaviourTracker>& tracker, const EPlayerBehaviourEvent::Enum event);
    bool ShouldTrackBehaviourImpl(const CObj<PlayerBehaviourTracker>& tracker);
    void UpdatePlayerStatisticsImpl(const CObj<PlayerBehaviourTracker>& tracker, StatisticService::RPC::SessionClientResultsPlayer& stats);

    int UpdateFastCRCImpl(const CObj<PlayerBehaviourTracker>& tracker, IBinSaver& f, const int indexBase);
  }

  void DispatchEvent(const NWorld::PFPlayer* const player, const EPlayerBehaviourEvent::Enum event)
  {
    if (!player)
      return;

    Private::DispatchEventImpl(player->GetBehaviourTracker(), event);
  }

  void DispatchEvent(int userId, const EPlayerBehaviourEvent::Enum event)
  {
    NGameX::AdventureScreen * advScreen = NGameX::AdventureScreen::Instance();
    if (!advScreen )
      return;

    NWorld::PFWorld *world = advScreen->GetWorld();
    if ( !world )
      return;

    NWorld::PFPlayer* player = world->GetPlayer( advScreen->GetLocalPlayerID() );
    if ( !player )
      return;

    Private::DispatchEventImpl(player->GetBehaviourTracker(), event);
  }



  void DispatchEvent(const NWorld::PFBaseHero* const hero, const EPlayerBehaviourEvent::Enum event)
  {
    if (!hero)
      return;

    const CPtr<NWorld::PFPlayer>& player = hero->GetPlayer();

    if (!IsValid(player))
      return;

    Private::DispatchEventImpl(player->GetBehaviourTracker(), event);
  }

  bool ShouldTrackBehaviour(const NWorld::PFPlayer* const player)
  {
    if (!player)
      return false;

    return Private::ShouldTrackBehaviourImpl(player->GetBehaviourTracker());
  }

  bool ShouldTrackBehaviour(const NWorld::PFBaseHero* const hero)
  {
    if (!hero)
      return false;

    const CPtr<NWorld::PFPlayer>& player = hero->GetPlayer();

    if (!IsValid(player))
      return false;

    return Private::ShouldTrackBehaviourImpl(player->GetBehaviourTracker());
  }

  void UpdatePlayerStatistics(const NWorld::PFPlayer* const player, StatisticService::RPC::SessionClientResultsPlayer& stats)
  {
    if (!player)
      return;

    Private::UpdatePlayerStatisticsImpl(player->GetBehaviourTracker(), stats);
  }

  int UpdateFastCRC(const NWorld::PFPlayer* const player, IBinSaver& f, const int indexBase)
  {
    NI_ASSERT(!!player, "Player must exist!");

    const CObj<PlayerBehaviourTracker> tracker(player ? player->GetBehaviourTracker() : NULL);

    return Private::UpdateFastCRCImpl(tracker, f, indexBase);
  }

}
