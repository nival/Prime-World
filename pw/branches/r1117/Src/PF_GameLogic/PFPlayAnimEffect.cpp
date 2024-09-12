#pragma once

#include "stdafx.h"
#include "PFCreature.h"
#include "PFClientCreature.h"
#include "PFPlayAnimEffect.h"

namespace NGameX
{

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFPlayAnimEffect::Apply(CPtr<PF_Core::ClientObjectBase> const &pUnit)
{
	NI_DATA_VERIFY(GetDBEffect().animGraphNode.size(), 
		             NStr::StrFmt("No animation name in effect %s", GetDBEffect().GetDBID().GetFileName().c_str()), 
								 return; );

	pOwner    = dynamic_cast<PFClientBaseUnit *> (pUnit.GetPtr());
	pAnimated = dynamic_cast<IAnimatedClientObject*>(pUnit.GetPtr());
	NI_DATA_VERIFY(NULL != pAnimated && IsValid(pOwner),
								 NStr::StrFmt("Effect %s could be applied on animated objects only", GetDBEffect().GetDBID().GetFileName().c_str()), 
								 return; );

	// Remember state ID to return
	returnStateId = pAnimated->GetCurrentStateId();

	unsigned int stateId = pAnimated->GetStateIdByName(GetDBEffect().animGraphNode.c_str());

  if ( stateId == DIANGR_NO_SUCH_ELEMENT )
  {
    DebugTrace( NStr::StrFmt("Bad animation name '%s' in effect %s", GetDBEffect().animGraphNode.c_str(), GetDBEffect().GetDBID().GetFileName().c_str()) );
    return;
  }

	pAnimated->SetAnimStateId(stateId);
	
	if (GetDBEffect().marker.size())
		pAnimated->ReachStateMarker(GetDBEffect().marker.c_str(), GetDBEffect().markerReachTime);

	if ( pUnit->GetSceneObject() )
		pUnit->GetSceneObject()->UpdateForced(0.1f, false, pOwner->IsVisible());
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFPlayAnimEffect::Die()
{
	if (!IsValid(pOwner) || !pAnimated )
	{
		BasicEffect::DieImmediate();
		return;
	}

	if (GetDBEffect().goToOtherNodeOnStop && !pOwner->WorldObject()->IsDead() && !IsInterrupted())
	{
		if (GetDBEffect().returnAnimGraphNode.size())
		{
			unsigned int stateId = pAnimated->GetStateIdByName(GetDBEffect().returnAnimGraphNode.c_str());

      if ( stateId == DIANGR_NO_SUCH_ELEMENT )
      {
        DebugTrace( NStr::StrFmt("Bad animation name '%s' in effect %s", GetDBEffect().returnAnimGraphNode.c_str(), GetDBEffect().GetDBID().GetFileName().c_str()) );
        return;
      }

      if ( pAnimated->GetNextStateId() != stateId )
      {
        pAnimated->SetAnimStateId( stateId );
      }
		}
		else
		{
			if (returnStateId != DIANGR_NO_SUCH_ELEMENT)
				pAnimated->SetAnimStateId(returnStateId);
		}
	}
  BasicEffect::Die();
}

void PFPlayAnimEffect::DieImmediate()
{ 
  pOwner    = 0;
  pAnimated = 0;

  BasicEffect::DieImmediate();
}
}