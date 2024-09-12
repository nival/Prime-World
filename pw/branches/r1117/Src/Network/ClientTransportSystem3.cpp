#include "transport/stdafx.h"
#include "ClientTransportSystem3.h"
#include "Network/FreePortsFinder.h"
#include "naio/Cfg.h"
#include "naio/Driver.h"
#include "transport/TLCfg.h"
#include "transport/TLTransportModule.h"
#include "transport/TLDefaultLogCallback.h"
#include "ClientTransportConfig.h"


namespace Transport
{
  ClientTransportSystem3::ClientTransportSystem3(Network::INetworkDriver* _pNetDriver, 
                                                 Transport::MessageFactory* _pFactory, 
                                                 Login::ClientVersion const & version, 
                                                 StrongMT<Transport::ITransportSystem> const & pts)
    : netDriver(_pNetDriver)
    , factory(_pFactory)
    , userId(-1)
    , loginResult( Login::ELoginResult::NoResult )
    , state( NotInitialized )
    , transport_(pts)
    , loginVersion_(version)
    , partialReconnectSupport_(false)
    , partialReconnectRetries_(0)
    , partialReconnectRetryTimeout_(0)
    , logtag_("[CTS3]")

  {
    loginClient = new Login::LoginClient( netDriver, version);
  }

  ClientTransportSystem3::~ClientTransportSystem3()
  {
    Logout();

    loginClient = 0;
  }

  void ClientTransportSystem3::Login( const Network::NetAddress& _loginServerAddress, const string& _login, const string& _password, 
    const string& _sessionKey, Login::LoginType::Enum _loginType )
  {
    if ( state == LoggingIn || state == ContactingRelay )
      return;

    Logout();
    state = LoggingIn;
    login = _login;
    loginServerAddress = _loginServerAddress;
    sessionKey_ = _sessionKey;
    loginClient->LoginRequest( loginServerAddress, login, _password, 0, _sessionKey, _loginType );
    loginResult = Login::ELoginResult::NoResult;
  }

  void ClientTransportSystem3::Logout()
  {
    DebugTrace( "Logout, userId=%d", userId );

    if (NotInitialized == state)
      return;

    state = NotInitialized;

    if (secondaryRelayCtx_)
    {
      LOG_M(0).Trace("%s closing secondary relay context(userId=%d)", logtag_, userId);
      secondaryRelayCtx_->close();
      secondaryRelayCtx_ = 0;
    }

    if ( relayChannel )
    {
      LOG_M(0).Trace("%s closing relay channel(userId=%d)", logtag_, userId);
      relayChannel->Close();
    }
    relayChannel = 0;

    if ( secondaryRelayChannel )
    {
      LOG_M(0).Trace("%s closing secondary relay channel(userId=%d)", logtag_, userId);
      secondaryRelayChannel->Close();
    }
    secondaryRelayChannel = 0;
  }

  EStatus::Enum ClientTransportSystem3::GetStatus()
  {
    switch( state )
    {
    case Failed:
      return EStatus::CRITICAL_FAIL;
    case Disconnected:
      return EStatus::FAIL;
    default:
      return EStatus::OK;
    }
  }

  void ClientTransportSystem3::SetupTransport()
  {
    state = ContactingRelay;

    if (!transport_)
    {
      TL::Cfg tlcfg;
      tlcfg.loglvl_ = Transport::ClientCfg::GetLogLevel();
      tlcfg.spLogMsgCb_.reset(new TL::LogCallback(::GetSystemLog()));
      tlcfg.mf_ = factory;
      tlcfg.disableNagleAlgorithm_ = Transport::ClientCfg::DisableNagleAlgorithm();
      tlcfg.read_block_size_ = Transport::ClientCfg::GetReadBlockSize();
      tlcfg.mbHeapDumpFreq_ = 0;  //  отключает дамп в лог message block heap'а
      tlcfg.checkActivityTimeout_ = Transport::ClientCfg::GetCheckConnectionActivityTimeout();

      tlcfg.threads_ = Transport::ClientCfg::GetNumberOfThreads();
      SYSTEM_INFO si;
      ::GetSystemInfo(&si);
      if ((DWORD)tlcfg.threads_ > si.dwNumberOfProcessors)
        tlcfg.threads_ = 0;

      StrongMT<TL::TransportModule> sptm = new TL::TransportModule;
      if (sptm->Init(tlcfg))
      {
        transport_ = sptm.Get();
      }
    }

    if (transport_)
    {
      LOG_M(0).Trace("%s connecting to relay server (addr=%s login=%s)", logtag_, relayAddress.c_str(), login.c_str());

      relayChannel = transport_->OpenChannelDirect(Transport::Address( Transport::ENetInterface::FrontEnd, userId ), 
          sessionId,
          relayAddress);

      if ( relayChannel )
      {
        relayChannel->KeepAlivePeriod(Transport::ClientCfg::GetKeepalivePeriod());

        if (!secondaryRelayAddress.empty() && relayAddress != secondaryRelayAddress)
        {
          LOG_M(0).Trace("%s connecting to secondary-relay server(addr=%s login=%s)", 
            logtag_, secondaryRelayAddress.c_str(), login.c_str());

          secondaryRelayChannel = transport_->OpenChannelDirect(Transport::Address( Transport::ENetInterface::FrontEnd, userId ), 
            sessionId,
            secondaryRelayAddress);

          if (secondaryRelayChannel)
            secondaryRelayChannel->KeepAlivePeriod(Transport::ClientCfg::GetKeepalivePeriod());
          else
          {
            LOG_M(0).Trace("%s cannot open channel to secondary-relay server(addr=%s login=%s)", 
              logtag_, secondaryRelayAddress.c_str(), login.c_str());
            loginResult = Login::ELoginResult::ServerError;
            state = Failed;
          }
        }
      }
      else
      {
        LOG_M(0).Trace("%s: cannot open channel to relay server(addr=%s login=%s)", 
          logtag_, relayAddress.c_str(), login.c_str());
        loginResult = Login::ELoginResult::ServerError;
        state = Failed;
      }
    }
    else
    {
      LOG_C(0).Trace("%s Can't initialize transport module(login=%s)", logtag_, login.c_str());
    }
  }

  bool ClientTransportSystem3::Work()
  {
    switch( state )
    {
      case NotInitialized:
        return true;

      case LoggingIn:
        {
          loginResult = loginClient->Step();

          if( loginResult == Login::ELoginResult::NoResult )
            return true;

          if ( loginResult == Login::ELoginResult::Success )
          {
            string relayCert;
            loginClient->GetConnectionData( &relayAddress, &secondaryRelayAddress, &userId, &sessionId, &relayCert, &sessionPath, 
              &partialReconnectSupport_, &partialReconnectRetries_, &partialReconnectRetryTimeout_ );
            LOG_M(0).Trace("%s: login accepted, userid=%d relay=%s secondaryrelay=%s partial_reconnect_support=%d partial_reconnect_retries=%d partial_reconnect_retry_timeout=%d",
              logtag_, userId, relayAddress.c_str(), secondaryRelayAddress.c_str(), partialReconnectSupport_, partialReconnectRetries_, partialReconnectRetryTimeout_);

            SetupTransport();
          }
          else 
          {
            switch( loginResult )
            {
            case Login::ELoginResult::NoConnection:
              LOG_M(0).Trace("%s cannot connect to login server(netaddr=%s login=%s)", logtag_, loginServerAddress.c_str(), login.c_str());
              state = Disconnected;
              break;
            case Login::ELoginResult::Refused:
              LOG_M(0).Trace("%s login refused (netaddr=%s login=%s)", logtag_, loginServerAddress.c_str(), login.c_str());
              state = Disconnected;
              break;
            case Login::ELoginResult::AlreadyIn:
              LOG_M(0).Trace("%s user with same login already logged in(netaddr=%s login=%s", logtag_, loginServerAddress.c_str(), login.c_str());
              state = Failed;
              break;
            case Login::ELoginResult::ServerError:
              LOG_M(0).Trace("%s internal server error(login=%)", logtag_, login.c_str());
              state = Failed;
              break;
            case Login::ELoginResult::ClientOutdated:
              LOG_M(0).Trace("%s  client is outdated. Update to newer version", logtag_);
              state = Failed;
              break;
            case Login::ELoginResult::ServerOutdated:
              LOG_M(0).Trace("%s server is outdated. Update server to newer version or connect to another server", logtag_);
              state = Failed;
              break;
            }
          }
          return true;
        }

      case ContactingRelay:
        {
          if (relayChannel->GetStatus() == Network::ConnectionState::Closed)
          {
            LOG_M(0).Trace("%s cannot connect to relay server(login=%s)", logtag_, login.c_str());
            loginResult = Login::ELoginResult::ServerError;
            state = Failed;
            return true;
          }

          if (secondaryRelayChannel && secondaryRelayChannel->GetStatus() == Network::ConnectionState::Closed)
          {
            LOG_M(0).Trace("%s cannot connect to secondary relay server(login=%s)", logtag_, login.c_str());
            loginResult = Login::ELoginResult::ServerError;
            state = Failed;
            return true;
          }

          if (relayChannel->GetStatus() == Network::ConnectionState::Connecting)
            return true;

          if (secondaryRelayChannel && secondaryRelayChannel->GetStatus() == Network::ConnectionState::Connecting)
            return true;

          LOG_M(0).Trace("%s started successfully(login=%s)", logtag_, login.c_str());
          state = Working;

          return true;
        }
      case Working:
        {
          if (secondaryRelayChannel && secondaryRelayChannel->GetStatus() == Network::ConnectionState::Connected)
          {
            if (!secondaryRelayCtx_ && partialReconnectSupport_)
            {
              secondaryRelayCtx_ = new SecondaryRelayCtx(netDriver, loginVersion_, transport_);
              secondaryRelayCtx_->open(secondaryRelayChannel, loginServerAddress, login, "", sessionKey_, partialReconnectRetries_, partialReconnectRetryTimeout_);
              secondaryRelayChannel = 0;
            }
          }

          if (secondaryRelayCtx_)
          {
            secondaryRelayCtx_->step();

            if (secondaryRelayCtx_->isclosed())
            {
              LOG_M(0).Trace("%s: secondary relay context is closed", logtag_);

              if (relayChannel)
                relayChannel->Close();
            }
          }

          if (relayChannel && relayChannel->GetStatus() == Network::ConnectionState::Closed)
          {
            LOG_M(0).Trace("%s relay channel is closed", logtag_);
            state = Failed;
          }

          if (secondaryRelayChannel && secondaryRelayChannel->GetStatus() == Network::ConnectionState::Closed)
          {
            LOG_M(0).Trace("%s secondary relay channel is closed", logtag_);
            state = Failed;
          }

          return true;
        }

      default:
      case Failed:
        //Stopping thread, we donno wonna it
        return false;
    }
  }



  StrongMT<Transport::IChannel> ClientTransportSystem3::OpenChannel( Transport::TServiceId interfaceId, unsigned int pingperiod, unsigned int to )
  {
    if ( state != Working )
      return 0;

    StrongMT<Transport::IChannel> spchnl;
    Transport::TServiceId svcls;
    if (Transport::GetServiceClass(interfaceId, svcls))
    {
      if (Transport::TServiceId("gamesvc") == svcls)
        spchnl = transport_->OpenChannelDirect(Transport::Address( interfaceId, userId ), sessionId, relayAddress, pingperiod, to);
      else
        spchnl = transport_->OpenChannelDirect(Transport::Address( interfaceId, userId ), sessionId, secondaryRelayAddress, pingperiod, to);
    }
    else
    {
      LOG_E(0).Trace("%s OpenChannel: can't get svc class from svcid(svcid=%s)", logtag_, interfaceId.c_str());
    }
    return spchnl;
  }

  Login::ELoginResult::Enum ClientTransportSystem3::GetLoginResult() const
  {
    if ( state == Working )
      return Login::ELoginResult::Success;
    if( state == LoggingIn || state == ContactingRelay )
      return Login::ELoginResult::NoResult;
    return loginResult;
  }

  void ClientTransportSystem3::Step()
  {
    Work();
  }

  void ClientTransportSystem3::GetNewAcceptedChannels(vector<StrongMT<Transport::IChannel>> & _chnls)
  {
    StrongMT<Transport::IChannelListener> cl = transport_->GetDefaultChannelListener();
    cl->GetNewConnections(&_chnls);
  }
}
