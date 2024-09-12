#include "stdafx.h"
#include "PFApplHelper.h"
#include "PFBaseUnit.h"
#include "PFApplUtils.h"
#include "PFWorld.h"
#include "PFDispatchFactory.h"
#include "PFDispatchStrike1.h"
#include "PFTargetSelector.h"
#ifndef VISUAL_CUTTED
#include "PF_Core\ControlledStatusEffect.h"
#include "PFClientDispatch.h"
#endif

namespace NWorld
{

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFApplSpellPeriodically::DoStrike()
{
  NI_ASSERT(IsValid(GetAbilityOwner()), "Internal logic error");
  SendSpell2Targets(this, GetDB().spell, pTargetSelector);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFApplSpellPeriodically::Strike()
{
  DoStrike();
	strikeCount++;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFApplSpellPeriodically::Start()
{
  if ( PFApplBuff::Start() )
    return true;

  if (GetDB().targetSelector)
	{
    pTargetSelector = GetDB().targetSelector->Create(GetWorld());
	}

  period      = RetrieveParam(GetDB().period, 0.0f);
  startOffset = RetrieveParam(GetDB().startOffset, 0.0f);

  if (startOffset <= 0.0f)
    curPeriod = period;
  else
    curPeriod = startOffset;

  timer = 0.0f;

  if ( startOffset < EPS_VALUE && IsEnabled() )
    Strike(); 

  return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFApplSpellPeriodically::Step(float dtInSeconds)
{
  if (PFApplBuff::Step(dtInSeconds))
    return true;

	if (!IsEnabled())
	{
		strikeCount = 0;
		return false;
	}

	if (period == 0.0f)
	{
		Strike();
		return false;
	}

  timer += dtInSeconds;
	if (timer > curPeriod)
	{
		Strike();
    NI_ASSERT(curPeriod > 0, "should be > 0 for next instruction")
		timer = fmodf(timer, curPeriod);
		curPeriod = period;
	}

  return false; // false means "not done"
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float PFApplSpellPeriodically::GetScale() const
{
	switch (GetDB().scaleMode)
	{
		case NDb::SCALECALCULATIONMODE_SCALEISCOUNT: return float(strikeCount);
		case NDb::SCALECALCULATIONMODE_SCALEISTIME: return (strikeCount - 1) * period + timer + startOffset;
		case NDb::SCALECALCULATIONMODE_SCALEISVPAR: 
			if (GetLifetime() > 0.0f)
        return Min(1.0f, ( (strikeCount - 1) * period + timer + startOffset) / GetLifetime());
			else
			  return 0.0f;
		default:
			NI_ALWAYS_ASSERT("Invalid scale mode in SpellPeriodicallyApplicator");
			return 0.0f;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFApplSpellPeriodicallyVisual::Start()
{
	if (PFApplSpellPeriodically::Start())
		return true;

	attackTimeOffset = RetrieveParam(GetDB().attackTimeOffset, 0.0f);

	NI_DATA_ASSERT(attackTimeOffset <= GetPeriod() && attackTimeOffset <= GetStartOffset(), 
								 ErrorStr("attackTimeOffset should be less then period and start offset"));

	return false;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void PFApplSpellPeriodicallyVisual::AfterStartEffects()
{
  PFApplSpellPeriodically::AfterStartEffects();

#ifndef VISUAL_CUTTED
  controlledEffects.resize( effects.size() );
  for ( int i = 0; i < effects.size(); i++ )
  {
    controlledEffects[i] = dynamic_cast<PF_Core::ControlledStatusEffect*>( effects[i].GetPtr() );
    NI_DATA_ASSERT( controlledEffects[i], ErrorStr( "SpellPeriodicallyVisual should use ControlledStatusEffect or derivatives" ) );

    // Synchronize with dispatch's effect
    PFDispatch* pDispatch = GetDispatch().GetPtr();
    if ( pDispatch && controlledEffects[i] )
    {
      PFDispatchUniformLinearMove* pLDispatch = dynamic_cast<PFDispatchUniformLinearMove*>( pDispatch );
      if ( pLDispatch )
      {
        NGameX::PFDispatchUniformLinearMove* pClientDispatch = pLDispatch->ClientObject();

        if ( pClientDispatch && pClientDispatch->GetEffectsCount() > 0 )
        {
          NGameX::EffectsBucket::const_iterator iter = pClientDispatch->GetEffects().begin();
          
          while(iter != pClientDispatch->GetEffects().end())
          {
            const NGameX::PFDispatchEffectHolder *pEffect = iter++;
            controlledEffects[i]->SynchronizeWithPrototypeEffect( pEffect->GetEffect() );
          }
        }
      }
    }
  }
#endif

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFApplSpellPeriodicallyVisual::Disable()
{
#ifndef VISUAL_CUTTED
  for ( int i = 0; i < controlledEffects.size(); i++ )
  {
    controlledEffects[i]->OnEvent( pReceiver->IsDead() ? NDb::EFFECTEVENT_DEATH : NDb::EFFECTEVENT_STOP );
  }
#endif

  PFApplBuff::Disable();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFApplSpellPeriodicallyVisual::Step(float dtInSeconds)
{
	if (PFApplSpellPeriodically::Step(dtInSeconds))
		return true;

  if (!IsEnabled())
    return false;

#ifndef VISUAL_CUTTED
	float time2Strike = GetTime2Strike();
	if ( attackTimeOffset > 0.0f )
	{
		if ( ( attackTimeOffset >= time2Strike ) && ( strikeCountMarker == strikeCount ) )
		{
			// Command effect
			strikeCountMarker = strikeCount + 1;
      for ( int i = 0; i < controlledEffects.size(); i++ )
      {
        controlledEffects[i]->OnEvent(NDb::EFFECTEVENT_ATTACK, time2Strike);
      }
		}
	}
	else
	{
		if ( strikeCountMarker != strikeCount )
		{
			// Command effect
			strikeCountMarker = strikeCount;
      for ( int i = 0; i < controlledEffects.size(); i++ )
      {
        controlledEffects[i]->OnEvent( NDb::EFFECTEVENT_ATTACK, 0.0f );
      }
		}
	}
#endif

	return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFApplSpellProbability::Start()
{
  if (PFBaseApplicator::Start())
    return true;

  if ( !GetWorld() )
    return true;

  float probability = RetrieveParam(GetDB().probability);

  if ( GetWorld()->GetRndGen()->Next(100) < int(probability) )
  {
    Target targ;
		MakeApplicationTarget(targ); // Apply on the same target as this applicator
		CreateDispatch(pAbility, this, targ, targ, GetDB().spell);
  }
  else
  {
    if ( GetDB().spellIfFailed )
    {
      Target targ;
		  MakeApplicationTarget(targ); // Apply on the same target as this applicator
		  CreateDispatch(pAbility, this, targ, targ, GetDB().spellIfFailed);
    }
  }

  return true; // done
}

}

REGISTER_WORLD_OBJECT_NM(PFApplSpellPeriodically,       NWorld);
REGISTER_WORLD_OBJECT_NM(PFApplSpellProbability,        NWorld);
REGISTER_WORLD_OBJECT_NM(PFApplSpellPeriodicallyVisual, NWorld);