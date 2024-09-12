#ifndef INITIALIZER_H_1D8765F8_023F_4D6F
#define INITIALIZER_H_1D8765F8_023F_4D6F
#include "Network.h"

namespace Network
{
	/** create new network thread to collect traffic*/
#if defined( NV_WIN_PLATFORM )
	INetworkDriver* __cdecl Initialize(EDriverTrafficType::Enum tt = EDriverTrafficType::Light);
#elif defined( NV_LINUX_PLATFORM )
    INetworkDriver* Initialize(EDriverTrafficType::Enum tt = EDriverTrafficType::Light);
#endif

  void SetNonBlockingConnect( bool nonBlocking );
  void SetConnectTimeout( int timeoutMs );
}
#endif //#define INITIALIZER_H_1D8765F8_023F_4D6F
