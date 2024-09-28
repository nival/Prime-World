#pragma warning( disable : 4251)
#pragma warning( disable : 4512)
#include "Driver.h"

namespace netlib
{
  Driver::Driver()
  {
  }

  Driver::~Driver()
  {
  }

  bool Driver::Init(naio::Cfg const & cfg)
  {
    return drv_.Init(cfg);
  }

  void Driver::Fini()
  {
    drv_.Fini();
  }

  StrongMT<netlib::IConnection> Driver::OpenConnection(nstl::string const & addr)
  {
    return StrongMT<netlib::IConnection>(new Connection);
  }
}
