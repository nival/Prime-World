#include "stdafx.h"

#include "LinksManager.h"
#include "NetLowest.h"
#include "NetLog.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace
{
	const bool B_DEBUG_TRACE_SOCKET_ERRORS_ENABLED_DEFAULT = true;
	bool bDebugTraceSocketErrorsEnabled = B_DEBUG_TRACE_SOCKET_ERRORS_ENABLED_DEFAULT;
  int _nInitializationsDone = 0;
}

#ifndef SIO_UDP_CONNRESET
  #define SIO_UDP_CONNRESET           _WSAIOW(IOC_VENDOR,12)
#endif

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace NNet
{
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool InitWinsock()
{
	WORD wVersionRequested = MAKEWORD(2, 2);
	WSADATA wsaData;
	//
  if(_nInitializationsDone == 0)
  {
    int wsaret = WSAStartup(wVersionRequested, &wsaData);
    if(wsaret != 0)
    {
      return false;
    }
    if(LOBYTE(wsaData.wVersion ) != 2 || HIBYTE( wsaData.wVersion ) != 2) 
    {
      WSACleanup();
      return false; 
    }
  }
  _nInitializationsDone++;
  return true;
}

bool TermWinsock()
{
  if(_nInitializationsDone <= 0)
  {
    return false;
  }
  _nInitializationsDone--;
  if(_nInitializationsDone == 0)
  {
    WSACleanup();
  }
  return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static struct SWSAInit
{
	SWSAInit() { InitWinsock(); }
	~SWSAInit()
	{
		TermWinsock();
	}
} wsaInit;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static int CheckErrors()
{
	if ( !bDebugTraceSocketErrorsEnabled )
		return -1;

	const int error = WSAGetLastError();
	switch (error)
	{
	case WSANOTINITIALISED:
		NI_ALWAYS_ASSERT( "WSAGetLastError()=WSANOTINITIALISED" );
		break;
	case WSAEWOULDBLOCK:
	case WSAEINVAL:
		break;
	default:
		break;
	}

	return error;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CLinksManagerCommon::CLinksManagerCommon()
{
	s = INVALID_SOCKET;
	// get host for broadcast addresses formation
	char szHost[1024];
	if ( gethostname( szHost, 1000 ) == SOCKET_ERROR )
	{
		CheckErrors();
		NI_ALWAYS_ASSERT( "CLinksManagerCommon::CLinksManagerCommon\ngethostname" );
		return;
	}
	hostent *he;
	he = gethostbyname( szHost ); // m.b. it is string comp.domain
	if ( he == NULL )
	{
		CheckErrors();
		NI_ALWAYS_ASSERT( "CLinksManagerCommon::CLinksManagerCommon\ngethostbyname" );
		return;
	}
	// form addresses
	CNodeAddress addr;
	sockaddr_in &name = *(sockaddr_in*)&addr;
	name.sin_family = AF_INET;
	// hostent are broken for some unknown reason, only one address is valid
	unsigned long *pAddr = (unsigned long*)( he->h_addr_list[0] );
	//for ( ; *pAddr; pAddr++ )
	{
		name.sin_addr.S_un.S_addr = pAddr[0];
		unsigned char bClass = name.sin_addr.S_un.S_un_b.s_b1;
		if ( bClass >= 1 && bClass <= 126 )
		{
			name.sin_addr.S_un.S_un_b.s_b2 = 255;
			name.sin_addr.S_un.S_un_b.s_b3 = 255;
			name.sin_addr.S_un.S_un_b.s_b4 = 255;
		}
		if ( bClass >= 128 && bClass <= 191 )
		{
			name.sin_addr.S_un.S_un_b.s_b3 = 255;
			name.sin_addr.S_un.S_un_b.s_b4 = 255;
		}
		if ( bClass >= 192 && bClass <= 223 )
			name.sin_addr.S_un.S_un_b.s_b4 = 255;
		broadcastAddr = addr;
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CLinksManagerCommon::~CLinksManagerCommon()
{
	if ( s != INVALID_SOCKET )
		closesocket( s );
	s = INVALID_SOCKET;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CLinksManagerCommon::Init( const int nPort )
{
	s = socket( AF_INET, SOCK_DGRAM, IPPROTO_UDP );
	if ( s == INVALID_SOCKET )
		return false;

  DWORD dwBytesReturned = 0;
  BOOL  bNewBehavior = FALSE;
  DWORD status;

  // disable  new behavior using
  // IOCTL: SIO_UDP_CONNRESET
  status = WSAIoctl(s, SIO_UDP_CONNRESET, &bNewBehavior, sizeof(bNewBehavior), NULL, 0, &dwBytesReturned, NULL, NULL);
  if(SOCKET_ERROR == status)
  {
    DWORD dwErr = WSAGetLastError();
    if (WSAEWOULDBLOCK == dwErr)
    {
      // nothing to do
    }
    else
    {
      DebugTrace("WSAIoctl(SIO_UDP_CONNRESET) Error: %d\n", dwErr);
      return false;
    }
  }

	sockaddr_in name;
	memset( &name, 0, sizeof(name) );
	name.sin_family = AF_INET;
	name.sin_addr.S_un.S_addr = INADDR_ANY;
	name.sin_port = htons( nPort );
	if ( nPort > 0 )
	{
		if ( bind( s, (sockaddr*)&name, sizeof( name ) ) != 0 )
		{
			closesocket( s );
			s = INVALID_SOCKET;
			return false;
		}
	}
	DWORD	dwOpt = 1;
	if ( ioctlsocket( s, FIONBIO, &dwOpt ) == SOCKET_ERROR ) // no block
		CheckErrors();
	if ( setsockopt( s, SOL_SOCKET, SO_BROADCAST, (const char*)&dwOpt, 4 ) == SOCKET_ERROR )
		CheckErrors();

	return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CLinksManagerCommon::MakeBroadcastAddr( CNodeAddress *pRes, int nPort ) const
{
	*pRes = broadcastAddr;
	sockaddr_in &name = *(sockaddr_in*)&pRes->addr;
	name.sin_port = htons( nPort );

	return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CLinksManagerCommon::IsLocalAddr( const CNodeAddress &test ) const
{
	const sockaddr_in &nt = *(sockaddr_in*)&test.addr;
	if ( nt.sin_addr.S_un.S_addr == 0x0100007f )
		return true;
	//for ( int i = 0; i < broadcastAddr.size(); ++i )
	{
		const CNodeAddress &broad = broadcastAddr;//[ i ];
		const sockaddr_in &nb = *(sockaddr_in*)&broad.addr;
		DWORD dwB = nb.sin_addr.S_un.S_addr;
		DWORD dwT = nt.sin_addr.S_un.S_addr;
		DWORD dwMask = 0;
		for ( int k = 3; k >= 0; k-- )
		{
			DWORD dwTestMask = 0xFF << k*8;
			if ( (dwB & dwTestMask) == dwTestMask )
				dwMask |= dwTestMask;
			else
				break;
		}
		dwMask = ~dwMask;
		const bool bTest = ( dwB & dwMask ) == ( dwT & dwMask );
		if ( bTest )
			return true;
	}

	return false;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CLinksManagerCommon::GetSelfAddress( CNodeAddressSet *pRes ) const
{
	pRes->Clear();
	sockaddr_in addr;
	int nBufLeng = sizeof(sockaddr_in);
	if ( getsockname( s, (sockaddr*)&addr, &nBufLeng ) != 0 )
		return false;
	pRes->nPort = ntohs( addr.sin_port );
	char szHostName[10000];
	gethostname( szHostName, 9999 );
	hostent *p = gethostbyname( szHostName );
	if ( !p || p->h_addrtype != AF_INET || p->h_length != 4 )
		return false;
	for ( int k = 0; k < N_MAX_HOST_HOMES; ++k )
	{
		if ( !p->h_addr_list[k] )
			break;
		pRes->ips[k] = *(int*)p->h_addr_list[k];
	}

	return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////#ifdef NET_TEST_APPLICATION
////bool bEmulateWeakNetwork = false;
////float fLostRate = 0.7f;
////struct SPacket
////{
////	CNodeAddress addr;
////	MemoryStream pkt;
////};
////#endif
//#pragma warning( push )
//#pragma warning( disable: 4996 ) //warning C4127: conditional expression is constant
//static FILE *OpenNewOnce()
//{
//  char const *fname = "netlog";
//  char const *ext = ".txt";
//  char buff[30];
//  static bool alreadyOpened = false;
//  static int nIdx = 0;
//  FILE *outFp = NULL;
//  while (outFp == NULL)
//  {
//    sprintf_s(buff, sizeof(buff) - 1,"%s%03d%s", fname, nIdx, ext);
//    FILE *fp;
//    if(!alreadyOpened)
//    {
//      fp = fopen(buff, "r");
//      if(fp == NULL)
//      {
//        outFp = fopen(buff, "w");
//        alreadyOpened = true;
//      }
//      else
//      {
//        nIdx++;
//      }
//    }
//    else
//    {
//      outFp = fopen(buff, "a");
//    }
//  }
//  return outFp;
//}
//void LogBuffer(void const *pBuff, int nSize, int nDir)
//{
//  if(nSize == 18)
//    return;
//  FILE *fp = OpenNewOnce();
//  unsigned char const *p = (unsigned char const *)pBuff;
//  fprintf(fp, "Stamp: %010u ", GetTickCount());
//  if(nDir == 1)
//  {
//    fprintf(fp, "Dir: send ");
//  }
//  if(nDir == 2)
//  {
//    fprintf(fp, "Dir: recv ");
//  }
//  fprintf(fp, "size: %04d ", nSize);
//  for(int nI = 0; nI < nSize; nI++)
//  {
//    fprintf(fp, "%02X", (unsigned int)*(p + nI));
//  }
//  fprintf(fp, "\n");
//  fclose(fp);
//}
//#pragma warning( pop )

bool CLinksManagerCommon::Send( const CNodeAddress &dst, MemoryStream &pkt ) const
{
	if ( !IsGoodAddress( dst.addr ) )
		return true;

//#ifdef NET_TEST_APPLICATION
//	static vector<SPacket> pktQueue[10];
//	if ( bEmulateWeakNetwork )
//	{
//		if ( rand() <= RAND_MAX * fLostRate )
//			return true;
//		pktQueue.push_back();
//		pktQueue.back().addr = dst;
//		pktQueue.back().pkt = pkt;
//		while ( pktQueue.size() > 3 )
//		{
//			int nPkt = rand() % pktQueue.size();
//			SPacket &p = pktQueue[nPkt];
//			int nSize = p.pkt.GetSize();
//			int nRv = sendto( s, (const char*)p.pkt.GetBuffer(), nSize, 0, &p.addr.addr, sizeof( p.addr.addr ) );
//
//			pktQueue.erase( pktQueue.begin() + nPkt );
//		}
//		return true;
//	}
//#endif

	const int nSize = pkt.GetSize();
  //LogBuffer(pkt.GetBuffer(), nSize, 1);
	const int nRv = sendto( s, (const char*)pkt.GetBuffer(), nSize, 0, &dst.addr, sizeof( dst.addr ) );

  //netTraffic( NLogg::LEVEL_MESSAGE, NStr::StrFmt( "Net driver error while receiving data, error code = %d", error ) );
	if ( nRv == SOCKET_ERROR ) 
	{
		CheckErrors();
	} 
	else 
	{
		NI_ASSERT(nRv == nSize, "Can`t correctly send packet (MTU size exceed)!");
	}


	return nRv == nSize;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CLinksManagerCommon::Recv( CNodeAddress *pSrc, MemoryStream *pPkt ) const
{
	ASSERT( pSrc );
	ASSERT( pPkt );

	int nAddrSize = sizeof( pSrc->addr );
	pPkt->Seek( 2048, SEEKORIGIN_BEGIN );
	char* incomingData = pPkt->GetBuffer();
	int nRes = recvfrom( s, incomingData, 2048, 0, &pSrc->addr, &nAddrSize );

	if(nRes == SOCKET_ERROR )
	{
		const int error = CheckErrors();
    if(error == WSAECONNRESET)
    {
      netTraffic( NLogg::LEVEL_MESSAGE, NStr::StrFmt( "Net driver error while receiving data, connection reset, while reading from %d.%d.%d.%d", 
        int(*((char const *)&(pSrc->addr) + 4)), int(*((char const *)&(pSrc->addr) + 5)), int(*((char const *)&(pSrc->addr) + 6)), int(*((char const *)&(pSrc->addr) + 7)) ));
    }
		else if(error != WSAEWOULDBLOCK)
		{
			netTraffic( NLogg::LEVEL_MESSAGE, NStr::StrFmt( "Net driver error while receiving data, error code = %d", error ) );
		}
	}
  //if(nRes > 0)
  //{
  //  LogBuffer(incomingData, nRes, 2);
  //}

	const bool bGoodAddress = IsGoodAddress( pSrc->addr );
	if ( !bGoodAddress )
		nRes = 0;

	if ( nRes >= 0 )
	{
		pSrc->addr.sa_family = AF_INET;			 // somehow this gets spoiled on win2k
		memset( pSrc->addr.sa_data + 6, 0, 8 );
		pPkt->SetSize( nRes );
	}

	pPkt->Seek( 0, SEEKORIGIN_BEGIN );

	return bGoodAddress && nRes >= 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CLinksManager : public CLinksManagerCommon
{
	OBJECT_METHODS( 0x1E4A8B03, CLinksManager );
public:
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ILinksManager* CreateServerLinksManager( const int nPort )
{
	CPtr<CLinksManager> pManager = new CLinksManager();
	const bool bSuccess = pManager->Init( nPort );

	return bSuccess ? pManager.Extract() : 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BASIC_REGISTER_CLASS( NNet::ILinksManager )
BASIC_REGISTER_CLASS( NNet::CLinksManager )
//START_REGISTER( LinksManager )
//REGISTER_VAR_EX( "debug_debug_trace_socket_errors_enable", NGlobal::VarBoolHandler, &bDebugTraceSocketErrorsEnabled, B_DEBUG_TRACE_SOCKET_ERRORS_ENABLED_DEFAULT, STORAGE_NONE )
//FINISH_REGISTER
