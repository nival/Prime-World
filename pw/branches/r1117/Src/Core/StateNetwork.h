#ifndef STATE_NETWORK_H_
#define STATE_NETWORK_H_

#include "NetMessageHandler.h"
#include "PacketProcessor.h"
#include "MessagesGeneral.h"
#include "../System/noncopyable.h"

namespace NNet { _interface IDriver; }
namespace Network { _interface INetworkDriver; }
namespace Transport { class ClientTransportSystem; }

namespace NCore
{
	_interface IBaseFSMState;
	class CoreFSM;

	/**
	 *	Base network state
	 */
	class NetworkState
		: private IObjectBase
		, private NonCopyable
		, private INetMessageHandler		
		, public CPacketProcessorBase
	{
		CObj<NNet::IDriver> pDriver;
    CObj<Network::INetworkDriver> driver;
    CObj<Transport::ClientTransportSystem> transportSystem;

	protected:
		NetworkState() {};

		NNet::IDriver* GetDriver() const { return pDriver; }

		/** process net packets */
		void ProcessMessages();
		/** send packet */
		bool Send( int clientId, CNetPacket* pPacket );

		virtual void ProcessNetMessage( int clientId, CNetPacket* packet );

	public:
		NetworkState( NNet::IDriver* );
		
		IBaseFSMState* Step( CoreFSM* );
	};
}

#endif

