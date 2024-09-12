#pragma once
#include <IOTerabit/RefCntProtocol.h>
#include "naio/Types.h"
#include "naio/ProtocolHandler.h"

namespace naio
{
  class ChannelManager;
  class Operation;
  class IProtocolHandler;

  struct ConnectionSettings;

  class BaseProtocol : public Terabit::RefCntProtocol
  {
    friend class Channel;
    friend class BaseProtocolFactory;

    enum State
    {
      ST_INIT,
      ST_OPENED,
      ST_CLOSED
    };

  protected:
    struct OperationChain
    {
      OperationChain()
        :first_(0), last_(0), count_(0)
      {}
      OperationChain(Operation* first, Operation* last)
        :first_(first), last_(last)
      {
        if (first_)
          count_ = 1;
      }

      Operation* first_;
      Operation* last_;
      unsigned int count_;
    };

  public:
    BaseProtocol(Terabit::ProtocolFactory& factory);
    virtual ~BaseProtocol();

    virtual void on_reset();

    void* act() const;
    void act(void * p);

    void set_message_block_factory(Terabit::MessageBlockFactory* mbf);
    virtual Terabit::MessageBlockFactory* get_message_block_factory() const;

  protected:
    //  Terabit::Protocol interface
    virtual int on_channel_up (Terabit::AsynchChannel *channel);
    virtual int on_read_completed (Terabit::AsynchChannel *channel, const char *data, size_t length);
    virtual void on_channel_done(Terabit::AsynchChannel *channel);
    virtual int check_activity (Terabit::AsynchChannel *channel, const ACE_Time_Value&  last_op_time);
    virtual int on_timeout (Terabit::AsynchChannel *channel, const void *arg);

    //  new Protocol interface
    virtual int on_user_operation(Terabit::AsynchChannel *channel, OperationPtr const & op);

  protected:
    ChannelManager* manager(Terabit::AsynchChannel *channel) const;
    int applyConnectionSettings(Terabit::AsynchChannel *channel, ConnectionSettings const & cs);

    void state_(State st);
    State state_() const;

  protected:
    Terabit::ProtocolFactory& factory_;
    void* act_;
    naio::IProtocolHandlerSP ph_;
    Terabit::MessageBlockFactory* mbf_;
    ChannelContextWeakPtr wpcc_;
    ACE_Atomic_Op<ACE_Thread_Mutex, unsigned long> st_;
    unsigned int log_written_bytes_;
    unsigned int written_bytes_;
    unsigned long long total_written_bytes_;
  };

  inline
  void* naio::BaseProtocol::act() const
  {
    return act_;
  }

  inline
  void naio::BaseProtocol::act(void* p)
  {
    act_ = p;
  }

  inline
  void naio::BaseProtocol::state_(State st)
  {
    st_ = st;
  }

  inline
  naio::BaseProtocol::State naio::BaseProtocol::state_() const
  {
    return (State)st_.value();
  }

  inline
  void BaseProtocol::set_message_block_factory(Terabit::MessageBlockFactory* mbf)
  {
    mbf_ = mbf;
  }
}
