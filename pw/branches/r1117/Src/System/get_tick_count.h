#ifndef __GET_TICK_COUNT_H_INCLUDED__897662__
#define __GET_TICK_COUNT_H_INCLUDED__897662__

#include "types.h"
#include <time.h>

namespace nival
{
	#if defined(NV_WIN_PLATFORM)

		inline uint32_t get_tick_count()
		{
			return GetTickCount();
		}

    inline uint64_t get_tick_count_64()
    {
      // There's no ::GetTickCount64() in WinXP
      return GetTickCount();
    }

	#elif defined(NV_LINUX_PLATFORM)

		inline uint64_t get_tick_count_64()
		{
			timespec current_tick;
			clock_gettime( CLOCK_MONOTONIC, &current_tick );

			return static_cast< uint64_t >( current_tick.tv_sec ) * 1000 + current_tick.tv_nsec / 1000000;

      /*
			uint32_t lo, hi;

			__asm__ __volatile__ (
				"xorl %%eax,%%eax \n        cpuid"
				::: "%rax", "%rbx", "%rcx", "%rdx"
			);

			__asm__ __volatile__ (
				"rdtsc" : "=a" (lo), "=d" (hi)
			);

			return uint64_t( hi ) << 32 | lo;
      */
		}

		inline uint32_t get_tick_count()
		{
			return static_cast< uint32_t >( get_tick_count_64() );
		}

	#endif

} // namepsace nival

#if defined(NV_LINUX_PLATFORM)

	inline nival::uint32_t GetTickCount()
	{
		return nival::get_tick_count();
	}

	inline nival::uint64_t GetTickCount64()
	{
		return nival::get_tick_count_64();
	}

#endif

#endif // __GET_TICK_COUNT_H_INCLUDED__897662__

