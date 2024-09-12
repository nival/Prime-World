#include "stdafx.h"
#include "StateWaitingRoomClient.h"
#include "CoreFSM.h"
#include "../Net/NetDriver.h"
#include "GameRoomPackets.h"
#include "StateLobby.h"
#include "MessagesGeneral.h"

#include "MessagesInGame.h"
#include "GameNodeRemote.h"
#include "StateInGameHost.h"
#include "StateIdle.h"

namespace NCore
{
	struct WaitingRoomClientState::ConnectionsManager
	{
		typedef vector<ConnectionDescriptor> Connections;
		Connections nodes;
		int myselfNodeId;
		int hostClientId;
		list<int> pendingClients;

		//bool 
		void AddConnectedNode( int clientId, int nodeId, const string& ip, int port )
		{
			ConnectionDescriptor connection;
			connection.clientId = clientId;
			if ( clientId >= 0 )
			{
				connection.ip = ip;
				connection.port = port;
				connection.connected = true;
			}
			connection.nodeId = nodeId;

			nodes.push_back( connection );
		}

		void AddUnconnectedNode( int nodeId, const string& ip, int port )
		{
			bool found = false;
			for ( Connections::iterator it = nodes.begin(); it != nodes.end(); ++it )
			{
				ConnectionDescriptor &connection = *it;
				if ( connection.nodeId == nodeId )
				{
					found = true;
					break;
				}
				else if ( connection.ip == ip && connection.port == port )
				{
					found = true;
          if(connection.nodeId == -1)
          {
            connection.connected = false;
          }
					connection.nodeId = nodeId;
					break;
				}
			}

			if ( found )
				return;

			ConnectionDescriptor connection;

			connection.nodeId = nodeId;
			connection.ip = ip;
			connection.port = port;
			if ( nodeId == myselfNodeId )
				connection.connected = true;
			nodes.push_back( connection );

			//TryToConnectTo( szIP, nPort );
		}

    ConnectionDescriptor * GetDescriptorByNodeId(int nodeId)
    {
      int nI;
      for(nI = 0; nI < nodes.size(); nI++)
      {
        if(nodes[nI].nodeId == nodeId)
        {
          return &(nodes[nI]);
        }
      }
      return NULL;
    }

		void RemoveConnection( int clientId )
		{
			// Remove from pending clients (if any)
			for ( list<int>::iterator it = pendingClients.begin(); it != pendingClients.end(); ++it )
			{
				if ( *it == clientId )
				{
					it = pendingClients.erase( it );
					break;
				}
			}

			// Remove from nodes
			for ( Connections::iterator it = nodes.begin(); it != nodes.end(); ++it )
			{
				ConnectionDescriptor &node = *it;
				if ( node.clientId == clientId )
				{
					nodes.erase( it );
					break;
				}
			}
		}

		bool AreAllConnected()
		{
			int connected = 0;
			for ( Connections::iterator it = nodes.begin(); it != nodes.end(); ++it )
			{
				ConnectionDescriptor &node = *it;
				if ( !node.connected || node.nodeId < 0 )
				{
					//return;
				}
				else
					++connected;
			}
			
			//coreLog( NLogg::LEVEL_DEBUG ) << "CStateConnectingToGame::CheckAllConnected: " << nConnected << " out of " << nodes.size() << endl;
			
			if ( connected < nodes.size() )
				return false;

			return true;
		}
	};

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	WaitingRoomClientState::WaitingRoomClientState( CoreFSM* context, NNet::IDriver* netDriver, const NNet::CNodeAddress& address, int selectedHero, int desiredTeam )
		: NetworkState( netDriver )
		, CoreFSMState( context ) 
		, connectionsManager( new ConnectionsManager() )
		, connectTo( address )
		, stage( STAGE_INIT )
    , selectedHero(selectedHero)
    , desiredTeam(desiredTeam)
    , connectionAttempt(0)
	{
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	WaitingRoomClientState::~WaitingRoomClientState()
	{		
		delete connectionsManager;
		connectionsManager = 0;
	}
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void WaitingRoomClientState::Init()
	{
		CoreFSMState::Init();
		
		// start Connecting
		GetDriver()->ConnectGame( connectTo, MemoryStream() );
		stage = STAGE_LOGGING_IN;

    connectionAttempt = 0;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void WaitingRoomClientState::SubscribeUpdates()
	{
		CoreFSMState::SubscribeUpdates();

		pContext->RegisterMessageBuilder( GetTypeId(), &NCore::Waiting::NewWaiting );

		// TODO: Register message processor for CANCEL
		REGISTER_PACKET_PROCESSOR( &NCore::WaitingRoomClientState::ConnectAccepted );
		REGISTER_PACKET_PROCESSOR( &NCore::WaitingRoomClientState::ConnectRefused );
		REGISTER_PACKET_PROCESSOR( &NCore::WaitingRoomClientState::Handshake );
		REGISTER_PACKET_PROCESSOR( &NCore::WaitingRoomClientState::NewClientNotify );
		REGISTER_PACKET_PROCESSOR( &NCore::WaitingRoomClientState::StartGame );		
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void WaitingRoomClientState::ProcessClientAdd( int clientId )
	{
		struct Stage2String
		{
			string operator() ( EStage stage ) const
			{
				if( stage == STAGE_INIT )
					return "STAGE_INIT";
				else if( stage == STAGE_LOGGING_IN )
					return "STAGE_LOGGING_IN";
				else if( stage == STAGE_ACCEPTED )
					return "STAGE_ACCEPTED";
				else if( stage == STAGE_FAILED )
					return "STAGE_FAILED";
        else if( stage == STAGE_READY)
          return "STAGE_READY";
        else if( stage == STAGE_START_GAME)
          return "STAGE_START_GAME";
				else
					return "unknown";
			}
		};

		coreLog( NLogg::LEVEL_DEBUG ) << "WaitingRoomClientState::ProcessClientAdd, clientId: " << clientId
			<< ", ip: " << GetDriver()->GetIP( clientId ) << ", port: " << GetDriver()->GetPort( clientId )
			<< ", current stage: " << Stage2String()( stage ) << endl;
		
		if ( stage == STAGE_LOGGING_IN )
		{
			connectionsManager->pendingClients.push_back( clientId );
		}
		else
		{
			NetMessagesProcessor::Send( GetDriver(), clientId, new GameRoom::ConnectHandshakePacket( connectionsManager->myselfNodeId ) );
		}

    pContext->PushMessageFromCore(new WaitingRoomClientAdd(GetDriver()->GetIP( clientId )));
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void WaitingRoomClientState::ProcessClientRemove(int clientId)
	{
		coreLog( NLogg::LEVEL_DEBUG ) << "WaitingRoomClientState::ProcessClientRemove( " << clientId << " )" << endl;

    if(pContext && connectionsManager && clientId >= 0 && clientId < connectionsManager->nodes.size())
    {
      //basically we may try to remove client that is not connected to us yet, therefore wee need to take all precautions
      pContext->PushMessageFromCore(new WaitingRoomClientRemove(connectionsManager->nodes[clientId].ip));
    }
		connectionsManager->RemoveConnection(clientId);
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	bool WaitingRoomClientState::Handshake( int clientId, GameRoom::ConnectHandshakePacket* packet )
	{
		coreLog( NLogg::LEVEL_DEBUG ) 
			<< "WaitingRoomClientState::Handshake( id:" << clientId << ", node: " << packet->nNode << " )" << endl;

		if ( stage == STAGE_LOGGING_IN )
		{
			for ( list<int>::iterator it = connectionsManager->pendingClients.begin(); it != connectionsManager->pendingClients.end(); ++it )
			{
				if ( *it != clientId )
					continue;

				connectionsManager->AddConnectedNode( *it, packet->nNode, GetDriver()->GetIP( clientId ), GetDriver()->GetPort( clientId ) );
				connectionsManager->pendingClients.erase( it );
				break;
			}
		}
		else
		{
			bool found = false;
			for ( ConnectionsManager::Connections::iterator it = connectionsManager->nodes.begin(); it != connectionsManager->nodes.end(); ++it )
			{
				ConnectionDescriptor &node = *it;
				if ( node.nodeId != packet->nNode )
					continue;

				if ( !found )
				{
					node.clientId = clientId;
					node.connected = true;
					node.ip = GetDriver()->GetIP( clientId );
					node.port = GetDriver()->GetPort( clientId );
					found = true;
				}
				else
				{
					it = connectionsManager->nodes.erase( it );
				}
			}

			if ( !found )
				connectionsManager->AddConnectedNode( clientId, packet->nNode, GetDriver()->GetIP( clientId ), GetDriver()->GetPort( clientId ) );
		}
		return true;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	bool WaitingRoomClientState::NewClientNotify(int clientId, GameRoom::NewClientNotifyPacket* packet)
	{
		//const string& ip = packet->szIP;
		//const int port = packet->nPort;

		// connect to node
    bool bFound = false;
    for ( ConnectionsManager::Connections::iterator it = connectionsManager->nodes.begin(); it != connectionsManager->nodes.end(); ++it )
    {
      ConnectionDescriptor &node = *it;
      if ( node.nodeId != packet->nNode )
        continue;
      bFound = true;
    }
    if(!bFound)
    {
      stage = STAGE_ACCEPTED;
      ConnectionDescriptor desc;
      desc.nodeId = packet->nNode;
      connectionsManager->nodes.push_back(desc);
    }

		return true;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	bool WaitingRoomClientState::ConnectAccepted( int clientId, GameRoom::AcceptConnectionPacket* packet )
	{
		coreLog( NLogg::LEVEL_DEBUG ) << "WaitingRoomClientState::ConnectAccepted( " << clientId << " ): "
			<< " my node = " << packet->nNode << ", " << packet->nodes.size() << " nodes to connect to" << endl;

		connectionsManager->myselfNodeId = packet->nNode;
		connectionsManager->hostClientId = clientId;
		
		const int myClientId = GetDriver()->GetSelfClientID();
		connectionsManager->AddConnectedNode( myClientId, connectionsManager->myselfNodeId,
			GetDriver()->GetIP( myClientId ), GetDriver()->GetPort( myClientId ) );

		// Send my nodeID info to all pending clients
		for ( list<int>::iterator it = connectionsManager->pendingClients.begin(); it != connectionsManager->pendingClients.end(); ++it )
		{
			const int clientId = *it;
			connectionsManager->AddConnectedNode( clientId, -1, GetDriver()->GetIP( clientId ), GetDriver()->GetPort( clientId ) );
			if ( connectionsManager->hostClientId != clientId )
			{
				Send( clientId, new GameRoom::ConnectHandshakePacket( connectionsManager->myselfNodeId ) );
        coreLog( NLogg::LEVEL_DEBUG ) << "Packet GameRoom::ConnectHandshakePacket sent to client " << clientId << "." << endl;
			}
		}
		connectionsManager->pendingClients.clear();

		// Fill nodes
		for ( int i = 0; i < packet->nodes.size(); ++i )
		{
			connectionsManager->AddUnconnectedNode( packet->nodes[i].nNode, packet->nodes[i].szIP, packet->nodes[i].nPort );
		}

		stage = STAGE_ACCEPTED;
		return true;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	bool WaitingRoomClientState::ConnectRefused( int clientId, GameRoom::RefuseConnectionPacket* packet )
	{
		stage = STAGE_FAILED;
		return true;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	bool WaitingRoomClientState::StartGame( int clientId, GameRoom::StartGamePacket* pPacket )
	{
		NI_VERIFY( pPacket && !pPacket->startInfo.mapName.empty(), "Invalid parameters!", stage = STAGE_FAILED; return false; );
    NI_ASSERT(stage == STAGE_READY, "Start game recieved in unexpected stage");

		stage = STAGE_START_GAME;
		startInfo = pPacket->startInfo;
		return true;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void WaitingRoomClientState::ProcessKicked()
	{
		stage = STAGE_FAILED;

		//TODO: report reason
	}
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	IBaseFSMState* WaitingRoomClientState::Step(float)
	{
		// process net packets
		ProcessMessages();
    pContext->PushMessageFromCore(new WaitingRoomClientStateMessage(connectionsManager->nodes));

		if ( stage == STAGE_ACCEPTED && connectionsManager->AreAllConnected() )
		{
			stage = STAGE_READY;
			Send( connectionsManager->hostClientId, new GameRoom::ReadyToGamePacket(selectedHero, desiredTeam) );
      coreLog( NLogg::LEVEL_DEBUG ) << "Packet GameRoom::ReadyToGamePacket sent to server " << connectionsManager->hostClientId << "." << endl;
		}
		if( stage == STAGE_START_GAME )
		{
			// create nodes
			const int myNodeID = connectionsManager->myselfNodeId;
			vector< CObj<CGameNode> > allNodes;
			vector<PlayerInfo> localNodes;

			// initialize human players
			for(int i = 0; i < startInfo.playersInfo.size(); ++i )
			{
        const int nodeIndex = allNodes.size();
        if(nodeIndex >= connectionsManager->nodes.size())
          continue;

				ConnectionDescriptor& descriptor = connectionsManager->nodes[nodeIndex];
				if( !descriptor.connected )
					continue;

        CGameNode* node = (nodeIndex == myNodeID) ? new CGameNode("local") : new CGameNodeRemote( GetDriver(), nodeIndex, (connectionsManager->GetDescriptorByNodeId(nodeIndex) != NULL)? connectionsManager->GetDescriptorByNodeId(nodeIndex)->ip.c_str(): "Unknown");
				allNodes.push_back( node );
			}

      const GameStartInfo info = { allNodes, startInfo };
			pContext->PushMessageFromCore(new GameStartedMessage(info));

      //Send( connectionsManager->hostClientId, new GameRoom::ReadyToPlayPacket());
      //coreLog( NLogg::LEVEL_DEBUG ) << "Packet ReadyToPlayPacket was send to host " << desc->clientId << endl;

      return new InGameHostState( pContext, GetDriver(), allNodes, myNodeID, startInfo.mapName );
		}
		else if ( stage == STAGE_FAILED )
		{
      if(connectionAttempt > 100)
      {
			  //TODO report failure
			  coreLog( NLogg::LEVEL_DEBUG ) << "*** Connecting failed " << typeid( this ).name() << endl;
			  return new CStateIdle( pContext );
      }
      else
      {
        connectionAttempt += 1;
        coreLog( NLogg::LEVEL_DEBUG ) << "*** Connecting failed " << typeid( this ).name() <<" attempting to reconnect. Attempt " << connectionAttempt << "." << endl;
        //try to connect again
        GetDriver()->ConnectGame(connectTo, MemoryStream());
        stage = STAGE_LOGGING_IN;
      }
		}

		return NetworkState::Step( pContext );
	}
}
