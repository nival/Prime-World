#include "naio/stdafx.h"
#include "naio/Ops.h"
#include <ace/INET_Addr.h>
#include "naio/ConnectionContext.h"
#include "naio/ChannelContext.h"

namespace naio
{
  //namespace op
  //{
    OpenConnectionOp::OpenConnectionOp(ACE_INET_Addr const & addr, ConnectionContextStrongPtr const & spctx)
      :Operation(Operation::OP_OPEN_CONNECTION, spctx),
      addr_(addr),
      conn_(spctx)
    {
    }

    OpenConnectionOp::~OpenConnectionOp()
    {
    }

    void OpenConnectionOp::OnConnection(bool /*success*/, ChannelContextStrongPtr const & /*spcc*/)
    {
    }

    //////////////////////////////////////////////////////////////////////////
    //  CloseConnectionOp
    //
    CloseConnectionOp::CloseConnectionOp(ConnectionContextStrongPtr const & spctx)
      :Operation(Operation::OP_CLOSE_CONNECTION, spctx)
    {
    }

    CloseConnectionOp::~CloseConnectionOp()
    {
    }

    //////////////////////////////////////////////////////////////////////////
    //  SendData
    //
    SendData::SendData(unsigned int size, char const * data, bool preallocated,
      ConnectionContextStrongPtr const & spctx)
      :Operation(Operation::OP_SEND_DATA, spctx),
      pmb_(0),
      preallocated_(preallocated)
    {
      NI_PROFILE_BLOCK(__FUNCTION__);

      ChannelContextStrongPtr spchnl = spctx_->channelContext();
      if (!spchnl.null())
      {
        pmb_ = spchnl->channel()->alloc_msg(size);
        if (pmb_)
          pmb_->copy(data, size);
      }
    }

    SendData::~SendData()
    {
      NI_PROFILE_BLOCK(__FUNCTION__);

      if (pmb_)
      {
        ChannelContextStrongPtr spchnl = spctx_->channelContext();
        if (!spchnl.null())
        {
          spchnl->channel()->free_msg(pmb_);
          pmb_ = 0;
        }
      }
    }
//  }
}
