#pragma once
#include "System/TPJobIntf.h"

namespace Transport
{
  _interface IChannel;
}

namespace rpc
{
  class CloseChannelJobFactory;
  _interface IGateKeeperCallback;
  class Node;

  class CloseChannelJob : public threading::ITPJob
  {
  public:
    CloseChannelJob(CloseChannelJobFactory* factory);
    CloseChannelJob( IGateKeeperCallback * cb, Transport::IChannel * chnl, rpc::Node * node,
                    CloseChannelJobFactory* factory);
    ~CloseChannelJob();

  public:
    void Init( IGateKeeperCallback * cb, Transport::IChannel * chnl, rpc::Node * node );
    void Execute();
    void Reset();

  private:
    StrongMT<IGateKeeperCallback> cb_;
    StrongMT<Transport::IChannel> chnl_;
    StrongMT<rpc::Node> node_;
    CloseChannelJobFactory* factory_;
  };

  class CloseChannelJobFactory
  {
  public:
    CloseChannelJobFactory();
    ~CloseChannelJobFactory();

  public:
    CloseChannelJob* create();
    void destroy(CloseChannelJob* j);

  private:
    typedef list<CloseChannelJob*> Jobs;
    Jobs free_;
    int freedCount_;
    int allocatedCount_;
  };
}
