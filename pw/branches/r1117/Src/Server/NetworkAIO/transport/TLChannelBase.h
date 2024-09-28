#pragma once
#include "transport/TLChannelInt.h"
#include <ace/Time_Value.h>
#include "transport/TLChannelOp.h"
#include <ace/Log_Msg.h>


class ACE_Message_Block;

namespace TransportLayer
{
  namespace TL = TransportLayer;

  class ChannelBase : public ChannelSuperBase
  {
    NI_DECLARE_CLASS_1( ChannelBase, ChannelSuperBase );

  public:
    ChannelBase(Transport::EChannelType::Enum _channeltype, bool _active, Transport::Address const & _addr, Transport::TLoginData const & _logindata, Transport::MessageFactory* _mf);
    ~ChannelBase();

  public:
    struct RecvData
    {
      RecvData() : mb_(0), recvtime_(0) {}
      RecvData(ACE_Message_Block* mb, NHPTimer::STime const & recvtime) : mb_(mb), recvtime_(recvtime) {}

      ACE_Message_Block* mb_;
      NHPTimer::STime recvtime_;
    };

  public:

    //////////////////////////////////////////////////////////////////////////
    /// ChannelSuperBase

    ///  open channel actively
    virtual int onOpenChannel(bool success, Transport::ChannelAddr const & remoteAddr);
    ///  channel open passively
    virtual int onOpenChannel(Transport::Address const & addr, Transport::TPipeId& pipeid);
    virtual void onOpenChannelNotify();

    ///  allocator methods
    virtual ACE_Message_Block* allocMsgBlock_(size_t len, MBType::Enum _type);
    virtual ACE_Message_Block* allocMsgBlock_(size_t len, char const * data, MBType::Enum _type);
    virtual void freeMsgBlock_(ACE_Message_Block* mb);

    virtual ACE_Message_Block* packMessage(Transport::MessageBase* pmsg);
    virtual Transport::MessageBase* unpackMessage(ACE_Message_Block* mb);

    virtual TL::ConnectionWP getConnection() { return wpconn_; }

    virtual void close(bool active);

    virtual void setPing(long ping, unsigned long seqnum);

    virtual unsigned long lastRecvSeqNum() const { return lastRecvSeqNum_.value(); }

    virtual int enqueueRecv(size_t len, char const * data);

    virtual void lastRecvSeqNum(unsigned long seqnum) { lastRecvSeqNum_ = seqnum; }

    virtual int completeOp(op::ChannelOpPtr const & op);

    virtual int checkActivity(ACE_Time_Value const & now);

    virtual unsigned int openTimeout() const { return openTimeout_; }

    virtual Transport::TLoginData const & openChannelKey() const;

    /// ChannelSuperBase
    //////////////////////////////////////////////////////////////////////////

  public:
    //  send queue
    unsigned int outOpQueueSize() const;

    //  recv queue
    ACE_Message_Block* dequeueRecv();
    ACE_Message_Block* dequeueRecv(NHPTimer::STime & recvtime);
    int recvQueueSize() const;

    ACE_Time_Value const & keepalivePeriod() const { return keepalivePeriod_; }

    //  others
    unsigned long lastOutSeqNum() const { return outSeqNum_.value(); }
    unsigned long lastSentSeqNum() const { return lastSentSeqNum_.value(); }

  protected:
    void messageBlockFactory_(TL::MessageBlockFactorySP const & _factory);

    void setConnection_(TL::ConnectionSP const & spconn) {
      NI_ASSERT(spconn != 0, "Connection must NOT be 0");
      wpconn_ = spconn;
    }

    //  recv queue
    void enqueueRecv_(RecvData const & recvdata);

    //  out queue
    void enqueueOutOp_(op::ChannelOpPtr const & op);
    op::ChannelOpPtr dequeueOutOp_();
    void clearOutOp_();

    //  connection out queue
    int startOutOp_(TL::ConnectionSP const & spconn);
    int startOutOp_(TL::ConnectionSP const & spconn, op::ChannelOpPtr const & op);

    void setOpenTimeout_(unsigned int timeout) { openTimeout_ = timeout; }
    void setPingPeriod_(unsigned int sec) { pingPeriod_ = ACE_Time_Value(sec); }

    int send_(TL::ConnectionSP const & spconn, ACE_Message_Block* mb);

    unsigned long ping() const { return ping_.value(); }
    unsigned long pingSeqNumRecv() const { return pingSeqNumRecv_.value(); }

    void keepalivePeriod(ACE_Time_Value const & _keepalivePeriod) { keepalivePeriod_ = _keepalivePeriod; }

    void sendMsg( Transport::MessageBase* pMessage );

  private:
    TL::MessageBlockFactorySP const & messageBlockFactory() const { return msgBlkFactory_; }

  protected:
    TL::ConnectionWP wpconn_;

  private:
    //  early output operations queue (operation pushed w/o established channel)
    struct OpQueueT
    {
      OpQueueT()
        :count_(0)
      {}

      op::ChannelOpPtr head_;
      op::ChannelOpPtr end_;
      unsigned int count_;
    };
    OpQueueT outOpQueue_;
    mutable ACE_Thread_Mutex outQueueMutex_;

    ACE_Atomic_Op<ACE_Thread_Mutex, unsigned long> outSeqNum_;
    ACE_Atomic_Op<ACE_Thread_Mutex, unsigned long> lastSentSeqNum_;

    //  receive queue
    typedef nstl::list<RecvData> RecvQueueT;
    RecvQueueT  recvQueue_;
    mutable ACE_Thread_Mutex recvQueueMutex_;
    Transport::MessageFactory* msgFactory_;
    ACE_Atomic_Op<ACE_Thread_Mutex, unsigned long> lastRecvSeqNum_;
    ACE_Atomic_Op<ACE_Thread_Mutex, unsigned long> lastDequeueRecvSeqNum_;

    ACE_Time_Value keepalivePeriod_;
    ACE_Time_Value lastKeepaliveTime_;
    unsigned int openTimeout_;

    ACE_Atomic_Op<ACE_Thread_Mutex, unsigned long> ping_;
    ACE_Atomic_Op<ACE_Thread_Mutex, unsigned long> pingSeqNumSent_;
    ACE_Atomic_Op<ACE_Thread_Mutex, unsigned long> pingSeqNumRecv_;
    ACE_Time_Value pingPeriod_;
    ACE_Time_Value lastPingTime_;

    Transport::TLoginData logindata_;

  private:
    TL::MessageBlockFactorySP msgBlkFactory_;
  };
}
