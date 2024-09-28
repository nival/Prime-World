#include "stdafx.h"
#include "Initializer.h"
#include "Driver.h"

namespace Network
{
#if defined( NV_WIN_PLATFORM )
  INetworkDriver* __cdecl Initialize(EDriverTrafficType::Enum tt)
#elif defined( NV_LINUX_PLATFORM )
  INetworkDriver* Initialize(EDriverTrafficType::Enum tt)
#endif
	{
		return new Driver(tt);
	}
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
