#include "transport/stdafx.h"
#include "SecondaryRelayCtx.h"
#include "Network/ClientTransportConfig.h"

namespace Transport
{
  SecondaryRelayCtx::SecondaryRelayCtx(StrongMT<Network::INetworkDriver> const & _netDriver, Login::ClientVersion const & _version, 
    StrongMT<Transport::ITransportSystem> const & _transport)
    :netDriver_(_netDriver),
    version_(_version),
    transport_(_transport),
    repairTimeoutStart_(0),
    repairTimeout_(0),
    logTag_("[SecondaryRelayCtx]"),
    internalState_(InternalState::INIT),
    state_(State::INIT),
    retriesCount_(0)
  {
  }

  SecondaryRelayCtx::~SecondaryRelayCtx()
  {
  }

  int SecondaryRelayCtx::open(StrongMT<Transport::IChannel> const & _chnl, 
    Network::NetAddress const & _loginaddr, string const & _login, string const & _password, 
    string const & _sessionKey, unsigned int _partialReconnectRetries, unsigned int _partialReconnectRetryTimeout)
  {
    LOG_M(0).Trace("%s Open(loginaddr=%s login=%s sessionKey=%s)", 
      logTag_, _loginaddr.c_str(), _login.c_str(), _sessionKey.c_str());

    if (State::CLOSE != state() && State::INIT != state())
      return 1;

    loginAddr_ = _loginaddr;
    login_ = _login;
    password_ = _password;
    sessionKey_ = _sessionKey;
    repairTimeout_ = _partialReconnectRetryTimeout;
    retries_ = _partialReconnectRetries;

    if (_chnl)
    {
      if (Network::ConnectionState::Connected == _chnl->GetStatus())
      {
        relayChannel_ = _chnl;
        internalState(InternalState::CONNECTED);
        state(State::OPEN);
        return 0;
      }
    }

    return open_();
  }

  void SecondaryRelayCtx::close()
  {
    if (State::CLOSE == state())
      return;

    if (relayChannel_)
      relayChannel_->Close();

    state(State::CLOSE);

  }

  void SecondaryRelayCtx::step()
  {
    switch(internalState_)
    {
    case InternalState::INIT:
      break;

    case InternalState::LOGIN:
    {
      Login::ELoginResult::Enum loginResult = loginClient_->Step();
      if (Login::ELoginResult::NoResult != loginResult)
      {
        if (Login::ELoginResult::Success == loginResult)
        {
          string relayAddress;
          loginClient_->GetConnectionData(0, &relayAddress, &userId_, &sessionId_);
          loginClient_ = 0;

          LOG_M(0).Trace("%s Logged in(relayAddress=%s userid=%d sessionid=%s)", 
            logTag_, relayAddress.c_str(), userId_, sessionId_.c_str());

          relayChannel_ = transport_->OpenChannelDirect(Transport::Address(Transport::ENetInterface::FrontEnd, userId_), sessionId_, relayAddress);
          if (!relayChannel_)
          {
            LOG_W(0).Trace("%s Open channel FAILED(relayAddress=%s userid=%d)", 
              logTag_, relayAddress.c_str(), userId_);

            startRetryTimeout(Result::CONNECTION_2_RELAY_FAILED);
          }
          else
          {
            LOG_M(0).Trace("%s Start open channel(relayAddress=%s userid=%d)", 
              logTag_, relayAddress.c_str(), userId_);

            relayChannel_->KeepAlivePeriod(Transport::ClientCfg::GetKeepalivePeriod());
            internalState(InternalState::CONNECTING_2_RELAY);
          }
        }
        else
        {
          WarningTrace("%s Login FAILED(error=%s)", logTag_, Login::ELoginResult::ToString( loginResult ) );
          startRetryTimeout(Result::LOGIN_FAILED);
        }
      }
    }
    break;

    case InternalState::CONNECTING_2_RELAY:
    {
      if (Network::ConnectionState::Connecting != relayChannel_->GetStatus())
      {
        if (Network::ConnectionState::Connected == relayChannel_->GetStatus())
        {
          LOG_M(0).Trace("%s Channel to relay opened(t=%s c=%d)", 
            logTag_, relayChannel_->GetAddress().target.c_str(), relayChannel_->GetInternalClientId());

          internalState(InternalState::CONNECTED);
        }
        else
        {
          LOG_W(0).Trace("%s Open channel FAILED(t=%s c=%d)", 
            logTag_, relayChannel_->GetAddress().target.c_str(), relayChannel_->GetInternalClientId());

          startRetryTimeout(Result::CONNECTION_2_RELAY_FAILED);
        }
      }
    }
    break;

    case InternalState::CONNECTED:
    {
      if (Network::ConnectionState::Connected != relayChannel_->GetStatus())
      {
        LOG_W(0).Trace("%s Channel closed(t=%s c=%d)", 
          logTag_, relayChannel_->GetAddress().target.c_str(), relayChannel_->GetInternalClientId());

        startRepairTimeout(Result::CONNECTION_2_RELAY_FAILED);
      }
    }
    break;

    case InternalState::REPAIR:
    case InternalState::RETRY:
    {
      NI_ASSERT(repairTimeoutStart_ != 0, "");

      NHPTimer::FTime currentTime = NHPTimer::GetScalarTime();
      if (currentTime - repairTimeoutStart_ > repairTimeout_)
      {
        LOG_M(0).Trace("%s Start secondary connection repair/retry(loginaddr=%s login=%s sessionKey=%s)", 
          logTag_, loginAddr_.c_str(), login_.c_str(), sessionKey_.c_str());

        repairTimeoutStart_ = 0;

        open_();
      }
    }
    break;

    case InternalState::CLOSE:
    {
      close();
    }
    break;

    default:
      break;
    }
  }

  int SecondaryRelayCtx::open_()
  {
    LOG_M(0).Trace("%s open_(loginaddr=%s login=%s sessionKey=%s)", 
      logTag_, loginAddr_.c_str(), login_.c_str(), sessionKey_.c_str());

    int rc = 0;
    state(State::OPENING);

    loginClient_ = new Login::LoginClient(netDriver_, version_);
    loginClient_->LoginRequest(loginAddr_, login_, password_, 0, sessionKey_, Login::LoginType::PARTIAL_RECONNECT);
    internalState(InternalState::LOGIN);

    return rc;
  }

  void SecondaryRelayCtx::startRepairTimeout(Result::Enum _reason)
  {
    LOG_M(0).Trace("%s Start repair timeout(loginaddr=%s login=%s sessionKey=%s retries=%d)", 
      logTag_, loginAddr_.c_str(), login_.c_str(), sessionKey_.c_str(), retries_);

    internalState(InternalState::REPAIR);
    repairTimeoutStart_ = NHPTimer::GetScalarTime();
    retriesCount_ = retries_;
  }

  void SecondaryRelayCtx::startRetryTimeout(Result::Enum _reason)
  {
    LOG_M(0).Trace("%s Start retry timeout(loginaddr=%s login=%s sessionKey=%s retriesCount=%d)", 
      logTag_, loginAddr_.c_str(), login_.c_str(), sessionKey_.c_str(), retriesCount_);

    if (retriesCount_)
    {
      --retriesCount_;
      internalState(InternalState::RETRY);
      repairTimeoutStart_ = NHPTimer::GetScalarTime();
    }
    else
    {
      LOG_M(0).Trace("%s all retries are exhaust(loginaddr=%s login=%s sessionKey=%s retriesCount=%d)", 
        logTag_, loginAddr_.c_str(), login_.c_str(), sessionKey_.c_str(), retriesCount_);

      internalState(InternalState::CLOSE);
    }
  }
}
