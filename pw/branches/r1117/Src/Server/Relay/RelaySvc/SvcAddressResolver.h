#pragma once

class TRB_Sock_Addr;

namespace Relay
{

class ISvcAddressResolver
{
public:
  virtual bool ResolveSvcAddress(Transport::TServiceId const & serviceid, TRB_Sock_Addr & netaddr) = 0;
};

}
