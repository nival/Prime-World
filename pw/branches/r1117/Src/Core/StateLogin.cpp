#include "stdafx.h"
#include "StateLogin.h"
#include "CoreFSM.h"
#include "StateLobby.h"
#include "MessagesGeneral.h"
#include "MessagesInGame.h"
#include "MessagesLobby.h"
#include "../Net/NetDriver.h"
#include "StateCreatingGame.h"
#include "StateWaitingRoomClient.h"
#include "StateWaitingRoomHost.h"
#include "NetMessagesProcessor.h"

#include "GameNode.h"
#include "GameMode.h"

#include "../PF_Core/World.h"


namespace NCore
{
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void CStateLogin::SubscribeUpdates()
  {
    pContext->RegisterProcessorToCore( this );
    Subscribe( &CStateLogin::EnterToLobby );
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void CStateLogin::Init()
  {
    CoreFSMState::Init();
    pContext->RegisterMessageBuilder( GetTypeId(), &NCore::LoginScreenState::NewLoginScreenState );
  }


  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  void CStateLogin::EnterToLobby(LoginToLobby const &msg)
  {
    m_login    = true;
  }


  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  IBaseFSMState* CStateLogin::Step(float)
  {
    if (m_login)
    {
      return new CStateLobby(pContext);
    }

    return NULL;
  }
}
