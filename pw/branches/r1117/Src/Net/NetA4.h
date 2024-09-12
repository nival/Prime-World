#pragma once

#include "NetStream.h"
#include "NetServerInfo.h"
#include "NetLogin.h"
#include "NetPeer2Peer.h"

#include "../System/HPTimer.h"
#include "TSList.h"
#include "../System/win32helper.h"
#include "../System/BitStreams.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NNet
{

////////////////////////////////////////////////////////////////////////////////////////////////////
class CNetDriver : public IDriver
{
	OBJECT_METHODS( 0x1E4A8B05, CNetDriver );
public:
	struct SServer
	{
		CNodeAddress addr;
		bool bWrongVersion;
		float fPing;
		MemoryStream info;
	};
	struct SMessage
	{
		EMessage msg;
		int nClientID;
		vector<int> received;
		MemoryStream pkt;
	};
private:
	SNetDriverConsts consts;
	bool bIsBroadcast; // used to prevent undesirable broadcast
	bool bIsClient; //to determine client or server
	//
	struct SClientAddressInfo
	{
		CNodeAddress inetAddress;
		CNodeAddressSet localAddress;
		
		SClientAddressInfo() {}
		SClientAddressInfo( const CNodeAddress &_inetAddress, const CNodeAddressSet &_localAddress ) 
			: inetAddress(_inetAddress), localAddress(_localAddress) {}
		bool NeedToTryShortcut() const;
	};
	//
	struct SPeer
	{
		CP2PTracker::UCID clientID;
		CNodeAddress currentAddr;
		SClientAddressInfo addrInfo;
		CAckTracker acks;
		CStreamTracker data;
		bool bTryShortcut;
		float fTimeToSendData;
		SPeer() : fTimeToSendData( 0.0f ) {}
	};

	//
	typedef hash_map<CP2PTracker::UCID,SPeer> CPeerList;
	CPeerList clients;
	EState state;
	EReject lastReject;
	NHPTimer::STime lastTime;
	CServerInfoSupport serverInfo;
	CLoginSupport login;
	CP2PTracker p2p;
	list<SMessage> msgQueue;
	bool bAcceptNewClients;
	CObj<ILinksManager> pLinks; // created/destroyed only in Init/Destroy
	int nGamePort;
	CNodeAddress gameHostAddress;
	bool bUseClientToClientShortcuts;

	static bool bIsServer;

	SPeer* GetClientByAddr( const CNodeAddress &addr );
	SPeer* GetClient( CP2PTracker::UCID nID );
	void AddNewP2PClient( const SClientAddressInfo &addr, CP2PTracker::UCID clientID );
	void AddClient( const SClientAddressInfo &addr, CP2PTracker::UCID clientID );
	void RemoveClient( CP2PTracker::UCID nID );
	void StepInactive();
	void StepConnecting();
	void StepActive( float fDeltaTime );

	void ProcessIncomingMessages();
	void ProcessLogin( const CNodeAddress &addr, BitStream &bits );
	void ProcessNormal( const CNodeAddress &addr, BitStream &bits );
	void ProcessIPNetworkBroadcast( const CNodeAddress &addr, BitStream &bits );
	void AddOutputMessage( EMessage msg, const CP2PTracker::UCID _from, 
		MemoryStream &data, const vector<CP2PTracker::UCID> &received );

	bool PollMessages( SPeer *pPeer );
	void ProcessP2PMessages();

	//
	// thread
	HANDLE hThread;
	HANDLE hThreadReport;
	HANDLE hStopCommand;

	// CRAP{ for traffic to winsock measurement
	DWORD lastTrafficCheckTime;
	int nSent;
	// CRAP}

	//
	void CreateEvents();
	void KillThread();

	void StartGameInfoSend( const MemoryStream &data );
public:
	CNetDriver();
	CNetDriver( const SNetDriverConsts &_consts, bool _bIsBroadcast );
	~CNetDriver();
	//
	virtual void Init( const APPLICATION_ID nApplicationID, const int nGamePort, bool bClientOnly, ILinksManager *pLinksManager );
	// get current state (active/inactive/connecting)
	virtual EState GetState() const;
	// get reject reason (then )
	virtual EReject GetRejectReason() const { return lastReject; }
	// connect to the game with particular address
	virtual void ConnectGame( const CNodeAddress &addr, const MemoryStream &pwd );
	// start game (server)
	virtual void StartGame();
	// start sending game info (for server), should be compatible with gamespy
	virtual void StartGameInfoSend( const SGameInfo &gameInfo );
	// stop sending game info (for server)
	virtual void StopGameInfoSend();
	// start accepting new players (for server)
	virtual void StartNewPlayerAccept();
	// stop accepting new players (for server)
	virtual void StopNewPlayerAccept();
	// get game info (for client)
	virtual bool GetGameInfo( int nIdx, CNodeAddress *pAddr, bool *pWrongVersion, float *pPing, SGameInfo *pGameInfo );
	// refresh servers list ( for client )
	virtual void RefreshServersList() { }
	// send broadcast message for all
	virtual bool SendBroadcast( const MemoryStream &pkt );
private:
	struct SDataToSend
	{
		int nClient;
		MemoryStream pkt;
	};
	CTSList<SDataToSend> dataToSend;
	virtual bool SendDirectInternal( int nClient, MemoryStream &pkt );
public:
	// send direct message for client 'nClient'
	virtual bool SendDirect( int nClient, const MemoryStream &pkt );
	// kick player 'nClient'
	virtual void Kick( int nClient );
	// get next message
private:
	struct SDataReceived
	{
		EMessage eMsg;
		int nClientID;
		vector<int> received;
		MemoryStream pkt;
	};
	CTSList<SDataReceived> dataReceived;
	virtual bool GetMessageInternal();
public:
	virtual bool GetMessage( EMessage *pMsg, int *pClientID, vector<int> *pReceived, MemoryStream *pPkt );
	// ping of the client, -1 if client doesn't exist
	virtual const float GetPing( unsigned int nClientID );
	// time since last message was received from this client
	virtual const float GetTimeSinceLastRecv( unsigned int nClientID );
	// step net driver
	virtual void Step();
	// send IP network unreliable broadcast
	virtual void SendIPNetworkBroadcast( const MemoryStream &pkt );
	virtual int GetSelfClientID() { return login.GetSelfClientID(); }

	virtual void AddP2PClient( const NNet::CNodeAddressSet &localAddresses, const CNodeAddress &externalAddr,
		int nClientID )
	{
		SClientAddressInfo addrInfo;
		addrInfo.inetAddress = externalAddr;
		addrInfo.localAddress = localAddresses;
		AddNewP2PClient( addrInfo, nClientID );
		state = ACTIVE;
	}

	virtual void SetSelfClientID( int nMyID ) { login.SetSelfClientID( nMyID ); }

	virtual const string GetIP( unsigned int nClientID );
	virtual const int GetPort( unsigned int nClientID );
	// 
	// for debug
	virtual const char* GetAddressByClientID( unsigned int nClientID ) const;

	virtual void UseClientToClientShortcuts( bool bUse ) { bUseClientToClientShortcuts = bUse; }

	virtual void PauseNet();
	virtual void UnpauseNet();
	virtual void SetLag( const DWORD period );
	
	// thread functions for internal use only
	void StartThread();
	bool CanWork();
	void FinishThread();
	//
	int operator&( IBinSaver &saver ) { return 0; }
};
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
