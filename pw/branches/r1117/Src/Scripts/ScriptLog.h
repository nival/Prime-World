#pragma once

NLogg::CChannelLogger &GetScriptLog();

#define scriptLog( level ) ( NLogg::StreamBuffer( GetScriptLog(), NLogg::SEntryInfo( level, DEBUG_FILE_LINE_PARAMS ) ) )
