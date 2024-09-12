#pragma once

#include "PFBaseUnit.h"

namespace NWorld
{

bool CountAffections(CPtr<PFBaseUnit> unit, float deltaTime, int *numByType, int maxNum);
void GetAffectors(CPtr<PFBaseUnit> unit, vector<CPtr<PFBaseUnit> > &affectors, float deltaTime);
float GetDamageDealed(CPtr<PFBaseUnit> unit, float deltaTime, PFAbilityInstance *ability);

template <typename F> void EnumerateAppliedApplicators(CPtr<PFBaseUnit> unit, float deltaTime, F &f)
{
  unit->ForAllAppliedApplicators(f);
  unit->ForAllAppliedApplicatorsInHistoryLess(f, deltaTime);
}

}