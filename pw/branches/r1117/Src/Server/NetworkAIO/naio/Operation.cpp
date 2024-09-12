#include "naio/stdafx.h"
#include "naio/Operation.h"
#include <TProactor/Proactor.h>
#include "naio/ConnectionContext.h"
#include "naio/ChannelContext.h"
#include "System/Asserts.h"

namespace naio
{

  Operation::Operation(OperationType t, ConnectionContextStrongPtr const & spctx)
    :type_(t),
    spctx_(spctx)
  {
    NI_PROFILE_BLOCK(__FUNCTION__);
  }

  Operation::~Operation()
  {
    NI_PROFILE_BLOCK(__FUNCTION__);
  }

  int Operation::PostCompletion(TRB_Handler* handler)
  {
    NI_PROFILE_BLOCK(__FUNCTION__);

    TRB_Asynch_User_Result::Buffer_Info bi;
    TRB_Asynch_User_Result result (handler, 
      ACE_INVALID_HANDLE, // handle
      bi,
      0,  // bytes requested
      0,  // offset low
      0,  // offset high
      (const void*) static_cast<Operation*>(this),
      0,  // completion key
      0,  // priority
      0); // signal_number

    return handler->proactor()->post_completion(result);
  }

  int Operation::Post()
  {
    NI_PROFILE_BLOCK(__FUNCTION__);

    ACE_DEBUG((LM_TRACE, ACE_TEXT("%s(type=%d)"), __FUNCTION__, type_));

    if (spctx_.null())
    {
      ACE_ERROR((LM_ERROR, ACE_TEXT("%s. Connection context is NULL! (type=%d)"), __FUNCTION__, type_));
      return -1;
    }

    ChannelContextStrongPtr spchnl = spctx_->channelContext();
    if (spchnl.null())
    {
      ACE_ERROR((LM_ERROR, ACE_TEXT("%s. Terabit channel context is NULL! (type=%d)"), __FUNCTION__, type_));
      return -1;
    }

    addRef();
    int rc = PostCompletion(spchnl->channel().get());
    if (rc < 0)
      releaseRef();

    return rc;
  }
}
