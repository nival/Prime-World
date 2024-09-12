#include "stdafx.h"

#include "shlwapi.h"
#include "FileUtils.h"
#include "FilePath.h"
#include <Shellapi.h>

namespace NFile
{


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ************************************************************************************************************************ //
// **
// ** class CFileIterator functions
// **
// **
// **
// ************************************************************************************************************************ //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


CFileIterator::CFileIterator( const CFileIterator::filename_type & mask ) :
    mask_( mask ), path_(), find_( INVALID_HANDLE_VALUE )
{
  FirstFile();
}

void CFileIterator::Close()
{
  if ( IsValid() ) 
  {
    NI_VERIFY_NO_RET( ::FindClose( find_ ) != FALSE, "FindClose() failed" );
    find_ = INVALID_HANDLE_VALUE;
    ::ZeroMemory( &findinfo_, sizeof( findinfo_ ) );
  }
}

const CFileIterator & CFileIterator::Next()
{
  // ≈сли это итератор на end - просто ничего не делать
  if ( IsValid() )
  {
    if ( ::FindNextFileA( find_, &findinfo_ ) == FALSE )
    {
	    Close();
    }
  }
  return *this;
}

bool CFileIterator::IsValid() const
{
  return ( find_ != INVALID_HANDLE_VALUE );
}

const SWin32Time CFileIterator::GetLastWriteTime() const
{
  return FILETIMEToWin32DateTime( findinfo_.ftLastWriteTime );
}

void CFileIterator::FirstFile()
{
  // –азделить маску на базовый путь и саму маску
  // ѕример: Data\*.*
  //   Data\ - это путь
  //   *.* - это маска
  CFileIterator::filename_type origMask = mask_;
  path_ = mask_;
  std::replace( path_.begin(), path_.end(), '/', '\\' );
  size_t pos = path_.rfind( '\\' );
  if ( pos == CFileIterator::filename_type::npos ) { path_.clear(); }
  else
  {
	  mask_ = path_.substr( pos + 1 );
	  path_ = path_.substr( 0, pos );
  }

  if ( ( !path_.empty() ) && ( path_[ path_.length() - 1 ] != '\\' ) ) { path_ += "\\"; }

  // create absolute path from the relative one
  NFile::GetFullName( &path_, path_ );

  // «ачем нужно делать это до и после GetFullName - разобратьс€
  if ( ( !path_.empty() ) && ( path_[ path_.length() - 1 ] != '\\' ) ) { path_ += "\\"; }

  ::ZeroMemory( &findinfo_, sizeof( findinfo_ ) );
  find_ = ::FindFirstFileA( origMask.c_str(), &findinfo_ );
}



int   GetCurDiskDirectory(char *buffer, int bufSize)
{
  int len;
  if (buffer)
    len = GetCurrentDirectoryA( bufSize, buffer );
  else
  {
    len = GetCurrentDirectoryA( 0, NULL );
  }
  return len;
}

void  SetCurDiskDirectory(const char *dir)
{
  SetCurrentDirectoryA( dir );
}

bool  CreateDiskDirectory(const char *dirName, int dirFlags)
{
  bool ret;
  
  ret = CreateDirectoryA(dirName, NULL);
  return ret;
}

int   GetDiskFullPathName(const char *fullName, const int outBufLen, char *outBufDrivePath, char **shortFileName)
{
  int bufLen;
  
  bufLen = GetFullPathNameA( fullName, outBufLen, outBufDrivePath, shortFileName);
  return bufLen;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool DoesFileExist( const string &szFileName )
{
  //return _access( szFileName.c_str(), 0 ) != -1;
  if(TRUE == PathFileExistsA(szFileName.c_str()))
    return true;
  else
    return false;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool DoesFolderExist( const string &szFolderName )
{
  //return _access( szFileName.c_str(), 0 ) != -1;
  if(TRUE == PathFileExistsA(szFolderName.c_str()))
    return true;
  else
    return false;
}

bool EraseFile( const string &szFileName )
{
  //return _access( szFileName.c_str(), 0 ) != -1;
  if( TRUE == PathFileExistsA( szFileName.c_str() ) )
  {
    return DeleteFileA( szFileName.c_str() );
  }
  return false;
}


void ExecuteFile( const string& szFileName )
{
  ShellExecute(NULL, "open", szFileName.c_str(), NULL, NULL, SW_SHOWNORMAL);
}

static int OpenFileWithDirInt( const char* fileName, int createMode )
{
  string fullFileName = GetFullName( fileName );
  NFile::CFilePath filePath = GetFilePath( fullFileName );
  if ( !DoesFolderExist( filePath ) )
  {
    CreatePath( filePath );
    if ( !DoesFolderExist( filePath ) )
      return (int)INVALID_HANDLE_VALUE;
  }

  return (int)CreateFileA( fullFileName.c_str(), FILE_GENERIC_WRITE, FILE_SHARE_READ, 0, createMode, FILE_ATTRIBUTE_NORMAL, 0 );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CreateFileWithDir( const char* fileName )
{
  return OpenFileWithDirInt( fileName, CREATE_ALWAYS );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int OpenFileWithDir( const char* fileName )
{
  return OpenFileWithDirInt( fileName, OPEN_ALWAYS );
}



} // namespace NFile


