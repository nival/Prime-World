#pragma once
#include "naio/Types.h"
#include "naio/Operation.h"

class ACE_Message_Block;

namespace Terabit
{
  class MessageBlockFactory;
}

namespace naio
{
  class Operation;

  class IProtocolHandler
  {
    friend class IProtocolHandlerFactory;

  public:
    virtual StatusT OnOpenConnection(bool success, bool isactive, ConnectionContextStrongPtr const & spconn) = 0;
    virtual StatusT HandleInput(size_t length, const char *data, size_t& readBytes, 
                          ConnectionContextStrongPtr const & spconn, Terabit::MessageBlockFactory& outmbf, ACE_Message_Block*& poutmb) = 0;
    virtual void PostHandleInput(naio::StatusT const & sts, ConnectionContextStrongPtr const & spconn) = 0;
    virtual StatusT HandleOutput(size_t length, const char *data, bool preallocated, 
      ConnectionContextStrongPtr const & spconn, Terabit::MessageBlockFactory& outmbf, ACE_Message_Block*& poutmb) = 0;
    virtual StatusT HandleOutput(ACE_Message_Block* pmb, ConnectionContextStrongPtr const & spconn, 
      Terabit::MessageBlockFactory& outmbf, ACE_Message_Block*& poutmb) = 0;
    virtual StatusT OnUserOperation(OperationPtr const & op, ConnectionContextStrongPtr const & spconn,
      Terabit::MessageBlockFactory& outmbf, ACE_Message_Block*& poutmb) = 0;
    virtual void UserOperationPostHandler(naio::StatusT const & sts, OperationPtr const & op, ConnectionContextStrongPtr const & spconn) = 0;
    virtual void OnCloseConnection(ConnectionContextStrongPtr const & spconn) = 0;
    virtual int CheckActivity(ConnectionContextStrongPtr const & spconn, const ACE_Time_Value& last_op_time) = 0;
    virtual int OnTimeout(ConnectionContextStrongPtr const & spconn, const void *arg) = 0;

    virtual Terabit::MessageBlockFactory* getMessageBlockFactory() const = 0;

  private:
    void* userContext_;
  };

  class IProtocolHandler;
  typedef ACE_Strong_Bound_Ptr<naio::IProtocolHandler, ACE_SYNCH_MUTEX> IProtocolHandlerStrongPtr;
  typedef ACE_Strong_Bound_Ptr<naio::IProtocolHandler, ACE_SYNCH_MUTEX> IProtocolHandlerSP;
  typedef ACE_Weak_Bound_Ptr<naio::IProtocolHandler, ACE_SYNCH_MUTEX> IProtocolHandlerWeakPtr;
  typedef ACE_Weak_Bound_Ptr<naio::IProtocolHandler, ACE_SYNCH_MUTEX> IProtocolHandlerWP;

  class IProtocolHandlerFactory
  {
  public:
    virtual IProtocolHandlerSP CreateProtocolHandler(void const * usercontext) = 0;
    virtual void DestroyProtocolHandler(IProtocolHandlerSP & ph) = 0;

  protected:
    void setUserContext(IProtocolHandlerSP const & ph, void const * usercontext) const
    {
      ph->userContext_ = const_cast<void*>(usercontext);
    }
  };
}
