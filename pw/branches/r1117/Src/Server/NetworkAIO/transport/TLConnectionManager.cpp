#include "transport/stdafx.h"
#include "transport/TLConnectionManager.h"
#include <ace/INET_Addr.h>
#include <ace/Guard_T.h>
#include "transport/TLConnection.h"
#include <naio/Driver.h>
#include <naio/ConnectionContext.h>
#include "transport/TLChannelListener.h"
#include "transport/TLChannel.h"

namespace TransportLayer
{
  unsigned long long keyAcceptedConnections_(ACE_INET_Addr const & addr)
  {
    unsigned long long key = (unsigned long long)(addr.get_ip_address()) << 16;
    key |= (unsigned long long)(addr.get_port_number());
    return key;
  }

  ConnectionManager::ConnectionManager()
  {
  }

  ConnectionManager::ConnectionManager(naio::DriverSP const & spdrv, TL::MessageBlockFactorySP const & mbf) :
  spdrv_(spdrv),
  mbf_(mbf),
  defaultChannelListener_( new ChannelListener(Transport::EmptySvcId, ACE_INET_Addr()) )
  {
  }

  ConnectionManager::~ConnectionManager()
  {
  }

  TL::ConnectionSP ConnectionManager::FindConnection_(nstl::string const & naddr)
  {
    NI_PROFILE_BLOCK(__FUNCTION__);

    ConnectionsT::iterator it = connections_.find(naddr);
    if (it != connections_.end())
    {
      if (TL::IsValid(it->second) && Connection::CLOSED != it->second->status())
          return it->second;

      connections_.erase(it);
    }

    return TL::ConnectionSP();
  }

  ConnectionSP ConnectionManager::OpenConnection(Network::NetAddress const & naddr,
    Transport::TServiceId const & svcid)
  {
    NI_PROFILE_BLOCK(__FUNCTION__);

    ACE_DEBUG((LM_TRACE, ACE_TEXT("%s"), __FUNCTION__));

    ACE_Guard<ACE_Thread_Mutex>  lock(connectionsMutex_);

    {
      TL::ConnectionSP spconn = FindConnection_(naddr);
      if (TL::IsValid(spconn))
        return spconn;
    }

    if (TL::IsValid(spCurrentConnection_) && naddr == spCurrentConnection_->netaddr())
      return spCurrentConnection_;

    if (!svcid.empty())
    {
      Peername2ConnectionT::const_iterator cit = peername2connection_.find(svcid);
      if (cit != peername2connection_.end())
      {
        TL::ConnectionSP spconn = cit->second;
        if (TL::IsValid(spconn))
          return spconn;
      }
    }

    for (Connections2OpenListT::iterator it = conns2open_.begin(); 
        it != conns2open_.end();
        ++it)
    {
      if ((*it)->netaddr() == naddr)
        return *it;
    }

    TL::ConnectionSP spconn(new TL::Connection(naddr, svcid, true, GetStrongFromThis(this)));
    spconn->init(spconn);
    spconn->setMessageBlockFactory(mbf_);

    //  establish connection
    if (spCurrentConnection_.null())
    {
      naio::ConnectionContextStrongPtr spconnctx = 
        spdrv_->OpenConnection(ACE_INET_Addr(spconn->netaddr().c_str()), new AsynchCompletionPointer<Connection>(spconn));
      spconn->connectionContext(spconnctx);
      spCurrentConnection_ = spconn;
    }
    else
    { //  enqueue open connection request
      conns2open_.push_back(spconn);
    }

    return spconn;
  }

  void ConnectionManager::CloseConnection_(TL::ConnectionSP const & spconn, bool active)
  {
    NI_PROFILE_BLOCK(__FUNCTION__);

    ACE_DEBUG((LM_TRACE, ACE_TEXT("%s"), __FUNCTION__));

    if (spconn->activelyEstablished())
    {
      ConnectionsT::iterator it = connections_.find(spconn->netaddr());
      if (it != connections_.end())
      {
        spdrv_->CloseConnection(spconn->connectionContext());
        connections_.erase(it);
      }
    }
    else
    {
      
      AcceptedConnectionsT::iterator it = acceptedConnections_.find(keyAcceptedConnections_(spconn->remoteAddr()));
      if (it != acceptedConnections_.end())
      {
        spdrv_->CloseConnection(spconn->connectionContext());
        acceptedConnections_.erase(it);
      }
    }
  }

  void ConnectionManager::CloseConnection(TL::ConnectionSP const & spconn, bool active)
  {
    NI_PROFILE_BLOCK(__FUNCTION__);

    ACE_Guard<ACE_Thread_Mutex>  lock(connectionsMutex_);
    CloseConnection_(spconn, active);
  }

  void ConnectionManager::OnConnectionEstablished(bool success, bool isactive, 
    naio::ConnectionContextStrongPtr const & spconnctx, TL::MessageBlockFactorySP const & spmbf)
  {
    NI_PROFILE_BLOCK(__FUNCTION__);

    ACE_DEBUG((LM_TRACE, ACE_TEXT("%s"), __FUNCTION__));

    ACE_Guard<ACE_Thread_Mutex>  lock(connectionsMutex_);

    if (isactive)
    {
      TL::ConnectionSP spconn = reinterpret_cast<AsynchCompletionPointer<TL::Connection>*>(spconnctx->userContext())->sp_;
      if (success)
      {
        spmbf->tag(spconn->id());
        spconn->setMessageBlockFactory(spmbf);
        spconn->channelListener( defaultChannelListener_ );
        spconn->status(TL::Connection::CONNECTED);
        std::pair<ConnectionsT::iterator, bool> res = connections_.insert(std::make_pair(spconn->netaddr(), spconn));
        NI_ASSERT(res.second, NI_STRFMT("Connection to %s already exists", spconn->netaddr().c_str()));
        if ( !res.second )
        {
          TL::ConnectionSP wrongConn = res.first->second;
          DebugTrace( "Prev conn svcid=%s", wrongConn->svcid().c_str() );
        }
      }
      else
      {
        ACE_ERROR((LM_ERROR, ACE_TEXT("[TL] Open connection is FAILED(netaddr=%s)"), spconn->netaddr().c_str()));
        spconn->status(TL::Connection::CLOSED);
      }

      if (conns2open_.size())
      {
        TL::ConnectionSP spc = conns2open_.front();
        do
        {
          conns2open_.pop_front();
          if (TL::IsValid(spc))
          {
            naio::ConnectionContextStrongPtr spconnctx = 
              spdrv_->OpenConnection(ACE_INET_Addr(spc->netaddr().c_str()), 
              new AsynchCompletionPointer<TL::Connection>(spc.get()));
            spc->connectionContext(spconnctx);
            spCurrentConnection_ = spc;
          }

          if (conns2open_.size())
            spc = conns2open_.front();
          else
            spc.reset(0);
        }
        while(TL::IsValid(spc));
      }
      else
      {
        spCurrentConnection_.reset();
      }
    }
    else
    {
      if (!spconnctx->invalid())
      {
        TL::ConnectionSP spconn(new TL::Connection("", "", isactive, GetStrongFromThis(this)));
        spconn->init(spconn);
        spmbf->tag(spconnctx->connid());
        spconn->setMessageBlockFactory(spmbf);
        spconn->channelListener(reinterpret_cast<AsynchCompletionPointer2<TL::ChannelListenerInternal, TL::ConnectionManager>*>(spconnctx->userContext())->sp1_);
        spconn->connectionContext(spconnctx);
        spconnctx->userContext(new AsynchCompletionPointer<TL::Connection>(spconn));

        ACE_INET_Addr remote = spconnctx->remoteAddr();
        ACE_INET_Addr local = spconnctx->localAddr();
        spconn->setAddresses(local, remote);
        spconn->status(TL::Connection::CONNECTED);

        bool res = acceptedConnections_.insert(std::make_pair(keyAcceptedConnections_(spconn->remoteAddr()), spconn)).second;
        NI_ASSERT(res, NI_STRFMT("Accepted connection (%s) already exists", remote.get_host_addr()));
        //  FIXME: handle this situation correctly
      }
      else
      {
        NI_ALWAYS_ASSERT(NI_STRFMT("Channel context MUST be NOT NULL"));
      }
    }
  }

  naio::AcceptorHandle ConnectionManager::OpenAcceptor(Network::NetAddress const & naddr)
  {
    NI_PROFILE_BLOCK(__FUNCTION__);

    ACE_INET_Addr addr;
    if (addr.set(naddr.c_str()) < 0)
      return naio::AcceptorHandle();

    return spdrv_->OpenAcceptor(addr, new AsynchCompletionPointer<TL::ConnectionManager>(GetStrongFromThis(this)));
  }

  void ConnectionManager::CloseAcceptor(naio::AcceptorHandle const & handle)
  {
    NI_PROFILE_BLOCK(__FUNCTION__);

    if (handle.valid())
    {
      void* userctx = handle.userContext();
      if (userctx)
      {
        delete reinterpret_cast<AsynchCompletionPointer<TL::ConnectionManager>*>(userctx);
      }
    }

    spdrv_->CloseAcceptor(handle);
  }

  void ConnectionManager::Peername2Connection(Transport::TServiceId const & _svcid, ConnectionWP const & _conn)
  {
    ACE_Guard<ACE_Thread_Mutex>  lock(connectionsMutex_);
    peername2connection_[_svcid] = _conn;
  }
}
