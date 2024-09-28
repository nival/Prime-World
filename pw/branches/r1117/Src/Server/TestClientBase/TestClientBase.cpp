#include <Server/Network/Transport.h>
#include <Server/Network/TransportMessages.h>
#include <Server/Network/ClientTransportSystem.h>
#include <Server/Network/ClientTransportSystem2.h>
#include <Server/NetworkAIO/transport/TLTransportModule.h>
#include <Network/FreePortsFinder.h>

#include "TestClientBase.h"

namespace TestClientNs
{
  ClientBase::ClientBase()
    :userid_(0),
    stage_(Stage::NONE),
    lastresult_(Result::NONE),
    bexit_(false)
  {
  }

  ClientBase::ClientBase(StrongMT<Network::INetworkDriver> driver,
                nstl::string const & loginaddr,
                nstl::string const & user, nstl::string const & pswd,
                StrongMT<TL::TransportModule> const & sptm)
    :netdriver_(driver),
    sptm_(sptm),
    userid_(0),
    stage_(Stage::NONE),
    lastresult_(Result::NONE),
    loginAddr_(loginaddr),
    user_(user),
    pswd_(pswd),
    bexit_(false)
  {
    Login::ClientVersion ver;
    if (sptm_)
    {
      transport_ = new Transport::ClientTransportSystem2( netdriver_, Transport::GetGlobalMessageFactory(), 
        Network::GetFreePortsFinder(), ver, sptm_.Get());
    }
    else
    {
      transport_ = new Transport::ClientTransportSystem( netdriver_, Transport::GetGlobalMessageFactory(), 
        Network::GetFreePortsFinder(), ver, 0);
    }
  }

  ClientBase::~ClientBase()
  {
    if( transport_ )
      transport_->Logout();
    transport_ = 0;
  }

  int ClientBase::startLogin()
  {
    return startLogin_(loginAddr_, user_, pswd_);
  }

  int ClientBase::startLogin(string const & loginaddr, string const & username, string const & pswd)
  {
    return startLogin_(loginaddr, username, pswd);
  }

  int ClientBase::startLogin_(string const & loginaddr, string const & username, string const & pswd)
  {
    transport_->Login(loginaddr, username, pswd, 0 );

    stage_ = Stage::LOGIN_STARTED;
    timeLoginStarted_ = NHPTimer::GetScalarTime();
    lastresult_ = Result::IN_PROGRESS;
    return lastresult_;
  }

  int ClientBase::checkLogin()
  {
    if (stage_ != Stage::LOGIN_STARTED)
      return Result::FAIL;

    Login::ELoginResult::Enum result = transport_->GetLoginResult();
    if (Login::ELoginResult::NoResult == result)
    {
      if ( timeLoginStarted_ + LOGIN_TIMEOUT_SECONDS < NHPTimer::GetScalarTime() )
      {
        if( transport_ )
        {
          LOG_M(0) << "Login timeout for client " << transport_->GetUserId();
          // login timeout: давайте-ка еще раз попробуем LOGIN
          transport_->Logout();
          return startLogin();
        }
      }
      
      return Result::IN_PROGRESS;
    }

    if (Login::ELoginResult::Success == result)
    {
      userid_ = transport_->GetUserId();
      stage_ = Stage::LOGIN_FINISHED;
      lastresult_ = Result::SUCCESS;
    }
    else if ( Login::ELoginResult::AsyncTimeout == result 
             || Login::ELoginResult::AlreadyIn == result )
    {
      LOG_M(0) << "Login async timeout for client " << transport_->GetUserId();
      // login timeout: давайте-ка еще раз попробуем LOGIN
      transport_->Logout();
      return startLogin();
    }
    else
    {
      lastresult_ = Result::FAIL;
    }

    return lastresult_;
  }
}
