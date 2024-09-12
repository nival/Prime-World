#include "transport/stdafx.h"
#include <Network/TransportMessages.h>
#include "transport/TLChannel.h"
#include <naio/Types.h>
#include "transport/TLConnection.h"
#include "Network/Transport.h"
#include "naio/ConnectionContext.h"
#include <System/ChunklessSaver.h>
#include <ace/OS_NS_sys_time.h>
#include "transport/TLTransportProtocol.h"

namespace TransportLayer
{
  Channel::Channel(bool _active, Transport::Address const & _taddr, Transport::TLoginData const & _logindata,
    Transport::MessageFactory* _mf)
    :ChannelBase(Transport::EChannelType::Unicast, _active, _taddr, _logindata, _mf)
  {
  }

  Channel::~Channel()
  {
    NI_PROFILE_BLOCK(__FUNCTION__);

    ACE_ERROR((LM_INFO, ACE_TEXT("%s(p=%d c=%d s=%d)"), 
      __FUNCTION__, chaddr().pipe, chaddr().client, chaddr().sender));

    close(false);
  }

  void Channel::Close()
  {
    NI_PROFILE_BLOCK(__FUNCTION__);
    close(true);
  }

  const Transport::Address& 
    Channel::GetAddress() const
  {
    return taddr();
  }

  Transport::TClientId 
  Channel::GetInternalClientId() const
  {
    return taddr().client;
  }

  bool Channel::IsIncomingConnection() const
  {
    return !active();
  }

  void Channel::SendMsg( Transport::MessageBase* pMsg )
  {
    sendMsg(pMsg);
  }

  Transport::MessageBase* Channel::ReceiveMsg()
  {
    NI_PROFILE_BLOCK(__FUNCTION__);

    Transport::MessageBase* msg = 0;

    TL::ConnectionSP spconn = wpconn_;
    if (TL::IsValid(spconn))
    {
      ACE_Message_Block* mb = dequeueRecv();
      if (mb)
      {
        NI_PROFILE_BLOCK("unpack message");
        msg = unpackMessage(mb);
        freeMsgBlock_(mb);
      }
    }

    return msg;
  }

  Transport::MessageBase* Channel::PeekMsg()
  {
    NI_ALWAYS_ASSERT("This function is obsolete and shouldn't be used");
    return 0;
  }

  void Channel::SendRaw( const byte* data, int size )
  {
    NI_PROFILE_BLOCK(__FUNCTION__);

    ACE_DEBUG((LM_TRACE, ACE_TEXT("%s(l=%d data_addr=%d)"), __FUNCTION__, size, data));

    EChannelStatus::Enum sts = status();
    if (sts < 0)
    {
      ACE_DEBUG((LM_DEBUG, ACE_TEXT("[TL] %s. Channel is already closed (t=%s p=%d c=%d)"),
        __FUNCTION__, taddr().target.c_str(), chaddr().pipe, chaddr().client));
      return;
    }

    TL::ConnectionSP spconn = wpconn_;
    if (TL::IsValid(spconn))
    {
      ACE_Message_Block* mb = allocMsgBlock_(size, (const char*)data, MBType::WRITE_BLOCK);
      if (mb)
        send_(spconn, mb);
      else
        ACE_ERROR((LM_CRITICAL, ACE_TEXT("%s. Can't allocate memory(sz=%d t=%s p=%d c=%d)"),
        __FUNCTION__, size, taddr().target.c_str(), chaddr().pipe, chaddr().client));
    }
    else
    {
      EChannelStatus::Enum sts = status();
      NI_ASSERT(sts < 0, NI_STRFMT("Channel status '%s'(%d), but connection already invalid", EChannelStatus::ToString(sts), (int)sts));

      ACE_DEBUG((LM_DEBUG, ACE_TEXT("%s. Connection is invalid(t=%s p=%d c=%d)"),
        __FUNCTION__, taddr().target.c_str(), chaddr().pipe, chaddr().client));
    }
  }

  bool Channel::ReceiveRaw( vector<byte>* data )
  {
    NI_PROFILE_BLOCK(__FUNCTION__);

    Transport::MessageMiscInfo miscInfo;
    return ReceiveRaw(data, miscInfo);
  }

  bool Channel::ReceiveRaw( vector<byte>* data, Transport::MessageMiscInfo & _miscInfo )
  {
    NI_PROFILE_BLOCK(__FUNCTION__);

    ACE_Message_Block* mb = dequeueRecv(_miscInfo.queueAbsTime);
    _miscInfo.recvAbsTime = timer::Now();

    if (!mb)
      return false;

    ACE_DEBUG((LM_TRACE, ACE_TEXT("%s(l=%d data_addr=%d)"), __FUNCTION__, mb->length(), mb->rd_ptr()));

    data->resize(mb->length());
    NI_ASSERT(mb->base() == mb->rd_ptr(), "base() have to be equal rd_ptr()");
    memcpy(data->begin(), mb->rd_ptr(), mb->length());

    freeMsgBlock_(mb);

    return true;
  }

  bool Channel::PeekRaw( vector<byte>* data )
  {
    NI_ALWAYS_ASSERT( "This function is obsolete and shoundn't be used");
    return false;
  }

  Transport::Ping Channel::GetPingTime() const
  {
    return Transport::Ping(ping(), pingSeqNumRecv());
  }

  //////////////////////////////////////////////////////////////////////////
  //
  //  Internal interface
  //

  void Channel::KeepAlivePeriod(unsigned int sec)
  {
    keepalivePeriod(ACE_Time_Value(sec));
  }


  void Channel::setStatus_(EChannelStatus::Enum _sts)
  {
    EChannelStatus::Enum oldsts = ChannelBase::_SetStatus(_sts);

    ACE_DEBUG((LM_DEBUG, ACE_TEXT("%s. %s->%s(c=%d p=%d s=%d)"), 
      __FUNCTION__, EChannelStatus::ToString(oldsts), EChannelStatus::ToString(_sts),
      chaddr().client, chaddr().pipe, chaddr().sender));
  }
}
