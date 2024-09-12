#pragma once

#include "CoreFSMState.h"

namespace NCore
{
	class CoreFSM;
	class CGameNode;

	class GameStateWon
		: public CoreFSMState
	{
		OBJECT_METHODS( 0xCF624CC0, GameStateWon );

	public:
		GameStateWon(CoreFSM *pContext, int _loserFaction);		

	protected:

		virtual void SubscribeUpdates();
		
		// updates handlers
		void OnOk( const struct GameWonOkMessage& );
				
		GameStateWon() {}

    virtual void Init();
    virtual IBaseFSMState *Step(float);

  private:
    bool ok;
    int  loserFaction;
	};
}

