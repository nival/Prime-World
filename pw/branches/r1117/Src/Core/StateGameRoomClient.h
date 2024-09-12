#pragma once

#include "BaseState.h"
#include "StateLANBase.h"

namespace NCore
{
class CoreFSM;

class CStateGameRoomClient : public CStateLANBase
{
	OBJECT_METHODS( 0x1F4A8B30, CStateGameRoomClient )

	hash_map<int,int> nodesMap;
	int nMyNode;
	bool bExitToLobby;

	CStateGameRoomClient() {}

protected:
	virtual void OnClientAdd( int nClient );
	virtual void OnClientRemove( int nClient );
	virtual void OnKicked();

	virtual void SubscribeUpdates() {}

	bool OnHandshake( int nClient, struct SConnectHandshakePacket *pPacket );
	bool OnNewClientNotify( int nClient, struct SNewClientNotifyPacket *pPacket );

	bool OnTestGameRoom( int nClient, struct STestGameRoomPacket *pPacket );

public:
  CStateGameRoomClient( CoreFSM *pContext, NNet::IDriver *pDdriver, hash_map<int,int> &_nodesMap, int _nMyNode );

	virtual IBaseFSMState *Step();
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}; // namespace NCore
