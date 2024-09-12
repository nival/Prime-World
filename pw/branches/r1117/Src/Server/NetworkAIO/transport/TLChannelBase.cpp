#include "transport/stdafx.h"
#include "transport/TLChannelBase.h"
#include "mballocator/MessageBlockFactory.h"
#include "transport/TLConnection.h"
#include <Network/Message.h>
#include "transport/TLSendDataOp.h"
#include "transport/TLCloseChannelOp.h"
#include "transport/TLPingChannelOp.h"
#include <Network/TransportUtils.h>
#include "transport/TLTransportProtocol.h"
#include <Network/TransportMessages.h>
#include <System/ChunklessSaver.h>
#include <System/AddressOf.h>

namespace TransportLayer
{

ChannelBase::ChannelBase(Transport::EChannelType::Enum _channeltype, bool _active, Transport::Address const & _taddr, Transport::TLoginData const & _logindata, Transport::MessageFactory* _mf) :
ChannelSuperBase(_channeltype, _active, _taddr),
  logindata_(_logindata),
  msgFactory_(_mf),
  outSeqNum_(0),
  lastSentSeqNum_(0),
  lastRecvSeqNum_(0),
  lastDequeueRecvSeqNum_(0),
  keepalivePeriod_(0),
  lastKeepaliveTime_(0),
  openTimeout_(10),
  pingSeqNumSent_(0),
  pingPeriod_(0),
  lastPingTime_(0)
{
}

ChannelBase::~ChannelBase()
{
}

void ChannelBase::messageBlockFactory_(TL::MessageBlockFactorySP const & _factory)
{
  msgBlkFactory_ = _factory;
}

ACE_Message_Block* ChannelBase::allocMsgBlock_(size_t len, MBType::Enum _type)
{
  NI_PROFILE_BLOCK(__FUNCTION__);
  return messageBlockFactory()->alloc_msg(len, _type);
}

ACE_Message_Block* ChannelBase::allocMsgBlock_(size_t len, char const * data, MBType::Enum _type)
{
  NI_PROFILE_BLOCK(__FUNCTION__);
  ACE_Message_Block* mb = allocMsgBlock_(len, _type);
  if (mb)
    mb->copy(data, len);
  return mb;
}

void ChannelBase::freeMsgBlock_(ACE_Message_Block* mb)
{
  NI_PROFILE_BLOCK(__FUNCTION__);
  messageBlockFactory()->free_msg(mb);
}


ACE_Message_Block* ChannelBase::packMessage(Transport::MessageBase* pmsg)
{
  NI_PROFILE_BLOCK(__FUNCTION__);

  unsigned int msgsz = Transport::GetMessageSize(pmsg);
  ACE_Message_Block* mb = allocMsgBlock_(msgsz, MBType::WRITE_BLOCK);
  if (!mb)
    return mb;

  FixedMemoryStream strm(mb->base(), mb->size());

  //  TODO: move code to transport utils
  //  pack message
  {
    NI_PROFILE_BLOCK("serialize msg");
    int msgType = pmsg->GetTypeId();
    strm.Write( (void*)&msgType, sizeof( int ) );
    ChunklessSaver saver( nival::getaddressof( strm ), 0, false );
    (*pmsg) & saver;
  }
  mb->wr_ptr(strm.GetPosition());

  return mb;
}

Transport::MessageBase* ChannelBase::unpackMessage(ACE_Message_Block* mb)
{
  Transport::MessageBase* msg = 0;

  FixedMemoryStream strm(mb->base(), mb->length());
  int msgtype = -1;
  if (Transport::ReadMessageType(nival::getaddressof( strm ), msgtype))
  {
    Transport::UnpackResult::Enum unpackrc = Transport::UnpackMessage(msgtype, msgFactory_, nival::getaddressof( strm ), TransportLayer::TransportProtocolHandler::MAX_MSG_DATA_SIZE, msg);
    if (unpackrc < 0)
    {
      ACE_ERROR((LM_ERROR, ACE_TEXT("[TL] %s. Can't unpack message(rc=%d msgtype=%d t=%s p=%d c=%d)"),
        __FUNCTION__, unpackrc, msgtype, taddr().target.c_str(), chaddr().pipe, chaddr().client));
    }
    else
    {
      ACE_DEBUG((LM_TRACE, ACE_TEXT("%s(msg=%d)"), __FUNCTION__, msg->GetTypeId()));
    }
  }
  else
  {
    ACE_ERROR((LM_ERROR, ACE_TEXT("[TL] %s. Can't read message type(t=%s p=%d c=%d)"),
      __FUNCTION__, taddr().target.c_str(), chaddr().pipe, chaddr().client));
  }

  return msg;
}

int ChannelBase::send_(TL::ConnectionSP const & spconn, ACE_Message_Block* mb)
{
  NI_PROFILE_BLOCK(__FUNCTION__);

  op::SendData* sndop = new op::SendData(spconn->connectionContext(), this, mb, 0/*++outSeqNum_*/);
  return startOutOp_(spconn, sndop);
}

unsigned int ChannelBase::outOpQueueSize() const
{
  NI_PROFILE_BLOCK(__FUNCTION__);

  ACE_Guard<ACE_Thread_Mutex> lock(outQueueMutex_);
  return outOpQueue_.count_;
}

void ChannelBase::enqueueOutOp_(op::ChannelOpPtr const & op)
{
  NI_PROFILE_BLOCK(__FUNCTION__);

  if (outOpQueue_.end_)
  {
    op::ChannelOpPtr prev = outOpQueue_.end_;
    op::ChannelOpPtr next = op;

    NI_ASSERT(prev->seqNum() + 1 == next->seqNum(), 
      NI_STRFMT("Wrong seq num during ENqueue(prevsn=%d nextsn=%d)", prev->seqNum(), next->seqNum()));

    outOpQueue_.end_->next(op);
    outOpQueue_.end_ = op;
  }
  else
  {
    outOpQueue_.head_ = outOpQueue_.end_ = op;
  }
  outOpQueue_.count_++;
}

op::ChannelOpPtr ChannelBase::dequeueOutOp_()
{
  NI_PROFILE_BLOCK(__FUNCTION__);

  op::ChannelOpPtr op;
  if (outOpQueue_.head_)
  {
    op = outOpQueue_.head_;
    outOpQueue_.head_ = 0;
    outOpQueue_.end_ = 0;
    outOpQueue_.count_ = 0;
  }
  return op;
}

void ChannelBase::clearOutOp_()
{
  NI_PROFILE_BLOCK(__FUNCTION__);

  ACE_Guard<ACE_Thread_Mutex> lock(outQueueMutex_);
  op::ChannelOpPtr op = dequeueOutOp_();
}

int ChannelBase::startOutOp_(TL::ConnectionSP const & spconn)
{
  NI_PROFILE_BLOCK(__FUNCTION__);

  ACE_Guard<ACE_Thread_Mutex> lock(outQueueMutex_);
  EChannelStatus::Enum sts = status();
  if (EChannelStatus::CONNECTED == sts || EChannelStatus::CLOSING == sts)
  {
    op::ChannelOpPtr outop = dequeueOutOp_();
    if (outop)
    {
      return spconn->startOutOp(outop);
    }
    else
    {
      ACE_DEBUG((LM_DEBUG, ACE_TEXT("%s. No data to send(c=%d p=%d s=%d)"), 
        __FUNCTION__, chaddr().client, chaddr().pipe, chaddr().sender));
    }
  }
  else
  {
    ACE_DEBUG((LM_DEBUG, ACE_TEXT("%s. Channel is NOT established yet.(c=%d p=%d s=%d)"), 
      __FUNCTION__, chaddr().client, chaddr().pipe, chaddr().sender));
  }

  return 0;
}

int ChannelBase::startOutOp_(TL::ConnectionSP const & spconn, op::ChannelOpPtr const & op)
{
  NI_PROFILE_BLOCK(__FUNCTION__);

  ACE_Guard<ACE_Thread_Mutex> lock(outQueueMutex_);

  NI_ASSERT(0 == op->next(), "op MUST BE single operation");
  op->seqNum(++outSeqNum_);
  enqueueOutOp_(op);

  EChannelStatus::Enum sts = status();
  if (EChannelStatus::CONNECTED == sts || EChannelStatus::CLOSING == sts)
  {
    op::ChannelOpPtr outop = dequeueOutOp_();
    if (op::CLOSE_CHANNEL == outop->type())
    {
      _SetStatus(EChannelStatus::CLOSED);
    }

    return spconn->startOutOp(outop);
  }

  return 0;
}

int ChannelBase::completeOp(op::ChannelOpPtr const & op)
{
  NI_PROFILE_BLOCK(__FUNCTION__);

  NI_ASSERT(lastSentSeqNum_.value() + 1 == op->seqNum(), 
    NI_STRFMT("Wrong seq number(lastsn=%d sn=%d)", lastSentSeqNum_.value(), op->seqNum()));
  lastSentSeqNum_ = op->seqNum();
  return 0;
}

int ChannelBase::enqueueRecv(size_t len, char const * data)
{
  NI_PROFILE_BLOCK(__FUNCTION__);

  NHPTimer::STime recvtime;
  NHPTimer::GetTime(recvtime);

  ACE_Guard<ACE_Thread_Mutex> lock(recvQueueMutex_);
  //unsigned long recvSeqNum;
  //if (len > sizeof(recvSeqNum))
  //{
  //  memcpy(&recvSeqNum, &data[0], sizeof(recvSeqNum));
  //  NI_ASSERT(recvSeqNum > lastRecvSeqNum_, "WRONG RECV SEQUENCE");
  //  lastRecvSeqNum_ = recvSeqNum;
  //}

  ACE_Message_Block* mb = allocMsgBlock_(len, data, MBType::READ_BLOCK);
  if (!mb)
  {
    ACE_ERROR((LM_CRITICAL, ACE_TEXT("%s. Can't allocate memory(sz=%d t=%s p=%d c=%d)"),
      __FUNCTION__, len, taddr().target.c_str(), chaddr().pipe, chaddr().client));
    return -1;
  }

  RecvData recvdata(mb, recvtime);
  enqueueRecv_(recvdata);
  return 0;
}

void ChannelBase::enqueueRecv_(RecvData const & recvdata)
{
  NI_PROFILE_BLOCK(__FUNCTION__);
  //unsigned long recvSeqNum;
  //if (mb->length() >= sizeof(recvSeqNum))
  //{
  //  memcpy(&recvSeqNum, mb->rd_ptr(), sizeof(recvSeqNum));
  //  NI_ASSERT(recvSeqNum > lastRecvSeqNum_.value(), "WRONG RECV SEQUENCE");
  //  lastRecvSeqNum_ = recvSeqNum;
  //}

  recvQueue_.push_back(recvdata);
}

ACE_Message_Block* ChannelBase::dequeueRecv()
{
  NHPTimer::STime recvtime;
  return dequeueRecv(recvtime);
}

ACE_Message_Block* ChannelBase::dequeueRecv(NHPTimer::STime & recvtime)
{
  NI_PROFILE_BLOCK(__FUNCTION__);
  ACE_Guard<ACE_Thread_Mutex> lock(recvQueueMutex_);
  RecvData data;
  if (recvQueue_.size())
  {
    data = recvQueue_.front();
    recvQueue_.pop_front();
    recvtime = data.recvtime_;
  }
  return data.mb_;
}

int ChannelBase::recvQueueSize() const
{
  NI_PROFILE_BLOCK(__FUNCTION__);
  ACE_Guard<ACE_Thread_Mutex> lock(recvQueueMutex_);
  return recvQueue_.size();
}

int ChannelBase::onOpenChannel(bool success, Transport::ChannelAddr const & chnlAddr)
{
  NI_PROFILE_BLOCK(__FUNCTION__);

  ACE_DEBUG((LM_TRACE, ACE_TEXT("%s(success=%d c=%d p=%d s=%d)"), 
    __FUNCTION__, success, chnlAddr.client, chnlAddr.pipe, chnlAddr.sender));

  ACE_ASSERT(true == active());

  int rc = -1;
  TL::ConnectionSP spconn = wpconn_;
  if (TL::IsValid(spconn))
  {
    if (success)
    {
      chaddr(chnlAddr);
      _SetStatus(EChannelStatus::CONNECTED);

      Transport::TPipeId pid = Transport::EKnownPipeId::Invalid;
      rc = spconn->onOpenChannel(this, pid);
      if (0 == rc)
      {
        rc = startOutOp_(spconn);
        if (rc < 0)
        {
          ACE_DEBUG((LM_WARNING, ACE_TEXT("%s. Can't start out operation (p=%d c=%d s=%d)"), 
            __FUNCTION__, chaddr().pipe, chaddr().client, chaddr().sender));
        }
      }
      else
      {
        ACE_DEBUG((LM_WARNING, ACE_TEXT("%s. Can't start out operation (p=%d c=%d s=%d)"), 
          __FUNCTION__, chaddr().pipe, chaddr().client, chaddr().sender));
      }
    }
    else
    {
      rc = 0;
      _SetStatus(EChannelStatus::CLOSED);
      spconn->onChannelClosed(this);
    }
  }
  else
  {
    ACE_DEBUG((LM_ERROR, ACE_TEXT("%s. Connection is invalid(t=%s p=%d c=%d s=%d)"), 
      __FUNCTION__, taddr().target.c_str(), chaddr().pipe, chaddr().client, chaddr().sender));
  }

  if (rc < 0)
    _SetStatus(EChannelStatus::CLOSED);

  return rc;
}

int ChannelBase::onOpenChannel(Transport::Address const & addr, Transport::TPipeId& pipeid)
{
  NI_PROFILE_BLOCK(__FUNCTION__);

  ACE_DEBUG((LM_TRACE, ACE_TEXT("%s(c=%d t=%s s=%s)"), 
    __FUNCTION__, addr.client, addr.target.c_str(), addr.source.c_str()));

  ACE_ASSERT(false == active());

  int rc = -1;
  TL::ConnectionSP spconn = wpconn_;
  if (TL::IsValid(spconn))
  {
    rc = spconn->onOpenChannel((this), pipeid);
    if (rc < 0)
    {
      ACE_ERROR((LM_WARNING, ACE_TEXT("%s. Can't start out operation (p=%d c=%d s=%d)"), 
        __FUNCTION__, chaddr().pipe, chaddr().client, chaddr().sender));
    }
    else
    {
      chaddr(addr.client, pipeid);
      //  can't set here Connected state due to actually we haven't sent response to remote peer yet
    }
  }
  else
  {
    ACE_ERROR((LM_ERROR, ACE_TEXT("%s. Connection is invalid(t=%s p=%d c=%d s=%d)"), 
      __FUNCTION__, taddr().target.c_str(), chaddr().pipe, chaddr().client, chaddr().sender));
  }

  if (rc < 0)
    _SetStatus(EChannelStatus::CLOSED);

  return rc;
}

void ChannelBase::onOpenChannelNotify()
{
  NI_PROFILE_BLOCK(__FUNCTION__);

  ACE_DEBUG((LM_TRACE, ACE_TEXT("%s(c=%d p=%d s=%d)"), 
    __FUNCTION__, chaddr().client, chaddr().pipe, chaddr().sender));

  _SetStatus(EChannelStatus::CONNECTED);

  TL::ConnectionSP spconn = wpconn_;
  if (TL::IsValid(spconn))
  {
    spconn->onOpenChannelNotify(this);
  }
}

Transport::TLoginData const & 
ChannelBase::openChannelKey() const
{
  return logindata_;
}

void ChannelBase::close(bool active)
{
  NI_PROFILE_BLOCK(__FUNCTION__);

  EChannelStatus::Enum sts = status();
  if (sts < 0)
  {
    ACE_ERROR((LM_INFO, ACE_TEXT("%s. Channel is already in '%s' state(active=%d p=%d c=%d s=%d)"), 
      __FUNCTION__, EChannelStatus::ToString(sts), active, chaddr().pipe, chaddr().client, chaddr().sender));
    return;
  }

  if (active)
  {
    if (EChannelStatus::CONNECTED == sts)
      _SetStatus(EChannelStatus::CLOSING);
    else
      _SetStatus(EChannelStatus::CLOSED);
  }
  else
  {
    _SetStatus(EChannelStatus::CLOSED);
  }

  sts = status();

  ACE_ERROR((LM_INFO, ACE_TEXT("%s(active=%d p=%d c=%d s=%d)"), 
    __FUNCTION__, active, chaddr().pipe, chaddr().client, chaddr().sender));

  if (active && EChannelStatus::CLOSING == sts)
  {
    //  send close channel command
    TL::ConnectionSP spconn = wpconn_;
    if (TL::IsValid(spconn))
    {
      op::CloseChannelPtr ccop(new op::CloseChannel(spconn->connectionContext(), this));
      int rc = startOutOp_(spconn, ccop);
      if (rc < 0)
      {
        ACE_DEBUG((LM_WARNING, ACE_TEXT("%s. Can't start close channel operation (p=%d c=%d s=%d)"), 
          __FUNCTION__, chaddr().pipe, chaddr().client, chaddr().sender));
      }
    }
  }
  else
  {
    clearOutOp_();
  }
}

int ChannelBase::checkActivity(ACE_Time_Value const & now)
{
  NI_PROFILE_BLOCK(__FUNCTION__);

  EChannelStatus::Enum sts = status();
  if (sts < 0)
  {
    ACE_ERROR((LM_INFO, ACE_TEXT("%s. Channel is already closed(t=%s p=%d c=%d s=%d)"), 
      __FUNCTION__, taddr().target.c_str(), chaddr().pipe, chaddr().client, chaddr().sender));
    return -1;
  }

  if (keepalivePeriod().sec() && now - lastKeepaliveTime_ > keepalivePeriod()) //  send keepalive msg
  {
    Transport::KeepAliveMessage msg;
    sendMsg(&msg);
    lastKeepaliveTime_ = now;
  }

  if (active() && pingPeriod_.sec() && now - lastPingTime_ > pingPeriod_)
  {
    TL::ConnectionSP spconn = wpconn_;
    if (TL::IsValid(spconn))
    {
      op::PingChannel* op(new op::PingChannel(spconn->connectionContext(), this, ++pingSeqNumSent_));
      if (op)
      {
        int rc = op->Post();
        if (rc < 0)
          ACE_ERROR((LM_WARNING, ACE_TEXT("%s. Can't post ping op(t=%s p=%d c=%d)"), 
          __FUNCTION__, taddr().target.c_str(), chaddr().pipe, chaddr().client));
      }
    }
    else
    {
      ACE_ERROR((LM_WARNING, ACE_TEXT("%s. Connection is not valid(t=%s p=%d c=%d)"), 
        __FUNCTION__, taddr().target.c_str(), chaddr().pipe, chaddr().client));
    }
    lastPingTime_ = now;
  }

  return 0;
}

void ChannelBase::sendMsg( Transport::MessageBase* pMsg )
{
  NI_PROFILE_BLOCK(__FUNCTION__);

  ACE_DEBUG((LM_TRACE, ACE_TEXT("%s(msg=%d)"), __FUNCTION__, pMsg->GetTypeId()));

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
    ACE_Message_Block* mb = packMessage(pMsg);
    if (mb)
      send_(spconn, mb);
    else
      ACE_ERROR((LM_CRITICAL, ACE_TEXT("%s. Can't allocate memory(msg=%d t=%s p=%d c=%d)"),
      __FUNCTION__, pMsg->GetTypeId(), taddr().target.c_str(), chaddr().pipe, chaddr().client));
  }
  else
  {
    NI_ASSERT(sts < 0, NI_STRFMT("Channel in '%s' state, but connection already invalid", EChannelStatus::ToString(sts)));

    ACE_DEBUG((LM_DEBUG, ACE_TEXT("%s. Connection is invalid(t=%s p=%d c=%d)"),
      __FUNCTION__, taddr().target.c_str(), chaddr().pipe, chaddr().client));
  }
}



void ChannelBase::setPing(long ping, unsigned long seqnum)
{
  //  лок ставить ради пинга не хочется, 
  //  допускаем погрешность, через GetPing могут взять новое значение счетчика и старое значение пинга
  NI_ASSERT(pingSeqNumRecv_ < seqnum, "Just received ping seqnum MUST BE more than previous one");
  pingSeqNumRecv_ = seqnum;
  ping_ = ping;
}

} //namespace TransportLayer
