#include "../../../../System/stdafx.h"

#include "FlashCompiler.h"

#include <windows.h>
#include <stdio.h>
#include <fstream>

#include <sys/stat.h>

bool FileExists(const char * filename) 
{
  bool ifExist = false;
  std::fstream fin;
  fin.open(filename,std::ios::in);
  if( fin.is_open() )
  {
    ifExist=true;
  }
  fin.close();

  return ifExist;
}

void CompileSource( const char * cmdLine );

nstl::string FlashCompiler::CompileActionFile( const char * actionFile )
{
  nstl::string abcStrFile(actionFile);
  nstl::string batFile("_build_test.bat");

  CompileSource((batFile + " "+ actionFile).c_str());
  
  abcStrFile.replace(abcStrFile.end()-2,abcStrFile.end(),"abc"); 
  const char * abcFile = abcStrFile.c_str();

  if (!FileExists(abcFile)) nstl::string();

  return abcFile;
}

void CompileSource( const char * cmdLine )
{
  STARTUPINFO si;
  PROCESS_INFORMATION pi;

  ZeroMemory( &si, sizeof(si) );
  si.cb = sizeof(si);
  ZeroMemory( &pi, sizeof(pi) );

  char * cmdline = const_cast<char*>(cmdLine);
    // Start the child process. 
  if( !CreateProcess( NULL,   // No module name (use command line)
    cmdline,        // Command line
    NULL,           // Process handle not inheritable
    NULL,           // Thread handle not inheritable
    FALSE,          // Set handle inheritance to FALSE
    0,              // No creation flags
    NULL,           // Use parent's environment block
    NULL,           // Use parent's starting directory 
    &si,            // Pointer to STARTUPINFO structure
    &pi )           // Pointer to PROCESS_INFORMATION structure
    ) 
  {
    printf( "CreateProcess failed (%d).\n", GetLastError() );
    return;
  }

  // Wait until child process exits.
  WaitForSingleObject( pi.hProcess, INFINITE );

  // Close process and thread handles. 
  CloseHandle( pi.hProcess );
  CloseHandle( pi.hThread );
}
