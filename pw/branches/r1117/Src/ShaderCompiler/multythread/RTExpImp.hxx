#ifndef __RTEXPIMP_H
#define __RTEXPIMP_H

#if defined(__INTEL_COMPILER)
#pragma warning(disable : 1478) // function "..." was declared "deprecated"
#pragma warning(disable : 1786)
#pragma warning(disable : 1879) // unimplemented pragma ignored
#pragma warning(disable : 589)  // transfer of control bypasses initialization
#pragma warning(disable : 1491) // definition from the enclosing scope is used.
#endif

//#include "../../Portability/RTOSDef.hxx"

// API prefixes (works under Linux because of __DECLSPEC macro)
#ifdef RTSCLIBENTRY
#undef RTSCLIBENTRY
#endif

#ifndef RTSCLIBENTRY
#if defined(_RTSCDLL_)
	#define RTSCLIBENTRY __DECLSPEC(dllexport)
#else
	#if defined(_RTSCSTATIC_)
		#define RTSCLIBENTRY
	#else
		#define RTSCLIBENTRY __DECLSPEC(dllimport)
	#endif
#endif
#endif

#endif	// __RTEXPIMP_H

