#include "naio/stdafx.h"
#include "naio/BaseProtocol.h"
#include <IOTerabit/AsynchChannel.h>
#include "naio/Ops.h"
#include "naio/ChannelManager.h"
#include "naio/ChannelContext.h"
#include "naio/ConnectionContext.h"
#include <ace/OS_NS_sys_socket.h>

#if defined( NV_LINUX_PLATFORM )
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/tcp.h>
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

const int SOCKET_ERROR = -1;
#endif

namespace naio
{
  struct ConnectionSettings
  {
    ConnectionSettings()
      :rcvBlockSize_(0),
      so_rcvbuf_(0),
      so_sndbuf_(0),
      disableNagleAlgorithm_(-1),
      so_keepalive_(-1),
      logWrittenBytes_(0)
    {
    }

    unsigned int rcvBlockSize_;
    int so_rcvbuf_;
    int so_sndbuf_;
    int disableNagleAlgorithm_;
    int so_keepalive_;
    unsigned int logWrittenBytes_;
  };

#pragma warning( push )
#pragma warning( disable : 4355)
  BaseProtocol::BaseProtocol(Terabit::ProtocolFactory& factory)
    : Terabit::RefCntProtocol(factory),
    factory_(factory),
    act_(0),
    st_(ST_INIT),
    mbf_(0),
    log_written_bytes_(0),
    written_bytes_(0),
    total_written_bytes_(0)
#pragma warning( pop )
  {
  }

  BaseProtocol::~BaseProtocol()
  {
  }

  int BaseProtocol::applyConnectionSettings(Terabit::AsynchChannel *channel, 
    ConnectionSettings const & cs)
  {
    NI_PROFILE_BLOCK(__FUNCTION__);

    ACE_DEBUG((LM_TRACE, ACE_TEXT("%s(ch=%d)"), __FUNCTION__, channel->get_id()));

    int rc = 0;

    //  set read buffer size
    if (cs.rcvBlockSize_)
    {
      channel->set_read_size(cs.rcvBlockSize_);
    }

    if (cs.so_rcvbuf_ > 0)
    {
      int recvbufsize = 0;
      int lrecvbufsize = sizeof(recvbufsize);
      int serr = ACE_OS::getsockopt(channel->handle(), SOL_SOCKET, SO_RCVBUF, 
        reinterpret_cast<char*>(&recvbufsize), &lrecvbufsize);
      if (SOCKET_ERROR == serr)
      {
        ACE_ERROR((LM_WARNING, ACE_TEXT("%s. Can't get SO_RCVBUF(ch=%d err=%d)"), 
          __FUNCTION__, channel->get_id(), errno));

        recvbufsize = cs.so_rcvbuf_;
      }
      else
      {
        ACE_ERROR((LM_INFO, ACE_TEXT("%s. Default SO_RCVBUF %d(ch=%d)"), 
          __FUNCTION__, recvbufsize, channel->get_id()));
      }

      //if (cs.so_rcvbuf_ > recvbufsize)
      {
        recvbufsize = cs.so_rcvbuf_;
        lrecvbufsize = sizeof(recvbufsize);
        serr = ACE_OS::setsockopt(channel->handle(),
          SOL_SOCKET, SO_RCVBUF, 
          reinterpret_cast<char*>(&recvbufsize), lrecvbufsize);
        if (SOCKET_ERROR == serr)
        {
          ACE_ERROR((LM_ERROR, ACE_TEXT("%s. Can't set SO_RCVBUF(ch=%d err=%d)"), 
            __FUNCTION__, channel->get_id(), errno));
          rc = -1;
        }
        else
        {
          ACE_ERROR((LM_INFO, ACE_TEXT("%s. SO_RCVBUF set to %d(ch=%d)"), 
            __FUNCTION__, recvbufsize, channel->get_id()));
        }
      }
    }

    //  Nagle algorithm
    if (-1 != cs.disableNagleAlgorithm_)
    {
#if defined( NV_WIN_PLATFORM )
      bool disableNagleAlgorithm_ = bool(cs.disableNagleAlgorithm_);
#elif defined( NV_LINUX_PLATFORM )
      // In POSIX it has to be int
      const int disableNagleAlgorithm_ = cs.disableNagleAlgorithm_;
#endif
      int serr = ACE_OS::setsockopt(channel->handle(),  IPPROTO_TCP, TCP_NODELAY, 
        reinterpret_cast<const char*>(&disableNagleAlgorithm_), sizeof(disableNagleAlgorithm_));

      if (SOCKET_ERROR == serr)
      {
        ACE_ERROR((LM_ERROR, ACE_TEXT("%s. Can't disable Nagle algorithm(ch=%d err=%d)"), 
          __FUNCTION__, channel->get_id(), errno));
        rc = -1;
      }
      else
      {
        ACE_ERROR((LM_INFO, ACE_TEXT("%s. Nagle algorithm disabled successfully(ch=%d)"), 
          __FUNCTION__, channel->get_id()));
      }
    }

    if (cs.so_keepalive_ != -1)
    {
      int serr = ACE_OS::setsockopt(channel->handle(),  SOL_SOCKET, SO_KEEPALIVE, 
        reinterpret_cast<const char*>(&cs.so_keepalive_), sizeof(cs.so_keepalive_));

      if (SOCKET_ERROR == serr)
      {
        ACE_ERROR((LM_ERROR, ACE_TEXT("%s. Can't set SO_KEEPALIVE(ch=%d err=%d val=%d)"), 
          __FUNCTION__, channel->get_id(), errno, cs.so_keepalive_));
        rc = -1;
      }
      else
      {
        ACE_ERROR((LM_INFO, ACE_TEXT("%s. SO_KEEPALIVE set to %d(ch=%d)"), 
          __FUNCTION__, cs.so_keepalive_, channel->get_id()));
      }
    }

    //  set sys send buffer
    if (cs.so_sndbuf_ != -1)
    {
      int sendbufsize = 0;
      int lsendbufsize = sizeof(sendbufsize);
      int serr = ACE_OS::getsockopt(channel->handle(), SOL_SOCKET, SO_SNDBUF, 
        reinterpret_cast<char*>(&sendbufsize), &lsendbufsize);
      if (SOCKET_ERROR == serr)
      {
        ACE_ERROR((LM_WARNING, ACE_TEXT("%s. Can't get SO_SNDBUF(ch=%d err=%d)"), 
          __FUNCTION__, channel->get_id(), errno));

        sendbufsize = cs.so_sndbuf_;
      }
      else
      {
        ACE_ERROR((LM_INFO, ACE_TEXT("%s. Default SO_SNDBUF %d(ch=%d)"), 
          __FUNCTION__, sendbufsize, channel->get_id()));
      }

      if (cs.so_sndbuf_ != -1)
      {
        //if (0 == cs.so_sndbuf_ || cs.so_sndbuf_ > sendbufsize)
        sendbufsize = cs.so_sndbuf_;

        if (sendbufsize == cs.so_sndbuf_) //  need to change default value
        {
          lsendbufsize = sizeof(sendbufsize);
          serr = ACE_OS::setsockopt(channel->handle(),
            SOL_SOCKET, SO_SNDBUF, 
            reinterpret_cast<char*>(&sendbufsize), lsendbufsize);
          if (SOCKET_ERROR == serr)
          {
            ACE_ERROR((LM_ERROR, ACE_TEXT("%s. Can't set SO_SNDBUF(ch=%d err=%d)"), 
              __FUNCTION__, channel->get_id(), errno));
            rc = -1;
          }
          else
          {
            if (0 == sendbufsize)
              ACE_ERROR((LM_INFO, ACE_TEXT("%s. Use zero-copy send buf(ch=%d)"), 
              __FUNCTION__, channel->get_id()));
            else
              ACE_ERROR((LM_INFO, ACE_TEXT("%s. SO_SNDBUF set to %d(ch=%d)"), 
              __FUNCTION__, sendbufsize, channel->get_id()));
          }
        }
        else
        {
          ACE_ERROR((LM_INFO, ACE_TEXT("%s. SO_SNDBUF input value is set to %d but default value is used(input=%d default=%d ch=%d)"), 
            __FUNCTION__, cs.so_sndbuf_, sendbufsize, channel->get_id()));
        }
      }
      else
      {
        ACE_ERROR((LM_INFO, ACE_TEXT("%s. Use default SO_SNDBUF %d(ch=%d)"), 
          __FUNCTION__, sendbufsize, channel->get_id()));
      }
    }

    if (cs.logWrittenBytes_)
    {
      log_written_bytes_ = cs.logWrittenBytes_;
      ACE_ERROR((LM_INFO, ACE_TEXT("%s. Log written bytes each %d bytes(ch=%d)"), 
        __FUNCTION__, log_written_bytes_, channel->get_id()));
    }

    return rc;
  }

  int BaseProtocol::on_channel_up(Terabit::AsynchChannel *channel)
  {
    NI_PROFILE_BLOCK(__FUNCTION__);

    ACE_DEBUG((LM_TRACE, ACE_TEXT("%s(ch=%d serverside=%d)"), __FUNCTION__, 
      channel->get_id(), channel->is_server()));

    state_(ST_OPENED);

    int rc = -1;

    IProtocolHandlerSP ph = ph_;
    if (ph.null())
    {
      ACE_ERROR((LM_ERROR, ACE_TEXT("%s(ch=%d). ProtocolHandler is NULL"), __FUNCTION__, channel->get_id()));
      return -1;
    }

    ConnectionSettings cs;
    cs.rcvBlockSize_ = manager(channel)->readBlockSize();
    cs.so_rcvbuf_ = manager(channel)->soRcvbuf();
    cs.so_sndbuf_ = manager(channel)->soSndbuf();
    cs.disableNagleAlgorithm_ = manager(channel)->disableNagleAlgorithm();
    cs.so_keepalive_ = manager(channel)->soKeepalive();
    cs.logWrittenBytes_ = manager(channel)->logWrittenBytes();
    BaseProtocol::applyConnectionSettings(channel, cs);

    if (!channel->is_server())
    {
      Ptr<OpenConnectionOp> ocop(reinterpret_cast<OpenConnectionOp*>(act_), false);
      if (ocop)
      {
        ChannelContextStrongPtr spcc = manager(channel)->RegisterChannel(channel, ocop->connctx());
        wpcc_ = spcc;

        ocop->OnConnection(true, spcc);
        rc = ph->OnOpenConnection(true, true, ocop->connctx());
      }
      else
      {
        ACE_ERROR((LM_ERROR, ACE_TEXT("OpenConnection operation is NULL(ch=%d)"), channel->get_id()));
      }
    }
    else
    {
      ChannelContextStrongPtr spcc = manager(channel)->RegisterChannel(channel, 
        ConnectionContextStrongPtr(new ConnectionContext(act_)));
      wpcc_ = spcc;
      rc = ph->OnOpenConnection(true, false, spcc->connctx());

      //ACE_ERROR((LM_ERROR, ACE_TEXT("Server mode is not supported (ch=%d)"), channel->get_id()));
    }

    return rc;
  }

  int BaseProtocol::on_user_operation(Terabit::AsynchChannel *channel, OperationPtr const & _op)
  {
    NI_PROFILE_BLOCK(__FUNCTION__);

    ACE_DEBUG((LM_TRACE, ACE_TEXT("%s(ch=%d op=%d)"), __FUNCTION__, channel->get_id(), _op->type()));

    if (ST_CLOSED == state_())
    {
      ACE_ERROR((LM_WARNING, ACE_TEXT("%s(ch=%d op=%d). Protocol is already CLOSED"), __FUNCTION__, 
        channel->get_id(), _op->type()));
      return -1;
    }

    ChannelContextStrongPtr spcc = wpcc_.strong();
    if (spcc.null())
    {
      ACE_ERROR((LM_WARNING, ACE_TEXT("%s(ch=%d op=%d). Channel context is null"), __FUNCTION__, 
        channel->get_id(), _op->type()));
      return -1;
    }

    IProtocolHandlerSP ph = ph_;
    if (ph.null())
    {
      ACE_ERROR((LM_WARNING, ACE_TEXT("%s(ch=%d). ProtocolHandler is NULL"), __FUNCTION__, channel->get_id()));
      return -1;
    }

    naio::StatusT sts = naio::status::FAIL;
    int rc = -1;
    OperationPtr op(_op);
    do
    {
      NI_PROFILE_BLOCK("do_while");

      sts = naio::status::FAIL;
      OperationPtr nextop = op->next();

      switch(op->type())
      {
      case Operation::OP_CLOSE_CONNECTION:
        {
          channel->close();
        }
        break;

      case Operation::OP_SEND_DATA:
        {
          Ptr<SendData> sdop(static_cast<SendData*>(op.get()));
          ACE_Message_Block* poutmb = 0;
          sts = ph->HandleOutput(sdop->mb()->length(), sdop->mb()->base(), sdop->preallocated(),
                            spcc->connctx(), static_cast<Terabit::MessageBlockFactory&>(*channel), poutmb);
          if (sts != naio::status::FAIL)
          {
            if (poutmb)
            {
              rc = channel->start_write(*poutmb);
              if (rc < 0)
              {
                ACE_ERROR((LM_INFO, ACE_TEXT("Can't start send data(ch=%d op=%d sz=%d)"), 
                  channel->get_id(), op->type(), poutmb->length()));

                sts = naio::status::FAIL;
              }
            }
            else
            {
              ACE_DEBUG((LM_DEBUG, ACE_TEXT("SendData operation handling - no output(ch=%d op=%d)"), 
                channel->get_id(), op->type()));
            }
          }
          else
          {
            ACE_ERROR((LM_WARNING, ACE_TEXT("SendData's HandleOutput() is FAILED (ch=%d, op=%d)"), 
              channel->get_id(), op->type()));
          }
        }
        break;

      default:
        {
          NI_PROFILE_BLOCK("OnUserOperation");

          ACE_Message_Block* poutmb = 0;
          sts = ph->OnUserOperation(op, spcc->connctx(), static_cast<Terabit::MessageBlockFactory&>(*channel), poutmb);
          if (sts >= 0)
          {
            if (poutmb)
            {
              unsigned int qlen = 0;
              unsigned int qlen_in_bytes = 0;
              unsigned int total_msg_size = poutmb->total_length();
              {
                NI_PROFILE_BLOCK("start_write");
                rc = channel->start_write(*poutmb, qlen, qlen_in_bytes);
              }
              if (rc < 0)
              {
                ACE_ERROR((LM_INFO, ACE_TEXT("Can't start send data(ch=%d op=%d sz=%d)"), 
                  channel->get_id(), op->type(), poutmb->length()));

                sts = naio::status::FAIL;
              }
              else
              {
                if (log_written_bytes_)
                {
                  written_bytes_ += total_msg_size;
                  if (written_bytes_ > log_written_bytes_)
                  {
                    total_written_bytes_ += written_bytes_;

                    ACE_ERROR((LM_INFO, 
                      ACE_TEXT("Written in output queue(total_msg_size=%d written_bytes=%d total_written_bytes=%Q qlen=%d qlen_in_bytes=%d ch=%d)"), 
                      total_msg_size, written_bytes_, total_written_bytes_, qlen, qlen_in_bytes, channel->get_id()));
                    written_bytes_ = 0;
                  }
                }
              }

              {
                NI_PROFILE_BLOCK("UserOperationPostHandler");
                ph->UserOperationPostHandler(sts, op, spcc->connctx());
              }
            }
            else
            {
              ACE_DEBUG((LM_DEBUG, ACE_TEXT("User operation handling - no output(ch=%d op=%d)"), 
                channel->get_id(), op->type()));
            }
          }
          else
          {
            ACE_ERROR((LM_ERROR, ACE_TEXT("User operation handling FAILED(sts=%d ch=%d op=%d)"), 
              sts, channel->get_id(), op->type()));
          }
        }
      }

      op = nextop;
    }
    while(naio::status::FAIL != rc && op);

    return (naio::status::FAIL == sts ? -1 : 0);
  }

  int BaseProtocol::on_read_completed (Terabit::AsynchChannel *channel, const char *data, size_t length)
  {
    NI_PROFILE_BLOCK(__FUNCTION__);

    ACE_DEBUG((LM_TRACE, ACE_TEXT("%s(ch=%d serverside=%d)"), __FUNCTION__, 
      channel->get_id(), channel->is_server()));

    ChannelContextStrongPtr spcc = wpcc_.strong();
    if (spcc.null())
    {
      ACE_ERROR((LM_ERROR, ACE_TEXT("%s(ch=%d). Channel context is null"), __FUNCTION__, channel->get_id()));
      return -1;
    }

    IProtocolHandlerSP ph = ph_;
    if (ph.null())
    {
      ACE_ERROR((LM_WARNING, ACE_TEXT("%s(ch=%d). ProtocolHandler is NULL"), __FUNCTION__, channel->get_id()));
      return -1;
    }

    NI_PROFILE_BLOCK("HandleInput");
    int rc = -1;
    ACE_Message_Block* pmb = 0;
    size_t readBytes = 0;
    naio::StatusT sts = ph->HandleInput(length, data, readBytes, spcc->connctx(), (Terabit::MessageBlockFactory&)(*channel), pmb);
    if (sts != status::FAIL)
    {
      ACE_ERROR((LM_DEBUG, ACE_TEXT("%s. %d bytes read from %d(ch=%d)"), __FUNCTION__, 
        readBytes, length, channel->get_id()));

      if (pmb)
      {
        NI_PROFILE_BLOCK("start_write");

        rc = channel->start_write(*pmb);
        if (rc < 0)
        {
          ACE_ERROR((LM_ERROR, ACE_TEXT("%s. Can't start write(ch=%d sz=%d)"), __FUNCTION__, 
            channel->get_id(), pmb->total_length()));
          sts = status::FAIL;
        }
      }
      else
      {
        //ACE_ERROR((LM_DEBUG, ACE_TEXT("%s. HandleInput has no output(ch=%d)"), __FUNCTION__, 
        //  channel->get_id()));
        rc = 0;
      }
    }
    else
    {
      ACE_ERROR((LM_ERROR, ACE_TEXT("%s. HandleInput is FAILED(ch=%d)"), __FUNCTION__, 
        channel->get_id()));
    }

    NI_PROFILE_BLOCK("PostHandleInput");
    ph->PostHandleInput(sts, spcc->connctx());

    if (rc >= 0)
    {
      if (0 == readBytes && length == channel->get_read_size())
      {
        ACE_ERROR((LM_ERROR, ACE_TEXT("%s. Read buffer is not big enough to read(ch=%d datalen=%d bufsize=%d)"), __FUNCTION__, 
          channel->get_id(), length, channel->get_read_size()));
        rc = -1;
      }
      else
        rc = (int)readBytes;
    }

    return rc;
  }

  void BaseProtocol::on_channel_done (Terabit::AsynchChannel *channel)
  {
    NI_PROFILE_BLOCK(__FUNCTION__);

    ACE_DEBUG((LM_TRACE, ACE_TEXT("%s(ch=%d)"), __FUNCTION__, channel->get_id()));

    state_(ST_CLOSED);

    IProtocolHandlerSP ph = ph_;
    if (ph.null())
    {
      ACE_ERROR((LM_WARNING, ACE_TEXT("%s(ch=%d). ProtocolHandler is NULL"), __FUNCTION__, channel->get_id()));
      return;
    }

    ChannelContextStrongPtr spcc = wpcc_.strong();
    if (!spcc.null())
    {
      ph->OnCloseConnection(spcc->connctx());
    }
    else
    {
      ACE_ERROR((LM_ERROR, ACE_TEXT("%s(ch=%d). Channel context is null"), __FUNCTION__, channel->get_id()));
    }

    manager(channel)->UnregisterChannel(channel->get_id());

    ph.reset(0);
    ph_.reset(0);
  }

  void BaseProtocol::on_reset()
  {
    state_(ST_INIT);
  }

  int BaseProtocol::on_timeout (Terabit::AsynchChannel *channel, const void *arg)
  {
    NI_PROFILE_BLOCK(__FUNCTION__);

    ACE_DEBUG((LM_TRACE, ACE_TEXT("%s(ch=%d to=%d)"), __FUNCTION__, channel->get_id(), arg));

    IProtocolHandlerSP ph = ph_;
    if (ph.null())
    {
      ACE_ERROR((LM_WARNING, ACE_TEXT("%s(ch=%d). ProtocolHandler is NULL"), __FUNCTION__, channel->get_id()));
      return -1;
    }

    ChannelContextStrongPtr spcc = wpcc_.strong();
    if (spcc.null())
    {
      ACE_ERROR((LM_ERROR, ACE_TEXT("%s(ch=%d). Channel context is null"), __FUNCTION__, channel->get_id()));
      return -1;
    }

    return ph->OnTimeout(spcc->connctx(), arg);
  }

  ChannelManager* BaseProtocol::manager(Terabit::AsynchChannel *channel) const
  {
    return (ChannelManager*)(channel->get_manager());
  }

  Terabit::MessageBlockFactory* BaseProtocol::get_message_block_factory() const
  {
    return mbf_;
  }

  int BaseProtocol::check_activity(Terabit::AsynchChannel *channel, const ACE_Time_Value&  last_op_time)
  {
    NI_PROFILE_BLOCK(__FUNCTION__);

    IProtocolHandlerSP ph = ph_;
    if (ph.null())
    {
      ACE_ERROR((LM_WARNING, ACE_TEXT("%s(ch=%d). ProtocolHandler is NULL"), __FUNCTION__, channel->get_id()));
      return -1;
    }

    ChannelContextStrongPtr spcc = wpcc_.strong();
    if (spcc.null())
    {
      ACE_ERROR((LM_ERROR, ACE_TEXT("%s(ch=%d). Channel context is null"), __FUNCTION__, channel->get_id()));
      return -1;
    }

    return ph->CheckActivity(spcc->connctx(), last_op_time);
  }
}
