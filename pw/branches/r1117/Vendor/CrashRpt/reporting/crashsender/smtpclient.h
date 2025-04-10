/************************************************************************************* 
This file is a part of CrashRpt library.
Copyright (c) 2003-2013 The CrashRpt project authors. All Rights Reserved.

Use of this source code is governed by a BSD-style license
that can be found in the License.txt file in the root of the source
tree. All contributing project authors may
be found in the Authors.txt file in the root of the source tree.
***************************************************************************************/

// File: SmtpClient.h
// Description: SMTP client.
// Authors: zexspectrum
// Date: 2009

#pragma once
#include "stdafx.h"
#include "AssyncNotification.h"

// Class: CEmailMessage
// Brief: Describes an E-mail message to send.
class CEmailMessage
{
public:

	// Constructor.
	CEmailMessage();

	// Destructor.
	~CEmailMessage();

	// Returns E-mail subject.
	CString GetSubject();

	// Sets E-mail subject.
	void SetSubject(LPCTSTR szSubject);

	// Returns E-mail sender's address.
	CString GetSenderAddress();

	// Sets E-mail sender address.
	void SetSenderAddress(LPCTSTR szEmailAddress);
	
	// Adds a recipient address.
	void AddRecipient(LPCTSTR szEmailAddress);

	// Adds multiple recipients (takes the comma-separated list of recipients).
	void AddRecipients(LPCTSTR szEmailAddresses);

	// Returns count of recipients.
	int GetRecipientCount();

	// Returns n-th recipient address
	CString GetRecipientAddress(int nRecipient);

	// Adds file attachment.
	void AddAttachment(LPCTSTR szFileName);

	// Returns count of attachments.
	int GetAttachmentCount();

	// Returns n-th attachment.
	CString GetAttachment(int nAttachment);

	// Returns E-mail body.
	CString GetText();

	// Sets E-mail body.
	void SetText(LPCTSTR szText);

private:

    CString m_sSubject;   // Subject
    CString m_sFrom;      // Sender address
    std::vector<CString> m_aTo; // Recipient addresses    
    CString m_sText;      // Message body
    std::vector<CString> m_aAttachments; // The list of file attachments
};

// Class: CSmtpClient
// Brief: Simple SMTP client.
// Details: Sends an E-mail message to one or several recipients.
//   Supports messages with attachment files. Can send mail in
//   assynchronous mode. Supports SMTP authentication.
class CSmtpClient
{
public:

	// Constructor.
    CSmtpClient();

	// Destructor.
    ~CSmtpClient();

	// Sets SMTP server's address (IP or domain name) and port.
	// If these not set, server name is resolved by recipient's E-mail address.
    int SetSmtpServer(CString sServer, int nPort);

	// Sets login and password for authentication procedure.
	// If these not set, authentication not used.
	int SetAuthParams(LPCTSTR szLogin, LPCTSTR szPassword);

	// Sends E-mail message in synchronous mode.
	// Returns zero on success, otherwise non-zero.
    int SendEmail(CEmailMessage* msg);
		
	// Sends E-mail message in assynchronous mode. This function returns immediately,
	// and message is sent in a worker thread.
	// Returns zero on success, otherwise non-zero.
    int SendEmailAssync(CEmailMessage* msg,  AssyncNotification* scn);

protected:

    // Resolves the domain name(s) of SMTP server by given E-mail address.
	// To resolve the name, MX record of DNS is used.
	// Returns zero on success, otherwise non-zero.
    int ResolveSmtpServerName(LPCTSTR szEmailAddress, std::map<WORD, CString>& host_list);

	// Sends E-mail message to the specified SMTP server.
	// Returns zero on success, otherwise non-zero.
    int SendEmailToRecipient(CString sSmtpServer, CEmailMessage* msg);
	
	// Validates E-mail address syntax.
	// Returns zero on success, otherwise non-zero.
    int CheckAddressSyntax(CString addr);

	// Sends a message to SMTP server and reads response.
	// Returns zero on success, otherwise non-zero.
    int SendMsg(SOCKET sock, LPCTSTR pszMessage, 
		LPSTR pszResponse=0, UINT uResponseSize=0);

	// Extracts the first number from reponse message.
    int GetMessageCode(LPSTR msg);

	// Validates attachment.
	// Returns zero on success, otherwise non-zero.
    int CheckAttachmentOK(CString sFileName);

	// Encodes the given file into BASE-64 encoding and returns the file contents as a string.
	// Returns zero on success, otherwise non-zero.
    int Base64EncodeAttachment(CString sFileName, 
        std::string& sEncodedFileData);

	// Converts a string from UTF-16 (UNICODE) to UTF-8 encoding.
    std::string UTF16toUTF8(LPCWSTR utf16);

	// Worker thread procedure.
    static DWORD WINAPI WorkerThread(VOID* pParam);
	
	/* Variables used internally */

    CString m_sServer;       // SMTP server.
    int m_nPort;             // Port.
	CString m_sLogin;        // Login name (used for SMTP authentication).
	CString m_sPassword;     // Password (used for SMTP authentication).
	CEmailMessage* m_msg;    // Pointer to E-mail message being sent.
    AssyncNotification* m_scn; // Synchronization object.
};


