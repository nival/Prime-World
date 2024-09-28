#include "stdafx.h"
#include "CoreFSM.h"
#include "StateGameWon.h"
#include "StateIdle.h"
#include "MessagesInGame.h"

namespace NCore
{
	GameStateWon::GameStateWon( CoreFSM *pContext, int _loserFaction )
		: CoreFSMState( pContext )
    , ok(false)
    , loserFaction(_loserFaction)
	{
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  void GameStateWon::Init()
  {
    CoreFSMState::Init();
    pContext->RegisterMessageBuilder( GetTypeId(), &NCore::GameStateWonState::NewGameStateWonState );
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void GameStateWon::SubscribeUpdates()
	{
		CoreFSMState::SubscribeUpdates();

		Subscribe( &GameStateWon::OnOk );
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void GameStateWon::OnOk( const struct GameWonOkMessage& )
	{
		ok = true;
	}

	IBaseFSMState* GameStateWon::Step(float dt)
	{
		if (ok)
			return new CStateIdle( pContext );

    static bool first = true;
    if (first)
    {
      GetGlobalGameFSM()->PushMessageFromCore(new GameShowWonMessage(loserFaction) );
      first = false;
    }

		return 0;
	}
}

