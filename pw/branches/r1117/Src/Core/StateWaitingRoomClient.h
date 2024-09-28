#pragma once

#include "CoreFSMState.h"
#include "StateNetwork.h"
#include "PacketProcessor.h"
#include "../Net/NetAddress.h"
#include "MessagesGeneral.h"

namespace NCore
{
	namespace GameRoom
	{
		struct ConnectHandshakePacket;
		struct NewClientNotifyPacket;
		struct AcceptConnectionPacket;
		struct RefuseConnectionPacket;
		struct StartGamePacket;
	}

	class CoreFSM;

	/**
	 *	TODO: refactor - split to ConnectingToServerState and client room
	 */
	class WaitingRoomClientState
		: public NetworkState
		, public CoreFSMState
	{
		OBJECT_METHODS( 0x104CCB80, WaitingRoomClientState );
		WaitingRoomClientState() {}

		enum EStage
		{
			STAGE_INIT,
			STAGE_LOGGING_IN,
			STAGE_ACCEPTED,
			STAGE_READY,
			STAGE_FAILED,
			STAGE_START_GAME
		};

		struct ConnectionsManager;
		ConnectionsManager* connectionsManager;		

		EStage stage;
		NNet::CNodeAddress connectTo;
		MapStartInfo startInfo;
    int selectedHero;
    int desiredTeam;
    int connectionAttempt;

		// network handlers
		virtual void ProcessClientAdd( int clientId );
		virtual void ProcessClientRemove( int clientId );
		virtual void ProcessKicked();

		bool Handshake( int, GameRoom::ConnectHandshakePacket* );
		bool NewClientNotify( int, GameRoom::NewClientNotifyPacket* );
		bool ConnectAccepted( int, GameRoom::AcceptConnectionPacket* );
		bool ConnectRefused( int, GameRoom::RefuseConnectionPacket* );
		bool StartGame( int, GameRoom::StartGamePacket* );

	protected:
		virtual void SubscribeUpdates();

	public:
		WaitingRoomClientState( CoreFSM*, NNet::IDriver*, const NNet::CNodeAddress&, int selectedHero, int desiredTeam);
		virtual ~WaitingRoomClientState();
		virtual IBaseFSMState* Step(float);
		virtual void Init();
	};
}
