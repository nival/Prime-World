#pragma once
#include "LoginClient.h"
#include "Transport.h"

namespace Transport
{
  class SecondaryRelayCtx : public BaseObjectMT
  {
    NI_DECLARE_REFCOUNT_CLASS_1( SecondaryRelayCtx, BaseObjectMT );

  public:

    struct State
    {
      enum Enum
      {
        INIT,
        OPENING,
        OPEN,
        REOPENING,
        CLOSE
      };
    };

    struct Result
    {
      enum Enum
      {
        LOGIN_FAILED,
        CONNECTION_2_RELAY_FAILED,
        SUCCESS
      };
    };

  public:
    SecondaryRelayCtx(StrongMT<Network::INetworkDriver> const & _netDriver, Login::ClientVersion const & _version, 
      StrongMT<Transport::ITransportSystem> const & _transportSystem);
    ~SecondaryRelayCtx();

  public:
    int open(StrongMT<Transport::IChannel> const & _chnl, 
      Network::NetAddress const & _loginaddr, string const & _login, string const & _password, 
      string const & _sessionKey, unsigned int _partialReconnectRetries, unsigned int _partialReconnectRetryTimeout);
    void close();

    void step();

    State::Enum state() const { return state_; }
    Result::Enum result() const { return result_; }
    bool isclosed() const { return (State::CLOSE == state_); }

  private:

    struct InternalState
    {
      enum Enum
      {
        INIT,
        LOGIN,
        CONNECTING_2_RELAY,
        CONNECTED,
        REPAIR,
        RETRY,
        CLOSE
      };
    };

    void internalState(InternalState::Enum _is) { internalState_ = _is; }
    InternalState::Enum internalState() const { return internalState_; }

    void state(State::Enum _state) { state_ = _state; }
    void result(Result::Enum _result) { result_ = _result; }

    int open_();

    void startRepairTimeout(Result::Enum _reason);
    void startRetryTimeout(Result::Enum _reason);

  private:
    StrongMT<Network::INetworkDriver> netDriver_;
    Login::ClientVersion const & version_;
    StrongMT<Login::LoginClient> loginClient_;
    StrongMT<Transport::ITransportSystem> transport_;
    StrongMT<Transport::IChannel> relayChannel_;
    State::Enum state_;
    Result::Enum result_;
    InternalState::Enum internalState_;

    Transport::TClientId userId_;
    string sessionId_;

    Network::NetAddress loginAddr_;
    string login_;
    string password_;
    string sessionKey_;

    NHPTimer::FTime repairTimeoutStart_;
    NHPTimer::FTime repairTimeout_;
    unsigned int retries_;
    unsigned int retriesCount_;
    char* logTag_;
  };
}
