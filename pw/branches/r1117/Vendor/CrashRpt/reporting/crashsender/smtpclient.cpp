/************************************************************************************* 
This file is a part of CrashRpt library.
Copyright (c) 2003-2013 The CrashRpt project authors. All Rights Reserved.

Use of this source code is governed by a BSD-style license
that can be found in the License.txt file in the root of the source
tree. All contributing project authors may
be found in the Authors.txt file in the root of the source tree.
***************************************************************************************/

// File: SmtpClient.cpp
// Description: SMTP client.
// Authors: zexspectrum
// Date: 2009

#include "stdafx.h"
#include "smtpclient.h"
#include "Utility.h"
#include "strconv.h"
#include "Base64.h"

//----------------------------------------------------------
// CEmailMessage impl
//----------------------------------------------------------


CEmailMessage::CEmailMessage()
{
}

CEmailMessage::~CEmailMessage()
{
}

CString CEmailMessage::GetSubject()
{
	return m_sSubject;
}

void CEmailMessage::SetSubject(LPCTSTR szSubject)
{
	m_sSubject = szSubject;
}


CString CEmailMessage::GetSenderAddress()
{
	// Return E-mail sender's address.
	return m_sFrom;
}

void CEmailMessage::SetSenderAddress(LPCTSTR szEmailAddress)
{
	// Set E-mail sender address.
	m_sFrom = szEmailAddress;
}
	
void CEmailMessage::AddRecipient(LPCTSTR szEmailAddress)
{
	// Add a recipient address.
	m_aTo.push_back(szEmailAddress);
}

void CEmailMessage::AddRecipients(LPCTSTR szEmailAddresses)
{
	std::vector<CString> aAddresses = Utility::ExplodeStr(szEmailAddresses, _T(", ;"));
	size_t i;
	for(i=0; i<aAddresses.size(); i++)
	{
		// Add a recipient address.
		m_aTo.push_back(aAddresses[i]);
	}
}

int CEmailMessage::GetRecipientCount()
{
	// Return count of recipients.
	return (int)m_aTo.size();
}

CString CEmailMessage::GetRecipientAddress(int nRecipient)
{
	// Return n-th recipient address
	return m_aTo[nRecipient];
}

void CEmailMessage::AddAttachment(LPCTSTR szFileName)
{
	// Add file attachment.
	m_aAttachments.push_back(szFileName);
}

int CEmailMessage::GetAttachmentCount()
{
	// Return count of attachments.
	return (int)m_aAttachments.size();
}

CString CEmailMessage::GetAttachment(int nAttachment)
{
	// Return n-th attachment.
	return m_aAttachments[nAttachment];
}

CString CEmailMessage::GetText()
{
	return m_sText;
}

void CEmailMessage::SetText(LPCTSTR szText)
{
	m_sText = szText;
}

//----------------------------------------------------------
// CSmtpClient impl
//----------------------------------------------------------

CSmtpClient::CSmtpClient()
{
    // Initialize WinSock library
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
	// Ensure result is success
    ATLASSERT(iResult==0); 
    iResult;

	// Default proxy port is 25
    m_nPort = 25;

	m_scn = NULL;
	m_msg = NULL;
}

CSmtpClient::~CSmtpClient()
{
	// Release WinSock
    int iResult = WSACleanup();
	// Check result
    iResult;
    ATLASSERT(iResult==0);
}

int CSmtpClient::SetSmtpServer(CString sServer, int nPort)
{
	// Save SMTP server and port
    m_sServer = sServer;
    m_nPort = nPort;
    return 0;
}

int CSmtpClient::SetAuthParams(LPCTSTR szLogin, LPCTSTR szPassword)
{
	// Set login and password.
	m_sLogin = szLogin;
	m_sPassword = szPassword;
	return 0;
}

int CSmtpClient::SendEmailAssync(CEmailMessage* msg,  AssyncNotification* scn)
{
	// This method starts worker thread that will send the E-mail in 
	// assynchronous mode.

	// Save the notification object
    m_scn = scn;
	m_msg = msg;

	// Create worker thread
    HANDLE hThread = CreateThread(NULL, 0, WorkerThread, (void*)this, 0, NULL);
    if(hThread==NULL)
        return 1; // Error creating thread
	
	// OK
    return 0;
}

DWORD WINAPI CSmtpClient::WorkerThread(VOID* pParam)
{
	// Redirect to SendMail method
    CSmtpClient* pSmtpClient = (CSmtpClient*)pParam;	    
    int nResult = pSmtpClient->SendEmail(pSmtpClient->m_msg);	    
	// Notify the caller about completion
	pSmtpClient->m_scn->SetCompleted(nResult);
    return 0;
}

int CSmtpClient::SendEmail(CEmailMessage* msg)
{
	m_scn->SetProgress(_T("Start sending email"), 0, false);

    std::map<WORD, CString> host_list;

	// Check whether to use proxy server or to resolve SMTP server 
	// address from MX record of domain.
    if(!m_sServer.IsEmpty())
    {
		// Use proxy server 
        host_list[0] = m_sServer;
    }
    else
    {
		// Resolve domain name(s) from DNS record
		int res = ResolveSmtpServerName(msg->GetRecipientAddress(0), host_list);
        if(res!=0)
        {
            m_scn->SetProgress(_T("Error querying DNS record."), 100, false);
            return 1;
        }
    }

	// For each resolved domain name of SMTP server, try to send E-mail to the specified domain.
    std::map<WORD, CString>::iterator it;
    for(it=host_list.begin(); it!=host_list.end(); it++)
    {
		// Check if operation cancelled by user
        if(m_scn->IsCancelled())    
            return 2;

		// Send E-mail to current SMTP server
        int res = SendEmailToRecipient(it->second, msg);
        if(res==0)
        {
			// Succeeded
            m_scn->SetProgress(_T("Finished OK."), 100, false);
            return 0;
        }
        if(res==2)
        {
			// Failure
            m_scn->SetProgress(_T("Critical error detected."), 100, false);
            return 2;
        }
    }

	// Failed to send E-mail
    m_scn->SetProgress(_T("Error sending email."), 100, false);	
    return 1;
}


int CSmtpClient::ResolveSmtpServerName(LPCTSTR szEmailAddress, std::map<WORD, CString>& host_list)
{
	// This methods takes an E-mail address and resolve the domain name(s)
	// associated with this address.

    DNS_RECORD *apResult = NULL;

	// Convert to CString
	CString sEmailAddress = szEmailAddress;
	// Crop server name part from the E-mail address
    CString sServer;
    sServer = sEmailAddress.Mid(sEmailAddress.Find('@')+1);

	// Add a message to log
    CString sStatusMsg;
    sStatusMsg.Format(_T("Quering MX record of domain %s"), sServer);
    m_scn->SetProgress(sStatusMsg, 2);

	// Resolve the domain name(s) of the SMTP servers associated with
	// the E-mail address. Use MX record of DNS.
    int r = DnsQuery(sServer, DNS_TYPE_MX, DNS_QUERY_STANDARD, 
        NULL, (PDNS_RECORD*)&apResult, NULL);

    PDNS_RECORD pRecOrig = apResult;
	// Check result
    if(r==0)
    {
		// Walk through returned DNS records
        while(apResult!=NULL)
        {
			// Look for MX record
            if(apResult->wType==DNS_TYPE_MX)        
            {
				// Save domain name to our list
                CString sServerName = CString(apResult->Data.MX.pNameExchange);        
                host_list[apResult->Data.MX.wPreference] = sServerName;
            }

			// Next record
            apResult = apResult->pNext;
        }

		// Free resources
        DnsRecordListFree(pRecOrig, DnsFreeRecordList);

		// Done
        return 0;
    } 

	// Failed to resolve the address
    sStatusMsg.Format(_T("DNS query failed with code %d"), r);
    m_scn->SetProgress(sStatusMsg, 2);
    return 1;
}


int CSmtpClient::SendEmailToRecipient(CString sSmtpServer, CEmailMessage* msg)
{
	// This method connects to the given SMTP server and tries to send
	// the E-mail message.

    int status = 1; // Resulting status.
    strconv_t strconv; // String convertor
    struct addrinfo *result = NULL; 
    struct addrinfo *ptr = NULL;
    struct addrinfo hints;
	std::string sEncodedLogin;
	std::string sEncodedPassword;	
	CString sBodyTo; //Vojtech: Lines of the "To:" and "Cc:" lines, that will become part of the e-mail header.
    int iResult = -1;  
    CString sPostServer;
	CString sServiceName;	
	SOCKET sock = INVALID_SOCKET;
    CString sMsg, str;
    std::set<CString>::iterator it;
    CString sStatusMsg;
	const int RESPONSE_BUFF_SIZE = 4096;
	char response[RESPONSE_BUFF_SIZE];	
	int res = SOCKET_ERROR;    
    std::string sEncodedFileData;
	bool bESMTP = false;

	// Convert port number to string
    sServiceName.Format(_T("%d"), 
        m_sServer.IsEmpty()?25:m_nPort);  
    
    // Prepare message text (we need to replace "\n" by "\r\n" and remove . from message). 
	CString sMessageText = msg->GetText();
    sMessageText.Replace(_T("\n"),_T("\r\n"));
    sMessageText.Replace(_T("\r\n.\r\n"), _T("\r\n*\r\n"));
    LPCWSTR lpwszMessageText = strconv.t2w(sMessageText.GetBuffer(0));
	// Convert the text to UTF-8 encoding
    std::string sUTF8Text = UTF16toUTF8(lpwszMessageText);
	
	// Check that all attachments exist
	int i;
	for(i=0; i<msg->GetAttachmentCount(); i++)
    {
		CString sFileName = msg->GetAttachment(i);
        if(CheckAttachmentOK(sFileName)!=0)
        {
			// Some attachment file does not present
            sStatusMsg.Format(_T("Attachment not found: %s"), sFileName);
            m_scn->SetProgress(sStatusMsg, 1);
            return 2; // critical error
        }
    }

	// Add a message to log
    sStatusMsg.Format(_T("Getting address info of %s port %s"), sSmtpServer, CString(sServiceName));
    m_scn->SetProgress(sStatusMsg, 1);
	
	// Prepare to open socket
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;  

    LPCSTR lpszSmtpServer = strconv.t2a(sSmtpServer);
    LPCSTR lpszServiceName = strconv.t2a(sServiceName);
    iResult = getaddrinfo(lpszSmtpServer, lpszServiceName, &hints, &result);
    if(iResult!=0)
        goto exit;

	// For each interface do
    for(ptr=result; ptr != NULL ;ptr=ptr->ai_next) 
    {
		// Check if cancelled
        if(m_scn->IsCancelled()) {status = 2; goto exit;}

		// Add a message to log
        sStatusMsg.Format(_T("Creating socket"));
        m_scn->SetProgress(sStatusMsg, 1);

		// Open socket
        sock = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        if(sock==INVALID_SOCKET)
        {
            m_scn->SetProgress(_T("Socket creation failed."), 1);
            goto exit;
        }

		// Add a message to log
        sStatusMsg.Format(_T("Connecting to SMTP server %s port %s"), sSmtpServer, CString(sServiceName));
        m_scn->SetProgress(sStatusMsg, 1);

		// Connect socket
        res = connect(sock, ptr->ai_addr, (int)ptr->ai_addrlen);
        if(res!=SOCKET_ERROR)
            break; // If successfull, break the loop    

		// Close socket
        closesocket(sock);
    }

	// Check if socket open
    if(res==SOCKET_ERROR)
	{
		sStatusMsg.Format(_T("Socket connection error."));
		m_scn->SetProgress(sStatusMsg, 5);
        goto exit;
	}

	// Add a message to log
    sStatusMsg.Format(_T("Connected OK."));
    m_scn->SetProgress(sStatusMsg, 5);

	// Check cancel status
    if(m_scn->IsCancelled()) {status = 2; goto exit;}

	m_scn->SetProgress(_T("Waiting for greeting message from SMTP server..."), 1);
	
	// Wait until server send us greeting message, for example:
	// 220 mail.company.tld ESMTP CommuniGate Pro 5.1.4i is glad to see you!    
	res=SendMsg(sock, NULL, response, RESPONSE_BUFF_SIZE);
    if(res==SOCKET_ERROR)
    {
		// Error - server did not send us greeting message
        sStatusMsg.Format(_T("Failed to receive greeting message from SMTP server (recv code %d)."), res);
        m_scn->SetProgress(sStatusMsg, 1);
        goto exit;
    }
	
	// Check the code server returned (expect code 220).
    if(220!=GetMessageCode(response)) 
    {
		// Invalid greeting
		m_scn->SetProgress(_T("Invalid greeting message."), 1);
        goto exit;
    }
	    
	// Add a message to log
    sStatusMsg.Format(_T("Sending EHLO"));
    m_scn->SetProgress(sStatusMsg, 1);
	    
    res=SendMsg(sock, _T("EHLO CrashSender\r\n"), response, RESPONSE_BUFF_SIZE);
	// Check return code (expect code 250)
    if(res==250)
    {
		sStatusMsg = CString(_T("EHLO command not supported"));
		bESMTP = true;
	}
	
	if(!bESMTP)
	{
		// Server may not understand EHLO, try HELO
		sStatusMsg.Format(_T("Sending HELO"));
		m_scn->SetProgress(sStatusMsg, 1);

		res=SendMsg(sock, _T("HELO CrashSender\r\n"), response, RESPONSE_BUFF_SIZE);
		// Expect code 250
		if(res!=250)
		{
			// Add a message to log
			sStatusMsg = CString(_T("HELO command not supported"));
			m_scn->SetProgress(sStatusMsg, 0);   
			goto exit;
		}
    }	
		
	// Check whether to perform authorization procedure
	if(!m_sLogin.IsEmpty())
	{
		if(!bESMTP)
		{
			sStatusMsg.Format(_T("SMTP server does not support authorization."));
			m_scn->SetProgress(sStatusMsg, 1);
		}

		sStatusMsg.Format(_T("Sending AUTH LOGIN."));
		m_scn->SetProgress(sStatusMsg, 1);

		// SMTP authorization
		// AUTH <SP> LOGIN <CRLF>		
		res=SendMsg(sock, _T("AUTH LOGIN\r\n"), response, RESPONSE_BUFF_SIZE);		
				
    	if(res!=334)
		{
			m_scn->SetProgress(_T("Unexpected server response"), 0);
			goto exit;
		}

		// Send login
		sStatusMsg.Format(_T("Sending login"));
		m_scn->SetProgress(sStatusMsg, 1);
		// Convert login to ASCII
		LPCSTR lpszLogin = strconv.t2a(m_sLogin);
		// And encode it in BASE-64
		sEncodedLogin = base64_encode(reinterpret_cast<const unsigned char*>(lpszLogin),(int)strlen(lpszLogin));
		sEncodedLogin+="\r\n";
		LPCTSTR lpwszLogin = strconv.a2t((LPCSTR)(sEncodedLogin.c_str()));
		memset(response,0,1024);   
		// Send it
		res=SendMsg(sock, lpwszLogin, response, 1024);
		// Check return code - expect 334
		if (res!=334)
		{
			sStatusMsg = _T("Login not accepted");
			m_scn->SetProgress(sStatusMsg, 0);    
			goto exit;
		}
    
		// Send password
		sStatusMsg.Format(_T("Sending password"));
		m_scn->SetProgress(sStatusMsg, 1);
		// Convert to ASCII
		LPCSTR lpszPassword = strconv.t2a(m_sPassword);
		// BASE-64 encode
		sEncodedPassword = base64_encode(reinterpret_cast<const unsigned char*>(lpszPassword),(int)strlen(lpszPassword));
		sEncodedPassword+="\r\n";
		LPCTSTR lpwszPassword = strconv.a2t((LPCSTR)(sEncodedPassword.c_str()));
		memset(response,0,1024);
		// Send it
		res=SendMsg(sock, lpwszPassword, response, 1024);
		if(res!=235)
		{
			sStatusMsg = _T("Authorization failed");
			m_scn->SetProgress(sStatusMsg, 0); 
		}
    }
  
	// Next send sender and recipient info
    sStatusMsg.Format(_T("Sending sender and recipient information"));
    m_scn->SetProgress(sStatusMsg, 1);

	// Send MAIL FROM
	sMsg.Format(_T("MAIL FROM:<%s>\r\n"), msg->GetSenderAddress());	
    res=SendMsg(sock, sMsg, response, RESPONSE_BUFF_SIZE);
	if (res!=250)
	{
        sStatusMsg = _T("Unexpected status code");
        m_scn->SetProgress(sStatusMsg, 0);    
        goto exit;
    }

	// Process multiple e-mail recipients.		
	for(i=0; i<msg->GetRecipientCount(); i++)
	{
		sMsg.Format(i==0 ? _T("To: <%s>\r\n") : _T("Cc: <%s>\r\n"), msg->GetRecipientAddress(i));
		sBodyTo += sMsg;
		sMsg.Format(_T("RCPT TO:<%s>\r\n"), msg->GetRecipientAddress(i));
		res=SendMsg(sock, sMsg, response, RESPONSE_BUFF_SIZE);
		if(res!=250)
		{
			sStatusMsg = _T("Unexpected status code");
			m_scn->SetProgress(sStatusMsg, 0);
			goto exit;
		}
	}
		
    sStatusMsg.Format(_T("Start sending email data"));
    m_scn->SetProgress(sStatusMsg, 1);

    // Send DATA	
    res=SendMsg(sock, _T("DATA\r\n"), response, RESPONSE_BUFF_SIZE);
	if (res!=354)
	{
        sStatusMsg = _T("Unexpected status code");
        m_scn->SetProgress(sStatusMsg, 0);    
        goto exit;
    }

    // Get current time
    time_t cur_time;
    time(&cur_time);
    char szDateTime[64] = "";
    
#if _MSC_VER >= 1400
	struct tm ltimeinfo;
    localtime_s(&ltimeinfo, &cur_time );
	strftime(szDateTime, 64,  "%a, %d %b %Y %H:%M:%S", &ltimeinfo);
#else
	struct tm* ltimeinfo = localtime(&cur_time );
	strftime(szDateTime, 64,  "%a, %d %b %Y %H:%M:%S", ltimeinfo);
#endif
        
    TIME_ZONE_INFORMATION tzi;
    GetTimeZoneInformation(&tzi);

    int diff_hours = -tzi.Bias/60;
    int diff_mins = abs(tzi.Bias%60);
	// Send date header
    str.Format(_T("Date: %s %c%02d%02d\r\n"), strconv.a2t(szDateTime), diff_hours>=0?'+':'-', diff_hours, diff_mins);
    sMsg = str;
	// Send From header
	str.Format(_T("From: <%s>\r\n"), msg->GetSenderAddress());
    sMsg  += str;
    sMsg += sBodyTo;
	// Send subject
	str.Format(_T("Subject: %s\r\n"), msg->GetSubject());
    sMsg += str;
	// Send MIME-Version header
    sMsg += "MIME-Version: 1.0\r\n";
	// Send Content-Type
    sMsg += "Content-Type: multipart/mixed; boundary=KkK170891tpbkKk__FV_KKKkkkjjwq\r\n";
    sMsg += "\r\n\r\n";
    res = SendMsg(sock, sMsg);
    if(res!=sMsg.GetLength())
        goto exit;

    /* Message text */

    sStatusMsg.Format(_T("Sending message text"));
    m_scn->SetProgress(sStatusMsg, 15);

    sMsg =  "--KkK170891tpbkKk__FV_KKKkkkjjwq\r\n";
    sMsg += "Content-Type: text/plain; charset=UTF-8\r\n";
    sMsg += "\r\n";  
    sMsg += sUTF8Text.c_str();
    sMsg += "\r\n";
    res = SendMsg(sock, sMsg);
    if(res!=sMsg.GetLength())
        goto exit;

    sStatusMsg.Format(_T("Sending attachments"));
    m_scn->SetProgress(sStatusMsg, 1);

    /* Attachments. */
	for(i=0; i<msg->GetAttachmentCount(); i++)
    {    
		CString sFileName = msg->GetAttachment(i);
        sFileName.Replace('/', '\\');
        CString sDisplayName = sFileName.Mid(sFileName.ReverseFind('\\')+1);

        // Header
        sMsg =  "\r\n--KkK170891tpbkKk__FV_KKKkkkjjwq\r\n";
        sMsg += "Content-Type: application/octet-stream\r\n";
        sMsg += "Content-Transfer-Encoding: base64\r\n";
        sMsg += "Content-Disposition: attachment; filename=\"";
        sMsg += sDisplayName;
        sMsg += "\"\r\n";
        sMsg += "\r\n";
        res = SendMsg(sock, sMsg);
        if(res!=sMsg.GetLength())
            goto exit;

        // Encode data
        LPBYTE buf = NULL;
        //int buf_len = 0;
        int nEncode=Base64EncodeAttachment(sFileName, sEncodedFileData);
        if(nEncode!=0)
        {
            sStatusMsg.Format(_T("Error BASE64-encoding attachment %s"), sFileName);
            m_scn->SetProgress(sStatusMsg, 1);
            goto exit;
        }

        // Send encoded data
        sMsg = sEncodedFileData.c_str();        
        res = SendMsg(sock, sMsg);
        if(res!=sMsg.GetLength())
            goto exit;

        delete [] buf;
    }

    sMsg =  "\r\n--KkK170891tpbkKk__FV_KKKkkkjjwq--";
    res = SendMsg(sock, sMsg);
    if(res!=sMsg.GetLength())
        goto exit;

    // End of message marker	
    res = SendMsg(sock, _T("\r\n.\r\n"), response, RESPONSE_BUFF_SIZE);
	if (res!=250)
	{
        goto exit;
    }

    // Quit	
    res = SendMsg(sock, _T("QUIT\r\n"), response, RESPONSE_BUFF_SIZE);
	// Expect code 221
	if(res!=221)
	{
        goto exit;
    }

    // OK.
    status = 0;

exit:

    if(m_scn->IsCancelled()) 
        status = 2;

    sStatusMsg.Format(_T("Finished with error code %d"), status);
    m_scn->SetProgress(sStatusMsg, 100, false);

    // Clean up
    closesocket(sock);
    freeaddrinfo(result);  
    return status;
}

int CSmtpClient::GetMessageCode(LPSTR msg)
{
	// This method extracts the return code from string.
	// For example, passing "220 Success" will return 220.
	// The SMTP server may return intermediate result in case of PIPELINING command,	
	// for example, passing "250-ENHANCEDSTATUSCODES" is an intermediate result.
	// For intermediate results, this function returns -1 indicating
	// more information should be received from server.
	// If the message has invalid format, -2 is returned.

	// Check if invalid string
    if(msg==NULL)
        return -1;

	// Split multi-line string
	std::vector<CString> aLines = Utility::ExplodeStr(CString(msg), _T("\n"));
	// Take the last line
	CString sLastLine = aLines[aLines.size()-1];

	// Check message format is valid
	if(sLastLine.GetLength()>4 &&
		isdigit(sLastLine.GetAt(0)) &&
	   isdigit(sLastLine.GetAt(1)) &&
	   isdigit(sLastLine.GetAt(2)))
	{
		if(sLastLine.GetAt(3)==' ')
		{
			// Extract the number
			return atoi(msg);
		}
		else if(sLastLine.GetAt(3)=='-')
		{
			// Intermediate result
			return -1;
		}
	}
	
	// Message format is invalid.
	return -2;
}

int CSmtpClient::CheckAddressSyntax(CString addr)
{
	// Validates E-mail address syntax
    if(addr=="") 
		return FALSE;

	// TODO: add more checks

    return TRUE;
}

std::string CSmtpClient::UTF16toUTF8(LPCWSTR utf16)
{
	// This helper method converts a string from UTF-16 to UTF-8 encoding

    std::string utf8;
    int len = WideCharToMultiByte(CP_UTF8, 0, utf16, -1, NULL, 0, 0, 0);
    if (len>1)
    { 
        char* buf = new char[len+1];	  
        WideCharToMultiByte(CP_UTF8, 0, utf16, -1, buf, len, 0, 0);
        utf8 = buf;
        delete [] buf;
    }

    return utf8;
}

int CSmtpClient::SendMsg(SOCKET sock, LPCTSTR pszMessage, LPSTR pszResponse, UINT uResponseSize)
{	
	// This method sends a message using the specified socket and
	// waits for response.

    strconv_t strconv;

	// Check if cancelled
    if(m_scn->IsCancelled()) {return -1;}
		
	if(pszMessage!=NULL)
	{
		// Determine message length.
	    int msg_len = (int)_tcslen(pszMessage);

		// Convert message to ASCII
		LPCSTR lpszMessageA = strconv.t2a((TCHAR*)pszMessage);

		// Send the message
		int res = send(sock, lpszMessageA, msg_len, 0);	
		if(pszResponse==NULL) 
		{
			m_scn->SetProgress(_T("Send error"), 0);    
			return res; // Failed
		}
	}
	
	for(;;)
	{
		// Read response
		memset(pszResponse, 0, uResponseSize);
		int br = recv(sock, pszResponse, uResponseSize, 0);
		// Check result
		if(br==SOCKET_ERROR)
		{
			m_scn->SetProgress(_T("Receive error"), 0);    
			return br; // Failed
		}

		// Add a message to log
		CString sStatusMsg = CString(pszResponse);
		m_scn->SetProgress(sStatusMsg, 0);    
	
		// Determine status returned
		int nStatusCode = GetMessageCode(pszResponse);
		if(nStatusCode==-1)
			continue; // Intermediate result
		else if(nStatusCode==-2)
			return -1; // Invalid response format
		else
			return nStatusCode; // Ready
	}	
}

int CSmtpClient::CheckAttachmentOK(CString sFileName)
{
	// This method checks if the given file presents.

    struct _stat st;  

    int nResult = _tstat(sFileName, &st);
    if(nResult != 0)
        return 1;  // File not found.

	// File exists.
    return 0;
}

int CSmtpClient::Base64EncodeAttachment(CString sFileName, 
                                        std::string& sEncodedFileData)
{
	// This method encodes the file into BASE-64 encoding.
	// It is suitable for small files only, because it reads
	// entire file contents into memory.

    strconv_t strconv;  
    int uFileSize = 0;
    BYTE* uchFileData = NULL;  
    
	// Check if file exists.	
	long lFileSize = Utility::GetFileSize(sFileName);
    if(lFileSize<0)
        return 1;  // File not found.

    // Allocate buffer of file size
    uFileSize = (int)lFileSize;
    uchFileData = new BYTE[uFileSize];

    // Read file data to buffer.
    FILE* f = NULL;
#if _MSC_VER<1400
    f = _tfopen(sFileName, _T("rb"));
#else
    _tfopen_s(&f, sFileName, _T("rb"));  
#endif 

	// Read file data to buffer
    if(!f || fread(uchFileData, uFileSize, 1, f)!=1)
    {
        delete [] uchFileData;
        uchFileData = NULL;
        return 2; // Coudln't read file data.
    }

	// Close file
    fclose(f);

	// Encode file data.
    sEncodedFileData = base64_encode(uchFileData, uFileSize);

	// Release buffer
    delete [] uchFileData;

    // OK.
    return 0;
}


