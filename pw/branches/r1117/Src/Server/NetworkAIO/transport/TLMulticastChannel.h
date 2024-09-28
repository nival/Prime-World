#pragma once
#include "Network/TransportMulticastChannel.h"
#include "transport/TLChannelBase.h"
#include <set>

namespace TransportLayer
{
  namespace TL = TransportLayer;

  class ChannelFactory;

  struct RecipientContext
  {
    RecipientContext()
      :client_(Transport::autoAssignClientId)
    {}

    RecipientContext(Transport::TClientId const & _client)
      :client_(_client)
    {}

    Transport::TClientId client_;

    bool operator < (RecipientContext const & _other) const
    {
      return (client_ < _other.client_);
    }
  };

  class MulticastChannel : public Transport::IMulticastChannel, public ChannelBase, public BaseObjectMT
  {
    NI_DECLARE_REFCOUNT_CLASS_3( MulticastChannel, Transport::IMulticastChannel, ChannelBase, BaseObjectMT )

    friend class TL::ChannelFactory;

    typedef std::set<RecipientContext> RecipientsT;

  public:
    MulticastChannel(bool _active, Transport::Address const & _taddr, Transport::MessageFactory* _mf);
    ~MulticastChannel();

  public:
    virtual Network::ConnectionState::Enum GetStatus() const;
    virtual Transport::EError::Enum Close();

    virtual Transport::Address const & GetAddress() const;
    virtual Transport::EError::Enum SendRaw(byte const * _data, int _size);

    virtual Transport::EError::Enum AddRecipient(Transport::TClientId const & _recipient);
    virtual Transport::EError::Enum RemoveRecipient(Transport::TClientId const & _recipient);
    virtual bool FindRecipient(Transport::TClientId const & _recipient);
    virtual unsigned int Recipients() const;

    virtual Transport::TClientId GetFirstRecipient(int & _bypass);
    virtual Transport::TClientId GetNextRecipient(int _bypass);

  protected:
    virtual int OnAddRecipientResponse(Transport::TClientId const & _recipient, Transport::AddRecipientResult::Enum _res);
    virtual int OnRemoveRecipient(Transport::TClientId const & _recipient);

  private:
    RecipientsT recipientsInProgress_;
    RecipientsT recipients_;
    mutable ACE_Thread_Mutex recipientsMutex_;
  };
}
