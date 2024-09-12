#include "transport/stdafx.h"
#include "transport/TLProtocolHandler.h"
#include <ace/Log_Msg.h>
#include "transport/TLConnection.h"
#include <IOTerabit/MessageBlockFactory.h>
#include "transport/TLConnectionManager.h"
#include <naio/ChannelContext.h>
#include "transport/TLChannel.h"
#include "transport/TLOpenChannelOp.h"
#include "transport/TLPingChannelOp.h"
#include "transport/TLConnectionOutputOp.h"
#include "transport/TLAddRecipientOp.h"
#include "transport/TLRemoveRecipientOp.h"

namespace TransportLayer
{
  ProtocolHandler::ProtocolHandler(Transport::MessageFactory* pMsgFactory, TL::ChannelFactory* chnlFactory,
    TL::MessageBlockFactorySP const & spmbf, bool packAddress)
    :realHandler_(pMsgFactory, chnlFactory, packAddress),
    spmbf_(spmbf)
  {
    NI_ASSERT(!spmbf.null(), "");
  }

  ProtocolHandler::~ProtocolHandler()
  {
  }

  naio::StatusT 
  ProtocolHandler::OnOpenConnection(bool success, bool isactive, naio::ConnectionContextStrongPtr const & spconnctx)
  {
    NI_PROFILE_BLOCK(__FUNCTION__);

    ACE_DEBUG((LM_TRACE, ACE_TEXT("%s"), __FUNCTION__));

    if (isactive)
    {
      TL::ConnectionSP spconn = connection(spconnctx);
      if (TL::IsValid(spconn))
      {
        TL::ConnectionManagerSP spmngr = spconn->manager();
        spmngr->OnConnectionEstablished(success, isactive, spconnctx, spmbf_);

        if (success)
        {
          if (spconn->startOpenQueuedChannel() < 0)
            return naio::status::FAIL;
        }
        else
        {
          spconn->cancelOpeningChannels();
        }

        return naio::status::SUCCESS;
      }
      else
      {
        return naio::status::FAIL;
      }
    }
    else
    {
      //  accepted connection
      TL::ConnectionManagerSP spmngr = connectionMngr(spconnctx);
      spmngr->OnConnectionEstablished(success, isactive, spconnctx, spmbf_);
      return naio::status::SUCCESS;
    }
  }

  naio::StatusT ProtocolHandler::HandleInput(size_t length, const char *data, size_t& readBytes, 
    naio::ConnectionContextStrongPtr const & spconnctx, 
    Terabit::MessageBlockFactory& outmbf, ACE_Message_Block*& poutmb)
  {
    NI_PROFILE_BLOCK(__FUNCTION__);

    ACE_DEBUG((LM_TRACE, ACE_TEXT("%s(ch=%d l=%d)"), __FUNCTION__, spconnctx->channelContext()->channel()->get_id(), length));
    return realHandler_.getNetworkHandler().HandleInput(length, data, readBytes, spconnctx, outmbf, poutmb);
  }

  void ProtocolHandler::PostHandleInput(naio::StatusT const & sts, naio::ConnectionContextStrongPtr const & spconnctx)
  {
    NI_PROFILE_BLOCK(__FUNCTION__);

    ACE_DEBUG((LM_TRACE, ACE_TEXT("%s(ch=%d sts=%d)"), __FUNCTION__, spconnctx->channelContext()->channel()->get_id(), sts));

    TL::ConnectionSP spconn = connection(spconnctx);
    if (TL::IsValid(spconn))
    {
      spconn->completeAcceptChannels();
    }
    else
    {
      ACE_ERROR((LM_ERROR, ACE_TEXT("%s. Connection is invalid(ch=%d)"), __FUNCTION__, 
        spconnctx->channelContext()->channel()->get_id()));
    }
  }

  naio::StatusT ProtocolHandler::HandleOutput(size_t length, const char *data, bool /*preallocated*/, naio::ConnectionContextStrongPtr const & /*spconn*/, 
    Terabit::MessageBlockFactory& outmbf, ACE_Message_Block*& poutmb)
  {
    ACE_DEBUG((LM_TRACE, ACE_TEXT("%s(l=%d)"), __FUNCTION__, length));

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
    NI_PROFILE_BLOCK(__FUNCTION__);

    naio::StatusT sts = naio::status::FAIL;

    switch(op->type())
    {
    case op::OPEN_CHANNEL:
      {
        NI_PROFILE_BLOCK("op::OPEN_CHANNEL");
        op::OpenChannel* ocop(static_cast<op::OpenChannel*>(op.get()));
        sts = ocop->execute(&realHandler_, outmbf, poutmb);
      }
      break;

    case op::PING_CHANNEL:
      {
        NI_PROFILE_BLOCK("op::PING_CHANNEL");
        op::PingChannel* pingop(static_cast<op::PingChannel*>(op.get()));
        sts = pingop->execute(&realHandler_, outmbf, poutmb);
      }
      break;

    case op::ADD_RECIPIENT:
      {
        NI_PROFILE_BLOCK("op::ADD_RECIPIENT");
        op::AddRecipient* arop(static_cast<op::AddRecipient*>(op.get()));
        sts = arop->execute(&realHandler_, outmbf, poutmb);
      }
      break;

    case op::REMOVE_RECIPIENT:
      {
        NI_PROFILE_BLOCK("op::REMOVE_RECIPIENT");
        op::RemoveRecipient* rrop(static_cast<op::RemoveRecipient*>(op.get()));
        sts = rrop->execute(&realHandler_, outmbf, poutmb);
      }
      break;

    case op::CONNECTION_OUTPUT:
      {
        NI_PROFILE_BLOCK("op::CONNECTION_OUTPUT");
        op::ConnectionOutput* coop(static_cast<op::ConnectionOutput*>(op.get()));
        sts = coop->execute(&realHandler_, outmbf, poutmb);
      }
      break;

    default:
      {
        NI_PROFILE_BLOCK("default");
        ACE_ERROR((LM_ERROR, ACE_TEXT("[TL] %s(op=%d). Unknown operation"), 
          __FUNCTION__, op->type()));
      }
    }

    return sts;
  }

  void ProtocolHandler::UserOperationPostHandler(naio::StatusT const & sts, naio::OperationPtr const & op, 
    naio::ConnectionContextStrongPtr const & spconn)
  {
    NI_PROFILE_BLOCK(__FUNCTION__);

    switch(op->type())
    {
    case op::OPEN_CHANNEL:
      {
        NI_PROFILE_BLOCK("op::OPEN_CHANNEL");
      }
      break;

    case op::PING_CHANNEL:
      {
        NI_PROFILE_BLOCK("op::PING_CHANNEL");
      }
      break;

    case op::CONNECTION_OUTPUT:
      {
        NI_PROFILE_BLOCK("op::CONNECTION_OUTPUT");
        op::ConnectionOutput* coop(static_cast<op::ConnectionOutput*>(op.get()));
        coop->complete();
      }
      break;

    default:
      {
        NI_PROFILE_BLOCK("default");
        ACE_ERROR((LM_ERROR, ACE_TEXT("[TL] %s(ch=%d op=%d). Unknown operation"), __FUNCTION__, op->type()));
      }
    }
  }

  void ProtocolHandler::OnCloseConnection(naio::ConnectionContextStrongPtr const & spconnctx)
  {
    NI_PROFILE_BLOCK(__FUNCTION__);

    ACE_DEBUG((LM_TRACE, ACE_TEXT("[TL] %s"), __FUNCTION__));

    TL::ConnectionSP spconn = connection(spconnctx);
    if (TL::IsValid(spconn))
    {
      NI_PROFILE_BLOCK("close");

      spconn->close(false);
      if (spconnctx->userContext())
        delete (reinterpret_cast<AsynchCompletionPointer<TL::Connection>*>(spconnctx->userContext()));
    }
  }

  TL::ConnectionSP ProtocolHandler::connection(naio::ConnectionContextStrongPtr const & spconn) const
  {
    return reinterpret_cast<AsynchCompletionPointer<TL::Connection>*>(spconn->userContext())->sp_;
  }

  TL::ConnectionManagerSP ProtocolHandler::connectionMngr(naio::ConnectionContextStrongPtr const & spconn) const
  {
    AsynchCompletionPointer2<TL::ChannelListenerInternal, TL::ConnectionManager>* acp2 = 
      reinterpret_cast<AsynchCompletionPointer2<TL::ChannelListenerInternal, TL::ConnectionManager>*>(spconn->userContext());
    return acp2->sp2_;
  }

  Terabit::MessageBlockFactory* ProtocolHandler::getMessageBlockFactory() const
  {
    return spmbf_.get();
  }

  int ProtocolHandler::CheckActivity(naio::ConnectionContextStrongPtr const & spconnctx, const ACE_Time_Value& last_op_time)
  {
    NI_PROFILE_BLOCK(__FUNCTION__);

    TL::ConnectionSP spconn = connection(spconnctx);
    if (!TL::IsValid(spconn))
    {
      ACE_ERROR((LM_ERROR, ACE_TEXT("%s. Connection is invalid(connid=%d)"), 
        __FUNCTION__, spconnctx->connid()));
      return -1;
    }

    return spconn->checkActivity(last_op_time);
  }

  int ProtocolHandler::OnTimeout(naio::ConnectionContextStrongPtr const & spconnctx, const void *arg)
  {
    NI_PROFILE_BLOCK(__FUNCTION__);

    TL::ConnectionSP spconn = connection(spconnctx);
    if (!TL::IsValid(spconn))
    {
      ACE_ERROR((LM_ERROR, ACE_TEXT("%s: connection is invalid(connid=%d)"), 
        __FUNCTION__, spconnctx->connid()));
      return -1;
    }

    return spconn->onTimeout(arg);
  }
}
