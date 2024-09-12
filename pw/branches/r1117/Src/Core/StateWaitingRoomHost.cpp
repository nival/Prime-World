#include "stdafx.h"
#include "StateWaitingRoomHost.h"
#include "CoreFSM.h"
#include "../Net/NetDriver.h"
#include "GameRoomPackets.h"
#include "StateInGameHost.h"

#include "MessagesGeneral.h"
#include "MessagesInGame.h"
#include "WorldBase.h"

#include "../System/nalgoritm.h"

namespace NCore
{
	struct WaitingRoomHostState::NodesManager
	{
		typedef vector<NodeDescriptor> NodesInRoom;
		NodesInRoom nodes;
		int nodesHighLimit;
    int nodesLowLimit;

		int CountNodes() const
		{
			int count = 0;
			for ( int i = nodes.size() - 1; i >= 0; --i )
			{
				if ( nodes[i].present )
					++count;
			}

			return count;
		}

    bool IsAllPresentNodesConnectedToOthers() const
    {
      for ( int i = nodes.size() - 1; i >= 0; --i )
      {
        if ( nodes[i].present && !nodes[i].connectedToOthers )
          return false;
      }
      return true;
    }

		bool IsAllNodesConnected() const
		{
      //count present nodes
      int nPresentNodesCount = 0;
      for(int i = nodes.size() - 1; i >= 0; --i)
      {
        if(nodes[i].present)
        {
          nPresentNodesCount += 1;
        }
      }
      if(nPresentNodesCount < (nodesLowLimit + 1))
      {
        return false;
      }
      return IsAllPresentNodesConnectedToOthers();
		}

		bool CanAcceptNewNode() const
		{
			return (CountNodes() <= nodesHighLimit) && IsAllPresentNodesConnectedToOthers();
		}

		CNetPacket* ComposeAcceptPacket( int clientId ) const
		{
			GameRoom::AcceptConnectionPacket *packet = new GameRoom::AcceptConnectionPacket();
			packet->nNode = clientId;

			packet->nodes.resize( CountNodes() );
			int j = 0;
			for ( int i = nodes.size() - 1; i >= 0; --i )
			{
				if ( !nodes[i].present )
					continue;

				packet->nodes[j].nNode = i;
				packet->nodes[j].szIP = nodes[i].ip;
				packet->nodes[j].nPort = nodes[i].port;
				++j;
			}

			return packet;
		}
		
		int AssignNewNode( int clientId, const string& ip, int port )
		{
			coreLog( NLogg::LEVEL_DEBUG ) << "AssignNewNode( " << clientId << " ), ip = " << ip << ":" << port << endl;

			int newNode = -1;
			for ( int i = 1; i < nodes.size(); ++i )
			{
				if ( nodes[i].present )
					continue;

				newNode = i;
				break;
			}

			if ( newNode < 0 )
			{
				newNode = nodes.size();
				nodes.resize( nodes.size() + 8 );
			}

			nodes[newNode].present = true;
			nodes[newNode].connectedToOthers = false;
			nodes[newNode].clientId = clientId;
			nodes[newNode].port = port;
			nodes[newNode].ip = ip;			

			return newNode;
		}

		void RemoveNode( int clientId )
		{
			for ( int i = nodes.size() - 1; i > MYSELF_NODE_ID; --i )
			{
				if ( nodes[i].clientId != clientId )
					continue;

				nodes[i].present = false;
				nodes[i].clientId = -1;
				return;
			}
		}
	};

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	WaitingRoomHostState::WaitingRoomHostState( CoreFSM* context, NNet::IDriver* netDriver, const MapStartInfo& _startInfo, int selectedHero, int desiredTeam, MapStartInfo::BalanceTeamMode mode, int humanPlayers )
		: NetworkState( netDriver )
		, CoreFSMState( context )
		, nodesManager( new NodesManager() )
		, clientsAreReady( false )
		, startInfo( _startInfo )
    , selectedHero( selectedHero )
    , desiredTeam( desiredTeam )
    , mode( mode )
    , humanPlayers( humanPlayers )
	{
		GetDriver()->StartGame();
		GetDriver()->StartNewPlayerAccept();
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	WaitingRoomHostState::~WaitingRoomHostState()
	{
		delete nodesManager;
		nodesManager = 0;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void WaitingRoomHostState::SubscribeUpdates()
	{
		CoreFSMState::SubscribeUpdates();
		pContext->RegisterMessageBuilder( GetTypeId(), &NCore::Waiting::NewWaiting );

		REGISTER_PACKET_PROCESSOR( &WaitingRoomHostState::ClientConnected );
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void WaitingRoomHostState::Init()
	{
		CoreFSMState::Init();

		// Init my node (clientId == MYSELF_NODE_ID)
		nodesManager->nodes.resize( 16 );

    NodeDescriptor& myNode   = nodesManager->nodes[MYSELF_NODE_ID];

		myNode.present           = true;
		myNode.connectedToOthers = true;
		myNode.ip                = GetDriver()->GetIP( GetDriver()->GetSelfClientID() );
		myNode.port              = GetDriver()->GetPort( GetDriver()->GetSelfClientID() );
    myNode.teamId            = desiredTeam;
		
    const int maxNodes = max(0, startInfo.CountValidPlayers() - 1);

    nodesManager->nodesHighLimit = maxNodes;
    nodesManager->nodesLowLimit  = (0 < humanPlayers) ? max(0, min(humanPlayers - 1, maxNodes ) ) : maxNodes;
		
		NI_ASSERT( 0 < nodesManager->nodesHighLimit, NStr::StrFmt( "Can't play map (%s) in multiplayer mode!", startInfo.mapName.c_str() ) );
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	bool WaitingRoomHostState::ClientConnected( int clientId, GameRoom::ReadyToGamePacket* message )
	{
		nodesManager->nodes[clientId].connectedToOthers = true;
    nodesManager->nodes[clientId].heroId = message->heroId;
    nodesManager->nodes[clientId].teamId = message->teamId;
		clientsAreReady = nodesManager->IsAllNodesConnected();

    pContext->PushMessageFromCore(new WaitingRoomClientAdd(nodesManager->nodes[clientId].ip) );

		return true;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	namespace
	{
		bool gLogNetTraffic = true;
	}


	void WaitingRoomHostState::ProcessClientAdd( int clientId )
	{
		if ( !nodesManager->CanAcceptNewNode() )
		{
      if(!nodesManager->IsAllPresentNodesConnectedToOthers())
      {
        coreLog( NLogg::LEVEL_DEBUG ) << "Refuse client: " << clientId << " because net is in transitional state." << endl;
      }
      else
      {
        if( gLogNetTraffic )
        {
          coreLog( NLogg::LEVEL_DEBUG ) << "Refuse client: " << clientId << ", can accept only " << nodesManager->nodesHighLimit << " nodes!" << endl;
        }
      }

			Send( clientId, new GameRoom::RefuseConnectionPacket() );
      GetDriver()->Kick(clientId);
			return;
		}

		const string ip = GetDriver()->GetIP( clientId );
		const int port = GetDriver()->GetPort( clientId );
		int nodeId = nodesManager->AssignNewNode( clientId, ip, port );
		Send( clientId, new GameRoom::ConnectHandshakePacket( MYSELF_NODE_ID ) );
		Send( clientId, nodesManager->ComposeAcceptPacket( nodeId ) );

		for ( int i = nodesManager->nodes.size() - 1; i > MYSELF_NODE_ID; --i )
		{
			if ( !nodesManager->nodes[i].present || i == nodeId )
				continue;

			Send(nodesManager->nodes[i].clientId, new GameRoom::NewClientNotifyPacket( nodeId, ip, port ) );
      //we expect one more confirmation
      nodesManager->nodes[i].connectedToOthers = false;
		}
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void WaitingRoomHostState::ProcessClientRemove( int clientId )
	{
		coreLog( NLogg::LEVEL_DEBUG ) << "WaitingRoomHostState::ProcessClientRemove( " << clientId << " )" << endl;

    pContext->PushMessageFromCore(new WaitingRoomClientRemove(nodesManager->nodes[clientId].ip) );

		nodesManager->RemoveNode( clientId );
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void WaitingRoomHostState::ProcessKicked()
	{
		NI_ALWAYS_ASSERT( "WaitingRoomHostState::ProcessKicked() - should not happen, game host can not be kicked" );
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	bool WaitingRoomHostState::ReadyToStart() const
	{
		return clientsAreReady;
	}

  template<typename It>
  It GetEmptySlot(It first, It last, int team = -1)
  {
    while( ++first != last)
      if( -1 == first->nodeID && first->teamID == team)
        return first;

    return last;
  }

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	IBaseFSMState* WaitingRoomHostState::Step(float)
	{
		// process net packets
		ProcessMessages();

    pContext->PushMessageFromCore(new WaitingRoomHostStateMessage(nodesManager->CountNodes(), startInfo.CountValidPlayers()));

		// all clients are ready. start game!
		if ( ReadyToStart() )
		{					

      GetDriver()->StopNewPlayerAccept();
			vector< CObj<CGameNode> > allNodes;
      vector<PlayerStartInfo>::iterator const begin = startInfo.playersInfo.begin();
      vector<PlayerStartInfo>::iterator const end   = startInfo.playersInfo.end();
			for(vector<PlayerStartInfo>::iterator it = begin; it != end; ++it)
			{
        const int nodeIndex = allNodes.size();

				NodeDescriptor& descriptor = nodesManager->nodes[nodeIndex];
				if( descriptor.present )
        {
          CGameNode* node = (nodeIndex == MYSELF_NODE_ID) ? new CGameNode("local") : new CGameNodeRemote( GetDriver(), descriptor.clientId, descriptor.ip.c_str() );

          vector<PlayerStartInfo>::iterator desiredNode = GetEmptySlot(begin, end, descriptor.teamId);
          if( end == desiredNode )
          {
            coreLog( NLogg::LEVEL_DEBUG ) << "Failed to move to desired team!" << endl; 
          }
          else
          {
            if( it != desiredNode )
              nstl::iter_swap( it, desiredNode );
          }
          
          it->nodeID     = nodeIndex;
          it->playerType = PLAYER_HUMAN;
          
          if( nodeIndex == MYSELF_NODE_ID )
            it->heroID   = -1 != selectedHero ? selectedHero : it->heroID;
          else
            it->heroID   = -1 != descriptor.heroId ? descriptor.heroId : it->heroID;
          
          allNodes.push_back( node );
        }
        else
        if( PLAYER_COMPUTER == it->playerType)
        {
          it->nodeID     = MYSELF_NODE_ID;
        }


			}

      startInfo.BalanceTeams( mode );

      for ( int i = nodesManager->nodes.size() - 1; i > MYSELF_NODE_ID; --i )
      {
        if ( nodesManager->nodes[i].present )
          Send( nodesManager->nodes[i].clientId, new GameRoom::StartGamePacket( startInfo ) );
      }
      
			const GameStartInfo info = { allNodes, startInfo };
			pContext->PushMessageFromCore( new GameStartedMessage( info ) );

			return new InGameHostState( pContext, GetDriver(), allNodes, MYSELF_NODE_ID, startInfo.mapName );
		}

		return NetworkState::Step( pContext );
	}
}
