#include "stdafx.h"

#ifdef WIN32
  #include <tchar.h>
#endif  

#include "FileUtils.h"
#include "FilePath.h"
#include <System/StrProc.h>
#include <System/ported/cwfn.h>

//objbase.h has its own defenition of "_interface"
#undef _interface

#ifdef WIN32
#include <objbase.h>
#include <shlwapi.h>
#pragma comment( lib, "shlwapi" ) 
#endif

#include <ctime>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NFile
{
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const unsigned long BUFFER_SIZE = 1024;
static char buffer[BUFFER_SIZE];
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ************************************************************************************************************************ //
// **
// ** class CFileIterator functions
// **
// **
// **
// ************************************************************************************************************************ //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ************************************************************************************************************************ //
//																				 external file utilites
// ************************************************************************************************************************ //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef WIN32
// LINUX: not used in project
class CDeleteFiles
{
	bool bDeleteRO;
	bool bDeleteDir;
public:
	CDeleteFiles( bool _bDeleteRO, bool _bDeleteDir ) : bDeleteRO( _bDeleteRO ), bDeleteDir( _bDeleteDir ) {	}
	//
	void operator()( const CFileIterator &it )
	{
		if ( !it.IsDirectory() )
		{
			if ( bDeleteRO && it.IsReadOnly() )
				SetFileAttributesA( it.GetFullName().c_str(), it.GetAttribs() & ~FILE_ATTRIBUTE_READONLY );
			DeleteFileA( it.GetFullName().c_str() );
		}
		else if ( bDeleteDir )
		{
			if ( bDeleteRO && it.IsReadOnly() )
				SetFileAttributesA( it.GetFullName().c_str(), it.GetAttribs() & ~FILE_ATTRIBUTE_READONLY );
			RemoveDirectoryA( it.GetFullName().c_str() );
		}
	}
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DeleteFiles( const char *pszStartDir, const char *pszMask, bool bRecursive )
{
	EnumerateFiles( pszStartDir, pszMask, CDeleteFiles(true, false), bRecursive );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DeleteDirectory( const string &szDir )
{
	EnumerateFiles( szDir, "*.*", CDeleteFiles(true, true), true );
	RemoveDirectoryA( szDir.c_str() );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class DeleteOldFilesFnc
{
  double olderThanSeconds;
  time_t curTime;

public:
  explicit DeleteOldFilesFnc( double olderThanSeconds ) : olderThanSeconds( olderThanSeconds ) 
  {	
    time(&curTime);  
  }
  
  void operator()( const CFileIterator &it )
  {
    if ( 
      !it.IsDots() && !it.IsReadOnly() && 
      std::difftime(curTime, it.GetISOLastWriteTime()) > olderThanSeconds 
    )
    {
      if ( it.IsDirectory() )
      {
        DeleteDirectory( it.GetFullName() );
      }
      else if( std::remove(it.GetFullName().c_str()) != 0 )
      {
        DebugTrace( "Can't delete file %s", it.GetFullName().c_str() );   
      }
    }
  }
};

void DeleteOldFiles( const char *szDirName, double olderThanSeconds )
{
  EnumerateFiles( szDirName, "*.*", DeleteOldFilesFnc(olderThanSeconds), false );
}

#endif

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CDirFileEnum
{
	list<string> *pNames;			// store names here
	bool bDir;														// enumerate dirs
	bool bFile;														// enumerate files
public:
	CDirFileEnum( list<string> *_pNames, bool _bDir, bool _bFile ) 
		: pNames( _pNames ), bDir( _bDir ), bFile( _bFile ) {	}
	void operator()( const CFileIterator &it )
	{
		if ( it.IsDirectory() )
		{
			if ( bDir )
				pNames->push_back( it.GetFullName() );
		}
		else if ( bFile )
			pNames->push_back( it.GetFullName() );
	}
};
void GetDirectoryDirs( const char *pszDirName, list<string> *pNames, bool bRecursive )
{
	EnumerateFiles( pszDirName, "*.*", CDirFileEnum(pNames, true, false), bRecursive );
}
void GetDirectoryFiles( const char *pszDirName, const char *pszMask, list<string> *pNames, bool bRecurse )
{
	EnumerateFiles( pszDirName, pszMask, CDirFileEnum(pNames, false, true), bRecurse );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// return number of bytes, free for the caller on the selected drive
#ifdef WIN32
// LINUX: not used in project

double GetFreeDiskSpace( const char *pszDrive )
{
	typedef BOOL (WINAPI *GDFSE)( const char*, PULARGE_INTEGER, PULARGE_INTEGER, PULARGE_INTEGER );

	GDFSE pfnGetDiskFreeSpaceEx = (GDFSE)GetProcAddress( GetModuleHandleA("kernel32.dll"), "GetDiskFreeSpaceExA" );
	BOOL bRetVal = FALSE;
	double fRetVal = 0;
	if ( pfnGetDiskFreeSpaceEx )
	{
	 ULARGE_INTEGER i64FreeBytesToCaller, i64TotalBytes, i64FreeBytes;
	 bRetVal = (*pfnGetDiskFreeSpaceEx)( pszDrive, &i64FreeBytesToCaller,
																			 &i64TotalBytes, &i64FreeBytes );
	 fRetVal = double( __int64(i64FreeBytesToCaller.QuadPart) );
	} 
	else 
	{
		unsigned long dwSectPerClust, dwBytesPerSect, dwFreeClusters, dwTotalClusters;
		bRetVal = GetDiskFreeSpaceA( pszDrive, &dwSectPerClust, &dwBytesPerSect,
																&dwFreeClusters, &dwTotalClusters );
		fRetVal = double( dwFreeClusters ) * double( dwSectPerClust ) * double( dwBytesPerSect );
	}

	return ( bRetVal == 0 ? 0 : fRetVal );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool IsValidFileName( const string &szFileName )
{
	const char *pszFileName = szFileName.c_str();
	const char *_pszFileName = max( strrchr( pszFileName, '\\' ), strrchr( pszFileName, '/' ) );
	if ( 0 == _pszFileName )
		_pszFileName = pszFileName;
	else
		++ _pszFileName;
	static char szValidCharSet[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ.-_0123456789 ";
	return 0 == strspn( _pszFileName, szValidCharSet );
}
#endif
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const char *pszWrongNames[] = {
	"con", "prn", "aux", "clock$", "nul", 
	"com1", "com2", "com3", "com4", "com5", "com6", "com7", "com8", "com9", 
	"lpt1", "lpt2", "lpt3", "lpt4", "lpt5", "lpt6", "lpt7", "lpt8", "lpt9",
	0
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// is valid win32 file name
bool IsValidDirName( const string &_szName )
{
	string szName = _szName;
	if ( szName.empty() || szName.size() > 250 )
		return false;
	NStr::ToLower( &szName );
	for ( int i = 0; i < szName.size(); ++i )
	{
		int c = (unsigned char) szName[i];
		if ( c < 33 || c == '<' || c == '>' || c == ':' || c == '"' || c == '/' || c == '\\' || c == '|' || c == '*' || c == '?' )
			return false;
	}
	for ( const char **p = pszWrongNames; *p; ++p )
	{
		if ( szName == *p )
			return false;
	}
	return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const bool IsXPointerName( const string &szFileName )
{
	return szFileName.find( '#') != string::npos;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef WIN32
// LINUX: not used in project
bool CopyFile( const string &szSrcName, const string &szDstName )
{
	CreatePath( GetFilePath( szDstName ) );
	return ::CopyFileA( szSrcName.c_str(), szDstName.c_str(), false ) != 0;
}

#endif

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
string GetFullName( const string &szPath )
{
	if(NFile::GetBaseDir() == "")
  {
    NFile::InitBaseDir();
  }
  string fillPath(szPath);
  if ( IsPathRelative( szPath ) )
  {
    fillPath = NFile::GetBaseDir() + szPath;
  }

  char *buffer = (char *)alloca((MAX_PATH + 1)* sizeof(char));
  PathCanonicalizeA(buffer, fillPath.c_str());
  return buffer;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GetFullName( string *pResult, const string &szPath )
{
  NI_VERIFY(pResult, "Cannot be empty", return;);
  pResult->assign(GetFullName(szPath));
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef WIN32
string GetTempPath()
{
	int nLength = ::GetTempPathA( BUFFER_SIZE, buffer );
	if ( nLength == 0 )
		return ".\\";
	else if ( buffer[nLength - 1] != '\\' )
	{
		buffer[nLength] = '\\';
		++nLength;
	}
	buffer[nLength] = 0;
	return buffer;
}

string GetTempFileName()
{
	GUID guid;
	::CoCreateGuid( &guid );
	string szFileName;
	NStr::GUID2String( &szFileName, guid );
	return GetTempPath() + szFileName;
}
#endif

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
string GetCurrDir()
{
	char buffer[1024];
	const int nLen = GetCurDiskDirectory(buffer, sizeof(buffer));
	return nLen == 0 ? "" : buffer;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
string GetNormalizedCurrDir()
{
	//string szCurrDir = GetCurrDir();
	//NFile::NormalizePath( &szCurrDir );
	//NFile::AppendSlash( &szCurrDir, '/' );
	return "./"; //szCurrDir;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SetCurrDir( const string &szDir )
{
	SetCurDiskDirectory( szDir.c_str() );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}; // namespace NFile ends
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
