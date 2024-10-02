#include "stdafx.h"

#include <stdio.h>
#include <stdlib.h>

#include "FsActivityLogReader.h"
#include "SimpleFileList.h"
#include "FilePileCompiler.h"

#include "System/FileSystem/FilePath.h"
#include "System/DebugTraceDumper.h"
#include "System/AssertDumper.h"
#include "System/ServerStdOutDumper.h"
#include "System/CmdLineLite.h"
#include "Version.h"

#pragma comment (lib, "Dbghelp.lib")
#pragma comment (lib, "rpcrt4.lib")

#if defined(NI_PLATF_LINUX)

  #define GET_CUR_DIR( dir, size ) getcwd( dir, size )

#else

  #define GET_CUR_DIR( dir, size ) GetCurrentDirectory( size, dir )

#endif  // defined(NI_PLATF_LINUX)


static void DumpStringVector( const char * title, const vector<string> & lst )
{
  string tmp;
  tmp.reserve( 256 );
  for ( int i = 0; i < lst.size(); ++i )
  {
    if ( !tmp.empty() )
      tmp += ", ";
    tmp += '"';
    tmp += lst[i];
    tmp += '"';
  }
  MessageTrace( "%s%s", title, tmp.c_str() );
}



int main( int argc, char **argv )
{
  CmdLineLite::Instance().Init( argc, argv );

  if ( CmdLineLite::Instance().IsKeyDefined( "-help" ) )
  {
    printf( 
      "Command-line help:\n"
      " -help                           Show this help\n"
      " -output <filename>              Specify output file name\n"
      " -packdir <base dir> [<filelist>] Add specified base directory/filelist pair.\n"
      "                                 Can process multiple filelists.\n"
      "                                 If file list is not specified, full\n"
      "                                 scan will be performed on specified\n"
      "                                 directory. Default is to pack \"Data\"\n"
      "                                 in current folder\n"
      " -masks <masks list>             Pack only files that comply with\n"
      "                                 specified wildcard list. Use semicolon\n"
      "                                 if tou need several masks\n"
      " -excl_masks <masks list>        Exclude files by wildcar set\n"
      " -comp_size <min file size>      Minimal file size that will compressed.\n"
      "                                 Omit this to disable compression at all\n"
      " -max_comp_ratio <percent>       Worst allowed file compression ratio\n"
      " -folders <folders list>         Scan next set of folders. If not specified,\n"
      "                                 all found folders will be used\n"
      " -verbose <level>                Specify verbose level: 1 - all messages\n"
      "                                 2 (default) - ignore debug messages, etc\n"
      " -buffer <size>                  Specify outpout buffer size, in MB\n"
      "\n"
      "Examples:\n"
      "\n"
      "FilePileCompilerApp.exe\n"
      "  Recursively scans Data/ folder and packs all ze files in it.\n"
      "  Generate \"result.pile\"\n"
      "\n"
      "FilePileCompilerApp.exe -output XdbAndTxt -masks \"*.xdb;*.txt\" -comp_size 64 -max_comp_ratio 50\n"
      "\n"
      "FilePileCompilerApp.exe -output NoXdbAndTxt -excl_masks \"*.xdb;*.txt\" -comp_size 64 -max_comp_ratio 75\n"
      "\n"
      "FilePileCompilerApp.exe -packdir ñ:\\work\\trunk c:\\work\\trunklist.txt -masks *.xdb\n"
      "\n"
      );
    return 1;
  }
  NLogg::CDebugTraceDumper debugTraceDumper( &GetSystemLog() );
  NLogg::CServerStdOutDumper stdOutDumper( &GetSystemLog(), (NLogg::ELevel)max<int>( NLogg::LEVEL_DEBUG, CmdLineLite::Instance().GetIntKey( "-verbose", NLogg::LEVEL_MESSAGE ) ) );
  
  char szCurrDir[512] = "";
  if ( GET_CUR_DIR( szCurrDir, 512 ) )
  {
    DebugTrace( "Working in directory '%s'\n", szCurrDir );
  }

  //Lez prepare
  fileSystem::FilePileCompiler::SSettings settings;

  CmdLineLite::TMultiStringArgs packDirs;
  CmdLineLite::Instance().GetMultipleStringKeys( "-packdir", packDirs );
  for ( CmdLineLite::TMultiStringArgs::const_iterator it = packDirs.begin(); it != packDirs.end(); ++it )
  {
    if ( ( it->size() != 1 ) && ( it->size() != 2 ) )
    {
      DebugTrace( "Wrong -packdir format!" );
      return 1;
    }
    fileSystem::FilePileCompiler::SSettingsFileList lst;
    lst.baseDir = it->front();
    if ( it->size() == 2 )
    {
      lst.fileList = new fileSystem::SimpleFileList;
      if ( !lst.fileList->Load( it->back().c_str() ) )
        return 1;
    }
    settings.fileLists.push_back( lst );
  }

  if ( settings.fileLists.empty() )
  {
    fileSystem::FilePileCompiler::SSettingsFileList lst;
    lst.baseDir = "Data";
    settings.fileLists.push_back( lst );
  }

  settings.output = CmdLineLite::Instance().GetStringKey( "-output", "result.pile" );
  if ( NFile::GetFileExt( settings.output ).empty() )
    settings.output += ".pile";

  settings.outputBufferSize = CmdLineLite::Instance().GetIntKey( "-buffer", 16 );

  NStr::SplitString( CmdLineLite::Instance().GetStringKey( "-masks", "*.*" ), &settings.masks, ';' );
  NStr::SplitString( CmdLineLite::Instance().GetStringKey( "-excl_masks", "" ), &settings.excludeMasks, ';' );

  settings.minFileSizeToCompress = CmdLineLite::Instance().GetIntKey( "-comp_size", -1 );
  settings.maxCompressionRatio = CmdLineLite::Instance().GetIntKey( "-max_comp_ratio", 99 ) / 100.0f;

  if ( const char * logArg = CmdLineLite::Instance().GetStringKey( "-order" ) )
  {
    string logFileName = NFile::GetBaseDir() + logArg;
    //settings.filesOrder = new fileSystem::ActivityLogReader;
    if ( !settings.filesOrder.Load( logFileName.c_str() ) )
      return 1;
  }

  if ( const char * dirListArg = CmdLineLite::Instance().GetStringKey( "-folders" ) )
    NStr::SplitString( dirListArg, &settings.foldersList, ';' );

  MessageTrace( "Job setup:" );
  DumpStringVector( "  Folders to process: ", settings.foldersList );
  DumpStringVector( "  Masks: ", settings.masks );
  DumpStringVector( "  Exclude masks: ", settings.excludeMasks );
  for ( int i = 0; i < settings.fileLists.size(); ++i )
  {
    const fileSystem::FilePileCompiler::SSettingsFileList& lst = settings.fileLists[i];
    if ( lst.fileList )
      MessageTrace( "  Process filelist \"%s\" (%d entries) in \"%s\"", lst.fileList->Filename().c_str(), lst.fileList->Access().size(), lst.baseDir.c_str() );
    else
      MessageTrace( "  Scan \"%s\"", lst.baseDir.c_str() );
  }

  fileSystem::FilePileCompiler compiler( settings );
  if ( compiler.Compile() )
  {
    MessageTrace( "Done!" );
    MessageTrace( "  %d files processed of total %d mb", compiler.Statistics().filesProcessed, (unsigned)( compiler.Statistics().totalFilesSize / ( 1024 * 1024 ) ) );
    if ( compiler.Statistics().totalFilesSize > 0 )
    {
      int compRate100 = (int)( 100.0f * (float)compiler.Statistics().totalCompressedFilesSize / (float)compiler.Statistics().totalFilesSize );
      MessageTrace( "  %d of them were compresed (%d%% average ratio)", compiler.Statistics().filesCompressed, compRate100 );
      MessageTrace( "  %d kb overhead", compiler.Statistics().overhead / 1024 );
    }
  }
  else
  {
    DebugTrace( "Failure!" );
    return 2;
  }

  // At this moment, the refcount for the dumpers is '1'.
  // The stdOutDumper job thread finishes and destroys the
  // dumper object.
  // The logger does not un-register the stdout dumper
  // on the dumper job thread exit, and the 'thread finished'
  // message dump attempt crashes the application.

  // Hence, hack a bit by increasing the ref counter.
  // The Logger::RemoveDumper() below forces a Dumper destructor call
  // (if the form of dumpers.erase(StrongMT<Dumper>p)), which
  // does not destroy the dumper object, but merely decreases the refcount.
  // So the stdOutDumper survives the removal from the Logger,
  // the message gets dumped succssfully, and we can
  // safely destroy the object at the end of the main() scope.
  stdOutDumper.StrongAddRef();
  debugTraceDumper.StrongAddRef();

  GetSystemLog().RemoveDumper(&debugTraceDumper);
  GetSystemLog().RemoveDumper(&stdOutDumper);
  return 0;
}
