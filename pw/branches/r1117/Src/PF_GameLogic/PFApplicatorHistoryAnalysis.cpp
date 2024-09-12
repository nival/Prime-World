#include "stdafx.h"

#include "PFApplInstant.h"
#include "PFApplicatorHistoryAnalysis.h"

namespace NWorld
{

namespace
{

struct DamageCounter_
{
  DamageCounter_(PFAbilityInstance *ability): damageDealed(0.f), ability(ability) {}
  void operator()(CObj<PFBaseApplicator> &app)
  {
    PFApplDamage *ad = dynamic_cast<PFApplDamage *>(app.GetPtr());
    if (ad && ad->GetAbility() == ability)
    {
      damageDealed += ad->GetDamageDealed();
    }
  }
  float damageDealed;
  PFAbilityInstance *ability;
};

}

float GetDamageDealed(CPtr<PFBaseUnit> unit, float deltaTime, PFAbilityInstance *ability)
{
  DamageCounter_ c(ability);
  unit->ForAllSentApplicatorsInHistoryLess(c, deltaTime);
  return c.damageDealed;
}

}