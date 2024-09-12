#include "stdafx.h"
#include "Logging.h"

namespace ni_log
{



void LogLevelProxy::Write( const char * _text )
{
  writer->Write( NLogg::SEntryInfo( level, "", 0, "" ), _text );
}





Handle::Handle( IWriter * _writer ) :
dbg     ( _writer, NLogg::LEVEL_DEBUG ),
info    ( _writer, NLogg::LEVEL_MESSAGE ),
warning ( _writer, NLogg::LEVEL_WARNING ),
error   ( _writer, NLogg::LEVEL_ERROR ),
crit    ( _writer, NLogg::LEVEL_CRITICAL )
{
  //TODO: Write header?
}

} //namespace ni_log
