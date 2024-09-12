#pragma once

#include "CoreFSMState.h"
#include "../Net/NetAddress.h"
#include "MessagesGeneral.h"
#include "MessagesLogin.h"

namespace NCore
{
  class CStateLogin 
    : public CoreFSMState
  {
    OBJECT_METHODS( 0xB5C94C0, CStateLogin );

    bool m_login;
    wstring m_name;     ///< User name
    wstring m_password; ///< User password

    virtual void SubscribeUpdates();
    void EnterToLobby(LoginToLobby const &msg);

    CStateLogin() : m_login(false) {}

  public:
    CStateLogin( CoreFSM *pContext ) : CoreFSMState( pContext ), m_login(false) {}
    virtual void Init();
    virtual IBaseFSMState* Step(float);
  };
}
