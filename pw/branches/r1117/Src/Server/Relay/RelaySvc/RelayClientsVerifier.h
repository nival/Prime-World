#pragma once
#include <Network/TransportClientsVerifier.h>
#include "System/Thread.h"
#include "System/HPTimer.h"
#include "RelayBalancer/RelayBalancerClientNotifyIface.h"
#include "ServerAppBase/PerfCounters.h"

namespace rpc
{
  class GateKeeper;
}

namespace Relay
{
  typedef NHPTimer::FTime Timestamp;

  class RIOutgoingClientNotifySink;

  class ClientsVerifier : public Transport::IClientsVerifier, public IIncomingClientNotifySink, public BaseObjectMT
  {
    NI_DECLARE_REFCOUNT_CLASS_3( ClientsVerifier, Transport::IClientsVerifier, IIncomingClientNotifySink, BaseObjectMT );

  public:
    ClientsVerifier(const Transport::TServiceId& relayService, Timestamp timeout, rpc::GateKeeper* _gk, Transport::IPerfCounters * _perCounters );
    ~ClientsVerifier();

  public:
    //  IClientsVerifier
    virtual bool VerifyNewClientConnected( Transport::TClientId userId, const Transport::TLoginData& loginData );
    virtual void NotifyClientDisconnected( Transport::TClientId userId );
    virtual void Step();

    //  IIncomingClientNotifySink
    virtual int RegisterOutgoingClientNotifySink(IOutgoingClientNotifySink* cb);
    virtual bool IncomingClientNotify(Transport::TClientId clientid, string const & sessionkey);

    int ccu() const { return userCount_; }

  private:
    ClientsVerifier() {}
    void OutgoingClientNotify(Transport::TClientId const & _userid, OutgoingClientReason::Enum _reason);

    void inccu() { ++userCount_; }
    void deccu() { 
      NI_VERIFY( userCount_ > 0, "", return );
      --userCount_;
    }

  private:
    StrongMT<RIOutgoingClientNotifySink> outgoingClientsNotify;
    Transport::TServiceId relayService;
    Timestamp timeout;
    StrongMT<rpc::GateKeeper> gk;
    WeakMT<Transport::IPerfCounters> perCounters;

    typedef map<Transport::TClientId, Timestamp> TUserToTime;
    TUserToTime usersTimeoutTime;
    threading::Mutex usersTimeoutTimeLock;
    volatile int userCount_;
  };
}
