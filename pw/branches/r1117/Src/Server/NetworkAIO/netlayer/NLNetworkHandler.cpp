#include "netlayer/stdafx.h"
#include "NLNetworkHandler.h"
#include <ace/Log_Msg.h>
#include <ace/Message_Block.h>
#include <IOTerabit/MessageBlockFactory.h>
#include <naio/ConnectionContext.h>

namespace NetworkLayer
{
  NetworkHandler::NetworkHandler(INetworkBasedHandler* input_handler)
    :input_handler_(input_handler)
  {
  }

  NetworkHandler::~NetworkHandler()
  {
  }

  naio::StatusT NetworkHandler::HandleInput(size_t length, const char *data, size_t& readBytes, 
                            naio::ConnectionContextStrongPtr const & spconn, 
                            Terabit::MessageBlockFactory& outmbf, ACE_Message_Block*& poutmb)
  {
    NI_PROFILE_BLOCK(__FUNCTION__);

    ACE_DEBUG((LM_TRACE, ACE_TEXT("%s(l=%d)"), __FUNCTION__, length));

    NI_ASSERT(length, "Data size have NOT to be zero!");

    if (length < HEADER_SIZE)
    {
      ACE_DEBUG((LM_DEBUG, ACE_TEXT("%s. Data length less than header size(l=%d)"), 
        __FUNCTION__, length));
      return naio::status::SUCCESS;
    }

    unsigned short packet_size = *((unsigned short*)data);
    if (length - HEADER_SIZE < packet_size)
    {
      ACE_DEBUG((LM_DEBUG, ACE_TEXT("%s. Data length less than packet size in header(l=%d psz=%d)"), 
        __FUNCTION__, length, packet_size));
      return naio::status::SUCCESS;
    }

    size_t consumed_bytes = 0;
    size_t remain_bytes = length - HEADER_SIZE;
    char const * pdata = data + HEADER_SIZE;

    ACE_Message_Block* plastmb = 0;
    unsigned int outmb_count = 0;

    do
    {
      NI_PROFILE_BLOCK("do_while");

      ACE_Message_Block* phandler_outmb = 0;

      size_t rb = 0;
      consumed_bytes += HEADER_SIZE;
      naio::StatusT sts = input_handler_->HandleInput(packet_size, pdata, rb, spconn, outmbf, phandler_outmb);
      if (naio::status::SUCCESS != sts)
      {
        ACE_DEBUG((LM_DEBUG, ACE_TEXT("%s Handling is failed"), __FUNCTION__));
        return sts;
      }

      ACE_ASSERT(rb == packet_size);

      if (phandler_outmb && phandler_outmb->length())
      {
        ACE_Message_Block* pout = 0;  //  will be equal to phandler_outmb
                                      //  because preallocated flag is true
        sts = HandleOutput(*phandler_outmb, true, spconn, outmbf, pout);
        if (naio::status::SUCCESS != sts)
        {
          ACE_DEBUG((LM_DEBUG, ACE_TEXT("%s HandleOutput is failed"), __FUNCTION__));
          outmbf.free_msg(phandler_outmb);
          return sts;
        }

        if (!poutmb)
        {
          poutmb = phandler_outmb;
          plastmb = poutmb;
        }
        else
        {
          plastmb->cont(phandler_outmb);
          plastmb = phandler_outmb;
        }
        ++outmb_count;
      }

      consumed_bytes += rb;
      remain_bytes -= rb;
      pdata += rb;

      if (remain_bytes >= HEADER_SIZE)
      {
        packet_size = *((unsigned short*)pdata);
        pdata += HEADER_SIZE;
        remain_bytes -= HEADER_SIZE;
      }
      else
        packet_size = MAX_PACKET_SIZE;
    }
    while(packet_size <= remain_bytes);

    if (outmb_count > 1)
    {
      ACE_DEBUG((LM_DEBUG, ACE_TEXT("%s(outmb_count=%d read_bytes=%d)"), __FUNCTION__, outmb_count, consumed_bytes));
    }

    readBytes = consumed_bytes;
    return naio::status::SUCCESS;
  }

  naio::StatusT NetworkHandler::HandleOutput(ACE_Message_Block& mb, bool preallocated, 
                             naio::ConnectionContextStrongPtr const & spconn, 
                             Terabit::MessageBlockFactory& outmbf, ACE_Message_Block*& poutmb)
  {
    NI_PROFILE_BLOCK(__FUNCTION__);

    ACE_ASSERT(mb.length() <= MAX_PACKET_SIZE);
    ACE_DEBUG((LM_TRACE, ACE_TEXT("%s(l=%d)"), __FUNCTION__, mb.length()));

    if (preallocated)
    {
      writeBodyLength(mb);
      return naio::status::SUCCESS;
    }
    else
    {
      ACE_Message_Block* pmb = AllocBuffer(outmbf, mb.length());
      if (pmb)
      {
        pmb->copy(mb.base(), mb.length());
        writeBodyLength(*pmb);
        poutmb = pmb;
        return naio::status::SUCCESS;
      }
      else
      {
        ACE_ERROR((LM_ERROR, ACE_TEXT("%s. Can't allocate buffer(l=%d connid=%d)"), __FUNCTION__, mb.length(), spconn->connid()));
        return naio::status::FAIL;
      }
    }
  }

  ACE_Message_Block* NetworkHandler::AllocBuffer(Terabit::MessageBlockFactory& mbf, unsigned int bodySize)
  {
    NI_PROFILE_BLOCK(__FUNCTION__);

    if (bodySize > MAX_PACKET_SIZE - HEADER_SIZE)
    {
      ACE_ERROR((LM_ERROR, ACE_TEXT("%s. Try allocate packet with body bigger then allowed(sz=%d allowed=%d)"),
        __FUNCTION__, bodySize, MAX_PACKET_SIZE - HEADER_SIZE));

      return 0;
    }

    ACE_Message_Block* pmb = mbf.alloc_msg(HEADER_SIZE + bodySize);
    if (!pmb)
    {
      NI_ASSERT(pmb, NI_STRFMT("Can't allocate memory(bsz=%d)", HEADER_SIZE + bodySize));

      ACE_ERROR((LM_CRITICAL, ACE_TEXT("%s. Can't allocate memory(bsz=%d)"),
        __FUNCTION__, HEADER_SIZE + bodySize));
      return 0;
    }

    pmb->wr_ptr(HEADER_SIZE);
    return pmb;
  }

  void NetworkHandler::writeBodyLength(ACE_Message_Block & mb)
  {
    unsigned short bodylen = static_cast< unsigned short >(mb.length() - HEADER_SIZE);
    mb.wr_ptr(mb.base());
    mb.copy((char*)&bodylen, sizeof(bodylen));
    mb.wr_ptr(bodylen);
  }
}
