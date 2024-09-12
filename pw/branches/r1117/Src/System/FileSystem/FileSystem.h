#ifndef FILESYSTEM_H_2276677A_09DF_42D1
#define FILESYSTEM_H_2276677A_09DF_42D1
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <System/config.h>
#include <System/Stream.h>
#include "FileTime.h"
#include <System/Functor.h>
#include "nvector.h"
#include "nstring.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
enum EFileAccess
{
	FILEACCESS_READ,
	FILEACCESS_WRITE,
	FILEACCESS_READ_WRITE,
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
enum EFileOpen
{
	FILEOPEN_OPEN_EXISTING,
  FILEOPEN_OPEN_ALWAYS,
	FILEOPEN_CREATE_NEW,
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
_interface IFileSystem;
class FileSystemChangesProcessor;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct SFileInfo
{
	CPtr<IFileSystem> pOwner;
	SWin32Time time;

	SFileInfo() : pOwner( 0 ), time( 0 )	{};
	SFileInfo( IFileSystem *_pOwner, SWin32Time _time, int _size ) : pOwner( _pOwner ), time( _time ) {};

	void Clear() { pOwner = 0; time = 0; }
};



//////////////////////////////////////////////////////////////////////////
enum FileReadResultCode
{
  FR_OK = 0,
  FR_NOT_FOUND,
  FR_READ_ERROR,
  FR_CRC_FAIL
};

struct FileReadCallbackContext : public CObjectBase
{
  OBJECT_BASIC_METHODS( FileReadCallbackContext );

public:
  string filename;
  void SetFileName(const string& name) { filename = name; }
};


struct IFileReadCallback : public IObjectBase
{
  virtual void operator () (FileReadResultCode, const string& filename) const = 0;
  //  virtual bool IsEqualTo (IAnimEventCallback const* pOther) const = 0;         
};


class FileReadCallback : public IFileReadCallback, public CObjectBase
{
  OBJECT_BASIC_METHODS( FileReadCallback );
  FileReadCallback() : pCallback(0) {}

public:
  typedef void (*Callback)(FileReadResultCode, FileReadCallbackContext*);
  typedef FileReadCallbackContext Context;
  FileReadCallback(Callback cbk, Context* context) : pCallback(cbk), pContext(context) {}

  void operator () (FileReadResultCode code, const string& filename) const 
  { 
    if ( IsValid(pContext) )
      pContext->SetFileName(filename);
    if ( pCallback )
      pCallback(code, pContext);
  }
private:
  Callback pCallback;
  CObj<Context> pContext;
};

IFileReadCallback* CreateFileReadCallback( FileReadCallback::Callback cbk, FileReadCallback::Context* context );

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
_interface IFileWatcher : public IObjectBase
{	
  typedef list<string> TChangedFileList;

  virtual bool SomethingChanged( TChangedFileList* ) = 0;
  virtual const string& GetPath() const = 0;
};


_interface IFileSystemDebugMonitor;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Interface for file systems
_interface IFileSystem : public IObjectBase
{
	// Gets FileInformation for specified file, check is file exists in this file system
	virtual bool GetFileInfo( SFileInfo* pInfo, const string& fileName ) = 0;
	// Gets the names of subdirectories in a specified directory
	virtual void GetDirectories( vector<string>* pDirectories, const string& root ) = 0;
	// Gets the names of files in a specified directory
	virtual void GetFiles( vector<string> *pFiles, const string& root, const string& mask, bool recursive, int param = 0 ) = 0;
	// Opens specified file
	virtual Stream* OpenFile( const string &fileName, EFileAccess access, EFileOpen options ) = 0;

  // Creates file change watcher for specified folder and its subfolders
  virtual IFileWatcher *CreateFileWatcher( const string& path ) = 0;
  virtual void SetFileReadCallback( IFileReadCallback* cb) = 0;
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
_interface ICombinerFileSystem : public IFileSystem
{
  virtual void RegisterFileSystem( IFileSystem* pFileSystem, IFileReadCallback* callback  = 0  ) = 0;
  virtual void UnregisterFileSystem( IFileSystem* pFileSystem ) = 0;
  virtual void ClearFileSystems() = 0;
  virtual bool SetWriteFileSystem( IFileSystem* pFileSystem ) = 0;

  virtual void EnableChangesProcessor( bool enable ) = 0; 
  virtual FileSystemChangesProcessor& GetChangesProcessor() = 0;

  virtual void AddDebugMonitor( IFileSystemDebugMonitor * monitor ) = 0;
  virtual void RemoveDebugMonitor( IFileSystemDebugMonitor * monitor ) = 0;

  virtual int GetOpenedFileCount() = 0;
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace RootFileSystem
{
  ICombinerFileSystem* GetRootFileSystem();
	bool GetFileInfo( SFileInfo *pInfo, const string &fileName );
	void GetDirectories( vector<string> *pDirectories, const string &root );
	void GetFiles( vector<string> *pFiles, const string &root, const string &mask, bool recursive );
  void GetFilesFromPileOnly( vector<string> *pFiles, const string &root, const string &mask, bool recursive );
	Stream* OpenFile( const string &fileName, EFileAccess access, EFileOpen options );
  IFileWatcher *CreateFileWatcher( const string& path );

	void RegisterFileSystem( IFileSystem* pFileSystem, IFileReadCallback* callback  = 0);
	void UnregisterFileSystem( IFileSystem* pFileSystem );
	void ClearFileSystems();

	bool SetWriteFileSystem( IFileSystem* pFileSystem );

  void ProcessFileWatchers();
  FileSystemChangesProcessor& GetChangesProcessor();

  void AddDebugMonitor( IFileSystemDebugMonitor * monitor );
  void RemoveDebugMonitor( IFileSystemDebugMonitor * monitor );

  int GetOpenedFileCount();
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif //#define FILESYSTEM_H_2276677A_09DF_42D1
