#pragma once

/////////////////////////////////////////////////////////////////////////////////////
namespace nstl
{
	template<> struct hash<__int64> {
		size_t operator()(__int64 __x) const { return __x; }
	};
}

namespace NNet
{
	/////////////////////////////////////////////////////////////////////////////////////
	class CP2PTracker
	{
	public:
		typedef unsigned int UCID;
		enum EOutMessage
		{
			NEW_CLIENT,
			REMOVE_CLIENT,
			DIRECT,
			BROADCAST,
		};
		struct SMessage
		{
			EOutMessage msg;
			UCID from;
			vector<UCID> received;
			MemoryStream pkt;
		};
		struct SPacket
		{
			UCID addr;
			MemoryStream pkt;

			SPacket() {}
			SPacket( UCID _addr, MemoryStream &_pkt ): addr(_addr), pkt(_pkt) {}
		};
		vector<SPacket> packets;
		vector<UCID> kicks;

		void SendBroadcast( MemoryStream &pkt );
		void SendDirect( UCID addr, MemoryStream &pkt );
		bool GetMessage( SMessage *pRes );
		void ProcessPacket( UCID addr, MemoryStream &pkt, bool bIsBroadcast );
		void AddNewClient( UCID addr, MemoryStream &addrInfo, bool bIsBroadcast );
		void KickClient( UCID addr, bool bIsBroadcast );
		bool IsActive( UCID addr );
		void CheckCorpses();

		CP2PTracker() {}
	private:
		struct SAck
		{
			UCID from;
			bool bAcked;
		};
		struct SQMessage
		{
			int nID;
			bool bDirect;
			MemoryStream msg;
			list<SAck> acks;
		};

		struct SFastAck
		{
			int nID;
			UCID broadcastSender; // broadcast sender address
		};

		struct SPeer
		{
			UCID addr;
			bool bActive;		// not active when peer is being dropped
			list<UCID> clients; // current clients from peer view
			list<SQMessage> messages;
			list<SFastAck> fastacks; // acks received from this peer before message itself
			list<UCID> requireKick;
			MemoryStream addrInfo;

			bool IsActive() const { return bActive; }
			bool HasClient( UCID addr ) const
			{
				return find( clients.begin(), clients.end(), addr ) != clients.end();
			}
			void RemoveClient( UCID addr )
			{
				clients.remove( addr );
			}
		};

		list<SMessage> output;
		hash_map<UCID,SPeer> clients;

		SPeer* GetClient( UCID addr );
		void AddOutputMessage( EOutMessage msg, UCID _from, 
			const MemoryStream *pData = 0, vector<UCID> *pReceived = 0 );
		void AddKickApprove( UCID victim, UCID kickFrom );
		void ApproveKick( UCID victim, UCID from );
		void ReceiveBroadcast( const UCID who, MemoryStream &data, int nID );
		void ReceiveDirect( const UCID who, MemoryStream &data );
		void ReceiveAddClient( const UCID peer, UCID who, MemoryStream &addrInfo, bool bIsBroadcast );
		void ReceiveRemoveClient( const UCID peer, UCID whom, bool bIsBroadcast );
		void ReceiveAck( const UCID from, const UCID addressOfBroadcastSender, int nID );
		void CheckQueuedMessages( const UCID who );
		void SendRemoveClient( UCID destAddr, UCID whom );
		void SendAddClient( const UCID dest, UCID whom, MemoryStream &addrInfo );
		void SendBroadcast( const UCID dest, int nID, MemoryStream &data );
		void SendAck( const UCID dest, const UCID addressOfBroadcastSender, int nID );
	};	
}
