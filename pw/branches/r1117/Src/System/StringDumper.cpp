#include "stdafx.h"

#include "LogFileName.h"
#include "FileSystem/FileUtils.h"

#include "StringDumper.h"

namespace NLogg
{

CStringDumper::CStringDumper( CLogger * pDefaultLogger, char * string, int size ) :
CDumper( pDefaultLogger, "string" ), string(string), size(size)
{
}



void CStringDumper::OnDump( const SEntryInfo & entryInfo, const char * headerAndText, const char * textOnly )
{
  threading::MutexLock lock( mutex );

  if( strlen(string) + strlen(headerAndText) < unsigned(size) ) // иначе при переполнении буфера будет валиться на NI_ASSERT-е внутри Cat
  {
    NStr::Cat(string, headerAndText, size);
  }
}

}
