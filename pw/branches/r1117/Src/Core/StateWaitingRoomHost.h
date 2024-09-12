#pragma once

#include "CoreFSMState.h"
#include "NetMessageHandler.h"
#include "PacketProcessor.h"
#include "MessagesGeneral.h"
#include "StateNetwork.h"


namespace NCore
{
	namespace GameRoom
	{
		struct ReadyToGamePacket;
	}

	class CoreFSM;

	class WaitingRoomHostState
		: public NetworkState
		, public CoreFSMState
	{
		OBJECT_METHODS( 0x104CCB00, WaitingRoomHostState );
		
		WaitingRoomHostState() {}

		const static int MYSELF_NODE_ID = 0;
		struct NodesManager;
		NodesManager* nodesManager;

		// network handlers
		virtual void ProcessClientAdd( int clientId );
		virtual void ProcessClientRemove( int clientId );
		virtual void ProcessKicked();

		bool clientsAreReady;
		bool ClientConnected( int, GameRoom::ReadyToGamePacket* );
		bool ReadyToStart() const;

		///< map info
		MapStartInfo                  startInfo;
    MapStartInfo::BalanceTeamMode mode;
    int                           selectedHero;
    int                           desiredTeam; 
    int                           humanPlayers;

	protected:
		virtual void SubscribeUpdates();

	public:
    WaitingRoomHostState( CoreFSM*, NNet::IDriver*, const MapStartInfo& startInfo, int selectedHero, int desiredTeam, MapStartInfo::BalanceTeamMode mode, int humanPlayers );
		virtual ~WaitingRoomHostState();
		virtual void Init();
		virtual IBaseFSMState* Step(float);		
	};
}
