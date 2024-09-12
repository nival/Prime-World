#ifndef CLIENTCONTROLTYPES_H_INCLUDED
#define CLIENTCONTROLTYPES_H_INCLUDED

#include "RPC/RPC.h"
#include "Network/TransportTypes.h"


namespace clientCtl
{

namespace ELoginSvcState
{
  enum Enum { Online, SoftStopped };
}

namespace serviceIds
{
  const Transport::TServiceId Service = "clientctrl";
  static const char * Gate = "clientctrl:gate";
} //namespace serviceIds

}; //namespace clientCtl

#endif //CLIENTCONTROLTYPES_H_INCLUDED
