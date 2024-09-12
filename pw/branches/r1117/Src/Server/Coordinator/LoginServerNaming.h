#pragma once 

namespace Login
{
  static const Transport::TServiceId serviceId = "login";
  static const string serviceIface = string(serviceId.c_str()) + ":server";
}
