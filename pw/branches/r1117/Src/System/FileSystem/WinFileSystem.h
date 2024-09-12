#ifndef WINFILESYSTEM_H_4175FD63_E274_4C
#define WINFILESYSTEM_H_4175FD63_E274_4C

#include "FileSystem.h"
#include "FileSystemChangesProcessor.h"



class WinFileSystem : public IFileSystem, public CObjectBase
{
  OBJECT_BASIC_METHODS( WinFileSystem );

public:
  WinFileSystem( const string &root, const bool writable );

  virtual bool GetFileInfo( SFileInfo *info, const string &fileName );
  virtual void GetDirectories( vector<string> *pDirectories, const string &root );
  virtual void GetFiles( vector<string> *pFiles, const string &root, const string & mask, bool recursive, int param = 0 );
  virtual Stream *OpenFile( const string &fileName, EFileAccess access, EFileOpen options );
  virtual IFileWatcher *CreateFileWatcher( const string& path );
  virtual void SetFileReadCallback( IFileReadCallback* ) {  }

private:
  string fileSystemRoot;
  bool writable;

  WinFileSystem() : writable ( false ) {}

  void GetFilesInternal( vector<string> *pFiles, const string &root, const string & relativeFolder, const string & mask, bool recursive );
};

#endif //#define WINFILESYSTEM_H_4175FD63_E274_4C
