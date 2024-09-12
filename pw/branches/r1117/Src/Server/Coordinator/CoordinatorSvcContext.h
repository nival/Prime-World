#pragma once
#include "Coordinator/CoordinatorServiceStatus.h"
#include <Network/Address.h>
#include "Network/TransportTypes.h"
#include "Network/TransportAddress.h"

namespace Coordinator
{
  class SvcContext : public BaseObjectMT
  {
    NI_DECLARE_REFCOUNT_CLASS_1(SvcContext, BaseObjectMT);

  public:

  public:
    SvcContext(Transport::TServiceId const & _svcpath, Transport::TServiceId const & _svcid, TServiceRole const & _svcrole,
      ServerIdT const & _srvid, int _pid, string const & _machineName);
    ~SvcContext();

  public:
    Transport::TServiceId const & fullsvcid() const;
    Transport::TServiceId const & svcpath() const;
    Transport::TServiceId const & svcid() const;
    Transport::TServiceId const & svcls() const;
    ServerIdT const & srvid() const;
    TServiceRole const & svcrole() const;

    Network::NetAddress const & backendAddr() const;
    void backendAddr(Network::NetAddress const & _backendAddr);
    Network::NetAddress const & frontendAddr() const;
    void frontendAddr(Network::NetAddress const & _frontendAddr);

    ServiceStatus::Enum status() const;
    void status(ServiceStatus::Enum _status);
    bool isstarted() const;
    bool isstopped() const;

    int pid() const;
    string const & machineName() const;

  private:
    ServerIdT srvid_;
    Transport::TServiceId fullsvcid_;
    Transport::TServiceId svcpath_;
    Transport::TServiceId svcid_;
    Transport::TServiceId svcls_;
    ServiceStatus::Enum status_;
    int pid_;
    string machineName_;
    Network::NetAddress backendAddr_;
    Network::NetAddress frontendAddr_;
    TServiceRole svcrole_;
  };

  inline
  Transport::TServiceId const & SvcContext::fullsvcid() const
  {
    return fullsvcid_;
  }

  inline
  Transport::TServiceId const & SvcContext::svcpath() const
  {
    return svcpath_;
  }

  inline
  Transport::TServiceId const & SvcContext::svcid() const
  {
    return svcid_;
  }

  inline
  Transport::TServiceId const & SvcContext::svcls() const
  {
    return svcls_;
  }

  inline
  ServerIdT const & SvcContext::srvid() const
  {
    return srvid_;
  }

  inline
  int SvcContext::pid() const
  {
    return pid_;
  }

  inline
  string const & SvcContext::machineName() const
  {
    return machineName_;
  }

  inline
  ServiceStatus::Enum SvcContext::status() const
  {
    return status_;
  }

  inline 
  void SvcContext::status(ServiceStatus::Enum _status)
  {
    status_ = _status;
  }

  inline
  Network::NetAddress const & SvcContext::backendAddr() const
  {
    return backendAddr_;
  }

  inline
  void SvcContext::backendAddr(Network::NetAddress const & _backendAddr)
  {
    backendAddr_ = _backendAddr;
  }

  inline
  Network::NetAddress const & SvcContext::frontendAddr() const
  {
    return frontendAddr_;
  }

  inline
  void SvcContext::frontendAddr(Network::NetAddress const & _frontendAddr)
  {
    frontendAddr_ = _frontendAddr;
  }

  inline
  bool SvcContext::isstarted() const
  {
    return (ServiceStatus::S_STARTED == status_);
  }

  inline
  bool SvcContext::isstopped() const
  {
    return (ServiceStatus::S_STOPPED == status_);
  }

  inline
  TServiceRole const & SvcContext::svcrole() const
  {
    return svcrole_;
  }
}
