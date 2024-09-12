#pragma once
#include "NetPacket.h"

namespace NCore
{
	_interface INetMessageHandler
	{
		virtual void ProcessNetMessage( int clientId, CNetPacket* packet ) = 0;
		virtual void ProcessClientAdd( int clientId ) = 0;
		virtual void ProcessClientRemove( int clientId ) = 0;
		virtual void ProcessKicked() = 0;
	};
}

