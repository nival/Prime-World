#include "naio/stdafx.h"
#include "naio/ChannelManager.h"
#include "naio/ChannelContext.h"
#include "naio/ConnectionContext.h"

namespace naio
{
  ChannelManager::ChannelManager(const ACE_TCHAR * name,
                                Terabit::IOThreadPool &    task,
                                Terabit::AsynchChannelFactory &  channelFactory)
    :Terabit::ChannelManager(name, task, channelFactory),
    read_block_size_(0),
    so_rcvbuf_(-1),
    disableNagleAlgorithm_(-1),
    so_sndbuf_(-1),
    so_keepalive_(-1),
    logWrittenBytes_(0)
  {
  }

  ChannelManager::~ChannelManager()
  {
  }

  ChannelContextStrongPtr ChannelManager::RegisterChannel(Terabit::AsynchChannel* chnl,
    ConnectionContextStrongPtr const & spconn)
  {
    NI_PROFILE_BLOCK(__FUNCTION__);

    ChannelContextStrongPtr spctx(new ChannelContext(chnl, spconn));
    spctx->setWeakPtr(spctx);
    spconn->channelContext(spctx);

    ACE_Guard<ACE_Thread_Mutex> lock(channelsMutex_);
    if (!channels_.insert(std::make_pair(chnl->get_id(), spctx)).second)
      return ChannelContextStrongPtr();

    return spctx;
  }

  void ChannelManager::UnregisterChannel(int chnlid)
  {
    NI_PROFILE_BLOCK(__FUNCTION__);

    ACE_Guard<ACE_Thread_Mutex> lock(channelsMutex_);
    ChannelsMapT::iterator it = channels_.find(chnlid);
    if (it != channels_.end())
    {
      it->second.reset();
      channels_.erase(it);
    }
  }
}
