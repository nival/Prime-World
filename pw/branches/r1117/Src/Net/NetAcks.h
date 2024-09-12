#pragma once

#include <winsock2.h>
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class BitStream;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NNet
{
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef unsigned int UPDATE_ID;
typedef unsigned short PACKET_ID;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RTT, acks, rate/congestion tracking
class CAckTracker
{
public:
	CAckTracker();
	float GetRTT() const { return fAvrgRTT; }
	float GetRTTDisp() const { return sqrt( fabs( sqr( fAvrgRTT ) - fAvrgRTT2 ) ); }
	float GetTimeSinceLastRecv() const { return fTimeSinceLastRecv; }
	const float GetPing() const { return fPing; }
	// if true is returned then packet considered sent and timer corrected accordingly
	// all packets are considered to be of same size
	bool CanSend(); 
	bool NeedSend() const;
	void Step( vector<PACKET_ID> *pRolled, vector<PACKET_ID> *pErased, double fDeltaTime, float fMaxRTT );
	PACKET_ID WriteAcks( BitStream *pBits, int nPktSize );
	bool ReadAcks( vector<PACKET_ID> *acked, BitStream &bits );
	void PacketLost( PACKET_ID pktID );

private:
	PACKET_ID nPktSent;				// is used to order update packets
	UPDATE_ID nPktLastReceived;// number of last received pkt
	UPDATE_ID nPktHighCounter; // high part of packet counter
	//
	// info on received pkts (acks on them should be sent)
	vector<UPDATE_ID> receivedPkts;
	// acknowledgements on packets cache
	DWORD dwAckedBits;
	PACKET_ID nAckedLast;
	//
	float fAvrgRTT, fAvrgRTT2;		// RTT statistics

	// ping information
	float fPing;
	long nPingPacketsReceived;		
	float fSumPktRTT4Period;
	float fLastPingUpdateTime;

	//
	float fWindow;
	int nFlyPackets;
	//float fUpdateTimeDelay;			 // recommended delay between updates (in seconds)
	//float fUpdateTimeElapsed;		 // time elapsed since last update
	float fTimeSinceLastSend;
	float fTimeSinceLastRecv;		 // time elapsed since last receive
	double fCurrentTime;
	//int nUpdateSize;							 // recommended update size
	// bool bHasNewPacketToAck;
	//
	// пакет, сформированный из CUpdateRequest
	class CUpdate 
	{
	public: 
		double fTimeCreated;
		PACKET_ID nPktNumber;
		bool bOnTheWindowEdge;
	};
	// info on sent update packets
	list< CUpdate > sentUpdates, rolledUpdates;		// unacknowledged updates
	
	void RegisterRTT( float fRTT );
	void SendPktAcks( BitStream *pBits );
	void ReceiveAck( vector<PACKET_ID> *pAcked, PACKET_ID nPkt );
	void ReceivePktAcks( vector<PACKET_ID> *pAcked, BitStream &bits );
	bool CheckRecvPacketNumber( UPDATE_ID nPkt );
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
