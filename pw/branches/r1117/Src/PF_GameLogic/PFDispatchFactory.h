#pragma once

namespace NWorld
{

class PFWorld;
class PFAbilityInstance;
class PFBaseApplicator;
class PFApplCreatePars;
class Target;
class PFDispatch;
class PFBaseUnit;

CObj<PFBaseApplicator> CreateApplicator(PFApplCreatePars const &cp);
PFDispatch *CreateDispatch(CObj<PFAbilityInstance> const &pAbility,
                           CPtr<PFBaseApplicator> const& pParent,
                           Target const &source, 
                           Target const &target,
                           NDb::Ptr<NDb::Spell> const& pSpell,
                           int flagsForApplicators = 0,
                           bool start = true, 
                           float startDelay = 0.0f );

}
