#include "stdafx.h"
#include "SceneComponent.h"
#include "TimeController.h"
#include "../System/RandomGen.h"
#include "TraceSceneComponent.h"

namespace NScene
{

bool HasChildWithFadeOut( SceneComponent* rootsc )
{
  struct Trav
  {
    bool hasChildWithFadeOut;

    Trav() : hasChildWithFadeOut(false) {}

    bool IsTraversable(const SceneComponent* comp) const
    {
      return comp->IsTraversable();
    }
    bool NeedToProcess(const SceneComponent* comp) const
    {
      return true;
    }
    void operator()(SceneComponent *pSC) 
    { 
      if ( dynamic_cast<TraceSceneComponent*>(pSC) )
        return;

      if ( !pSC->GetTimeControllerDesc().IsEmpty() && pSC->GetTimeControllerDesc()->fadeout > 0.0f )
        hasChildWithFadeOut = true;
      if ( !pSC->Ready2Die() )
        hasChildWithFadeOut = true;
    }
  } f;

  SceneComponent* itFront = rootsc->GetChild();
  if ( itFront )
  {
    SceneComponent* it = itFront;
    do
    {
      it->Traverse( f );
      it = it->GetBrother();
    } while ( it && it != itFront );
  }

  return f.hasChildWithFadeOut || !rootsc->Ready2Die();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TimeController::Update(SceneComponent &sc, float timeAdvance, float &timeDelta) // Returns true if time was looped
{
  // Simple case
	if (!pDBData)
	{
		timeDelta = timeAdvance * speed;
		time += timeDelta;
    if ( tryToFinish && !HasChildWithFadeOut(&sc) )
    {
      sc.DisableStrong(true);
      tryToFinish = false;
    }
		return;
	}

	timeDelta = timeAdvance * speed + timeOffset;
	timeOffset = 0.f; // used for one-time offset
  float oldTime = time;
	time += timeDelta;

	// Activate scene component when time comes
	if (oldTime < 0.0f)
	{
		if (time >= 0.0f)
		{
			sc.EnableWeak(true);
			float offset = GenerateFirstCycleOffset();
      time += offset;
			timeDelta += offset;
		}
		else
		{
			timeDelta = 0.0f;
			return;
		}
	} 

	// Calculate cycle length
	float fadeTime = pDBData->fadein + pDBData->fadeout;
	float cycleLength;
	if (pDBData->cycleLength > 0.0f)
		cycleLength = pDBData->cycleLength;
	else
		cycleLength = pureAnimationLength - fadeTime;

	// Live forever if cycleLength = 0
	if (cycleLength == 0.0f)
		return;

	if (time > (pDBData->fadein + cycleLength) && numCycles2Loop > 0)
	{
		int cycles2Skip = int( (time - pDBData->fadein) / cycleLength );
		float time2Dec = cycleLength * cycles2Skip;

		float time2StartWith = oldTime - time2Dec;
		if (time2StartWith < 0.0f)
		{
			timeDelta += time2StartWith;
			time2StartWith = 0.0f;
		}
		
		sc.OnTimeLooped(time2StartWith);

		time -= time2Dec;
		numCycles2Loop -= cycles2Skip;
		if (numCycles2Loop < 0)
			numCycles2Loop = 0;
	}

	if (time > (pDBData->fadein + cycleLength + pDBData->fadeout) && !sc.IsStronglyDisabled() && !HasChildWithFadeOut(&sc))
	{
		sc.DisableStrong(true); // Disable component forever!
    tryToFinish = false;
	} 
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TimeController::Reinit(SceneComponent &sc) 
{
  tryToFinish = false;
  if (!pDBData)
	{
		time = 0.0f;
		speed = 1.0f;
		numCycles2Loop = -1;
		return;
	}
	
	if (pDBData->cycleCount > 0)
		numCycles2Loop = pDBData->cycleCount - 1;
	else
		numCycles2Loop = 0x7FFFFFFF; // Infinity =)

	speed = pDBData->speed;

	if (pDBData->startDelay > 0.0f)
	{
		sc.EnableWeak(false);
		time = -pDBData->startDelay;
	}
	else
  {
		time = 0.f;
    timeOffset = GenerateFirstCycleOffset();
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TimeController::Finish(SceneComponent &sc)
{
	numCycles2Loop = 0;
	if (!(pDBData && pDBData->fadeout > 0.0f) && !HasChildWithFadeOut(&sc))
  {
		sc.DisableStrong(true);
    tryToFinish = false;
  }
  else
    tryToFinish = true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float TimeController::EvaluateAnimLength( const SceneComponent &sc ) const
{
	if (!pDBData)
		return pureAnimationLength;

	float fadeTime = pDBData->fadein + pDBData->fadeout;
	float cycleLength; 
	if (pDBData->cycleLength > 0.0f)
		cycleLength = pDBData->cycleLength;
	else
		cycleLength = pureAnimationLength - fadeTime;

  float cycleCount = pDBData->cycleCount > 0 ? pDBData->cycleCount : 1;

  float parentDelay = 0.0f;
  if ( sc.GetParent() && IsValid( sc.GetParent()->GetTimeControllerDesc() ) )
  {
    parentDelay = sc.GetParent()->GetTimeControllerDesc()->startDelay;
  }

  return parentDelay / sc.GetParentSpeedCoeff() + (pDBData->startDelay + fadeTime + cycleLength * cycleCount) / speed;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TimeController::ResetSpeed()
{
	speed = pDBData ? pDBData->speed : 1.0f;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float TimeController::GenerateFirstCycleOffset()
{
  if (!pDBData || pDBData->firstCycleOffset < 0.f)
    return 0.f;

  if (pDBData->firstCycleOffsetDelta > 0.f)
  {
    return NRandom::Random(Max(pDBData->firstCycleOffset - pDBData->firstCycleOffsetDelta, 0.f), pDBData->firstCycleOffset + pDBData->firstCycleOffsetDelta);
  }
  return pDBData->firstCycleOffset;
}

void TimeController::SetPureAnimationLength( float length )
{
	NI_ASSERT( length<1000.0f, NStr::StrFmt( "Bad animation length %s", pDBData ? pDBData->GetDBID().GetFileName() : "none") );
  pureAnimationLength = length;
}
}