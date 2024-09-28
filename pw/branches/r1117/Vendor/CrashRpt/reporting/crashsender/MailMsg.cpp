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
//  Module: MailMsg.cpp
//
//    Desc: See MailMsg.h
//
// Copyright (c) 2003 Michael Carruth
//
///////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MailMsg.h"
#include "Utility.h"
#include "strconv.h"

CMailMsg::CMailMsg()
{
    m_lpMapiLogon     = NULL;
    m_lpMapiSendMail  = NULL;
    m_lpMapiLogoff    = NULL;
    m_bReady          = FALSE;
}

CMailMsg::~CMailMsg()
{
    if (m_bReady)
        MAPIFinalize();
}


void CMailMsg::SetFrom(CString sAddress)
{  
    strconv_t strconv;
    LPCSTR lpszAddress = strconv.t2a(sAddress.GetBuffer(0));
    m_from = lpszAddress;
}

void CMailMsg::AddRecipient(CString sAddress)
{
    strconv_t strconv;
    LPCSTR lpszAddress = strconv.t2a(sAddress.GetBuffer(0));
	m_to.push_back(lpszAddress);
}

void CMailMsg::SetSubject(CString sSubject)
{
    strconv_t strconv;
    LPCSTR lpszSubject = strconv.t2a(sSubject.GetBuffer(0));
    m_sSubject = lpszSubject;
}

void CMailMsg::SetMessage(CString sMessage) 
{
    strconv_t strconv;
    LPCSTR lpszMessage = strconv.t2a(sMessage.GetBuffer(0));
    m_sMessage = lpszMessage;
};

void CMailMsg::AddAttachment(CString sAttachment, CString sTitle)
{
    strconv_t strconv;
    LPCSTR lpszAttachment = strconv.t2a(sAttachment.GetBuffer(0));
    LPCSTR lpszTitle = strconv.t2a(sTitle.GetBuffer(0));
    m_attachments[lpszAttachment] = lpszTitle;  
}

BOOL CMailMsg::DetectMailClient(CString& sMailClientName)
{
    CRegKey regKey;
    TCHAR buf[1024] = _T("");
    ULONG buf_size = 0;
    LONG lResult;

    lResult = regKey.Open(HKEY_CURRENT_USER, _T("SOFTWARE\\Clients\\Mail"), KEY_READ);
    if(lResult!=ERROR_SUCCESS)
    {
        lResult = regKey.Open(HKEY_LOCAL_MACHINE, _T("SOFTWARE\\Clients\\Mail"), KEY_READ);
    }

    if(lResult==ERROR_SUCCESS)
    {    
        buf_size = 1023;
#pragma warning(disable:4996)
        LONG result = regKey.QueryValue(buf, _T(""), &buf_size);
#pragma warning(default:4996)
        if(result==ERROR_SUCCESS)
        {
            sMailClientName = buf;
            return TRUE;  
        }

        regKey.Close();  
    }
    else
    {
        sMailClientName = "Not Detected";
    }

    return FALSE;
}

BOOL CMailMsg::MAPIInitialize()
{   
    // Determine if there is default email program

    CString sMailClientName;
    if(!DetectMailClient(sMailClientName))
    {
        m_sErrorMsg = _T("Error detecting E-mail client");     
        return FALSE;
    }
    else
    {
        m_sErrorMsg = _T("Detected E-mail client ") + sMailClientName;
    }   

    // Load MAPI.dll

    m_hMapi = ::LoadLibrary(_T("mapi32.dll"));
    if (!m_hMapi)
    {
        m_sErrorMsg = _T("Error loading mapi32.dll");
        return FALSE;
    }

    m_lpMapiLogon = (LPMAPILOGON)::GetProcAddress(m_hMapi, "MAPILogon");
    m_lpMapiSendMail = (LPMAPISENDMAIL)::GetProcAddress(m_hMapi, "MAPISendMail");
    m_lpMapiLogoff = (LPMAPILOGOFF)::GetProcAddress(m_hMapi, "MAPILogoff");

    m_bReady = (m_lpMapiLogon && m_lpMapiSendMail && m_lpMapiLogoff);

    if(!m_bReady)
    {
        m_sErrorMsg = _T("Not found required function entries in mapi32.dll");
    }

    return m_bReady;
}

void CMailMsg::MAPIFinalize()
{
    ::FreeLibrary(m_hMapi);
}

CString CMailMsg::GetEmailClientName()
{
    return m_sEmailClientName;
}

BOOL CMailMsg::Send()
{
    if(m_lpMapiSendMail==NULL)
        return FALSE;

    TStrStrMap::iterator p;
    int                  nIndex = 0;   
    MapiRecipDesc*       pRecipients = NULL;
    int                  nAttachments = 0;
    MapiFileDesc*        pAttachments = NULL;
    ULONG                status = 0;
    MapiMessage          message;

    if(!m_bReady && !MAPIInitialize())
        return FALSE;

    LHANDLE hMapiSession = 0;
    status = m_lpMapiLogon(NULL, NULL, NULL, MAPI_LOGON_UI|MAPI_PASSWORD_UI, NULL, &hMapiSession);
    if(status!=SUCCESS_SUCCESS)
    {
        m_sErrorMsg.Format(_T("MAPILogon has failed with code %X."), status);
        return FALSE;
    }


    pRecipients = new MapiRecipDesc[1+m_to.size()];
    if(!pRecipients)
    {
        m_sErrorMsg = _T("Error allocating memory");
        return FALSE;
    }

    nAttachments = (int)m_attachments.size();
    if (nAttachments)
        pAttachments = new MapiFileDesc[nAttachments];
    if(!pAttachments)
    {
        m_sErrorMsg = _T("Error allocating memory");
        return FALSE;
    }

    // set from
    pRecipients[0].ulReserved = 0;
    pRecipients[0].ulRecipClass = MAPI_ORIG;
    pRecipients[0].lpszAddress = (LPSTR)m_from.c_str();
    pRecipients[0].lpszName = "";
    pRecipients[0].ulEIDSize = 0;
    pRecipients[0].lpEntryID = NULL;

	// set to
	size_t i;
	for(i=0; i<m_to.size(); i++)
	{
		pRecipients[i+1].ulReserved = 0;
		pRecipients[i+1].ulRecipClass = MAPI_TO;
		pRecipients[i+1].lpszAddress = (LPSTR)m_to[i].c_str();
		pRecipients[i+1].lpszName = (LPSTR)m_to[i].c_str();
		pRecipients[i+1].ulEIDSize = 0;
		pRecipients[i+1].lpEntryID = NULL;
	}

    // add attachments
    nIndex=0;   
    for (p = m_attachments.begin(), nIndex = 0;
        p != m_attachments.end(); p++, nIndex++)
    {
        pAttachments[nIndex].ulReserved        = 0;
        pAttachments[nIndex].flFlags           = 0;
        pAttachments[nIndex].nPosition         = 0xFFFFFFFF;
        pAttachments[nIndex].lpszPathName      = (LPSTR)p->first.c_str();
        pAttachments[nIndex].lpszFileName      = (LPSTR)p->second.c_str();
        pAttachments[nIndex].lpFileType        = NULL;
    }

    message.ulReserved                        = 0;
    message.lpszSubject                       = (LPSTR)m_sSubject.c_str();
    message.lpszNoteText                      = (LPSTR)m_sMessage.c_str();
    message.lpszMessageType                   = NULL;
    message.lpszDateReceived                  = NULL;
    message.lpszConversationID                = NULL;
    message.flFlags                           = 0;
    message.lpOriginator                      = pRecipients;
	message.nRecipCount                       = (ULONG)m_to.size();
    message.lpRecips                          = &pRecipients[1];
    message.nFileCount                        = nAttachments;
    message.lpFiles                           = nAttachments ? pAttachments : NULL;

    status = m_lpMapiSendMail(hMapiSession, 0, &message, 0/*MAPI_DIALOG*/, 0);    

    if(status!=SUCCESS_SUCCESS)
    {
        m_sErrorMsg.Format(_T("MAPISendMail has failed with code %X."), status);      
    }

    m_lpMapiLogoff(hMapiSession, NULL, 0, 0);

    if (pRecipients)
        delete [] pRecipients;

    if (nAttachments)
        delete [] pAttachments;

    return (SUCCESS_SUCCESS == status);
}


