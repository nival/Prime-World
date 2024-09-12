#ifndef __HTTPDOWNLOADER_H_
#define __HTTPDOWNLOADER_H_

#include <string>
#include <Winhttp.h>
#include "resource.h"

class HTTPDownloader
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

  DownloadStatus DownloadFileIfNeeded(char const *url, wchar_t const *localPath);
  DownloadStatus DownloadFile(char const *url, wchar_t const *localPath);
  DownloadStatus DownloadFile(char const *url, wchar_t const *localPath, wchar_t const *method, int64 *npExpectedContentSize = NULL);
  DownloadStatus DownloadFileHead(char const *url, wchar_t const *localPath, int64 *npExpectedContentSize = NULL);
  void           Reset();

  DownloadStatus GetStatus()       {return status;}
  unsigned       GetContentSize()  {return contentSize;}
  unsigned       GetRecievedSize() {return recievedSize; }

  static std::wstring GetHeaderField(HINTERNET hHandle, unsigned code);
  static byte    *ReadLocalFile(wchar_t const *localPath, int64 *npSize);
  static int64    LocalFileSize(wchar_t const *localPath);
  static UINT     GetStringMessage(DownloadStatus status)    
  {
    assert(IDS_DL_NOTREQUIRED == IDS_DL_NOTACTIVE + (DL_NOTREQUIRED - DL_NOTACTIVE));
    return (int)status - (int)DL_NOTACTIVE + IDS_DL_NOTACTIVE;
  }
  HTTPDownloader();
private:
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
  bool AcceptCertificate(TCHAR const *cpServer, INTERNET_PORT port);
};
#endif //__HTTPDOWNLOADER_H_
