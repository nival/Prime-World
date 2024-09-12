#include "stdafx.h"
#include "CoreFSMState.h"
#include "CoreFSM.h"

namespace NCore
{
	void CoreFSMState::SubscribeUpdates()
	{
		NI_VERIFY( IsValid( pContext ), "Invalid FSM context!", return; );
		pContext->RegisterProcessorToCore( this );
	};

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void CoreFSMState::Init()
	{
		SubscribeUpdates();
	}
}