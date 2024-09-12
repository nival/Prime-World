#pragma once

#include "../System/Basic.h"
#include "../System/NameMap.h"

namespace NGameX
{

typedef int UserId;

class PlayerData : public NNameMap::Map
{
  NAMEMAP_DECLARE;
public:
  PlayerData() : experience(0) {}
  explicit PlayerData(wstring const &_name, UserId userId_,  int _experience, int _rating, bool isPremium_, bool fwod_, bool isCustomGame_, wstring const &_heroName, string const &_heroPersistentId ) 
		: name(_name)
		, experience(_experience)
		, rating(_rating) 
		, userId(userId_)
		, isPremium(isPremium_)
		, fwod(fwod_)
    , isCustomGame(isCustomGame_)
    , heroName(_heroName)
    , heroPersistentId(_heroPersistentId)
	{}

  string const &GetHeroPersistentId() const { return heroPersistentId; }
  wstring const &GetPlayerName() const { return name; }
  wstring const &GetHeroName() const { return heroName; }
  int GetHeroExperience() const { return experience; }
  int GetHeroRating() const { return rating; }
	bool IsPremium() const {return isPremium;}
	UserId GetUserId() const {return userId;}
	bool IsFirstWin() const {return fwod;}
  bool IsCustomGame() const {return isCustomGame;}
	
  wstring name;
  string heroPersistentId;
  int experience;
  int rating;
	UserId userId;
	bool isPremium;
	bool fwod;
  bool isCustomGame;
  wstring heroName;
};

class PlayerDataManager : public CObjectBase
{
  OBJECT_METHODS(0xB67F440, PlayerDataManager);
public:
  PlayerDataManager();
  void AddPlayerData(int playerId, PlayerData const &data);
  PlayerData const &GetPlayerData(int playerId) const;
	const PlayerData & GetPlayerDataByUser( UserId userId ) const;
protected:
  typedef map<int, PlayerData> PlayerDataMap;
  PlayerData          m_dummy;
  PlayerDataMap       m_map;
};

}