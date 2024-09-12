#include "stdafx.h"
#include "NLProtocolHandler.h"
#include <ace/Log_Msg.h>
#include <IOTerabit/MessageBlockFactory.h>
#include <naio/Operation.h>

namespace NetworkLayer
{
  ProtocolHandler::ProtocolHandler()
    :mbf_("")
  {
  }

  ProtocolHandler::~ProtocolHandler()
  {
  }

  naio::StatusT 
  ProtocolHandler::OnOpenConnection(bool success, bool isactive, naio::ConnectionContextStrongPtr const & spconnctx)
  {
    return naio::status::SUCCESS;
  }

  naio::StatusT ProtocolHandler::HandleInput(size_t length, const char *data, size_t& readBytes, 
    naio::ConnectionContextStrongPtr const & spconn, 
    Terabit::MessageBlockFactory& outmbf, ACE_Message_Block*& poutmb)
  {
    ACE_DEBUG((LM_TRACE, ACE_TEXT("(%t)%T %s(l=%d)"), __FUNCTION__, length));
    return realHandler_.getNetworkHandler().HandleInput(length, data, readBytes, spconn, outmbf, poutmb);
  }

  void ProtocolHandler::PostHandleInput(naio::StatusT const & sts, naio::ConnectionContextStrongPtr const & spconn)
  {

  }

  naio::StatusT ProtocolHandler::HandleOutput(size_t length, const char *data, bool /*preallocated*/, naio::ConnectionContextStrongPtr const & /*spconn*/, 
    Terabit::MessageBlockFactory& outmbf, ACE_Message_Block*& poutmb)
  {
    ACE_DEBUG((LM_TRACE, ACE_TEXT("(%t)%T %s(l=%d)"), __FUNCTION__, length));

    return naio::status::SUCCESS;
  }

  naio::StatusT ProtocolHandler::HandleOutput(ACE_Message_Block* pmb, naio::ConnectionContextStrongPtr const & spconn, 
    Terabit::MessageBlockFactory& outmbf, ACE_Message_Block*& poutmb)
  {
    return naio::status::SUCCESS;
  }

  naio::StatusT ProtocolHandler::OnUserOperation(naio::OperationPtr const & op, 
    naio::ConnectionContextStrongPtr const & spconnctx,
    Terabit::MessageBlockFactory& outmbf, ACE_Message_Block*& poutmb)
  {
    naio::StatusT sts = naio::status::FAIL;
    return sts;
  }

  void ProtocolHandler::UserOperationPostHandler(naio::StatusT const & sts, naio::OperationPtr const & op, 
    naio::ConnectionContextStrongPtr const & spconn)
  {
  }

  void ProtocolHandler::OnCloseConnection(naio::ConnectionContextStrongPtr const & spconnctx)
  {
    ACE_DEBUG((LM_TRACE, ACE_TEXT("(%t)%T [TL] %s"), __FUNCTION__));
  }

  int ProtocolHandler::CheckActivity(naio::ConnectionContextStrongPtr const & spconn, const ACE_Time_Value& last_op_time)
  {
    return 0;
  }

  int ProtocolHandler::OnTimeout(naio::ConnectionContextStrongPtr const & spconn, const void *arg)
  {
    return 0;
  }

  Terabit::MessageBlockFactory* ProtocolHandler::getMessageBlockFactory() const
  {
    return (Terabit::MessageBlockFactory*)(&mbf_);
  }
}
