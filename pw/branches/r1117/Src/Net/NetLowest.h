#pragma once

#include "NetAddress.h"
////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NNet
{
////////////////////////////////////////////////////////////////////////////////////////////////////
const int N_MAX_HOST_HOMES = 4;
class CNodeAddressSet
{
	WORD nPort;
	int ips[N_MAX_HOST_HOMES];
public:
	int operator&( IBinSaver &f );

	CNodeAddressSet();
	void Clear();
	bool IsZero() const;
	bool GetAddress( int n, CNodeAddress *pRes ) const;
	WORD GetPort() const;
	bool SetAddress( int n, const CNodeAddress &addr );
	bool operator==( const CNodeAddressSet &rhs ) const;

	friend class CLinksManagerCommon;
};
////////////////////////////////////////////////////////////////////////////////////////////////////
}
