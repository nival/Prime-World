#include "stdafx.h"
#include "PollJob.h"
#include "GateKeeper.h"

namespace rpc
{
  CloseChannelJob::CloseChannelJob(CloseChannelJobFactory* factory) :
  cb_(0),
  chnl_(0),
  node_(0),
  factory_(factory)
  {
  }

  CloseChannelJob::CloseChannelJob( IGateKeeperCallback * cb, Transport::IChannel * chnl, rpc::Node * node, CloseChannelJobFactory * factory ) :
  cb_(cb),
  chnl_(chnl),
  node_(node),
  factory_(factory)
  {
  }

  CloseChannelJob::~CloseChannelJob()
  {
  }

  void CloseChannelJob::Init( IGateKeeperCallback * cb, Transport::IChannel * chnl, rpc::Node * node )
  {
    cb_ = cb;
    chnl_ = chnl;
    node_ = node;
  }

  void CloseChannelJob::Execute()
  {
    cb_->OnChannelClosed(chnl_, node_);
    factory_->destroy(this);
  }

  void CloseChannelJob::Reset()
  {
    cb_ = 0;
    chnl_ = 0;
    node_ = 0;
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  CloseChannelJobFactory::CloseChannelJobFactory()
    :freedCount_(0),
    allocatedCount_(0)
  {
  }

  CloseChannelJobFactory::~CloseChannelJobFactory()
  {
    NI_ASSERT(allocatedCount_ == freedCount_, "");
  }

  CloseChannelJob* CloseChannelJobFactory::create()
  {
    CloseChannelJob* j = 0;
    if (free_.size())
    {
      j = free_.front();
      free_.pop_front();
    }
    else
    {
      j = new CloseChannelJob(this);
    }

    ++allocatedCount_;

    return j;
  }

  void CloseChannelJobFactory::destroy(CloseChannelJob* j)
  {
    if (!j)
      return;

    j->Reset();

    free_.push_front(j);
    ++freedCount_;
  }
}
