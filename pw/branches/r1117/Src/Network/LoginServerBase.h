#pragma once

#include "ServerAppBase/NivalService.h"
#include "../System/Thread.h"
#include "RPC/RPC.h"
//#include "RPC/P2PNode.h" // ValQueryCB<>
#include "System/TextFileDumper.h"
#include "System/HPTimer.h"

#include "LoginTypes.h"
#include "LoginData.h"
#include "ConnectionHandler.h"
#include "LoginClientVersion.h"
#include "LoginContext.h"

namespace Login
{

class LoginServerBase : public Network::IConnectionProcessor, public Transport::BaseService
{
  NI_DECLARE_REFCOUNT_CLASS_1( LoginServerBase, Transport::BaseService )

protected:
  LoginServerBase( const Transport::ServiceParams & _svcParams, const Transport::CustomServiceParams & _customParams, const Network::NetAddress& _loginServerAddress );

  void StepLogin();

 // IConnectionProcessor
  virtual bool ProcessPacket(Stream* stream, Network::IConnection *connection);
  virtual void OnDropConnection(Network::IConnection* connection) {} // // найти у себя соотв. context и пометить для удаления?..  

  // Own: 
  virtual void OnNewLoginSuccess( LoginResultMessage & resp ) {}
  virtual bool ProcessNewContext( SLoginContext * context ) { return true; } // "всё обработали, сразу дропайте клиента"

  void SendReply( SLoginContext * context );

private:
  ELoginResult::Enum checkClientVersion(Login::ClientVersion const & cv);

  Network::ConnectionHandler handler;

  Login::ClientVersion compatibleClientVersion;
};

} // namespace Login
