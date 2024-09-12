#include "stdafx.h"
#include "PFApplicator.h"
#include "PFWorld.h"
#include "PFAIWorld.h"
#include "PFBaseUnit.h"
#include "PFTargetSelector.h"
#include "PFHero.h"
#include "PFDispatchStrike1.h"
#include "PFWorldNatureMap.h"
#include "PFDispatchFactory.h"
#include "PFBaseMovingUnit.h"
#include "../Core/CoreFSM.h"
#include "PFLogicDebug.h"
#include "FormulaExecutor.h"
#include "PFApplicatorHistoryAnalysis.h"
#include "PFTree.h"
#include "PFTalent.h"
#include "TileMap.h"

#include "PFAbilityInstance.h"
#include "PFApplInstant.h"
#include "SmartRandom.h"

#include "AdventureScreen.h"
//#define LOG_APPLICATORS_LIFECYCLE

namespace NWorld
{

namespace
{

const PFBaseApplicator* GoUpByApplicatorHierarchy(const PFBaseApplicator *pStart, int levelsUp = 100000)
{
	int count = levelsUp;

	const PFBaseApplicator *pAppl = pStart;
	while (IsValid(pAppl->GetParentAppl()) && count > 0)
	{
		pAppl = pAppl->GetParentAppl().GetPtr();
		--count;
	}

	return pAppl;
}

}

#ifndef _SHIPPING
  map<NDb::DBID, int> PFBaseApplicator::s_ActiveApplicatorsCountByDBID;
#endif

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
IUnitFormulaPars const *PFBaseApplicator::RetriveReciever() const
{ 
  return target.IsUnit() ? target.GetUnit() : 0; 
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float PFBaseApplicator::RetrieveParam(ExecutableFloatString const &par, float defaultValue) const
{ 
  return par(GetAbilityOwner(), pReceiver, this, defaultValue); 
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFBaseApplicator::RetrieveParam(ExecutableBoolString const &par, bool defaultValue) const
{ 
  return par(GetAbilityOwner(), pReceiver, this, defaultValue); 
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int  PFBaseApplicator::RetrieveParam(ExecutableIntString const &par, int defaultValue) const
{ 
  return par(GetAbilityOwner(), pReceiver, this, defaultValue); 
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PFBaseApplicator::GetRank() const
{
  return pAbility ? pAbility->GetRank() : 1;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const CObj<PFDispatch>& PFBaseApplicator::GetDispatch() const {
  return (!pDispatch && IsValid(pParent)) ? pParent->GetDispatch() : pDispatch;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CVec2 PFBaseApplicator::GetTargetPos(void) const
{
  if (GetTarget().IsPosition())
    return GetTarget().GetPosition().AsVec2D();
  else
    return GetTarget().GetObject()->GetPos();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float PFBaseApplicator::GetScale() const
{
  return GetAbility()->GetScale() * GetParentScale();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFBaseApplicator::IsAbilityOn() const
{
  return pAbility ? pAbility->IsOn() : true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float PFBaseApplicator::GetDist2Target() const
{
	if (!pOwner)
    return 0.0f;

  CVec2 dist = target.AcquirePosition().AsVec2D() - pOwner->GetPosition().AsVec2D();
  return dist.Length();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float PFBaseApplicator::GetManaCost() const
{
  return GetAbilityData()->GetManaCost();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float PFBaseApplicator::GetPreparedness() const
{
  return GetAbilityData()->GetPreparedness();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PFBaseApplicator::GetAbilityType() const
{
  return GetAbilityData()->GetType();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PFBaseApplicator::GetScrollLevel() const
{
  return pOwner && pOwner->GetWorld() ?
    pOwner->GetWorld()->GetAIWorld()->GetAveragePriestessLvl( pOwner->GetFaction() ) : 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFBaseApplicator::IsNight() const
{
  if (!pOwner)
    return false;
  if (!pOwner->GetWorld())
    return false;

  return pOwner->GetWorld()->IsNight();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float PFBaseApplicator::GetParentScale() const
{
  if (IsValid(pParent))
    return pParent->GetScale();
  else
    return 1.0f;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFBaseApplicator::Roll(float probability) const
{
	return pOwner ? pOwner->GetWorld()->GetRndGen()->Roll(probability) : false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PFBaseApplicator::GetRandom(int from, int to) const
{
  return pOwner ? pOwner->GetWorld()->GetRndGen()->Next(from, to) : (from + to) / 2 ;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFBaseApplicator::GetSmartRoll( float probability, int maxFailReps, int maxSuccessReps, const IUnitFormulaPars* pFirst, const IUnitFormulaPars* pSecond ) const
{
  return pOwner ? pOwner->GetWorld()->GetSmartRndGen()->Roll( probability, maxFailReps, maxSuccessReps, pFirst, pSecond, GetDBBase()->GetDBID().GetHashKey() ) : false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PFBaseApplicator::GetSmartRandom( int outcomesNumber, float probDecrement, const IUnitFormulaPars* pFirst, const IUnitFormulaPars* pSecond ) const
{
  return pOwner ? pOwner->GetWorld()->GetSmartRndGen()->Random( outcomesNumber, probDecrement, pFirst, pSecond, GetDBBase()->GetDBID().GetHashKey() ) : 0;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float PFBaseApplicator::GetConstant(const char *name, IUnitFormulaPars const *pSender, IUnitFormulaPars const* pReceiver) const
{
  if ( IsValid( pUpgraderAbilityData ) )
  {
    return pUpgraderAbilityData->CalcParam(name, pSender, pReceiver, this);
  }
  return pAbility && pAbility->GetData() ? pAbility->GetData()->CalcParam(name, pSender, pReceiver, this) : 0.0f;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NDb::UnitConstant const* PFBaseApplicator::GetConstant( const char *name ) const
{
  if ( IsValid( pUpgraderAbilityData ) )
  {
    return pUpgraderAbilityData->GetConstant( name );
  }
  return pAbility && pAbility->GetData() ? pAbility->GetData()->GetConstant( name ) : NULL;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PFBaseApplicator::GetTerrainType() const
{
	CVec3 pos = AcquireApplicationPosition();
	return GetAbilityOwner()->GetWorld()->GetNatureMap()->GetNatureInPoint(pos.x, pos.y);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
IUnitFormulaPars const* PFBaseApplicator::GetObject( char const* objName ) const
{
  if ( strcmp( objName, "Target" ) == 0 )
  {
    if ( target.IsObjectValid( true ) )
      return target.GetObject();
  }
  else if ( strcmp( objName, "AbilityTarget" ) == 0 )
  {
    Target const& targ = GoUpByApplicatorHierarchy( this )->GetTarget();
    if ( targ.IsObjectValid( true ) )
      return targ.GetObject();
  }
  else if ( strcmp( objName, "InitialTarget" ) == 0 )
  {
    AbilityTarget const& targ = pAbility->GetTarget();
    if ( targ.IsObjectValid( true ) )
      return targ.GetObject();
    else if ( targ.IsPosition() )
      return 0;
  }

  return pReceiver;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float PFBaseApplicator::GetAbilityScale( bool isDamage, float statValue, EAbilityScaleMode abScaleMode, float valueLeft, float valueRight, bool bRound /*= true*/ ) const
{
  return GetAbilityData()->GetAbilityScale( isDamage, statValue, abScaleMode, valueLeft, valueRight, bRound );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PFBaseApplicator::GetAlternativeTargetIndex() const
{
  return pAbility->GetTarget().GetDBAlternativeTarget() ? pAbility->GetTarget().GetDBAlternativeTarget()->index : -1;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PFBaseApplicator::MakeSpellTargetFactionFlags(NDb::ESpellTarget spellTarget) const
{
	return NWorld::MakeSpellTargetFactionFlags(*GetAbilityOwner(), spellTarget);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PFBaseApplicator::PFBaseApplicator(PFApplCreatePars const &cp)
: PFWorldObjectBase( (cp.pAbility ? cp.pAbility->GetWorld() : (IsValid(cp.pWorld) ? cp.pWorld : 0)) , 0 )
, pAbility(cp.pAbility)
, pOwner( cp.pAbility ? cp.pAbility->GetOwner() : (IsValid(cp.pOwner) ? cp.pOwner : 0) )
, pParent(cp.pParent), target(cp.target), pDBAppl(cp.pDBAppl), pDispatch(cp.pDispatch)
, flags(FLAG_ENABLED)
, bPassive(cp.bPassive)
, stopReason(APPL_STOP_REASON_NONE)
{
  NI_ASSERT( IsValid(pOwner) || !pAbility, "Owner must be valid!" );
	// Save time
  if (cp.pAbility)
	  markerTime = cp.pAbility->GetOwner()->GetWorld()->GetTimeElapsed();
#ifdef LOG_APPLICATORS_LIFECYCLE
	DebugTrace("APPL %s (%08X) created normally by %s (%08X)", this->GetObjectTypeName(), int(this),
		         pParent ? pParent->GetObjectTypeName() : "root", int(pParent.GetPtr()));
#endif

  if ( !GetDBBase()->providerName.empty() )
  {
    PFTalent* pTalent = pOwner->GetTalentById( GetDBBase()->providerName.c_str() );
    NI_DATA_ASSERT( pTalent || !pOwner->IsTrueHero(), "Providing talent not found" );
    pUpgraderAbilityData = pTalent;
  }

  if ( pUpgraderAbilityData == 0 && cp.pParent)
    pUpgraderAbilityData = cp.pParent->GetUpgraderAbilityData();

  if ( pUpgraderAbilityData == 0 )
    pUpgraderAbilityData = cp.pUpgraderAbilityData;

  if ( IsValid( pAbility ) && pAbility->GetData()->IsMelee() )
    flags |= FLAG_MELEE;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PFBaseApplicator::PFBaseApplicator()
{
#ifdef LOG_APPLICATORS_LIFECYCLE
	DebugTrace("APPL %s (%08X) recreated as invalid", this->GetObjectTypeName(), int(this));
#endif
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PFBaseApplicator::~PFBaseApplicator()
{
#ifdef LOG_APPLICATORS_LIFECYCLE
	DebugTrace("APPL %s (%08X) deleted finally", this->GetObjectTypeName(), int(this));
#endif
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFBaseApplicator::Init()
{
	Target targ;
	MakeApplicationTarget(targ);

	if (targ.IsUnit())
		pReceiver = targ.GetUnit();
  else
    pReceiver = 0;

	NI_DATA_VERIFY(CheckTarget(targ), 
								 NStr::StrFmt( "Applicator %s DBID(%s, %s) is going to be applied on wrong target: %s", 
								               pDBAppl->GetObjectTypeName(), 
															 pDBAppl->GetDBID().GetFileName().c_str(), 
															 pDBAppl->GetDBID().GetId().c_str(), 
															 targ.IsUnit() ? targ.GetUnit()->GetObjectTypeName() : "position" ),
								 return false; )

	return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseApplicator::SetEnabled(bool isEnabled)
{
	if (isEnabled)
		flags |= FLAG_ENABLED;
	else
		flags &= ~FLAG_ENABLED;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseApplicator::SetBlocked(bool isBlocked)
{
	if (isBlocked)
		flags |= FLAG_BLOCKED;
	else
		flags &= ~FLAG_BLOCKED;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseApplicator::SetChanged(bool isChanged)
{
	if (isChanged)
		flags |= FLAG_CHANGED;
	else
		flags &= ~FLAG_CHANGED;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFBaseApplicator::Start() 
{ 
	// Remove applicators that are not stackable with this one
	if (IsValid(pReceiver) && !IsStackableWithTheSameType())
	{
		struct RemoveSameApplicator
		{
			RemoveSameApplicator(const PFBaseApplicator* pNewcomer) 
				: typeID(pNewcomer->GetTypeId()) {}

			void operator()(const CObj<PFBaseApplicator> &pAppl)
			{
				if (pAppl->GetTypeId() == typeID)
				{
					pAppl->Stop();
					MemorizeApplicator(pAppl);
				}
			}

		private:
			int typeID;
		} f(this);
		
		pReceiver->ForAllAppliedApplicators(f);
	}

	LogApplicator(*this, "START APPLICATOR");

  if (pAbility)
    pAbility->NotifyApplicatorStarted(pReceiver);
	if (IsValid(pParent))
		pParent->OnNotification(*this, NDb::PARENTNOTIFICATION_START);
  
  // delegated applicators are always enabled at Start
  bool isEnabled = (flags & FLAG_DELEGATED) == 0 ? RetrieveParam(pDBAppl->enabled, true) : true;
	SetEnabled(isEnabled);

#ifdef LOG_APPLICATORS_LIFECYCLE
	DebugTrace("APPL %s (%08X) started as %s", this->GetObjectTypeName(), int(this), isEnabled ? "enabled" : "disabled");
#endif
  
  return !isEnabled; 
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseApplicator::Stop() 
{ 
#ifdef LOG_APPLICATORS_LIFECYCLE
	DebugTrace("APPL %s (%08X) stopped", this->GetObjectTypeName(), int(this));
#endif

	pDispatch = 0; // No need to store dispatch any more
  pUpgraderAbilityData = 0; // same

	NI_ASSERT(IsAlive(), "Applicator already stopped! It's a bug!");
  LogApplicator(*this, "STOP APPLICATOR");
  if (pAbility)
    pAbility->NotifyApplicatorStopped(pReceiver); 
	if (IsValid(pParent))
		pParent->OnNotification(*this, NDb::PARENTNOTIFICATION_STOP);
	
	flags |= FLAG_STOPPED;

  // Remove from named applicators list if name not empty
  if ( namedRingPart.isLinked() )
  {
    NamedRing::remove(this);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFBaseApplicator::Step(float /*dtInSeconds*/) 
{
  bool isEnabled = IsEnabled();
    
  if (!IsBlocked())
    isEnabled = RetrieveParam(pDBAppl->enabled, true);
  
  if ( pOwner && pOwner->IsDead() )
    isEnabled &= !NeedToDisableOnDeath(); // need to disable if owner die?
  
  if (isEnabled == IsEnabled())
    return false;

	SetEnabled(isEnabled);
	if (isEnabled)
    Enable();
  else
    Disable();

  return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseApplicator::Enable()
{
  LogApplicator(*this, "ENABLE APPLICATOR");
	NI_ASSERT(IsEnabled(), "Logic failed");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseApplicator::Disable()
{
  LogApplicator(*this, "DISABLE APPLICATOR");
	NI_ASSERT(!IsEnabled(), "Logic failed");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseApplicator::Block()
{
  SetBlocked(true);

  if (IsEnabled())
  {
    SetEnabled(false);
    Disable();
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseApplicator::Unblock()
{
  SetBlocked(false);

  if (!IsEnabled())
  {
    SetEnabled(true);
    Enable();
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseApplicator::MakeApplicationTarget(Target &targ, NDb::EApplicatorApplyTarget applyTarget) const
{
	switch (applyTarget)
	{
	case NDb::APPLICATORAPPLYTARGET_APPLICATORTARGET: 
	case NDb::APPLICATORAPPLYTARGET_APPLICATORSELECTEDTARGET: 
		targ = target; 
		break;
	case NDb::APPLICATORAPPLYTARGET_ABILITYOWNER: 
		targ.SetUnit(GetAbilityOwner()); 
		break;
	case NDb::APPLICATORAPPLYTARGET_PREVAPPLICATORTARGET:
		if (IsValid(pParent))
			targ = pParent->GetTarget();
		else
			targ = target;
		break;
	case NDb::APPLICATORAPPLYTARGET_PREVAPPLICATORRECEIVER:
		if (IsValid(pParent))
			targ.SetUnit(pParent->GetReceiver());
		else
			targ = target;
		break;
	case NDb::APPLICATORAPPLYTARGET_HIER1UPAPPLICATORTARGET:
		targ = GoUpByApplicatorHierarchy(this, 1)->GetTarget();
		break;
	case NDb::APPLICATORAPPLYTARGET_HIER2UPAPPLICATORTARGET:
		targ = GoUpByApplicatorHierarchy(this, 2)->GetTarget();
		break;
	case NDb::APPLICATORAPPLYTARGET_HIER3UPAPPLICATORTARGET:
		targ = GoUpByApplicatorHierarchy(this, 3)->GetTarget();
		break;
	case NDb::APPLICATORAPPLYTARGET_ABILITYTARGET:
		targ = GetAbility()->GetTarget();
		break;
  case NDb::APPLICATORAPPLYTARGET_CASTPOSITION:
    targ = Target( GetAbility()->GetCastPosition() );
    break;
  case NDb::APPLICATORAPPLYTARGET_CASTMASTERPOSITION:
    targ = Target( GetAbility()->GetCastMasterPosition() );
    break;
	default:
		NI_ALWAYS_ASSERT("Invalid applicator applyTarget");
		targ = target; 
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CVec3 PFBaseApplicator::AcquireApplicationPosition() const
{
	Target targ;
	MakeApplicationTarget(targ);
	return targ.AcquirePosition();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFBaseApplicator::CheckTarget(const Target &target) const
{
	// Check target type
	NI_ASSERT(target.GetType() != Target::INVALID, "Uninitialized target");
	if ( ((1 << target.GetType()) & GetAcceptableTargetFlags()) == 0 )
		return false; 

	// Check unit type
	if (target.IsUnit() && ( (1 << target.GetUnit()->GetUnitType()) & GetAcceptableUnitTypeFlags() ) == 0 )
		return false;

	return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Collect all applicators that was made by this one to specified ring
struct ApplicatorsToStopCollector : public NonCopyable
{ 
  PFBaseApplicator const*     pParent;
  PFBaseApplicator::SentRing& applicatorsToStop;

  ApplicatorsToStopCollector( PFBaseApplicator const* pParent, PFBaseApplicator::SentRing& applicatorsToStop )
    : pParent(pParent), applicatorsToStop(applicatorsToStop) {}
  
  void operator()(CObj<PFBaseApplicator> const &pApp)
  {
    if (pApp->GetParentAppl() == pParent)
    {
      PFBaseApplicator::SentRing::safeRemove(pApp);
      applicatorsToStop.addLast(pApp);
    }
  }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseApplicator::RemoveChildrenApplicators()
{
	PFBaseApplicator::SentRing applicatorsToStop;
  
  // Remove all applicators that was made by this one
	ApplicatorsToStopCollector f(this, applicatorsToStop);

  if(IsValid(pOwner))
  {
    pOwner->ForAllSentApplicators(f);
    pOwner->ForAllAppliedApplicators(f);
  }

  if(IsValid(pReceiver))
  {
    pReceiver->ForAllSentApplicators(f);
    pReceiver->ForAllAppliedApplicators(f);
  }

  while (!applicatorsToStop.empty())
  {
    PFBaseApplicator *app = applicatorsToStop.first();

    CObj<PFBaseApplicator> applObj(app);

    PFBaseApplicator::SentRing::remove(app);

    app->Stop();
    MemorizeApplicator(app);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseApplicator::RemoveChildrenApplicatorsFromUnit(PFBaseUnit *pUnit)
{
	// Remove all applicators from unit that was made by this one
  PFBaseApplicator::SentRing applicatorsToStop;

  // Remove all applicators that was made by this one
  ApplicatorsToStopCollector f(this, applicatorsToStop);
  pUnit->ForAllAppliedApplicators(f);

  while (!applicatorsToStop.empty())
  {
    PFBaseApplicator *app = applicatorsToStop.first();

    CObj<PFBaseApplicator> applObj(app);

    PFBaseApplicator::SentRing::remove(app);

    app->Stop();
    MemorizeApplicator(app);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseApplicator::Recalculate()
{
	// Recalculation should be manual for each applicator (if needed)
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CPtr<PFBaseUnit> PFBaseApplicator::GetAbilityOwner() const
{ 
  return pOwner.GetPtr();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseApplicator::DumpInfo(NLogg::CChannelLogger &logger) const
{
	LogLogicInfo(logger)("    %s from %s @ %2.2f (%08X) (%s)\n", 
		                    GetDBBase()->GetObjectTypeName(), MakeUnitIDString(GetAbilityOwner()), GetMarkerTime(), (void*)this, bPassive ? "passive" : "active");

	LogLogicInfo(logger)("      parent: %s (%08X)\n", IsValid(pParent) ? pParent->GetObjectTypeName() : "root", (void*)pParent.GetPtr() );
	LogLogicInfo(logger)("      applied on: %s\n", pReceiver ? MakeUnitIDString(pReceiver) : "ground" );

	if (target.IsPosition())
	{
		const CVec3 &pos = target.GetPosition();
		LogLogicInfo(logger)("      target: (%3.2f, %3.2f)\n", pos.x, pos.y);
	}
	else
	{
		LogLogicInfo(logger)("      target: %s\n", MakeUnitIDString(target.GetObject()));
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFBaseApplicator::CheckDamageTypeFilter( int flags, int damageType, NDb::EDamageFilter filterFlags, bool enableReflected )
{
  // Don't reflect reflected damage
  if ( !enableReflected && (flags & FLAG_REFLECTED) )
    return false;

  // Melee/range filter
  int toCheck = (flags & FLAG_MELEE) != 0 ? NDb::DAMAGEFILTER_MELEE : NDb::DAMAGEFILTER_RANGED;
  if ( (filterFlags & toCheck) == 0 )
    return false;

  // Material/energy filter
  if ( damageType == NDb::APPLICATORDAMAGETYPE_PURE )
    toCheck = NDb::DAMAGEFILTER_PURE;
  else
    toCheck = ( damageType == NDb::APPLICATORDAMAGETYPE_MATERIAL ) ? NDb::DAMAGEFILTER_MATERIAL : NDb::DAMAGEFILTER_ENERGY;
  if ( (filterFlags & toCheck) == 0 )
    return false;

  return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char* PFBaseApplicator::ErrorStr(const char *str) const
{
	return NStr::StrFmt("%s from file %s dbid %s: %s", GetDBBase()->GetObjectTypeName(), 
		                  GetDBBase()->GetDBID().GetFileName().c_str(), GetDBBase()->GetDBID().GetId().c_str(), str);
}

NDb::Ptr<NDb::BaseApplicator> const& PFBaseApplicator::GetDBBase() const
{
  if ( pDBAppl->GetObjectTypeID() == NDb::ApplicatorNameOverrider::typeId )
    return static_cast<NDb::ApplicatorNameOverrider const*>(pDBAppl.GetPtr())->applicator;

  return pDBAppl;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
string const& PFBaseApplicator::GetApplicatorName() const
{
  if ( pDBAppl->GetObjectTypeID() == NDb::ApplicatorNameOverrider::typeId )
    return pDBAppl->formulaName;

  return GetDBBase()->formulaName;
}

float PFBaseApplicator::GetTerrainPart(int faction) const
{
  return GetWorld()->GetNatureMap()->GetNaturePercent((NDb::EFaction)faction);
}

int PFBaseApplicator::GetTerrianTypeUnderCursor() const
{
  CVec3 posOnTerra = NGameX::AdventureScreen::Instance()->GetCurrentCursorPosOnTerrain();
  return GetWorld()->GetNatureMap()->GetNatureInPoint(posOnTerra.X(), posOnTerra.Y());
}

int PFBaseApplicator::GetNatureTypeInPos(CVec2 pos) const
{
  return GetWorld()->GetNatureMap()->GetNatureInPoint(pos.x, pos.y);
}

bool PFBaseApplicator::CheckUpgradePerCastPerTarget() const
{
  const CObj<PFAbilityData>& upgrader = GetUpgraderAbilityData();

  // TODO: cache
  if (upgrader)
  {
    const NDb::Ability* dbUpgrader = upgrader->GetDBDesc();

    for (int i = 0, count = dbUpgrader->passiveApplicators.size(); i < count; ++i)
    {
      const NDb::Ptr<NDb::BaseApplicator>& dbUpgraderPassiveApplicator = dbUpgrader->passiveApplicators[i];

      if (dbUpgraderPassiveApplicator->GetObjectTypeID() != NDb::AbilityUpgradeApplicator::typeId)
        continue;

      const NDb::AbilityUpgradeApplicator* const dbAbilityUpgrade = static_cast<const NDb::AbilityUpgradeApplicator*>(dbUpgraderPassiveApplicator.GetPtr());

      if (dbAbilityUpgrade->flags & NDb::ABILITYUPGRADEMODE_APPLYONCEPERCASTPERTARGET)
      {
        NI_ASSERT(!!pAbility && !!pAbility->GetData(), "Invalid ability!");
        NI_ASSERT(pAbility->GetData()->GetAbilityTypeId() == NDb::ABILITYTYPEID_TALENT, "Applicator's ability is not a talent!");

        const PFTalent* const talent = static_cast<const PFTalent*>(pAbility->GetData());

        const int talentObjectId = talent->GetObjectId();
        const int talentLastUseStep = talent->GetLastUseStep();

        const ValueWithModifiers* const vwm = GetReceiver()->SearchVariableVWM(GetTalentLastUseStepVariableName(talentObjectId));

        if (vwm)
          return vwm->GetBaseValue() < talentLastUseStep;
      }
    }
  }

  return true;
}

int PFBaseApplicator::GetActivatedWithinKit() const
{
  return GetAbility() ? GetAbility()->GetData()->GetActivatedWithinKit() : 0;
}

int PFBaseApplicator::GetTalentsWithinKit() const
{
  return GetAbility() ? GetAbility()->GetData()->GetTalentsWithinKit() : 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float PFBaseApplicator::GetStatusDispellPriority( const IUnitFormulaPars* pUnitToCheck, bool returnDuration ) const
{
  vector<PFBaseApplicator*> statuses;
  int factionFlags = GetAbilityOwner()->GetOppositeFactionFlags();

  const PFBaseUnit* pUnit = dynamic_cast<const PFBaseUnit*>(pUnitToCheck);
  NI_VERIFY( pUnit, "Invalid object to get status dispell priority", return -1.0f );

  PFApplDispell::SearchStatus2Dispell( vector<const PFBaseUnit*>(1, pUnit), factionFlags, GetTarget(), statuses );

  if ( statuses.empty() )
    return -1.0f;

  if ( !returnDuration )
  {
    return (float)(static_cast<const PFApplStatus*>(statuses[0])->GetDB().dispellPriority);
  }

  float maxDuration = 0.0f;
  for ( int i = 0, count = statuses.size(); i < count; i++ )
  {
    const PFApplStatus* pStatus = static_cast<const PFApplStatus*>(statuses[i]);
    const float lifetime = pStatus->GetLifetime();
    if ( lifetime == -1.0f )
    {
      maxDuration = 1.0f;
      break;
    }
    else if ( lifetime < 0.1f  ) // Less than step
    {
      continue;
    }
    float duration = pStatus->GetDuration() / lifetime;
    if ( duration > maxDuration )
      maxDuration = duration;
  }

  return maxDuration;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFBaseApplicator::CheckEffectEnabled( const PF_Core::BasicEffect &effect )
{
  bool bEnable = true;

  if(effect.GetDBDesc() && !effect.GetDBDesc()->enableCondition.IsEmpty())
  {
    bEnable = effect.GetDBDesc()->enableCondition->condition(pOwner, pReceiver,this, bEnable);
  }

  return bEnable;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseApplicator::OnAfterReset()
{
  PFWorldObjectBase::OnAfterReset();

  if (IsEnabled())
  {
    if (NeedEnableAfterReset())
      Enable();
  }
  else
  {
    if (NeedDisableAfterReset())
      Disable();
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ActivateApplicator(CObj<PFBaseApplicator> app, CObj<PFAbilityInstance> const& pAbility)
{
  NI_ASSERT(app,      "Applicator should be valid");
  NI_ASSERT(pAbility, "AbilityData should be valid");

	// Make applicator target
  Target target;
	app->MakeApplicationTarget(target);

  TileMap * tileMap = app->GetWorld()->GetTileMap();
  CVec2 pos = app->GetTargetPos();
  SVector position = tileMap->GetTile(pos);
  if ( tileMap->IsPointOutsideMap( position.x, position.y ) )
    return false;

	if (!target.IsUnit())
  {
    bool done = app->Start();
    NI_ASSERT(done, "Position-targeted applicator must complete its work on Start.");
    app->Stop();
		return true;
  }
	else
	{
    if (pAbility->GetData()->IsTargetValid(target, app->CanBeAppliedOnDead()))
		{
			return target.GetUnit()->OnApplicatorApply(app);
		}
	}

	return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CreateAndActivateApplicators(const vector<NDb::Ptr<NDb::BaseApplicator>> &applicators, const CObj<PFAbilityInstance> &pAbility, 
																	Target const &target, CPtr<PFBaseApplicator> pParent)
{
	PFApplCreatePars cp(pAbility, target, pParent);

	const int count = applicators.size();
	for (int i = 0; i < count; i++)
	{
		cp.pDBAppl = applicators[i];
    NI_VERIFY(cp.pDBAppl, "Void applicator in list!", continue; );
		CObj<PFBaseApplicator> pApplicator(CreateApplicator(cp));
		ActivateApplicator(pApplicator, pAbility);
		if( IsValid(pParent) )
		{
			pParent->OnChildApplicatorCreated(pApplicator);
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MemorizeApplicator(CObj<PFBaseApplicator> app)
{
  app->RemoveFromRingsSafe();
#ifdef LOG_APPLICATORS_LIFECYCLE
	PFBaseApplicator *pAppl = app.GetPtr();
	DebugTrace("APPL %s (%08X) memorize", pAppl->GetObjectTypeName(), pAppl);
#endif

  CPtr<PFBaseUnit> pSender   = app->GetAbilityOwner();
  CPtr<PFBaseUnit> pReceiver = app->GetReceiver();

  PFWorld* pWorld = IsValid(pSender) ? pSender->GetWorld() : IsValid(pReceiver) ? pReceiver->GetWorld() : NULL;
  
  if ( pWorld )
    app->SetMarkerTime( pWorld->GetTimeElapsed() );

  if (IsValid(pReceiver))
  {
#ifdef LOG_APPLICATORS_LIFECYCLE
		DebugTrace("... RegisterAppliedApplicator in %s %X", pReceiver->GetObjectTypeName(), pReceiver.GetPtr());
#endif
    pReceiver->RegisterAppliedApplicatorToHistory(app);
  }

	if (IsValid(pSender))
  {
#ifdef LOG_APPLICATORS_LIFECYCLE
		DebugTrace("... RegisterSentApplicator in %s %X", pSender->GetObjectTypeName(), pSender.GetPtr());
#endif
    pSender->RegisterSentApplicatorToHistory(app);
  }
}

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
REGISTER_WORLD_OBJECT_NM(PFBaseApplicator, NWorld);
