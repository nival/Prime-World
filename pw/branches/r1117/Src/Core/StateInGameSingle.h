#pragma once

#include "StateInGame.h"

namespace NCore
{
	class InGameStateSingle
		: public InGameState
	{
		OBJECT_METHODS( 0x9A532BC0, InGameStateSingle );
		InGameStateSingle() {}

		// /virtual void SubscribeUpdates();
		//void OnAdventureScreenStarted(struct AdventureScreenStarted const& msg);
	public:
		InGameStateSingle( CoreFSM *pContext, vector<CObj<CGameNode>>& nodes, int selfNode, const string& map );
	};
}
