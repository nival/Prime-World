#pragma once

#include "Network/Transport.h"
#include "Network/LoginData.h"
#include "Network/AddressTranslator.h"
#include "Coordinator/ServiceRole.h"
#include "Coordinator/CoordinatorTypes.h"
#include "Coordinator/SvcNetAddresses.h"

namespace rpc
{
  class GateKeeper;
  class Node;
}

namespace UserManager
{
  class IUserManagerAgent;
}

namespace Coordinator
{

class RICoordinatorServerRemote;



_interface ICoordinatorClient : public IBaseInterfaceMT
{
  NI_DECLARE_CLASS_1( ICoordinatorClient, IBaseInterfaceMT );

  virtual UserManager::IUserManagerAgent * GetUserManagerAgent() const = 0;
  virtual Transport::IAddressTranslator * GetBackendAddressTranslator() const = 0;
  virtual Transport::IAddressTranslator * GetFrontendAddressTranslator() const = 0;
  virtual void AddExplicitRoute( const Transport::TServiceId & _service, const SvcNetAddresses & _addrs ) = 0;
};


namespace EServiceInstancing
{
  enum Enum
  {
    UNKNOWN = 0,
    SINGLE,           // single server of this class present in cluster.
    MULTIPLE,         // many servers of this class can appear in cluster
  };
}


namespace ESvcFlags
{
  enum
  {
    CAN_RELOAD_CFG    = 1,
    HAS_NO_CFG        = 2,
    EXTERNAL          = 4
  };
}


struct SInterfacePolicy
{
  EServiceInstancing::Enum    type;
  unsigned                    flags;

  SInterfacePolicy() :
  type( EServiceInstancing::SINGLE ),
  flags( 0 )
  {}

  SInterfacePolicy( EServiceInstancing::Enum _type, unsigned _flags = 0 ) :
  type( _type ),
  flags( _flags )
  {}
};

}
