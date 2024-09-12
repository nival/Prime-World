#ifndef __HTTPDOWNLOADER_H_
#define __HTTPDOWNLOADER_H_

#include <string>
#include <Winhttp.h>

namespace NFile
{

template <typename T>
void CreateDirectory(const T* Path, bool ignoreFilename)
{
  T DirName[MAX_PATH];
  const T* p = Path;
  T* q = DirName; 
  while(*p)
  {
    if ((L'\\' == *p) || (L'/' == *p))
    {
      if (L':' != *(p-1))
      {
        ::CreateDirectoryW(DirName, NULL);
      }
    }
    *q++ = *p++;
    *q = L'\0';
  }
  if (!ignoreFilename)
  {
    ::CreateDirectoryW(DirName, NULL);
  }
}

} // NFile


class HTTPDownloaderService
{
public:
  enum DownloadStatus
  {
    DL_NOTACTIVE,     // means not started
    DL_CONNECTING,
    DL_CONNECTED,
    DL_RECIEVING  ,
    DL_NOTFOUND,   // means error 404
    DL_COULDNOTCONNECT,
    DL_ERROR, //just random error
    DL_COULDNOTOPENFILE,
    DL_OUTOFMEMORY,
    DL_COMPLETED,   //means OK
    DL_NOTREQUIRED, // means OK
  };

  DownloadStatus DownloadFileIfNeeded(char const *url, wchar_t const *localPath, threading::Event* event=0);
  DownloadStatus DownloadFile(char const *url, wchar_t const *localPath, threading::Event* event=0);
  void           Reset();

  DownloadStatus GetStatus() const { return status;}
  unsigned       GetContentSize() const {return contentSize;}
  unsigned       GetRecievedSize() const {return recievedSize; }

  HTTPDownloaderService();
private:
  DownloadStatus DownloadFile(char const *url, wchar_t const *localPath, wchar_t const *method, int64 *npExpectedContentSize = NULL);
  DownloadStatus DownloadFileHead(char const *url, wchar_t const *localPath, int64 *npExpectedContentSize = NULL);
  static std::wstring GetHeaderField(HINTERNET hHandle, unsigned code);
  static byte    *ReadLocalFile(wchar_t const *localPath, int64 *npSize);
  static int64    LocalFileSize(wchar_t const *localPath);

  DownloadStatus status;
  unsigned       contentSize;
  unsigned       recievedSize; 

  HINTERNET  hSession;
  HINTERNET  hConnect;
  HINTERNET  hRequest;
  HANDLE     hFile;
  LPBYTE     pBuffer;

  bool DownloadFileStart(char const *url, wchar_t const *localPath, wchar_t const *method);
  bool DownloadFileReceive();
  void DownloadFileFinalize();
  bool AcceptCertificate(wchar_t const *cpServer, INTERNET_PORT port);
};
#endif //__HTTPDOWNLOADER_H_
