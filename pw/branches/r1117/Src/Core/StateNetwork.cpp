#include "stdafx.h"
#include "StateNetwork.h"
#include "CoreFSM.h"
#include "NetMessagesProcessor.h"
#include "GameRoomPackets.h"

#include "../Net/NetDriver.h"
#include "StateIdle.h"

#include "Network/ClientTransportSystem.h"
#include "Network/Initializer.h"
#include "Network/Network.h"
#include "Network/TransportMessages.h"

namespace NCore
{
	NetworkState::NetworkState( NNet::IDriver* _pDriver )
		: pDriver( _pDriver )
	{
		NI_ASSERT( IsValid( pDriver ), "Invalid net driver!" );

    // Initialize TCP transport
    //driver = Network::Initialize();
    //transportSystem = new Transport::ClientTransportSystem( driver, Transport::GetGlobalMessageFactory(), 35200 );
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void NetworkState::ProcessNetMessage( int clientId, CNetPacket* pPacket )
	{
		const bool packetProcessed = ProcessPacket( clientId, pPacket );
		NI_ASSERT( packetProcessed, NStr::StrFmt( "State %s: Unknown packet %s from client %d", GetObjectTypeName(), pPacket->GetObjectTypeName(), clientId ) );
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void NetworkState::ProcessMessages()
	{
		NI_VERIFY( IsValid( pDriver ), "Invalid net driver!", return; );
		NetMessagesProcessor::ProcessMessages( pDriver, this );
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	bool NetworkState::Send( int clientId, CNetPacket* pPacket )
	{
		NI_VERIFY( IsValid( pDriver ), "Invalid net driver!", return false; );
		return NetMessagesProcessor::Send( GetDriver(), clientId, pPacket );
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	const char* Reason2String( NNet::IDriver::EReject reject )
	{
		switch( reject )
		{
			case NNet::IDriver::NONE: return "NONE";
			case NNet::IDriver::TIMEOUT: return "TIMEOUT";
			case NNet::IDriver::BANNED: return "BANNED";
			case NNet::IDriver::WRONG_VERSION: return "WRONG_VERSION";
			case NNet::IDriver::MAXPLAYERS_REACHED: return "MAXPLAYERS_REACHED";
			case NNet::IDriver::PASSWORD_FAILED: return "PASSWORD_FAILED";
			case NNet::IDriver::ALREADY_CONNECTED: return "ALREADY_CONNECTED";
			case NNet::IDriver::FORBIDDEN: return "FORBIDDEN";
			default: return "unknown";
		};
	}

	IBaseFSMState* NetworkState::Step( CoreFSM* pContext )
	{
		// check on inactive driver
		if( GetDriver()->GetState() == NNet::IDriver::INACTIVE )
		{
			const string message = Reason2String( GetDriver()->GetRejectReason() );
			coreLog( NLogg::LEVEL_DEBUG ) << "*** Inactive net, reason: " << message << endl;

			// push message from core to game
			NI_ASSERT( IsValid( pContext ), "Invalid FSM!" );
			pContext->PushMessageFromCore( new TextMessage( message ) );
			
			return new CStateIdle( pContext );
		}
		else
			return 0;
	}
}