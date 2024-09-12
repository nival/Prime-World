#include "stdafx.h"
#include "PFApplicator.h"
#include "PFTargetSelector.h"
#include "PFBaseUnit.h"
#include "PFDispatchFactory.h"
#include "PFApplUtils.h"
#include "PFTriggerApplicator.h"

namespace NWorld
{

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SendSpellToSingleTarget(PFBaseApplicator *pAppl, NDb::Ptr<NDb::Spell> pSpell, Target &targ, bool justCount)
{
	if (!targ.IsValid( pAppl->GetAbility()->GetData()->GetDBDesc()->flags & NDb::ABILITYFLAGS_APPLYTODEAD ))
		return 0;

	Target const source( pAppl->GetAbilityOwner() );
  
  // Has not target selector
	if (!justCount)
		CreateDispatch(pAppl->GetAbility(), CPtr<PFBaseApplicator>(pAppl), source, targ, pSpell);

	return 1;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SendSpell2Targets(PFBaseApplicator *pAppl, NDb::Ptr<NDb::Spell> pSpell, PFTargetSelector* pSelector, bool justCount)
{
	if (!pSpell && !justCount) // No spell to send
		return 0;

	// Make target and fill position
	Target targ;
  pAppl->MakeApplicationTarget(targ);

	if (pSelector)
	{ 
		// Has target selector
		struct Func : public ITargetAction, NonCopyable
		{
			CPtr<PFBaseApplicator> pAppl;
			NDb::Ptr<NDb::Spell>   pSpell;
			Target const&          source;
			int                    spellsSentCount;
			bool                   justCount;
      bool                   checkVulnerability;

			Func(CPtr<PFBaseApplicator> pAppl_, NDb::Ptr<NDb::Spell> pSpell_, Target const &source_, bool justCount_, bool checkVulnerability_) 
				: pAppl(pAppl_), pSpell(pSpell_), source(source_), spellsSentCount(0), justCount(justCount_), checkVulnerability(checkVulnerability_)
			{}

			virtual void operator()(const Target &target)
			{
        if ( !target.IsValid(true) )
          return;

				if ( checkVulnerability && target.IsUnit())
				{
					PFBaseUnit *pUnit = target.GetUnit().GetPtr();
					if ( pUnit->GetFaction() != pAppl->GetAbilityOwner()->GetFaction() && !pUnit->IsVulnerable() )
						return;
				}

				if (!justCount && IsValid(pSpell))
				{
					CreateDispatch(pAppl->GetAbility(), pAppl, source, target, pSpell);
				}

				++spellsSentCount;
			}
    } f(CPtr<PFBaseApplicator>(pAppl), pSpell, targ, justCount, !pAppl->GetAbility()->GetData()->IsInteractionAbility() );

		PFTargetSelector::RequestParams pars(*pAppl, targ);
		pSelector->EnumerateTargets(f, pars);
		return f.spellsSentCount;
	}
	else
	{
    return SendSpellToSingleTarget( pAppl, pSpell, targ, justCount );
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SendSpell2Targets(PFBaseApplicator *pAppl, NDb::Ptr<NDb::Spell> pSpell, NDb::Ptr<NDb::TargetSelector> pSelector, bool justCount)
{
	CObj<PFTargetSelector> pSel;
	if (pSelector)
	{
		pSel = pSelector->Create( pAppl->GetWorld() );
	}
	return SendSpell2Targets(pAppl, pSpell, pSel, justCount);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool IsApplicatorInList( const NDb::BaseApplicator* dbApplicator, const NDb::ApplicatorsList* pApplicatorsList, CompareType compareType /* = ByDBID */ )
{
  if ( !pApplicatorsList )
  {
    return false;
  }

  // Check applicators
  for ( vector<NDb::Ptr<NDb::BaseApplicator>>::const_iterator iAppl = pApplicatorsList->applicators.begin(), iEnd = pApplicatorsList->applicators.end(); iAppl != iEnd; iAppl++ )
  {
    switch ( compareType )
    {
    case ByTypeID:
      if ( (*iAppl) && ( (*iAppl)->GetObjectTypeID() == dbApplicator->GetObjectTypeID() ) )
      {
        return true;
      }
      break;
    case ByDBID:
      if ( (*iAppl) && ( (*iAppl)->GetDBID() == dbApplicator->GetDBID() ) )
      {
        return true;
      }
      break;
    }
  }

  // Check lists
  for ( vector<NDb::Ptr<NDb::ApplicatorsList>>::const_iterator iList = pApplicatorsList->applicatorLists.begin(), iEnd = pApplicatorsList->applicatorLists.end(); iList != iEnd; iList++ )
  {
    if ( (*iList) && IsApplicatorInList( dbApplicator, (*iList), compareType ) )
    {
      return true;
    }
  }

  return false;
}

}
