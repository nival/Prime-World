#pragma once

#include "stdafx.h"

#include "HeroSpawn.h"
#include "PFAdvMap.h"

#include "DBAdvMap.h"
#include "DBStats.h"
#include "DBHeroesList.h"

#ifndef VISUAL_CUTTED
#include "PFMinigamePlace.h"
#include "PFClientObjectHelpers.h"
#endif

#include "PFHero.h"
#include "PF_Core/World.h"

#include "System/nalgoritm.h"
#include "libdb/Db.h"
#include "System/Placement.h"
#include "System/Reminder.h"
#include "System/LoadingProgress.h"
#include "System/InlineProfiler.h"
#include "System/Crc32Checksum.h"
#include "System/RandomGenerator.h"

#include "Scene/AnimatedSceneComponent.h"
#include "AdventureScreen.h"

#include "MapLoadingUtility.hpp"

namespace 
{
  struct BotOverride
  {
    string heroIds[5];
    int pet[5];           // PetType
    string customTS[5];   // xdb с переопределенным TS
  };

  BotOverride botOverride[2];
}

static bool g_useTestTalentSet = false;
REGISTER_DEV_VAR( "use_test_talentset", g_useTestTalentSet, STORAGE_NONE );

static bool s_prechacheSessionData = true;
REGISTER_DEV_VAR( "precache_session_data", s_prechacheSessionData, STORAGE_NONE );

bool G_GetPrechacheSessionData() { return s_prechacheSessionData; }

static bool g_useRandomSkins = false;
REGISTER_DEV_VAR( "use_random_skins", g_useRandomSkins, STORAGE_NONE );
bool G_IsRandomBotSkinsEnabled() { return g_useRandomSkins; }

static string g_validHeroesForTestTalentSet = "";
REGISTER_DEV_VAR( "valid_heroes_for_test_talentset", g_validHeroesForTestTalentSet, STORAGE_NONE );

static string g_validPets = "";
REGISTER_DEV_VAR( "valid_pets", g_validPets, STORAGE_NONE );

namespace NWorld
{
   
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef VISUAL_CUTTED
  void PreloadHero( NDb::Ptr<NDb::BaseHero> pHero, NWorld::PFWorld* pWorld, int teamID )
  {
    NI_PROFILE_FUNCTION_MEM;

    if ( !IsValid( pHero ) )
      return;

    if ( !IsValid( pHero->heroSceneObjects[teamID] ) )
    {
      teamID = (teamID == NDb::TEAMID_A) ? NDb::TEAMID_B : NDb::TEAMID_A;
    }

    NDb::Ptr<NDb::DBSceneObject> sceneObject;
    if ( IsValid( pHero->heroSceneObjects[teamID] ) )
    {
      sceneObject = pHero->heroSceneObjects[teamID];
    }
    else
    {
      sceneObject = pHero->sceneObject;
    }

//     pWorld->GetIAdventureScreen()->PreloadEffectsInResourceTree( pHero.GetPtr() );
// 
//     if ( IsValid( sceneObject ) )
//       NScene::SceneObjectsPool::Get()->Reserve( pWorld->GetScene(), sceneObject, 1 );

    if ( IsValid( sceneObject ) )
      pWorld->GetIAdventureScreen()->PreloadEffectsInResourceTree( sceneObject.GetPtr(), REVIVENODE );
  }
#endif

  const NDb::Hero *FindHeroInOverride(const NDb::AdvMapHeroesOverrideData* data, uint heroId)
  {
    if ( !data )
      return 0;

    if ( data->ownHero.hero && Crc32Checksum().AddString( data->ownHero.hero->id.c_str()).Get() == heroId )
      return data->ownHero.hero;

    for (vector<NDb::AdvMapPlayerData>::const_iterator it =data->allies.begin(); it != data->allies.end(); ++it ) 
      if( it->hero && Crc32Checksum().AddString( it->hero->id.c_str()).Get() == heroId )
        return it->hero;

    for (vector<NDb::AdvMapPlayerData>::const_iterator it =data->enemies.begin(); it != data->enemies.end(); ++it ) 
      if( it->hero && Crc32Checksum().AddString( it->hero->id.c_str()).Get() == heroId )
        return it->hero;

    return 0;
  }

  const NDb::Hero * FindHero( const NDb::HeroesDB * db, const NDb::AdvMapDescription* advMapDesc, uint heroId )
  {
    for ( int i = 0; i < db->heroes.size(); ++i ) {
      NI_VERIFY( db->heroes[i], "", continue );
      if ( Crc32Checksum().AddString( db->heroes[i]->id.c_str()).Get() == heroId )
        return db->heroes[i];
    }
    if ( advMapDesc && advMapDesc->heroesOverride )
    {
      if ( const NDb::Hero* hero = FindHeroInOverride( advMapDesc->heroesOverride->singlePlayerMale, heroId ) )
        return hero;
      if ( const NDb::Hero* hero = FindHeroInOverride( advMapDesc->heroesOverride->singlePlayerFemale, heroId ) )
        return hero;
    }
    return 0;
  }

  const wstring& FindNicknameInOverride(const NDb::AdvMapHeroesOverrideData* data, const NDb::BaseHero* hero)
  {
    static wstring empty;

    if ( !data )
      return empty;

    if ( data->ownHero.hero && data->ownHero.hero->GetDBID() == hero->GetDBID() )
      return data->ownHero.nickname.GetText();

    for (vector<NDb::AdvMapPlayerData>::const_iterator it =data->allies.begin(); it != data->allies.end(); ++it ) 
      if( it->hero && it->hero->GetDBID() == hero->GetDBID() )
        return it->nickname.GetText();

    for (vector<NDb::AdvMapPlayerData>::const_iterator it =data->enemies.begin(); it != data->enemies.end(); ++it ) 
      if( it->hero && it->hero->GetDBID() == hero->GetDBID() )
        return it->nickname.GetText();

    return empty;
  }

  const wstring& FindHeroNickname( const NDb::AdvMapDescription* advMapDesc, const NDb::BaseHero* hero )
  {
    if ( advMapDesc && advMapDesc->heroesOverride )
    {
      {
        const wstring& nickname = FindNicknameInOverride( advMapDesc->heroesOverride->singlePlayerMale, hero );
        if ( !nickname.empty() )
          return nickname;
      }
      {
        const wstring& nickname = FindNicknameInOverride( advMapDesc->heroesOverride->singlePlayerFemale, hero );
        if ( !nickname.empty() )
          return nickname;
      }
    }
    static wstring empty;
    return empty;
  }

  void AddPet( const char* petname, NWorld::PFWorld* pWorld, const NCore::TPlayersStartInfo::const_iterator& player_it, const TTeamSpawnInfo::iterator& spawner )
  {
    int petid = Crc32Checksum().AddString(petname).Get();
    NGameX::AdventureScreen* advScreen = dynamic_cast<NGameX::AdventureScreen*>(pWorld->GetIAdventureScreen());
    advScreen->AddToInventory( player_it->playerID, petid );
    spawner->playerInfo.inventory.push_back( petid );
  }

  void ApplyCustomTalentSet( const NDb::Ptr<NDb::TalentsSet>& talentSet, NWorld::PFWorld* pWorld, const NCore::TPlayersStartInfo::const_iterator& player_it, const TTeamSpawnInfo::iterator& spawner )
  {
    uint id = 1;
    spawner->usePlayerInfoTalentSet = true;
    for ( int i = 0; i < talentSet->levels.size(); i++ )
    {
      for ( int j = 0; j < talentSet->levels[i].talents.size(); j++ )
      {
        if ( IsValid(talentSet->levels[i].talents[j].talent) )
          spawner->playerInfo.talents[id].id = Crc32Checksum().AddString( talentSet->levels[i].talents[j].talent->persistentId.c_str() ).Get();
        else
          spawner->playerInfo.talents[id].id = 0;
        
        NGameX::AdventureScreen* advScreen = dynamic_cast<NGameX::AdventureScreen*>(pWorld->GetIAdventureScreen());
        advScreen->SetTalentInTS( player_it->playerID, id, spawner->playerInfo.talents[id].id );
        id++;
      }
    }
  }

  bool IsValidHeroForTestTalentSet( const string& heroPersistentId )
  {
    vector<string> heroes;
    NStr::SplitString( g_validHeroesForTestTalentSet, &heroes, ' ' );

    struct not_isalnum { bool operator()(char c) { return !isalnum(c); } };

    for ( int i = 0; i < heroes.size(); i++ )
    {
      NStr::TrimInsideIf( heroes[i], not_isalnum() );
      if ( heroPersistentId == heroes[i] )
      {
        return true;
      }
    }
    return false;
  }

  void OverrideHero( uint overrideId, const string& heroSkin, NWorld::PFWorld* pWorld, const NCore::TPlayersStartInfo::const_iterator& player_it, const TTeamSpawnInfo::iterator& spawner )
  {
    NGameX::AdventureScreen* advScreen = dynamic_cast<NGameX::AdventureScreen*>(pWorld->GetIAdventureScreen());
    advScreen->OverrideHeroId( player_it->playerID, overrideId, heroSkin, player_it->nickname );
    spawner->playerInfo.heroId = overrideId;
    spawner->playerInfo.heroSkin = heroSkin;
  }

  string GetRandomHeroSkin( uint heroId, const NDb::AdvMapDescription* advMapDesc, NRandom::RandomGenerator& randGen, NCore::ETeam::Enum teamId )
  {
    const NDb::SessionLogicRoot* pRoot = NDb::SessionRoot::GetRoot()->logicRoot; 
    NI_ASSERT(pRoot, "Force::Calculate: AI Logic Root is NULL");

    NDb::Ptr<NDb::HeroesDB> pHeroes = pRoot->heroes;

    const NDb::Hero * dbHero = NWorld::FindHero( pHeroes, advMapDesc, heroId );
    DebugTrace(" find hero skin for %s (%d)", dbHero->persistentId, heroId);
    NI_VERIFY( dbHero, NStr::StrFmt( "Invalid hero id '0x%0X' assigned to player!", heroId ), return 0 );
    
    NI_VERIFY( teamId != NCore::ETeam::None, "Invalid hero team", return 0 );

    NDb::EHeroRaces currentHeroRace = (teamId == NCore::ETeam::Team1) ? NDb::HERORACES_A : NDb::HERORACES_B;
    if ( randGen.Next( 2 ) == 1 )
    {
      vector<string> availableSkins;
      for(int i=0; i < dbHero->heroSkins.size(); ++i) 
      {
        const NDb::HeroSkin* heroSkin = dbHero->heroSkins[i].GetPtr();
        if ( !heroSkin || 
          currentHeroRace != (heroSkin->heroRace & currentHeroRace) || 
          (!heroSkin->botRoll && !g_useRandomSkins) || 
          !heroSkin->legal )
          continue;

        availableSkins.push_back( heroSkin->persistentId );
      }

      if (!availableSkins.empty())
      {
        int skinIdx = randGen.Next( availableSkins.size() );
        DebugTrace( "get random skin: hero %s, skin %s", dbHero->persistentId.c_str(), availableSkins[skinIdx] );
        return availableSkins[skinIdx];
      }
    }
    
    
    DebugTrace( "no random skin: hero %s", dbHero->persistentId.c_str() );
    
    return "";
  }


  bool SpawnHeroes( NWorld::PFWorld * pWorld, const NDb::AdvMapDescription* advMapDescription, const NCore::TPlayersStartInfo & players, const bool isTutorial, 
        TSpawnInfo* pSpawnInfo, NScene::IScene * pScene, LoadingProgress * progress )
  {
    NI_PROFILE_FUNCTION_MEM;

    MAP_LOADING_SCOPE(pWorld->GetMapLoadingController());
    MAP_LOADING_IP;

    NHPTimer::STime time;
    NHPTimer::GetTime( time );

    NDb::Ptr<NDb::HeroesDB> pHeroes = NDb::SessionRoot::GetRoot()->logicRoot->heroes;

    NI_VERIFY(pWorld,     "Invalid world!",           return false; );
    NI_VERIFY(pSpawnInfo, "Invalid spawn info!",      return false; );
    NI_VERIFY(pHeroes,    "Invalid heroes database!", return false; );

    // collect players and assign them to spawners
    int heroesToSpawn = 0;
    int overrideCnt[] = { 0, 0 };

    for( NCore::TPlayersStartInfo::const_iterator player_it = players.begin(), player_end = players.end(); player_it != player_end; ++player_it)
    {
      MAP_LOADING_IP;

      if( player_it->playerType == NCore::EPlayerType::Invalid )
        continue;

      // check player team
      NI_VERIFY(0 <= player_it->teamID && player_it->teamID < pSpawnInfo->size(), "Invalid team assigned to player!", continue; );

      // find spawn point
      TTeamSpawnInfo & teamInfo = (*pSpawnInfo)[player_it->teamID];

      TTeamSpawnInfo::iterator spawner = teamInfo.begin();
      for( ; spawner != teamInfo.end(); ++spawner )
        if( -1 == spawner->playerId)
          break;
      NI_VERIFY( spawner != teamInfo.end(), "Not enough HeroPlaceholders to spawn all players!", continue );

      MAP_LOADING_IP;

      const NDb::Hero * checkHero = FindHero( pHeroes, advMapDescription, player_it->playerInfo.heroId );
      NI_VERIFY( checkHero, NStr::StrFmt( "Invalid hero id '0x%0X' assigned to player!", player_it->playerInfo.heroId ), continue );

      spawner->playerId = player_it->playerID;
      spawner->playerInfo = player_it->playerInfo;
      spawner->usePlayerInfoTalentSet = player_it->usePlayerInfoTalentSet;

      //NUM_TASK
      //if ( player_it->playerType == NCore::EPlayerType::Computer )
      {
        MAP_LOADING_IP;

        //@iA@: BSV is Adeptus Obfuscaturus
        const int overrideIndex = overrideCnt[player_it->teamID]++;
        const string overrideId = botOverride[player_it->teamID].heroIds[overrideIndex];

        vector<string> pets;
        NStr::SplitString( g_validPets, &pets, ' ' );
        int powVal = 1;
        for ( int i = 0; i < pets.size(); i++ )
        {
          if ( (botOverride[player_it->teamID].pet[overrideIndex] & powVal) == powVal )
            AddPet( pets[i].c_str(), pWorld, player_it, spawner );
          powVal *= 2;
        }

        MAP_LOADING_IP;
        
        if ( g_useTestTalentSet )
        {
          if ( IsValidHeroForTestTalentSet( checkHero->persistentId ) )
          {
            int talentSetIdx = pWorld->GetRndGen()->Next( 11 ); // 0...10
            if ( talentSetIdx > 0 )
            {
              char forceSetName[256];
              sprintf( forceSetName, "Test/Talents/TestSet%d.TALENTSET.xdb", talentSetIdx );
              NDb::Ptr<NDb::TalentsSet> talentSet = NDb::Get<NDb::TalentsSet>( NDb::DBID(forceSetName) );
              if ( IsValid( talentSet ) )
              {
                ApplyCustomTalentSet( talentSet, pWorld, player_it, spawner );
              }
            }
          }
        }

        MAP_LOADING_IP;

        string customTS = botOverride[player_it->teamID].customTS[overrideIndex];
        if ( !customTS.empty() )
        {
          NDb::Ptr<NDb::TalentsSet> talentSet = NDb::Get<NDb::TalentsSet>( NDb::DBID(customTS) );
          if ( IsValid( talentSet ) )
          {
            ApplyCustomTalentSet( talentSet, pWorld, player_it, spawner );
          }
        }

        MAP_LOADING_IP;

        if ( !overrideId.empty() )
        {
          vector<string> heroParams;
          NStr::SplitString( overrideId, &heroParams, ':' );
          const char *pCharOverrideId = heroParams[0].c_str();
          uint overrideId = Crc32Checksum().AddString(pCharOverrideId).Get();

          string heroSkin;
          if ( heroParams.size() > 1 )
            heroSkin = heroParams[1];

          DebugTrace( "Hero skin: %s", heroSkin.c_str() );
          const NDb::Hero * overrideHero = FindHero( pHeroes, advMapDescription, overrideId );
          if ( overrideHero )
          {
            OverrideHero( overrideId, heroSkin, pWorld, player_it, spawner );
          }
          else
            NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "\"%s\" is not a valid hero name", pCharOverrideId ) );
        }
      }

      ++heroesToSpawn;
    }
    DebugTrace( "SpawnHeroes:FindPlayers: %2.3f", NHPTimer::GetTimePassedAndUpdateTime( time ) );

    NI_VERIFY(heroesToSpawn, "No valid players to spawn heroes!", return false; );

    DebugTrace( "SpawnHeroes:FindPlace: %2.3f", NHPTimer::GetTimePassedAndUpdateTime( time ) );

    // process spawn
    int heroesSpawned = 0;
    for( TSpawnInfo::const_iterator team_it = pSpawnInfo->begin(), team_end = pSpawnInfo->end(); team_it != team_end; ++team_it )
    {
      MAP_LOADING_IP;

      int inTeamId = 1; // yes, I know :( it`s pretty bad, but I need count heroes starting from 1
      for( TTeamSpawnInfo::const_iterator it = team_it->begin(), end = team_it->end(); it != end; ++it )
      {
        MAP_LOADING_IP;

        if( -1 == it->playerId )
          break; // spawned all heroes for this team

        NWorld::PFBaseHero::SpawnInfo heroSpawnDesc;
        heroSpawnDesc.playerId  = it->playerId;
        heroSpawnDesc.placement = it->placement;
        heroSpawnDesc.inTeamId  = inTeamId++;
        heroSpawnDesc.isClone = false;
        heroSpawnDesc.playerInfo = it->playerInfo;
        heroSpawnDesc.usePlayerInfoTalentSet = it->usePlayerInfoTalentSet;
        heroSpawnDesc.bInitInventory = !isTutorial;

        NHPTimer::GetTime( time );

        const NDb::Hero * hero = FindHero( pHeroes, advMapDescription, it->playerInfo.heroId );
        NI_ASSERT( hero, "" );

        /*
        IM: убрал прелоад геро€, т.к. тут он не нужен - все случаетс€ чуть позже при создании. ≈сли будут проблемы, вернуть.
        int precacheDepth = G_GetPrechacheSessionData() ? 20 : 0;
        heroSpawnDesc.pHero NDb::Precache<NDb::BaseHero>( hero->GetDBID(), precacheDepth );
        DebugTrace( "SpawnHeroes:Precache:%d: %2.3f", heroSpawnDesc.playerId, NHPTimer::GetTimePassedAndUpdateTime( time ) );
        */
        heroSpawnDesc.pHero = hero;

        

#ifndef VISUAL_CUTTED

//         CPtr<NWorld::PFPlayer> player = pWorld->GetPlayer( heroSpawnDesc.playerId );
// 
//         if ( IsValid( player ) )
//           PreloadHero( heroSpawnDesc.pHero, pWorld, player->GetTeamID() );
//         DebugTrace( "SpawnHeroes:PreloadHero:%d: %2.3f", heroSpawnDesc.playerId, NHPTimer::GetTimePassedAndUpdateTime( time ) );
#endif
        CreateHero( pWorld, heroSpawnDesc );
        DebugTrace( "SpawnHeroes:CreateHero:%d: %2.3f", heroSpawnDesc.playerId, NHPTimer::GetTimePassedAndUpdateTime( time ) );

        if ( players.size() )
          progress->SetPartialProgress( NWorld::EMapLoadStages::Heroes, ( ++heroesSpawned ) / (float)players.size() );
      }
    }

    progress->SetPartialProgress( NWorld::EMapLoadStages::Heroes, 1.0f );

    return true;
  }
} //namespace NWorld

REGISTER_DEV_VAR( "team0_player0_heroid", botOverride[0].heroIds[0], STORAGE_NONE )
REGISTER_DEV_VAR( "team0_player1_heroid", botOverride[0].heroIds[1], STORAGE_NONE )
REGISTER_DEV_VAR( "team0_player2_heroid", botOverride[0].heroIds[2], STORAGE_NONE )
REGISTER_DEV_VAR( "team0_player3_heroid", botOverride[0].heroIds[3], STORAGE_NONE )
REGISTER_DEV_VAR( "team0_player4_heroid", botOverride[0].heroIds[4], STORAGE_NONE )
REGISTER_DEV_VAR( "team1_player0_heroid", botOverride[1].heroIds[0], STORAGE_NONE )
REGISTER_DEV_VAR( "team1_player1_heroid", botOverride[1].heroIds[1], STORAGE_NONE )
REGISTER_DEV_VAR( "team1_player2_heroid", botOverride[1].heroIds[2], STORAGE_NONE )
REGISTER_DEV_VAR( "team1_player3_heroid", botOverride[1].heroIds[3], STORAGE_NONE )
REGISTER_DEV_VAR( "team1_player4_heroid", botOverride[1].heroIds[4], STORAGE_NONE )

REGISTER_DEV_VAR( "team0_player0_pet", botOverride[0].pet[0], STORAGE_NONE )
REGISTER_DEV_VAR( "team0_player1_pet", botOverride[0].pet[1], STORAGE_NONE )
REGISTER_DEV_VAR( "team0_player2_pet", botOverride[0].pet[2], STORAGE_NONE )
REGISTER_DEV_VAR( "team0_player3_pet", botOverride[0].pet[3], STORAGE_NONE )
REGISTER_DEV_VAR( "team0_player4_pet", botOverride[0].pet[4], STORAGE_NONE )
REGISTER_DEV_VAR( "team1_player0_pet", botOverride[1].pet[0], STORAGE_NONE )
REGISTER_DEV_VAR( "team1_player1_pet", botOverride[1].pet[1], STORAGE_NONE )
REGISTER_DEV_VAR( "team1_player2_pet", botOverride[1].pet[2], STORAGE_NONE )
REGISTER_DEV_VAR( "team1_player3_pet", botOverride[1].pet[3], STORAGE_NONE )
REGISTER_DEV_VAR( "team1_player4_pet", botOverride[1].pet[4], STORAGE_NONE )

REGISTER_DEV_VAR( "team0_player0_talentset", botOverride[0].customTS[0], STORAGE_NONE )
REGISTER_DEV_VAR( "team0_player1_talentset", botOverride[0].customTS[1], STORAGE_NONE )
REGISTER_DEV_VAR( "team0_player2_talentset", botOverride[0].customTS[2], STORAGE_NONE )
REGISTER_DEV_VAR( "team0_player3_talentset", botOverride[0].customTS[3], STORAGE_NONE )
REGISTER_DEV_VAR( "team0_player4_talentset", botOverride[0].customTS[4], STORAGE_NONE )
REGISTER_DEV_VAR( "team1_player0_talentset", botOverride[1].customTS[0], STORAGE_NONE )
REGISTER_DEV_VAR( "team1_player1_talentset", botOverride[1].customTS[1], STORAGE_NONE )
REGISTER_DEV_VAR( "team1_player2_talentset", botOverride[1].customTS[2], STORAGE_NONE )
REGISTER_DEV_VAR( "team1_player3_talentset", botOverride[1].customTS[3], STORAGE_NONE )
REGISTER_DEV_VAR( "team1_player4_talentset", botOverride[1].customTS[4], STORAGE_NONE )
