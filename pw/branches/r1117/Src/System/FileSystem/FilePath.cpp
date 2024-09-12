#include "stdafx.h"

#include "FilePath.h"
#include "FileUtils.h"
#include "System/StrProc.h"

#include <string>


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static string szBaseDir = "";
static string szBinDir = "";

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NFile
{
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SConvertCharsTable tblChars( ConvertChar_ToUpperAndSlash );
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
__forceinline char ConvertChar( const char chr )
{
	return tblChars.LookUp( chr );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
__forceinline char ConvertFolderSeparator( const char chr )
{
	const char temp = chr - '\\';
	const char mask = (temp >> 7) | ((-temp) >> 7);
  return (chr & mask) | (NFile::FILE_SEPARATOR & (~mask));
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static int FindLastSlash( const string &szFullFilePath )
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
// ************************************************************************************************************************ //
// **
// ** path splitting functions
// **
// **
// **
// ************************************************************************************************************************ //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const NFile::CFilePath GetFilePath( const NFile::CFilePath &fullFilePath )
{
	const int nPos = FindLastSlash( fullFilePath );
	return (nPos != (int)string::npos) ? fullFilePath.substr( 0, nPos + 1 ) : "";
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
string GetFileTitle( const string &szFullFilePath )
{
	const string szFileName = GetFileName( szFullFilePath );
	const int nPos = szFileName.rfind( '.' );
	return (nPos != (int)string::npos) ? szFileName.substr( 0, nPos ) : szFileName;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
string GetFileExt( const string &szFullFilePath )
{
	const int nPos = szFullFilePath.rfind( '.' );
	return (nPos != (int)string::npos) ? szFullFilePath.substr( nPos ) : "";
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
string CutFileExt( const string &szFullFilePath, const char *pszExt )
{
	if ( szFullFilePath.empty() )
		return szFullFilePath;
	//
	if ( pszExt == 0 || pszExt[0] == 0 )
	{
		const int nPos = FindLastSlash( szFullFilePath );
		for ( int i = szFullFilePath.size() - 1; i > nPos; --i )
		{
			if ( szFullFilePath[i] == '.' )
				return szFullFilePath.substr( 0, i );
		}
		return szFullFilePath;
	}
	else
	{
		const int nPos = szFullFilePath.rfind( '.' );
		const int nCmpSize = szFullFilePath.size() - (nPos + 1);
		if ( (nPos != (int)string::npos) && ComparePathEq(nPos + 1, nCmpSize, szFullFilePath, 0, strlen(pszExt), pszExt) != false )
			return szFullFilePath.substr( 0, nPos );
		return	szFullFilePath;
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static int FindNextSlash( const string &szFullFilePath, const int nStartPos )
{
	for ( int i = nStartPos; i < szFullFilePath.size(); ++i )
	{
		if ( IsFolderSeparator(szFullFilePath[i]) )
			return i;
	}
	return (int)string::npos;
}
void SplitPath( list<string> *pRes, const string &szFullFilePath )
{
	int nLastPos = 0;
	do
	{
		const int nPos = FindNextSlash( szFullFilePath, nLastPos );
		pRes->push_back( szFullFilePath.substr( nLastPos, nPos - nLastPos ) );
		nLastPos = nPos + 1;
	} while( nLastPos != static_cast<int>(string::npos) + 1 );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ************************************************************************************************************************ //
// **
// ** comparison functions
// **
// **
// **
// ************************************************************************************************************************ //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ComparePathEq( const int nStart1, const int nLength1, const string &szPath1, 
										const int nStart2, const int nLength2, const string &szPath2 )
{
	if ( nLength1 != nLength2 )
		return false;
	if ( &szPath1 == &szPath2 )
		return true;
	if ( nLength1 == 0 )
		return true;
	//
	const char *p1 = &( szPath1[nStart1] );
	const char *p2 = &( szPath2[nStart2] );
	for ( int i = 0; i < nLength1; ++i )
	{
		if ( ConvertChar(p1[i]) != ConvertChar(p2[i]) )
			return false;
	}
	return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ComparePathLt( const int nStart1, const int nLength1, const string &szPath1, 
									 const int nStart2, const int nLength2, const string &szPath2 )
{
	const int nLength = min( nLength1, nLength2 );
	if ( nLength > 0 )
	{
		const char *p1 = &( szPath1[nStart1] );
		const char *p2 = &( szPath2[nStart2] );
		for ( int i = 0; i < nLength; ++i )
		{
			const char chp1 = ConvertChar(p1[i]);
			const char chp2 = ConvertChar(p2[i]);
			if ( chp1 < chp2 )
				return true;
			if ( chp1 > chp2 )
				return false;
		}
	}

	return nLength1 < nLength2;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ComparePathBt( const int nStart1, const int nLength1, const string &szPath1, 
									 const int nStart2, const int nLength2, const string &szPath2 )
{
	const int nLength = min( nLength1, nLength2 );
	const char *p1 = &( szPath1[nStart1] );
	const char *p2 = &( szPath2[nStart2] );
	for ( int i = 0; i < nLength; ++i )
	{
		const char chp1 = ConvertChar(p1[i]);
		const char chp2 = ConvertChar(p2[i]);
		if ( chp1 > chp2 )
			return true;
		if ( chp1 < chp2 )
			return false;
	}

	return nLength1 > nLength2;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool IsPathRelative( const string &szPath )
{
	return !IsFolderSeparator(szPath[0]) && (szPath[1] != ':');
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MakeRelativePath( string *pRes, const string &szFullPath, const string &szParentPath )
{
	if ( szFullPath.empty() )
	{
		pRes->clear();
		return;
	}
	//
	const int nPos = FindLastSlash( szParentPath );
	if ( (nPos != (int)string::npos) && ComparePathEq(0, nPos + 1, szParentPath, 0, nPos + 1, szFullPath) )
		*pRes = szFullPath.c_str() + nPos + 1;
	else
		*pRes = '/' + szFullPath;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MakeFullPath( string *pRes, const string &szRelativePath, const string &szParentPath )
{
	if ( szRelativePath.empty() )
	{
		pRes->clear();
		return;
	}
	else if ( szParentPath.empty() )
	{
		*pRes = IsFolderSeparator(szRelativePath[0]) == true ? szRelativePath.c_str() + 1 : szRelativePath;
		return;
	}
	//
	if ( IsFolderSeparator(szRelativePath[0]) ) // absolute path
		*pRes = szRelativePath.c_str() + 1;
	else	// relative to parent's path
	{
		const int nPos = FindLastSlash( szParentPath );
		if ( nPos != (int)string::npos )
			*pRes = szParentPath.substr( 0, nPos ) + "/" + szRelativePath;
		else
			*pRes = szRelativePath;
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void NormalizePath( string *pRes, const string &szFilePath )
{
	const int nSize = szFilePath.size();
	pRes->resize( szFilePath.size() );
	
  int i = 0;

  // preserve double-backslash in UNC path names
  if (szFilePath[0] == '\\' && szFilePath[1] == '\\')
  {
    (*pRes)[i++] = '\\';
    (*pRes)[i++] = '\\';
  }

  for ( ; i < nSize; ++i )
		(*pRes)[i] = ConvertFolderSeparator( szFilePath[i] );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AppendSlash( string *pFilePath, const char cSlash )
{
	if ( !pFilePath->empty() && !IsFolderSeparator((*pFilePath)[pFilePath->size() - 1]) ) 
		(*pFilePath) += cSlash;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RemoveSlash( string *pFilePath )
{
	if ( !pFilePath->empty() && IsFolderSeparator((*pFilePath)[pFilePath->size() - 1]) ) 
		pFilePath->resize( pFilePath->size() - 1 );
}
void ConvertSlashes( string *pFilePath, const char cFrom, const char cTo )
{
	for ( string::iterator it = pFilePath->begin(); it != pFilePath->end(); ++it )
	{
		if ( *it == cFrom ) 
			*it = cTo;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
string Combine( const string &leftPath, const string &rightPath, const char cSlash )
{
	string left = leftPath;
	string right = rightPath;

	NStr::TrimRight( left, '\\' );
	NStr::TrimLeft( right, '\\' );
	NStr::TrimRight( left, '/' );
	NStr::TrimLeft( right, '/' );

  string result = ( left.empty() ? right : left + cSlash + right );

	return result;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// author Jack Handy
// Modified by Joshua Jensen.
//
// Borrowed from http://www.codeproject.com/.
//
bool WildcardMatch( const string &szPattern, const string &szString, bool bCaseSensitive )
{
	string::const_iterator patternIt = szPattern.begin();
	string::const_iterator stringIt = szString.begin();

	// Handle all the letters of the pattern and the string.
	while ( *stringIt != 0	&&	*patternIt != '*' )
	{
		if ( *patternIt != '?' )
		{
			if ( bCaseSensitive )
			{
				if ( *patternIt != *stringIt )
					return false;
			}
			else
			{
				if ( toupper( *patternIt ) != toupper( *stringIt ) )
					return false;
			}
		}

		patternIt++;
		stringIt++;
	}

	const char* mp = NULL;
	const char* cp = NULL;
	while ( *stringIt != 0 )
	{
		if (*patternIt == '*')
		{
			// It's a match if the wildcard is at the end.
			if ( *++patternIt == 0 )
			{
				return true;
			}

			mp = patternIt;
			cp = stringIt + 1;
		}
		else
		{
			if ( bCaseSensitive )
			{
				if ( *patternIt == *stringIt	||	*patternIt == '?' )
				{
					patternIt++;
					stringIt++;
				}
				else 
				{
					patternIt = mp;
					stringIt = cp++;
				}
			}
			else
			{
				if ( toupper( *patternIt ) == toupper( *stringIt )	||	*patternIt == '?' )
				{
					patternIt++;
					stringIt++;
				}
				else
				{
					patternIt = mp;
					stringIt = cp++;
				}
			}
		}
	}

	// Collapse remaining wildcards.
	while ( *patternIt == '*' )
		patternIt++;

	return !*patternIt;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CreatePath( const string &_szFullPath )
{	
	static char buffer[1024];
	string szFullPath = _szFullPath;
	NStr::ReplaceAllChars( &szFullPath, '/', '\\' );
	// remember current directory
  GetCurDiskDirectory(buffer, sizeof(buffer));
	// for local full path
#if defined( NV_WIN_PLATFORM )
	if ( szFullPath.size() > 1 && szFullPath[1] == ':' )
	{
		int pos = szFullPath.find_first_of( '\\' );
		if ( pos != (int)string::npos )
		{
			string curDir = string( szFullPath.begin(), szFullPath.begin() + pos + 1 );
			SetCurDiskDirectory( curDir.c_str() );
			szFullPath.assign( szFullPath.begin() + pos + 1, szFullPath.end() );
		}
	}
#elif defined( NV_LINUX_PLATFORM )
  if ( szFullPath.size() > 1 && szFullPath[0] == '\\' )
	{
    SetCurDiskDirectory( "/" );
    szFullPath.assign( szFullPath.begin() + 1, szFullPath.end() );
	}
#endif
	// for UNC name
	else if ( szFullPath.size() > 2 && szFullPath[0] == '\\' && szFullPath[1] == '\\' )
	{
		int pos = szFullPath.find_first_of( '\\', 2 );
		pos = szFullPath.find_first_of( '\\', pos + 1 );
		if ( pos != (int)string::npos )
		{
			string curDir = string( szFullPath.begin(), szFullPath.begin() + pos );
			SetCurDiskDirectory( curDir.c_str() );
			szFullPath.assign( szFullPath.begin() + pos + 1, szFullPath.end() );
		}
	}
	// create entire path dir by dir
	string szDir;
	for ( NStr::CStringIterator<char> it(szFullPath, '\\'); !it.IsEnd(); it.Next() )
	{
		it.Get( &szDir );
		if ( !szDir.empty() ) 
		{
			CreateDiskDirectory( szDir.c_str(), 0 );
#if defined( NV_WIN_PLATFORM )
			SetCurDiskDirectory( (szDir + "\\").c_str() );
#elif defined( NV_LINUX_PLATFORM )
      SetCurDiskDirectory( szDir.c_str() );
#endif
		}
		else
			break;
	}
	// restore old current directory
  SetCurDiskDirectory( buffer );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ************************************************************************************************************************ //
// **
// ** 
// **
// **
// **
// ************************************************************************************************************************ //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CFilePath::MakeHashKey() const
{
	unsigned int uHashKey = 0; 
	for ( string::const_iterator it = this->begin(); it != this->end(); ++it )
		uHashKey = 5*uHashKey + ConvertChar( *it );
	return uHashKey;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CFilePath::operator&( IBinSaver &saver )
{
	saver.Add( 1, (string*)this );
	return 0;
}

void SetModuleCurrentDir()
{
    TCHAR szFileName[MAX_PATH];
    GetModuleFileName( NULL, szFileName, MAX_PATH );

    std::string path(szFileName);
    std::string::size_type n = path.rfind(NFile::FILE_SEPARATOR);
    std::string szDirName = path.substr(0, n);

    SetCurrentDirectory(szDirName.c_str());
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void InitBaseDir(wchar_t const *rootDir)
{
   if(!rootDir)
  {
	  const int dwCurrentDirSize = GetCurDiskDirectory( NULL, 0 );
	  char *szBuffer = new char[dwCurrentDirSize + 1];
	  GetCurDiskDirectory( szBuffer, dwCurrentDirSize + 1 );
	  const int dwFullPathSize = GetDiskFullPathName( szBuffer, 0, NULL, NULL );
	  char *szBuffer2 = new char[dwFullPathSize + 1];
    memset( szBuffer2, 0, dwFullPathSize + 1 );
	  GetDiskFullPathName( szBuffer, dwFullPathSize + 1, szBuffer2, NULL );

	  int nLastNonSeparator = dwFullPathSize;
	  if ( IsFolderSeparator( szBuffer2[nLastNonSeparator] ) )
		  --nLastNonSeparator;

	  for( int i = nLastNonSeparator; i >= 0; --i )
	  {
		  if ( IsFolderSeparator( szBuffer2[i] ) )
		  {
			  szBuffer2[i] = 0;
			  break;
		  }
	  }

	  szBaseDir = szBuffer2;

	  delete[] szBuffer2;
	  delete[] szBuffer;
  }
  else
  {
    //HACK: remove when FS will be with Unicode support
    szBaseDir = NStr::ToMBCS(wstring(rootDir));
  }

	//FIX: add / in the end
 	if (szBaseDir[szBaseDir.length() - 1] != NFile::FILE_SEPARATOR)
	{
		szBaseDir += NFile::FILE_SEPARATOR;
	}

	NFile::NormalizePath( &szBaseDir );

  szBinDir = szBaseDir + "Bin" + NFile::FILE_SEPARATOR;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const string &GetBaseDir()
{
	return szBaseDir;
}

const string &GetBinDir()
{
	return szBinDir;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
char ConvertChar_ToUpperAndSlash( char chr )
{
	const char temp = chr - '\\';
	const char mask = (temp >> 7) | ((-temp) >> 7);
	const char chr1 = (chr & mask) | ('/' & (~mask));
	return chr1 - ( ('A' - 'a') & ( (('A' - chr1 - 1) & (chr1 - 'Z' - 1)) >> 7 ) );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
