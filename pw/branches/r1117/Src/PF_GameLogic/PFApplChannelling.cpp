#pragma once

#include "stdafx.h"
#include "PFBaseUnit.h"
#include "PFHero.h"
#include "PFAIWorld.h"
#include "PFApplChannelling.h"
#include "PFApplUtils.h"
#include "PFAbilityInstance.h"
#include "PFTargetSelector.h"
#include "AdventureScreen.h"

namespace NWorld
{

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFApplChannelling::Start() 
{ 
  pOwner->AddFlag( NDb::UNITFLAG_FORBIDAUTOATTACK );

  if ( pOwner->IsInChannelling() )
    pOwner->CancelChannelling();

	if ( PFApplBuff::Start() )
  {
    return true; 
  }

	// Calculate strike period
	period = GetDB().period;

	// Just mark that we started
	SetOwnerProgress( 0.0001f );

	// Apply applicators on self
	CreateAndActivateApplicators( GetDB().applicatorsOnSelf, GetAbility(), Target( pReceiver ), this );

	// Attach to base unit as event listener
	pOwner->AddEventListener( this );
  pAbility->GetData()->SubscribeChanneling( this );

	// Create target selector
	if ( GetDB().targetSelector )
  {
    pTargetSelector = GetDB().targetSelector->Create(GetWorld());
  }

	// Activate start spell to targets
	SendSpell2Targets( this, GetDB().startSpell, pTargetSelector );

	// Strike with periodical spell
	timer = 0.0f;
	Strike();

	return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFApplChannelling::Stop() 
{
  pOwner->RemoveFlag( NDb::UNITFLAG_FORBIDAUTOATTACK );
  PFAbilityData* pData = pAbility->GetData();

  // Attach to base unit as event listener
  pOwner->RemoveEventListener( this );
  pData->UnsubscribeChanneling( this );

  if ( IsUnitValid( pReceiver ) ) // if unit is not valid then we're dying
  {
    // Drop all effects on cancel
    if ( ( state == STATE_CANCEL || state == STATE_INTERRUPT ) && GetDB().removeStartSpellEffectOnInterrupt )
    {
      RemoveChildrenApplicators();
      pAbility->Interrupt();
    }

    bool isTargetValid = IsChannelingTargetValid();
    bool fireSpell = ( state == STATE_FIRE || !GetDB().cancelOnInterrupt ) && isTargetValid;
    // Activate spell to targets
    if ( fireSpell )
    {
      Fire();
    }
    else
    {
      Cancel();
    }

    // take mana or drop cooldown if needed
    if ( GetDB().channelingType == NDb::CHANNELINGTYPE_CREATION )
    {
      pAbility->NotifyChannelingCreateStop(fireSpell);

      if ( ( !isTargetValid && state != STATE_INTERRUPT ) || ( state == STATE_CANCEL && GetDB().cancelOnInterrupt ) )
      {
        pData->DropCooldown(false);
      }
      else
      {
        const float manaCost = pData->GetManaCost();
        if ( manaCost > 0.0f )
        {
          if ( pAbility->GetFlags() & NDb::ABILITYFLAGS_CHANNELINGCREATE )
          {
            pData->SpendMana();
          }
          else
          {
            NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Talent %s includes channeling with type creation, but flag ChannelingCreate isn't set!",
              pData->GetDBDesc()->GetDBID().GetFormatted().c_str() ) );
          }
        }
      }
    }
  }

  // Channelling finished
  // if добавил для починки NUM_TASK
  if ( state != STATE_CANCEL && state != STATE_INTERRUPT )
  {
    if(GetStopReason() != APPL_STOP_REASON_ONDEATH)
      pData->NotifyCastProcessed();
    SetOwnerProgress( 0.0f );
  }
  else
  {
    PFApplBuff::SetInterrupted(true);
  }

  PFApplBuff::Stop();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFApplChannelling::Step(float dtInSeconds) 
{
  bool commonBuffStepResult = PFApplBuff::Step( dtInSeconds );

  if ( GetDB().cancelOnDisable && !IsEnabled() )
  {
    SetOwnerProgress(0.0f);
    state = STATE_CANCEL;
  }

  if ( ( state == STATE_CANCEL ) || ( state == STATE_INTERRUPT ) )
  {
    return true;
  }

  if ( commonBuffStepResult )
  {
    state = STATE_FIRE;
    return true;
  }

  SetOwnerProgress( CalculateProgress() );

  // Strike with periodical spell
  timer += dtInSeconds;
  if ( ( period > 0.0f ) && ( timer > period ) )
  {
    timer = fmodf( timer, period );
    Strike();
  }

  return state != STATE_CHANNELLING;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFApplChannelling::Strike()
{
	if ( GetDB().periodicalSpell )
	{
		SendSpell2Targets( this, GetDB().periodicalSpell, pTargetSelector );
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFApplChannelling::Fire()
{
  SendSpell2Targets( this, GetDB().stopSpell, pTargetSelector );
  
  if( GetDB().LoggingEvent >= 0 ) // logging enabled
  {
    StatisticService::RPC::SessionEventInfo params;
    params.intParam1 = NGameX::AdventureScreen::Instance()->GetHero()->GetFaction();
    params.intParam2 = 1; // fire
    NGameX::AdventureScreen::Instance()->LogWorldSessionEvent( (SessionEventType::EventType)GetDB().LoggingEvent, params );
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFApplChannelling::Cancel()
{
  SendSpell2Targets( this, GetDB().cancelSpell, pTargetSelector );
  
  if( GetDB().LoggingEvent >= 0 ) // logging enabled
  {
    StatisticService::RPC::SessionEventInfo params;
    params.intParam1 = NGameX::AdventureScreen::Instance()->GetHero()->GetFaction();
    params.intParam2 = 0; // cancel
    NGameX::AdventureScreen::Instance()->LogWorldSessionEvent( (SessionEventType::EventType)GetDB().LoggingEvent, params );
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float PFApplChannelling::CalculateProgress() const
{
	if (GetLifetime() > 0.0f)
    return (GetLifetime() - GetDuration()) / GetLifetime();
	else
		return 1.0f;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFApplChannelling::SetOwnerProgress(float progress)
{
	CDynamicCast<PFUnitAbilities> pUnitWithAbilitites(pOwner);
	if (pUnitWithAbilitites)
		pUnitWithAbilitites->SetChannellingProgress(progress);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float PFApplChannelling::GetScale() const
{
	return state != STATE_CHANNELLING ? CalculateProgress() : scale;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned int PFApplChannelling::OnEvent(const PFBaseUnitEvent *pEvent)
{
	NI_ASSERT(pEvent, "NULL is not supported");
  const NDb::EBaseUnitEvent& eventType = pEvent->GetType();

  // Для случая когда подписаны в нескольких местах
  if ( state == STATE_CANCEL || state == STATE_INTERRUPT )
    return PFBaseUnitEventListener::FLAGS_REMOVE;

	if ( (GetDB().interruptEvents & ((int64)1 << eventType)) != 0 || eventType == NDb::BASEUNITEVENT_CHANNELINGCANCELED )
	{
    switch ( eventType )
    {
      // these events are considered to be initiated by owner
      case NDb::BASEUNITEVENT_ABILITYSTART:
      case NDb::BASEUNITEVENT_CASTMAGIC:
      case NDb::BASEUNITEVENT_USETALENT:
      case NDb::BASEUNITEVENT_USECONSUMABLE:
      case NDb::BASEUNITEVENT_USEPORTAL:
        // Ignore events about same ability as one that started the channeling
        if ( pEvent->GetAbility() == pAbility )
          return 0;
      case NDb::BASEUNITEVENT_MOVE:
      case NDb::BASEUNITEVENT_ATTACK:
      case NDb::BASEUNITEVENT_ASSIGNTARGET:
      case NDb::BASEUNITEVENT_ISOLATE:
      case NDb::BASEUNITEVENT_PICKUP:
      case NDb::BASEUNITEVENT_CHANNELINGCANCELED:
      case NDb::BASEUNITEVENT_CONSUMABLEOBTAINED:
        state = STATE_CANCEL;
        break;

      // other events are considered to be initiated by hostiles
      default:
        // Check whether event is really hostile
        if ( pEvent->IsEventHostileTo( GetAbilityOwner() ) )
          state = STATE_INTERRUPT;
        break;
    }

    // Ignore if not canceled and not interrupted after all
    if ( state != STATE_CANCEL && state != STATE_INTERRUPT )
      return 0;

    scale = RetrieveParam(GetDB().scaleWhenInterrupted, 1.0f);

    // stop progress immediately to prevent confusing of another state with channelling
    SetOwnerProgress( 0.0f );

    return PFBaseUnitEventListener::FLAGS_REMOVE;
	}
	
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFApplChannelling::IsChannelingTargetValid() const
{
  Target const &abilityTarget = pAbility->GetTarget();

  if ( !abilityTarget.IsValid() )
    return false;

  if ( abilityTarget.IsObject() && !abilityTarget.GetObject()->IsVisibleForFaction( pOwner->GetFaction() ) )
    return false;

  if ( ( pAbility->GetFlags() & NDb::ABILITYFLAGS_CANUSEOUTOFRANGE ) != 0 )
    return true;

  float castAllowRange = RetrieveParam( GetAbility()->GetData()->GetDBDesc()->castAllowRange, 0.0f );

  if ( castAllowRange < EPS_VALUE )
  {
    float rangeCoeff = pOwner->GetWorld()->GetAIWorld()->GetAIParameters().channelingAbilityRangeMultiplier;
    castAllowRange = pAbility->GetData()->GetUseRange() * rangeCoeff;
  }
  return pOwner->IsTargetInRange( abilityTarget, castAllowRange );
}

float PFApplChannelling::GetVariable( const char* varName ) const
{
  if ( strcmp( varName, "Interrupted" ) == 0 )
    return state == STATE_INTERRUPT;

  return Base::GetVariable( varName );
}

}

REGISTER_WORLD_OBJECT_NM(PFApplChannelling, NWorld);
