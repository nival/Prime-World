#pragma once

#include "CoreFSM.h"
#include "CoreFSMState.h"
#include "../System/HPTimer.h"
#include "GameMode.h"
#include "../Net/NetDriver.h"
#include "../Net/NetAddress.h"
#include "../System/Update.h"
#include "MessagesGeneral.h"

namespace NCore
{

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CoreFSM;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CStateLobby : public CoreFSMState
{
	OBJECT_METHODS( 0x1F4A8B35, CStateLobby )

  enum ETransfer
  {
    ET_NONE,
    ET_SINGLE,
    ET_SERVER,
    ET_CLIENT,
    ET_LOGIN,
  };
  
  CPtr<IBaseFSMState> pNextState;

  int          m_selectedHero;
  bool         m_startGame;
  MapStartInfo m_startInfo;
  ETransfer    eGoTo;
  NNet::CNodeAddress url;

  IBaseFSMState *createStateForSingleGame();
  IBaseFSMState *createStateForQuickPlay();
protected:


  void ConnectToServer();
  void GameQuit( const struct GameQuitMessage& );

  virtual void SubscribeUpdates();
  void StartSingleGame( const struct SetInGameState& );
  void StartServerGame( const struct StartServer& );
  void StartClientGame( const struct StartClient& );
  void SelectHero( const struct SelectHeroMessage& );

	CStateLobby() {}

public:
  CStateLobby( CoreFSM *pContext);

  virtual void Init();
  virtual IBaseFSMState* Step(float);
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}; // namespace NCore
