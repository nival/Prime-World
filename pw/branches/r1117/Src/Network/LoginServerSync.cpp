#include "stdafx.h"
#include "LoginServerSync.h"

namespace Login
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LoginServerSync::LoginServerSync( Network::INetworkDriver* _pDriver, const Network::NetAddress& _loginServerAddress, 
  ILoginProcessor* _processor, ::SSL_CTX* _secureContext, Login::ClientVersion const & _clientVer)
  : LoginServerBase( _pDriver, _loginServerAddress, 0, _secureContext, _clientVer )
{
  processor = _processor;
  Start(); // запускаем thread
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool LoginServerSync::ProcessNewContext( StrongMT<SLoginContext>& context )
{
  LoginRequestMessage & req = context->request;
  LoginResultMessage & resp = context->response;
  // обратимся к нашему виртуальному процессору насчет логина
  resp.loginResult = processor->CheckLogin( req.login, req.password, context->connection, &resp );
  // и сразу же отсылаем ответ
  SendReply( context );
  return false; // не надо сразу дропать клиента, пусть до него дойдет SendReply
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LoginServerSync::OnNewLoginSuccess( LoginResultMessage & resp )
{
  processor->NewClientLoggedIn( resp.userId, resp.sessionId );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace Login