#include "stdafx.h"
//#include "StateGameConnect.h"
//#include "CoreFSM.h"
//#include "../Net/NetDriver.h"
//#include "StateGameRoomClient.h"
//#include "GameRoomPackets.h"
//#include "StateLANInit.h"
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//namespace NCore
//{
//
//
//// Candidate for refactoring:
//// - split into two states
//
//
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//CStateConnectingToGame::CStateConnectingToGame( CoreFSM *pContext, NNet::IDriver *pDdriver, const NNet::CNodeAddress &_addr ) 
//: CStateLANBase( pContext, pDdriver )
//, eStage( STAGE_INIT )
//{
//	connectTo = _addr;
//}
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//void CStateConnectingToGame::Init()
//{ 
//	CStateLANBase::Init();
//	// Start Connecting
//	GetDriver()->ConnectGame( connectTo, MemoryStream() );
//	
//	//TODO: Register message processor for CANCEL
//
//	// Register packet processors
//	REGISTER_PACKET_PROCESSOR( &NCore::CStateConnectingToGame::OnConnectAccepted );
//	REGISTER_PACKET_PROCESSOR( &NCore::CStateConnectingToGame::OnConnectRefused );
//	REGISTER_PACKET_PROCESSOR( &NCore::CStateConnectingToGame::OnHandshake );
//	REGISTER_PACKET_PROCESSOR( &NCore::CStateConnectingToGame::OnNewClientNotify );
//
//	eStage = STAGE_LOGGING_IN;
//}
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//nstl::string CStateConnectingToGame::Stage2String() const
//{
//	switch( eStage )
//	{
//	case CStateConnectingToGame::STAGE_INIT:
//		return "STAGE_INIT";
//	case CStateConnectingToGame::STAGE_LOGGING_IN:
//		return "STAGE_LOGGING_IN";
//	case CStateConnectingToGame::STAGE_ACCEPTED:
//		return "STAGE_ACCEPTED";
//	case CStateConnectingToGame::STAGE_SUCCESS:
//		return "STAGE_SUCCESS";
//	case CStateConnectingToGame::STAGE_FAILED:
//		return "STAGE_FAILED";
//	default:
//		return nstl::string( "unknown stage" ) + NStr::IntToStr( eStage );
//	}
//}
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//void CStateConnectingToGame::OnClientAdd( int nClient )
//{
//	coreLog( NLogg::LEVEL_DEBUG ) 
//		<< "CStateConnectingToGame::OnClientAdd( " << nClient << " - " << GetDriver()->GetIP( nClient ) << " )"
//		<< " Object state: " << Stage2String() << endl;
//	if ( eStage == STAGE_LOGGING_IN )
//	{
//		pendingClients.push_back( nClient );
//	}
//	else
//	{
//		Send( nClient, new ConnectHandshakePacket( nMyNode ) );
//	}
//}
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//void CStateConnectingToGame::OnClientRemove( int nClient )
//{
//	coreLog( NLogg::LEVEL_DEBUG ) << "CStateConnectingToGame::OnClientRemove( " << nClient << " )" << endl;
//	// Remove from pending clients (if any)
//	for ( list<int>::iterator it = pendingClients.begin(); it != pendingClients.end(); ++it )
//	{
//		if ( *it == nClient )
//		{
//			it = pendingClients.erase( it );
//			break;
//		}
//	}
//
//	// Remove from nodes
//	for ( CConnections::iterator it = nodes.begin(); it != nodes.end(); ++it )
//	{
//		SConnectionInfo &node = *it;
//		if ( node.nClient == nClient )
//		{
//			nodes.erase( it );
//			break;
//		}
//	}
//
//}
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//void CStateConnectingToGame::OnKicked()
//{
//	eStage = STAGE_FAILED;
//
//	//TODO: report reason
//}
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//void CStateConnectingToGame::AddConnectedNode( int nClient, int nNode )
//{
//	coreLog( NLogg::LEVEL_DEBUG ) << "CStateConnectingToGame::AddConnectedNode( " << nClient << " - "
//		<< GetDriver()->GetIP( nClient ) << ", node " << nNode << " )" << endl;
//	SConnectionInfo newConnection;
//	newConnection.nClient = nClient;
//	if ( nClient >= 0 )
//	{
//		newConnection.szIP = GetDriver()->GetIP( newConnection.nClient );
//		newConnection.nPort = GetDriver()->GetPort( newConnection.nClient );
//		newConnection.bConnected = true;
//	}
//	newConnection.nNode = nNode;
//
//	nodes.push_back( newConnection );
//}
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//void CStateConnectingToGame::AddUnconnectedNode( int nNode, string szIP, int nPort )
//{
//	coreLog( NLogg::LEVEL_DEBUG ) << "CStateConnectingToGame::AddUnconnectedNode( " << szIP << " as node " << nNode << " )" << endl;
//	bool bFound = false;
//	for ( CConnections::iterator it = nodes.begin(); it != nodes.end(); ++it )
//	{
//		SConnectionInfo &node = *it;
//		if ( node.nNode == nNode )
//		{
//			bFound = true;
//			break;
//		}
//
//		if ( node.szIP == szIP && node.nPort == nPort )
//		{
//			bFound = true;
//			node.nNode = nNode;
//			break;
//		}
//	}
//
//	if ( bFound )
//		return;
//
//	SConnectionInfo newConnection;
//	newConnection.nNode = nNode;
//	newConnection.szIP = szIP;
//	newConnection.nPort = nPort;
//	if ( nNode == nMyNode )
//		newConnection.bConnected = true;
//	nodes.push_back( newConnection );
//
//	TryToConnectTo( szIP, nPort );
//}
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//bool CStateConnectingToGame::OnConnectAccepted( int nClient, SAcceptConnectionPacket *pPacket )
//{
//	nMyNode = pPacket->nNode;
//	nHostClientID = nClient;
//	coreLog( NLogg::LEVEL_DEBUG ) << "CStateConnectingToGame::OnConnectAccepted( " << nClient << " ): "
//		<< " my node = " << nMyNode << ", " << pPacket->nodes.size() << " nodes to connect to" << endl;
//	AddConnectedNode( GetDriver()->GetSelfClientID(), nMyNode );
//
//	// Send my nodeID info to all pending clients
//	for ( list<int>::iterator it = pendingClients.begin(); it != pendingClients.end(); ++it )
//	{
//		AddConnectedNode( *it, -1 );
//		if ( nHostClientID != *it )
//		{
//			Send( *it, new SConnectHandshakePacket( nMyNode ) );
//		}
//	}
//	pendingClients.clear();
//
//	// Fill nodes
//	for ( int i = 0; i < pPacket->nodes.size(); ++i )
//	{
//		AddUnconnectedNode( pPacket->nodes[i].nNode, pPacket->nodes[i].szIP, pPacket->nodes[i].nPort );
//	}
//
//	eStage = STAGE_ACCEPTED;
//	return true;
//}
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//bool CStateConnectingToGame::OnConnectRefused( int nClient, SRefuseConnectionPacket *pPacket )
//{
//	eStage = STAGE_FAILED;
//
//	//TODO: report reason
//	return true;
//}
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//bool CStateConnectingToGame::OnNewClientNotify( int nClient, struct SNewClientNotifyPacket *pPacket )
//{
//	coreLog( NLogg::LEVEL_DEBUG ) << "CStateConnectingToGame::OnNewClientNotify( " << pPacket->szIP << " )" << endl;
//	AddUnconnectedNode( pPacket->nNode, pPacket->szIP, pPacket->nPort );
//	return true;
//}
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//bool CStateConnectingToGame::OnHandshake( int nClient, SConnectHandshakePacket *pPacket )
//{
//	coreLog( NLogg::LEVEL_DEBUG ) << "CStateConnectingToGame::OnHandshake( " << nClient << " - node "
//		<< pPacket->nNode << " )" << endl;
//	if ( eStage == STAGE_LOGGING_IN )
//	{
//		for ( list<int>::iterator it = pendingClients.begin(); it != pendingClients.end(); ++it )
//		{
//			if ( *it != nClient )
//				continue;
//
//			AddConnectedNode( *it, pPacket->nNode );
//			pendingClients.erase( it );
//			break;
//		}
//	}
//	else
//	{
//		bool bFound = false;
//		for ( CConnections::iterator it = nodes.begin(); it != nodes.end(); ++it )
//		{
//			SConnectionInfo &node = *it;
//			if ( node.nNode != pPacket->nNode )
//				continue;
//
//			if ( !bFound )
//			{
//				node.nClient = nClient;
//				node.bConnected = true;
//				node.szIP = GetDriver()->GetIP( nClient );
//				node.nPort = GetDriver()->GetPort( nClient );
//				bFound = true;
//			}
//			else
//			{
//				it = nodes.erase( it );
//			}
//		}
//
//		if ( !bFound )
//			AddConnectedNode( nClient, pPacket->nNode );
//	}
//	return true;
//}
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//void CStateConnectingToGame::CheckAllConnected()
//{
//	if ( eStage != STAGE_ACCEPTED )
//		return;
//
//	int nConnected = 0;
//	for ( CConnections::iterator it = nodes.begin(); it != nodes.end(); ++it )
//	{
//		SConnectionInfo &node = *it;
//		if ( !node.bConnected || node.nNode < 0 )
//		{
//			//return;
//		}
//		else
//			++nConnected;
//	}
//	coreLog( NLogg::LEVEL_DEBUG ) << "CStateConnectingToGame::CheckAllConnected: " << nConnected << " out of " << nodes.size() << endl;
//	if ( nConnected < nodes.size() )
//		return;
//
//	eStage = STAGE_SUCCESS;
//}
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//IBaseFSMState* CStateConnectingToGame::CreateClientState()
//{
//	hash_map<int,int> nodesMap;
//	for ( CConnections::iterator it = nodes.begin(); it != nodes.end(); ++it )
//	{
//		SConnectionInfo &node = *it;
//		nodesMap[node.nNode] = node.nClient;
//	}
//	return new CStateGameRoomClient( pContext, GetDriver(), nodesMap, nMyNode );
//}
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//IBaseFSMState* CStateConnectingToGame::Step()
//{
//	//if ( GetDriver()->GetState() == NNet::IDriver::INACTIVE )
//	{
//		// Failed
//		//TODO report failure
//		coreLog( NLogg::LEVEL_DEBUG ) << "*** NET driver inactive " << typeid( this ).name() << endl;
//		return new CStateLANInit( pContext );
//	}
//
//	CStateLANBase::Step();
//
//	CheckAllConnected();
//
//	if ( eStage == STAGE_SUCCESS )
//	{
//		Send( nHostClientID, new SConnectedToOthersPacket() );
//		return CreateClientState();
//	}
//	else if ( eStage == STAGE_FAILED )
//	{
//		//TODO report failure
//		coreLog( NLogg::LEVEL_DEBUG ) << "*** Connecting failed " << typeid( this ).name() << endl;
//		return new CStateLANInit( pContext );
//	}
//	else
//		return 0;
//}
//	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//}; // namespace NCore
