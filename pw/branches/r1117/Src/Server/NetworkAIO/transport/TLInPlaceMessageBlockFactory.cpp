#include "transport/stdafx.h"
#include "transport/TLInPlaceMessageBlockFactory.h"
#include <mballocator/MessageBlockFactory.h>

namespace TransportLayer
{
  InPlaceMessageBlockFactory::InPlaceMessageBlockFactory(char* place, unsigned int size)
    :offset_(0),
    place_(place),
    size_(size)
  {
    ACE_DEBUG((LM_TRACE, ACE_TEXT("%s(addr=%d sz=%d)"), __FUNCTION__, place_, size_));
  }

  InPlaceMessageBlockFactory::~InPlaceMessageBlockFactory()
  {
    ACE_DEBUG((LM_TRACE, ACE_TEXT("%s(addr=%d sz=%d offset=%d)"), __FUNCTION__, place_, size_, offset_));
  }

  ACE_Message_Block* InPlaceMessageBlockFactory::alloc_msg (size_t length)
  {
    NI_PROFILE_BLOCK(__FUNCTION__);

    ACE_DEBUG((LM_TRACE, ACE_TEXT("%s(offset=%d l=%d)"), __FUNCTION__, offset_, length));

    ACE_Message_Block* mb = 0;
    if (size_ - offset_ >= length)
    {
      char* addr = place_ + offset_;
      mb = new ACE_Message_Block(addr, length);
      if (mb)
        offset_+=length;
    }
    else
    {
      ACE_ERROR((LM_WARNING, ACE_TEXT("%s. FAILED(size=%d offset=%d length=%d)"), 
        __FUNCTION__, size_, offset_, length));
    }

    if (mb)
      ACE_DEBUG((LM_TRACE, ACE_TEXT("%s:out(mb=%d mb_data_addr=%d sz=%d)"), __FUNCTION__, mb, mb->base(), mb->size()));
    else
      ACE_DEBUG((LM_TRACE, ACE_TEXT("%s:out(mb=%d)"), __FUNCTION__, mb));
    return mb;
  }

  void InPlaceMessageBlockFactory::free_msg (ACE_Message_Block * mb)
  {
    NI_PROFILE_BLOCK(__FUNCTION__);

    ACE_DEBUG((LM_TRACE, ACE_TEXT("%s(mb=%d mb_data_addr=%d sz=%d l=%d)"), __FUNCTION__, mb, mb->base(), mb->size(), mb->length()));
    if (mb)
      mb->release();
  }
}
