#pragma once

namespace Relay
{
  char const * const RBLOG = "relaybalancer";

  typedef unsigned int AllocCtxIdT;

  class SvcContext;
  typedef StrongMT<SvcContext> SvcContextPtr;

  class UserContext;
  typedef StrongMT<UserContext> UserContextPtr;

  class GameContext;
  typedef StrongMT<GameContext> GameContextPtr;

  class GameUserGroup;
  typedef StrongMT<GameUserGroup> GameUserGroupPtr;

  namespace Balancer
  {
    namespace RelayAllocationMode
    {
      enum Enum
      {
        primary_relays_only = 0,
        secondary_relays_optional = 1,
        secondary_relays_mandatory = 2,
        default_mode = secondary_relays_optional,
      };

      NI_ENUM_DECL_STD;
    }
  }
}
