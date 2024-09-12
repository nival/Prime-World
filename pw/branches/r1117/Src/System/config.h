#ifndef __CONFIG_H_INCLUDED__280426__
#define __CONFIG_H_INCLUDED__280426__

#if defined( WIN32 )

	#if defined( NV_LINUX_PLATFORM )
		#error "Definitions collision detected. WIN32 and NV_LINUX_PLATFORM are both defined."
	#endif

	#if !defined( NV_WIN_PLATFORM )
		#define NV_WIN_PLATFORM
	#endif

	#if !defined( _WIN32_WINNT )		// Specifies that the minimum required platform is Windows Vista.
		#define _WIN32_WINNT 0x0600	// Change this to the appropriate value to target other versions of Windows.
	#endif

// #elif defined( __GNUC__ )
#elif defined( __linux__ )

	#if defined( NV_WIN_PLATFORM )
		#error "Definitions collision detected. __GNUC__ and NV_WIN_PLATFORM are both defined."
	#endif

	#if !defined( NV_LINUX_PLATFORM )
		#define NV_LINUX_PLATFORM
	#endif

#else

	#error "Unknown platform."

#endif // defined( WIN32 ) && defined( __GNUC__ )

#if defined( NV_WIN_PLATFORM )

	#if !defined( NOMINMAX )
		#define NOMINMAX
	#endif

	#define WIN32_LEAN_AND_MEAN

	#include <windows.h>

#endif

#include "types.h"

#if defined( NV_LINUX_PLATFORM )

	// TODO: Need to remove after porting MemoryLib

	inline long GetMallocsTotal()
	{
		return 0;
	}

#endif

#endif // __CONFIG_H_INCLUDED__280426__

