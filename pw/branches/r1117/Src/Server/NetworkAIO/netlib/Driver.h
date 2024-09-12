#pragma once
#include <naio/Driver.h>
#include "Connection.h"
#include "NetworkProtocol.h"

namespace netlib
{
  class IDriver : public IObjectBase
  {
  public:
    virtual StrongMT<netlib::IConnection> OpenConnection(nstl::string const & addr) = 0;
  };

  class Driver : public IDriver, public CObjectBase
  {
    OBJECT_BASIC_METHODS(Driver);

  public:
    Driver();
    ~Driver();

  public:
    bool Init(naio::Cfg const & cfg);
    void Fini();

    StrongMT<netlib::IConnection> OpenConnection(nstl::string const & addr);

  private:
    naio::Driver<NetworkProtocol> drv_;
  };

}