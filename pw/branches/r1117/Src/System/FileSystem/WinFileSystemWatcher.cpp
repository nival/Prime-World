#include "stdafx.h"
#include "WinFileSystemWatcher.h"

#include "FilePath.h"
#include "FileUtils.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
WinFileSystemWatcher::WinFileSystemWatcher( const string& _basePath, const string _path )
: basePath( _basePath )
, path( _path )
, pThread( 0 )
, directoryHandle( 0 )
, hasDataFlag( 0 ) 
{
  directoryHandle = CreateFile( NFile::Combine( basePath, path ).c_str(), FILE_LIST_DIRECTORY, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, 0
    , OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OVERLAPPED, 0 );

  if( directoryHandle == INVALID_HANDLE_VALUE )
    return;

  pThread = new threading::ProcessingThread<WinFileSystemWatcher>( *this );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
WinFileSystemWatcher::~WinFileSystemWatcher()
{
  if ( pThread )
  {
    pThread->Stop( true, 1000 );
    pThread->Stop( false );
    delete pThread;
    pThread = 0;
  }
  if ( directoryHandle != 0 )
   CloseHandle( directoryHandle ); 
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool WinFileSystemWatcher::SomethingChanged( IFileWatcher::TChangedFileList* pFileList )
{

  if( hasDataFlag == 0 )
    return false;

  bufferLock.Lock();

  string result;
  hasDataFlag = 0;

  hash_set<string> changedFiles;

  for( vector<char>::const_iterator iter = buffer.begin(), end = buffer.end(); iter!= end; ++iter  )
  {
    result = &*iter;
    iter += result.length();
    result = NFile::Combine( path, result );
    NStr::TrimLeft(  result, "\\" );
    NFile::NormalizePath( &result );

    if ( changedFiles.find( result ) != changedFiles.end() )
      continue;
    else
      changedFiles.insert( result );

    pFileList->push_back( result );
  }
  buffer.clear();

  bufferLock.Unlock();
  return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DWORD WinFileSystemWatcher::Process( volatile bool& isRunning )
{
  const int fileBufferTrack = 1 << 15;
  char fileBuffer[fileBufferTrack];

  OVERLAPPED request;
  request.hEvent = CreateEvent( 0, TRUE, false, 0 );
  bool requestValid = false;
  while( isRunning )
  {
    DWORD cSize = 0;
    
    if ( !requestValid )
    {
      requestValid = true;
      ReadDirectoryChangesW( directoryHandle, fileBuffer, fileBufferTrack, true, FILE_NOTIFY_CHANGE_LAST_WRITE | FILE_NOTIFY_CHANGE_FILE_NAME, &cSize, &request, 0 );
    }


    if ( WaitForSingleObject( request.hEvent, 0 ) == WAIT_TIMEOUT )
    {
      Sleep( 20 );
      continue;
    }

    GetOverlappedResult( directoryHandle, &request, &cSize, FALSE );
    requestValid = false; 

    if ( cSize == 0 )
    {
      Sleep( 20 );
      continue;
    }

    bufferLock.Lock();

    NI_VERIFY( buffer.size() < fileBufferTrack, "Changed files cache overflow. Check all watchers is flushed periodically",  buffer.clear() );

    const char *endFileBufer = ( fileBuffer +  fileBufferTrack );
    char *offset = fileBuffer;

    FILE_NOTIFY_INFORMATION *pFNI = ( FILE_NOTIFY_INFORMATION *)fileBuffer;
    while ( ( (char *)pFNI +  sizeof( FILE_NOTIFY_INFORMATION ) ) < endFileBufer )
    {
      wstring wFileName( pFNI->FileName, pFNI->FileNameLength / 2 );
      string ansiFileName = NStr::ToMBCS( wFileName );

      const vector<char>::iterator end = buffer.end();
      buffer.insert( end, ansiFileName.begin(), ansiFileName.end() );
      buffer.push_back( static_cast< char >( 0 ) );

      if ( pFNI->NextEntryOffset)
      {
        offset += pFNI->NextEntryOffset;
        pFNI = (FILE_NOTIFY_INFORMATION *)( offset );
      }
      else
      {
        break;
      }
    }

    hasDataFlag = 1;
    bufferLock.Unlock();
  }


  return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
