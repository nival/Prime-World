#include "stdafx.h"
#include "PFApplBounce.h"
#include "PFBaseUnit.h"
#include "PFWorld.h"
#include "PFDispatchFactory.h"
#include "PFAIWorld.h"
#include "PFTargetSelector.h"
#include "PFClientBaseUnit.h"

#ifndef VISUAL_CUTTED
#include "PFClientApplicators.h"
#include "PF_Core/EffectsPool.h"
#else
#include "../Game/pf/Audit/ClientStubs.h"
#endif

namespace NWorld
{

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFApplBounce::Start()
{
  if (PFApplBuff::Start())
		return true;

  MakeApplicationTarget( currentTarget, GetDB().startTarget );

  if ( (GetDB().flags & NDb::BOUNCEFLAGS_RENEWTARGETONSTART) != 0 )
  {
    // Set new target for 
    struct NewTargetSetter : NonCopyable
    {
      NewTargetSetter( const Target & _target, const PFAbilityData * _pAbilityData, const NDb::DBID & _applDbid )
        : target(_target), pAbilityData(_pAbilityData), found(false), applDbid(_applDbid)  {}

      void operator()( const CObj<PFBaseApplicator> &pAppl )
      {
        if ( pAppl->GetTypeId() == PFApplBounce::typeId && pAppl->GetAbility()->GetData() == pAbilityData && pAppl->GetDBBase()->GetDBID() == applDbid )
        {
          static_cast<PFApplBounce*>(pAppl.GetPtr())->SetNewTarget( target );
          found = true;
        }
      }
      const Target & target;
      const PFAbilityData * pAbilityData;
      const NDb::DBID & applDbid;
      bool found;
    } f( currentTarget, GetAbility()->GetData(), GetDB().GetDBID() );

    pReceiver->ForAllAppliedApplicators(f);

    if ( f.found )
      return true;
  }

  NI_VERIFY( GetDB().target, "No target selector for BounceApplicator", return true );

  pTargetSelector = static_cast<PFSingleTargetSelector*>(GetDB().target->Create( GetWorld() ));

  targetsNumber = RetrieveParam( GetDB().targetsNumber );
  bounceDelay = RetrieveParam( GetDB().bounceDelay );
 
  return !ExecuteNext();
}

void PFApplBounce::Stop()
{
  if ( targetsNumber > 0 )
    targetCounter = targetsNumber;

	PFApplBuff::Stop();
}

bool PFApplBounce::Step(float dtInSeconds)
{
	if (PFApplBuff::Step(dtInSeconds))
		return true;

  if ( finished )
  {
    return true;
  }

  if ( IsValid(pDispatch) )
  {
    if ( !pDispatch->HasArrived() )
      return false;

    pDispatch = 0;
    timeToNextBounce = bounceDelay;
  }

  if ( timeToNextBounce > EPS_VALUE && ( (GetDB().flags & NDb::BOUNCEFLAGS_BOUNCENEXTTARGETONLOSS) == 0 || currentTarget.IsObjectValid() ) )
  {
    timeToNextBounce -= dtInSeconds;
    return false;
  }

  return !ExecuteNext();
}

bool PFApplBounce::ExecuteNext()
{
  if ( (GetDB().flags & NDb::BOUNCEFLAGS_STARTFROMOWNER) == 0 || targetCounter > 0 )
  {
    Target const source( currentTarget );

    // find next target around prev target
    PFTargetSelector::RequestParams params(pOwner.GetPtr(), this, source );
    if ( !pTargetSelector->FindTarget( params, currentTarget ) )
      return false;

    pDispatch = CreateDispatch( pAbility, this, source, currentTarget, GetDB().spell );
  }
  else
  {
    Target const source( pOwner );
    pDispatch = CreateDispatch( pAbility, this, source, currentTarget, GetDB().spell );
  }

  ++targetCounter;

  return !IsFinished();
}

void PFApplBounce::OnDispatchTargetDropped( const PFDispatch * pDispatch )
{
  if ( (GetDB().flags & NDb::BOUNCEFLAGS_BOUNCENEXTTARGETONLOSS) == 0 )
    return;

  // find next target around dispatch pos
  PFTargetSelector::RequestParams params( pOwner.GetPtr(), this, Target( pDispatch->GetCurrentPosition() ) );
  if ( !pTargetSelector->FindTarget( params, currentTarget ) )
  {
    finished = true;
    return;
  }

  if ( IsValid(this->pDispatch) )
    this->pDispatch->SetNewTarget( currentTarget );
}

void PFApplBounce::SetNewTarget( const Target & _target )
{
  // Учитываем ситуацию, когда текущий диспатч уже успел прилететь.
  if ( IsValid( pDispatch ) && pDispatch->HasArrived() )
  {
    targetCounter++;
  }

  timeToNextBounce = 0;

  // Если новая цель - владелец, то завершаем и проигрываем cancelEffect
  if ( _target.IsUnitValid() && _target.GetUnit() == GetAbilityOwner() )
  {
#ifndef VISUAL_CUTTED
    int teamID = GetAbilityOwner() ? GetAbilityOwner()->GetOriginalTeamId() : -1;
    if ( teamID == -1 )
    {
      teamID = NDb::TEAMID_A;
    }
    if ( GetDB().cancelEffect[teamID].IsEmpty() )
    {
      teamID = ( teamID == NDb::TEAMID_B ) ? NDb::TEAMID_A : NDb::TEAMID_B;
    }

    const NDb::EffectBase* pDBEffect = GetDB().cancelEffect[teamID];

    if ( pDBEffect )
    {
      CObj<PF_Core::BasicEffect> pEffect = PF_Core::EffectsPool::Get()->Retrieve( pDBEffect );
      if ( pEffect )
      {
        if ( IsValid( pDispatch ) )
        {
          PF_Core::ClientObjectBase* pClientDispatch = pDispatch->ClientObject();
          if ( IsValid( pClientDispatch ) )
            pEffect->Apply( pClientDispatch, GetAbilityOwner()->GetFaction() );

          pDispatch->Cancel();
          pDispatch = 0;
        }
        else if ( currentTarget.IsObjectValid() && IsValid( currentTarget.GetObject()->ClientObject() ) )
        {
          pEffect->Apply( currentTarget.GetObject()->ClientObject(), GetAbilityOwner()->GetFaction() );
        }
      }
    }
#endif //VISUAL_CUTTED

    finished = true;

    return;
  }

  if ( IsValid( pDispatch ) && !pDispatch->HasArrived() )
  {
    pDispatch->SetNewTarget( _target );
  }
  else
  {
    pDispatch = CreateDispatch( pAbility, this, currentTarget, _target, GetDB().spell );
  }

  currentTarget = _target;
}

bool PFApplBounce::IsFinished() const
{
  if ( targetsNumber > 0 )
    return targetCounter == targetsNumber;

  return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float PFApplBounce::GetVariable(const char* sVariableName) const
{
  if ( strcmp(sVariableName, "target") == 0 )
    return (float)targetCounter;

  if ( strcmp(sVariableName, "IsInDelay") == 0 )
  {
    if ( timeToNextBounce > EPS_VALUE || IsValid( pDispatch ) && pDispatch->HasArrived() )
      return 1.0f;

    return 0.0f;
  }

  return PFBaseApplicator::GetVariable(sVariableName);
}

}

REGISTER_WORLD_OBJECT_NM(PFApplBounce,        NWorld);