#include "mballocator/stdafx.h"
#include "mballocator/MessageBlockFactory.h"

namespace TransportLayer
{
  MessageBlockFactory::MessageBlockFactory(char const * name, unsigned int dumpstep)
    :allocator_(name),
    allocCounter_(0),
    dumpstep_(dumpstep),
    tag_(-1)
  {
  }

  MessageBlockFactory::~MessageBlockFactory()
  {
  }

  ACE_Message_Block* MessageBlockFactory::alloc_msg (size_t length, MBType::Enum _type, unsigned long long _msgtag)
  {
    NI_PROFILE_BLOCK(__FUNCTION__);

    ACE_Message_Block* mb = allocator_.alloc_msg(length, _type, _msgtag);
    if (mb)
    {
      ++allocCounter_;
      if (dumpstep_ && 0 == allocCounter_ % dumpstep_)
        allocator_.dump(tag());
    }

    return mb;
  }

  ACE_Message_Block* MessageBlockFactory::alloc_msg (size_t length)
  {
    return alloc_msg(length, MBType::NOTYPE_BLOCK);
  }

  ACE_Message_Block* MessageBlockFactory::alloc_msg (size_t length, unsigned long long _msgtag)
  {
    return alloc_msg(length, MBType::NOTYPE_BLOCK, _msgtag);
  }

  void MessageBlockFactory::free_msg (ACE_Message_Block * mb)
  {
    NI_PROFILE_BLOCK(__FUNCTION__);

    allocator_.free_msg(mb);
  }
}
