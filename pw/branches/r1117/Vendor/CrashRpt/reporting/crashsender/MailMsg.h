/************************************************************************************* 
This file is a part of CrashRpt library.
Copyright (c) 2003-2013 The CrashRpt project authors. All Rights Reserved.

Use of this source code is governed by a BSD-style license
that can be found in the License.txt file in the root of the source
tree. All contributing project authors may
be found in the Authors.txt file in the root of the source tree.
***************************************************************************************/

///////////////////////////////////////////////////////////////////////////////
//
//  Module: MailMsg.h
//
//    Desc: This class encapsulates the MAPI mail functions.
//
// Copyright (c) 2003 Michael Carruth
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _MAILMSG_H_
#define _MAILMSG_H_

#include "stdafx.h"

typedef std::map<std::string, std::string> TStrStrMap;

// ===========================================================================
// CMailMsg
// 
// See the module comment at top of file.
//
class CMailMsg  
{
public:

    // Construction/destruction
    CMailMsg();
    virtual ~CMailMsg();

    // Operations
    void AddRecipient(CString sAddress);
    void SetFrom(CString sAddress);
    void SetSubject(CString sSubject);
    void SetMessage(CString sMessage);
    void AddAttachment(CString sAttachment, CString sTitle = _T(""));

    BOOL MAPIInitialize();
    void MAPIFinalize();

    static BOOL DetectMailClient(CString& sMailClientName);
    CString GetEmailClientName();
    BOOL Send();
    CString GetLastErrorMsg(){ return m_sErrorMsg; }

protected:

    std::string    m_from;                       // From <address,name>
    std::vector<std::string> m_to;               // To: array of <address,name>
    TStrStrMap     m_attachments;                // Attachment <file,title>
    std::string    m_sSubject;                   // EMail subject
    std::string    m_sMessage;                   // EMail message

    HMODULE        m_hMapi;                      // Handle to MAPI32.DLL
    LPMAPILOGON    m_lpMapiLogon;                // Mapi func pointer
    LPMAPISENDMAIL m_lpMapiSendMail;             // Mapi func pointer
    LPMAPILOGOFF   m_lpMapiLogoff;               // Mapi func pointer

    BOOL           m_bReady;                     // MAPI is loaded
    CString        m_sEmailClientName;

    CString        m_sErrorMsg;
};

#endif	// _MAILMSG_H_
