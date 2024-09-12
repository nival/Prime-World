#ifndef TESTFILESYSTEM_H_E29C29AC_F782_4
#define TESTFILESYSTEM_H_E29C29AC_F782_4

#include "FileSystem.h"
#include "FileSystemChangesProcessor.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class TestFileSystem : public IFileSystem, public CObjectBase
{
public:
  TestFileSystem( const string &root, const bool writable, bool automapRoot = false );

  void SetFileWithContents( const string& fileName, const string& fileData );
  void AssignFileWithFile( const string& fileName, const string& realFileName );
  void ResetUsageCounts();
  int GetUsageCount( const string& fileName );

  // IFileSystem
  virtual bool GetFileInfo( SFileInfo *info, const string &fileName );
  virtual void GetDirectories( vector<string> *pDirectories, const string &root );
  virtual void GetFiles( vector<string> *pFiles, const string &root, const string &mask, bool recursive, int param );
  virtual Stream *OpenFile( const string &fileName, EFileAccess access, EFileOpen options );
  virtual IFileWatcher *CreateFileWatcher( const string& path );
  virtual void SetFileReadCallback( IFileReadCallback* cb) {}

private:
  OBJECT_BASIC_METHODS( TestFileSystem );
  TestFileSystem() : writable ( false ) {}

  typedef hash_map<string, CObj<Stream> > TFiles;
  typedef hash_map<string, int > TUsageCount;
  string fileSystemRoot;
  bool writable;
  TFiles files;
  bool automapRoot;
  TUsageCount usageCounts;
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif //#define TESTFILESYSTEM_H_E29C29AC_F782_4
