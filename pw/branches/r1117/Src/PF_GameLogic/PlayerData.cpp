#include "stdafx.h"
#include "PlayerData.h"

namespace NGameX
{
  NAMEMAP_BEGIN(PlayerData)
    NAMEMAP_FUNC_RO(name, &PlayerData::GetPlayerName)
  NAMEMAP_END

  PlayerDataManager::PlayerDataManager() : m_dummy(L"Dummy name", 0, 0, 0, false, false, false, L"", "")
  {
  }

  void PlayerDataManager::AddPlayerData(int playerId, PlayerData const &data)
  {
    m_map[playerId] = data;
  }

  PlayerData const &PlayerDataManager::GetPlayerData(int playerId) const
  {
    PlayerDataMap::const_iterator it = m_map.find(playerId);
    
    if ( it != m_map.end() )
    {
      return it->second;
    }

    return m_dummy;
  }

	const PlayerData & PlayerDataManager::GetPlayerDataByUser( UserId userId ) const
	{
		for (PlayerDataMap::const_iterator it = m_map.begin(); it!= m_map.end(); it++)
		{
			if (it->second.GetUserId() == userId)
			{
				return it->second;
			}
		}

		return m_dummy;
	}

}


BASIC_REGISTER_CLASS( NGameX::PlayerDataManager);