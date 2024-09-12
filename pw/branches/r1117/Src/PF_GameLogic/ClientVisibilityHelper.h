#pragma once

#include "ClientVisibilityFlags.hpp"

#include "AdventureScreen.h"
#include "PFClientVisibilityMap.h"

#include "PFClientBaseUnit.h"
#include "PFClientCreature.h"

namespace NGameX
{
  class DeveloperClientVisibilityHelper;

  class ClientVisibilityHelper : public NonCopyable
  {
    friend DeveloperClientVisibilityHelper;
  public:
    STARFORCE_FORCE_INLINE static bool IsSpectatorMode()
    {
      if (!IsValid(advScreen))
        return false;

      return advScreen->IsSpectator();
    }

    STARFORCE_FORCE_INLINE static bool IsSharedVisionMode()
    {
      if (!IsSpectatorMode())
        return false;

      if (!IsValid(visMap))
        return false;

      return visMap->IsSharedVisionMode();
    }

    STARFORCE_FORCE_INLINE static bool IsPointVisible(const CVec2& p)
    {
      if (!IsValid(visMap))
        return false;

      return visMap->IsPointVisible(p);
    }

    STARFORCE_FORCE_INLINE static NDb::EFaction GetPlayerFaction()
    {
      if (!IsValid(advScreen))
        return NDb::FACTION_NEUTRAL;

      return advScreen->GetPlayerFaction();
    }

    STARFORCE_FORCE_INLINE static bool IsPartialVisibilityApplicable(const ClientVisibilityFlags& flags)
    {
      if (!flags.enemy || flags.sharedVision)
        return false;

      // объект либо полностью невидим (под туманом), либо полностью видим
      if (!flags.placementVisible || flags.objectVisible)
        return false;

      // объект не является невидимкой
      if (!flags.hasInvisibility || flags.hasIgnoreInvisibility)
        return false;

      return true;
    }

    STARFORCE_FORCE_INLINE static bool IsVisibleForPlayer(const ClientVisibilityFlags& flags)
    {
      if (!flags.enemy || flags.sharedVision)
        return true;

      return flags.objectVisible && flags.placementVisible;
    }

    STARFORCE_FORCE_INLINE static void UpdateFlags(const NWorld::PFLogicObject* const worldObject, ClientVisibilityFlags& flags)
    {
      struct Local
      {
        static inline bool IsVisionShared(const NWorld::PFLogicObject* const worldObject)
        {
          if (!advScreen->IsSpectator())
            return false;

          if (!visMap->IsSharedVisionMode())
            return false;
          if (!visMap->IsSharedVisionFaction(worldObject->GetFaction()))
            return false;

          return true;
        }
      };

      flags.Reset();

      if (!worldObject)
        return;

      if (!IsValid(advScreen))
        return;
      if (!IsValid(visMap))
        return;

      const NDb::EFaction playerFaction = advScreen->GetPlayerFaction();

      if (worldObject->GetFaction() == playerFaction)
      {
        flags.objectVisible = true;
        flags.sharedVision = true;
      }
      else
      {
        flags.enemy = true;
        flags.objectVisible = worldObject->IsVisibleForFactionInternal(playerFaction);
        flags.sharedVision = Local::IsVisionShared(worldObject);
      }

      if (worldObject->GetWarfogFaction() == playerFaction)
      {
        flags.placementVisible = true;
      }
      else
      {
        flags.placementVisible = visMap->IsPointVisible(worldObject->GetPos());
      }

      if (worldObject->IsDead())
      {
      }
      else
      {
        flags.hasInvisibility = worldObject->CheckFlagType(NDb::UNITFLAGTYPE_INVISIBLE);
        flags.hasIgnoreInvisibility = worldObject->CheckFlagType(NDb::UNITFLAGTYPE_IGNOREINVISIBLE);
      }
    }

    STARFORCE_FORCE_INLINE static void UpdateFlags(const NWorld::PFPlayer* const player, const NWorld::PFLogicObject* const worldObject, ClientVisibilityFlags& flags)
    {
      struct Local
      {
        static inline NDb::EFaction GetPlayerFaction(const NWorld::PFPlayer* const player)
        {
          NI_VERIFY(!!player, "Invalid player!", return NDb::FACTION_NEUTRAL);

          switch (player->GetTeamID())
          {
          case NCore::ETeam::Team1:
            return NDb::FACTION_FREEZE;
          case NCore::ETeam::Team2:
            return NDb::FACTION_BURN;
          default:
            return NDb::FACTION_NEUTRAL;
          }
        }

        static inline bool IsObjectPlacementVisible(const NWorld::PFPlayer* const player, const NDb::EFaction playerFaction, const NWorld::PFLogicObject* const worldObject)
        {
          NI_VERIFY(!!player, "Invalid player!", return false);
          NI_VERIFY(!!worldObject, "Invalid object!", return false);

          const SVector tile(tileMap->GetTile(worldObject->GetPos()));

          if (tile.x < 0)
            return false;
          if (tile.y < 0)
            return false;

          return fogOfWar->IsTileVisible(tile, static_cast<int>(playerFaction));
        }
      };

      flags.Reset();

      if (!player)
        return;
      if (!worldObject)
        return;

      if (!IsValid(fogOfWar))
        return;
      if (!IsValid(tileMap))
        return;

      const NDb::EFaction playerFaction = Local::GetPlayerFaction(player);

      flags.enemy = (worldObject->GetFaction() != playerFaction);
      flags.objectVisible = worldObject->IsVisibleForFactionInternal(playerFaction);
      flags.placementVisible = Local::IsObjectPlacementVisible(player, playerFaction, worldObject);
      flags.hasInvisibility = worldObject->CheckFlagType(NDb::UNITFLAGTYPE_INVISIBLE);
      flags.hasIgnoreInvisibility = worldObject->CheckFlagType(NDb::UNITFLAGTYPE_IGNOREINVISIBLE);
    }

    STARFORCE_FORCE_INLINE static ClientVisibilityFlags GetFlags(const PFClientLogicObject* const clientObject)
    {
      ClientVisibilityFlags flags;

      if (clientObject)
        UpdateFlags(clientObject->WorldObject(), flags);

      return flags;
    }

    STARFORCE_FORCE_INLINE static ClientVisibilityFlags GetFlags(const NWorld::PFLogicObject* const worldObject)
    {
      ClientVisibilityFlags flags;

      if (worldObject)
        UpdateFlags(worldObject, flags);

      return flags;
    }

    STARFORCE_FORCE_INLINE static bool IsPartialVisibilityApplicable(const PFClientLogicObject* const clientObject)
    {
      const ClientVisibilityFlags flags(GetFlags(clientObject));

      return IsPartialVisibilityApplicable(flags);
    }

    STARFORCE_FORCE_INLINE static bool IsPartialVisibilityApplicable(const NWorld::PFLogicObject* const worldObject)
    {
      const ClientVisibilityFlags flags(GetFlags(worldObject));

      return IsPartialVisibilityApplicable(flags);
    }

    STARFORCE_FORCE_INLINE static bool IsVisibleForPlayer(const PFClientLogicObject* const clientObject)
    {
      const ClientVisibilityFlags flags(GetFlags(clientObject));

      return IsVisibleForPlayer(flags);
    }

    STARFORCE_FORCE_INLINE static bool IsVisibleForPlayer(const NWorld::PFLogicObject* const worldObject)
    {
      const ClientVisibilityFlags flags(GetFlags(worldObject));

      return IsVisibleForPlayer(flags);
    }
  private:
    ClientVisibilityHelper();
    ~ClientVisibilityHelper();

    static DI_WEAK(AdventureScreen) advScreen;
    static DI_WEAK(VisibilityMapClient) visMap;
    static DI_WEAK(NWorld::FogOfWar) fogOfWar;
    static DI_WEAK(NWorld::TileMap) tileMap;
  };

  class DeveloperClientVisibilityHelper : public NonCopyable
  {
  public:
    STARFORCE_FORCE_INLINE static bool CanCreatureSleep(const NGameX::PFClientCreature* const clientObject)
    {
#ifndef _SHIPPING
      if (!clientObject)
        return true;

      const ClientVisibilityFlags flags(ClientVisibilityHelper::GetFlags(clientObject));

      if (flags.placementVisible)
        return false;

      const NWorld::PFCreature* const worldObject = clientObject->WorldObject();

      if (!worldObject)
        return true;

      if (worldObject->GetFaction() != NDb::FACTION_NEUTRAL)
        return true;

      if (!IsValid(ClientVisibilityHelper::visMap))
        return true;

      if (ClientVisibilityHelper::visMap->GetMode() != EVisMapMode::FactionN)
        return true;

      return false;
#else
      return true;
#endif
    }

    STARFORCE_FORCE_INLINE static void ForceUnitVisibilityIfNecessary(NGameX::PFClientBaseUnit* const clientObject)
    {
#ifndef _SHIPPING
      if (!clientObject)
        return;

      if (clientObject->IsVisible())
        return;

      const ClientVisibilityFlags flags(ClientVisibilityHelper::GetFlags(clientObject));

      if (flags.hasInvisibility || !flags.placementVisible)
        return;

      clientObject->SetVisibility(true);
#endif
    }
  private:
    DeveloperClientVisibilityHelper();
    ~DeveloperClientVisibilityHelper();
  };
}
