#include "stdafx.h"

#include "PFUniTarget.h"
#include "PFApplInstant.h"
#include "PFTargetSelector.h"
#include "PFBaseUnit.h"
#include "PFAbilityData.h"
#include "PFCastLimitations.h"

namespace NWorld
{

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const PFAbilityData* CheckTargetLimitation(NDb::TargetCastLimitation const &dbLimit, CastLimitationsCheckParams const &cp)
{
  CObj<PFTargetSelector> pTS = dbLimit.targetSelector->Create(0);

  struct CalcTargets : public ITargetAction
  {
    CalcTargets() : count(0) {}
    int count;
    virtual void operator()(const Target &target) { count++; }
  } f;

  PFTargetSelector::RequestParams rp(cp.pAbility->GetOwner(), cp.pAbility, *cp.pTarget);
  pTS->EnumerateTargets(f, rp);

  return f.count > 0 ? cp.pAbility : 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const PFAbilityData* CheckConditionLimitation(NDb::ConditionCastLimitation const &dbLimit, CastLimitationsCheckParams const &cp)
{
	PFLogicObject *pObject = cp.pTarget->IsPosition() ? cp.pAbility->GetOwner().GetPtr() : cp.pTarget->GetObject();

	bool res = dbLimit.condition(cp.pAbility->GetOwner(), pObject, cp.pAbility, true);

	return res ? cp.pAbility : 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const PFAbilityData* CheckDispellLimitation(NDb::DispellCastLimitation const &dbLimit, CastLimitationsCheckParams const &cp)
{
  vector<PFBaseApplicator*> statuses;
  PFBaseUnit* pAbilityOwner = cp.pAbility->GetOwner();
  int count = PFApplDispell::SearchStatus2Dispell( vector<const PFBaseUnit*>( 1, pAbilityOwner ), 
                                                  cp.pAbility->GetOwner()->GetOppositeFactionFlags(), Target( pAbilityOwner ), statuses );
  return count > 0 ? cp.pAbility : 0;
}

const PFAbilityData* CheckPositionLimitation( NDb::PositionCastLimitation const& dbLimit, CastLimitationsCheckParams const& cp )
{
  const CVec3 pos = cp.pTarget->IsPosition() ? cp.pTarget->GetPosition() : cp.pTarget->GetUnit()->GetPosition() ;
  const PFPositionObject* pObject = new PFPositionObject(pos);

  bool allow = dbLimit.condition(cp.pAbility->GetOwner(), pObject, cp.pAbility, false);
  delete pObject;

  return allow ? cp.pAbility : 0;
}
}
