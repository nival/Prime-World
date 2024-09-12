#pragma once
#include "naio/BaseProtocolFactory.h"
#include "naio/ChannelManager.h"
#include "naio/Channel.h"
#include "naio/Types.h"
#include "naio/AcceptorHandle.h"

namespace Terabit
{
  class ChannelConnector;
}


namespace naio
{
  class Connector;
  class IProtocolHandler;
  class Cfg;

  class Driver
  {
  public:
    Driver();
    ~Driver();

  public:
    bool Init(Cfg const & cfg);
    void Fini();

  public:
    ConnectionContextStrongPtr OpenConnection(ACE_INET_Addr const & addr, void* act);
    void CloseConnection(ConnectionContextStrongPtr const & pctx);

    AcceptorHandle OpenAcceptor(ACE_INET_Addr const & addr, void* userContext);
    void CloseAcceptor(AcceptorHandle const & handle);

  private:
    bool InitLog(Cfg const & cfg);
    void FiniLog();

  private:
    ChannelFactory<Channel> chnlFactory_;
    naio::BaseProtocolFactory protoFactory_;
    Terabit::IOThreadPool*   tp_;
    ChannelManager* chnlManager_;
    Connector* connector_;
    naio::IProtocolHandlerFactory* handlerFactory_;
    LogMsgCallbackSP  spLogMsgCb_;
    int logflags_;

    typedef std::map<unsigned long, naio::AcceptorStrongPtr> AcceptorsMapT;
    AcceptorsMapT acceptors_;
    ACE_Atomic_Op<ACE_Thread_Mutex, long> initialized_;
  };
}
