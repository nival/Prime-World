#ifndef __SLEEP_H_INCLUDED__711841__
#define __SLEEP_H_INCLUDED__711841__

#include "types.h"

#if defined( NV_LINUX_PLATFORM )
	#include <sched.h>
#endif

namespace nival {

	#if defined( NV_WIN_PLATFORM )

		inline void sleep( uint_t milliseconds )
		{
			::Sleep( milliseconds );
		}

		inline void yield()
		{
			::Sleep( 0 );
		}

	#elif defined( NV_LINUX_PLATFORM )

		inline void yield()
		{
			sched_yield();
		}

		inline void sleep( uint_t milliseconds )
		{
			if ( 0 == milliseconds )
				yield();
			else {

				timespec time_to_sleep;
				time_to_sleep.tv_sec = milliseconds / 1000;
				time_to_sleep.tv_nsec = ( milliseconds % 1000 ) * 1000000;

				while ( nanosleep( &time_to_sleep, &time_to_sleep ) < 0 )
				{}

			}

		}

	#endif

} // namespace nival

#endif // __SLEEP_H_INCLUDED__711841__

