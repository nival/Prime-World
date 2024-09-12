#include <System/FileSystem/FileSystem.h>
#include <zlib.h>
#include <System/Minizip/unzip.h>

class ZipStream : public Stream, public CObjectBase
{
  OBJECT_METHODS( 0x7A4A4B14, ZipStream );
public:
  ZipStream(unzFile _zipFile, const char* path):
  zipFile(_zipFile),
  position(0)
  {
    unzGoToFirstFile(zipFile);
    char buffer[256];
    do 
    {
      unzGetCurrentFileInfo (zipFile, &info, buffer, sizeof(buffer), 0, 0, 0, 0);
      if (strcmp(buffer, path) == 0)
      {
        SetBroken(false);
        SetCanRead(true);
        SetCanWrite(false);
        SetCanSeek(false);
        break;
      }
    } while (unzGoToNextFile(zipFile) == UNZ_OK);
    if (IsOk())
    {
      unzOpenCurrentFile(zipFile);
    }
  }
  ~ZipStream()
  {
    if (IsOk())
    {
      unzCloseCurrentFile(zipFile);
    }
  }
protected:
  virtual void SeekInternal( const int offset ) 
  {

  }
  virtual void SetSizeInternal( const int size ) 
  {

  }

  virtual int ReadInternal( void *pData, const int length ) 
  { 
    int result = unzReadCurrentFile(zipFile, pData, length);
    if (result >= 0)
    {
      position += result;
    }
    return result;
  }
  virtual int WriteInternal( const void *pData, const int length ) { return 0; }

  virtual int GetSize() const { return info.uncompressed_size; }
  virtual int GetPosition() const  { return position; }
  virtual const char *GetBuffer() const  { return 0; }

  virtual void Close()  {} 
private:
  ZipStream() {}
  unzFile zipFile;
  unz_file_info info;
  int position;
};

class ZipFileSystem : public CObjectBase, public IFileSystem
{
  OBJECT_METHODS( 0x1E5B9A21, ZipFileSystem );
public:
  ZipFileSystem(const char* path) 
  {
    zipFile = unzOpen(path);
  }

  ~ZipFileSystem()
  {
    if (zipFile)
    {
      unzClose(zipFile);
    }
  }

  virtual bool GetFileInfo( SFileInfo* pInfo, const string& fileName ) { return false; }
  virtual void GetDirectories( vector<string>* pDirectories, const string& root ) { return; }
  virtual void GetFiles( vector<string> *pFiles, const string& root, const string& mask, bool recursive, int param ) 
  { 
    int count = 0;
    unzGoToFirstFile(zipFile);
    char buffer[256];
    do 
    {
      unz_file_info info;
      unzGetCurrentFileInfo(zipFile, &info, buffer, sizeof(buffer), 0, 0, 0, 0);
      if (pFiles)
      {
        pFiles->push_back(buffer);
        count ++;
      }
    } while (unzGoToNextFile(zipFile) == UNZ_OK);
    return;
  }
  virtual IFileWatcher *CreateFileWatcher( const string& path ) { return 0; }
  //
  virtual Stream* OpenFile( const string &fileName, EFileAccess access, EFileOpen options ) 
  { 
    if (zipFile)
    {
      return new ZipStream(zipFile, fileName.c_str()); 
    }
    return 0;
  }

  virtual void SetFileReadCallback( IFileReadCallback* cb) {}

private:
  ZipFileSystem() {}
  CObj<Stream> mainFile;
  unzFile zipFile;
};
