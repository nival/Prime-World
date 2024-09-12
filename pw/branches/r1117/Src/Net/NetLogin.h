#pragma once

#include "NetDriver.h"
#include "NetLowest.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class BitStream;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NNet
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CLoginSupport
{
public:
	typedef __int64 TServerID;
	enum EState
	{
		INACTIVE,
		LOGIN,
		ACCEPTED,
		REJECTED
	};
	struct SLoginInfo
	{
		int nLoginAttempt;
		bool bWrongVersion;
		CNodeAddressSet localAddr;
		MemoryStream pwd;
	};

	void Step( float fDeltaTime );
	bool CanSend() const { return fLoginTimeLeft < 0; }
	EState GetState() const { return state; }
	int GetRejectReason() const { return nLastReject; }
	void WriteLogin( BitStream *pBits, const CNodeAddressSet &localAddr );
	bool ProcessLogin( const CNodeAddress &addr, BitStream &bits, SLoginInfo *pRes );
	void AcceptLogin( const CNodeAddress &addr, BitStream *pBits, const SLoginInfo &info, int *pnClientID, const CNodeAddressSet &localAddr );
	void RejectLogin( const CNodeAddress &addr, BitStream *pBits, const SLoginInfo &info, int nReason );
	bool HasAccepted( const CNodeAddress &addr, const SLoginInfo &info );
	void ProcessAccepted( const CNodeAddress &addr, BitStream &bits );
	void ProcessRejected( const CNodeAddress &addr, BitStream &bits );
	void StartLogin( const CNodeAddress &addr, const MemoryStream &buf );
	const CNodeAddress& GetLoginTarget() const { return server; }
	int GetSelfClientID() const { return nSelfClientID; }
	void SetSelfClientID( int nMyID ) { nSelfClientID = nMyID; }
	const CNodeAddressSet& GetTargetLocalAddr() const { return serverLocalAddr; }
	TServerID GetUniqueServerID() const { return uniqueServerID; }

	CLoginSupport( APPLICATION_ID _applicationID );
	void Init( APPLICATION_ID _applicationID ) { applicationID = _applicationID; } 
private:
	struct SAcceptedLogin
	{
		CNodeAddress addr;
		int nLoginAttempt;
		float fTimeLeft;
		int nClientID;
	};
	APPLICATION_ID applicationID;
	float fLoginTimeLeft, fLoginInterval;
	int nLoginAttempt;
	CNodeAddress server;
	MemoryStream pwd;
	EState state;
	int nLastReject;
	list<SAcceptedLogin> acceptedList;
	int nClientIDTrack;
	int nSelfClientID;
	CNodeAddressSet serverLocalAddr;
	TServerID uniqueServerID;

	SAcceptedLogin& GetAcceptedLogin( const CNodeAddress &addr, const SLoginInfo &info );
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
