/************************************************************************************* 
This file is a part of CrashRpt library.
Copyright (c) 2003-2013 The CrashRpt project authors. All Rights Reserved.

Use of this source code is governed by a BSD-style license
that can be found in the License.txt file in the root of the source
tree. All contributing project authors may
be found in the Authors.txt file in the root of the source tree.
***************************************************************************************/

#include "stdafx.h"
#include "HttpRequestSender.h"
#include "base64.h"
#include "md5.h"
#include "Utility.h"
#include "strconv.h"

#ifndef MIN
#define MIN(a,b) ((a)<(b)?(a):(b))
#endif

// Constructor
CHttpRequestSender::CHttpRequestSender()
{
    // Init variables
    m_sBoundary = _T("AaB03x5fs1045fcc7");

    m_sTextPartHeaderFmt = _T("--%s\r\nContent-disposition: form-data; name=\"%s\"\r\n\r\n");
    m_sTextPartFooterFmt = _T("\r\n");   
    m_sFilePartHeaderFmt = _T("--%s\r\nContent-disposition: form-data; name=\"%s\"; filename=\"%s\"\r\nContent-Type: %s\r\nContent-Transfer-Encoding: binary\r\n\r\n");
    m_sFilePartFooterFmt = _T("\r\n");  
}

// Sends HTTP request assyncronously (in a working thread)
BOOL CHttpRequestSender::SendAssync(CHttpRequest& Request, AssyncNotification* an)
{
    // Copy parameters
    m_Request = Request;
    m_Assync = an;

    // Create worker thread
    HANDLE hThread = CreateThread(NULL, 0, WorkerThread, (void*)this, 0, NULL);
    if(hThread==NULL)
        return FALSE;

    return TRUE;
}

// Thread procedure.
DWORD WINAPI CHttpRequestSender::WorkerThread(VOID* pParam)
{
    CHttpRequestSender* pSender = (CHttpRequestSender*)pParam;
    // Delegate further actions to CHttpRequestSender class
    pSender->InternalSend();  

    return 0;
}

// Sends HTTP request and checks response
BOOL CHttpRequestSender::InternalSend()
{ 
    BOOL bStatus = FALSE;      // Resulting status
    strconv_t strconv;         // String conversion
    HINTERNET hSession = NULL; // Internet session
    HINTERNET hConnect = NULL; // Internet connection
    HINTERNET hRequest = NULL; // Handle to HTTP request
    TCHAR szProtocol[512];     // Protocol
    TCHAR szServer[512];       // Server name
    TCHAR szURI[1024];         // URI
    DWORD dwPort=0;            // Port
    CString sHeaders = _T("Content-type: multipart/form-data; boundary=") + m_sBoundary;
    LPCTSTR szAccept[2]={_T("*/*"), NULL};
    INTERNET_BUFFERS BufferIn;
    BYTE pBuffer[4096] = {0};
    BOOL bRet = FALSE;
    DWORD dwBuffSize = 0;
    CString sMsg;
    LONGLONG lPostSize = 0;  
    std::map<CString, std::string>::iterator it;
    std::map<CString, CHttpRequestFile>::iterator it2;

    // Calculate size of data to send
    m_Assync->SetProgress(_T("Calculating size of data to send."), 0);
    bRet = CalcRequestSize(lPostSize);
    if(!bRet)
    {
        m_Assync->SetProgress(_T("Error calculating size of data to send!"), 0);
        goto cleanup;
    }

    // Create Internet session
    m_Assync->SetProgress(_T("Opening Internet connection."), 0);
    hSession = InternetOpen(_T("CrashRpt"), INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
    if(hSession==NULL)
    {
        m_Assync->SetProgress(_T("Error opening Internet session"), 0);
        goto cleanup; 
    }

    // Parse application-provided URL
    ParseURL(m_Request.m_sUrl, szProtocol, 512, szServer, 512, dwPort, szURI, 1024);

    // Connect to HTTP server
    m_Assync->SetProgress(_T("Connecting to server"), 0, true);

    hConnect = InternetConnect(
        hSession,     // InternetOpen handle
        szServer,     // Server  name
        (WORD)dwPort, // Default HTTPS port - 443
        NULL,         // User name
        NULL,         //  User password
        INTERNET_SERVICE_HTTP, // Service
        0,            // Flags
        0             // Context
        );
    if(hConnect==NULL)
    {
        DWORD dwError = GetLastError();
        CString sMsg;
        sMsg.Format(_T("Error connecting to server (code 0x%08x): %s"), dwError, Utility::FormatErrorMsg(dwError));
        m_Assync->SetProgress(sMsg, 0);
        goto cleanup; 
    }
	
	// Set large receive timeout to avoid problems in case of 
	// slow upload => slow response from the server.
	DWORD dwReceiveTimeout = 0;
	InternetSetOption(hConnect, INTERNET_OPTION_RECEIVE_TIMEOUT, 
		&dwReceiveTimeout, sizeof(dwReceiveTimeout));

    // Check if canceled
    if(m_Assync->IsCancelled()){ goto cleanup; }

    // Add a message to log
    m_Assync->SetProgress(_T("Opening HTTP request..."), 0, true);

    // Configure flags for HttpOpenRequest
    DWORD dwFlags = INTERNET_FLAG_NO_CACHE_WRITE | INTERNET_FLAG_NO_AUTO_REDIRECT;
    if(dwPort==INTERNET_DEFAULT_HTTPS_PORT)
	    dwFlags |= INTERNET_FLAG_SECURE; // Use SSL
	
	BOOL bRedirect = FALSE;
	int nCount = 0;
	while(nCount==0 || bRedirect)
	{
		nCount++;

		// Open HTTP request
		hRequest = HttpOpenRequest(
			hConnect, 
			_T("POST"), 
			szURI, 
			NULL, 
			NULL, 
			szAccept, 
			dwFlags, 
			0
			);
		if (!hRequest)
		{
			//m_Assync->SetProgress(_T("HttpOpenRequest has failed."), 0, true);
      
      DWORD dwError = GetLastError();
      CString sMsg;
      sMsg.Format(_T("HttpOpenRequest has failed (code 0x%08x): %s"), dwError, Utility::FormatErrorMsg(dwError));
      m_Assync->SetProgress(sMsg, 0, true);

			goto cleanup;
		}

		// This code was copied from http://support.microsoft.com/kb/182888 to address the problem
		// that MVS doesn't have a valid SSL certificate.
		DWORD extraSSLDwFlags = 0;
		DWORD dwBuffLen = sizeof(extraSSLDwFlags);
		InternetQueryOption (hRequest, INTERNET_OPTION_SECURITY_FLAGS,
		(LPVOID)&extraSSLDwFlags, &dwBuffLen);
		// We have to specifically ignore these 2 errors for MVS	
		extraSSLDwFlags |= SECURITY_FLAG_IGNORE_REVOCATION |  // Ignores certificate revocation problems.
						   SECURITY_FLAG_IGNORE_WRONG_USAGE | // Ignores incorrect usage problems.
						   SECURITY_FLAG_IGNORE_CERT_CN_INVALID | // Ignores the ERROR_INTERNET_SEC_CERT_CN_INVALID error message.
						   SECURITY_FLAG_IGNORE_CERT_DATE_INVALID; // Ignores the ERROR_INTERNET_SEC_CERT_DATE_INVALID error message.
		InternetSetOption (hRequest, INTERNET_OPTION_SECURITY_FLAGS,
							&extraSSLDwFlags, sizeof (extraSSLDwFlags) );

		// Fill in buffer
		BufferIn.dwStructSize = sizeof( INTERNET_BUFFERS ); // Must be set or error will occur
		BufferIn.Next = NULL; 
		BufferIn.lpcszHeader = sHeaders;
		BufferIn.dwHeadersLength = sHeaders.GetLength();
		BufferIn.dwHeadersTotal = 0;
		BufferIn.lpvBuffer = NULL;                
		BufferIn.dwBufferLength = 0;
		BufferIn.dwBufferTotal = (DWORD)lPostSize; // This is the only member used other than dwStructSize
		BufferIn.dwOffsetLow = 0;
		BufferIn.dwOffsetHigh = 0;

		m_dwPostSize = (DWORD)lPostSize;
		m_dwUploaded = 0;

		// Add a message to log
		m_Assync->SetProgress(_T("Sending HTTP request..."), 0);
		// Send request
		if(!HttpSendRequestEx( hRequest, &BufferIn, NULL, 0, 0))
		{

			//m_Assync->SetProgress(_T("HttpSendRequestEx has failed."), 0);

      DWORD dwError = GetLastError();
      CString sMsg;
      sMsg.Format(_T("HttpSendRequestEx has failed (code 0x%08x): %s"), dwError, Utility::FormatErrorMsg(dwError));
      m_Assync->SetProgress(sMsg, 0);
			goto cleanup;
		}

		// Write text fields
		for(it=m_Request.m_aTextFields.begin(); it!=m_Request.m_aTextFields.end(); it++)
		{
			bRet = WriteTextPart(hRequest, it->first); 
			if(!bRet)
				goto cleanup;
		}

		// Write attachments
		for(it2=m_Request.m_aIncludedFiles.begin(); it2!=m_Request.m_aIncludedFiles.end(); it2++)
		{
			bRet = WriteAttachmentPart(hRequest, it2->first); 
			if(!bRet)
				goto cleanup;
		}

		// Write boundary
		bRet = WriteTrailingBoundary(hRequest);
		if(!bRet)
			goto cleanup;

		// Add a message to log
		m_Assync->SetProgress(_T("Ending HTTP request..."), 0);

		// End request
		if(!HttpEndRequest(hRequest, NULL, 0, 0))
		{
			//m_Assync->SetProgress(_T("HttpEndRequest has failed."), 0);
      DWORD dwError = GetLastError();
      CString sMsg;
      sMsg.Format(_T("HttpEndRequest has failed (code 0x%08x): %s"), dwError, Utility::FormatErrorMsg(dwError));
      m_Assync->SetProgress(sMsg, 0);
			goto cleanup;
		}

		// Add a message to log
		m_Assync->SetProgress(_T("Reading server response..."), 0);
	
		// Get HTTP response code from HTTP headers
		DWORD lHttpStatus = 0;
		DWORD lHttpStatusSize = sizeof(lHttpStatus);
		BOOL bQueryInfo = HttpQueryInfo(hRequest, HTTP_QUERY_STATUS_CODE|HTTP_QUERY_FLAG_NUMBER, 
										&lHttpStatus, &lHttpStatusSize, 0);
	
		if(bQueryInfo)
		{
			sMsg.Format(_T("Server response code: %ld"), lHttpStatus);
			m_Assync->SetProgress(sMsg, 0);
		}

		// Read HTTP response
		/*InternetReadFile(hRequest, pBuffer, 4095, &dwBuffSize);
		pBuffer[dwBuffSize] = 0;
		sMsg = CString((LPCSTR)pBuffer, dwBuffSize);
*/
    sMsg.Empty();
    while( true )
    {
      if ( !InternetReadFile(hRequest, pBuffer, 4095, &dwBuffSize) )
      {
         // report an error
        m_Assync->SetProgress(_T("Failed (can't read http response message)."), 100, false);
        goto cleanup;
      }
      if ( !dwBuffSize )
        break;

      pBuffer[dwBuffSize] = 0;
      sMsg += CString((LPCSTR)pBuffer, dwBuffSize);
    }

		sMsg = _T("Server response body:")  + sMsg;
		m_Assync->SetProgress(sMsg, 0);
	
		// If the first byte of HTTP response is a digit, than assume a legacy way
		// of determining delivery status - the HTTP response starts with a delivery status code
		if(dwBuffSize>0 && pBuffer[0]>='0' && pBuffer[0]<='9')
		{
			m_Assync->SetProgress(_T("Assuming legacy method of determining delivery status (from HTTP response body)."), 0);

			// Get status code from HTTP response
			//if(atoi((LPCSTR)pBuffer)!=200)
      if(  (sMsg.CompareNoCase(_T("OK")) != 0)  || (atoi( (LPCSTR)sMsg.GetBuffer(0) ) != 200) )
			{
				m_Assync->SetProgress(_T("Failed (HTTP response body doesn't start with code 200)."), 100, false);
				goto cleanup;
			}

			break;
		}
		else
		{
			// If the first byte of HTTP response is not a digit, assume that
			// the delivery status should be read from HTTP header
		
			// Check if we have a redirect (302 response code)
			if(bQueryInfo && lHttpStatus==302)
			{	
				// Check for multiple redirects
				if(bRedirect)
				{
					m_Assync->SetProgress(_T("Multiple redirects are not allowed."), 100, false);
					goto cleanup;
				}

				bRedirect = TRUE;

				TCHAR szBuffer[1024]=_T("");
				DWORD dwBuffSize = sizeof(szBuffer)*sizeof(TCHAR);	
				DWORD nIndex = 0;				

				BOOL bQueryInfo = HttpQueryInfo(hRequest, HTTP_QUERY_LOCATION,
						szBuffer,
						&dwBuffSize,
						&nIndex);
				if(!bQueryInfo)
				{
					m_Assync->SetProgress(_T("Failed to redirect."), 100, false);
					goto cleanup;
				}
				else
				{
					// Parse the redirect URL
					ParseURL(szBuffer, szProtocol, 512, szServer, 512, dwPort, szURI, 1024);

					CString sMsg;
					sMsg.Format(_T("Redirecting to %s"), szBuffer);
					m_Assync->SetProgress(sMsg, 0, true);
					continue;
				}
			}

			// Check for server response code - expected code 200
			if(!bQueryInfo || lHttpStatus!=200)
			{
				m_Assync->SetProgress(_T("Failed (HTTP response code is not equal to 200)."), 100, false);
				goto cleanup;
			}
			
			break;
		}
	}

	// Add a message to log
    m_Assync->SetProgress(_T("Error report has been sent OK!"), 100, false);
    bStatus = TRUE;

cleanup:

    if(!bStatus)
    {
        // Add a message to log
        m_Assync->SetProgress(_T("Error sending HTTP request."), 100, false);
    }

    // Clean up
    if(hRequest) 
        InternetCloseHandle(hRequest);

    // Clean up internet handle
    if(hConnect) 
        InternetCloseHandle(hConnect);

    // Clean up internet session
    if(hSession) 
        InternetCloseHandle(hSession);

    // Notify about completion
    m_Assync->SetCompleted(bStatus?0:1);

    return bStatus;
}

BOOL CHttpRequestSender::WriteTextPart(HINTERNET hRequest, CString sName)
{
    BOOL bRet = FALSE;

    /* Write part header */
    CString sHeader;
    bRet= FormatTextPartHeader(sName, sHeader);
    if(!bRet)
    {
        m_Assync->SetProgress(_T("Error formatting text part header."), 0);
        return FALSE;
    }

    strconv_t strconv;
    LPCSTR pszHeader = strconv.t2a(sHeader);
    if(pszHeader==NULL)
    {
        m_Assync->SetProgress(_T("Error converting text part header to ASCII."), 0);
        return FALSE;
    }

    DWORD dwBytesWritten = 0;
    bRet=InternetWriteFile(hRequest, pszHeader, (DWORD)strlen(pszHeader), &dwBytesWritten);
    if(!bRet)
    {
        m_Assync->SetProgress(_T("Error uploading text part header."), 0);
        return FALSE;
    }
    UploadProgress(dwBytesWritten);

    /* Write form data */

    std::map<CString, std::string>::iterator it = m_Request.m_aTextFields.find(sName);
    if(it==m_Request.m_aTextFields.end())
    {
        m_Assync->SetProgress(_T("Error searching for text part header name."), 0);
        return FALSE; 
    }

    size_t nDataSize = it->second.length();
    int pos = 0;    
    DWORD dwBytesRead = 0;
    for(;;)
    {
        if(m_Assync->IsCancelled())
        {
            return FALSE;
        }

        dwBytesRead = (DWORD)MIN(1024, nDataSize-pos);    
        if(dwBytesRead==0)
            break; // EOF

        std::string sBuffer = it->second.substr(pos, dwBytesRead);

        DWORD dwBytesWritten = 0;
        bRet=InternetWriteFile(hRequest, sBuffer.c_str(), dwBytesRead, &dwBytesWritten);
        if(!bRet)
        {
            //m_Assync->SetProgress(_T("Error uploading text part data."), 0);
            DWORD dwError = GetLastError();
            CString sMsg;
            sMsg.Format(_T("Error uploading text part data (code 0x%08x): %s"), dwError, Utility::FormatErrorMsg(dwError));
            m_Assync->SetProgress(sMsg, 0);
            return FALSE;
        }
        UploadProgress(dwBytesWritten);

        pos += dwBytesRead;    
    }

    /* Write part footer */

    CString sFooter;
    bRet= FormatTextPartFooter(sName, sFooter);
    if(!bRet)
    {
        m_Assync->SetProgress(_T("Error formatting text part footer."), 0);
        return FALSE;
    }

    LPCSTR pszFooter = strconv.t2a(sFooter);
    if(pszFooter==NULL)
    {
        m_Assync->SetProgress(_T("Error converting text part footer to ASCII."), 0);
        return FALSE;
    }

    bRet=InternetWriteFile(hRequest, pszFooter, (DWORD)strlen(pszFooter), &dwBytesWritten);
    if(!bRet)
    {
        m_Assync->SetProgress(_T("Error uploading text part footer."), 0);
        return FALSE;
    }
    UploadProgress(dwBytesWritten);

    return TRUE;
}

BOOL CHttpRequestSender::WriteAttachmentPart(HINTERNET hRequest, CString sName)
{
    BOOL bRet = FALSE;

    /* Write part header */
    CString sHeader;
    bRet= FormatAttachmentPartHeader(sName, sHeader);
    if(!bRet)
    {
        m_Assync->SetProgress(_T("Error formatting attachment part header."), 0);
        return FALSE;
    }

    strconv_t strconv;
    LPCSTR pszHeader = strconv.t2a(sHeader);
    if(pszHeader==NULL)
    {
        m_Assync->SetProgress(_T("Error converting attachment part header to ASCII."), 0);
        return FALSE;
    }

    DWORD dwBytesWritten = 0;
    bRet=InternetWriteFile(hRequest, pszHeader, (DWORD)strlen(pszHeader), &dwBytesWritten);
    if(!bRet)
    {
        m_Assync->SetProgress(_T("Error uploading attachment part header."), 0);
        return FALSE;
    }
    UploadProgress(dwBytesWritten);

    /* Write attachment data */

    std::map<CString, CHttpRequestFile>::iterator it = m_Request.m_aIncludedFiles.find(sName);
    if(it==m_Request.m_aIncludedFiles.end())
    {
        m_Assync->SetProgress(_T("Error searching for attachment part name."), 0);
        return FALSE; 
    }

    CString sFileName = it->second.m_sSrcFileName.GetBuffer(0);
    HANDLE hFile = CreateFile(sFileName, 
        GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, NULL, NULL); 
    if(hFile==INVALID_HANDLE_VALUE)
    {    
        m_Assync->SetProgress(_T("Error opening attachment file."), 0);
        return FALSE; 
    }

    BYTE pBuffer[1024];
    DWORD dwBytesRead = 0;
    for(;;)
    {
        if(m_Assync->IsCancelled())
            return FALSE;

        bRet = ReadFile(hFile, pBuffer, 1024, &dwBytesRead, NULL);
        if(!bRet)
        {
            m_Assync->SetProgress(_T("Error reading data from attachment file."), 0);
            CloseHandle(hFile);
            return FALSE;
        }

        if(dwBytesRead==0)
            break; // EOF

        DWORD dwBytesWritten = 0;
        bRet=InternetWriteFile(hRequest, pBuffer, dwBytesRead, &dwBytesWritten);
        if(!bRet)
        {
            m_Assync->SetProgress(_T("Error uploading attachment part data."), 0);
            return FALSE;
        }
        UploadProgress(dwBytesWritten);
    }

    CloseHandle(hFile);

    /* Write part footer */

    CString sFooter;
    bRet= FormatAttachmentPartFooter(sName, sFooter);
    if(!bRet)
    {
        m_Assync->SetProgress(_T("Error formatting attachment part footer."), 0);
        return FALSE;
    }

    LPCSTR pszFooter = strconv.t2a(sFooter);
    if(pszFooter==NULL)
    {
        m_Assync->SetProgress(_T("Error converting attachment part footer to ASCII."), 0);
        return FALSE;
    }

    bRet=InternetWriteFile(hRequest, pszFooter, (DWORD)strlen(pszFooter), &dwBytesWritten);
    if(!bRet)
    {
        m_Assync->SetProgress(_T("Error uploading attachment part footer."), 0);
        return FALSE;
    }
    UploadProgress(dwBytesWritten);

    return TRUE;
}

BOOL CHttpRequestSender::WriteTrailingBoundary(HINTERNET hRequest)
{
    BOOL bRet = FALSE;

    CString sText;
    bRet= FormatTrailingBoundary(sText);
    if(!bRet)
        return FALSE;

    strconv_t strconv;
    LPCSTR pszText = strconv.t2a(sText);
    if(pszText==NULL)
        return FALSE;

    DWORD dwBytesWritten = 0;
    bRet=InternetWriteFile(hRequest, pszText, (DWORD)strlen(pszText), &dwBytesWritten);
    if(!bRet)
        return FALSE;

    UploadProgress(dwBytesWritten);

    return TRUE;
}


BOOL CHttpRequestSender::FormatTextPartHeader(CString sName, CString& sPart)
{
    std::map<CString, std::string>::iterator it = m_Request.m_aTextFields.find(sName);
    if(it==m_Request.m_aTextFields.end())
        return FALSE;

    sPart.Format(m_sTextPartHeaderFmt, m_sBoundary, it->first);    

    return TRUE;
}

BOOL CHttpRequestSender::FormatTextPartFooter(CString sName, CString& sText)
{
    sText = m_sTextPartFooterFmt;
    return TRUE;
}

BOOL CHttpRequestSender::FormatAttachmentPartHeader(CString sName, CString& sText)
{
    std::map<CString, CHttpRequestFile>::iterator it = m_Request.m_aIncludedFiles.find(sName);
    if(it==m_Request.m_aIncludedFiles.end())
        return FALSE; 

    sText.Format(m_sFilePartHeaderFmt, m_sBoundary, it->first, Utility::GetFileName(it->second.m_sSrcFileName), it->second.m_sContentType);
    return TRUE;
}

BOOL CHttpRequestSender::FormatAttachmentPartFooter(CString sName, CString& sText)
{
    sText = m_sFilePartFooterFmt;
    return TRUE;
}  

BOOL CHttpRequestSender::FormatTrailingBoundary(CString& sText)
{
    sText.Format(_T("--%s--\r\n"), m_sBoundary);
    return TRUE;
}

BOOL CHttpRequestSender::CalcRequestSize(LONGLONG& lSize)
{
    lSize = 0;

    // Calculate summary size of all text fields included into request
    std::map<CString, std::string>::iterator it;
    for(it=m_Request.m_aTextFields.begin(); it!=m_Request.m_aTextFields.end(); it++)
    {
        LONGLONG lPartSize;
        BOOL bCalc = CalcTextPartSize(it->first, lPartSize);        
        if(!bCalc)
            return FALSE;
        lSize += lPartSize;
    }

    // Calculate summary size of all files included into report
    std::map<CString, CHttpRequestFile>::iterator it2;
    for(it2=m_Request.m_aIncludedFiles.begin(); it2!=m_Request.m_aIncludedFiles.end(); it2++)
    {
        LONGLONG lPartSize;
        BOOL bCalc = CalcAttachmentPartSize(it2->first, lPartSize);        
        if(!bCalc)
            return FALSE;
        lSize += lPartSize;
    }

    CString sTrailingBoundary;
    FormatTrailingBoundary(sTrailingBoundary);
    lSize += sTrailingBoundary.GetLength();

    return TRUE;
}

BOOL CHttpRequestSender::CalcTextPartSize(CString sName, LONGLONG& lSize)
{
    lSize = 0;

    CString sPartHeader;
    BOOL bFormat = FormatTextPartHeader(sName, sPartHeader);
    if(!bFormat)
        return FALSE;
    lSize += sPartHeader.GetLength();

    std::map<CString, std::string>::iterator it = m_Request.m_aTextFields.find(sName);
    if(it==m_Request.m_aTextFields.end())
        return FALSE; 

    lSize += it->second.length();

    CString sPartFooter;
    bFormat = FormatTextPartFooter(sName, sPartFooter);
    if(!bFormat)
        return FALSE;
    lSize += sPartFooter.GetLength();

    return TRUE;
}

BOOL CHttpRequestSender::CalcAttachmentPartSize(CString sName, LONGLONG& lSize)
{
    lSize = 0;

    CString sPartHeader;
    BOOL bFormat = FormatAttachmentPartHeader(sName, sPartHeader);
    if(!bFormat)
        return FALSE;
    lSize += sPartHeader.GetLength();

    std::map<CString, CHttpRequestFile>::iterator it = m_Request.m_aIncludedFiles.find(sName);
    if(it==m_Request.m_aIncludedFiles.end())
        return FALSE; 

    CString sFileName = it->second.m_sSrcFileName.GetBuffer(0);
    HANDLE hFile = CreateFile(sFileName, 
        GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, NULL, NULL); 
    if(hFile==INVALID_HANDLE_VALUE)
    {    
        return FALSE; 
    }

    LARGE_INTEGER lFileSize;
    BOOL bGetSize = GetFileSizeEx(hFile, &lFileSize);
    if(!bGetSize)
    {
        CloseHandle(hFile);
        return FALSE;
    }

    lSize += lFileSize.QuadPart;
    CloseHandle(hFile);

    CString sPartFooter;
    bFormat = FormatAttachmentPartFooter(sName, sPartFooter);
    if(!bFormat)
        return FALSE;
    lSize += sPartFooter.GetLength();

    return TRUE;
}

// This method updates upload progress status
void CHttpRequestSender::UploadProgress(DWORD dwBytesWritten)
{
    m_dwUploaded += dwBytesWritten;

    float progress = 100*(float)m_dwUploaded/m_dwPostSize;
    m_Assync->SetProgress((int)progress, false);
}

// Parses URL and splits it into URL, port, protocol and so on. This method's code was taken from 
// http://www.codeproject.com/KB/IP/simplehttpclient.aspx
void CHttpRequestSender::ParseURL(LPCTSTR szURL, LPTSTR szProtocol, UINT cbProtocol, 
                                  LPTSTR szAddress, UINT cbAddress, DWORD &dwPort, LPTSTR szURI, UINT cbURI)
{  
    cbURI;
    cbAddress;
    cbProtocol;

    DWORD dwPosition=0;
    BOOL bFlag=FALSE;

    while(_tcslen(szURL)>0 && dwPosition<_tcslen(szURL) && _tcsncmp((szURL+dwPosition), _T(":"), 1))
        ++dwPosition;

    if(!_tcsncmp((szURL+dwPosition+1), _T("/"), 1)){	// is PROTOCOL
        if(szProtocol){
            _TCSNCPY_S(szProtocol, cbProtocol, szURL, dwPosition);
            szProtocol[dwPosition]=0;
        }
        bFlag=TRUE;
    }else{	// is HOST 
        if(szProtocol){
            _TCSNCPY_S(szProtocol, cbProtocol, _T("http"), 4);
            szProtocol[5]=0;
        }
    }

    DWORD dwStartPosition=0;

    if(bFlag){
        dwStartPosition=dwPosition+=3;				
    }else{
        dwStartPosition=dwPosition=0;
    }

    bFlag=FALSE;
    while(_tcslen(szURL)>0 && dwPosition<_tcslen(szURL) && _tcsncmp(szURL+dwPosition, _T("/"), 1))
        ++dwPosition;

    DWORD dwFind=dwStartPosition;

    for(;dwFind<=dwPosition;dwFind++){
        if(!_tcsncmp((szURL+dwFind), _T(":"), 1)){ // find PORT
            bFlag=TRUE;
            break;
        }
    }

    if(bFlag)
    {
        TCHAR sztmp[256]=_T("");
        _TCSNCPY_S(sztmp, 256, (szURL+dwFind+1), dwPosition-dwFind);
        dwPort=_ttol(sztmp);
        int len = dwFind-dwStartPosition;
        _TCSNCPY_S(szAddress, cbAddress, (szURL+dwStartPosition), len);
        szAddress[len]=0;
    }
    else if(!_tcscmp(szProtocol,_T("https")))
    {
        dwPort=INTERNET_DEFAULT_HTTPS_PORT;
        int len = dwPosition-dwStartPosition;
        _TCSNCPY_S(szAddress, cbAddress, (szURL+dwStartPosition), len);
        szAddress[len]=0;
    }
    else 
    {
        dwPort=INTERNET_DEFAULT_HTTP_PORT;
        int len = dwPosition-dwStartPosition;
        _TCSNCPY_S(szAddress, cbAddress, (szURL+dwStartPosition), len);    
        szAddress[len]=0;
    }

    if(dwPosition<_tcslen(szURL))
    { 
        // find URI
        int len = (int)(_tcslen(szURL)-dwPosition);
        _TCSNCPY_S(szURI, cbURI, (szURL+dwPosition), len);
        szURI[len] = 0;
    }
    else
    {
        szURI[0]=0;
    }

    return;
}

