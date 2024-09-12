#pragma once
#include <naio/ProtocolHandler.h>
#include <naio/ConnectionContext.h>
#include "NLServerHandler.h"
#include "mballocator/MessageBlockFactory.h"

namespace NetworkLayer
{
  namespace NL = NetworkLayer;

  class Connection;

  class ProtocolHandler : public naio::IProtocolHandler
  {
  public:
    static const unsigned short  HEADER_SIZE = sizeof(unsigned short);
    static const unsigned short  MAX_PACKET_SIZE = 0xFFFF;
    static const unsigned short  MAX_DATA_SIZE = MAX_PACKET_SIZE - HEADER_SIZE;

  public:
    ProtocolHandler();
    ~ProtocolHandler();

  public:
    virtual naio::StatusT OnOpenConnection(bool success, bool isactive, naio::ConnectionContextStrongPtr const & spconn);
    virtual naio::StatusT HandleInput(size_t length, const char *data, size_t& readBytes, 
      naio::ConnectionContextStrongPtr const & spconn, Terabit::MessageBlockFactory& outmbf, ACE_Message_Block*& poutmb);
    virtual void PostHandleInput(naio::StatusT const & sts, naio::ConnectionContextStrongPtr const & spconn);
    virtual naio::StatusT HandleOutput(size_t length, const char *data, bool preallocated, 
      naio::ConnectionContextStrongPtr const & spconn, Terabit::MessageBlockFactory& outmbf, ACE_Message_Block*& poutmb);
    virtual naio::StatusT HandleOutput(ACE_Message_Block* pmb, naio::ConnectionContextStrongPtr const & spconn, 
      Terabit::MessageBlockFactory& outmbf, ACE_Message_Block*& poutmb);
    virtual naio::StatusT OnUserOperation(naio::OperationPtr const & op, naio::ConnectionContextStrongPtr const & spconn,
      Terabit::MessageBlockFactory& outmbf, ACE_Message_Block*& poutmb);
    virtual void UserOperationPostHandler(naio::StatusT const & sts, naio::OperationPtr const & op, naio::ConnectionContextStrongPtr const & spconn);
    virtual void OnCloseConnection(naio::ConnectionContextStrongPtr const & spconn);
    virtual int CheckActivity(naio::ConnectionContextStrongPtr const & spconn, const ACE_Time_Value& last_op_time);
    virtual int OnTimeout(naio::ConnectionContextStrongPtr const & spconn, const void *arg);

    virtual Terabit::MessageBlockFactory* getMessageBlockFactory() const;

  private:
    NL::ServerHandler realHandler_;
    TransportLayer::MessageBlockFactory mbf_;
  };

}
