#pragma once

#include "CoreFSMState.h"
#include "NetMessageHandler.h"
#include "StateNetwork.h"

namespace NCore
{
	class CoreFSM;

	class CreatingGameState
		: public NetworkState
		, public CoreFSMState
	{
		OBJECT_METHODS( 0x104CCC00, CreatingGameState );
		
		CreatingGameState() {}

		// network handlers
		virtual void ProcessNetMessage( int clientId, CNetPacket* packet );
		virtual void ProcessClientAdd( int clientId );
		virtual void ProcessClientRemove( int clientId );
		virtual void ProcessKicked();

	protected:
		void SubscribeUpdates();

	public:
		CreatingGameState( CoreFSM*, NNet::IDriver* );
		virtual IBaseFSMState* Step(float);
	};
}
