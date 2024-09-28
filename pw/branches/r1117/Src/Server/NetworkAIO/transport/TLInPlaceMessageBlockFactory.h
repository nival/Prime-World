#pragma once
#include <transport/TLTypes.h>
#include <IOTerabit/MessageBlockFactory.h>

namespace TransportLayer
{
  namespace TL = TransportLayer;

  class InPlaceMessageBlockFactory : public Terabit::MessageBlockFactory
  {
  public:
    InPlaceMessageBlockFactory(char* place = 0, unsigned int size = 0);
    ~InPlaceMessageBlockFactory();

    void set_place(char* place, unsigned int size);

    virtual ACE_Message_Block *alloc_msg (size_t length);
    virtual void free_msg (ACE_Message_Block * mb);

    unsigned int bytes_allocated() const;

  private:
    unsigned int offset_;
    char* place_;
    unsigned int size_;
  };

  inline
  void InPlaceMessageBlockFactory::set_place(char* place, unsigned int size)
  {
    place_ = place;
    size_ = size;
    offset_ = 0;

    ACE_DEBUG((LM_TRACE, ACE_TEXT("%s(addr=%d sz=%d offset=%d)"), __FUNCTION__, place_, size_, offset_));
  }

  inline
  unsigned int InPlaceMessageBlockFactory::bytes_allocated() const
  {
    ACE_DEBUG((LM_TRACE, ACE_TEXT("%s(addr=%d sz=%d offset_=%d)"), __FUNCTION__, place_, size_, offset_));
    return offset_;
  }
}
