#include "stdafx.h"
#include "StateGameRoomHost.h"
#include "../Net/NetDriver.h"
#include "CoreFSM.h"
#include "GameRoomPackets.h"
#include "StateLANInit.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NCore
{

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CStateGameRoomHost::CStateGameRoomHost( CoreFSM *pContext, NNet::IDriver *pDdriver )
: CStateLANBase( pContext, pDdriver )
{
	GetDriver()->StartGame();
	GetDriver()->StartNewPlayerAccept();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CStateGameRoomHost::Init()
{
	CStateLANBase::Init();
	REGISTER_PACKET_PROCESSOR( &NCore::CStateGameRoomHost::OnClientConnectedToOthers );
	REGISTER_PACKET_PROCESSOR( &NCore::CStateGameRoomHost::OnTestGameRoom );

	// Init my node - 0
	nodes.resize( 16 );
	nodes[0].bPresent = true;
	nodes[0].bConnectedToOthers = true;
	nodes[0].szIP = GetDriver()->GetIP( GetDriver()->GetSelfClientID() );
	nodes[0].nPort = GetDriver()->GetPort( GetDriver()->GetSelfClientID() );

	//TODO: subscribe for messages
	pContext->RegisterProcessorToCore( this );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CStateGameRoomHost::OnClientAdd( int nClient )
{
	if ( !CanAcceptNewNode() )
	{
		Send( nClient, new SRefuseConnectionPacket() );
		return;
	}

	int nNewNode = AssignNewNode( nClient );
	Send( nClient, new SConnectHandshakePacket( 0 ) );
	Send( nClient, ComposeAcceptPacket( nNewNode ) );

	for ( int i = 1; i < nodes.size(); ++i )
	{
		if ( !nodes[i].bPresent || i == nNewNode )
			continue;
		
		Send( nodes[i].nClient, new SNewClientNotifyPacket( nNewNode, nodes[nNewNode].szIP, nodes[nNewNode].nPort ) );
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const int CStateGameRoomHost::AssignNewNode( int nClient )
{
	coreLog( NLogg::LEVEL_DEBUG ) << "CStateGameRoomHost::AssignNewNode( " << nClient << " - "
		<< GetDriver()->GetIP( nClient ) << " )" << endl;
	
	int nNewNode = -1;
	for ( int i = 1; i < nodes.size(); ++i )
	{
		if ( nodes[i].bPresent )
			continue;
		
		nNewNode = i;
		break;
	}

	if ( nNewNode < 0 )
	{
		nNewNode = nodes.size();
		nodes.resize( nodes.size() + 8 );
	}

	nodes[nNewNode].bPresent = true;
	nodes[nNewNode].nClient = nClient;
	nodes[nNewNode].bConnectedToOthers = false;
	nodes[nNewNode].szIP = GetDriver()->GetIP( nClient );
	nodes[nNewNode].nPort = GetDriver()->GetPort( nClient );

	return nNewNode;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CStateGameRoomHost::OnClientRemove( int nClient )
{
	coreLog( NLogg::LEVEL_DEBUG ) << "CStateGameRoomHost::OnClientRemove( " << nClient << " )" << endl;
	for ( int i = 1; i < nodes.size(); ++i )
	{
		if ( nodes[i].nClient != nClient )
			continue;

		nodes[i].bPresent = false;
		nodes[i].nClient = -1;
		return;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CStateGameRoomHost::OnKicked()
{
	NI_ALWAYS_ASSERT( "CStateGameRoomHost::OnKicked() - should not happen, game host can not be kicked" );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CStateGameRoomHost::OnClientConnectedToOthers( int nClient, struct SConnectedToOthersPacket *pPacket )
{
	coreLog( NLogg::LEVEL_DEBUG ) << "CStateGameRoomHost::OnClientConnectedToOthers( " << nClient << " )" << endl;
	return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const bool CStateGameRoomHost::CanAcceptNewNode()
{
	return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const int CStateGameRoomHost::CountNodes() const
{
	int nCount = 0;
	for ( int i = 0; i < nodes.size(); ++i )
	{
		if ( nodes[i].bPresent )
			++nCount;
	}

	return nCount;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CNetPacket* CStateGameRoomHost::ComposeAcceptPacket( int nNewNode )
{
	SAcceptConnectionPacket *pPacket = new SAcceptConnectionPacket();
	pPacket->nNode = nNewNode;

	pPacket->nodes.resize( CountNodes() );
	int j = 0;
	for ( int i = 0; i < nodes.size(); ++i )
	{
		if ( !nodes[i].bPresent )
			continue;

		pPacket->nodes[j].nNode = i;
		pPacket->nodes[j].szIP = nodes[i].szIP;
		pPacket->nodes[j].nPort = nodes[i].nPort;
		++j;
	}

	return pPacket;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
IBaseFSMState* CStateGameRoomHost::Step()
{
	CStateLANBase::Step();

	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CStateGameRoomHost::OnTestGameRoom( int nClient, struct STestGameRoomPacket *pPacket )
{
	coreLog( NLogg::LEVEL_DEBUG ) << "CStateGameRoomHost::OnTestGameRoom( " << nClient << ", " << pPacket->nParam << " )" << endl;
	return true;
}
 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}; // namespace NCore
