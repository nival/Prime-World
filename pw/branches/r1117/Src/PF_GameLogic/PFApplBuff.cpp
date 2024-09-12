#include "stdafx.h"
#include "PFApplBuff.h"
#include "PFWorld.h"
#include "PFAIWorld.h"
#include "PFBaseUnit.h"
#include "PFDispatchStrike1.h"
#include "PFDispatchFactory.h"
#include "PFLogicDebug.h"
#include "PFHero.h"

#ifndef VISUAL_CUTTED
#include "PFClientApplicators.h"
#else
#include "../Game/pf/Audit/ClientStubs.h"
#endif

namespace NWorld
{

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PFApplBuff::PFApplBuff(PFApplCreatePars const &cp)
  : PFBaseApplicator(cp), lifeTime(0.0f), duration(0.0f), isInterrupted(false)
{}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFApplBuff::Init()
{
	if (!PFBaseApplicator::Init())
  {
	  lifeTime = -1.0f;
	  duration = 0;
		return false;
  }

	lifeTime = RetrieveParam(GetDBAppl<NDb::BuffApplicator>().lifeTime, -1.0f);
	duration = GetModifiedDuration(lifeTime);

	return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFApplBuff::Start()
{
  PFBaseApplicator::Start();

#ifndef _SHIPPING
  int& count = PFBaseApplicator::s_ActiveApplicatorsCountByDBID[ GetDBBase()->GetDBID() ];
  count++;
  if ( count > 0 && count % 100 == 0 )
    DebugTrace( "Warning! %d active applicators detected: %s", count, GetDBBase()->GetDBID().GetFormatted().c_str() );
#endif

  if ( RetrieveParam( GetDBAppl<NDb::BuffApplicator>().startCondition, true ) == false )
  {
    SetEnabled( false );
    return true;
  }

  if (IsEnabled())
    Enable();

  if( IsValid(pReceiver) )
    receiverPlacementOnStart = pReceiver->GetVisualPosition3D();

  return false;
}

PFLogicObject* PFApplBuff::GetEffectOrigin()
{
  return GetAbilityOwner();
}

PFLogicObject* PFApplBuff::GetEffectTarget()
{
  return pReceiver;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFApplBuff::Enable()
{
  PrepareEffects( false );
  
  for ( int i = 0; i < effects.size(); i++ )
    NGameX::ApplyEffect(effects[i], GetAbilityOwner(), GetEffectTarget(), GetEffectOrigin(), this );
    
  AfterStartEffects();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void PFApplBuff::RestartEffects()
{
  KillEffects();
  
  if ( IsEnabled() )
  {
    PrepareEffects( true );
      
    for ( int i = 0; i < effects.size(); i++ )
      NGameX::RestoreEffect(effects[i], GetAbilityOwner(), GetEffectTarget(), GetEffectOrigin(), receiverPlacementOnStart, this );
    
    AfterStartEffects();
  }   
}

void PFApplBuff::PrepareEffects( bool manualDeathTypeOnly )
{
  const NDb::BuffApplicator& dbAppl = GetDBAppl<NDb::BuffApplicator>();

  int teamID = GetAbilityOwner() ? GetAbilityOwner()->GetOriginalTeamId() : -1;
  if ( teamID == -1 )
  {
    teamID = NDb::TEAMID_A;
  }
  if ( dbAppl.effect[teamID].IsEmpty() )
  {
    teamID = ( teamID == NDb::TEAMID_B ) ? NDb::TEAMID_A : NDb::TEAMID_B;
    if ( dbAppl.effect[teamID].IsEmpty() )
    {
      return;
    }
  }

  const NDb::EffectBase* pDBEffect = dbAppl.effect[teamID];
  const bool isList = ( pDBEffect->GetObjectTypeID() == NDb::EffectList::typeId );
  const NDb::EffectList* pEffectList = isList ? ( static_cast<const NDb::EffectList*>( pDBEffect ) ) : 0;
  const int effectsNumber = isList ? pEffectList->effects.size() : 1;
  effects.resize( effectsNumber );

  if ( isList )
  {
    for ( int i = 0; i < effectsNumber; i++ )
    {
      if ( GetAbilityOwner() )
        pEffectList->effects[i].ChangeState(GetAbilityOwner()->GetSkinId());

      if ( !manualDeathTypeOnly || ( pEffectList->effects[i]->deathType == NDb::EFFECTDEATHTYPE_MANUAL ) )
      {
        NGameX::PrepareEffect( effects[i], pEffectList->effects[i] );
      }
    }
  }
  else
  {
    if ( GetAbilityOwner() )
      dbAppl.effect[teamID].ChangeState(GetAbilityOwner()->GetSkinId());

    if ( !manualDeathTypeOnly || ( dbAppl.effect[teamID]->deathType == NDb::EFFECTDEATHTYPE_MANUAL ) )
    {
      NGameX::PrepareEffect( effects[0], dbAppl.effect[teamID] );
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFApplBuff::Disable()
{
  // flag tells us not to kill effect
  // but at the moment there're no use cases where this effect will be killed by anyone else
  // so let's just delay effect death until current animation is finished

  KillEffects();
}

void PFApplBuff::KillEffects()
{
  for ( int i = 0; i < effects.size(); i++ )
  {
    CObj<PF_Core::BasicEffect> &pEffect = effects[i];

    if(IsValid(pEffect))
      pEffect->SetInterrupted(GetInterrupted());

    NGameX::KillEffect( pEffect, GetDBAppl<NDb::BuffApplicator>().behaviorFlags & NDb::BUFFBEHAVIOR_DONTREMOVEEFFECT );
  }

  effects.clear();
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFApplBuff::Step(float dtInSeconds)
{
  NI_PROFILE_FUNCTION

  PFBaseApplicator::Step(dtInSeconds);

  if (!IsEnabled() && (GetDBAppl<NDb::BuffApplicator>().behaviorFlags & NDb::BUFFBEHAVIOR_STOPONDISABLE) != 0)
    return true;

  if (duration == -1.f)
  {
    return false;
  }

  duration -= dtInSeconds;
  return duration < EPS_VALUE;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFApplBuff::CanBeAppliedOnDead()
{
  return GetDBAppl<NDb::BuffApplicator>().behaviorFlags & NDb::BUFFBEHAVIOR_APPLYTODEAD;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFApplBuff::Stop()
{
  NI_PROFILE_FUNCTION

  if (IsEnabled())
	{
		SetEnabled(false);
    Disable();
	}

	if ( (GetDBAppl<NDb::BuffApplicator>().behaviorFlags & NDb::BUFFBEHAVIOR_REMOVECHILDREN) != 0 )
		RemoveChildrenApplicators();

#ifndef _SHIPPING
  PFBaseApplicator::s_ActiveApplicatorsCountByDBID[ GetDBBase()->GetDBID() ]--;
#endif

  PFBaseApplicator::Stop();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFApplBuff::GetRemainingLifeTime(float &time) const
{ 
  if (duration == -1.f)
    return false;

  time = duration;
  return true; 
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float PFApplBuff::GetVariable( const char *varName ) const
{
  if ( strcmp( varName, "duration" ) == 0 )
  {
    return duration;
  }
  return 0.0f;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFApplBuff::DumpInfo( NLogg::CChannelLogger & logger ) const
{
  PFBaseApplicator::DumpInfo(logger);
  LogLogicInfo(logger)("      time: %3.2f of %3.2f\n", duration, lifeTime);
}

bool PFApplBuff::NeedToStopOnDeath() const
{
  CPtr<PFBaseUnit> const& pReceiver = GetReceiver();
  if ( (GetDBAppl<NDb::BuffApplicator>().behaviorFlags & NDb::BUFFBEHAVIOR_DONTSTOPONDEATH)
       || ( bPassive && IsValid(pReceiver) && pOwner == pReceiver ) )
    return false;
  
  return PFBaseApplicator::NeedToStopOnDeath();
}

bool PFApplBuff::NeedToStopOnSenderDeath() const
{
  CPtr<PFBaseUnit> const& pReceiver = GetReceiver();
  if ( (GetDBAppl<NDb::BuffApplicator>().behaviorFlags & NDb::BUFFBEHAVIOR_DONTSTOPONSENDERDEATH)
       || ( bPassive && IsValid(pReceiver) && pOwner == pReceiver ) )
    return false;

  return PFBaseApplicator::NeedToStopOnSenderDeath();
}

bool PFApplBuff::NeedToDisableOnDeath() const
{
  if (GetDBAppl<NDb::BuffApplicator>().behaviorFlags & NDb::BUFFBEHAVIOR_ENABLEDONSENDERDEATH)
    return false;
  
  return PFBaseApplicator::NeedToDisableOnDeath();
}

//////////////////////////////////////////////////////////////////////////
bool PFApplAddApplicatorDuration::Start()
{
  if ( PFBaseApplicator::Start() )
  {
    return true;
  }

  NI_VERIFY(!GetDB().applicators.empty(), "PFApplAddApplicatorDuration: no applicators specified!", return true; );

  bool bCheckByName = GetDB().flags & NDb::UPDATEDURATIONFLAGS_CHECKBYFORMULANAME;
  bool bSetDuration = GetDB().flags & NDb::UPDATEDURATIONFLAGS_SETDURATION;

  struct UpdateApplicatorDuration : public NonCopyable
  {
    UpdateApplicatorDuration( vector<NDb::Ptr<NDb::BuffApplicator>> const& _dbApplList, float _durationToAdd, string const& _nameToCheck, bool _bCheckByName, bool _bSetDuration )
     : dbApplList( _dbApplList ), durationToAdd( _durationToAdd ), nameToCheck(_nameToCheck), bCheckByName(_bCheckByName), bSetDuration(_bSetDuration) { }

   void operator()( const CObj<PFBaseApplicator>& pAppl )
   {
     vector<NDb::Ptr<NDb::BuffApplicator>>::const_iterator it = dbApplList.begin();
     for (; it != dbApplList.end(); ++it )
     {
       if ( pAppl->GetDBBase()->GetDBID() == (*it)->GetDBID() && ( !bCheckByName || nameToCheck == pAppl->GetApplicatorName() ) )
       {
         PFApplBuff* pApplBuff = static_cast<PFApplBuff*>( pAppl.GetPtr() );

         if ( pApplBuff->GetDuration() > 0.0f )
         {
           float newDuration = bSetDuration ? durationToAdd : pApplBuff->GetDuration() + durationToAdd;
           pApplBuff->SetDuration( newDuration );
         }

         if ( pApplBuff->GetLifetime() > 0.0f )
         {
           float newLifeTime = bSetDuration ? durationToAdd : pApplBuff->GetLifetime() + durationToAdd;
           pApplBuff->SetLifetime( newLifeTime );
         }

         return;
       }
     }
   }

  private:
   vector<NDb::Ptr<NDb::BuffApplicator>> const& dbApplList;
   float durationToAdd;
   bool bSetDuration;
   bool bCheckByName;
   string const& nameToCheck;
  } updateApplicatorDuration( GetDB().applicators, RetrieveParam( GetDB().durationToAdd, 0.0f ), GetDB().nameToCheck, bCheckByName, bSetDuration );

  if ( IsValid(pReceiver) )
  {
    pReceiver->ForAllAppliedApplicators( updateApplicatorDuration );
  }

  return true;
}


}

REGISTER_WORLD_OBJECT_NM(PFApplBuff,                  NWorld);
REGISTER_WORLD_OBJECT_NM(PFApplAddApplicatorDuration, NWorld);

