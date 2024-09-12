#include "stdafx.h"
#include "FilePileCompiler.h"
#include "FilePileFormat.h"
#include "SimpleFileList.h"
#include "FsActivityLogReader.h"
#include "FilePath.h"
#include "FileUtils.h"
#include "zlib.h"
#include "System/Crc32Checksum.h"
#include "System/SimpleCrypt.hpp"


#pragma warning( disable : 4996 ) //warning C4996: 'fopen': This function or variable may be unsafe


#if defined(NI_PLATF_LINUX)

  #include <sys/io.h>
  long filelength( FILE * f )
  {
    long res;
    fpos_t position; 
    if ( fgetpos(f, &position) )
      return -1;
    fseek(f, 0, SEEK_END);
    res = ftell(f);
    if ( fsetpos(f, &position) )
      return -1;
    return res;
  }
  #define GET_FILE_SIZE( file ) filelength( file );

#else

  #include <io.h>
  #define GET_FILE_SIZE( file ) _filelength( _fileno( file ) );

#endif  // defined(NI_PLATF_LINUX)


namespace fileSystem
{
template<class ContT, class RndIter>
inline void Assign( ContT &c, RndIter first, size_t size )
{
  //nstl не поддерживает range assign
  c.clear();
  c.insert( c.begin(), first, first + size );
}

FilePileCompiler::FilePileCompiler( const SSettings & _settings ) :
settings( _settings ),
outBufferLimit( settings.outputBufferSize * 1024 * 1024 ),
outFile( 0 ),
bytesWritten( 0 )
{
  outBuffer.reserve( outBufferLimit );
}



FilePileCompiler::~FilePileCompiler()
{
}



bool FilePileCompiler::Compile()
{
  NI_VERIFY( !outFile, "", return false );

  if ( !CollectFiles() )
    return false;

  MessageTrace( "Writing data of %d files...", files.size() );
  outBuffer.clear();
  bytesWritten = 0;

  string outputFilename = settings.output;
  outFile.handle = fopen( outputFilename.c_str(), "wb" );
  NI_VERIFY( outFile, NStr::StrFmt( "Could not create output file '%s', code %d (%s)", outputFilename.c_str(), (int)errno, strerror( errno ) ), return false );

  //Tail header
  SFilePileTail tail;

  //Let's write safety tag
  WriteObject( FILEPILE_TAG );

  //Raw file data
  for ( int i = 0; i < files.size(); ++i )
    if ( !WriteFile( files[i] ) )
    {
      NI_ALWAYS_ASSERT( NStr::StrFmt( "Could not compress file '%s'", files[i].fullFilename.c_str() ) );
      return false;
    }
  tail.filesNumber = fileEntries.size();

  MessageTrace( "Writing indices of %d files...", fileEntries.size() );

  vector<char> buff;
  SimpleCrypt simpleCrypt;

  //Strings table
  tail.stringsOffset = bytesWritten;
  for ( int i = 0; i < fileEntries.size(); ++i )
  {
    fileEntries[i].second.fileNameOffset = bytesWritten - tail.stringsOffset;

    Assign( buff, fileEntries[i].first.c_str(), fileEntries[i].first.length() + 1 );
    simpleCrypt.EncryptDecrypt( &buff[0], buff.size() );
    WriteBytes( &buff[0], buff.size() );
  }
  tail.stringsLength = bytesWritten - tail.stringsOffset;

  simpleCrypt.Reset();

  //File index
  tail.fileIndexOffset = bytesWritten;
  for ( int i = 0; i < fileEntries.size(); ++i )
  {
    SFilePileEntry tmp(fileEntries[i].second);
    simpleCrypt.EncryptDecrypt( &tmp );
    WriteObject( tmp ); 
  }

  //Tail structure
  WriteObject( tail );

  statistics.overhead = (UInt64)bytesWritten - (UInt64)statistics.totalCompressedFilesSize;

  FlushBuffer();
  outFile.Close();

  return true;
}



bool FilePileCompiler::CollectFiles()
{
  NI_VERIFY( !settings.fileLists.empty(), "No files to pack specified", return false );

  fileEntries.clear();

  for ( int i = 0; i < settings.fileLists.size(); ++i )
  {
    const SSettingsFileList& lst = settings.fileLists[i];

    if ( lst.fileList )
    {
      DebugTrace( "Adding file list \"%s\" of %u entries...", lst.fileList->Filename().c_str(), lst.fileList->Access().size() );
      for ( int j = 0; j < lst.fileList->Access().size(); ++j )
        AddFile( lst.baseDir, lst.fileList->Access()[j] );
    }
    else //No explicit list - just scan the directories
    {
      if ( settings.foldersList.empty() )
        ScanDir( lst.baseDir, "" );
      else
        for ( int i = 0; i < settings.foldersList.size(); ++i )
          ScanDir( lst.baseDir, settings.foldersList[i] );
    }
  }

  return true;
}



void FilePileCompiler::AddFile( const string & baseDir, const string & relativeName )
{
  if ( !WeNeedThisFile( relativeName ) )
    return;

  files.push_back( SFileInfo() );

  files.back().relativeFilename = relativeName;
  NStr::TrimLeft( files.back().relativeFilename, "\\/" );
  NStr::ReplaceAllChars( &files.back().relativeFilename, '\\', '/' );

  files.back().fullFilename = NFile::Combine( baseDir, relativeName );
}



void FilePileCompiler::ScanDir( const string & baseDir, const string & relativeFolder )
{
  DebugTrace( "Scanning dir %s\\%s", baseDir.c_str(), relativeFolder.c_str() );

  vector<string> dirFiles;
  ScanDirRecursive( dirFiles, baseDir, relativeFolder );
  for ( int i = 0; i < dirFiles.size(); ++i )
    AddFile( baseDir, dirFiles[i] );
}



bool FilePileCompiler::WeNeedThisFile( const string & name )
{
  string noPath = NFile::GetFileName( name );

  for ( int i = 0; i < settings.excludeMasks.size(); ++i )
    if ( NStr::WildcardCompare( noPath.c_str(), settings.excludeMasks[i].c_str() ) )
      return false;

  for ( int i = 0; i < settings.masks.size(); ++i )
    if ( NStr::WildcardCompare( noPath.c_str(), settings.masks[i].c_str() ) )
      return true;

  return false;
}



bool FilePileCompiler::WriteFile( const SFileInfo & fileinfo )
{
  DebugTrace( "Processing '%s'...", fileinfo.fullFilename.c_str() );

  SAutoFile file( fopen( fileinfo.fullFilename.c_str(), "rb" ) );
  NI_VERIFY( file, NStr::StrFmt( "Could not open file '%s'", fileinfo.fullFilename.c_str() ), return false );

  long fileSize = GET_FILE_SIZE( file );
  NI_VERIFY( fileSize >= 0, NStr::StrFmt( "Could not open file '%s'", fileinfo.fullFilename.c_str() ), return false );

  vector<Byte> data( fileSize, 0 );
  const Byte * dataPtr = 0;
  if ( fileSize )
  {
    int elemRead = fread( &data[0], fileSize, 1, file );
    NI_VERIFY( elemRead == 1, NStr::StrFmt( "Could not read file '%s'", fileinfo.fullFilename.c_str() ), return false );
    dataPtr = &data[0];
  }

  Crc32Checksum crc;
  if ( !data.empty() )
    crc.Add( &data[0], data.size() );

  ++statistics.filesProcessed;
  statistics.totalFilesSize += (UInt64)fileSize;

  fileEntries.push_back( pair<string, SFilePileEntry>() );
  fileEntries.back().first = fileinfo.relativeFilename;
  SFilePileEntry & e = fileEntries.back().second;
  e.size = fileSize;
  e.sourceSize = fileSize;
  e.offset = bytesWritten;
  e.flags = 0;
  e.fileNameOffset = 0; //To be filled later
  e.crc = crc.Get();

  if ( ( settings.minFileSizeToCompress >= 0 ) && ( fileSize > settings.minFileSizeToCompress ) )
  {
    uLong zipSz = compressBound( (uLong)fileSize );
    zipBuffer.resize( Max( (int)zipBuffer.size(), (int)zipSz ) );

    int zres = compress2( &zipBuffer[0], &zipSz, (const Bytef *)dataPtr, (uLong)fileSize, 9 );
    NI_VERIFY( zres == Z_OK, NStr::StrFmt( "Zip compression failed (%d)", zres ), return false );
    NI_ASSERT( zipSz > 0, "Empty files" );

    float ratio = (float)zipSz / (float)fileSize;
    if ( ratio <= settings.maxCompressionRatio )
    {
      e.size = zipSz;
      e.flags |= FILEPILE_COMPRESSED;

      ++statistics.filesCompressed;
      statistics.totalCompressedFilesSize += (UInt64)zipSz;
      return WriteBytes( &zipBuffer[0], zipSz );
    }
  }
  statistics.totalCompressedFilesSize += (UInt64)fileSize;
  return WriteBytes( dataPtr, fileSize );
}



bool FilePileCompiler::WriteBytes( const void * data, unsigned size )
{
  NI_VERIFY( outFile, "File was not opened", return false );
  NI_VERIFY( bytesWritten + (UInt64)size < 0x7ffffffful, NStr::StrFmt( "Output file is too big!" ), return false );

  const Byte * bytes = static_cast<const Byte *>( data );
  for ( unsigned i = 0; i < size; ++i ) //per byte copying is cool
  {
    if ( (unsigned)outBuffer.size() >= outBufferLimit )
      if ( !FlushBuffer() )
        return false;

    outBuffer.push_back( bytes[i] );
  }

  bytesWritten += size;

  return true;
}



bool FilePileCompiler::FlushBuffer()
{
  if ( !outBuffer.empty() )
  {
    DebugTrace( "Flushing %u mb to disk...", outBuffer.size() / 1024 / 1024 );

    int written = fwrite( &outBuffer[0], outBuffer.size(), 1, outFile );
    NI_VERIFY( written == 1, NStr::StrFmt( "Writing %d bytes failed: code %d (%s), count %d", outBuffer.size(), (int)errno, strerror( errno ), written ), return false );
    outBuffer.clear();
  }
  return true;
}



void FilePileCompiler::ScanDirRecursive( vector<string> & files, const string & baseDir, const string & relativeFolder )
{
  string fullPath = NFile::Combine( baseDir, relativeFolder );

	if ( !NFile::DoesFolderExist( fullPath ) )
		return;

  // В Unix-системах *.* пропустет все файлы и директории без точек в имени
  // string searchPath = NFile::Combine( fullPath, "*.*" );
  string searchPath = NFile::Combine( fullPath, "*" );
  for ( NFile::CFileIterator it( searchPath ); !it.IsEnd(); ++it )
	{
		if ( it.IsDirectory() )
      continue;
    files.push_back( NFile::Combine( relativeFolder, it.GetFileName() ) );
	}

  for ( NFile::CFileIterator it( searchPath ); !it.IsEnd(); ++it )
  {
    if ( !it.IsDirectory() || it.IsDots() )
      continue;

    string dirName = it.GetFileName();
    if ( !NStr::ICmp( dirName.c_str(), ".svn" ) )
      continue;

    ScanDirRecursive( files, baseDir, NFile::Combine( relativeFolder, dirName ) );
  }
}






void SAutoFile::Close()
{
  if ( handle )
  {
    int fcloseResult = fclose( handle );
    NI_ASSERT( fcloseResult == 0, NStr::StrFmt( "Output file closure failed, code %d (%s)", (int)errno, strerror( errno ) ) );
  }

  handle = 0;
}

} //namespace fileSystem
