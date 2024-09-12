#include "stdafx.h"

#include "PFAbilityData.h"
#include "PFAbilityInstance.h"
#include "PFAIWorld.h"
#include "PFBaseUnit.h"
#include "PFUnitAbilities.h"

namespace NWorld
{

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Abilities 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void PFUnitAbilities::CreateAbilities(PFBaseUnit *pOwner, const NDb::Unit &unitDesc)
{
  const int abilitiesCount = NDb::KnownEnum<NDb::EAbility>::SizeOf();
  abilities.resize(abilitiesCount);

  int curAbility = 0;
  for(vector<NDb::Ptr<NDb::Ability> >::const_iterator it = unitDesc.abilities.begin(),
    end = unitDesc.abilities.end(); it != end; ++it, ++curAbility )
  {
    if (*it)
    {
      PFAbilityData *pA = new PFAbilityData(pOwner, *it, NDb::EAbilityTypeId(NDb::ABILITYTYPEID_ABILITY0 + curAbility) );
      abilities[ curAbility ].pAbility = pA;
    }
  }

  globalCooldownTime = pOwner->GetWorld()->GetAIWorld()->GetAIParameters().globalCooldownTime;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PFAbilityData* PFUnitAbilities::GetAbility(int id)
{
  NI_VERIFY(0 <= id && id < NDb::KnownEnum<NDb::EAbility>::SizeOf(), "Invalid ability id!", return NULL; ) ;
  NI_VERIFY(0 <= id && id < abilities.size(),                        "Invalid ability id!", return NULL; ) ;

  return abilities[id].pAbility;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PFAbilityData const* PFUnitAbilities::GetAbility(int id) const
{
  NI_VERIFY(0 <= id && id < NDb::KnownEnum<NDb::EAbility>::SizeOf(), "Invalid ability id!", return NULL; ) ;
  NI_VERIFY(0 <= id && id < abilities.size(), "Invalid ability id!", return NULL; ) ;

  return abilities[id].pAbility;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFUnitAbilities::SetAbility(int id, PFAbilityData *pAbility)
{
  NI_VERIFY(0 <= id && id < NDb::KnownEnum<NDb::EAbility>::SizeOf(), "Invalid ability id!", return; ) ;
  NI_VERIFY(0 <= id && id < abilities.size(), "Invalid ability id!", return; ) ;

  abilities[id].pAbility = pAbility;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PFUnitAbilities::GetAbilitiesCount() const
{
  return abilities.size();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PFUnitAbilities::GetAbilityIndex(PFAbilityData const *pAbility) const
{
  TAbilities::const_iterator const itEnd = abilities.end();
  TAbilities::const_iterator const itBegin = abilities.begin();
  for (TAbilities::const_iterator it = itBegin; it != itEnd; ++it)
  {
    if (it->pAbility == pAbility)
    {
      return it - itBegin;
    }
  }
  return -1;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFUnitAbilities::IsAbilityInProgress(int id) const
{
  NI_VERIFY(0 <= id && id < NDb::KnownEnum<NDb::EAbility>::SizeOf(), "Invalid ability id!", return false; ) ;
  NI_VERIFY(0 <= id && id < abilities.size(),                        "Invalid ability id!", return false; ) ;

  return abilities[id].isInProgress;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFUnitAbilities::SetAbilityInProgress(int id, bool isInProgress)
{
  NI_VERIFY(0 <= id && id < NDb::KnownEnum<NDb::EAbility>::SizeOf(), "Invalid ability id!", return; ) ;
  //NI_VERIFY(0 <= id && id < abilities.size(),                        "Invalid ability id!", return; ) ;

  if (0 == abilities.size() || !IsValid(abilities[id].pAbility))
    return;

  abilities[id].isInProgress = isInProgress;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFUnitAbilities::HaveAbilityInProgress() const
{
  for ( vector<AbilityData>::const_iterator iAbility = abilities.begin(), iEnd = abilities.end(); iAbility != iEnd; ++iAbility)
    if ( iAbility->isInProgress )
      return true;
  return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFUnitAbilities::DropAbilitiesCooldowns( DropCooldownParams const& dropCooldownParams )
{
  for ( TAbilities::iterator it = abilities.begin(), end = abilities.end(); it != end; ++it )
  {
    if ( it->pAbility )
    {
      bool const checkMask          = 0 != (dropCooldownParams.flags & (1 << it->pAbility->GetAbilityTypeId()));
      bool const checkExceptAbility = it->pAbility.GetPtr() != dropCooldownParams.exceptAbility;

      if (checkMask && checkExceptAbility)
        it->pAbility->DropCooldown(true, dropCooldownParams.cooldownReduction, dropCooldownParams.reduceByPercent);
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFUnitAbilities::DestroyAbilities()
{
  // do not clean abilities when removed from world (OnDie) ...
  for( TAbilities::iterator it = abilities.begin(), end = abilities.end(); it != end; ++it)
  {
    if( it->pAbility )
      it->pAbility->ApplyPassivePart(false);
  }
  abilities.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFUnitAbilities::UpdateAbilities(float dtInSeconds, bool isDead)
{
  NI_PROFILE_FUNCTION
  
  int ndx = 0;
  for(TAbilities::iterator it = abilities.begin(), end = abilities.end(); it != end; ++it, ++ndx)
  {
    if (CObj<PFAbilityData> const &pAbility = it->pAbility)
      it->pAbility->Update(dtInSeconds, !isDead);
  }  

  if ( globalActionsCooldown > 0 )
    globalActionsCooldown -= dtInSeconds;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void PFUnitAbilities::DropAbilitiesProgress()
{
  for ( TAbilities::iterator it = abilities.begin(), end = abilities.end(); it != end; ++it )
    it->isInProgress = false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFUnitAbilities::UpgradeAbilities()
{
  for(int i = 0, count = NDb::KnownEnum<NDb::EAbility>::SizeOf(); i < count; ++i)
  {
    PFAbilityData *pAbility = GetAbility(i);
    if ( IsValid(pAbility) )
      pAbility->LevelUp();
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFUnitAbilities::IsAbilityAvailable(int id) const
{
  NI_VERIFY(0 <= id && id < GetAbilitiesCount(), "Invalid ability id!", return false; ) ;

  PFAbilityData const* pAbility = GetAbility(id);
  if ( pAbility->IsActive() && globalActionsCooldown > 0 ) // Global cooldown
    return false;

  return pAbility->CanBeUsed();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float PFUnitAbilities::GetAbilityPreparedness(int id) const
{
  NI_VERIFY(0 <= id && id < GetAbilitiesCount(), "Invalid ability id!", return 0.0f; ) ;

  PFAbilityData const* pAbility = GetAbility(id);
  if( NULL == pAbility )
    return 0.0f;

  if (!pAbility->IsActive())
    return 1.0f;

  float preparedness = pAbility->GetPreparedness();
  return (preparedness < 1.0f) ? preparedness : GetGlobalPreparedness();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float PFUnitAbilities::GetGlobalPreparedness() const
{
  return globalCooldownTime > 0 ? 1.0f - max(0.0f, globalActionsCooldown) / globalCooldownTime : 1.0f;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// State
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

PFBaseUnitUseAbilityState::PFBaseUnitUseAbilityState(CPtr<PFWorld> const& pWorld, CPtr<PFBaseUnit> const& pOwner, int id, Target const &target)
: PFBaseUseState(pOwner, target)
, pWorld(pWorld)
, abilityID(id)
, wait4channeling(false)
{
  NI_ASSERT( NDb::ABILITY_ID_1 <= id && id <= NDb::ABILITY_ID_4, "Invalid ability id!" );

  if ( PFAbilityData const *pAbility = pOwner->GetAbility(id) )
  {
    if ( pAbility->GetType() == NDb::ABILITYTYPE_CHANNELLING )
      wait4channeling = true;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseUnitUseAbilityState::OnEnter()
{
  pOwner->SetAbilityInProgress( abilityID, true );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFBaseUnitUseAbilityState::OnStep( float dt )
{
  if ( !IsUnitValid( pOwner ) || !target.IsValid() )
  {
    return true;
  }

  if ( target.IsObject() && !IsValid( target.GetObject() ) )
  {
    return true;
  }

  FSMStep( dt );

  // Check when we still chase pTarget or moving to target
  if ( GetCurrentState() )
  {
    return false;
  }

  if ( !pAbilityInstance )
  {
    pAbilityInstance = pOwner->UseAbility( abilityID, target );
    if ( !pAbilityInstance )
    {
      return true;
    }
  }

  bool isToggleOff = false;
  if ( ( pAbilityInstance->GetData()->GetType() == NDb::ABILITYTYPE_SWITCHABLE ) && !pAbilityInstance->IsOn() )
  {
    isToggleOff = true;
  }

  // This means that ability is already used, but we need to wait for 1 step for dispatch.
  if ( IsCastFinished() && wait4channeling && dt > 0.0f )
  {
    wait4channeling = false;
  }

  return ( IsCastFinished() && !wait4channeling ) || isToggleOff;
}

void PFBaseUnitUseAbilityState::OnLeave()
{
  if ( IsValid( pOwner ) )
  {
    pOwner->SetAbilityInProgress( abilityID, false );
  }
}

NDb::Ability const* PFBaseUnitUseAbilityState::GetDBDesc() const
{ 
  return pOwner->GetAbility( abilityID )->GetDBDesc();
} 

}
REGISTER_WORLD_OBJECT_NM(PFBaseUnitUseAbilityState, NWorld)
