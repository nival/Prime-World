#include "stdafx.h"
#include "FileSystem.h"
#include "FilePileLoader.h"
#include "FilePileStream.h"
#include "FilePileFormat.h"
#include "System/Crc32Checksum.h"
#include "System/InlineProfiler.h"
#include "zlib.h"
#if defined( NV_WIN_PLATFORM )
#include "MemoryLib/UserMessage.h"
#endif
#include "../SimpleCrypt.hpp"


NI_DEFINE_REFCOUNT( fileSystem::FilePileLoader );

//Special macro to enable custom error reporting in "shipping" build cfg
#define CRITICAL_PILE_FILE_CHECK( expr, user_text, statement, error_code ) { if ( !(expr) ) { OnFileCorruption( #expr, user_text, error_code ); { statement; } } }

DEV_VAR_STATIC int s_FileSizeHardlimit = 256;
REGISTER_DEV_VAR( "fs_piled_file_size_limit", s_FileSizeHardlimit, STORAGE_NONE );


namespace fileSystem
{

#pragma warning( disable : 4996 ) //warning C4996: 'fopen': This function or variable may be unsafe

FilePileLoader::FilePileLoader() :
file( 0 )
{
}



FilePileLoader::~FilePileLoader()
{
  if ( file )
    fclose( file );
  file = 0;
}

template<class T>
STARFORCE_FORCE_NOINLINE void FilePileLoader::Decrypt( T *pData, size_t size )
{
  SimpleCrypt().EncryptDecrypt( pData, size );
}

STARFORCE_FORCE_INLINE bool FilePileLoader::ReadTail( SFilePileTail & tail )
{
  STARFORCE_STOPWATCH();
  
  int result = fseek( file, -(long)sizeof( tail ), SEEK_END );
  CRITICAL_PILE_FILE_CHECK( result == 0, "Tail seek error", return false, FR_READ_ERROR );

  result = fread( &tail, sizeof( tail ), 1, file );
  CRITICAL_PILE_FILE_CHECK( result == 1, "Tail read error", return false, FR_READ_ERROR );

  bool fileOk = ( tail.tag == FILEPILE_TAG );
  CRITICAL_PILE_FILE_CHECK( ( tail.version == FILEPILE_VERSION ), NStr::StrFmt( "Wrong version 0x%08x, 0x%08x is needed", tail.version, FILEPILE_VERSION ), return false, FR_READ_ERROR );
  fileOk = fileOk && ( tail.filesNumber > 0 ) && ( tail.filesNumber < 1024 * 1024 );
  fileOk = fileOk && ( tail.stringsLength > 0 ) && ( tail.stringsLength < 16 * 1024 * 1024 );
  CRITICAL_PILE_FILE_CHECK( fileOk, "File is corrupt (range check)", return false, FR_READ_ERROR );

  return true;
}

STARFORCE_FORCE_INLINE bool FilePileLoader::ReadStringsTable( const SFilePileTail & tail )
{
  STARFORCE_STOPWATCH();
  
  int result = fseek( file, tail.stringsOffset, SEEK_SET );
  CRITICAL_PILE_FILE_CHECK( result == 0, "Strings seek error", return false, FR_READ_ERROR );

  filenamesTable.resize( tail.stringsLength, 0 );
  result = fread( &filenamesTable[0], tail.stringsLength, 1, file );
  CRITICAL_PILE_FILE_CHECK( result == 1, "Strings read error", return false, FR_READ_ERROR );
  Decrypt( &filenamesTable[0], tail.stringsLength );
  
  return true;
}

STARFORCE_FORCE_NOINLINE bool FilePileLoader::BuildInternalIndex( const TDiskIndex &diskIndex )
{
  const UInt32 fileSizeHardLimit = (UInt32)( s_FileSizeHardlimit * 1024u * 1024u );

  //lets build internal index
  for ( TDiskIndex::const_iterator it = diskIndex.begin(); it != diskIndex.end(); ++it )
  {
    const SFilePileEntry & entry = *it;
    
    CRITICAL_PILE_FILE_CHECK( entry.fileNameOffset < (UInt32)filenamesTable.size(), "File is corrupt", return false, FR_READ_ERROR );
    const char * const fileName = filenamesTable.c_str() + (int)entry.fileNameOffset;

    CRITICAL_PILE_FILE_CHECK( entry.size < fileSizeHardLimit, "File size is too big", return false, FR_READ_ERROR );
    CRITICAL_PILE_FILE_CHECK( entry.sourceSize < fileSizeHardLimit, "Source file size is too big", return false, FR_READ_ERROR );
    CRITICAL_PILE_FILE_CHECK( *fileName != '0', "File is corrupt", return false, FR_READ_ERROR );
    CRITICAL_PILE_FILE_CHECK( *fileName != '/', "File is corrupt", return false, FR_READ_ERROR );
    
    SIndexKey key( fileName );
    index[key] = entry;
  }
  
  return true;
}

STARFORCE_FORCE_INLINE bool FilePileLoader::ReadFileIndex( const SFilePileTail & tail )
{
  STARFORCE_STOPWATCH();
  
  TDiskIndex diskIndex;
  diskIndex.resize( tail.filesNumber );
  int result = fseek( file, tail.fileIndexOffset, SEEK_SET );
  CRITICAL_PILE_FILE_CHECK( result == 0, "Index seek error", return false, FR_READ_ERROR );

  result = fread( &diskIndex[0], sizeof( SFilePileEntry ), tail.filesNumber, file );
  CRITICAL_PILE_FILE_CHECK( result == (int)tail.filesNumber, "Index read error", return false, FR_READ_ERROR );
  Decrypt( &diskIndex[0], tail.filesNumber );

  return BuildInternalIndex(diskIndex);
}

bool FilePileLoader::Init( const string & fullFilename, IFileReadCallback* cb )
{
  NI_PROFILE_FUNCTION

  SetFileReadCallback(cb);

  packFilename = fullFilename;

  file = fopen( packFilename.c_str(), "rb" );
  CRITICAL_PILE_FILE_CHECK( file, "Could not open file", return false, FR_READ_ERROR );
  
  SFilePileTail tail;
  if ( !ReadTail( tail ) || !ReadStringsTable( tail ) || !ReadFileIndex( tail ))
    return false;
  
  return true;
}

bool FilePileLoader::HasFile( const string & fileName ) const
{
  return FindFile( fileName ) ? true : false;
}

Stream * FilePileLoader::ReadFile( const string & fileName ) const
{
  NI_PROFILE_FUNCTION

  const SFilePileEntry * entry = FindFile( fileName );
  if ( !entry )
    return 0;

  vector<Byte> bytes;

  CRITICAL_PILE_FILE_CHECK( ReadFileBytes( bytes, *entry ), "File is corrupt", return 0, FR_READ_ERROR );
  
  if ( entry->flags & FILEPILE_COMPRESSED )
    return DecompressFile( *entry, bytes, fileName.c_str() );
  else
  {
    CRITICAL_PILE_FILE_CHECK( entry->size == entry->sourceSize, "File is corrupt", return 0, FR_READ_ERROR );
    if ( !CheckCrc( *entry, bytes, fileName.c_str() ) )
      return 0;

    OnFileOk();
    return new FilePileStream( bytes );
  }
}



bool FilePileLoader::ReadFileBytes( vector<Byte> & bytes, const SFilePileEntry & entry ) const
{
  NI_PROFILE_FUNCTION

  bytes.resize( entry.size, 0 );

  if ( !entry.sourceSize )
    return true;

  threading::MutexLock lock( mutex );

  int result = fseek( file, entry.offset, SEEK_SET );
  CRITICAL_PILE_FILE_CHECK( result == 0, "File data seek error", return false, FR_READ_ERROR );

  result = fread( &bytes[0], entry.size, 1, file );
  CRITICAL_PILE_FILE_CHECK( result == 1, "File data read error", return false, FR_READ_ERROR );

  return true;
}



Stream * FilePileLoader::DecompressFile( const SFilePileEntry & entry, const vector<Byte> & bytes, const char * _debugFilename ) const
{
  NI_PROFILE_FUNCTION;

  NI_ASSERT( entry.flags & FILEPILE_COMPRESSED, "" );
  CRITICAL_PILE_FILE_CHECK( ( entry.sourceSize > 0 ) && ( entry.size > 0 ), "File is corrupt", return 0, FR_READ_ERROR );

  vector<Byte> zipBuffer( entry.sourceSize );
  memset( &zipBuffer[0], 0, zipBuffer.size() );

  uLong bufSz = (uLong)zipBuffer.size();
  int zres = uncompress( &zipBuffer[0], &bufSz, &bytes[0], (uLong)bytes.size() );
  CRITICAL_PILE_FILE_CHECK( zres == Z_OK, NStr::StrFmt( "Zip '%s' decompression failed (%d)", _debugFilename, zres ), return 0, FR_READ_ERROR );

  if ( !CheckCrc( entry, zipBuffer, _debugFilename ) )
    return 0;

  OnFileOk();
  return new FilePileStream( zipBuffer );
}



bool FilePileLoader::CheckCrc( const SFilePileEntry & entry, const vector<Byte> & bytes, const char * _debugFilename ) const
{
  Crc32Checksum crc;
  if ( !bytes.empty() )
    crc.Add( &bytes[0], bytes.size() );


  if( entry.crc != crc.Get() )
  {
    if (!IsValid(readCallback))
    {
      OnFileCorruption( "CRC Check", NStr::StrFmt( "CRC '%s' check failed", _debugFilename ), FR_CRC_FAIL );

#if defined( NV_WIN_PLATFORM )
      UserMessage::ShowMessageAndTerminate( 
          EXCEPTION_DATATYPE_MISALIGNMENT,
          "File corrupted.\nPlease reinstall the application."
        );
#endif
    
      return false;
    }
    else
      CRITICAL_PILE_FILE_CHECK( false, NStr::StrFmt( "CheckCrc failed on file '%s'", _debugFilename), return false, FR_CRC_FAIL );
  }
  
  return true;
}



void FilePileLoader::FindFiles( vector<string> * fileNames, const string & baseDir, const string & mask, bool recursive ) const
{
  NI_PROFILE_FUNCTION

  //Folder tree search simulation with linear search through full filenames

  string path;
  PrepareFilename( path, baseDir );
  NStr::TrimRight( path, '/' );

  int pathLen = path.length();

  for ( TIndex::const_iterator it = index.begin(); it != index.end(); ++it )
  {
    const char * filename = it->first;
#if defined( NV_WIN_PLATFORM )
    if ( strnicmp( path.c_str(), filename, path.size() ) != 0 )
      continue;
#elif defined( NV_LINUX_PLATFORM )
    if ( strncasecmp( path.c_str(), filename, path.size() ) != 0 )
      continue;
#endif

    if ( filename[pathLen] != '/' )
      continue;

    const char * neededFilename = filename + pathLen + 1;

    //Is tis file in folder 'baseDir' or deeper?
    if ( !recursive )
    {
      if ( strchr( neededFilename, '/' ) )
        continue;
    }

    //check mask
    if ( !mask.empty() )
    {
      const char * filenameItself = strrchr( neededFilename, '/' );
      if ( !filenameItself )
        filenameItself = neededFilename;

      if ( !NStr::WildcardCompare( filenameItself, mask.c_str() ) )
        continue;
    }

    if ( fileNames )
      fileNames->push_back( neededFilename );
  }
}



void FilePileLoader::FindFilesWild( vector<FilePileItemInfo> & fileNames, const string & mask ) const
{
  string fixedMask;
  PrepareFilename( fixedMask, mask );

  for ( TIndex::const_iterator it = index.begin(); it != index.end(); ++it )
  {
    string fname;
    PrepareFilename( fname, it->first.pName );

    if ( NStr::WildcardCompare( fname.c_str(), fixedMask.c_str() ) )
      fileNames.push_back( FilePileItemInfo( fname.c_str(), it->second.sourceSize ) );
  }
}



const SFilePileEntry * FilePileLoader::FindFile( const string & fileName ) const
{
  NI_PROFILE_FUNCTION

  string name;
  PrepareFilename( name, fileName );

  SIndexKey key( name.c_str() );

  TIndex::const_iterator it = index.find( key );
  if ( it == index.end() )
    return 0;
  return &it->second;
}



void FilePileLoader::PrepareFilename( string & result, const string & fileName )
{
  int from = ( !fileName.empty() && IsSlash( fileName[0] ) ) ? 1 : 0;
  
  result.resize( fileName.size() - from );
  for ( int i = from; i < fileName.size(); ++i )
  {
    char c = fileName[i];
    result[i - from] = ( c == '\\' ) ? '/' : c;
  }
}



void FilePileLoader::OnFileCorruption( const char * _expr, const char * _msg, FileReadResultCode err_code ) const
{
  DebugTrace( "Pile file '%s' corrupted: check '%s' failed: %s", packFilename.c_str(), _expr, _msg );

  if (IsValid(readCallback)) 
  {
    (*readCallback.GetPtr())(err_code, packFilename.c_str());
    //предотвратим повторный вызов
    readCallback.SetPtr(NULL);
  }
}

void FilePileLoader::OnFileOk() const
{
  if (IsValid(readCallback)) (*readCallback.GetPtr())(FR_OK, packFilename.c_str());
}

} //namespace fileSystem

#undef CRITICAL_PILE_FILE_CHECK
