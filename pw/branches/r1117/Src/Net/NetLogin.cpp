#include "StdAfx.h"
#include "NetLogin.h"
#include "../System/HPTimer.h"
#include "../System/BitStreams.h"

const float F_KEEP_ACCEPTED_TIME = 2000;
const int N_MAX_ACCEPTED_LIST_SIZE = 30;
namespace NNet
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CLoginSupport
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CLoginSupport::CLoginSupport( APPLICATION_ID _applicationID )
	: applicationID(_applicationID), state(INACTIVE), nClientIDTrack(0), nSelfClientID(0) 
{
	NHPTimer::STime time;
	NHPTimer::GetTime( time );
	uniqueServerID = time;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CLoginSupport::WriteLogin( BitStream *pBits, const CNodeAddressSet &localAddr )
{
	fLoginInterval *= 2;
	fLoginTimeLeft = fLoginInterval;
	(*pBits).Write( applicationID );
	(*pBits).Write( nLoginAttempt );
	(*pBits).Write( localAddr );
	//pkt << nRate;
	short nSize = pwd.GetSize();
	(*pBits).Write( nSize );
	(*pBits).Write( pwd.GetBuffer(), nSize );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CLoginSupport::ProcessLogin( const CNodeAddress &addr, BitStream &bits, SLoginInfo *pRes )
{
	APPLICATION_ID appID;
	bits.Read( appID );
	pRes->bWrongVersion = appID != applicationID;
	bits.Read( pRes->nLoginAttempt );
	bits.Read( pRes->localAddr );
	unsigned short nSize;
	bits.Read( nSize );
	if ( nSize >= 500 )
		return false;
	if ( acceptedList.size() > N_MAX_ACCEPTED_LIST_SIZE )
		return false;
	pRes->pwd.SetSize( nSize );
	bits.Read( pRes->pwd.GetBuffer(), nSize );
	return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CLoginSupport::SAcceptedLogin& CLoginSupport::GetAcceptedLogin( const CNodeAddress &addr, const SLoginInfo &info )
{
	for ( list<SAcceptedLogin>::iterator i = acceptedList.begin(); i != acceptedList.end(); ++i )
	{
		if ( i->addr == addr && i->nLoginAttempt == info.nLoginAttempt )
		{
			i->fTimeLeft = F_KEEP_ACCEPTED_TIME;
			return *i;
		}
	}
	SAcceptedLogin &a = *acceptedList.insert( acceptedList.end() );
	a.addr = addr;
	a.fTimeLeft = F_KEEP_ACCEPTED_TIME;
	a.nLoginAttempt = info.nLoginAttempt;
	a.nClientID = ++nClientIDTrack;
	return a;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CLoginSupport::AcceptLogin( const CNodeAddress &addr, BitStream *pBits, 
	const SLoginInfo &info, int *pnClientID, const CNodeAddressSet &localAddr )
{
	SAcceptedLogin &a = GetAcceptedLogin( addr, info );
	(*pBits).Write( info.nLoginAttempt );
	(*pBits).Write( a.nClientID );
	*pnClientID = a.nClientID;
	(*pBits).Write( localAddr );
	(*pBits).Write( uniqueServerID );

	for ( list<SAcceptedLogin>::iterator i = acceptedList.begin(); i != acceptedList.end(); )
	{
		if ( i->addr == addr )
		{
			i = acceptedList.erase( i );
		}
		else
			++i;
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CLoginSupport::RejectLogin( const CNodeAddress &addr, BitStream *pBits, const SLoginInfo &info, int nReason )
{
	(*pBits).Write( info.nLoginAttempt );
	(*pBits).Write( nReason );

	for ( list<SAcceptedLogin>::iterator i = acceptedList.begin(); i != acceptedList.end(); )
	{
		if ( i->addr == addr )
		{
			i = acceptedList.erase( i );
		}
		else
			++i;
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CLoginSupport::HasAccepted( const CNodeAddress &addr, const SLoginInfo &info )
{
	for ( list<SAcceptedLogin>::iterator i = acceptedList.begin(); i != acceptedList.end(); ++i )
	{
		if ( i->addr == addr && i->nLoginAttempt == info.nLoginAttempt )
			return true;
	}
	return false;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CLoginSupport::ProcessAccepted( const CNodeAddress &addr, BitStream &bits )
{
	if ( server != addr )
	{
		//if (pCSLog) (*pCSLog) << "ERROR: Accepted msg received from unknown host " << addr.GetFastName() << endl;
	}
	else
	{
		int nAckedAttempt;
		bits.Read( nAckedAttempt );
		if ( nAckedAttempt != nLoginAttempt )
		{
			//if (pCSLog) (*pCSLog) << "ERROR: Accepted msg received with wrong linkID" << endl;
			return;
		}
		if ( state == LOGIN )
		{
			bits.Read( nSelfClientID );
			bits.Read( serverLocalAddr );
			bits.Read( uniqueServerID );
			state = ACCEPTED;
			//if (pCSLog) (*pCSLog) << "Start connection" << endl;
		}
		else
		{
			//if (pCSLog) (*pCSLog) << "ERROR: Accept for already started session or without login from " << addr.GetFastName() << endl;
		}
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CLoginSupport::ProcessRejected( const CNodeAddress &addr, BitStream &bits )
{
	if ( server != addr )
	{
		//if (pCSLog) (*pCSLog) << "ERROR: Accepted msg received from unknown host " << addr.GetFastName() << endl;
	}
	else
	{
		int nAckedAttempt;
		bits.Read( nAckedAttempt );
		if ( nAckedAttempt != nLoginAttempt )
		{
			//if (pCSLog) (*pCSLog) << "ERROR: Accepted msg received with wrong linkID" << endl;
			return;
		}
		if ( state == LOGIN )
		{
			state = REJECTED;
			bits.Read( nLastReject );
			//if (pCSLog) (*pCSLog) << "Start connection" << endl;
		}
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CLoginSupport::Step( float fDeltaTime )
{
	if ( fLoginInterval != 0 )
	{
		fLoginTimeLeft -= fDeltaTime;
		if ( fLoginTimeLeft < 0 )
		{
			if ( fLoginInterval > 3 )
			{
				state = INACTIVE;
				//if (pCSLog) (*pCSLog) << "Connection failed" << endl;
			}
		}
	}
	for ( list<SAcceptedLogin>::iterator i = acceptedList.begin(); i != acceptedList.end(); )
	{
		i->fTimeLeft -= fDeltaTime;
		if ( i->fTimeLeft < 0 )
			i = acceptedList.erase( i );
		else
			++i;
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CLoginSupport::StartLogin( const CNodeAddress &addr, const MemoryStream &buf )
{
	state = LOGIN;
	server = addr;
	pwd = buf;
	fLoginTimeLeft = 0;
	fLoginInterval = 0.1f;
	nLoginAttempt = (int)GetTickCount();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
