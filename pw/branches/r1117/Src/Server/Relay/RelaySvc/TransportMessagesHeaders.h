#pragma once

#if defined( NV_WIN_PLATFORM )
#define WIN32_LEAN_AND_MEAN
#pragma warning( disable: 4005 ) // warning C4005: 'identifier' : macro redefinition
#define _WIN32_WINNT 0x600
#include <windows.h>
#endif // defined( NV_WIN_PLATFORM )

#include "System/DefaultTypes.h"

//  stuff for binsaver, damn
#include "System/Asserts.h"
#include "System/nstring.h"
#include "System/nhash_fun.h"
#include "System/nvector.h"
#include "System/nlist.h"
#include "System/nhash_map.h"
#include "System/nmap.h"
#include "System/nhash_set.h"
#include "System/nset.h"
#include "System/nmap.h"
using namespace nstl;
#include "System/Ring.h"
#include "System/staticarray.h"
#include "System/Basic.h"
#include "System/MemoryStream.h"
#include "System/BinSaver.h"

#include "System/FixedMemoryStream.h"
#include "Network/TransportMessages.h"
