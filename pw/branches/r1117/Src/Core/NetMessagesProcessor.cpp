#include "stdafx.h"
#include "NetMessagesProcessor.h"

#include "../Net/NetDriver.h"
#include "../Net/LinksManager.h"
#include "../Net/NetAddress.h"

#include "NetPacket.h"
#include "CommandSerializer.h"
#include "NetMessageHandler.h"


// time out [s]
int g_NetTimeout = 2000;

namespace NetMessagesProcessor
{
	void ProcessMessages( NNet::IDriver* driver, NCore::INetMessageHandler* handler )
	{
		NNet::IDriver::EMessage messageId;
		int clientId;
		MemoryStream memStream;
		while ( driver->GetMessage( &messageId, &clientId, 0, &memStream ) )
		{
			CPtr<CNetPacket> netPacket;
      //NetLog
			//coreLog( NLogg::LEVEL_DEBUG ) << "FSM collect driver message: " << NNet::NetMessage2String( messageId ) 
			//	<< " from " << clientId << "(len " << memStream.GetSize() << ")" << endl;

			switch ( messageId )
			{
			case NNet::IDriver::DIRECT:
			case NNet::IDriver::BROADCAST:
				{
					netPacket = NCore::ReadNetPacketFromStream( &memStream );

					if ( IsValid( netPacket ) )
					{
						//coreLog( NLogg::LEVEL_DEBUG ) << "Decoded net packet type: " << netPacket->GetObjectTypeName() << endl;
						handler->ProcessNetMessage( clientId, netPacket );
					}
					else
					{
						NI_ALWAYS_ASSERT( "Unable to decode net packet" );
					}
					break;
				}
			case NNet::IDriver::NEW_CLIENT:
				handler->ProcessClientAdd( clientId );
				break;
			case NNet::IDriver::REMOVE_CLIENT:
				handler->ProcessClientRemove( clientId );
				break;
			case NNet::IDriver::KICKED:
				handler->ProcessKicked();
				break;
			default:
				break;
			}
		}
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	bool Send( NNet::IDriver* driver, int clientId, CNetPacket* message )
	{
		CPtr<CNetPacket> pNetPacket = message;
		MemoryStream memStream;

		NCore::WriteNetPacketToStream( message, &memStream );
		return driver->SendDirect( clientId, memStream );
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	const int LAN_GAME_VERSION = 1;

	NNet::IDriver* InitNet( bool client )
	{
		int port = NNet::IDriver::LAN_GAME_PORT - 2;

		NNet::SNetDriverConsts netConsts( g_NetTimeout );
		CPtr<NNet::IDriver> pNetDriver = NNet::CreateNetDriver( netConsts, true );
		CPtr<NNet::ILinksManager> pLinksManager;
		do 
		{
			port += 2;
			pLinksManager = NNet::CreateServerLinksManager( port );
		} while ( !IsValid( pLinksManager ) );

		pNetDriver->Init( LAN_GAME_VERSION, port, client, pLinksManager );
		return pNetDriver.Extract();
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//REGISTER_VAR( "net_timeout", g_NetTimeout, STORAGE_USER );
