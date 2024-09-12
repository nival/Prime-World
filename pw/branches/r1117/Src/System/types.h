#ifndef __TYPES_H_INCLUDED__131902__
#define __TYPES_H_INCLUDED__131902__

#include "System/config.h"

#include <stddef.h>
#if defined ( NV_LINUX_PLATFORM )
#include <stdint.h>
#endif

namespace nival {

	typedef unsigned int		uint_t;
	typedef unsigned long		ulong_t;
	typedef unsigned char		uchar_t;
	typedef unsigned char		byte_t;

	typedef char				int8_t;

	typedef unsigned char		uint8_t;

#if defined( NV_WIN_PLATFORM )
  
    typedef short				int16_t;
    typedef int					int32_t;
    
    typedef unsigned short		uint16_t;
    typedef unsigned int		uint32_t;

		typedef __int64				int64_t;
		typedef unsigned __int64	uint64_t;

#elif defined ( NV_LINUX_PLATFORM )

    typedef int16_t				int16_t;
    typedef int32_t     int32_t;
    
    typedef uint16_t		uint16_t;
    typedef uint32_t		uint32_t;
  
		typedef long long 			int64_t;
		typedef unsigned long long	uint64_t;

#endif

	typedef char *				str_t;
	typedef char const *		cstr_t;

	typedef wchar_t *			wstr_t;
	typedef wchar_t const *		cwstr_t;

	typedef int 				result_t;

	const result_t result_ok				= 0;

	const result_t result_false				= 1;
	const result_t result_already_done		= 2;

	const result_t result_fail				= -1;
	const result_t result_inv_args			= -2;
	const result_t result_wrong_state		= -3;
	const result_t result_no_resources		= -4;
	const result_t result_not_impl			= -5;
	const result_t result_impossible_action	= -6;

	inline bool NV_CSUCCESS( result_t checking_result )
	{
		return 0 <= checking_result;
	}

	inline bool NV_CFAIL( result_t checking_result )
	{
		return 0 > checking_result;
	}

	#define NV_CRR( __checking_struct ) \
		{ \
			result_t __check_result = ( __checking_struct ); \
			if ( NV_CFAIL( __check_result ) ) return __check_result; \
		}

} // namespace nival

#endif // __TYPES_H_INCLUDED__131902__

