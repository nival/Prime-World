#pragma once
#include <Network/TransportTypes.h>
#include "UserEnvInfo.h"
#include "UserManagerSvc/RUserManagerIface.auto.h"
#include "RelayBalancer/RelayBalancerIface.h"
#include "UserManagerSvc/IUserRegister.h"
#include "UserManagerSvc/IPrepareUserEnvNotify.h"
#include "UserManagerSvc/PartialReconnectSettings.h"

namespace UserManager
{
  class PrepareUserEnvCtx : public Relay::IBalancerCallback, public BaseObjectMT
  {
    NI_DECLARE_REFCOUNT_CLASS_2( PrepareUserEnvCtx, Relay::IBalancerCallback, BaseObjectMT );

    struct State
    {
      enum Enum
      {
        CLOSED = -1,
        INIT = 0,
        RELAY_ALLOCATION_IN_PROGRESS,
        RELAY_ALLOCATION_RETURN,
        RELAY_ALLOCATION_FINISHED,
      };
    };

  public:
    PrepareUserEnvCtx();
    PrepareUserEnvCtx(UserEnvInfo const & _uei, RIPrepareUserEnvCallback * _cb, IUserRegister * _ur, IPrepareUserEnvNotify * _notify, PartialReconnectSettings const & _prs);
    ~PrepareUserEnvCtx();

  public:
    Cluster::TUserId const & userid() const;
    string const & sessionKey() const;
    Transport::TServiceId const & sessionPath() const;
    wstring const & username() const;
    Cluster::TGameId const & gameid() const;

    void timemark(NHPTimer::FTime const & _timemark);
    NHPTimer::FTime const & timemark() const;

    bool isclosed() const;

  public:
    //  Relay::IBalancerCallback
    void OnRelayAllocateReturn(int _rc, Cluster::TUserId _userid, rpc::CallStatus _status);
    void OnRelayAllocated(Transport::TClientId _clienid, int _userctx, 
      Transport::TServiceId const & _relay, Network::NetAddress const & _relayaddr,
      Transport::TServiceId const & _secondaryrelay, Network::NetAddress const & _secondaryaddr);

  public:
    int Complete(Result::Enum err);

  private:
    State::Enum state_() const;
    void state_(State::Enum _st);
    bool isclosed_() const;

    void complete_(int _result, Cluster::TUserId _userid, Transport::TServiceId const & _relay = "", Network::NetAddress const & _relayaddr = "",
      Transport::TServiceId const & _secondaryrelay = "", Network::NetAddress const & _secondaryaddr = "",
      bool _partialReconnectSupported = false, unsigned int _partialReconnectRetries = 0, unsigned int _partialReconnectRetryTimeout = 0);

  private:
    UserEnvInfo uei_;
    StrongMT<RIPrepareUserEnvCallback> cb_;
    State::Enum st_;

    Transport::TServiceId relay_;
    Network::NetAddress   relayAddr_;
    Transport::TServiceId secondaryrelay_;
    Network::NetAddress   secondaryrelayAddr_;
    long relayConfirmationCount_;
    StrongMT<IUserRegister> userRegister_;
    StrongMT<IPrepareUserEnvNotify> notify_;
    NHPTimer::FTime timemark_;

    PartialReconnectSettings prs_;
  };

  inline
  Cluster::TUserId const & PrepareUserEnvCtx::userid() const
  {
    return uei_.userid_;
  }

  inline
  string const & PrepareUserEnvCtx::sessionKey() const
  {
    return uei_.sessionKey_;
  }

  inline
  Transport::TServiceId const & PrepareUserEnvCtx::sessionPath() const
  {
    return uei_.sessionPath_;
  }

  inline
  wstring const & PrepareUserEnvCtx::username() const
  {
    return uei_.username_;
  }

  inline
  Cluster::TGameId const & PrepareUserEnvCtx::gameid() const
  {
    return uei_.gameid_;
  }

  inline
  PrepareUserEnvCtx::State::Enum PrepareUserEnvCtx::state_() const
  {
    return st_;
  }

  inline
  void PrepareUserEnvCtx::state_(PrepareUserEnvCtx::State::Enum _st)
  {
    st_ = _st;
  }

  inline
  bool PrepareUserEnvCtx::isclosed_() const
  {
    return (state_() == State::CLOSED);
  }

  inline
  void PrepareUserEnvCtx::timemark(NHPTimer::FTime const & _timemark)
  {
    timemark_ = _timemark;
  }

  inline
  NHPTimer::FTime const & PrepareUserEnvCtx::timemark() const
  {
    return timemark_;
  }

  inline
  bool PrepareUserEnvCtx::isclosed() const
  {
    return isclosed_();
  }
}
