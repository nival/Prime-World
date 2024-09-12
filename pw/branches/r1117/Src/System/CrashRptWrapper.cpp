#include "stdafx.h"
#include "CrashRptWrapper.h"

#include "System/StackWalk.h"
#include "System/TimeUtils.h"
#include "System/BSUtil.h"
#include "MemoryLib/SymAccess.h"
#include "Version.h"
#include "FileSystem/FilePath.h"
#include "FileSystem/FileUtils.h"
#include <CrashRpt.h>


namespace CrashRptWrapper
{

static BOOL WINAPI CrashCallback( PEXCEPTION_POINTERS pExceptionPointers, LPVOID lpvState );

static bool s_installed = false;

void InstallForProcess( const char * uploadUrl, bool useBinaryEncoding, bool noGui, const char * productTitleOverride, const char * privacyPolicyUrl, bool enableLogging /*= false*/, bool sendQueuedReports /*= true*/ )
{
  if ( s_installed )
    return;

  string versionString( NI_STRFMT( "%s-%s-%d.%d.%02d.%04d-b.%s", VERSION_LINE, VERSION_TYPE, VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH, VERSION_REVISION, VERSION_BUILD ) );

  CR_INSTALL_INFO info;
  memset( &info, 0, sizeof( CR_INSTALL_INFO ) );
  info.cb = sizeof( CR_INSTALL_INFO );
  info.pszAppName = productTitleOverride ? productTitleOverride : PRODUCT_TITLE;
  info.pszAppVersion = versionString.c_str();
  info.pszEmailSubject = NULL;
  info.pszEmailTo = NULL;
  info.pszUrl = uploadUrl;
  info.pfnCrashCallback = CrashCallback;
  info.uPriorities[CR_SMTP] = CR_NEGATIVE_PRIORITY;
  info.uPriorities[CR_SMAPI] = CR_NEGATIVE_PRIORITY;
  info.uPriorities[CR_HTTP] = 1;
  info.dwFlags = 0;
  //  выставляем обработчики флагов так чтобы работал перехват Ctrl+C в консоли через SetConsoleCtrlHandler
  info.dwFlags |= CR_INST_SEH_EXCEPTION_HANDLER
    | CR_INST_TERMINATE_HANDLER
    | CR_INST_UNEXPECTED_HANDLER
    | CR_INST_PURE_CALL_HANDLER
    | CR_INST_NEW_OPERATOR_ERROR_HANDLER
    | CR_INST_SECURITY_ERROR_HANDLER
    | CR_INST_INVALID_PARAMETER_HANDLER
    | CR_INST_SIGABRT_HANDLER
    | CR_INST_SIGFPE_HANDLER
    //| CR_INST_SIGILL_HANDLER
    //| CR_INST_SIGINT_HANDLER
    //| CR_INST_SIGSEGV_HANDLER
    //| CR_INST_SIGTERM_HANDLER
    //| CR_INST_CRT_EXCEPTION_HANDLERS
    ;

  if ( noGui )
    info.dwFlags |= CR_INST_NO_GUI;

  if ( enableLogging )
    info.dwFlags |= CR_INST_ENABLE_LOGGING;

  if ( useBinaryEncoding )
    info.dwFlags |= CR_INST_HTTP_BINARY_ENCODING;

  if ( sendQueuedReports ) 
    info.dwFlags |= CR_INST_SEND_QUEUED_REPORTS;

  info.pszDebugHelpDLL = NULL;
  info.uMiniDumpType = MiniDumpNormal;

  info.pszPrivacyPolicyURL = privacyPolicyUrl;
  info.pszErrorReportSaveDir = NULL;
  info.pszRestartCmdLine = NULL;

  // get the current language from the 'lang.cfg' file
  // get the current language from the 'lang.cfg' file
  nstl::string filepath("");

  nstl::string lang;
  NStr::UnicodeToUTF8(&lang, NGlobal::GetVar("language").GetString());
  if (!lang.empty())
  {
    filepath = NFile::Combine(NFile::GetBaseDir(), "Data/Localization/" + lang + "/crashrpt_lang.ini");
  }

  if (NFile::DoesFileExist(filepath))
    info.pszLangFilePath = filepath.c_str();

  int installResult = crInstall( &info );
  //NI_ASSERT( installResult == 0, "Failed to install exception handler" )
  if( installResult != 0 )
  {
    char szErrorMsg[512] = "";
    crGetLastErrorMsg( szErrorMsg, 512 );
    NI_ALWAYS_ASSERT( NI_STRFMT( "Failed to install CrashRpt handler: %s", szErrorMsg ) );
    return;
  }

  char computerName[128] = "";
  GetEnvironmentVariable( "COMPUTERNAME", computerName, 128 );
  crAddProperty( "ComputerName", computerName );

  s_installed = true;
}



void UninstallFromProcess()
{
  if ( !s_installed )
    return;

  crUninstall();

  s_installed = false;
}



void InstallToCurrentThread()
{
  if ( !s_installed )
    return;

  crInstallToCurrentThread2( 0 );
}



void UninstallFromCurrentThread()
{
  if ( !s_installed )
    return;

  crUninstallFromCurrentThread();
}



void AddFileToReport( const char * filename, const char * description )
{
  if ( s_installed )
    crAddFile2( filename, NULL, description, CR_AF_MAKE_FILE_COPY );
}



void AddTagToReport( const char * name, const char * value )
{
  if ( s_installed )
    crAddProperty( name, value );
}



static BOOL WINAPI CrashCallback( PEXCEPTION_POINTERS pExceptionPointers, LPVOID lpvState )
{
  vector<SCallStackEntry> entries;
  CollectCallStack( &entries, pExceptionPointers );

  struct tm t;
  GetOsUtcTime(&t);
  string excepFilename;
  NBSU::WriteExceptionLogFile( t, pExceptionPointers, entries, &excepFilename );

  crAddFile2( excepFilename.c_str(), NULL, "Exception Description", CR_AF_MAKE_FILE_COPY );
#ifndef _SHIPPING
  crAddScreenshot( CR_AS_MAIN_WINDOW );
#endif _SHIPPING

  return TRUE;
}

} //namespace CrashRptWrapper
