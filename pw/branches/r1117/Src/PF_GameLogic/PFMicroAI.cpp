#include "stdafx.h"
#include "PFAbilityData.h"
#include "PFBaseUnit.h"
#include "PFAIWorld.h"

#include "PFMicroAI.h"
#include "PFTargetSelector.h"
#include "TargetSelectorHelper.hpp"

namespace
{
  static bool g_dump_micro_ai_ts = false;

}
namespace NWorld
{

///////////////////////////////////////////////////////////////////////////////////////////////////
// Service functions to find units of desired type
///////////////////////////////////////////////////////////////////////////////////////////////////

template<class UnitType>
struct UnitCollector : NonCopyable
{
	UnitCollector(vector<UnitType*> &_objects)
	: objects(_objects)
	{}

	void operator()(PFLogicObject &baseUnit)
	{
		CDynamicCast<UnitType> unit = &baseUnit;
		if (unit)															// required type
			objects.push_back(unit);
	}

	vector<UnitType*> &objects;
};

static bool FindUnits(PFWorld* pWorld, const CVec3& pos, float range, int factionFlags, int targetType, vector<PFBaseUnit*>& objects)
{
	UnitCollector<PFBaseUnit> collector(objects);
	pWorld->GetAIWorld()->ForAllUnitsInRange(pos, range, collector, UnitMaskingPredicate(factionFlags, targetType));
	return objects.size() > 0;
}

static bool FindBuildings(PFWorld* pWorld, const CVec3& pos, float range, int factionFlags, int targetType, vector<PFLogicObject*>& objects)
{
	UnitCollector<PFLogicObject> collector(objects);
	pWorld->GetAIWorld()->ForAllObjectsInRange(pos, range, collector, UnitMaskingPredicate(factionFlags, targetType));
	return objects.size() > 0;
}


///////////////////////////////////////////////////////////////////////////////////////////////////
// PFBasicMicroAI
///////////////////////////////////////////////////////////////////////////////////////////////////

bool PFBasicMicroAI::CheckConditions() const
{
  NI_VERIFY(IsValid(pAbility), "Invalid ability", return false);

  // check usability of this ability
  if (!pAbility->CanBeUsed())
    return false;

  if (pAbility->GetType() == NDb::ABILITYTYPE_PASSIVE || pAbility->GetType() == NDb::ABILITYTYPE_AUTOCASTABLE || pAbility->GetType() == NDb::ABILITYTYPE_SIMPLE )
    return false;

  CPtr<PFBaseUnit> const & pUnit = pAbility->GetOwner();
  NI_VERIFY(IsValid(pUnit), "Invalid ability owner", return false);
  NI_VERIFY(IsValid(pUnit->GetBehaviour()), "Invalid ability owner behaviour", return false);

  if ( GetDB().castWhenIdle && !pUnit->GetBehaviour()->IsInDefaultState() )
    return false;

  // check activation condition
  if (!GetDB().condition(pUnit, pUnit, pAbility, false))
    return false;

  // check usability by unit
  int abilityId = pAbility->GetAbilityTypeId() - NDb::ABILITYTYPEID_ABILITY0;
  if (abilityId >= 1 && abilityId < NDb::KnownEnum<NDb::EAbility>::sizeOf)
  {
    PFCreature* pCreature = dynamic_cast<PFCreature*>(pUnit.GetPtr());
    if (pCreature && (!pCreature->IsAbilityAvailable(abilityId) || !pCreature->CanUseAbility(abilityId) || pCreature->IsAbilityInProgress(abilityId)))
      return false;
  }
  
  return true;
}

bool PFBasicMicroAI::GetTargetImpl(Target& target, const ITargetCondition* const condition) const
{
	if (!CheckConditions())
    return false;
  
  // get ability ownner
  NDb::ESpellTarget targetType = pAbility->GetTargetType();

  // find target for this ability

  PFBaseUnit *pUnit = pAbility->GetOwner();
  if (!pUnit)
    return false;

  // type 0
	if (targetType == 0 || targetType == NDb::SPELLTARGET_SELF)
	{
		//vector<PFBaseUnit*> objects;
		//if (!FindUnits(pUnit->GetWorld(), pUnit->GetPosition(), pUnit->GetAttackRange() * 1.5f /*pUnit->GetVisibilityRange()*/,
		//		pUnit->GetOppositeFactionFlags(), NDb::SPELLTARGET_ALL, objects))
		//{
		//	return false;		// some heuristic: cast these spells only when enemy units are available
		//}
		target = Target( pAbility->GetOwner() );
		return CheckTargetCondition(target, condition, pAbility);
	}

  if ((targetType & (NDb::SPELLTARGET_ENEMY | NDb::SPELLTARGET_ALLY)) != 0)
	{
		float useRange = pAbility->GetUseRange();
		// get faction
		int factionFlags = 0;
		if (targetType & NDb::SPELLTARGET_ALLY)
			factionFlags |= 1 << pUnit->GetFaction();
		if (targetType & NDb::SPELLTARGET_ENEMY)
			factionFlags |= pUnit->GetOppositeFactionFlags();
		// allied units or enemy units
		NI_ASSERT(useRange > 0.0f, "Bad ability range");

    const unsigned unitTargetTypeMask =
      NDb::SPELLTARGET_HEROMALE |
      NDb::SPELLTARGET_HEROFEMALE |
      NDb::SPELLTARGET_CREEP |
      NDb::SPELLTARGET_SIEGECREEP |
      NDb::SPELLTARGET_ALLNEUTRALS |
      NDb::SPELLTARGET_FACTIONCHAMPION;

		if ((targetType & unitTargetTypeMask) != 0)
		{
      vector<PFBaseUnit*> objects;

			if (FindUnits(pUnit->GetWorld(), pUnit->GetPosition(), useRange, factionFlags, targetType, objects))
			{
				CPtr<PFBaseUnit> bestUnit = NULL;
				for (int i = 0; i < objects.size(); i++)
				{
					CPtr<PFBaseUnit> obj(objects[i]);
					if (!IsUnitValid(obj))
						continue;
          {
            const Target target(objects[i]);
            if (!CheckTargetCondition(target, condition, pAbility))
              continue;
          }
					bestUnit = obj;
#if USE_NEW_AI
					if (obj->IsHero() && bestUnit && !bestUnit->IsHero() && (targetType & (NDb::SPELLTARGET_HEROMALE | NDb::SPELLTARGET_HEROFEMALE)) )
						break;					// found a hero
#else
					break;
#endif
				}
				if (bestUnit.GetPtr())
				{
					target = Target(bestUnit);
					return true;
				}
				return false;
			}
		}
		else
		{
      const unsigned buildingTargetTypeMask =
        NDb::SPELLTARGET_TOWER |
        NDb::SPELLTARGET_MAINBUILDING |
        NDb::SPELLTARGET_BUILDING |
        NDb::SPELLTARGET_TREE;

			NI_ASSERT((targetType & buildingTargetTypeMask) != 0, "Unknown target type!");

      vector<PFLogicObject*> objects;

			if (FindBuildings(pUnit->GetWorld(), pUnit->GetPosition(), useRange, factionFlags, targetType, objects))
			{
				for (int i = 0; i < objects.size(); i++)
				{
					CPtr<PFLogicObject> obj(objects[i]);
					if (IsUnitValid(obj))
					{
						target = Target(obj);
            if (CheckTargetCondition(target, condition, pAbility))
						  return true;
					}
				}
				return false;
			}
		}
		return false; // target was not found
	}

	return false; // unknown type
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// TargetSelectorMicroAI
///////////////////////////////////////////////////////////////////////////////////////////////////
PFTargetSelectorMicroAI::PFTargetSelectorMicroAI(CreateParams const &cp) : Base(cp)
{
  if (IsValid(GetDB().targetSelector))
	{
    pTargetSelector = dynamic_cast<PFSingleTargetSelector*>( GetDB().targetSelector->Create( GetWorld() ) );
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////

bool PFTargetSelectorMicroAI::GetTargetImpl(Target& target, const ITargetCondition* const condition) const
{
  if (!CheckConditions())
    return false;
  if (!IsValid(pTargetSelector))
    return PFBasicMicroAI::GetTarget(target);

  NI_VERIFY(IsValid(pAbility), "Invalid ability", return false; );

  CPtr<PFBaseUnit> const& pUnit = pAbility->GetOwner();
  NI_VERIFY( IsValid(pUnit), "Unit mast be valid!", return false; );

  PFTargetSelector::RequestParams rp(pAbility->GetOwner(), pAbility, Target(pUnit), condition );
  bool hasTarget = pTargetSelector->FindTarget(rp, target);

  if ( hasTarget && g_dump_micro_ai_ts )
  {
    PFTargetSelector::s_DumpSelectors = true;
    Target t;
    pTargetSelector->FindTarget(rp, t);
    PFTargetSelector::s_DumpSelectors = false;
  }

  return hasTarget;
}


///////////////////////////////////////////////////////////////////////////////////////////////////
// TriggerMicroAI
///////////////////////////////////////////////////////////////////////////////////////////////////
PFMultipleTargetSelectorMicroAI::PFMultipleTargetSelectorMicroAI(CreateParams const &cp) : Base(cp)
{
  if (IsValid(GetDB().targetSelector))
	{
    pTargetSelector = dynamic_cast<PFMultipleTargetSelector*>( GetDB().targetSelector->Create( GetWorld() ) );
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////

bool PFMultipleTargetSelectorMicroAI::GetTargetImpl(Target& target, const ITargetCondition* const condition) const
{
  if (!CheckConditions())
    return false;
  if (!IsValid(pTargetSelector))
    return PFBasicMicroAI::GetTarget(target);

  NI_VERIFY(IsValid(pAbility), "Invalid ability", return false; );

  CPtr<PFBaseUnit> const& pUnit = pAbility->GetOwner();
  NI_VERIFY( IsValid(pUnit), "Unit mast be valid!", return false; );

  struct Enumerator : public ITargetAction, public NonCopyable
  {
    Enumerator(PFBaseUnit const *pOwner, ConstPtr<PFAbilityData> const &pAbility, ExecutableBoolString const &cond, float targetWeight, const NDb::UnitTargetingParameters &unitPars)
      : pOwner(pOwner), pAbility(pAbility), cond(cond), count(0), targetWeight(targetWeight), unitPars(unitPars) {}

    virtual void operator()(const Target &target)
    {
      if ( !target.IsUnit() )
        return;

      CPtr<PFBaseUnit> const& pUnit = target.GetUnit();

      if ( cond(pOwner, pUnit, pAbility) )
      {
        if ( !pOwner->CanSelectTarget(pUnit, true) ) // CanSelectTarget is autoattack specific; maybe more loose check needed, also see PFWeightTargetSelector::FindTarget
          return;

        float weight = pOwner->GetTargetWeight( pUnit, unitPars, NULL );
        if ( weight > targetWeight )
          ++count;
      }
    }
    int GetCount() const { return count; }

  protected:
    PFBaseUnit const              *pOwner;
    ConstPtr<PFAbilityData> const &pAbility;
    ExecutableBoolString const    &cond;
    int   count;
    float targetWeight;
    const NDb::UnitTargetingParameters &unitPars;

  } enumerator( pUnit, pAbility, GetDB().unitFilter, GetDB().minTargetWeight, pUnit->GetTargetingParams() );

  PFTargetSelector::RequestParams rp(pUnit, pAbility, Target(pUnit), condition );
  pTargetSelector->EnumerateTargets(enumerator, rp);

  if ( GetDB().minTargetCount == 0 ? enumerator.GetCount() == 0 : enumerator.GetCount() >= GetDB().minTargetCount)
  {
    target.SetUnit( pAbility->GetOwner() );
    return true;
  }
  return false;
}


} // name space

REGISTER_DEV_VAR("dump_micro_ai_ts", g_dump_micro_ai_ts, STORAGE_NONE);


REGISTER_WORLD_OBJECT_NM(PFMicroAI, NWorld)
REGISTER_WORLD_OBJECT_NM(PFBasicMicroAI, NWorld)
REGISTER_WORLD_OBJECT_NM(PFTargetSelectorMicroAI, NWorld)
REGISTER_WORLD_OBJECT_NM(PFMultipleTargetSelectorMicroAI, NWorld)
