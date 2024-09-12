#pragma once
#include "LoginServerBase.h"

namespace Login
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SYNC processing version (legacy/client local/test)
class LoginServerSync : public LoginServerBase
{
  NI_DECLARE_REFCOUNT_CLASS_1( LoginServerSync, LoginServerBase )

public:
  // этот вариант создается с синхронным процессором (ILoginProcessor)
  LoginServerSync( Network::INetworkDriver* _pDriver, const Network::NetAddress& _loginServerAddress, 
    ILoginProcessor* _processor, ::SSL_CTX* secureContext, Login::ClientVersion const & clientVer = Login::ClientVersion());
  
protected:
  virtual void OnNewLoginSuccess( LoginResultMessage & resp );
  virtual bool ProcessNewContext( StrongMT<SLoginContext> & context );

private:
	ILoginProcessor* processor;
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace Login
