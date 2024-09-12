#pragma once

namespace NNet
{
typedef unsigned int APPLICATION_ID;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct SNetDriverConsts
{
	// время, после которого drop клиента [s]
	int fTimeout;
	// время, после которого удаление сервера из serverslist
	float fServerListTimeout;

	SNetDriverConsts() : fTimeout( 60 ), fServerListTimeout( 20 ) {}
	SNetDriverConsts( const int _nTimeOut ) : fTimeout( _nTimeOut ), fServerListTimeout( 20 ) { }
};
////////////////////////////////////////////////////////////////////////////////////////////////////
// abstraction from SOCKET
_interface ILinksManager : public CObjectBase
{
	virtual bool MakeBroadcastAddr( class CNodeAddress *pRes, int nPort ) const = 0;
	virtual bool IsLocalAddr( const CNodeAddress &test ) const = 0;
	virtual bool Send( const CNodeAddress &dst, MemoryStream &pkt ) const = 0;
	virtual bool Recv( class CNodeAddress *pSrc, MemoryStream *pPkt ) const = 0;
	virtual bool GetSelfAddress( class	CNodeAddressSet *pRes ) const = 0;
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
_interface ILinksManagerContainer: public CObjectBase
{
	enum { tidTypeID = 0x8C31D480 };
	virtual ILinksManager *GetGameLinksManager() = 0;
	virtual ILinksManager *GetUnboundLinksManager() = 0;
	virtual ILinksManager *GetLinksManagerOnPort( int nPort ) = 0;
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ILinksManagerContainer *CreateLinksManagerContainer();
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
_interface IDriver : public CObjectBase
{
	enum EState
	{
		INACTIVE,
		ACTIVE,
		CONNECTING
	};
	enum EReject
	{
		NONE,
		TIMEOUT,
		BANNED,
		WRONG_VERSION,
		MAXPLAYERS_REACHED,
		PASSWORD_FAILED,
		ALREADY_CONNECTED,
		FORBIDDEN
	};
	enum EMessage
	{
		NEW_CLIENT,
		REMOVE_CLIENT,
		DIRECT,
		BROADCAST,
		SERVER_DEAD,
		KICKED,
		EM_IP_NETWORK_BROADCAST
	};
	enum EServerGameMode
	{
		ESGM_WAIT,						// waiting for players to join
		ESGM_SETTINGS,				// players are determining game parameters, no joining allowed
		ESGM_CLOSEDPLAYING,		// game is in progress, no joining allowed
		ESGM_OPENPLAYING,			// game is in progress, players may still join
		ESGM_DEBRIEFING,			// game is over, stats/info is being shown, no joining allowed
		ESGM_EXITING,					// server is shutting down, remove from server list
	};

	///< default LAN game connection port
	const static unsigned int LAN_GAME_PORT = 15147;

	struct SGameInfo
	{
		ZDATA
		string szServerName;
		string szGameType;
		int nCurPlayers, nMaxPlayers;
		EServerGameMode eGameMode;
		bool bPasswordRequired;
		MemoryStream gameSettings;
		ZEND int operator&( IBinSaver &f ) { f.Add(2,&szServerName); f.Add(3,&szGameType); f.Add(4,&nCurPlayers); f.Add(5,&nMaxPlayers); f.Add(6,&eGameMode); f.Add(7,&bPasswordRequired); f.Add(8,&gameSettings); return 0; }

		SGameInfo() : szGameType( "" ), nCurPlayers( 0 ), nMaxPlayers( 0 ), eGameMode( ESGM_SETTINGS ), bPasswordRequired( false ) { }
	};
	//
	virtual void Init( const APPLICATION_ID nApplicationID, const int nGamePort, bool bClientOnly, ILinksManager *pLinksManager ) = 0;
	// get current state (active/inactive/connecting)
	virtual EState GetState() const = 0;
	// get reject reason (then )
	virtual EReject GetRejectReason() const = 0;
	// connect to the game with particular address
	virtual void ConnectGame( const CNodeAddress &addr, const MemoryStream &pkt ) = 0;
	// start game (server)
	virtual void StartGame() = 0;
	// start sending game info (for server)
	virtual void StartGameInfoSend( const SGameInfo &gameInfo ) = 0;
	// stop sending game info (for server)
	virtual void StopGameInfoSend() = 0;
	// start accepting new players (for server)
	virtual void StartNewPlayerAccept() = 0;
	// stop accepting new players (for server)
	virtual void StopNewPlayerAccept() = 0;
	// get game info (for client)
	virtual bool GetGameInfo( int nIdx, CNodeAddress *pAddr, bool *pWrongVersion, float *pPing, SGameInfo *pGameInfo ) = 0;
	// refresh servers list ( for client )
	virtual void RefreshServersList() = 0;
	// send broadcast message for all
	virtual bool SendBroadcast( const MemoryStream &_pkt ) = 0;
	// send direct message for client 'nClient'
	virtual bool SendDirect( int nClient, const MemoryStream &_pkt ) = 0;
	// kick player 'nClient'
	virtual void Kick( int nClient ) = 0;
	// send IP network unreliable broadcast
	virtual void SendIPNetworkBroadcast( const MemoryStream &pkt ) = 0;
	// get next message
	virtual bool GetMessage( EMessage *pMsg, int *pClientID, vector<int> *pReceived, MemoryStream *pPkt ) = 0;
	// ping of the client, -1 if client doesn't exist
	virtual const float GetPing( unsigned int nClientID ) = 0;
	// time since last message was received from this client
	virtual const float GetTimeSinceLastRecv( unsigned int nClientID ) = 0;
	// step net driver
	virtual void Step() = 0;
	// nClientID of this host
	virtual int GetSelfClientID() = 0;

	// for debug of lagging net
	virtual void PauseNet() {}
	virtual void UnpauseNet() {}
	virtual void SetLag( const DWORD ) {}

	virtual const string GetIP( unsigned int nClientID ) = 0;
	virtual const int GetPort( unsigned int nClientID ) = 0;
	
	virtual void AddP2PClient( const NNet::CNodeAddressSet &localAddresses, const CNodeAddress &externalAddr,
		int nClientID ) = 0;

	virtual void SetSelfClientID( int nMyID ) = 0;
	// for debug
	virtual const char* GetAddressByClientID( unsigned int ) const { return "Unknown"; }

	virtual void UseClientToClientShortcuts( bool bUse ) = 0;
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
IDriver* CreateNetDriver( const SNetDriverConsts &consts, bool bIsBroadcast = true );

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
string NetMessage2String( IDriver::EMessage messageId );

void GetNOPStream( MemoryStream *pNOP );
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
