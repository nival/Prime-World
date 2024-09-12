#pragma warning( disable : 4996)
#include "stdafx.h"
#include "TProactor/Proactor.h"
#include "PeerContext.h"
#include "Operation.h"

namespace Relay
{

Operation::Operation(OperationType::Enum t)
  :type_(t),
  next_(0),
  refCount_(1)
{
}

Operation::~Operation()
{
}

int Operation::PostCompletion(TRB_Handler* handler)
{
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

int Operation::PostCompletion(PeerContext* context)
{
  if (context->isclosed())
    return -1;

  Terabit::AsynchChannelPtr const & chnl = context->channel();
  if (!chnl)
    return -1;

  return PostCompletion(chnl.get());
}

void Operation::Close()
{
  NI_PROFILE_BLOCK(__FUNCTION__);
  releaseRef();
}

void Operation::addRef()
{
  NI_PROFILE_BLOCK(__FUNCTION__);
  ++refCount_;
}

void Operation::releaseRef()
{
  NI_PROFILE_BLOCK(__FUNCTION__);
  if (--refCount_ <= 0)
    delete this;
}

}
