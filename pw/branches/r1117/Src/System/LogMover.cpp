#include "stdafx.h"

#include "System/FileSystem/FilePath.h"
#include "System/FileSystem/WinFileSystem.h"
#include "System/FileSystem/FileUtils.h"
#include "System/FileSystem/FileTime.h"
#include "System/LogFileName.h"
#include "System/CmdLine.h"

#include "System/LogMover.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NLogg
{

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool LogMover::Init(int argc, char* argv[])
{
  // посмотрим, нет ли в ком.строке наших ключиков на "перенос старых логов"
  moveLogsTo = "";
	oldLogDaysLimit = 0;

	NCmdLine::CCmdLine cl( "", true ); // true: ignore unknown options
	cl.AddOption( "--movelogs", &moveLogsTo, "Move old logs to this sub-directory name" );
	cl.AddOption( "--movelogdays", &oldLogDaysLimit, "Move old logs, which are older than <float number> days" );
	
	if ( cl.Process( argc, argv ) != NCmdLine::CCmdLine::PROC_RESULT_OK )
		cl.PrintUsage( "Log Options Usage: --movelogs <to_subdir_name> --movelogdays <old_logs_storage_limit_days>" );

  // пока соберем все подходящие по расширению и времени имена файлов; потом, после того как определимся с именем кластера и т.п., отфильтруем нужные нам имена
  oldLogFileNames.clear();
  time_t osTime;  
  time(&osTime);
  time_t limitTime = osTime - (oldLogDaysLimit * 24*60*60); // time_t в секундах, опция задает время в сутках
  for ( NFile::CFileIterator it( (string(NDebug::GetDebugLogDir()) + "/*.txt").c_str() ); !it.IsEnd(); ++it )
	{
		if ( !it.IsDirectory() )
    {
      SWin32Time win32time = it.GetLastWriteTime();
      time_t fileTime = Win32ToDOSDateTime( win32time.GetFullTime() );

      if( fileTime < limitTime ) // файл достаточно старый?
  			oldLogFileNames.push_back( it.GetFileName() );
    }
	}

  return !oldLogFileNames.empty();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool LogMover::Move( const nstl::string & _substr )
{
  bool movedAnything = false;

  if( !moveLogsTo.empty() && !oldLogFileNames.empty() )
  {
    LOG_M(0) << "MOVE OLD LOGS to dir '" << moveLogsTo << "', log days limit=" << oldLogDaysLimit;

    string logDir = NDebug::GetDebugLogDir();
    string archiveDir = logDir + "/" + moveLogsTo;
    NFile::CreateDiskDirectory( archiveDir.c_str() );

    string clusterSubstr = string("-") + _substr + "_";
    for( vector<string>::iterator it = oldLogFileNames.begin(); it != oldLogFileNames.end(); ++it )
      if( _substr.empty() || (*it).find( clusterSubstr ) != (*it).npos )
      {
        LOG_D(0) << "> old log:" << *it;
#if defined( NV_WIN_PLATFORM )
        ::MoveFileEx( (logDir+"/"+(*it)).c_str(), (archiveDir+"/"+(*it)).c_str(), MOVEFILE_COPY_ALLOWED | MOVEFILE_REPLACE_EXISTING );
#elif defined( NV_WIN_PLATFORM )
        ::rename( (logDir+"/"+(*it)).c_str(), (archiveDir+"/"+(*it)).c_str() );
#endif
        movedAnything = true;
      }
  }

  return movedAnything;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LogMover & LogMover::GetInstance()
{
  static LogMover singleton;
  return singleton;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} //namespace NLogg

