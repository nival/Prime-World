//!Component("System/FileSystem")

#include "stdafx.h"
#include "cxxtest/TestSuite.h"
#include "FileUtils.h"
#include "FilePath.h"
#include "FileSystem.h"
#include "WinFileSystem.h"
#include "FileSystemChangesProcessor.h"
#include "sleep.h"

#include "../TestAssertDumper.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const char data1[] = "File system test";
static const char data2[] = "01234567890123456789";
static const char base_dir[] = "file_system_test";
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class FileSystemTest : public CxxTest::TestSuite 
{
public:
  string fullDir;
  void setUp()
  {
    NFile::InitBaseDir();
    NFile::SetCurDiskDirectory( NFile::GetBaseDir().c_str() );
    fullDir = base_dir;
    NFile::CreateDiskDirectory( fullDir.c_str(), 0 );
  }

  void tearDown()
  {
    NFile::DeleteDirectory( (string(base_dir) + "\\").c_str() );
  }
  int guard;

  void CreateTestFile( const char* name, const char* data )
  {
    const string buf = string( base_dir ) + string( "/" ) + string( name );
#if defined( NV_WIN_PLATFORM )
    HANDLE hnd = (HANDLE) NFile::CreateFileWithDir( buf.c_str() );
    TS_ASSERT( hnd != INVALID_HANDLE_VALUE );
    DWORD bytesWritten = 0; 
    WriteFile( hnd, data, strlen( data ), &bytesWritten, 0 );
    CloseHandle( hnd );
#elif defined( NV_LINUX_PLATFORM )
    const int hnd = NFile::CreateFileWithDir( buf.c_str() );
    TS_ASSERT( hnd != -1 );
    const ssize_t bytesWritten = ::write( hnd, data, strlen( data ) );
    TS_ASSERT( bytesWritten == strlen( data ) );
    ( void ) ::close( hnd );
#endif
  }
  void ModifyTestFile( const char* name, const char* newData )
  {
    const string buf = string( base_dir ) + string( "/" ) + string( name );
#if defined( NV_WIN_PLATFORM )
    HANDLE hnd = (HANDLE)NFile::OpenFileWithDir( buf.c_str() );
    TS_ASSERT( hnd != INVALID_HANDLE_VALUE && hnd != 0 );
    DWORD bytesWritten = 0; 
    WriteFile( hnd, newData, strlen( newData ), &bytesWritten, 0 );
    CloseHandle( hnd );
#elif defined( NV_LINUX_PLATFORM )
    const int hnd = NFile::OpenFileWithDir( buf.c_str() );
    TS_ASSERT( hnd != -1 );
    const ssize_t bytesWritten = ::write( hnd, newData, strlen( newData ) );
    TS_ASSERT( bytesWritten == strlen( newData ) );
    ( void ) ::close( hnd );
#endif
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void testSingleWinVFS()
	{                  
    CreateTestFile( "a.txt", data1 );
    CreateTestFile( "b.txt", data1 );
    CreateTestFile( "1.data", data2 );
    CreateTestFile( "2.data", data2 );
    CreateTestFile( "1/3.data", data2 );
    CreateTestFile( "1/4.data", data2 );

    CObj<WinFileSystem> fileSys = new WinFileSystem( fullDir, false );

    vector<string> files;
    fileSys->GetFiles( &files, "", "*.txt", true );

    TS_ASSERT_EQUALS( files.size(), 2 );
    TS_ASSERT( files[0] == "a.txt" );
    TS_ASSERT( files[1] == "b.txt" );

    files.clear();
    fileSys->GetFiles( &files, "1/", "*.*", true );
    TS_ASSERT_EQUALS( files.size(), 2 );
    TS_ASSERT( files[0] == "3.data" );
    TS_ASSERT( files[1] == "4.data" );

    CObj<Stream> stream = fileSys->OpenFile( "1/3.data", FILEACCESS_READ, FILEOPEN_OPEN_EXISTING );
    TS_ASSERT( strcmp( stream->GetBuffer(), data2 ) == 0 ); 

    stream = fileSys->OpenFile( "a.txt", FILEACCESS_READ, FILEOPEN_OPEN_EXISTING );
    TS_ASSERT( strcmp( stream->GetBuffer(), data1 ) == 0 ); 
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void testFileWatcher()
  {
    CreateTestFile( "1.data", data1 );
    CreateTestFile( "2.data", data1 );
    CreateTestFile( "1/3.data", data1 );
    CreateTestFile( "1/4.data", data1 );
    CreateTestFile( "1/2/5.data", data1 );

    IFileWatcher::TChangedFileList changedFiles;

    CObj<WinFileSystem> fileSys = new WinFileSystem( fullDir, false );
    CObj<IFileWatcher> watcher1 = fileSys->CreateFileWatcher( "" );
    CObj<IFileWatcher> watcher2 = fileSys->CreateFileWatcher( "1" );
    TS_ASSERT( watcher1->GetPath() == "" );
    TS_ASSERT( watcher2->GetPath() == "1" );

    nival::sleep( 100 );
    TS_ASSERT( !watcher1->SomethingChanged( &changedFiles ) );
    TS_ASSERT( !watcher2->SomethingChanged( &changedFiles ) );

    ModifyTestFile( "1/3.data", data2 );
    ModifyTestFile( "1.data", data1 );

    guard = 100;
    while( !watcher2->SomethingChanged( &changedFiles ) && --guard > 0 )
      nival::sleep( 10 );

    TS_ASSERT_EQUALS( changedFiles.size(), 1 );
    TS_ASSERT( changedFiles.front() == "1/3.data" );
    
    changedFiles.clear();
    guard = 100;
    while( changedFiles.size() < 2  && --guard > 0 )
    {
      watcher1->SomethingChanged( &changedFiles );
        nival::sleep( 10 );
    }


    TS_ASSERT_EQUALS( changedFiles.size(), 2 );
    TS_ASSERT( changedFiles.front() == "1/3.data" );
    TS_ASSERT( *( ++changedFiles.begin()) == "1.data" );

    CreateTestFile( "a.data", data1 );

    changedFiles.clear();
    guard = 100;
    while( !watcher1->SomethingChanged( &changedFiles ) && --guard > 0 )
      nival::sleep( 10 );
    TS_ASSERT_EQUALS( changedFiles.size(), 1 );
    TS_ASSERT( changedFiles.front() == "a.data" );
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void testRootFSWatcher()
  {
    CreateTestFile( "1/1.data", data2 );
    CreateTestFile( "1/2.data", data2 );
    CreateTestFile( "2/3.data", data2 );
    CreateTestFile( "2/4.data", data2 );

    RootFileSystem::ClearFileSystems();
    RootFileSystem::RegisterFileSystem( new WinFileSystem( string(fullDir) + "/1", false ) );
    RootFileSystem::RegisterFileSystem( new WinFileSystem( string(fullDir) + "/2", false ) );

    IFileWatcher::TChangedFileList changedFiles;
    CObj<IFileWatcher> watcher = RootFileSystem::CreateFileWatcher( "" );

    nival::sleep( 100 );
    TS_ASSERT( !watcher->SomethingChanged( &changedFiles ) );

    ModifyTestFile( "1/2.data", data1 );

    changedFiles.clear();
    guard = 100;
    while( !watcher->SomethingChanged( &changedFiles ) && --guard > 0 )
      nival::sleep( 10 );

    TS_ASSERT_EQUALS( changedFiles.size(), 1 );
    TS_ASSERT( changedFiles.front() == "2.data" );


    ModifyTestFile( "1/1.data", data1 );
    ModifyTestFile( "2/3.data", data1 );

    changedFiles.clear();
    guard = 100;
    while( changedFiles.size() < 2  && --guard > 0 )
    {
      watcher->SomethingChanged( &changedFiles );
      nival::sleep( 10 );
    }

    TS_ASSERT_EQUALS( changedFiles.size(), 2 );
    TS_ASSERT( changedFiles.front() == "1.data" );
    TS_ASSERT( *( ++changedFiles.begin()) == "3.data" );

    RootFileSystem::ClearFileSystems();
  }

};

class FileSystemChangesProcessorTest : public CxxTest::TestSuite 
{
public:
  class MockFileSystemWatcher : public IFileWatcher, public CObjectBase
  {	
  public:
    MockFileSystemWatcher(){}

    virtual bool SomethingChanged( IFileWatcher::TChangedFileList* pFileList )
    {
      if ( fileList.empty() )
        return false;

      pFileList->insert( pFileList->begin(), fileList.begin(), fileList.end() );
      fileList.clear();

      return true;
    }

    virtual const string& GetPath() const { return path; }

    IFileWatcher::TChangedFileList fileList;
    string path;
  private:
    OBJECT_BASIC_METHODS( MockFileSystemWatcher );
  };

  static string lastXDB;
  static string lastXDB2;
  static string lastData;
  static string lastFileName;

  static void TestHandlerXDB( const string& fileName )
  { lastXDB = fileName; }

  static void TestHandlerXDB2( const string& fileName )
  { lastXDB2 = fileName; }

  static void TestHandlerData( const string& fileName )
  { lastData = fileName; }

  static void TestHandlerFileName( const string& fileName )
  { lastFileName = fileName; }

  void TestStaticFunctor()
  {
    MockFileSystemWatcher* w = new MockFileSystemWatcher();
    FileSystemChangesProcessor proc;
    proc.SetFileWatcher( w );
    TS_ASSERT( proc.RegisterFileWatchByExtension( ".xdb", new FileWatchFunctor( TestHandlerXDB ) ) );
    TS_ASSERT( proc.RegisterFileWatchByExtension( ".xdb", new FileWatchFunctor( TestHandlerXDB2 ) ) );

    NLogg::FailTestOnAnyError( false );
    TS_ASSERT( !proc.RegisterFileWatchByExtension( ".xdb", new FileWatchFunctor( TestHandlerXDB ) ) );
    NLogg::FailTestOnAnyError( true );

    TS_ASSERT( proc.RegisterFileWatchByExtension( ".data", new FileWatchFunctor( TestHandlerData ) ) );
    TS_ASSERT( proc.RegisterFileWatchByName( "test1.xdb", new FileWatchFunctor( TestHandlerFileName ) ) );

    proc.ProcessFileWatchers();

    TS_ASSERT( lastXDB == "" );
    TS_ASSERT( lastData == "" );
    TS_ASSERT( lastFileName == "" );

    w->fileList.push_back( "ttt/a.xdb" );
    proc.ProcessFileWatchers();
    TS_ASSERT( lastXDB == "ttt/a.xdb" ); lastXDB.clear();
    TS_ASSERT( lastXDB2 == "ttt/a.xdb" ); lastXDB2.clear();
    TS_ASSERT( lastData == "" ); lastData.clear();
    TS_ASSERT( lastFileName == "" ); lastFileName.clear();

    w->fileList.push_back( "ttt/b" );
    proc.ProcessFileWatchers();
    TS_ASSERT( lastXDB == "" ); lastXDB.clear();
    TS_ASSERT( lastData == "" ); lastData.clear();
    TS_ASSERT( lastFileName == "" ); lastFileName.clear();

    {
      FileWatchFunctor f( TestHandlerXDB2 );
      TS_ASSERT( proc.UnregisterFileWatchByExtension( ".xdb", &f ) );
    }

    w->fileList.push_back( "test1.xdb" );
    proc.ProcessFileWatchers();
    TS_ASSERT( lastXDB == "test1.xdb" ); lastXDB.clear();
    TS_ASSERT( lastXDB2 == "" ); lastXDB2.clear();
    TS_ASSERT( lastData == "" ); lastData.clear();
    TS_ASSERT( lastFileName == "test1.xdb" ); lastFileName.clear();

    w->fileList.push_back( "a/b/c/k.data" );
    w->fileList.push_back( "a/f.data" );
    proc.ProcessFileWatchers();
    TS_ASSERT( lastXDB == "" ); lastXDB.clear();
    TS_ASSERT( lastData == "a/f.data" ); lastData.clear();
    TS_ASSERT( lastFileName == "" ); lastFileName.clear();
  }

  struct FileHandler
  {
    string lastFileName;

    void OnFile( const string& fileName )
    {
      lastFileName = fileName;
    }
  };

  void TestMethodFunctor()
  {
    FileHandler handlerXDB; 
    FileHandler handlerXDB2; 
    FileHandler handlerFileName; 

    MockFileSystemWatcher* w = new MockFileSystemWatcher();
    FileSystemChangesProcessor proc;
    proc.SetFileWatcher( w );
    TS_ASSERT( proc.RegisterFileWatchByExtension( ".xdb", new FileWatchMethodFunctor<FileHandler>( &handlerXDB, &FileHandler::OnFile ) ) );
    TS_ASSERT( proc.RegisterFileWatchByExtension( ".xdb", new FileWatchMethodFunctor<FileHandler>( &handlerXDB2, &FileHandler::OnFile ) ) );

    NLogg::FailTestOnAnyError( false );
    TS_ASSERT( !proc.RegisterFileWatchByExtension( ".xdb", new FileWatchMethodFunctor<FileHandler>( &handlerXDB, &FileHandler::OnFile ) ) );
    NLogg::FailTestOnAnyError( true );

    TS_ASSERT( proc.RegisterFileWatchByName( "test1.xdb", new FileWatchMethodFunctor<FileHandler>( &handlerFileName, &FileHandler::OnFile ) ) );

    proc.ProcessFileWatchers();

    TS_ASSERT( handlerXDB.lastFileName == "" );
    TS_ASSERT( handlerXDB2.lastFileName == "" );
    TS_ASSERT( handlerFileName.lastFileName == "" );

    w->fileList.push_back( "ttt/a.xdb" );
    proc.ProcessFileWatchers();
    TS_ASSERT( handlerXDB.lastFileName == "ttt/a.xdb" ); handlerXDB.lastFileName.clear();
    TS_ASSERT( handlerXDB2.lastFileName == "ttt/a.xdb" ); handlerXDB2.lastFileName.clear();
    TS_ASSERT( handlerFileName.lastFileName == "" ); handlerFileName.lastFileName.clear();

    {
      FileWatchMethodFunctor<FileHandler> f( &handlerXDB2, &FileHandler::OnFile );
      TS_ASSERT( proc.UnregisterFileWatchByExtension( ".xdb", &f ) );
    }

    w->fileList.push_back( "test1.xdb" );
    proc.ProcessFileWatchers();
    TS_ASSERT( handlerXDB.lastFileName == "test1.xdb" ); handlerXDB.lastFileName.clear();
    TS_ASSERT( handlerXDB2.lastFileName == "" ); handlerXDB2.lastFileName.clear();
    TS_ASSERT( handlerFileName.lastFileName == "test1.xdb" ); handlerFileName.lastFileName.clear();

  }

};

string FileSystemChangesProcessorTest::lastXDB;
string FileSystemChangesProcessorTest::lastXDB2;
string FileSystemChangesProcessorTest::lastData;
string FileSystemChangesProcessorTest::lastFileName;
