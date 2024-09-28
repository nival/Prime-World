#include "transport/stdafx.h"
#include "transport/TLOpenChannelOp.h"
#include <IOTerabit/AsynchChannel.h>
#include "transport/TLChannel.h"
#include <naio/ConnectionContext.h>
#include <naio/ChannelContext.h>
#include "transport/TLDataHandler.h"
#include "transport/TLConnection.h"
#include <Network/TransportMessages.h>

namespace TransportLayer
{
  namespace op
  {
    Terabit::AsynchChannelPtr GetTerabitChannelFromConnectionContext(naio::ConnectionContextStrongPtr const & spconnctx)
    {
      NI_PROFILE_BLOCK(__FUNCTION__);

      if (!TL::IsValid(spconnctx))
      {
        ACE_ERROR((LM_WARNING, ACE_TEXT("%s. Connection context is null"), __FUNCTION__));
        return Terabit::AsynchChannelPtr();
      }

      naio::ChannelContextSP spchnlctx = spconnctx->channelContext();
      if (!TL::IsValid(spchnlctx))
      {
        ACE_ERROR((LM_DEBUG, ACE_TEXT("%s. naio channel context is null(connid=%d)"), 
          __FUNCTION__, spconnctx->connid()));
        return Terabit::AsynchChannelPtr();
      }

      return spchnlctx->channel();
    }

    OpenChannel::OpenChannel(naio::ConnectionContextStrongPtr const & spconnctx, TL::IChannelInternalSP const & spchnl, void* tag)
      :ChannelOp(op::OPEN_CHANNEL, spconnctx, spchnl, 0),
      tag_(tag)
    {
    }

    OpenChannel::~OpenChannel()
    {
    }

    naio::StatusT
    OpenChannel::execute(TL::DataHandler* dh, 
                       Terabit::MessageBlockFactory& outmbf, ACE_Message_Block*& poutmb)
    {
      NI_PROFILE_BLOCK(__FUNCTION__);

      TL::ConnectionSP spconn = channel()->getConnection();
      if (!TL::IsValid(spconn))
      {
        ACE_ERROR((LM_DEBUG, ACE_TEXT("%s. Connection is null(t=%s s=%s c=%d ld=%s)"), __FUNCTION__,
          GetAddress().target.c_str(), GetAddress().source.c_str(), 
          GetAddress().client, GetLoginData().c_str()));
        return naio::status::FAIL;
      }

      Terabit::AsynchChannelPtr spchnl = GetTerabitChannelFromConnectionContext(naio::Operation::spctx_);
      if (!spchnl)
      {
        ACE_ERROR((LM_DEBUG, ACE_TEXT("%s. terabit channel is null(t=%s s=%s c=%d ld=%s)"), __FUNCTION__,
          GetAddress().target.c_str(), GetAddress().source.c_str(), 
          GetAddress().client, GetLoginData().c_str()));
        return naio::status::FAIL;
      }

      long rc = -1;
      if (channel()->openTimeout())
      {
        NI_PROFILE_BLOCK("start_timer");

        ACE_Time_Value tv(channel()->openTimeout());
        rc = spchnl->start_timer(tv, this->tag());
        if (rc < 0)
        {
          ACE_ERROR((LM_DEBUG, ACE_TEXT("%s. Can't start timer(t=%s s=%s c=%d ld=%s)"), __FUNCTION__,
            GetAddress().target.c_str(), GetAddress().source.c_str(), 
            GetAddress().client, GetLoginData().c_str()));
          return naio::status::FAIL;
        }
      }

      NI_PROFILE_BLOCK("send NewConnectionNetMessage");
      Transport::OpenChannelRequest msg;
      msg.clientAddress = this->GetAddress();
      msg.localPipeId = Transport::EKnownPipeId::FirstCustomPipeId; //  because channels open serially
      msg.loginData = this->GetLoginData();
      msg.channelType = channel()->channeltype();

      ACE_DEBUG((LM_TRACE, ACE_TEXT("%s(t=%s s=%s c=%d lp=%d ld=%s)"), __FUNCTION__,
        msg.clientAddress.target.c_str(), msg.clientAddress.source.c_str(), 
        msg.clientAddress.client, msg.localPipeId, msg.loginData.c_str()));

      rc = dh->HandleOutput(&msg, 
        Transport::ChannelAddr(Transport::EKnownPipeId::NetLogic, Transport::autoAssignClientId, msg.clientAddress.sender),
        this->spctx_,
        outmbf, poutmb);
      if (rc < 0)
      {
        ACE_ERROR((LM_ERROR, ACE_TEXT("[TL] OpenChannel.start FAILED(t='%s' s='%s' c='%d')"), 
          channel()->taddr().target.c_str(), channel()->taddr().source.c_str(), channel()->taddr().client));
      }
      else
      {
        ACE_ERROR((LM_INFO, ACE_TEXT("[TL] OpenChannel.start(t='%s' s='%s' c='%d')"), 
          channel()->taddr().target.c_str(), channel()->taddr().source.c_str(), channel()->taddr().client));
      }

      return (rc < 0 ? naio::status::FAIL : naio::status::SUCCESS);
    }

    unsigned int OpenChannel::getFinalOutputDataSize(TL::DataHandler* dh)
    {
      NI_PROFILE_BLOCK(__FUNCTION__);

      Transport::OpenChannelRequest msg;
      msg.clientAddress = this->GetAddress();
      msg.localPipeId = Transport::EKnownPipeId::FirstCustomPipeId; //  because channels open serially
      msg.loginData = this->GetLoginData();
      msg.channelType = channel()->channeltype();

      Transport::ChannelAddr caddr(Transport::EKnownPipeId::NetLogic, msg.clientAddress.client);
      return dh->GetFinalOutputDataSize(caddr, &msg);
    }

    naio::StatusT
    OpenChannel::complete(Transport::OpenChannelResponse const * msg)
    {
      NI_PROFILE_BLOCK(__FUNCTION__);

      ACE_DEBUG((LM_DEBUG, ACE_TEXT("[TL] %s(res=%d p=%d c=%d)"), 
        __FUNCTION__, msg->success, msg->remoteAddr.pipe, msg->remoteAddr.client));

      int rc = -1;

      Terabit::AsynchChannelPtr spchnl = GetTerabitChannelFromConnectionContext(naio::Operation::spctx_);
      if (spchnl)
      {
        NI_PROFILE_BLOCK("cancel_timer");

        rc = spchnl->cancel_timer();
        if (rc < 0)
        {
          ACE_ERROR((LM_WARNING, ACE_TEXT("%s. Cancel timer is failed(t=%s s=%s c=%d ld=%s)"), __FUNCTION__,
            GetAddress().target.c_str(), GetAddress().source.c_str(), 
            GetAddress().client, GetLoginData().c_str()));
          rc = 0; //  can't close connection due to failed cancel_timer operation
        }
      }
      else
      {
        ACE_ERROR((LM_WARNING, ACE_TEXT("%s. terabit channel is null(t=%s s=%s c=%d ld=%s)"), __FUNCTION__,
          GetAddress().target.c_str(), GetAddress().source.c_str(), 
          GetAddress().client, GetLoginData().c_str()));
      }

      TL::ConnectionSP spconn = channel()->getConnection();
      if (TL::IsValid(spconn))
      {
        if (msg->channelType == channel()->channeltype())
        {
          if (msg->success)
          {
            ACE_ERROR((LM_INFO, ACE_TEXT("[TL] OpenChannel.completed(p=%d t='%s' s='%s' c='%d')"), 
              msg->remoteAddr.pipe, channel()->taddr().target.c_str(), channel()->taddr().source.c_str(), 
              channel()->taddr().client));
          }
          else
          {
            ACE_ERROR((LM_WARNING, ACE_TEXT("[TL] OpenChannel.FAILED(p=%d t='%s' s='%s' c='%d')"), 
              msg->remoteAddr.pipe, channel()->taddr().target.c_str(), channel()->taddr().source.c_str(), 
              channel()->taddr().client));
          }

          NI_PROFILE_BLOCK("onOpenChannel");
          rc = channel()->onOpenChannel(msg->success, msg->remoteAddr);
        }
        else
        {
          ACE_ERROR((LM_WARNING, ACE_TEXT("[TL] OpenChannel.FAILED. Incorrect channel type in response(p=%d t='%s' s='%s' c='%d' expectedType=%s receivedType=%s)"), 
            msg->remoteAddr.pipe, channel()->taddr().target.c_str(), channel()->taddr().source.c_str(), 
            channel()->taddr().client, Transport::EChannelType::ToString(channel()->channeltype()), Transport::EChannelType::ToString(msg->channelType)));

          NI_PROFILE_BLOCK("onOpenChannel");
          rc = channel()->onOpenChannel(false, msg->remoteAddr);
          rc = -1;
        }

      }
      else
      {
        ACE_ERROR((LM_WARNING, ACE_TEXT("[TL] %s. Connection already is INVALID(res=%d p=%d c=%d)"), 
          __FUNCTION__, msg->success, msg->remoteAddr.pipe, msg->remoteAddr.client));
      }

      return (rc < 0 ? naio::status::FAIL : naio::status::SUCCESS);
    }

    Transport::TLoginData const & OpenChannel::GetLoginData() const
    {
      return channel()->openChannelKey();
    }

    Transport::Address const & OpenChannel::GetAddress() const
    {
      return channel()->taddr();
    }
  }
}
