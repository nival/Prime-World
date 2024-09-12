#include "stdafx.h"

#include "DBConsumable.h"
#include "DBGameLogic.h"
#include "DBGameLogic.h"
#include "DBStats.h"
#include "DBSound.h"
#include "PFBaseUnitStates.h"
#include "PFChest.h"
#include "PFHeroStates.h"
#include "PFPet.h" // for pet debugging
#include "PFStatistics.h"
#include "PFHero.h"
#include "PFLogicDebug.h"
#include "PFGameLogicLog.h"
#include "PFWorldNatureMap.h"

#include "PFBaseAttackData.h"
#include "PFConsumable.h"
#include "PFTalent.h"

#include "../System/InlineProfiler.h"

#include "AdventureCameraController.hpp"

#ifndef VISUAL_CUTTED
#include "PFClientHero.h"
#include "PFClientSummoned.h"
#include "PFClientApplicators.h"
#else
#include "../Game/pf/Audit/ClientStubs.h"
#endif

#include "PFImpulsiveBuffs.h"
#include "PFAbilityData.h"
#include "PFAchievement.h"

#include "PFPredefinedUnitVariables.h"

//logging session events
#include "AdventureScreen.h"
#include "IAdventureScreen.h"
#include "SessionEventType.h"
#include "System/StarForce/StarForce.h"

#include "PlayerBehaviourTracking.h"


namespace
{
  int  g_addPetToPlayer = -1;
  float g_fGiveWorldGoldDelay = 1.0f;
  static bool g_zzSexSameAsGender = false;
  
  const float mountPriestessDistance = 15.0f;

  CVec3 FindFountainPos(const NWorld::PFBaseHero * pHero)
  {
    CVec3 fountainPos(-1.0f, -1.0f, -1.0f);

    NI_VERIFY(pHero, "Invalid hero!", return fountainPos);

    struct FountainFinder : public NonCopyable
    {
      const NWorld::PFBaseHero    * pHero;
      const NWorld::PFLogicObject * pFoundFountain;
            NDb::EFaction           faction;

      FountainFinder(const NWorld::PFBaseHero * _pHero) 
        : pHero(_pHero)
        , pFoundFountain(0)
        , faction(NDb::FACTION_NEUTRAL) //No neutral fountains, therefore it is a default in error case
      {
        if (pHero)
          faction = pHero->GetFaction();
      }

      void FountainFinder::operator()(const NWorld::PFLogicObject & object)
      {
        if (object.GetUnitType() == NDb::UNITTYPE_BUILDING && object.GetFaction() == faction)
        {
          if (const NWorld::PFFountain * pFountain = dynamic_cast<const NWorld::PFFountain *>(&object))
          {
            pFoundFountain = pFountain;
          }
        }
      }
    } fountainFinder(pHero);

    const NWorld::PFAIWorld * pAIWorld = pHero->GetWorld()->GetAIWorld();
    NI_VERIFY(pAIWorld, "Invalid world!", return fountainPos);

    pAIWorld->ForAllUnits(fountainFinder);

    if (fountainFinder.pFoundFountain)
    {
      fountainPos = fountainFinder.pFoundFountain->GetPosition();
    }

    return fountainPos;
  }
}

REGISTER_DEV_VAR( "debug_add_pet_to", g_addPetToPlayer, STORAGE_NONE );

namespace NWorld
{

typedef void (PFBaseHero::*TSetterFunc)( const wstring & value );

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NAMEMAP_BEGIN( PFBaseHero )
  NAMEMAP_PARENT( PFCreature )
  NAMEMAP_FUNC_RO ( maxExperience, &PFBaseHero::GetLevelMaxExperienceRef )
  NAMEMAP_FUNC_RO ( playerName, &PFBaseHero::GetPlayerName )
  NAMEMAP_VAR_RO( experience )
  NAMEMAP_VAR_RO( redeemCost )
  NAMEMAP_FUNC_RO( team, &PFBaseHero::GetTeamName )
  NAMEMAP_FUNC_RO( customEnergyValue, &PFBaseHero::GetCustomEnergyValue )
  NAMEMAP_FUNC_RO( customEnergyMaximum, &PFBaseHero::GetCustomEnergyMaximum )
  NAMEMAP_FUNC_RO( customEnergyRegeneration, &PFBaseHero::GetCustomEnergyRegeneration )
NAMEMAP_END

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PFBaseHero::PFBaseHero(PFWorld* pWorld, const SpawnInfo &info, NDb::EUnitType unitType, NDb::EFaction faction, NDb::EFaction _originalFaction)
  : PFCreature(pWorld, info.placement.pos, INITIALDIR2, *info.pHero)
  , respawnDelay(-1.0f)
  , advanceRespawnDelay(-1.0f)
  , forbidRespawn(false)
  , spawnPos(VNULL3)
  , isClone(info.isClone)
  , experience(0.0f)
  , pPlayer(NULL)
  , giveWorldGoldOffset( pWorld->GetAIWorld()->GetBattleStartDelay() )
  , distanceRun(0.f)
  , pDbHero( info.pHero )
  , isolated( false )
  , ripTime(0.f)
  , inTeamId( info.inTeamId )
  , redeemCost(0.0f)
  , redeemCostRecalculateDelay(-1.0f)
  , abilityModsActualizationTime(-1.0f)
  , pMount(NULL)
  , timeSinceLastSlice(0)
  , slicesCount(0)
  , cloneCounter(0)
  , fountainPos(VNULL3)
  , canControlMount(false)
  , force(0.0f)
  , takeModDmg( 1.f )
  , takeTypeUnit( NDb::ESpellTarget( 0 ) )
  , raiting(info.playerInfo.heroRating)
  , scriptControlledProgressValue(0.0f)
  , partyId(info.playerInfo.partyId)
  , isMuted(info.playerInfo.chatMuted)
  , flagId(info.playerInfo.flagId)
  , customEnergy(false)
  , customEnergyValue(NULL)
  , customEnergyMaximum(NULL)
  , customEnergyRegeneration(NULL)
  , heroState(EHeroState::First)
{
  NI_VERIFY( info.pHero, "Invalid spawn info !", return );
  NI_ASSERT( unitType == NDb::UNITTYPE_HEROMALE || unitType == NDb::UNITTYPE_HEROFEMALE, "Wrong unit type!" );

  pStatistics = new PFHeroStatistics( this, pWorld->GetStatistics()->DbScoring());
  pProfile    = new PFBetweenSessionsData( pWorld );

  // Initialize base unit
  PFBaseUnit::InitData data;
  data.faction      = faction;
  data.type         = unitType;
  data.playerId     = -1;
  data.pObjectDesc  = info.pHero;
  Initialize(data);

  SetSkin(info.playerInfo.heroSkin);
  SetAnimatedAvatar(info.playerInfo.isAnimatedAvatar);
  SetLeagueIndex(info.playerInfo.leagueIndex);
  SetOwnLeaguePlace(info.playerInfo.ownLeaguePlace);
  leaguePlaces = info.playerInfo.leaguePlaces;

  EnableAbilityAI(false);

  //TODO: Set player inventory size based on ZZima account
  consumables.resize( 32 );

  spawnPos       = GetPosition();
  gold           = 0.0f; //init to hero value

  originalFaction = (_originalFaction != NDb::FACTION_NEUTRAL) ? _originalFaction : faction;

  PrepareExcludedResourcesList( originalFaction );

  playerGender = PlayerGenderFromDbGender();

  if ( !isClone )
  {
    CObj<PFBaseBehaviour> pB( new PFHeroBehaviour( this ) );
    AddBehaviourOnTop( pB );
  }
}
NDb::EFaction GetAntiFaction(NDb::EFaction currentFaction)
{
  return (currentFaction == NDb::FACTION_FREEZE) ? NDb::FACTION_BURN : NDb::FACTION_FREEZE;
}

void PFBaseHero::PrepareExcludedResourcesList( const NDb::EFaction& sourceFaction )
{
  const NDb::HeroSkin* currentSkin = GetHeroSkin();

  {
    typedef vector<NDb::Ptr<NDb::HeroSkin>> HeroSkinVector;

    HeroSkinVector::const_iterator it = pDbHero->heroSkins.begin();
    HeroSkinVector::const_iterator it_end = pDbHero->heroSkins.end();
    for (; it != it_end; ++it)
    {
      if ((*it).GetPtr() == currentSkin)
        continue;

      excludedResources.push_back(*it);
    }
  }
  
  {
    typedef vector<NDb::Ptr<NDb::TalentsSet>> HeroTalentSetsVector;
    
    if ( NDb::Ptr<NDb::Hero> pHero = dynamic_cast<NDb::Hero const*>(pDbHero.GetPtr()) )
    {
      HeroTalentSetsVector::const_iterator it = pHero->defaultTalentsSets.begin();
      HeroTalentSetsVector::const_iterator it_end = pHero->defaultTalentsSets.end();
      for (; it != it_end; ++it)
      {
        excludedResources.push_back(*it);
      }
    }
  }

  if ( !currentSkin )
  {
    const NDb::Ptr<NDb::DBSceneObject>& ourSideSO =
      NGameX::PFBaseClientHero::CreatePars::SelectSceneObj( *pDbHero, GetFaction(), "" );
    const NDb::Ptr<NDb::DBSceneObject>& otherSideSO =
      NGameX::PFBaseClientHero::CreatePars::SelectSceneObj( *pDbHero, GetAntiFaction(GetFaction()), "" );
    if (ourSideSO.GetPtr() != otherSideSO.GetPtr())
      excludedResources.push_back(otherSideSO);
  }
  else
  {
    // NUM_TASK heroSceneObjects может содержать объект, который используется скином
    // TODO: DataAssert ?
    {
      typedef vector<NDb::Ptr<NDb::DBSceneObject>> SceneObjectVector;

      SceneObjectVector::const_iterator it = pDbHero->heroSceneObjects.begin();
      SceneObjectVector::const_iterator it_end = pDbHero->heroSceneObjects.end();
      for (; it != it_end; ++it)
      {
        if ((*it).GetPtr() == currentSkin->sceneObject)
          continue;

        excludedResources.push_back(*it);
      }
    }

    if ( currentSkin->heroImageA )
      excludedResources.push_back(pDbHero->heroImageA);
    if ( currentSkin->heroImageB )
      excludedResources.push_back(pDbHero->heroImageB);
  }

  NI_ASSERT(sourceFaction != NDb::FACTION_NEUTRAL, "Unable t pre cache summon units for NEUTRAL faction. ");

  typedef vector<NDb::SummonedUnits> TSummonContainer;
  TSummonContainer::const_iterator summonIter = pDbHero->summonedUnits.begin();
  for( ; summonIter != pDbHero->summonedUnits.end(); ++summonIter )
  {
    const NDb::Summoned* otherSideUnit = (sourceFaction == NDb::FACTION_FREEZE) ? summonIter->unitB : summonIter->unitA;
    const NDb::Summoned* ourSideUnit = (sourceFaction == NDb::FACTION_FREEZE) ? summonIter->unitA : summonIter->unitB;
    
    if (!ourSideUnit && otherSideUnit)
      ourSideUnit = otherSideUnit;

    // исключения загрузки саммонов другой фракции
    if (otherSideUnit && otherSideUnit != ourSideUnit)
      excludedResources.push_back(otherSideUnit);

    // для каждого саммона нашей фракции надо добавить в список исключаемых из прелоада ресурсов те скины, которые не будут использоваться
    if (ourSideUnit)
      NGameX::PFClientSummoned::PrepareExcludedResourcesList( ourSideUnit, currentSkin ? currentSkin->persistentId : "", excludedResources );
    }
}

bool PFBaseHero::SetSkin( const nstl::string& skinId, bool invalidateClientObject /*= false*/ )
{
  if (!GetWorld()->GetAIWorld()->CanUseSkins())
    return false;

  NDb::Ptr<NDb::HeroSkin> prevSkin = pCurrentHeroSkin;
  // найдем нужный скин, если юзер выбрал его для игры
  if (!skinId.empty() && skinId != "default")
  {
    vector<NDb::Ptr<NDb::HeroSkin>>::const_iterator it = pDbHero->heroSkins.begin();
    for ( ; it != pDbHero->heroSkins.end(); ++it )
    {
      if ((*it)->persistentId == skinId)
      {
        heroSkinId = skinId;
        pCurrentHeroSkin = *it;
        break;
      }
    }
  }
  else
  {
    heroSkinId.clear();
    pCurrentHeroSkin = 0;
  }

  if (prevSkin == pCurrentHeroSkin)
    return false;

  if (invalidateClientObject)
  {
    RemoveClientObject();
    RestoreClientObject();
  }

  return true;
}

//////////////////////////////////////////////////////////////////////////
NDb::EGender PFBaseHero::GetDbGender() const
{
  if ( pCurrentHeroSkin.GetPtr() )
    return pCurrentHeroSkin->gender;

  return pDbHero->gender;
}

NCore::ESex::Enum PFBaseHero::PlayerGenderFromDbGender()
{
  return (GetDbGender() == NDb::GENDER_MALE) ? NCore::ESex::Male : NCore::ESex::Female;
}


//////////////////////////////////////////////////////////////////////////
const NDb::AskSounds* PFBaseHero::GetHeroAsks(EHeroState::Enum forHeroState) const
{
  if( IsClone() || (pCurrentHeroSkin && pCurrentHeroSkin->mute))	// Clones do not speak
    return 0;

  NI_VERIFY(pDbHero, "Failed to get hero's DB descriptor!", return 0);
  NDb::ETeamID teamID = NDb::TEAMID_A;
  NDb::EFaction faction = GetOriginalFaction();

  if (faction == NDb::FACTION_FREEZE)
    teamID = NDb::TEAMID_A;
  else if (faction == NDb::FACTION_BURN)
    teamID = NDb::TEAMID_B;
  else
    NI_ALWAYS_ASSERT("Invalid faction");
  
  if ( pCurrentHeroSkin.GetPtr() )
  {
    if (forHeroState == EHeroState::First)
      if ( pCurrentHeroSkin->askList.GetPtr() )
        return &pCurrentHeroSkin->askList->asks;
    else
      if ( pCurrentHeroSkin->askListSecondState.GetPtr() )
        return &pCurrentHeroSkin->askList->asks;

    if ( pCurrentHeroSkin->heroRace == NDb::HERORACES_A )
      teamID = NDb::TEAMID_A;
    else if ( pCurrentHeroSkin->heroRace == NDb::HERORACES_B )
      teamID = NDb::TEAMID_B;
  }

  if (forHeroState == EHeroState::First)
    return &pDbHero->askLists[teamID];
  else
    return &pDbHero->askListsSecondState[teamID];
}

void PFBaseHero::PlayAskSound( int id, NWorld::PFBaseHero const * pTarget /*= 0*/, int announcePriority /*= -1*/ ) const
{
  CALL_CLIENT_3ARGS( PlayAskSound, id, pTarget, announcePriority );
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseHero::OnDestroyContents()
{
  DismountSpecial();

  PFCreature::OnDestroyContents();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseHero::Reset()
{
  PFCreature::Reset();

  for ( int i = 0; i < rgConsumablesAbilities.size(); ++i )
    AddConsumableToGroup( rgConsumablesAbilities[i] );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseHero::ClientAttachToPlayer()
{
  UpdateClientColor();

  if( NGameX::PFBaseClientHero* pClient = ClientObject() )
    pClient->OnBecameLocal( IsLocal() );
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseHero::AttachToPlayer(CPtr<PFPlayer> const& pNewPlayer)
{
  if( pPlayer == pNewPlayer )
    return;

  DetachFromPlayer();

  pPlayer  = pNewPlayer;
  playerId = pPlayer ? pPlayer->GetPlayerID() : -1;
  faction  = NWorld::GetFaction(pPlayer);

  if ( IsValid(pPlayer) && !pPlayer->IsBot() && !g_zzSexSameAsGender )
    playerGender = pPlayer->GetZZimaSex();
  else
    playerGender = PlayerGenderFromDbGender();
  

  pPlayer->AttachHero( this );

  ClientAttachToPlayer();

  // Test: add pet
  if (GetPlayer()->GetPlayerID() == g_addPetToPlayer)
    CreateTestPet( GetWorld(), "Pets/cat.PTOB.xdb", this );

  GetWorld()->GetAIWorld()->RegisterHero(this);

  // expo mode feature //
  if ( ( NGlobal::GetVar( "immortal_heroes" ).GetInt64() != 0 ) && pPlayer && !pPlayer->IsBot() )
  {
    NDb::Ptr<NDb::StatsContainer> unitStats = pDbHero->stats;
    NI_DATA_ASSERT( unitStats, NStr::StrFmt( "Unit \"%s\" has no stats", NDb::GetFormattedDbId( pDbHero->GetDBID() ).c_str() ) );

    NDb::Ptr<NDb::StatsContainer> defaultStats = GetWorld()->GetAIWorld()->GetUnitParameters( type ).defaultStats;
    NDb::Ptr<NDb::UnitConstantsContainer> globalConstants = GetWorld()->GetAIWorld()->GetAIParameters().globalConstants;

    NDb::Ptr<NDb::StatsEnhancersContainer> statsEnhancers = GetWorld()->GetAIWorld()->GetAIParameters().expoModeParams.statsEnhancers;

    stats->Load( unitStats, defaultStats, globalConstants, statsEnhancers );
    stats->Upgrade( 0, naftaLevel );

    // TODO: consider unique hero resource?
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseHero::DetachFromPlayer()
{
  if( IsValid(pPlayer) )
  {
    pPlayer->DetachHero();

    pPlayer  = NULL;
    playerId = -1;
    faction  = NDb::FACTION_NEUTRAL;
  }

  playerGender = PlayerGenderFromDbGender();

  GetWorld()->GetAIWorld()->UnregisterHero(this);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFBaseHero::UpdateClientColor()
{
  if( NWorld::PFAIWorld const* pAIWorld = GetWorld()->GetAIWorld() )
  {
    CALL_CLIENT_1ARGS(Recolor, pAIWorld->GetHeroColor(GetFaction(), GetInTeamId()));
    return true;
  }

  return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PFBaseHero::GetStatisticsUid() const
{
  NI_VERIFY( IsValid( GetPlayer() ), "", return 0; );

  return GetPlayer()->GetUserID();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseHero::Initialize(InitData const& data)
{
  struct Local
  {
    static void DisableStat(StatValueWithModifiers* const stat)
    {
      if (!stat)
        return;

      // TODO: ensure unique?
      const int provider = std::numeric_limits<int>::min() + 3;

      // TODO: remove previously added modifiers?

      stat->AddModifier(0.0f, 0.0f, provider, true, NDb::STATCONSTRAINT_LOWERLIMIT);
      stat->AddModifier(0.0f, 0.0f, provider, true, NDb::STATCONSTRAINT_UPPERLIMIT);
    }

    static void DisableStat(const CObj<PFStatContainer>& stats, const NDb::EStat stat)
    {
      if (!stats)
        return;

      DisableStat(stats->Get(stat));
    }
  };

  PFCreature::Initialize(data);

  customEnergy = false;
  const NDb::Ptr<NDb::HeroResource>& uniqueResource = pDbHero->uniqueResource;

  if (IsValid(uniqueResource))
  {
    NI_DATA_ASSERT(IsValid(uniqueResource->overtipManaProgressMaterial), NI_STRFMT("Invalid unique resource overtip bar material!", pDbHero->GetDBID().GetFormatted()));

    NI_DATA_ASSERT(!uniqueResource->formulaNameValue.empty(), NI_STRFMT("Invalid unique resource value formula name!", pDbHero->GetDBID().GetFormatted()));
    NI_DATA_ASSERT(!uniqueResource->formulaNameMaximum.empty(), NI_STRFMT("Invalid unique resource maximum formula name!", pDbHero->GetDBID().GetFormatted()));
    NI_DATA_ASSERT(!uniqueResource->formulaNameRegeneration.empty(), NI_STRFMT("Invalid unique resource regeneration formula name!", pDbHero->GetDBID().GetFormatted()));

    Local::DisableStat(stats, NDb::STAT_ENERGY);
    Local::DisableStat(stats, NDb::STAT_ENERGYDRAIN);
    Local::DisableStat(stats, NDb::STAT_ENERGYREGENERATION);
    Local::DisableStat(stats, NDb::STAT_ENERGYREGENERATIONABSOLUTE);

    InitializeLifeEnergy();

    if (IsValid(uniqueResource->overtipManaProgressMaterial) &&
      !uniqueResource->formulaNameValue.empty() &&
      !uniqueResource->formulaNameMaximum.empty() &&
      !uniqueResource->formulaNameRegeneration.empty())
    {
      customEnergy = true;
    }

    InitializeCustomEnergyVariables();

    if (customEnergy &&
      customEnergyValue && customEnergyMaximum && customEnergyRegeneration)
    {
      customEnergy = true;
    }
    else
    {
      customEnergy = false;
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseHero::InitHero(const NDb::BaseHero *pDesc)
{
  //DoLevelups(CountLevelups());
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFBaseHero::Step(float dtInSeconds)
{
  NI_PROFILE_FUNCTION

  LoggTimeSliceIfNeeded(dtInSeconds);

  // Update hero in dead state
  if( IsDead() )
  {
    if (pStatistics)
    {
      pStatistics->AddTimeInDeath(dtInSeconds);
    }

    if( advanceRespawnDelay >= 0.0f )
    {
      advanceRespawnDelay -= dtInSeconds;
      if( advanceRespawnDelay < EPS_VALUE )
        AdvanceResurrect();
    }

    if( respawnDelay >= 0.0f )
    {
      ripTime      += dtInSeconds;
      respawnDelay -= dtInSeconds;

      if( !IsClone() && IsLocal() )
      {
        const NDb::Ptr<NDb::SoundRoot>& soundRoot = NDb::SoundRoot::GetRoot();
        if ( (int)(respawnDelay-0.1f) != (int)(respawnDelay-0.11f)  )
        {
          NSoundScene::EventStart( soundRoot->timerSounds.deadTimerSound );
        }
        if ( respawnDelay <= soundRoot->timerSounds.timeToRestorePitch )
        {
          NSoundScene::SetGlobalPitchCoeff( respawnDelay/soundRoot->timerSounds.timeToRestorePitch );
        }
      }

      if( respawnDelay < EPS_VALUE )
      {
        DoResurrect();
      }
    }

    if( 0 < redeemCostRecalculateDelay )
    {
      redeemCostRecalculateDelay -= dtInSeconds;
      if( redeemCostRecalculateDelay < EPS_VALUE )
        RecalculateRedeemCost();
    }
  }
  else
  {
    // Auto attack targets on idle
    if ( !isolated && !GetCurrentState() && !HasQueuedStates() &&
      !CheckFlagType(NDb::UNITFLAGTYPE_FORBIDATTACK) && !CheckFlagType(NDb::UNITFLAGTYPE_FORBIDAUTOATTACK) )
    {
      //Hold position
      OnIdle();
    }

    

    //if ( NGameX::AdventureScreen::Instance() )
    //{
    //  if( !NGameX::AdventureScreen::Instance()->IsGameEnded() && !NGameX::AdventureScreen::Instance()->IsPlayingMinigame())
    //  {
    //    CALL_CLIENT_1ARGS(UpdateBattleSound, dtInSeconds);
    //  }
    //}

    if (pStatistics)
    {
      if (!(fountainPos.x || fountainPos.y)) // Both x and y are zero, if not initialized
        fountainPos = FindFountainPos(this);

      if (fountainPos.x != -1.0f) // fountainPos.x = -1.0f if previously failed to find fountain
        if (CanSee(fountainPos)  && fabs(GetPosition() - fountainPos) <= 22.0f)
          pStatistics->AddTimeAtHome(dtInSeconds);

      if (IsIdle())
        pStatistics->AddTimeInIdle(dtInSeconds);
    }
  }

  if ( !isClone && ( !IsDead() || GetWorld()->GetAIWorld()->GetPrimeSettings().giveWorldPrimeToDead ) )
  {
    giveWorldGoldOffset -= dtInSeconds;
    if ( giveWorldGoldOffset < 0 )
    {
      // Calculate nafta salary
      float naftaSalary = GetWorld()->GetAIWorld()->GetPrimeSettings().giveWorldPrimeAmount 
                            + GetVariable( UnitVariables::szNaftaForTimeBonus );

      // Grant the salary to the hero
      AddGold( naftaSalary, false );

      // Update hero's nafta salary statistics
      AddTSliceSalary(naftaSalary);

      giveWorldGoldOffset = g_fGiveWorldGoldDelay;
    }
  }

  // update consumables
  {
    struct Updater
    {
      float dt;
      inline Updater(float dt) : dt(dt) {}
      inline void operator()(CObj<PFConsumableAbilityData>& pAbilityData)
      {
        pAbilityData->Update(dt, true);
      }
    };

    for_each( rgConsumablesAbilities.begin(), rgConsumablesAbilities.end(), Updater(dtInSeconds) );
  }

  if (!IsDead() && HasCustomEnergy())
  {
    // Если так вышло (хотя непонятно как)
    if (pDbHero->uniqueResource == NULL || pDbHero->uniqueResource.IsEmpty())
    {
      customEnergy = false;
    }

    float value = GetCustomEnergyValue();
    float maximum = GetCustomEnergyMaximum();
    float regeneration = GetCustomEnergyRegeneration();

    value = Clamp(value + regeneration * dtInSeconds, 0.f, maximum);

    if (customEnergy && customEnergyValue != NULL)
    {
      customEnergyValue->SetBaseValue(value);
    }
  }

  if ( GetFaction() == NDb::FACTION_NEUTRAL )
    WakeUp();

  return PFCreature::Step(dtInSeconds);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PFBaseHero::GetTotalNaftaEarned() const
{
  if ( IsClone() )
    return 0;

  float money = GetWorld()->GetStatistics()->GetMoney(this);
  return static_cast<int>(money);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PFBaseHero::GetKillStreak() const
{
  if (IsClone())
    return 0;

  if (!IsValid(pStatistics))
    return 0;

  return pStatistics->GetCurrentKillSpree();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PFBaseHero::GetDeathStreak() const
{
  if (IsClone())
    return 0;

  if (!IsValid(pStatistics))
    return 0;

  return pStatistics->GetCurrentDeathSpree();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PFBaseHero::GetTSliceSalary() const
{
  if ( IsClone() )
    return 0;

  float salary = GetWorld()->GetStatistics()->GetTSliceSalary(this);
  return static_cast<int>(salary);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseHero::SetTSliceSalary(float salary)
{
  if ( !IsClone() && GetWorld() && GetWorld()->GetStatistics() )
  {
    GetWorld()->GetStatistics()->SetTSliceSalary(this, salary);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseHero::AddTSliceSalary(float salary)
{
  if ( !IsClone() && GetWorld() && GetWorld()->GetStatistics() )
  {
    GetWorld()->GetStatistics()->AddTSliceSalary(this, salary);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseHero::OnDie()
{
  DismountSpecial();

  PFCreature::OnDie();

  customEnergyValue = NULL;
  customEnergyMaximum = NULL;
  customEnergyRegeneration = NULL;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class TowerHelpCaller : NonCopyable
{
public:
  TowerHelpCaller( const CPtr<PFBaseUnit>& pTarget, const CPtr<PFBaseUnit>& pCaller ) : pTarget( pTarget ), pCaller (pCaller) {}

  void operator() ( PFBaseUnit &unit )
  {
    const CPtr<PFBaseUnit> pUnit( &unit );

    if ( IsUnitValid( pUnit ) )
    {
      const CPtr<PFBaseUnit>& pUnitTarget = pUnit->GetCurrentTarget();

      // check if already attacking a hero (without alpha summon) or alpha summon
      if ( IsValid(pUnitTarget) && ( ( pUnitTarget->IsTrueHero() && !pUnitTarget->GetAlphaSummon() ) || pUnitTarget->IsAlphaSummon() ) )
        return;

      // attack hero's alphasummon if any
      const CPtr<PFBaseUnit>& pTargetNew = pTarget->GetAlphaSummon() ? pTarget->GetAlphaSummon() : pTarget;

      if ( pUnit->IsTargetInAttackRange( pTargetNew ) )
      {
        pUnit->AssignTarget(pTargetNew, false);
        pUnit->AddToPriorityTargets(pTarget);
      }
      else
        if ( pTarget->IsInRange(pUnit, pUnit->GetTargetingParams().nearbyRange) )
          pUnit->AddToPriorityTargets(pTarget);

    }
  }

  const CPtr<PFBaseUnit>& pTarget;
  const CPtr<PFBaseUnit>& pCaller;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseHero::CallForTowerHelp( const CPtr<PFBaseUnit>& pTarget )
{
  NI_VERIFY( IsUnitValid(pTarget), "Invalid Target!", return; );
  NI_ASSERT( GetWorld() && GetWorld()->GetAIWorld(), "Invalid world" );
  NI_ASSERT( pTarget->IsVulnerable() && pTarget->GetFaction() != GetFaction(), "Target must be valid!" );

	// Don't scream on targets that we can't autotarget on
	if (pTarget->CheckFlagType(NDb::UNITFLAGTYPE_FORBIDAUTOTARGETME))
		return;

  // Screaming
  TowerHelpCaller towerHelpCaller( pTarget, this );
  GetWorld()->GetAIWorld()->ForAllUnits(towerHelpCaller, UnitMaskingPredicate( 1 << GetFaction(), NDb::SPELLTARGET_TOWER ) );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFHeroBehaviour::OnDamage( const PFBaseUnitDamageDesc& desc )
{
  if ( IsTargetValid(desc.pSender) && desc.pSender->GetFaction() != pUnit->GetFaction() )
  {
    // call for tower help on any damage from heroes
    if ( desc.pSender->IsTrueHero() || desc.pSender->IsAlphaSummon() )
      static_cast<PFBaseHero*>(pUnit.GetPtr())->CallForTowerHelp( desc.pSender );

    if ( !desc.dontAttackBack && !desc.pSender->CheckFlagType(NDb::UNITFLAGTYPE_FORBIDAUTOTARGETME) && desc.pSender->IsVisibleForFaction(pUnit->GetFaction()) )
    {
      if( pUnit->IsIdle() && !pUnit->HasQueuedStates()
        && !pUnit->CheckFlagType(NDb::UNITFLAGTYPE_FORBIDSELECTTARGET)
        && !pUnit->CheckFlagType(NDb::UNITFLAGTYPE_FORBIDAUTOATTACK) )
      {
        pUnit->PushState( new PFBaseUnitAttackState( GetWorld(), pUnit, desc.pSender, true ) );
      }

      if ( screamCooldown < 0 && desc.pSender->IsTrueHero() )
      {
        screamCooldown = GetWorld()->GetAIWorld()->GetAIParameters().heroScreamDelay;
        DoScream(desc.pSender, ScreamTarget::ScreamForHelp); // call to help!
      }
    }
  }
}

bool PFHeroBehaviour::OnStep( float dtInSeconds )
{
  if ( screamCooldown >= 0 )
    screamCooldown -= dtInSeconds;

  return true;
}

void PFHeroBehaviour::OnTarget( const CPtr<PFBaseUnit>& pTarget, bool bStrongTarget )
{
  NI_ASSERT( IsTargetValid(pTarget), "Invalid Target!" );

  if ( pUnit->CheckFlagType(NDb::UNITFLAGTYPE_FORBIDATTACK) )
    return; // Attack forbid flag not empty!

  const IPFState* state = pUnit->GetCurrentState();
  if ( !state || state->GetTypeId() != PFBaseUnitAttackState::typeId || static_cast<const PFBaseUnitAttackState*>( state )->GetTarget() != pTarget )
    pUnit->EnqueueState( new PFBaseUnitAttackState(GetWorld(), pUnit, pTarget, bStrongTarget), true );
}

//////////////////////////////////////////////////////////////////////////
bool  PFBaseHero::OnDispatchApply(PFDispatch const &dispatch)
{
  const CPtr<PFBaseUnit> pSender = dispatch.GetSender();
  if ( IsTargetValid(pSender) && pSender->GetFaction() != GetFaction() )
  {

    // call for tower help on any damage from heroes
    if ( pSender->IsTrueHero() || pSender->IsAlphaSummon() )
      CallForTowerHelp( pSender );
  }
  return PFCreature::OnDispatchApply(dispatch);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float PFBaseHero::OnBeforeDamage(const DamageDesc &desc)
{
  if ( UnitMaskingPredicate( this, takeTypeUnit )( *desc.pSender ) )
    return ( desc.amount * takeModDmg );
	 
  return PFCreature::OnBeforeDamage( desc );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float PFBaseHero::OnDamage(const DamageDesc &desc)
{
  // TODO Titov : доделать
  if ( isolated )
    return 0;

  float ret;

  if ( UnitMaskingPredicate( this, takeTypeUnit )( *desc.pSender ) )
  {
    DamageDesc descNew;
    descNew = desc;
    descNew.amount *= takeModDmg;
	 
    ret = PFCreature::OnDamage(descNew);
  }
  else
    ret = PFCreature::OnDamage(desc);
  
  
  if (desc.amount!=0 )
  {
    NGameX::IAdventureScreen * screen = GetWorld()->GetIAdventureScreen();
    if (IsValid(screen))
      screen->OnHeroDamaged(this);
  }

  return ret;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseHero::OnAddGold(CPtr<PFBaseUnit> pSender, float amount, bool showGold /* = true */)
{
  PFCreature::OnAddGold(pSender, amount, showGold);

  //add only amount to the total earned hero money in the statistic.
  if ( !IsClone() && GetWorld() && GetWorld()->GetStatistics() )
  {
    GetWorld()->GetStatistics()->AddMoney(this, amount);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float PFBaseHero::OnHeal(CPtr<PFBaseUnit> pSender, float amount, bool ignoreHealingMods)
{
  float healedAmount = PFCreature::OnHeal(pSender, amount, ignoreHealingMods);

  if (!IsClone())
    if (PFWorld * pWorld = GetWorld())
      if (PFStatistics * pStatistics = pWorld->GetStatistics())
        pStatistics->AddHealedAmount(this, healedAmount);

  return healedAmount;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float PFBaseHero::GetTimeToRespawn() const
{
  if (!IsDead())
    return -1.0f;
  if (respawnDelay >= 0)
    return advanceRespawnDelay > 0 ? advanceRespawnDelay : 0.0f;
  return 0.0f;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseHero::RecalculateRedeemCost()
{
  if( IsDead() )
  {
    NDb::AILogicParameters const& params = GetWorld()->GetAIWorld()->GetAIParameters();
    NDb::Ptr<NDb::HeroRespawnParams> const& heroRespawnParams = GetWorld()->GetAIWorld()->GetHeroRespawnParams();

    const int level               = GetNaftaLevel();
    const float baseRespawndelay  = level * heroRespawnParams->heroRespawnDelayMultiplier;
    const float delay             = respawnDelay < 0.0f ? baseRespawndelay : respawnDelay;
    redeemCost                    = params.baseRedeemCost + ( level * params.redeemCostPerLevel ) * delay / baseRespawndelay;

    redeemCostRecalculateDelay    = params.redeemCostrecalculateTime;
  }
  else
  {
    redeemCost                    = 0.0f;
    redeemCostRecalculateDelay    = -1.0f;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseHero::RemoveCorpse()
{
	PFCreature::RemoveCorpse();
  if (isClone)
  {
    // die as creep
    Die();
    return;
  }

  UpdateHiddenState(false);
}

void PFBaseHero::StartRespawnTimer()
{
  if (!forbidRespawn)
  {
    NDb::Ptr<NDb::HeroRespawnParams> const& heroRespawnParams = GetWorld()->GetAIWorld()->GetHeroRespawnParams();
    const float sessionElapsedTime = GetWorld()->GetTimeElapsed() / 60.0f; // minutes

    respawnDelay        = heroRespawnParams->heroBaseRespawnTime + GetNaftaLevel() * heroRespawnParams->heroRespawnDelayMultiplier;
    
    const float overtime = heroRespawnParams->overtimeRespawnParams.overtime;

    if ( overtime < sessionElapsedTime )
    {
      const float respawnDelayForOvertime = heroRespawnParams->overtimeRespawnParams.respawnDelayForOvertime;
      respawnDelay     += respawnDelayForOvertime * ceil( sessionElapsedTime - overtime );
    }
    respawnDelay        = max( heroRespawnParams->heroMinRespawnTime , respawnDelay );

    respawnDelay       *= 1.0f + GetVariable( UnitVariables::szReviveTimeScale );
    respawnDelay       += GetVariable( UnitVariables::szReviveTimeShift );

    respawnDelay       = max( respawnDelay, GetWorld()->GetAIWorld()->GetAIParameters().heroAdvanceRespawnTime );
    respawnDelay       = max( respawnDelay, GetDeathParams()->deathTime);

    advanceRespawnDelay = max( respawnDelay - GetWorld()->GetAIWorld()->GetAIParameters().heroAdvanceRespawnTime, EPS_VALUE );
    resurrectParams     = ResurrectParams();
  }
}

void PFBaseHero::AdvanceResurrect()
{
  if (deadUnitLifeTime > 0)
    RemoveCorpse();

  // reset FSM
  Cleanup();

  // Register unit in AI world
  RegisterInAIWorld();

  // reset BasePathUnit
  TeleportTo( ResurrectParams::Base == resurrectParams.resurrectAt ? spawnPos.AsVec2D() : GetPosition().AsVec2D() );

  // notify client
  UpdateHiddenState(true);
  CALL_CLIENT(OnResurrect);

  advanceRespawnDelay = -1.0f;
}

void PFBaseHero::AddTalentActivatedWhileDead( CPtr<PFTalent> pTalent )
{
  if ( IsValid(pTalent) )
  {
    activatedWhileLastDeathtime.push_back( pTalent );
  }
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseHero::DoResurrect()
{
  RestoreClientObject();

  respawnDelay = -1.0f;

  StatisticService::RPC::SessionEventInfo emptyParams;
  LogSessionEvent(SessionEventType::Ressurection, emptyParams);

  // update health
  health = GetStatValue(NDb::STAT_LIFE)   * resurrectParams.healthPercent;
  energy = GetStatValue(NDb::STAT_ENERGY) * resurrectParams.energyPercent;


  for ( vector< CPtr<PFTalent> >::iterator iter = activatedWhileLastDeathtime.begin(); iter != activatedWhileLastDeathtime.end(); iter++ )
  {
    CPtr<PFTalent> pCurrent = *iter;
    if ( IsValid(pCurrent) )
    {
      if ( ( pCurrent->GetDBDesc()->flags & NDb::ABILITYFLAGS_APPLYTODEAD ) == 0 )
      {
        pCurrent->ApplyPassivePart( true );
      }
    }
  }
  activatedWhileLastDeathtime.clear();

  NI_ASSERT( GetWorld() && GetWorld()->GetAIWorld() , "World invalid!" );
  giveWorldGoldOffset = max( GetWorld()->GetAIWorld()->GetPrimeSettings().giveWorldPrimeRessurectDelay, giveWorldGoldOffset );

  OpenWarFog();

  OnRessurect();

  // restart behaviour on resurrect
  if ( !HasBehaviour() )
  {
    CObj<PFBaseBehaviour> pB( new PFHeroBehaviour( this ) );
    AddBehaviourOnTop( pB );
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseHero::DoStop()
{
  PFFsm::Cleanup();
  PFBaseMovingUnit::Stop();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PFBaseHero::GetOriginalTeamId() const
{
  return (originalFaction == NDb::FACTION_FREEZE) ? NCore::ETeam::Team1 : (originalFaction == NDb::FACTION_BURN) ? NCore::ETeam::Team2 : NCore::ETeam::None;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PFBaseHero::GetZZimaSex() const
{
  return playerGender;
  /*if ( IsValid(pPlayer) && !pPlayer->IsBot() && !g_zzSexSameAsGender )
  {
    return pPlayer->GetZZimaSex();
  }
  return IsMale() ? ZZSEX_MALE : ZZSEX_FEMALE;
  */
}


bool PFBaseHero::IsMale() const
{
  return (GetDbGender() == NDb::GENDER_MALE);
}

const wstring& PFBaseHero::GetPlayerName() const
{
  return GetWorld()->GetIAdventureScreen()->GetPlayerName( playerId );
}

const wstring & PFBaseHero::GetDescription() const
{

  const NDb::HeroSkin* currentSkin = GetHeroSkin();

  if (currentSkin && !currentSkin->heroName.GetText().empty())
    return currentSkin->heroName.GetText();

  switch ( GetOriginalFaction() )
  {
    case NDb::FACTION_FREEZE:
      return pDbHero->heroNameA.GetText();

    case NDb::FACTION_BURN:
      return pDbHero->heroNameB.GetText();

    default:
      return PFCreature::GetDescription();
  }
}

const NDb::UnitDeathParameters* PFBaseHero::GetDeathParams() const
{
  const NDb::HeroSkin* currentSkin = GetHeroSkin();

  if (currentSkin && IsValid(currentSkin->deathParameters))
    return currentSkin->deathParameters;

  return PFCreature::GetDeathParams();
}

const NDb::Texture * PFBaseHero::GetUiAvatarImage() const
{
  const NDb::HeroSkin* currentSkin = GetHeroSkin();
  
  switch ( GetOriginalFaction() )
  {
    case NDb::FACTION_FREEZE:
      return (currentSkin && currentSkin->heroImageA) ? currentSkin->heroImageA : pDbHero->heroImageA;

    case NDb::FACTION_BURN:
      return (currentSkin && currentSkin->heroImageB) ? currentSkin->heroImageB : pDbHero->heroImageB;

    default:
      return pDbHero->image;
  }
}



const NDb::Texture * PFBaseHero::GetUiAvatarImage(const NDb::Hero* dbHeroPtr, NDb::EFaction faction, const string& skinId)
{
  const NDb::HeroSkin* currentSkin = GetHeroSkin(dbHeroPtr, skinId);

  switch ( faction )
  { 
  case NDb::FACTION_FREEZE:
    return (currentSkin && currentSkin->heroImageA) ? currentSkin->heroImageA : dbHeroPtr->heroImageA;

  case NDb::FACTION_BURN:
    return (currentSkin && currentSkin->heroImageB) ? currentSkin->heroImageB : dbHeroPtr->heroImageB;

  default:
    return dbHeroPtr->image;
  }
}

const NDb::HeroSkin* PFBaseHero::GetHeroSkin(const NDb::Hero* dbHeroPtr, const string& skinId)
{
  // найдем нужный скин, если юзер выбрал его для игры
  if (!skinId.empty() && skinId != "default")
  {
    vector<NDb::Ptr<NDb::HeroSkin>>::const_iterator it = dbHeroPtr->heroSkins.begin();
    for ( ; it != dbHeroPtr->heroSkins.end(); ++it )
    {
      if ((*it)->persistentId == skinId)
        return *it;
    }
  }
  
  return 0;

}

const NDb::Texture * PFBaseHero::GetUiMinimapImage() const
{
  switch ( GetOriginalFaction() )
  {
  case NDb::FACTION_FREEZE:
    return pDbHero->minimapIconA;

  case NDb::FACTION_BURN:
    return pDbHero->minimapIconB;

  default:
    return pDbHero->image;
  }
}



void PFBaseHero::DropCooldowns( DropCooldownParams const& dropCooldownParams )
{
  DropAbilitiesCooldowns( dropCooldownParams );

  if (0 != (dropCooldownParams.flags & NDb::ABILITYIDFLAGS_CONSUMABLES))
  {
    DropConsumablesCooldowns( dropCooldownParams );
  }
}

void PFBaseHero::DropImpulsesCooldowns()
{
  NGameX::AdventureScreen* pAdventureScreen = NGameX::AdventureScreen::Instance();
  NI_VERIFY( IsValid( pAdventureScreen ), "Failed to retreive the AdventureScreen!", return );

  ImpulsiveBuffsManager* pImpulsiveBuffsManager = pAdventureScreen->GetImpulseBuffsManager();
  NI_VERIFY( IsValid( pImpulsiveBuffsManager ), "Failed to retreive the ImpulsiveBuffsManager!", return );

  pImpulsiveBuffsManager->ResetAllCooldowns();
}


// http://SITE - No more XP
//const int   PFBaseHero::GetExperience() const
//{
//  return static_cast<int>(Clamp(experience, 0.0f, static_cast<float>(GetLevelMaxExperience())));
//}
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//const int   PFBaseHero::GetLevelMaxExperience() const
//{
//  CPtr<PFAIWorld> pAIWorld = GetWorld()->GetAIWorld();
//  const int level          = GetLevel();
//  const int maxLevel       = pAIWorld->GetMaxHeroLevel();
//
//  return pAIWorld->GetHeroExperience4Level( (level < maxLevel) ? level + 1 : level);
//}

const int & PFBaseHero::GetLevelMaxExperienceRef() const // for namemap
{
  static int level;

  // level = GetLevelMaxExperience(); // http://SITE - No more XP
  level = 0;

  return level;
}

const int   PFBaseHero::GetLevelMaxDevPoints() const
{
  CPtr<PFAIWorld> pAIWorld = GetWorld()->GetAIWorld();
  const int level          = GetNaftaLevel();
  const int maxLevel       = pAIWorld->GetMaxHeroLevel();

  return pAIWorld->GetHeroDevPoints4Level( (level < maxLevel) ? level + 1 : level);
}

const int & PFBaseHero::GetLevelMaxDevPointsRef() const
{
  static int level;

  level = GetLevelMaxDevPoints();
  return level;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// http://SITE - No more XP
//const float PFBaseHero::GetLevelExperiencePercent() const
//{
//  const float levelExp = GetWorld()->GetAIWorld()->GetHeroExperience4Level( GetLevel() );
//  const float expValue = Clamp(experience - levelExp, 0.0f, static_cast<float>(GetLevelMaxExperience()));
//  const float maxExp   = GetLevelMaxExperience() - levelExp ;
//
//  return maxExp < EPS_VALUE ? 1.0f : (expValue / maxExp);
//}

const float PFBaseHero::GetLevelDevPointsPercent() const
{
  const int levelDevPoints = GetWorld()->GetAIWorld()->GetHeroDevPoints4Level( GetNaftaLevel() );
  const int devPointsValue = Clamp( GetDevPoints() - levelDevPoints, 0, GetLevelMaxDevPoints() );
  const int maxDevPoints = GetLevelMaxDevPoints() - levelDevPoints;

  return maxDevPoints < 0 ? 1.0f : ( 1.0f * devPointsValue / maxDevPoints );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// http://SITE - No more XP
//void PFBaseHero::AddExperience(float value)
//{
//  NI_VERIFY( !(value < 0.0f), "Trying to take experience away", return; );
//
//  CPtr<PFAIWorld> pAIWorld = GetWorld()->GetAIWorld( );
//  experience = min( experience + value * GetStatValue(NDb::STAT_GAINEDEXPERIENCEMULTIPLIER),
//      pAIWorld->GetHeroExperience4Level( pAIWorld->GetMaxHeroLevel() ) );
//  NI_ASSERT(experience >= 0.0f, "Insane experience");
//  int nLevelUps = CountLevelups();
//  NI_ASSERT(nLevelUps >= 0 && nLevelUps <= 20, "Insane levelups");
//  DoLevelups(nLevelUps);
//}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PFBaseHero::CountLevelups()
{
  CPtr<PFAIWorld> pAIWorld    = GetWorld()->GetAIWorld();
  const int currentLevel      = GetNaftaLevel();
  const int maxLevel          = pAIWorld->GetMaxHeroLevel();
  // const int currentExperience = static_cast<int>(experience); // http://SITE - No more XP
  const int currentDevPoints  = GetDevPoints();

  int levelUps = 0;
  for(int i = currentLevel + 1; i <= maxLevel; ++i)
  {
    // if( pAIWorld->GetHeroExperience4Level( i ) <= currentExperience ) // http://SITE - No more XP
    if( pAIWorld->GetHeroDevPoints4Level( i ) <= currentDevPoints )
      ++levelUps;
  }

  return levelUps;
}

void PFBaseHero::OnLevelUp()
{
  PFCreature::OnLevelUp();
  if (GetNaftaLevel() == 1)
    return;

  StatisticService::RPC::SessionEventInfo params;
  params.intParam1 = GetNaftaLevel();
  LogSessionEvent(SessionEventType::LevelUp, params);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseHero::AwardForKill(CPtr<PFBaseUnit> const& pVictim, const float money, bool fromVictim )
{
  if ( fromVictim )
    OnAddGold( pVictim, money, true );
  else
    OnAddGold( this, money, true );
}

void PFBaseHero::OnKill( CPtr<PFBaseUnit> const& pVictim, bool lastHit )
{
  CALL_CLIENT_2ARGS( OnKill, pVictim, lastHit );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseHero::DebugDie()
{
  Die();
  bool isValid = IsValid(this);
  isValid;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseHero::Resurrect( const ResurrectParams& params)
{
  NI_VERIFY( IsDead() && !IsResurrecting(), "Unable to ressurect hero when dead or ressurecting", return );
  if ( deadUnitLifeTime > 0.0f )
  {
    RemoveCorpse();
  }

  RestoreClientObject();
  RestoreSceneObject();

  unitFallUndergroundOffset = deadUnitLifeTime = -1.0f;
  resurrectParams           = params;
  respawnDelay              = GetWorld()->GetAIWorld()->GetAIParameters().heroAdvanceRespawnTime + EPS_VALUE;
  advanceRespawnDelay       = EPS_VALUE;

  // restart behaviour on resurrect
  if ( !HasBehaviour() )
  {
    CObj<PFBaseBehaviour> pB( new PFHeroBehaviour( this ) );
    AddBehaviourOnTop( pB );
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseHero::OnScream( const CPtr<PFBaseUnit> pTarget, ScreamTarget::ScreamType st )
{
  // not reacting on scream!
  // PFCreature::OnScream();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CVec3 PFBaseHero::GetPetEscortPosition() const
{
	CVec2 offset = -GetMoveDirection();
	Normalize(&offset);
	offset *= 8.0f;
	return GetPosition() + CVec3(offset.x, offset.y, 0.f);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseHero::Emote(NDb::EEmotion emotion)
{
  CALL_CLIENT_1ARGS(OnEmote, emotion);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const wstring& PFBaseHero::GetTeamName() const
{
  return GetFactionName();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseHero::DismountSpecial()
{
  if( NULL != pMount )
  {
    if( IsValid(pMount) )
    {
      pMount->DetachUnit();
      if ( !pMount->IsTrueHero() )
      {
        pMount->DropStates();
      }
    }

    OnUnmountSpecial();
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseHero::OnMountSpecial( CPtr<NWorld::PFBaseMovingUnit> const& pMountUnit, bool _canControlMount )
{
  if(NGameX::PFBaseClientHero* pClient = ClientObject())
  {
    pClient->OnMountSpecial( pMountUnit );

    if( NGameX::AdventureScreen* adventure = NGameX::AdventureScreen::Instance() )
      if ( adventure->GetCamera()->IsObservedObject( pClient ) )
        adventure->GetCamera()->SetObservedObject( pMountUnit->ClientObject() );
  }

  AddFlag(NDb::UNITFLAG_FORBIDMOVE);
  PFHFSM::Cleanup();

  pMount = pMountUnit;
  canControlMount = _canControlMount;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFBaseHero::IsRecommended( int stat ) const
{
  const nstl::vector<NDb::EStat>& recommendedStats = pDbHero->recommendedStats;
  return (recommendedStats.find(static_cast<NDb::EStat>(stat)) != recommendedStats.end());
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseHero::OnUnmountSpecial()
{ 
  if(NGameX::PFBaseClientHero* pClient = ClientObject())
  {
    pClient->OnUnmountSpecial();

    if( NGameX::AdventureScreen* adventure = NGameX::AdventureScreen::Instance() )
      if ( adventure->GetCamera()->IsObservedObject( pMount->ClientObject() ) && IsLocal() )
        adventure->GetCamera()->SetObservedObject( pClient );
  }

  RemoveFlag(NDb::UNITFLAG_FORBIDMOVE);

  pMount = NULL;
  canControlMount = false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float GetDistance2Line(CVec2 const& p, CVec2 const& begin, CVec2 const& end)
{
  const float distStart = fabs( begin - p );
  const float distEnd   = fabs( end - p );

  if(end == begin)
    return distStart;

  if( ( p - begin ).Dot( end - begin ) <= 0.0f || 0.0f <= ( p - end ).Dot( end - begin ) )
    return distStart < distEnd ? distStart : distEnd;

  const float divider  = sqrt( pow(end.x - begin.x, 2) + pow(end.y - begin.y, 2) );
  float distance       =
    (begin.y - end.y) * p.x + (end.x - begin.x) * p.y + ( begin.x * end.y - begin.y * end.x );

  distance /= divider;

  return fabs(distance);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NDb::ERoute PFBaseHero::GetNearestRoute(float* pDistance) const
{
  int nearestRoute      = -1;
  float distance        = FP_MAX_VALUE;
  CVec2 const vPosition = CVec2(position.X(), position.Y());

  PFWorld const* pWorld = GetWorld();
  if( PFWorldNatureMap const* pNatureMap = pWorld ? pWorld->GetNatureMap() : NULL)
  {
    for (int iRoute = 0; iRoute < NDb::KnownEnum<NDb::ENatureRoad>::sizeOf; ++iRoute)
    {
      //if( vector<CVec2> const* pRoad = pNatureMap->GetRoad((NDb::ENatureRoad)iRoute) )
      {
        vector<CVec2> const& road = pNatureMap->GetLogicRoad((NDb::ENatureRoad)iRoute);
        vector<CVec2>::const_iterator route_begin = road.begin();
        vector<CVec2>::const_iterator route_end   = road.end();

        vector<CVec2>::const_iterator begin = route_begin, end = route_begin;
        advance(end, 1);

        for(; end != route_end; ++begin, ++end)
        {
          const float length = GetDistance2Line(vPosition, *begin, *end);
          if(length < distance)
          {
            distance     = length;
            nearestRoute = iRoute;
          }
        }
      }
    }
  }

  if( NULL != pDistance)
    *pDistance = distance;

  NDb::ERoute result = NDb::ROUTE_UNASSIGNED;
  switch(nearestRoute)
  {
  case 0:
    result = NDb::ROUTE_TOP;
    break;
  case 1:
    result = NDb::ROUTE_CENTER;
    break;
  case 2:
    result = NDb::ROUTE_BOTTOM;
    break;
  };

  return result;
}

//////////////////////////////////////////////////////////////////////////
bool PFBaseHero::IsSlotValid( int slot ) const
{
  return slot>=0 && slot<consumables.size();
}



int PFBaseHero::GetSlotCount() const
{
  return consumables.size();
}



PFConsumable const* PFBaseHero::GetConsumable(int slot) const
{
  NI_VERIFY( IsSlotValid(slot), "Invalid slot index!", return 0; );
  return consumables[slot];
}



void PFBaseHero::DropConsumable( int slot, const CVec2& target)
{
  NI_VERIFY( IsSlotValid(slot), "Invalid slot index!", return; );

  CObj<PFConsumable>& pConsumable = consumables[slot];
  NI_VERIFY( pConsumable, "There is no consumable in slot!", return; );

  NDb::Consumable const* pDesc = pConsumable->GetDBDesc();
  CObj<PFConsumableChest> pChest = PFConsumableChest::Create( GetWorld(), pDesc, target, pConsumable->GetQuantity(), pDesc ? pDesc->gameObject : NULL );
  pConsumable = NULL;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseHero::AddConsumableCooldown(CObj<PFConsumable> const& pConsumable)
{
  if ( rgConsumablesAbilities.end() == find( rgConsumablesAbilities.begin(), rgConsumablesAbilities.end(), pConsumable->GetAbility() ))
    rgConsumablesAbilities.push_back( pConsumable->GetAbility() );
}

void PFBaseHero::OnSerialize(IBinSaver& f)
{
  if (f.IsReading())
  {
    // NOTE: customEnergy может быть true, только если уникальный ресурс определен и проверен
    if (customEnergy)
      InitializeCustomEnergyVariables();
  }
}

void PFBaseHero::InitializeCustomEnergyVariables()
{
  NI_VERIFY(customEnergy, "Invariant", return);

  const NDb::Ptr<NDb::HeroResource> uniqueResource = pDbHero->uniqueResource;

  NI_VERIFY(IsValid(uniqueResource), "Invariant", return);

  const string& varValue = uniqueResource->formulaNameValue;
  const string& varMaximum = uniqueResource->formulaNameMaximum;
  const string& varRegeneration = uniqueResource->formulaNameRegeneration;

  customEnergyValue = SearchVariableVWM(varValue.c_str());
  customEnergyMaximum = SearchVariableVWM(varMaximum.c_str());
  customEnergyRegeneration = GetVariableVWM(varRegeneration.c_str());

  // TODO: ensure unique?
  const int provider = std::numeric_limits<int>::min() + 3;

  if (!customEnergyValue)
  {
    customEnergyValue = GetVariableVWM(varValue.c_str());
    customEnergyValue->AddModifier(0.f, 0.f, provider, true, NDb::STATCONSTRAINT_LOWERLIMIT);
  }

  if (!customEnergyMaximum)
  {
    customEnergyMaximum = GetVariableVWM(varMaximum.c_str());
    customEnergyMaximum->AddModifier(0.f, 0.f, provider, true, NDb::STATCONSTRAINT_LOWERLIMIT);
  }
}

bool PFBaseHero::CanUseConsumable(int slot) const
{
  if( !IsSlotValid(slot) )
    return false;

  CObj<PFConsumable> const& pConsumable = consumables[slot];
  if( !pConsumable || !pConsumable->GetQuantity() )
    return false;

  CObj<PFConsumableAbilityData> const& pAbility = pConsumable->GetAbility();
  if( !pAbility || ( pAbility->GetCurrentCooldown() > EPS_VALUE ) )
    return false;

  return CanUseConsumables();
}

bool PFBaseHero::CanUseConsumables() const
{
  return !CheckFlagType( NDb::UNITFLAGTYPE_FORBIDUSECONSUMABLES );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CObj<PFAbilityInstance> PFBaseHero::UseConsumable( CObj<PFConsumable>& pConsumable, const Target& target, bool isLocal )
{
  if ( isLocal && pConsumable->IsPet() )
  {
    int persId = Crc32Checksum().AddString( pConsumable->GetDBDesc()->persistentId.c_str() ).Get();
    const NGlobal::VariantValue val = NGlobal::GetVar( "current_pet" );
    if ( persId == val.GetInt64() )
      NGlobal::SetVar( "current_pet", -1, STORAGE_USER );      
    else
      NGlobal::SetVar( "current_pet", persId, STORAGE_USER );      
  }

  pConsumable->GetAbility()->SetUsingConsumable( pConsumable );
  CObj<PFAbilityInstance> pInstance = CreateAbilityInstance( pConsumable->GetAbility(), target );
  if ( pInstance )
  {
    // It is supposed that only one of same consumables can be used at a moment
    EventHappened( PFBaseUnitAbilityStartEvent( pInstance.GetPtr() ) );
    PFAbilityData const* pAbilityData = pInstance->GetData();

    ELookKind lookAtTarget = pInstance->IsCasterShouldLookAtTarget();
    if ( lookAtTarget != DontLook )
    {
      SetMoveDirection( target.AcquirePosition().AsVec2D() );
    }

    CALL_CLIENT_6ARGS( OnUseAbility, pAbilityData->GetAbilityNode(), pAbilityData->GetAbilityMarker(), target, pAbilityData->GetTimeOffset( true ), lookAtTarget, pAbilityData->IsAbilitySupposedToStopUnit() );

    return pInstance;
  }

  return NULL;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CObj<PFAbilityInstance> PFBaseHero::UseConsumable( int slot, const Target& target, bool isLocal )
{
  if( CanUseConsumable( slot ) )
  {
    return UseConsumable( consumables[slot], target, isLocal );
  }

  return NULL;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFBaseHero::TakeConsumable( const NDb::Consumable * pDBDesc, int quantity, NDb::EConsumableOrigin origin /*= NDb::CONSUMABLEORIGIN_DEFAULT*/, int slot /* = -1 */ )
{
  NI_ASSERT( !IsSlotValid(slot) || CanPutConsumableIntoSlot(pDBDesc, quantity, slot), "Cannot put consumable into given slot!" );

  if ( !IsSlotValid( slot ) )
    slot = GetSlotForConsumable( pDBDesc, quantity );

  if ( !IsSlotValid( slot ) )
    return false;

  CObj<PFConsumable>& pConsumable = consumables[slot];

  if ( !pConsumable )
  {
    CObj<PFConsumableAbilityData> pAbility = GetConsumableAbility( pDBDesc );
    pConsumable = new PFConsumable( pAbility, quantity );
    if ( !pAbility->HasPassiveInstance() )
      pAbility->ApplyPassivePart(true);
  }
  else
  {
    pConsumable->AddQuantity(quantity);
  }

  if ( origin != NDb::CONSUMABLEORIGIN_DEFAULT )
    EventHappened( PFHeroEventConsumableObtained( pDBDesc, origin ) );

  return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseHero::SwapConsumables(int id1, int id2)
{
  NI_ASSERT( IsSlotValid(id1) && IsSlotValid(id2), "Invalid slot index!" );
  swap( consumables[id1], consumables[id2] );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFBaseHero::RemoveConsumable(int slot)
{
  NI_ASSERT( IsSlotValid(slot), "Invalid slot index!" );

  CObj<PFConsumable>& pConsumable = consumables[slot];
  NI_VERIFY(pConsumable, "There is no consumable in given slot!", return false; );

  pConsumable = NULL;
  return true;
}

void PFBaseHero::RemoveConsumable( PFConsumable const* pConsumable )
{
  for ( int slot = 0; slot < consumables.size(); ++slot )
  {
    if ( consumables[slot] == pConsumable )
    {
      consumables[slot] = NULL;
      return;
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFBaseHero::CanPutConsumableIntoSlot( const NDb::Consumable * pDBDesc, int quantity, int slot) const
{
	NI_VERIFY( IsSlotValid(slot), NStr::StrFmt( "Slot index (%d) out of bounds (0..%d)", slot, consumables.size() ), return false );
  CObj<PFConsumable> const& pConsumable = consumables[slot];
  return !pConsumable || ( (pConsumable->GetDBDesc() == pDBDesc) && (pConsumable->GetQuantity() + quantity <= pConsumable->GetMaxQuantity()) );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PFBaseHero::GetSlotForConsumable( const NDb::Consumable * pDBDesc, int quantity ) const
{
  int emptySlot = -1;
  for ( int slot = 0; slot < consumables.size(); ++slot )
  {
    const CObj<PFConsumable> & pConsumable = consumables[slot];
    if ( pConsumable )
    {
      if ( ( pConsumable->GetDBDesc() == pDBDesc ) && ( pConsumable->GetQuantity() + quantity <= pConsumable->GetMaxQuantity() ) )
        return slot;
    }
    else
      if ( emptySlot == -1 )
        emptySlot = slot;
  }

  return emptySlot;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFBaseHero::CanTakeConsumable( const NDb::Consumable * pDBDesc, int quantity ) const
{
  return GetSlotForConsumable( pDBDesc, quantity ) >= 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseHero::DropConsumablesCooldowns( DropCooldownParams const& dropCooldownParams )
{
  for ( int slot = 0; slot < consumables.size(); ++slot )
  {
    if ( CObj<PFConsumable>& pConsumable = consumables[slot] )
    {
      CObj<PFConsumableAbilityData> const& pData = pConsumable->GetAbility();
      if ( pData != dropCooldownParams.exceptAbility )
        pData->DropCooldown(true, dropCooldownParams.cooldownReduction, dropCooldownParams.reduceByPercent);
    }
  }
}


CObj<PFConsumableAbilityData> PFBaseHero::GetConsumableAbility( const NDb::Ability * pDBDesc )
{
  for ( int i = 0; i < rgConsumablesAbilities.size(); ++i )
    if ( pDBDesc == rgConsumablesAbilities[i]->GetDBDesc() )
      return rgConsumablesAbilities[i];

  for ( int slot = 0; slot < consumables.size(); ++slot )
  {
    CObj<PFConsumable>& pConsumable = consumables[slot];
    if ( pConsumable && pConsumable->GetDBDesc() == pDBDesc )
      return pConsumable->GetAbility();
  }

  rgConsumablesAbilities.push_back( new PFConsumableAbilityData( this, pDBDesc, NDb::ABILITYTYPEID_CONSUMABLE ) );
  CObj<PFConsumableAbilityData>& pAbilityData = rgConsumablesAbilities.back();
  AddConsumableToGroup( pAbilityData );

  return pAbilityData;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFBaseHero::CanStackConsumables( int src, int dst ) const
{
  PFConsumable const* pSrc = GetConsumable(src);
  PFConsumable const* pDst = GetConsumable(dst);

  if( NULL != pSrc && NULL != pDst )
    if( pSrc->GetDBDesc() == pDst->GetDBDesc() && CanPutConsumableIntoSlot( pDst->GetDBDesc(), pSrc->GetQuantity(), dst ) )
      return true;

  return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFBaseHero::StackConsumables( int src, int dst )
{
  if( false == CanStackConsumables( src, dst) )
    return false;

  PFConsumable const* pConsumable = GetConsumable(src);
  if( TakeConsumable(pConsumable->GetDBDesc(), pConsumable->GetQuantity(), NDb::CONSUMABLEORIGIN_DEFAULT, dst) )
  {
    RemoveConsumable(src);
    return true;
  }

  NI_ALWAYS_ASSERT("Failed to stack consumables when was detected it`s possible!");
  return false;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseHero::SellConsumable(int slot)
{
  PFConsumable const *pConsumable = GetConsumable(slot);
  NI_VERIFY(NULL != pConsumable, "Invalid consumable index", return);

  AddGold( pConsumable->GetMoneyCost() * pConsumable->GetQuantity() / 2 );

  RemoveConsumable(slot);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float PFBaseHero::GetConsumableCost( const NDb::Consumable * pDBDesc ) const
{
  return GetModifiedAbilityValue( pDBDesc->naftaCost, NDb::ABILITYMODMODE_NAFTACOST, NDb::ABILITYTYPEID_CONSUMABLE, pDBDesc );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseHero::RestartGroupCooldowns( PFConsumableAbilityData const* pConsumableAD )
{
  NDb::ConsumableGroup const* group = pConsumableAD->GetGroup();

  if ( !group )
    return;

  for ( vector<NDb::Ptr<NDb::Consumable>>::const_iterator it = group->consumables.begin(); it != group->consumables.end(); ++it )
  {
    PFConsumableAbilityData* pCons = GetConsumableAbility( *it );
    if ( pCons != pConsumableAD && pCons->GetCurrentCooldown() < group->cooldown )
    {
      pCons->PFAbilityData::RestartCooldown( group->cooldown );
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseHero::AddConsumableToGroup( PFConsumableAbilityData* pConsumableAD )
{
  typedef vector<NDb::ConsumableGroup> ConsGroups;

  NDb::Ptr<NDb::ConsumableGroupList> const& pDBConsGroups = GetWorld()->GetAIWorld()->GetAIParameters().consumableGroups;
  if ( !pDBConsGroups )
    return;

  ConsGroups const& consGroups = pDBConsGroups->groups;

  for ( ConsGroups::const_iterator it = consGroups.begin(); it != consGroups.end(); ++it )
  {
    vector<NDb::Ptr<NDb::Consumable>> vecCons = it->consumables;
    for ( vector<NDb::Ptr<NDb::Consumable>>::const_iterator descIt = vecCons.begin(); descIt != vecCons.end(); ++descIt )
    {
      if ( (*descIt)->GetDBID() == pConsumableAD->GetDBDesc()->GetDBID() )
      {
        pConsumableAD->SetGroup( it );
      }
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseHero::AddAbilityModifier( PFApplAbilityMod* appl )
{
  rgAbilitiesModifiers.addLast(appl);
  RecacheAbilitiesModifiers();
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseHero::RemoveAbilityModifier( PFApplAbilityMod* appl )
{
  PFApplAbilityMod::Ring::remove(appl);
  RecacheAbilitiesModifiers();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseHero::RecacheAbilitiesModifiers()
{
  abilityModsActualizationTime = GetWorld()->GetTimeElapsed();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float PFBaseHero::GetModifiedAbilityValue( float value, NDb::EAbilityModMode mode, NDb::EAbilityTypeId abilityType, NDb::Ptr<NDb::Ability> const& dbAbility ) const
{
  float add = 0.0f, mul = 1.0f;

  for ( ring::Range<PFApplAbilityMod::Ring> it(rgAbilitiesModifiers); it; ++it )
  {
    PFApplAbilityMod *pAppl = &(*it);
    NI_VERIFY( IsValid(pAppl), "Invalid applicator in AbilityMods ring!", continue );
    pAppl->AddModifier( add, mul, mode, abilityType, dbAbility );
  }

  return value * mul + add;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseHero::LogSessionEvent( SessionEventType::EventType eventType, const StatisticService::RPC::SessionEventInfo & params )
{
  NGameX::IAdventureScreen * adventureScreen = GetWorld()->GetIAdventureScreen();

  NI_VERIFY( IsValid(adventureScreen), "wtf?", return);

  adventureScreen->LogSessionEvent(this, eventType, params);
}

void PFBaseHero::LogSessionEvent( SessionEventType::EventType eventType, const NDb::DbResource *  resource)
{
  StatisticService::RPC::SessionEventInfo params;
  params.intParam1 = resource->GetDBID().GetHashKey();
  params.intParam2 = GetNaftaLevel();
  LogSessionEvent(eventType, params);
}

void PFBaseHero::LogSessionEvent( SessionEventType::EventType eventType, int intParam1)
{
  StatisticService::RPC::SessionEventInfo params;
  params.intParam1 = intParam1;
  params.intParam2 = GetNaftaLevel();
  LogSessionEvent(eventType, params);
}

void PFBaseHero::LoggTimeSliceIfNeeded( float deltaTime )
{
  float slicePeriod = GetWorld()->GetAIWorld()->GetAIParameters().heroStatisticsParams.timeSlicePeriod;
  
  timeSinceLastSlice += deltaTime;
 
  if (timeSinceLastSlice >= slicePeriod)
  {
    timeSinceLastSlice -= slicePeriod;
    slicesCount++;

    StatisticService::RPC::SessionEventInfo params;
    params.intParam1 = slicesCount*slicePeriod/60;
    params.intParam2 = GetNaftaLevel();
    //This parameter was missed during previous development, but probably will be needed in the future
    //params.intParam3 = GetGold();
    params.intParam3 = GetTotalNaftaEarned();
    params.intParam4 = GetTSliceSalary();   // Only nafta earned as a salary per current time slice

    LogSessionEvent(SessionEventType::TimeSliceResults, params);

    // Reset per time slice nafta statistics
    SetTSliceSalary(0.0f);

    NGameX::AdventureScreen * adventureScreen = NGameX::AdventureScreen::Instance();
    NI_VERIFY( IsValid(adventureScreen), "Failed to retreive the AdventureScreen!", return);
    adventureScreen->OnTimeSlice();
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseHero::ForAllClones( CloneFunc& cloneFunc )
{
  for ( vector<CloneInfo>::iterator iter = clones.begin(); iter != clones.end(); iter++ )
  {
    PFBaseHero* pClone = iter->clone;
    NI_VERIFY( pClone->IsClone(), NStr::StrFmt( "Hero \"%s\" is not clone!", NStr::ToMBCS( GetDescription() ).c_str() ), return );
    cloneFunc( pClone );
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseHero::DoLevelups( int count, float statsBonusBudget /* = 0.0f */ )
{
  if ( !IsClone() )
  {
    PFBaseUnit::DoLevelups( count, statsBonusBudget );

    struct LevelSynchronizer: CloneFunc, ISummonAction
    {
      int level;

      LevelSynchronizer( int _level ) : level ( _level ) { }
      void operator()( PFBaseUnit* pUnit ) { pUnit->SetNaftaLevel( level ); }
      void operator()( PFBaseHero* pClone ) { operator()( (PFBaseUnit*)pClone ); }
    } f( naftaLevel );
    ForAllSummons( f, NDb::SUMMONTYPE_PRIMARY );
    ForAllSummons( f, NDb::SUMMONTYPE_SECONDARY );
    ForAllClones( f );
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float PFBaseHero::GetUltimateCD() const
{ 
  const int levels = NDb::KnownEnum<NDb::ETalentLevel>::SizeOf();
  const int slots  = NDb::KnownEnum<NDb::ETalentSlot>::SizeOf();


  for ( int i = 0; i < levels; i++ )
  {
    for ( int j = 0; j < slots; j++ )
    {
      PFTalent* currentTalent = GetTalent( i, j );
      if ( currentTalent && currentTalent->IsUltimate() && currentTalent->IsTalentBought() && currentTalent->GetCooldown() > 0.0f )
      {
        return currentTalent->GetCurrentCooldown() / currentTalent->GetCooldown();
      }
    }
  }
  

  return -1.0f;
}

IMiscFormulaPars const* PFBaseHero::GetTalent(const char* id) const
{
  return GetTalentById( id );
}

PFTalent* PFBaseHero::GetTalentById(const char* id) const
{
  NI_PROFILE_FUNCTION
  
  const int levels = NDb::KnownEnum<NDb::ETalentLevel>::SizeOf();
  const int slots  = NDb::KnownEnum<NDb::ETalentSlot>::SizeOf();

  for ( int i = 0; i < levels; i++ )
  {
    for ( int j = 0; j < slots; j++ )
    {
      PFTalent* currentTalent = GetTalent( i, j );
      if ( currentTalent && strcmp( currentTalent->GetTalentDesc()->persistentId.c_str(), id ) == 0 )
      {
        return currentTalent;
      }
    }
  }
  return NULL;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFBaseHero::HasTalentFromPack( const char* id ) const
{
  const int levels = NDb::KnownEnum<NDb::ETalentLevel>::SizeOf();
  const int slots  = NDb::KnownEnum<NDb::ETalentSlot>::SizeOf();

  for ( int i = 0; i < levels; i++ )
  {
    for ( int j = 0; j < slots; j++ )
    {
      PFTalent* currentTalent = GetTalent( i, j );
      if ( currentTalent && currentTalent->GetPack() && strcmp( currentTalent->GetPack()->id.c_str(), id ) == 0 )
      {
        return true;
      }
    }
  }
  return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseHero::OnGameFinished( const NDb::EFaction failedFaction )
{
  struct GameFinished
  {
    NDb::EFaction failedFaction;

    GameFinished( NDb::EFaction _failedFaction ) : failedFaction(_failedFaction) {}
    void operator()( NWorld::PFAchievBase* pAchiev )
    {
      pAchiev->OnVictory( failedFaction );
    }

  } gameFinished( failedFaction );

  if ( GetHeroStatistics() )
    GetHeroStatistics()->ForAllAchievements( gameFinished );

  PFCreature::OnGameFinished( failedFaction );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseHero::SetHappy()
{
  if ( IsMounted() )
  {
    DismountSpecial();
  }

  PFCreature::SetHappy();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseHero::OnStopped()
{
  PFCreature::OnStopped();

  if(!IsDead() && !IsClone())
  {
    //DevTrace("%08x : PFBaseHero::OnStopped()", int(this));
    if(!GetCurrentState())
      PushState(new PFHeroSuspendState( this, true ) );
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseHero::OnTargetDropped()
{
  PFCreature::OnTargetDropped();

  if(!IsDead() && !IsClone())
  {
      PushState(new PFHeroSuspendState( this, false ) );
  }

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseHero::NotifyMoving( bool teleported )
{
  PFBaseMovingUnit::NotifyMoving(teleported);
  if (teleported)
    OnStopped();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseHero::OnScrollReceived()
{
  CALL_CLIENT( OnScrollReceived );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseHero::OnGlyphPickUp( const PFGlyph* pGlyph )
{
  if ( GetHeroStatistics() )
    GetHeroStatistics()->AddGlyphPickuped();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float PFBaseHero::GetHeroStatisticsValue( HeroStatisticsId heroStatId ) const
{
  if ( IsClone() )
    return 0.f;

  const PFHeroStatistics* pHeroStats = GetHeroStatistics();

  if ( !pHeroStats )
    return 0.f;

  float val = 0.f;

  switch ( heroStatId )
  {
    case TOWERS_DESTROYED:
      val = pHeroStats->GetTotalNumTowersKilled();
      break;
    case BARRACKS_DESTROYED:
      val = pHeroStats->GetTotalNumQuartersDestroyed();
      break;
    case HERO_KILLS:
      val = pHeroStats->GetTotalNumHeroKills();
      break;
    case ASSISTS:
      val = pHeroStats->GetTotalNumHeroAssists();
      break;
    case DEATHS:
      val = pHeroStats->GetNumDeaths();
  	  break;
    case GLYPHS_PICKUPED:
      val = pHeroStats->GetGlyphsPickuped();
      break;
    case ACHIEVEMENTS_SCORE:
      val = pHeroStats->GetAchievScore();
      break;
    case TOTAL_SCORE:
      val = pHeroStats->GetGrandScore();
    default:
      break;
  }

  return val;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PFBaseHero::GetHeroAchievementCount( const char* achievId ) const
{
  if ( IsClone() )
    return 0.f;

  const PFHeroStatistics* pHeroStats = GetHeroStatistics();

  if ( !pHeroStats )
    return 0.f;

  struct AchievFinder
  {
    AchievFinder( const char* _achievId ) : achievId(_achievId), pFoundAchiev(0) {}

    void operator()( const CObj<PFAchievBase>& pAchiev )
    {
      if ( !pFoundAchiev && pAchiev && strcmp( NDb::EnumToString( pAchiev->GetDBBase()->achievType ), achievId ) == 0 )
      {
        pFoundAchiev = pAchiev;
      }
    }
    const char* achievId;
    const PFAchievBase* pFoundAchiev;
  } achievFinder( achievId );

  pHeroStats->ForAllAchievements( achievFinder );

  if ( !achievFinder.pFoundAchiev )
  {
    DebugTrace("Achievement %s not found for GetAchievementCount", achievId );
    return 0;
  }

  return achievFinder.pFoundAchiev->GetCount();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFBaseHero::CanMove() const
{
  return !CheckFlagType( NDb::UNITFLAGTYPE_FORBIDPLAYERCONTROL ) && !CheckFlagType( NDb::UNITFLAGTYPE_INMINIGAME ) 
          && ( CheckFlag( NDb::UNITFLAG_CANTURNWHILEFORBIDMOVE ) || !CheckFlagType( NDb::UNITFLAGTYPE_FORBIDMOVE ) 
                || ControlsMount() );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseHero::Move(const CVec2 & target)
{
  CPtr<PFBaseMovingUnit> pHeroOrMount = ControlsMount() ? GetMount() : this;
  NI_VERIFY(IsValid(pHeroOrMount), "Invalid hero or mount!", return;);

  // PFBaseUnitMoveToState stops movement if target is within 1.0f range
  // Therefore we update listeners manually here
  if ( pHeroOrMount->IsPositionInRange( target, 1.0f ) )
    pHeroOrMount->EventHappened( NWorld::PFBaseUnitEvent( NDb::BASEUNITEVENT_MOVE ) );

  if ( PFBaseUnitMoveToState* st = dynamic_cast<PFBaseUnitMoveToState*>( pHeroOrMount->GetCurrentState() ) )
    st->SetNewParams( target, 0.0f );
  else      
    pHeroOrMount->EnqueueState(new PFBaseUnitMoveToState(CPtr<PFBaseMovingUnit>(pHeroOrMount), target, 0.0f), true);
}

float PFBaseHero::GetCustomEnergyValue() const
{
  if (!customEnergy || customEnergyValue == NULL)
    return 0.f;

  if (pDbHero->uniqueResource != NULL && !pDbHero->uniqueResource.IsEmpty())
  {
    return customEnergyValue->GetValue();   
  }

  return 0.f;
}

float PFBaseHero::GetCustomEnergyMaximum() const
{
  if (!customEnergy || customEnergyMaximum == NULL)
    return 0.f;

  if (pDbHero->uniqueResource != NULL && !pDbHero->uniqueResource.IsEmpty())
  {
    return customEnergyMaximum->GetValue();
  }

  return 0.f;
}

float PFBaseHero::GetCustomEnergyRegeneration() const
{
  if (!customEnergy || customEnergyRegeneration == NULL)
    return 0.f;

  if (pDbHero->uniqueResource != NULL && !pDbHero->uniqueResource.IsEmpty())
  {
    return customEnergyRegeneration->GetValue();
  }

  return 0.f;
}

void PFBaseHero::OnIdle()
{
  //DevTrace("%08x : PFBaseHero::OnIdle()", int(this));
  if(!IsClone() && !IsHoldingPosition())
  {
    CPtr<PFWorld> pWorld = this->GetWorld();
    if(IsValid(pWorld))
      PushState(new PFHeroHoldState(pWorld, this, false));
  }
}

void PFBaseHero::OnAfterSuspend(bool isLongSuspend)
{
  //if(!IsDead() && isLongSuspend)
  //{
  //  //DevTrace("%08x : PFBaseHero::OnAfterSuspend()", int(this));
  //  //PushState(new PFHeroHoldState(this->GetWorld(), this, false));
  //}
}

#pragma code_seg(push, "~")

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseHero::OnUnitDie( CPtr<PFBaseUnit> pKiller, int flags, PFBaseUnitDamageDesc const* pDamageDesc /*= 0*/ )
{
  STARFORCE_STOPWATCH();

  bool isDeathDeferred = ( (flags & UNITDIEFLAGS_DEFERREDDEATH) != 0 );
  bool isRewardsForbidden = ( (flags & UNITDIEFLAGS_FORBIDREWARDS) != 0 );

  if (isClone)
  {
    PFCreature::OnUnitDie(pKiller, flags, pDamageDesc );
    return;
  }

  // switch off talents
  const int levels = NDb::KnownEnum<NDb::ETalentLevel>::SizeOf();
  const int slots  = NDb::KnownEnum<NDb::ETalentSlot>::SizeOf();

  for ( int i = 0; i < levels; i++ )
  {
    for ( int j = 0; j < slots; j++ )
    {
      PFTalent* currentTalent = GetTalent( i, j );
      if ( currentTalent && currentTalent->IsOn() )
      {
        currentTalent->SwitchOff();
      }
    }
  }

  DismountSpecial();

  respawnDelay = -1.0f;

  if(!isRewardsForbidden)
    GetWorld()->GetStatistics()->AddHeroDeath(this, pKiller);

  PFCreature::OnUnitDie(pKiller, flags, pDamageDesc);
  DropTarget();

  Protection::CheckReadOnlyAndExecutable();

  if(!isDeathDeferred)
  {
    RecalculateRedeemCost();
    StartRespawnTimer();
  }

  // TODO: ?
  PlayerBehaviourTracking::DispatchEvent(this, EPlayerBehaviourEvent::Died);
}

#pragma code_seg(pop)

} // namespace NWorld;

REGISTER_WORLD_OBJECT_WITH_CLIENT_NM(PFBaseHero,     NWorld)

REGISTER_WORLD_OBJECT_NM(PFHeroBehaviour, NWorld)

BASIC_REGISTER_CLASS(NWorld::IInventory);
REGISTER_DEV_VAR("hero_give_world_gold_delay",   g_fGiveWorldGoldDelay,    STORAGE_NONE);
REGISTER_WORLD_OBJECT_NM(PFBetweenSessionsData,  NWorld)

#ifdef EXPOMODE
REGISTER_VAR( "zzsex_is_gender", g_zzSexSameAsGender, STORAGE_NONE )
#else
REGISTER_DEV_VAR( "zzsex_is_gender", g_zzSexSameAsGender, STORAGE_NONE )
#endif