#ifndef SYSTEM_STD_AFX_H__
#define SYSTEM_STD_AFX_H__

#include "System/config.h"

#ifdef STATIC_LIB
  #define DO_NOT_USE_DLLMAIN
  #define INTERMODULE_EXPORT
#else
#if defined( NV_WIN_PLATFORM )
  #define INTERMODULE_EXPORT __declspec(dllexport)
#elif defined( NV_LINUX_PLATFORM )
  #define INTERMODULE_EXPORT
#endif
#endif


#ifndef STARFORCE_PROTECTED
  #if( defined(_SHIPPING ) && defined(STATIC_LIB) )
    #define STARFORCE_PROTECTED
  #endif
#endif  

#ifndef WIN32

// Linux specific includes

#if (!defined(_XBOX) && defined(_MSC_VER) && defined (_M_IX86)) || (defined(__MWERKS__) && defined(__INTEL__))
  #define NI_PLATF_WIN
  #ifndef _WIN32_WINNT            // Specifies that the minimum required platform is Windows Vista.
    #define _WIN32_WINNT 0x0600     // Change this to the appropriate value to target other versions of Windows.
  #endif
#else
  #if (defined(NI_PLATF_WIN))
    #error "Wrong definition"
  #endif
  #ifndef NI_PLATF_LINUX
    #define NI_PLATF_LINUX
  #endif
#endif

#ifdef NI_PLATF_LINUX

//include Linux API headers
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <syslog.h>
#include <signal.h>
#include <string.h>
#include <stdarg.h>
#include <wchar.h>
#include <memory.h>
#include <pthread.h>
#include <ctype.h>
#include <iconv.h>
#include <typeinfo>

typedef long LONG;

#ifndef ASSERT
#define ASSERT(a)
#endif
#include "../System/nlist.h"
#include "../System/nstring.h"
#include "../System/nvector.h"
using namespace nstl;
#include "../System/StrProc.h"
#include "../System/Logger.h"
#include "../System/LogStreamBuffer.h"
#include "../System/SystemLog.h"

#include "../System/Basic.h"
#include "../System/Asserts.h"


#endif


#else

// Windows specific includes

#pragma once
#define WIN32_LEAN_AND_MEAN
#pragma warning( disable: 4005 ) // warning C4005: 'identifier' : macro redefinition
#define _WIN32_WINNT 0x600
#include <windows.h>
#include <typeinfo.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma warning( disable: 4800 ) // warning C4800: 'type' : forcing value to bool 'true' or 'false' (performance warning)
#pragma warning( disable: 4100 ) // warning C4100: 'identifier' : unreferenced formal parameter
#pragma warning( disable: 4127 ) // warning C4127: conditional expression is constant
#pragma warning( disable: 4324 ) // warning C4324: structure was padded due to __declspec(align())
#pragma warning ( disable: 4793 ) // warning C4793: function compiled as native
#pragma warning( disable: 4530 ) // warning C4530: C++ exception handler used, but unwind semantics are not enabled

#ifdef _SHIPPING
#pragma warning( disable: 4505 ) // warning C4324: unreferenced local function has been removed
#endif
#pragma warning( error : 114 ) // warning C4141: same type qualifier used more than once
#pragma warning( error : 99 ) // warning C4099: type name first seen using 'struct' now seen using 'class'
#pragma warning( error : 715 ) // not all control paths return a value
#pragma warning( error : 305 ) // warning C4305: 'argument' : truncation from 'double' to 'float'
#pragma warning( error : 172 ) // warning C4172: returning address of local variable or temporary

//#pragma warning( error : 189 ) // unreferenced local variable
//#pragma warning( error : 101 ) // unreferenced local variable
#pragma warning( error : 18 )
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif



#include "DefaultTypes.h"
#ifndef NI_PLATF_LINUX
  #include "../MemoryLib/newdelete.h"
#endif

#define for if(false); else for					// to achive standard variable scope resolving, declared inside 'for'
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define ARRAY_SIZE( a ) ( sizeof( a ) / sizeof( (a)[0] ) )
#define DUMMY_ASSIGNMENT( c ) c &operator=( const c & ) { return *this; }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "../System/Asserts.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "../System/nlist.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef WIN32
  #pragma component( mintypeinfo, off )
#endif
#include "../System/nstring.h"

#include "../System/nvector.h"

//////////////
#ifdef WIN32
  #pragma component( mintypeinfo, on )
#endif  
#include "../System/nhash_map.h"
#include "../System/nmap.h"
#include "../System/nhash_set.h"

#include "../System/nset.h"
#include "../System/nmap.h"
#include "../System/ncircular_buffer.h"

#ifdef WIN32
  #pragma component( mintypeinfo, off )
#endif  
#include "../System/nhelpdebug.h"
using namespace nstl;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "../System/StrProc.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "../System/Ring.h"
#include "../System/staticarray.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "../System/Basic.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "../System/LogStreamBuffer.h"
#include "../System/SystemLog.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "../System/MathTools.h"
#include "../System/Geom.h"
#include "../System/Color.h"
#include "../System/matrix43.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "System/Stream.h"
#include "System/FileSystem/FileStream.h"
#include "System/FileSystem/FileWriteStream.h"
#include "System/MemoryStream.h"
#include "System/ProtectedStream.h"
#include "System/FixedMemoryStream.h"
#include "System/BinSaver.h"
#include "System/FileSystem/FileSystem.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "System/Commands.h"
#include "System/StrConvert.h"
#include "System/DebugVar.h"
#include "System/ProfilingHelper.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "System/Texts.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "System/Reminder.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "System/ScopedArray.h"
#include "System/ScopedPtr.h"
#include "System/AutoPtr.h"
#include "System/IntrusivePtr.h"
#include "System/RefCntObject.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "System/Singleton.h"
#include "System/noncopyable.h"

#include "System/StrUtils.h"
#include "System/SafeTextFormatEx.h"

#include "System/ScopeGuards.h"
#include "System/Compatibility.h"

#ifndef _SHIPPING
#	ifdef _DEBUG
//#		define WORLD_CRC_DEBUG
# endif
#endif

#define SAFE_DELETE( p ) { if ( (p) ) { delete (p); (p) = NULL; } }
#define SAFE_DELETE_ARRAY( p ) { if ( (p) ) { delete [] (p); (p) = NULL; } }

///////////////////////////////////////////////////////////////////////////////
// Helper macro BOOST_JOIN:
// The following piece of macro magic joins the two
// arguments together, even when one of the arguments is
// itself a macro (see 16.3.1 in C++ standard).  The key
// is that macro expansion of macro arguments does not
// occur in BOOST_DO_JOIN2 but does in BOOST_DO_JOIN.
///////////////////////////////////////////////////////////////////////////////
#define BOOST_JOIN( X, Y ) BOOST_DO_JOIN( X, Y )
#define BOOST_DO_JOIN( X, Y ) BOOST_DO_JOIN2(X,Y)
#define BOOST_DO_JOIN2( X, Y ) X##Y

#endif // SYSTEM_STD_AFX_H__
