#ifndef __THREAD_SPECIFIC_H_INCLUDED__540624__
#define __THREAD_SPECIFIC_H_INCLUDED__540624__

#include "types.h"

#if defined( NV_LINUX_PLATFORM )

  #include "ported/types.h"
	#include <System/threading/thread.h>

	const DWORD TLS_OUT_OF_INDEXES = -1;

	DWORD TlsAlloc();
	BOOL TlsFree(DWORD index);
	BOOL TlsSetValue(DWORD index, LPVOID value);
	LPVOID TlsGetValue(DWORD index);

#endif // defined( NV_LINUX_PLATFORM )
#endif // __THREAD_SPECIFIC_H_INCLUDED__540624__

