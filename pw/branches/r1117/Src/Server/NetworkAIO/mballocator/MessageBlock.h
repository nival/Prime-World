#pragma once
#include <ace/Message_Block.h>
#include <mballocator/MessageBlockType.h>

namespace TransportLayer
{
  namespace TL = TransportLayer;

  class MessageBlock : public ACE_Message_Block
  {
  public:
    MessageBlock(size_t size, MBType::Enum type = MBType::NOTYPE_BLOCK, unsigned long long _tag = 0);
    ~MessageBlock();

  public:
    void alloctime(NHPTimer::STime const & time);
    NHPTimer::STime const & alloctime() const;

    void type(MBType::Enum _type);
    MBType::Enum type() const;
    void tag(unsigned long long _tag);
    unsigned long long tag() const;

  private:
    NHPTimer::STime   alloctime_;
    MBType::Enum      type_;
    unsigned long long tag_;
  };

  inline
  void MessageBlock::alloctime(NHPTimer::STime const & time)
  {
    alloctime_ = time;
  }

  inline
  NHPTimer::STime const & MessageBlock::alloctime() const
  {
    return alloctime_;
  }

  inline
  void MessageBlock::type(MBType::Enum _type)
  {
    type_ = _type;
  }

  inline
  MBType::Enum MessageBlock::type() const
  {
    return type_;
  }

  inline
  void MessageBlock::tag(unsigned long long _tag)
  {
    tag_ = _tag;
  }

  inline
  unsigned long long MessageBlock::tag() const
  {
    return tag_;
  }
}
