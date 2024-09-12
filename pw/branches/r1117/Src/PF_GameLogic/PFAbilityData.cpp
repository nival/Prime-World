#include "stdafx.h"
#include "PFAbilityData.h"
#include "../Core/Transceiver.h"

#include "PFBaseUnit.h"
#include "PFAbilityInstance.h"
#include "PFUniTarget.h"
#include "PFTargetSelector.h"
#include "PFCastLimitations.h"
#include "PFMicroAI.h"

#include "PFAIWorld.h"
#include "PFConsumable.h"
#include "SmartRandom.h"
#include "PFWorldNatureMap.h"

#ifndef VISUAL_CUTTED
#include "AdventureScreen.h"
#include "AdventureScreenEvents.h"
#include "UnitNameMap.h"
#include "../Scene/AnimatedSceneComponent.h"
#include "../Scene/SceneObjectCreation.h"
#endif

namespace NNameMap
{
  const wstring wstrNoname = L"#noname#";
  const string  strNoname = "#noname#";
}

namespace NWorld
{

  int PFAbilityData::baseRefineRate = 4;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PFAbilityData
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

PFAbilityData::PFAbilityData( CPtr<PFBaseUnit> const& pOwner, NDb::Ptr<NDb::Ability> const& _pDBDesc, NDb::EAbilityTypeId abilityType, bool needRegisterInWorld, bool isInteractionAbility /*= false*/)
: PFWorldObjectBase( needRegisterInWorld ? pOwner->GetWorld() : 0, 0 )
, pOwner(pOwner)
, pDBDesc(_pDBDesc)
, manaCost(0.0f)
, zzCost( 0 )
, rank(1)
, isOn(false)
, forbids(0)
, isInPassivePartUpdate(false)
, abilityType(abilityType)
, cachedModifiersTime(-1)
, castSelfLimitationPassed( true )
, isInteractionAbility( isInteractionAbility )
, abilityState(EAbilityState::First)
{
  ::Reset( pConstantsMap, new PFAbilityConstantsMap(this, pDBDesc) );
  constResolver.Init(this);
  condsResolver.Init(this);
  UpdateAbilityModifiers();

  cooldownTime[EAbilityState::First] = 0.0f;
  cooldownTime[EAbilityState::Second] = 0.0f;
  cooldown[EAbilityState::First] = 0.0f;
  cooldown[EAbilityState::Second] = 0.0f;

  if (pDBDesc->autoTargetSelector)
  {
    pAutoTargetSelector = static_cast<PFSingleTargetSelector*>(pDBDesc->autoTargetSelector->Create( needRegisterInWorld ? pOwner->GetWorld() : 0 ));
  }

  pMicroAI = CreateMicroAI();

  RecalculateCooldown();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PFAbilityData::PFAbilityData()
  : isInPassivePartUpdate(false)
{
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFAbilityData::Reset()
{
	PFWorldObjectBase::Reset();
	::Reset( pConstantsMap, new PFAbilityConstantsMap(this, pDBDesc) );
	constResolver.Init(this);
	condsResolver.Init(this);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PFMicroAI* PFAbilityData::CreateMicroAI() const
{
  if ( !IsValid( pDBDesc->microAI ) )
    return 0;

  const PFMicroAICreateParams cp( pDBDesc->microAI, this );
  return pDBDesc->microAI->Create( cp );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFAbilityData::Update(float dt, bool fullUpdate)
{
  if(fullUpdate)
  {
    isInPassivePartUpdate = true;
    
    // Update passive instance
    if ( pPassiveInstance )
      pPassiveInstance->Update(dt);

    isInPassivePartUpdate = false;
    
    UpdateAbilityModifiers();
    RecalculateManaCost(); // need to update manaCost each step
  }
  
  // Update cooldown
  for (int i = 0; i < EAbilityState::_Count; ++i)
  {
    if (cooldown[i] > 0.0f)
      cooldown[i] = max(0.0f, cooldown[i] - dt);

    if( cooldown[i] < dt / 2.0f )
      cooldown[i] = 0.0f;
  }

  // check cast limitation for active abilities accepting no targets and abilities that uses current unit target
  bool bAbilityUsesAttackTarget = ( pDBDesc->flags & NDb::ABILITYFLAGS_USEATTACKTARGET ) != 0;
  if ( IsActive() && ( GetTargetType() == 0 || bAbilityUsesAttackTarget ) )
  {
    castSelfLimitationPassed = CheckCastLimitations( (Target const)( pOwner.GetPtr() ) ) == 0;
    // default cast limitation for ability of such kind
    if ( bAbilityUsesAttackTarget && castSelfLimitationPassed )
    {
      PFBaseUnit const* pTarget = pOwner->GetCurrentTarget();
      castSelfLimitationPassed = IsValid( pTarget )
        && UnitMaskingPredicate( pOwner, pDBDesc->targetType )( *pTarget )
        && pOwner->IsTargetInRange( pTarget, pDBDesc->useRange( pOwner, pTarget, this, 0.0f ) )
        && !pTarget->IsInvalidAbilityTarget();
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float PFAbilityData::GetScale() const
{
  return GetModifiedValue( 1.0f, NDb::ABILITYMODMODE_SCALE );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFAbilityData::FindAutoTarget(Target & target)
{
	if (!pAutoTargetSelector)
		return false;

	Target requestPos(pOwner);
	PFTargetSelector::RequestParams pars(pOwner, this, requestPos);
	return pAutoTargetSelector->FindTarget(pars, target);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFAbilityData::FindMicroAITarget(Target & target)
{
	if (!pMicroAI)
		return false;

	return pMicroAI->GetTarget(target);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFAbilityData::FindMicroAITargetTemp(Target & target) const
{
	if ( !IsValid( pDBDesc->microAI ) )
		return false;

	PFMicroAICreateParams cp( pDBDesc->microAI, this );
	cp.isAITemp = true;
	CObj<PFMicroAI> pMicroAI = pDBDesc->microAI->Create( cp );
  if ( !pMicroAI )
    return false;
	
  return pMicroAI->GetTarget(target);
}

bool PFAbilityData::FindMicroAITargetTemp(Target & target, const ITargetCondition& condition) const
{
  if ( !IsValid( pDBDesc->microAI ) )
    return false;

  PFMicroAICreateParams cp( pDBDesc->microAI, this );
  cp.isAITemp = true;
  CObj<PFMicroAI> pMicroAI = pDBDesc->microAI->Create( cp );
  if ( !pMicroAI )
    return false;

  return pMicroAI->GetTarget(target, condition);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFAbilityData::ApplyPassivePart( bool bApply /* = true */ )
{
  if ( IsValid(pPassiveInstance) )
  {
    // Remove old passive instance
    RemoveApplicatorsFrom(pOwner);
    pPassiveInstance->Remove();
    pPassiveInstance = NULL;
  }

  if (bApply)
  {
    // Create new passive instance
    pPassiveInstance = new PFAbilityInstance( this, Target( pOwner ), true );
    pPassiveInstance->ApplyPassive();
    AddInstance(pPassiveInstance);
  }

  RecalculateCooldown();
  RecalculateManaCost();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CObj<PFAbilityInstance> PFAbilityData::ApplyToTarget( Target const& target )
{
  const NDb::Ability* pDBDesc = GetDBDesc();

  if ( pDBDesc->targetType == NDb::SPELLTARGET_LAND )
  {
    NI_ASSERT( target.IsPosition(), "Position expected, got object" );
  }
  else if ( pDBDesc->targetType && (pDBDesc->targetType & NDb::SPELLTARGET_LAND) == 0 )
  {
    NI_ASSERT( target.IsObject(), "Object expected, got position" );
  }

  if ( !IsReady() || !IsEnoughMana() )
    return NULL;


	// Check possibility of casting
  NDb::CastLimitation const* castLimitation = CheckCastLimitations( target );
  if ( castLimitation )
  {
    NGameX::ProcessUnitEvent( castLimitation->uiEvent, pOwner );

    // Application failed
    return CObj<PFAbilityInstance>(0);
  }

  AbilityTarget targetToApply = target;

  const float minUseRangeCorrection = pDBDesc->minUseRangeCorrection;

  // minUseRangeCorrection
  if ( target.IsPosition() && minUseRangeCorrection > 0.0f )
  {
    CVec2 vectorToTarget = target.GetPosition().AsVec2D() - pOwner->GetPosition().AsVec2D();

    const float vectorLen2 = fabs2( vectorToTarget );
    const float minUseRangeCorrection2 = minUseRangeCorrection * minUseRangeCorrection;

    if ( vectorLen2 < minUseRangeCorrection2 && vectorLen2 > EPS_VALUE )
    {
      const float vectorLen = sqrt( vectorLen2 );
      vectorToTarget *= minUseRangeCorrection / vectorLen;
      targetToApply.SetPosition( pOwner->GetPosition() + CVec3( vectorToTarget, 0.0f ) );
    }
  }

  // Create new instance 
  CObj<PFAbilityInstance> instance = new PFAbilityInstance( this, targetToApply, false );
  if (!instance->ApplyToTarget())
		return CObj<PFAbilityInstance>(0);
  rgInstances.push_back(instance);

  return instance;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CObj<PFAbilityInstance> PFAbilityData::Toggle( Target const& target )
{
  CObj<PFAbilityInstance> pInstance(0);

  if ( !isOn )
  {
    pInstance = pOwner->CreateAbilityInstance( this, target );
  }
  else
  {
    SwitchOff();
    CancelActiveInstances();
  }

  return pInstance;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFAbilityData::RemoveApplicatorsFrom(CPtr<PFBaseUnit> const& pUnit) const
{
  for ( InstancesVec::const_iterator iInst = rgInstances.begin(), iEnd = rgInstances.end(); iInst != iEnd; ++iInst )
    (*iInst)->RemoveApplicatorsFrom(pUnit);
  
  if (pPassiveInstance)
    pPassiveInstance->RemoveApplicatorsFrom(pOwner);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//void PFAbilityData::SetOwner(CPtr<PFBaseUnit> const& pOwner_)
//{
//  bool bIsOn = IsOn();
//  if (bIsOn && pOwner)
//    ApplyPassivePart(false);
//  pOwner = pOwner_;
//  if (bIsOn && pOwner)
//    ApplyPassivePart(bIsOn);
//}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFAbilityData::LevelUp()
{
  UpdateAbilityModifiers();
  RecalculateCooldown();

  if ( !pPassiveInstance )
    ApplyPassivePart(true);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFAbilityData::IsReady() const
{
  return cooldown[abilityState] < EPS_VALUE;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFAbilityData::IsEnoughMana() const
{
  if ( !IsValid( pOwner ) )
    return false;

  if ( DoesSpendLifeInsteadEnergy() )
    return GetManaCost() <= pOwner->GetLife();

  return GetManaCost() <= pOwner->GetMana();
}

void PFAbilityData::SpendMana() const
{
  if ( !IsValid( pOwner ) )
    return;

  if ( DoesSpendLifeInsteadEnergy() )
    pOwner->TakeHealth( GetManaCost() );
  else
    pOwner->TakeMana( GetManaCost() );
}

bool PFAbilityData::DoesSpendLifeInsteadEnergy() const
{
  return GetFlags() & NDb::ABILITYFLAGS_SPENDLIFEINSTEADENERGY;
}

bool PFAbilityData::IsActiveCustomTrigger() const
{
  if (GetDBDesc())
  {
    return GetDBDesc()->activeCustomTrigger;
  }

  return true;
}

bool PFAbilityData::DoesApplyToDead() const
{
  return GetFlags() & NDb::ABILITYFLAGS_APPLYTODEAD;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFAbilityData::CanBeUsed() const
{
  return ( IsOn() || IsEnoughMana() )
    && IsReady()
    && !IsForbidded()
    && IsCastSelfLimitationPassed();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFAbilityData::UpdateAbilityModifiers()
{
  if ( !IsValid(pOwner) || !pOwner->IsHero() )
    return;

  // Update cached modifiers if not actualized yet
  PFBaseHero const* pHero = static_cast<PFBaseHero const*>(pOwner.GetPtr());
  if ( cachedModifiersTime < pHero->AbilitiesModsGetActualizationTime() )
  {
    // Clear old cached values
    for ( int i = 0; i < NDb::KnownEnum<NDb::EAbilityModMode>::sizeOf; ++i )
      modifiers[i].clear();

    bool setSecondState = false;
    // Enumerate PFApplAbilityMod applicators, applied to 
    for (PFApplAbilityMod* mod = pHero->GetAbilitiesMods().first(), *last = pHero->GetAbilitiesMods().last(); mod != last; mod = PFApplAbilityMod::Ring::next(mod))
    {
      if (mod->GetMode() == NDb::ABILITYMODMODE_STATE)
      {
        if (mod->IsApplicable(mod->GetMode(), abilityType, GetDBDesc()))
        {
          setSecondState = true;
        }
      }
      else
      {
        mod->AddModifier( modifiers[mod->GetMode()].add, modifiers[mod->GetMode()].mul, mod->GetMode(), abilityType, GetDBDesc() );
      }
    }

    abilityState = setSecondState ? EAbilityState::Second : EAbilityState::First;

    // Update cached modifiers timestamp to actual
    cachedModifiersTime = pHero->AbilitiesModsGetActualizationTime();
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float PFAbilityData::GetModifiedValue(float value, NDb::EAbilityModMode mode) const
{
  NI_VERIFY( mode >= 0 &&  mode < (int)modifiers.capacity(), "Wrong ability modifier id!", return value );

  if ( !IsValid(pOwner) || !pOwner->IsHero() )
    return value;

  return value * modifiers[mode].mul + modifiers[mode].add;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float PFAbilityData::GetBaseManaCost() const
{
  float rawCost = pDBDesc->manaCost( pOwner, pOwner, this, 0.0f );
  return pOwner->GetManaCostModifier( DoesSpendLifeInsteadEnergy() ) * rawCost;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFAbilityData::RecalculateManaCost()
{
  if ( DoesSpendLifeInsteadEnergy() )
    manaCost = GetBaseManaCost(); // No mods for life spending
  else
    manaCost = GetModifiedValue( GetBaseManaCost(), NDb::ABILITYMODMODE_MANACOST );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFAbilityData::RecalculateCooldown()
{
  cooldownTime[EAbilityState::First] = GetModifiedValue( pDBDesc->cooldownTime( pOwner, pOwner, this, 0.0f ), NDb::ABILITYMODMODE_COOLDOWN );
  cooldownTime[EAbilityState::Second] = GetModifiedValue( pDBDesc->cooldownTimeSecondState( pOwner, pOwner, this, 0.0f ), NDb::ABILITYMODMODE_COOLDOWN );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFAbilityData::RestartCooldown(float cooldownTime_)
{
  if ( cooldownTime_ >= 0 )
    cooldownTime[abilityState] = cooldownTime_;
  cooldown[abilityState] = cooldownTime[abilityState];
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFAbilityData::RecalculateAndRestartCooldown()
{
  RecalculateCooldown();
  RestartCooldown();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFAbilityData::DropCooldown(bool forAllStates, float cooldownReduction /*= 0.0f*/, bool reduceByPercent /*= false */)
{
  if (forAllStates)
  {
    DropCooldown(EAbilityState::First, cooldownReduction, reduceByPercent);
    DropCooldown(EAbilityState::Second, cooldownReduction, reduceByPercent);
  }
  else
  {
    DropCooldown(abilityState, cooldownReduction, reduceByPercent);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFAbilityData::DropCooldown(EAbilityState::Enum forAbilityState, float cooldownReduction, bool reduceByPercent)
{
  if (cooldownReduction == 0.0f)
  {
    cooldown[forAbilityState] = 0.0f;
  }
  else
  {
    if (reduceByPercent)
    {
      cooldown[forAbilityState] = min(cooldownTime[forAbilityState], cooldown[forAbilityState] * (1.0f - min(cooldownReduction, 1.0f)));
    }
    else
    {
      cooldown[forAbilityState] = max(0.0f, cooldown[forAbilityState] - cooldownReduction);
      if (cooldown[forAbilityState] > cooldownTime[forAbilityState])
        cooldownTime[forAbilityState] -= cooldownReduction;
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float PFAbilityData::GetUseRange() const
{
  return pDBDesc->useRange(pOwner, pOwner, this, 0.0f);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float PFAbilityData::GetUseRange(const PFBaseUnit * pTarget) const
{
  if (IsValid(pTarget))
  {
    return pDBDesc->useRange(pOwner, pTarget, this, 0.0f);
  }
  else
  {
    NI_ALWAYS_ASSERT("Target must be valid!");
  }

  return pDBDesc->useRange(pOwner, pOwner, this, 0.0f);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float PFAbilityData::GetUseRange(const NWorld::Target & target) const
{
  if (target.IsUnit())
  {
    PFBaseUnit * targetUnit = target.GetUnit();
    if (IsValid(targetUnit))
    {
      return pDBDesc->useRange(pOwner, targetUnit, this, 0.0f);
    }
    else
    {
      NI_ALWAYS_ASSERT("Target must be valid!");
    }
  }

  return pDBDesc->useRange(pOwner, pOwner, this, 0.0f);
}

NDb::AlternativeTarget const* PFAbilityData::GetAlternativeTarget( Target const& origTarget, const bool bFromMinimap, Target& altTarget ) const
{
  vector<NDb::Ptr<NDb::AlternativeTarget>> const& dbAltTargets = pDBDesc->alternativeTargets;
  for ( int i = 0; i < dbAltTargets.size(); i++ )
  {
    NDb::AlternativeTarget const* pDBAltTarget = dbAltTargets[i];
    if ( pDBAltTarget && pDBAltTarget->targetSelector && pDBAltTarget->fromMinimap == bFromMinimap )
    {
      const PFTargetSelector::RequestParams rp( GetOwner(), this, origTarget );
      CObj<PFSingleTargetSelector> pTS = static_cast<PFSingleTargetSelector*>(pDBAltTarget->targetSelector->Create( 0 ));
      Target target;
      if ( pTS && pTS->FindTarget( rp, target ) )
      {
        if ( pDBAltTarget->updateTarget )
          altTarget = target;

        return pDBAltTarget;
      }
    }
  }
  return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFAbilityData::AddInstance(CObj<PFAbilityInstance> const& inst)
{
  rgInstances.push_back(inst);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFAbilityData::SwitchOff()
{
  isOn = false;

  RecalculateAndRestartCooldown();
}

void PFAbilityData::SwitchOn()
{
  isOn = true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFAbilityData::CancelAbility()
{
  if ( IsMultiState() )
  {
    SwitchOff();
  }
  else
  {
    RemoveApplicatorsFrom(pOwner);
  }

  // CancelActiveInstances 
  CancelActiveInstances();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFAbilityData::CancelActiveInstances()
{
  for ( InstancesVec::iterator iInst = rgInstances.begin(), iEnd = rgInstances.end(); iInst != iEnd; ++iInst )
    if ( IsValid(*iInst) )
      (*iInst)->Cancel();

  rgInstances.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFAbilityData::OnAbilityInstanceRemoved( PFAbilityInstance const* pInstance )
{
  InstancesVec::iterator iInst = find( rgInstances.begin(), rgInstances.end(), pInstance );
  //NI_ASSERT(iInst != rgInstances.end(), "Ability instance not found in instances vector!");
	if (iInst != rgInstances.end())
		rgInstances.erase(iInst);
}

static void AddNumber( const nstl::string& from, nstl::string& to )
{
	for ( int i = 0; i < from.size(); i++ )
	{
		if ( isdigit(from[i]) )
		{
			to += from[i];
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float PFAbilityData::GetWorkTime() const
{
	nstl::string nodeName = GetDBDesc()->node;
	nstl::string markerName  = "workTime";
	AddNumber( nodeName, markerName );
	float calcWorkTime = 0.0f;

	if ( nodeName.empty() || markerName.empty() )
		return 0.0f;

	bool needDelete = false;
	NScene::SceneObject* pSO = GetSO( needDelete );

	if ( !pSO )
	{
		return 0.0f;
	}

	calcWorkTime = GetMarkerPlace( pSO, nodeName, markerName );

	if ( needDelete )	 
		delete pSO;

  return calcWorkTime;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float PFAbilityData::GetSpeed() const
{ 
  const float workTime = GetWorkTime();
  return (workTime < EPS_VALUE) ? 0.0f : (1.0f / workTime); // yes, it`s not very logical, but it`s right
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float PFAbilityData::GetTimeOffset( bool getRawTime ) const
{
	const float rawTimeOffset = GetAttackTimeOffset();
	//NI_ASSERT( fabs( GetDBDesc()->attackTimeOffset - aTO ) < 0.1f, NStr::StrFmt( "Wrong AttackTimeOffest %f %f %s", GetDBDesc()->attackTimeOffset, aTO, GetFormattedDbId(GetDBDesc()->GetDBID()).c_str() ) );
  if( getRawTime )
    return rawTimeOffset;
  float stepLengthInSeconds = pWorld->GetStepLengthInSeconds();
  return int( rawTimeOffset / stepLengthInSeconds + 0.5f) * stepLengthInSeconds;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned PFAbilityData::GetFlags() const
{
  return GetDBDesc() ? GetDBDesc()->flags : 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float PFAbilityData::GetAoeSize() const
{
  return GetDBDesc() ? GetDBDesc()->aoeSize( pOwner, pOwner, this, 0.0f ) : 0.0f;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFAbilityData::OnDispatchStarted() const
{
  if( false == isInPassivePartUpdate && IsValid(pOwner) )
    pOwner->OnAbilityDispatchStarted( this );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFAbilityData::IsTargetValid( Target const& target, bool bAllowDead ) const
{
  if( target.IsPosition() )
    return true;

  if( target.IsUnit() )
  {
    CPtr<PFBaseUnit> const& pUnit = target.GetUnit();
    return IsValid(pUnit) ? (!pUnit->IsDead() ^ (GetDBDesc()->flags & NDb::ABILITYFLAGS_APPLYTODEAD) || bAllowDead) : false;
  }

  if( target.IsObject() )
    return target.IsObjectValid();

  return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// AbilityPars
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float PFAbilityData::GetDist2Target() const
{
  return 0.f;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float PFAbilityData::GetParentScale() const
{
  return 1.f;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PFAbilityData::GetAbilityType() const
{
  return (int)GetType();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFAbilityData::Roll(float probability ) const
{
  return GetOwner()->GetWorld()->GetRndGen()->Roll(probability);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PFAbilityData::GetRandom(int from, int to ) const
{
  return GetOwner()->GetWorld()->GetRndGen()->Next(from, to);
}

//////////////////////////////////////////////////////////////////////////
float PFAbilityData::GetRefineAbilityScale( float valueAtRefineLevel0, float incrementPerLevel ) const
{
  return valueAtRefineLevel0 + incrementPerLevel * (float)(GetRefineRate() - 1);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFAbilityData::GetSmartRoll( float probability, int maxFailReps, int maxSuccessReps, const IUnitFormulaPars* pFirst, const IUnitFormulaPars* pSecond ) const
{
  return GetOwner()->GetWorld()->GetSmartRndGen()->Roll( probability, maxFailReps, maxSuccessReps, pFirst, pSecond, GetDBDesc()->GetDBID().GetHashKey() );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PFAbilityData::GetSmartRandom( int outcomesNumber, float probDecrement, const IUnitFormulaPars* pFirst, const IUnitFormulaPars* pSecond ) const
{
  return GetOwner()->GetWorld()->GetSmartRndGen()->Random( outcomesNumber, probDecrement, pFirst, pSecond, GetDBDesc()->GetDBID().GetHashKey() );
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float PFAbilityData::CalcParam(const char *name, IUnitFormulaPars const *pSender, IUnitFormulaPars const* pReceiver, IMiscFormulaPars const* pMisc) const
{
  NDb::UnitConstant const* pConstant = GetConstant(name);
  
  NI_DATA_VERIFY( pConstant, NStr::StrFmt( "Constant '%s' not found in ability '%s'!", name, NDb::GetFormattedDbId( GetDBDesc()->GetDBID() ).c_str() ), return 0.0f; );

  return pConstant->var(pSender, pReceiver, pMisc, 0.0f);
}

NDb::UnitConstant const* PFAbilityData::GetConstant(char const *name) const
{
  NI_VERIFY( pConstantsMap, "Invalid Constants Map!", return NULL; );
  
  NDb::UnitConstant const* pConstant = pConstantsMap->Get(name);

  return pConstant;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float PFAbilityData::GetConstant(const char *name, IUnitFormulaPars const *pSender, IUnitFormulaPars const* pReceiver) const
{
  return CalcParam(name, pSender, pReceiver, this);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFAbilityData::CheckUpgradePerCastPerTarget() const
{
  // TODO: ?
  return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const IUnitFormulaPars* PFAbilityData::GetObjectOwner() const
{
  return GetOwner();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PFAbilityData::GetScrollLevel() const
{
  CPtr<PFBaseUnit> const& pOwner = GetOwner();
  return pOwner && pOwner->GetWorld() ?
    pOwner->GetWorld()->GetAIWorld()->GetAveragePriestessLvl( pOwner->GetFaction() ) : 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFAbilityData::IsNight() const
{
  const CPtr<PFBaseUnit>& pOwner = GetOwner();

  if (!pOwner)
    return false;
  if (!pOwner->GetWorld())
    return false;

  return pOwner->GetWorld()->IsNight();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NDb::CastLimitation const* PFAbilityData::CheckCastLimitations( const Target& target ) const
{
  const CastLimitationsCheckParams cp( *this, target );

  typedef vector<NDb::Ptr<NDb::CastLimitation>> CastLimitations;
  const CastLimitations &castLimitations = pDBDesc->castLimitations;
  for ( CastLimitations::const_iterator it = castLimitations.begin(); it != castLimitations.end(); it++ )
  {
    const NDb::Ptr<NDb::CastLimitation>& curLimit = *it;
    if ( !curLimit->Check( cp ) )
    {
      // Application failed
      return curLimit;
    }
  }

  return 0;
}
 
::DiAnimGraph* PFAbilityData::GetAG( NScene::SceneObject* so ) const
{
	if ( so->GetRootComponent() )
		if ( NScene::AnimatedSceneComponent* asc = dynamic_cast<NScene::AnimatedSceneComponent*>(so->GetRootComponent()) )
			if ( asc->GetMainAnimGraph()->GetDBFileName() != "none" )
				return asc->GetMainAnimGraph();

	struct AGFinder : public NScene::FullTraverser
	{
		bool isFind;
		::DiAnimGraph* ag;

		AGFinder() : isFind( false ), ag( 0 ) {}

		void operator()( NScene::SceneComponent *pSC )
		{
			if ( isFind )
				return;

			if ( NScene::AnimatedSceneComponent* asc = dynamic_cast<NScene::AnimatedSceneComponent*>(pSC) )
			{
				if ( asc->GetMainAnimGraph() && asc->GetMainAnimGraph()->GetDBFileName() != "none" )
				{
					ag = asc->GetMainAnimGraph();
					isFind = true;
				}
			}
		}
	} finder;
	so->Traverse( finder );
	
	if ( finder.isFind )
		return finder.ag;

	return 0;
}

float PFAbilityData::GetAttackTimeOffset() const
{
	nstl::string nodeName = GetDBDesc()->node;
	nstl::string markerName  = GetDBDesc()->marker;
	float attackTimeOffset = 0.0f;

	if ( pDBDesc->GetObjectTypeID() == NDb::BaseAttack::typeId )
	{
		nodeName = "attack";
		markerName = "doFire";
	}

	if ( nodeName.empty() || markerName.empty() || fabs(GetWorkTime()) < EPS_VALUE  )
		return 0.0f;

	bool needDelete = false;
	NScene::SceneObject* pSO = GetSO( needDelete );

	if ( !pSO )
	{
		return 0.0f;
	}

	attackTimeOffset = GetMarkerPlace( pSO, nodeName, markerName );

	if ( needDelete )	 
		delete pSO;

	return attackTimeOffset;
}

float PFAbilityData::GetMarkerPlace( NScene::SceneObject* pSO, const nstl::string &nodeName, const nstl::string &markerName ) const
{
	::DiAnimGraph* pAG = GetAG( pSO );
	if ( !pAG )
	{
		NI_ALWAYS_ASSERT( NStr::StrFmt("Can not find AG in %s", pSO->GetRootComponent()->GetDBID().GetFileName().c_str()) );
		return 0.0f;
	}

	uint nodeId = pAG->GetNodeIDByNameSlowQuite( nodeName.c_str() );
	if ( nodeId >= pAG->GetNumNodes() )
	{
		NI_ALWAYS_ASSERT( NStr::StrFmt("Can not find node %s in %s in %s", nodeName.c_str(), pAG->GetDBFileName().c_str(), pSO->GetRootComponent()->GetDBID().GetFileName().c_str()) );
		return 0.0f;
	}
	DiAnimNode* node = pAG->GetNodeData( nodeId );
	if ( !node )
	{
		NI_ALWAYS_ASSERT( NStr::StrFmt("Can not find node %s in %s in %s", nodeName.c_str(), pAG->GetDBFileName().c_str(), pSO->GetRootComponent()->GetDBID().GetFileName().c_str()) );
		return 0.0f;
	}
	DiAnGrMarker* marker = 0;
	if ( node->IsSwitcher() )
	{
		struct FindMarker : public INeiFunctor
		{
			bool isFind;
			DiAnGrMarker* marker;
			nstl::string markerName;
			DiAnimNode* animNode;
			DiAnimGraph* pAG;

			FindMarker( DiAnimGraph* ag, const nstl::string& markerName ) : isFind( false ), marker( 0 ), animNode( 0 ), pAG( ag ), markerName( markerName ) {}
			virtual void operator()( DiUInt32 nodeId )
			{
				if ( isFind )
					return;

				DiAnimNode* node = pAG->GetNodeData( nodeId );
				if ( node->IsSubNode() )
				{
					marker = pAG->FindMarkerByNameInNode( markerName, nodeId );
					animNode = node;
					if ( marker )
						isFind = true;
				}
			}
		} f( pAG, markerName );
		pAG->ForAllNeighbours( nodeId, &f );

		if ( f.isFind )
		{
			marker = f.marker;
			node = f.animNode;
		}
	}
	else
	{
		marker = pAG->FindMarkerByNameInNode( markerName, nodeId );
	}

	if ( !marker )
	{
		return 0.0f;
	}

	float virtPar = marker->GetVirtPar();
	virtPar /= node->GetSpeed();

	return virtPar;
}

NScene::SceneObject* PFAbilityData::GetSO( bool& needDelete ) const
{
	needDelete = false;
	NScene::SceneObject* pSO = GetOwner()->GetClientSceneObject();

	if ( !pSO )
	{
		if ( !GetOwner()->DbUnitDesc()->sceneObject.IsEmpty() )
		{
			AutoPtr<NScene::SceneObject> so = NScene::CreateSceneObject( GetWorld()->GetScene(), *GetOwner()->DbUnitDesc()->sceneObject.GetPtr(), BADNODENAME );
			pSO = Release( so );
		}
		else if ( const NDb::BaseHero* hero = dynamic_cast<const NDb::BaseHero*>( GetOwner()->DbUnitDesc() ) )
		{
			AutoPtr<NScene::SceneObject> so = NScene::CreateSceneObject( GetWorld()->GetScene(), *hero->heroSceneObjects[0].GetPtr(), BADNODENAME );
			pSO = Release( so );
		}
		else
			return 0;

		needDelete = true;
	}
	return pSO;
}

bool PFAbilityData::IsInstaCast() const
{
  return (GetFlags() & NDb::ABILITYFLAGS_INSTACAST);
}

bool PFAbilityData::GetEventTypeByAbilityTypeId( NDb::EBaseUnitEvent& eventType )
{
  switch ( abilityType )
  {
    case NDb::ABILITYTYPEID_ABILITY0:
    case NDb::ABILITYTYPEID_ABILITY1:
    case NDb::ABILITYTYPEID_ABILITY2:
    case NDb::ABILITYTYPEID_ABILITY3:
    case NDb::ABILITYTYPEID_ABILITY4:
      eventType = NDb::BASEUNITEVENT_CASTMAGIC;
      return true;

    case NDb::ABILITYTYPEID_TALENT:
      eventType = NDb::BASEUNITEVENT_USETALENT;
      return true;

    case NDb::ABILITYTYPEID_CONSUMABLE:
      eventType = NDb::BASEUNITEVENT_USECONSUMABLE;
      return true;

    case NDb::ABILITYTYPEID_PORTAL:
      eventType = NDb::BASEUNITEVENT_USEPORTAL;
      return true;

    // no events for other ability types
    default:
      return false;
  }
}

float PFAbilityData::GetAbilityScale( bool isDamage, float statValue, EAbilityScaleMode abScaleMode, float valueLeft, float valueRight, bool bRound /*= true*/ ) const
{
  const NDb::AbilityAndDamageScalingParams& pDBAIParams = GetOwner()->GetWorld()->GetAIWorld()->GetAIParameters().abilityAndDamageScalingParams;

  float statLeft = 0.0f, statRight = 0.0f;

  switch (abScaleMode)
  {
    case ABILITYSCALEMODE_STAT:
      statLeft  = isDamage ? pDBAIParams.damageScaleStatLeft  : pDBAIParams.abilityScaleStatLeft;
      statRight = isDamage ? pDBAIParams.damageScaleStatRight : pDBAIParams.abilityScaleStatRight;
      break;
    case ABILITYSCALEMODE_LIFE:
      statLeft  = isDamage ? pDBAIParams.damageScaleLifeLeft  : pDBAIParams.abilityScaleLifeLeft;
      statRight = isDamage ? pDBAIParams.damageScaleLifeRight : pDBAIParams.abilityScaleLifeRight;
      break;
    case ABILITYSCALEMODE_ENERGY:
      statLeft  = isDamage ? pDBAIParams.damageScaleEnergyLeft  : pDBAIParams.abilityScaleEnergyLeft;
      statRight = isDamage ? pDBAIParams.damageScaleEnergyRight : pDBAIParams.abilityScaleEnergyRight;
      break;

    default:
      NI_ALWAYS_ASSERT( "Unknown ability scale mode" );
      return 0.0f;
  }

  float result = max( ( statValue - statLeft ) * ( valueRight - valueLeft ) / ( statRight - statLeft ) + valueLeft, valueLeft );

  if ( bRound )
    result = Round( result );

  return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFAbilityData::IsAbilitySupposedToStopUnit() const
{
  unsigned flags = GetFlags();
  if ( flags & NDb::ABILITYFLAGS_FORCEDONOTSTOPUNIT )
  {
    return false;
  }
  return IsAbilitySupposedToSyncVisual();
}

bool PFAbilityData::IsAbilitySupposedToSyncVisual() const
{
  unsigned flags = GetFlags();
  return ( flags & NDb::ABILITYFLAGS_MOMENTARY) == 0
      || ( flags & NDb::ABILITYFLAGS_WAITFORCHANNELING )
      || ( NStr::Len( GetAbilityNode() ) > 0 )
      || GetDBDesc()->isUnitFreeAfterCast == false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFAbilityData::IsAbilitySuitable( NDb::Ability const* pDbAbility, vector<NDb::Ptr<NDb::Ability>> const& dbAbilities, NDb::EUseMode mode )
{
  bool isTalentInList = false;

  for ( int j = 0; j < dbAbilities.size(); j++ )
  {
    if ( pDbAbility->GetDBID() == dbAbilities[j]->GetDBID() )
    {
      isTalentInList = true;
      break;
    }
  }

  return mode == NDb::USEMODE_LISTASRULE      &&  isTalentInList ||
         mode == NDb::USEMODE_LISTASEXCEPTION && !isTalentInList;
}

float PFAbilityData::GetTerrainPart(int faction) const
{
  return GetWorld()->GetNatureMap()->GetNaturePercent((NDb::EFaction)faction);
}

int PFAbilityData::GetTerrianTypeUnderCursor() const
{
  CVec3 posOnTerra = NGameX::AdventureScreen::Instance()->GetCurrentCursorPosOnTerrain();
  return GetWorld()->GetNatureMap()->GetNatureInPoint(posOnTerra.X(), posOnTerra.Y());
}

int PFAbilityData::GetNatureTypeInPos(CVec2 pos) const
{
  return GetWorld()->GetNatureMap()->GetNatureInPoint(pos.x, pos.y);
}

int PFAbilityData::GetActivatedWithinKit() const
{
  NI_ALWAYS_ASSERT( "Trying to get kit property for generic ability" );
  return 0;
}

int PFAbilityData::GetTalentsWithinKit() const
{
  NI_ALWAYS_ASSERT( "Trying to get kit property for generic ability" );
  return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float PFAbilityData::GetStatusDispellPriority( const IUnitFormulaPars* pUnitToCheck, bool returnDuration ) const
{
  return -1.0; // Has no sense for ability
}

void PFAbilityData::SubscribeChanneling( PFBaseUnitEventListener *pListener )
{
  list<CObj<PFBaseUnitEventListener>>::iterator it = nstl::find( channelings.begin(), channelings.end(), pListener );
  if ( it == channelings.end() )
  {
    channelings.push_back( pListener );
  }
}

void PFAbilityData::UnsubscribeChanneling( PFBaseUnitEventListener *pListener )
{
  list<CObj<PFBaseUnitEventListener>>::iterator it = nstl::find( channelings.begin(), channelings.end(), pListener );
  if ( it != channelings.end() )
    channelings.erase( it );
}

void PFAbilityData::AddForbid( const PFBaseApplicator* pAppl /*= 0*/ )
{
  forbids++;

  if ( !IsValid( pAppl ) )
    return;

  if ( channelings.empty() )
    return;

  PFBaseUnitApplicatorEvent evt( NDb::BASEUNITEVENT_FORBIDCAST, pAppl );

  for ( nstl::list<CObj<PFBaseUnitEventListener>>::iterator it = channelings.begin(); it != channelings.end(); )
  {
    PFBaseUnitEventListener *pListener = *it;

    if (pListener)
    {
      unsigned int returnFlags = pListener->OnEvent(&evt);
      if (returnFlags & PFBaseUnitEventListener::FLAGS_REMOVE)
        it = channelings.erase( it );
      else 
        ++it;
    }
    else
    {
      NI_ALWAYS_ASSERT("Bad event listener!");
      it = channelings.erase( it );
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFConsumableAbilityData::NotifyCastProcessed()
{
  if ( !IsValid(GetOwner()) )
    return;

  CPtr<PFWorld> pWorld = GetWorld();
  
  if(IsValid(pWorld))
    pWorld->NotifyConsumableProcessed(this);

  if ( IsValid(pUsingConsumable) )
  {
    pUsingConsumable->AddQuantity( -1 );
    if ( pUsingConsumable->GetQuantity() <= 0 )
    {
      GetOwner()->RemoveConsumable( pUsingConsumable );
    }

    pUsingConsumable = 0;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PFConsumableAbilityData::PFConsumableAbilityData( CPtr<PFBaseUnit> const& pOwner_, NDb::Ptr<NDb::Ability> const& pDBDesc, NDb::EAbilityTypeId abilityType, bool needRegisterInWorld /*= true*/, bool /*= false*/)
: PFAbilityData( pOwner_, pDBDesc, abilityType, needRegisterInWorld, false ), pOwner(dynamic_cast<PFBaseHero*>(pOwner_.GetPtr())), pDBGroup(0) {}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFConsumableAbilityData::RestartCooldown( float cooldownTime_ )
{
  PFAbilityData::RestartCooldown( cooldownTime_ );

  if ( !IsValid(GetOwner()) )
    return;

  if ( pDBGroup )
    GetOwner()->RestartGroupCooldowns( this );
}

} //namespace NWorld

REGISTER_WORLD_OBJECT_NM(PFAbilityData, NWorld);
REGISTER_WORLD_OBJECT_NM(PFConsumableAbilityData, NWorld);
