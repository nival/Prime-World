#pragma once
#include <Network/TransportTypes.h>
#include <RPC/IfaceRequester.h>
#include "RelayBalancer/RelayAllocationContext.h"
#include <Network/Address.h>
#include <Coordinator/ServiceRole.h>
#include "RelayBalancer/RRelayBalancerClientNotifyIface.auto.h"
#include "RelayBalancer/RelayBalancerUserContext.h"
#include "RelayBalancer/IRelayCCUCounter.h"

namespace Relay
{
  class ISvcContextNotify;

  class SvcContext : public IOutgoingClientNotifySink,
                     public ICCUCounter,
                     public rpc::IfaceRequesterCallback<Relay::RIIncomingClientNotifySink>,
                     public BaseObjectMT
  {
    NI_DECLARE_REFCOUNT_CLASS_4( SvcContext, IOutgoingClientNotifySink, ICCUCounter, rpc::IfaceRequesterCallback<Relay::RIIncomingClientNotifySink>, BaseObjectMT );

    typedef nstl::map<uint, StrongMT<UserContext> > UserContextsT;

  public:
    struct State
    {
      enum Enum
      {
        INIT,
        OPENING,
        OPENED,
        REOPENING,
        CLOSED
      };
    };

  public:
    SvcContext(Transport::TServiceId const & _svcid, Coordinator::TServiceRole const & role,  ISvcContextNotify * cb);

    int open(rpc::GateKeeper * _gk, Transport::IAddressTranslator* _addrResolver, NLogg::CChannelLogger * _logstrm, char const * _chnlName);
    void close();
    int reopen();

    void step();

    int externalCCUCounter(StrongMT<ICCUCounter> const & counter);

  public:

    Transport::TServiceId const & svcpath() const { return svcpath_; }
    Transport::TServiceId const & svcid() const { return svcid_; }
    Transport::TServiceId const & localsvcid() const { return localsvcid_; }
    Transport::TServiceId const & frontendsvcid() const { return frontendsvcid_; }
    Transport::TServiceId const & localFrontendsvcid() const { return localFrontendsvcid_; }
    Network::NetAddress const & frontendAddr() const { return frontendAddr_; }
    Coordinator::TServiceRole const & svcrole() const { return svcrole_; }
    Network::NetAddress const & netaddr() const { return netaddr_; }

    bool isopen() const { return isstate_(State::OPENED); }
    bool isclosed() const { return isstate_(State::CLOSED); }

    StrongMT<Relay::RIIncomingClientNotifySink> relayNotifySink() const;

    int addUserCtx(StrongMT<UserContext> const & uctx);
    int removeUserCtx(Transport::TClientId const & userid);

    unsigned int usersConnectTimeoutExpiredCount() const { return usersConnectTimeoutExpiredCount_; }
    void resetUsersConnectTimeoutExpiredCount() { usersConnectTimeoutExpiredCount_ = 0; }

    void incRelayAllocationFailedCount() { ++relayAllocationFailedCount_; }
    void resetRelayAllocationFailedCount() { relayAllocationFailedCount_ = 0; }
    unsigned int relayAllocationFailedCount() const { return relayAllocationFailedCount_; }

    NHPTimer::FTime offlineTimeStart() const { return offlineTimeStart_; }
    void resetOfflineTimeStart() { offlineTimeStart_ = 0.0; }
    void initOfflineTimeStart() { offlineTimeStart_ = NHPTimer::GetScalarTime(); }

  protected:
    //  IIncomingClientNotifySink
    void OnReturn_RegisterOutgoingClientNotifySink(int _rc);

    //  IOutgoingClientNotifySink
    void OutgoingClientNotify(Transport::TClientId _clientid, int _reason);
    void ClientConnectedNotify(Transport::TClientId _clientid);

    //  public rpc::IfaceRequesterCallback<Relay::RIIncomingClientNotifySink>
    void onChangeState(rpc::IfaceRequesterState::Enum ifacest, StrongMT<rpc::IfaceRequester<Relay::RIIncomingClientNotifySink> > const & ifacereq);

  private:
    void DetachUserFromSvc_(StrongMT<UserContext> const & uctx);
    int DetachUserFromSvc_(uint _userid);

    State::Enum state_() const { return st; }
    void state_(State::Enum _st);
    bool isstate_(State::Enum const & _st) const { return (_st == st); }

  private:
    Transport::TServiceId svcpath_;
    Transport::TServiceId svcid_;
    Coordinator::TServiceRole svcrole_;
    Network::NetAddress netaddr_;
    Transport::TServiceId localsvcid_;
    Transport::TServiceId frontendsvcid_;
    Transport::TServiceId localFrontendsvcid_;
    Network::NetAddress frontendAddr_;
    uint ccuLimit;
    State::Enum st;
    StrongMT<rpc::IfaceRequester<Relay::RIIncomingClientNotifySink> > relayNotifier;
    StrongMT<Transport::IAddressTranslator> addrResolver; 
    UserContextsT users_;
    StrongMT<ISvcContextNotify> notifyCallback_;
    StrongMT<ICCUCounter> extCounter_;
    unsigned int usersConnectTimeoutExpiredCount_;
    unsigned int relayAllocationFailedCount_;
    NHPTimer::FTime offlineTimeStart_;
  };
}
