#pragma once
#include <naio/Types.h>
#include <Network/TransportTypes.h>
#include "transport/TLTypes.h"
#include <ace/INET_Addr.h>
#include <Network/TransportUtils.h>
#include <mballocator/MessageBlockFactory.h>
#include "transport/TLChannelListenerInt.h"
#include "naio/ConnectionContext.h"
#include <naio/Operation.h>
#include "transport/TLOpsPtr.h"
#include <map>

namespace Transport
{
  struct OpenChannelResponse;
}

namespace naio
{
  class Operation;
}

namespace TransportLayer
{
  namespace TL = TransportLayer;

  namespace op
  {
    class OpenChannel;
    class ChannelOp;
    class ConnectionOutput;
  }

  class ConnectionManager;

  class ChannelIndex
  {
  public:
    ChannelIndex()
      :cid_(Transport::autoAssignClientId),
      pid_(Transport::EKnownPipeId::Invalid)
    {}

    ChannelIndex(Transport::TClientId const & cid, Transport::TPipeId const & pid)
      :cid_(cid),
      pid_(pid)
    {}

    ChannelIndex(Transport::ChannelAddr const & chaddr)
      :cid_(chaddr.client),
      pid_(chaddr.pipe)
    {}

    ~ChannelIndex()
    {}

  public:
    bool operator < (ChannelIndex const & other) const
    {
      if (cid_ == other.cid_)
        return pid_ < other.pid_;
      else
        return cid_ < other.cid_;
    }

  private:
    Transport::TClientId  cid_;
    Transport::TPipeId    pid_;
  };


  struct ChannelContainer
  {
    typedef std::map<ChannelIndex, TL::IChannelInternalSP> ChannelsMapT;
    ChannelsMapT map_;

    bool add(TL::IChannelInternalSP const & spchnl);
    bool add(TL::IChannelInternalSP const & spchnl, Transport::TClientId const & cid, Transport::TPipeId const & pid);
    void remove(Transport::ChannelAddr const & chaddr);
    TL::IChannelInternalSP find(Transport::ChannelAddr const & chaddr);
    void clear()
    {
      map_.clear();
    }
    size_t size() const
    {
      return map_.size();
    }
  };

  class Connection : public StrongFromThis<Connection>
  {
    friend class ConnectionManager;
    friend class ChannelFactory;

  public:
    enum StatusT
    {
      INVALID = -2,
      CLOSED = -1,
      CONNECTED = 0,
      CONNECTING = 1,
    };

  public:
    Connection();
    Connection(nstl::string const & netaddr, Transport::TServiceId const & svcid, bool activelyEstablished,
      TL::ConnectionManagerSP const & mngr);
    ~Connection();

  public:
    TL::IChannelInternalSP findChannel(Transport::ChannelAddr const & caddr);

    //  getters
    Connection::StatusT status() const;
    naio::ConnectionContextSP const & connectionContext() const { return spconnctx_; }
    unsigned int id() const;
    nstl::string const & netaddr() const { return netaddr_; }
    ACE_INET_Addr const & localAddr() const { return localAddr_; }
    ACE_INET_Addr const & remoteAddr() const { return remoteAddr_; }
    Transport::TServiceId const & svcid() const { return svcid_; }
    TL::ConnectionManagerWP manager() const { return mngr_; }

    //  
    int startOpenQueuedChannel();
    int startOpenChannel(IChannelInternalSP const & spchnl);
    int completeOpenChannel(Transport::OpenChannelResponse *pMsg);
    int cancelOpenChannel(const void* tag);
    int cancelOpeningChannels();

    void close(bool active);
    unsigned int channelCount() const;

    int onOpenChannel(TL::IChannelInternalSP const & spchnl, Transport::TPipeId& pid);
    void completeAcceptChannels();
    void onOpenChannelNotify(TL::IChannelInternalSP const & spchnl);
    void onChannelClosed(TL::IChannelInternalSP const & spchnl);

    bool activelyEstablished() const { return activelyEstablished_; }

    int checkActivity(const ACE_Time_Value& last_op_time);
    int onTimeout(const void *arg);

    //  send queue
    unsigned int sendOpQueueSize() const;
    int startOutOp();
    int startOutOp(op::ChannelOpPtr const & op);
    int completeActiveOp(op::ConnectionOutputPtr const & op);

  private:
    void init(TL::ConnectionWP const & wp);
    void setMessageBlockFactory(TL::MessageBlockFactorySP const & mbf);
    void id(unsigned int);
    void setAddresses(ACE_INET_Addr const & local, ACE_INET_Addr const & remote);

    void status(Connection::StatusT sts);
    Connection::StatusT status_() const { return sts_; }
    void status_(Connection::StatusT sts) { sts_ = sts; }

    void connectionContext(naio::ConnectionContextSP const & spcc) { spconnctx_ = spcc; }
    void channelListener( TL::ChannelListenerInternal *  spcl ) { spChnlListener_ = spcl; }

    void enqueueChannel2Open_(IChannelInternalSP const & spchnl);
    IChannelInternalSP dequeueChannel2Open_();
    unsigned int channels2open() const;

    void close_(bool active);
    void closeOpenedChannels_();
    int openedChannels() const;

    bool registerChannel_(TL::IChannelInternalSP const & spchnl, Transport::TPipeId& pid);
    void unregisterChannel_(TL::IChannelInternalSP const & spchnl);

    TL::MessageBlockFactorySP  messageBlockFactory_() const { return msgBlkFactory_; }

    Transport::TPipeId generatePipeId_(Transport::TClientId const & cid);
    void freePipeId_(Transport::TClientId const & cid, Transport::TPipeId const & pid);
    bool registerPipeId_(Transport::TClientId const & cid, Transport::TPipeId pid);
    bool unregisterPipeId_(Transport::TClientId const & cid, Transport::TPipeId const & pid);

    //  send queue internals
    int startOutOp_();
    unsigned int enqueueOutOp_(op::ChannelOpPtr const & op);
    op::ChannelOpPtr dequeueOutOp_();
    op::ChannelOpPtr dequeueAllOutOp_();

    op::OpenChannelPtr const & currentOpenChannelOp() const;
    op::OpenChannelPtr popCurrentOpenChannelOp();
    void cancelWaitingChannels4Opening();

  private:
    naio::ConnectionContextStrongPtr spconnctx_;
    StrongMT<TL::ChannelListenerInternal> spChnlListener_;
    StatusT sts_;
    mutable ACE_Thread_Mutex stsMutex_;
    nstl::string  netaddr_;
    ACE_INET_Addr localAddr_;
    ACE_INET_Addr remoteAddr_;
    Transport::TServiceId svcid_;
    TL::ConnectionManagerWP mngr_;
    unsigned int connid_;

    typedef std::map<Transport::TClientId, Transport::PipeIdGenerator> User2IdGenMapT;
    User2IdGenMapT clientPipeGens_;

    typedef vector<Transport::TPipeId> PipesT;
    typedef std::map<Transport::TClientId, vector<Transport::TPipeId> > User2PipesT;
    User2PipesT reservedPipes_;

    typedef nstl::list<TL::IChannelInternalSP> ChannelsT;
    ChannelContainer channels_;
    ChannelsT acceptingChannels_;
    mutable ACE_Thread_Mutex  channelsMutex_;

    ChannelsT channels2open_;
    op::OpenChannelPtr  currentOpenChannelOp_;
    mutable ACE_Thread_Mutex  openChannelsMutex_;

    TL::MessageBlockFactorySP msgBlkFactory_;
    bool activelyEstablished_;

    //  output operations queue
    struct OutOpQueueT
    {
      OutOpQueueT()
        :count_(0)
      {}

      op::ChannelOpPtr head_;
      op::ChannelOpPtr end_;
      unsigned int count_;
    };

    OutOpQueueT outOpQueue_;
    naio::OperationPtr  activeOutOp_;
    mutable ACE_Thread_Mutex outQueueMutex_;

    volatile unsigned int openChannelOpCount_;
  };
}

namespace TL = TransportLayer;
