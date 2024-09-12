#include "transport/stdafx.h"
#include "transport/TLConnection.h"
#include "transport/TLChannelInt.h"
#include <ace/Guard_T.h>
#include <ace/OS_NS_sys_time.h>
#include "transport/TLOpenChannelOp.h"
#include "transport/TLConnectionManager.h"
#include "transport/TLConnectionOutputOp.h"
#include <Network/TransportMessages.h>

namespace TransportLayer
{
  bool ChannelContainer::add(TL::IChannelInternalSP const & spchnl)
  {
    Transport::ChannelAddr const & caddr = spchnl->chaddr();
    NI_ASSERT(caddr.pipe >= Transport::EKnownPipeId::FrontEnd, "");
    return map_.insert(std::make_pair(ChannelIndex(caddr.client, caddr.pipe), spchnl)).second;
  }

  bool ChannelContainer::add(TL::IChannelInternalSP const & spchnl, Transport::TClientId const & cid, Transport::TPipeId const & pid)
  {
    NI_ASSERT(pid >= Transport::EKnownPipeId::FrontEnd, "");
    return map_.insert(std::make_pair(ChannelIndex(cid, pid), spchnl)).second;
  }

  void ChannelContainer::remove(Transport::ChannelAddr const & chaddr)
  {
    ChannelsMapT::iterator it = map_.find(ChannelIndex(chaddr));
    if (it != map_.end())
    {
      map_.erase(it);
    }
  }

  TL::IChannelInternalSP ChannelContainer::find(Transport::ChannelAddr const & chaddr)
  {
    ChannelsMapT::iterator it = map_.find(ChannelIndex(chaddr));
    if (it != map_.end())
      return it->second;

    return TL::IChannelInternalSP();
  }

  Connection::Connection()
    :sts_(Connection::INVALID),
    openChannelOpCount_(0)
  {}

  Connection::Connection(nstl::string const & netaddr, 
                         Transport::TServiceId const & svcid, 
                         bool activelyEstablished, 
                         TL::ConnectionManagerSP const & mngr)
    :sts_(Connection::INVALID),
    netaddr_(netaddr),
    svcid_(svcid),
    mngr_(mngr),
    activelyEstablished_(activelyEstablished),
    connid_(static_cast< unsigned int >(-1)),
    openChannelOpCount_(0)
  {
    NI_ASSERT(mngr != 0, "Connection manager is NULL!!!");
  }

  Connection::~Connection()
  {
  }

  void Connection::init(TL::ConnectionWP const & wp)
  {
    NI_PROFILE_BLOCK(__FUNCTION__);

    NI_ASSERT(wp.unsafe_get() == this, "Pointers is not equal!");
    this->setWeakPtr(wp);
    this->status(TL::Connection::CONNECTING);
  }

  void Connection::setMessageBlockFactory(TL::MessageBlockFactorySP const & mbf)
  {
    msgBlkFactory_ = mbf;
  }

  void Connection::close_(bool active)
  {
    NI_PROFILE_BLOCK(__FUNCTION__);

    status(CLOSED);
    TL::ConnectionManagerSP spmngr = mngr_;
    if (TL::IsValid(spmngr))
      spmngr->CloseConnection(TL::GetStrongFromThis(this), active);
  }

  int Connection::startOpenQueuedChannel()
  {
    NI_PROFILE_BLOCK(__FUNCTION__);

    IChannelInternalSP spchnl;
    return startOpenChannel(spchnl);
  }

  int Connection::startOpenChannel(TL::IChannelInternalSP const & spchnl)
  {
    ACE_DEBUG((LM_DEBUG, ACE_TEXT("%s(t=%s)"), __FUNCTION__, (TL::IsValid(spchnl) ? spchnl->taddr().target.c_str() : "" )));

    NI_PROFILE_BLOCK(__FUNCTION__);

    if (Connection::CLOSED ==  status())
    {
      ACE_ERROR((LM_WARNING, ACE_TEXT("%s. Connection already closed(t=%s)"), 
        __FUNCTION__, (TL::IsValid(spchnl) ? spchnl->taddr().target.c_str() : "" )));
      return -1;
    }

    int rc = 0;
    {
      ACE_Guard<ACE_Thread_Mutex> lock(openChannelsMutex_);
      TL::IChannelInternalSP spch = spchnl;

      if (!TL::IsValid(spch))
        spch = dequeueChannel2Open_();

      if (TL::IsValid(spch))
      {
        if (status() == Connection:: CONNECTED && !currentOpenChannelOp_)
        {
          op::OpenChannelPtr ocop(new op::OpenChannel(spconnctx_, spch, reinterpret_cast<void*>(++openChannelOpCount_)));
          currentOpenChannelOp_ = ocop;
          rc = ocop->Post();
          if (rc < 0)
          {
            currentOpenChannelOp_ = 0;
            ACE_DEBUG((LM_ERROR, ACE_TEXT("%s: can't post open channel operation"), __FUNCTION__));
          }
        }
        else
        {
          enqueueChannel2Open_(spch);
        }
      }

    }

    return rc;
  }

  int Connection::completeOpenChannel(Transport::OpenChannelResponse *pMsg)
  {
    NI_PROFILE_BLOCK(__FUNCTION__);

    ACE_DEBUG((LM_DEBUG, ACE_TEXT("[TL] %s(res=%d p=%d c=%d)"), 
      __FUNCTION__, pMsg->success, pMsg->remoteAddr.pipe, pMsg->remoteAddr.client));

    int rc = 0;
    op::OpenChannelPtr ocop = popCurrentOpenChannelOp();
    if (ocop)
    {
      rc = ocop->complete(pMsg);
    }
    else
    {
      ACE_ERROR((LM_ERROR, ACE_TEXT("[TL] %s. No open channel operation is in progress(res=%d p=%d c=%d)"), 
        __FUNCTION__, pMsg->success, pMsg->remoteAddr.pipe, pMsg->remoteAddr.client));
    }

    rc = startOpenQueuedChannel();
    return rc;
  }

  int Connection::cancelOpenChannel(const void* tag)
  {
    NI_PROFILE_FUNCTION;

    ACE_DEBUG((LM_DEBUG, ACE_TEXT("[TL] %s(tag=%@)"), __FUNCTION__, tag));

    int rc = 0;
    op::OpenChannelPtr ocop = popCurrentOpenChannelOp();
    if (ocop)
    {
      IChannelInternalSP chnl = ocop->channel();
      if (chnl)
      {
        if (ocop->tag() == tag) //  check than this timeout belong to this operation
        {
          ACE_ERROR((LM_WARNING, ACE_TEXT("[TL] %s. Open channel timeout(tag=%@ c=%d p=%d)"), 
            __FUNCTION__, tag, chnl->chaddr().client, chnl->chaddr().pipe));

          Transport::OpenChannelResponse fakemsg(false, chnl->channeltype());
          rc = ocop->complete(&fakemsg);
        }
        else
        {
          //  report late timeout
          ACE_ERROR((LM_WARNING, ACE_TEXT("[TL] %s. late timeout(tag=%@ optag=%@ c=%d p=%d)"), 
            __FUNCTION__, tag, ocop->tag(), chnl->chaddr().client, chnl->chaddr().pipe));
        }
      }
      else
      {
        ACE_ERROR((LM_ERROR, ACE_TEXT("[TL] %s. Channel is NULL in open channel operation(tag=%@)"), 
          __FUNCTION__, tag));
      }
    }
    else
    {
      ACE_ERROR((LM_ERROR, ACE_TEXT("[TL] %s. No open channel operation is in progress(tag=%@)"), 
        __FUNCTION__, tag));
    }

    rc = startOpenQueuedChannel();
    return rc;
  }

  int Connection::cancelOpeningChannels()
  {
    NI_PROFILE_BLOCK(__FUNCTION__);

    op::OpenChannelPtr ocop = popCurrentOpenChannelOp();
    if (ocop)
    {
      Transport::OpenChannelResponse fakemsg(false, ocop->channel()->channeltype());
      ocop->complete(&fakemsg);
    }

    cancelWaitingChannels4Opening();

    return 0;
  }

  void Connection::completeAcceptChannels()
  {
    NI_PROFILE_BLOCK(__FUNCTION__);

    ACE_Guard<ACE_Thread_Mutex> lock(channelsMutex_);
    ChannelsT::iterator it = acceptingChannels_.begin();
    ChannelsT::iterator eit = acceptingChannels_.end();
    for (; it != eit; ++it)
    {
      (*it)->onOpenChannelNotify();
    }
    acceptingChannels_.clear();
  }

  bool Connection::registerChannel_(TL::IChannelInternalSP const & spchnl, Transport::TPipeId& pid)
  {
    NI_PROFILE_BLOCK(__FUNCTION__);

    if (spchnl->getConnection().strong() != TL::GetStrongFromThis(this))
      return false;

    ACE_Guard<ACE_Thread_Mutex> lock(channelsMutex_);
    bool addchnl = false;
    if (!spchnl->active())
    {
      pid = Transport::EKnownPipeId::Invalid;
      pid = generatePipeId_(spchnl->taddr().client);
      if (Transport::EKnownPipeId::Invalid == pid)
        return false;

      addchnl = channels_.add(spchnl, spchnl->taddr().client, pid);
    }
    else
    {
      if (registerPipeId_(spchnl->taddr().client, spchnl->chaddr().pipe))
      {
        addchnl = channels_.add(spchnl);
      }
    }
    NI_ASSERT(addchnl, "");

    if (addchnl)
    {
      if (!spchnl->active())
        acceptingChannels_.push_back(spchnl);

      ConnectionManagerSP connmngr = manager();
      if (TL::IsValid(connmngr))
      {
        if (spchnl->active())
          connmngr->Peername2Connection(spchnl->taddr().target, getWeakPtr());
        else
          connmngr->Peername2Connection(spchnl->taddr().source, getWeakPtr());
      }
    }

    return addchnl;
  }

  void Connection::unregisterChannel_(TL::IChannelInternalSP const & spchnl)
  {
    NI_PROFILE_BLOCK(__FUNCTION__);

    if (spchnl->getConnection().strong() != TL::GetStrongFromThis(this))
      return;

    Transport::ChannelAddr const & caddr = spchnl->chaddr();

    ACE_DEBUG((LM_DEBUG, ACE_TEXT("[TL] %s (c=%d p=%d t=%s)"), 
      __FUNCTION__, caddr.client, caddr.pipe, spchnl->taddr().target.c_str()));

    ACE_DEBUG((LM_DEBUG, ACE_TEXT("[TL] Remove channel from connection(c=%d p=%d t=%s)"), 
      caddr.client, caddr.pipe, spchnl->taddr().target.c_str()));

    ACE_Guard<ACE_Thread_Mutex> lock(channelsMutex_);
    freePipeId_(caddr.client, caddr.pipe);
    channels_.remove(caddr);
  }

  TL::IChannelInternalSP Connection::findChannel(Transport::ChannelAddr const & caddr)
  {
    NI_PROFILE_BLOCK(__FUNCTION__);

    ACE_Guard<ACE_Thread_Mutex> lock(channelsMutex_);
    return channels_.find(caddr);
  }

  void Connection::close(bool active)
  {
    NI_PROFILE_BLOCK(__FUNCTION__);

    ACE_ERROR((LM_INFO, ACE_TEXT("[TL] %s(connid=%d active=%d)"), __FUNCTION__, id(), active));

    {
      ACE_Guard<ACE_Thread_Mutex> lock(stsMutex_);
      if (CLOSED == status_())
        return;

      status_(CLOSED);
    }

    if (!active)
    {
      closeOpenedChannels_();
      cancelOpeningChannels();
    }

    close_(active);
  }

  unsigned int Connection::channelCount() const
  {
    NI_PROFILE_BLOCK(__FUNCTION__);

    ACE_Guard<ACE_Thread_Mutex> lock(channelsMutex_);
    return (unsigned int)(channels_.size());
  }

  void Connection::enqueueChannel2Open_(TL::IChannelInternalSP const & spchnl)
  {
    NI_PROFILE_BLOCK(__FUNCTION__);

    channels2open_.push_back(spchnl);
    ACE_DEBUG((LM_DEBUG, ACE_TEXT("[TL] ENqueueChannel2Open(qs=%d t='%s' s='%s' c='%d')"), 
      channels2open_.size(), spchnl->taddr().target.c_str(), spchnl->taddr().source.c_str(), spchnl->taddr().client));
  }

  TL::IChannelInternalSP Connection::dequeueChannel2Open_()
  {
    NI_PROFILE_BLOCK(__FUNCTION__);

    IChannelInternalSP spchnl;
    if (channels2open_.size())
    {
      spchnl = channels2open_.front();
      channels2open_.pop_front();

      ACE_DEBUG((LM_DEBUG, ACE_TEXT("[TL] DEqueueChannel2Open(qs=%d t='%s' s='%s' c='%d')"), 
        channels2open_.size(), spchnl->taddr().target.c_str(), spchnl->taddr().source.c_str(), spchnl->taddr().client));
    }
    return spchnl;
  }

  int Connection::onOpenChannel(TL::IChannelInternalSP const & spchnl, Transport::TPipeId& pid)
  {
    NI_PROFILE_BLOCK(__FUNCTION__);

    ACE_DEBUG((LM_TRACE, ACE_TEXT("%s(c=%d t=%s s=%s)"), 
      __FUNCTION__, spchnl->taddr().client, spchnl->taddr().target.c_str(), spchnl->taddr().source.c_str()));

    int rc = 0;
    if (!registerChannel_(spchnl, pid))
    {
      Transport::ChannelAddr const & caddr = spchnl->chaddr();
      ACE_ERROR((LM_ERROR, ACE_TEXT("%s. Can't register channel(p=%d c=%d s=%d)"), 
        __FUNCTION__, caddr.pipe, caddr.client, caddr.sender));
      rc = -1;
    }

    return rc;
  }

  void Connection::onOpenChannelNotify(TL::IChannelInternalSP const & spchnl)
  {
    NI_PROFILE_BLOCK(__FUNCTION__);

    ACE_DEBUG((LM_TRACE, ACE_TEXT("%s(c=%d p=%d s=%d)"), 
      __FUNCTION__, spchnl->chaddr().client, spchnl->chaddr().pipe, spchnl->chaddr().sender));

    if (!spchnl->active())
    {
      NI_ASSERT(TL::IsValid(spChnlListener_), "Channel listener have to exist");
      //  notify channel listener
      spChnlListener_->onOpenChannel(spchnl);
    }
  }

  void Connection::onChannelClosed(TL::IChannelInternalSP const & spchnl)
  {
    NI_PROFILE_BLOCK(__FUNCTION__);

    ACE_DEBUG((LM_TRACE, ACE_TEXT("%s(c=%d p=%d s=%d)"), 
      __FUNCTION__, spchnl->chaddr().client, spchnl->chaddr().pipe, spchnl->chaddr().sender));

    EChannelStatus::Enum sts = spchnl->status();
    NI_ASSERT(EChannelStatus::CLOSED == sts || EChannelStatus::CLOSING == sts, "Channel have to be in one of these states");

    unregisterChannel_(spchnl);
  }

  void Connection::setAddresses(ACE_INET_Addr const & localaddr, ACE_INET_Addr const & remoteaddr)
  {
    NI_PROFILE_BLOCK(__FUNCTION__);

    localAddr_ = localaddr;
    remoteAddr_ = remoteaddr;
  }

  Transport::TPipeId Connection::generatePipeId_(Transport::TClientId const & cid)
  {
    NI_PROFILE_BLOCK(__FUNCTION__);

    Transport::TPipeId pipeid = Transport::EKnownPipeId::Invalid;
    Transport::PipeIdGenerator& gen = clientPipeGens_[cid];
    bool bexit = false;
    do
    {
      pipeid = gen.Generate();
      if (Transport::EKnownPipeId::Invalid != pipeid)
      {
        if (registerPipeId_(cid, pipeid))
          bexit = true;
        else
          bexit = false;
      }
      else
      {
        bexit = true;
      }
    }
    while(!bexit);

    return pipeid;
  }

  void Connection::freePipeId_(Transport::TClientId const & cid, Transport::TPipeId const & pid)
  {
    NI_PROFILE_BLOCK(__FUNCTION__);

    Transport::ClientIdGenerator& gen = clientPipeGens_[cid];
    gen.Release(pid);

    unregisterPipeId_(cid, pid);
  }

  int Connection::startOutOp()
  {
    NI_PROFILE_BLOCK(__FUNCTION__);

    ACE_Guard<ACE_Thread_Mutex> lock(outQueueMutex_);
    ACE_DEBUG((LM_TRACE, ACE_TEXT("%s(conn=%d)"), __FUNCTION__, spconnctx_->connid()));
    return startOutOp_();
  }

  int Connection::startOutOp(op::ChannelOpPtr const & op)
  {
    NI_PROFILE_BLOCK(__FUNCTION__);

    ACE_Guard<ACE_Thread_Mutex> lock(outQueueMutex_);
    unsigned int count = enqueueOutOp_(op);

    ACE_DEBUG((LM_DEBUG, ACE_TEXT("%s(count=%d)"), 
      __FUNCTION__, count));

    return startOutOp_();
  }

  unsigned int Connection::enqueueOutOp_(op::ChannelOpPtr const & op)
  {
    NI_PROFILE_BLOCK(__FUNCTION__);

    unsigned int count = 1;
    if (outOpQueue_.end_)
      outOpQueue_.end_->next(op);
    else
      outOpQueue_.head_ = outOpQueue_.end_ = op;

    op::ChannelOpPtr last = op;
    while(last->next())
    {
      last = last->next();
      ++count;
    }

    outOpQueue_.end_ = last;
    outOpQueue_.count_ += count;

    return count;
  }

  op::ChannelOpPtr Connection::dequeueOutOp_()
  {
    NI_PROFILE_BLOCK(__FUNCTION__);

    op::ChannelOpPtr op;
    if (outOpQueue_.head_)
    {
      op = outOpQueue_.head_;
      outOpQueue_.head_ = op->next();
      op->next(0);
      outOpQueue_.count_--;
      if (0 == outOpQueue_.count_)
        outOpQueue_.end_ = 0;
    }
    return op;
  }

  op::ChannelOpPtr Connection::dequeueAllOutOp_()
  {
    NI_PROFILE_BLOCK(__FUNCTION__);

    op::ChannelOpPtr op;
    if (outOpQueue_.head_)
    {
      op = outOpQueue_.head_;
      outOpQueue_.head_ = outOpQueue_.end_ = 0;
      outOpQueue_.count_ = 0;
    }
    return op;
  }

  int Connection::startOutOp_()
  {
    NI_PROFILE_BLOCK(__FUNCTION__);

    ACE_DEBUG((LM_TRACE, ACE_TEXT("%s(ch=%d)"), 
      __FUNCTION__, connectionContext()->connid()));

    int rc = 0;
    if (!activeOutOp_)
    {
      op::ChannelOpPtr op = dequeueAllOutOp_();
      if (op)
      {
        activeOutOp_ = new op::ConnectionOutput(TL::GetStrongFromThis(this), msgBlkFactory_, op);
        rc = activeOutOp_->Post();
        if (rc < 0)
        {
          activeOutOp_ = 0;
        }
      }
      else
      {
        ACE_DEBUG((LM_DEBUG, ACE_TEXT("%s. No out operations(ch=%d)"), 
          __FUNCTION__, connectionContext()->connid()));
      }
    }
    else
    {
      ACE_DEBUG((LM_DEBUG, ACE_TEXT("%s. Out op in progress(ch=%d)"), 
        __FUNCTION__, connectionContext()->connid()));
    }

    return rc;
  }

  int Connection::completeActiveOp(op::ConnectionOutputPtr const & op)
  {
    NI_PROFILE_BLOCK(__FUNCTION__);

    ACE_Guard<ACE_Thread_Mutex> lock(outQueueMutex_);
    NI_ASSERT(op == activeOutOp_, "op for comletition have to be active operation");

    op::ChannelOpPtr pcop = op->op();
    op::ChannelOpPtr tmpop = pcop;
    do
    {
      tmpop->channel()->completeOp(tmpop);
      tmpop = tmpop->next();
    }
    while (tmpop);

    activeOutOp_ = 0;
    return startOutOp_();
  }

  unsigned int Connection::id() const
  {
    return connid_;
  }

  int Connection::checkActivity(const ACE_Time_Value& last_op_time)
  {
    NI_PROFILE_BLOCK(__FUNCTION__);

    ACE_Time_Value now = ACE_OS::gettimeofday();

    ChannelContainer channels;
    {
      ACE_Guard<ACE_Thread_Mutex> lock(channelsMutex_);
      channels = channels_;
    }

    ChannelContainer::ChannelsMapT::iterator it = channels.map_.begin();
    ChannelContainer::ChannelsMapT::iterator eit = channels.map_.end();
    for(; it != eit; ++it)
    {
      it->second->checkActivity(now);
    }

    if (!currentOpenChannelOp() && !channels2open() && !channelCount())
    {
      ACE_ERROR((LM_INFO, ACE_TEXT("[TL] Close connection due to there are no active channels(ch=%d)"), 
        connectionContext()->connid()));
      return -1;
    }

    return 0;
  }

  int Connection::onTimeout(const void *arg)
  {
    NI_PROFILE_BLOCK(__FUNCTION__);

    int rc = cancelOpenChannel(arg);
    if (rc < 0)
    {
      ACE_ERROR((LM_ERROR, ACE_TEXT("%s. cancelOpenChannel failed(ch=%d)"), 
        __FUNCTION__, connectionContext()->connid()));
    }

    return rc;
  }

  inline
  op::OpenChannelPtr Connection::popCurrentOpenChannelOp()
  {
    NI_PROFILE_BLOCK(__FUNCTION__);

    ACE_Guard<ACE_Thread_Mutex> lock(openChannelsMutex_);
    if (currentOpenChannelOp_)
    {
      op::OpenChannelPtr tmp = currentOpenChannelOp_;
      currentOpenChannelOp_ = 0;
      return tmp;
    }

    return currentOpenChannelOp_;
  }

  void Connection::cancelWaitingChannels4Opening()
  {
    NI_PROFILE_FUNCTION

    ACE_Guard<ACE_Thread_Mutex> lock(openChannelsMutex_);
    TL::IChannelInternalSP spchnl = dequeueChannel2Open_();
    while (TL::IsValid(spchnl))
    {
      Transport::ChannelAddr caddr;
      spchnl->onOpenChannel(false, caddr);
      spchnl = dequeueChannel2Open_();
    }
  }

  void Connection::closeOpenedChannels_()
  {
    NI_PROFILE_FUNCTION

    ACE_Guard<ACE_Thread_Mutex> lock(channelsMutex_);
    for (ChannelContainer::ChannelsMapT::iterator it = channels_.map_.begin(); it != channels_.map_.end(); ++it)
    {
      it->second->close(false);
    }
    channels_.clear();
  }

  bool Connection::registerPipeId_(Transport::TClientId const & cid, Transport::TPipeId pid)
  {
    PipesT & pipes = reservedPipes_[cid];
    PipesT::iterator it = std::find(pipes.begin(), pipes.end(), pid);
    if (it != pipes.end())
      return false;

    pipes.push_back(pid);
    return true;
  }

  bool Connection::unregisterPipeId_(Transport::TClientId const & cid, Transport::TPipeId const & pid)
  {
    PipesT & pipes = reservedPipes_[cid];
    PipesT::iterator it = std::find(pipes.begin(), pipes.end(), pid);
    if (it != pipes.end())
    {
      pipes.erase(it);
      return true;
    }

    return false;
  }



  Connection::StatusT Connection::status() const
  {
    NI_PROFILE_BLOCK(__FUNCTION__);
    ACE_Guard<ACE_Thread_Mutex> lock(stsMutex_);
    return status_();
  }



  void Connection::status(Connection::StatusT sts)
  {
    NI_PROFILE_BLOCK(__FUNCTION__);
    {
      ACE_Guard<ACE_Thread_Mutex> lock(stsMutex_);
      status_(sts);
    }

    if (CONNECTED == sts)
      connid_ = spconnctx_->connid();
  }



  op::OpenChannelPtr const & Connection::currentOpenChannelOp() const
  {
    NI_PROFILE_FUNCTION
    ACE_Guard<ACE_Thread_Mutex> lock(openChannelsMutex_);
    return currentOpenChannelOp_;
  }



  unsigned int Connection::channels2open() const
  {
    NI_PROFILE_FUNCTION
    ACE_Guard<ACE_Thread_Mutex> lock(openChannelsMutex_);
    return (unsigned int)channels2open_.size();
  }
}
