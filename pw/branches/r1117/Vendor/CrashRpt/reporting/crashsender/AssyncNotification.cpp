/************************************************************************************* 
This file is a part of CrashRpt library.
Copyright (c) 2003-2013 The CrashRpt project authors. All Rights Reserved.

Use of this source code is governed by a BSD-style license
that can be found in the License.txt file in the root of the source
tree. All contributing project authors may
be found in the Authors.txt file in the root of the source tree.
***************************************************************************************/

#include "stdafx.h"
#include "AssyncNotification.h"
#include "strconv.h"

AssyncNotification::AssyncNotification()
{
    // Init variables
    m_hCompletionEvent = CreateEvent(0, FALSE, FALSE, 0);
    m_hCancelEvent = CreateEvent(0, FALSE, FALSE, 0);
    m_hFeedbackEvent = CreateEvent(0, FALSE, FALSE, 0);
	// Init handle to log file
    m_fileLog = NULL;
	
    Reset();
}

AssyncNotification::~AssyncNotification()
{
	CloseLogFile();
}

void AssyncNotification::CloseLogFile()
{
	if(m_fileLog != NULL)
	{
		fclose(m_fileLog);
		m_fileLog = NULL;
	}
}

void AssyncNotification::InitLogFile(LPCTSTR szFileName)
{
	// Open log file
    m_sLogFile = szFileName;
#if _MSC_VER<1400
    m_fileLog = _tfopen(m_sLogFile, _T("wt"));
#else
    _tfopen_s(&m_fileLog, m_sLogFile.GetBuffer(0), _T("wt"));
#endif
    fprintf(m_fileLog, "%c%c%c", 0xEF, 0xBB, 0xBF); // UTF-8 signature
}

CString AssyncNotification::GetLogFilePath()
{
	return m_sLogFile;
}

void AssyncNotification::Reset()
{ 
    // Reset the event

    m_cs.Lock(); // Acquire lock

    m_nCompletionStatus = -1;    
    m_nPercentCompleted = 0;
    m_statusLog.clear();

    ResetEvent(m_hCancelEvent);
    ResetEvent(m_hCompletionEvent);
    ResetEvent(m_hFeedbackEvent);

    m_cs.Unlock(); // Free lock
}

void AssyncNotification::SetProgress(CString sStatusMsg, int percentCompleted, bool bRelative)
{
    m_cs.Lock(); // Acquire lock

    m_statusLog.push_back(sStatusMsg);

	if(m_fileLog)
	{
	    strconv_t strconv;
	    LPCSTR szLine = strconv.t2utf8(sStatusMsg);
	    fprintf(m_fileLog, szLine);
	    fprintf(m_fileLog, "\n");
	}

    if(bRelative) // Update progress relatively to its previous value
    {
        m_nPercentCompleted += percentCompleted;
        if(m_nPercentCompleted>100)
            m_nPercentCompleted = 100;      
    }
    else // Update progress relatively to zero
    {
        m_nPercentCompleted = percentCompleted;
    }

    m_cs.Unlock(); // Free lock
}

void AssyncNotification::SetProgress(int percentCompleted, bool bRelative)
{
    m_cs.Lock(); // Acquire lock

    if(bRelative) // Update progress relatively to its previous value
    {
        m_nPercentCompleted += percentCompleted;
        if(m_nPercentCompleted>100)
            m_nPercentCompleted = 100;      
    }
    else // Update progress relatively to zero
    {
        m_nPercentCompleted = percentCompleted;
    }

    m_cs.Unlock(); // Free lock
}

void AssyncNotification::GetProgress(int& nProgressPct, std::vector<CString>& msg_log)
{
    msg_log.clear(); // Init message log (clear it)

    m_cs.Lock(); // Acquire lock

    nProgressPct = m_nPercentCompleted;
    msg_log = m_statusLog;
    m_statusLog.clear();

    m_cs.Unlock(); // Free lock
}

void AssyncNotification::SetCompleted(int nCompletionStatus)
{
    // Notifies about assynchronious operation completion
    m_cs.Lock(); // Acquire lock
    m_nCompletionStatus = nCompletionStatus;
    m_cs.Unlock(); // Free lock
    SetEvent(m_hCompletionEvent); // Set event
}

int AssyncNotification::WaitForCompletion()
{
    // Blocks until assynchronous operation is completed
    WaitForSingleObject(m_hCompletionEvent, INFINITE);

    // Get completion status
    int status = -1;
    m_cs.Lock(); // Acquire lock
    status = m_nCompletionStatus;
    m_cs.Unlock(); // Free lock

    return status;
}

void AssyncNotification::Cancel()
{
    // Cansels the assync operation
    SetProgress(_T("[cancelled_by_user]"), 0);
    SetEvent(m_hCancelEvent);
}

bool AssyncNotification::IsCancelled()
{
    // Determines if the assync operation is cancelled or not
    DWORD dwWaitResult = WaitForSingleObject(m_hCancelEvent, 0);
    if(dwWaitResult==WAIT_OBJECT_0)
    {
        SetEvent(m_hCancelEvent);      
        return true;
    }

    return false;
}

void AssyncNotification::WaitForFeedback(int &code)
{
    // Waits until the main thread's signal
    ResetEvent(m_hFeedbackEvent);      
    WaitForSingleObject(m_hFeedbackEvent, INFINITE);
    m_cs.Lock();
    code = m_nCompletionStatus;
    m_cs.Unlock();
}

void AssyncNotification::FeedbackReady(int code)
{
    // Sends signal to the waiting thread
    m_cs.Lock();
    m_nCompletionStatus = code;
    m_cs.Unlock();
    SetEvent(m_hFeedbackEvent);      
}
