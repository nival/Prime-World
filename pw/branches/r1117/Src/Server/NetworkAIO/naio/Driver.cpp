#include "naio/stdafx.h"
#include "Driver.h"
#include <IOTerabit/ChannelConnector.h>
#include "Cfg.h"
#include "naio/ProtocolHandler.h"
#include "naio/Ops.h"
#include "naio/ConnectionContext.h"
#include "naio/Connector.h"
#include "naio/ThreadPool.h"
#include "naio/Acceptor.h"

namespace naio
{
  Driver::Driver()
    :protoFactory_("naioProtocolFactory", 0),
    tp_(0),
    chnlManager_(0),
    connector_(0),
    logflags_(0),
    initialized_(0)
  {
  }

  Driver::~Driver()
  {
    Fini();
  }

  bool
  Driver::Init(Cfg const & cfg)
  {
    if (initialized_ != 0)
    {
      ACE_ERROR((LM_ERROR, ACE_TEXT("[naio] Already initialized")));
      return true;
    }

    if (ACE::init() < 0)
    {
      ACE_ERROR((LM_ERROR, ACE_TEXT("[naio]Can't initialize ACE framework")));
      return false;
    }

    ACE_DEBUG((LM_INFO, ACE_TEXT("[naio] ACE::init()")));

    if (!InitLog(cfg))
    {
      ACE_ERROR((LM_ERROR, ACE_TEXT("[naio] Log initialization is FAILED")));
      return false;
    }
    ACE_DEBUG((LM_INFO, ACE_TEXT("[naio] InitLog Ok")));

    if (cfg.phf_)
    {
      if (protoFactory_.setProtocolHandlerFactory(cfg.phf_))
        return false;
    }
    else
      return false;

    //  thread pool size
    unsigned int threads = cfg.threads_;
    if (0 == threads)
      threads = ACE_OS::num_processors();

    // IO Thread Pool for Channels, Acceptors, Connectors
    tp_ = new naio::ThreadPool("naioThreadPool", cfg.spLogMsgCb_.get());
    TRB_Proactor* pro = tp_->get_proactor();
    if (!pro)
    {
      ACE_ERROR((LM_ERROR, ACE_TEXT("[naio] Thread pool creation is FAILED")));
      return false;
    }

    ACE_DEBUG((LM_INFO, ACE_TEXT("[naio] Thread pool is created")));

    chnlManager_ = new ChannelManager("naioChannelManager", *tp_, chnlFactory_);
    chnlManager_->set_log_level(cfg.terabit_loglvl_);
    chnlManager_->readBlockSize(cfg.read_block_size_);
    chnlManager_->soRcvbuf(cfg.so_rcvbuf_);
    chnlManager_->soSndbuf(cfg.so_sndbuf_);
    chnlManager_->disableNagleAlgorithm(cfg.disableNagleAlgorithm_);
    chnlManager_->soKeepalive(cfg.so_keepalive_);
    chnlManager_->connectionsActivityTimeout(cfg.checkActivityTimeout_);
    chnlManager_->logWrittenBytes(cfg.logWrittenBytes_);
    ACE_DEBUG((LM_INFO, ACE_TEXT("[naio] ChannelManager is created")));

    connector_ = new Connector(*tp_, protoFactory_, *chnlManager_);
    ACE_DEBUG((LM_INFO, ACE_TEXT("[naio] Connector is created")));

    int rc = tp_->start(threads);
    if (rc < 0)
    {
      ACE_ERROR((LM_ERROR, ACE_TEXT("[naio] Thread pool start is FAILED(threads=%d)"), threads));
      return false;
    }
    ACE_DEBUG((LM_INFO, ACE_TEXT("[naio] Thread pool is started")));

    rc = chnlManager_->open();
    if (rc < 0)
    {
      ACE_ERROR((LM_ERROR, ACE_TEXT("[naio] ChannelManager open is FAILED")));
      return false;
    }
    ACE_DEBUG((LM_INFO, ACE_TEXT("[naio] ChannelManager is opened")));

    ++initialized_;
    return true;
  }

  void
  Driver::Fini()
  {
    if (initialized_ <= 0)
    {
      return;
    }

    --initialized_;

    if (acceptors_.size())
    {
      for (AcceptorsMapT::iterator it = acceptors_.begin();
        it != acceptors_.end(); ++it)
      {
        it->second->cancel();
      }

      for (AcceptorsMapT::iterator it = acceptors_.begin();
        it != acceptors_.end(); ++it)
      {
        it->second->wait();
      }

      acceptors_.clear();
    }

    if (connector_)
    {
      connector_->cancel();
      connector_->wait();
      delete connector_;
      connector_ = 0;
    }

    if (chnlManager_)
    {
      chnlManager_->close();
      chnlManager_->wait();
      delete chnlManager_;
      chnlManager_ = 0;
    }

    if (tp_)
    {
      tp_->stop();
      delete tp_;
      tp_ = 0;
    }


    FiniLog();
    spLogMsgCb_.reset(0);

    ACE::fini();
  }

  bool
  Driver::InitLog(Cfg const & cfg)
  {
    //  init log level
    int loglevel = cfg.loglvl_;
    u_long logmask = u_long(-1);
    if (3 == loglevel)
      logmask = LM_WARNING | LM_ERROR | LM_CRITICAL;
    else
    if (2 == loglevel)
      logmask = LM_INFO | LM_NOTICE | LM_WARNING | LM_ERROR | LM_CRITICAL;
    else
    if (1 == loglevel)
      logmask = LM_DEBUG | LM_INFO | LM_NOTICE | LM_WARNING | LM_ERROR | LM_CRITICAL;
    else
    if (0 == loglevel)
      logmask = LM_TRACE | LM_DEBUG | LM_INFO | LM_NOTICE | LM_WARNING | LM_ERROR | LM_CRITICAL;

    ACE_LOG_MSG->priority_mask (logmask, ACE_Log_Msg::PROCESS);


    spLogMsgCb_ = cfg.spLogMsgCb_;
    if (!spLogMsgCb_.null())
    {
      logflags_ = ACE_LOG_MSG->flags();
      ACE_LOG_MSG->set_flags (ACE_Log_Msg::MSG_CALLBACK);
      ACE_LOG_MSG->clr_flags (ACE_Log_Msg::STDERR);
      ACE_LOG_MSG->msg_callback (spLogMsgCb_.get());
    }

    return true;
  }

  void Driver::FiniLog()
  {
    if (!spLogMsgCb_.null())
    {
      ACE_LOG_MSG->clr_flags(ACE_Log_Msg::MSG_CALLBACK);
      ACE_LOG_MSG->msg_callback(0);
      ACE_LOG_MSG->set_flags (logflags_);
    }
  }

  ConnectionContextStrongPtr
  Driver::OpenConnection(ACE_INET_Addr const & addr, void* act)
  {
    ConnectionContextStrongPtr connctx(new ConnectionContext(act));
    Ptr<OpenConnectionOp> ocop(new OpenConnectionOp(addr, connctx));
    ocop->addRef();
    int rc = connector_->start(addr, (void*)ocop.get());
    if (rc < 0)
    {
      ocop->releaseRef();
      return ConnectionContextStrongPtr();
    }

    return connctx;
  }

  void Driver::CloseConnection(ConnectionContextStrongPtr const & spctx)
  {
    Ptr<CloseConnectionOp> ccop(new CloseConnectionOp(spctx));
    int rc = ccop->Post();
    if (rc < 0)
    {
      ACE_ERROR((LM_ERROR, ACE_TEXT("[naio] Can't post CloseConnection operation(rc=%d)"), rc));
    }
  }

  AcceptorHandle Driver::OpenAcceptor(ACE_INET_Addr const & addr, void* userContext)
  {
    AcceptorsMapT::iterator it = acceptors_.find(addr.hash());
    if (acceptors_.end() != it)
    {
      return AcceptorHandle(it->second, addr, userContext);
    }

    AcceptorStrongPtr spAcceptor(new naio::Acceptor(*tp_, protoFactory_, *chnlManager_));
    int rc = spAcceptor->start(addr, userContext, 20);
    if (rc < 0)
    {
      ACE_ERROR((LM_ERROR, ACE_TEXT("[naio] Can't start acceptor(rc=%d port=%d)"), rc, addr.get_port_number()));
      return AcceptorHandle();
    }

    acceptors_.insert(std::make_pair(addr.hash(), spAcceptor));
    return AcceptorHandle(spAcceptor, addr, userContext);
  }

  void Driver::CloseAcceptor(AcceptorHandle const & handle)
  {
    AcceptorsMapT::iterator it = acceptors_.find(handle.address().hash());
    if (acceptors_.end() != it)
    {
      it->second->cancel();
      it->second->wait();
      acceptors_.erase(it);
    }
  }
}
