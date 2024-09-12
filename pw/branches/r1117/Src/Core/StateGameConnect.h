/**
 *	deprecated
 *  use StateWaitingRoomClient and StateWaitingRoomHost instead
 */


//#pragma once
//
//#include "StateLANBase.h"
//#include "../Net/NetAddress.h"
//
//namespace NCore
//{
//class CoreFSM;
//
//class CStateConnectingToGame : public CStateLANBase
//{
//	OBJECT_METHODS( 0x1F4A8B2F, CStateConnectingToGame )
//
//	enum EStage
//	{
//		STAGE_INIT,
//		STAGE_LOGGING_IN,
//		STAGE_ACCEPTED,
//		STAGE_SUCCESS,
//		STAGE_FAILED,
//	};
//
//	struct SConnectionInfo
//	{
//		int nNode;
//		bool bConnected;
//		int nClient;
//		string szIP;
//		int nPort;
//
//		SConnectionInfo() : bConnected(false), nClient(-1), nNode(-1) {}
//	};
//	typedef list<SConnectionInfo> CConnections;
//
//	EStage eStage;
//	list<int> pendingClients;
//	CConnections nodes;
//	int nMyNode;
//	int nHostClientID;
//	NNet::CNodeAddress connectTo;
//
//	void CheckAllConnected();
//	void AddConnectedNode( int nClient, int nNode );
//	void AddUnconnectedNode( int nNode, string szIP, int nPort );
//
//	virtual void SubscribeUpdates() {}
//	
//	nstl::string Stage2String() const;
//
//	IBaseFSMState* CreateClientState();
//	CStateConnectingToGame() {}
//
//protected:
//	virtual void Init();
//
//	virtual void OnClientAdd( int nClient );
//	virtual void OnClientRemove( int nClient );
//	virtual void OnKicked();
//
//	bool OnConnectAccepted( int nClient, struct SAcceptConnectionPacket *pPacket );
//	bool OnConnectRefused( int nClient, struct SRefuseConnectionPacket *pPacket );
//	bool OnHandshake( int nClient, struct SConnectHandshakePacket *pPacket );
//	bool OnNewClientNotify( int nClient, struct SNewClientNotifyPacket *pPacket );
//
//public:
//	CStateConnectingToGame( CoreFSM *pContext, NNet::IDriver *pDdriver, const NNet::CNodeAddress &_addr );
//
//	virtual IBaseFSMState *Step();
//};
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//}; // namespace NCore
