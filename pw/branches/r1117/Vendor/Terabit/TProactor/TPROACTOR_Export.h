
// -*- C++ -*-
// $Id$
// Definition for Win32 Export directives.
// This file is generated automatically by generate_export_file.pl TPROACTOR
// ------------------------------
#ifndef TPROACTOR_EXPORT_H
#define TPROACTOR_EXPORT_H

#include "ace/config-all.h"

#if !defined (TPROACTOR_HAS_DLL)
#  define TPROACTOR_HAS_DLL 1
#endif /* ! TPROACTOR_HAS_DLL */

#if defined (TPROACTOR_HAS_DLL) && (TPROACTOR_HAS_DLL == 1)
#  if defined (TPROACTOR_BUILD_DLL)
#    define TPROACTOR_Export ACE_Proper_Export_Flag
#    define TPROACTOR_SINGLETON_DECLARATION(T) ACE_EXPORT_SINGLETON_DECLARATION (T)
#    define TPROACTOR_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_EXPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  else /* TPROACTOR_BUILD_DLL */
#    define TPROACTOR_Export ACE_Proper_Import_Flag
#    define TPROACTOR_SINGLETON_DECLARATION(T) ACE_IMPORT_SINGLETON_DECLARATION (T)
#    define TPROACTOR_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_IMPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  endif /* TPROACTOR_BUILD_DLL */
#else /* TPROACTOR_HAS_DLL == 1 */
#  define TPROACTOR_Export
#  define TPROACTOR_SINGLETON_DECLARATION(T)
#  define TPROACTOR_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#endif /* TPROACTOR_HAS_DLL == 1 */

// Set TPROACTOR_NTRACE = 0 to turn on library specific tracing even if
// tracing is turned off for ACE.
#if !defined (TPROACTOR_NTRACE)
#  if (ACE_NTRACE == 1)
#    define TPROACTOR_NTRACE 1
#  else /* (ACE_NTRACE == 1) */
#    define TPROACTOR_NTRACE 0
#  endif /* (ACE_NTRACE == 1) */
#endif /* !TPROACTOR_NTRACE */

#if (TPROACTOR_NTRACE == 1)
#  define TPROACTOR_TRACE(X)
#else /* (TPROACTOR_NTRACE == 1) */
#  if !defined (ACE_HAS_TRACE)
#    define ACE_HAS_TRACE
#  endif /* ACE_HAS_TRACE */
#  define TPROACTOR_TRACE(X) ACE_TRACE_IMPL(X)
#  include "ace/Trace.h"
#endif /* (TPROACTOR_NTRACE == 1) */

#endif /* TPROACTOR_EXPORT_H */

// End of auto generated file.
