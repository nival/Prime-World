#ifndef __cxxtest__Win32SEH_h__
#define __cxxtest__Win32SEH_h__

#define WIN32_LEAN_AND_MEAN
#pragma warning( disable: 4005 ) // warning C4005: 'identifier' : macro redefinition
#define _WIN32_WINNT 0x600

#include <Windows.h>
#include <Winbase.h>
#include "TestSuite.h"

namespace win32
{
    struct SEHHandler
    {
        SEHHandler() : originalFilter( SetUnhandledExceptionFilter( ExceptionFilter ) ) {}
        ~SEHHandler() { SetUnhandledExceptionFilter( originalFilter ); }

    private:
        LPTOP_LEVEL_EXCEPTION_FILTER originalFilter;
        SEHHandler( const SEHHandler& );
        SEHHandler& operator = ( const SEHHandler& );

        static LONG __stdcall ExceptionFilter( struct _EXCEPTION_POINTERS* )
        {
            TS_FAIL( "Unhandled exception!" );
            std::cerr << "Unhandled Exception occured!" << std::endl;
            //return EXCEPTION_CONTINUE_EXECUTION;
            return EXCEPTION_EXECUTE_HANDLER;
            //return EXCEPTION_CONTINUE_SEARCH;
        }
    };
}

#endif // __cxxtest__Win32SEH_h__