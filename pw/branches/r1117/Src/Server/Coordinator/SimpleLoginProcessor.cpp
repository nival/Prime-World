#include "stdafx.h"
#include "SimpleLoginProcessor.h"

//#include "rpc/P2PNode.h"
#include "Network/AddressTranslator.h"

#if defined( NV_WIN_PLATFORM )
#include <shlwapi.h>
#endif // defined( NV_WIN_PLATFORM )

using namespace Login;


SimpleLoginProcessor::SimpleLoginProcessor( unsigned int _firstUserId, unsigned int _maskUserId ) :
ServerLoginProcessorBase(),
nextId( _firstUserId ),
maskUserId( _maskUserId )
{
}



bool SimpleLoginProcessor::PerformLoginCheck( const string & login, const string & password, Network::IConnection * connection, Login::LoginResultData * result )
{
  if ( !login.empty() && login[0] != '_' )
  {
    LoggedUsersT::iterator it = loggedUsers.find( login );
    if ( it != loggedUsers.end() )
    {
      if( result->nUserID == 0 ) // ненулевой nUserID == признак того, что трогать его не надо (SessionLogin)
        result->nUserID = it->second;
      result->username = NStr::ToUnicode( login );
      return true;
    }
  }

  if( result->nUserID == 0 ) // ненулевой nUserID == признак того, что трогать его не надо (SessionLogin)
  {
    result->nUserID = nextId | maskUserId; // ставим бит-признак "userId, авто-генеренного внутри кластера" 
    ++nextId;
  }
  loggedUsers[ login ] = result->nUserID;

  result->username = NStr::ToUnicode( login );
  return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool SimpleLoginProcessor::ClientStep( StrongMT<Login::SLoginContext> & context )
{
  bool res = true;
  switch( context->stage )
  {
  case SLoginContext::STAGE_RECONNECT_CHECK_START:
    {
      userMngrIface_->iface()->FindUserSession(context->sessionKey(), (LoginType::PARTIAL_RECONNECT == context->request.loginType), context.Get(), &SLoginContext::onFindUserSession);
      SetClientStage(context, SLoginContext::STAGE_RECONNECT_CHECK_IN_PROGRESS);
    }
    break;

  case SLoginContext::STAGE_RECONNECT_CHECK_IN_PROGRESS:
    break;

  case SLoginContext::STAGE_RECONNECT_CHECK_FINISH:
    {
      if (Cluster::INVALID_USER_ID == context->GetUserId())
      {
        LOG_E(LOGIN_CHNL).Trace("Reconnect session key is NOT found(u=%d login=%s)",
          context->GetUserId(), context->request.login.c_str());
      }
      else
      {
        LOG_M(LOGIN_CHNL).Trace("Reconnect session key is found(u=%d login=%s sessionKey=%s)",
          context->GetUserId(), context->request.login.c_str(), context->request.sessionKey.c_str());
        SetClientStage(context, SLoginContext::STAGE_NEW);
      }

      if (context->stage != SLoginContext::STAGE_NEW)
      {
        LOG_W(LOGIN_CHNL) << "login check fail, login=" << context->request.login << "/" << context->response.userId;
        context->response.loginResult = ELoginResult::Refused;
        SetClientStage( context, SLoginContext::_TIME_FAIL ); // debug timing
        res = false;
      }
    }
    break;

  default:
    res = Login::ServerLoginProcessorBase::ClientStep(context);
  }

  return res;
}
