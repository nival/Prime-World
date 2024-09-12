#pragma once

#include <winsock2.h>
#include "NetAcks.h"
/////////////////////////////////////////////////////////////////////////////////////
namespace NNet
{
/////////////////////////////////////////////////////////////////////////////////////
template<int N_SIZE>
class CRingBuffer
{
	unsigned int nReadPtr, nWritePtr;
	char szBuffer[ N_SIZE ];
public:
	CRingBuffer() { nReadPtr = 0; nWritePtr = 0; }
	int GetMaxReadSize() const { return (nWritePtr - nReadPtr + N_SIZE) % N_SIZE; }
	int GetMaxWriteSize() const { return N_SIZE - 1 - GetMaxReadSize(); }
	int Peek( void *pBuf, int nBufSize ) const
	{
		int nRes = Min( nBufSize, GetMaxReadSize() );
		if ( nReadPtr + nRes > N_SIZE )
		{
			int nRight = N_SIZE - nReadPtr;
			memcpy( pBuf, szBuffer + nReadPtr, nRight );
			memcpy( ((char*)pBuf) + nRight, szBuffer, nRes - nRight );
		}
		else
		{
			memcpy( pBuf, szBuffer + nReadPtr, nRes );
		}
		return nRes;
	}
	int Read( void *pBuf, int nBufSize )
	{
		int nRes = Peek( pBuf, nBufSize );
		nReadPtr = ( nReadPtr + nRes ) % N_SIZE;
		return nRes;
	}
	int Write( const void *pBuf, int nLength )
	{
		ASSERT( GetMaxReadSize() + nLength < N_SIZE );
		int nRes = Min( GetMaxWriteSize(), nLength );

		if ( nWritePtr + nRes > N_SIZE )
		{
			int nRight = N_SIZE - nWritePtr;
			memcpy( szBuffer + nWritePtr, pBuf, nRight );
			memcpy( szBuffer, ((const char*)pBuf) + nRight, nRes - nRight );
			nWritePtr = ( nWritePtr + nRes ) % N_SIZE;
		}
		else
		{
			memcpy( szBuffer + nWritePtr, pBuf, nRes );
			nWritePtr = nWritePtr + nRes;
		}
		return nRes;
	}
};
/////////////////////////////////////////////////////////////////////////////////////
// streamed connection, input/output buffers
//const int N_STREAM_BUFFER = 32768;
const int N_STREAM_BUFFER = 128000;
const int N_MAX_PACKET_SIZE = 4096; // low level packet size
class CStreamTracker
{
	typedef unsigned int CHANNEL_DATA_OFFSET;
#pragma pack(push,1)
	struct SChannelBlock
	{
		CHANNEL_DATA_OFFSET nOffset;
		unsigned char nLength;
		char cData[256];
		PACKET_ID nPkt;
		
		int GetSendSize() const { return sizeof(nOffset) + sizeof(nLength) + nLength; }
		int GetHeaderSize() const { return sizeof(nOffset) + sizeof(nLength); }
	};
#pragma pack(pop)

public:
	// channel data
	CRingBuffer<N_STREAM_BUFFER> channelInBuf;
	list<MemoryStream> outList;
private:

	CRingBuffer<N_STREAM_BUFFER> channelOutBuf;
	
	// streaming data control structures
	// текущее смещение отсылаемых и принимаемых данных
	CHANNEL_DATA_OFFSET nChannelOutputOffset, nChannelInputOffset;
	typedef list<SChannelBlock> SChannelBlockList;
	SChannelBlockList channelOutFlyList, channelOutList, channelInList;
	hash_map< PACKET_ID, PACKET_ID > reassign;

	static bool IsBefore( CHANNEL_DATA_OFFSET border, CHANNEL_DATA_OFFSET test );

public:
	CStreamTracker();
	bool HasOutData() { return !outList.empty() || channelOutBuf.GetMaxReadSize() != 0 || !channelOutList.empty(); }
	bool CanReadMsg() const { return channelInBuf.GetMaxWriteSize() > N_MAX_PACKET_SIZE; }
	void WriteMsg( PACKET_ID nPkt, BitStream *pBits, int nSizeLimit );
	bool ReadMsg( BitStream &bits );
	void Rollback( const vector<PACKET_ID> &pkts );
	void Erase( const vector<PACKET_ID> &pkts );
	void Commit( const vector<PACKET_ID> &pkts );
};
/////////////////////////////////////////////////////////////////////////////////////
}
