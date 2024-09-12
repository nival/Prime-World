#ifndef SYSTEMLOG_H__
#define SYSTEMLOG_H__

#include "ChannelLogger.h"
#include "LogStreamBuffer.h"

#ifndef STARFORCE_PROTECTED 
  #define DEBUG_FILE_LINE_PARAMS __FILE__, __LINE__
#else
  #define DEBUG_FILE_LINE_PARAMS "", 0
#endif


NLogg::CChannelLogger &GetSystemLog();

#define systemLog( level ) ( NLogg::StreamBuffer( GetSystemLog(), NLogg::SEntryInfo( level, DEBUG_FILE_LINE_PARAMS ) ) )

#define systemLogEx( level, file, line ) ( NLogg::StreamBuffer( GetSystemLog(), NLogg::SEntryInfo( level, file, line ) ) )


#ifndef _SHIPPING
#define DevTrace ( NLogg::StreamBuffer( GetSystemLog(), NLogg::SEntryInfo( NLogg::LEVEL_DEBUG, DEBUG_FILE_LINE_PARAMS ) ) ).Trace
#else
#define DevTrace(...)
#endif

#define DebugTrace ( NLogg::StreamBuffer( GetSystemLog(), NLogg::SEntryInfo( NLogg::LEVEL_DEBUG, DEBUG_FILE_LINE_PARAMS ) ) ).Trace
#define MessageTrace ( NLogg::StreamBuffer( GetSystemLog(), NLogg::SEntryInfo( NLogg::LEVEL_MESSAGE, DEBUG_FILE_LINE_PARAMS ) ) ).Trace
#define WarningTrace ( NLogg::StreamBuffer( GetSystemLog(), NLogg::SEntryInfo( NLogg::LEVEL_WARNING, DEBUG_FILE_LINE_PARAMS ) ) ).Trace
#define ErrorTrace ( NLogg::StreamBuffer( GetSystemLog(), NLogg::SEntryInfo( NLogg::LEVEL_ERROR, DEBUG_FILE_LINE_PARAMS ) ) ).Trace
#define CriticalTrace ( NLogg::StreamBuffer( GetSystemLog(), NLogg::SEntryInfo( NLogg::LEVEL_CRITICAL, DEBUG_FILE_LINE_PARAMS ) ) ).Trace

#define localLog(log, level) if (log) ( NLogg::StreamBuffer( *log, NLogg::SEntryInfo( level, DEBUG_FILE_LINE_PARAMS ) ) )



// new macros work with channels (default channel == NULL works as a broadcast to all available dumpers)

// LOG_X: systemLog() to channel (X = severity 1st letter: M=Message, A=Assert etc..)
#define LOG_D( channel ) ( NLogg::StreamBuffer( GetSystemLog(), NLogg::SEntryInfo( NLogg::LEVEL_DEBUG, DEBUG_FILE_LINE_PARAMS, channel ) ) )
#define LOG_M( channel ) ( NLogg::StreamBuffer( GetSystemLog(), NLogg::SEntryInfo( NLogg::LEVEL_MESSAGE, DEBUG_FILE_LINE_PARAMS, channel ) ) )
#define LOG_W( channel ) ( NLogg::StreamBuffer( GetSystemLog(), NLogg::SEntryInfo( NLogg::LEVEL_WARNING, DEBUG_FILE_LINE_PARAMS, channel ) ) )
#define LOG_E( channel ) ( NLogg::StreamBuffer( GetSystemLog(), NLogg::SEntryInfo( NLogg::LEVEL_ERROR,   DEBUG_FILE_LINE_PARAMS, channel ) ) )
#define LOG_A( channel ) ( NLogg::StreamBuffer( GetSystemLog(), NLogg::SEntryInfo( NLogg::LEVEL_ASSERT,  DEBUG_FILE_LINE_PARAMS, channel ) ) )
#define LOG_C( channel ) ( NLogg::StreamBuffer( GetSystemLog(), NLogg::SEntryInfo( NLogg::LEVEL_CRITICAL,DEBUG_FILE_LINE_PARAMS, channel ) ) )

// LOG_ALL_X: systemLog to ALL available channels (X = severity 1st letter: M=Message, A=Assert etc..)
#define LOG_DEFAULT_D() ( NLogg::StreamBuffer( GetSystemLog(), NLogg::SEntryInfo( NLogg::LEVEL_DEBUG,   DEBUG_FILE_LINE_PARAMS ) )
#define LOG_DEFAULT_M() ( NLogg::StreamBuffer( GetSystemLog(), NLogg::SEntryInfo( NLogg::LEVEL_MESSAGE, DEBUG_FILE_LINE_PARAMS ) )
#define LOG_DEFAULT_W() ( NLogg::StreamBuffer( GetSystemLog(), NLogg::SEntryInfo( NLogg::LEVEL_WARNING, DEBUG_FILE_LINE_PARAMS ) )
#define LOG_DEFAULT_E() ( NLogg::StreamBuffer( GetSystemLog(), NLogg::SEntryInfo( NLogg::LEVEL_ERROR,   DEBUG_FILE_LINE_PARAMS ) )
#define LOG_DEFAULT_A() ( NLogg::StreamBuffer( GetSystemLog(), NLogg::SEntryInfo( NLogg::LEVEL_ASSERT,  DEBUG_FILE_LINE_PARAMS ) )
#define LOG_DEFAULT_C() ( NLogg::StreamBuffer( GetSystemLog(), NLogg::SEntryInfo( NLogg::LEVEL_CRITICAL,DEBUG_FILE_LINE_PARAMS ) )

// logX: local log with channels (X = severity 1st letter: M=Message, A=Assert etc..)
#define LOGL_D( log, channel ) if (log) NLogg::StreamBuffer( *log, NLogg::SEntryInfo( NLogg::LEVEL_DEBUG,   DEBUG_FILE_LINE_PARAMS, channel ) )
#define LOGL_M( log, channel ) if (log) NLogg::StreamBuffer( *log, NLogg::SEntryInfo( NLogg::LEVEL_MESSAGE, DEBUG_FILE_LINE_PARAMS, channel ) )
#define LOGL_W( log, channel ) if (log) NLogg::StreamBuffer( *log, NLogg::SEntryInfo( NLogg::LEVEL_WARNING, DEBUG_FILE_LINE_PARAMS, channel ) )
#define LOGL_E( log, channel ) if (log) NLogg::StreamBuffer( *log, NLogg::SEntryInfo( NLogg::LEVEL_ERROR,   DEBUG_FILE_LINE_PARAMS, channel ) )
#define LOGL_A( log, channel ) if (log) NLogg::StreamBuffer( *log, NLogg::SEntryInfo( NLogg::LEVEL_ASSERT,  DEBUG_FILE_LINE_PARAMS, channel ) )
#define LOGL_C( log, channel ) if (log) NLogg::StreamBuffer( *log, NLogg::SEntryInfo( NLogg::LEVEL_CRITICAL,DEBUG_FILE_LINE_PARAMS, channel ) )

// logAllX: local log to all available channels (X = severity 1st letter: M=Message, A=Assert etc..)
#define LOGL_DEFAULT_D( log ) if (log) NLogg::StreamBuffer( *log, NLogg::SEntryInfo( NLogg::LEVEL_DEBUG,   DEBUG_FILE_LINE_PARAMS ) )
#define LOGL_DEFAULT_M( log ) if (log) NLogg::StreamBuffer( *log, NLogg::SEntryInfo( NLogg::LEVEL_MESSAGE, DEBUG_FILE_LINE_PARAMS ) )
#define LOGL_DEFAULT_W( log ) if (log) NLogg::StreamBuffer( *log, NLogg::SEntryInfo( NLogg::LEVEL_WARNING, DEBUG_FILE_LINE_PARAMS ) )
#define LOGL_DEFAULT_E( log ) if (log) NLogg::StreamBuffer( *log, NLogg::SEntryInfo( NLogg::LEVEL_ERROR,   DEBUG_FILE_LINE_PARAMS ) )
#define LOGL_DEFAULT_A( log ) if (log) NLogg::StreamBuffer( *log, NLogg::SEntryInfo( NLogg::LEVEL_ASSERT,  DEBUG_FILE_LINE_PARAMS ) )
#define LOGL_DEFAULT_C( log ) if (log) NLogg::StreamBuffer( *log, NLogg::SEntryInfo( NLogg::LEVEL_CRITICAL,DEBUG_FILE_LINE_PARAMS ) )

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif //SYSTEMLOG_H__

