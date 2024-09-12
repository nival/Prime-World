#ifndef _LOGFILENAME_H_
#define _LOGFILENAME_H_

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NDebug
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SetProductNameAndVersion( const string& workDir, const char* productName, const char* productLine, int major, int minor, int build, int revision );
const char* GetProductName();
const wchar_t* GetProductNameW();
nstl::string GenerateDebugFileName( const char* suffix, const char* extension, const char* folder=0 , bool useFolder = true);
nstl::string GenerateDebugFileName( const struct tm& time, const char* suffix, const char* extension, const char* folder=0, bool useFolder = true);
nstl::string GenerateDebugFileNameWoTimestamp( const char* suffix, const char* extension, const char* folder=0);
const char* GetDebugLogDir();
void OverrideDebugLogDir( const char* folder );
const char* GetWorkDir();
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} //namespace NDebug

#endif

