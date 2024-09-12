#pragma once

namespace chat
{
  class Context : public IBaseInterfaceMT
  {
    NI_DECLARE_CLASS_1( Context, IBaseInterfaceMT );

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

    Context()
      :st_(State::INIT)
    {
    }

    ~Context() {}

  public:
    int open();
    bool close();
    bool isclosed() const;

    State::Enum state() const;

  private:
    int state(State::Enum _st);

  private:
    State::Enum st_;
  };

  inline
  int Context::state(State::Enum _st)
  {
    if (st_ == _st)
      return 1;

    st_ = _st;
    return 0;
  }

  inline
  int Context::open()
  {
    return state(State::OPENED);
  }

  inline
  bool Context::close()
  {
    return (0 == state(State::CLOSED));
  }

  inline
  bool Context::isclosed() const
  {
    return (State::CLOSED == state());
  }

  inline
  Context::State::Enum Context::state() const
  {
    return st_;
  }
}
