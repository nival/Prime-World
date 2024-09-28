#include "stdafx.h"
#include "CombinerFileSystem.h"
#include "PileFileSystem.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "FilePath.h"
#include "FileUtils.h"
#include <System/InlineProfiler.h>
#include <System/ported/cwfn.h>


namespace
{

static NDebug::DebugVar<int> openedFileCount( "Opened File Count", "FileSystem" );

static bool s_detect_multiopen = false;
REGISTER_DEV_VAR( "fs_detect_multiopen", s_detect_multiopen, STORAGE_NONE );

}

namespace detail {

	struct RD_SCompare {

		bool operator () ( const string & left, const string & right )
		{
			return _stricmp( left.c_str(), right.c_str() ) < 0;
		}

	};

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void RemoveDuplicates( vector<string> & filenames )
{
  if ( filenames.empty() )
    return;

  detail::RD_SCompare compare;

  sort( filenames.begin(), filenames.end(), compare );

	vector<string>::iterator it = filenames.begin();
	vector<string>::iterator prev = filenames.begin();

  for( ++it; it != filenames.end(); )
	{
		if ( !_stricmp( prev->c_str(), it->c_str() ) )
			it = filenames.erase( it );
		else
		{
			prev = it;
			++it;
		}
	}
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void PrepareNamesList( vector<string> & filenames )
{
  for ( int i = 0; i < filenames.size(); ++i )
    NStr::ReplaceAllChars( &filenames[i], '\\', '/' );

	RemoveDuplicates( filenames );
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CombinerFileSystem::CombinerFileSystem()
: changesProcessor()
{
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CombinerFileSystem::EnableChangesProcessor( bool enable )
{
  if ( !enable )
  {
    pFileWatcher = 0;
    changesProcessor.SetFileWatcher( pFileWatcher );
  }
  else
  {
    if ( !pFileWatcher )
    {
      pFileWatcher = new CombinerFileSystemWatcher( "" );
      changesProcessor.SetFileWatcher( pFileWatcher );

      for( TFileSystems::const_iterator it = fileSystems.begin(); it != fileSystems.end(); ++it )
      {
        pFileWatcher->AddWatcher( (*it)->CreateFileWatcher( "" ) );
      }
    }
  }
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CombinerFileSystem::RegisterFileSystem( IFileSystem *pFileSystem, IFileReadCallback* fileReadCallback )
{
	for( TFileSystems::const_iterator it = fileSystems.begin(); it != fileSystems.end(); ++it )
	{
		if ( *it == pFileSystem )
			return;
	}

  pFileSystem->SetFileReadCallback(fileReadCallback);
	fileSystems.push_back( pFileSystem );

  if ( pFileWatcher )
    pFileWatcher->AddWatcher( pFileSystem->CreateFileWatcher( "" ) );

}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CombinerFileSystem::UnregisterFileSystem( IFileSystem *pFileSystem )
{		
	if ( pWriteFileSystem == pFileSystem )
		pWriteFileSystem = 0;
	for( TFileSystems::iterator it = fileSystems.begin(); it != fileSystems.end();  )
	{
		if ( *it == pFileSystem )
		{
			it = fileSystems.erase( it );
		}
		else
		{
			++it;
		}
	}

  if ( pFileWatcher )
  {
    // TODO
    //pFileWatcher->AddWatcher( pFileSystem->CreateFileWatcher( "" ); )
  }
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CombinerFileSystem::ClearFileSystems()
{
	pWriteFileSystem = 0;
	fileSystems.clear();
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CombinerFileSystem::SetWriteFileSystem( IFileSystem* pFileSystem )
{
	for( TFileSystems::const_iterator it = fileSystems.begin(); it != fileSystems.end(); ++it )
	{
		if ( (*it) == pFileSystem )
		{
			pWriteFileSystem = pFileSystem;
			return true;
		}
	}

	return false;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CombinerFileSystem::GetDirectories( vector<string> *pDirectories, const string &root )
{
  NI_PROFILE_FUNCTION

  NI_ASSERT( pDirectories, "" );

  NHPTimer::FTime startTime = NHPTimer::GetScalarTime();

	for( TFileSystems::const_iterator it = fileSystems.begin(); it != fileSystems.end(); ++it )
	{
		vector<string> thisDirs;
		(*it)->GetDirectories( &thisDirs, root );
    if ( pDirectories )
		  pDirectories->insert( pDirectories->end(), thisDirs.begin(), thisDirs.end() );
	}

  PrepareNamesList( *pDirectories );

  NHPTimer::FTime finishTime = NHPTimer::GetScalarTime();
  for ( TDebugMonitors::iterator it = debugMonitors.begin(); it != debugMonitors.end(); ++it )
    (*it)->OnGetDirectories( root, finishTime - startTime );
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CombinerFileSystem::GetFiles( vector<string> *pFiles, const string &root, const string &mask, bool recursive, int param /*= 0*/)
{
  NI_PROFILE_FUNCTION

  NI_ASSERT( pFiles, "" );

  NHPTimer::FTime startTime = NHPTimer::GetScalarTime();

	for( TFileSystems::const_iterator it = fileSystems.begin(); it != fileSystems.end(); ++it )
	{
    if ( param == CFS_GETFILES_PILEONLY && strcmp( (*it)->GetObjectTypeName(), fileSystem::PileFileSystem::GetTypeName() ) != 0 )
      continue;

		vector<string> thisFiles;
		(*it)->GetFiles( &thisFiles, root, mask, recursive );
		pFiles->insert( pFiles->end(), thisFiles.begin(), thisFiles.end() );
	}

  PrepareNamesList( *pFiles );

  NHPTimer::FTime finishTime = NHPTimer::GetScalarTime();
  for ( TDebugMonitors::iterator it = debugMonitors.begin(); it != debugMonitors.end(); ++it )
    (*it)->OnGetFiles( root, finishTime - startTime );
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CombinerFileSystem::GetFileInfo( SFileInfo *pInfo, const string &fileName )
{
  NI_PROFILE_FUNCTION

  NHPTimer::FTime startTime = NHPTimer::GetScalarTime();

	if ( pInfo )
		pInfo->Clear();

	for( TFileSystems::const_iterator it = fileSystems.begin(); it != fileSystems.end(); ++it )
	{
		SFileInfo thisFileInfo;
		if ( (*it)->GetFileInfo( &thisFileInfo, fileName ) )
		{
			if ( pInfo )
				*pInfo = thisFileInfo;
      return true;
		}
	}

  NHPTimer::FTime finishTime = NHPTimer::GetScalarTime();
  for ( TDebugMonitors::iterator it = debugMonitors.begin(); it != debugMonitors.end(); ++it )
    (*it)->OnGetFileInfo( fileName, finishTime - startTime );

	return pInfo && pInfo->pOwner;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Stream * CombinerFileSystem::OpenFile( const string &fileName, EFileAccess access, EFileOpen options )
{
  NI_PROFILE_FUNCTION

  NHPTimer::FTime startTime = NHPTimer::GetScalarTime();

  Stream * stream = 0;

	if ( access == FILEACCESS_READ_WRITE || access == FILEACCESS_WRITE || options == FILEOPEN_CREATE_NEW )
    stream = pWriteFileSystem->OpenFile( fileName, access, options );
  else
  {
    for( TFileSystems::const_iterator it = fileSystems.begin(); it != fileSystems.end(); ++it )
    {
      Stream * s = (*it)->OpenFile( fileName, access, options );
      if ( s )
      {
        stream = s;
        break;
      }
    }
  }

  if ( stream )
  {
    NHPTimer::FTime finishTime = NHPTimer::GetScalarTime();
    for ( TDebugMonitors::iterator it = debugMonitors.begin(); it != debugMonitors.end(); ++it )
      (*it)->OnOpenFile( fileName, finishTime - startTime, stream ? stream->GetSize() : 0 );

    openedFileCount.AddValue( 1 );
  }

  if ( s_detect_multiopen )
  {
    if ( stream )
    {
      string key = fileName;
      NStr::ReplaceAllChars( &key, '\\', '/' );
      NStr::ToLower( &key );

      TOpenedStreams::iterator it = openedStreams.find( key );
      if ( it != openedStreams.end() )
        NI_DATA_ASSERT( !IsValid( it->second ), NI_STRFMT( "File '%s' opened twice!", fileName.c_str() ) );
      openedStreams[key] = stream;
    }
  }
  else
    openedStreams.clear();

	return stream;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
IFileWatcher* CombinerFileSystem::CreateFileWatcher( const string& path )
{
  CombinerFileSystemWatcher* watcher = new CombinerFileSystemWatcher( path );

  for( TFileSystems::const_iterator it = fileSystems.begin(); it != fileSystems.end(); ++it )
  {
    IFileWatcher* systemWatcher = (*it)->CreateFileWatcher( path );
    if ( systemWatcher )
      watcher->AddWatcher( systemWatcher );
  }

  return watcher;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CombinerFileSystem::GetOpenedFileCount()
{
  return openedFileCount.GetValue();
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CombinerFileSystemWatcher::AddWatcher( IFileWatcher* watcher )
{
  if ( !watcher )
    return;
  watchers.push_back( watcher );
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CombinerFileSystemWatcher::RemoveWatcher( IFileWatcher* watcher )
{
  if ( !watcher )
    return;
  list<CObj<IFileWatcher> >::iterator it = find( watchers.begin(), watchers.end(), watcher );
  if( it != watchers.end() )
    watchers.erase( it );
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CombinerFileSystemWatcher::SomethingChanged( IFileWatcher::TChangedFileList* pFileList )
{
  bool res = false;
  for( list<CObj<IFileWatcher> >::const_iterator it = watchers.begin(), itEnd = watchers.end(); it != itEnd; ++it )
  {
    if ( (*it)->SomethingChanged( pFileList ) )
      res = true;
  }
  return res;
}
