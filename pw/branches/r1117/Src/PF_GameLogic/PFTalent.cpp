#include "stdafx.h"
#include "PFTalent.h"

#include "DBTalent.h"
#include "PFMaleHero.h"
#include "PFAIWorld.h"

#include "PFClientObjectHelpers.h"
#include "PFStatistics.h"
#include "Scene/AnimatedSceneComponent.h"
#include "PFResourcesCollectionClient.h"

#include "ForceCalc.h"

namespace
{
  string g_strTalentSetToLoad = "";
} // unnamed namespace

namespace NWorld
{

NAMEMAP_BEGIN(PFTalent)
  NAMEMAP_PARENT(PFAbilityData)
  NAMEMAP_FUNC_RO(moneyCost, &PFTalent::GetMoneyCost )
  NAMEMAP_FUNC_RO(devPoints, &PFTalent::GetDevPoints )
  NAMEMAP_FUNC_RO(minLevel,  &PFTalent::GetMinLevel  )
  NAMEMAP_FUNC_RO(rarityName, &PFTalent::GetRarityName )
  NAMEMAP_FUNC_RO(isBought, &PFTalent::IsActivated )
  NAMEMAP_VAR_RO(refineRate)
  NAMEMAP_FUNC_RO(isInGroup, &PFTalent::IsInGroup )
  NAMEMAP_FUNC_RO(groupName, &PFTalent::GetGroupName )
  NAMEMAP_FUNC_RO(groupDescription, &PFTalent::GetGroupDescription )
  NAMEMAP_FUNC_RO(isClass,       &PFTalent::IsClass )
  NAMEMAP_FUNC_RO(isOrdinary,    &PFTalent::IsOrdinary )
  NAMEMAP_FUNC_RO(isGood,        &PFTalent::IsGood )
  NAMEMAP_FUNC_RO(isExcellent,   &PFTalent::IsExcellent )
  NAMEMAP_FUNC_RO(isMagnificent, &PFTalent::IsMagnificent )
  NAMEMAP_FUNC_RO(isExclusive,   &PFTalent::IsExclusive )
  NAMEMAP_FUNC_RO(mConsumptionBonusPercent, &PFTalent::ConsumptionBonusPercent )  // fake to fix http://SITE
  NAMEMAP_FUNC_RO(activatedInKit, &PFTalent::GetActivatedWithinKit )
  NAMEMAP_FUNC_RO(totalInKit,     &PFTalent::GetTalentsWithinKit )
  NAMEMAP_FUNC_RO(kitName,        &PFTalent::GetKitName )
  NAMEMAP_FUNC_RO(isInKit,        &PFTalent::IsInKit )
  NAMEMAP_FUNC_RO(isInPack,       &PFTalent::IsInPack )
  NAMEMAP_FUNC_RO(isSpecialInKit, &PFTalent::IsSpecialInKit )
  NAMEMAP_FUNC_RO(packIcon,       &PFTalent::GetPackIconStyle )
NAMEMAP_END

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PFTalent::PFTalent( CPtr<PFBaseMaleHero> const& _pOwner, NDb::Ptr<NDb::Talent> const& _pDBTalentDesc, int _refineRate, int _aIPriority, int _actionBarIndex, bool _isInstaCast )
  : PFAbilityData( _pOwner.GetPtr(), _pDBTalentDesc.GetPtr(), NDb::ABILITYTYPEID_TALENT )
  , pOwner( _pOwner )
  , pDBTalentDesc( _pDBTalentDesc )
  , refineRate( _refineRate )
  , bActivated( false )
  , aIPriority ( _aIPriority )
  , actionBarIndex(_actionBarIndex)
  , lastUseStep(-1)
  , isInstaCast(_isInstaCast)
  , lastActivatedStep(-1)
  , pDBGroup(0)
{
  if (IsValid(pOwner) && !pOwner->IsClone())
  {
    if (PFWorld * pWorld = pOwner->GetWorld())
    {
      if (NGameX::IAdventureScreen * pAdventureScreen = pWorld->GetIAdventureScreen())
      {
        pAdventureScreen->PreloadEffectsInResourceTree( pDBTalentDesc.GetPtr(), SUMMONNODE, _pOwner->GetExcludedResourcesList(), _pOwner->GetSkinId() );
      }
    }
  }

  PFAbilityData::SetRank( refineRate );
}

bool PFTalent::CanBeActivated() const
{
  if ( pDBTalentDesc->activationConditions.empty() )
    return true;

  PFStatistics* pStats = pOwner->GetWorld()->GetStatistics();
  for ( vector<NDb::AchievmentCondition>::const_iterator iCond = pDBTalentDesc->activationConditions.begin(), iEnd = pDBTalentDesc->activationConditions.end(); iCond != iEnd; ++iCond )
  {
    NI_DATA_VERIFY(IsValid((*iCond).achiev), "Talent error: empty achievements fields.", return true)
    int rank = pStats->GetHeroAchievmentRank( pOwner.GetPtr(), (*iCond).achiev->GetObjectTypeID());
    if ( rank >= (*iCond).minRank )
      return true;
  }
  
  return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool PFTalent::Activate()
{
  if ( bActivated )
    return false;
  
  NI_VERIFY( !IsOn(), "Ability already is on!", return false; );
  const int naftaCost = GetNaftaCost();
  if ( pOwner->GetGold() < naftaCost )
    return false;
  
  pOwner->OnRemoveGold( pOwner.GetPtr(), naftaCost );

  if ( pOwner->IsDead() )
  {
    pOwner->AddTalentActivatedWhileDead( this );
  }

  if ( pTalentKit )
    pOwner->GetTalentsSet()->IncActivatedWithinKit( pTalentKit );
  
  return (bActivated = true);
}

// @todo [Oleg] this is not valid place for this function
wstring const &PFTalent::GetRarityName() const
{
  NDb::Ptr<NDb::DBUIData> pUIData = NDb::Get<NDb::DBUIData>(NDb::DBID("UI/Content/_.UIDT.xdb"));
  return pUIData->rarityValue[pDBTalentDesc->rarity].GetText();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFTalent::RestartCooldown( float cooldownTime_ )
{
  PFAbilityData::RestartCooldown( cooldownTime_ );

  if ( pDBGroup )
    pOwner->RestartGroupCooldowns( this );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
wstring const& PFTalent::GetGroupName() const
{
  return pDBGroup ? pDBGroup->name.GetText() : NNameMap::wstrNoname;
}

wstring const& PFTalent::GetGroupDescription() const
{
  return pDBGroup ? pDBGroup->description.GetText() : NNameMap::wstrNoname;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFTalent::NotifyCastProcessed()
{
  CPtr<PFWorld> pWorld = GetWorld();

  if( IsValid( pWorld ) )
  {
    // Save last talent activated step for scripting needs
    lastActivatedStep = pWorld->GetStepNumber();
    pWorld->NotifyTalentCastProcessed(this);
  }
}


//////////////////////////////////////////////////////////////////////////
float PFTalent::CalcBudget( const NDb::AILogicParameters* pAIParams, int refineRate, int level, int rarity )
{
  NDb::Ptr<NDb::ForceParameters> pForceParams = pAIParams->forceParameters;

  float mr = pForceParams->talentRarityForceModifiers[rarity];
  float mt;
  float sm;

  if (rarity == NDb::TALENTRARITY_CLASS)
  {
    mt = pForceParams->classTalentLevelForceModifiers[level];
    sm = pForceParams->classTalentForceBonusPerStar;
  }
  else
  {
    mt = pForceParams->talentLevelForceModifiers[level];
    sm = pForceParams->talentForceBonusPerStar;
  }

  mr *= 0.01f;
  mt *= 0.01f;
  sm *= 0.01f;

  return pAIParams->talentBaseStatBudget * (1.0f + mt) * mr * (1.0f + (refineRate-1.0f)*sm) / 220.0f * pForceParams->talentForceModifier; // TODO: Get rid of magic numbers (220)
}

int PFTalent::GetMoneyCost() const
{
  NI_ASSERT(pDBTalentDesc, "dbtalent is null");
  int naftaCost = pDBTalentDesc->naftaCost;
  if (naftaCost < 0)
  {
    const NDb::AILogicParameters& aiParams = GetWorld()->GetAIWorld()->GetAIParameters();
    naftaCost = aiParams.talentNaftaCostByLevel[GetTalentLevel()];
  }
  
  return naftaCost; 
}

int PFTalent::GetVendorCost() const
{
  NI_ASSERT(pDBTalentDesc, "dbtalent is null");
  int vendorCost = pDBTalentDesc->vendorCost;
  if (vendorCost < 0)
  {
    const NDb::AILogicParameters& aiParams = GetWorld()->GetAIWorld()->GetAIParameters();
    vendorCost = aiParams.talentVendorCostByRarity[pDBTalentDesc->rarity];
  }

  return vendorCost; 
}

int PFTalent::GetActivatedWithinKit() const
{
  return pTalentKit ? pOwner->GetTalentsSet()->GetActivatedWithinKit( pTalentKit ) : 0;
}

int PFTalent::GetTalentsWithinKit() const
{
  return pTalentKit ? pTalentKit->talents.size() : 0;
}

wstring const &PFTalent::GetKitName() const
{
  return pTalentKit ? pTalentKit->name.GetText() : NNameMap::wstrNoname;
}

const bool PFTalent::IsSpecialInKit() const
{
  return pTalentKit && pTalentKit->special ? pTalentKit->special->GetDBID() == pDBTalentDesc->GetDBID() : false;
}

const string& PFTalent::GetPackIconStyle() const
{
  return pTalentPack ? pTalentPack->iconStyle : NNameMap::strNoname;
}

void PFTalent::Reset()
{
  PFAbilityData::Reset();

  if ( bActivated && pTalentKit )
  {
    if ( pOwner->GetTalentsSet() )
      pOwner->GetTalentsSet()->IncActivatedWithinKit( pTalentKit );
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFTalent::PlayAck( const PFBaseHero* pAuxAckRecipient ) const
{
  int askId = pDBTalentDesc->askId;
  if ( askId == 0 )
    return;

  pOwner->PlayAskSound( NDb::ASKSOUNDS_ABILITY_1 + askId - 1, pAuxAckRecipient );
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PFTalentsSet
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

PFTalentsSet::PFTalentsSet( )
  : devPoints(0)
  , acquiredBudgetPercent(0.0f)
{
}

PFTalentsSet::PFTalentsSet( PFWorld* world )
  : PFWorldObjectBase( world, 0 )
  , devPoints(0)
  , acquiredBudgetPercent(0.0f)
{
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void PFTalentsSet::CleanSet()
{
  // Delete old set at first
  for ( int levelIndex = 0; levelIndex < LEVELS_COUNT; ++levelIndex )
  {
    for ( int slotIndex = 0; slotIndex < SLOTS_COUNT; ++slotIndex )
    {
      CObj<PFTalent>& pTalent = talents[levelIndex][slotIndex];
      if ( IsValid(pTalent) )
      {
        pTalent->CancelAbility();
        pTalent->ApplyPassivePart(false);
        pTalent = NULL;
      }
    }
  }

  devPoints = 0;
  pOwner = 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFTalentsSet::ActivateTakenOnStart()
{
  for ( vector<pair<int,int>>::const_iterator it = talentsToActivate.begin(); it != talentsToActivate.end(); ++it )
  {
    ActivateTalent( it->first, it->second );
  }
  talentsToActivate.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void PFTalentsSet::LoadSet( CPtr<PFBaseMaleHero> const& pOwner_, SetInfo const& setInfo )
{
  CleanSet();

  NI_ASSERT( !pOwner, "Talents set is alredy loaded!" );
  
  pOwner = pOwner_;
  
  for ( int level = 0; level < LEVELS_COUNT; ++level )
  {
    for ( int slot = 0; slot < SLOTS_COUNT; ++slot )
    {
      SlotInfo const& slotInfo = setInfo[level][slot];
      
      if ( IsValid(slotInfo.pTalentDesc) )
      {
        NI_VERIFY( slotInfo.status == NDb::TALENTSLOTSTATUS_NORMAL, "Slot in talent is not enpty, but is not aviable!", continue; );
        PFTalent *talent = new PFTalent( pOwner, slotInfo.pTalentDesc, slotInfo.refineRate, slotInfo.aIPriority, slotInfo.actionBarIndex, slotInfo.isInstaCast );
        
        talents[level][slot] = talent;
        if ( slotInfo.pTalentDesc->isTakenOnStart )
        {          
          int cost = talent->GetNaftaCost();
          NI_DATA_VERIFY( cost == 0, NStr::StrFmt( "Talent \"%s\" that is taken by default for hero \"%s\" has nonzero nafta cost = %d!", NStr::ToMBCS( talent->GetAbilityName() ).c_str(), NStr::ToMBCS( pOwner->GetDescription() ).c_str(), cost ), continue );
          talentsToActivate.push_back( make_pair( level, slot ) );
        }
      }
    }
  }
  CreateGroups();
  CreateKits();
  CreatePacks();
}

void PFTalentsSet::Reset()
{
  // True heroes already have their sets with created groups, kits and packs
  if ( pOwner->IsClone() )
  {
    CreateGroups();
    CreateKits();
    CreatePacks();
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFTalentsSet::CreateGroups()
{
  typedef vector<NDb::TalentGroup> TalGroups;

  talentGroups.clear();

  NDb::Ptr<NDb::TalentGroupList> const& pDBTalGroups = GetWorld()->GetAIWorld()->GetAIParameters().talentGroups;
  if ( !pDBTalGroups )
    return;

  TalGroups const& talGroups = pDBTalGroups->groups;

  if ( talGroups.empty() )
    return;

  for ( int level = 0; level < LEVELS_COUNT; ++level )
  {
    for ( int slot = 0; slot < SLOTS_COUNT; ++slot )
    {
      PFTalent* pTalent = talents[level][slot];
      if ( !pTalent )
        continue;

      for ( TalGroups::const_iterator it = talGroups.begin(); it != talGroups.end(); ++it )
      {
        if ( it->talents.find( pTalent->GetTalentDesc() ) != it->talents.end() )
        {
          vector<PFTalent*>& vecTalents = talentGroups[it];
          vecTalents.push_back( pTalent );
          pTalent->SetGroup( it );
        }
      }
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFTalentsSet::CreateKits()
{
  typedef vector<NDb::Ptr<NDb::TalentKit>> TalKits;

  talentKits.clear();

  NDb::Ptr<NDb::TalentKitList> const& pDBTalKits = GetWorld()->GetAIWorld()->GetAIParameters().talentKits;
  if ( !pDBTalKits )
    return;

  TalKits const& dbTalKits = pDBTalKits->kits;

  if ( dbTalKits.empty() )
    return;

  for ( int level = 0; level < LEVELS_COUNT; ++level )
  {
    for ( int slot = 0; slot < SLOTS_COUNT; ++slot )
    {
      PFTalent* pTalent = talents[level][slot];
      if ( !pTalent )
        continue;

      bool bFound = false;
      // Find in existing kits
      for ( ActivatedInTalentKits::const_iterator it = talentKits.begin(); it != talentKits.end(); ++it )
      {
        vector<NDb::Ptr<NDb::Talent>> const& talentsInKit = it->first->talents;
        if ( talentsInKit.find( pTalent->GetTalentDesc() ) != talentsInKit.end() )
        {
          pTalent->SetKit( it->first );
          bFound = true;
          break;
        }
      }

      if ( bFound )
        continue;

      // Find in global kits list
      for ( TalKits::const_iterator it = dbTalKits.begin(); it != dbTalKits.end(); ++it )
      {
        if ( (*it)->talents.find( pTalent->GetTalentDesc() ) != (*it)->talents.end() )
        {
          pTalent->SetKit( *it );
          talentKits[ *it ] = 0;
          break;
        }
      }
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFTalentsSet::CreatePacks()
{
  typedef vector<NDb::Ptr<NDb::TalentPack>> TalPacks;

  NDb::Ptr<NDb::TalentPackList> const& pDBTalPacks = GetWorld()->GetAIWorld()->GetAIParameters().talentPacks;
  if ( !pDBTalPacks )
    return;

  TalPacks const& dbTalPacks = pDBTalPacks->packs;

  if ( dbTalPacks.empty() )
    return;

  for ( int level = 0; level < LEVELS_COUNT; ++level )
  {
    for ( int slot = 0; slot < SLOTS_COUNT; ++slot )
    {
      PFTalent* pTalent = talents[level][slot];
      if ( !pTalent )
        continue;

      for ( TalPacks::const_iterator it = dbTalPacks.begin(); it != dbTalPacks.end(); ++it )
      {
        if ( (*it)->talents.find( pTalent->GetTalentDesc() ) != (*it)->talents.end() )
        {
          pTalent->SetPack( *it );
          break;
        }
      }
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFTalentsSet::Update(float dt)
{
  for ( int lvl = 0; lvl < LEVELS_COUNT; ++lvl )
  {
    for ( int slot = 0; slot < SLOTS_COUNT; ++slot )
    {
      if ( CObj<PFTalent> const& pTalent = talents[lvl][slot] )
        pTalent->Update( dt, true );
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CObj<PFTalent> const& PFTalentsSet::GetTalent(int level, int slot) const
{
  static CObj<PFTalent> const pNullTalent;
  NI_VERIFY( level >= 0 && level < LEVELS_COUNT, "Wrong level of talent!", return pNullTalent );  
  NI_VERIFY( slot >= 0 && slot < SLOTS_COUNT, "Wrong slot of talent!", return pNullTalent );
  return talents[level][slot];
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool IsShopNearHero( CPtr<PFBaseMaleHero> const& pOwner )
{
  NI_VERIFY( IsUnitValid(pOwner), "Owner must be valid!", return false; );
  const float talentsBuyRange = pOwner->GetWorld()->GetAIWorld()->GetAIParameters().talentsBuyRange;
  if ( talentsBuyRange == 0 )
    return true;
  
  struct ShopFinder {
    ShopFinder() : nearHero(false){}
    void operator()(PFBaseUnit& unit) { nearHero = true; }
    bool nearHero;
  } isShop;
  
  PFAIWorld const* pAIWorld = pOwner->GetWorld()->GetAIWorld();
  const int factionsMask = (1 << pOwner->GetFaction()) | (1 << NDb::FACTION_NEUTRAL);

  pAIWorld->ForAllUnitsInRange( pOwner->GetPosition(), talentsBuyRange, isShop, UnitMaskingPredicate(factionsMask, NDb::SPELLTARGET_SHOP) );

  return isShop.nearHero;
};


ETalentActivation::Enum PFTalentsSet::CanActivateTalent(int level, int slot) const
{
  if ( !IsValid(pOwner) || level > GetLevelOfDevelopment() )
    return ETalentActivation::Denied;
  
  if ( !pOwner->IsDead() && !IsShopNearHero(pOwner) )
    return ETalentActivation::Denied;
  
  CObj<PFTalent> const& pTalent = GetTalent(level, slot);
  if ( !pTalent || pTalent->IsActivated() || !pTalent->CanBeActivated() )
    return ETalentActivation::Denied;
  
  /*NDb::Ptr<NDb::Talent> const& pDBDesc = pTalent->GetTalentDesc();
  NI_VERIFY( pDBDesc, "No DB desc in talent!", return ETalentActivation::Denied );
  */
  if ( pTalent->GetNaftaCost() > pOwner->GetGold() )
    return ETalentActivation::NoMoney;
  
  return ETalentActivation::Ok;
}



bool PFTalentsSet::HasFreshTalentsToBuy() const
{
  int level = GetLevelOfDevelopmentCapped();

  for ( int slot = 0; slot < SLOTS_COUNT; ++slot )
    if ( CanActivateTalent( level, slot ) == ETalentActivation::Ok )
      return true;

  return false;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool PFTalentsSet::ActivateTalent(int level, int slot)
{
  // NI_ASSERT( CanActivateTalent(level, slot) == ETalentActivation::Ok, "Can't activate talent! Need to call PFTalentsSet::CanActivateTalent first!" );
  CObj<PFTalent> const& pTalent = GetTalent(level, slot);
  
  if ( !pTalent || !pTalent->Activate() )
    return false;

  const int talentDevPoints = pTalent->GetDevPoints();

  devPoints += talentDevPoints;

  // count total devpoints for level
  int devpointsPerLevel = 0;
  for ( int s = 0; s < SLOTS_COUNT; ++s )
  {
    PFTalent const* talent = GetTalent( level, s );
    if ( talent )
    {
      devpointsPerLevel += talent->GetDevPoints();
    }
  }
  NI_ASSERT( devpointsPerLevel > 0, "Zero devpoints per level" );

  const float statsIncrementFraction = GetWorld()->GetAIWorld()->GetAIParameters().forceParameters->talentLevelBonusPercent[level] / devpointsPerLevel * 0.01f;

  acquiredBudgetPercent += statsIncrementFraction * talentDevPoints;

  pOwner->OnTalentActivated( level, slot, statsIncrementFraction );

  pTalent->ApplyPassivePart(true);

  return true;
}
//////////////////////////////////////////////////////////////////////////

float PFTalentsSet::PreloadTalentsSetAndCalcForce(const NDb::AILogicParameters* pAIParams, const NDb::BaseHero* pDBHero, 
                                                  bool usePlayerInfoTalentSet, const NWorld::PFResourcesCollection* collection,
                                                  const NCore::PlayerInfo& playerInfo, PFTalentsSet::SetInfo& info)
{
  NI_ASSERT(pAIParams, "aiParams is empty");

  float force = 0;
//  const NDb::Ptr<NDb::ForceParameters>& pDBForceParams = pAIParams->forceParameters;

  //NI_DATA_ASSERT( !pDBForceParams.IsEmpty(), "forceParameters is empty" );

  Force::TalentsForceCalculator talentsForceCalculator( pAIParams );

  if (!usePlayerInfoTalentSet)
  {
    PFTalentsSet::PreparePredefinedSet(pAIParams, pDBHero, "", talentsForceCalculator, info);
  } 
  else
  {
    NI_ASSERT(collection,"NWorld::PFResourceCollection is NULL!");
    PFTalentsSet::PrepareCustomSet(&playerInfo.talents, collection, talentsForceCalculator, info);
  }

  force += talentsForceCalculator.GetResult();
  force += pAIParams->forceParameters->baseHeroForce;

  return force;
}

//////////////////////////////////////////////////////////////////////////
// *** For debug only! Do not use!! *** //
//////////////////////////////////////////////////////////////////////////

void PFTalentsSet::PreparePredefinedSet(const NDb::AILogicParameters* pAIParams, const NDb::BaseHero* pDBHero, string const& forceSetName, 
                                        ITalentCalculator& calculator, SetInfo& info)
{
  NDb::Ptr<NDb::TalentsSet> pDefaultSet;

  if ( !forceSetName.empty() )
  {
    pDefaultSet = NDb::Get<NDb::TalentsSet>( NDb::DBID(forceSetName) );
  }
  if ( !pDefaultSet && !g_strTalentSetToLoad.empty() )
  {
    pDefaultSet = NDb::Get<NDb::TalentsSet>( NDb::DBID(g_strTalentSetToLoad) );
  }
  if ( !pDefaultSet )
  {
    if ( NDb::Ptr<NDb::Hero> pHero = dynamic_cast<NDb::Hero const*>(pDBHero) )
      pDefaultSet = pHero->defaultTalentsSets[0];
  }
  if ( !pDefaultSet )
  {
    pDefaultSet = pAIParams->defaultTalentsSet;
  }

  NI_VERIFY( pDefaultSet, NStr::StrFmt( "Can not load default talent set for hero \"%s\"", NDb::GetFormattedDbId( pDBHero->GetDBID() ).c_str() ), return );

  struct DublicatsChecker {
    bool IsAlreadyUsed( NDb::Ptr<NDb::Talent> const& pTalent )
    {
      vector<NDb::Ptr<NDb::Talent>>::const_iterator iFind = find(rgTalents.begin(), rgTalents.end(), pTalent);
      if ( iFind == rgTalents.end() )
      {
        rgTalents.push_back(pTalent);
        return false;
      }
      return true;
    }
    vector<NDb::Ptr<NDb::Talent>> rgTalents;
  } dublicatsChecker;

  for ( int level = 0; level < LEVELS_COUNT; ++level )
  {
    for ( int slot = 0; slot < SLOTS_COUNT; ++slot )
    {
      SlotInfo& slotInfo = info[level][slot];

      NDb::TalentSlot const& dbSlot = pDefaultSet->levels[level].talents[slot];

      slotInfo.status = dbSlot.status;
      if ( dbSlot.talent )
      {
        NI_VERIFY( !dublicatsChecker.IsAlreadyUsed(dbSlot.talent), "Duplicated talents (talent skipped)!", continue; )
          NI_VERIFY( dbSlot.status == NDb::TALENTSLOTSTATUS_NORMAL, "Slot for talent is not available (talent skipped)!", continue; );
        NI_VERIFY( dbSlot.talent->minLevel == level, "Wrong talent level (talent skipped)!", continue; );
        slotInfo.pTalentDesc = dbSlot.talent;
        slotInfo.refineRate = dbSlot.refineRate;
        slotInfo.aIPriority = dbSlot.aIPriority;
        //default value
        slotInfo.actionBarIndex = -1;
        slotInfo.isInstaCast = dbSlot.talent->flags & NDb::ABILITYFLAGS_INSTACAST;

        calculator( slotInfo.pTalentDesc, level, slotInfo );
      }
    }
  }
}



void PFTalentsSet::LoadPredefinedSet(CPtr<PFBaseMaleHero> const& _pOwner, string const& forceSetName, ITalentCalculator& calculator) 
{
  //////////////////////////////////////////////////////////////////////////
  // *** For debug only! Do not use!! *** //
  //////////////////////////////////////////////////////////////////////////
  
  // Load new set
  SetInfo info;
  PreparePredefinedSet(&_pOwner->GetWorld()->GetAIWorld()->GetAIParameters(), _pOwner->GetDbHero(), forceSetName, calculator, info);
  LoadSet(_pOwner, info);
}


//////////////////////////////////////////////////////////////////////////

void PFTalentsSet::PrepareCustomSet(const NCore::PlayerTalentSet* talentSet, const NWorld::PFResourcesCollection* collection, ITalentCalculator& calculator, SetInfo& info)
{
  for (NCore::PlayerTalentSet::iterator it=talentSet->begin();it!=talentSet->end();++it)
  {
    int index = it->first-1;
    const NCore::TalentInfo& talent = it->second;
    int level = index / SLOTS_COUNT;
    int slot = index % SLOTS_COUNT;
    SlotInfo& slotInfo = info[level][slot];

    slotInfo.pTalentDesc = collection->FindTalentById(talent.id);
    NI_VERIFY( slotInfo.pTalentDesc != NULL, "Talent not found (talent skipped)!", continue; );
    slotInfo.status = NDb::TALENTSLOTSTATUS_NORMAL;
    slotInfo.refineRate = talent.refineRate;
    slotInfo.aIPriority = 0;
    //here slotInfo.actionBarIndex is null based
    slotInfo.actionBarIndex = talent.actionBarIdx;
    slotInfo.isInstaCast = talent.isInstaCast;

    calculator( slotInfo.pTalentDesc, level, slotInfo );
  }
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
void PFTalentsSet::CalculateForce(ITalentCalculator& calculator)
{
  for ( int lvl = 0; lvl < LEVELS_COUNT; ++lvl )
  {
    for ( int slot = 0; slot < SLOTS_COUNT; ++slot )
    {
      if ( CObj<PFTalent> const& pTalent = talents[lvl][slot] )
      {
        SlotInfo slotInfo;
        slotInfo.refineRate = pTalent->GetRefineRate();
        calculator(pTalent->GetTalentDesc(), lvl, slotInfo);
      }
    }
  }
}


} //namespace NWorld

REGISTER_WORLD_OBJECT_NM(PFTalent, NWorld);

REGISTER_WORLD_OBJECT_NM(PFTalentsSet, NWorld);

REGISTER_DEV_VAR("default_talent_set",                  g_strTalentSetToLoad,                       STORAGE_NONE);
