#include "StdAfx.h"
#include "NetPeer2Peer.h"
#include "NetLog.h"

namespace
{
	const bool bDebugTraceEnabled = false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NNet
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CP2PTracker
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
enum EPacket
{
	PKT_ADD_CLIENT,
	PKT_REMOVE_CLIENT,
	PKT_BROADCAST_MSG,
	PKT_DIRECT_MSG,
	PKT_ACK,
	PKT_KICK_ADDR
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CP2PTracker::AddOutputMessage( EOutMessage msg, const UCID _from, 
		const MemoryStream *pData, vector<UCID> *pReceived )
{
/*#ifdef LOG
	cout << "OUT ";
	switch ( msg )
	{
		case NEW_CIENT: cout << "new client " << _from.GetFastName() << endl; break;
		case REMOVE_CLIENT: cout << "del client " << _from.GetFastName() << endl; break;
		case DIRECT: cout << "direct from " << _from.GetFastName() << endl; break;
		case BROADCAST: cout << "broadcast from " << _from.GetFastName() << endl; break;
		default:
			NI_ALWAYS_ASSERT( "" );
			break;
	}
#endif*/
	SMessage &res = *output.insert( output.end() );
	res.msg = msg;
	res.from = _from;
	if ( pData )
		res.pkt = *pData;
	if ( pReceived )
		res.received = *pReceived;

	if ( bDebugTraceEnabled )
	{
		switch ( msg )
		{
		case DIRECT:		
			{
				netTraffic( NLogg::LEVEL_MESSAGE, NStr::StrFmt( "p2p: direct from: %d, size = %d", _from, res.pkt.GetSize() ) );
			}
			break;

		case NEW_CLIENT: 
			netTraffic( NLogg::LEVEL_MESSAGE, NStr::StrFmt( "p2p: new client from %d", _from ) );
			break;

		case REMOVE_CLIENT: 
			netTraffic( NLogg::LEVEL_MESSAGE, NStr::StrFmt( "p2p: del client %d", _from ) );
			break;
		}
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CP2PTracker::GetMessage( SMessage *pRes )
{
	if ( output.empty() )
		return false;
	*pRes = output.front();
	output.pop_front();
	return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CP2PTracker::SPeer* CP2PTracker::GetClient( UCID addr )
{
	hash_map<UCID,SPeer>::iterator it = clients.find( addr );
	if ( it != clients.end() )
		return &(it->second);
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CP2PTracker::IsActive( UCID addr )
{
	SPeer *pTest = GetClient( addr );
	if ( !pTest )
		return false;
	return pTest->IsActive();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CP2PTracker::CheckQueuedMessages( const UCID from )
{
	/*if ( bDebugTraceEnabled )
		DebugTrace( "CP2PTracker::CheckQueuedMessages: from=%d", from );*/
	// put all completely acked messages into output queue
	SPeer *pFrom = GetClient( from );
	while ( pFrom && !pFrom->messages.empty() )
	{
		SQMessage &b = pFrom->messages.front();
		if ( bDebugTraceEnabled )
		{
			DebugTrace( "CP2PTracker::CheckQueuedMessages: message with id=%d", b.nID );
		}
		bool bAcked = true;
		for ( list<SAck>::iterator i1 = b.acks.begin(); i1 != b.acks.end(); ++i1 )
		{
			if ( bDebugTraceEnabled )
				DebugTrace( "CP2PTracker::CheckQueuedMessages: ack from %d = %s", i1->from, i1->bAcked ? "true" : "false" );
			bAcked &= i1->bAcked;
		}
		if ( !bAcked )
		{
			if ( bDebugTraceEnabled )
			{
				DebugTrace( "CP2PTracker::CheckQueuedMessages: message is NOT completely acked" );
			}
			break;
		}
		if ( bDebugTraceEnabled )
		{
			DebugTrace( "CP2PTracker::CheckQueuedMessages: message is completely acked" );
		}
		vector<UCID> res;
		for ( list<SAck>::iterator i2 = b.acks.begin(); i2 != b.acks.end(); ++i2 )
			res.push_back( i2->from );
		if ( b.bDirect )
			AddOutputMessage( DIRECT, pFrom->addr, &b.msg );
		else
			AddOutputMessage( BROADCAST, pFrom->addr, &b.msg, &res );
		pFrom->messages.pop_front();
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// check if it is time to remove some inactive clients
void CP2PTracker::CheckCorpses()
{
	//list<UCID> idsToDel;
	vector<UCID> idsToDel;
	for ( hash_map<UCID,SPeer>::iterator i = clients.begin(); i != clients.end(); ++i )
	{
		if ( !i->second.IsActive()
			//&& i->second.messages.empty()
			&& i->second.requireKick.empty() )
		{
			AddOutputMessage( REMOVE_CLIENT, i->second.addr );
			idsToDel.push_back( i->first );
		}
	}
	for ( vector<UCID>::iterator it = idsToDel.begin(); it != idsToDel.end(); ++it )
	{
		clients.erase( *it );
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CP2PTracker::AddKickApprove( UCID victim, UCID kickFrom )
{
	SPeer *pV = GetClient( victim );
	if ( pV )
	{
		if ( find( pV->requireKick.begin(), pV->requireKick.end(), kickFrom ) == pV->requireKick.end() )
			pV->requireKick.push_back( kickFrom );
	}
	else
		NI_ALWAYS_ASSERT( "" );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CP2PTracker::ApproveKick( UCID victim, UCID from )
{
	SPeer *pV = GetClient( victim );
	if ( pV )
	{
		pV->requireKick.remove( from );
	}
	else
		NI_ALWAYS_ASSERT( NStr::StrFmt( "Try kick invalid client: %d", victim ) );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CP2PTracker::ReceiveDirect( const UCID from, MemoryStream &data )
{
	if ( bDebugTraceEnabled )
	{
		netTraffic( NLogg::LEVEL_MESSAGE, NStr::StrFmt( "p2p receive direct: from = %d, size = %d", from, data.GetSize() ) );		
	}
	// add to pending list
	SPeer *pWho = GetClient( from );
	SQMessage &b = *pWho->messages.insert( pWho->messages.end() );
	b.msg = data;
	b.nID = -1;
	b.bDirect = true;
	CheckQueuedMessages( from );	
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CP2PTracker::ReceiveBroadcast( const UCID from, MemoryStream &data, int nID )
{
	/*if ( bDebugTraceEnabled )
		DebugTrace( "CP2PTracker::ReceiveBroadcast: from=%d, nID=%d", from, nID );*/
	// add to pending list
	SPeer *pBroadcastSender = GetClient( from );
	SQMessage &b = *pBroadcastSender->messages.insert( pBroadcastSender->messages.end() );
	b.msg = data;
	b.nID = nID;
	b.bDirect = false;
	// set pending acks to intersection between active hosts from pBroadcastSender view and current host view
	for ( list<UCID>::iterator i = pBroadcastSender->clients.begin(); i != pBroadcastSender->clients.end(); ++i )
	{
		SPeer *pClientOfBroadcastSender = GetClient( *i );
		// we are not client of self so pClientOfBroadcastSender is zero for us
		// eventually ack from ourselves will not be required
		if ( pClientOfBroadcastSender && pClientOfBroadcastSender->IsActive() )
		{
			// add ack request if such client exist
			SAck &ack = *b.acks.insert( b.acks.end() );
			ack.from = *i;
			ack.bAcked = false;
			// seek through fast acks if required ack exists
			list<SFastAck>::iterator k = pClientOfBroadcastSender->fastacks.begin();
			while ( k != pClientOfBroadcastSender->fastacks.end() )
			{
				if ( k->broadcastSender == pBroadcastSender->addr && k->nID == nID )
				{
					ack.bAcked = true;
					k = pClientOfBroadcastSender->fastacks.erase( k );
				}
				else
					++k;
			}
			SendAck( *i, from, nID );
		}
	}
	CheckQueuedMessages( from ); // can be no acks required
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CP2PTracker::ReceiveAck( const UCID from, const UCID addressOfBroadcastSender, int nID )
{
	/*if ( bDebugTraceEnabled )
		DebugTrace( "CP2PTracker::ReceiveAck: from=%d, addressOfBroadcastSender=%d, nID=%d",
			from, addressOfBroadcastSender, nID );*/
	SPeer *pBroadcastSender = GetClient( addressOfBroadcastSender );
	if ( !pBroadcastSender )
		return;
	// find message in question and remove pending ack from xx
	bool bFound = false;
	for ( list<SQMessage>::iterator i = pBroadcastSender->messages.begin(); i != pBroadcastSender->messages.end(); ++i )
	{
		if ( i->nID == nID )
		{
			SQMessage &b = *i;
			bFound = true;
			for ( list<SAck>::iterator k = b.acks.begin(); k != b.acks.end(); ++k )
			{
				if ( k->from == from )
				{
					ASSERT( !k->bAcked );
					k->bAcked = true;
					/*if ( bDebugTraceEnabled )
						DebugTrace( "CP2PTracker::ReceiveAck: ack accepted, from=%d, addressOfBroadcastSender=%d, nID=%d",
							from, addressOfBroadcastSender, nID );*/
					break;
				}
			}
			break;
		}
	}
	SPeer *pFrom = GetClient( from );
	if ( bFound )
		CheckQueuedMessages( addressOfBroadcastSender );
	else 
	{
		// save ack for the future
		// if ack sender is inactive no messages from him will be received and ack is useless
		if ( pFrom->IsActive() ) 
		{
			SFastAck &b = *pFrom->fastacks.insert( pFrom->fastacks.end() );
			b.broadcastSender = addressOfBroadcastSender;
			b.nID = nID;
		}
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CP2PTracker::ReceiveAddClient( const UCID from, const UCID clientAddr, MemoryStream &_addrInfo, bool bIsBroadcast )
{
	/*if ( bDebugTraceEnabled )
		DebugTrace( "CP2PTracker::ReceiveAddClient: from=%d, clientAddr=%d, bIsBroadcast=%s",
			from, clientAddr, bIsBroadcast ? "true" : "false" );*/
		//if this is client being kicked then respond with kick addr and do nothing more
	SPeer *pTest = GetClient( clientAddr );
	if ( pTest )
	{
		if ( !pTest->IsActive() )
		{
			// pWho бредит - этого парня мы как раз кикаем
			SendRemoveClient( from, clientAddr );
			return;
		}
	}
	else
		AddNewClient( clientAddr, _addrInfo, bIsBroadcast ); // это что-то новое, нужно добавить в свой список
	// now to remove buddy we need to receive kick messages from every client pWho talked about him
	AddKickApprove( clientAddr, from );
	SPeer *pWho = GetClient( from );
	if ( !pWho )
		return;
	for ( list<UCID>::iterator i = pWho->clients.begin(); i != pWho->clients.end(); ++i )
	{
		SPeer *pT = GetClient( *i );
		if ( pT && pT->IsActive() )
			AddKickApprove( clientAddr, *i );
		else
			ASSERT( pT );
	}
	// client is added to peer tracking record
	/*if ( bDebugTraceEnabled )
		DebugTrace( "CP2PTracker::ReceiveAddClient: client %d added to client %d", clientAddr, from );*/
	pWho->clients.push_back( clientAddr );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CP2PTracker::ReceiveRemoveClient( const UCID from, const UCID corpse, bool bIsBroadcast )
{
	/*if ( bDebugTraceEnabled )
	{
		DebugTrace( "CP2PTracker::ReceiveRemoveClient: from=%d, corpse=%d, bIsBroadcast=%s",
			from, corpse, bIsBroadcast ? "true" : "false" );
	}*/
	SPeer *pFrom = GetClient( from );
	if ( !pFrom )
		return;
	bool bHadCorpse = pFrom->HasClient( corpse );
	//ASSERT( find( pFrom->clients.begin(), pFrom->clients.end(), corpse ) != pFrom->clients.end() );
	pFrom->RemoveClient( corpse );
  DebugTrace("Client %d kicked because it is dead.", corpse);
	KickClient( corpse, bIsBroadcast );

	// every ack for broadcast message from pFrom awaiting ack from client corpse 
	// is approved via ack remove
	for ( list<SQMessage>::iterator i = pFrom->messages.begin(); i != pFrom->messages.end(); ++i )
	{
		SQMessage &b = *i;
		for ( list<SAck>::iterator k = b.acks.begin(); k != b.acks.end(); )
		{
			if ( k->from == corpse )
				k = b.acks.erase( k );
			else
				++k;
		}
	}
	CheckQueuedMessages( from );
	SPeer *pCorpse = GetClient( corpse );
	if ( pCorpse )
	{
		ApproveKick( corpse, pFrom->addr );
		ASSERT( !pCorpse->IsActive() );
		// every pending message from corpse awaiting ack from pFrom is removed
		for ( list<SQMessage>::iterator i = pCorpse->messages.begin(); i != pCorpse->messages.end(); )
		{
			SQMessage &b = *i;
			bool bRemove = false;
			for ( list<SAck>::iterator k = b.acks.begin(); k != b.acks.end(); ++k )
			{
				if ( k->from == pFrom->addr && k->bAcked == false )
					bRemove = true;
			}
			if ( bRemove )
			{
				/*if ( bDebugTraceEnabled )
				{
					DebugTrace( "CP2PTracker::ReceiveRemoveClient:"
						" message with id=%d removed from awaiting ack messages queue of client=%d",
						b.nID, pCorpse->addr );
				}*/
				i = pCorpse->messages.erase( i );
			}
			else
				++i;
		}
		CheckQueuedMessages( corpse );
	}
	else
		ASSERT( !bHadCorpse ); // was removed too early
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static int nBroadcastID = 1;
void CP2PTracker::SendBroadcast( MemoryStream &pkt )
{
	for ( hash_map<UCID,SPeer>::iterator i = clients.begin(); i != clients.end(); ++i )
	{
		if ( i->second.IsActive() )
			SendBroadcast( i->second.addr, nBroadcastID, pkt );
	}
	++nBroadcastID;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//void CP2PTracker::SendDirect( UCID addr, MemoryStream &data )
void CP2PTracker::SendDirect( UCID addr, MemoryStream &data )
{
	SPeer* peer = GetClient( addr );
	NI_ASSERT( peer != 0, "Try to send packet to unknown client!" );
	if ( !peer )
		return;

	MemoryStream pkt;
	{
		// prepare data to coping all stream
		data.Seek( 0, SEEKORIGIN_BEGIN );

		// p2p message id
		pkt << (char)PKT_DIRECT_MSG;
		// data
		pkt.CopyFrom( &data );
		// push outgoing packet
		packets.push_back( SPacket( addr, pkt ) );
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CP2PTracker::AddNewClient( const UCID addr, MemoryStream &_addrInfo, bool bIsBroadcast )
{
/*#ifdef LOG
	cout << "ADD attempt, client " << addr.GetFastName() << endl;
#endif*/
	SPeer *pTest = GetClient( addr );
//	ASSERT( !pTest );
	if ( pTest )
		return;

/*#ifdef LOG
	cout << "ADD, client " << addr.GetFastName() << " ID=" << newID << endl;
#endif*/
	AddOutputMessage( NEW_CLIENT, addr, &_addrInfo );
	// new client addr is added and for every existing channel info about that is sent
	for ( hash_map<UCID,SPeer>::iterator i1 = clients.begin(); i1 != clients.end(); ++i1 )
	{
		if ( bIsBroadcast && ( i1->second.IsActive() ) )
			SendAddClient( i1->second.addr, addr, _addrInfo );
	}
	// to client addr info sent about every active SPeer on the moment
	SPeer& res = clients[addr];
	res.addr = addr;	
	res.bActive = true;
	res.addrInfo = _addrInfo;
	for ( hash_map<UCID,SPeer>::iterator i2 = clients.begin(); i2 != clients.end(); ++i2 )
	{
		if ( bIsBroadcast && ( i2->second.IsActive() ) && &res != &i2->second )
		{
			SendAddClient( addr, i2->second.addr, i2->second.addrInfo );
			res.requireKick.push_back( i2->second.addr );
			AddKickApprove( i2->second.addr, addr );
		}
	}
	//clients[res.addr] = res;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// mark client as corpse and inform everybody about it
// no messages from this address will be received anymore
void CP2PTracker::KickClient( const UCID addr, bool bIsBroadcast )
{
	SPeer *pVictim = GetClient( addr );
	/*if ( bDebugTraceEnabled )
		DebugTrace( "CP2PTracker::KickClient: addr=%d, bIsBroadcast=%s", addr, bIsBroadcast ? "true" : "false" );*/
	if ( pVictim && pVictim->IsActive() )
	{
		kicks.push_back( addr );
		/*if ( bDebugTraceEnabled )
			DebugTrace( "CP2PTracker::KickClient: %d added to kick messages awaiting send", addr, bIsBroadcast ? "true" : "false" );*/

		pVictim->bActive = false;
		for ( hash_map<UCID,SPeer>::iterator i1 = clients.begin(); i1 != clients.end(); ++i1 )
		{
			ApproveKick( (i1->second).addr, addr ); // мертвые не кусаются и вряд ли пришлют подтверждение о kick
			if ( bIsBroadcast && ( i1->second.IsActive() ) )
				SendRemoveClient( i1->second.addr, addr );
		}
		// every fast ack received about messages from victim should be deleted
		for ( hash_map<UCID,SPeer>::iterator i2 = clients.begin(); i2 != clients.end(); ++i2 )
		{
			for ( list<SFastAck>::iterator k = i2->second.fastacks.begin(); k != i2->second.fastacks.end(); )
			{
				if ( k->broadcastSender == addr )
					k = i2->second.fastacks.erase( k );
				else
					++k;
			}
		}
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CP2PTracker::SendRemoveClient( UCID destAddr, const UCID whom )
{
/*#ifdef LOG
	cout << "SEND delclient to " << destAddr.GetFastName() << " client " << whom.GetFastName() << endl;
#endif*/
	MemoryStream pkt;
	pkt << (char)PKT_REMOVE_CLIENT;
	pkt << whom;
	packets.push_back( SPacket( destAddr, pkt ) );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CP2PTracker::SendAddClient( const UCID dest, const UCID whom, MemoryStream &addrInfo )
{
/*#ifdef LOG
	cout << "SEND addclient to " << dest.GetFastName() << " client " << whom.GetFastName() << endl;
#endif*/
	MemoryStream pkt;
	pkt << (char)PKT_ADD_CLIENT;
	pkt << whom;
	int nSize = addrInfo.GetSize();
	pkt << nSize;
	pkt.Write( addrInfo.GetBuffer(), nSize );
	packets.push_back( SPacket( dest, pkt ) );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CP2PTracker::SendBroadcast( const UCID dest, int nID, MemoryStream &data )
{
	/*if ( bDebugTraceEnabled )
		DebugTrace( "CP2PTracker::SendBroadcast: dest=%d, nID=%d", dest, nID );*/
	MemoryStream pkt;
	pkt << (char)PKT_BROADCAST_MSG;
	pkt << nID;
	data.Seek( 0, SEEKORIGIN_BEGIN );
	pkt.CopyFrom( &data );
	packets.push_back( SPacket( dest, pkt ) );
	
#ifdef __LOG__
	data.Seek( 0, SEEKORIGIN_BEGIN );
	
	BYTE cMsgID;
	data >> cMsgID;
	if ( cMsgID != 9 )
		Singleton<IConsoleBuffer>()->WriteASCII( CONSOLE_STREAM_CONSOLE, NStr::StrFmt( "p2p: send broadcast, msg %d", (int)cMsgID ), 0xffffff00, true );
#endif
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CP2PTracker::SendAck( const UCID addr, const UCID addressOfBroadcastSender, int nID )
{
	/*if ( bDebugTraceEnabled )
		DebugTrace( "CP2PTracker::SendAck: addr=%d, addressOfBroadcastSender=%d, nID=%d",
			addr, addressOfBroadcastSender, nID );*/
	MemoryStream pkt;
	pkt << (char)PKT_ACK;
	pkt << addressOfBroadcastSender;
	pkt << nID;
	packets.push_back( SPacket( addr, pkt ) );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void ReadRest( MemoryStream &src, MemoryStream *pDst )
{
	pDst->CopyFrom( &src );
	//src.ReadTo( pDst, src.GetSize() - src.GetPosition() );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
namespace
{
	char const* Packet2String( EPacket packet )
	{
		switch( packet )
		{
		case PKT_ADD_CLIENT:
			return "PKT_ADD_CLIENT";
		case PKT_REMOVE_CLIENT:
			return "PKT_REMOVE_CLIENT";
		case PKT_BROADCAST_MSG:
			return "PKT_BROADCAST_MSG";
		case PKT_DIRECT_MSG:
			return "PKT_DIRECT_MSG";
		case PKT_ACK:
			return "PKT_ACK";
		default:
			return "default";
		}
	}
}
*/
void CP2PTracker::ProcessPacket( const UCID from, MemoryStream &pkt, bool bIsBroadcast )
{
	SPeer *pWho = GetClient( from );
	if ( !pWho || !pWho->IsActive() )
		return;
	pkt.Seek( 0, SEEKORIGIN_BEGIN );
	EPacket t = (EPacket)0;
	pkt.Read( &t, sizeof(char) );

  //NetLog
	//netTraffic( NLogg::LEVEL_MESSAGE, NStr::StrFmt( "*** P2PTracker process packet from: %d, packet id: %s, size = %d",
	// from, Packet2String( t ).c_str(), pkt.GetSize() ) );

	switch ( t )
	{
		case PKT_ADD_CLIENT:
			{
				UCID clientAddr;
				MemoryStream addrInfo;
				pkt >> clientAddr;
				int nSize;
				pkt >> nSize;
				if ( nSize < 1024 )
				{
					addrInfo.SetSize( nSize );
					pkt.Read( addrInfo.GetBuffer(), nSize );
					addrInfo.Seek( 0, SEEKORIGIN_BEGIN );
				}
				ReceiveAddClient( from, clientAddr, addrInfo, bIsBroadcast );
			}
			break;
		case PKT_REMOVE_CLIENT:
			{
				UCID clientAddr;
				pkt >> clientAddr;
				ReceiveRemoveClient( from, clientAddr, bIsBroadcast );
			}
			break;
		case PKT_BROADCAST_MSG:
			{
				MemoryStream data;
				int nID;
				pkt >> nID;
				ReadRest( pkt, &data );
				ReceiveBroadcast( from, data, nID );
			}
			break;
		case PKT_DIRECT_MSG:
			{
				MemoryStream data;
				ReadRest( pkt, &data );
				ReceiveDirect( from, data );
			}
			break;
		case PKT_ACK:
			{
				int nID;
				UCID addressOfBroadcastSender;
				pkt >> addressOfBroadcastSender;
				pkt >> nID;
				ReceiveAck( from, addressOfBroadcastSender, nID );
			}
			break;
		default:
			NI_ALWAYS_ASSERT( "" );
			break;
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
