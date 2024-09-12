#pragma once
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <winsock2.h>
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NNet
{
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CNodeAddress
{
	sockaddr addr;
public:
	int operator&( IBinSaver &f );

	CNodeAddress() { memset( &addr, 0, sizeof(addr) ); }
	CNodeAddress( const char* host, int port ) { SetInetName( host, port ); }
	CNodeAddress( const CNodeAddress &src );

	void Clear() { memset( &addr, 0, sizeof(addr) ); }
	bool IsZero() const;
	//
	void SetToBroadcastAddress( int nPort );
	bool SetInetName( const char *pszHost, int nDefaultPort );
	string GetName( bool bResolve ) const;
	string GetFastName() const { return GetName( false ); }
	//
	string GetIP() const;
	int GetPort() const;
	//
  bool SameIP( const CNodeAddress &a ) const {return memcmp(((char*)&a.addr) + 4, ((char*)&addr) + 4, 4) == 0; } // { return false; }

	bool operator == ( const CNodeAddress &a ) const { return memcmp(&addr, &a.addr, sizeof(addr)) == 0; } //true; } 
	bool operator != ( const CNodeAddress &a ) const { return memcmp(&addr, &a.addr, sizeof(addr)) != 0; } // false; } //

	const sockaddr *GetSockAddr() const { return &addr; }
	sockaddr *GetSockAddr() { return &addr; }

	
	CNodeAddress &operator=( const CNodeAddress &src );

	friend class CLinksManagerCommon;
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
