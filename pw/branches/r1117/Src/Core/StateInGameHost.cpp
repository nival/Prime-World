#include "stdafx.h"
#include "StateInGameHost.h"
#include "../Net/NetDriver.h"
#include "GameNode.h"
#include "GameNodeRemote.h"
#include "CoreFSM.h"

#include "MessagesInGame.h"
#include "StateIdle.h"
#include "GameCommand.h"
#include "GameRoomPackets.h"

namespace NCore
{
	InGameHostState::InGameHostState( CoreFSM* context, NNet::IDriver* netDriver,
		vector<CObj<CGameNode>>& nodes, int selfNode, const string& map )
		: NetworkState( netDriver )
		, InGameState( context, nodes, selfNode, map )
	{
		for( int i = nodes.size() - 1; i >= 0; --i )
		{
			if( CGameNodeRemote* node = CDynamicCast<CGameNodeRemote>( nodes[i] ) )
			{
				const ClientId clientId = node->GetClientId();
				remoteNodes[clientId] = node;
			}
		}
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void InGameHostState::ProcessNetMessage( int clientId, CNetPacket* packet )
	{
		if( ProcessPacket( clientId, packet ) )
			return;

		//TODO: check for "i am synced" packet or somesuch, some way to determine the moment when someone is synced

		CDynamicCast<CGameCmd> pGameCommand = packet;
		if ( !IsValid( pGameCommand ) )
		{
			coreLog( NLogg::LEVEL_DEBUG ) << "InGameHostState::ProcessNetMessage - non-game packet" << endl;
			return;
		}

		NodesCollection::iterator it = remoteNodes.find( clientId );
		if ( it != remoteNodes.end() && IsValid( it->second ) )
		{
            //netLog
			//coreLog( NLogg::LEVEL_DEBUG ) << "InGameHostState::ProcessNetMessage - from: " << clientId
			//	<< ", game command: " << pGameCommand->GetObjectTypeName() << " at segment " << pGameCommand->GetSegment() << endl;
			it->second->PushGameCommand( pGameCommand );
		}
		else
		{
			coreLog( NLogg::LEVEL_DEBUG ) << "InGameHostState::ProcessNetMessage - game command from unknown node " << clientId << endl;
		}
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void InGameHostState::ProcessClientAdd( int clientId )
	{
		coreLog( NLogg::LEVEL_DEBUG ) << "InGameHostState::ProcessClientAdd - connect to client " << clientId << endl;

		//TODO: check if it is a reconnection

		//// new client connected, create GameNode
		//CPtr<CGameNodeRemote> node = new CGameNodeRemote( driver, clientId );
		//remoteNodes[clientId] = node;
		//transceiver.Add( node );
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void InGameHostState::ProcessClientRemove( int clientId )
	{
		NodesCollection::iterator it = remoteNodes.find( clientId );
		if ( it != remoteNodes.end() )
		{
			CPtr<NCore::CGameNodeRemote> node = it->second;
			if( IsValid( node ) )
				node->OnDisconnect();

			remoteNodes.erase( it );
			transceiver.Unregister( node );

			pContext->PushMessageFromCore( new ClientDisconnectedMessage( clientId ) );
		}
		else
		{
			coreLog( NLogg::LEVEL_DEBUG ) << "InGameHostState::ProcessClientRemove - trying to disconnect unknown node " << clientId << endl;
		}
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void InGameHostState::ProcessKicked()
	{
		// Should not happen at the moment
		NI_ALWAYS_ASSERT( "InGameHostState::ProcessKicked - should not happen, at least not now" );
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	bool InGameHostState::StartGame( int clientId, GameRoom::ReadyToPlayPacket* packet )
	{
		//// CRAP { need check that meet all requirements
		//pContext->PushMessageFromCore( new CreateMap( mapName ) );
		//// CRAP }
		
		return true;
	}

  bool InGameHostState::OnGamePaused(int clientId, GameRoom::GamePausePacket* packet)
  {
    //NI_ASSERT((transceiver.IsGamePaused() ^ packet->isGamePaused) == 1, "Could not set the pause twice!!!");
    transceiver.ResumeGame();
    return true;
  }
  
	bool InGameHostState::OnNodeReady(int clientId, GameRoom::NodeReadyPacket* packet)
	{
		transceiver.OnNodeReady(packet->iNode);
		return true;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void InGameHostState::Init()
	{
		CoreFSMState::Init();

		REGISTER_PACKET_PROCESSOR( &NCore::InGameHostState::StartGame );
		REGISTER_PACKET_PROCESSOR( &NCore::InGameHostState::OnNodeReady );
    REGISTER_PACKET_PROCESSOR( &NCore::InGameHostState::OnGamePaused );
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	IBaseFSMState* InGameHostState::Step(float dt)
	{
		// process net packets
		ProcessMessages();

		IBaseFSMState* pNewState = NetworkState::Step( pContext );
		return pNewState ? pNewState : InGameState::Step(dt);
	}
}
