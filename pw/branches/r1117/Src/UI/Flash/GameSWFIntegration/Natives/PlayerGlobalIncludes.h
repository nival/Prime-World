#pragma once
#include <Vendor/Tamarin/source/platform/system-selection.h>
#include <Vendor/Tamarin/source/platform/win32/win32-platform.h>
#include <Vendor/Tamarin/source/core/avmplus.h>

#include <UI/Flash/GameSWFIntegration/Builtins/NativesBuiltins.h>
#include "ClassMacros.h"
#include <UI/Flash/GameSWFIntegration/SafeGCRoot.h>

namespace SwfDebugLog
{
  //TODO make this as a macros
  inline void CallLog( const char * className, const char * functionName )
  {
#ifdef DEBUG_SWF
    char buf[128];
    sprintf_s( buf, "%s::%s()\n", className, functionName );
    OutputDebugString( buf );
#endif
  }

  inline void CallLog( const char * className, const char * functionName, const char * functionArgName)
  {
#ifdef DEBUG_SWF
    char buf[128];
    sprintf_s( buf, "%s::%s(%s)\n", className, functionName, functionArgName);
    OutputDebugString( buf );
#endif
  }

  inline void CallLog( const char * debugMessage)
  {
#ifdef DEBUGGER
    DebugTrace("\n%s\n", debugMessage);
    /*OutputDebugString( "\n" );
    OutputDebugString( debugMessage );
    OutputDebugString( "\n" );*/
#endif
  }

  inline void CallLog( const char * className, const char * functionName, avmplus::AvmString functionArgName)
  {
#ifdef DEBUG_SWF
    CallLog(className, functionName, avmplus::StUTF8String(functionArgName).c_str());
#endif
  }
}
