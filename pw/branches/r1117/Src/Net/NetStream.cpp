#include "StdAfx.h"
#include "NetStream.h"
#include "../System/BitStreams.h"
#include "NetLog.h"

namespace NNet
{
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CStreamTracker
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CStreamTracker::CStreamTracker(): nChannelOutputOffset(0), nChannelInputOffset(0)
{
}
// return true if test offset is before border
bool CStreamTracker::IsBefore( CHANNEL_DATA_OFFSET border, CHANNEL_DATA_OFFSET test )
{
	return ((CHANNEL_DATA_OFFSET)(test - border)) > 0x80000000;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CStreamTracker::WriteMsg( PACKET_ID nPkt, BitStream *pBits, int nSizeLimit )
{
	ASSERT( nSizeLimit <= N_MAX_PACKET_SIZE );
	if ( channelOutList.empty() )
	{
		if ( channelOutBuf.GetMaxReadSize() < N_MAX_PACKET_SIZE )
		{
			while ( !outList.empty() && channelOutBuf.GetMaxWriteSize() >= outList.front().GetSize() )
			{
				MemoryStream &m = outList.front();
				channelOutBuf.Write( m.GetBuffer(), m.GetSize() );
				outList.pop_front();
			}
		}
		if ( channelOutBuf.GetMaxReadSize() == 0 )
		{
			SChannelBlock block;
			block.nOffset = nChannelOutputOffset;
			block.nLength = 0;
			pBits->Write( &block, block.GetSendSize() );
			return;
		}
		else
		{
			SChannelBlock *pMSVCSuck = 0;
			int nMaxSize = nSizeLimit - pMSVCSuck->GetHeaderSize();
			nMaxSize = Min( nMaxSize, 255 );
			int nSize = Min( nMaxSize, channelOutBuf.GetMaxReadSize() );
			
			SChannelBlock &block = *channelOutFlyList.insert( channelOutFlyList.end() );
			block.nOffset = nChannelOutputOffset;
			block.nLength = nSize;
			channelOutBuf.Read( block.cData, nSize );
			nChannelOutputOffset += nSize;
		}
	}
	else
	{
		// find first block
		SChannelBlockList::iterator i = channelOutList.begin(), ibest = i;
		CHANNEL_DATA_OFFSET bestOffset = i->nOffset;
		for ( ; i != channelOutList.end(); ++i )
		{
			if ( IsBefore( bestOffset, i->nOffset ) )
			{
				bestOffset = i->nOffset;
				ibest = i;
			}
		}
		PACKET_ID oldPkt = ibest->nPkt;
		channelOutFlyList.splice( channelOutFlyList.end(), channelOutList, ibest );
		reassign[ oldPkt ] = nPkt;
	}
	// send channel data
	SChannelBlock &block = channelOutFlyList.back();
	ASSERT( block.GetSendSize() <= nSizeLimit );
	block.nPkt = nPkt;

	pBits->Write( &block, block.GetSendSize() );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CStreamTracker::ReadMsg( BitStream &bits )
{
	// receive channel data
	SChannelBlock block;
	bits.Read( &block, block.GetHeaderSize() );
	bits.Read( block.cData, block.nLength );

	// is not this data already received?
	if(IsBefore( nChannelInputOffset, block.nOffset ) || block.nLength == 0 )
	{
		return false;
	} 
	channelInList.push_back( block );
	// gather input blocks into stream
	for(;;)
	{
		bool bCont = false;
		for ( SChannelBlockList::iterator i = channelInList.begin(); i != channelInList.end(); )
		{
			if ( i->nOffset == nChannelInputOffset )
			{
				if ( channelInBuf.GetMaxWriteSize() < i->nLength )
        {
          NI_ASSERT(0, "Packet size too large! Data lost!");
					break; // avoid buffer overflow
        }
				int nRes = channelInBuf.Write( i->cData, i->nLength );
				ASSERT( nRes == i->nLength ); // buffer overflow
				nChannelInputOffset += i->nLength;
				i = channelInList.erase( i );
				bCont = true;
			}
			else
				++i;
		}
		if ( !bCont )
			break;
	}        
	// remove redundant blocks
	for ( SChannelBlockList::iterator i = channelInList.begin(); i != channelInList.end(); )
	{
		if ( IsBefore( nChannelInputOffset, i->nOffset ) )
			i = channelInList.erase( i );
		else
			++i;
	}          
	return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CStreamTracker::Rollback( const vector<PACKET_ID> &pkts )
{
	for ( int it = 0; it < pkts.size(); ++it )
	{
		PACKET_ID nPkt = pkts[it];
		SChannelBlockList::iterator i;
		for ( i = channelOutFlyList.begin(); i != channelOutFlyList.end(); )
		{
			if ( i->nPkt == nPkt )
			{
				channelOutList.splice( channelOutList.end(), channelOutFlyList, i );
				break;
			}
			else
				++i;
		}
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CStreamTracker::Erase( const vector<PACKET_ID> &pkts )
{
	for ( int i = 0; i < pkts.size(); ++i )
	{
		PACKET_ID nPkt = pkts[i];
		hash_map< PACKET_ID, PACKET_ID >::iterator k = reassign.find( nPkt );
		if ( k != reassign.end() )
			reassign.erase( k );
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CStreamTracker::Commit( const vector<PACKET_ID> &pkts )
{
	for ( int i = 0; i < pkts.size(); ++i )
	{
		PACKET_ID nPkt = pkts[i];
		for(;;)
		{
			hash_map< PACKET_ID, PACKET_ID >::iterator k = reassign.find( nPkt );
			if ( k == reassign.end() )
				break;
			nPkt = k->second;
			reassign.erase( k );
		}
		SChannelBlockList::iterator k;
		bool isFound = false;
		for ( k = channelOutFlyList.begin(); k != channelOutFlyList.end(); )
		{
			if ( k->nPkt == nPkt )
			{
				channelOutFlyList.erase( k );
				isFound = true;
				break;
			}
			++k;
		}
		if ( !isFound )
		{
			for ( k = channelOutList.begin(); k != channelOutList.end(); )
			{
				if ( k->nPkt == nPkt )
				{
					channelOutList.erase( k );
					break;
				}
				++k;
			}
		}
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
