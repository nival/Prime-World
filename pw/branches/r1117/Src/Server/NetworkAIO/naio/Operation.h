#pragma once
#include "naio/Types.h"
#include "naio/Ptr.h"
#include "System/InlineProfiler.h"

class TRB_Handler;

namespace naio
{
  class ChannelContext;

  typedef int OperationType;

  class Operation
  {
  public:
    enum
    {
      OP_NOP = 0,
      OP_OPEN_CONNECTION = 1,
      OP_CLOSE_CONNECTION = 2,
      OP_OPEN_ACCEPT = 3,
      OP_CLOSE_ACCEPT = 4,
      OP_SEND_DATA = 5,
      OP_RECEIVE_DATA = 6,
      OP_USER = 0xFF,
      OP_INVALID = 0xFFFFFFFF,
    };

  public:
    Operation(OperationType t, ConnectionContextStrongPtr const & spctx);
    virtual ~Operation();

  public:
    int Post();

  public:
    OperationType type() const
    {
      return type_;
    }

    Ptr<Operation> const & next() const
    {
      return next_;
    }

    Ptr<Operation> next(Ptr<Operation> const & op)
    {
      Ptr<Operation> n = next_;
      next_ = op;
      return n;
    }

    void addRef();
    void releaseRef();

    long refCount() const;

  protected:
    int PostCompletion(TRB_Handler* handler);

  protected:
    OperationType type_;
    Ptr<Operation> next_;
    ConnectionContextStrongPtr spctx_;

    ACE_Atomic_Op<ACE_Thread_Mutex, long> refCount_;
  };

  inline
  void Operation::addRef()
  {
    NI_PROFILE_BLOCK(__FUNCTION__);
    ++refCount_;
  }

  inline
  void Operation::releaseRef()
  {
    NI_PROFILE_BLOCK(__FUNCTION__);

    long count = --refCount_;
    if (count <= 0)
    {
      NI_ASSERT(0 == count, "Counter MUST be 0");
      if (0 == count)
      {
        NI_PROFILE_BLOCK("delete this");
        delete this;
      }
    }
  }

  typedef Ptr< Operation > OperationPtr;
}
