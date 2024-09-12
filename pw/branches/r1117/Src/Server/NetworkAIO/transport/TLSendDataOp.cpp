#include "transport/stdafx.h"
#include "transport/TLSendDataOp.h"
#include "transport/TLChannel.h"
#include "transport/TLDataHandler.h"
#include <ace/Message_Block.h>

namespace TransportLayer
{
  namespace op
  {
    //////////////////////////////////////////////////////////////////////////
    //  Send data operation
    //
    SendData::SendData(naio::ConnectionContextStrongPtr const & spconnctx, TL::IChannelInternalSP const & spchnl,
                       ACE_Message_Block* mb, unsigned long seqNum)
      :ChannelOp(op::SEND_DATA, spconnctx, spchnl, seqNum),
      mb_(mb)
    {
    }

    SendData::~SendData()
    {
      NI_PROFILE_BLOCK(__FUNCTION__);
      channel()->freeMsgBlock_(mb_);
    }

    naio::StatusT 
    SendData::execute(TL::DataHandler* dh, Terabit::MessageBlockFactory& outmbf, ACE_Message_Block*& poutmb)
    {
      NI_PROFILE_BLOCK(__FUNCTION__);
      //NI_ASSERT(channel()->lastSentSeqNum() + 1 == seqNum(), "Wrong msg sequence!!!");

      Transport::ChannelAddr caddr = channel()->chaddr();
      caddr.SeqNum(seqNum());

      //ACE_DEBUG((LM_DEBUG, ACE_TEXT("[TL] send(lsn=%d sn=%d)"),  //   p=%d t='%s' s='%s' c='%d')"
      //  channel()->lastSentSeqNum(), caddr.SeqNum(), caddr.pipe, 
      //  channel()->GetAddress().target.c_str(), channel()->GetAddress().source.c_str(), spchnl_->GetAddress().client));

      return dh->HandleOutput(caddr, mb_->length(), mb_->base(), this->spctx_, outmbf, poutmb);
    }

    unsigned int SendData::getFinalOutputDataSize(TL::DataHandler* dh)
    {
      NI_PROFILE_BLOCK(__FUNCTION__);
      return dh->GetFinalOutputDataSize(channel()->chaddr(), mb_->length());
    }
  }
}
