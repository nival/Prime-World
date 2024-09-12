#pragma once
#include <IOTerabit/MessageBlockFactory.h>
#include <mballocator/MessageBlockAllocator.h>
#include <mballocator/Types.h>

namespace TransportLayer
{
  namespace TL = TransportLayer;

  class MessageBlockFactory : public Terabit::MessageBlockFactory
  {
  public:
    MessageBlockFactory(char const * name, unsigned int dumpstep = 0);
    ~MessageBlockFactory();

    //  Terabit::MessageBlockFactory
    virtual ACE_Message_Block *alloc_msg (size_t length);
    virtual ACE_Message_Block* alloc_msg (size_t length, unsigned long long _msgtag);
    virtual void free_msg (ACE_Message_Block * mb);

    ACE_Message_Block* alloc_msg (size_t length, MBType::Enum _type, unsigned long long _msgtag = 0);

    void tag(int t);
    int tag() const;

    void threshold(MBType::Enum _type, int _threshold, unsigned long long const * _tag_filter = 0, int _tag_filter_size = 0, bool _logEach = false);
    int  threshold(MBType::Enum _type) const;

  private:
    MessageBlockAllocator allocator_;
    long long allocCounter_;
    unsigned int dumpstep_;
    int tag_;
  };

  inline
  void MessageBlockFactory::tag(int t)
  {
    tag_ = t;
  }

  inline
  int MessageBlockFactory::tag() const
  {
    return tag_;
  }

  inline
  void MessageBlockFactory::threshold(MBType::Enum _type, int _threshold, unsigned long long const * _tag_filter, int _tag_filter_size, bool _logEach)
  {
    allocator_.threshold(_type, _threshold, _tag_filter, _tag_filter_size, _logEach);
  }

  inline
  int MessageBlockFactory::threshold(MBType::Enum _type) const
  {
    allocator_.threshold(_type);
  }
}
