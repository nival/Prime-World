#pragma once

#include "StateLANBase.h"

namespace NCore
{
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CoreFSM;

class CStateGameRoomHost : public CStateLANBase
{
	OBJECT_METHODS( 0x1F4A8B31, CStateGameRoomHost )

	struct SNodeInfo
	{
		bool bPresent;
		bool bConnectedToOthers;
		int nClient;
		string szIP;
		int nPort;

		SNodeInfo() : bPresent(false), bConnectedToOthers(false), nClient(-1) {}
	};
	typedef vector<SNodeInfo> CNodesInRoom;

	CNodesInRoom nodes;

	const int CountNodes() const;
	const int AssignNewNode( int nClient );
	CNetPacket* ComposeAcceptPacket( int nNewNode );
	const bool CanAcceptNewNode();
	virtual void SubscribeUpdates() {}
	
protected:
	CStateGameRoomHost() {}
	void Init();

	virtual void OnClientAdd( int nClient );
	virtual void OnClientRemove( int nClient );
	virtual void OnKicked();

	bool OnClientConnectedToOthers( int nClient, struct SConnectedToOthersPacket *pPacket );

	bool OnTestGameRoom( int nClient, struct STestGameRoomPacket *pPacket );

public:
  CStateGameRoomHost( CoreFSM *pContext, NNet::IDriver *pDdriver );

	virtual IBaseFSMState *Step();
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}; // namespace NCore
