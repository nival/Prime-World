#include "mballocator/stdafx.h"
#include "mballocator/MessageBlock.h"

namespace TransportLayer
{
  MessageBlock::MessageBlock(size_t size, MBType::Enum _type, unsigned long long _tag)
    :ACE_Message_Block(size),
    type_(_type),
    tag_(_tag)
  {
  }

  MessageBlock::~MessageBlock()
  {
    NI_PROFILE_BLOCK(__FUNCTION__);
  }
}
