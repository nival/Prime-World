#ifndef _SYSTEM_FILE_UTILS_H_
#define _SYSTEM_FILE_UTILS_H_

#ifdef NV_LINUX_PLATFORM
  #include <sys/types.h>
  #include <sys/stat.h>
  #include <unistd.h>
  #include <fcntl.h>
  #include <dirent.h>
  #include <sys/dir.h>
  #include <ctype.h>
  #include <locale.h>
  #include <glob.h>
  #include "nstring.h"

//#include <rpm/rpmdav.h>
#endif


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NFile
{

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/**
  @class CFileIterator
  @brief Find files by mask and iterate over results
  This is not valid forward iterator since it's not copyable
 */
class CFileIterator : private NonCopyable
{

public:
  typedef nstl::string       filename_type;
  typedef unsigned long      attrs_type;
  // TODO: перейти к unsigned - проверить по references
  typedef int                length_type;

public:
  CFileIterator( const filename_type & mask );
  ~CFileIterator() throw() { Close(); }

  const CFileIterator & Next();
  // Только постфиксный ++, т.к. у нас нет конструктора копирования
  const CFileIterator & operator++() { return Next(); }
  bool IsValid() const;
	bool IsEnd() const { return !IsValid(); }

#if defined( NV_WIN_PLATFORM )

  length_type GetLength() const { return findinfo_.nFileSizeLow; }
  filename_type GetFileName() const { return findinfo_.cFileName; }
	filename_type GetFullName() const { return path_ + GetFileName(); }

  attrs_type GetAttribs() const { return findinfo_.dwFileAttributes; }
	bool IsReadOnly() const    { return ( GetAttribs() & FILE_ATTRIBUTE_READONLY ) != 0; }
	bool IsSystem() const      { return ( GetAttribs() & FILE_ATTRIBUTE_SYSTEM ) != 0; }
	bool IsHidden() const      { return ( GetAttribs() & FILE_ATTRIBUTE_HIDDEN ) != 0; }
	bool IsDirectory() const   { return ( GetAttribs() & FILE_ATTRIBUTE_DIRECTORY ) != 0; }

#elif defined( NV_LINUX_PLATFORM )

  length_type GetLength() const { return static_cast< length_type >( stat_.st_size ); }
  filename_type GetFileName() const
  {
    if ( !IsValid() ) { filename_type(); }
    NI_ASSERT( data_.gl_pathv != 0, "glob struct is 0" );
    return filename_type( data_.gl_pathv[ ind_ ] + path_.length() );
  }
	filename_type GetFullName() const { return path_ + GetFileName(); }

  attrs_type GetAttribs() const
  {
    if ( !IsValid() ) { return 0; }
    return static_cast< attrs_type >( stat_.st_mode );
  }
	bool IsReadOnly() const;
	bool IsSystem() const      { return false; }
	bool IsHidden() const      { return false; }
	bool IsDirectory() const   { return S_ISDIR( stat_.st_mode ); }

#endif

	// special kind of directory: '.' - this dir and '..' - parent dir
	bool IsDots() const
  {
		return ( ( GetFileName() == "." ) || ( GetFileName() == ".." ) );
	}

  const SWin32Time GetLastWriteTime() const;
  // Эти функции есть только в Win32
  // Чтобы их грамотно спортировать, надо определиться с интерфейсом
#if defined( NV_WIN_PLATFORM )
  // file time attributes
	FILETIME GetCreationTime() const { return findinfo_.ftCreationTime; }
	FILETIME GetLastAccessTime() const { return findinfo_.ftLastAccessTime; }
	const _FILETIME    GetLastWriteFileTime() const { return findinfo_.ftLastWriteTime; }
  time_t GetISOLastWriteTime() const { return Win32ToDOSDateTime( GetLastWriteTime().GetFullTime() ); }
#endif

  const filename_type & GetBasePath() const { return mask_; }
  const filename_type & GetBaseMask() const { return path_; }

private:
  void FirstFile();
  void Close();

private:
  CFileIterator::filename_type mask_;
  CFileIterator::filename_type path_;
#if defined( NV_WIN_PLATFORM )
  HANDLE find_;
  WIN32_FIND_DATAA findinfo_;
#elif defined( NV_LINUX_PLATFORM )
  glob_t data_;
  size_t ind_;
  struct stat stat_;
#endif

}; // class CFileIterator


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// enumerate all files by mask.
// при рекурсивной енумерации сначала входим в директорию, а потом только получаем её имя (при выходе из рекурсии)
template <class TEnumFunc>
void EnumerateFiles( const string &szStartDir, const char *pszMask, TEnumFunc callback, bool bRecurse )
{
	string szDir = szStartDir;
	// iterate throug all files by mask
	for ( CFileIterator it( (szDir + pszMask).c_str() ); !it.IsEnd(); ++it )
	{
		if ( !it.IsDirectory() )
			callback( it );
	}
	// iterate throug all dirs by "*.*"
	for ( CFileIterator it( (szDir + "*.*").c_str() ); !it.IsEnd(); ++it )
	{
		if ( it.IsDirectory() && !it.IsDots() )
		{
			// dive into recurse
			if ( bRecurse )
				EnumerateFiles( (it.GetFullName() +	"\\").c_str(), pszMask, callback, bRecurse );
			//
			callback( it );
		}
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
string GetCurrDir();
string GetNormalizedCurrDir();
void SetCurrDir( const string &szDir );
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CCurrDirHolder
{
	string szDir;
public:
	CCurrDirHolder() { szDir = GetCurrDir(); }
	~CCurrDirHolder() { SetCurrDir( szDir ); }
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GetDirectoryDirs( const char *pszDirName, list<string> *pNames, bool bRecursive = true );
void GetDirectoryFiles( const char *pszDirName, const char *pszMask, list<string> *pNames, bool bRecurse = true );
void DeleteFiles( const char *pszStartDir, const char *pszMask, bool bRecursive );
void DeleteDirectory( const string &szDir );
void DeleteOldFiles( const char *szDirName, double olderThanSeconds );
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool DoesFileExist( const string &szFileName );
bool DoesFolderExist( const string &szFolderName );
bool EraseFile( const string &szFileName );
void ExecuteFile( const string& szFileName );

bool IsValidFileName( const string &szFileName );

// is valid win32 file name
bool IsValidDirName( const string &szName );
// copy file. create dst path before copying
bool CopyFile( const string &szSrcName, const string &szDstName );
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
string GetFullName( const string &szPath );
void GetFullName( string *pResult, const string &szPath );
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
string GetTempPath();
string GetTempFileName();
const bool IsXPointerName( const string &szFileName );
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// return number of bytes, free for the caller on the selected drive
double GetFreeDiskSpace( const char *pszDrive );
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int CreateFileWithDir( const char* fileName );
int OpenFileWithDir( const char* fileName );

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


int   GetCurDiskDirectory(char *buffer, int bufSize);
void  SetCurDiskDirectory(const char *dir);
bool  CreateDiskDirectory(const char *dirName, int dirFlags = 0);
int   GetDiskFullPathName(const char *fullName, const int outBufLen, char *outBufDrivePath, char **shortFileName);

#if defined( NV_LINUX_PLATFORM )

	bool CreateFullPath( char const * path );

#endif

}

#endif

