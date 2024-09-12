#include "stdafx.h"
#include "PFBaseAIController.h"
#include "PFAIHelper.h"
#include "PFMaleHero.h"
#include "PFAIStates.h"
#include "Core/Scheduler.h"

namespace NWorld
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PFBaseAIController::PFBaseAIController(PFBaseHero * _hero, NCore::ITransceiver * transceiver)
: aiHelper(_hero, transceiver)
, isDead(true)  // The hero is "dead" initially and respawns when session starts
{
  hero = dynamic_cast<PFBaseMaleHero*>( _hero );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseAIController::Step( float timeDelta )
{
  if ( hero->IsDead() )
  {
    if ( !isDead )
    {
      // Just dead
      isDead = true;
      OnDie();
    }
  }
  else
  {
    if ( isDead )
    {
      // Just respawned
      isDead = false;
      OnRespawn();
    }
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AIBaseState* PFBaseAIController::CurrentState()
{
  return dynamic_cast<AIBaseState*>( GetCurrentState() );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char* PFBaseAIController::GetCurrentStateName()
{
  AIBaseState* state = CurrentState();
  return state ? PFAIStatesEnum_ToString(state->stateType) : PFAIStatesEnum_ToString(NONE);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PFWorld * PFBaseAIController::GetWorld()
{
  return IsValid(hero) ? hero->GetWorld() : 0;
};

} // namespace NWorld
