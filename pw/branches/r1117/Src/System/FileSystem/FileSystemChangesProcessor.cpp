#include "stdafx.h"
#include "FileSystemChangesProcessor.h"
#include "FileSystem.h"
#include "FilePath.h"



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FileSystemChangesProcessor::FileSystemChangesProcessor()
{
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FileSystemChangesProcessor::~FileSystemChangesProcessor()
{
  for( TFunctorsMap::iterator itMap = functorsByExt.begin(); itMap != functorsByExt.end(); ++itMap )
  {
    list<IFileWatchFunctor*>& functors = itMap->second;

    for ( list<IFileWatchFunctor*>::iterator it = functors.begin(), itEnd = functors.end(); it != itEnd; ++it )
      delete *it;

    functors.clear();
  }
  for( TFunctorsMap::iterator itMap = functorsByName.begin(); itMap != functorsByName.end(); ++itMap )
  {
    list<IFileWatchFunctor*>& functors = itMap->second;

    for ( list<IFileWatchFunctor*>::iterator it = functors.begin(), itEnd = functors.end(); it != itEnd; ++it )
      delete *it;

    functors.clear();
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FileSystemChangesProcessor::SetFileWatcher( IFileWatcher* _fileWatcher )
{
  fileWatcher = _fileWatcher;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FileSystemChangesProcessor::ProcessFileWatchers()
{
  if ( !fileWatcher )
    return;

  IFileWatcher::TChangedFileList changedFiles;
  if ( !fileWatcher->SomethingChanged( &changedFiles ) )
    return;

  for( IFileWatcher::TChangedFileList::iterator it = changedFiles.begin(); it != changedFiles.end(); ++it )
  {
    string& fileName = *it;
    string fileExt = NFile::GetFileExt( fileName );

    {
      TFunctorsMap::iterator itFunctor = functorsByExt.find( fileExt );
      if ( itFunctor != functorsByExt.end() )
        CallFunctors( itFunctor, fileName );
    }
    {
      TFunctorsMap::iterator itFunctor = functorsByName.find( fileName );
      if ( itFunctor != functorsByName.end() )
        CallFunctors( itFunctor, fileName );
    }
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool FileSystemChangesProcessor::RegisterFileWatchByExtension( const string& fileExt, IFileWatchFunctor* pFunctor )
{
  list<IFileWatchFunctor*>& functors = functorsByExt[ fileExt ];

  for ( list<IFileWatchFunctor*>::iterator it = functors.begin(), itEnd = functors.end(); it != itEnd; ++it )
  {
    NI_VERIFY( !pFunctor->Equals( *it ), NI_STRFMT( "Duplicate functor for file extension %s", fileExt.c_str() ), delete pFunctor; return false );
  }

  functors.push_back( pFunctor );
  return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool FileSystemChangesProcessor::UnregisterFileWatchByExtension( const string& fileExt, IFileWatchFunctor* pFunctor )
{
  list<IFileWatchFunctor*>& functors = functorsByExt[ fileExt ];

  for ( list<IFileWatchFunctor*>::iterator it = functors.begin(), itEnd = functors.end(); it != itEnd; ++it )
  {
    if ( pFunctor->Equals( *it ) )
    {
      delete *it;
      functors.erase( it );
      return true;
    }
  }
  NI_ALWAYS_ASSERT( NI_STRFMT( "Unregistered functor for file extension %s", fileExt.c_str() ) );
  return false;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool FileSystemChangesProcessor::RegisterFileWatchByName( const string& fileName, IFileWatchFunctor* pFunctor )
{
  list<IFileWatchFunctor*>& functors = functorsByName[ fileName ];

  for ( list<IFileWatchFunctor*>::iterator it = functors.begin(), itEnd = functors.end(); it != itEnd; ++it )
  {
    NI_VERIFY( !pFunctor->Equals( *it ), NI_STRFMT( "Duplicate functor for file name %s", fileName.c_str() ), return false );
  }

  functors.push_back( pFunctor );
  return true;

}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool FileSystemChangesProcessor::UnregisterFileWatchByName( const string& fileName, IFileWatchFunctor* pFunctor )
{
  list<IFileWatchFunctor*>& functors = functorsByName[ fileName ];

  for ( list<IFileWatchFunctor*>::iterator it = functors.begin(), itEnd = functors.end(); it != itEnd; ++it )
  {
    if ( pFunctor->Equals( *it ) )
    {
      delete *it;
      functors.erase( it );
      return true;
    }
  }
  NI_ALWAYS_ASSERT( NI_STRFMT( "Unregistered functor for file name %s", fileName.c_str() ) );
  return false;

}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FileSystemChangesProcessor::CallFunctors( TFunctorsMap::iterator& itFunctor, const string& fileName )
{
  list<IFileWatchFunctor*>& functors = itFunctor->second;
  for ( list<IFileWatchFunctor*>::iterator it = functors.begin(), itEnd = functors.end(); it != itEnd; ++it )
  {
    (*it)->Call( fileName );
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
