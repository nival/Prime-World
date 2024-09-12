#include "stdafx.h"
#include "FileSystem.h"
#include "CombinerFileSystem.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
IFileReadCallback* CreateFileReadCallback( FileReadCallback::Callback cbk, FileReadCallback::Context* context  )
{
  return new FileReadCallback(cbk, context);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace RootFileSystem
{
  struct SFileSystemGuard
  {
    ICombinerFileSystem* Get() 
    { 
      if ( !rootFileSystem )
        rootFileSystem = new CombinerFileSystem();
      return rootFileSystem;
    }
    ~SFileSystemGuard() { rootFileSystem = 0; }

  private:
    CObj<CombinerFileSystem> rootFileSystem;
  };
  static SFileSystemGuard rootFS;
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ICombinerFileSystem* GetRootFileSystem()
  {
    return rootFS.Get();
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void RegisterFileSystem( IFileSystem* pFileSystem, IFileReadCallback* callback/* = 0*/) { GetRootFileSystem()->RegisterFileSystem( pFileSystem, callback ); }
  void UnregisterFileSystem( IFileSystem* pFileSystem ) { GetRootFileSystem()->UnregisterFileSystem( pFileSystem ); }
  void ClearFileSystems() { GetRootFileSystem()->ClearFileSystems(); }

  bool SetWriteFileSystem( IFileSystem* pFileSystem ) { return GetRootFileSystem()->SetWriteFileSystem( pFileSystem ); }

  bool GetFileInfo( SFileInfo *pInfo, const string &fileName ) { return GetRootFileSystem()->GetFileInfo( pInfo, fileName ); }
  void GetDirectories( vector<string> *pDirectories, const string &root ) { GetRootFileSystem()->GetDirectories( pDirectories, root ); }
  void GetFiles( vector<string> *pFiles, const string &root, const string &mask, bool recursive ) { GetRootFileSystem()->GetFiles( pFiles, root, mask, recursive ); }
  void GetFilesFromPileOnly( vector<string> *pFiles, const string &root, const string &mask, bool recursive ) { GetRootFileSystem()->GetFiles( pFiles, root, mask, recursive, CombinerFileSystem::CFS_GETFILES_PILEONLY ); }
  Stream* OpenFile( const string &fileName, EFileAccess access, EFileOpen options ) { return GetRootFileSystem()->OpenFile( fileName, access, options ); }
  IFileWatcher *CreateFileWatcher( const string& path )  { return GetRootFileSystem()->CreateFileWatcher( path ); }

  FileSystemChangesProcessor& GetChangesProcessor() { return GetRootFileSystem()->GetChangesProcessor(); }
  void ProcessFileWatchers() { GetRootFileSystem()->GetChangesProcessor().ProcessFileWatchers(); }

  void AddDebugMonitor( IFileSystemDebugMonitor * monitor ) { GetRootFileSystem()->AddDebugMonitor( monitor ); }
  void RemoveDebugMonitor( IFileSystemDebugMonitor * monitor ) { GetRootFileSystem()->RemoveDebugMonitor( monitor ); }

  int GetOpenedFileCount() { return GetRootFileSystem()->GetOpenedFileCount(); }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}; // namespace RootFileSystem
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static bool CmdWatchForFileModifications( const char* name, const vector<wstring>& args )
{
  if ( args.size() != 1)
  {
    systemLog( NLogg::LEVEL_MESSAGE ) << "usage: " << name << " 0 / 1" << endl;
    return true;
  }

  bool enable = NStr::ToInt( args[0] ) == 1;
  RootFileSystem::GetRootFileSystem()->EnableChangesProcessor( enable );
  return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
REGISTER_DEV_CMD( watch_file_modifications, CmdWatchForFileModifications );
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BASIC_REGISTER_CLASS( IFileSystem );
BASIC_REGISTER_CLASS( IFileWatcher );