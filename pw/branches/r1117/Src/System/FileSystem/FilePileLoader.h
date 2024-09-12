#ifndef SYSTEM_FILEPILELOADER_H_INCLUDED
#define SYSTEM_FILEPILELOADER_H_INCLUDED

#include "FileSystem.h"
#include "FilePileFormat.h"
#include "System/SyncPrimitives.h"
#include "../StarForce/StarForce.h"
#include "../nvector.h"
#include "../nstring.h"

namespace fileSystem
{

struct FilePileItemInfo
{
  string  name;
  size_t  size;

  FilePileItemInfo( const char * nm, size_t sz ) : 
  name( nm ), size( sz )
  {}

  FilePileItemInfo() :
  size( 0 )
  {}
};



class FilePileLoader : public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_1( FilePileLoader, BaseObjectST );

public:
  FilePileLoader();
  ~FilePileLoader();

  bool Init( const string & fullFilename, IFileReadCallback* cb = 0 );

  bool HasFile( const string & fileName ) const;

  Stream * ReadFile( const string & fileName ) const;

  void FindFiles( vector<string> * fileNames, const string & baseDir, const string & mask, bool recursive ) const;
  void FindFilesWild( vector<FilePileItemInfo> & fileNames, const string & mask ) const;

  int FilesNumber() const { return index.size(); }
  void SetFileReadCallback( IFileReadCallback* cb ) { readCallback = cb; }

private:
  struct SIndexKey
  {
    const char *  pName;

    explicit SIndexKey( const char * name = "" ) : pName( name ) {}
    bool operator == ( const SIndexKey & other ) const
    {
      return ( NStr::ICmp( pName, other.pName ) == 0 );
    }
    operator const char * () const { return pName; }
  };

  struct SIndexKeyHash
  {
    size_t operator () ( const SIndexKey & key ) const
    {
      size_t h = 0;
	    for ( const char * str = key.pName; *str; ++str )
		    h = 5 * h + tolower( *str );
	    return h;
    }
  };

  typedef hash_map<SIndexKey, SFilePileEntry, SIndexKeyHash> TIndex;
  typedef vector<SFilePileEntry> TDiskIndex;
  
  string    packFilename;
  FILE *    file;
  string    filenamesTable;
  TIndex    index;
  threading::Mutex mutex;
  
  bool ReadTail( SFilePileTail & tail );
  bool ReadStringsTable( const SFilePileTail & tail );
  bool ReadFileIndex( const SFilePileTail & tail );

  bool ReadFileBytes( vector<Byte> & bytes, const SFilePileEntry & entry ) const;
  Stream * DecompressFile( const SFilePileEntry & entry, const vector<Byte> & bytes, const char * _debugFilename ) const;
  bool CheckCrc( const SFilePileEntry & entry, const vector<Byte> & bytes, const char * _debugFilename ) const;

  const SFilePileEntry * FindFile( const string & fileName ) const;
  static bool IsSlash( char c ) { return ( c == '/' ) || ( c == '\\' ); }
  static void PrepareFilename( string & result, const string & fileName );

  void OnFileCorruption( const char * _expr, const char * _msg, FileReadResultCode err_code ) const;
  void OnFileOk( ) const;
  
  template<class T>
  static void Decrypt( T *pData, size_t size );
   
  bool BuildInternalIndex( const TDiskIndex &diskIndex );

  mutable CPtr<IFileReadCallback> readCallback;
};

} //namespace fileSystem

#endif //SYSTEM_FILEPILELOADER_H_INCLUDED
