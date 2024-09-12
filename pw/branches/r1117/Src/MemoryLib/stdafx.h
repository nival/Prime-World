#pragma once
#define WIN32_LEAN_AND_MEAN
#pragma warning( disable: 4005 )
#define _WIN32_WINNT 0x600

#include "../System/config.h"

#if defined( NV_WIN_PLATFORM )
#include <windows.h>
#include <typeinfo.h>
#elif defined( NV_LINUX_PLATFORM )
#include <typeinfo>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "../System/DefaultTypes.h"
#include "../MemoryLib/newdelete.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma warning( disable: 4800 ) // warning C4800: 'type' : forcing value to bool 'true' or 'false' (performance warning)
#pragma warning( disable: 4100 ) // warning C4100: 'identifier' : unreferenced formal parameter
#pragma warning( disable: 4127 ) // warning C4127: conditional expression is constant
