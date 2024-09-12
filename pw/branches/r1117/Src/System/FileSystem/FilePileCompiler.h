#ifndef FILEPILECOMPILER_H_INCLUDED
#define FILEPILECOMPILER_H_INCLUDED

#include "FilePileFormat.h"
#include "SimpleFileList.h"
#include "FsActivityLogReader.h"

namespace fileSystem
{



struct SAutoFile : NonCopyable
{
  FILE * handle;
  SAutoFile( FILE * f ) : handle( f ) {}
  SAutoFile() : handle( 0 ) {}
  ~SAutoFile() { Close(); }
  void Close();
  operator FILE * () const { return handle; }
};



class FilePileCompiler : public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_1( FilePileCompiler, BaseObjectST );

public:
  typedef ni_detail::UInt64 UInt64;

  struct SSettingsFileList
  {
    string                  baseDir;
    Strong<SimpleFileList>  fileList;

    SSettingsFileList():fileList(0) {}
    ~SSettingsFileList() {}
  };

  struct SSettings
  {
    string                                  output;
    vector<string>                          masks;
    vector<string>                          excludeMasks;
    vector<SSettingsFileList>               fileLists;
    fileSystem::ActivityLogReader           filesOrder; //TODO
    vector<string>                          foldersList;
    int                                     minFileSizeToCompress;
    float                                   maxCompressionRatio;
    unsigned                                outputBufferSize; //in MB
    SSettings() : minFileSizeToCompress( 0 ), maxCompressionRatio( 1.0 ), outputBufferSize( 4 ) {}
  };

  struct SStatistics
  {
    int     filesProcessed;
    int     filesCompressed;
    UInt64  totalFilesSize;
    UInt64  totalCompressedFilesSize;
    UInt64  overhead;
    SStatistics() : filesProcessed(), filesCompressed(), totalFilesSize(), totalCompressedFilesSize(), overhead() {}
  };

  FilePileCompiler( const SSettings & _settings );
  ~FilePileCompiler();

  bool Compile();

  const SStatistics & Statistics() const { return statistics; }

private:
  struct SFileInfo
  {
    string    relativeFilename;
    string    fullFilename;
  };

  SSettings                 settings;

  vector<SFileInfo>         files;

  vector<Byte>              outBuffer;
  unsigned                  outBufferLimit;
  SAutoFile                 outFile;
  UInt64                    bytesWritten;

  vector<Byte>              zipBuffer;

  vector<pair<string, SFilePileEntry> >  fileEntries;

  SStatistics               statistics;

  bool CollectFiles();
  void AddFile( const string & baseDir, const string & relativeName );
  void ScanDir( const string & baseDir, const string & relativeFolder );
  bool WeNeedThisFile( const string & name );

  bool WriteFile( const SFileInfo & name );

  bool WriteBytes( const void * data, unsigned size );
  template <class T> bool WriteObject( const T & obj ) { return WriteBytes( &obj, sizeof( obj ) ); }
  bool FlushBuffer();
  static void ScanDirRecursive( vector<string> & files, const string & baseDir, const string & relativeFolder );
};

} //namespace fileSystem

#endif //FILEPILECOMPILER_H_INCLUDED
