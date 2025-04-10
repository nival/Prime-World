/************************************************************************************* 
This file is a part of CrashRpt library.
Copyright (c) 2003-2013 The CrashRpt project authors. All Rights Reserved.

Use of this source code is governed by a BSD-style license
that can be found in the License.txt file in the root of the source
tree. All contributing project authors may
be found in the Authors.txt file in the root of the source tree.
***************************************************************************************/

// File: AssyncNotification.h
// Description: Provides a way to communicate between worker thread and the main thread.
// Authors: zexspectrum
// Date: 2009

#pragma once
#include "stdafx.h"

struct AssyncNotification
{
    /* Constructor */
    AssyncNotification(); 
	~AssyncNotification(); 

	void InitLogFile(LPCTSTR szFileName);
	void CloseLogFile();

	CString GetLogFilePath();

    // Resets the event
    void Reset();

    // Sets the progress message and percent completed
    void SetProgress(CString sStatusMsg, int percentCompleted, bool bRelative=true);

    // Sets the percent completed
    void SetProgress(int percentCompleted, bool bRelative=true);

    // Returns the current assynchronous operation progress
    void GetProgress(int& nProgressPct, std::vector<CString>& msg_log);

    // Notifies about assynchronous operation completion
    void SetCompleted(int nCompletionStatus);

    // Blocks until assynchronous operation is completed
    int WaitForCompletion();

    // Cancels the assynchronous operation
    void Cancel();

    // Determines if the assynchronous operation was cancelled
    bool IsCancelled();

    // Waits until the feedback is received
    void WaitForFeedback(int &code);

    // Notifies about feedback is ready to be received
    void FeedbackReady(int code);
private:

    CComAutoCriticalSection m_cs; // Protects internal state
    int m_nCompletionStatus;      // Completion status of the assync operation
    HANDLE m_hCompletionEvent;    // Completion event
    HANDLE m_hCancelEvent;        // Cancel event
    HANDLE m_hFeedbackEvent;      // Feedback event
    int m_nPercentCompleted;      // Percent completed
    std::vector<CString> m_statusLog; // Status log
	  CString m_sLogFile;
    FILE* m_fileLog;	
};
