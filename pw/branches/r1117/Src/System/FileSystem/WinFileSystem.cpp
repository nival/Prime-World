#include "stdafx.h"

#include "WinFileSystem.h"
#include "FilePath.h"
#include "FileUtils.h"

#if defined( NV_WIN_PLATFORM )
  #include "WinFileSystemWatcher.h"
#endif

#include "FileStream_stdlib.h"
#include "System/InlineProfiler.h"

#include <System/ported/cwfn.h>


static bool s_map_files = true;
REGISTER_DEV_VAR( "fs_map_files", s_map_files, STORAGE_NONE );


#if defined( NV_WIN_PLATFORM )

static SWin32Time GetLastWriteTime( const string& fileName )
{
	FILETIME ftWrite;
	SWin32Time time = SWin32Time();
	HANDLE hFile = CreateFile( fileName.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);

	if ( hFile == INVALID_HANDLE_VALUE )
		return time;

	// Retrieve the file time for the file
	if ( GetFileTime( hFile, 0, 0, &ftWrite ) )
	{
		// transforms FILETIME to Win32 date/time ( SWin32Time )
		time = FILETIMEToWin32DateTime( ftWrite );
	}

	CloseHandle( hFile );
	return time;
}



static string FixFolderPath( const string& path )
{
	string result;
	bool lastSlash = false;

  string::const_iterator it = path.begin();

  if ( path.size() >= 2 )
  {
    // preserve double-backslash for UNC path names
    if (path[0] == '\\' && path[1] == '\\')
    {
      result += "\\\\";
      it++; it++;
      lastSlash = true;
    }
  }

	for( ; it != path.end(); ++it )
	{
    if ( NFile::IsFolderSeparator( *it ) )
		{
			if ( !lastSlash )
				result += '/';
			lastSlash = true;
		}
		else
		{
			result += *it;
			lastSlash = false;
		}
	}

	if ( !lastSlash )
		result += '/';

	return result;
}



IFileWatcher * WinFileSystem::CreateFileWatcher( const string& path )
{
	NI_PROFILE_FUNCTION

	return new WinFileSystemWatcher( fileSystemRoot, path );
}



#elif defined( NV_LINUX_PLATFORM )

static SWin32Time GetLastWriteTime( const string & fileName )
{
  SWin32Time time = SWin32Time();

  struct stat file_info;
  if ( stat( fileName.c_str(), &file_info ) )
    return time;

  return DOSToWin32DateTime( file_info.st_mtime );
}

static string FixFolderPath( const string &path )
{
  string result;
  bool lastSlash = false;

  string::const_iterator it = path.begin();

  // preserve double-backslash for UNC path names
  if ( path.size() >= 2 && '\\' == path[ 0 ] && '\\'== path[ 1 ] )
  {
    result += "\\\\";
    it += 2;
    lastSlash = true;
  }

  for ( ; path.end() != it; ++it )
  {
    if ( NFile::IsFolderSeparator( *it ) )
    {
      if ( !lastSlash )
        result += '/';

      lastSlash = true;
    }
    else
    {
      result += *it;
      lastSlash = false;
    }
  }

  if ( !lastSlash )
    result += '/';

  return result;
}

IFileWatcher * WinFileSystem::CreateFileWatcher( const string& path )
{
  return NULL;
}

#endif



WinFileSystem::WinFileSystem( const string &_root, const bool _writable )
{
	fileSystemRoot = FixFolderPath( _root );
	writable = _writable;

	if ( writable && !NFile::DoesFolderExist( _root ) )
		NFile::CreatePath( _root );
}



void WinFileSystem::GetDirectories( vector<string> *pDirectories, const string &root )
{
  NI_PROFILE_FUNCTION

  string fullPath = NFile::Combine( fileSystemRoot, root );

  if ( !NFile::DoesFolderExist( fullPath ) )
    return;

  pDirectories->clear();

  for ( NFile::CFileIterator it( ( fullPath + "*.*" ) ); !it.IsEnd(); ++it )
  {
    if ( !it.IsDirectory() || it.IsDots() )
      continue;

    string dirName = it.GetFileName();
    if ( !_stricmp( dirName.c_str(), ".svn" ) )
      continue;
    pDirectories->push_back( it.GetFileName() );
  }
}



void WinFileSystem::GetFiles( vector<string> *pFiles, const string &root, const string &mask, bool recursive, int param /*= 0*/ )
{
  NI_PROFILE_FUNCTION

  pFiles->clear();

  GetFilesInternal( pFiles, root, "", mask, recursive );
}



bool WinFileSystem::GetFileInfo( SFileInfo *info, const string &fileName )
{
  NI_PROFILE_FUNCTION;

  const string fullPath = NFile::Combine( fileSystemRoot, fileName );

	if ( !NFile::DoesFileExist( fullPath ) )
		return false;

	if ( info )
	{
		info->pOwner = this;
		info->time = GetLastWriteTime( fullPath );
	}

	return true;
}



Stream* WinFileSystem::OpenFile( const string &fileName, EFileAccess access, EFileOpen options )
{
  NI_PROFILE_FUNCTION

	if ( access == FILEACCESS_READ )
		NI_VERIFY( options != FILEOPEN_CREATE_NEW, "Cant create readonle file for writing", return 0; )
	else
		NI_VERIFY( writable, "Cant open readonle file for writing", return 0; )

  Stream * stream = 0;

  if ( s_map_files )
    stream = new FileStream( NFile::Combine( fileSystemRoot, fileName ), access, options );
  else
    stream = new StdLibFileStream( NFile::Combine( fileSystemRoot, fileName ), access, options );

	if ( stream == 0 || !stream->IsOk() )
	{
		delete stream;
		return 0;
	}
	return stream;
}



void WinFileSystem::GetFilesInternal( vector<string> *pFiles, const string &root, const string & relativeFolder, const string & mask, bool recursive )
{
  string fullPath = NFile::Combine( fileSystemRoot, root );

	if ( !NFile::DoesFolderExist( fullPath ) )
		return;

  for ( NFile::CFileIterator it( NFile::Combine( fullPath, mask ) ); !it.IsEnd(); ++it )
	{
		if ( it.IsDirectory() )
      continue;

    pFiles->push_back( NFile::Combine( relativeFolder, it.GetFileName() ) );
	}

  if ( !recursive )
    return;

  for ( NFile::CFileIterator it( NFile::Combine( fullPath, "*.*" ) ); !it.IsEnd(); ++it )
  {
    if ( !it.IsDirectory() || it.IsDots() )
      continue;
    string dirName = it.GetFileName();
    if ( !_stricmp( dirName.c_str(), ".svn" ) )
      continue;

    GetFilesInternal( pFiles, NFile::Combine( root, dirName ), NFile::Combine( relativeFolder, dirName ), mask, recursive );
  }
}
