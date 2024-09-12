#include "StdAfx.h"

#include <process.h>
#include "../System/Thread.h"
#include "NetA4.h"
#include "../System/BitStreams.h"
#include "NetLowest.h"
#include "../System/SystemLog.h"
#include "../System/SyncProcessorState.h"
#include "NetLog.h"
#include "../System/BinChunkSaver.h"
//#include "LinksManager.h"


#ifdef LOG
#undef LOG
#endif

namespace
{
	const bool bDebugTracePackets = true;
	const bool bDebugTraceMessages = true;
}

const int PACKET_SIZE = 500;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NNet
{
bool CNetDriver::bIsServer = false;
using namespace NWin32Helper;
static threading::Mutex netDriverMutex;
//const float MIN_TIME_BETWEEN_PACKETS_PER_PEER = 0.050f;
const float MIN_TIME_BETWEEN_PACKETS_PER_PEER = 0.050f;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// interaction with master server is accomplished with different object
// if so then it should be possible to start
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
enum EPacket
{
	NORMAL,
	LOGIN,
	REQUEST_SERVER_INFO,
	SERVER_INFO,
	ACCEPTED,
	REJECTED,
	LOGOUT,
	TRY_SHORTCUT,
	NOP,
	KICK,
	IP_NETWORK_BROADCAST
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace
{
	char const* Packet2String( EPacket packet )
	{
		switch( packet )
		{
		case NORMAL:
			return "NORMAL";
		case LOGIN:
			return "LOGIN";
		case REQUEST_SERVER_INFO:
			return "REQUEST_SERVER_INFO";
		case SERVER_INFO:
			return "SERVER_INFO";
		case ACCEPTED:
			return "ACCEPTED";
		case REJECTED:
			return "REJECTED";
		case LOGOUT:
			return "LOGOUT";
		case TRY_SHORTCUT:
			return "TRY_SHORTCUT";
		case NOP:
			return "NOP";
		case KICK:
			return "KICK";
		case IP_NETWORK_BROADCAST:
			return "IP_NETWORK_BROADCAST";
		default:
			return "default";
		}
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GetNOPStream( MemoryStream *pNOP )
{
	pNOP->SetSize( 0 );
	pNOP->Seek( 0, SEEKORIGIN_BEGIN );
	EPacket ePacket = NOP;
	pNOP->Write( &ePacket, 1 );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const int N_APPLICATIONID = 0x45143100;
class CSendPacket
{
	ILinksManager *pLinks;
	const CNodeAddress &addr;
	static MemoryStream pkt;
	static BitLocker bits;
	static bool bLastPacket;
	
	EPacket packetId;

public:
	CSendPacket( const CNodeAddress &_addr, EPacket packet, ILinksManager *_pLinks ) : addr( _addr ), pLinks( _pLinks ), packetId( packet ) 
	{
		pkt.Seek( 0, SEEKORIGIN_BEGIN );
		bits.LockWrite( pkt, N_MAX_PACKET_SIZE + 1024 );
		bits.Write( &packet, 1 );
	}
	CSendPacket( const CNodeAddress &_addr, EPacket packet, CP2PTracker::UCID clientID, ILinksManager *_pLinks ): addr(_addr), pLinks(_pLinks), packetId( packet )
	{		
		pkt.Seek( 0, SEEKORIGIN_BEGIN );
		bits.LockWrite( pkt, N_MAX_PACKET_SIZE + 1024 );
		bits.Write( &packet, 1 );
		bits.Write( &clientID, sizeof(clientID) );
	}
	~CSendPacket()
	{		
		bits.Free();
		pkt.SetSize( pkt.GetPosition() );
		bLastPacket = pLinks->Send( addr, pkt );

		//netTraffic( NLogg::LEVEL_MESSAGE, NStr::StrFmt( "Send packet: %s to: %s, (packet size = %d)", 
		//	Packet2String( packetId ).c_str(), addr.GetFastName().c_str(), pkt.GetSize() ) );
	}
	BitStream* GetBits() { return &bits; }
	static bool GetResult() { return bLastPacket; }
private:
  CSendPacket operator = (CSendPacket const &)
  {
    NI_ALWAYS_ASSERT("should not be called");
  }
};
MemoryStream CSendPacket::pkt;
BitLocker CSendPacket::bits;
bool CSendPacket::bLastPacket = true;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// packet to/from stream
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static bool CanReadPacket( const CRingBuffer<N_STREAM_BUFFER> &buf )
{
	if ( buf.GetMaxReadSize() < sizeof(int) )
		return false;		

	int nSize;
	buf.Peek( &nSize, sizeof(nSize) );
	if ( nSize & 1 )
		nSize &= 0xff;
	nSize >>= 1;
	if ( buf.GetMaxReadSize() >= nSize + (nSize >= 128 ? 4 : 1) )
		return true;
	else
	{
		return false;
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void WritePacket( list<MemoryStream> *pDst, MemoryStream &pkt )
{
	NI_ASSERT( pkt.GetSize() < N_STREAM_BUFFER - 1000, NStr::StrFmt( "Wrong memory stream size (%d)", pkt.GetSize() ) );
	MemoryStream &b = *( pDst->insert( pDst->end() ) );
	int nSize = pkt.GetSize();
	if ( nSize >= 128 )
	{
		nSize <<= 1;
		b.Write( &nSize, 4 );
	}
	else
	{
		nSize <<= 1;
		nSize |= 1;
		b.Write( &nSize, 1 );
	}
	b.Write( pkt.GetBuffer(), pkt.GetSize() );
}
static void ReadPacket( CRingBuffer<N_STREAM_BUFFER> &src, MemoryStream *pDst )
{
	NI_ASSERT( CanReadPacket( src ), "Can't read a packet" );
	int nSize = 0;
	src.Read( &nSize, 1 );
	if ( (nSize & 1) == 0 )
		src.Read( ((char*)&nSize) + 1, 3 );
	nSize >>= 1;
	pDst->SetSize( nSize );
	src.Read( pDst->GetBuffer(), nSize );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ************************************************************************************************************************ //
// **
// ** net driver
// **
// **
// **
// ************************************************************************************************************************ //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static unsigned __stdcall TheThreadProc( LPVOID lpParameter )
{
  SyncProcessorState();
	CNetDriver *pNet = reinterpret_cast<CNetDriver*>(lpParameter);
  //boost net driver priority since it is already nice enough to other threads 
  SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_HIGHEST);
	// run function
	pNet->StartThread();
	while(pNet->CanWork())
	{
		Sleep( 10 );
		pNet->Step();
	}
	pNet->FinishThread();
	return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CNetDriver::SClientAddressInfo::NeedToTryShortcut() const
{
	// We need to try shortcut if there is at least one local addr not equal to inet addr
	CNodeAddress addr;
	for ( int i = 0; i < N_MAX_HOST_HOMES && localAddress.GetAddress( i, &addr ); ++i )
	{
		if ( addr.SameIP( inetAddress ) )
			continue;
		return true;
	}
	return false;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
IDriver::EState CNetDriver::GetState() const 
{
//	threading::MutexLock mutexLock( netDriverMutex );
	return state; 
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CNetDriver::StartThread()
{
	SetEvent( hThreadReport );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CNetDriver::CanWork()
{
	return IsValid(this) && WaitForSingleObject( hStopCommand, 0 ) != WAIT_OBJECT_0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CNetDriver::FinishThread()
{
	SetEvent( hThreadReport );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CNetDriver::CreateEvents()
{
	hThread = 0;
	hThreadReport = CreateEvent( 0, true, false, 0 );
	hStopCommand = CreateEvent( 0, true, false, 0 );
}
////////////////////////////////////////////////////////////////////////////////////////////////////
CNetDriver::CNetDriver() : serverInfo( 0 ), login( 0 ), state( INACTIVE ), bUseClientToClientShortcuts( true )
{
	CreateEvents();
	bIsBroadcast = true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CNetDriver::CNetDriver( const SNetDriverConsts &_consts, bool _bIsBroadcast ) 
: serverInfo( 0 ), login( 0 ), state( INACTIVE ), consts(_consts), bIsBroadcast(_bIsBroadcast),
bUseClientToClientShortcuts( true )
{
	CreateEvents();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CNetDriver::KillThread()
{
	if ( hThread )
	{
		DWORD dwExitCode = 0;
		if ( !GetExitCodeThread( hThread, &dwExitCode ) || dwExitCode != STILL_ACTIVE )
			return;
		SetEvent( hStopCommand );
		WaitForSingleObject( hThreadReport, INFINITE );

		CloseHandle( hThread );
		hThread = 0;
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////
CNetDriver::~CNetDriver()
{
	KillThread();

  threading::MutexLock mutexLock( netDriverMutex );
	
	switch ( state )
	{
		case ACTIVE:
			{
				if ( ( !bIsClient ) || ( bIsBroadcast ) )
					for ( CPeerList::iterator i = clients.begin(); i != clients.end(); ++i )
					{
						CSendPacket p( i->second.currentAddr, LOGOUT, i->second.clientID, pLinks );
						netTraffic( NLogg::LEVEL_MESSAGE, NStr::StrFmt( "Send packet: %s to: %s", 
							Packet2String( LOGOUT ), i->second.currentAddr.GetFastName().c_str() ) );
					}
				else
					//sends message to server only
					for ( CPeerList::iterator i = clients.begin(); i != clients.end(); ++i )
					{
						if ( i->second.clientID == 0 ) 
						{
							CSendPacket p( i->second.currentAddr, LOGOUT, i->second.clientID, pLinks );
							netTraffic( NLogg::LEVEL_MESSAGE, NStr::StrFmt( "Send packet: %s to: %s", 
								Packet2String( LOGOUT ), i->second.currentAddr.GetFastName().c_str() ) );
						}
					}
					break;
			}
		case CONNECTING:
			{
				CSendPacket p( login.GetLoginTarget(), LOGOUT, 0xFFFFFFFF, pLinks );
				netTraffic( NLogg::LEVEL_MESSAGE, NStr::StrFmt( "Send packet: %s to: %s", 
					Packet2String( LOGOUT ), login.GetLoginTarget().GetFastName().c_str() ) );
			}
			break;
	}

	//{
	//	CNodeAddress broadcast;
	//	broadcast.SetInetName( "255.255.255.255", nGamePort );
	//	CSendPacket pkt( broadcast, IP_NETWORK_BROADCAST, login.GetSelfClientID(), pLinks );
	//	//CSendPacket p( i->second.currentAddr, LOGOUT, i->second.clientID, pLinks );
	//	//netTraffic( NLogg::LEVEL_MESSAGE, NStr::StrFmt( "Send packet: %s to: %s", 
	//	//	Packet2String( LOGOUT ).c_str(), i->second.currentAddr.GetFastName().c_str() ) );
	//}

	CloseHandle( hThreadReport );
	CloseHandle( hStopCommand );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CNetDriver::Init( const APPLICATION_ID nApplicationID, const int _nGamePort, bool bClientOnly, ILinksManager *pLinksManager )
{
	NI_ASSERT( pLinksManager != 0, "Can't initialize by 0 linksManager" );
	pLinks = pLinksManager;
	
	serverInfo.Init( nApplicationID );
	login.Init( nApplicationID );
	nGamePort = _nGamePort;
	//
	state = INACTIVE;
	lastReject = NONE;
	bAcceptNewClients = true;
	NHPTimer::GetTime( lastTime );
	//
	bIsClient = bClientOnly;

	unsigned int dwThreadId;
	ResetEvent( hStopCommand );
	ResetEvent( hThreadReport );
	hThread = (HANDLE)_beginthreadex( 0, 1024*1024, TheThreadProc, reinterpret_cast<LPVOID>(this), 0, &dwThreadId );
	WaitForSingleObject( hThreadReport, INFINITE );
	ResetEvent( hThreadReport );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CNetDriver::SPeer* CNetDriver::GetClientByAddr( const CNodeAddress &addr )
{
	for ( CPeerList::iterator i = clients.begin(); i != clients.end(); ++i )
	{
		if ( i->second.currentAddr == addr )
			return &(i->second);
	}
	return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
CNetDriver::SPeer* CNetDriver::GetClient( CP2PTracker::UCID nID )
{
	CPeerList::iterator i = clients.find( nID );
	if ( i != clients.end() )
		return &(i->second);
	return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void CNetDriver::AddClient( const SClientAddressInfo &addr, CP2PTracker::UCID clientID )
{
	NI_ASSERT( clients.find( clientID ) == clients.end(), "Duplicate peer" );
	SPeer &peer = clients[clientID];
	peer.currentAddr = addr.inetAddress;
	peer.clientID = clientID;
	peer.addrInfo = addr;
	peer.bTryShortcut = addr.NeedToTryShortcut();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CNetDriver::AddNewP2PClient( const SClientAddressInfo &addr, CP2PTracker::UCID clientID )
{
	MemoryStream addrInfo;
	addrInfo.Write( &addr, sizeof( addr ) );
	p2p.AddNewClient( clientID, addrInfo, bIsBroadcast );
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void CNetDriver::RemoveClient( CP2PTracker::UCID nID )
{
	clients.erase( nID );
}
////////////////////////////////////////////////////////////////////////////////////////////////////
bool CNetDriver::SendBroadcast( const MemoryStream &_pkt )
{
	threading::MutexLock mutexLock( netDriverMutex );

	if ( state != ACTIVE )
		return false;
	//
	MemoryStream pkt = _pkt;
	// CRAP{ for traffic measurement
	nSent += pkt.GetSize();
	// CRAP}

	p2p.SendBroadcast( pkt );
	return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CNetDriver::SendDirect( int nClient, const MemoryStream &_pkt )
{
	SDataToSend *pBack = dataToSend.GetBack();
	pBack->nClient = nClient;
	pBack->pkt = _pkt;
	dataToSend.PushBack();

  DebugTrace("Message to client %d, size: %d", nClient, _pkt.GetSize());

	return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CNetDriver::SendDirectInternal( int nClient, MemoryStream &_pkt )
{
	SPeer *pDst = GetClient( nClient );
	if ( pDst == 0 || state != ACTIVE )
		return false;

	p2p.SendDirect( pDst->clientID, _pkt );

	return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CNetDriver::Kick( int nClient )
{
	threading::MutexLock mutexLock( netDriverMutex );
	
	SPeer *pDst = GetClient( nClient );
//	NI_ASSERT( pDst != 0, "pDst == 0 " );
	NI_ASSERT( state == ACTIVE, "Wrong state of the game" );
	if ( pDst )
		p2p.KickClient( nClient, bIsBroadcast );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CNetDriver::GetMessageInternal()
{
	// must not place critical section here! method is under cirtical section already!
	if ( msgQueue.empty() )
		return false;
	else
	{
		SDataReceived *pData = dataReceived.GetBack();
		SMessage &msg = msgQueue.front();
		pData->eMsg = msg.msg;
		pData->nClientID = msg.nClientID;
		pData->received = msg.received;
		pData->pkt = msg.pkt;
		msgQueue.pop_front();
		dataReceived.PushBack();
	}

	return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CNetDriver::GetMessage( EMessage *pMsg, int *pClientID, vector<int> *pReceived, MemoryStream *pPkt )
{
	threading::MutexLock mutexLock( netDriverMutex );

	if ( dataReceived.IsEmpty() )
		return false;
	else
	{
		SDataReceived *pData = dataReceived.GetFront();
		if ( pMsg )
			*pMsg = pData->eMsg;
		if ( pClientID )
			*pClientID = pData->nClientID;
		if ( pReceived )
			*pReceived = pData->received;
		if ( pPkt )
			*pPkt = pData->pkt;
		dataReceived.PopFront();
	}

	return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CNetDriver::ProcessLogin( const CNodeAddress &addr, BitStream &bits )
{
	// if can accept login requests only
	CLoginSupport::SLoginInfo info;
	if ( login.ProcessLogin( addr, bits, &info ) )
	{
		bool bAddp2pClient = false;		
		EReject reject = NONE;
		if ( info.bWrongVersion )
			reject = WRONG_VERSION;
		else
		{
			SPeer *pPeer = GetClientByAddr( addr );
			if ( pPeer )
			{
				if ( !login.HasAccepted( addr, info ) )
				{
					netTraffic( NLogg::LEVEL_MESSAGE, NStr::StrFmt( "*** IGNORE obsolete or too new request from: %s", addr.GetFastName().c_str() ) );
					return;
				}
			}
			else if ( info.pwd.GetSize() ) // wrong password
				reject = PASSWORD_FAILED;
			else
			{
				if ( !bAcceptNewClients )
					reject = FORBIDDEN;
				else
					bAddp2pClient = true;
			}
		}
		if ( reject != NONE )
		{
			CSendPacket pkt( addr, REJECTED, pLinks );
			netTraffic( NLogg::LEVEL_MESSAGE, NStr::StrFmt( "Send packet: %s to: %s", 
				Packet2String( REJECTED ), addr.GetFastName().c_str() ) );
			login.RejectLogin( addr, pkt.GetBits(), info, (int)reject );
		}
		else
		{
			int nClientID;
			CSendPacket pkt( addr, ACCEPTED, pLinks );
			netTraffic( NLogg::LEVEL_MESSAGE, NStr::StrFmt( "Send packet: %s to: %s", 
				Packet2String( ACCEPTED ), addr.GetFastName().c_str() ) );

			CNodeAddressSet localAddr;
			bool bGetSelf = pLinks->GetSelfAddress( &localAddr );
			ASSERT( bGetSelf );
			login.AcceptLogin( addr, pkt.GetBits(), info, &nClientID, localAddr );

			if ( bAddp2pClient )
				AddNewP2PClient( SClientAddressInfo( addr, info.localAddr ), nClientID );
			else
			{
				netTraffic( NLogg::LEVEL_MESSAGE, "*** Accept new clients FORBIDDEN..." );
			}
		}
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CNetDriver::ProcessNormal( const CNodeAddress &addr, BitStream &bits )
{
	CP2PTracker::UCID clientID = 0xFFFFFFFF;
	bits.Read( clientID );
	if ( !p2p.IsActive( clientID ) )
	{
		netTraffic( NLogg::LEVEL_MESSAGE, NStr::StrFmt( "*** p2p inactive for client: %i ", clientID ) );
		return;
	}
	SPeer *pPeer = GetClient( clientID );
	if ( pPeer )
	{
		pPeer->currentAddr = addr;
		pPeer->bTryShortcut = false;
		vector<PACKET_ID> acked;
		NI_ASSERT( pPeer->data.CanReadMsg(), "data polling is not perfect" ); // data polling is not perfect
		if ( pPeer->data.CanReadMsg() && pPeer->acks.ReadAcks( &acked, bits ) )
		{
			const bool messageGetted = pPeer->data.ReadMsg( bits );
			pPeer->data.Commit( acked );
			if( messageGetted && !PollMessages( pPeer ) )
			{
				netTraffic( NLogg::LEVEL_MESSAGE, NStr::StrFmt( "*** Net driver can't read packet while poll messages for peer: %s", addr.GetFastName().c_str() ) );
			}
			else
			{
				//netTraffic( NLogg::LEVEL_MESSAGE, NStr::StrFmt( "*** Net driver message for peer: %s", addr.GetFastName().c_str() ) );
			}
		}
	}
	else
	{
		netTraffic( NLogg::LEVEL_MESSAGE, NStr::StrFmt( "*** WARNING: normal packet from non client received from %s", addr.GetFastName().c_str() ) );
		//if (pCSLog) (*pCSLog) << "normal packet from non client received from " << addr.GetFastName() << endl;
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CNetDriver::ProcessIPNetworkBroadcast( const CNodeAddress &addr, BitStream &bits )
{
	msgQueue.push_back();
	SMessage &message = msgQueue.back();
	int nMessageSize = 0;
	bits.Read( nMessageSize );
	message.msg = EM_IP_NETWORK_BROADCAST;
	message.nClientID = -1;
	message.pkt.SetSize( nMessageSize );
	bits.Read( message.pkt.GetBuffer(), nMessageSize );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CNetDriver::ProcessIncomingMessages()
{
	// process incoming packets
	CNodeAddress addr;
	static MemoryStream pkts;
	bool bContinue = true;
	while ( pLinks->Recv( &addr, &pkts ) && bContinue )
	{
		if ( pkts.GetSize() == 0 )
		{
			netTraffic( NLogg::LEVEL_MESSAGE, NStr::StrFmt( "ZERO length packet received from: %s", addr.GetFastName().c_str() ) );
			continue;
		}
		EPacket cmd = (EPacket)0;
		pkts.Read( &cmd, 1 );

		BitStream bits( pkts.GetBuffer() + 1, BitStream::read, pkts.GetSize() - 1 );

		//netTraffic( NLogg::LEVEL_MESSAGE, NStr::StrFmt( "Recieve packet: %s from: %s (packet size: %d)",
		//	Packet2String( cmd ).c_str(), addr.GetFastName().c_str(), pkts.GetSize() ) );
    DebugTrace("Recieve packet: %s from: %s (packet size: %d)", Packet2String( cmd ), addr.GetFastName().c_str(), pkts.GetSize());


		switch ( cmd )
		{
			case NORMAL:
				ProcessNormal( addr, bits );
				break;
			case LOGIN:
				ProcessLogin( addr, bits );
				bContinue = false;
				break;
			case REQUEST_SERVER_INFO:
				if ( serverInfo.DoReplyRequest() )
				{
					CSendPacket pkt( addr, SERVER_INFO, pLinks );
					netTraffic( NLogg::LEVEL_MESSAGE, NStr::StrFmt( "Send packet: %s to: %s", 
						Packet2String( SERVER_INFO ), addr.GetFastName().c_str() ) );
					serverInfo.ReplyServerInfoRequest( bits, pkt.GetBits() );
				}
				break;
			case SERVER_INFO:
				serverInfo.ProcessServerInfo( addr, bits, consts.fServerListTimeout );
				break;
			case ACCEPTED:
				login.ProcessAccepted( addr, bits );
				break;
			case REJECTED:
				login.ProcessRejected( addr, bits );
				break;
			case LOGOUT:
				{
					CP2PTracker::UCID clientID = 0xFFFFFFFF;
					bits.Read( clientID );
          DebugTrace("Client %d kicked because it logged out.", clientID);
					p2p.KickClient( clientID, bIsBroadcast );
					SPeer *pPeer = GetClientByAddr( addr );
					if ( pPeer )
          {
            DebugTrace("Client %d kicked because we are logging out", pPeer->clientID);
						p2p.KickClient( pPeer->clientID, bIsBroadcast );
          }
				}
				break;
			case TRY_SHORTCUT:
				{
					CP2PTracker::UCID clientID = 0xFFFFFFFF;
					bits.Read( clientID );
					CLoginSupport::TServerID uniqueServerID;
					bits.Read( uniqueServerID );
					if ( uniqueServerID == login.GetUniqueServerID() )
					{
						if ( !p2p.IsActive( clientID ) )
							return;
						SPeer *pPeer = GetClient( clientID );
						if ( pPeer )
						{
							pPeer->currentAddr = addr;
							pPeer->bTryShortcut = false;
						}
					}
					else if ( bUseClientToClientShortcuts )
					{
						CSendPacket pkt( addr, TRY_SHORTCUT, login.GetSelfClientID(), pLinks );
						pkt.GetBits()->Write( uniqueServerID );
					}
				}
				break;
			case NOP:
				break;
			case KICK:
				// was kicked
				{
					if ( !bIsServer )
					{
						MemoryStream fake;
						vector<CP2PTracker::UCID> fake1;
						AddOutputMessage( KICKED, 0, fake, fake1 );
						while ( !clients.empty() )
						{
							CP2PTracker::UCID clientID = clients.begin()->first;
							AddOutputMessage( REMOVE_CLIENT, clientID, fake, fake1 );
							if ( clientID == 0 )
								AddOutputMessage( SERVER_DEAD, 0, fake, fake1 );
							RemoveClient( clientID );
						}
					}
				}
				break;
			case IP_NETWORK_BROADCAST:
				{
					ProcessIPNetworkBroadcast( addr, bits );
				}
				break;
			default:
				// Unknown UDP packet. Maybe a remote spam. The packet should be ignored.
				//NI_NI_ALWAYS_ASSERT(	"Unknown command", "Unknown command" );
				break;
		}
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CNetDriver::StepInactive()
{
	if ( !serverInfo.CanSendRequest() )
	{
		return;
	}
	// here we form list of addresses, where to send request
	vector<CNodeAddress> dest;
	CNodeAddress tmp;
	// make broadcast address according to our's address class (net-prefix-directed broadcast)
	pLinks->MakeBroadcastAddr( &tmp, nGamePort );
	dest.push_back( tmp );
	
#ifdef _FINALRELEASE
	// make limited broadcast
	//tmp.SetInetName( "255.255.255.255", nGamePort );
	tmp.SetToBroadcastAddress( nGamePort );
	dest.push_back( tmp );
#else 
	for ( int nTempPort = nGamePort; nTempPort >= IDriver::LAN_GAME_PORT; nTempPort -= 2 )
	{
		//tmp.SetInetName( "255.255.255.255", nTempPort );
		tmp.SetToBroadcastAddress( nTempPort );
		dest.push_back( tmp );
	}
#endif
	// here we send request
	for ( int i = 0; i < dest.size(); ++i )
	{
		CSendPacket pkt( dest[i], REQUEST_SERVER_INFO, pLinks );
		serverInfo.WriteRequest( pkt.GetBits() );
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CNetDriver::SendIPNetworkBroadcast( const MemoryStream &packet )
{
	CNodeAddress broadcast;
	// here we send only limited broadcast, as this function used only for chatting in lan lobbies
	// if we also send net-prefix-directed broadcast, chat messages may be dupped
	broadcast.SetInetName( "255.255.255.255", nGamePort );
	CSendPacket pkt( broadcast, IP_NETWORK_BROADCAST, pLinks );
	netTraffic( NLogg::LEVEL_MESSAGE, NStr::StrFmt( "Send packet: %s to: %s", 
		Packet2String( IP_NETWORK_BROADCAST ), broadcast.GetFastName().c_str() ) );
	pkt.GetBits()->Write( packet.GetSize() );
	pkt.GetBits()->Write( packet.GetBuffer(), packet.GetSize() );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CNetDriver::StepConnecting()
{
	switch ( login.GetState() )
	{
		case CLoginSupport::INACTIVE:
			netTraffic( NLogg::LEVEL_MESSAGE, "*** Connecting state: go to inactive state" );
			lastReject = TIMEOUT;
			state = INACTIVE;
			break;
		case CLoginSupport::LOGIN:
			if ( login.CanSend() )
			{
				CNodeAddressSet localAddr;
				if ( !pLinks->GetSelfAddress( &localAddr ) )
				{
					CSendPacket pkt( login.GetLoginTarget(), NOP, pLinks );
					netTraffic( NLogg::LEVEL_MESSAGE, NStr::StrFmt( "Send packet: %s to: %s", 
						Packet2String( NOP ), login.GetLoginTarget().GetFastName().c_str() ) );
				}
				const bool bGetSelf = pLinks->GetSelfAddress( &localAddr );
				ASSERT( bGetSelf );
				CSendPacket pkt( login.GetLoginTarget(), LOGIN, pLinks );
				login.WriteLogin( pkt.GetBits(), localAddr );

				netTraffic( NLogg::LEVEL_MESSAGE, NStr::StrFmt( "*** Try to connect to: %s", login.GetLoginTarget().GetFastName().c_str() ) );
			}
			break;
		case CLoginSupport::ACCEPTED:
			{
				netTraffic( NLogg::LEVEL_MESSAGE, NStr::StrFmt( "*** LOGIN accepted by: %s, add new p2p connection...", login.GetLoginTarget().GetFastName().c_str() ) );
				// ставим 0, т.к. id server == 0
				const int clientId = 0;
				AddNewP2PClient( SClientAddressInfo( login.GetLoginTarget(), login.GetTargetLocalAddr() ), clientId );
				state = ACTIVE;
				StepActive( 0 );
			}
			break;
		case CLoginSupport::REJECTED:
			netTraffic( NLogg::LEVEL_MESSAGE, NStr::StrFmt( "*** LOGIN rejected, reason %d", login.GetRejectReason() ) );
			lastReject = (EReject)login.GetRejectReason();
			state = INACTIVE;
			break;
		default:
			NI_ALWAYS_ASSERT(	"Unknown message" );
			break;
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CNetDriver::AddOutputMessage( EMessage msg, const CP2PTracker::UCID _from, 
		MemoryStream &data, const vector<CP2PTracker::UCID> &received )
{
	if ( msg == KICKED )
	{
		SMessage &res = *msgQueue.insert( msgQueue.end() );
		res.msg = msg;
		return;
	}
	SPeer *pPeer = GetClient( _from );
	NI_VERIFY( pPeer != 0, "NULL peer", return; )
	SMessage &res = *msgQueue.insert( msgQueue.end() );
	res.msg = msg;
	res.pkt = data;
	res.nClientID = pPeer->clientID;
	for ( int i = 0; i < received.size(); ++i )
	{
		SPeer *pTest = GetClient( received[i] );
		NI_ASSERT( pTest != 0, "NULL pTest" );
		if ( pTest )
			res.received.push_back( pTest->clientID );
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CNetDriver::PollMessages( SPeer *pPeer )
{
	// seek for packets through incoming traffic
	if ( CanReadPacket( pPeer->data.channelInBuf ) )
	{
		MemoryStream pkt;
		ReadPacket( pPeer->data.channelInBuf, &pkt );
    //LogBuffer(pkt.GetBuffer(), pkt.GetSize(), 0);
		p2p.ProcessPacket( pPeer->clientID, pkt, bIsBroadcast );
		return true;
	}
	else
	{
		return false;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace
{
	string P2PMessage2String( CP2PTracker::EOutMessage message )
	{
		switch( message )
		{
		case CP2PTracker::NEW_CLIENT:
			return "CP2PTracker::NEW_CIENT";
		case CP2PTracker::REMOVE_CLIENT:
			return "CP2PTracker::REMOVE_CLIENT";
		case CP2PTracker::BROADCAST:
			return "CP2PTracker::BROADCAST";
		case CP2PTracker::DIRECT:
			return "CP2PTracker::DIRECT";
		default:
			return string( "unknown message id: " ) + NStr::IntToStr( message );
		}				
	}

}

void CNetDriver::ProcessP2PMessages()
{
	CP2PTracker::SMessage msg;
	while ( p2p.GetMessage( &msg ) )
	{
        //netLog
		//netTraffic( NLogg::LEVEL_MESSAGE, NStr::StrFmt( "*** Process P2P message: %s, from: %i",
		//	P2PMessage2String( msg.msg ).c_str(), msg.from ) );

		switch ( msg.msg )
		{
		case CP2PTracker::NEW_CLIENT:
			{
				SClientAddressInfo addr;
				msg.pkt.Seek( 0, SEEKORIGIN_BEGIN );
				msg.pkt.Read( &addr, sizeof(addr) );
				AddClient( addr, msg.from );
				AddOutputMessage( NEW_CLIENT, msg.from, msg.pkt, msg.received );
			}

			break;
		case CP2PTracker::REMOVE_CLIENT:
			AddOutputMessage( REMOVE_CLIENT, msg.from, msg.pkt, msg.received );

			if ( msg.from == 0 )
			{
				AddOutputMessage( SERVER_DEAD, msg.from, msg.pkt, msg.received );
			}

			RemoveClient( msg.from );

			break;
		case CP2PTracker::DIRECT:
			AddOutputMessage( DIRECT, msg.from, msg.pkt, msg.received );
			break;
		case CP2PTracker::BROADCAST:
			AddOutputMessage( BROADCAST, msg.from, msg.pkt, msg.received );
			break;
		}
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void CNetDriver::StepActive( float fDeltaTime )
{
	// rollback outdated packets
	for ( CPeerList::iterator i = clients.begin(); i != clients.end(); ++i )
	{
		vector<PACKET_ID> rolled, erased;
		SPeer& peer = i->second;
		peer.acks.Step( &rolled, &erased, fDeltaTime, consts.fServerListTimeout );
  
		peer.data.Rollback( rolled );
		peer.data.Erase( erased );
		PollMessages( &peer );
	}

	// give out kicks
	for ( int k = 0; k < p2p.kicks.size(); ++k )
	{
		SPeer *pPeer = GetClient( p2p.kicks[k] );
		if ( pPeer )
		{
			CSendPacket pkt( pPeer->currentAddr, KICK, login.GetSelfClientID(), pLinks );
			netTraffic( NLogg::LEVEL_MESSAGE, NStr::StrFmt( "Send packet: %s to: %s", 
				Packet2String( KICK ), pPeer->currentAddr.GetFastName().c_str() ) );
		}
	}
	p2p.kicks.clear();
	p2p.CheckCorpses();
	ProcessP2PMessages();

	// form output packets
	for ( int pi = 0; pi < p2p.packets.size(); ++pi )
	{
		CP2PTracker::SPacket &p = p2p.packets[pi];
		SPeer *pPeer = GetClient( p.addr );
		if ( pPeer )
		{
			WritePacket( &pPeer->data.outList, p.pkt );
		}
	}
	p2p.packets.resize( 0 );

	int nKicksLeft = 5; // limit the number of timeout kicks per step
	// send updates & check for timeouts
	for ( CPeerList::iterator it = clients.begin(); it != clients.end() && nKicksLeft > 0; ++it )
	{
		if ( it->second.acks.GetTimeSinceLastRecv() > consts.fTimeout )
		{
      DebugTrace("Client %d kicked because of timeout. Client timed out for %d, while only %d allowed.", it->second.clientID, it->second.acks.GetTimeSinceLastRecv(), consts.fTimeout);
			p2p.KickClient( it->second.clientID, bIsBroadcast );
			--nKicksLeft;
		}
	}
	
	for ( CPeerList::iterator it = clients.begin(); it != clients.end(); ++it )
	{
		//const CP2PTracker::UCID& id = it->first;
		SPeer& peer = it->second;
		//
		if ( p2p.IsActive( peer.clientID ) )
		{
			// check if we should send acks
			const bool needSendAcks = (peer.acks.CanSend() && peer.data.HasOutData()) || peer.acks.NeedSend();
			// and check time to live
			const bool needSendData = needSendAcks && peer.fTimeToSendData <= 0;
			if ( needSendData )
			{
				// try to send data throw others clients
				peer.fTimeToSendData = MIN_TIME_BETWEEN_PACKETS_PER_PEER;
				if ( peer.bTryShortcut && bUseClientToClientShortcuts )
				{
					for ( int k = 0; N_MAX_HOST_HOMES; ++k )
					{
						CNodeAddress dest;
						if ( !peer.addrInfo.localAddress.GetAddress( k, &dest ) )
							break;
						CSendPacket pkt( dest, TRY_SHORTCUT, login.GetSelfClientID(), pLinks );
						pkt.GetBits()->Write( login.GetUniqueServerID() );
					}
				}

				// form and send acks
				PACKET_ID pktID = 0xFFFF;
				{
					CSendPacket pkt( peer.currentAddr, NORMAL, login.GetSelfClientID(), pLinks );
					BitStream* streamToStore = pkt.GetBits();
					// write acks to packet
					pktID = peer.acks.WriteAcks( streamToStore, PACKET_SIZE ); // CRAP - packet size limits??					
					// write data to packet
					peer.data.WriteMsg( pktID, streamToStore, PACKET_SIZE );
				}
				
				// check sending result
				if ( !CSendPacket::GetResult() )
				{
					peer.acks.PacketLost( pktID );
					vector<PACKET_ID> roll;
					roll.push_back( pktID );
					peer.data.Rollback( roll );
					break;
				}
			}
			else
			{
				peer.fTimeToSendData -= fDeltaTime;
			}
		}
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CNetDriver::Step()
{
	threading::MutexLock mutexLock( netDriverMutex );

	if ( !CanWork() )
		return;

	// prepare to send data
	while ( !dataToSend.IsEmpty() )
	{
		SDataToSend* pData = dataToSend.GetFront();
		SendDirectInternal( pData->nClient, pData->pkt );
		dataToSend.PopFront();
	}

	while ( GetMessageInternal() )
	{}

	float fSeconds = NHPTimer::GetTimePassedAndUpdateTime( lastTime );
	serverInfo.Step( fSeconds );
	login.Step( fSeconds );
	ProcessIncomingMessages();
	//
	switch ( state )
	{
		case INACTIVE:
			StepInactive();
			break;
		case ACTIVE:
			StepActive( fSeconds );
			break;
		case CONNECTING:
			StepConnecting();
			break;
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CNetDriver::StartGame()
{
	threading::MutexLock mutexLock( netDriverMutex );

	NI_ASSERT( state == INACTIVE, "Wrong state of the game" );
	state = ACTIVE;
	bIsServer = true;
  CNodeAddressSet addrs;
  addrs.Clear();
  pLinks->GetSelfAddress(&addrs);
  CNodeAddress addr;
  for(int i = 0; addrs.GetAddress(i, &addr); i++)
  {
    DebugTrace("Server %dth address is: %s", i, addr.GetIP().c_str());
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CNetDriver::ConnectGame( const CNodeAddress &addr, const MemoryStream &pwd )
{
	threading::MutexLock mutexLock( netDriverMutex );
	
	state = CONNECTING;
	login.StartLogin( addr, pwd );

	gameHostAddress.Clear();
	gameHostAddress.SetInetName( addr.GetFastName().c_str(), 0 );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CNetDriver::StartGameInfoSend( const MemoryStream &pkt )
{
	threading::MutexLock mutexLock( netDriverMutex );
	serverInfo.StartReply( pkt );
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void CNetDriver::StartGameInfoSend( const SGameInfo &_gameInfo )
{
	MemoryStream memStream;
	{
		CObj<IBinSaver> p = CreateWriteBinSaver( &memStream, 0, false );
		SGameInfo gameInfo = _gameInfo;
		gameInfo.gameSettings.Seek( 0, SEEKORIGIN_BEGIN );
		p->Add( 1, &gameInfo );
	}
	StartGameInfoSend( memStream );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CNetDriver::StopGameInfoSend()
{
	threading::MutexLock mutexLock( netDriverMutex );
	
	serverInfo.StopReply();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CNetDriver::GetGameInfo( int nIdx, CNodeAddress *pAddr, bool *pWrongVersion, float *pPing, SGameInfo *pGameInfo )
{
	threading::MutexLock mutexLock( netDriverMutex );
	
	CServerInfoSupport::SServerInfo _serverInfo;

	if ( !serverInfo.GetServerInfo( &_serverInfo, nIdx ) )
		return false;
	
	if ( pAddr )
		*pAddr = _serverInfo.addr;
	if ( pWrongVersion )
		*pWrongVersion = _serverInfo.bWrongVersion;
	if ( pPing )
		*pPing = _serverInfo.fPing;
	{
		IBinSaver *p = CreateReadBinSaver( &_serverInfo.info, 0 );
		p->Add( 1, pGameInfo );
		delete p;
	}

	return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CNetDriver::StartNewPlayerAccept() 
{
	threading::MutexLock mutexLock( netDriverMutex );

	bAcceptNewClients = true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CNetDriver::StopNewPlayerAccept()
{
	threading::MutexLock mutexLock( netDriverMutex );
	
	bAcceptNewClients = false;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const float CNetDriver::GetPing(unsigned int nClientID )
{
	threading::MutexLock mutexLock( netDriverMutex );

	CPeerList::const_iterator iter = clients.find( nClientID );
	if ( iter == clients.end() )
		return -1.0f;
	else
		return iter->second.acks.GetPing();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const float CNetDriver::GetTimeSinceLastRecv( unsigned int nClientID )
{
	threading::MutexLock mutexLock( netDriverMutex );
	
	CPeerList::const_iterator iter = clients.find( nClientID );
	if ( iter == clients.end() )
		return -1.0f;
	else
		return iter->second.acks.GetTimeSinceLastRecv();	
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// for debug
static const char *szInvalidClient = "Invalid client ID";
const char* CNetDriver::GetAddressByClientID( unsigned int nClientID ) const
{
	threading::MutexLock mutexLock( netDriverMutex );
	CPeerList::const_iterator iter = clients.find( nClientID );
	if ( iter == clients.end() )
		return szInvalidClient;
	else
		return iter->second.currentAddr.GetFastName().c_str();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const string CNetDriver::GetIP( unsigned int nClientID )
{
	string szEmpty;
	threading::MutexLock mutexLock( netDriverMutex );
	CPeerList::iterator iter = clients.find( nClientID );
	return iter == clients.end() ? szEmpty : iter->second.currentAddr.GetIP();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const int CNetDriver::GetPort( unsigned int nClientID )
{
	threading::MutexLock mutexLock( netDriverMutex );
	CPeerList::iterator iter = clients.find( nClientID );
	return iter == clients.end() ? 0 : iter->second.currentAddr.GetPort();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CNetDriver::PauseNet()
{
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CNetDriver::UnpauseNet()
{
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CNetDriver::SetLag( const DWORD period )
{
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
IDriver* CreateNetDriver( const SNetDriverConsts &consts, bool bIsBroadcast )
{	
	return new NNet::CNetDriver( consts, bIsBroadcast );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
string NetMessage2String( IDriver::EMessage messageId )
{
	switch( messageId )
	{
	case IDriver::BROADCAST:
		return "EMessage::BROADCAST";
	case IDriver::DIRECT:
		return "EMessage::DIRECT";
	case IDriver::EM_IP_NETWORK_BROADCAST:
		return "EMessage::EM_IP_NETWORK_BROADCAST";
	case IDriver::KICKED:
		return "EMessage::KICKED";		
	case IDriver::NEW_CLIENT:
		return "EMessage::NEW_CLIENT";
	case IDriver::REMOVE_CLIENT:
		return "EMessage::REMOVE_CLIENT";
	case IDriver::SERVER_DEAD:
		return "EMessage::SERVER_DEAD";
	default:
		return NStr::IntToStr( messageId ) + " unknown message id";
	}	
} 

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
