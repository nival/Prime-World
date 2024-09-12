#include "stdafx.h"
#include "PFApplAura.h"
#include "PFBaseUnit.h"
#include "PFDebug.h"
#include "PFWorld.h"
#include "PFHero.h"
#include "PFDispatchFactory.h"
#include "PFTargetSelector.h"
#include "PFAIWorld.h"
#include "PFClientBaseUnit.h"

namespace
{
  static bool g_showAuraRange = false;
}

namespace NWorld
{

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFApplAura::Start()
{
	if (PFApplBuff::Start())
		return true;

#ifndef _SHIPPING
  if (g_showAuraRange)
    NDebug::ShowAuraApplicatorRange(this);
#endif

	if (GetDB().targetSelector)
	{
		pTargetSelector = GetDB().targetSelector->Create(GetWorld());
	}

	// 
	activeBuffer = 0;
	// Reserve memory to avoid reallocs
	appliedApplicator1.reserve(32);
	appliedApplicator2.reserve(32);

	return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFApplAura::ProcessUnit(const Target &target)
{
	AffectedUnits &outVec = GetAffectedUnit(1-activeBuffer);
	AffectedUnits &vec = GetAffectedUnit(activeBuffer);
	for (AffectedUnits::iterator it = vec.begin(); it != vec.end(); ++it)
	{
		if ((*it) == target.GetUnit())
		{
			// Unit is already present in list
			outVec.push_back(target.GetUnit());
			*it = 0; // Remove from vector
			return;
		}
	}

	// Unit not found. It's a new one. Apply applicators to it.
	outVec.push_back(target.GetUnit());
	CreateAndActivateApplicators(GetDB().applicators, GetAbility(), target, this);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFApplAura::RemoveApplicatorsFromUnits()
{
	// Process the rest. Remove applicators from units that are out-of-range
	AffectedUnits &vec = GetAffectedUnit(activeBuffer);
	for (AffectedUnits::const_iterator it = vec.begin(); it != vec.end(); ++it)
	{
		if (IsValid(*it))
		{
			RemoveChildrenApplicatorsFromUnit(it->GetPtr());
		}
	}
  vec.clear();
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFApplAura::Enable()
{
  if ( IsUnitValid( pOwner ) && pOwner->ClientObject() )
  {
    NDb::EAuraVisualType type = GetDB().type;
    if ( type != NDb::AURAVISUALTYPE_NONE )
    {
      pOwner->ClientObject()->OnSelfAuraChange( type == NDb::AURAVISUALTYPE_ALLY, true );
    }
  }
  return PFApplBuff::Enable();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFApplAura::Reset()
{
  PFApplBuff::Reset();

  if ( IsEnabled() && IsValid( pOwner ) && pOwner->ClientObject() )
  {
    NDb::EAuraVisualType type = GetDB().type;
    if ( type != NDb::AURAVISUALTYPE_NONE )
    {
      pOwner->ClientObject()->OnSelfAuraChange( type == NDb::AURAVISUALTYPE_ALLY, true );
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFApplAura::Disable()
{
	RemoveApplicatorsFromUnits();
  PFApplBuff::Disable();
  if ( IsValid( pOwner ) && pOwner->ClientObject() )
  {
    NDb::EAuraVisualType type = GetDB().type;
    if ( type != NDb::AURAVISUALTYPE_NONE )
    {
      pOwner->ClientObject()->OnSelfAuraChange( type == NDb::AURAVISUALTYPE_ALLY, false );
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFApplAura::Step(float dtInSeconds)
{
  NI_PROFILE_FUNCTION;
    
  if (PFApplBuff::Step(dtInSeconds))
    return true;

  if (!IsEnabled())
    return false;

  float auraRange = RetrieveParam(GetDB().range, 0.0f);
  
  // Select factions
  int factionFlags = MakeSpellTargetFactionFlags(GetDB().targets);

	CVec3 checkPos = AcquireApplicationPosition();

	// Process selected units
	if (pTargetSelector)
	{
		// Make target and fill position
		Target targ;
		if (IsValid(pReceiver))
			targ.SetUnit(pReceiver);
		else
			targ.SetPosition(checkPos);

		struct Func : public ITargetAction, public NonCopyable
		{
			PFApplAura *pAura;
			float      range;
			CVec2      checkPos;

			Func(PFApplAura *pThis, CVec2 const &pos, float r) 
				: pAura(pThis), checkPos(pos), range(r) 
			{}

			virtual void operator()(const Target &target)
			{
				NI_DATA_VERIFY(target.IsUnit(), "Aura target selector should return units only", return; );
				if ( (range == 0.0 || target.GetUnit()->IsInRange( checkPos, range )) && !target.GetUnit()->IsInvalidAbilityTarget() )
					pAura->ProcessUnit(target);
			}
		} f(this, checkPos.AsVec2D(), auraRange);

		PFTargetSelector::RequestParams pars(*this, targ);
		pTargetSelector->EnumerateTargets(f, pars);
	}
	else
	{
    struct Func : NonCopyable
		{
			PFApplAura *pAura;
			float      range;
			CVec2      checkPos;

			Func(PFApplAura *pThis, CVec2 const &pos, float r) 
				: pAura(pThis), checkPos(pos), range(r) 
			{}

			void operator()(PFBaseUnit &unit)
			{
        if (IsUnitValid(&unit) && ( range == 0.0 || unit.IsInRange( checkPos, range ) ) && !unit.IsInvalidAbilityTarget())
          pAura->ProcessUnit(Target(CPtr<PFBaseUnit>(&unit)));
			}
		} f(this, checkPos.AsVec2D(), auraRange);

		PFAIWorld const *pAIWorld = GetAbilityOwner()->GetWorld()->GetAIWorld();
		pAIWorld->ForAllUnitsInRange(checkPos, auraRange + pAIWorld->GetMaxObjectSize() * 0.5f, f, 
			                           UnitMaskingPredicate(factionFlags, GetDB().targets, pOwner));
	}

	RemoveApplicatorsFromUnits();

	// Swap active buffer
	activeBuffer = 1 - activeBuffer;

  return false;
}

PFApplAura::AffectedUnits& PFApplAura::GetAffectedUnit( int idx )
{
	if ( idx == 0 )
		return appliedApplicator1;
	return appliedApplicator2;
}

// ugly but true!
PFApplAura::AffectedUnits const& PFApplAura::GetAffectedUnit( int idx ) const
{
	if ( idx == 0 )
		return appliedApplicator1;
	return appliedApplicator2;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float PFApplAura::GetVariable(const char* sVariableName) const
{
  if ( strcmp(sVariableName, "targetsCount") == 0 )
    return GetAffectedUnit( activeBuffer ).size();

  return PFBaseApplicator::GetVariable(sVariableName);
}

}

REGISTER_DEV_VAR("show_aura_range", g_showAuraRange, STORAGE_NONE);

REGISTER_WORLD_OBJECT_NM(PFApplAura, NWorld);