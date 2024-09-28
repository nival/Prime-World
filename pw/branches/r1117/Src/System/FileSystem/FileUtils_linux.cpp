#include "stdafx.h"
#include "FilePath.h"
#include "FileUtils.h"
#include "Asserts.h"
#include <System/config.h>

#if defined( NV_LINUX_PLATFORM )

#include <vector>
#include <cstring>
#include <limits.h>

namespace NFile {

CFileIterator::CFileIterator( const CFileIterator::filename_type & mask ) :
    mask_( mask ), path_(), ind_( 0 )
{
  path_ = mask_;
  size_t pos = path_.rfind( '\\' );
  if ( pos == CFileIterator::filename_type::npos ) { path_.clear(); }
  else
  {
	  mask_ = path_.substr( pos + 1 );
	  path_ = path_.substr( 0, pos );
  }

  data_.gl_pathc = 0;
  data_.gl_pathv = NULL;
  data_.gl_offs = 1;
  // HACK: пока так, потом надо исправить на более высоком уровне
  CFileIterator::filename_type msk( mask );
  std::replace( msk.begin(), msk.end(), '\\', '/' );
  const int globRes = ::glob( msk.c_str(), 0, NULL, &data_ );
  if ( globRes == 0 )
  {
    ::memset( &stat_, 0, sizeof( stat_ ) );
    NI_ASSERT( data_.gl_pathc > 0, "glob() returned 0 files" );
    NI_ASSERT( data_.gl_pathv != 0, "glob() returned NULL instead of files" );
    NI_VERIFY_NO_RET( ( ::stat( data_.gl_pathv[ 0 ], &stat_ ) == 0 ), "stat() failed" );
  }
  else
  {
    // На всякий случай - убедиться, что IsValid() вернет false
    data_.gl_pathc = 0;
  }
}

bool CFileIterator::IsValid() const
{
  return ( ind_ < data_.gl_pathc );
}

const SWin32Time CFileIterator::GetLastWriteTime() const
{
  return SWin32Time( stat_.st_mtime );
}

void CFileIterator::Close()
{
  if ( IsValid() )
  {
    ::globfree( &data_ );
    memset( &data_, 0, sizeof( data_ ) );
    memset( &stat_, 0, sizeof( stat_ ) );
  }
}

const CFileIterator & CFileIterator::Next()
{
  // Если это итератор на end - просто ничего не делать
  if ( IsValid() )
  {
    ++ind_;
    if ( !IsValid() ) { Close(); }
    else
    {
      NI_VERIFY_NO_RET( ( ::stat( data_.gl_pathv[ ind_ ], &stat_ ) == 0 ), "stat() failed" );
    }
  }
  return *this;
}

bool CFileIterator::IsReadOnly() const 
{
  if ( !IsValid() ) { return false; }
  if ( stat_.st_uid == geteuid() )
  {
    return ( ( stat_.st_mode & S_IWUSR ) == 0 );
  }
  else if ( stat_.st_gid == getgid() )
  {
    return ( ( stat_.st_mode & S_IWGRP ) == 0 );
  }
  return ( ( stat_.st_mode & S_IWOTH ) == 0 );
}


	int GetCurDiskDirectory( char *buffer, int bufSize )
	{
		int len = 0;

		if ( buffer )
        {
          if ( getcwd( buffer, bufSize ) )
          {
            len =  strlen( buffer );
          }
          else
          {
            buffer[ 0 ] = 0;
          }
		}
        else
        {
		  std::vector< char > buf( PATH_MAX );
		  getcwd( &buf[0], buf.size() );
		  len = strlen( &buf[0] );
		}

		return len;
	}

	void SetCurDiskDirectory( const char *dir )
	{
		assert( NULL != dir );
		chdir( dir );
	}

	bool CreateDiskDirectory( const char *dirName, int dirFlags )
	{
		assert( NULL != dirName );
		return mkdir( dirName, 0777 ) == 0;
	}

	int GetDiskFullPathName( const char *fullName, const int outBufLen, char *outBufDrivePath, char **shortFileName )
	{
		assert( NULL != fullName );
		//assert( NULL != outBufDrivePath );

		std::vector< char > full_path( PATH_MAX );
		if ( realpath( fullName, &( full_path[ 0 ] ) ) ) {

      if ( outBufLen < full_path.size() )
      {
        return full_path.size();
      }

			std::strncpy( outBufDrivePath, &full_path[ 0 ], std::min< size_t >( outBufLen - 1, full_path.size() ) );
			size_t path_length = std::strlen( outBufDrivePath );

			if ( shortFileName ) {

				char *file_name = &outBufDrivePath[ path_length ];
				while ( file_name > outBufDrivePath ) {

					if ( '/' == *--file_name || '\\' == *file_name ) {

						++file_name;
						break;

					}

				}

				*shortFileName = file_name;

			}

			return path_length;

		}

		return 0;
	}

	bool CreateFullPath( char const * path )
	{
		assert( NULL != path );

		char current_path[ PATH_MAX ];
		char *current_position = &current_path[ 0 ];

		if ( '/' == *path ) {

			*current_position++ = '/';
			++path;

		} else if ( '~' == *path ) {

			*current_position++ = '~';

			if ( '/' == *++path ) {

				*current_position++ = '/';
				++path;

			} else
				return false;

		}

		while ( *path )
			if ( '/' == *path ) {

				*current_position = '\0';
				if ( DoesFolderExist( current_path ) == false && mkdir( current_path, 0777 ) )
					return false;

				*current_position++ = '/';
				++path;

			} else
				*current_position++ = *path++;

		return true;
	}

	bool DoesFileExist( const string &szFileName )
	{
		struct stat fs;
		return stat( szFileName.c_str(), &fs ) == 0 && !S_ISDIR( fs.st_mode );
	}

	bool DoesFolderExist( const string &szFolderName )
	{
		struct stat fs;
		return stat( szFolderName.c_str(), &fs ) == 0 && S_ISDIR( fs.st_mode );
	}

	void DeleteDirectory( const string &szDir )
	{
		if ( DoesFolderExist( szDir ) )
			remove( szDir.c_str() );
	}

static int OpenFileWithDirInt( const char* fileName, int createMode )
{
  string fullFileName = GetFullName( fileName );
  NFile::CFilePath filePath = GetFilePath( fullFileName );
  if ( !DoesFolderExist( filePath ) )
  {
    CreatePath( filePath );
    if ( !DoesFolderExist( filePath ) )
      return -1;
  }
  return open( fullFileName.c_str(), createMode );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CreateFileWithDir( const char* fileName )
{
  // return OpenFileWithDirInt( fileName, CREATE_ALWAYS );
  return OpenFileWithDirInt( fileName, O_CREAT | O_WRONLY );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int OpenFileWithDir( const char* fileName )
{
  // return OpenFileWithDirInt( fileName, OPEN_ALWAYS );
  return OpenFileWithDirInt( fileName, O_CREAT | O_RDWR );
}


} // namespace

#endif

