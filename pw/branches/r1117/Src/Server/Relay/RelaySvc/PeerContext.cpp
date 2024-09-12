#pragma warning( disable : 4996)
#include "stdafx.h"
#include "PeerContext.h"

namespace Relay
{

int PeerContext::open(ContextId const & id, Terabit::AsynchChannelPtr const & chnl)
{
  NI_PROFILE_BLOCK(__FUNCTION__);

  ACE_ASSERT(chnl);
  ACE_Guard<ACE_Thread_Mutex> lock(mutex_);
  id_ = id;
  channel_ = chnl;
  channelId_ = channel_->get_id();
  Resource::open();
  return 0;
}

bool PeerContext::close()
{
  NI_PROFILE_BLOCK(__FUNCTION__);

  ACE_Guard<ACE_Thread_Mutex> lock(mutex_);
  return Resource::close();
}

ACE_Message_Block* PeerContext::allocMsg(size_t sz)
{
  NI_PROFILE_BLOCK(__FUNCTION__);

  ACE_Guard<ACE_Thread_Mutex> lock(mutex_);

  NI_PROFILE_BLOCK("inside mutex");
  if (isopen())
    return channel_->alloc_msg(sz);

  return 0;
}

void PeerContext::freeMsg(ACE_Message_Block* mb)
{
  NI_PROFILE_BLOCK(__FUNCTION__);

  ACE_Guard<ACE_Thread_Mutex> lock(mutex_);

  NI_PROFILE_BLOCK("inside mutex");
  if (isopen())
    channel_->free_msg(mb);
  else
    mb->release();
}

unsigned long PeerContext::disableRead()
{
  NI_PROFILE_BLOCK(__FUNCTION__);

  ACE_Guard<ACE_Thread_Mutex> lock(mutex_);
  unsigned long count = ++disableReadCount_;
  if (1 == count && channel_)
    channel_->disable_read();

  return count;
}

unsigned long PeerContext::enableRead()
{
  NI_PROFILE_BLOCK(__FUNCTION__);

  ACE_Guard<ACE_Thread_Mutex> lock(mutex_);
  unsigned long count = (--disableReadCount_);
  if (0 == count && channel_)
    channel_->enable_read();

  return count;
}

int PeerContext::registerPipeId_(Transport::TPipeId const & pid)
{
  PipeIdsT::iterator it = std::find(registeredPipeIds_.begin(), registeredPipeIds_.end(), pid);
  if (it != registeredPipeIds_.end())
    return -1;

  registeredPipeIds_.push_back(pid);
  return 0;
}

int PeerContext::unregisterPipeId_(Transport::TPipeId const & pid)
{
  PipeIdsT::iterator it = std::find(registeredPipeIds_.begin(), registeredPipeIds_.end(), pid);
  if (it != registeredPipeIds_.end())
  {
    registeredPipeIds_.erase(it);
    return 0;
  }

  return -1;
}

int PeerContext::registerPipeId(Transport::TPipeId const & pid)
{
  ACE_Guard<ACE_Thread_Mutex> lock(pipeidsMutex_);
  return registerPipeId_(pid);
}

int PeerContext::unregisterPipeId(Transport::TPipeId const & pid)
{
  ACE_Guard<ACE_Thread_Mutex> lock(pipeidsMutex_);
  return unregisterPipeId_(pid);
}

Transport::TPipeId PeerContext::generatePipeId()
{
  ACE_Guard<ACE_Thread_Mutex> lock(pipeidsMutex_);
  int rc = 0;
  Transport::TPipeId pid = Transport::EKnownPipeId::Invalid;
  do
  {
    pid = pipeIdGenerator_.Generate();
    if (Transport::EKnownPipeId::Invalid != pid)
      rc = registerPipeId_(pid);
    else
      rc = 0;
  }
  while (rc < 0);

  return pid;
}

void PeerContext::freePipeId(Transport::TPipeId const & pid)
{
  ACE_Guard<ACE_Thread_Mutex> lock(pipeidsMutex_);
  pipeIdGenerator_.Release(pid);

  unregisterPipeId_(pid);
}

}
