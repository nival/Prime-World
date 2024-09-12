#include "UserManagerSvc/stdafx.h"
#include "UserManagerSvc/UserManagerIface.h"

namespace UserManager
{
  SERIALIZE_FACTORY(UserSessionInfo);
  SERIALIZE_FACTORY(RelayInfo);
  SERIALIZE_FACTORY(PartialReconnectInfo);
}
