#pragma once

#include "PFApplicator.h"

namespace NWorld
{

int SendSpellToSingleTarget(PFBaseApplicator *pAppl, NDb::Ptr<NDb::Spell> pSpell, Target &targ, bool justCount = false );
int SendSpell2Targets(PFBaseApplicator *pAppl, NDb::Ptr<NDb::Spell> pSpell, NDb::Ptr<NDb::TargetSelector> pSelector, bool justCount = false);
int SendSpell2Targets(PFBaseApplicator *pAppl, NDb::Ptr<NDb::Spell> pSpell, PFTargetSelector* pSelector, bool justCount = false);

enum CompareType
{
  ByTypeID,
  ByDBID
};

bool IsApplicatorInList( const NDb::BaseApplicator* dbApplicator, const NDb::ApplicatorsList* pApplicatorsList, CompareType compareType = ByDBID );

}
