
// -*- C++ -*-
// $Id$
// Definition for Win32 Export directives.
// This file is generated automatically by generate_export_file.pl IOTERABIT
// ------------------------------
#ifndef IOTERABIT_EXPORT_H
#define IOTERABIT_EXPORT_H

#include "ace/config-all.h"

#if !(defined (ACE_WIN32) || defined (ACE_HAS_AIO_CALLS) || defined(ACE_HAS_AIO_EMULATION))
#error Platform does not support AIO
#endif

// This only works on platforms that support async i/o.

#if defined (ACE_AS_STATIC_LIBS) && !defined (IOTERABIT_HAS_DLL)
#  define IOTERABIT_HAS_DLL 0
#endif /* ACE_AS_STATIC_LIBS && IOTERABIT_HAS_DLL */

#if !defined (IOTERABIT_HAS_DLL)
#  define IOTERABIT_HAS_DLL 1
#endif /* ! IOTERABIT_HAS_DLL */

#if defined (IOTERABIT_HAS_DLL) && (IOTERABIT_HAS_DLL == 1)
#  if defined (IOTERABIT_BUILD_DLL)
#    define IOTERABIT_Export ACE_Proper_Export_Flag
#    define IOTERABIT_SINGLETON_DECLARATION(T) ACE_EXPORT_SINGLETON_DECLARATION (T)
#    define IOTERABIT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_EXPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  else /* IOTERABIT_BUILD_DLL */
#    define IOTERABIT_Export ACE_Proper_Import_Flag
#    define IOTERABIT_SINGLETON_DECLARATION(T) ACE_IMPORT_SINGLETON_DECLARATION (T)
#    define IOTERABIT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_IMPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  endif /* IOTERABIT_BUILD_DLL */
#else /* IOTERABIT_HAS_DLL == 1 */
#  define IOTERABIT_Export
#  define IOTERABIT_SINGLETON_DECLARATION(T)
#  define IOTERABIT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#endif /* IOTERABIT_HAS_DLL == 1 */

// Set IOTERABIT_NTRACE = 0 to turn on library specific tracing even if
// tracing is turned off for ACE.
#if !defined (IOTERABIT_NTRACE)
#  if (ACE_NTRACE == 1)
#    define IOTERABIT_NTRACE 1
#  else /* (ACE_NTRACE == 1) */
#    define IOTERABIT_NTRACE 0
#  endif /* (ACE_NTRACE == 1) */
#endif /* !IOTERABIT_NTRACE */

#if (IOTERABIT_NTRACE == 1)
#  define IOTERABIT_TRACE(X)
#else /* (IOTERABIT_NTRACE == 1) */
#  if !defined (ACE_HAS_TRACE)
#    define ACE_HAS_TRACE
#  endif /* ACE_HAS_TRACE */
#  define IOTERABIT_TRACE(X) ACE_TRACE_IMPL(X)
#  include "ace/Trace.h"
#endif /* (IOTERABIT_NTRACE == 1) */

#endif /* IOTERABIT_EXPORT_H */

// End of auto generated file.
