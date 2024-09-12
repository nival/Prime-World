#include "transport/stdafx.h"
#include "transport/TLChannel.h"
#include "transport/TLChannelWrapper.h"

namespace TransportLayer
{
  ChannelWrapper::ChannelWrapper()
  {
  }

  ChannelWrapper::ChannelWrapper(TL::IChannelInternalSP const & spchnl)
    :sp_((TL::Channel*)spchnl.Get())
  {
  }

  ChannelWrapper::~ChannelWrapper()
  {
    ResetPtr(sp_);
  }

  Network::ConnectionState::Enum ChannelWrapper::GetStatus() const
  {
    NI_PROFILE_BLOCK(__FUNCTION__);

    switch (sp_->status())
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

  void ChannelWrapper::Close()
  {
    NI_PROFILE_BLOCK(__FUNCTION__);
    sp_->Close();
  }

  const Transport::Address& 
    ChannelWrapper::GetAddress() const
  {
    NI_PROFILE_BLOCK(__FUNCTION__);
    return sp_->taddr();
  }

  const Transport::TLoginData& 
    ChannelWrapper::GetLoginData() const
  {
    NI_PROFILE_BLOCK(__FUNCTION__);
    return sp_->openChannelKey();
  }

  Transport::TClientId 
    ChannelWrapper::GetInternalClientId() const
  {
    NI_PROFILE_BLOCK(__FUNCTION__);
    return sp_->GetInternalClientId();
  }

  bool ChannelWrapper::IsIncomingConnection() const
  {
    NI_PROFILE_BLOCK(__FUNCTION__);
    return sp_->IsIncomingConnection();
  }

  void ChannelWrapper::SendMsg( Transport::MessageBase* pMsg )
  {
    NI_PROFILE_BLOCK(__FUNCTION__);
    sp_->SendMsg(pMsg);
  }

  Transport::MessageBase* ChannelWrapper::ReceiveMsg()
  {
    NI_PROFILE_BLOCK(__FUNCTION__);
    return sp_->ReceiveMsg();
  }

  Transport::MessageBase* ChannelWrapper::PeekMsg()
  {
    NI_ALWAYS_ASSERT("This function is obsolete and shoundn't be used");
    return 0;
  }

  void ChannelWrapper::SendRaw( const byte* data, int size )
  {
    NI_PROFILE_BLOCK(__FUNCTION__);
    sp_->SendRaw(data, size);
  }

  bool ChannelWrapper::ReceiveRaw( vector<byte>* data )
  {
    NI_PROFILE_BLOCK(__FUNCTION__);
    return sp_->ReceiveRaw(data);
  }

  bool ChannelWrapper::ReceiveRaw( vector<byte>* data, Transport::MessageMiscInfo & _miscInfo )
  {
    NI_PROFILE_BLOCK(__FUNCTION__);
    return sp_->ReceiveRaw(data, _miscInfo);
  }

  bool ChannelWrapper::PeekRaw( vector<byte>* data )
  {
    NI_ALWAYS_ASSERT( "This function is obsolete and shoundn't be used");
    return false;
  }

  Transport::Ping ChannelWrapper::GetPingTime() const
  {
    ping_ = sp_->GetPingTime();
    return ping_;
  }

  void ChannelWrapper::KeepAlivePeriod(unsigned int sec)
  {
    NI_PROFILE_BLOCK(__FUNCTION__);
    sp_->KeepAlivePeriod(sec);
  }
}

