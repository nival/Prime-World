#include "stdafx.h"

#include "LogFileName.h"
#include "TimeUtils.h"
#include "FileSystem/FilePath.h"

#include <System/ported/cwfn.h>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NDebug
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static char g_productName[128];
static wchar_t g_productNameW[128];
static char g_workDir[256] = {'.', 0};
static char g_logDir[MAX_PATH] = {0};


void SetProductNameAndVersion( const string& workDir, const char* productName, const char* productLine, int major, int minor, int build, int revision )
{
  std::sprintf( g_productName, "%s-%s-%d.%d.%02d.%04d", productName, productLine, major, minor, build, revision );
  MultiByteToWideChar( CP_ACP, 0, g_productName, -1, g_productNameW, sizeof( g_productNameW ) / sizeof( g_productNameW[0] ) );
  string dirWithoutSlash = workDir;
  NFile::RemoveSlash( &dirWithoutSlash );
  std::sprintf( g_workDir, "%s", dirWithoutSlash.c_str() );
}



const char* GetProductName()
{
  return g_productName;
}



const wchar_t* GetProductNameW()
{
  return g_productNameW;
}



nstl::string GenerateDebugFileName( const char* suffix, const char* extension, const char* folder, bool useFolder /*= true*/)
{
  struct tm t = {};
  GetOsUtcTime(&t);

  return GenerateDebugFileName( t, suffix, extension, folder, useFolder );
}



nstl::string GenerateDebugFileName( const struct tm  &tim, const char* suffix, const char* extension, const char* _folder, bool useFolder /*= true*/)
{
  char fileName[512];

  if (useFolder)
  {
    const char* folder = _folder ? _folder : GetDebugLogDir();
    std::sprintf( fileName, "%s/%s-%04d.%02d.%02d-%02d.%02d.%02d-%s.%s", folder, g_productName
      , tim.tm_year, tim.tm_mon, tim.tm_mday, tim.tm_hour, tim.tm_min, tim.tm_sec, suffix, extension );
  }
  else
  {
    std::sprintf( fileName, "%s-%04d.%02d.%02d-%02d.%02d.%02d-%s.%s", g_productName
      , tim.tm_year, tim.tm_mon, tim.tm_mday, tim.tm_hour, tim.tm_min, tim.tm_sec, suffix, extension );
  }

  return fileName;
}



nstl::string GenerateDebugFileNameWoTimestamp( const char * suffix, const char * extension, const char * _folder )
{
  const char* folder = _folder ? _folder : GetDebugLogDir();
	char fileName[MAX_PATH];
  std::sprintf( fileName, "%s/%s-%s.%s", folder, g_productName, suffix, extension);

	return fileName;
}



const char* GetDebugLogDir()
{
  if (g_logDir[0] != 0)
    return g_logDir;

  static char logDir[MAX_PATH];
  std::sprintf( logDir, "%s/logs/", GetWorkDir());

  return logDir;
}

void OverrideDebugLogDir( const char* folder )
{
  string dirWithoutSlash = folder;
  NFile::RemoveSlash( &dirWithoutSlash );
  // sprintf_s( g_logDir, "%s", dirWithoutSlash.c_str() );
  NStr::Printf( g_logDir, MAX_PATH, "%s", dirWithoutSlash.c_str() );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char* GetWorkDir()
{
  return g_workDir;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} //namespace NDebug

