#pragma once

#include "NetDriver.h"
#include "NetServerInfo.h"
#include "NetLowest.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class BitStream;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NNet
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// support for server info requests and server info tracking
// support for master server, address books, etc can be added here
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CServerInfoSupport
{
public:
	struct SServerInfo
	{
		CNodeAddress addr;
		float fValidTimeLeft;	 // how much time left until server info expires//TimeSinceUpdate;
		float fPing;						// ping to server in seconds
		bool bWrongVersion;		 // to catch different version
		MemoryStream info;
	};
	typedef list<SServerInfo> CServerInfoList;
private:
	CServerInfoList servers;
	float fTime, fRequestDelay;
	APPLICATION_ID applicationID;
	bool bDoReply;
	MemoryStream serverInfo;

	//SServerInfo& GetInfo( const CNodeAddress &addr );
	void UpdateServerInfo( const SServerInfo &serverInfo );
public:
	CServerInfoSupport( APPLICATION_ID _nApplicationID );
	//
	void Init( APPLICATION_ID _applicationID ) { applicationID = _applicationID; }
	//
	void Step( float fDeltaTime );
	CServerInfoList& GetServers() { return servers; }
	bool GetServerInfo( SServerInfo * pServerInfo, int nIndex );
	// requests reply	support
	bool DoReplyRequest() const { return bDoReply; }
	void StartReply( const MemoryStream &info ) { bDoReply = true; serverInfo = info; }
	void StopReply() { bDoReply = false; }
	// packets forming
	void ReplyServerInfoRequest( BitStream &bits, BitStream *pDstBits );
	void ProcessServerInfo( const CNodeAddress &addr, BitStream &bits, float fServerListTimeout );
	void WriteRequest( BitStream *pBits );
	// server search
	bool CanSendRequest();
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
