#pragma once

#include "MulticastClientContext.h"
#include "MulticastSessionIface.h"

namespace MulticastTest
{
  class RIMulticastClient;

  class MulticastSession : public IMulticastSession, public BaseObjectMT
  {
    NI_DECLARE_REFCOUNT_CLASS_2( MulticastSession, IMulticastSession, BaseObjectMT );

    typedef map<Transport::TClientId, StrongMT<ClientContext>>  ClientContextsT;
    typedef map<Transport::TServiceId, StrongMT<Transport::IMulticastChannel>>  MulticastChannelsT;

  public:
    MulticastSession(StrongMT<Transport::ITransportSystem> const & _ts, unsigned int _userlimit, NHPTimer::FTime _stepFrequency = 0.1);
    ~MulticastSession();

  public:
    int RegisterClient(const char* name, uint clientId, StrongMT<IMulticastClient> const & _client);

    //  IMulticastSession
    void ConfirmStep(Transport::TClientId _cid, unsigned int _step);

    void Step();

    bool full() const;

  private:
    void sendRawStep(int _step, byte* _data, unsigned int _size);
    void removeRecipients();
    void closeMulticastChannels();

  private:
    StrongMT<Transport::ITransportSystem> ts_;
    ClientContextsT clients_;
    unsigned int step_;
    unsigned int userlimit_;

    NHPTimer::FTime lastStepTime_;
    NHPTimer::FTime stepFrequency_;

    MulticastChannelsT  channels_;
  };

  inline
  bool MulticastSession::full() const
  {
    return (clients_.size() == (int)userlimit_);
  }
}
