#include "transport/stdafx.h"
#include "ClientTransportSystem2.h"
#include "Network/FreePortsFinder.h"
#include "naio/Cfg.h"
#include "naio/Driver.h"
#include "transport/TLCfg.h"
#include "transport/TLTransportModule.h"
#include "transport/TLDefaultLogCallback.h"
#include "ClientTransportConfig.h"

namespace Transport
{
  ClientTransportSystem2::ClientTransportSystem2(Network::INetworkDriver* _pNetDriver, 
    Transport::MessageFactory* _pFactory, 
    Login::ClientVersion const & version)
    : netDriver(_pNetDriver)
    , factory(_pFactory)
    , userId(-1)
    , loginResult( Login::ELoginResult::NoResult )
    , state( NotInitialized )
  {
    loginClient = new Login::LoginClient( netDriver, version );
  }

  ClientTransportSystem2::ClientTransportSystem2(Network::INetworkDriver* _pNetDriver, 
                                                 Transport::MessageFactory* _pFactory, 
                                                 Login::ClientVersion const & version, 
                                                 StrongMT<Transport::ITransportSystem> const & pts)
    : netDriver(_pNetDriver)
    , factory(_pFactory)
    , userId(-1)
    , loginResult( Login::ELoginResult::NoResult )
    , state( NotInitialized )
    , transport_(pts)
  {
    loginClient = new Login::LoginClient( netDriver, version);
  }

  ClientTransportSystem2::~ClientTransportSystem2()
  {
    Logout();

    loginClient = 0;
  }

  void ClientTransportSystem2::Login( const Network::NetAddress& _loginServerAddress, const string& _login, const string& _password,
    const string& _sessionKey, Login::LoginType::Enum _loginType )
  {
    if ( state == LoggingIn || state == ContactingRelay )
      return;

    Logout();
    state = LoggingIn;
    login = _login;
    loginServerAddress = _loginServerAddress;
    loginClient->LoginRequest( loginServerAddress, login, _password, 0, _sessionKey, _loginType );
    loginResult = Login::ELoginResult::NoResult;
  }

  void ClientTransportSystem2::Logout()
  {
    DebugTrace( "Logout, userId=%d", userId );

    if (NotInitialized == state)
      return;

    state = NotInitialized;

    if ( relayChannel )
    {
      LOG_M(0) << "Closing relay channel for client " << userId;
      relayChannel->Close();
    }
    relayChannel = 0;

    if ( secondaryRelayChannel )
    {
      LOG_M(0) << "Closing secondary-relay channel for client " << userId;
      secondaryRelayChannel->Close();
    }
    secondaryRelayChannel = 0;
  }

  EStatus::Enum ClientTransportSystem2::GetStatus()
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

  void ClientTransportSystem2::SetupTransport()
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

      StrongMT<TL::TransportModule> sptm(new TL::TransportModule);
      if (sptm->Init(tlcfg))
      {
        transport_ = sptm.Get();
      }
    }

    if (transport_)
    {
      systemLog( NLogg::LEVEL_MESSAGE ).Trace("Client2: connecting to relay server (addr=%s login=%s)", 
        relayAddress.c_str(), login.c_str());

      relayChannel = transport_->OpenChannelDirect(Transport::Address( Transport::ENetInterface::FrontEnd, userId ), 
          sessionId,
          relayAddress);

      if ( relayChannel )
      {
        relayChannel->KeepAlivePeriod(Transport::ClientCfg::GetKeepalivePeriod());

        if (!secondaryRelayAddress.empty() && relayAddress != secondaryRelayAddress)
        {
          systemLog( NLogg::LEVEL_MESSAGE ).Trace("Client2: connecting to secondary-relay server(addr=%s login=%s)", 
            secondaryRelayAddress.c_str(), login.c_str());

          secondaryRelayChannel = transport_->OpenChannelDirect(Transport::Address( Transport::ENetInterface::FrontEnd, userId ), 
            sessionId,
            secondaryRelayAddress);

          if (secondaryRelayChannel)
            secondaryRelayChannel->KeepAlivePeriod(Transport::ClientCfg::GetKeepalivePeriod());
          else
          {
            systemLog( NLogg::LEVEL_MESSAGE ).Trace("Client2: cannot open channel to secondary-relay server(addr=%s login=%s)", 
              secondaryRelayAddress.c_str(), login.c_str());
            loginResult = Login::ELoginResult::ServerError;
            state = Failed;
          }
        }
      }
      else
      {
        systemLog( NLogg::LEVEL_MESSAGE ).Trace("Client2: cannot open channel to relay server(addr=%s login=%s)", 
          relayAddress.c_str(), login.c_str());
        loginResult = Login::ELoginResult::ServerError;
        state = Failed;
      }
    }
    else
    {
      systemLog( NLogg::LEVEL_CRITICAL ) << "Can't initialize transport module" << ", login=" << login;
    }
  }


  bool ClientTransportSystem2::Work()
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
            loginClient->GetConnectionData( &relayAddress, &secondaryRelayAddress, &userId, &sessionId, &relayCert, &sessionPath );
            systemLog( NLogg::LEVEL_MESSAGE ) << "Client2: login accepted, userid=" << userId << 
              " relay=" << relayAddress << " secondary-relay=" << secondaryRelayAddress << endl;

            SetupTransport();
          }
          else 
          {
            switch( loginResult )
            {
            case Login::ELoginResult::NoConnection:
              systemLog( NLogg::LEVEL_MESSAGE ) << "Client2: cannot connect to login server at " << loginServerAddress << ", login=" << login;
              state = Disconnected;
              break;
            case Login::ELoginResult::Refused:
              systemLog( NLogg::LEVEL_MESSAGE ) << "Client2: login refused on login server at " << loginServerAddress << ", login=" << login;
              state = Disconnected;
              break;
            case Login::ELoginResult::AlreadyIn:
              systemLog( NLogg::LEVEL_MESSAGE ) << "Client2: user with same login already connected at " << loginServerAddress << ", login=" << login;
              state = Failed;
              break;
            case Login::ELoginResult::ServerError:
              systemLog( NLogg::LEVEL_MESSAGE ) << "Client2: internal server error, login=" << login;
              state = Failed;
              break;
            case Login::ELoginResult::ClientOutdated:
              systemLog( NLogg::LEVEL_MESSAGE ) << "Client2: client is outdated. Update to newer version" << endl;
              state = Failed;
              break;
            case Login::ELoginResult::ServerOutdated:
              systemLog( NLogg::LEVEL_MESSAGE ) << "Client2: server is outdated. Update server to newer version or connect to another server." << endl;
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
            systemLog( NLogg::LEVEL_MESSAGE ) << "Client2: cannot connect to relay server, login=" << login;
            loginResult = Login::ELoginResult::ServerError;
            state = Failed;
            return true;
          }

          if (secondaryRelayChannel && secondaryRelayChannel->GetStatus() == Network::ConnectionState::Closed)
          {
            systemLog( NLogg::LEVEL_MESSAGE ) << "Client2: cannot connect to secondary-relay server, login=" << login;
            loginResult = Login::ELoginResult::ServerError;
            state = Failed;
            return true;
          }

          if (relayChannel->GetStatus() == Network::ConnectionState::Connecting)
            return true;

          if (secondaryRelayChannel && secondaryRelayChannel->GetStatus() == Network::ConnectionState::Connecting)
            return true;

          systemLog( NLogg::LEVEL_MESSAGE ) << "Client2: started successfully, login=" << login;
          state = Working;
          return true;
        }
      case Working:
        {
          if (relayChannel && relayChannel->GetStatus() == Network::ConnectionState::Closed)
          {
            systemLog( NLogg::LEVEL_MESSAGE ) << "Client2: relay channel is closed";
            state = Failed;
          }

          if (secondaryRelayChannel && secondaryRelayChannel->GetStatus() == Network::ConnectionState::Closed)
          {
            systemLog( NLogg::LEVEL_MESSAGE ) << "Client2: secondary relay channel is closed";
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



  StrongMT<Transport::IChannel> ClientTransportSystem2::OpenChannel( Transport::TServiceId interfaceId, unsigned int pingperiod, unsigned int to )
  {
    if ( state != Working )
    {
      systemLog( NLogg::LEVEL_WARNING ).Trace("%s: client transport system is not in working state(svcid=%s)", __FUNCTION__, interfaceId.c_str());
      return 0;
    }

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
      systemLog( NLogg::LEVEL_ERROR ).Trace("%s: can't get svc class from svcid(svcid=%s)", __FUNCTION__, interfaceId.c_str());
    }
    return spchnl;
  }

  Login::ELoginResult::Enum ClientTransportSystem2::GetLoginResult() const
  {
    if ( state == Working )
      return Login::ELoginResult::Success;
    if( state == LoggingIn || state == ContactingRelay )
      return Login::ELoginResult::NoResult;
    return loginResult;
  }

  void ClientTransportSystem2::Step()
  {
    Work();
  }
}
