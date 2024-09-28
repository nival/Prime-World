#include "StdAfx.h"
#include <math.h>
#include "NetAcks.h"
#include "../System/BitStreams.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NNet
{
const int CS_PACKET_ID_RANGE = 0x10000;
const float FP_RTT_KEEP = 0.93f;		// RTT recalc rate
const float TIME_TO_UPDATE_PING = 4;
const float F_INITIAL_RTT = 3;
const float MIN_WINDOWS_SIZE = 2.0f;
const float MAX_WINDOWS_SIZE = 10.0f;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CAckTracker
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CAckTracker::CAckTracker()
{
	DWORD dwTick = GetTickCount();
	float fRTT;
	fRTT = F_INITIAL_RTT;
	fAvrgRTT = fRTT;
	fAvrgRTT2 = sqr( fAvrgRTT );
	// 1 мало, т.к. в начале первые пакеты с обоих сторон не имеют ack`ов. Как следствие обе стороны приходят в состояние
	// "хочу послать подтверждение о первом приеме, но не могу, т.к. окно занято не подтвержденным первым сообщением"
	// это состояние разрешается по таймауту. Чтобы это происходило сразу нужно окно как минимум 2
	fWindow = MIN_WINDOWS_SIZE;
	nFlyPackets = 0;
	//fUpdateTimeDelay = 0.04f;// * ( 0.5f + (dwTick & 0xff ) / 255.0 );
	//fUpdateTimeElapsed = 0;
	fTimeSinceLastSend = 0;
	fTimeSinceLastRecv = 0;
	fCurrentTime = 0;
	//nUpdateSize = 220;//512;
	nPktSent = dwTick & 0xffff;
	nPktLastReceived = 0;
	nPktHighCounter = CS_PACKET_ID_RANGE;
	dwAckedBits = 0;
	nAckedLast = 0;

	//
	fPing = 0;
	nPingPacketsReceived = 0;
	fSumPktRTT4Period = 0;
	fLastPingUpdateTime = fCurrentTime;
	//bHasNewPacketToAck = true; // так делать нельзя: не все пакеты содержат данные!
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*void CAckTracker::SetRate( int nBytesPerSec )
{
	nBytesPerSec = Max( nBytesPerSec, 500 );
	nBytesPerSec = Min( nBytesPerSec, 50000 );
	fUpdateTimeDelay = 250.0f / nBytesPerSec;
}*/
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CAckTracker::CanSend()
{
	if ( nFlyPackets < fWindow )
	{
		return true;
	}
	return false;
/*	if ( fUpdateTimeElapsed > fUpdateTimeDelay )
	{
		fUpdateTimeElapsed -= fUpdateTimeDelay;
		fTimeSinceLastSend = 0;
		return true;
	}
	return false;*/
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CAckTracker::NeedSend() const
{
	return fTimeSinceLastSend > 1.0f;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CAckTracker::RegisterRTT( float _fRTT )
{
	//ASSERT( fRTT >= 0 );
	float fRTT = Clamp( _fRTT, 0.0f, 20.0f );
	fAvrgRTT *= FP_RTT_KEEP;
	fAvrgRTT += ( 1 - FP_RTT_KEEP ) * fRTT;
	fAvrgRTT2 *= FP_RTT_KEEP;
	fAvrgRTT2 += ( 1 - FP_RTT_KEEP ) * sqr( fRTT );

	// update ping info
	++nPingPacketsReceived;
	fSumPktRTT4Period += fRTT;
	if ( fLastPingUpdateTime + TIME_TO_UPDATE_PING < fCurrentTime )
	{
		fPing = fSumPktRTT4Period / nPingPacketsReceived;
		
		fLastPingUpdateTime = fCurrentTime;
		fSumPktRTT4Period = 2 * fPing;
		nPingPacketsReceived = 2;
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CAckTracker::Step( vector<PACKET_ID> *pRolled, vector<PACKET_ID> *pErased, double fDeltaTime, float fMaxRTT )
{
	pRolled->resize( 0 );
	pErased->resize( 0 );
	fTimeSinceLastRecv += fDeltaTime;
	fTimeSinceLastSend += fDeltaTime;
	//fUpdateTimeElapsed += fDeltaTime;

	fCurrentTime += fDeltaTime;
	// 
	float fRTTDiscard = fAvrgRTT + GetRTTDisp() * 3; // 99% probability if normal distribution
	// check network capacity
	//float fMaxTimeElapsed = Max( fUpdateTimeDelay * 1.2f, fRTTDiscard );
	//fUpdateTimeElapsed = Min( fUpdateTimeElapsed, fMaxTimeElapsed );
	fRTTDiscard = Max( fRTTDiscard, 0.1f );
	fRTTDiscard = Min( fRTTDiscard, fMaxRTT );
	// roll back updates that are out of estimated rtt
	list<CUpdate>::iterator it, itmp;
	for ( it = sentUpdates.begin(); it != sentUpdates.end(); )
	{
		//double fCrap = it->fTimeCreated;
		if ( fCurrentTime - it->fTimeCreated > fRTTDiscard )
		{
			//fUpdateTimeDelay *= 1.2f;
			--nFlyPackets;
			fWindow -= 0.5f;
			fWindow = Max( MIN_WINDOWS_SIZE, fWindow );
			//fUpdateTimeDelay = Min( fUpdateTimeDelay, 0.5f );
			pRolled->push_back( it->nPktNumber );
			itmp = it;
			++it;
			rolledUpdates.splice( rolledUpdates.end(), sentUpdates, itmp );
		}
		else
			break;
	}
	for ( it = rolledUpdates.begin(); it != rolledUpdates.end(); )
	{
		if ( fCurrentTime - it->fTimeCreated > fMaxRTT )
		{
			pErased->push_back( it->nPktNumber );
			it = rolledUpdates.erase( it );
		}
		else
			++it;
	}
	//
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// receive single ack, search for this packet and ack it
void CAckTracker::ReceiveAck( vector<PACKET_ID> *pAcked, PACKET_ID nPkt )
{
	list<CUpdate>::iterator i;
	for ( i = sentUpdates.begin(); i != sentUpdates.end(); )
	{
		if ( ( i->nPktNumber ) == nPkt )
		{
			--nFlyPackets;
			if ( i->bOnTheWindowEdge )
			{
				fWindow += 0.05f;
				fWindow = Min( fWindow, MAX_WINDOWS_SIZE );
			}
				// / fWindow;
			//fUpdateTimeDelay *= 0.99f;
			//fUpdateTimeDelay = Max( fUpdateTimeDelay, 0.00001f );
			pAcked->push_back( nPkt );
			RegisterRTT( fCurrentTime - i->fTimeCreated );
			i = sentUpdates.erase( i );
			return;
		}
		else
			++i;
	}
	// this should be very rare case so perfomance is not critical
	for ( i = rolledUpdates.begin(); i != rolledUpdates.end(); )
	{
		if ( i->nPktNumber == nPkt )
		{
			pAcked->push_back( nPkt );
			RegisterRTT( fCurrentTime - i->fTimeCreated );
			i = rolledUpdates.erase( i );
			return;
		}
		else
			++i;
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// pair to SendPktAcks()
void CAckTracker::ReceivePktAcks( vector<PACKET_ID> *pAcked, BitStream &bits )
{
	DWORD dwBits, dwNewAckBits;
	PACKET_ID nLast;
	bits.Read( nLast );
	bits.Read( dwBits );
	//
	int nShift = ( nLast - nAckedLast ) & ( CS_PACKET_ID_RANGE - 1 );
	if ( nShift > CS_PACKET_ID_RANGE / 2 )
		nShift -= CS_PACKET_ID_RANGE;
	if ( nShift <= 0 )
	{
		if ( nShift < -32 )
			dwAckedBits = 0;
		else
			dwAckedBits >>= -nShift;
	}
	else
	{
		dwAckedBits <<= 1;
		dwAckedBits |= 1;
		nShift--;
		if ( nShift < 32 )
			dwAckedBits <<= nShift;
		else
			dwAckedBits = 0;
	}
	dwNewAckBits = dwBits & ~dwAckedBits;
	dwAckedBits |= dwNewAckBits;
	nAckedLast = nLast;
	//
	ReceiveAck( pAcked, nLast );
	for ( int i = 1; i <= 32; i++ )
	{
		nLast--;
		if ( dwNewAckBits & ( 1 << (i-1) ) )
			ReceiveAck( pAcked, nLast );
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// check if nPkt can be acked and is not too obsolete
// add it to received list and update pktlastreceived value if needed
bool CAckTracker::CheckRecvPacketNumber( UPDATE_ID nPkt )
{
	// is not update too old?
	if ( nPkt + 32 < nPktLastReceived )
	{
		//if (pCSLog) (*pCSLog) << "SKIP too old update, dif=" << nPktLastReceived - nPkt << endl;
		return false;
	}
	nPktLastReceived = Max( nPktLastReceived, nPkt );
	// check for duplicate (for economy on rcvList mostly, because ack maybe already be sent
	// and duplication will not be detected)
	for ( vector<UPDATE_ID>::iterator k = receivedPkts.begin(); k != receivedPkts.end(); ++k )
	{
		if ( *k == nPkt )
		{
			//if (pCSLog) (*pCSLog) << "DUPLICATE update received from " << peer.GetFastName() << endl;
			return false;
		}
	}
	// add to receivedPkts set
	receivedPkts.push_back( nPkt );
	return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CAckTracker::ReadAcks( vector<PACKET_ID> *pAcked, BitStream &bits )
{
	PACKET_ID nReceived;
	UPDATE_ID nCurUpdate;
	
	pAcked->resize( 0 );
	fTimeSinceLastRecv = 0;
	//
	bits.Read( nReceived );
	// calcing sequential number of arrived update (accounting for wrapping of pkt numbers)
	nCurUpdate = nPktHighCounter + nReceived;
	if ( nPktLastReceived == 0 )
		nPktLastReceived = nCurUpdate;
	int nDif = nCurUpdate - nPktLastReceived;
	if ( nDif > CS_PACKET_ID_RANGE / 2 )
		nCurUpdate -= CS_PACKET_ID_RANGE;
	else if ( nDif < -CS_PACKET_ID_RANGE / 2 )
	{
		nCurUpdate += CS_PACKET_ID_RANGE;
		nPktHighCounter += CS_PACKET_ID_RANGE;
	}
	// check is not packet too obsolete
	if ( !CheckRecvPacketNumber( nCurUpdate ) )
		return false;
	
	// receiving acks
	ReceivePktAcks( pAcked, bits );
	//bHasNewPacketToAck = true;
	return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// use receivedPkts
void CAckTracker::SendPktAcks( BitStream *pBits )
{
	int i;
	DWORD dwBits = 0;
	PACKET_ID nLast = nPktLastReceived & 0xffff;
	UPDATE_ID nTest = nPktLastReceived;
	for ( i = 1; i <= 32; i++ )
	{
		nTest--;
		vector<UPDATE_ID>::iterator k;
		k = find( receivedPkts.begin(), receivedPkts.end(), nTest );
		if ( k != receivedPkts.end() )
			dwBits |= 1 << (i-1);
	}
	(*pBits).Write( &nLast, sizeof(nLast) );
	(*pBits).Write( &dwBits, 4 );
	// removing too old ack Pkts
	for ( i = receivedPkts.size() - 1; i >= 0; i-- )
	{
		if ( receivedPkts[i] + 32 < nPktLastReceived )
			receivedPkts.erase( receivedPkts.begin() + i );
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PACKET_ID CAckTracker::WriteAcks( BitStream *pBits, int nPktSize )
{
	++nFlyPackets;
	fTimeSinceLastSend = 0;
	// current packet number
	// const unsigned char *pStart = bits.GetCurrentPtr();
	PACKET_ID nPktCurrent = nPktSent++;

	(*pBits).Write( &nPktCurrent, sizeof(PACKET_ID) );
	
	// acks on received packets
	SendPktAcks( pBits );
	
	CUpdate &update = *sentUpdates.insert( sentUpdates.end() );
	update.fTimeCreated = fCurrentTime;
	update.nPktNumber = nPktCurrent; 
	update.bOnTheWindowEdge = nFlyPackets + 1 > fWindow;

//	bHasNewPacketToAck = false;
	// CRAP - fix rate tracking info
	return nPktCurrent;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CAckTracker::PacketLost( PACKET_ID pktID )
{
	bool bFound = false;
	list<CUpdate>::iterator it;
	for ( it = sentUpdates.begin(); it != sentUpdates.end(); )
	{
		if ( it->nPktNumber == pktID )
		{
			bFound = true;
			--nFlyPackets;
			fWindow -= 1.0f;
			fWindow = Max( MIN_WINDOWS_SIZE, fWindow );
			it = sentUpdates.erase( it );			
		}
		else
			++it;
	}
	ASSERT( bFound );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
