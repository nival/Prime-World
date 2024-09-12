#include "stdafx.h"
#include "PFAdvMap.h"

#include "DBAdvMap.h"
#include "DBStats.h"
#include "DBHeroesList.h"

#include "GameMaps.h"

#ifndef VISUAL_CUTTED
#include "PFMinigamePlace.h"
#include "PFClientObjectHelpers.h"
#endif

#include "PFHero.h"
#include "HeroSpawn.h"
#include "../PF_Core/World.h"

#include "../System/nalgoritm.h"
#include "../System/Win32Random.h"
#include "../libdb/Db.h"
#include "../System/Placement.h"
#include "../System/Reminder.h"
#include "Game/PF/HybridServer/PeeredTypes.h"


namespace
{
  void AddBots(vector<NCore::PlayerStartInfo> & players, const vector<NDb::AdvMapPlayerData> & bots, NCore::ETeam::Enum team)
  {
    for (int i = 0; i < bots.size(); ++i)
    {
      if (IsValid(bots[i].hero))
      {
        NCore::PlayerStartInfo & player = players.push_back();

        player.playerType = NCore::EPlayerType::Computer;
        player.userID     = -1;
        player.zzimaSex   = NCore::ESex::Male;  // Doesn't really matter for bots - filled elsewhere
        player.teamID     = team;
        player.originalTeamID = team;
        player.playerInfo.heroId = Crc32Checksum().AddString( bots[i].hero->id.c_str() ).Get();
        player.usePlayerInfoTalentSet = false;
        player.nickname = bots[i].nickname.GetText();
        player.playerInfo.leagueIndex = 0;
      }
    }
  }

  const Peered::ClientInfo * FindClientInfo( int clientId, const vector<Peered::ClientInfo> & clientInfos )
  {
    for (nstl::vector<Peered::ClientInfo>::const_iterator it = clientInfos.begin(); it != clientInfos.end(); ++it)
    {
      if ((*it).clientId == clientId)
      {
        return it;
      }
    }
    return 0;
  }

} // namespace

extern bool G_IsRandomBotSkinsEnabled();

namespace NWorld
{


static bool GetSpawnersImpl( NCore::TPlayerSpawnInfo & result, const NDb::AdvMap * dbMap, int & team1Size, int & team2Size )
{

  NCore::TPlayersStartInfo players;
  
  vector<NDb::AdvMapObject> const& objects = dbMap->objects;
  for ( vector<NDb::AdvMapObject>::const_iterator it = objects.begin(), end = objects.end(); it != end; ++it )
  {
    NDb::Ptr<NDb::GameObject> pGO = it->gameObject;
    if( pGO && ( pGO->GetObjectTypeID() == NDb::HeroPlaceHolder::typeId ) )
    {
      NDb::HeroPlaceHolder const* pSpawner = dynamic_cast<const NDb::HeroPlaceHolder *>(pGO.GetPtr());
      NI_VERIFY( pSpawner, "Invalid gameobject!", continue );

      NCore::ETeam::Enum team = (NCore::ETeam::Enum)pSpawner->teamId;

      if( team == NCore::ETeam::Team1 )
        ++team1Size;
      else if( team == NCore::ETeam::Team2 )
        ++team2Size;
      else
      {
        NI_ALWAYS_ASSERT( "Wrong team id" );
        continue;
      }

      result.push_back( team );
    }
  }

  NI_VERIFY( ( 0 < team1Size ) && ( 0 < team2Size ), "Invalid map: no placeholders found for one or both team(s)", return false );
  DebugTrace( "Loaded info for map '%s', max players per team: %d / %d", dbMap->GetDBID().GetFileName().c_str(), team1Size, team2Size );
  return true;
}


inline void ShuffleHeroes( vector<NCore::PlayerStartInfo>& players, const int randomSeed )
{
  NRandom::RandomGenerator randGen( randomSeed );

  vector<NCore::PlayerInfo*> teamPlayerInfos[2];
  for ( int pl = 0, total = players.size(); pl < total; pl++ )
  {
    NCore::PlayerStartInfo& playerStartInfo = players[pl];

    if (playerStartInfo.playerType != NCore::EPlayerType::Human)
      continue;

    NI_VERIFY( 0 <= playerStartInfo.teamID && playerStartInfo.teamID < 2, "Invalid teamID", continue );

    teamPlayerInfos[ playerStartInfo.teamID ].push_back( &playerStartInfo.playerInfo );
  }

  for ( int team = 0; team < 2; team++ )
  {
    vector<NCore::PlayerInfo*>& playerInfos = teamPlayerInfos[team];
    const int teamSize = playerInfos.size();

    if (teamSize < 2)
      continue;

    vector<int> shufflePos;
    shufflePos.resize( teamSize );
    for ( int i = 0; i < teamSize; i++ )
      shufflePos[i] = i;

    const bool odd = teamSize % 2; // Нечётность кол-ва игроков в команде

    for ( int count = 0, total = teamSize / 2 + odd; count < total; count++ )
    {
      int pos = shufflePos[count];
      int tmp = randGen.Next( count + 1, shufflePos.size() - 1 );
      int otherPos = shufflePos[tmp];
      NCore::PlayerInfo& leftPI  = *(playerInfos[pos]);
      NCore::PlayerInfo& rightPI = *(playerInfos[otherPos]);

      nstl::swap( leftPI.heroId,      rightPI.heroId );
      nstl::swap( leftPI.talents,     rightPI.talents );
      nstl::swap( leftPI.heroSkin,    rightPI.heroSkin );

      // Только для финальной статистики и экрана загрузки
      nstl::swap( leftPI.heroLevel,   rightPI.heroLevel );
      nstl::swap( leftPI.heroExp,     rightPI.heroExp );
      nstl::swap( leftPI.heroRating,  rightPI.heroRating );
      //

      nstl::swap( leftPI.hsHealth,    rightPI.hsHealth );
      nstl::swap( leftPI.hsMana,      rightPI.hsMana );
      nstl::swap( leftPI.hsStrength,  rightPI.hsStrength );
      nstl::swap( leftPI.hsIntellect, rightPI.hsIntellect );
      nstl::swap( leftPI.hsAgility,   rightPI.hsAgility );
      nstl::swap( leftPI.hsCunning,   rightPI.hsCunning );
      nstl::swap( leftPI.hsFortitude, rightPI.hsFortitude );
      nstl::swap( leftPI.hsWill,      rightPI.hsWill );
      nstl::swap( leftPI.hsLifeRegen, rightPI.hsLifeRegen );
      nstl::swap( leftPI.hsManaRegen, rightPI.hsManaRegen );

      if ( !odd || count > 0 )
        shufflePos.eraseByIndex( tmp );
    }
  }
}


class PWFillMapStartInfo : public IMapLoader, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( PWFillMapStartInfo, IMapLoader, BaseObjectMT );

public:
  PWFillMapStartInfo( const NDb::AdvMap * _dbMap ) 
    : dbMap( _dbMap ), dbMapDescription(0) {}

  PWFillMapStartInfo( const NDb::AdvMapDescription * _dbMapDescription ) 
    : dbMap( _dbMapDescription->map ), dbMapDescription(_dbMapDescription) {}

  virtual const char * GetMapDbId() const { return dbMap->GetDBID().GetFileName().c_str(); } //FIXME: We returning filename only, WITHOUT id
  virtual const char* GetMapDescName() { return  (IsValid(dbMapDescription) ? dbMapDescription->GetDBID().GetFileName().c_str() : 0); }

  virtual bool FillMapStartInfo( NCore::MapStartInfo & _mapStartInfo, const lobby::TGameLineUp & _gameLineup, const lobby::SGameParameters & _gameParams )
  {
    NCore::TPlayerSpawnInfo spawners;
    int team1Size = 0, team2Size = 0;
    if ( !NWorld::GetSpawnersImpl( spawners, dbMap, team1Size, team2Size ) )
      return false;

    if (!IsValid(dbMapDescription))
      return false;

    _mapStartInfo = NCore::MapStartInfo();
    _mapStartInfo.randomSeed = _gameParams.randomSeed;
    _mapStartInfo.mapDescName = dbMapDescription->GetDBID().GetFileName();
    _mapStartInfo.playersInfo.resize( spawners.size() );
	_mapStartInfo.isCustomGame = _gameParams.customGame;

    vector<NCore::PlayerStartInfo> players;
    players.reserve(_gameLineup.size());

    for (int i = 0; i < _gameLineup.size(); ++i)
    {
      const lobby::SGameMember & lobbyPlayer = _gameLineup[i];

      NCore::PlayerStartInfo & player = players.push_back();

      player.playerType = NCore::EPlayerType::Enum( lobbyPlayer.context.playerType );
      player.userID     = lobbyPlayer.user.userId;
      player.zzimaSex   = (NCore::ESex::Enum)lobbyPlayer.user.zzimaSex;
      player.teamID     = (NCore::ETeam::Enum)lobbyPlayer.context.team;
      player.originalTeamID = (NCore::ETeam::Enum)lobbyPlayer.context.original_team;

      player.nickname   = lobbyPlayer.user.nickname;

      DevTrace("player.userID=%d, player.teamID=%d, player.originalTeamID=%d", player.userID, (int)player.teamID, (int)player.originalTeamID);
      
      player.playerInfo.heroId = Crc32Checksum().AddString( lobbyPlayer.context.hero.c_str() ).Get();
      player.usePlayerInfoTalentSet = false;

      // NUM_TASK поддержка выдачи ботам скинов со стороны сервера
      if ( player.playerType == NCore::EPlayerType::Computer ) 
        player.playerInfo.heroSkin = lobbyPlayer.context.botSkin;
    }

    // Handle heroes override settings (only single player game is currently overridable)
    const NDb::AdvMapHeroesOverride* pDBHeroesOverride = dbMapDescription->heroesOverride;
    if (pDBHeroesOverride)
    {
      if ( !players.empty() && dbMapDescription->mapType == NDb::MAPTYPE_COOPERATIVE )
        OverrideCooperative( players );
      else if ( players.size() == 1 )
        OverrideSinglePlayer( players );
    }

    for ( int i = 0; i < players.size(); ++i )
    {
      NCore::PlayerStartInfo * firstFreeSlot = 0, * firstCorrectSlot = 0;
      for ( int j = 0; j < spawners.size(); ++j )
      {
        NCore::PlayerStartInfo * player = & _mapStartInfo.playersInfo[j];
        if ( player->playerType != NCore::EPlayerType::Invalid )
          continue;
        
        if ( !firstFreeSlot )
          firstFreeSlot = player;

        if ( !firstCorrectSlot && ( spawners[j] == players[i].teamID/*requiredTeam*/ ) )
        {
          firstCorrectSlot = player;
          break;
        }
      }

      NI_DATA_VERIFY( firstFreeSlot, "Not enough spawners at all", return false );
      NI_DATA_VERIFY( firstCorrectSlot, "Not enough spawners for one of the teams", firstCorrectSlot = firstFreeSlot )

      *firstCorrectSlot = players[i];
    }

    for ( int i = 0; i < _mapStartInfo.playersInfo.size(); ++i )
      _mapStartInfo.playersInfo[i].playerID = i;

    return true;
  }

  void OverrideSinglePlayer( vector<NCore::PlayerStartInfo> &players )
  {
    NDb::Ptr<NDb::AdvMapHeroesOverrideData> heroesOverride;

    if (players[0].zzimaSex == NCore::ESex::Male)
      heroesOverride = dbMapDescription->heroesOverride->singlePlayerMale;
    else if (players[0].zzimaSex == NCore::ESex::Female)
      heroesOverride = dbMapDescription->heroesOverride->singlePlayerFemale;

    if (!IsValid(heroesOverride))
      return;

    players.reserve(1 + heroesOverride->allies.size() + heroesOverride->enemies.size());
    if (IsValid(heroesOverride->ownHero.hero)) // Overriding of own hero is optional
    {
      players[0].playerInfo.heroId = Crc32Checksum().AddString( heroesOverride->ownHero.hero->id.c_str() ).Get();
    }
    NCore::ETeam::Enum localTeam = players[0].teamID;
    NCore::ETeam::Enum enemyTeam = (localTeam == NCore::ETeam::Team1)?(NCore::ETeam::Team2):(NCore::ETeam::Team1);
    AddBots(players, heroesOverride->allies, localTeam);
    AddBots(players, heroesOverride->enemies, enemyTeam);
  }

  void OverrideCooperative( vector<NCore::PlayerStartInfo> &players )
  {
    NDb::Ptr<NDb::AdvMapHeroesOverrideData> heroesOverride = dbMapDescription->heroesOverride->singlePlayerMale;
    if (!IsValid(heroesOverride))
      return;

    players.reserve( players.size() + heroesOverride->enemies.size() );

    NCore::ETeam::Enum localTeam = players[0].teamID;
    NCore::ETeam::Enum enemyTeam = (localTeam == NCore::ETeam::Team1) ? NCore::ETeam::Team2 : NCore::ETeam::Team1;
    AddBots(players, heroesOverride->enemies, enemyTeam);
  }

  virtual bool FillPlayersInfo( NCore::MapStartInfo & _mapStartInfo, const vector<Peered::ClientInfo> & _clientInfos, bool assertIfNoInfo = false )
  {
    NRandom::RandomGenerator randGen;
    randGen.SetSeed(_mapStartInfo.randomSeed);

    for ( int i = 0; i < _mapStartInfo.playersInfo.size(); ++i )
    {
      NCore::PlayerStartInfo & slot = _mapStartInfo.playersInfo[i];

      if ( slot.playerType == NCore::EPlayerType::Computer && (/* NUM_TASK dbMapDescription->botsUseSkins ||*/ G_IsRandomBotSkinsEnabled()))
      {
        NCore::ETeam::Enum teamId = slot.originalTeamID;

        switch (teamId)
        {
        case NCore::ETeam::Team1:
        case NCore::ETeam::Team2:
          break;
        default:
          teamId = slot.teamID;
          break;
        }

        slot.playerInfo.heroSkin = GetRandomHeroSkin( slot.playerInfo.heroId, dbMapDescription.GetPtr(), randGen, teamId );
      }
      
      if ( slot.playerType != NCore::EPlayerType::Human )
        continue;

      const Peered::ClientInfo * clientInfo = FindClientInfo( slot.userID, _clientInfos );
      if ( clientInfo && clientInfo->info.talents.size() && clientInfo->info.heroId )
      {
        slot.playerInfo = clientInfo->info;
        slot.usePlayerInfoTalentSet = true;
      }
      else if ( assertIfNoInfo )
        NI_ALWAYS_ASSERT( NStr::StrFmt( "No details for player %d", slot.userID ) );

      if (clientInfo)
      {
        slot.playerInfo.partyId = clientInfo->info.partyId;
      }
    }

    // Shuffle heroes if needed
    if ( dbMapDescription->heroesOverride && dbMapDescription->heroesOverride->shuffleHeroesInTeam )
    {
      NI_ASSERT( !dbMapDescription->heroesOverride->singlePlayerMale 
                  && !dbMapDescription->heroesOverride->singlePlayerFemale,
                    "Incompatible heroesOverride settings" );
      ShuffleHeroes( _mapStartInfo.playersInfo, _mapStartInfo.randomSeed );
    }

    return true;
  }


  virtual int GetMaxPlayersPerTeam()
  {
    int team1Size = 0, team2Size = 0;
    NCore::TPlayerSpawnInfo spawns;
    NWorld::GetSpawnersImpl( spawns, dbMap, team1Size, team2Size );

    return Min( team1Size, team2Size );
  }

private:
 NDb::Ptr<NDb::AdvMap> dbMap; // for precache
 NDb::Ptr<NDb::AdvMapDescription> dbMapDescription;
};



IMapLoader* CreatePWFillMapStartInfo( const NDb::AdvMapDescription * _dbMapDescription )
{
  return new PWFillMapStartInfo( _dbMapDescription );
}

IMapLoader * CreatePWFillMapStartInfo( const NDb::AdvMap * _dbMap )
{
  return new PWFillMapStartInfo( _dbMap );
}

} // namespace NWorld

NI_DEFINE_REFCOUNT( NWorld::IMapLoader )
