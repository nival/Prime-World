/************************************************************************************* 
This file is a part of CrashRpt library.
Copyright (c) 2003-2013 The CrashRpt project authors. All Rights Reserved.

Use of this source code is governed by a BSD-style license
that can be found in the License.txt file in the root of the source
tree. All contributing project authors may
be found in the Authors.txt file in the root of the source tree.
***************************************************************************************/

// File: httpsend.h
// Description: Sends error report over HTTP connection.
// Authors: zexspectrum
// Date: 2009

#pragma once
#include "stdafx.h"
#include "AssyncNotification.h"


struct CHttpRequestFile
{  
    CString m_sSrcFileName;  // Name of the file attachment.
    CString m_sContentType;  // Content type.
};

// HTTP request information
class CHttpRequest
{
public:
    CString m_sUrl;      // Script URL  
    std::map<CString, std::string> m_aTextFields;    // Array of text fields to include into POST data
    std::map<CString, CHttpRequestFile> m_aIncludedFiles; // Array of binary files to include into POST data
};

// Sends HTTP request
// See also: RFC 1867 - Form-based File Upload in HTML (http://www.ietf.org/rfc/rfc1867.txt)
class CHttpRequestSender
{
public:

    CHttpRequestSender();

    // Sends HTTP request assynchroniously
    BOOL SendAssync(CHttpRequest& Request, AssyncNotification* an);

private:

    // Worker thread procedure
    static DWORD WINAPI WorkerThread(VOID* pParam);  

    BOOL InternalSend();

    // Used to calculate summary size of the request
    BOOL CalcRequestSize(LONGLONG& lSize);
    BOOL FormatTextPartHeader(CString sName, CString& sText);
    BOOL FormatTextPartFooter(CString sName, CString& sText);  
    BOOL FormatAttachmentPartHeader(CString sName, CString& sText);
    BOOL FormatAttachmentPartFooter(CString sName, CString& sText);
    BOOL FormatTrailingBoundary(CString& sBoundary);
    BOOL CalcTextPartSize(CString sFileName, LONGLONG& lSize);
    BOOL CalcAttachmentPartSize(CString sFileName, LONGLONG& lSize);
    BOOL WriteTextPart(HINTERNET hRequest, CString sName);
    BOOL WriteAttachmentPart(HINTERNET hRequest, CString sName);
    BOOL WriteTrailingBoundary(HINTERNET hRequest);
    void UploadProgress(DWORD dwBytesWritten);

    // This helper function is used to split URL into several parts
    void ParseURL(LPCTSTR szURL, LPTSTR szProtocol, UINT cbProtocol,
        LPTSTR szAddress, UINT cbAddress, DWORD &dwPort, LPTSTR szURI, UINT cbURI);

    CHttpRequest m_Request;       // HTTP request being sent
    AssyncNotification* m_Assync; // Used to communicate with the main thread  

    CString m_sFilePartHeaderFmt;
    CString m_sFilePartFooterFmt;
    CString m_sTextPartHeaderFmt;
    CString m_sTextPartFooterFmt;
    CString m_sBoundary;
    DWORD m_dwPostSize;
    DWORD m_dwUploaded;
};


