#include "stdafx.h"
#include "SimpleLoginProcessor.h"

//#include "rpc/P2PNode.h"
#include "Network/AddressTranslator.h"
#include "Network/ClusterConfiguration.h"
#include "Server/ZZima/ZZimaService.h" // E_XXX error codes

namespace Login {

static unsigned int s_prepareUserEnvRpcCallTimeout = 20;
REGISTER_VAR( "login_prepare_user_env_rpc_call_timeout", s_prepareUserEnvRpcCallTimeout, STORAGE_NONE );


ServerLoginProcessorBase::ServerLoginProcessorBase()
{
}



// helper: заодно считаем кол-во асинхронных операций за степ (дл€ которых isAsync == true)
void ServerLoginProcessorBase::SetClientStage( SLoginContext * context, const SLoginContext::TStage stage, const bool isAsync )
{ 
  context->SetStage( stage ); 
  if( isAsync ) 
    asyncOpCount++; 
}



bool ServerLoginProcessorBase::MainStep()
{
  timeServerNow = NHPTimer::GetScalarTime();
  asyncOpCount = 0; // счетчик "асинхронных операций в течение step-а", в начале степа (mainStep) как раз обнул€ем
  return true;
}



bool ServerLoginProcessorBase::ClientStep( SLoginContext * context )
{
  bool async_client_ok = false;
  NI_ASSERT( context, "Bad login context in ServerLoginProcessorBase::ClientStep");

  LoginRequestMessage & req = context->request;
  LoginResultMessage & resp = context->response;
  LoginResultData & result = context->resultData;

  if ( Network::ConnectionState::Closed == context->connection->GetStatus() )
  {// коннект, увы, успел закрытьс€
    resp.loginResult = ELoginResult::NoConnection; 
    LOG_W(LOGIN_CHNL) << "connection closed: (stage=" << context->stage << ", login=" << req.login << ")";
    return false;
  }

  if (!userMngrIface_->isopen())
  {
    resp.loginResult = ELoginResult::ServerError;
    LOG_W(LOGIN_CHNL).Trace("No user manager(login=%s u=%d sessionKey=%s)", req.login.c_str(), result.nUserID, req.sessionKey.c_str());
    return false;
  }

  switch( context->stage )
  {
  case SLoginContext::STAGE_NEW:
    {
      resp.loginResult = ELoginResult::ServerError; // если что-нибудь случитс€ и мы развалимс€, пусть будет "Server Internal"
      result.nErrorCode = ZZima::E_OK;
      SetClientStage( context, SLoginContext::_TIME_LOGIN_CHECK_START ); // debug timing
      bool success = PerformLoginCheck(req.login, req.password, context->connection, &result);
      resp.userId = result.nUserID;
   
      if ( result.nErrorCode == ZZima::E_ASYNC_WAIT )
      {// это не fail, просто у нас async login processor (напр. ZZima), к которому надо ломитьс€ асинхронно, через threads
        resp.loginResult = ELoginResult::AsyncWait;
        AsyncLoginRequest(req.login, req.password, context); // дл€ Async проверки нужен ptr на весь наш логин-контекст
        LOG_D(LOGIN_CHNL) << "login check: async_wait, wait for ZZima (login=" << req.login << ")";
        SetClientStage( context, SLoginContext::STAGE_ASYNC_LOGIN_WAIT ); 
        break;
      }
      else
      {
        resp.loginResult = success ? ELoginResult::AsyncSuccess : ELoginResult::AsyncFail;
        context->isLoginChecked = true;
      }
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Ѕ≈« break: если результат не ASYNC_WAIT, проваливаемс€ сразу дальше, в синхронную обработку Async-результата, 
    //   без стадии STAGE_ASYNC_LOGIN_WAIT
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  case SLoginContext::STAGE_ASYNC_LOGIN_WAIT: // если пришли нормальным путем, после Login
    if ( context->isLoginChecked )
    {
      resp.userId = result.nUserID;
      SetClientStage( context, SLoginContext::_TIME_ASYNC_LOGIN_DONE ); // debug timing
      if ( resp.loginResult != ELoginResult::AsyncSuccess )
      {// не залогало         
        LOG_W(LOGIN_CHNL) << "login check fail, login=" << req.login << "/" << resp.userId;
        resp.loginResult = ELoginResult::Refused;
        SetClientStage( context, SLoginContext::_TIME_FAIL ); // debug timing
        return false;
      }

      SetClientStage( context, SLoginContext::_TIME_REPARE_USER_ENVIRONMENT);
      UserManager::UserEnvInfo uei(resp.userId, req.sessionKey, resp.sessionPath, NStr::ToUnicode(req.login), 
        Login::LoginType::PARTIAL_RECONNECT == req.loginType, context->gameid);

      userMngrIface_->iface()->PrepareUserEnv(uei, RemotePtr<UserManager::RIPrepareUserEnvCallback>(context), 
        context, &SLoginContext::OnPrepareUserEnvReturn, resp.userId, s_prepareUserEnvRpcCallTimeout);

      SetClientStage( context, SLoginContext::STAGE_PREPARE_USER_ENVIRONMENT_STARTED, true );
    }
    else if ( context->IsTimeout( timeServerNow ) )
    {
      LOG_W(LOGIN_CHNL) << "web login timeout, login=" << req.login;
      resp.loginResult = ELoginResult::ServerError; 
      SetClientStage( context, SLoginContext::_TIME_FAIL ); // debug timing
      return false;
    }
    break;

  case SLoginContext::STAGE_PREPARE_USER_ENVIRONMENT_STARTED:
    break;

  case SLoginContext::STAGE_PREPARE_USER_ENVIRONMENT_RETURN:
    {
      UserManager::Result::Enum rc = context->rcUserEnvPrep;
      if ( UserManager::Result::IN_PROGRESS == rc )
      {
        LOG_M(LOGIN_CHNL).Trace("User environment preparation in progress(login=%s id=%d)", req.login.c_str(), resp.userId);
        SetClientStage( context, SLoginContext::STAGE_PREPARE_USER_ENVIRONMENT_IN_PROGRESS);
      }
      else
      {
        if ( rc < 0 )
        {
          LOG_W(LOGIN_CHNL).Trace("User environment preparation is FAILED: %s(rc=%d login=%s id=%d)", 
            UserManager::Result::ToString(rc), (int)rc, req.login.c_str(), result.nUserID);

          if (UserManager::Result::USER_ALREADY_REGISTERED == rc)
            resp.loginResult = ELoginResult::AlreadyIn;
          else
            resp.loginResult = ELoginResult::ServerError;
        }
        else
        {
          LOG_C(LOGIN_CHNL).Trace("PrepareUserEnv return unexpected code: %s(rc=%d login=%s id=%d)", 
            UserManager::Result::ToString(rc), (int)rc, req.login.c_str(), result.nUserID);
          NI_ALWAYS_ASSERT(NStr::StrFmt("PrepareUserEnv return unexpected code: %s(rc=%d login=%s id=%d)", 
            UserManager::Result::ToString(rc), (int)rc, req.login.c_str(), result.nUserID));
          resp.loginResult = ELoginResult::ServerError;
        }

        SetClientStage( context, SLoginContext::_TIME_FAIL );
        return false;
      }
    }
    break;

  case SLoginContext::STAGE_PREPARE_USER_ENVIRONMENT_IN_PROGRESS:
    {
      if ( context->IsTimeout( timeServerNow ) )
      {
        LOG_W(LOGIN_CHNL).Trace("UserManager::PrepareUserEnv callback TIMEOUT(login=%s id=%d)", req.login, resp.userId);
        resp.loginResult = ELoginResult::ServerError;
        SetClientStage( context, SLoginContext::_TIME_FAIL );
        return false;
      }
    }
    break;

  case SLoginContext::STAGE_PREPARE_USER_ENVIRONMENT_COMPLETED:
    if ( UserManager::Result::SUCCESS == context->rcUserEnvPrep )
    {
      LOG_M(LOGIN_CHNL).Trace("User environment preparation COMPLETED(login=%s id=%d relay=%s secondary-relay=%s)",
        req.login.c_str(), resp.userId, context->relay.c_str(), context->secondaryRelay.c_str());

      resp.relayAddress = context->relayAddr;
      resp.secondaryRelayAddress = context->secondaryRelayAddr;
      async_client_ok = true;
    }
    else
    {
      LOG_W(LOGIN_CHNL).Trace("User environment preparation FAILED: %s(rc=%d login=%s id=%d)",
        UserManager::Result::ToString(context->rcUserEnvPrep), (int)context->rcUserEnvPrep, req.login.c_str(), resp.userId);

      if (UserManager::Result::USER_ALREADY_REGISTERED == context->rcUserEnvPrep)
        resp.loginResult = ELoginResult::AlreadyIn;
      else
        resp.loginResult = ELoginResult::ServerError;
      SetClientStage( context, SLoginContext::_TIME_FAIL );
      return false;
    }
    break;

  default:
    {
      LOG_A(LOGIN_CHNL) << "BAD login context stage=" << context->stage << ", login=" << req.login << " id=" << resp.userId;
      return false;
    }
  }

  if ( async_client_ok )
  {
    resp.loginResult = ELoginResult::Success;
    SetClientStage( context, SLoginContext::_TIME_SUCCESS ); // debug timing
    return false;
  }

  return true; // продолжаем работать с клиентом (login context), не удал€йте его
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

} // namespace Login
