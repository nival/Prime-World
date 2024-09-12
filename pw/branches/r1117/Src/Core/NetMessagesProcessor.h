#ifndef _MESSAGES_PROCESSOR_H_
#define _MESSAGES_PROCESSOR_H_

namespace NNet
{
	_interface IDriver;	
}

namespace NCore
{
	_interface INetMessageHandler;
}

class CNetPacket;

namespace NetMessagesProcessor
{
	/** function to process messages from net driver */
	void ProcessMessages( NNet::IDriver*, NCore::INetMessageHandler* );

	/** send net packet */
	bool Send( NNet::IDriver*, int, CNetPacket* );

	/** init net driver */
	NNet::IDriver* InitNet( bool client );
}

#endif

