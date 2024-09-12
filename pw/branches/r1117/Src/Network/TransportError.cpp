#include "stdafx.h"
#include "Network/TransportError.h"

namespace Transport
{
  NI_ENUM_BEGIN_STD(EError);
  NI_ENUM_ITEM( ALREADY_CLOSED );
  NI_ENUM_ITEM( NOT_FOUND );
  NI_ENUM_ITEM( FAIL );
  NI_ENUM_ITEM( OK );
  NI_ENUM_ITEM( IN_PROGRESS );
  NI_ENUM_END_STD;
}
