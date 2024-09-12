#pragma once

#include <ace/Atomic_Op.h>

class TRB_Handler;

namespace Relay
{

class PeerContext;

namespace OperationType
{
  enum Enum
  {
    OPEN_CHNL_2_SVC = 0,
    CLOSE_CHNL_2_SVC = 1,
    C2S_TRANSMISSION = 2,
    C2C_TRANSMISSION = 4,
    //  START_OPERATION = 5,
    C2S_PING = 6,
    OPEN_CHNL_2_CLIENT = 7,
    _COUNT_,
    INVALID = static_cast< unsigned int >(-1)
  };
}

class Operation
{
public:
  Operation(OperationType::Enum t);
  virtual ~Operation();

public:
  virtual void Close();

public:
  OperationType::Enum type() const
  {
    return type_;
  }

  Operation* next() const
  {
    return next_;
  }

  Operation* next(Operation* op)
  {
    Operation* n = next_;
    next_ = op;
    return n;
  }

  void addRef();
  void releaseRef();
  long refCount() const;

protected:
  int PostCompletion(TRB_Handler* handler);
  int PostCompletion(PeerContext* context);

private:
  OperationType::Enum type_;
  Operation* next_;

  ACE_Atomic_Op<ACE_Thread_Mutex, long> refCount_;
};

inline
long Operation::refCount() const
{
  return refCount_.value();
}


template <typename T>
class AutoOpPtr
{
public:
  AutoOpPtr(T* op)
    :op_(op)
  {}

  ~AutoOpPtr()
  {
    if (op_)
      op_->releaseRef();
  }

  T* release()
  {
    T* op = op_;
    op_ = 0;
    return op;
  }

  T* operator-> () const
  {
    return op_;
  }

  T* get() const
  {
    return op_;
  }

private:
  T* op_;
};

#include "Ptr.h"
}
