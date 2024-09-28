#pragma once
#include <System/SystemLog.h>
#include <RPC/RPC.h>
#include <RPC/GateKeeper.h>

namespace rpc
{

struct IfaceRequesterState
{
  enum Enum
  {
    NONE,
    INIT,
    OPENING,
    RPC_NODE_REQUESTED,
    RPC_IFACE_QUERIED,
    RPC_IFACE_CREATED,
    OPENED,
    CLOSED
  };
};

template<typename T>
class IfaceRequester;

template<typename T>
class IfaceRequesterCallback : public IBaseInterfaceMT
{
  NI_DECLARE_CLASS_1(IfaceRequesterCallback, IBaseInterfaceMT);

public:
  virtual void onChangeState(rpc::IfaceRequesterState::Enum st, StrongMT<rpc::IfaceRequester<T> > const & ifacereq) = 0;
};

template<typename T>
class IfaceRequester : public rpc::IGateKeeperCallback, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(IfaceRequester, rpc::IGateKeeperCallback, BaseObjectMT);

  StrongMT<rpc::GateKeeperBase> gk;
  Transport::TServiceId svcid_;
  nstl::string ifacename_;
  StrongMT<rpc::Node> rpcNode;
  StrongMT<T> iface_;
  IfaceRequesterState::Enum st;
  NLogg::CChannelLogger* logstrm;
  nstl::string logChnlNameBuf;
  char const * logChnlName;
  nstl::string password;
  WeakMT<IfaceRequesterCallback<T> > stcb_;
  nstl::vector<IfaceRequesterState::Enum> stateHistory;
  const static size_t MaxStateHistory = 16;
  NHPTimer::FTime retryTimeout_;
  NHPTimer::FTime retryTimeoutStartPoint_;
  NHPTimer::FTime queryIfaceTimeout_;

public:
  IfaceRequester(const char* _password=0)
    :st(IfaceRequesterState::INIT),
    logstrm( 0 ),
    logChnlName(0),
    retryTimeout_(0.0),
    retryTimeoutStartPoint_(0.0)
  {
    if (_password)
    {
      password = _password;
    }
    stateHistory.reserve( MaxStateHistory );
  }

  ~IfaceRequester()
  {
    close();
  }

  IfaceRequesterState::Enum PopNewState() {
    if ( stateHistory.empty() )
      return IfaceRequesterState::NONE;

    IfaceRequesterState::Enum result = stateHistory.front();
    stateHistory.erase( stateHistory.begin() );
    return result;
  }

private:
  void pushStateHistory( IfaceRequesterState::Enum _st )
  {
    if ( stateHistory.size() >= MaxStateHistory )
      return;

    stateHistory.push_back( _st );
  }

  void changeState(IfaceRequesterState::Enum _st)
  {
    if (_st != st)
    {
      st = _st;

      pushStateHistory( _st );

      if (IfaceRequesterState::CLOSED == st)
      {
        retryTimeoutStartPoint_ = NHPTimer::GetScalarTime();
      }

      StrongMT<IfaceRequesterCallback<T> > stcb = stcb_.Lock();
      if (stcb)
        stcb->onChangeState(_st, this);
    }
  }

public:
  int init( rpc::GateKeeperBase * _gk, Transport::TServiceId const & _svcid,
    char const * _ifacename = 0, NLogg::CChannelLogger* _logstrm = &::GetSystemLog(), char const * _chnlName = 0,
    IfaceRequesterCallback<T> * _stcb = 0, NHPTimer::FTime _retryTimeout = 2.0, NHPTimer::FTime _queryIfaceTimeout = 20.0)
  {
    logstrm = _logstrm;
    if (_chnlName)
    {
      logChnlNameBuf = _chnlName;
      logChnlName = logChnlNameBuf.c_str();
    }

    stcb_ = _stcb;
    retryTimeout_ = _retryTimeout;
    queryIfaceTimeout_ = _queryIfaceTimeout;

    int rc = -1;
    if (_gk)
    {
      gk = _gk;
      if (!_svcid.empty())
      {
        svcid_ = _svcid;

        if ( _ifacename && strlen( _ifacename ) ) //User wants Query<>, not Create<>
          ifacename_ = _ifacename;

        gk->attachNotificationCallback(this);
        rc = 0;
      }
      else
      {
        LOGL_E(logstrm, logChnlName).Trace("%s is FAILED: service id is empty", __FUNCTION__);
      }
    }
    else
    {
      LOGL_E(logstrm, logChnlName).Trace("%s is FAILED: gatekeeper is NULL", __FUNCTION__);
    }

    if (0 == rc)
    {
      rc = open();
    }
    return rc;
  }

  int open()
  {
    int rc = -1;
    if (IfaceRequesterState::INIT == st || IfaceRequesterState::CLOSED == st)
    {
      st = IfaceRequesterState::OPENING;
      rc = 0;
    }
    else
    if (IfaceRequesterState::OPENED == st)
    {
      rc = 1;
    }
    else
    if (IfaceRequesterState::OPENING == st)
    {
      rc = 2;
    }

    return rc;
  }

  int close()
  {
    if (IfaceRequesterState::CLOSED == st)
      return 1;

    iface_ = 0;
    rpcNode = 0;
    changeState(IfaceRequesterState::CLOSED);

    return 0;
  }

private:
  void oncall(T* result, int context, rpc::CallStatus status)
  {
    NI_ASSERT(st == IfaceRequesterState::RPC_IFACE_QUERIED || st == IfaceRequesterState::CLOSED, "");

    if (rpc::CallSuccessful == status)
    {
      if (result)
      {
        iface_ = result;
        changeState(IfaceRequesterState::OPENED);
        LOGL_M(logstrm, logChnlName).Trace( "Iface received. svcid=%s, iface=%s", svcid_.c_str(), ifacename_.c_str() );
      }
      else
      {
        close();
        LOGL_W(logstrm, logChnlName).Trace( "Iface received but NULL. svcid=%s, iface=%s, rpcsts=%s(%d)", svcid_.c_str(), ifacename_.c_str(), CallStatusToString( status ), (int)status);
      }
    }
    else
    {
      close();
      LOGL_E(logstrm, logChnlName).Trace( "Iface request FAILED due to rpc error. svcid=%s, iface=%s, rpcsts=%s(%d)", svcid_.c_str(), ifacename_.c_str(), CallStatusToString( status ), (int)status);
    }
  }

public:
  int step()
  {
    if (IfaceRequesterState::OPENED == st || IfaceRequesterState::INIT == st)
      return 0;

    if (IfaceRequesterState::CLOSED == st)
    {
      if (retryTimeoutStartPoint_ && retryTimeout_ && retryTimeoutStartPoint_ + retryTimeout_ > NHPTimer::GetScalarTime())
        return 0;
    }

    if (IfaceRequesterState::OPENING == st || IfaceRequesterState::CLOSED == st)
    {
      rpcNode = gk->RequestNode(svcid_);
      if (rpcNode)
      {
        changeState(IfaceRequesterState::RPC_NODE_REQUESTED);
        LOGL_M(logstrm, logChnlName).Trace("Node requested successfully(svcid=%s)", svcid_.c_str());
      }
    }

    if ( IfaceRequesterState::RPC_NODE_REQUESTED == st )
    {
      if ( ifacename_.empty() )
        _createInstance();
      else
        _requestInterface();
    }

    if ( IfaceRequesterState::RPC_IFACE_CREATED == st )
    {
      NI_VERIFY( iface_, "", return 0 );
      if ( iface_->GetStatus() == rpc::Connected )
      {
        LOGL_M( logstrm, logChnlName ).Trace("Remote interface successfully created(svcid=%s)", svcid_.c_str() );
        changeState( IfaceRequesterState::OPENED );
      }
    }

    return 0;
  }

  bool isopen() { return (IfaceRequesterState::OPENED == st); }

  StrongMT<T> const & iface() const { return iface_; }

  StrongMT<rpc::Node> const & node() const { return rpcNode; }

  Transport::TServiceId const & svcid() const { return this->svcid_; }

  nstl::string const & ifacename() const { return this->ifacename_; }

private:
  //rpc::IGateKeeperCallback
  void OnNewNode( Transport::IChannel * channel,  rpc::Node * node )
  {
  }

  //rpc::IGateKeeperCallback
  void OnChannelClosed( Transport::IChannel * channel,  rpc::Node * node )
  {
    if ( node == rpcNode.Get() )
    {
      close();
    }
  }

  //rpc::IGateKeeperCallback
  void OnCorruptData( Transport::IChannel * channel,  rpc::Node * node )
  {
    if ( node == rpcNode.Get() )
    {
      close();
    }
  }

  void _createInstance() {
    NI_ASSERT( IfaceRequesterState::RPC_NODE_REQUESTED == st, "" );
    NI_VERIFY( rpcNode, "", return );
    NI_VERIFY( ifacename_.empty(), "", return );

    iface_ = rpcNode->Create<T>();
    if ( !iface_ ) {
      LOGL_W(logstrm, logChnlName).Trace("can't create interface(svcid=%s iface=%s)", svcid_.c_str(), T::StaticClassName() );
      return;
    }

    changeState(IfaceRequesterState::RPC_IFACE_CREATED);
    LOGL_M(logstrm, logChnlName).Trace("create rpc interface(svcid=%s iface=%s)", svcid_.c_str(), T::StaticClassName() );
  }

  void _requestInterface() {
    NI_ASSERT( IfaceRequesterState::RPC_NODE_REQUESTED == st, "" );
    NI_VERIFY( rpcNode, "", return );
    NI_VERIFY( !ifacename_.empty(), "", return );

    if (!rpcNode->Query<T>(ifacename_.c_str(), this, &IfaceRequester<T>::oncall, 0, queryIfaceTimeout_, password.size()>0?password.c_str():0))
    {
      LOGL_W(logstrm, logChnlName).Trace("%s: can't query interface(svcid=%s iface=%s)", __FUNCTION__, svcid_.c_str(), ifacename_.c_str());
      return;
    }

    changeState(IfaceRequesterState::RPC_IFACE_QUERIED);
    LOGL_M(logstrm, logChnlName).Trace("Query rpc interface(svcid=%s iface=%s)", svcid_.c_str(), ifacename_.c_str());
  }
}; //class IfaceRequester

} //namespace rpc
