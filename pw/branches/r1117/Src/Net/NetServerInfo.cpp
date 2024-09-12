#include "StdAfx.h"
#include "NetServerInfo.h"
#include "../System/BitStreams.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NNet
{
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CServerInfoSupport::CServerInfoSupport( APPLICATION_ID _nApplicationID )
	: applicationID(_nApplicationID), fTime(0), bDoReply(false), fRequestDelay(0) 
{
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CServerInfoSupport::Step( float fDeltaTime )
{
	fRequestDelay -= fDeltaTime;
	fTime += fDeltaTime;
	// remove outdated information about servers
	for ( CServerInfoList::iterator i = servers.begin(); i != servers.end(); )
	{
		if ( i->fValidTimeLeft > 0 )
		{
			i->fValidTimeLeft -= fDeltaTime;
			if ( i->fValidTimeLeft <= 0 )
			{
				i = servers.erase( i );
			}
			else
			{
				++i;
			}
		}
		else
		{
			++i;
		}
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CServerInfoSupport::ReplyServerInfoRequest( BitStream &bits, BitStream *pDstBits )
{
	float fReqTime;
	bits.Read( fReqTime );
	(*pDstBits).Write( fReqTime );
	(*pDstBits).Write( applicationID );
	short nSize = serverInfo.GetSize();
	(*pDstBits).Write( nSize );
	(*pDstBits).Write( serverInfo.GetBuffer(), serverInfo.GetSize() );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CServerInfoSupport::GetServerInfo( SServerInfo * pServerInfo, int nIndex )
{
	CServerInfoList::iterator i = servers.begin();
	int n = 0;
	for ( ; n < nIndex && i != servers.end(); ++i, ++n )
		;
	if ( i == servers.end() )
		return false;
	SServerInfo &tmp = *i;
	if ( pServerInfo )
		*pServerInfo = tmp;
	return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CServerInfoSupport::UpdateServerInfo( const SServerInfo &serverInfo )
{

	for ( CServerInfoList::iterator i = servers.begin(); i != servers.end(); ++i )
	{
		if ( i->addr == serverInfo.addr )
		{
			*i = serverInfo;
			return;
		}
	}
	servers.push_back( serverInfo );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CServerInfoSupport::ProcessServerInfo( const CNodeAddress &fromAddr, BitStream &bits, float fServerListTimeout )
{
	APPLICATION_ID appID;
	float fReqSent;
	//
	bits.Read( fReqSent );
	bits.Read( appID );
	// check that application is correct
	if ( (appID&0xFFFFFF00) != (applicationID&0xFFFFFF00) )
		return;

	SServerInfo info;
	info.addr = fromAddr;
	info.bWrongVersion = appID != applicationID;
	info.fPing = fTime - fReqSent;
	short nSize;
	bits.Read( nSize );
	info.info.SetSize( nSize );
	bits.Read( info.info.GetBuffer(), nSize );
	info.fValidTimeLeft = fServerListTimeout;
	UpdateServerInfo( info );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CServerInfoSupport::WriteRequest( BitStream *pBits )
{
	(*pBits).Write( fTime );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CServerInfoSupport::CanSendRequest()
{
	if ( fRequestDelay <= 0 )
	{
		fRequestDelay = 1;
		return true;
	}
	return false;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
