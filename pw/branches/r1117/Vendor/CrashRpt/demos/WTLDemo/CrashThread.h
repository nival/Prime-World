/************************************************************************************* 
This file is a part of CrashRpt library.
Copyright (c) 2003-2013 The CrashRpt project authors. All Rights Reserved.

Use of this source code is governed by a BSD-style license
that can be found in the License.txt file in the root of the source
tree. All contributing project authors may
be found in the Authors.txt file in the root of the source tree.
***************************************************************************************/

#pragma once
#include "stdafx.h"
#include "CrashRpt.h"


struct CrashThreadInfo
{  
    HANDLE m_hWakeUpEvent;
    bool m_bStop;
    int m_ExceptionType;
};

DWORD WINAPI CrashThread(LPVOID pParam);

void test_generate_report();

