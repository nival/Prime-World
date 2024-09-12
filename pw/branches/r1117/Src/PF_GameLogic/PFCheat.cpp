#include "stdafx.h"

#include "../System/DebugTraceDumper.h"

#include "AdventureScreen.h"
#include "PFWorld.h"
#include "PFEaselPlayer.h"
#include "PFMaleHero.h"
#include "PFBaseUnit.h"
#include "PFBaseSpawner.h"
#include "PFConsumable.h"
#include "PFUniTarget.h"
#include "PFLogicDebug.h"
#include "PFGameLogicLog.h"
#include "PFRoadFlagpole.h"
#include "PFTalent.h"
#include "PFWorldNatureMap.h"
#include "ValueWithModifiers.hpp"
#include "Core/WorldCommand.h"

#include "Core/CoreFSM.h"
#include "System/Updater.h"
#include "System/StrProc.h"

#include "ForceCalc.h"

#include "HeroActions.h"
#include "AdventureScreenEvents.h"
#include "AdventureScreenLogic.h"
#include "AdventureFlashInterface.h"
#include "TeamInfoNew.h"

#include "DBHeroesList.h"
#include "DBHeroRanks.h"

#include "PFStatistics.h"
#include "PFCheat.h"

#include "SessionEventType.h"
#include "HeroRankCalculator.h"

#include "libdb/DbResourceCache.h"
#include "PFAIContainer.h"
#include "PFAchievement.h"
#include "FinalStatisticsController.h"

#include "PFMainBuilding.h"


#ifndef _SHIPPING


namespace
{

typedef bool (*CheatCallback)(const char *name, const vector<wstring> &params, const NGameX::CheatData& data);

struct CheatDesc
{
  CheatDesc() : callback(0), notifyStatistics(true) {}
  explicit CheatDesc(CheatCallback callback_, bool _notifyStatistics) : callback(callback_), notifyStatistics(_notifyStatistics) {}
  CheatCallback callback;
  bool notifyStatistics;
};

typedef hash_map<string, CheatDesc> TCheats;
TCheats &GetCheats()
{
  static TCheats cheats;
  return cheats;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool RegisterCmd(const string &szID, CheatCallback pHandler, bool notifyStatistics)
{
  if (GetCheats().find( szID ) != GetCheats().end())
    return false;

  GetCheats()[szID] = CheatDesc(pHandler, notifyStatistics);
  return true;
}

} // noname namespace

#define REGISTER_CHEAT_CMD(command, callback)               \
REGISTER_DEV_CMD(command, NGameX::CheatCommandProxy);       \
static struct SRegisterGheatCommand_##command               \
{                                                           \
  SRegisterGheatCommand_##command##()                       \
  {                                                         \
    RegisterCmd( #command, callback, true );                      \
  }                                                         \
} registerCheatCommand_##command##;

#define REGISTER_DEVCHEAT_CMD(command, callback)            \
REGISTER_DEV_CMD(command, NGameX::CheatCommandProxy);       \
static struct SRegisterGheatCommand_##command               \
{                                                           \
  SRegisterGheatCommand_##command##()                       \
  {                                                         \
    RegisterCmd( #command, callback, false );               \
  }                                                         \
} registerCheatCommand_##command##;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace NGameX
{

DEFINE_3_PARAM_CMD(0x11629400, CmdCheat, string, cheatName, vector<wstring>, params, CheatData, data);

bool checkPlayerID ( int ID )
{
  if ( AdventureScreen* pAdvScreen = AdventureScreen::Instance() )
    if ( NWorld::PFWorld* pWorld = pAdvScreen->GetWorld() )
    {
      int cnt = pWorld->GetPlayersCount();

      if ((ID >= 0) && (ID < cnt))
        if ( NWorld::PFPlayer* pPlayer = pWorld->GetPlayer(ID) )
          if ( NWorld::PFBaseHero* pHero = pPlayer->GetHero() )
            return true;
    }

    return false;
}

// extract hero from last param if possible
bool commandStart(string usageMsg, int maxParams, const vector<wstring> &params, CPtr<NWorld::PFBaseUnit> &pUnit)
{
  if ((params.size() != maxParams - 1) && (params.size() != maxParams))
  {
    systemLog( NLogg::LEVEL_MESSAGE ) << usageMsg << endl;
    return false;
  }

  if (params.size() == maxParams)
  {
    int playerID;
    playerID = (int)NGlobal::VariantValue( params[maxParams-1] ).GetFloat();
    if (!checkPlayerID(playerID))
    {
      systemLog( NLogg::LEVEL_MESSAGE ) << "wrong player ID: " << playerID << endl;
      return false;
    }
    if ( AdventureScreen* pAdvScreen = AdventureScreen::Instance() )
      if ( NWorld::PFWorld* pWorld = pAdvScreen->GetWorld() )
        if ( NWorld::PFPlayer* pPlayer = pWorld->GetPlayer(playerID) )
          if ( !(pUnit = pPlayer->GetHero()) )
            return false;
  }

  if (!IsUnitValid(pUnit))
    return false;

  return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static bool HeroAddGold( const char *name, const vector<wstring> &params, const CheatData& data )
{
  CPtr<NWorld::PFBaseUnit> pUnit(data.selectedObject);

  if (!commandStart(string("usage: ") + name + " gold [player_ID]", 2, params, pUnit))
    return false;

  float gold = NGlobal::VariantValue( params[0] ).GetFloat();
  if (NWorld::PFBaseHero* pHero = dynamic_cast<NWorld::PFBaseHero*>(pUnit.GetPtr()))
  {
    pHero->AddGold(gold);
    return true;
  }

  return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static bool HeroActivateAllTalents( const char *name, const vector<wstring> &params, const CheatData& data )
{
  CPtr<NWorld::PFBaseUnit> pUnit(data.selectedObject);

  if (!commandStart(string("usage: ") + name + " [player_ID]", 1, params, pUnit))
    return false;

  if (NWorld::PFBaseMaleHero* pHero = dynamic_cast<NWorld::PFBaseMaleHero*>(pUnit.GetPtr()))
  {
    const int numLevels = NDb::KnownEnum<NDb::ETalentLevel>::sizeOf;
    const int numSlots  = NDb::KnownEnum<NDb::ETalentSlot>::sizeOf;

    for (int level = 0; level < numLevels; ++level)
    {
      for (int slot = 0; slot < numSlots; ++slot)
      {
        NWorld::PFTalent* const talent = pHero->GetTalent(level, slot);

        if (!talent || talent->IsActivated())
          continue;

        pHero->AddGold(talent->GetMoneyCost());
        pHero->ActivateTalent(level, slot);
      }
    }

    return true;
  }

  return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static bool ReceiveArtifact( const char *name, const vector<wstring> &params, const CheatData& data )
{
  // Command not work: we have no consumablesDB!
  NI_ALWAYS_ASSERT("This cheat not work!");
  return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static bool UseConsumable( const char* name, const vector<wstring>& params, const CheatData& data )
{
  CPtr<NWorld::PFBaseUnit> pUnit( data.selectedObject );

  if ( params.size() != 1 )
  {
    systemLog( NLogg::LEVEL_MESSAGE ) << "usage: " << name << " xdb_path" << endl;
    return true;
  }

  if ( pUnit->DbUnitDesc()->GetObjectTypeID() == NDb::Hero::typeId )
  {
    NWorld::PFBaseHero* pHero = static_cast<NWorld::PFBaseHero*>( pUnit.GetPtr() );

    string path;
    NStr::UnicodeToUTF8( &path, params[0] );
    NDb::Ptr<NDb::Consumable> pDbConsumable = NDb::Get<NDb::Consumable>( NDb::DBID( path ) );

    CObj<NWorld::PFConsumable> pConsumable = new NWorld::PFConsumable( pHero->GetWorld(), pHero, pDbConsumable );

    NWorld::Target target( data.pickedPosition );
    if ( IsUnitValid( data.pickedObject ) )
    {
      target = NWorld::Target( data.pickedObject );
    }

    pHero->UseConsumable( pConsumable, target, pHero->IsLocal() );
    return true;
  }

  return false;
}

static bool TakeConsumable( const char* name, const vector<wstring>& params, const CheatData& data )
{
  CPtr<NWorld::PFBaseUnit> pUnit( data.selectedObject );

  if ( params.size() != 1 )
  {
    systemLog( NLogg::LEVEL_MESSAGE ) << "usage: " << name << " xdb_path" << endl;
    return true;
  }

  if ( pUnit->DbUnitDesc()->GetObjectTypeID() == NDb::Hero::typeId )
  {
    NWorld::PFBaseHero* pHero = static_cast<NWorld::PFBaseHero*>( pUnit.GetPtr() );

    string path;
    NStr::UnicodeToUTF8( &path, params[0] );
    NDb::Ptr<NDb::Consumable> pDbConsumable = NDb::Get<NDb::Consumable>( NDb::DBID( path ) );

    pHero->TakeConsumable( pDbConsumable, 1 );
    return true;
  }

  return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static bool ResfreshCooldown( const char *name, const vector<wstring> &params, const CheatData& data )
{
  CPtr<NWorld::PFBaseUnit> pUnit( data.selectedObject );

  if (!commandStart(string("usage: ") + name + " [player_ID]", 1, params, pUnit))
    return false;

  if ( NWorld::PFBaseHero* pHero = dynamic_cast<NWorld::PFBaseHero*>(pUnit.GetPtr()) )
  {
    const NWorld::DropCooldownParams dropCdParams( NDb::ABILITYIDFLAGS_ALL );
    pHero->DropCooldowns( dropCdParams );

    if ( pHero == data.cheater )
    {
      pHero->DropImpulsesCooldowns();
    }

    return true;
  }

  return false;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static bool DebugKillUnit( const char *name, const vector<wstring> &params, const CheatData& data )
{  
  if ( AdventureScreen* pAdvScreen = AdventureScreen::Instance() )
  {
    if ( IsUnitValid( data.pickedObject ) )
    {
      CPtr<NWorld::PFBaseUnit> pKiller(data.pickedObject);
      if ( NWorld::PFWorld* pWorld = pAdvScreen->GetWorld() )
      {
        if( NWorld::PFPlayer* pPlayer = pWorld->GetPlayer(data.localPlayerId) )
        {
          pKiller = pPlayer->GetHero();
        }
      }

      data.pickedObject->KillUnit(pKiller);
      return true;
    }
  }
  return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static bool TeleportUnit( const char *name, const vector<wstring> &params, const CheatData& data )
{
  if ( AdventureScreen* pAdvScreen = AdventureScreen::Instance() )
  {
    if ( NWorld::PFBaseUnit *pUnit = data.selectedObject)
    {
      CVec3 const& target = data.pickedPosition;
      
      NWorld::PFBaseMovingUnit* pMovingUnit = dynamic_cast<NWorld::PFBaseMovingUnit*>(pUnit);
      if( pMovingUnit && false == pMovingUnit->IsMounted() && false == pMovingUnit->IsDead() )
      {
				pMovingUnit->PlaceUnitWithPush(target.AsVec2D(), 30.0f); // pMovingUnit->TeleportTo(target);
        pMovingUnit->DropTarget();
        pMovingUnit->DropStates();
        pMovingUnit->StopAttackingMe();

        struct Predicat
        {
          bool operator () ( NWorld::PFLogicObject const& unit ) const { return true; }
        }predic;

        struct DropStatesFunctor
        {
          void operator () ( NWorld::PFBaseUnit& arg ) { if( arg.HasQueuedStates() ) arg.DropStates(); }
        }dropStates;

        pMovingUnit->ForAllAttackers( predic, dropStates );
        return true;
      }
    }
  }

  return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static bool HeroChange( const char *name, const vector<wstring> &params, const CheatData& data )
{
  if ((params.size() < 1) || (params.size() > 2))
  {
    systemLog( NLogg::LEVEL_MESSAGE ) << "usage: " << name << " hero_type_ID [player_ID]" << endl;
    return true;
  }

  int playerID;
  int heroTypeID;
  heroTypeID = (int)NGlobal::VariantValue( params[0] ).GetFloat();

  if (params.size() == 1)
    playerID = data.localPlayerId;
  else
    playerID = (int)NGlobal::VariantValue( params[1] ).GetFloat();  

  if (!checkPlayerID(playerID))
  {
    systemLog( NLogg::LEVEL_MESSAGE ) << "wrong player ID: " << playerID << endl;
    return true;
  }

  NDb::Ptr<NDb::HeroesDB> pHeroes = NDb::Get<NDb::HeroesDB>( NDb::DBID( "Heroes/_.HRDB.xdb" ) );
  NI_VERIFY( pHeroes, "Invalid heroes database", return false; );

  NI_VERIFY( 0 <= heroTypeID && heroTypeID < pHeroes->heroes.size(), "Invalid hero ID!", return false; );

  if ( AdventureScreen* pAdvScreen = AdventureScreen::Instance() )
  {
    if ( NWorld::PFWorld* pWorld = pAdvScreen->GetWorld() )
    {
      if( NWorld::PFPlayer* pPlayer = pWorld->GetPlayer(playerID) )
      {
        NWorld::PFBaseHero::SpawnInfo info;
        info.pHero     = pHeroes->heroes[heroTypeID];
        info.playerId  = static_cast<NDb::EPlayerID>(playerID);
        info.placement = Placement(data.pickedPosition, QNULL, CVec3(1.0f, 1.0f, 1.0f) );
				info.isClone   = false;

        if ( NWorld::PFBaseHero* pHero = pPlayer->GetHero() )
          pHero->DebugDie();

        pPlayer->DetachHero();
        NWorld::CreateHero(pWorld, info);      
      }      
    }
  }

  return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static bool HeroSetActive( const char *name, const vector<wstring> &params, const CheatData& data )
{
  AdventureScreen* pAdvScreen = AdventureScreen::Instance();
	if (!pAdvScreen)
		return false;

	NWorld::PFWorld* pWorld = pAdvScreen->GetWorld();
	if (!pWorld)
		return false;

	NWorld::PFBaseUnit *pUnit = data.selectedObject;
	if (!pUnit)
		return false;

  CPtr<NWorld::PFPlayer> pPlayer1, pPlayer2;
  CPtr<NWorld::PFBaseHero> pHero1, pHero2;

  pPlayer1 = pWorld->GetPlayer(data.localPlayerId);
  pHero1   = pPlayer1->GetHero();

  pHero2 = dynamic_cast<NWorld::PFBaseHero*>(pUnit);
	if (!pHero2)
		return false;

  pPlayer2 = pHero2->GetPlayer();
  if(!pPlayer2->IsBot())
  {
    systemLog( NLogg::LEVEL_MESSAGE ) << "Activating non-bot heroes not allowed!" << endl;
    return false;
  }

  // Switch user IDs, otheriwse we will control a bot with ID == -1
  int id1 = pPlayer1->GetUserID();
  int id2 = pPlayer2->GetUserID();
  pPlayer1->SetUserID(id2);
  pPlayer2->SetUserID(id1);

  NWorld::PFAIContainer* container = pWorld->GetAIContainer();
  if ( IsValid( container ) )
  {
    container->Remove(pHero2);
  }

  if (pPlayer1 != 0 && pPlayer2 != 0 && pPlayer1 != pPlayer2)
  {
    bool needLocal = false;
    if ( data.localPlayerId == pAdvScreen->GetPlayer()->GetPlayerID() )
    {
      needLocal = true;
      pAdvScreen->SetActivePlayer( pPlayer2 );
    }
    
    CDynamicCast<NWorld::PFEaselPlayer> easelPlayer2 = pHero2;
    if ( IsValid(easelPlayer2) && easelPlayer2->GetMinigames() )
    {
      easelPlayer2->GetMinigames()->SetLocal( needLocal );
      easelPlayer2->GetMinigames()->ReinitGames();
    }

    CDynamicCast<NWorld::PFEaselPlayer> easelPlayer1 = pHero1;
    if ( IsValid(easelPlayer1) && easelPlayer1->GetMinigames() )
    {
      easelPlayer1->GetMinigames()->SetLocal( false );
      easelPlayer1->GetMinigames()->ReinitGames();
    }

    return true;
  }

  return false;
}

static bool UnitStat( const char *name, const vector<wstring> &params, const CheatData& data )
{
  if ((params.size() < 1) || (params.size() > 3))
  {
    string stats;

    for (int i = 0; i < NDb::KnownEnum<NDb::EStat>::SizeOf(); ++i)
    {
      stats.append( NDb::KnownEnum<NDb::EStat>::ToString( NDb::EStat(i) ) );
      stats.append( " = " );
      stats.append( NStr::IntToStr( i ) );
      stats.append( "\n" );
    }

    systemLog( NLogg::LEVEL_MESSAGE ) << "usage: " << name << " stat [new_value] [player_ID]\n"
      << "where stat may be:\n" << stats;

    return true;
  }

  // Get value
  string buf;
  NStr::UnicodeToUTF8(&buf, params[0]);
  NDb::EStat stat = NDb::KnownEnum<NDb::EStat>::ToEnum(buf);

  CPtr<NWorld::PFBaseUnit> pUnit(data.selectedObject);

  if (params.size() == 3)
  {
    int playerID;
    playerID = (int)NGlobal::VariantValue( params[2] ).GetFloat();
    if (!checkPlayerID(playerID))
    {
      systemLog( NLogg::LEVEL_MESSAGE ) << "wrong player ID: " << playerID << endl;
      return true;
    }
    if ( AdventureScreen* pAdvScreen = AdventureScreen::Instance() )
      if ( NWorld::PFWorld* pWorld = pAdvScreen->GetWorld() )
        if ( NWorld::PFPlayer* pPlayer = pWorld->GetPlayer(playerID) )
          if ( !(pUnit = pPlayer->GetHero()) )
            return true;
  }

  if (!IsUnitValid(pUnit))
    return true;

  // 
  if (params.size() == 1)
  {
    systemLog( NLogg::LEVEL_MESSAGE ) << "stat: " << params[0] << "   value: " << pUnit->GetStatValue(stat) << endl;
  }
  else
  {
    float newValue = NGlobal::VariantValue(params[1]).GetFloat();
    systemLog( NLogg::LEVEL_MESSAGE ) << "change unit stat '" << params[0] << "' from value " << pUnit->GetStatValue(stat) <<" to base value " << newValue << endl;
    NWorld::StatValueWithModifiers *unitValue(pUnit->GetStat(stat));
    if (unitValue)
    {
      unitValue->SetValue(newValue);
    }
  }

  return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static bool GlobalStatScale( const char *name, const vector<wstring> &params, const CheatData& data )
{
  if (params.size() != 2)
  {
    systemLog( NLogg::LEVEL_MESSAGE ) << "usage: " << name << " stat scale" << endl;
    return true;
  }

  AdventureScreen* pAdvScreen = AdventureScreen::Instance();
	if (!pAdvScreen)
		return false;

	NWorld::PFWorld* pWorld = pAdvScreen->GetWorld();
	if (!pWorld)
		return false;

  // Get value
  string buf;
  NStr::UnicodeToUTF8(&buf, params[0]);
  NDb::EStat stat = NDb::KnownEnum<NDb::EStat>::ToEnum(buf);

  float scale = NGlobal::VariantValue(params[1]).GetFloat();

  if (scale <= 0)
  {
    systemLog( NLogg::LEVEL_MESSAGE ) << "command: " << name << " used with wrong value!" << endl;
    return true;
  }

  struct UnitStatModify : NonCopyable
  {
    NDb::EStat stat;
    float statMult;

    UnitStatModify(float _statMult, NDb::EStat _stat) : statMult(_statMult) , stat(_stat) {}

    void operator()( PF_Core::WorldObjectBase &baseUnit )
	  {
      // Apply if unit
      CDynamicCast<NWorld::PFBaseUnit> pUnit = &baseUnit;
      if (IsValid(pUnit))
      {
        NWorld::ValueWithModifiers *unitValue(pUnit->GetStat(stat));
        if (unitValue)
        {
          unitValue->AddModifier(statMult, 0.0f, PF_Core::WORLD_ID, true);
        }
      }
      else
      {
        // Apply if spawner
        CDynamicCast<NWorld::PFBaseSpawner> pSpawner = &baseUnit;
        if (IsValid(pSpawner))
        {
          pSpawner->AddStatModifier(stat, statMult, true);
        }
      }
    }
  } unitStatModify(scale, stat);

  // Go through all world objects and apply global stat modifier
  pWorld->ForAllObjectsBeingStepped(unitStatModify);

  return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static bool HeroForceCalculate( const char *name, const vector<wstring> &params, const CheatData& data )
{
  if ( params.size() > 1 )
  {
    systemLog( NLogg::LEVEL_MESSAGE ) << "usage: " << name << " [new budget value]" << endl;
    return true;
  }

  NWorld::PFBaseMaleHero* pHero = dynamic_cast<NWorld::PFBaseMaleHero*>(data.selectedObject.GetPtr());

  if ( !pHero )
  {
    return true;
  }
  
  // TODO: use from UnitLogicParameters
  vector<float> defaultStatValues(NDb::KnownEnum<NDb::EStat>::SizeOf(), 0.0f);
  defaultStatValues[NDb::STAT_LIFE] = 600.0f;
  defaultStatValues[NDb::STAT_ENERGY] = 600.0f;
  defaultStatValues[NDb::STAT_STRENGTH] = 50.0f;
  defaultStatValues[NDb::STAT_INTELLECT] = 50.0f;
  defaultStatValues[NDb::STAT_STAMINA] = 50.0f;
  defaultStatValues[NDb::STAT_WILL] = 50.0f;
  defaultStatValues[NDb::STAT_DEXTERITY] = 50.0f;
  defaultStatValues[NDb::STAT_ATTACKSPEED] = 50.0f;
  defaultStatValues[NDb::STAT_MOVESPEED] = 50.0f;

  NDb::StatsContainer const* dbHeroStats = pHero->GetDbHero()->stats.GetPtr();
  NDb::AILogicParameters const* dbAILogicParams = &AdventureScreen::Instance()->GetWorld()->GetAIWorld()->GetAIParameters();
  NDb::ForceParameters const* dbForceParams = dbAILogicParams->forceParameters.GetPtr();
  vector<NDb::StatBudget> const& statBudget = dbAILogicParams->statsBudget->stats;

  // Talents calculations
  struct DevPointsCalc : NonCopyable
  {
    DevPointsCalc()
    {
      levelDevPoints.resize( NWorld::PFTalentsSet::LEVELS_COUNT, 0 );
    }

    void operator()( NWorld::PFTalent* pTalent, int level, int slot )
    {
      levelDevPoints[level] += pTalent->GetDevPoints();
    }

    vector<int> levelDevPoints;
  } devpointsCalc;

  struct TalentsForceCalc : NonCopyable
  {
    TalentsForceCalc( NDb::AILogicParameters const* dbAILogicParams_, int maxLevel_, vector<int> const& levelDevPoints_ )
      : dbAILogicParams( dbAILogicParams_ )
      , dbForceParams(dbAILogicParams->forceParameters.GetPtr())
      , totalTalentForce(0.0f)
      , totalTalentBudget(0.0f)
      , totalBaseBonusBudget(0.0f)
      , heroLevel(0)
      , maxHeroLevel(maxLevel_)
      , levelDevPoints(levelDevPoints_)
    {
      talentsForce.resize(NWorld::PFTalentsSet::LEVELS_COUNT, 0.0f);
      talentsBudget.resize(NWorld::PFTalentsSet::LEVELS_COUNT, 0.0f);
    }

    void operator()( NWorld::PFTalent* pTalent, int level, int slot )
    {
      float talBudget = pTalent->GetTalentDesc()->budget;
      bool isClassTalent = pTalent->GetTalentDesc()->rarity == NDb::TALENTRARITY_CLASS;

      float talForce = 0;
      
      if (talBudget < 0)
        talBudget = NWorld::PFTalent::CalcBudget(dbAILogicParams, pTalent->GetRefineRate(), level, pTalent->GetTalentDesc()->rarity);
      
      float modifierPercent = isClassTalent ? dbForceParams->classTalentLevelForceModifiers[level] : dbForceParams->talentLevelForceModifiers[level];
      talForce = talBudget / (1.0f + modifierPercent * 0.01f ) +  dbForceParams->talentRarityForceSummand[pTalent->GetTalentDesc()->rarity];;

      if ( pTalent->IsTalentBought() )
      {
        if ( !isClassTalent  )
        {
          talentsBudget[level] += talBudget;
          totalTalentBudget += talBudget;
        }
        //if ( heroLevel < maxHeroLevel )
        //{
        //  int points = min( maxHeroLevel - heroLevel, pTalent->GetDevPoints() );
          totalBaseBonusBudget += pTalent->GetDevPoints() * dbForceParams->defaultStatBonus * dbForceParams->talentLevelBonusPercent[level] / levelDevPoints[level] * 0.01f;
        //  heroLevel += points;
        //}
      }

      
      talentsForce[level] += talForce;
      totalTalentForce += talForce;
    }

    vector<float> talentsForce;
    vector<float> talentsBudget;
    float totalTalentForce;
    float totalTalentBudget;
    float totalBaseBonusBudget;
    NDb::AILogicParameters const* dbAILogicParams;
    NDb::ForceParameters const* dbForceParams;
    int heroLevel;
    const int maxHeroLevel;
    vector<int> const& levelDevPoints;
  } talentsForceCalc( dbAILogicParams, AdventureScreen::Instance()->GetWorld()->GetAIWorld()->GetMaxHeroLevel(), devpointsCalc.levelDevPoints );

  pHero->ForAllTalents( devpointsCalc );
  pHero->ForAllTalents( talentsForceCalc );

  // Hero stats calculation
  float baseBudget = 0.0f;
  float incBudget = 0.0f;
  vector<float> incBudgets(NDb::KnownEnum<NDb::EStat>::SizeOf(), 0.0f);
  vector<float> plainStatBudgets(NDb::KnownEnum<NDb::EStat>::SizeOf(), 0.0f);
  for ( vector<NDb::StatBudget>::const_iterator it = statBudget.begin(); it != statBudget.end(); ++it )
  {
    float value = 0.0f;
    float increment = 0.0f;
    NDb::EStat stat = it->stat;
    float budget = it->budget;
    plainStatBudgets[stat] = budget;
    if ( !it->upgradesWithForce )
      continue;

    for ( vector<NDb::UnitStat>::const_iterator itStat = dbHeroStats->stats.begin(); itStat != dbHeroStats->stats.end(); ++itStat )
    {
      if ( itStat->statId == stat )
      {
        // WARNING! It is assumed that ONLY number tokens are used in hero stat's formula!
        // Otherwise crash is guaranteed
        value = itStat->value( NULL, NULL, NULL );
        increment = itStat->increment( NULL, NULL, NULL );
        break;
      }
    }

    float valueDiff = value - defaultStatValues[stat];
    baseBudget += valueDiff / budget;
    incBudget += increment / budget;
    incBudgets[stat] = increment / budget;
  }
  float baseForce = dbForceParams->baseHeroForce;
  float levelBudget = incBudget * pHero->GetNaftaLevel();

  // Persistent calculation
  float masteryBudget = 0.0f;
  {
    for (unsigned int i = 0; i < pHero->GetPersistentStats().capacity(); ++i)
    {
      if ( plainStatBudgets[ i ] > 0.0f )
        masteryBudget += pHero->GetPersistentStats()[i] / plainStatBudgets[ i ];
    }
  }
  
  // Summary
  float summaryBudget = talentsForceCalc.totalTalentBudget + talentsForceCalc.totalBaseBonusBudget + baseBudget + levelBudget + masteryBudget;
  float summaryForce = talentsForceCalc.totalTalentForce + baseForce /*+ masteryBudget*/; // see http://SITE

  // Cheat calculation
  float& cheatBudget = pHero->GetCheatBudgetRef();
  if ( params.size() == 1 )
  {
    cheatBudget = NGlobal::VariantValue( params[0] ).GetFloat() - ( summaryBudget - baseBudget );
    for ( vector<NDb::StatBudget>::const_iterator it = statBudget.begin(); it != statBudget.end(); ++it )
    {
      if ( !it->upgradesWithForce )
        continue;

      NDb::EStat stat = it->stat;
      float addValue = cheatBudget * incBudgets[stat] / incBudget * plainStatBudgets[stat];
      NWorld::StatValueWithModifiers *unitStatValue( pHero->GetStat( stat ) );
      if ( unitStatValue )
      {
        unitStatValue->SetCheatModifier( addValue );

        if ( stat == NDb::STAT_ENERGY )
          pHero->RecalculateManaCostModifier();
      }
    }
  }

  // Output
  for ( int level = 0, levels = NDb::KnownEnum<NDb::ETalentLevel>::SizeOf(); level < levels; ++level )
  {
    systemLog( NLogg::LEVEL_MESSAGE ) << NStr::StrFmt("Tier %d   : budget = %-6.0f, force = %-6.0f", level + 1, talentsForceCalc.talentsBudget[level], talentsForceCalc.talentsForce[level] ) << endl;
  }
  systemLog( NLogg::LEVEL_MESSAGE ) << NStr::StrFmt("Talents  : budget = %-6.0f, force = %-6.0f", talentsForceCalc.totalTalentBudget, talentsForceCalc.totalTalentForce ) << endl;
  systemLog( NLogg::LEVEL_MESSAGE ) << NStr::StrFmt("Base     : budget = %-6.1f, force = %-6.1f", baseBudget,    baseForce ) << endl;
  systemLog( NLogg::LEVEL_MESSAGE ) << NStr::StrFmt("Level    : budget = %-6.1f", levelBudget ) << endl;
  systemLog( NLogg::LEVEL_MESSAGE ) << NStr::StrFmt("BaseBonus: budget = %-6.1f", talentsForceCalc.totalBaseBonusBudget ) << endl;
  systemLog( NLogg::LEVEL_MESSAGE ) << NStr::StrFmt("Mastery  : budget = %-6.0f, force = %-6.0f", masteryBudget, 0/*masteryBudget*/ ) << endl;
  systemLog( NLogg::LEVEL_MESSAGE ) << NStr::StrFmt("Cheat    : budget = %-6.0f", cheatBudget ) << endl;
  systemLog( NLogg::LEVEL_MESSAGE ) << NStr::StrFmt("Summary  : budget = %-6.1f, force = %-6.1f", summaryBudget + cheatBudget, summaryForce ) << endl;

  return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static bool AddHealth( const char *name, const vector<wstring> &params, const CheatData& data )
{
  CPtr<NWorld::PFBaseUnit> pUnit( data.selectedObject );

  if ( !commandStart( string( "usage: " ) + name + " health [player_ID]", 2, params, pUnit ) )
  {
    return false;
  }

  float deltaHealth = NGlobal::VariantValue( params[0] ).GetFloat();
  pUnit->ChangeHealth(deltaHealth);
  return true;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static bool AddMana( const char *name, const vector<wstring> &params, const CheatData& data )
{
  CPtr<NWorld::PFBaseUnit> pUnit(data.selectedObject);

  if ( !commandStart( string( "usage: " ) + name + " mana [player_ID]", 2, params, pUnit ) )
  {
    return false;
  }

  float mana = NGlobal::VariantValue( params[0] ).GetFloat();
  pUnit->ChangeMana(mana);
  return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static bool AddKilledCreeps( const char *name, const vector<wstring> &params, const CheatData& data )
{
  CPtr<NWorld::PFBaseUnit> pUnit(data.selectedObject);
  if (!commandStart(string("usage: ") + name + " number [player_ID]", 2, params, pUnit))
    return false;

  if ( NWorld::PFBaseHero* pHero = dynamic_cast<NWorld::PFBaseMaleHero*>(pUnit.GetPtr()) )
  {
    int numCreeps = NGlobal::VariantValue( params[0] ).GetInt64();    
    
    struct AddCreepsToStat
    {
      AddCreepsToStat(int _numCreep) : numCreeps(_numCreep) {}
      void operator()(NWorld::PFBaseHero &hero)
      {
        NWorld::PFHeroStatistics &stat = *hero.GetHeroStatistics();
        stat.SetNumKillsTotal(max(0, stat.GetNumKillsTotal() + numCreeps));
        stat.SetCreepsKilled(max(0, stat.GetCreepsKilled() + numCreeps));
      }
      int numCreeps;
    } functor(numCreeps);

    AdventureScreen::Instance()->GetWorld()->GetStatistics()->ForAllHeroes(functor);

    return true;
  }
  
  return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static bool AddKilledTowers( const char *name, const vector<wstring> &params, const CheatData& data )
{
  CPtr<NWorld::PFBaseUnit> pUnit(data.selectedObject);
  if (!commandStart(string("usage: ") + name + " number [player_ID]", 2, params, pUnit))
    return false;

  if ( NWorld::PFBaseHero* pHero = dynamic_cast<NWorld::PFBaseMaleHero*>(pUnit.GetPtr()) )
  {
    int numTorrets = NGlobal::VariantValue( params[0] ).GetInt64();    
    NWorld::PFStatistics *pfStat = AdventureScreen::Instance()->GetWorld()->GetStatistics();

    struct AddTowersToStat
    {
      AddTowersToStat(int _numTowers) : numTowers(_numTowers) {}
      void operator()(NWorld::PFBaseHero &hero)
      {
        NWorld::PFHeroStatistics &stat = *hero.GetHeroStatistics();
        stat.SetNumKillsTotal(max(0, stat.GetNumKillsTotal() + numTowers));
        stat.SetNumTowersKilled(numTowers);
      }
      int numTowers;
    } functor(numTorrets);

    pfStat->SetTowersDestroyedCnt(max(0, pfStat->GetTowersDestroyedCnt() + numTorrets));
    pfStat->ForAllHeroes(functor);

    return true;
  }

  return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static bool ResurrectHero( const char *name, const vector<wstring> &params, const CheatData& data )
{
  CPtr<NWorld::PFBaseUnit> pUnit(data.selectedObject);  
  if ( NWorld::PFBaseHero* pHero = IsValid(pUnit) ? dynamic_cast<NWorld::PFBaseHero*>(pUnit.GetPtr()) : NULL)
  {
    pHero->Resurrect();
    return true;
  }

  return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static bool SetHealth( const char *name, const vector<wstring> &params, const CheatData& data )
{
  CPtr<NWorld::PFBaseUnit> pUnit( data.selectedObject );

  if (!commandStart(string("usage: ") + name + " health [player_ID]", 2, params, pUnit))
    return false;

  float health = NGlobal::VariantValue( params[0] ).GetFloat();
  pUnit->SetHealth( health );
  return true;
}

//////////////////////////////////////////////////////////////////////////
static bool SetSkin( const char *name, const vector<wstring> &params, const CheatData& data )
{
  CPtr<NWorld::PFBaseUnit> pUnit(data.selectedObject);
  CPtr<NWorld::PFBaseMaleHero> pHero = IsValid(pUnit) ? dynamic_cast<NWorld::PFBaseMaleHero*>(pUnit.GetPtr()) : NULL;
  NI_VERIFY( pHero, "Target must be an male hero!", return false; );

  if (!commandStart(string("usage: ") + name + " <set_skin skin_id is_animated_avatar> [player_ID]", 3, params, pUnit))
    return false;

  string skinId = NStr::ToMBCS(NGlobal::VariantValue( params[0] ).GetString());
  bool isAnimatedAvatar = NGlobal::VariantValue( params[1] ).GetInt64() != 0;

  bool res = pHero->SetSkin(skinId, true);
  pHero->SetAnimatedAvatar(isAnimatedAvatar);

  if (res)
  {
    const char * texturePath =  pHero->GetUiAvatarImage()? pHero->GetUiAvatarImage()->textureFileName.c_str() : "";

    const NDb::AILogicParameters& aiLogic = AdventureScreen::Instance()->GetWorld()->GetAIWorld()->GetAIParameters();
    Strong<HeroRankCalculator> rankCalculator = new HeroRankCalculator(aiLogic.heroRanks);

    const NDb::Rank & rank = rankCalculator->GetRank(pHero->GetRaiting());

    NDb::EFaction originalFaction = pHero->GetOriginalFaction();

    float raiting = pHero->GetRaiting();

    string flagIcon;
    wstring flagTooltip;

    // TODO: добавить параметр включения/выключения анимированного портрета
    AdventureScreenLogic* advLogic = dynamic_cast<AdventureScreenLogic*>(AdventureScreen::Instance()->GetLogic());
    NI_ASSERT( advLogic, "Can't acquire adventure screen logic" );
    advLogic->GetFlashInterface()->SetHeroIdentity(
      pHero->GetPlayerName(), 
      pHero->GetDescription(), 
      pHero->GetPlayerId(), texturePath, 
      ( pHero->GetZZimaSex() == ZZSEX_MALE ),
      pHero->GetFaction() != advLogic->GetTeamInfo()->GetOurHero()->GetFaction(), 
      pHero->GetPlayer()->IsBot(),
      pHero->GetForce(true), 
      pHero->GetFaction(), 
      originalFaction,
      raiting, 
      rankCalculator->GetRankIcon(originalFaction, rank), 
      rankCalculator->GetRankName(originalFaction, rank),
      false,pHero->GetPartyId(),flagIcon,flagTooltip, isAnimatedAvatar, pHero->GetLeagueIndex(), pHero->GetOwnLeaguePlace(), pHero->GetLeaguePlaces());
  }
  
  return res;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static bool SetRefineRate( const char *name, const vector<wstring> &params, const CheatData& data )
{
  CPtr<NWorld::PFBaseUnit> pUnit(data.selectedObject);
  CPtr<NWorld::PFBaseMaleHero> pHero = IsValid(pUnit) ? dynamic_cast<NWorld::PFBaseMaleHero*>(pUnit.GetPtr()) : NULL;
  NI_VERIFY( pHero, "Target must be an male hero!", return false; );

  if (!commandStart(string("usage: ") + name + " <refine rate value> [player_ID]", 2, params, pUnit))
    return false;

  int refineRate = NGlobal::VariantValue( params[0] ).GetInt64();
  
  struct ChangeRefineRate : NonCopyable
  {
    ChangeRefineRate( NDb::AILogicParameters const* dbAILogicParams_, int newRefineRate_ )
      : dbAILogicParams( dbAILogicParams_ )
      , dbForceParams( dbAILogicParams->forceParameters.GetPtr() )
      , newRefineRate( newRefineRate_ ) {}

    void operator()( NWorld::PFTalent* pTalent, int level, int slot )
    {
      pTalent->SetRefineRate(newRefineRate);
    }
    NDb::AILogicParameters const* dbAILogicParams;
    NDb::ForceParameters const* dbForceParams;
    int newRefineRate;
  } changeRefineRate( &AdventureScreen::Instance()->GetWorld()->GetAIWorld()->GetAIParameters(), refineRate );

  pHero->ForAllTalents(changeRefineRate);
  pHero->SetForce( NWorld::Force::CalculateForce(pHero) );
  
  return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static bool PauseFSM( const char *name, const vector<wstring> &params, const CheatData& data )
{
  CPtr<NWorld::PFBaseUnit> pUnit( data.selectedObject );

  if (!commandStart(string("usage: ") + name + " mode [player_ID]", 2, params, pUnit))
    return false;

  bool pause = NGlobal::VariantValue( params[0] ).GetFloat();
  pUnit->PauseFSM( pause );
  return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static bool GetVar( const char *name, const vector<wstring> &params, const CheatData& data )
{
  CPtr<NWorld::PFBaseUnit> pUnit( data.selectedObject );

  if (params.size() > 1)
  {
    systemLog( NLogg::LEVEL_MESSAGE ) << "usage: " << name << " varName" << endl;
    return true;
  }

  if (params.size() == 1)
  {
    string buf;
    NStr::UnicodeToUTF8(&buf, params[0]);

    systemLog( NLogg::LEVEL_MESSAGE ) << "var: " << params[0] << "   value: " << pUnit->GetVariableValue(buf.c_str()) << endl;
  }
  else
  {
    struct DisplayToLog
    {
      void operator () ( nstl::string &name, NWorld::ValueWithModifiers &var )
      {
        systemLog( NLogg::LEVEL_MESSAGE ) << "var: " << name << "   value: " << var.GetValue() << endl;
      }
    } displayToLog;

    systemLog( NLogg::LEVEL_MESSAGE ) << "unit variables:" << endl;
    pUnit->ForAllVariables( displayToLog );
  }

  return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static bool SetVar( const char *name, const vector<wstring> &params, const CheatData& data )
{
  CPtr<NWorld::PFBaseUnit> pUnit( data.selectedObject );

  if (params.size() != 2)
  {
    systemLog( NLogg::LEVEL_MESSAGE ) << "usage: " << name << " varName value" << endl;
    return true;
  }

  string buf;
  NStr::UnicodeToUTF8(&buf, params[0]);

  float newValue = NGlobal::VariantValue( params[1] ).GetFloat();

  NWorld::ValueWithModifiers* prevVWM = pUnit->GetVariableVWM(buf.c_str());
  float prevBaseValue = prevVWM->GetBaseValue();
  prevVWM->SetBaseValue( newValue );

  systemLog( NLogg::LEVEL_MESSAGE ) << "var: " << params[0] << "   value: " << prevBaseValue << "   changed to: " << newValue << endl;

  return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static bool FindAppl( const char *name, const vector<wstring> &params, const CheatData& data )
{
  CPtr<NWorld::PFBaseUnit> pUnit( data.selectedObject );

  if (params.size() != 1)
  {
    systemLog( NLogg::LEVEL_MESSAGE ) << "usage: " << name << " applName" << endl;
    return true;
  }

  string buf;
  NStr::UnicodeToUTF8(&buf, params[0]);

  if ( pUnit->FindApplicator(buf.c_str(),0,GLOBAL) )
    systemLog( NLogg::LEVEL_MESSAGE ) << "applicator: " << params[0] << "  is applied to unit" << endl;
  else
    systemLog( NLogg::LEVEL_MESSAGE ) << "applicator: " << params[0] << "  is NOT applied to unit" << endl;

  return true;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static bool DamageUnit( const char *name, const vector<wstring> &params, const CheatData& data )
{
  CPtr<NWorld::PFBaseUnit> pUnit( data.selectedObject );

  if ( !IsValid( pUnit ) )
    return false;

  if ( params.size() != 1 )
  {
    systemLog( NLogg::LEVEL_MESSAGE ) << "usage: " << name << " amount" << endl;
    return true;
  }

  CPtr<NWorld::PFBaseUnit> pDamager(pUnit);
  if ( AdventureScreen* pAdvScreen = AdventureScreen::Instance() )
  {
    if ( NWorld::PFWorld* pWorld = pAdvScreen->GetWorld() )
    {
      if( NWorld::PFPlayer* pPlayer = pWorld->GetPlayer(data.localPlayerId) )
      {
        pDamager = pPlayer->GetHero();
      }
    }
  }

  float damageAmount = NGlobal::VariantValue( params[0] ).GetFloat();

  NWorld::PFBaseUnit::DamageDesc damageDesc;
	damageDesc.pSender     = pDamager;
	damageDesc.amount      = damageAmount;
  damageDesc.damageType  = NDb::APPLICATORDAMAGETYPE_PURE;
	damageDesc.flags       = 0;
  damageDesc.damageMode  = NDb::DAMAGEMODE_DONTATTACKBACK;
	damageDesc.dontAttackBack = true;
	damageDesc.pDealerApplicator = 0;

  pUnit->OnDamage( damageDesc );

  return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static bool SetPause( const char *name, const vector<wstring> &params, const CheatData& data )
{
  if ( AdventureScreen* pAdvScreen = AdventureScreen::Instance() )
    if ( !pAdvScreen->IsInReplayMode() )
      if ( NWorld::PFWorld* pWorld = pAdvScreen->GetWorld() )
      {
        bool removePause = params.size() == 1 && params[0] == L"false";
        bool paused = !removePause && !pWorld->IsPaused();
        pAdvScreen->ProcessGamePause( paused ? NGameX::PAUSE_PLAYER : NGameX::PAUSE_OFF, data.cheater->GetPlayerId() );
      }
  
  return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static bool NAttack( const char *name, const vector<wstring> &params, const CheatData& data )
{
  if (params.size() != 3)
  {
    systemLog( NLogg::LEVEL_MESSAGE ) << "usage: " << name << " Neutral|Freeze|Burn Top|Center|Bottom count" << endl;
    return true;
  }

  NDb::EFaction faction = NDb::KnownEnum<NDb::EFaction>::ToEnum( NStr::ToMBCS( params[0] ) );
  if (faction == NDb::FACTION_NEUTRAL)
    return true;
  
  NDb::ENatureRoad roadIndex = NDb::KnownEnum<NDb::ENatureRoad>::ToEnum( NStr::ToMBCS( params[1] ) );
  int count = NStr::ToInt( params[2] );
  
  NWorld::PFRoadFlagpole::Attack( faction, roadIndex, count );
  return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static bool NOverride( const char *name, const vector<wstring> &params, const CheatData& data )
{
  if (params.size() != 3)
  {
    systemLog( NLogg::LEVEL_MESSAGE ) << "usage: " << name << " Neutral|Freeze|Burn radius time" << endl;
    return true;
  }

  NDb::EFaction faction      = NDb::KnownEnum<NDb::EFaction>::ToEnum( NStr::ToMBCS( params[0] ) );
  float radius = NStr::ToFloat( params[2] );
  float time = NStr::ToFloat( params[2] );
  
  if ( AdventureScreen* advScreen = AdventureScreen::Instance() )
    if ( NWorld::PFWorld* world = advScreen->GetWorld() )
    {
      world->GetNatureMap()->DebugOverride( faction, data.pickedPosition.AsVec2D(), radius, time );
    }
  return true;
}

//////////////////////////////////////////////////////////////////////////
// ~~~ Debug stuff for talents ~~~
static bool LoadTalents( const char *name, const vector<wstring> &params, const CheatData& data )
{
  NI_VERIFY( params.size() <= 1, "Bad params! Usage: LoadTalents [<aumlets_set_path>]", return false; );
  NWorld::PFBaseMaleHero* pHero = IsValid(data.selectedObject) ? dynamic_cast<NWorld::PFBaseMaleHero*>(data.selectedObject.GetPtr()) : NULL;
  NI_VERIFY( pHero, "Target must be an male hero!", return false; );
  
  string const& strSetName = params.size() == 1 ? NStr::ToMBCS( params[0] ) : "";
  
  bool oldValue = NDb::GetDbResourceCache().EnableAssertionLoadingFiles( false );

  pHero->LoadTalents(strSetName);

  AdventureScreen* pAdvScreen = AdventureScreen::Instance();
  if (!pAdvScreen)
    return false;

  pAdvScreen->SetLogicHero( pAdvScreen->GetHero() );

  NDb::GetDbResourceCache().EnableAssertionLoadingFiles( oldValue );

  return true;
}
// ~~~ Debug stuff for talents ~~~
//////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void SendCheatCommand( const char* name, const vector<wstring> &params, const CheatData& data )
{
#ifndef _SHIPPING
  AdventureScreen* advScreen = AdventureScreen::Instance();
  if ( !IsValid( advScreen ) )
    return;

  if ( advScreen->IsInReplayMode() )
  {
    CObj<CmdCheat> command =  new CmdCheat( name, params, data );
    command->Execute( advScreen->GetWorld() );
  }
  else
    advScreen->SendGameCommand( new CmdCheat( name, params, data ) );
#endif
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static bool CheatCommandProxy(const char *name, const vector<wstring> &params)
{
  if (AdventureScreen* pAdvScreen = AdventureScreen::Instance())
  {
    NWorld::PFPlayer * pLocalPlayer = pAdvScreen->GetWorld()->GetPlayer( pAdvScreen->GetLocalPlayerID() );

    CheatData data;
    data.localPlayerId = pAdvScreen->GetLocalPlayerID();
    data.cheater = pLocalPlayer ? pLocalPlayer->GetHero() : 0;
    data.selectedObject = pAdvScreen->GetCurrentSelectedObject();
    if ( !data.selectedObject )
      data.selectedObject = data.cheater;
    data.pickedObject = dynamic_cast<NWorld::PFBaseUnit*>( pAdvScreen->GetCurrentPickedObject() );
    data.pickedPosition = pAdvScreen->GetCurrentPickedPos();
    
    SendCheatCommand( name, params, data );
  }

  return true;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CreateCheatCmd(const char *cmdName)
{
  const vector<wstring> cmdParams;
  CheatCommandProxy(cmdName, cmdParams);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CreateCheatCmd(const char *cmdName, vector<wstring> const& cmdParams)
{
  CheatCommandProxy(cmdName, cmdParams);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CreateCheatCmd(const char *cmdName, const CheatData& data)
{
  vector<wstring> cmdWParams;
  SendCheatCommand( cmdName, cmdWParams, data );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CreateCheatCmd(const char *cmdName, string const& param, const CheatData& data)
{
  vector<wstring> cmdWParams;
  cmdWParams.push_back( NStr::ToUnicode( param ) );
  SendCheatCommand( cmdName, cmdWParams, data );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CreateCheatCmd(const char *cmdName, string const& param1, string const& param2, const CheatData& data)
{
  vector<wstring> cmdWParams;
  cmdWParams.push_back( NStr::ToUnicode( param1 ) );
  cmdWParams.push_back( NStr::ToUnicode( param2 ) );
  SendCheatCommand( cmdName, cmdWParams, data );
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CmdCheat::Execute( NCore::IWorldBase* pWorld )
{
  TCheats::iterator cheatIt = GetCheats().find(cheatName);
  if (cheatIt == GetCheats().end())
  {
    NI_ALWAYS_ASSERT("Unknown command received");
    return;
  }

  NI_VERIFY(cheatIt->second.callback, "Fatal: missing callback", return; );

  // Log the cheat
  if ( cheatIt->second.notifyStatistics )
  {
    StatisticService::RPC::SessionEventInfo eventParams;
    eventParams.strParam1.resize(cheatName.length());
    nstl::copy(cheatName.begin(), cheatName.end(), eventParams.strParam1.begin());
    data.cheater->LogSessionEvent(SessionEventType::CheatUsed, eventParams);
  }

  (*cheatIt->second.callback)( cheatName.c_str(), params, data );

  if ( IsValid( data.cheater ) )
  {
    NWorld::PFWorld * world = dynamic_cast<NWorld::PFWorld *>( pWorld );
    if ( world )
      world->GetStatistics()->SendCheatMessage( data.cheater );
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool LogUnitCmd(const char *name, const vector<wstring> &paramsSet)
{
	NWorld::PFBaseUnit const* pUnit = dynamic_cast<NWorld::PFBaseUnit const*>(AdventureScreen::Instance()->GetCurrentPickedObject());
	if (!pUnit)
		return true;

	const int bufSize = 16*1024;
	char buf[bufSize];
	NWorld::DumpUnitInfoToString(pUnit, buf, bufSize);

    DebugTrace( buf );

    localLog( &GetGameLogicLog(), NLogg::LEVEL_MESSAGE ) << buf;
	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static bool ActivateBidon( const char *name, const vector<wstring> &params, const CheatData& data )
{
  CPtr<NWorld::PFBaseUnit> pUnit(data.selectedObject);

  if ( !commandStart(string("usage: ") + name + " bidon_id [player_ID]", 2, params, pUnit) )
    return false;

  CDynamicCast<NWorld::PFEaselPlayer> easelPlayer = pUnit;

  if ( IsValid( easelPlayer ) )
  {
    int bidonID = (int)NGlobal::VariantValue( params[0] ).GetFloat();
    easelPlayer->SetCurrentBidon( static_cast<NDb::EBidonType>( bidonID ) );

    AdventureScreen* pAdvScreen = AdventureScreen::Instance();

    if ( pAdvScreen )
    {
      pAdvScreen->SetLogicHero( pAdvScreen->GetHero() );
      pAdvScreen->OnHeroSetActive();
    }

    return true;
  }

  return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static bool SpawnerSpawn( const char *name, const vector<wstring> &params, const CheatData& data )
{
  if (params.size() != 1)
  {
    systemLog( NLogg::LEVEL_MESSAGE ) << "usage: " << name << " xdb_path" << endl;
    return true;
  }

  AdventureScreen* pAdvScreen = AdventureScreen::Instance();
	if (!pAdvScreen)
		return false;

	NWorld::PFWorld* pWorld = pAdvScreen->GetWorld();
	if (!pWorld)
		return false;

  string spawnerFile = NStr::ToMBCS(params[0]);

  struct SpawnerSpawn : NonCopyable
  {
    string spawnerDbid;
    bool found;

    SpawnerSpawn(string _spawnerDbid) : spawnerDbid(_spawnerDbid), found(false) { NDb::FixFileNameForDBID(&spawnerDbid); }

    void operator()( PF_Core::WorldObjectBase &baseUnit )
	  {
      CDynamicCast<NWorld::PFBaseSpawner> pSpawner = &baseUnit;
      if (IsValid(pSpawner) && pSpawner->GetDBDesc()->GetDBID().GetFileName() == spawnerDbid)
      {
        pSpawner->SpawnWave();
        found = true;
      }
    }
  } spawnerSpawn(spawnerFile);

  pWorld->ForAllObjectsBeingStepped(spawnerSpawn);

  if (!spawnerSpawn.found) 
  {
    systemLog( NLogg::LEVEL_MESSAGE ) << "Spawner " << spawnerFile << " not found!" << endl;
  }

  return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static bool UpdateMapForce( const char *name, const vector<wstring> &params, const CheatData& data )
{
  NWorld::PFAIWorld* pAIWorld = AdventureScreen::Instance()->GetWorld()->GetAIWorld();

  pAIWorld->ApplyForceModifiersCheat();
  MessageTrace( "New StatsCoeffs applied: %f", pAIWorld->GetStatsCoeffs().coeffsByFaction[0] );
  return true;
}

static bool Win( const char *name, const vector<wstring> &params, const CheatData& data )
{
  AdventureScreen* pAdvScreen = AdventureScreen::Instance();
  NWorld::PFBaseHero* pHero = data.cheater;

  int addScore = (int)NGlobal::VariantValue( params[0] ).GetInt64();

  pHero->GetHeroStatistics()->AddAchievementScore( addScore );
  pAdvScreen->GetWorld()->GameFinish( pHero->GetOppositeFaction() );

  return true;
}

static bool EaselWinGame(const char *name, const vector<wstring> &params, const CheatData& data)
{
  DevTrace("NGameX::EaselWinGame");
  AdventureScreen* pAdvScreen = AdventureScreen::Instance();
  NWorld::PFBaseHero* pHero = data.cheater;

  if(pAdvScreen->IsPlayingMinigame())
  {

  CDynamicCast<NWorld::PFEaselPlayer> easelPlayer = pHero;

  if ( IsValid( easelPlayer ) )
  {
    CObj<PF_Minigames::IMinigames> minigames = easelPlayer->GetMinigames();
    if(IsValid( minigames ))
    {
      minigames->GetCurrentMinigame()->CheatWinGame();
    }
  }
  }

  return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static bool PlayAchievs( const char *name, const vector<wstring> &params, const CheatData& data )
{
  DevTrace("NGameX::PlayAchievs");
  NWorld::PFBaseHero* pHero = data.cheater;


  float step = 5.0f;
  if ( !params.empty() )
    step = NGlobal::VariantValue( params[0] ).GetFloat();

  struct PlayUI
  {
    float val;
    float step;
    
    PlayUI( float _step ) : val(1.0f), step(_step) {}

    void operator()( NWorld::PFAchievBase* pAchiev )
    {
      pAchiev->OnCheatPlay( val );
      val += step;
    }

  } playUI(step);

  if ( pHero->GetHeroStatistics() )
    pHero->GetHeroStatistics()->ForAllAchievements( playUI );

  return true;
}

static bool SetCheatTitle( const char *name, const vector<wstring> &params, const CheatData& data )
{
  DevTrace("NGameX::SetCheatTitle");
  int title = 0;
  if ( !params.empty() )
    title = NGlobal::VariantValue( params[0] ).GetInt64();

  title = Clamp( title, 0, NDb::KnownEnum<NDb::EHeroTitle>::sizeOf-1 );

  if ( NGameX::AdventureScreen::Instance() )
  {
    if ( NGameX::AdventureScreenLogic* pAdvScreenLogic = dynamic_cast<NGameX::AdventureScreenLogic*>(NGameX::AdventureScreen::Instance()->GetLogic()) )
    {
      if( pAdvScreenLogic->GetFinalStatisticsController() )
      {
        pAdvScreenLogic->GetFinalStatisticsController()->ForceSetTitle( (NDb::EHeroTitle)title );
      }
    }
  }

  return true;
}

static bool SetLeagueIndex( const char *name, const vector<wstring> &params, const CheatData& data )
{
  DevTrace("NGameX::SetLeagueIndex");
  AdventureScreen* pAdvScreen = AdventureScreen::Instance();
  if (!pAdvScreen)
    return false;

  NWorld::PFWorld* pWorld = pAdvScreen->GetWorld();
  if (!pWorld)
    return false;

  NWorld::PFBaseUnit *pUnit = data.selectedObject;
  if (!pUnit)
    return false;

  int new_league_index = (int)NGlobal::VariantValue( params[0] ).GetInt64();
  bool is_rand_league = false;
  if (params.size() == 2)
    is_rand_league = (int)NGlobal::VariantValue( params[1] ).GetInt64() == 0 ? false : true;
  
  srand (time(0));

  int count_heroes = pWorld->GetPlayersCount();
  for (int i = 0; i < count_heroes; ++i)
  {
    NWorld::PFPlayer* pPlayer = pWorld->GetPlayer(i);
    NWorld::PFBaseHero* pHero = pPlayer->GetHero();
    if ( !pHero )
      continue;

  
      const char * texturePath =  pHero->GetUiAvatarImage()? pHero->GetUiAvatarImage()->textureFileName.c_str() : "";

      const NDb::AILogicParameters& aiLogic = AdventureScreen::Instance()->GetWorld()->GetAIWorld()->GetAIParameters();
      Strong<HeroRankCalculator> rankCalculator = new HeroRankCalculator(aiLogic.heroRanks);

      const NDb::Rank & rank = rankCalculator->GetRank(pHero->GetRaiting());

      NDb::EFaction originalFaction = pHero->GetOriginalFaction();

      float raiting = pHero->GetRaiting();

      string flagIcon;
      wstring flagTooltip;      
      
      AdventureScreenLogic* advLogic = dynamic_cast<AdventureScreenLogic*>(AdventureScreen::Instance()->GetLogic());
      NI_ASSERT( advLogic, "Can't acquire adventure screen logic" );

      int league_index = !is_rand_league ? new_league_index : advLogic->GetTeamInfo()->GetOurHero()->GetPlayerId() == pHero->GetPlayerId() ? new_league_index : rand() % 5;

      advLogic->GetFlashInterface()->SetHeroIdentity(
        pHero->GetPlayerName(), 
        pHero->GetDescription(), 
        pHero->GetPlayerId(), texturePath, 
        ( pHero->GetZZimaSex() == ZZSEX_MALE ),
        pHero->GetFaction() != advLogic->GetTeamInfo()->GetOurHero()->GetFaction(), 
        pHero->GetPlayer()->IsBot(),
        pHero->GetForce(true), 
        pHero->GetFaction(), 
        originalFaction,
        raiting, 
        rankCalculator->GetRankIcon(originalFaction, rank), 
        rankCalculator->GetRankName(originalFaction, rank),
        false,pHero->GetPartyId(),flagIcon,flagTooltip, pHero->GetAnimatedAvatar(), league_index, pHero->GetOwnLeaguePlace(), pHero->GetLeaguePlaces());

      advLogic->GetFlashInterface()->ShowHeroPortrait(pHero->GetPlayerId(), pHero->GetFaction() != advLogic->GetTeamInfo()->GetOurHero()->GetFaction());
  }

  return true;
}

static bool SetRatingChange( const char *name, const vector<wstring> &params, const CheatData& data )
{
  DevTrace("NGameX::SetRatingChange");

  float new_rating_change = (int)NGlobal::VariantValue( params[0] ).GetFloat();

  AdventureScreenLogic* advLogic = dynamic_cast<AdventureScreenLogic*>(AdventureScreen::Instance()->GetLogic());
  NI_ASSERT( advLogic, "Can't acquire adventure screen logic" );

  static wstring empty;
  advLogic->GetFlashInterface()->AwardDeltaRaiting(new_rating_change, "", empty );

  return true;
}

static bool DebugKillMBuildings(const char *name, const vector<wstring> &params, const CheatData& data)
{
  typedef vector<NWorld::PFLogicObject*> TMainBuildings;

  NWorld::PFBaseHero* pHero = data.cheater;

  struct MBFinder
  {
    MBFinder::MBFinder( ): mainBuilding(0) {}
    void operator()( NWorld::PFLogicObject &object )
    {
      if ( object.GetUnitType() == NDb::UNITTYPE_MAINBUILDING )
      {
        mainBuilding.push_back(&object);
      }
    }
    TMainBuildings mainBuilding;
  } finder;

  pHero->GetWorld()->GetAIWorld()->ForAllUnits( finder );

  struct MBSort
  {
    MBSort(NDb::EFaction _faction): faction(_faction){};
    
    bool operator() (NWorld::PFLogicObject *object1,NWorld::PFLogicObject *object2)
    {
      if(object1->GetFaction() == faction )
        return false;

      return true;
    }

    NDb::EFaction faction;
  } magic(pHero->GetFaction());

  nstl::sort(finder.mainBuilding.begin(), finder.mainBuilding.end(), magic);

  TMainBuildings::iterator iter = finder.mainBuilding.begin();

  while(iter != finder.mainBuilding.end())
  {
    if ( CDynamicCast<NWorld::PFMainBuilding> mainBuilding = *iter )
    {
      mainBuilding->OnUnitDie( pHero, NWorld::PFBaseUnit::UNITDIEFLAGS_NONE );
    }

    iter++;
  }

  return true;

}

} // namespace NGameX

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
REGISTER_CHEAT_CMD( add_gold, NGameX::HeroAddGold );
REGISTER_CHEAT_CMD( receive_artifact,  NGameX::ReceiveArtifact );
REGISTER_CHEAT_CMD( refresh_cd,  NGameX::ResfreshCooldown );
REGISTER_CHEAT_CMD( kill_unit,  NGameX::DebugKillUnit );
REGISTER_CHEAT_CMD( teleport_unit,  NGameX::TeleportUnit );
REGISTER_CHEAT_CMD( hero_change,  NGameX::HeroChange );
REGISTER_CHEAT_CMD( hero_set_active,  NGameX::HeroSetActive );
REGISTER_CHEAT_CMD( resurrect_hero,  NGameX::ResurrectHero );
REGISTER_CHEAT_CMD( unit_stat,  NGameX::UnitStat );
REGISTER_CHEAT_CMD( global_stat_scale,  NGameX::GlobalStatScale );
REGISTER_CHEAT_CMD( add_health,  NGameX::AddHealth );
REGISTER_CHEAT_CMD( add_mana,  NGameX::AddMana );
REGISTER_CHEAT_CMD( add_killed_creeps,  NGameX::AddKilledCreeps );
REGISTER_CHEAT_CMD( add_killed_towers,  NGameX::AddKilledTowers );
REGISTER_CHEAT_CMD( set_health,  NGameX::SetHealth );
REGISTER_CHEAT_CMD( debug_pauseFSM,  NGameX::PauseFSM );
REGISTER_CHEAT_CMD( unit_getvar,  NGameX::GetVar );
REGISTER_CHEAT_CMD( unit_setvar,  NGameX::SetVar );
REGISTER_CHEAT_CMD( unit_findappl,  NGameX::FindAppl );
REGISTER_CHEAT_CMD( damage_unit,  NGameX::DamageUnit );
REGISTER_CHEAT_CMD( set_pause,  NGameX::SetPause );
REGISTER_CHEAT_CMD( nattack, NGameX::NAttack );
REGISTER_CHEAT_CMD( noverride, NGameX::NOverride );
REGISTER_CHEAT_CMD( use_consumable,  NGameX::UseConsumable );
REGISTER_CHEAT_CMD( take_consumable,  NGameX::TakeConsumable );
REGISTER_CHEAT_CMD( hero_force,  NGameX::HeroForceCalculate );
REGISTER_CHEAT_CMD( spawner_spawn,  NGameX::SpawnerSpawn );
REGISTER_CHEAT_CMD( update_map_force,  NGameX::UpdateMapForce );
REGISTER_CHEAT_CMD( set_refinerate,  NGameX::SetRefineRate );
REGISTER_CHEAT_CMD( set_skin,  NGameX::SetSkin );
REGISTER_DEVCHEAT_CMD( win , NGameX::Win );
REGISTER_CHEAT_CMD( easel_win_game , NGameX::EaselWinGame );
REGISTER_CHEAT_CMD( play_achievs, NGameX::PlayAchievs );
REGISTER_CHEAT_CMD( set_cheat_title, NGameX::SetCheatTitle );
REGISTER_CHEAT_CMD( set_league_index, NGameX::SetLeagueIndex );
REGISTER_CHEAT_CMD( set_rating_change, NGameX::SetRatingChange );

REGISTER_CHEAT_CMD( destroy_all_main_buildings,  NGameX::DebugKillMBuildings );

REGISTER_CHEAT_CMD( aat, NGameX::HeroActivateAllTalents );
REGISTER_CHEAT_CMD( activate_all_talents, NGameX::HeroActivateAllTalents );

REGISTER_DEV_CMD(gl_log_unit, NGameX::LogUnitCmd);

//////////////////////////////////////////////////////////////////////////
// ~~~ Debug stuff for talents ~~~
REGISTER_CHEAT_CMD(load_talents, NGameX::LoadTalents);
// ~~~ Debug stuff for talents ~~~
//////////////////////////////////////////////////////////////////////////

REGISTER_CHEAT_CMD( bidon, NGameX::ActivateBidon );



REGISTER_SAVELOAD_CLASS_NM(CmdCheat, NGameX)

#endif // #ifndef _SHIPPING
