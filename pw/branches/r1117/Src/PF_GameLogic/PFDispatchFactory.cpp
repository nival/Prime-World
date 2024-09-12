#include "stdafx.h"

#include "PFDispatchFactory.h"

#include "PFBaseUnit.h"
#include "PFUniTarget.h"
#include "PFWorld.h"
#include "PFDispatchStrike1.h"
#include "PFApplicator.h"
#include "PFApplBuff.h"
#include "PFApplSummon.h"
#include "PFApplInstant.h"
#include "PFApplMod.h"
#include "PFApplHelper.h"
#include "PFApplAura.h"
#include "PFApplMove.h"
#include "PFApplSpecial.h"
#include "PFApplChainLightning.h"
#include "PFLogicDebug.h"
#include "PFAbilityInstance.h"
#include "PFAbilityData.h"

namespace NWorld
{

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CObj<PFBaseApplicator> CreateApplicator(PFApplCreatePars const &cp)
{
	CObj<PFBaseApplicator> pAppl(cp.pDBAppl->Create(cp));
	if (pAppl)
	{
		if (!pAppl->Init())
			pAppl = 0; // Kill applicator
	}
	return pAppl;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PFDispatch *CreateDispatch(CObj<PFAbilityInstance> const &pAbility,
                           CPtr<PFBaseApplicator> const& pParent,
                           Target const &source, 
                           Target const &target,
                           NDb::Ptr<NDb::Spell> const& pSpell,
                           int flagsForApplicators,
                           bool start, 
                           float startDelay)
{
  LogAbilityUsage(pAbility);

	NI_DATA_VERIFY(pSpell->dispatch, NStr::StrFmt("Spell %s should have dispatch!", NDb::GetFormattedDbId(pSpell->GetDBID())), return 0;)
	NI_ASSERT(IsValid(pAbility) && IsValid(pAbility->GetData()), "Ability is not valid");

  const CPtr<PFBaseUnit> &pSender = pAbility->GetData()->GetOwner();

  PFDispatchCreateParams dcp(pAbility, target, source, flagsForApplicators, pParent);
  dcp.pDBDispatch      = pSpell->dispatch;
  dcp.pSender          = pSender;
  dcp.pWorld           = pSender->GetWorld();
  dcp.clientStartDelay = startDelay;

	PFDispatch *pD = pSpell->dispatch ? pSpell->dispatch->Create(dcp) : new PFDispatchImmediate(dcp);
	NI_DATA_VERIFY(pD, "Dispatch has invalid type and couldn't be created", return 0;)

  pD->AddApplicators(pSpell->applicators);
  if ( (pSpell->dispatch->flags & NDb::DISPATCHFLAGS_UPGRADABLE) != 0 )
    pD->UpgradeBeforeApply();

  if( start )
	  pD->Start();

	return pD;
}

}
