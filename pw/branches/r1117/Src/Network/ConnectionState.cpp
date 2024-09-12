#include "stdafx.h"
#include "Network/ConnectionState.h"

namespace Network
{
  NI_ENUM_BEGIN_STD(ConnectionState);
  NI_ENUM_ITEM( Initialized );
  NI_ENUM_ITEM( Connecting );
  NI_ENUM_ITEM( Connected );
  NI_ENUM_ITEM( Closed );
  NI_ENUM_ITEM( Invalid );
  NI_ENUM_END_STD;
}
