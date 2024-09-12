#include "stdafx.h"

#include "PFAbilityInstance.h"
#include "PFApplSpecial.h"
#include "PFApplicatorHistoryAnalysis.h"
#include "PFBaseUnit.h"
#include "PFBaseUnitStates.h"
#include "PFDispatch.h"
#include "PFDispatchFactory.h"
#include "PFLogicDebug.h"
#include "PFEaselPlayer.h"
#include "PFTargetSelector.h"
#include "PFTree.h"
#include "PFUIEvent.h"
#include "PFWorld.h"
#include "WarFog.h"
#include "PFWorldNatureMap.h"
#include "TileMap.h"
#include "UnitNameMap.h"
#include "PFClientBaseUnit.h"
#include "PFPickupable.h"
#include "PFMaleHero.h"
#include "HeroActions.h"
#include "../PF_Core/GhostEffect.h"
#include "SessionEventType.h"
#include "DayNightController.h"

#ifndef VISUAL_CUTTED
#include "AdventureScreen.h"
#include "PFClientApplicators.h"
#else
#include "../Game/pf/Audit/ClientStubs.h"
#endif

namespace NWorld
{

namespace
{
  float GetAverageHeroesLevel(PFWorld *pWorld, NDb::EFaction factionId)
  {
    struct GetAvgLevelFunc : public NonCopyable
    {
      int numHeroes;
      int levelSum;

      GetAvgLevelFunc() : numHeroes(0), levelSum(0) {}
      void operator()(PFLogicObject &unit) 
      {
        PFBaseMaleHero * hero = dynamic_cast<PFBaseMaleHero *>(&unit);
        if (hero)
        {
          ++numHeroes;
          levelSum += hero->GetNaftaLevel();
        }
      }

      float GetAvgLevel() const { return (numHeroes > 0) ? (float)levelSum / numHeroes : 1.f; }
    } f;

    pWorld->GetAIWorld()->ForAllHeroes(f, factionId);
    return f.GetAvgLevel();
  }
} // ns


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PFApplDropTree::PFApplDropTree(PFApplCreatePars const &cp)
: Base(cp)
{
}

bool PFApplDropTree::Start()
{
  if ( PFBaseApplicator::Start() )
  {
    return true;
  }

	// @BVS@TODO Should be an assert
	const Target& targ = GetTarget();
	NI_VERIFY( targ.IsObject() && IsValid( targ.GetObject() ) && ( targ.GetObject()->GetUnitType() == NDb::UNITTYPE_TREE ),
    "Target should be an tree!", return true );

  PFTree* pTree = dynamic_cast<PFTree*>( targ.GetObject().GetPtr() );
  NI_VERIFY( pTree, "Target should be an tree!", return true; );

  CVec2 fromPos;
	if ( IsValid( pParent ) )
  {
    fromPos = pParent->AcquireApplicationPosition().AsVec2D();
  }
	else
  {
    fromPos = GetAbilityOwner()->GetPosition().AsVec2D();
  }

	CVec2 dir = pTree->GetPosition().AsVec2D() - fromPos;
  Normalize( &dir );

  pTree->DropTree( dir, GetAbilityOwner() );

  return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFApplRaiseFlag::Start()
{
  if ( PFApplChannelling::Start() )
  {
    return true;
  }

  pFlagpole = dynamic_cast<PFFlagpole*>( pReceiver.GetPtr() );
  NI_VERIFY( IsValid( pFlagpole ), "Target should be a flagpole!", return true );

  if ( pFlagpole->CanRaise( GetAbilityOwner()->GetFaction() ) )
  {
    pFlagpole->OnStartRaise( GetAbilityOwner()->GetTeamId(), GetLifetime() );
    started = true;
    return false;
  }

  return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFApplRaiseFlag::Fire()
{
  PFApplChannelling::Fire();
  if ( IsUnitValid( pFlagpole ) )
  {
    pFlagpole->OnRaise( GetAbilityOwner()->GetFaction(), GetAbilityOwner());
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFApplRaiseFlag::Cancel()
{
  PFApplChannelling::Cancel();
  if ( started && IsUnitValid( pFlagpole ) )
  {
    pFlagpole->OnCancelRaise();
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFApplRaiseFlag::Step( float dtInSeconds )
{
  if ( !PFApplChannelling::Step( dtInSeconds ) )
  {
    NDb::EFaction faction = GetAbilityOwner()->GetFaction();
    const PFFlagpole* pCurrent = pFlagpole;
    if ( const PFFlagpole* prev =  pCurrent->GetPrevFlagpole( faction ) )
    {
      return ( prev->GetFaction() != faction );
    }
    return false;
  }

  return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool PFApplDealedDamageConverter::Start()
{
  if (PFBaseApplicator::Start())
    return true;

  float damageDealed = GetDamageDealed(pReceiver, GetDB().deltaTime, GetAbility());
  float value = damageDealed * scale;

  switch (GetDB().type)
  {
    case NDb::HEALTARGET_HEALTH:
    {
      pReceiver->OnHeal(pReceiver, value);
      break;
    }
    case NDb::HEALTARGET_ENERGY:
    {
      pReceiver->OnHealEnergy(pReceiver, value);
      break;
    }
    default:
      NI_ALWAYS_ASSERT("Unknown heal target type");
  }
  return true; // done
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFApplWaitForSpell::Start()
{
	if (PFApplBuff::Start())
		return true;

	Target targ;
	MakeApplicationTarget(targ, GetDB().spellTarget);

  if( !targ.IsValid(true) )
    return true;

	Target source;
  MakeApplicationTarget(source);
  if ( GetDB().dispatchSource )
  {
    CObj<PFSingleTargetSelector> pSourceTS = static_cast<PFSingleTargetSelector*>(GetDB().dispatchSource->Create( GetWorld() ));
    if ( pSourceTS )
    {
      const PFTargetSelector::RequestParams rp( *this, source );
      pSourceTS->FindTarget( rp, source );
    }
  }

  if ( !pTargetSelector && GetDB().firstTargetToHit )
    pTargetSelector = static_cast<PFSingleTargetSelector*>(GetDB().firstTargetToHit->Create( GetWorld() ));

  pDispatch = CreateDispatch(GetAbility(), this, source, targ, GetDB().spell, 0, true );

	return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFApplWaitForSpell::Stop()
{
	if (IsValid(pDispatch))
	{
		pDispatch->Cancel();
	}

  pDispatch = 0;

	PFApplBuff::Stop();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFApplWaitForSpell::Step(float dtInSeconds)
{
	if (PFApplBuff::Step(dtInSeconds))
		return true;

	if ( !IsValid(pDispatch) )
		return true;

	if ( !isDispatchFinished && pDispatch->HasArrived() )
	{
		if ( IsValid(pParent) && !isFirstHitTargetFound )
		{
			if ( (GetDB().behaviour & NDb::WAITFORSPELLBEHAVIOUR_UPDATEPARENTTARGET) != 0 )
        pParent->SetTarget( Target(pDispatch->GetCurrentPosition()) );

      // Notify Cancel if target of dispatch was dropped (non-position was set to position)
      if ( !pDispatch->GetTarget().IsPosition() || pDispatch->GetOriginalTarget().IsPosition() )
			  pParent->OnNotification(*this, NDb::PARENTNOTIFICATION_DONE);
      else
        pParent->OnNotification(*this, NDb::PARENTNOTIFICATION_CANCEL);
		}

		// Stop effect earlier
    for ( int i = 0; i < effects.size(); i++ )
    {
      NGameX::KillEffect( effects[i] );
    }

		isDispatchFinished = true;

    if ( (GetDB().behaviour & NDb::WAITFORSPELLBEHAVIOUR_STOPWHENSPELLFINISHED) != 0)
			return true;
	}

	return false;
}

void PFApplWaitForSpell::OnDispatchStep( PFDispatch* pDispatch )
{
  if ( !pTargetSelector )
    return;

  NI_VERIFY( IsValid( pDispatch ), "Invalid dispatch for OnDispatchStep", return );

  if ( !pDispatch->HasArrived() )
  {
    PFDispatchUniformLinearMove* pLinearDispatch = dynamic_cast<PFDispatchUniformLinearMove*>(pDispatch);
    if ( !pLinearDispatch )
      return;

    Target firstHitTarget;
    const PFTargetSelector::RequestParams rp( *this, (const Target)(pLinearDispatch->GetCurrentPosition()) );
    if ( pTargetSelector->FindTarget( rp, firstHitTarget ) )
    {
      pLinearDispatch->ForceArrive( firstHitTarget, (GetDB().behaviour & NDb::WAITFORSPELLBEHAVIOUR_DONTAPPLYEFFECTONFIRSTTARGET) == 0 );
      if ( IsValid(pParent) )
      {
        if ( (GetDB().behaviour & NDb::WAITFORSPELLBEHAVIOUR_UPDATEPARENTTARGET) != 0 )
          pParent->SetTarget( firstHitTarget );

        pParent->OnNotification(*this, NDb::PARENTNOTIFICATION_DONE);
      }
      isFirstHitTargetFound = true;
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFApplWatch::Start() 
{ 
	if (PFApplBuff::Start())
		return true; 

	// Attach to base unit as event listener
	pReceiver->AddEventListener(this);

	return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned int PFApplWatch::OnEvent(const PFBaseUnitEvent *pEvent)
{
	if (!pParent || GetDB().onSenderDispatchApply == NDb::PARENTNOTIFICATION_NA)
		return 0;

	if (pEvent->GetType() != NDb::BASEUNITEVENT_DISPATCHAPPLIED && 
		  pEvent->GetType() != NDb::BASEUNITEVENT_DISPATCHEVADED &&
      pEvent->GetType() != NDb::BASEUNITEVENT_DISPATCHMISSED)
		return 0;

	const PFBaseUnitDispatchEvent *pDispatchEvent = static_cast<const PFBaseUnitDispatchEvent*>(pEvent);
	if (IsValid(pParent) && pDispatchEvent->GetDispatch()->GetSender() == pParent->GetReceiver())
	{
		if (pEvent->GetType() == NDb::BASEUNITEVENT_DISPATCHAPPLIED)
		{
			if (GetDB().onSenderDispatchApply != NDb::PARENTNOTIFICATION_NA)
				pParent->OnNotification(*this, GetDB().onSenderDispatchApply);
		}
		
    if (pEvent->GetType() == NDb::BASEUNITEVENT_DISPATCHMISSED)
		{
			if (GetDB().onSenderDispatchMiss != NDb::PARENTNOTIFICATION_NA)
				pParent->OnNotification(*this, GetDB().onSenderDispatchMiss);
		}

    if (pEvent->GetType() == NDb::BASEUNITEVENT_DISPATCHEVADED)
    {
     if (GetDB().onSenderDispatchEvade != NDb::PARENTNOTIFICATION_NA)
      pParent->OnNotification(*this, GetDB().onSenderDispatchEvade);
    }
	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFApplWatch::Stop()
{
	if (IsValid(pParent))
	{
		if (pReceiver->IsDead())
		{
			if (GetDB().onUnitDeath != NDb::PARENTNOTIFICATION_NA)
				pParent->OnNotification(*this, GetDB().onUnitDeath);
		}
		else
		{
			if (GetDB().onFinish != NDb::PARENTNOTIFICATION_NA)
				pParent->OnNotification(*this, GetDB().onFinish);
		}
	}

	// Attach to base unit as event listener
	pReceiver->RemoveEventListener(this);

	PFApplBuff::Stop();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFApplSpellSwitch::Start()
{
  if (PFBaseApplicator::Start())
    return true;

  int nIndex = RetrieveParam(GetDB().activeSpellIndex);

  if( nIndex >= 0 && GetDB().spells.size() > nIndex && GetDB().spells[nIndex] != NULL)
  {
    Target targ;
    MakeApplicationTarget(targ); // Apply on the same target as this applicator

    if ( GetDB().dontUseDispatches )
    {
      PFApplCreatePars cp(pAbility, targ, this);
      for ( int i = 0, applsNumber = GetDB().spells[nIndex]->applicators.size(); i < applsNumber; ++i )
      {
        cp.pDBAppl = GetDB().spells[nIndex]->applicators[i];
	      CObj<PFBaseApplicator> pAppl = CreateApplicator(cp);

		    if (pAppl)
          ActivateApplicator(pAppl, pAbility);
      }
    }
    else
    {
      Target const source( pOwner );
      CreateDispatch(pAbility, this, source, targ, GetDB().spells[nIndex]);
    }
  }

  return true; // done
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFApplNaftaTransfer::Start()
{
  if (PFBaseApplicator::Start())
    return true;

  float amount = RetrieveParam(GetDB().amount);

  Target targ;
  MakeApplicationTarget(targ, GetDB().naftaTransferTarget);

  float amountNaftaRemoved = pReceiver->OnRemoveGold(GetAbilityOwner(), amount);
#ifndef VISUAL_CUTTED
  CObj<NGameX::PFUIEvent> pUIEvent;
  if (GetDB().uiEvent)
    pUIEvent = new NGameX::PFUIEvent( GetDB().uiEvent, pReceiver );

  NGameX::SingleValueNameMapFloat eventData(amount);
  NGameX::AdventureScreen::Instance()->OnUIEvent(pUIEvent, &eventData);
#endif

  float rMul    = RetrieveParam(GetDB().multiplier);
  float rAdd    = RetrieveParam(GetDB().addition  );

  NI_DATA_VERIFY(targ.IsUnit(), 
    NStr::StrFmt("NaftaTransferApplicator::naftaTransferTarget (%s, %s) should be UNIT", 
    GetDB().GetDBID().GetFileName().c_str(), GetDB().GetDBID().GetId().c_str()), 
    return true; );

  naftaTransferred = rMul * amountNaftaRemoved + rAdd;
  targ.GetUnit()->OnAddGold(GetAbilityOwner(), naftaTransferred);

  PFBaseHero * pHero = dynamic_cast<PFBaseHero*>(targ.GetUnit().GetPtr());
  if (IsValid( pHero ))
  {
    StatisticService::RPC::SessionEventInfo eventParams;
    eventParams.intParam1 = naftaTransferred;
    pHero->LogSessionEvent(SessionEventType::NaftaIncomeFromTalent, eventParams);
  }

  return true; // done
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float PFApplNaftaTransfer::GetVariable(const char* sVariableName) const
{
  if ( strcmp(sVariableName, "naftaTransferred") == 0 )
    return naftaTransferred;
  return PFBaseApplicator::GetVariable(sVariableName);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFApplModifyTerrain::Start()
{
	if (PFBaseApplicator::Start())
		return true;

  if(PFWorldNatureMap * pMap = GetWorld()->GetNatureMap())
  {
    float           durationTime = RetrieveParam(GetDB().durationTime);
    NDb::EFaction   faction  = NDb::EFaction(RetrieveParam(GetDB().faction, 0));
    CVec2           position = GetTarget().AcquirePosition().AsVec2D();
    float           radius = RetrieveParam(GetDB().modifRadius, 1.0f);
    CCircle         circle(position, radius);
    pMap->Override(faction, circle, durationTime, GetObjectId());
  }

  return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFApplModifyTerrain::Step(float dtInSeconds)
{
  PFWorldNatureMap * pMap = GetWorld()->GetNatureMap();
  return pMap ? !pMap->IsOverrideActive(GetObjectId()) : true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFApplProgram::DumpInfo(NLogg::CChannelLogger &logger) const
{
	PFBaseApplicator::DumpInfo(logger);
	LogLogicInfo(logger)("      exec index: %d (%s)\n", applicatorExecuting, pApplExecuting ? pApplExecuting->GetObjectTypeName() : "unknown");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFApplProgram::ExecuteNext()
{
  if ( IsFinished() )
  {
    return false;
  }

	do 
	{
    if ( applicatorExecuting >= 0 )
    {
      const bool shouldStopByCondition = RetrieveParam( GetDB().applicators[applicatorExecuting].stopCondition, false );
      if ( shouldStopByCondition )
      {
        return false;
      }

      const bool shouldContinueByCondition = RetrieveParam( GetDB().applicators[applicatorExecuting].continueCondition, false );
      ready2Execute |= shouldContinueByCondition;

      if ( !isDelayTimerEnabled )
      {
        const float delayTimer = RetrieveParam( GetDB().applicators[applicatorExecuting].delay, -1.0f );
        if ( delayTimer >= 0.0f )
        {
          isDelayTimerEnabled = true;
          currentDelayTimer = delayTimer;
        }
      }
      else
      {
        if ( currentDelayTimer < 0.0f )
        {
          ready2Execute = true;
          isDelayTimerEnabled = false;
        }
      }
    }

    if ( !ready2Execute )
    {
      return true;
    }

    ready2Execute = false;

  	applicatorExecuting++;
		if ( IsFinished() )
    {
      return false;
    }

    NDb::Ptr<NDb::BaseApplicator> const& pApplDesc = GetDB().applicators[applicatorExecuting].applicator;
    if ( !pApplDesc.IsEmpty() )
    {
      Target targ( pReceiver );
      PFApplCreatePars cp( pAbility, targ, this );
      cp.pDBAppl = pApplDesc;
      CObj<PFBaseApplicator> pAppl = CreateApplicator( cp );
      if ( pAppl )
      {
        pApplExecuting = pAppl;
        if ( !ActivateApplicator( pAppl, pAbility ) ) // skip if can't activate applicator (target is dead, appl is canceled etc)
        {
          ready2Execute = true;
        }

        if ( IsFinished() )
        {
          return false;
        }
      }
      else
      {
        ready2Execute = true;
      }
		}
	} while ( ready2Execute || ( GetDB().applicators[applicatorExecuting].continueEvents == 0 ) || GetDB().applicators[applicatorExecuting].applicator.IsEmpty() );

	return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFApplProgram::OnNotification(PFBaseApplicator &appl, NDb::EParentNotification note)
{
	if (&appl != pApplExecuting.GetPtr() || IsFinished()) // ignore events from non-current applicator
		return;

	if (( GetDB().applicators[applicatorExecuting].stopEvents & (1 << note) ) != 0)
	{
		applicatorExecuting = GetDB().applicators.size(); // Finished
    NotifyParent(NDb::PARENTNOTIFICATION_CANCEL);
    return;
	}

	if (( GetDB().applicators[applicatorExecuting].continueEvents & (1 << note) ) != 0)
	{
		ready2Execute = true; // Ready to execute
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFApplProgram::IsFinished() const
{
	return applicatorExecuting >= GetDB().applicators.size();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFApplProgram::Start()
{
	if ( PFApplBuff::Start() )
  {
    return true;
  }

  if ( !IsEnabled() )
  {
    return true; // don't start program
  }

	return !ExecuteNext();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFApplProgram::Stop()
{
	pApplExecuting = 0; // Drop executing applicator. We've done!
	PFApplBuff::Stop();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFApplProgram::Step( float dtInSeconds )
{
  NI_PROFILE_FUNCTION

	if ( PFApplBuff::Step( dtInSeconds ) )
  {
    return true;
  }

  if ( isDelayTimerEnabled )
  {
    currentDelayTimer -= dtInSeconds;
  }
	const bool finished = !ExecuteNext();
  if ( finished )
  {
    NotifyParent( NDb::PARENTNOTIFICATION_DONE );
  }
  return finished;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace
{

struct RememberTargets : ITargetAction, NonCopyable
{
  RememberTargets(vector< Target > & _targets) : targets(_targets) {}

  void operator()(Target const &target)
  {
    targets.push_back(target);
  }

  vector< Target > & targets;
};

}

bool PFApplForAllTargets::Start()
{
  if (PFBaseApplicator::Start())
    return true;

  NDb::ForAllTargetsApplicator const &dbDesc = GetDB();
  NI_VERIFY(IsValid(dbDesc.targets), "Target selector for ForAllTargetsApplicator is invalid", return true);
  
  CObj<PFTargetSelector> pTargetSelector = dbDesc.targets->Create( GetWorld() );

  PFTargetSelector::RequestParams params(pOwner.GetPtr(), this, Target(pReceiver));

  targets.reserve(10);
  RememberTargets remember(targets);
  pTargetSelector->EnumerateTargets(remember, params);

  ready2Execute = true;
  currentTarget = 0;
 
  return !ExecuteNext();
}

void PFApplForAllTargets::Stop()
{
  currentProgram = 0;
  targets.clear();
  PFApplBuff::Stop();
}

bool PFApplForAllTargets::Step(float dtInSeconds)
{
  if (PFBaseApplicator::Step(dtInSeconds))
    return true;

  bool finished = !ExecuteNext();
  if ( finished )
    NotifyParent(NDb::PARENTNOTIFICATION_DONE);
  return finished;
}

void PFApplForAllTargets::OnNotification(PFBaseApplicator &appl, NDb::EParentNotification note)
{
  if (&appl != currentProgram.GetPtr()) // ignore events from non-current applicator
    return;

  if (( GetDB().stopEvents & (1 << note) ) != 0)
  {
    ready2Execute = true;
    currentTarget = targets.size(); // Finished
    NotifyParent(NDb::PARENTNOTIFICATION_CANCEL);
    return;
  }

  if (( GetDB().continueEvents & (1 << note) ) != 0)
  {
    ready2Execute = true; // Ready to execute
  }
}

bool PFApplForAllTargets::ExecuteNext()
{
  if ( ready2Execute )
  {
    if ( IsFinished() )
      return false;
  }
  else
  {
    return true;
  }

  do 
  {
    ready2Execute = false;

    Target const &target = targets[currentTarget];
    currentTarget += 1;

    PFApplCreatePars cp(pAbility, target, this);
    cp.pDBAppl = GetDB().program;

    currentProgram = 0;
    if (CObj<PFBaseApplicator> pAppl = CreateApplicator(cp))
    {
      currentProgram = pAppl;

      if ( GetDB().skipTargetIfInvalid && !target.IsValid( true ) )
        ready2Execute = true;
      else if ( !ActivateApplicator(pAppl, pAbility) ) // skip if can't activate applicator (target is dead, appl is cancelled etc)
        ready2Execute = true;

      if ( IsFinished() && ready2Execute )
        return false;
    }
  } while (ready2Execute);

  return true;
}

bool PFApplForAllTargets::IsFinished() const
{
  return currentTarget >= targets.size();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float PFApplForAllTargets::GetVariable(const char* sVariableName) const
{
  if ( strcmp(sVariableName, "lastTarget") == 0 )
    return IsFinished() ? 1.0f : 0.0f;

  if ( strcmp(sVariableName, "targetsCount") == 0 )
    return (float)targets.size();

  return PFBaseApplicator::GetVariable(sVariableName);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFApplMovementControl::Enable()
{
	PFApplBuff::Enable();

	CPtr<PFBaseMovingUnit> pMovingRecever = IsValid(pReceiver) ? dynamic_cast<PFBaseMovingUnit*>( pReceiver.GetPtr() ) : NULL;
  CPtr<PFBaseMovingUnit> pMovingSender  = IsValid(pAbility) ? dynamic_cast<PFBaseMovingUnit*>( pAbility->GetOwner().GetPtr() ) : NULL;
  
  if ( IsValid(pMovingRecever) && IsValid(pMovingSender) )
  {
    pMovingRecever->FollowTo(pMovingSender, true);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFApplMovementControl::Disable()
{
  CPtr<PFBaseMovingUnit> pMovingRecever = IsValid(pReceiver) ? dynamic_cast<PFBaseMovingUnit*>( pReceiver.GetPtr() ) : NULL;
  CPtr<PFBaseMovingUnit> pMovingSender  = IsValid(pAbility) ? dynamic_cast<PFBaseMovingUnit*>( pAbility->GetOwner().GetPtr() ) : NULL;
 
  if ( IsValid(pMovingRecever) )
    pMovingRecever->FollowTo(NULL, true);

	PFApplBuff::Disable();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFApplChangeAnimSet::Start()
{
  if( Base::Start() )
    return true;
  
  CPtr<PFCreature> pCreature = IsValid(pReceiver) ? dynamic_cast<PFCreature*>(pReceiver.GetPtr()) : NULL;
  setId = pCreature ? pCreature->ReplaceAnimSet( GetDB().animSet ) : -1;
    
  return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFApplChangeAnimSet::Stop()
{
  Base::Stop();
  
  CPtr<PFCreature> pCreature = IsValid(pReceiver) ? dynamic_cast<PFCreature*>(pReceiver.GetPtr()) : NULL;
  if( pCreature && -1 != setId )
    pCreature->RollbackAnimSet( setId ) ;

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFApplChangeAnimation::Enable()
{
  Base::Enable();

  CPtr<PFCreature> pCreature = IsValid(pReceiver) ? dynamic_cast<PFCreature*>(pReceiver.GetPtr()) : NULL;
  animId = pCreature->ReplaceAnimation(GetDB().animState, GetDB().animation.c_str(), GetDB().marker.c_str(), GetDB().upper, GetDB().affectAllSets);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFApplChangeAnimation::Disable()
{
  CPtr<PFCreature> pCreature = IsValid(pReceiver) ? dynamic_cast<PFCreature*>(pReceiver.GetPtr()) : NULL;
  if( pCreature && -1 != animId )
    pCreature->RollbackAnimation( GetDB().animState, animId, GetDB().upper) ;
   
  Base::Disable();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFApplEye::Start()
{
  MakeApplicationTarget(eyeTarget, GetDB().eyeTarget);

  return PFApplBuff::Start();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFApplEye::Enable()
{
  PFApplBuff::Enable();

  if (eyeTarget.IsValid())
  {
    float visRange = RetrieveParam(GetDB().visRange, 1.0f);
    NI_VERIFY( visRange > 0, NStr::StrFmt("Wrong vision range in applicator %s", NDb::GetFormattedDbId(GetDB().GetDBID()) ) , return; );

    TileMap * tileMap = pOwner->GetWorld()->GetTileMap();
    SVector position = tileMap->GetTile(eyeTarget.AcquirePosition().AsVec2D());
    int visTileRange = tileMap->GetLenghtInTiles(visRange);

    int factionMask = pOwner->GetFactionMask( GetDB().flags );
    if ( (factionMask & (1 << NDb::FACTION_FREEZE)) != 0 )
      visUnitID0 = pOwner->GetWorld()->GetFogOfWar()->AddObject(position, NDb::FACTION_FREEZE, visTileRange, GetDB().cancelObstacles);
    if ( (factionMask & (1 << NDb::FACTION_BURN)) != 0 )
      visUnitID1 = pOwner->GetWorld()->GetFogOfWar()->AddObject(position, NDb::FACTION_BURN, visTileRange, GetDB().cancelObstacles);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFApplEye::Disable()
{
  if ( visUnitID0 > -1 )
    pOwner->GetWorld()->GetFogOfWar()->RemoveObject(visUnitID0);
  if ( visUnitID1 > -1 )
    pOwner->GetWorld()->GetFogOfWar()->RemoveObject(visUnitID1);

	visUnitID0 = -1;
	visUnitID1 = -1;

  PFApplBuff::Disable();
}

void PFApplEye::Reset()
{
	PFApplBuff::Reset();

  /* Currently the warfog is serrialized, so there is no need for that
	float visRange = RetrieveParam(GetDB().visRange, 1.0f);
	TileMap * tileMap = pOwner->GetWorld()->GetTileMap();
	SVector position = tileMap->GetTile(eyeTarget.AcquirePosition().AsVec2D());
	int visTileRange = tileMap->GetLenghtInTiles(visRange);

	if (  visUnitID0 > -1 )
		visUnitID0 = pOwner->GetWorld()->GetFogOfWar()->AddObject(position, NDb::FACTION_FREEZE, visTileRange);
	if ( visUnitID1 > -1 )
		visUnitID1 = pOwner->GetWorld()->GetFogOfWar()->AddObject(position, NDb::FACTION_BURN, visTileRange);*/
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFApplEye::Step(float dtInSeconds)
{
  if (Base::Step(dtInSeconds))
    return true;

  UpdateEyePosition();
  return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFApplEye::UpdateEyePosition()
{
  if (eyeTarget.IsValid())
  {
    SVector pos = pOwner->GetWorld()->GetTileMap()->GetTile(eyeTarget.AcquirePosition().AsVec2D());
    if ( visUnitID0 > -1 )
      pOwner->GetWorld()->GetFogOfWar()->MoveObject(visUnitID0, pos);
    if ( visUnitID1 > -1 )
      pOwner->GetWorld()->GetFogOfWar()->MoveObject(visUnitID1, pos);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool PFApplLockTiles::Start()
{
  NI_VERIFY(IsValid(pOwner), "Invalid usage", return false;);

  if ( !GetDB().collision.IsEmpty() )
  {
    coll = GetDB().collision;
  }
  else
  {
    // build collision bbox
    coll.x1 = FP_MAX_VALUE;
    coll.x2 = -FP_MAX_VALUE;
    coll.y1 = FP_MAX_VALUE;
    coll.y2 = -FP_MAX_VALUE;
    for ( int i = 0; i < GetDB().lockMask.mask.size(); ++i)
    {
      coll.x1 = Min( coll.x1, (float)GetDB().lockMask.mask[i].x );
      coll.x2 = Max( coll.x2, (float)GetDB().lockMask.mask[i].x );
      coll.y1 = Min( coll.y1, (float)GetDB().lockMask.mask[i].y );
      coll.y2 = Max( coll.y2, (float)GetDB().lockMask.mask[i].y );
    }
    
    coll.x2 = 0.5f * GetDB().lockMask.tileSize * (coll.x2 - coll.x1 + 1.f);
    coll.x1 = -coll.x2;
    coll.y2 = 0.5f * GetDB().lockMask.tileSize * (coll.y2 - coll.y1 + 1.f);
    coll.y1 = -coll.y2;
  }

  // lock tiles
  if (GetTarget().IsUnit())
  {
    CPtr<PFBaseUnit> const &pUnit = GetTarget().GetUnit();
    if ( IsValid( pUnit ) )
    {
      place.pos = pUnit->GetPosition();

      // get orientation from moving unit
      if ( PFBaseMovingUnit const* pMovingUnit = dynamic_cast<PFBaseMovingUnit const*>(pUnit.GetPtr()) )
      {
        CVec2 dir = pMovingUnit->GetMoveDirection();
        
        SHMatrix m;
        Identity(&m);
        m._11 = dir.x;   m._12 = -dir.y;
        m._21 = dir.y;   m._22 = dir.x;
        
        place.rot.FromEulerMatrix(m);
      }
      else if ( PFBuilding const* pBldg = dynamic_cast<PFBuilding const*>(pUnit.GetPtr()) )
      {
        place.rot = pBldg->GetAdvMapObjectCopy().offset.GetPlace().rot;
      }
    }
  }
  else
  {
    place.pos = GetTarget().GetPosition();
  }
  
  vector<SVector> occupiedTiles;
  pOwner->GetWorld()->GetTileMap()->FillOccupiedTiles(occupiedTiles, coll, GetDB().lockMask.tileSize, GetDB().lockMask.mask, place);
  pOwner->GetWorld()->GetTileMap()->MarkObject(occupiedTiles, true, MAP_MODE_BUILDING);

  // push out units
  float radius = 0.5f * ( Max(coll.x2 - coll.x1, coll.y2 - coll.y1) + 1 );
  vector<PFBaseMovingUnit*> units;
  PFBaseMovingUnit::GetAllUnitsInRangeConsiderSize(pOwner->GetWorld()->GetAIWorld(), place.pos.AsVec2D(), radius, units, false,
                                       GetDB().pushCaster ? 0 : dynamic_cast<PFBaseMovingUnit*>(pOwner.GetPtr()) );
  for ( int i = 0; i < units.size(); ++i)
  {
    if ( !units[i]->CheckFlagType( NDb::UNITFLAGTYPE_IGNOREPUSH ) )
    {
      CVec2 newPos;
      units[i]->FindFreePlace(units[i]->GetPosition().AsVec2D(), 2.f * radius, newPos);
      units[i]->TeleportTo(newPos, true, false);
    }
  }

  return Base::Start();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFApplLockTiles::Stop()
{
  NI_PROFILE_FUNCTION

  Base::Stop();

  vector<SVector> occupiedTiles;
  pOwner->GetWorld()->GetTileMap()->FillOccupiedTiles(occupiedTiles, coll, GetDB().lockMask.tileSize, GetDB().lockMask.mask, place);
  pOwner->GetWorld()->GetTileMap()->MarkObject(occupiedTiles, false, MAP_MODE_BUILDING);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool PFApplMount::Start()
{
  if (PFBaseApplicator::Start())
    return true;

  NI_VERIFY( IsValid(pReceiver), "Receiver must be valid!", return true );

  if ( !pReceiver->IsHero() || pReceiver->IsDead() )
    return true; // this applicator works only on alive heroes

  pHero = static_cast<PFBaseHero*>(pReceiver.GetPtr());

  if ( pHero->GetMount() )
    return true; // already mounted

	Target targ;
	MakeApplicationTarget(targ, GetDB().mountTarget);

  NI_VERIFY(targ.IsUnit(), "Mount should be unit", return true; );

  pMount = dynamic_cast<PFBaseMovingUnit*>(targ.GetUnit().GetPtr());
  NI_VERIFY(pMount, "Mount should be PFBaseMovingUnit", return true; );
  NI_VERIFY(pMount != pHero, "Trying to mount itself", return true; );

  if ( pMount->IsDead() )
  {
    NotifyParent(NDb::PARENTNOTIFICATION_CANCEL);
    return true;
  }

  pHero->Stop();
  pHero->OnMountSpecial( pMount, GetDB().controlMount );
  pMount->AttachUnit( pHero.GetPtr() );
  pMount->SetMount( true );

  pReceiver->AddEventListener(this);

  return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFApplMount::Stop()
{
  pReceiver->RemoveEventListener(this);
  if ( IsValid( pHero) )
    pHero->DismountSpecial();
  if ( IsValid( pMount ) )
    pMount->SetMount( false );

  Base::Stop();
}


bool PFApplMount::Step(float dtInSeconds)
{
  if ( IsValid( pMount ) )
  {
    if ( PFBaseHero* hero = dynamic_cast<PFBaseHero*>(pMount.GetPtr()) )
    {
      if ( hero->IsIsolated() )
      {
        return true;
      }
    }
  }
  return Base::Step(dtInSeconds);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned int PFApplMount::OnEvent(const PFBaseUnitEvent *pEvent)
{
  if ( pEvent->GetType() != NDb::BASEUNITEVENT_DEATH && pEvent->GetType() != NDb::BASEUNITEVENT_ISOLATE )
    return 0;
  
  if ( PFBaseUnitEventUnitDeath const* pEvtDeath = dynamic_cast<PFBaseUnitEventUnitDeath const*>(pEvent) )
  {
    if ( pEvtDeath->GetVictim() == pHero->GetMount() ) // mount is dead
    {
      pHero->DismountSpecial();
    }
  }
  else if ( PFBaseUnitMinigameEvent const* pEvt = dynamic_cast<PFBaseUnitMinigameEvent const*>(pEvent) )
  {
    if (pEvt->GetType() == NDb::BASEUNITEVENT_MINIGAMESTARTED && pEvt->GetUnit() == pHero->GetMount() )
    {
      pHero->DismountSpecial();
    }
  }

  return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFApplScaleControl::Enable()
{
  PFApplBuff::Enable();
  curScale = 1.0f;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFApplScaleControl::Disable()
{
  PFApplBuff::Disable();

  ApplyScale( 1.0f );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFApplScaleControl::Step(float dtInSeconds)
{
  NI_PROFILE_FUNCTION

    if (PFApplBuff::Step(dtInSeconds))
      return true;

  if (!IsEnabled())
    return false;

  float desiredScale = RetrieveParam( GetDB().desiredScale, 1.0f );
  if ( fabs(curScale - desiredScale ) < 1e-3 )
    return false;

  float speed = RetrieveParam( GetDB().changeSpeed, 0.0f );
  if ( speed <= 0.f )
    ApplyScale( desiredScale );
  else
  {
    float maxDif = speed * dtInSeconds / 100.f;
    float nextScale = desiredScale < curScale ? Max( desiredScale, curScale - maxDif ) : Min( desiredScale, curScale + maxDif );
    ApplyScale( nextScale );
  }

  return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFApplScaleControl::DumpInfo(NLogg::CChannelLogger &logger) const
{
  PFApplBuff::DumpInfo(logger);
  LogLogicInfo(logger)("      scale: %2.3f\n", curScale );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFApplScaleControl::Reset()
{
  PFApplBuff::Reset();
  if ( !pReceiver )
    return;

  float nextScale = curScale;
  curScale = 1.0f;
  ApplyScale( nextScale );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFApplScaleControl::ApplyScale( float scale )
{
  float scaleDiff = scale / curScale;

  if ( pReceiver->ClientObject() )
  {
    pReceiver->ClientObject()->MultiplyTemporaryScale( scaleDiff );
    pReceiver->ClientObject()->MultiplyAnimSpeed( scaleDiff );
  }

  curScale = scale;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFApplPickupChanneling::Start()
{
  if ( PFApplChannelling::Start() )
  {
    return true;
  }

  pPickupable = dynamic_cast<PFPickupableObjectBase*>( GetTarget().GetObject().GetPtr() );
  NI_VERIFY( IsValid( pPickupable ), "Target should be a pickupable!", return true );

  if ( pPickupable->CanBePickedUpBy( GetAbilityOwner() ) )
  {
    pPickupable->SetIsBeingPickuped( true );
    return false;
  }

  return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFApplPickupChanneling::Fire()
{
  PFApplChannelling::Fire();
  if ( IsValid( pPickupable ) )
  {
    pPickupable->PickUp( GetAbilityOwner() );
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFApplPickupChanneling::Stop()
{
  PFApplChannelling::Stop();
  if ( IsValid( pPickupable ) )
  {
    pPickupable->SetIsBeingPickuped( false );
  }
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PFApplInvalidAbilityTarget::PFApplInvalidAbilityTarget()
{

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PFApplInvalidAbilityTarget::PFApplInvalidAbilityTarget(PFApplCreatePars const &cp)
  : Base(cp)
{

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFApplInvalidAbilityTarget::Enable()
{
  PFApplBuff::Enable();

  pReceiver->SetInvalidAbilityTarget(true);

  DevTrace("+++ InvalidAbilityTarget (%d)", pReceiver->GetObjectId());
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFApplInvalidAbilityTarget::Disable()
{
  DevTrace("--- InvalidAbilityTarget (%d)", pReceiver->GetObjectId());

  pReceiver->SetInvalidAbilityTarget(false);

  PFApplBuff::Disable();
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PFApplDayNightTransition::PFApplDayNightTransition()
{

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PFApplDayNightTransition::PFApplDayNightTransition(PFApplCreatePars const &cp)
  : Base(cp)
{

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFApplDayNightTransition::Start()
{
  if (Base::Start())
    return true;

  if (DayNightController* const dayNightController = GetWorld()->GetDayNightController())
    dayNightController->Switch(GetDB().desiredState, GetDB().desiredStateFraction);

  return true;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////
PFApplSetTimescale::PFApplSetTimescale()
{
}

PFApplSetTimescale::PFApplSetTimescale(PFApplCreatePars const &cp)
: Base(cp)
{
}

bool PFApplSetTimescale::Start()
{
  if (PFBaseApplicator::Start())
    return true;

  float scale = Clamp(GetDB().desiredTimescale, 0.5f, 1.5f);
  NGameX::AdventureScreen::Instance()->SendGameCommand(CreateCmdSetTimescale(scale), true);

  return true; // done
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

REGISTER_WORLD_OBJECT_NM(PFApplDealedDamageConverter    , NWorld);
REGISTER_WORLD_OBJECT_NM(PFApplDropTree                 , NWorld);
REGISTER_WORLD_OBJECT_NM(PFApplRaiseFlag                , NWorld);
REGISTER_WORLD_OBJECT_NM(PFApplSpellSwitch              , NWorld);
REGISTER_WORLD_OBJECT_NM(PFApplProgram                  , NWorld);
REGISTER_WORLD_OBJECT_NM(PFApplForAllTargets            , NWorld);
REGISTER_WORLD_OBJECT_NM(PFApplWatch                    , NWorld);
REGISTER_WORLD_OBJECT_NM(PFApplModifyTerrain            , NWorld);
REGISTER_WORLD_OBJECT_NM(PFApplNaftaTransfer            , NWorld);
REGISTER_WORLD_OBJECT_NM(PFApplMovementControl          , NWorld);
REGISTER_WORLD_OBJECT_NM(PFApplChangeAnimSet            , NWorld);
REGISTER_WORLD_OBJECT_NM(PFApplChangeAnimation          , NWorld);
REGISTER_WORLD_OBJECT_NM(PFApplWaitForSpell             , NWorld);
REGISTER_WORLD_OBJECT_NM(PFApplEye                      , NWorld);
REGISTER_WORLD_OBJECT_NM(PFApplLockTiles                , NWorld);
REGISTER_WORLD_OBJECT_NM(PFApplMount                    , NWorld);
REGISTER_WORLD_OBJECT_NM(PFApplScaleControl             , NWorld);
REGISTER_WORLD_OBJECT_NM(PFApplPickupChanneling         , NWorld);
REGISTER_WORLD_OBJECT_NM(PFApplInvalidAbilityTarget     , NWorld);
REGISTER_WORLD_OBJECT_NM(PFApplDayNightTransition       , NWorld);
REGISTER_WORLD_OBJECT_NM(PFApplSetTimescale		          , NWorld);

