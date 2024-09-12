#pragma once
#include "StateInGame.h"
#include "NetMessageHandler.h"
#include "NetMessagesProcessor.h"
#include "GameNodeRemote.h"
#include "PacketProcessor.h"
#include "StateNetwork.h"

namespace NCore
{
	namespace GameRoom
	{
		struct ReadyToPlayPacket;
		struct NodeReadyPacket;
    struct GamePausePacket;
	}

	class InGameHostState
		: public NetworkState
		, public InGameState
	{
		OBJECT_METHODS( 0x104CC480, InGameHostState );

		InGameHostState() {}

		typedef int ClientId;
		typedef hash_map<ClientId, CPtr<CGameNodeRemote>> NodesCollection;
		NodesCollection remoteNodes;

		// network handlers
		virtual void ProcessNetMessage( int clientId, CNetPacket* packet );
		virtual void ProcessClientAdd( int clientId );
		virtual void ProcessClientRemove( int clientId );
		virtual void ProcessKicked();

		bool StartGame( int, GameRoom::ReadyToPlayPacket* );

		bool OnNodeReady(int, GameRoom::NodeReadyPacket* );
    bool OnGamePaused(int, GameRoom::GamePausePacket* );

	public:
		InGameHostState( CoreFSM*, NNet::IDriver*, vector<CObj<CGameNode>>&, int selfNode, const string& map );
		virtual IBaseFSMState* Step(float dt);
		virtual void Init();
	};
}
