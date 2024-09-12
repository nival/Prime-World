#pragma once

#if defined( NV_WIN_PLATFORM ) && defined( _DO_ASSERT )

void __debugbreak();
int __declspec(dllimport) __stdcall IsDebuggerPresent();

void __cdecl ni_report_assert(const char* message, const char* file, int line);

#define ni_assert( x )	 															\
	if ( !(x) )																					\
	{																										\
		ni_report_assert( #x, __FILE__, __LINE__ );				\
		if ( IsDebuggerPresent() )												\
		{																									\
			static int ignore = 0;													\
			if ( !ignore )																	\
				__debugbreak();																\
		}																									\
	}																										

#else
#define ni_assert( x )	 	
#endif
