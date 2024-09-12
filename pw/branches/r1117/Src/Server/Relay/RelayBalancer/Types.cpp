#include "stdafx.h"

namespace Relay
{
  namespace Balancer
  {
    NI_ENUM_BEGIN_STD( RelayAllocationMode );
    NI_ENUM_ITEM( primary_relays_only );
    NI_ENUM_ITEM( secondary_relays_optional );
    NI_ENUM_ITEM( secondary_relays_mandatory );
    NI_ENUM_END_STD;
  }
}
