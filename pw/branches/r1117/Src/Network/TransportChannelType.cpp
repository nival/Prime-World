#include "stdafx.h"
#include "TransportChannelType.h"

namespace Transport
{
  NI_ENUM_BEGIN_STD(EChannelType);
  NI_ENUM_ITEM( Invalid );
  NI_ENUM_ITEM( Unicast );
  NI_ENUM_ITEM( Multicast );
  NI_ENUM_END_STD;
}
