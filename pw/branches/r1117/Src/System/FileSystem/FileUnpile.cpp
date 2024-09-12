#include "systemStdAfx.h"
#include "FilePileLoader.h"
#include "System/DebugTraceDumper.h"
#include "System/ServerStdOutDumper.h"
#include "System/CmdLineLite.h"
#include "System/FileSystem/FileUtils.h"
#include "System/FileSystem/FilePath.h"
#include "SystemLog.h"
#include <errno.h>

struct CacheItem
{
  string        filename;
  CObj<Stream>  data;

  CacheItem( const string & nm, Stream * dt ) : filename( nm ), data( dt ) {}
  CacheItem() {}
};


struct MyExcep
{
  MyExcep( const char * _msg ) : msg( _msg ) {}

  string msg;
};


void WriteItem( const char * destDir, CacheItem & item )
{
  string fullfname = destDir;
  NFile::AppendSlash( &fullfname, '/' );
  fullfname += item.filename;

  DebugTrace( "Writing file '%s'...", fullfname );

#if defined( NV_WIN_PLATFORM )
  HANDLE handle = (HANDLE)NFile::CreateFileWithDir( fullfname.c_str() );
  if ( handle == INVALID_HANDLE_VALUE )
    throw MyExcep( NI_STRFMT( "Could not create file '%s'!", fullfname ) );

  DWORD written = 0;
  if ( !WriteFile( handle, item.data->GetBuffer(), item.data->GetSize(), &written, NULL ) )
    throw MyExcep( NI_STRFMT( "Could not write to file '%s'!", fullfname ) );

  if ( !CloseHandle( handle ) )
    throw MyExcep( NI_STRFMT( "Could write-close not write to file '%s'!", fullfname ) );
#elif defined( NV_LINUX_PLATFORM )
  // HACK
  int handle = NFile::CreateFileWithDir( fullfname.c_str() );
  if ( handle == -1 )
  {
    throw MyExcep( NI_STRFMT( "Could not create file '%s'!", fullfname ) );
  }
  if ( write( handle, item.data->GetBuffer(), item.data->GetSize() ) == -1 )
  {
    close( handle );
    throw MyExcep( NI_STRFMT( "Could not write to file '%s'!", fullfname ) );
  }
  close( handle );
#endif
}



void FlushCache( const char * destDir, vector<CacheItem> & cache )
{
  DebugTrace( "Flushing cache of %d file(s)...", cache.size() );

  for ( int i = 0; i < cache.size(); ++i )
    WriteItem( destDir, cache[i] );

  cache.clear();
}



void List( fileSystem::FilePileLoader * pile, const vector<fileSystem::FilePileItemInfo> & filesList )
{
  threading::Sleep( 100 ); //dirty hack: let buffered console output to catch up

  printf( "Listing %d files...\n", filesList.size() );

  size_t total = 0;

  for ( int i = 0; i < filesList.size(); ++i ) {
    const fileSystem::FilePileItemInfo & item = filesList[i];

    printf( "%s, %u bytes\n", item.name.c_str(), item.size );

    total += item.size;
  }

  printf( "Total bytes: %u\n", total );
}



void Unpack( fileSystem::FilePileLoader * pile, const vector<fileSystem::FilePileItemInfo> & filesList, const char * destDir, size_t cacheLimit )
{
  MessageTrace( "Unpacking %d files...", filesList.size() );

  size_t total = 0;

  vector<CacheItem> writeCache;
  size_t cacheSize = 0;
  for ( int i = 0; i < filesList.size(); ++i )
  {
    const fileSystem::FilePileItemInfo & item = filesList[i];
    DebugTrace( "Unpacking '%s'...", item.name );

    CObj<Stream> data = pile->ReadFile( item.name );
    if ( !data )
      throw MyExcep( NI_STRFMT( "Could not read '%s'!", item.name ) );

    writeCache.push_back( CacheItem( item.name, data ) );
    cacheSize += (size_t)data->GetSize();
    if ( cacheSize >= cacheLimit ) {
      FlushCache( destDir, writeCache );
      cacheSize = 0;
    }

    total += item.size;
  }

  MessageTrace( "Total bytes: %u", total );

  FlushCache( destDir, writeCache );
}



int main( int argc, char **argv)
{
  CmdLineLite::Instance().Init( argc, argv );

  // HACK
#if defined( NV_WIN_PLATFORM )
  wchar_t szCurrDir[1024] = L"";
  GetCurrentDirectoryW( 1024, szCurrDir );
  NFile::InitBaseDir( szCurrDir );
#elif defined( NV_LINUX_PLATFORM )
  char szCurrDir[512] = "";
  if ( getcwd( szCurrDir, 512 ) )
  {
    DebugTrace( "Working in directory '%s'\n", szCurrDir );
  }
  wstring curDir;
  NStr::ToUnicode( &curDir, string( szCurrDir ) );
  NFile::InitBaseDir( curDir.c_str() );
#endif

  NLogg::CDebugTraceDumper debugTraceDumper( &GetSystemLog() );
  NLogg::CServerStdOutDumper stdOutDumper( &GetSystemLog(), (NLogg::ELevel)max<int>( NLogg::LEVEL_DEBUG, CmdLineLite::Instance().GetIntKey( "-verbose", NLogg::LEVEL_MESSAGE ) ) );

  const char * pileName = CmdLineLite::Instance().GetStringKey( "-pile" );
  if ( !pileName ) {
    printf( 
      "Wrong command line arguments!\n"
      "Usage help:\n"
      "  FileUnpile.exe -pile <pile_file> [-mask <file_mask>] [-dest <output_folder>] [-verbose] [-list] [-cache <size_in_mb>]\n" );
    return 1;
  }
  const char * mask = CmdLineLite::Instance().GetStringKey( "-mask", "*" );
  const char * destDir = CmdLineLite::Instance().GetStringKey( "-dest", "." );
  const bool justList = CmdLineLite::Instance().IsKeyDefined( "-list" );

  size_t cacheLimit = 1024 * 1024 * (size_t)CmdLineLite::Instance().GetIntKey( "-cache", 256 );

  MessageTrace( "Pile: %s", pileName );
  MessageTrace( "Mask: %s", mask );
  MessageTrace( "Destination folder: %s", destDir );
  MessageTrace( "Cache: %d mb", cacheLimit / (1024 * 1024) );

  Strong<fileSystem::FilePileLoader> pile = new fileSystem::FilePileLoader;
  if ( !pile->Init( pileName ) )
  {
    ErrorTrace( "Could not open pile '%s'", pileName );
    return 1;
  }

  MessageTrace( "Pile contains %d files", pile->FilesNumber() );

  vector<fileSystem::FilePileItemInfo> filesList;
  pile->FindFilesWild( filesList, mask );

  try
  {
    if ( justList )
      List( pile, filesList );
    else
      Unpack( pile, filesList, destDir, cacheLimit );
  }
  catch ( const MyExcep & ex )
  {
    ErrorTrace( "Operation failed: %s", ex.msg );
    return 1;
  }

  MessageTrace( "Done!" );
  return 0;
}
