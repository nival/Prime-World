/************************************************************************************* 
This file is a part of CrashRpt library.
Copyright (c) 2003-2013 The CrashRpt project authors. All Rights Reserved.

Use of this source code is governed by a BSD-style license
that can be found in the License.txt file in the root of the source
tree. All contributing project authors may
be found in the Authors.txt file in the root of the source tree.
***************************************************************************************/

// File: CrashDescReader.h
// Description: Crash description XML file reader.
// Authors: zexspectrum
// Date: 2010

#pragma once
#include "stdafx.h"
#include <map>
#include "tinyxml.h"

class CCrashDescReader
{
public:

    CCrashDescReader();
    ~CCrashDescReader();

    int Load(CString sFileName);

    bool m_bLoaded;

    DWORD m_dwGeneratorVersion;

    CString m_sCrashGUID;
    CString m_sAppName;
    CString m_sAppVersion;
    CString m_sImageName;
    CString m_sOperatingSystem;
    BOOL    m_bOSIs64Bit;
    CString m_sSystemTimeUTC;
    CString m_sGeoLocation;

    DWORD m_dwExceptionType;
    DWORD m_dwExceptionCode;

    DWORD m_dwFPESubcode;

    CString m_sInvParamExpression;
    CString m_sInvParamFunction;
    CString m_sInvParamFile;
    DWORD m_dwInvParamLine;

    CString m_sUserEmail;
    CString m_sProblemDescription;

    CString m_sMemoryUsageKbytes;
    CString m_sGUIResourceCount;
    CString m_sOpenHandleCount;

    std::map<CString, CString> m_aFileItems;
    std::map<CString, CString> m_aCustomProps;

private:

    int LoadXmlv10(TiXmlHandle hDoc);
};

