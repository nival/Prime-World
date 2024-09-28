#pragma once

#include "Core/GameTypes.h"

namespace NGameX
{
  namespace PlayerInfoHelper
  {
    static const NCore::PlayerStartInfo* FindPlayerInfoByUserId(const NCore::TPlayersStartInfo& psi_list, const int userId)
    {
      NCore::TPlayersStartInfo::const_iterator it = psi_list.begin();
      NCore::TPlayersStartInfo::const_iterator it_end = psi_list.end();
      for (; it != it_end; ++it)
      {
        NCore::TPlayersStartInfo::const_reference psi = *it;

        if (psi.userID == userId)
          return &psi;
      }

      return NULL;
    }

    static const NCore::PlayerStartInfo* FindPlayerInfoByPlayerId(const NCore::TPlayersStartInfo& psi_list, const int playerId)
    {
      NCore::TPlayersStartInfo::const_iterator it = psi_list.begin();
      NCore::TPlayersStartInfo::const_iterator it_end = psi_list.end();
      for (; it != it_end; ++it)
      {
        NCore::TPlayersStartInfo::const_reference psi = *it;

        if (psi.playerID == playerId)
          return &psi;
      }

      return NULL;
    }

    static bool IsLeaver(const NCore::PlayerStartInfo* const psi)
    {
      if (!psi)
        return false;

      return (psi->playerInfo.basket == NCore::EBasket::Leaver);
    }

    static bool IsLeaverParty(const NCore::TPlayersStartInfo& psi_list, const NCore::PlayerStartInfo* const member)
    {
      if (!member)
        return false;

      const uint partyId = member->playerInfo.partyId;

      if (partyId == 0U)
        return IsLeaver(member);

      NCore::TPlayersStartInfo::const_iterator it = psi_list.begin();
      NCore::TPlayersStartInfo::const_iterator it_end = psi_list.end();
      for (; it != it_end; ++it)
      {
        NCore::TPlayersStartInfo::const_reference psi = *it;

        if (psi.playerInfo.partyId != partyId)
          continue;

        if (IsLeaver(&psi))
          return true;
      }

      return false;
    }
  }
}
