#pragma once
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "netaddress.h"
#include "NetDriver.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NNet
{
class CLinksManagerCommon : public ILinksManager
{
	SOCKET s;
	CNodeAddress broadcastAddr;
protected:
	virtual bool IsGoodAddress( const sockaddr& ) const { return true; }
public:
	CLinksManagerCommon();
	~CLinksManagerCommon();
	bool Init( const int nPort );

	virtual bool MakeBroadcastAddr( class CNodeAddress *pRes, int nPort ) const;
	virtual bool IsLocalAddr( const CNodeAddress &test ) const;
	virtual bool Send( const CNodeAddress &dst, MemoryStream &pkt ) const;
	virtual bool Recv( class CNodeAddress *pSrc, MemoryStream *pPkt ) const;
	virtual bool GetSelfAddress( class	CNodeAddressSet *pRes ) const;
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ILinksManager* CreateServerLinksManager( const int nPort );
//void LogBuffer(void const *pBuff, int nSize, int nDir = 0);

bool InitWinsock();
bool TermWinsock();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
