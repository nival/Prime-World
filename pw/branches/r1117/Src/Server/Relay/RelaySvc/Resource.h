#pragma once
#include "Types.h"

namespace Relay
{
  class Resource
  {
  public:

    struct State
    {
      enum Enum
      {
        INIT   = 0x0000,   // JUST CREATED
        OPENED = 0x0001,   // OPERATIONAL
        CLOSED = 0x0002    // CLOSED
      };
    };

  public:
    Resource()
      :state_(State::INIT)
    {}

    Resource(State::Enum _state)
      :state_(_state)
    {}

    int open();
    bool isopen() const;
    bool close();
    bool isclosed() const;
    State::Enum state() const;

  private:
    ACE_Atomic_Op<ACE_Thread_Mutex, unsigned long> state_;
  };

  inline
  bool Resource::isopen() const
  {
    return (state_ == (unsigned long)State::OPENED);
  }

  inline
  bool Resource::isclosed() const
  {
    return (state_ == (unsigned long)State::CLOSED);
  }

  inline
  Resource::State::Enum Resource::state() const
  {
    return State::Enum(state_.value());
  }

  inline
  int Resource::open()
  {
    if (state_ != State::INIT)
      return -1;

    state_ = State::OPENED;
    return 0;
  }

  inline
  bool Resource::close()
  {
    if (state_ == State::CLOSED)
      return false;

    state_ = State::CLOSED;
    return true;
  }
}
