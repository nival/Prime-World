#include "transport/stdafx.h"
#include "transport/TLMulticastChannel.h"
#include "transport/TLAddRecipientOp.h"
#include "transport/TLRemoveRecipientOp.h"
#include "transport/TLConnection.h"

using namespace Transport;

namespace TransportLayer
{
  MulticastChannel::MulticastChannel(bool _active, Transport::Address const & _taddr, Transport::MessageFactory* _mf)
    :ChannelBase(Transport::EChannelType::Multicast, _active, _taddr, "", _mf)
  {
  }


  MulticastChannel::~MulticastChannel()
  {
  }

  Network::ConnectionState::Enum MulticastChannel::GetStatus() const
  {
    NI_PROFILE_FUNCTION;

    switch (status())
    {
    case EChannelStatus::INIT:
      return Network::ConnectionState::Initialized;
    case EChannelStatus::CLOSING:
    case EChannelStatus::CLOSED:
      return Network::ConnectionState::Closed;
    case EChannelStatus::CONNECTING:
      return Network::ConnectionState::Connecting;
    case EChannelStatus::CONNECTED:
      return Network::ConnectionState::Connected;
    default:
      return Network::ConnectionState::Invalid;
    }
  }

  EError::Enum MulticastChannel::Close()
  {
    if (ChannelBase::status() < 0)
      return EError::ALREADY_CLOSED;

    ChannelBase::close(true);
    return EError::OK;
  }

  Transport::Address const & MulticastChannel::GetAddress() const
  {
    return taddr();
  }

  EError::Enum MulticastChannel::SendRaw(byte const * _data, int _size)
  {
    NI_PROFILE_FUNCTION;

    ACE_DEBUG((LM_TRACE, ACE_TEXT("%s(l=%d data_addr=%d)"), __FUNCTION__, _size, _data));

    EChannelStatus::Enum sts = status();
    if (sts < 0)
    {
      ACE_DEBUG((LM_DEBUG, ACE_TEXT("%s. Channel is already closed (t=%s p=%d c=%d)"),
        __FUNCTION__, taddr().target.c_str(), chaddr().pipe, chaddr().client));
      return EError::ALREADY_CLOSED;
    }

    EError::Enum rc = EError::FAIL;
    TL::ConnectionSP spconn = wpconn_;
    if (TL::IsValid(spconn))
    {
      ACE_Message_Block* mb = allocMsgBlock_(_size, (const char*)_data, MBType::WRITE_BLOCK);
      if (mb)
      {
        if (send_(spconn, mb) >= 0)
          rc = EError::OK;
      }
      else
        ACE_ERROR((LM_CRITICAL, ACE_TEXT("%s. Can't allocate memory(sz=%d t=%s p=%d c=%d)"),
        __FUNCTION__, _size, taddr().target.c_str(), chaddr().pipe, chaddr().client));
    }
    else
    {
      EChannelStatus::Enum sts = status();
      NI_ASSERT(sts < 0, NI_STRFMT("Channel status '%s'(%d), but connection already invalid", EChannelStatus::ToString(sts), (int)sts));

      ACE_DEBUG((LM_DEBUG, ACE_TEXT("%s. Connection is invalid(t=%s p=%d c=%d)"),
        __FUNCTION__, taddr().target.c_str(), chaddr().pipe, chaddr().client));
    }

    return rc;
  }

  EError::Enum MulticastChannel::AddRecipient(Transport::TClientId const & _recipient)
  {
    NI_PROFILE_FUNCTION;

    ACE_Guard<ACE_Thread_Mutex> lock(recipientsMutex_);

    RecipientsT::const_iterator cit = recipients_.find(_recipient);
    if (cit != recipients_.end())
    {
      ACE_ERROR((LM_WARNING, ACE_TEXT("%s. Recipient already exists(recipient=%d t=%s p=%d)"), 
        __FUNCTION__, _recipient, taddr().target.c_str(), chaddr().pipe));
      return EError::ALREADY_EXISTS;
    }

    std::pair<RecipientsT::iterator, bool> res = recipientsInProgress_.insert(_recipient);
    if (!res.second)
    {
      ACE_ERROR((LM_WARNING, ACE_TEXT("%s. Recipient already in progress(recipient=%d t=%s p=%d)"), 
        __FUNCTION__, _recipient, taddr().target.c_str(), chaddr().pipe));
      return EError::ALREADY_IN_PROGRESS;
    }

    int rc = -1;
    TL::ConnectionSP spconn = wpconn_;
    if (TL::IsValid(spconn))
    {
      op::AddRecipientPtr arop(new op::AddRecipient(spconn->connectionContext(), this, _recipient));
      rc = startOutOp_(spconn, arop);
      if (rc < 0)
      {
        ACE_ERROR((LM_WARNING, ACE_TEXT("%s. Can't start add recipient operation (p=%d c=%d s=%d)"), 
          __FUNCTION__, chaddr().pipe, chaddr().client, chaddr().sender));
      }
    }
    else
    {
      ACE_ERROR((LM_WARNING, ACE_TEXT("%s. Connection is NULL or closed(t=%s p=%d c=%d)"), 
        __FUNCTION__, taddr().target.c_str(), chaddr().pipe, chaddr().client));
    }

    if (rc < 0)
    {
      recipientsInProgress_.erase(_recipient);
      return EError::FAIL;
    }

    return EError::OK;
  }

  EError::Enum MulticastChannel::RemoveRecipient(Transport::TClientId const & _recipient)
  {
    NI_PROFILE_FUNCTION;

    ACE_Guard<ACE_Thread_Mutex> lock(recipientsMutex_);

    RecipientsT::iterator it = recipients_.find(_recipient);
    if (it == recipients_.end())
    {
      ACE_ERROR((LM_WARNING, ACE_TEXT("%s. There is no such recipient(recipient=%d t=%s p=%d)"), 
        __FUNCTION__, _recipient, taddr().target.c_str(), chaddr().pipe));
      return EError::NOT_FOUND;
    }

    recipients_.erase(it);

    int rc = -1;
    TL::ConnectionSP spconn = wpconn_;
    if (TL::IsValid(spconn))
    {
      op::RemoveRecipientPtr arop(new op::RemoveRecipient(spconn->connectionContext(), this, _recipient));
      rc = startOutOp_(spconn, arop);
      if (rc < 0)
      {
        ACE_ERROR((LM_WARNING, ACE_TEXT("%s. Can't start remove recipient operation (recipient=%d p=%d c=%d s=%d)"), 
          __FUNCTION__, _recipient, chaddr().pipe, chaddr().client, chaddr().sender));
      }
      else
      {
        ACE_ERROR((LM_INFO, ACE_TEXT("%s. Removing recipient is started (recipient=%d p=%d c=%d s=%d)"), 
          __FUNCTION__, _recipient, chaddr().pipe, chaddr().client, chaddr().sender));
      }
    }
    else
    {
      ACE_ERROR((LM_WARNING, ACE_TEXT("%s. Connection is NULL or closed(recipient=%d t=%s p=%d c=%d)"), 
        __FUNCTION__, _recipient, taddr().target.c_str(), chaddr().pipe, chaddr().client));
    }

    return EError::FAIL;
  }

  bool MulticastChannel::FindRecipient(Transport::TClientId const & _recipient)
  {
    NI_PROFILE_FUNCTION;

    ACE_Guard<ACE_Thread_Mutex> lock(recipientsMutex_);
    RecipientsT::const_iterator cit = recipients_.find(_recipient);
    return (cit != recipients_.end());
  }

  unsigned int MulticastChannel::Recipients() const
  {
    NI_PROFILE_FUNCTION;

    ACE_Guard<ACE_Thread_Mutex> lock(recipientsMutex_);
    return recipients_.size();
  }

  Transport::TClientId MulticastChannel::GetFirstRecipient(int & _bypass)
  {
    _bypass = -1;
    return Transport::autoAssignClientId;
  }

  Transport::TClientId MulticastChannel::GetNextRecipient(int _bypass)
  {
    return Transport::autoAssignClientId;
  }

  int MulticastChannel::OnAddRecipientResponse(Transport::TClientId const & _recipient, Transport::AddRecipientResult::Enum _res)
  {
    NI_PROFILE_FUNCTION;

    ACE_Guard<ACE_Thread_Mutex> lock(recipientsMutex_);

    int rc = -1;
    RecipientsT::iterator it = recipientsInProgress_.find(_recipient);
    if (it != recipientsInProgress_.end())
    {
      if (AddRecipientResult::OK == _res)
      {
        std::pair<RecipientsT::iterator, bool> res = recipients_.insert(_recipient);
        if (res.second)
        {
          rc = 0;
          ACE_ERROR((LM_INFO, ACE_TEXT("%s. Recipient successfully added(recipient=%d t=%s p=%d)"), 
            __FUNCTION__, _recipient, taddr().target.c_str(), chaddr().pipe));
        }
        else
        {
          ACE_ERROR((LM_ERROR, ACE_TEXT("%s. Recipient already exists(recipient=%d t=%s p=%d)"), 
            __FUNCTION__, _recipient, taddr().target.c_str(), chaddr().pipe));
        }
      }
      else
      {
        ACE_ERROR((LM_WARNING, ACE_TEXT("%s. Recipient adding is FAILED(recipient=%d t=%s p=%d)"), 
          __FUNCTION__, _recipient, taddr().target.c_str(), chaddr().pipe));
        rc = 0;
      }

      recipientsInProgress_.erase(it);
    }
    else
    {
      ACE_ERROR((LM_WARNING, ACE_TEXT("%s. There is not such recipient in list for recipient's adding(recipient=%d t=%s p=%d)"), 
        __FUNCTION__, _recipient, taddr().target.c_str(), chaddr().pipe));
    }

    return rc;
  }

  int MulticastChannel::OnRemoveRecipient(Transport::TClientId const & _recipient)
  {
    NI_PROFILE_FUNCTION;

    ACE_Guard<ACE_Thread_Mutex> lock(recipientsMutex_);

    int rc = -1;
    RecipientsT::iterator it = recipients_.find(_recipient);
    if (it != recipients_.end())
    {
      ACE_ERROR((LM_INFO, ACE_TEXT("%s. Remove recipient(recipient=%d t=%s p=%d)"), 
        __FUNCTION__, _recipient, taddr().target.c_str(), chaddr().pipe));

      recipients_.erase(it);
      rc = 0;
    }
    else
    {
      ACE_ERROR((LM_WARNING, ACE_TEXT("%s. Recipient is not found(recipient=%d t=%s p=%d)"), 
        __FUNCTION__, _recipient, taddr().target.c_str(), chaddr().pipe));
    }

    return rc;
  }

}
