#include <windows.h>
#include <windowsx.h>
#include <ATLCONV.h>
#include <ATLCOmcli.h>
#include <shlobj.h>
#include <Shlwapi.h>
#include <Winhttp.h>
#include <Wincrypt.h>
#pragma comment(lib, "shlwapi.lib")
#pragma comment(lib, "Winhttp.lib")
#pragma comment(lib, "Crypt32.lib")
#pragma warning(disable: 4996)
#pragma warning(disable: 4245)
#pragma warning(disable: 4805)
#include <string>
#include "HTTPDownloaderService.h"


HTTPDownloaderService::HTTPDownloaderService()
{
  Reset();
}

void HTTPDownloaderService::Reset()
{
  status       = DL_NOTACTIVE;
  contentSize  = 0;
  recievedSize = 0;
}

byte *HTTPDownloaderService::ReadLocalFile(wchar_t const *localPath, int64 *npSize)
{
  HANDLE hFile = CreateFileW(localPath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL); 
  if(INVALID_HANDLE_VALUE == hFile)
    return NULL;
  *npSize = GetFileSize(hFile, NULL);
  byte *pRet = new byte[(unsigned int)*npSize];
  DWORD nRead;
  ReadFile(hFile, pRet, (DWORD)*npSize, &nRead, NULL);
  if(INVALID_HANDLE_VALUE != hFile) CloseHandle(hFile);
  return pRet;
}

int64 HTTPDownloaderService::LocalFileSize(wchar_t const *localPath)
{
  int64 nSize = 0;
  HANDLE hFile = CreateFileW(localPath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL); 
  if(INVALID_HANDLE_VALUE == hFile)
    return nSize;
  nSize = GetFileSize(hFile, NULL);
  if(INVALID_HANDLE_VALUE != hFile) CloseHandle(hFile);
  return nSize;
}

std::wstring HTTPDownloaderService::GetHeaderField(HINTERNET hRequest, unsigned code)
{
  DWORD headerIndex  = 0;
  DWORD bufferLength = 0;
  DWORD nextIndex    = 0;
  byte *pBuffer = NULL;
  std::wstring retStr(L"");
  do 
  {
    headerIndex = nextIndex;
    bufferLength = 0;                   
    nextIndex = headerIndex;
    WinHttpQueryHeaders(hRequest, code, NULL, WINHTTP_NO_OUTPUT_BUFFER, &bufferLength, &nextIndex);
    if(headerIndex != ERROR_WINHTTP_HEADER_NOT_FOUND && bufferLength > 0)
    {
      pBuffer = new byte[bufferLength + 1]; 
      pBuffer[bufferLength] = 0;
      nextIndex = headerIndex;
      WinHttpQueryHeaders(hRequest, code, NULL, pBuffer, &bufferLength, &nextIndex);
      retStr.append((WCHAR *)pBuffer, bufferLength / sizeof(WCHAR));
      if(pBuffer) delete [] pBuffer; 
      pBuffer = NULL;
    }
  }while(ERROR_WINHTTP_HEADER_NOT_FOUND != nextIndex && bufferLength > 0 && nextIndex != headerIndex);
  return retStr;
}

PCCERT_CONTEXT FindCertWithOUNITName()
{
  //This function performs a certificate context search
  //by the organizational unit name of the issuer
  //Take this function as a sample for your possible different search functions
  PCCERT_CONTEXT pCertContext = NULL;		
  CERT_RDN certRDN;

  certRDN.cRDNAttr = 1;
  certRDN.rgRDNAttr = new CERT_RDN_ATTR;
  certRDN.rgRDNAttr->pszObjId = szOID_ORGANIZATIONAL_UNIT_NAME;
  certRDN.rgRDNAttr->dwValueType = CERT_RDN_ANY_TYPE;
  certRDN.rgRDNAttr->Value.pbData = (BYTE *) NULL;
  certRDN.rgRDNAttr->Value.cbData = 0;

  //pCertContext = CertFindCertificateInStore(m_hStore,  X509_ASN_ENCODING | PKCS_7_ASN_ENCODING,   0, CERT_FIND_ISSUER_ATTR, &certRDN, NULL);
  delete certRDN.rgRDNAttr;
  return pCertContext;
}
struct AutoEventSet
{
  AutoEventSet(threading::Event* _event):
event(_event)
{
}

~AutoEventSet()
{
  if (event)
  {
    event->Set();
  }
}

threading::Event* event;

};


HTTPDownloaderService::DownloadStatus HTTPDownloaderService::DownloadFileIfNeeded(char const *url, wchar_t const *localPath, threading::Event* event)
{
  AutoEventSet autoEvent(event);
  if(!PathIsURLA(url))
    return DL_NOTREQUIRED;
  std::wstring headPath(localPath);
  headPath += L".head";
  byte *cpOldHead = NULL;
  int64 fileSize = 0;
  bool  bCacheOutdated = true;
  if(PathFileExistsW(headPath.c_str()))
  {
    cpOldHead = ReadLocalFile(headPath.c_str(), &fileSize);
  }
  int64 nExpectedSize = 0;
  DownloadStatus headStat = DownloadFileHead(url, headPath.c_str(), &nExpectedSize);
  if(DL_COMPLETED != headStat)
  {
    if (cpOldHead) delete [] cpOldHead;
    return headStat;
  }
  if(cpOldHead != NULL)
  {
    int64 newSize = 0;
    byte *cpNewHead = ReadLocalFile(headPath.c_str(), &newSize);
    bCacheOutdated = (newSize != fileSize) || (0 != memcmp(cpOldHead, cpNewHead, (size_t)min(fileSize, newSize)));
    if (cpNewHead) delete [] cpNewHead;
  }

  if (cpOldHead) delete [] cpOldHead;

  if(bCacheOutdated || !PathFileExistsW(localPath) || LocalFileSize(localPath) != nExpectedSize)
  {
    DownloadStatus fileStat = DownloadFile(url, localPath);
    return fileStat;
  }
  else
  {
    return DL_NOTREQUIRED;
  }

}
HTTPDownloaderService::DownloadStatus HTTPDownloaderService::DownloadFile(char const *url, wchar_t const *localPath, threading::Event* event)
{
  AutoEventSet autoEvent(event);
  return DownloadFile(url, localPath, L"GET");
}

HTTPDownloaderService::DownloadStatus HTTPDownloaderService::DownloadFile(char const *url, wchar_t const *localPath, wchar_t const *method, int64 *npExpectedContentSize)
{
  if(!DownloadFileStart(url, localPath, method))
    return status;

  std::wstring sHeader = GetHeaderField(hRequest, WINHTTP_QUERY_STATUS_CODE);
  int nHTTPStatus = _wtoi(sHeader.c_str());
  if(nHTTPStatus == HTTP_STATUS_MOVED || nHTTPStatus == HTTP_STATUS_REDIRECT)
  {
    USES_CONVERSION;
    std::wstring sNewURL = GetHeaderField(hRequest, WINHTTP_QUERY_CONTENT_LOCATION);
    DownloadFileFinalize();
    return DownloadFile(W2A(sNewURL.c_str()), localPath, method);
  }
  if(nHTTPStatus == HTTP_STATUS_NOT_FOUND)
  {
    DownloadFileFinalize();
    status = DL_NOTFOUND;
    return status;
  }
  if(nHTTPStatus != HTTP_STATUS_OK)
  {
    DownloadFileFinalize();
    status = DL_ERROR;
    return status;
  }

  //check for header
  if(_wcsicmp(method, L"HEAD") == 0)
  {
    std::wstring sHeader = GetHeaderField(hRequest, WINHTTP_QUERY_ETAG);
    if(npExpectedContentSize)
      *npExpectedContentSize = _wtoi64(GetHeaderField(hRequest, WINHTTP_QUERY_CONTENT_LENGTH).c_str());
    DWORD wmWritten;
    /*BOOL fr = */WriteFile(hFile, sHeader.c_str(), sHeader.length() * sizeof(WCHAR), &wmWritten, NULL);
    DownloadFileFinalize();
    status = DL_COMPLETED;
    return status;
  }
  else
  {
    contentSize = _wtoi(GetHeaderField(hRequest, WINHTTP_QUERY_CONTENT_LENGTH).c_str());
    if(npExpectedContentSize)
      *npExpectedContentSize = contentSize;
    recievedSize = 0;
    DownloadFileReceive();
  }
  DownloadFileFinalize();
  return status;
}


bool HTTPDownloaderService::AcceptCertificate(wchar_t const *cpServer, INTERNET_PORT port)
{
  DWORD dwFlags = SECURITY_FLAG_IGNORE_CERT_CN_INVALID| SECURITY_FLAG_IGNORE_CERT_DATE_INVALID | SECURITY_FLAG_IGNORE_UNKNOWN_CA;

  // open a session handle
  HINTERNET hSession = WinHttpOpen( L"Nival download/1.0", WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0 );

  // connect to a web server
  HINTERNET hConnect = WinHttpConnect( hSession, cpServer, port, 0 );

  // open a request handle
  HINTERNET hRequest = WinHttpOpenRequest( hConnect, L"GET",  L"", NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, WINHTTP_FLAG_SECURE ); 

  // important - set security to ignore 'bad' certs
  BOOL bRet = WinHttpSetOption( hRequest, WINHTTP_OPTION_SECURITY_FLAGS, &dwFlags, sizeof(DWORD) );

  // send the request
  bRet = WinHttpSendRequest( hRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0, WINHTTP_NO_REQUEST_DATA,  0,  0,  0 );

  if(bRet)
  {
    // get a handle on the certificate
    PCCERT_CONTEXT pCert = NULL;
    DWORD dwLen = sizeof(pCert);
    bRet = WinHttpQueryOption( hRequest, WINHTTP_OPTION_SERVER_CERT_CONTEXT, &pCert, &dwLen );
    if(pCert != NULL)
    {
      // open a certificate store
      HCERTSTORE hCertStore = CertOpenStore( CERT_STORE_PROV_SYSTEM, 0, 0, CERT_STORE_OPEN_EXISTING_FLAG | CERT_SYSTEM_STORE_LOCAL_MACHINE,  L"Root"); 

      // add the certificate
      bRet =  CertAddCertificateContextToStore( hCertStore, pCert, CERT_STORE_ADD_REPLACE_EXISTING,  NULL );
      WinHttpSetOption( this->hRequest, WINHTTP_OPTION_CLIENT_CERT_CONTEXT, (LPVOID) pCert, sizeof(CERT_CONTEXT) );

      // release the certificate
      CertFreeCertificateContext(pCert);

      // close the store
      bRet = CertCloseStore( hCertStore, 0 );
    }
  }
  WinHttpCloseHandle(hRequest);
  WinHttpCloseHandle(hConnect);
  WinHttpCloseHandle(hSession);
  return true;
}

bool HTTPDownloaderService::DownloadFileStart(char const *url, wchar_t const *localPath, wchar_t const *method)
{
  USES_CONVERSION;
  BOOL  bResults = FALSE;

  //init
  hFile = INVALID_HANDLE_VALUE;
  hSession = NULL;
  hConnect = NULL;
  hRequest = NULL;
  pBuffer  = NULL;

  status = DL_CONNECTING;

  URL_COMPONENTS urlComp;
  // Initialize the URL_COMPONENTS structure.
  ZeroMemory(&urlComp, sizeof(urlComp));
  urlComp.dwStructSize = sizeof(urlComp);
  urlComp.dwSchemeLength    = -1;
  urlComp.dwHostNameLength  = -1;
  urlComp.dwUrlPathLength   = -1;
  urlComp.dwExtraInfoLength = -1;
  urlComp.nPort             = INTERNET_DEFAULT_HTTP_PORT;

  WinHttpCrackUrl(A2W(url), wcslen(A2W(url)), 0, &urlComp);
  
  // Use WinHttpOpen to obtain a session handle.
  hSession = WinHttpOpen( L"Nival download/1.0", WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);
  // Specify an HTTP server.
  if (hSession)    
  {
    std::wstring server(urlComp.lpszHostName, urlComp.dwHostNameLength);
    hConnect = WinHttpConnect( hSession, server.c_str(), urlComp.nPort, 0);
  }
  // Create an HTTP request handle.
  if (hConnect)    
  {
    std::wstring path(urlComp.lpszUrlPath, urlComp.dwUrlPathLength);
    bool bSecure = ((urlComp.dwSchemeLength == 5) && (_wcsnicmp(urlComp.lpszScheme, L"HTTPS", 5) == 0));
    hRequest = WinHttpOpenRequest( hConnect, method, path.c_str(), NULL, WINHTTP_NO_REFERER, NULL, (bSecure)?WINHTTP_FLAG_SECURE:NULL);
    if(hRequest != NULL && bSecure)
    {
      DWORD dwFlags = SECURITY_FLAG_IGNORE_CERT_CN_INVALID| SECURITY_FLAG_IGNORE_CERT_DATE_INVALID | SECURITY_FLAG_IGNORE_UNKNOWN_CA | SECURITY_FLAG_IGNORE_CERT_WRONG_USAGE;
      WinHttpSetOption( hRequest, WINHTTP_OPTION_SECURITY_FLAGS, &dwFlags, sizeof(DWORD) );
      WinHttpSetOption( this->hRequest, WINHTTP_OPTION_CLIENT_CERT_CONTEXT, WINHTTP_NO_CLIENT_CERT_CONTEXT, 0 );
      //std::wstring server(urlComp.lpszHostName, urlComp.dwHostNameLength);
      //AcceptCertificate(server.c_str(), urlComp.nPort);
    }
  }
  
  // Send a request.
  if (hRequest)    
  {
    bResults = WinHttpSendRequest( hRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0, WINHTTP_NO_REQUEST_DATA, 0, 0, 0);
    if(!bResults && GetLastError() == ERROR_WINHTTP_CLIENT_AUTH_CERT_NEEDED)
    {
      WinHttpSetOption( this->hRequest, WINHTTP_OPTION_CLIENT_CERT_CONTEXT, WINHTTP_NO_CLIENT_CERT_CONTEXT, 0 );
    }
  }
  // End the request.
  if (bResults)    
  {
    status = DL_CONNECTED;
    bResults = WinHttpReceiveResponse( hRequest, NULL );

    if(!bResults)
    {
      _tprintf(_T("WinHttpReceiveResponse failed with %d"), GetLastError());
    }
  }
  else
  {
    status = DL_COULDNOTCONNECT;
    DownloadFileFinalize();
    return (bResults == TRUE);
  }

  // Keep checking for data until there is nothing left.
  if (bResults) 
  {
    NFile::CreateDirectory(localPath, true);
    hFile = CreateFileW(localPath, GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL); 
    if(hFile == INVALID_HANDLE_VALUE)
    {
      status = DL_COULDNOTOPENFILE;
      DownloadFileFinalize();
      return (bResults == TRUE);
    }
  }
  else
  {
    DownloadFileFinalize();
  }
  return (bResults == TRUE);
}

bool HTTPDownloaderService::DownloadFileReceive()
{
  DWORD dwSize;
  DWORD dwDownloaded;
  status = DL_RECIEVING;
  recievedSize = 0;
  do     
  {        
    // Check for available data.        
    dwSize = 0;        
    if (!WinHttpQueryDataAvailable( hRequest, &dwSize))
    {
      //to browser console
      printf( "Error %u in WinHttpQueryDataAvailable.\n", GetLastError());        
      status = DL_ERROR;
      return false;
    }
    // Allocate space for the buffer.        
    pBuffer = new byte[dwSize + 1];        
    if (!pBuffer)        
    {            
      //to browser console
      printf("Out of memory\n");            
      dwSize = 0;
      status = DL_OUTOFMEMORY;
      return false;
    }        
    else        
    {            
      // Read the Data.            
      ZeroMemory(pBuffer, dwSize + 1);            
      if (!WinHttpReadData( hRequest, (LPVOID)pBuffer, dwSize, &dwDownloaded))                
      {                
        printf( "Error %u in WinHttpReadData.\n", GetLastError());
        status = DL_ERROR;
        return false;
      }            
      else                
      {              
        recievedSize += dwDownloaded;
        DWORD wmWritten;
        BOOL fr = WriteFile(hFile, pBuffer, dwDownloaded, &wmWritten, NULL);
        UNREFERENCED_PARAMETER(fr);
        int n = GetLastError();              
        UNREFERENCED_PARAMETER(n);
      }            
      // Free the memory allocated to the buffer.            
      delete [] pBuffer;        
      pBuffer = NULL;
    }    
  } while (dwSize > 0);
  status = DL_COMPLETED;
  return true;
}

void HTTPDownloaderService::DownloadFileFinalize()
{
  if(pBuffer) 
  {
    delete [] pBuffer; 
    pBuffer = NULL;
  }       
  if(INVALID_HANDLE_VALUE != hFile)
  {
    //truncate file if we wrote something useful into it
    if(0 != SetFilePointer(hFile, 0, NULL, FILE_CURRENT))
    {
      SetEndOfFile(hFile);
    }
    CloseHandle(hFile);
    hFile = INVALID_HANDLE_VALUE;
  }
  // Close any open handles.
  if (hRequest) {WinHttpCloseHandle(hRequest); hRequest = NULL;}
  if (hConnect) {WinHttpCloseHandle(hConnect); hConnect = NULL;}
  if (hSession) {WinHttpCloseHandle(hSession); hSession = NULL;}
}

HTTPDownloaderService::DownloadStatus HTTPDownloaderService::DownloadFileHead(char const *url, wchar_t const *localPath, int64 *npExpectedContentSize)
{
  return DownloadFile(url, localPath, L"HEAD", npExpectedContentSize);
}

