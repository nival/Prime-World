#include "stdafx.h"
#include "StateInGameSingle.h"
#include "CoreFSM.h"
#include "MessagesInGame.h"

namespace NCore
{
	InGameStateSingle::InGameStateSingle( CoreFSM *pContext, vector<CObj<CGameNode>>& nodes, int selfNode, const string& map )
		: InGameState( pContext, nodes, selfNode, map )
	{
	}

	//void InGameStateSingle::SubscribeUpdates()
	//{
	//	InGameState::SubscribeUpdates();
	//	Subscribe( &InGameStateSingle::OnAdventureScreenStarted );
	//}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//void InGameStateSingle::OnAdventureScreenStarted(AdventureScreenStarted const& msg)
	//{
	//	transceiver.Init(msg.pWorld, msg.pLoadCmd);
	//	//pContext->PushMessageFromCore( new CreateMap( mapName ) );
	//}
}
