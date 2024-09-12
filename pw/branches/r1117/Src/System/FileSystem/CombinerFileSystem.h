#ifndef ROOTFILESYSTEM_H_8DF1AF7F_7F73_4
#define ROOTFILESYSTEM_H_8DF1AF7F_7F73_4

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "FileSystemChangesProcessor.h"
#include "FileSystemDebugMonitor.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CombinerFileSystemWatcher;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CombinerFileSystem : public ICombinerFileSystem, public CObjectBase
{
public:
  enum { CFS_GETFILES_PILEONLY = 1 };

  CombinerFileSystem();

  // IFileSystem
  virtual bool GetFileInfo( SFileInfo *pInfo, const string &fileName );
  virtual void GetDirectories( vector<string> *pDirectories, const string &root );
  virtual void GetFiles( vector<string> *pFiles, const string &root, const string &mask, bool recursive, int param = 0 );
  virtual Stream *OpenFile( const string &fileName, EFileAccess access, EFileOpen options );
  virtual IFileWatcher *CreateFileWatcher( const string& path );

  //ICombinerFileSystem
  virtual void RegisterFileSystem( IFileSystem* pFileSystem, IFileReadCallback* fileReadCallback );
  virtual void UnregisterFileSystem( IFileSystem* pFileSystem );
  virtual void ClearFileSystems();
  virtual bool SetWriteFileSystem( IFileSystem* pFileSystem );
  virtual void EnableChangesProcessor( bool enable ); 
  virtual FileSystemChangesProcessor& GetChangesProcessor() { return changesProcessor; }
  virtual void AddDebugMonitor( IFileSystemDebugMonitor * monitor ) { debugMonitors.insert( monitor ); }
  virtual void RemoveDebugMonitor( IFileSystemDebugMonitor * monitor ) { debugMonitors.erase( monitor ); }
  virtual void SetFileReadCallback( IFileReadCallback*  ) { }

  virtual int GetOpenedFileCount();

private:
  typedef vector<CObj<IFileSystem> > TFileSystems;

  TFileSystems fileSystems;
  CObj<IFileSystem> pWriteFileSystem;

  CObj<CombinerFileSystemWatcher> pFileWatcher;
  FileSystemChangesProcessor changesProcessor;

  typedef set<CObj<IFileSystemDebugMonitor> >  TDebugMonitors;
  TDebugMonitors debugMonitors;

  typedef map<string, CPtr<Stream> > TOpenedStreams;
  TOpenedStreams openedStreams;

  OBJECT_BASIC_METHODS( CombinerFileSystem )
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CombinerFileSystemWatcher : public IFileWatcher, public CObjectBase
{	
public:
  CombinerFileSystemWatcher( const string& path )
    : path( path ) 
  {}

  void AddWatcher( IFileWatcher* watcher );
  void RemoveWatcher( IFileWatcher* watcher );

  virtual bool SomethingChanged( IFileWatcher::TChangedFileList* pFileList );
  virtual const string& GetPath() const { return path; }

private:
  string path;
  list<CObj<IFileWatcher> > watchers;

  CombinerFileSystemWatcher() {}
  OBJECT_BASIC_METHODS( CombinerFileSystemWatcher );
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif //#define ROOTFILESYSTEM_H_8DF1AF7F_7F73_4
