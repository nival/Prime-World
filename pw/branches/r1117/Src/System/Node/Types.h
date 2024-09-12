#ifndef __TYPES_H_INCLUDED__131903__
#define __TYPES_H_INCLUDED__131903__

#include "System/Node/Config.h"

#include <stddef.h>
#include <assert.h>
#include <sstream>

namespace nvl {

	typedef unsigned int		uint_t;
	typedef unsigned long		ulong_t;
	typedef unsigned char		uchar_t;
	typedef unsigned char		byte_t;

	typedef char				int8_t;
	typedef short				int16_t;
	typedef int					int32_t;

	typedef unsigned char		uint8_t;
	typedef unsigned short		uint16_t;
	typedef unsigned int		uint32_t;

	#if defined( NV_WIN_PLATFORM )

		typedef __int64				int64_t;
		typedef unsigned __int64	uint64_t;

	#elif defined ( NV_LINUX_PLATFORM )

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
	const result_t result_cancel			= 3;

	const result_t result_fail				= -1;
	const result_t result_unknown			= -2;
	const result_t result_inv_args			= -3;
	const result_t result_wrong_state		= -4;
	const result_t result_wrong_type		= -5;
	const result_t result_no_resources		= -6;
	const result_t result_not_impl			= -7;
	const result_t result_impossible_action	= -8;
	const result_t result_out_of_memory		= -9;

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

	#define NV_THROW( __expression )					\
		{												\
			std::stringstream ss;						\
			ss << __expression;							\
			throw std::exception( ss.str().c_str() );	\
		}

	#define NV_CHECK_THROW( __condition, __expression )	\
		{												\
			if ( ( __condition ) )						\
				NV_THROW( __expression );				\
		}

	#if defined( NV_LINUX_PLATFORM )
		enum { NV_INFINITE = -1 };
	#endif

	struct non_copyable_t {

		non_copyable_t()
		{}

	private:

		non_copyable_t( non_copyable_t const & );
		non_copyable_t & operator = ( non_copyable_t const & );

	};

} // namespace nvl

#endif // __TYPES_H_INCLUDED__131903__
