#include "UserManagerSvc/stdafx.h"
#include "UserManagerSvc/PrepareUserEnvCtx.h"
#include "UserManagerSvc/UserManagerCfg.h"

NI_DEFINE_REFCOUNT(UserManager::PrepareUserEnvCtx);

namespace UserManager
{
  PrepareUserEnvCtx::PrepareUserEnvCtx()
    :st_(State::INIT),
    timemark_(0.0)
  {
  }

  PrepareUserEnvCtx::PrepareUserEnvCtx( UserEnvInfo const & _uei, RIPrepareUserEnvCallback * _cb, IUserRegister * _ur, IPrepareUserEnvNotify * _notify, PartialReconnectSettings const & _prs)
    :st_(State::INIT),
    uei_(_uei),
    cb_(_cb),
    userRegister_(_ur),
    notify_(_notify),
    timemark_(0.0),
    prs_(_prs)
  {
  }

  PrepareUserEnvCtx::~PrepareUserEnvCtx()
  {
  }

  void PrepareUserEnvCtx::OnRelayAllocateReturn(int _rc, Cluster::TUserId _userid, rpc::CallStatus _status)
  {
    if (isclosed_())
    {
      LOG_W(UMLOG).Trace("%s: context is already CLOSED(rc=%d userid=%d rpcsts=%d)", 
        __FUNCTION__, _rc, (int)_status, _userid);
      return;
    }

    if (_status != rpc::CallSuccessful)
    {
      LOG_E(UMLOG).Trace("%s: rpc call timeout/disconnect(rpcsts=%d userid=%d)", 
        __FUNCTION__, (int)_status, _userid);
      complete_(Result::RELAY_ALLOCATION_FAILED, uei_.userid_);

      state_(State::CLOSED);
      return;
    }

    if (_rc >=0)
    {
      LOG_M(UMLOG).Trace("%s (u=%d rc=%d)", __FUNCTION__, uei_.userid_, _rc);
      notify_->OnRelayAllocationInProgress(this);
      state_(State::RELAY_ALLOCATION_RETURN);
    }
    else
    {
      LOG_E(UMLOG).Trace("%s: relay allocation FAILED (u=%d rc=%d)", __FUNCTION__, uei_.userid_, _rc);
      complete_(Result::RELAY_ALLOCATION_FAILED, uei_.userid_);
    }
  }

  void PrepareUserEnvCtx::OnRelayAllocated(Transport::TClientId _clienid, int _userctx, 
    Transport::TServiceId const & _relay, Network::NetAddress const & _relayaddr,
    Transport::TServiceId const & _secondaryrelay, Network::NetAddress const & _secondaryaddr)
  {
    if (isclosed_())
    {
      LOG_W(UMLOG).Trace("%s: context is already CLOSED(u=%d userctx=%d relay=%s relayaddr=%s secondaryrelay=%s secondaryaddr=%s)",
        __FUNCTION__, _clienid, _userctx, _relay.c_str(), _relayaddr.c_str(), _secondaryrelay.c_str(), _secondaryaddr.c_str());
      return;
    }

    LOG_M(UMLOG).Trace("%s(u=%d userctx=%d relay=%s relayaddr=%s secondaryrelay=%s secondaryaddr=%s)",
      __FUNCTION__, _clienid, _userctx, _relay.c_str(), _relayaddr.c_str(), _secondaryrelay.c_str(), _secondaryaddr.c_str());

    relay_ = _relay;
    relayAddr_ = _relayaddr;
    secondaryrelay_ = _secondaryrelay;
    secondaryrelayAddr_ = _secondaryaddr;

    if (!uei_.partialReconnect_)
    {
      if (!relay_.empty())
      {
        int rc = userRegister_->RegisterUser(uei_);
        if (rc >= 0)
        {
          LOG_M(UMLOG).Trace("User successfully registered(u=%d)", uei_.userid_);
          complete_(Result::SUCCESS, uei_.userid_, relay_, relayAddr_, secondaryrelay_, secondaryrelayAddr_);
        }
        else
        {
          LOG_E(UMLOG).Trace("User already registered(u=%d)", uei_.userid_);
          complete_(Result::USER_ALREADY_REGISTERED, uei_.userid_);
        }
      }
      else
      {
        LOG_E(UMLOG).Trace("%s: relay allocation is FAILED(u=%d)", __FUNCTION__, uei_.userid_);
        complete_(Result::RELAY_ALLOCATION_FAILED, uei_.userid_);
      }
    }
    else
    {
      if (!secondaryrelayAddr_.empty())
      {
        LOG_M(UMLOG).Trace("%s: secondary relay successfully allocated for user(u=%d)", __FUNCTION__, uei_.userid_);
        complete_(Result::SUCCESS, uei_.userid_, relay_, relayAddr_, secondaryrelay_, secondaryrelayAddr_);
      }
      else
      {
        LOG_E(UMLOG).Trace("%s: secondary relay allocation is FAILED(u=%d)", __FUNCTION__, uei_.userid_);
        complete_(Result::RELAY_ALLOCATION_FAILED, uei_.userid_);
      }
    }
  }

  void PrepareUserEnvCtx::complete_(int _result, Cluster::TUserId _userid, 
    Transport::TServiceId const & _relay, Network::NetAddress const & _relayaddr, 
    Transport::TServiceId const & _secondaryrelay, Network::NetAddress const & _secondaryaddr,
    bool _partialReconnectSupported, unsigned int _partialReconnectRetries, unsigned int _partialReconnectRetryTimeout)
  {
    notify_->OnPrepareUserEnvCompleted(_result, this); //FIXME: ÇÄÅÑÜ ÓÄÀËßÅÒÑß ÈÇ ÏÀÐÅÍÒÀ ÎÁÚÅÊÒ 'this' !!!

    RelayInfo relayInfo(_relay, _relayaddr, _secondaryrelay, _secondaryaddr);
    PartialReconnectInfo preconnInfo( prs_.supported(), prs_.retries(), prs_.retryTimeout() );
    cb_->OnPrepareUserEnv( _result, _userid, relayInfo, preconnInfo );
    state_( State::CLOSED );
  }

  int PrepareUserEnvCtx::Complete(Result::Enum err)
  {
    NI_ASSERT(err < 0, "Here must be error.");

    if (isclosed_())
    {
      LOG_W(UMLOG).Trace("%s: context is already CLOSED(u=%d)", __FUNCTION__, uei_.userid_);
      return -1;
    }

    complete_(err, uei_.userid_);
    return 0;
  }

}
