#ifndef _FILE_PATH_H_
#define _FILE_PATH_H_

#ifdef NV_LINUX_PLATFORM
  #include "nlist.h"
  #include "nstring.h"
#endif

#include "System/ported/types.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NFile
{
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CFilePath;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//! Check, is given char folder separator?
template <typename T>
__forceinline bool IsFolderSeparator( const T chr )
{
  return chr == L'/' || chr == L'\\';
}

template <typename T>
int FindLastSlash( const T& szFullFilePath )
{
  int i = szFullFilePath.size();
  while ( --i >= 0 )
  {
    if ( IsFolderSeparator(szFullFilePath[i]) )
      return i;
  }
  return int( string::npos );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//! Get folder path from full file path name (c:/mydir/myfile.txt => c:/mydir/).
//! \return Folder path or empty string (in the cast of bare filename)
const NFile::CFilePath GetFilePath( const NFile::CFilePath &fullFilePath );

template <typename T>  T GetFolder( const T& fullFilePath )
{
  const int nPos = FindLastSlash( fullFilePath );
  return (nPos != (int)T::npos) ? fullFilePath.substr( 0, nPos + 1 ) : L"";
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//! Get file name from full file path name (c:/mydir/myfile.txt => myfile.txt).
//! \return File name or empty string (in the case of folder path)
template <typename T>
T GetFileName( const T &szFullFilePath )
{
  const int nPos = FindLastSlash( szFullFilePath );
  return (nPos != (int)T::npos) ? szFullFilePath.substr( nPos + 1 ) : szFullFilePath;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//! Get file title full file path name (c:/mydir/myfile.txt => myfile)
//! \return File title or empty string (in the case of folder path)
string GetFileTitle( const string &szFullFilePath );
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//! Get file extension full file path name (c:/mydir/myfile.txt => .txt)
//! \return File extension or empty string (in the case of folder path or extension-less file name)
string GetFileExt( const string &szFullFilePath );
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//! Cut file's extension (any part before '.' (and this '.' must be before path separator))
//! \return File full path without extension
string CutFileExt( const string &szFullFilePath, const char *pszExt );
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//! Split full file path into parts.
void SplitPath( list<string> *pRes, const string &szFullFilePath );
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//! Compare (sub)pathes on equality, ignore case and path separator type.
//! \return True if (sub)pathes are equal and false in other case
bool ComparePathEq( const int nStart1, const int nLength1, const string &szPath1, 
										const int nStart2, const int nLength2, const string &szPath2 );
//! Compare full pathes on equality, ignore case and path separator type.
//! \return True if pathes are equal and false in other case
__forceinline bool ComparePathEq( const string &szPath1, const string &szPath2 ) { return ComparePathEq( 0, szPath1.size(), szPath1, 0, szPath2.size(), szPath2 ); }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//! Compare (sub)pathes on less-then, ignore case and path separator type.
//! \return True if first (sub)path are less then second one and false in other case
bool ComparePathLt( const int nStart1, const int nLength1, const string &szPath1, 
									 const int nStart2, const int nLength2, const string &szPath2 );
bool ComparePathBt( const int nStart1, const int nLength1, const string &szPath1, 
									 const int nStart2, const int nLength2, const string &szPath2 );
//! Compare full pathes on less-then, ignore case and path separator type.
//! \return True if first path are less then second and false in other case
__forceinline bool ComparePathLt( const string &szPath1, const string &szPath2 ) { return ComparePathLt( 0, szPath1.size(), szPath1, 0, szPath2.size(), szPath2 ); }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//! Returns true if supplyed path is in relative form
bool IsPathRelative( const string &szPath );
//! Make relative path from parent's and full one. Prepends with '/' in the case of the result path are absolute (can't be represented as relative to parent's)
void MakeRelativePath( string *pRes, const string &szFullPath, const string &szParentPath );
//! Make full path from relative and parent's. Is relative path already prepended with '/' or '\', it is treated as absolute
void MakeFullPath( string *pRes, const string &szRelativePath, const string &szParentPath );
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//! Replace all '\' to '/'. One can pass the same string in both parameters
void NormalizePath( string *pRes, const string &szFilePath );
__forceinline void NormalizePath( string *pFilePath ) { NormalizePath( pFilePath, *pFilePath ); }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if defined( NV_WIN_PLATFORM )
const char FILE_SEPARATOR = '\\';
#elif defined( NV_LINUX_PLATFORM )
const char FILE_SEPARATOR = '/';
#endif
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if defined( NV_WIN_PLATFORM )
void AppendSlash( string *pFilePath, const char cSlash = '\\' );
#elif defined( NV_LINUX_PLATFORM )
void AppendSlash( string *pFilePath, const char cSlash = '/' );
#endif
void RemoveSlash( string *pFilePath );
void ConvertSlashes( string *pFilePath, const char cFrom, const char cTo );
#if defined( NV_WIN_PLATFORM )
string Combine( const string &leftPath, const string &rightPath, const char cSlash = '\\' );
#elif defined( NV_LINUX_PLATFORM )
string Combine( const string &leftPath, const string &rightPath, const char cSlash = '/' );
#endif
////////////////////////////////////////////////////////////////////////////////////////////////////////
bool WildcardMatch( const string &szPattern, const string &szString, bool bCaseSensitive );
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//! Create path on the disk
void CreatePath( const string &szFullPath );
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CFilePath : public string
{
public:
	CFilePath() {}
	CFilePath( const char *_pszFilePath ): string( _pszFilePath ) {}
	CFilePath( const string &_szFilePath ): string( _szFilePath ) {}
	CFilePath( const CFilePath &path ): string( path ) {}
	//
	const CFilePath &operator=( const char *_pszFilePath ) { (*(string*)this) = _pszFilePath; return *this; }
	const CFilePath &operator=( const string &szFilePath ) { (*(string*)this) = szFilePath; return *this; }
	const CFilePath &operator=( const CFilePath &filePath ) { (*(string*)this) = filePath; return *this; }
	//
	int MakeHashKey() const;

	bool operator<( const NFile::CFilePath &filePath2 ) const { return NFile::ComparePathLt(0, size(), *this, 0, filePath2.size(), filePath2 ); }
	bool operator>( const NFile::CFilePath &filePath2 ) const { return NFile::ComparePathBt(0, size(), *this, 0, filePath2.size(), filePath2 ); }

	bool operator<=( const NFile::CFilePath &filePath2 ) const { return !operator>( filePath2 ); }
	bool operator>=( const NFile::CFilePath &filePath2 ) const { return !operator<( filePath2 ); }

	bool operator==( const NFile::CFilePath &filePath2 ) const { return NFile::ComparePathEq(0, size(), *this, 0, filePath2.size(), filePath2 ); }
	bool operator!=( const NFile::CFilePath &filePath2 ) const { return !operator==( filePath2 ); }

	//
	int operator&( IBinSaver &saver );
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void InitBaseDir(wchar_t const *rootDir = NULL);
const string &GetBaseDir();
const string &GetBinDir();

void SetModuleCurrentDir();
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace nstl
{
	template<> struct hash<NFile::CFilePath>
	{
		size_t operator()( const NFile::CFilePath &path ) const { return path.MakeHashKey(); }
	};
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class SConvertCharsTable
{
	char lookup[256];
	
public:
	SConvertCharsTable( char (*func)(char) )
	{
		//ASSERT( sizeof( char ) == 1 );
		for( int i = 0; i < 256; ++i )
			lookup[i] = func( (char)((unsigned char)i) );
	}

	__forceinline char LookUp( const char chr ) const
	{
		return lookup[ (unsigned char)chr ];
	}
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
char ConvertChar_ToUpperAndSlash( char chr );
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

